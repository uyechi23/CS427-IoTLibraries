/**
 * iot_demo_temp
 *
 * This library is written for the Temperature Sensor demonstration for CS427.
 * This includes a tutorial on writing a simple Flask app backend, as well as
 * the code for an ESP32.
 */

// include libraries - WiFi.h and DHT
#include <WiFi.h>
#include <DHT.h>

// define the DHT sensor
#define DHT_PIN 14
#define DHT_TYPE DHT11

// define the LED
#define LED_PIN 4

// create a DHT object to represent data from the sensor
DHT dht_sensor(DHT_PIN, DHT_TYPE);

// SSID - the Wi-Fi network's name
// Password - the Wi-Fi network's password
const char* ssid     = "UPIoT";
const char* password = "";

// host - the main URL of the webpage you want to connect to; you can use the IP address of a Flask app
const char host[] = "http://192.168.68.111";
const byte flaskappip[4] = {192, 168, 68, 111};

// url - the route of your app to connect to
const String url = "/temp/test/10.0";

// port - the port of the flask app
const int port = 5000;

void setup() {
    // initialize Serial communication
    Serial.begin(115200);
    
    // begin the Wi-Fi connection
    WiFi.begin(ssid, password);

    // pending Wi-Fi connection...
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    // notify the Serial monitor when the Wi-Fi connection is a success
    // display the device's IP address
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // start the DHT sensory
    dht_sensor.begin();

    // set the LED pin as an output
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    
    // WiFiClient variable - a struct that contains relevant Wi-Fi data
    WiFiClient client;
    
    // connect to the client using the IP address and Port of the Flask App
    // set these values above - they can be found when running the Flask application
    if(client.connect(flaskappip, port)){
        // success message
        Serial.println("Connected!");

        // read temperature in Fahrenheit
        float tempF = dht_sensor.readTemperature(true);

        // check whether the reading is Dsuccessful or not;
        // if it is, send an HTTP GET request
        if( !isnan(tempF) ){
          String urlWithData = "/temp/" + WiFi.macAddress() + "/" + tempF;

          client.print(String("GET ") + urlWithData + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");
        }
    }else{
        // failure message
        Serial.println("Failed to connect...");
    }

    // timeout loop
    unsigned long timeout = millis();
    while (client.available() == 0) {
        // if 5 seconds pass, stop the client due to timeout issue
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // while the client is available, print out the returned data
    String avgTemp = "";
    while (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);

        // store the line in avgTemp;
        // avgTemp should have the last line of the response once the loop ends
        avgTemp = line;
    }

    // remove the whitespace around the data and convert to a float
    avgTemp.trim();
    float temperature = avgTemp.toFloat();

    // if statement to turn on LED
    if(temperature < 50.0){
      digitalWrite(LED_PIN, HIGH);
    }else{
      digitalWrite(LED_PIN, LOW);
    }


    // separating newlines to make it look nicer
    Serial.println();
    Serial.println();

    // delay 1 second
    delay(10000);
}