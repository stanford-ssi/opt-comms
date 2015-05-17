//Created August 23 2006
//Heather Dewey-Hagborg
//http://www.arduino.cc

#include <ctype.h>
#include <SoftwareSerial.h>

byte rx = 6;
byte tx = 7;
//byte celestron.val;

SoftwareSerial celestron(rx,tx);

void setup() {
  Serial.begin(9600);
  celestron.begin(9600);
  //delay(1000);
  /*celestron.print('P');
  celestron.print(2);
  celestron.print(16);
  celestron.print(36);
  celestron.print(9);
  celestron.print(0);
  celestron.print(0);
  celestron.print(0);*/
}

void loop()
{
  
  if(Serial.available()){
    char c = Serial.read();
    celestron.print(c);
    //delay(2);
  }
  
  if(celestron.available()){
    char in = celestron.read();
    Serial.print(in);
    //delay(2);
  }
}

