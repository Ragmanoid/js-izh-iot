#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

void setup() {
	Serial.begin(9600);

	// Connect to wifi 
	WiFi.begin("SSID", "PASSWORD");

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
	// Check WiFi connection status
	if (WiFi.status() != WL_CONNECTED) {	
		Serial.println("{\"error\": 1, \"data\": \"Wifi is not connected\"}");
		return;
	}

	// Parse serial json data
	DynamicJsonDocument doc(1024);
	deserializeJson(doc, data);

	const char* iotServer = doc["server"];
	const char* thingName = doc["thingName"];
	const char* serviceName = doc["serviceName"];
	const char* apiKey = doc["apiKey"];

	String getParams = "";

	for (int i = 0; i < doc["getParams"].size(); i++) {
		const char* key = doc["getParams"][i]["key"];
		const char* value = doc["getParams"][i]["value"];
		getParams += String("&") + key + "=" + value;
	}

	HTTPClient http;	// Declare an object of class HTTPClient

	// Generate request
	String request = String("http://") +
		iotServer + 
		"/Thingworx/Things/" +
		thingName + 
		"/Services/" +
		serviceName +
		"?appKey=" + 
		apiKey + 
		"&method=post&x-thingworx-session=true" + getParams;

	// Serial.println(request);

	// Specify request destination
	http.begin(request);

	// Set headers
	http.addHeader("Accept", "application/json");
	http.addHeader("Host", iotServer);
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
}