#include <Servo.h>

#define SERVO_PIN 9

Servo myServo;

void setup() {
    myServo.attach(SERVO_PIN);
}

void loop() {
    myServo.write(0); // Set 0 deg on servo 
    delay(1000); // delay
    myServo.write(180); // Set 180 deg on servo 
    delay(1000); // delay
}