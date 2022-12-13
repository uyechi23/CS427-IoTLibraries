/**
 * joycon
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The joycon included in the kit can be moved up and down (y-value), left and right (x-value),
 * and also pushed like a button (z-value).
 * 
 * Joycon Wires:
 * These will be connected in the format (circuit board pin: ESP32 pin).
 * - GND: Ground/GND
 * - +5V: +5V
 * - VRX: 13
 * - VRY: 12
 * - SW: 14
 */

// set the pins of the X, Y, and Z pins
int joyconVals[] = {13, 12, 14};

void setup() {
  // begin serial communication on 115200 baud channel
  Serial.begin(115200);

  // set the SW pin as an input, since the joycon acts like a button when pushed
  pinMode(joyconVals[2], INPUT_PULLUP);
}
void loop() {
  // read each x, y, and z value
  int xVal = analogRead(joyconVals[0]);
  int yVal = analogRead(joyconVals[1]);
  int zVal = digitalRead(joyconVals[2]);

  // print the data
  Serial.printf("X,Y,Z: %d,\t%d,\t%d\n", xVal, yVal, zVal);
}