/*
 * Description: 
 * Interrupt pin 3
 * Interrupt pin 2
 * 
 */
 #include "TimerObject.h"

Timer t;
void setup() {
  const byte activePin = 1; //Capsule MC will sense when the pin is high. 
  const byte relayPin1 = 2; //Interface with detatch relay
  const byte relayPin2 = 3; //Interface with blade relay
  int timeBlade = 10000;
  double temp[];
  double gyro[];
  attachInterrupt(digitalPinToInterrupt(activePin),detatch,HIGH);
  t.blade();
  blades = false;
}

void loop() {
  temp = 3in1Temp();
  gyro = 3in1Gyro();
  data = parsing(temp, gyro);
  iridium(data);
  t.update(); 
}

double 3in1Temp(){
  
}
double 3in1Gyro(){
  
}
double parsing(double temp, double gyro){
  
}
void iridium(double data){
  
}
void bladeUnlock(){
  
}
void detatch(){
  
}

void blade(){
  
}
