/**
 * ultrasonic_ranger
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The ultrasonic ranger included in the ESP32 kit measures distance based on a short sonar
 * ping. The time it takes for the ultrasonic wave to bounce off an object and return to the
 * sensor is used to calculate the distance to the object it bounced off of.
 */
// define pins
#define TRIGGER_PIN 13
#define ECHO_PIN 14

// define constants
#define SOUND_VELOCITY 340
#define MAX_DISTANCE 500
float timeout = MAX_DISTANCE * 60;

void setup() {
  // set trigger and echo pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // begin Serial communication on 115200 baud channel
  Serial.begin(115200);
}

void loop() {
  // delay samples by 100ms
  delay(100);

  // print out the ultrasonic reader values
  Serial.print("Distance (cm): ");
  Serial.println(getSonar());
}

// a function to actuate the ultrasonic ranging sensor and calculate the distance value
float getSonar() {
  // create a variable for the time for a sensor to ping off an object
  unsigned long pingTime;

  // a variable for the distance from the sensor to the nearest object
  float distance;

  // make the sensor send a ping
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // retrieve the time it took for the ping to return to the sensor
  pingTime = pulseIn(ECHO_PIN, HIGH, timeout);

  // calculate and return the distan
  distance = (float)pingTime * SOUND_VELOCITY / 2 / 10000;
  return distance;
}