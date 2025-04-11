#include <Arduino.h>
#include <DHT.h>

#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht = DHT(DHT_PIN, DHT_TYPE);

float t = 0.0;
float h = 0.0;

void setup() {
  Serial.begin(9600);
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
  Serial.println(" F");

  delay(1000);
}