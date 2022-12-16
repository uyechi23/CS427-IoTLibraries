/**
 * liquid_crystal_display
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The LCD (liquid crystal display) included in the ESP32 kit uses an I2C interface.
 * This requires an additional library to use the device, but makes the circuit layout much
 * simpler and easy to use.
 *
 * This LCD example is implemented with a push button that will increment the counter
 * displayed on the screen. When making an IoT device, you will need to use "sensors" like
 * the button to modify what the "actuators" do.
 *
 * LCD Wires:
 * The layout of the wires should be in small print on the green circuit board. Look for
 * the small set wires along the short edge of the circuit board. Near those pins, there
 * should be a table - the following list shows where to connect each wire, in the format
 * (circuit board pin: ESP32 pin):
 * - GND: Ground/GND
 * - VDD: +5V
 * - SDA: Pin 13
 * - SCL: Pin 14
 * 
 * Required Libraries:
 * - LiquidCrystal I2C
 */

// include files
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// set the SDA and SCL pins - these are the primary communication pins for the I2C protocol
#define SDA 13
#define SCL 14

// set a pin for the button
#define BUTTON 4

// make a counter variable for how many times a button is pushed
int counter = 0;

// initialize the LCD display settings
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // set the button pin as an input
  pinMode(BUTTON, INPUT);

  // sets up the I2C wires (almost like pinMode for some of the other libraries)
  Wire.begin(SDA, SCL);

  // initialize the LCD drivers
  lcd.init();

  // turn on the LCD's backlight
  lcd.backlight();

  // move the cursor and print a message
  lcd.setCursor(0,0);
  lcd.print("Hello, CS427!");
  delay(3000);
}

void loop() {
  // if the button was pushed...
  if(digitalRead(BUTTON) == HIGH){
    // ...increment the counter and print information
    counter++;
    lcd.setCursor(0,1);
    lcd.print("Counter: ");
    lcd.print(counter);

    // delay so the button doesn't increment the counter too quickly
    delay(250);
  }
}