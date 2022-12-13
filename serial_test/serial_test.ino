/**
 * serial_test.ino
 * 
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * This is a Hello World program for the ESP32-WROVER-DEV Module from FreeNove.
 */

/**
 * setup()
 * 
 * Runs once when the ESP32 is connected to power.
 * Put code here that "initializes" your project - variables, constants, etc.
 */
void setup() {
    // begin Serial communication between the ESP32 and your computer
    // this uses a baud rate of 115200, which specifies how fast information is transmitted
    Serial.begin(115200);
}

/**
 * loop()
 * 
 * Runs continuously while your ESP32 is connected to power.
 * The loop doesn't have a built-in delay, so you'll need to add a delay() statement
 * to prevent it from running too quickly.
 */
void loop() {
    // print "Hello World!" to the Serial Monitor
    // be sure to set the Serial Monitor's baud rate to 115200 to match this program
    Serial.println("Hello World!");

    // delay the loop 500 milliseconds
    delay(500);
}
