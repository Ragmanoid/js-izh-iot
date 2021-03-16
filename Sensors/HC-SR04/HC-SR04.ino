#include "Ultrasonic.h"

#define TRIG_PIN 12
#define ECHO_PIN 13

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

void setup() {
	Serial.begin(9600);
}

void loop() {
    float dist_cm = ultrasonic.Ranging(CM);
    Serial.println(dist_cm);
    delay(100); 
}