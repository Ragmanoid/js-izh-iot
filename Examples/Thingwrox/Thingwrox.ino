#include "Thingworx.h"

#define BAUD_RATE 9600
#define COUNT_SENSORS 3

Thingworx thx;

// Create an array to store the names of the parameters that will be accepted in Thingworx 
String sensors_names[COUNT_SENSORS] = {
	"TemperatureInner",
	"Humidity",
	"TemperatureOut"
};

// Create an array for storing values from sensors
String sensors_values[COUNT_SENSORS] = {
	"1", "2", "3"
};

void setup() {
	// Set baud rate
	Serial.begin(BAUD_RATE);

	// Set up data to establish a connection with thingworx
	thx.iot_server = "127.0.0.1";	// Thingworx server
	thx.thing_name = "My_Thing";	// Thing name
	thx.service_name = "My_Service"; 	// Service name
	thx.api_key = "aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa";	// Api key

	// Set wi-fi pins for software serial
	// Connect crosswise 
	thx.WIFI_RX_PIN = 2; // rx
	thx.WIFI_TX_PIN = 3; // tx
}

void loop() {
	// Format data for Thingworx class
	String data[COUNT_SENSORS*2];
	for (int i = 0; i < COUNT_SENSORS*2; i += 2) {
		data[i] = sensors_names[i/2];
		data[i+1] = sensors_values[i/2];
	}

	Serial.println(thx.send_data(data, COUNT_SENSORS));
	delay(1000);
}
