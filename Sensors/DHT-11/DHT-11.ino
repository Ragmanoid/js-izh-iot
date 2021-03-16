#include "DHT.h"

#define DHT11_PIN 4

DHT dht(DHTPIN, DHT11);

void setup() {
	Serial.begin(9600);
	dht.begin();
}

void loop() {
    delay(2000); 
    float h = dht.readHumidity(); //Измеряем влажность
    float t = dht.readTemperature(); //Измеряем температуру
    if (isnan(h) || isnan(t)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
        Serial.println("Ошибка считывания");
        return;
    }
    Serial.print("Влажность: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Температура: ");
    Serial.print(t);
    Serial.println(" *C "); //Вывод показателей на экран
}