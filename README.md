# ESP8266 & ESP-01S Transceiver for Robot Soccer (UKM Roboholic)

## 📖 Deskripsi Proyek
Proyek ini adalah sistem komunikasi *transceiver* nirkabel yang dirancang untuk mengendalikan *mobil robot soccer*. Sistem ini memungkinkan pengiriman data kontrol secara *real-time* dengan latensi rendah di arena pertandingan.
*(Catatan: Ini adalah proyek kelompok, repositori ini dikhususkan untuk mendokumentasikan peran teknis dan implementasi hardware yang saya kerjakan).*

## 🎯 Peran Saya (Hardware & System Integration)
Dalam tim ini, saya bertanggung jawab penuh sebagai **Hardware Executor**, yang mencakup:
* Merancang dan menggambar skematik rangkaian kelistrikan.
* Membuat program untuk controller (ESP-8266) dan program untuk robot (ESP-01S).
* Memilih spesifikasi komponen (ESP8266, ESP-01S, motor driver, dll) yang paling efisien untuk kebutuhan daya dan ukuran mobil.
* Melakukan penyolderan, perakitan fisik (*wiring*), dan *troubleshooting* pada level sirkuit kelistrikan.
* Memastikan konektivitas fisik stabil saat robot bermanuver pada kecepatan tinggi.

## 🛠️ Alat dan Komponen (Bill of Materials)
* **Mikrokontroler:** NodeMCU ESP8266 & Modul ESP-01S
* **Aktuator/Motor:** DC Gear TT Motor
* **Motor Driver:** DRV8833
* **Sumber Daya:** Li-Ion 14500/AA 2 Cell 7.4V 550mAh
* **Komponen Pasif/Lainnya:** Kapasitor 470uF 16V, PCB dot matrix 5x7cm, Mini 360 Buck Converter, slide switch SPDT 3 pin, push button, pin header female, socket JST-PH2.0 2 pin, kabel tunggal 0.5mm, spacer 1,4cm, 2WD Robot Car Chassis Kit, 3D printed custom part.

## 📐 Skematik dan Arsitektur Hardware
<img width="777" height="504" alt="Schematic_Fritzing" src="https://github.com/user-attachments/assets/65cea548-37de-450b-b4e3-1ef8c0ac2816" />

Alasan teknis di balik desain ini:
* **Penggunaan ESP-01S:** Selain karena *form factor*-nya yang sangat kecil sehingga menghemat ruang pada sasis mobil robot, Mikrokontroller ini juga sudah lama tidak saya gunakan sehingga saya ingin memanfaatkannya untuk suatu projek, meski ukurannya yang kecil namun tetap memiliki kemampuan komunikasi WiFi/ESP-NOW yang mumpuni.
* **Penggunaan ESP-8266:** Saat membuat proyek ini saya belum memiliki ESP32 dan mikrokontroller ini juga senasib dengan ESP-01S yang sudah lama tidak digunakan, maka saya gabungkan ke dalam proyek ini. Mengingat ESP-8266 juga memiliki kemampuan WiFi/ESP-NOW yang cocok untuk proyek transceiver ini.
* **Pemilihan DRV8833:** Sama seperti ESP-01S, motor driver ini memiliki *form factor* yang kecil namun cukup powerfull dibandingkan dengan motor driver dual channel lainnya, mengingat proyek ini disusun di atas PCB dot matrix dengan ukuran 5x7cm.
* **Manajemen Daya:** Karena ESP-01S dan DRV8833 memiliki operating voltage yang berbeda dan suplai daya yang digunakan adalah 7.4V, maka diperlukan mini 360 buck converter sebagai penurun tegangan untuk menghidupkan ESP-01S dengan output voltage yang stabil di angka 3.3V. Penambahan kapasitor 470uF pada jalur power ESP-01S juga berguna untuk mem-*filter* noise dari motor driver DRV8833 sehingga mencegah ESP-01S restart sendiri.

## 🚧 Tantangan Teknis & Pemecahan Masalah
Selama proses eksekusi fisik, ada beberapa kendala yang berhasil diatasi:
1. **Interferensi Sinyal/Daya:** Sempat terjadi penurunan voltase (*voltage drop*) saat motor bergerak tiba-tiba. *Solusi: Saya menambahkan kapasitor 470 uF pada jalur daya dan memisahkan ground antara logic dan motor.*
2. **Keterbatasan Pin ESP-01S:** ESP-01S hanya memiliki 2 pin GPIO yang di artinya ia hanya bisa digunakan untuk menggerakkan 1 motor, sedangkan robot soccer ini membutuhkan 2 motor untuk bisa berkendara seperti mobil. *Solusi: saya mengalokasikan pin RX dan TX pada ESP-01S sebagai pin output yang digunakan untuk memberikan sinyal ke motor driver untuk menggerakkan motor ke-2.*
3. **Hasil 3D Print yang Kurang Akurat:** sempat terjadi salah ukur untuk bagian *penggiring* yang dicetak 3D dengan desain custom akibat dari minimnya informasi ukuran chassis yang digunakan, dan pengukuran manual menggunakan sigmat/jangka sorong digital. *Solusi: melubangi beberapa bagian menggunakan bor agar baut pengencang bisa terpasang pada chassis.*
4. **Kapasitas Baterai yang Kecil:** karena durasi pertandingan cukup lama, kapasitas batertai 550mAh kurang bertahan lama *Solusi: mengganti baterai yang semula berukuran 14500/AA dengan kapasitas 550mAh menjadi baterai 18650 dengan kapasitas 2000mAh*

## 📸 Dokumentasi Perakitan
* [Proses penyolderan PCB]
  <br>
  <img width="360" height="640" alt="Proses Solder PCB" src="https://github.com/user-attachments/assets/958c062f-9af1-4326-a8e4-e75cfc008ed4" />
  
* [Proses desain 3D untuk penggiring bola]
  <br>
  <img width="910" height="404" alt="Screenshot_6" src="https://github.com/user-attachments/assets/8b29bd80-9448-4aaa-b34f-934f8bacdbd5" />
  
* [Hasil Penyolderan PCB]
  <br>
  <img width="360" height="640" alt="Hasil PCB Setelah Solder Back" src="https://github.com/user-attachments/assets/b173e35a-7c85-4499-86ab-833dfaf00de5" />
  <img width="360" height="640" alt="Hasil PCB Setelah Solder Front" src="https://github.com/user-attachments/assets/f5b09752-82f3-4184-86e4-e0f989bdbdd4" />

* [Robot Soccer]
  <br>
  <img width="720" height="auto" alt="Robot Soccer" src="https://github.com/user-attachments/assets/24727ddc-9e39-4302-9eb8-cf3330ffd9cc" />
  <img width="400" height="300" alt="Robot Soccer 2" src="https://github.com/user-attachments/assets/9c9e0a5c-9d9b-439d-9929-1b8102594b12" />
  <img width="400" height="300" alt="Robot Soccer 4" src="https://github.com/user-attachments/assets/cf8fb1b0-19c5-45a8-aaa8-fd19bfd01332" />
  <img width="300" height="400" alt="Robot Soccer 3" src="https://github.com/user-attachments/assets/44389cc7-e8df-4007-bdcd-cad5dc1d7859" />
