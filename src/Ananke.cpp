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
void Ananke::connectWifi(const char* ssid, const char* password ) {
	
	delay(10);
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	Serial.println(WiFi.status());
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	
}

boolean Ananke::connectAnanke(const char* deviceId, const char* username, const char* password ) {
	(this->client)->setServer("138.197.92.157", 1883);
	while (!(this->client)->connected()) {
	Serial.print("Attempting MQTT connection...");
	if ((this->client)->connect(deviceId,username,password)) {
		Serial.println("connected");
		//(this->client)->publish("a4395340/g6598292/d6370259/PUB", "{'doorAlarm' : '1'}");
        //(this->client)->subscribe("a4395340/g6598292/d6370259/SUB");
		return true;
	} else {
		Serial.print("failed, rc=");
		Serial.print((this->client)->state());
		Serial.println(" try again in 5 seconds");
		delay(5000);
	}
  }
  
}

boolean Ananke::subscribeAnanke(const char* appId, const char* groupId, const char* deviceId, uint8_t qos ) {
	String str=String(appId)+"/"+String(groupId)+"/"+String(deviceId) +"/"+"SUB";
	char chr[str.length()+1];
	str.toCharArray(chr,str.length()+1);
	return (this->client)->subscribe(chr,qos);
	
}

boolean Ananke::unsubscribeAnanke(const char* appId, const char* groupId, const char* deviceId ) {
	String str=String(appId)+"/"+String(groupId)+"/"+String(deviceId) +"/"+"SUB";
	char chr[str.length()+1];
	str.toCharArray(chr,str.length()+1);
	return (this->client)->unsubscribe(chr);
	
}

boolean Ananke::publishAnanke(const char* appId, const char* groupId, const char* deviceId, const char* payload ) {
	String str=String(appId)+"/"+String(groupId)+"/"+String(deviceId) +"/"+"PUB";
	char chr[str.length()+1];
	str.toCharArray(chr,str.length()+1);
	return (this->client)->publish(chr,payload);
	
}

void Ananke::disconnectAnanke() {
    
	(this->client)->disconnect();
	
}

boolean Ananke::connectedAnanke(){
	
	return (this->client)->connected();
	
}
boolean Ananke::AnankeLoop(){
	
	return (this->client)->loop();
	
}
void Ananke::setCallback(MQTT_CALLBACK_SIGNATURE) {
	
	(this->client)->setCallback(callback);
	
}
