/*
 * Description: 
 * Interrupt pin 3
 * Interrupt pin 2
 * 
 */
void setup() {
  double temp[];
  double gyro[];
  interrupt1 //Battery
  interrrupt2
  blades = false;
}

void loop() {
  temp = 3in1Temp();
  gyro = 3in1Gyro();
  data = parsing(temp, gyro);
  iridium(data);
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
void relay(){
  
}
