# Pertemuan 3

## 3.5.4 Percobaan 3A: Komunikasi Serial (UART)

1. Jelaskan proses dari input keyboard hingga LED menyala/mati!

> User mengetik karakter di Serial Monitor Arduino IDE, kemudian menekan enter. Komputer mengirimkan karakter tersebut melalui kabel USB ke Arduino. Di dalam loop(), Serial.available() mendeteksi adanya data (bernilai >0). char data = Serial.read() membaca satu karakter. Program membandingkan data dengan '1' atau '0'. Jika cocok, digitalWrite(PIN_LED, HIGH/LOW) mengubah status LED. Arduino mengirim balasan "LED ON" atau "LED OFF" ke Serial Monitor sebagai konfirmasi.

2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?

> Serial.available() digunakan untuk mengecek apakah ada data yang masuk ke buffer serial. Jika tidak ada, program tidak perlu membaca karena Serial.read() akan mengembalikan nilai -1 yang dapat menyebabkan error logika sehingga program menjadi tidak efisien (banyak pembacaan percuma).

3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan!

```c++
// Modifikasi 3A: LED berkedip saat input '2', berhenti saat input '0'
#include <Arduino.h>

const int PIN_LED = 12;
bool blinkMode = false;   // status mode berkedip
unsigned long previousMillis = 0;
const long interval = 500; // jeda 500ms
bool ledState = false;

void setup() {
    Serial.begin(9600);
    Serial.println("Ketik '1' (ON), '0' (OFF), '2' (BLINK)");
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    // Baca perintah dari serial
    if (Serial.available() > 0) {
        char data = Serial.read();
        if (data == '1') {
            blinkMode = false;
            digitalWrite(PIN_LED, HIGH);
            Serial.println("LED ON");
        }
        else if (data == '0') {
            blinkMode = false;
            digitalWrite(PIN_LED, LOW);
            Serial.println("LED OFF");
        }
        else if (data == '2') {
            blinkMode = true;
            Serial.println("BLINK MODE ON");
        }
        else if (data != '\n' && data != '\r') {
            Serial.println("Perintah tidak dikenal");
        }
    }
    
    // Jika mode blink aktif, lakukan kedip tanpa delay() blocking
    if (blinkMode) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            ledState = !ledState;
            digitalWrite(PIN_LED, ledState);
        }
    }
}
```

4. Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap sistem!

> Pada modifikasi ini digunakan millis(), bukan delay(). Alasannya dikarenakan sistem tesrebut bersifat non-blocking. Program tetap bisa membaca input serial sambil menghitung waktu yang berlalu. Setiap loop, program mengecek apakah sudah waktunya mengganti status LED tanpa menghentikan eksekusi. Sehingga menjadi lebih responsif terhadap input dari pengguna. Cocok untuk aplikasi yang memerlukan pemrosesan paralel seperti membaca sensor, menerima perintah, dan menggerakkan aktuator secara bersamaan.

## 3.6.4 Percobaan 3B: Inter-Integrated Circuit (I2C)

1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!

> Hanya terdapat dua kabel: SDA (data) dan SCL (clock). Arduino mengirimkan alamat slave (0x27) terlebih dahulu untuk "memanggil" LCD. Setelah LCD merespon dengan acknowledge (ACK), Arduino mengirimkan perintah atau data (misal inisialisasi, set kursor, karakter). Library LiquidCrystal_I2C.h menyembunyikan detail ini. Fungsi lcd.print() akan mengirimkan data karakter ke alamat 0x27 melalui bus I2C. Karena I2C adalah protokol sinkron, clock (SCL) diatur oleh Arduino agar kedua perangkat sinkron. Keuntungan: dengan 2 kabel, bisa dihubungkan banyak slave (masing-masing dengan alamat unik).

2. Apakah pin potensiometer harus seperti itu? Jelaskan apa yang terjadi apabila pin kiri dan pin kanan tertukar!

> Potensiometer tetap berfungsi, tetapi arah putaran menjadi terbalik. Artinya, jika diputar searah jarum jam biasanya nilai ADC naik (0→1023), setelah tertukar akan turun (1023→0). Secara teknis tidak merusak, hanya membalik skala. Nilai maksimum dan minimum tetap sama (0 dan 1023). Untuk aplikasi yang menginginkan arah tertentu (misal kanan = naik), perlu disesuaikan.

3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai
output) sehingga:
- Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor
- Adapun data yang ditampilkan pada Serial Monitor sesuai dengan table berikut:

   | ADC: 0 | Volt: 0.00V | Persen: 0% |
   | ------ | ----------- | ---------- |
  
Tampilan jika potensiometer dalam kondisi diputar paling kiri
- ADC: 0 0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1)
- Berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

```c++
// Modifikasi 3B: Tampilan ke Serial Monitor dan LCD dengan format rapi
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinPot = A0;

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
}

void loop() {
    int nilaiADC = analogRead(pinPot);
    if (nilaiADC < 1) nilaiADC = 1;   // hindari pembagian nol (opsional)
    
    float tegangan = (nilaiADC / 1023.0) * 5.0;
    int persen = map(nilaiADC, 0, 1023, 0, 100);
    
    // --- Serial Monitor format sesuai tabel (UART) ---
    Serial.print("ADC: ");
    Serial.print(nilaiADC);
    Serial.print(" Volt: ");
    Serial.print(tegangan, 2);
    Serial.print(" V Persen: ");
    Serial.print(persen);
    Serial.println("%");
    
    // --- LCD baris 1: "ADC: nilai persen%" (I2C) ---
    lcd.setCursor(0, 0);
    lcd.print("ADC: ");
    lcd.print(nilaiADC);
    lcd.print(" ");
    lcd.print(persen);
    lcd.print("%   ");   // hapus sisa karakter
    
    // --- LCD baris 2: bar grafis (I2C) ---
    int panjangBar = map(nilaiADC, 0, 1023, 0, 16);
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
        if (i < panjangBar) {
            lcd.print((char)255);   // blok
        } else {
            lcd.print(" ");
        }
    }
    
    delay(200);
}
```

4. Lengkapi tabel berikut berdasarkan pengamatan pada Serial Monitor


| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00     | 0%         |
| 21  | 0.10     | 2%         |
| 49  | 0.24     | 4%         |
| 74  | 0.36     | 7%         |
| 96  | 0.47     | 9%         |

# Dokumentasi

1. Percobaan 3A: Komunikasi Serial (UART)

![Gambar 1](Dokumentasi_Percobaan_3A_I.jpg)
![Gambar 2](Dokumentasi_Percobaan_3A_II.jpg)
![Gambar 3](Dokumentasi_Percobaan_3A_III.jpg)

2. Percobaan 3B: Inter-Integrated Circuit (I2C)

![Gambar 1](Dokumentasi_Percobaan_3B_I.jpg)
![Gambar 2](Dokumentasi_Percobaan_3B_II.jpg)

2. Hasil Output Percobaan 3B (No.4)

![ACD 1](Hasil_Dokumentasi_Percobaan_3B_(ACD=1).png)
![ACD 21](Hasil_Dokumentasi_Percobaan_3B_(ACD=21).png)
![ACD 49](Hasil_Dokumentasi_Percobaan_3B_(ACD=49).png)
![ACD 74](Hasil_Dokumentasi_Percobaan_3B_(ACD=74).png)
![ACD 96](Hasil_Dokumentasi_Percobaan_3B_(ACD=96).png)
