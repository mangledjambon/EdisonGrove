/*
    RotaryThresholdSoundSensor.ino
    Author:   Sean Breen
    
    This sketch reads the value from the sound sensor, and when it goes above a threshold value lights the LED.
    The threshold value is set using the rotary angle sensor.
    Both the threshold value and sound sensor values are displayed on the LCD display.
    When the threshold is exceeded, the screen will also turn red.
    
    Setup as follows:
    
      1.  Connect sound sensor to A0.
      2.  Connect rotary angle sensor to A1.
      3.  Connect LED to D4.
      4.  Connect LCD display to I2C.
      5.  Transfer this sketch to Edison using Arduino IDE.
*/

/*macro definitions of the sound sensor, potentiometer and LED*/
#define POTENTIOMETER A1
#define SOUND_SENSOR A0
#define LED 4      // the number of the LED pin (D4 in ths case)

#include <Wire.h>
#include "rgb_lcd.h"

/* define the LCD screen */
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

void loop() { // this code loops forever

    int soundSensorValue = analogRead(SOUND_SENSOR);      // use A0 to read signal from sound sensor
    int potentiometerValue = analogRead(POTENTIOMETER);   // use A1 to read signal from potentiometer
    int thresholdValue = 1023 - potentiometerValue;       // correct threshold value
    
    lcd.clear();                        
    lcd.print("T = ");
    lcd.print(thresholdValue);
    lcd.setCursor(0, 1);        // move to second line of LCD screen
    lcd.print("S = ");
    lcd.print(soundSensorValue);
    
    // check if sound level has exceeded threshold
    if(soundSensorValue > thresholdValue)
    {
      Serial.print("Threshold exceeded!\n");
      Serial.print("Sound level = ");
      Serial.println(soundSensorValue);

      Serial.print("Threshold = ");
      Serial.println(thresholdValue);

      lcd.setPWM(REG_GREEN, 0); // turn LCD red
      lcd.setPWM(REG_BLUE, 0);
      digitalWrite(LED, HIGH);  // if the sound sensor value is larger than the threshold value, then light the LED   
      delay(200);
      lcd.setPWM(REG_GREEN, 254);
      lcd.setPWM(REG_BLUE, 254);
      
    }
    
    digitalWrite(LED, LOW);

}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
