//Created August 23 2006
//Heather Dewey-Hagborg
//http://www.arduino.cc

#include <ctype.h>
#include <SoftwareSerial.h>

byte rx = 6;
byte tx = 7;

int pos = 0;
char response[20];

SoftwareSerial celestron(rx,tx);

void setup() {
  Serial.begin(9600);
  celestron.begin(9600);
}

void loop()
{
  
  if(Serial.available()){
    char c = Serial.read();
    celestron.print(c);
  }
  
  if(celestron.available()){
    char in = celestron.read();
    Serial.print(in);
  }
}

