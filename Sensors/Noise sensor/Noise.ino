#define NOISE_SENSOR_PIN 10

void setup() {
	Serial.begin(9600);
	pinMode(NOISE_SENSOR_PIN, INPUT);
}

void loop() {
    // Выводит значение в %, но можно и просто analogRead считать
	Serial.println(analogRead(NOISE_SENSOR_PIN / 1023.0 * 100.0)); 
}