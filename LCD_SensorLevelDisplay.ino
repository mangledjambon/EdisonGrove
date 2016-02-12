
/*macro definitions of the sound sensor and the LED*/
#define SOUND_SENSOR A0
#define LED 3      // the number of the LED pin

#define THRESHOLD_VALUE 400 //The threshold to turn the led on 400.00*5/1024 = 1.95v

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 1);
    Serial.begin(9600);
   
    pinMode(LED, OUTPUT);
    pinMode(SOUND_SENSOR, INPUT);
    
}

void loop() {

    //delay(10);
    int sensorValue = analogRead(SOUND_SENSOR); //use A0 to read signal
    lcd.clear();
    
    Serial.println(sensorValue);
    lcd.print(sensorValue);
    
    if(sensorValue > THRESHOLD_VALUE)
    {
      digitalWrite(LED, HIGH);  //if the value read from A0 is larger than 400,then light the LED   
      delay(200);
    }
    
    digitalWrite(LED, LOW);

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
