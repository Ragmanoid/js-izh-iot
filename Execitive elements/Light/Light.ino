#define LIGHT_PIN 10

void setup() {
	pinMode(LIGHT_PIN, OUTPUT);
}

void loop() {
    // Turn on the light
	digitalWrite(LIGHT_PIN, HIGH);
	delay(1000); // delay
    // Turn off the light
	digitalWrite(LIGHT_PIN, LOW);
	delay(1000); // delay
}