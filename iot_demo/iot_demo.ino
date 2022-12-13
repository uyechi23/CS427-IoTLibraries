/**
 * iot_demo
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The ESP32 has a built-in Wi-Fi module that is vital in creating an IoT device.
 * This project extends off of the wifi_client library, and works specifically on the
 * supplementary Flask Template at https://github.com/uyechi23/CS427-FlaskTemplate
 */

// include libraries - WiFi.h
#include <WiFi.h>

// include files for the LCD
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// define the pin that the button is attached to
#define BUTTON_PIN 4

// set the SDA and SCL pins - these are the primary communication pins for the I2C protocol
#define SDA 13
#define SCL 14

// SSID - the Wi-Fi network's name
// Password - the Wi-Fi network's password
const char* ssid     = "UPIoT";
const char* password = "";

// host - the main URL of the webpage you want to connect to; you can use the IP address of a Flask app
const char host[] = "http://192.168.68.111:5000";
const byte flaskappip[4] = {192, 168, 68, 111};

// port - the port of the flask app
const int port = 5000;

// url - the route of your app to connect to
const String url = "/iotdemo/";

// initialize the LCD display settings
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // initialize Serial communication
  Serial.begin(115200);

  // button setup

  // set the button pin as an input
  pinMode(BUTTON_PIN, INPUT);

  // Wi-Fi setup

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

  // LCD Setup

  // sets up the I2C wires (almost like pinMode for some of the other libraries)
  Wire.begin(SDA, SCL);

  // initialize the LCD drivers
  lcd.init();

  // turn on the LCD's backlight
  lcd.backlight();

  // move the cursor and print a message
  lcd.setCursor(0,0);
  lcd.print("Hello, CS427!");
}

void loop() {
  if(digitalRead(BUTTON_PIN) == HIGH){
    // WiFiClient variable - a struct that contains relevant Wi-Fi data
    WiFiClient client;
    
    // connect to the client using the IP address and Port of the Flask App
    // set these values above - they can be found when running the Flask application
    if(client.connect(flaskappip, port)){
      // success message
      Serial.println("Connected!");

      // send an HTTPS GET request
      client.print(String("GET ") + url + WiFi.macAddress() + " HTTP/1.1\r\n" +
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

    // value to store onto the data received from the web application's response
    // for a simple response, it will be the last line in the client's response
    String response = "";
    
    // while the client is available, print out the returned data
    while (client.available()) {
      // read the client's response line-by-line
      String line = client.readStringUntil('\r');
      Serial.print(line);

      // the last time this loop iterates should be the response
      // additionally, trim any excess whitespace that might not be interpreted by the LCD
      response = line;
      response.trim();
    }

    // update the LCD's text
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Last accessed:");
    lcd.setCursor(0, 1);
    lcd.print(response + "s ago.");

    //delay 250 ms to prevent button spamming
    delay(250);
  }
}
