#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include "secrets.h"

#define DHT_PIN 5
#define DHT_TYPE DHT11

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

DHT dht = DHT(DHT_PIN, DHT_TYPE);

float t = 0.0;
float h = 0.0;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
}

void loop() {
  t = dht.readTemperature();
  t = dht.convertCtoF(t);
  h = dht.readHumidity();

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *F");

  delay(1000);
}