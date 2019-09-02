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

//Connect Electricity sensor at Analog Input A0
#define ELECTRICITY_SENSOR A0 // Analog input pin that sensor is attached to

float amplitude_current;     //amplitude current
float effective_value;       //effective current

void setup()
{
    Serial.begin(9600);
    pinMode(ELECTRICITY_SENSOR, INPUT);

    Wire.begin();
    SeeedOled.init();  //initialze SEEED OLED display
  
    SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
    SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
    SeeedOled.setPageMode();           //Set addressing mode to Page Mode
}
void loop()
{
    int sensor_max;
    sensor_max = getMaxValue();

    //the VCC on the Grove interface of the sensor is 5v
    amplitude_current=(float)sensor_max/1024*5/800*2000000;
    effective_value=amplitude_current/1.414;//minimum_current=1/1024*5/800*2000000/1.414=8.6(mA)
                                            //Only for sinusoidal alternating current
    
    SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("Max Value:");
    SeeedOled.putFloat(sensor_max, 0);
    SeeedOled.putString("mA");   
    SeeedOled.setTextXY(2,0);          //Set the cursor to Xth Page, Yth Column
    SeeedOled.putString("Amplitude:"); //Print the String  
    SeeedOled.putFloat(amplitude_current,0);
    SeeedOled.putString("mA");
    SeeedOled.setTextXY(4,0);          //Set the cursor to Xth Page, Yth Column
    SeeedOled.putString("Current:");
    SeeedOled.putFloat(effective_value,2);
    SeeedOled.putString("mA");
}

/*Function: Sample for 1000ms and get the maximum value from the SIG pin*/
int getMaxValue()
{
    int sensorValue;                    //value read from the sensor
    int sensorMax = 0;
    uint32_t start_time = millis();
    while((millis()-start_time) < 1000)//sample for 1000ms
    {
        sensorValue = analogRead(ELECTRICITY_SENSOR);
        if (sensorValue > sensorMax)
        {
            /*record the maximum sensor value*/
            sensorMax = sensorValue;
        }
    }
    return sensorMax;
}
