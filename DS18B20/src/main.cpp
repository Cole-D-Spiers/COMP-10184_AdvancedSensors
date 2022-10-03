/*
* I, Cole Spiers, student number 000389039, 
* certify that this material is my original work. 
* No other person's work has been used without due acknowledgment 
* and I have not made my work available to anyone else.
* 2022-10-03
*/

// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h>
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire);
DeviceAddress address;
 
void setup()
{ 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  //this is the byte buffer holding the id of the sensor
  uint8_t address[8];
 
 //if da sensor be plugged in print the address use the returning value as an error check
  if(DS18B20.getAddress(address, 0)){
    Serial.println("Temperature Application");
    Serial.print("Found DS18B20 sensor with address: ");
  }else{
    Serial.println("No DS18B20 temperature sensors are installed!");
    return;
  }
 
 //printing each byte of the address in hexidecimal format
  for(int i = 0; i<8; i++){
    Serial.printf("%02X ",address[i]);
  }
  
  //putting a space just to make it all look a litte better
  Serial.println("\n");
}
 
void loop() 
{ 
  //if da sensor be plugged in
  if(DS18B20.getAddress(address, 0))
  {
    float fTemp;

    // ask DS18B20 for the current temperature 
    DS18B20.requestTemperatures(); 
  
    // fetch the temperature.  We only have 1 sensor, so the index is 0. 
    fTemp = DS18B20.getTempCByIndex(0);

    //putting the tempurature into different temp catagorys
    String ans;
    //if the temp is greater then 35
    if(fTemp > 35)
    {
      ans = "Too Hot!";
    }
    //if the temp is eqal too or greater then 30
    else if(fTemp >= 30)
    {
      ans = "Hot";
    }
    //if the temp is equal too or greater then 25
    else if(fTemp >= 25)
    {
      ans = "Warm";
    }
    //if the temp is greater then or equal to 15
    else if(fTemp >= 15)
    {
      ans = "Perfect";
    }
    //if the temp is greater then or equal to 10
    else if(fTemp >= 10)
    {
      ans = "Cool";
    }
    //if thee temp is less then 10
    else
    {
      ans = "Cold!";
    } 

      // print the temp to the USB serial monitor
      Serial.println("Current temperature is: " + String(fTemp) + "° C or " + ans);
    
  }

    // wait 5s (5000ms) before doing this again 
    delay(5000);
}