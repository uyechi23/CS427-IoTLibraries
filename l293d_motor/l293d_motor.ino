/**
 * l293d_motor
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * A D.C. motor is a device that takes an electric current and converts it into rotational energy.
 * Most motors can only operate at full speed (voltage on), or stopped (voltage off).
 * The L293D Integrated Circuit (IC) chip included in the ESP32 kit is a chip that allows
 * you to control the speed that a D.C. motor spins at. This is achieved through Pulse-Width
 * Modulation, a technique that sends short pulses of voltage to control how much current goes
 * through a certain device.
 *
 * This program lets you control the speed and direction of a D.C. motor using a L293D IC chip and potentiometer.
 * Some computers have issues running this driver - if it's easier, please use the servo library instead of this one.
 * The servo is better for low-speed precision turns, while D.C. motors are better at high-speed turns.
 *
 * Specifics for how this works can be found here: https://en.wikipedia.org/wiki/Pulse-width_modulation
 * The L293D chip documentation can be found here: https://www.ti.com/lit/ds/symlink/l293.pdf
 * 
 */

// set the pins to control the motor
#define motor1Pin1 27
#define motor1Pin2 26
#define enable1Pin 14
#define POT_PIN 33
 
// Setting PWM (pulse width modulation)
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
 
void setup() {
  // sets the pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(POT_PIN, OUTPUT);
  
  // configure the PWM properties using the built-in ledcSetup
  // PWM was introduced to Arduino to control the brightness of
  // LEDs, but it can be used for more than just setting the brightness
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  // this is essentially the pinMode for a PWM signal
  ledcAttachPin(enable1Pin, pwmChannel);
 
  // begin serial communication on 115200 baud channel
  Serial.begin(115200);
}
 
void loop() {
  // read the value and map it to a duty cycle from -255 to 255,
  // where -255 is the maximum backward speed and 255 is the maximum forward speed
  // print this to the Serial Monitor
  float val = analogRead(POT_PIN);
  int dutycycle = map(val, 0, 4095, 0, 510) - 255;
  Serial.print("Speed: ");
  Serial.println(dutycycle);

  // if the duty cycle is less than 0, make the motor go backward
  int isBackward = 0;
  if(dutycycle < 0){
    isBackward = 1;
  }

  // make sure the duty cycle is positive
  dutycycle = abs(dutycycle);

  // set the pins on the L293D IC
  if(isBackward){
    // if the duty cycle is negative, move the motor backward
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
  }else{
    // if the duty cycle is positive, move the motor forward
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
  }

  // write that value to the motor
  // note that the motor has limitations on how slow it can spin,
  // so values below 200 might not turn on the motor at all.
  ledcWrite(pwmChannel, dutycycle);
}