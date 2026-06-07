#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD I2C (Alamat biasanya 0x27, ukuran 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definisi PIN
const int pinTrig = 9;
const int pinEcho = 10;
const int ledMerah = 2;
const int ledHijau = 3;
const int pinBuzzer = 4;

// Variabel untuk perhitungan jarak
long durasi;
int jarak;

void setup() {
  // Pengaturan jenis PIN
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  
  // Tampilan Awal (Splash Screen)
  lcd.setCursor(0, 0);
  lcd.print("  Smart Parking ");
  lcd.setCursor(0, 1);
  lcd.print("     System     ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. Membersihkan pinTrig
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  
  // 2. Memicu sensor dengan sinyal HIGH selama 10 mikrodetik
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  // 3. Membaca durasi pantulan gelombang (dalam mikrodetik)
  durasi = pulseIn(pinEcho, HIGH);
  
  // 4. Menghitung jarak dalam centimeter (Rumus fisika kecepatan suara)
  jarak = durasi * 0.034 / 2;

  // 5. Menampilkan jarak ke LCD
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(jarak);
  lcd.print(" cm    "); // Spasi tambahan untuk menghapus sisa angka sebelumnya

  // 6. Logika Kondisi Parkir
  if (jarak <= 15) {
    // KONDISI BAHAYA: Terlalu dekat (<= 15 cm)
    lcd.setCursor(0, 1);
    lcd.print("STATUS: STOP!!  ");
    
    digitalWrite(ledMerah, HIGH);
    digitalWrite(ledHijau, LOW);
    
    // Bunyi buzzer terus-menerus tanpa putus
    digitalWrite(pinBuzzer, HIGH); 
  } 
  else if (jarak > 15 && jarak <= 40) {
    // KONDISI WASPADA: Dekat (16 cm - 40 cm)
    lcd.setCursor(0, 1);
    lcd.print("STATUS: AWAS..  ");
    
    digitalWrite(ledMerah, HIGH);
    digitalWrite(ledHijau, LOW);
    
    // Bunyi buzzer putus-putus (makin dekat makin cepat)
    digitalWrite(pinBuzzer, HIGH);
    delay(jarak * 5); // Kecepatan kedip tergantung jarak
    digitalWrite(pinBuzzer, LOW);
    delay(jarak * 5);
  } 
  else {
    // KONDISI AMAN: (> 40 cm)
    lcd.setCursor(0, 1);
    lcd.print("STATUS: AMAN    ");
    
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledHijau, HIGH);
    digitalWrite(pinBuzzer, LOW); // Buzzer mati
  }

  delay(100); // Delay kecil agar pembacaan LCD lebih stabil
}