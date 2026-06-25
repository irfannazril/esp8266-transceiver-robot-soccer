/*
   KODE PENGIRIM (SENDER) - Untuk NodeMCU
   Pastikan Board dipilih: NodeMCU 1.0
*/
#include <ESP8266WiFi.h>
#include <espnow.h>

// ==================================================
// GANTI DENGAN MAC ADDRESS ESP-01S 
// Contoh jika MAC: A0:20:A6:12:34:56
// Tulis: {0xA0, 0x20, 0xA6, 0x12, 0x34, 0x56}
uint8_t broadcastAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
// ==================================================

// Struct untuk mengirim pesan ke Receiver (Sama persis dengan Receiver)
typedef struct pesan_struct {
  int dinamoStatus = 0;
} pesan_struct;

pesan_struct dataKirim;

// Pin push button
const int tombolMaju = D1; 
const int tombolMundur = D2;
const int tombolKiri = D3;
const int tombolKanan = D4;

void setup() {
  Serial.begin(115200);
  
  pinMode(tombolMaju, INPUT_PULLUP);
  pinMode(tombolMundur, INPUT_PULLUP);
  pinMode(tombolKiri, INPUT_PULLUP);
  pinMode(tombolKanan, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error init ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  
  Serial.println("Siap Mengirim...");
}

void loop() {
  // Baca pin push button
  int valueMaju = digitalRead(tombolMaju);
  int valueMundur = digitalRead(tombolMundur);
  int valueKiri = digitalRead(tombolKiri);
  int valueKanan = digitalRead(tombolKanan);

  if (valueMaju == LOW) {
    dataKirim.dinamoStatus = 1; // Kirim sinyal MAJU
  } else if (valueMundur == LOW) {
    dataKirim.dinamoStatus = 2; // Kirim sinyal MUNDUR
  } else if (valueKiri == LOW) {
    dataKirim.dinamoStatus = 3; // Kirim sinyal Kiri
  } else if (valueKanan == LOW) {
    dataKirim.dinamoStatus = 4; // Kirim sinyal Kanan
  } else {
    dataKirim.dinamoStatus = 0; // Kirim sinyal Default
  }

  // Kirim data via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *) &dataKirim, sizeof(dataKirim));

  delay(20); // Jeda sedikit agar stabil
}
