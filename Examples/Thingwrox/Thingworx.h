#include <ArduinoJson.h>
#include <SoftwareSerial.h>

class Thingworx {
	public:
		String iot_server = ""; 
		String thing_name = ""; 
		String service_name = ""; 
		String api_key = "";

		int WIFI_RX_PIN;
		int WIFI_TX_PIN;

		String send_data(String get_params[], int count_sensors) {
			DynamicJsonDocument data_sensors(512);

			// Add data from sensors
			for (int i = 0; i < count_sensors*2; i += 2) {
				DynamicJsonDocument sensor(50);
				sensor["key"] = get_params[i];
				sensor["value"] = get_params[i+1];
				data_sensors["get_params"][i/2] = sensor;
			}

			// Add thing data 
			data_sensors["server"] = iot_server;
			data_sensors["thing_name"] = thing_name;
			data_sensors["service_name"] = service_name;
			data_sensors["api_key"] = api_key;

			// Init wifi serial
			SoftwareSerial wifi_serial(WIFI_RX_PIN, WIFI_TX_PIN);
			wifi_serial.begin(9600);

			// Send json on wifi module
			// serializeJson(data_sensors, Serial);
			serializeJson(data_sensors, wifi_serial);

			// Waiit data from server
			Serial.println();
			while (true) {
				// Serial.print('.');
				if (wifi_serial.available()) {
					Serial.println();
					return wifi_serial.readString();
				}
				delay(100);
			}
		}
};
