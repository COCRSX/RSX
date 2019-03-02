/* Programmers:
 * Description:
 *
 *
 *
 */

#include "TimerObject.h"
#include <IridiumSBD.h>
#include <SPI.h>
#include <math.h>


#define IridiumSerial Serial3
#define DIAGNOSTICS false //true for Diag.

IridiumSBD modem(IridiumSerial); //Create a new instance
Timer t; //New timer object for second interrupt
volatile byte bladeState = 0; //Blades have not unlocked
const byte activePin = 1; //Capsule MC will sense when the pin is high.
const byte relayPin1 = 2; //Detatch relay pin
const byte relayPin2 = 3; //Attach battery pin
const byte relayPin3 = 4; //Activate blade relay pin
const int timeBlade = 10000; //Set time to unlock blades
double temp[]; //Store data from temp sensor
double gyro[]; //Store data from gyro sensor

void setup() {
  int signalQuality = -1; //signalQualitiy ready to transfer would be 2 or better
  int err; //Error code

  // Start the console serial port
  Serial.begin(115200);
  while (!Serial); //wait until serial port is open

  // Start the serial port connected to the satellite modem
  IridiumSerial.begin(19200);

  // Begin satellite modem operation
  Serial.println("Starting modem...");
  err = modem.begin();
  if (err != ISBD_SUCCESS)
  {
    Serial.print("Begin failed: error ");
    Serial.println(err);
    if (err == ISBD_NO_MODEM_DETECTED)
      Serial.println("No modem detected: check wiring.");
    return;
  }

  // Example: Print the firmware revision
  char version[12];
  err = modem.getFirmwareVersion(version, sizeof(version));
  if (err != ISBD_SUCCESS)
  {
     Serial.print("FirmwareVersion failed: error ");
     Serial.println(err);
     return;
  }
  Serial.print("Firmware Version is ");
  Serial.print(version);
  Serial.println(".");

  // Example: Test the signal quality.
  // This returns a number between 0 and 5.
  // 2 or better is preferred.
  err = modem.getSignalQuality(signalQuality);
  if (err != ISBD_SUCCESS)
  {
    Serial.print("SignalQuality failed: error ");
    Serial.println(err);
    return;
  }
  Serial.print("On a scale of 0 to 5, signal quality is currently ");
  Serial.print(signalQuality);
  Serial.println(".");

  pinMode(relayPin1, OUTPUT); //Initialize detach relay
  pinMode(relayPin2, OUTPUT); //Initialize battery relay
  pinMode(relayPin3, OUTPUT); //Initialize blade relay
  attachInterrupt(digitalPinToInterrupt(activePin),detatch,HIGH); //Interrupt 1 when payload MC sets pin to High
  t.bladeUnlock(); //Interrupt 2 when timer goes off
}

void loop() {
  temp = 3in1Temp();
  gyro = 3in1Gyro();
  data = parsing(temp, gyro);
  iridium(data);
  t.update();
}

double 3in1Temp(){
  //read in data return array
}
double 3in1Gyro(){
  //Read in data if altitude is a certain high call bladeUnlock() return array
}
double parsing(double temp, double gyro){
  //Format data also bundle data for timed transmission. "It's import that the lib does not retry too quickly
  //as this can drain the capacitor and render the device inoperable. EX(90mA max usb supply the internal to transmit 60 sec
  //compared to 20 for a high current battery solution)
}
void iridium(double data){
  Serial.print("Trying to send the message.  This might take several minutes.\r\n");
  err = modem.sendSBDText(data);
  if (err != ISBD_SUCCESS)
  {
    Serial.print("sendSBDText failed: error ");
    Serial.println(err);
    if (err == ISBD_SENDRECEIVE_TIMEOUT)
      Serial.println("Try again with a better view of the sky.");
  }

  else
  {
    Serial.println("Hey, it worked!");
  }
}

void bladeUnlock(){
  Serial.println("Blade Unlocking...");
  if(bladeState == 0){ //Since we have to paths to get here we need to make sure that we dont activate the blades twice
    digitalWrite(relayPin3, HIGH); //Open battery to solenoid
    bladeState = 1;
  }

}
void detatch(){
  Serial.println("Deteaching...");
  digitalWrite(relayPin1,HIGH); //Close payload MC power line
  digitalWrite(relayPin2, HIGH); // Open on board battery line
}
