### Anggota Kelompok:
1. [Syamsudin Nur] - [25032014035]
2. [Muhammad Aldi Nur C.] - [25032014020]
3. [Rafif Rizal A. A.] - [25032014003]

---

## Deskripsi Proyek
Proyek ini merupakan implementasi *embedded system* menggunakan mikrokontroler Arduino Uno untuk menciptakan sistem asisten parkir pintar (*Smart Parking System*) yang mampu meningkatkan keselamatan berkendara dengan mengatasi masalah titik buta (*blind spot*) saat memarkir kendaraan. 

Sistem ini mengintegrasikan sensor ultrasonik HC-SR04 untuk mendeteksi jarak objek di belakang mobil secara *real-time*, yang kemudian diproses untuk memberikan respons multi-sensorik yang interaktif bagi pengemudi.

Proyek ini dirancang untuk mendemonstrasikan pemahaman mengenai:
* **Sensor dan Transduser:** Mengukur jarak fisik menggunakan gelombang ultrasonik berbasis waktu pantul.
* **Protokol Komunikasi Serial:** Implementasi I2C Bus (*Inter-Integrated Circuit*) untuk menghemat penggunaan pin digital saat mengontrol LCD.
* **Logika Pengambil Keputusan (State Machine):** Mengelompokkan kondisi sistem ke dalam 3 *state* (Aman, Waspada, Bahaya) berdasarkan jarak yang dideteksi.
* **Modulasi Frekuensi Output:** Mengatur ritme ketukan dan frekuensi suara buzzer secara dinamis berbasis variabel matematika.

---

## Fitur Sistem
* **Pengukuran Jarak Akurat:** Sensor HC-SR04 mendeteksi jarak objek di belakang kendaraan dalam satuan centimeter (cm) secara *real-time*.
* **Display Informasi I2C:** Menampilkan data numerik jarak aktual dan status keamanan langsung pada layar LCD 16x2.
* **Sistem Peringatan Visual:** Indikator LED dual-warna (Hijau untuk kondisi aman, Merah untuk kondisi waspada/bahaya).
* **Audio Feedback Adaptif:** Buzzer akan berbunyi putus-putus dengan ritme "bip" yang otomatis melaju semakin cepat dan rapat seiring semakin dekatnya kendaraan dengan dinding penghalang.
* **Sinyal Interupsi Bahaya (Latching Alarm):** Ketika jarak menyentuh batas kritis (<= 15 cm), buzzer akan langsung mengunci suara pada frekuensi tinggi secara konstan tanpa putus sebagai instruksi mutlak untuk berhenti (*STOP*).

---

## Cara Menjalankan Simulasi (Wokwi)

Karena proyek ini disimulasikan menggunakan [Wokwi](https://wokwi.com/), tidak perlu menginstal perangkat lunak fisik apa pun (Arduino IDE tidak diwajibkan). Buka tautan Wokwi proyek kami atau ikuti langkah-langkah berikut:

1. Buka platform Wokwi di browser.
2. Buat *project* Arduino Uno baru.
3. Salin seluruh kode dari file `src/sketch.ino` di repositori ini dan tempelkan ke editor kode Wokwi (`sketch.ino`).
4. Pastikan kamu sudah menambahkan library **LiquidCrystal I2C** melalui menu *Library Manager* di Wokwi.
5. Buka tab `diagram.json` di Wokwi, salin seluruh isi file `src/diagram.json` dari repositori ini, dan tempelkan untuk memuat tata letak komponen secara otomatis.
6. Klik tombol **"Play"** (Start the simulation) di pojok kanan atas area kode.
7. **Cara interaksi:**
    * Geser *slider* jarak pada komponen **Sensor Ultrasonik HC-SR04** untuk mensimulasikan pergerakan mobil mendekati dinding.
    * Perhatikan perubahan warna **LED**, ritme suara **Buzzer**, serta teks status pada **LCD** yang akan berubah secara dinamis sesuai dengan 3 zona jarak yang telah diprogram.

---

## Struktur Repositori
* `src/` — Berisi kode sumber Arduino (`.ino`) dan konfigurasi tata letak komponen Wokwi (`diagram.json`).
* `docs/` — Berisi laporan singkat arsitektur sistem, penjelasan logika *state machine*, dan *flowchart* cara kerja alat.
* `test/` — Berisi data hasil pengujian fungsionalitas akurasi jarak sensor dan respons akurator.

---

## Video Presentasi & Demo
Silakan tonton video presentasi kelompok kami yang menjelaskan secara detail mengenai analisis kode, demonstrasi cara kerja sistem saat mendeteksi objek, dan evaluasi arsitektur software melalui tautan berikut:

**Link YouTube:** [Klik Disini](https://youtu.be/DXRQG78xs-k)