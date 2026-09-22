// Pin LED
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;

void setup() {
  // Menentukan semua pin LED sebagai OUTPUT
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  // Memulai komunikasi Serial
  Serial.begin(9600);

  Serial.println("=== KONTROL 6 LED ===");
  Serial.println("Masukkan angka 1 - 6");
}

void loop() {

  // Mengecek apakah ada data dari Serial Monitor
  if (Serial.available() > 0) {

    int pilihan = Serial.parseInt();

    // Matikan semua LED terlebih dahulu
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);

    // Percabangan
    if (pilihan == 1) {
      digitalWrite(led1, HIGH);
      Serial.println("LED 1 MENYALA");
    }
    
    else if (pilihan == 2) {
      digitalWrite(led2, HIGH);
      Serial.println("LED 2 MENYALA");
    }
    
    else if (pilihan == 3) {
      digitalWrite(led3, HIGH);
      Serial.println("LED 3 MENYALA");
    }
    
    else if (pilihan == 4) {
      digitalWrite(led4, HIGH);
      Serial.println("LED 4 MENYALA");
    }
    
    else if (pilihan == 5) {
      digitalWrite(led5, HIGH);
      Serial.println("LED 5 MENYALA");
    }
    
    else if (pilihan == 6) {
      digitalWrite(led6, HIGH);
      Serial.println("LED 6 MENYALA");
    }
    
    else {
      Serial.println("Pilihan tidak valid!");
      Serial.println("Masukkan angka 1 - 6.");
    }
  }
}