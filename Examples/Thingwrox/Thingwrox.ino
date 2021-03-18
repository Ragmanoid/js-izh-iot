#include <IOT.h>

#define BAUD_RATE 9600

IOT iot;

void setup() {
	Serial.begin(BAUD_RATE);

	iot.iot_server = "";	// Thingworx server
	iot.thing_name = "";	// Thing name
	iot.service_name = ""; 	// Service name
	iot.api_key = "";	// Api key

	iot.ssid = "SweetHome";	// Ssid network
	iot.wifi_password = "P@ssw0rd";	// Wifi password

	iot.

	iot.init();
}

void loop() {
	iot.read_data();
	iot.send_data();
}