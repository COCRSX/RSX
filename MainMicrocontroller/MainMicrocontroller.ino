/* Programmers: 
 * Description: 
 * 
 * 
 * 
 */
 
#include "TimerObject.h"

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
  //Find out how Iridium likes to recieve data return array
}
void iridium(double data){
  //Send data to the tranciever
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
  digitalWrite(relayPin1,LOW); //Close payload MC power line
  digitalWrite(relayPin2, HIGH); // Open on board battery line 
}
