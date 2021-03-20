#include "Thingworx.h"

#define BAUD_RATE 9600
#define COUNT_SENSORS 3

Thingworx thingworx_wifi;

String sensors_names[COUNT_SENSORS] = {
	"TemperatureInner",
	"Humidity",
	"TemperatureOut"
};

String sensors_values[COUNT_SENSORS] = {
	"1", "2", "3"
};

void setup() {
	Serial.begin(BAUD_RATE);

	thingworx_wifi.iot_server = "127.0.0.1";	// Thingworx server
	thingworx_wifi.thing_name = "My_Thing";	// Thing name
	thingworx_wifi.service_name = "My_Service"; 	// Service name
	thingworx_wifi.api_key = "aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa";	// Api key

	thingworx_wifi.WIFI_RX_PIN = 2;
	thingworx_wifi.WIFI_TX_PIN = 3;
}

void loop() {
	String data[COUNT_SENSORS*2];

	for (int i = 0; i < COUNT_SENSORS*2; i += 2) {
		data[i] = sensors_names[i/2];
		data[i+1] = sensors_values[i/2];
	}

	Serial.println(thingworx_wifi.send_data(data, COUNT_SENSORS));
	delay(1000);
}
