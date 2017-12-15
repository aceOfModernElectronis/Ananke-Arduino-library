# Ananke IoT Platform
Ananke is developed by Effective Solutions Pvt Ltd as an end to end cloud based IoT platform. Ananke delivers amazing set of features for IoT developers which enable connecting IoT hardwares, applications and services together. Ananke follows platform as a service model with following features,
 - Multi-protocol support (MQTT,Web Sockets and HTTP)
 - Cloud services for Machine Learning and Logic Processing
 - Cloud APIs for Smart Transportation, Health Care, etc
 - Easy prototyping with complete graphical programming interface.
 - SDK availability for Raspberry Pi, Arduino and other iot enabled developer kits

# Ananke-Arduino-library
This library provides a client for doing simple publish/subscribe messaging with
Ananke IOT platform that supports MQTT. A full API document is given in the API documentation 
of Ananke Arduino Library.txt file

## Examples

The library comes with a one example sketch. See File > Examples > Ananke
within the Arduino application.

## Limitations

 - It can only publish QoS 0 messages. It can subscribe at QoS 0 or QoS 1.
 - The maximum message size, including header, is **128 bytes** by default. This
   is configurable via `MQTT_MAX_PACKET_SIZE` in /tests/src/lib/`PubSubClient.h`.
 - The keepalive interval is set to 60 seconds by default. This is configurable
   via `MQTT_KEEPALIVE` in /tests/src/lib/`PubSubClient.h`.
 - The client uses MQTT 3.1.1 by default. It can be changed to use MQTT 3.1 by
   changing value of `MQTT_VERSION` in /tests/src/lib/`PubSubClient.h`.


## Compatible Hardware

The library uses the Arduino Ethernet Client api for interacting with the
underlying network hardware. This means it Just Works with a growing number of
boards and shields, including:

 - Arduino Ethernet
 - Arduino Ethernet Shield
 - Arduino YUN – use the included `YunClient` in place of `EthernetClient`, and
   be sure to do a `Bridge.begin()` first
 - Arduino WiFi Shield - if you want to send packets > 90 bytes with this shield,
   enable the `MQTT_MAX_TRANSFER_SIZE` define in /tests/src/lib/`PubSubClient.h`.
 - Sparkfun WiFly Shield – [library](https://github.com/dpslwk/WiFly)
 - TI CC3000 WiFi - [library](https://github.com/sparkfun/SFE_CC3000_Library)
 - Intel Galileo/Edison
 - ESP8266

The library cannot currently be used with hardware based on the ENC28J60 chip –
such as the Nanode or the Nuelectronics Ethernet Shield. For those, there is an
[alternative library](https://github.com/njh/NanodeMQTT) available.

## References 
	PubSubClient Arduino Library :- http://pubsubclient.knolleary.net/ 
	git :- https://github.com/knolleary/pubsubclient

## License

This code is released under the MIT License.
