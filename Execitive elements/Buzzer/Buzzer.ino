#define BUZZER_PIN 5

int frequency = 800;

void setup() {

}

void loop() {
    // Turn on the buzzer
    tone(BUZZER_PIN, frequency);
    delay(1000); // delay
    // Turn off the buzzer
    noTone(BUZZER_PIN);
    delay(1000); // delay
}