/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the Ananke library in combination
 with the ESP8266 board/library.

 It connects to an Ananke IOT platform and then:
  - subscribes to the "SUB" topic of the device, printing out any messages
    it receives. If the received message is "{'relay' : '1'}" then the D8 pin will be logic HIGH.
    If the received message is "{'relay' : '0'}" then the D8 pin will be logic LOW. 
  - If the the D7 pin is logic HIGH then it publishes "{'doorAlarm' : '1'}" to the "PUB" topic every 500 miliseconds.
    If the the D7 pin is logic LOW then it publishes "{'doorAlarm' : '0'}" to the "PUB" topic every 500 miliseconds.

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <Ananke.h>

// Update these with values suitable for your network.

const char* ssid = "....";                    //ssid of your WiFi Network
const char* password = "....";                //password of your WiFi Network
const char* appId = "....";                   //Ananke application Id
const char* groupId = "....";                 //Ananke group Id
const char* deviceId = "....";                //Ananke device Id
const char* username = "....";                //Username of your Ananke account
const char* pass = "....";                    //Password of your Ananke account

Ananke dev;
long lastMsg = 0;
char msg[50];
int value = 0;
char relay;

void setup() {
  pinMode(D8, OUTPUT);                                   // Initialize the D8 pin as an output (pin you should connect an LED)
  pinMode(D7, INPUT);                                    // Initialize the D7 pin as an input  (pin you should connect an LED)
  Serial.begin(115200);                           
  dev.connectWifi( ssid, password );                     // Connecting to the WiFi network
  dev.begin(appId, groupId, deviceId, username, pass );  // Connecting to the Ananke
  dev.setOnMessage(onMessage);                           // Making onMessage function alive 
}

void onMessage(char* topic, byte* message, unsigned int length) {  // Topic will be automatically generated 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);         // Printing the messages and the topic
  }
  Serial.println();                   
  digitalWrite( D8,message[length-3]-48 );  // If the switch of the mobile app is ON, Make the D8 pin High

}

void loop() {

  if ( !dev.isConnected() ) {
    
    dev.begin( appId, groupId, deviceId, username, pass );  // If the device has been disconnected from the Ananke, Reconnecting it 
  }
  dev.Loop();

  long now = millis();
  if (now - lastMsg > 500) {                        // Checks the pin D7 for every 500 miliseconds.
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Relay #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    if (digitalRead(D7)){
      dev.sendMessage( "{'doorAlarm' : '1'}"); // If the D7 pin is High, Make the Bulb of the mobile app ON 
    }else{
      dev.sendMessage( "{'doorAlarm' : '0'}"); // If the D7 pin is Low, Make the Bulb of the mobile app OFF
    }
  }
}
