# sleep_basic

This is a c++ program for Particle Wifi and cellular chip which wakes up the chip on touch of a PIN called WAKE_UP_PIM D3 and it connects to wifi and calculate the below information:

          // lipo.getVoltage() returns a voltage value (e.g. 3.93)
	        voltage = lipo.getVoltage();
	        
          // lipo.getSOC() returns the estimated state of charge (e.g. 79%)
	        soc = lipo.getSOC();
	        
          // lipo.getAlert() returns a 0 or 1 (0=alert not triggered)
	        alert = lipo.getAlert();
          
          // Those variables will update to the Spark Cloud, but we'll also print them
	        // locally over serial for debugging:
          
          
The circuit board has Spark fun battery guage  and the library to use in the code is "SparkFunMAX17043/SparkFunMAX17043.h".

The porgram repeats itself every 60 seconds after the device disconnect from wifi and go to sleep.

