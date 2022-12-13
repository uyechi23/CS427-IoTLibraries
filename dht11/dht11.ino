/**
 * dht11
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The DHT11 provided may either have 4 pins or 3 pins; this program works with the version
 * with 3 pins.
 * 
 * Required Libraries:
 * - DHT sensor library (by Adafruit)
 */

// include the DHT library
#include <DHT.h>

// define the DHT sensor
#define DHT_PIN 14
#define DHT_TYPE DHT11

// create a DHT object to represent data from the sensor
DHT dht_sensor(DHT_PIN, DHT_TYPE);

void setup() {
  // begin Serial communication on 115200 baud channel
  Serial.begin(115200);

  // start the DHT sensory
  dht_sensor.begin();
}

void loop() {
  // read humidity
  float humi  = dht_sensor.readHumidity();
  // read temperature in Celsius
  float tempC = dht_sensor.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht_sensor.readTemperature(true);

  // check whether the reading is successful or not
  if( isnan(tempC) || isnan(tempF) || isnan(humi) ){
    // if any of the data received is nan (failed), print error message
    Serial.println("Failed to read from DHT sensor!");
  }else{
    // if all of the data is successfully read, print to Serial monitor
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C / ");
    Serial.print(tempF);
    Serial.println("°F");
  }

  // wait 2000ms
  delay(2000);
}