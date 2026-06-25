# ESP8266 & ESP-01S Transceiver for Robot Soccer (UKM Roboholic)

## 📖 Deskripsi Proyek
Proyek ini adalah sistem komunikasi *transceiver* nirkabel yang dirancang untuk mengendalikan *mobil robot soccer*. Sistem ini memungkinkan pengiriman data kontrol secara *real-time* dengan latensi rendah di arena pertandingan.
*(Catatan: Ini adalah proyek kelompok, repositori ini dikhususkan untuk mendokumentasikan peran teknis dan implementasi hardware yang saya kerjakan).*

## 🎯 Peran Saya (Hardware & System Integration)
Dalam tim ini, saya bertanggung jawab penuh sebagai **Hardware Executor**, yang mencakup:
* Merancang dan menggambar skematik rangkaian kelistrikan.
* Memilih spesifikasi komponen (ESP8266, ESP-01S, motor driver, dll) yang paling efisien untuk kebutuhan daya dan ukuran mobil.
* Melakukan penyolderan, perakitan fisik (*wiring*), dan *troubleshooting* pada level sirkuit kelistrikan.
* Memastikan konektivitas fisik stabil saat robot bermanuver pada kecepatan tinggi.

## 🛠️ Alat dan Komponen (Bill of Materials)
* **Mikrokontroler:** NodeMCU ESP8266 & Modul ESP-01S
* **Aktuator/Motor:** DC Gear TT Motor
* **Motor Driver:** DRV8833
* **Sumber Daya:** Li-Ion 14500/AA 2 Cell 7.4V 550mAh
* **Komponen Pasif/Lainnya:** Kapasitor 470uF 16V, PCB dot matrix 5x7cm, Mini 360 Buck Converter, push button, pin header female, socket JST-PH2.0 2 pin, kabel tunggal 0.5mm, spacer 1,4cm, 2WD Robot Car Chassis Kit, 3D printed custom part.

## 📐 Skematik dan Arsitektur Hardware
*(Catatan untuk Anda: Di bagian ini, unggah gambar skematik yang Anda buat).*
![Skematik Rangkaian](link_gambar_skematik_anda.png)

Alasan teknis di balik desain ini:
* **Penggunaan ESP-01S:** Dipilih karena *form factor*-nya yang sangat kecil sehingga menghemat ruang pada sasis mobil robot, namun tetap memiliki kemampuan komunikasi WiFi/ESP-NOW yang mumpuni.
* **Manajemen Daya:** (Ceritakan sedikit bagaimana Anda mengatur agar mikrokontroler tidak *restart* saat motor menarik arus besar, misal penggunaan kapasitor atau pemisahan sumber daya).

## 🚧 Tantangan Teknis & Pemecahan Masalah
Selama proses eksekusi fisik, ada beberapa kendala yang berhasil diatasi:
1. **Interferensi Sinyal/Daya:** Sempat terjadi penurunan voltase (*voltage drop*) saat motor bergerak tiba-tiba. *Solusi: Saya menambahkan kapasitor x mF pada jalur daya dan memisahkan ground antara logic dan motor.*
2. **Keterbatasan Pin ESP-01S:** (Ceritakan bagaimana Anda memaksimalkan pin GPIO yang sedikit pada ESP-01S untuk mengendalikan robot).

## 📸 Dokumentasi Perakitan
*(Unggah foto-foto proses penyolderan, foto saat robot belum ditutup casing, atau foto saat pengujian di breadboard).*
* [Foto proses penyolderan PCB]
* [Foto integrasi mikrokontroler dengan motor driver]
