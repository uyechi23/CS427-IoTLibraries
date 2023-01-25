/**
 * wifi_client
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The ESP32 has a built-in Wi-Fi module that is vital in creating an IoT device.
 * This project sets up a basis for connecting to a Wi-Fi network using the ESP32 and retrieving
 * data from a common webpage.
 */

// include libraries - WiFi.h
#include <WiFi.h>

// SSID - the Wi-Fi network's name
// Password - the Wi-Fi network's password
const char* ssid     = "poggers";
const char* password = "UngaBunga69420";

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

    
}

void loop() {
    
    // WiFiClient variable - a struct that contains relevant Wi-Fi data
    WiFiClient client;
    
    // connect to the client using the IP address and Port of the Flask App
    // set these values above - they can be found when running the Flask application
    if(client.connect(flaskappip, port)){
        // success message
        Serial.println("Connected!");

        // send an HTTPS GET request
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
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
    while (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }

    // separating newlines to make it look nicer
    Serial.println();
    Serial.println();

    // delay 1 second
    delay(1000);
}