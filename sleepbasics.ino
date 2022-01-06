// This #include statement was automatically added by the Particle IDE.
#include "SparkFunMAX17043/SparkFunMAX17043.h"
#define Buzzer D7
#define WAKE_UP_PIN D3
#include "application.h" //http://docs.xamarin.com/ios/tutorials/Working_with_the_File_System

SYSTEM_MODE(MANUAL);

unsigned long lastTime = 0UL;
char publishString[40];
double voltage = 0;
double soc = 0;
int alert;


void setup() {

        pinMode(WAKE_UP_PIN, INPUT);
        pinMode(Buzzer,OUTPUT);
       
       // Battery Gauge
      
        Serial.begin(9600); // Start serial, to output debug data

	    // Set up Spark variables (voltage, soc, and alert):
	    Particle.variable("voltage", &voltage, DOUBLE);
	    Particle.variable("soc", &soc, DOUBLE);
	    Particle.variable("alert", &alert, INT);
	    // To read the values from a browser, go to:
	    // http://api.particle.io/v1/devices/{DEVICE_ID}/{VARIABLE}?access_token={ACCESS_TOKEN}

	    // Set up the MAX17043 LiPo fuel gauge:
	    lipo.begin(); // Initialize the MAX17043 LiPo fuel gauge

	    // Quick start restarts the MAX17043 in hopes of getting a more accurate
	    // guess for the SOC.
	    lipo.quickStart();


	    lipo.clearAlert(); 
	    
	    // We can set an interrupt to alert when the battery SoC gets too low.
	    // We can alert at anywhere between 1% - 32%:
	    lipo.setThreshold(10); // Set alert threshold to 10%.
	    
}

void loop()
{
    
        
	        // lipo.getVoltage() returns a voltage value (e.g. 3.93)
	        voltage = lipo.getVoltage();
	        // lipo.getSOC() returns the estimated state of charge (e.g. 79%)
	        soc = lipo.getSOC();
	        // lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
	        alert = lipo.getAlert();

	        // Those variables will update to the Spark Cloud, but we'll also print them
	        // locally over serial for debugging:
	   
    
        int sensorValue = digitalRead(WAKE_UP_PIN);

            if(sensorValue == 1)
            {
                      
                         
                        digitalWrite(Buzzer, HIGH);
                        delay(10000);
                        digitalWrite(Buzzer, LOW);
                        
                        Particle.connect();
                      
                        while(!Particle.connected())
                        {
                            Particle.process();
                            delay(100);
                            
                          
                        }
                        
                        Particle.process(); 
                        
                        if (Particle.connected())
                        {
                                    Particle.process(); 
                                    Particle.publish("Touch", "on", 60, PRIVATE);
                                    Particle.publish("Soc", String(soc), 60, PRIVATE);
                                    Particle.publish("Alert", String(alert), 60, PRIVATE);
                                    
                                    delay(100);
                                    Particle.process(); 
                                    delay(100);
                                    Particle.process(); 
                                   
                        }
                        
                        Spark.syncTime();  
                        Particle.disconnect();
                        
                        System.sleep(WAKE_UP_PIN, RISING,60);
            }
            else
            {
                        digitalWrite(Buzzer, HIGH);
                        delay(10000);
                        digitalWrite(Buzzer, LOW);
                         
                       //   Send an event for the threshold time 
                       //   measure the time 
                        
                     
                            unsigned long now = millis();
                        //Every 30 seconds publish uptime
                            now = millis();
       
       
       
                       // if ((now - lastTime) >= 60000UL) {
                        //        lastTime = now;
                                // now is in milliseconds
                                unsigned nowSec = now/1000UL;
                                unsigned sec = nowSec%60;
                                unsigned min = (nowSec%3600)/60;
                                unsigned hours = (nowSec%86400)/3600;
                                sprintf(publishString,"%u:%u:%u",hours,min,sec);
                            
                                
                                Particle.connect();
                                Particle.process();
                                
                                    while(!Particle.connected())
                                    {
                                            Particle.process();
                                            delay(100);
                                    }
                        
                                Particle.process(); 
                        
                                if (Particle.connected())
                                {
                                    Particle.process(); 
                                    Particle.publish("Uptime",publishString,60,PRIVATE);
                                    Particle.publish("Touch", "on", 60, PRIVATE);
                                    Particle.publish("Soc", String(soc), 60, PRIVATE);
                                    Particle.publish("Alert", String(alert), 60, PRIVATE);
                                    
                                    delay(100);
                                    Particle.process(); 
                                    delay(100);
                                    Particle.process(); 
                                }
                        
                                Spark.syncTime();          
                                Particle.disconnect();            
                         //}
                         
                        System.sleep(WAKE_UP_PIN, RISING,60);
                          
                         
            }           
      
    
}
          
    
