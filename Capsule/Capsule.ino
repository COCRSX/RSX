/*

----------------------
COC M.A.P.P.P 
Project: M.A.P.P.L.E. 
Module: Capsule
----------------------
All data should be constants at the top of our code Comment all lines of code!
Description: 
Programmers: Luis Ivey,


*/




#--------------------------------------
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SparkFun_MS5803_I2C.h>
#---------------------------------------

#---------------------------------------
#define BME280SDI A4
#define BME280SCK A5


#define YOSTLABTX D3
#define YOSTLABRX D2 

#define MS5803SDI  A6
#define MS5803SCK A7

#define PAYLOADDECK1 A0
#define PAYLOADDECK2 A1

#define PIEZO D9

#define ULTIMATEGPSTX D7
#define ULTIMATEGPSRX D6

#define CHRONODOTSCL D4
#define CHRONODOTSDA D5

#define IRIDIUMTX A2
#define IRIDIUMRX A3

#define BLADES D8

#define RELAY D1 

#----------------------------------------




#----------------------------------------
struct capsule {
  // BME280
  float temperature;
  float humidity;
  float pressure;
  float altitude_bme;

  // SFE MS5803-14BA
  float altitude_sfe;

  // YOST 3-Space
  float x, y, z;

  // Errors
  byte errors = 0;
}

#----------------------------------------




#----------------------------------------
# Struct Inizialization 
Adafruit_BME280 bme; 
capsule mapple;

#----------------------------------------







#----------------------------------------
void setup(){
  float seaLevel_Pressure = 1013.25;
  attachInterrupt(digitalPinToInterrupt(PAYLOADDECK1),detach,HIGH);
}

void loop(){
 

}

#-----------------------------------------

void iridium (){
  
}

void bme280(){
// Read Data (Temperature, Altitude, Pressure)
float temperature = bme.readTemperature();
float altitude    = bme.readAltitude(SEALEVELPRESSURE_HPA);
float pressure    = bme.readPressure() / 100.0F;

// TODO: Update global struct with new data values
}

void yostLab(){
// KEVIN: Write code to interface with the yostlab sensor and then update the global struct with new values.
// Read Data
}

void MS5803_14BA(){
// Read Data (Altitude)
float altitude = float(altitude_ms5803(sfe.getPressure(ADC_4096)));

// TODO: Update global struct with new data values
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

bool readSignal(){
  /*The capsule’s atmega328p microcontroller has read a high signal from the payload's Arduino Mega. */
  attachInterrupt(digitalPinToInterrupt(PAYLOADDECKMEGA), timerOffRocket, HIGH)
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
