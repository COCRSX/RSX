#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <math.h>
#include <TimerFreeTone.h>
#define TONE_PIN A2
//#include <SHT1x.h>

// #define dataPin 6
// #define clockPin 8
// SHT1x sht1x(dataPin, clockPin);


SPISettings settings(16000000, MSBFIRST, SPI_MODE3 );
const int chipSelect = 10;
const int CSN = 9;
const int SI = 11;
const int SO = 12;
const int CLK = 13;

double D;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
int ledState = LOW;
int relayState= LOW;

const long interval = 500;
const long interval2 = 2000;

//int piezoPin = A2;





// If using software serial, keep this line enabled
// (you can change the pin numbers to match your wiring):
SoftwareSerial mySerial(3, 2);


Adafruit_GPS GPS(&mySerial);


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences.
#define GPSECHO  false

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy


// Needed to convert the bytes from SPI to float
union u_types {
   byte b[4];
   float fval;
} data[3];  // Create 3 unions, one for each euler angle

void setup(){
  //tone(piezoPin, 500, 400);

  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");

  //Set Pin Modes

 pinMode(CSN, OUTPUT);
 pinMode(SI, OUTPUT);
 pinMode(SO, INPUT);
 pinMode(CLK, OUTPUT);

 pinMode (A5, OUTPUT);
 pinMode (A4, OUTPUT);
// pinMode (A2, OUTPUT);






 //Set Slave Select High to Start i.e disable chip
 digitalWrite(CSN, HIGH);

 //Initialize SPI
 SPI.begin();

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);



 //pour a bowl of serial

 Serial.print("Initializing SD card...");
   if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;
    // writing direct to UDR0 is much much faster than Serial.print
    // but only one character can be written at a time.
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

byte transferByte(byte byteToWrite) {

 byte Result = 0x00;
 digitalWrite(CSN,LOW);
 delay(1);
 Result = SPI.transfer(byteToWrite);
 delay(1);
 digitalWrite(CSN,HIGH);
 return Result;
}

//function to swap endian
void endianSwap(byte temp[4]) {
 byte myTemp = temp[0];
 temp[0] = temp[3];
 temp[3] = myTemp;
 myTemp = temp[1];
 temp[1] = temp[2];
 temp[2] = myTemp;
}


uint32_t timer = millis();



void loop(){
  TimerFreeTone(TONE_PIN, 500, 500);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(A4, ledState);

  }

  if (currentMillis - previousMillis2 >= interval2) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (relayState == LOW) {
      relayState = HIGH;
    } else {
      relayState = LOW;
    }

    // set the LED with the ledState of the variable:

    digitalWrite(A5,relayState);
  }



   SPI.beginTransaction(settings);


    // Clear the internal data buffer on the IMU
    byte result = transferByte(0x01);
        //Serial.print("Cleared internal buffer. Result: "),Serial.println(result);

    // Send start of packet:
    result = transferByte(0xF6);
         //Serial.print("Send start of packet. Result: "),Serial.println(result);

    // Send command (tared euler angles)
    result = transferByte(0x01);
         //Serial.print("Send commmand 0x01. Result: "),Serial.println(result);

    // Get status of device:
    result = transferByte(0xFF);
         //Serial.print("Status of device. Result: "),Serial.println(result);

    while (result != 0x01) {  // Repeat until device is Ready
      delay(1);
      result = transferByte(0xFF);
      //Serial.print("Status of device. Result: "),Serial.println(result);
    }

    // Get the 12 bytes of return data from the device:
    //first for loop is how many bytes you want
    for (int ii=0; ii<3; ii++) {
      for (int jj=0; jj<4; jj++) {
        data[ii].b[jj] =  transferByte(0xFF);
        delay(1);
      }
    }

    SPI.endTransaction();

    for( int mm=0; mm<3; mm++) {
      endianSwap(data[mm].b);
    }




    // Serial.print(" X :"), Serial.print(data[0].fval);
    // Serial.print(" Y:"), Serial.print(data[1].fval);
    // Serial.print(" Z:"), Serial.print(data[2].fval);
    //
    //   Serial.print(" Temperature: ");
    //  Serial.print(temp_c, DEC);
    //  Serial.print("C / ");
    //  Serial.print(temp_f, DEC);
    //  Serial.print("F. Humidity: ");
    //  Serial.print(humidity);
    //  Serial.println("% ");


   /////////////////////////////




  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
  }

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();



  // approximately every 2 seconds or so, print out the current stats



  if (millis() - timer > 2000) {


    timer = millis(); // reset the timer


    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    // make a string for assembling the data to log:


     // read three sensors and append to the string:




     //
     // dataString += String("\nTime: ");
     // dataString += String(GPS.hour, DEC);
     // dataString += ":";
     // dataString += String(GPS.minute, DEC);
     // dataString += ":";
     // dataString += String(GPS.seconds, DEC);
     // dataString += ".";
     //
     //
     //
     //
     // File dataFile = SD.open("datalog.txt", FILE_WRITE);
     //
     // // if the file is available, write to it:
     // if (dataFile) {
     //
     //   dataFile.println(dataString);
     //   dataFile.close();
     //   // print to the serial port too:
     //   //Serial.println(dataString);
     // }
     // // if the file isn't open, pop up an error:
     // else {
     //   Serial.println("error opening datalog.txt");
     // }




    if (GPS.fix) {

      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", ");
      Serial.println(GPS.longitudeDegrees, 4);

      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
  // // make a string for assembling the data to log:
    String dataString = "";
  //
  //  // read three sensors and append to the string:
  //
  //  // dataString += "TEMP";
  //  // dataString += String(temp_f);
  //
  //  dataString += time;
  //  dataString += ",";
  //
   dataString += String("\nCORDS: ");
   dataString += String(data[0].fval);
   dataString += " ,";
   dataString += String(data[1].fval);
   dataString += " ,";
   dataString += String(data[2].fval);
   dataString += ",";

   // open the file. note that only one file can be open at a time,
   // so you have to close this one before opening another.
   File dataFile = SD.open("datalog.txt", FILE_WRITE);

   // if the file is available, write to it:
   if (dataFile) {
     dataFile.println(dataString);
     dataFile.close();
     // print to the serial port too:
     Serial.println(dataString);
   }
   // if the file isn't open, pop up an error:
   else {
     Serial.println("error opening datalog.txt");
   }

}
