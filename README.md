# Assignment 2 - MQTT Broker and Client

* File: 				SensorsLCD.ino
* Dependencies:		
  * Mosquitto, 
  * Grove sensors,
  * PubSubClient

Using a PubSubClient instance to create an MQTT broker and client on the Intel Edison. 
Sensor values are read from the Grove sensors and published to topics.
Current topics are temperature (edison/sensors/temp), sound level (edison/sensors/sound),
light level (edison/sensors/light) and a test channel which will display the messages 
it receives on the LCD screen.
