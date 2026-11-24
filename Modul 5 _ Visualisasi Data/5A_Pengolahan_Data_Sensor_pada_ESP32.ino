#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

// Mock function pengganti sensor DHT22
float bacaSuhuMock() {
    static unsigned long jumlahBaca = 0;
    jumlahBaca++;

    // Suhu dasar berubah secara bertahap
    float suhuDasar = 28.0 + 2.0 * sin(jumlahBaca * 0.08);

    // Noise kecil untuk mensimulasikan fluktuasi sensor
    float noise = random(-5, 6) * 0.1;

    float suhu = suhuDasar + noise;

    // Lonjakan suhu setiap 25 pembacaan untuk simulasi anomali
    if (jumlahBaca % 25 == 0) {
        suhu += 8.0;
    }

    return suhu;
}

DHT dht(DHTPIN, DHTTYPE);

const int N = 5; // jumlah sampel moving average
float buffer[N]; // menyimpan N pembacaan terakhir
int indeks = 0; // posisi penulisan berikutnya pada buffer
int jumlah = 0; // jumlah sampel yang sudah terisi

float suhuMin = 1000.0;
float suhuMax = -1000.0;

float hitungMovingAverage(float nilaiBaru) {
  buffer[indeks] = nilaiBaru;
  indeks = (indeks + 1) % N;
  if (jumlah < N) jumlah++;

  float total = 0;
  for (int i = 0; i < jumlah; i++) {
    total += buffer[i];
  }
  return total / jumlah;
}

// Fungsi baru untuk menghitung simpangan baku dari buffer
float hitungSimpanganBaku() {
  if (jumlah < 2) return 0.0; // butuh minimal 2 data

  float rataRata = 0;
  // 1. Hitung rata-rata
  for (int i = 0; i < jumlah; i++) {
    rataRata += buffer[i];
  }
  rataRata /= jumlah;

  // 2. Hitung total selisih kuadrat
  float totalVariansi = 0;
  for (int i = 0; i < jumlah; i++) {
    totalVariansi += pow(buffer[i] - rataRata, 2);
  }

  // 3. Bagi dengan jumlah data lalu akar kuadratkan
  return sqrt(totalVariansi / jumlah);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float suhu = bacaSuhuMock();

  if (isnan(suhu)) {
    Serial.println("Pembacaan gagal, data diabaikan");
  } else {
    float suhuFilter = hitungMovingAverage(suhu);
    float stdDev = hitungSimpanganBaku(); // Panggil fungsi baru

    if (suhu < suhuMin) suhuMin = suhu;
    if (suhu > suhuMax) suhuMax = suhu;

    Serial.print("Mentah: ");
    Serial.print(suhu);
    Serial.print(" | Filter: ");
    Serial.print(suhuFilter);
    Serial.print(" | StdDev: ");
    Serial.print(stdDev); // Tampilkan StdDev
    Serial.print(" | Min: ");
    Serial.print(suhuMin);
    Serial.print(" | Max: ");
    Serial.println(suhuMax);
  }
  delay(2000);
}
