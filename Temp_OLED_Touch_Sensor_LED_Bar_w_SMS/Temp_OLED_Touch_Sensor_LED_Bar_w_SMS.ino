/*******************************************************
 * SANTRONIX <info@santronix.in>
 * 
 * This file is part of SANTRONIX Mediatek LinkIt Tutorials Project.
 * 
 * SANTRONIX Mediatek LinkIt Tutorials Project can not be copied and/or distributed without the express
 * permission of SANTRONIX
 *******************************************************/

#include <Grove_LED_Bar.h>
#include <LGSM.h>
#include <math.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include <TimedAction.h>

const int touchPin = 2;
Grove_LED_Bar ledBar(5,4,0);
const int B = 4250;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;

float temperature = 0.0;
int touchSensorValue = 0;

bool processing = false;

void checkTemperature()
{
  int a = analogRead(pinTempSensor);

  float R = 1023.0/a-1;
  R = R0*R;

  temperature = 1.0/((log(R/R0)/B)+(1/298.15))-273.15; // convert to temperature via datasheet

  SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putString("Temperature"); //Print the String
  SeeedOled.setTextXY(2,0);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putFloat(temperature,2);
  SeeedOled.putString(" C");
}

void sendSms()
{
  if(touchSensorValue==1)
  {
    if(!processing)
    {
      processing = true;
      LSMS.beginSMS("8291922124"); 
      LSMS.print("Temperature is : ");
      LSMS.print(temperature);
      LSMS.print(" C");                   // for e.g., Temperature is : 25.6 C
      if (LSMS.endSMS())                  // Send the SMS and wait for reply
      {
        SeeedOled.setTextXY(4,0);
        SeeedOled.putString("SMS Sent");
        delay(5000);
        SeeedOled.clearDisplay();
        processing = false;
      }
      else
      {
        SeeedOled.setTextXY(4,0);
        SeeedOled.putString("SMS Not Sent");
        delay(5000);
        SeeedOled.clearDisplay();
        processing = false;
      } 
    }
  }
}


TimedAction checkTempThread = TimedAction(1000, checkTemperature);
TimedAction smsThread = TimedAction(1000, sendSms);

void setup() {
  // put your setup code here, to run once:
  pinMode(touchPin, INPUT);
  ledBar.begin();
  //Serial.begin(9600);

  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display

  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode

  while (!LSMS.ready())                 // Wait for the sim to initialize
  {
    delay(1000);                        // Wait for a second and then try again
  }
  SeeedOled.putString("SIM Initialized");
  //Serial.println("Sim initialized");
  
  delay(3000);
  SeeedOled.clearDisplay();
}

void loop() {
  checkTempThread.check();
  smsThread.check();
  // put your main code here, to run repeatedly:
  touchSensorValue = digitalRead(touchPin);
  
  if(touchSensorValue==1)
  {
    ledBar.setLevel(10);
  }else{
    ledBar.setLevel(1);
  }
}


