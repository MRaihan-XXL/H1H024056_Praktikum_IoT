<h2>Modul Perulangan dan Percabangan</h2>

## 1.5.4 Percobaan 1A: Percabangan

1. Pada kondisi apa program masuk ke blok if?

   > Program masuk ke blok `if` ketika nilai variabel `timeDelay <= 100`.

2. Pada kondisi apa program masuk ke blok else?

   > Program masuk ke blok `else` ketika `timeDelay > 100`. 

3. Apa fungsi dari perintah delay(timeDelay)?

   > `delay(timeDelay)` berfungsi menunda eksekusi program selama `timeDelay` milidetik. `delay` secara langsung menentukan kecepatan kedipan LED. Semakin kecil nilai `timeDelay`, semakin cepat LED berkedip, dan sebaliknya.

4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati),
ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang →
mati dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

   ```c++
   // Modifikasi Percobaan 1A: LED cepat -> sedang -> mati
   const int ledPin = 6;        // LED terhubung ke pin digital 6
   int timeDelay = 1000;        // waktu delay awal (lambat)
   int arah = -1;               // -1 = percepat, 1 = perlambat
   
   void setup() {
       pinMode(ledPin, OUTPUT); // set pin 6 sebagai output
   }

   void loop() {
       digitalWrite(ledPin, HIGH);  // nyalakan LED
       delay(timeDelay);            // tahan sesuai timeDelay
       digitalWrite(ledPin, LOW);   // matikan LED
       delay(timeDelay);            // tahan sesuai timeDelay

       // Jika kecepatan sudah mencapai batas cepat (delay <= 100)
       if (timeDelay <= 100) {
           arah = 1;                // ubah arah menjadi perlambat
       }
       // Jika kecepatan sudah mencapai batas lambat (delay >= 1000)
       else if (timeDelay >= 1000) {
           arah = -1;               // ubah arah menjadi percepat
       }
   
       // Ubah timeDelay: percepat jika arah=-1, perlambat jika arah=1
       timeDelay += arah * 100;

       // Jika delay mencapai 1000 dan sedang dalam mode perlambat (arah=1)
       if (timeDelay == 1000 && arah == 1) {
           digitalWrite(ledPin, LOW);  // pastikan LED mati
           delay(3000);                // mati total selama 3 detik
           timeDelay = 1000;           // reset ke delay awal
           arah = -1;                  // reset arah ke percepatan
      }
    }
   ```

## 1.6.4 Percobaan 2A: Perulangan

1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!

![Skematik](Skematik.png)

2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!

   > Perulangan `for` pertama melakukan iterasi dari pin 2 hingga pin 7 (nilai pin bertambah). Pada setiap iterasi, LED dinyalakan, ditunda, lalu dimatikan sebelum berpindah ke pin berikutnya. Proses berurutan ini menciptakan ilusi titik cahaya bergerak dari kiri ke kanan. Tidak ada LED yang menyala bersamaan, sehingga efek pergerakan terlihat jelas.

3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!

   > Perulangan `for` kedua melakukan iterasi dari pin 7 turun ke pin 2 (nilai pin berkurang). Setiap LED dinyalakan, ditunda, lalu dimatikan secara berurutan dari kanan ke kiri. Efek yang dihasilkan adalah titik cahaya bergerak kembali dari kanan ke kiri. Kedua perulangan bergantian dalam fungsi `loop()` menghasilkan gerakan bolak-balik terus-menerus.

4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian

   ```c++
   // Program LED: 3 kiri dan 3 kanan bergantian
   int timer = 200;   // jeda perpindahan grup (ms)
   
   void setup() {
       // Inisialisasi semua pin 2-7 sebagai OUTPUT
       for (int i = 2; i < 8; i++) {
           pinMode(i, OUTPUT);
       }
   }
   
   void loop() {
       // --- Grup Kiri (pin 2,3,4) menyala ---
       // Matikan semua LED terlebih dahulu (bersihkan kondisi)
       for (int i = 2; i < 8; i++) {
           digitalWrite(i, LOW);
       }
       // Nyalakan 3 LED kiri (pin 2,3,4) bersamaan
       for (int i = 2; i <= 4; i++) {
           digitalWrite(i, HIGH);
       }
       delay(timer);   // tahan selama timer ms
   
       // --- Grup Kanan (pin 5,6,7) menyala ---
       // Matikan semua LED lagi
       for (int i = 2; i < 8; i++) {
           digitalWrite(i, LOW);
       }
       // Nyalakan 3 LED kanan (pin 5,6,7) bersamaan
       for (int i = 5; i <= 7; i++) {
           digitalWrite(i, HIGH);
       }
       delay(timer);   // tahan selama timer ms
   }
   ```

<h2></h2>

<br>
<div align="center">
  <a href="https://github.com/uckypradestha"><img src="https://github.com/uckypradestha/assets/raw/main/social/logo-social-github.png" width="3%" alt="Ultralytics GitHub"></a>
  <img src="https://github.com/uckypradestha/assets/raw/main/social/logo-transparent.png" width="3%" alt="space">
  <a href="https://www.linkedin.com/uckypradestha/"><img src="https://github.com/uckypradestha/assets/raw/main/social/logo-social-linkedin.png" width="3%" alt="Ultralytics LinkedIn"></a>
  <img src="https://github.com/uckypradestha/assets/raw/main/social/logo-transparent.png" width="3%" alt="space">
  <a href="https://twitter.com/uckypradestha"><img src="https://github.com/uckypradestha/assets/raw/main/social/logo-social-twitter.png" width="3%" alt="Ultralytics Twitter"></a>
  <img src="https://github.com/uckypradestha/assets/raw/main/social/logo-transparent.png" width="3%" alt="space">
  <a href="https://www.youtube.com/@ckypradestha"><img src="https://github.com/uckypradestha/assets/raw/main/social/logo-social-youtube.png" width="3%" alt="Ultralytics YouTube"></a>
  <img src="https://github.com/uckypradestha/assets/raw/main/social/logo-transparent.png" width="3%" alt="space">
  <a href="https://www.tiktok.com/@pradestha"><img src="https://github.com/uckypradestha/assets/raw/main/social/logo-social-tiktok.png" width="3%" alt="Ultralytics TikTok"></a>
  <img src="https://github.com/uckypradestha/assets/raw/main/social/logo-transparent.png" width="3%" alt="space">
</div>
