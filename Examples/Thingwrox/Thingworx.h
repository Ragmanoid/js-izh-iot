#include <ArduinoJson.h>
#include <SoftwareSerial.h>

class Thingworx {
	public:
		String iotServer = ""; 
		String thingName = ""; 
		String serviceName = ""; 
		String apiKey = "";

		int WIFI_RX_PIN;
		int WIFI_TX_PIN;

		String sendData(String getParams[], int countSensors) {
			DynamicJsonDocument dataSensors(500);

			// Add data from sensors
			for (int i = 0; i < countSensors*2; i += 2) {
				DynamicJsonDocument sensor(50);
				sensor["key"] = getParams[i];
				sensor["value"] = getParams[i+1];
				dataSensors["getParams"][i/2] = sensor;
			}

			// Add thing data 
			dataSensors["server"] = iotServer;
			dataSensors["thingName"] = thingName;
			dataSensors["serviceName"] = serviceName;
			dataSensors["apiKey"] = apiKey;

			// Init wifi serial
			SoftwareSerial wifiSerial(WIFI_RX_PIN, WIFI_TX_PIN);
			wifiSerial.begin(9600);

			// Send json on wifi module
			// serializeJson(dataSensors, Serial);
			serializeJson(dataSensors, wifiSerial);

			// Waiit data from server
			while (true) {
				if (wifiSerial.available()) {
					return wifiSerial.readString();
				}
				delay(100);
			}
		}
};
