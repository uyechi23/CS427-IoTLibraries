/**
 * push_button_pullup
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * This is code written for an ESP32 to connect to a push button (configured with a PULLUP resistor).
 * A statement will be printed to the Serial Monitor based on the button's state.
 */
#define BUTTON_PIN 4        // use pin 4 as the button's input

void setup() {
    // set the button pin as an INPUT so the ESP32 knows to read from it
    pinMode(BUTTON_PIN, INPUT);

    // begin Serial communication on the 115200 baud rate channel
    Serial.begin(115200);
}

void loop() {
    // digitalRead() the button pin and check if it's HIGH or LOW
    // if the button_state is pressed (high, 5V), print out "PRESSED"
    // otherwise, print out "NOT PRESSED"
    if(digitalRead(BUTTON_PIN) == LOW){
        Serial.println("PRESSED");
    }else{
        Serial.println("NOT PRESSED");
    }

    // delay for 500 milliseconds
    delay(500);
}
