/**
 * rgb_led
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The RGB LED included in the ESP32 kit is a common-anode LED, meaning the common pin between
 * the three of them is connected to +5V. The other three pins are separate red, green, and blue
 * LEDs. This program reads the values of potentiometers to set the brightness of each LED,
 * allowing you to create a variety of shades of color.
 */

// define potentiometer pins
#define RED_POT 25
#define GREEN_POT 26
#define BLUE_POT 27

// define LED pins
#define RED_LED 19
#define GREEN_LED 18
#define BLUE_LED 5

// define PWM channels; one for each color
#define PWM_RED_CHANNEL 0
#define PWM_GREEN_CHANNEL 1
#define PWM_BLUE_CHANNEL 2

// define PWM characteristics
// PWM_RES is 8 bits, meaning we have values 0-255
#define PWM_FREQ 1000
#define PWM_RES 8

void setup() {
  // define pins as inputs and outputs
  pinMode(RED_POT, INPUT);
  pinMode(GREEN_POT, INPUT);
  pinMode(BLUE_POT, INPUT);

  // setup PWM
  // the PWM channels on the ESP32 are numbered from 0-15, but since
  // we need to control each individual LED color, we need 3 channels
  ledcSetup(PWM_RED_CHANNEL, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_GREEN_CHANNEL, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_BLUE_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(RED_LED, PWM_RED_CHANNEL);
  ledcAttachPin(GREEN_LED, PWM_GREEN_CHANNEL);
  ledcAttachPin(BLUE_LED, PWM_BLUE_CHANNEL);
}

void loop() {
  // read the values of the potentiometers and convert it to a 0-255 scale
  int red = map(analogRead(RED_POT), 0, 4095, 0, 255);
  int green = map(analogRead(GREEN_POT), 0, 4095, 0, 255);
  int blue = map(analogRead(BLUE_POT), 0, 4095, 0, 255);

  // write the RGB values to the LED
  // note that the LED does not fully turn off due to limits of PWM
  ledcWrite(PWM_RED_CHANNEL, red);
  ledcWrite(PWM_GREEN_CHANNEL, green);
  ledcWrite(PWM_BLUE_CHANNEL, blue);

  // set a short delay
  delay(50);
}