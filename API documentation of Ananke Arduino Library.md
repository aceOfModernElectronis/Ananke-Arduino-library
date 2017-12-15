# API Documentation

## Constructors
 - Ananke (client)
## Functions
 - boolean connectAnanke (deviceID, username, password)
 - void disconnectAnanke ()
 - int publishAnanke (appID, groupID, deviceID, payload)
 - boolean subscribeAnanke (appID, groupID, deviceID,qos)
 - boolean unsubscribeAnanke (appID, groupID, deviceID)
 - Boolean AnankeLoop ()
 - int connectedAnanke ()
 - Ananke setCallback (callback)
## Other
 - Configuration Options
 - Subscription Callback


************************************************************************************************************************************
# Constructors

## Ananke (client)
Ananke (client)
Creates a partially initialised client instance.
Before it can be used, the server details must be configured:
WiFiClient espClient;
Ananke client(espClient);

void setup() {
   client.connectAnanke("<device ID>",”<Username>”,”<Password>”);
   // client is now ready for use
}
 
Parameters,
 - client : an instance of Client, typically WiFiClient.


# Functions

## boolean connectAnanke (deviceID, username, password)
Connects the device with a username and password specified.

Parameters,
 - deviceID : the device ID to use when connecting to the Ananke.(given by Ananke)
 - username : the Ananke accounts username to use. If NULL, no username or password is used (const char[])
 - password : the Ananke accounts password to use. If NULL, no password is used (const char[])
 
Returns,
 - false - connection failed.
 - true - connection succeeded.


## void disconnectAnanke ()
Disconnects the client.

## int publishAnanke (appID, groupID, deviceID, payload)
Publishes a string message to the specified topic.

Parameters,
 - appID - the application ID to publish to (const char[])
 - groupID - the group ID to publish to (const char[])
 - deviceID - the device ID of the device to publish to (const char[])
 - payload - the message to publish (const char[])
 
Returns,
 - false - publish failed, either connection lost, or message too large
 - true - publish succeeded

## boolean subscribeAnanke (appID, groupID, deviceID,qos)
Subscribes to messages published to the specified topic.

Parameters,
 - appID - the application ID to subscribe to (const char[])
 - groupID - the group ID to subscribe to (const char[])
 - deviceID - the device ID of the device to subscribe to (const char[])
 - QoS - Quality of Service you want (only 0 and 1 are possible)
 
        QoS 0 :- This is the simplest, lowest-overhead method of sending a message. The client    simply publishes the message, and there is no acknowledgement by the broker.
        
        QoS 1 :- This method guarantees that the message will be transferred successfully to the broker.The broker sends an acknowledgement back to the sender, but in the event that that the acknowledgement is lost the sender won't realise the message has got through, so will send the message again. The client will re-send until it gets the broker's acknowledgement.This means that sending is guaranteed, although the message may reach the broker more than once. 

Returns,
 - false - sending the subscribe failed, either connection lost, or message too large.
 - true - sending the subscribe succeeded. The request completes asynchronously.

## boolean unsubscribeAnanke (appID, groupID, deviceID)
Unsubscribes from the specified topic.

Parameters,
 - appID - the application ID to unsubscribe to (const char[])
 - groupID - the group ID to unsubscribe to (const char[])
 - deviceID - the device ID of the device to unsubscribe to (const char[])
 
Returns,
 - false - sending the unsubscribe failed, either connection lost, or message too large.
 - true - sending the unsubscribe succeeded. The request completes asynchronously

## Boolean AnankeLoop ()
This should be called regularly to allow the client to process incoming messages and maintain its connection to the server.

Returns,
 - false - the client is no longer connected
 - true - the client is still connected

## int connectedAnanke ()
Checks whether the client is connected to the server.

Returns,
 - false - the client is no longer connected
 - true - the client is still connected

## Ananke setCallback (callback)
Sets the message callback function.

Parameters,
 - callback : a pointer to a message callback function called when a message arrives for a subscription created by this client.
 
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
Default: 15 seconds

## Subscription Callback

If the client is used to subscribe to topics, a callback function must be provided in the constructor. This function is called when new messages arrive at the client.
The callback function has the following signature:

void callback(const char[] topic, byte* payload, unsigned int length)

Parameters,
 - topic - the topic the message arrived on (const char[])
 - payload - the message payload (byte array)
 - length - the length of the message payload (unsigned int)

Internally, the client uses the same buffer for both inbound and outbound messages. After the callback function returns, or if a call to either publish or subscribe is made from within the callback function, the topic and payload values passed to the function will be overwritten. The application should create its own copy of the values if they are required beyond this.
