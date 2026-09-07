// Percobaan 3A: Kendali LED via Serial Monitor
#include <Arduino.h>

const int PIN_LED = 12;   // LED di pin 12

void setup() {
    Serial.begin(9600);   // inisialisasi komunikasi serial 9600 bps [4]
    Serial.println("Ketik '1' untuk menyalakan LED, '0' untuk mematikan LED");
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    // Cek apakah ada data dari komputer yang masuk [4]
    if (Serial.available() > 0) {
        char data = Serial.read();   // baca 1 karakter
        
        if (data == '1') {
            digitalWrite(PIN_LED, HIGH);
            Serial.println("LED ON");
        }
        else if (data == '0') {
            digitalWrite(PIN_LED, LOW);
            Serial.println("LED OFF");
        }
        else if (data != '\n' && data != '\r') {
            // Abaikan karakter newline, tampilkan error untuk input lain
            Serial.println("Perintah tidak dikenal");
        }
    }
}
