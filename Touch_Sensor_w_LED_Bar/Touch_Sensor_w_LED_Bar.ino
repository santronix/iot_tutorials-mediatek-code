/*******************************************************
 * SANTRONIX <info@santronix.in>
 * 
 * This file is part of SANTRONIX Mediatek LinkIt Tutorials Project.
 * 
 * SANTRONIX Mediatek LinkIt Tutorials Project can not be copied and/or distributed without the express
 * permission of SANTRONIX
 *******************************************************/

#include <Grove_LED_Bar.h>


const int touchPin = 2;
Grove_LED_Bar ledBar(5,4,0);

void setup() {
  // put your setup code here, to run once:
  pinMode(touchPin, INPUT);
  ledBar.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = digitalRead(touchPin);
  
    if(sensorValue==1)
    {
        ledBar.setLevel(10);
    }
    else
    {
        ledBar.setLevel(0);
    }
}
