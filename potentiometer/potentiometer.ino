/**
 * potentiometer
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The potentiometers included are 10k potentiometers, which means they have a total resistance
 * of 10,000 Ohms. Turning the shaft of the potentiometer changes the resistance between the
 * center pin and both of the outer pins.
 */

 // set the ESP32 pin for the potentiometer
 #define POT_PIN 33

void setup() {
    // set the potentiometer pin to analog input
    pinMode(POT_PIN, INPUT);
    
    // begin Serial communication on 115200 baud channel
    Serial.begin(115200);

}

void loop() {
    // read the value and print to Serial monitor
    float val = analogRead(POT_PIN);
    Serial.print("12-bit Potentiometer Value: ");
    Serial.println(val);

    // the analog to digital converter (ADC) in the ESP32 is 12-bit, which means the values
    // are between 0-4095, so val will be within that range. You can use Arduino's built-in
    // map() function to read how much voltage is at the potentiometer's center pin.
    float millivoltage = float(map(val, 0, 4095, 0, 3300));
    float voltage = millivoltage/1000.0;
    Serial.print("Voltage at Center Potentiometer Pin: ");
    Serial.println(voltage);

    // delay 200ms
    delay(200);
}
