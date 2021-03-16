#define IM_PIN A0

void setup() {
	Serial.begin(9600);
    pinMode(IM_PIN, INPUT);
}

void loop() {
    if(analogRead(IM_PIN) > 500) { 
        Serial.println("Есть движение!");   
    }   
    else {
        Serial.print("Нет движения")
    }
}