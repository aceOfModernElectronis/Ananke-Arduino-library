/*
  Ananke.cpp - A simple client for MQTT.
  Janith Kodithuwakku, Sudheera Withanage
  https://aceofme.com
*/

#include "Ananke.h"
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "PubSubClient.h"


Ananke::Ananke() {
	client = new PubSubClient(espClient);
}
void Ananke::connectWifi(const char* ssid, const char* wifiPassword ) {
	
	delay(10);
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	Serial.println(WiFi.status());
	WiFi.begin(ssid, wifiPassword);

	while (WiFi.status() != WL_CONNECTED) {
		
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	
}

boolean Ananke::begin(const char* appId, const char* groupId, const char* deviceId, const char* username, const char* password ) {
	
	deviceIdIn = deviceId;
	appIdIn = appId;
	groupIdIn = groupId;
	usernameIn = username;
	passwordIn = password;
	
	(this->client)->setServer("138.197.92.157", 1883);
	while (!(this->client)->connected()) {
	Serial.print("Attempting MQTT connection...");
		if ((this->client)->connect(deviceId,username,password)) {
			Serial.println("connected");
			return true;
		} else {
			Serial.print("failed, rc=");
			Serial.print((this->client)->state());
			Serial.println(" try again in 5 seconds");
			delay(5000);
	}
  }
  
}

boolean Ananke::subscribeAnanke(uint8_t qos ) {
	String str=String(appIdIn)+"/"+String(groupIdIn)+"/"+String(deviceIdIn) +"/"+"SUB";
	Serial.println("Subscribed");
	Serial.println(str);
	char chr[str.length()+1];
	str.toCharArray(chr,str.length()+1);
	return (this->client)->subscribe(chr,qos);
	
}

// boolean Ananke::unsubscribeAnanke() {
	// String str=String(appIdIn)+"/"+String(groupIdIn)+"/"+String(deviceIdIn) +"/"+"SUB";
	// char chr[str.length()+1];
	// str.toCharArray(chr,str.length()+1);
	// return (this->client)->unsubscribe(chr);
	
// }

boolean Ananke::sendMessage(const char* message ) {
	String str=String(appIdIn)+"/"+String(groupIdIn)+"/"+String(deviceIdIn) +"/"+"PUB";
	char chr[str.length()+1];
	str.toCharArray(chr,str.length()+1);
	return (this->client)->publish(chr,message);
	
}

void Ananke::stop() {
    
	(this->client)->disconnect();
	
}

boolean Ananke::isConnected(){
	
	return (this->client)->connected();
	
}
boolean Ananke::Loop(){
	
	return (this->client)->loop();
	
}
void Ananke::setOnMessage(MQTT_CALLBACK_SIGNATURE) {
	
	(this->client)->setCallback(callback);
	
}
