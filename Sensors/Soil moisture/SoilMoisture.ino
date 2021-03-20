#define SOIL_MOISTURE_SENSOR_PIN 11

void setup() {
	Serial.begin(9600);
	pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT);
}

void loop() {
    // Выводит значение в %, но можно и просто analogRead считать
    Serial.println((1023.0 - analogRead(SOIL_MOISTURE_SENSOR_PIN)) / 1023.0 * 100.0); 
}