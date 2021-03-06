/*******************************************************
 * SANTRONIX <info@santronix.in>
 * 
 * This file is part of SANTRONIX Mediatek LinkIt Tutorials Project.
 * 
 * SANTRONIX Mediatek LinkIt Tutorials Project can not be copied and/or distributed without the express
 * permission of SANTRONIX
 *******************************************************/

#include <math.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include <avr/dtostrf.h>

const int B = 4250;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
    
    int a = analogRead(pinTempSensor);

    float R = 1023.0/a-1.0;
    R = R0*R;

    float temperature = 1.0/((log(R/R0)/B)+(1/298.15))-273.15; // convert to temperature via datasheet

    Serial.print("temperature = ");
    Serial.println(temperature);
    
    delay(1000);
}
