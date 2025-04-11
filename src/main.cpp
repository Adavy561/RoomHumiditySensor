#include <Arduino.h>
#include <DHT.h>
#include "secrets.h"
#include <AdafruitIO.h>

#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht = DHT(DHT_PIN, DHT_TYPE);

// io and wifi connection defined in Adafruit IO config file. See example config.h under Adafruit IO library examples for setup.
AdafruitIO_Feed *temperature = io.feed("temperature_feed");
AdafruitIO_Feed *humidity = io.feed("humidity_feed");

float dht_temperature_celcius = 0.0;
float dht_temperature_fahrenheit = 0.0;
float dht_humidity = 0.0;

void setup() {
  Serial.begin(9600);

  dht.begin();
  
  // WiFi now handled by Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

const int send_interval = 15 * 60 * 1000; // Send once every 15 minutes; 15 Minutes * 60 Seconds * 1000 Milliseconds
unsigned long last_send_time = 0;

void loop() {
  io.run();

  unsigned long current_time = millis();

  if (current_time - last_send_time >= send_interval) {
    dht_temperature_celcius = dht.readTemperature();
    dht_temperature_fahrenheit = dht.convertCtoF(dht_temperature_celcius);
    dht_humidity = dht.readHumidity();

    temperature->save(dht_humidity);
    Serial.print("Humidity: ");
    Serial.print(dht_humidity);
    Serial.println("%");

    humidity->save(dht_humidity);
    Serial.print("Temperature: ");
    Serial.print(dht_temperature_fahrenheit);
    Serial.println(" *F");

    last_send_time = current_time;
  } 

  delay(5000);
}