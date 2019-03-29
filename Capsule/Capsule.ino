/*
----------------------
COC M.A.P.P.P 
Project: M.A.P.P.L.E. 
Module: Capsule
----------------------

All data should be constants at the top of our code! 
Comment all lines of code!


Description: 
Programmers: Luis Ivey,


*/
// HEADERS

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SparkFun_MS5803_I2C.h>

// TODO: Define pin values for the sensors with their actual values
#define BME280SDI 0
#define BME280SCK 1

// KEVIN: Deal with yostlabs pin assignments
#define YOSTLABPINA 1000
#define YOSTLABPINB 1000
// ...

// KEVIN: Figure out which pins (if any) do we need to assign for the MS5803-14BA Sensor
#define ALTIMETERPIN 3 // MS5803_14BA

// BME280
Adafruit_BME280 bme; // Uses I2C protocol
#define SEALEVELPRESSURE_HPA (1013.25)

// MS5803_14BA
MS5803 sfe(ADDRESS_HIGH);
inline double altitude_ms5803(double P) return(44330.0*(1-pow(P/SEALEVELPRESSURE_HPA,1/5.255)));

// Global struct for packaging transmission data
struct TXData {
  // TODO: Figure out what needs to get stored here
}

Setup(){
	
}

loop(){
/* 
1. Capsule is powered on by GSE Line. Constantly read in data and send through Iridium. 
2. Interrupt pin line goes high from the payload deck (signalling ready for launch). 
3. Onboard timer to unlock blades starts. 
5. Unlock Blades. 
4. If the timer did not work use last resort alitude check. 
*/
}

iridium (){
	
}

bme280(){
// Read Data (Temperature, Altitude, Pressure)
float temperature = bme.readTemperature();
float altitude    = bme.readAltitude(SEALEVELPRESSURE_HPA);
float pressure    = bme.readPressure() / 100.0F;

// TODO: Update global struct with new data values
}

yostLab(){
// KEVIN: Write code to interface with the yostlab sensor and then update the global struct with new values.
// Read Data
}

MS5803_14BA(){
// Read Data (Altitude)
float altitude = float(altitude_ms5803(sfe.getPressure(ADC_4096)));

// TODO: Update global struct with new data values
}

detach(){
/*
The signal will also cut power from Relay 3 to prevent any induced current during the action of the wire 
being pulled out from the capsule by the deck’s rod motion. 
*/

}

gps(){
// Read Data	
}

launchTimer(){
/*An onboard timer will start once we have received a signal from the payload's microcontroller. 
The time interval that will take the rod to push the capsule off Wallops' rocket + leeway time, 
will determine our timer's set time to release the capsule's blades. */

	
}

readSignal(){
	/*The capsule’s atmega328p microcontroller has read a high signal from the payload's Arduino Mega. */
}

piezoOn(){
	// Tone for on 
}

piezoError(){
	// Tone for Error
}

noSignalPDTimer(){
	/*Capsule’s microcontroller did not read in a signal from the Arduino Mega.
	A timer will start once the microcontroller is powered on. 
	If the microcontroller does not receive any signal from the Arduino Mega
	by a certain time then send an error message and cut all operations. */
}

raspberryPi(){
	/* Bluetooth acting as our iridium system for testing */
}
