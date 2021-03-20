#define RELAY_PIN 10

void setup() {
	pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
    // Turn on the relay
	digitalWrite(RELAY_PIN, HIGH);
	delay(1000); // delay
    // Turn off the relay
	digitalWrite(RELAY_PIN, LOW);
	delay(1000); // delay
}