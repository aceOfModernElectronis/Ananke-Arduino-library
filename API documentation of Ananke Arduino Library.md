# API Documentation

## Constructors
 - Ananke (client)
## Functions
 - boolean begin(appId, groupId, deviceId, username, password)
 - void stop()
 - boolean sendMessage(message)
 - boolean Loop ()
 - int isConnected ()
 - Ananke setOnMessage(onMessage);
## Other
 - Configuration Options
 - Subscription onMessage

************************************************************************************************************************************
# Constructors

## Ananke (client)
Ananke (client)
creates a partially initialised client instance.
Before it can be used, the server details must be configured:
WiFiClient espClient;
Ananke client(espClient);

```
void setup() {
   client.begin("<app ID>","<group ID>","<device ID>",”<Username>”,”<Password>”);
   // client is now ready for use
}
```
 
Parameters,
 - client : an instance of Client, typically WiFiClient.


# Functions

## boolean begin(appId, groupId, deviceId, username, password)
Connects the device with a username and password specified. QoS value of this connection is 1.

    QoS 1 :- This method guarantees that the message will be transferred successfully to the broker.The broker sends an acknowledgement back to the sender, but in the event that that the acknowledgement is lost the sender won't realise the message has got through, so will send the message again. The client will re-send until it gets the broker's acknowledgement.This means that sending is guaranteed, although the message may reach the broker more than once.

Parameters,
 - appID - the application ID to publish to (const char[])
 - groupID - the group ID to publish to (const char[])
 - deviceID : the device ID to use when connecting to the Ananke.(given by Ananke)
 - username : the Ananke accounts username to use. If NULL, no username or password is used (const char[])
 - password : the Ananke accounts password to use. If NULL, no password is used (const char[])
 
Returns,
 - false - connection failed.
 - true - connection succeeded.


## void stop ()
Disconnects the client.

## int sendMessage( message );
Publishes a string message to the specified topic.

Parameters,
 - message - the message to publish (const char[])
 
Returns,
 - false - publish failed, either connection lost, or message too large
 - true - publish succeeded

## boolean Loop ()
This should be called regularly to allow the client to process incoming messages and maintain its connection to the server.

Returns,
 - false - the client is no longer connected
 - true - the client is still connected

## int isConnected ()
Checks whether the client is connected to the server.

Returns,
 - false - the client is no longer connected
 - true - the client is still connected

## Ananke setOnMessage (onMessage)
Sets the message callback function.

Parameters,
 - onMessage : a pointer to a message onMessage function called when a message arrives for a subscription created by this client.
 
Returns,
 - Ananke - the client instance, allowing the function to be chained


# Other

## Configuration Options

The following configuration options can be used to configure the library. They are contained in tests/src/lib/PubSubClient.h.

 - MQTT_MAX_PACKET_SIZE
 
Sets the largest packet size, in bytes, the client will handle. Any packet received that exceeds this size will be ignored.
Default: 128 bytes

 - MQTT_KEEPALIVE 
 
Sets the keepalive interval, in seconds, the client will use. This is used to maintain the connection when no other packets are being sent or received.
Default: 15 seconds

 - MQTT_VERSION 
 
Sets the version of the MQTT protocol to use.
Default: MQTT 3.1.1

 - MQTT_MAX_TRANSFER_SIZE
 
Sets the maximum number of bytes passed to the network client in each write call. Some hardware has a limit to how much data can be passed to them in one go, such as the Arduino Wifi Shield.
Default: undefined (complete packet passed in each write call)

 - MQTT_SOCKET_TIMEOUT
 
Sets the timeout when reading from the network. This also applies as the timeout for calls to connect.
Default: 60 seconds

## Subscription onMessage

If the client is used to subscribe to topics, a callback function must be provided in the constructor. This function is called when new messages arrive at the client.
The onMessage function has the following signature:

void onMessage(const char[] topic, byte* payload, unsigned int length)

Parameters (Values for these parameters are given automatically. User just has to define those in the function),
 - topic - the topic the message arrived on (const char[])
 - payload - the message payload (byte array)
 - length - the length of the message payload (unsigned int)

Internally, the client uses the same buffer for both inbound and outbound messages. After the onMessage function returns, or if a call to either publish or subscribe is made from within the onMessage function, the topic and payload values passed to the function will be overwritten. The application should create its own copy of the values if they are required beyond this.
