#define BUTTON_PIN 4

void setup() {
	Serial.begin(9600);
	pinMode(BUTTON_PIN, INPUT);
}

void loop() {
	Serial.println(read_data()); 
	delay(200);
}


// Функция будет возвращать bool значение 
bool read_data() {
	bool button_state = digitalRead(BUTTON_PIN);
	// Если button_state = 1 - кнопка не нажата
	// Если button_state = 0 - кнопка нажата
	return !button_state; // Перевернём значения наоборот (1 - нажата, 0 - не нажата)
}