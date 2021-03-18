#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Wifi parameters
String ssid = "WIFI SSID";	// Wifi ssid
String wifi_password = "password";	// Wifi password

String iot_server = "";
String thing_name = "";
String service_name = "";
String api_key = "";
String get_params = "";

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
	if (Serial.available()) {
		parse_data(Serial.readString());
		send_data();
	}
}

void parse_data(String data) {
	Serial.println(data);
	
	StaticJsonDocument<1024> doc;
	deserializeJson(doc, data);

	iot_server = String(doc["server"]);
	thing_name = String(doc["thing_name"]);
	service_name = String(doc["service_name"]);
	api_key = String(doc["api_key"]);

	String get_arr[] = doc["get_params"];
	
}

void send_data() {
	if (WiFi.status() == WL_CONNECTED) {	// Check WiFi connection status

		HTTPClient http;	// Declare an object of class HTTPClient

		// Generate request
		String request = String("http://") +
			iot_server + 
			"/Thingworx/" +
			thing_name + 
			"/Services/" +
			service_name +
			"?appKey" + 
			api_key + 
			"&method=post&x-thingworx-session=true" + get_params;

		Serial.println(request);

		// Set headers
		http.addHeader("Accept", "application/json");
		http.addHeader("Host", iot_server);
		http.addHeader("Content-Type", "application/json");

		// Specify request destination
		http.begin(request);

		// Send the request
		int httpCode = http.GET();

		// Check the returning code
		if (httpCode > 0) {
			String payload = http.getString();	// Get the request response payload
			Serial.println(payload);

		}

		http.end();	// Close connection
	} else {
		Serial.println("Wifi is not connected");	
	}
}