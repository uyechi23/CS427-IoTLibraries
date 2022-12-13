/**
 * servo
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The servos included in the ESP32 package are controlled by the "ESP32Servo", which can be installed
 * via the Library Manager for the Arduino IDE. For this particular example, a potentiometer will be
 * used as an input, and based on the position of the potentiometer, the server motor will change
 * as well.
 * 
 * Servo wires:
 * Red - Power (VCC, +5V)
 * Brown - Ground (GND, 0V)
 * Orange - Data/Control (Pin 32)
 * 
 * Required Libraries:
 * - ESP32Servo
 */

// include files
#include <ESP32Servo.h>

// set the ESP32 pin for the potentiometer and servo
#define POT_PIN 33
#define SERVO_PIN 32

// create an object to represent a servo
Servo servo;

void setup() {
  // set the potentiometer pin to analog input
  pinMode(POT_PIN, INPUT);

  // initialize the timers and other servo configurations (from ESP32Servo.h)
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN);

  // begin Serial communication on 115200 baud channel
  Serial.begin(115200);
}

void loop() {
  // read the value, map it to 180 degrees, and print both to Serial monitor
  // the servo can only turn 180 degrees - values above or below will not work.
  float val = analogRead(POT_PIN);
  int pos = 180 - map(val, 0, 4095, 0, 180);
  Serial.print("12-bit Digital Value: ");
  Serial.println(val);
  Serial.print("Degree measurement: ");
  Serial.println(pos);

  // set the servo to the value of the potentiometer
  servo.write(pos);
}
