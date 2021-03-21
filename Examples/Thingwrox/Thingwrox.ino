#include <ArduinoJson.h>
#include "Thingworx.h"

#define BAUD_RATE 9600
#define COUNT_SENSORS 3

Thingworx thx;

// Create an array to store the names of the parameters that will be accepted in Thingworx 
String sensorsNames[COUNT_SENSORS] = {
	"TemperatureInner",
	"Humidity",
	"TemperatureOut"
};

// Create an array for storing values from sensors
String sensorsValues[COUNT_SENSORS] = {
	"1", "2", "3"
};

void setup() {
	// Set baud rate
	Serial.begin(BAUD_RATE);

	// Set up data to establish a connection with thingworx
	thx.iotServer = "127.0.0.1";	// Thingworx server
	thx.thingName = "My_Thing";	// Thing name
	thx.serviceName = "My_Service"; 	// Service name
	thx.apiKey = "aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa";	// Api key
	
	// Set wi-fi pins for software serial
	// Connect crosswise wifi
	thx.WIFI_RX_PIN = 2; // rx
	thx.WIFI_TX_PIN = 3; // tx
}

void loop() {
	// Format data for Thingworx class
	String data[COUNT_SENSORS*2];
	for (int i = 0; i < COUNT_SENSORS*2; i += 2) {
		data[i] = sensorsNames[i/2];
		data[i+1] = sensorsValues[i/2];
	}

	DynamicJsonDocument result(200);
	deserializeJson(result, thx.sendData(data, COUNT_SENSORS));
	serializeJson(result, Serial);

	delay(1000);
}
