/*
----------------------
COC M.A.P.P.P 
Project: M.A.P.P.L.E. 
Module: Capsule
----------------------

!All data should be constants at the top of our code Comment all lines of code!


Description: 
Programmers: Luis Ivey,


*/


Setup(){
	
}

loop(){
/* 1. Start reading in data	from the sensors
   2. Parse data, group, and store
   3. Iridium send data 
   4. Constantly check signal from payload deck, and last resort altitude
*/
}

iridium (){
	
}

bme280(){
# Read Data
	
}

yostLab(){
# Read Data
	
}

MS5803-14BA(){
 # Read Data
}

parsing(){
/* Check to see if sensor is malfunctioning (Usually spits out 0 output). Time stamp, Organinze data, store, and make sure it is well within the data limit to send to iridium */
	
}

bladeUnlock(){
/* MS5803-14BA altimeter sensor on board the capsule will be our redundant blade activating system. If the timer is malfunctioning and has not  deployed the blades, then deploy the blades. If the blades have already been deployed then do nothing (Error Check 1) */	
}

detach(){
/*The capsule’s atmega328p microcontroller has read a high signal from the payload's Arduino Mega. This will cause the activation of Relay 4 to start supplying power to our capsule (inhibited batteries). The signal will also cut power from Relay 3 to prevent any induced current during the action of the wire being pulled out from the capsule by the deck’s rod motion. */

}

gps(){
# Read Data	
}

timerOffRocket(){
/*An onboard timer will start once we have received a signal from the payload's microcontroller. The time interval that will take the rod to push the capsule off Wallops' rocket + leeway time, will determine our timer's set time to release the capsule's blades. */

	
}

readSignal(){
	/*The capsule’s atmega328p microcontroller has read a high signal from the payload's Arduino Mega. */
}

piezoOn(){
	#Tone for on 
}

piezoError(){
	#Tone for Error
}

error4(){
	/*Capsule’s microcontroller did not read in a signal from the Arduino Mega. A timer will start once the microcontroller is powered on. If the microcontroller does not receive any signal from the Arduino Mega by a certain time then send an error message and cut all operations. */
}
error2(){
	/*Error Check 2: A accurate altimeter sensor will be used as a fail safe to eject off the rocket. If the altimeter sensor is reading an appropriate height but the timed event lines have not powered on, then our payload deck’s Arduino Mega will send a signal to the capsule’s microcontroller. The signal will determine an error message that will be sent to us via Iridium. The message will say that our payload deck’s Arduino Mega could not read in timed event line. Our program will end and stop all operations. We need the timed event lines to continue because one of the timed event lines is connected to our launching mechanisms. */
}

raspberryPi(){
	/* Bluetooth acting as our iridium system for testing */
}