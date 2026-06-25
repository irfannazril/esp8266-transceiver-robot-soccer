/*
   KODE PENERIMA (RECEIVER) - Untuk ESP-01S
   Board: Generic ESP8266 Module
   Fungsi: Menerima data ESP-NOW dan menggerakkan DRV8833
*/
#include <ESP8266WiFi.h>
#include <espnow.h>

// Struktur pesan HARUS SAMA PERSIS dengan Sender
typedef struct pesan_struct {
  int dinamoStatus = 0;
} pesan_struct;

pesan_struct dataTerima;

// Definisi Pin ESP-01S untuk DRV8833
// Menggunakan GPIO 0, 2, 1 (TX), 3 (RX)
const int MOTOR_A_1 = 0;  // GPIO 0
const int MOTOR_A_2 = 2;  // GPIO 2
const int MOTOR_B_1 = 3;  // GPIO 3 (RX Pin)
const int MOTOR_B_2 = 1;  // GPIO 1 (TX Pin)

// Callback saat data diterima
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&dataTerima, incomingData, sizeof(dataTerima));
  
  // Debugging tidak bisa via Serial karena pin Serial dipakai motor
  // Langsung eksekusi gerak
  gerakkanMotor(dataTerima.dinamoStatus);
}

void setup() {
  // Matikan fungsi Serial agar pin TX(1) dan RX(3) bisa jadi GPIO biasa
  // Namun, tidak memanggil Serial.begin() saja sudah cukup.
  // Set semua pin sebagai OUTPUT
  pinMode(MOTOR_A_1, OUTPUT);
  pinMode(MOTOR_A_2, OUTPUT);
  pinMode(MOTOR_B_1, OUTPUT); // RX bisa jadi output digital
  pinMode(MOTOR_B_2, OUTPUT); // TX bisa jadi output digital (Function 3)
  
  // Set fungsi pin TX/RX ke GPIO (kadang otomatis, tapi ini memastikan)
  FUNCTION_3; 
  FUNCTION_0;

  // Pastikan motor mati saat awal
  stopMotor();

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Loop kosong, semua dikerjakan di OnDataRecv
}

void gerakkanMotor(int perintah) {
  switch (perintah) {
    case 1: // MAJU
      // Motor Kiri Maju, Motor Kanan Maju
      digitalWrite(MOTOR_A_1, HIGH); digitalWrite(MOTOR_A_2, LOW);
      digitalWrite(MOTOR_B_1, HIGH); digitalWrite(MOTOR_B_2, LOW);
      break;

    case 2: // MUNDUR
      // Motor Kiri Mundur, Motor Kanan Mundur
      digitalWrite(MOTOR_A_1, LOW); digitalWrite(MOTOR_A_2, HIGH);
      digitalWrite(MOTOR_B_1, LOW); digitalWrite(MOTOR_B_2, HIGH);
      break;

    case 3: // KIRI (Spin Turn)
      // Motor Kiri Mundur, Motor Kanan Maju
      digitalWrite(MOTOR_A_1, LOW); digitalWrite(MOTOR_A_2, HIGH);
      digitalWrite(MOTOR_B_1, HIGH); digitalWrite(MOTOR_B_2, LOW);
      break;
      
    case 4: // KANAN (Spin Turn)
      // Motor Kiri Maju, Motor Kanan Mundur
      digitalWrite(MOTOR_A_1, HIGH); digitalWrite(MOTOR_A_2, LOW);
      digitalWrite(MOTOR_B_1, LOW); digitalWrite(MOTOR_B_2, HIGH);
      break;

    default: // STOP (0 atau sinyal lain)
      stopMotor();
      break;
  }
}

void stopMotor() {
  digitalWrite(MOTOR_A_1, LOW);
  digitalWrite(MOTOR_A_2, LOW);
  digitalWrite(MOTOR_B_1, LOW);
  digitalWrite(MOTOR_B_2, LOW);
}
