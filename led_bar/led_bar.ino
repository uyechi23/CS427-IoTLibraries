/**
 * led_bar
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The LED bar included in the kit is an array of several basic LEDs; this is code to cycle
 * through and turn on each LED
 */

// create an array of integers representing the pins on the ESP32
// connect the LEDs on the LED bar to the pin numbers on the ESP32
int pins[] = {19, 18, 32, 4, 25, 26, 27, 14, 12, 13};
int numpins = 10;

// set the current and previous LEDs
int curr = 1;
int prev = 0;

void setup() {
    // setup all pins in pins[] array to output;
    // this should work even if the pin numbers are changed
    for(int i = 0; i < numpins; i++){
        pinMode(pins[i], OUTPUT);
    }
}

void loop() {
    // pins[curr] should be the current LED; turn it on
    digitalWrite(pins[curr], HIGH);

    // pins[prev] should be the previous LED; turn it off
    digitalWrite(pins[prev], LOW);

    // update curr and prev (move to the next LED in the LED bar)
    prev = curr;
    curr = (curr + 1) % numpins;

    // delay 200 ms
    delay(200);
}
