#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "OPPO A31";
const char* password = "12345678";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* topicPerintahLed = "unsoed/tk245004/kelompok3/perintah/led";
const char* topicPerintahBuzzer = "unsoed/tk245004/kelompok3/perintah/buzzer";
const int ledPin = D2;
const int buzzerPin = D1;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String pesan;
  for (unsigned int i = 0; i < length; i++) pesan += (char)payload[i];

  JsonDocument doc;
  if (deserializeJson(doc, pesan)) return;

  if (strcmp(topic, topicPerintahLed) == 0) {
    const char* perintah = doc["perintah"];
    digitalWrite(ledPin, String(perintah) == "ON" ? HIGH : LOW);
    Serial.print("LED -> "); Serial.println(perintah);
  } else if (strcmp(topic, topicPerintahBuzzer) == 0) {
    const char* perintah = doc["perintah"];
    digitalWrite(buzzerPin, String(perintah) == "ON" ? HIGH : LOW);
    Serial.print("Buzzer -> "); Serial.println(perintah);
  }
}

void hubungkanWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi berhasil terhubung!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void hubungkanMQTT() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      client.subscribe(topicPerintahLed);
      client.subscribe(topicPerintahBuzzer);
      Serial.println("Subscribe ke topic LED dan Buzzer");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  hubungkanWiFi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) hubungkanMQTT();
  client.loop();
}
