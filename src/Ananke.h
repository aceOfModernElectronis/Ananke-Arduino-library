/*
 Ananke.h - A simple client for MQTT.
  Janith Kodithuwakku, Sudheera Withanage
  https://aceofme.com
*/

#ifndef Ananke_h
#define Ananke_h

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "PubSubClient.h"
#include "IPAddress.h"
#include "Client.h"
#include "Stream.h"


class Ananke {
	
private:
	PubSubClient* client;
	WiFiClient espClient;
	const char* deviceIdIn;
	const char* appIdIn;
	const char* groupIdIn;
	const char* usernameIn;
	const char* passwordIn;
   
public:
    
	Ananke();
    	void connectWifi(const char* ssid, const char* wifiPassword );
	boolean begin(const char*appId, const char* groupId, const char* deviceId, const char* username, const char* password );
	boolean subscribeAnanke(uint8_t qos );
	//boolean unsubscribeAnanke();
	boolean sendMessage(const char* message );
	boolean Loop();
	void stop();
	boolean isConnected();
	void setOnMessage(MQTT_CALLBACK_SIGNATURE);
   
};


#endif

