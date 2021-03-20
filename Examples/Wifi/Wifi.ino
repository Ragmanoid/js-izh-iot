#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Wifi parameters
String ssid = "SSID";	// Wifi ssid
String wifi_password = "PASSWORD";	// Wifi password

void setup() {
	Serial.begin(9600);

	// Connect to wifi 
	WiFi.begin(ssid, wifi_password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting to wifi..");
	}
	Serial.println("Success connect to wifi!");
}

void loop() {
	if (Serial.available()) 
		send_data(Serial.readString());
}

void send_data(String data) {
	if (WiFi.status() == WL_CONNECTED) {	// Check WiFi connection status
		
		// Parse serial json data
		DynamicJsonDocument doc(1024);
		deserializeJson(doc, data);

		const char* iot_server = doc["server"];
		const char* thing_name = doc["thing_name"];
		const char* service_name = doc["service_name"];
		const char* api_key = doc["api_key"];

		String get_params = "";

		for (int i = 0; i < doc["get_params"].size(); i++) {
			const char* key = doc["get_params"][i]["key"];
			const char* value = doc["get_params"][i]["value"];
			get_params += String("&") + key + "=" + value;
		}

		HTTPClient http;	// Declare an object of class HTTPClient

		// Generate request
		String request = String("http://") +
			iot_server + 
			"/Thingworx/Things/" +
			thing_name + 
			"/Services/" +
			service_name +
			"?appKey=" + 
			api_key + 
			"&method=post&x-thingworx-session=true" + get_params;

		// Serial.println(request);

		// Specify request destination
		http.begin(request);

		// Set headers
		http.addHeader("Accept", "application/json");
		http.addHeader("Host", iot_server);
		http.addHeader("Content-Type", "application/json");


		// Send the request
		int httpCode = http.POST("");

		// Check the returning code
		if (httpCode > 0) {
			String payload = http.getString();	// Get the request response payload
			Serial.println(payload);
		} else {
			Serial.println("{\"error\": 1, \"data\": \"Error server connection\"}");
		}

		http.end();	// Close connection
	} else {
		Serial.println("{\"error\": 1, \"data\": \"Wifi is not connected\"}");
	}
}