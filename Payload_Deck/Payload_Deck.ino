/*
 * Programmer:
 * Description: 
 * Payload Deck
 */
 
#include "TimerObject.h"

const byte buttonPressure = 1; //Pin button to stop rod
const byte relayPin1 = 2; //Pin signal relay to open latch
const byte relayPin2 = 3; //Pin signal relay to open motor
const byte signalCapsule = 4; //Pin to signal capsule
void setup() {
  pinMode(relayPin1, OUTPUT); //Initialize relay1
  pinMode(relayPin2, OUTPUT); //Initialize relay2
  digitalWrite(relayPin1, HIGH); //Open latch relay
  digitalWrite(relayPin2, HIGH); //Open motor relay
  digitalWrite(signalCapsule, HIGH); //Signal capsule to close latches. 
  attachInterrupt(digitalPinToInterrupt(buttonPressure),closeMotor,HIGH); //close motor after a certain distance
}

void loop() {
  
}

void closeMotor(){
  Serial.println("Closing...")
  digitalWrite(relayPin2, LOW);
}
