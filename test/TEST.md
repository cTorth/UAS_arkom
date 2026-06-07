# Dokumen Pengujian Sistem (System Testing Report)

Dokumen ini memuat data hasil pengujian fungsionalitas, akurasi sensor, serta pengujian *timing* (respons waktu) pada proyek **Smart Parking System** berbasis Arduino Uno. Pengujian dilakukan melalui platform simulasi Wokwi untuk memastikan arsitektur *software* dan *hardware* bekerja sesuai dengan spesifikasi kode program terbaru.

---

## 1. Rencana Pengujian (Test Plan)
Pengujian dibagi menjadi tiga tahap utama:
1. **Uji Akurasi Sensor:** Membandingkan jarak input objek pada simulasi dengan hasil pembacaan kalkulasi linear di program Arduino.
2. **Uji Logika Kondisional (State Machine Test):** Memastikan transisi kondisi (AMAN, WASPADA, BAHAYA) berjalan tepat pada parameter batasan jarak yang baru ditentukan.
3. **Uji Timing & Frekuensi Aktuator:** Mengukur respons perubahan ritme ketukan (*delay*) buzzer dan kondisi LED.

---

## 2. Hasil Pengujian Fungsionalitas & Akurasi

### Tabel 1: Hasil Pengujian Pembacaan Sensor Jarak
Pengujian dilakukan dengan menggeser *slider* jarak objek pada komponen HC-SR04 di Wokwi dan mencatat hasilnya pada layar LCD.

| Nilai Input Sensor (Wokwi) | Pembacaan pada LCD (cm) | Status Error (%) | Keterangan |
|----------------------------|-------------------------|------------------|------------|
| 200 cm                     | 200 cm                  | 0%               | Presisi    |
| 160 cm                     | 160 cm                  | 0%               | Presisi    |
| 120 cm                     | 120 cm                  | 0%               | Presisi    |
| 80 cm                      | 80 cm                   | 0%               | Presisi    |
| 50 cm                      | 50 cm                   | 0%               | Presisi    |
| 20 cm                      | 20 cm                   | 0%               | Presisi    |

*Catatan: Pada lingkungan simulasi, konversi matematika $\text{jarak} = \text{durasi} \times 0.034 / 2$ menghasilkan tingkat akurasi 100% presisi.*

---

## 3. Hasil Pengujian Logika Kondisional & Respons Aktuator

Sistem diprogram untuk membagi respons ke dalam 3 zona wilayah keamanan berdasarkan parameter kode terbaru. Berikut adalah hasil pengujian matriks kebenaran logikanya:

### Tabel 2: Matriks Pengujian Kondisi (State Machine)

| Test Case | Jarak Terdeteksi | Ekspektasi Status | Output LCD Aktual | Kondisi LED | Kondisi Suara Buzzer | Hasil (Pass/Fail) |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **TC-01** | 165 cm | **AMAN** | `STATUS: AMAN` | Hijau: NYALA<br>Merah: MATI | MATI TOTAL (`noTone`) | **PASS** |
| **TC-02** | 100 cm | **WASPADA** | `STATUS: AWAS..` | Hijau: MATI<br>Merah: NYALA | Bunyi Putus-putus<br>(Interval: 500 ms) | **PASS** |
| **TC-03** | 60 cm | **WASPADA** | `STATUS: AWAS..` | Hijau: MATI<br>Merah: NYALA | Bunyi Putus-putus<br>(Interval: 300 ms) | **PASS** |
| **TC-04** | 45 cm | **BAHAYA** | `STATUS: STOP!!` | Hijau: MATI<br>Merah: NYALA | Bunyi Konstan Melengking<br>(Frekuensi: 1000 Hz) | **PASS** |

---

## 4. Analisis Pengujian Timing Dinamis (Speedup & Benchmark)

Fitur utama pada arsitektur *software* proyek ini adalah **ritme bunyi buzzer yang adaptif**. Berdasarkan kode program pada kondisi WASPADA (`jarak > 50 && jarak <= 150`):
```cpp
tone(pinBuzzer, 800);
delay(jarak * 5); 
noTone(pinBuzzer);    
delay(jarak * 5);