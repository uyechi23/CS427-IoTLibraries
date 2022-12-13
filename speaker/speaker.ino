/**
 * speaker
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * A simple 8-ohm speaker needs more components to make it sound good; for the purpose of
 * it making a simple tone, this library will use Pulse-Width Modulation.
 */

// define PWM settings
#define PWM_CHANNEL 0
#define PWM_PRECISION 12
#define PWM_FREQUENCY 5000

// define the speaker pin
#define SPEAKER_PIN 14

void setup() {
  // set up timer and attach it to the speaker pin
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_PRECISION);
  ledcAttachPin(SPEAKER_PIN, PWM_CHANNEL);
}

void loop() {
  // play a note using PWM
  ledcWrite(PWM_CHANNEL, 2000);
}