/*
----------------------
COC M.A.P.P.P 
Project: M.A.P.P.L.E. 
Module: Payload Deck
----------------------

!All data should be constants at the top of our code Comment all lines of code!


Description: 
Programmers: Luis Ivey,


*/



setup(){
	
}

loop(){
	#Constantly check a signal from the timed event line, if so are we ready to fly? check with the gps and altimeter
}

readSignal(){
	/*Our launch system will start once the time event signals high. Our payload deck’s Arduino Mega will be listening in on that line. */
}

MS5803-14BA(){
/*To prevent false positives and accidentally signaling the capsule's micro-controller to activate the inhibited batteries, we will be comparing the altitude with a sensor on the payload deck (Error Check 2) connected to the Arduino Mega. */
}

gps(){
	/*To prevent false positives and accidentally signaling the capsule's micro-controller to activate the inhibited batteries, we will be comparing the altitude with a sensor on the payload deck (Error Check 2) connected to the Arduino Mega. */
}
ready4Launch(){
	/*T+180s (estimated time) We are now ready to launch off the sounding rocket! This process starts by activating the 2 channel relay. This switch will allow current to flow through our lock mechanism and motor attached to a ball screw linear rod (Error Check 3). Our Arduino Mega will also signal (via pin from low to high and only for a few seconds. Therefore the line does not need to go through a relay) our capsule's micro-controller (Error Check 4). */

}

turnRealyOff(){
	/*The rod will travel a certain distance in order to reach and press against a pressure button. This will ensure a safety net for the rod not to damage the interior of the rocket. In case our pressure button fails, the tdwell Timer Event line will stop supplying power to our motor, thus stopping the rod altogether. */ 

}

error2(){
	/*Error Check 2: A accurate altimeter sensor will be used as a fail safe to eject off the rocket. If the altimeter sensor is reading an appropriate height but the timed event lines have not powered on, then our payload deck’s Arduino Mega will send a signal to the capsule’s microcontroller. The signal will determine an error message that will be sent to us via Iridium. The message will say that our payload deck’s Arduino Mega could not read in timed event line. Our program will end and stop all operations. We need the timed event lines to continue because one of the timed event lines is connected to our launching mechanisms. */
	
}