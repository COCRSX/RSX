/*
----------------------
COC M.A.P.P.P
Project: M.A.P.P.L.E.
Module: Capsule
----------------------

!All data should be constants at the top of our code Comment all lines of code!


Description:
Programmers: Luis Ivey, Kyle Strem


*/
/* ------------------------------------------------------------------ */
/* HEADERS */
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SparkFun_MS5803_I2C.h>
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* PIN ASSIGNMENTS */
// BME280
#define BME280SDI         A4
#define BME280SCK         A5

// YOST LAB 3-SPACE
#define YOSTLABTX         D3
#define YOSTLABRX         D2

// MS5803 ALTIMETER
#define MS5803SDI         A6
#define MS5803SCK         A7

// PAYLOAD DECK ARDUINO MEGA
#define PAYLOADDECKMEGA1  A0
#define PAYLOADDECKMEGA2  A1

// PIEZO
#define PIEZO             D9

// ULTIMATE GPS
#define ULTIMATEGPSTX     D7
#define ULTIMATEGPSRX     D6

// CHRONODOT TIMER
#define CHRONODOTSCL      D4
#define CHRONODOTSDA      D5

// IRIDIUM TRANS
#define IRIDIUMTX         A2
#define IRIDIUMRX         A3

// BLADES
#define BLADES            D8
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* Other Constants */
#define SEALEVELPRESSURE_HPA (1013.25)
// Inline function for getting an altitude reading from the MS5803 Altimeter
inline double altitude_ms5803(double P) return(44330.0*(1-pow(P/SEALEVELPRESSURE_HPA,1/5.255)));
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* Capsule Struct for transmission */
struct capsule {
  // BME280
  float temperature;
  float humidity;
  float pressure;

  // SFE MS5803-14BA
  float altitude_sfe;

  // YOST 3-Space
  float x, y, z;
  float acceleration;

  // Errors
  byte  errors = 0;
}
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* Initialization */
Adafruit_BME280 bme; // Uses I2C protocol
MS5803          sfe(ADDRESS_HIGH);
capsule         mapple;
/* ------------------------------------------------------------------ */

void setup(){
  attachInterrupt(digitalPinToInterrupt(PAYLOADDECKMEGA1),detach,HIGH);
}

void loop(){
/* 1. Start reading in data	from the sensors
   2. Parse data, group, and store
   3. Iridium send data
   4. Constantly check signal from payload deck, and last resort altitude
*/
}

void iridium (){

}

void bme280(){
// Read Data (Temperature, Humidity, Pressure)
float temperature = bme.readTemperature();
float humidity    = bme.readHumidity();
float pressure    = bme.readPressure() / 100.0F;

mapple.temperature  = temperature;
mapple.humidity     = humidity;
mapple.pressure     = pressure;
}

void yostLab(){
// TODO: Write code to interface with the yostlab sensor and then update the global struct with new values.
// Read Data
}

void MS5803_14BA(){
// Read Data (Altitude)
float altitude = float(altitude_ms5803(sfe.getPressure(ADC_4096)));

mapple.altitude_sfe = altitude;
}

void parsing(){
/* Check to see if sensor is malfunctioning (Usually spits out 0 output).
Time stamp, Organinze data, store, and make sure it is well within the data limit to send to iridium */

}

void bladeUnlock(){
/* MS5803-14BA altimeter sensor on board the capsule will be our redundant blade activating system.
If the timer is malfunctioning and has not  deployed the blades, then deploy the blades.
If the blades have already been deployed then do nothing (Error Check 1) */

// TODO: Read altimeter sensor data from struct
float altitude = capsule.altitude_bme;

// TODO: If Blades have been deployed do nothing (error check?)
if ( !blades_deployed ) {
}
}


}

void detach(){
/*The capsule’s atmega328p microcontroller has read a high signal from the payload's Arduino Mega.
This will cause the activation of Relay 4 to start supplying power to our capsule (inhibited batteries).
The signal will also cut power from Relay 3 to prevent any induced current during the action of the wire
being pulled out from the capsule by the deck’s rod motion. */

}

void gps(){
// Read Data
}

void timerOffRocket(){
/*An onboard timer will start once we have received a signal from the payload's microcontroller.
The time interval that will take the rod to push the capsule off Wallops' rocket + leeway time,
will determine our timer's set time to release the capsule's blades. */


}

void piezoOn(){
	// Tone for on
}

void piezoError(){
	// Tone for Error
}

void error4(){
	/*Capsule’s microcontroller did not read in a signal from the Arduino Mega.
	A timer will start once the microcontroller is powered on.
	If the microcontroller does not receive any signal from the Arduino Mega
	by a certain time then send an error message and cut all operations. */
}
void error2(){
	/*Error Check 2: A accurate altimeter sensor will be used as a fail safe to eject off the rocket.
	If the altimeter sensor is reading an appropriate height but the timed event lines have not powered on,
	then our payload deck’s Arduino Mega will send a signal to the capsule’s microcontroller.
	The signal will determine an error message that will be sent to us via Iridium.
	The message will say that our payload deck’s Arduino Mega could not read in timed event line.
	Our program will end and stop all operations.
	We need the timed event lines to continue because one of the timed event lines is connected to our launching mechanisms. */
}

void raspberryPi(){
	/* Bluetooth acting as our iridium system for testing */
}

void on(){

}
void off(){

}
