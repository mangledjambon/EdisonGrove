
/*macro definitions of the sound sensor and the LED*/
#define POTENTIOMETER A1
#define SOUND_SENSOR A0
#define LED 4      // the number of the LED pin

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
  
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    Serial.begin(9600);
   
    pinMode(LED, OUTPUT);
    pinMode(SOUND_SENSOR, INPUT);

    lcd.print("Loading");
    lcd.setCursor(0, 1);
    lcd.print("Sound sensor");
    lcd.setCursor(7, 0);
    delay(1000);
    lcd.print(".");
    delay(1000);
    lcd.print(".");
    delay(1000);
    lcd.print(".");
    delay(1000);
    
}

void loop() {

    int soundSensorValue = analogRead(SOUND_SENSOR); //use A0 to read signal
    int potentiometerValue = analogRead(POTENTIOMETER);
    int thresholdValue = 1023 - potentiometerValue;
    
    lcd.clear();
    lcd.print("T = ");
    lcd.print(thresholdValue);
    lcd.setCursor(0, 1);
    lcd.print("S = ");
    lcd.print(soundSensorValue);
    
    if(soundSensorValue > thresholdValue)
    {
      Serial.print("Threshold exceeded!\n");
      Serial.print("Sound level = ");
      Serial.println(soundSensorValue);

      Serial.print("Threshold = ");
      Serial.println(thresholdValue);

      lcd.setPWM(REG_GREEN, 0);
      lcd.setPWM(REG_BLUE, 0);
      digitalWrite(LED, HIGH);  //if the value read from A0 is larger than 400,then light the LED   
      delay(200);
      lcd.setPWM(REG_GREEN, 254);
      lcd.setPWM(REG_BLUE, 254);
      
    }
    
    digitalWrite(LED, LOW);

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
