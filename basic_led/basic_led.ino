/**
 * basic_led
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * This is code written for a single LED, turned off and on every second.
 */

#define LED_PIN 4

void setup() {
    // configure the LED_PIN as an output, so the ESP32 knows to write a value to this pin
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // digitalWrite() sets the pin's voltage level at HIGH or LOW;
    // alternate between the two with a 1-second delay between statements
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
}
