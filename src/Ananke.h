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
   
public:
    
	Ananke();
    void connectWifi(const char* ssid, const char* password );
	boolean connectAnanke(const char* deviceId, const char* username, const char* password );
	boolean subscribeAnanke(const char* appId, const char* groupId, const char* deviceId, uint8_t qos );
	boolean unsubscribeAnanke(const char* appId, const char* groupId, const char* deviceId );
	boolean publishAnanke(const char* appId, const char* groupId, const char* deviceId, const char* payload );
	boolean AnankeLoop();
	void disconnectAnanke();
	boolean connectedAnanke();
	void setCallback(MQTT_CALLBACK_SIGNATURE);
   
};


#endif

