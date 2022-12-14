/**
 * buzzer
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The piezo buzzer is a simple device similar to a speaker, but normally isn't meant to
 * play precise notes.
 */

// define the pin the buzzer is on; this should connect to the longer lead on the buzzer
#define BUZZER_PIN 18

// define PWM characteristics
#define PWM_CHANNEL 0
#define PWM_FREQ 10000
#define PWM_RES 8

void setup() {
  // set up PWM channel
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(BUZZER_PIN, PWM_CHANNEL);

  // play a tone
  ledcWriteTone(PWM_CHANNEL, 1000);
}

void loop() {
  // do nothing
}