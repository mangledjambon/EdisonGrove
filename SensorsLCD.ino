/*
    Sean Breen R00070693
    Assignment 2 - MQTT
    
    https://github.com/mangledjambon/EdisonGrove
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
//#include <math.h>
#include <Wire.h>
#include "rgb_lcd.h"

#define LIGHT_SENSOR A0
#define SOUND_SENSOR A2
#define TEMP_SENSOR A3

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };      // this device's MAC Address
IPAddress ip(192, 168, 1, 16);                                // this device's IP Address
IPAddress server(127, 0, 0, 1);                               // IP Address of the Broker

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

EthernetClient ethClient;                                     // declaring an EthernetClient object
PubSubClient client(server, 1883, callback, ethClient);       // PubSubClient object constructor

rgb_lcd lcd;          // declare LCD screen lcd

char numAsCharArray[3];
String numAsString;
float temperature;
int B = 3975;
float resistance;

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {

  // Allocate the correct amount of memory for the payload copy
  byte* p = (byte*)malloc(length);
  
  // Copy the payload to the new buffer
  memcpy(p,payload,length);
  //client.publish("edison/test", p, length);

  lcd.clear();
  lcd.print(topic);
  lcd.setCursor(0, 1);
  
  for (int i=0;i<length;i++){
    lcd.print((char)payload[i]);
  }
  
  // Free the memory
  free(p);
}

void setup()
{
  // start network connection
  Ethernet.begin(mac, ip);

  // prepare lcd screen
  lcd.begin(16, 2);

  // if connection to client is successful
  if (client.connect("arduinoClient")) 
  {
    lcd.print("Publish to test");
    lcd.setCursor(0, 1);
    lcd.print("to see msg here.");
    client.subscribe("edison/test");  // subscribe client to test channel to handle callback
  }
  else
  {
    lcd.print("Failed to connect.");  
  }

  // set up sensors to read values
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(SOUND_SENSOR, INPUT);
  pinMode(TEMP_SENSOR, INPUT);
 
}

void loop()
{

  client.loop();

  // read light sensor value
  int lightLevel = analogRead(LIGHT_SENSOR);
  float light = (float)(1023-lightLevel)*10/lightLevel;
  sprintf(numAsCharArray, "%d", lightLevel);
  client.publish("edison/sensors/light", numAsCharArray); // publish to light topic

  // read sound level sensor value
  int soundLevel = analogRead(SOUND_SENSOR);
  numAsString = String(soundLevel);
  numAsString.toCharArray(numAsCharArray, 3);
  client.publish("edison/sensors/sound", numAsCharArray); // publish to sound topic

  // read temperature sensor value
  int tempLevel = analogRead(TEMP_SENSOR);
  resistance = (float)(1023-tempLevel)*10000/tempLevel;
  temperature = 1/(log(resistance/10000)/B+1/298.15) - 273.15;
  sprintf(numAsCharArray, "%f", temperature);
  client.publish("edison/sensors/temp", numAsCharArray);  // publish to temperature topic
  
  delay(300); // wait 3 seconds
}
