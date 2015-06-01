//SSI Optical Comms Celestron Control Code
//Sasha Maldonado
//May 31 2015

/*************************************

  USAGE NOTES:
  
  Code will automatically poll telescope for position. 
  Expect output in the form:
  
  <HEX>,<HEX> --> Pos: <Number>,<Number>
   Azm, Alt   -->      Azm, Alt
  
  If HIGH_PRECISION is commented out, 4 hex digits and 2 decimal points will be used
  If HIGH_PRECISION is NOT commented out, 8 hex digits and 4 decimal points will be used
  Comment out HIGH_PRECISION for TX. Uncomment HIGH_PRECISION for RX.
  
  Useful commands:
  BFFFF,FFFF 
    --> LOW PRECISION Goto AzAlt
  bFFFFFFFF,FFFFFFFF 
    --> HIGH PRECISION Goto AzAlt - only supported by RX
    
  Go to "Tools-->Port" to select the Serial port the Arduino is connected to.
  Click "Serial Monitor" in the upper right corner to open it in a new window.
  Text should begin printing into console; if not, cycle power for the telescope arm.
  Make sure "Baud Rate" is set to 9600 baud, and "Line Ending" is set to "None"
  Type commands into box in the top of Serial Monitor. Hit enter to send.
  
  Call KC3ESZ for support as needed :D

*************************************/

//Original Code Created August 23 2006
//Heather Dewey-Hagborg
//http://www.arduino.cc

#include <ctype.h>
#include <SoftwareSerial.h>

byte rx = 6;
byte tx = 7;

int pos = 0;
char response[20];
//#define HIGH_PRECISION //Comment out if not

SoftwareSerial celestron(rx,tx);

void setup() {
  Serial.begin(9600);
  celestron.begin(9600);
}

void loop()
{
  char PROMPT_CHAR = 'Z';
  #ifdef HIGH_PRECISION
    PROMPT_CHAR = 'z';
  #endif  
  
  if(Serial.available()){
    while(Serial.available()){
      char c = Serial.read();
      celestron.print(c);
    }
  }else{
    celestron.print(PROMPT_CHAR);
    delay(100);
  }
  
  while(celestron.available() && pos >= 0){
    char in = celestron.read();
    if(in == '#'){
      pos = -1;
    }else{
      response[pos] = in;
      pos++;
    }
  }
  
  if(pos == -1){
    parseResponse(response);
  }
}

void parseResponse(char message[20]){
  //Pick relevant magic numbers based on precision
  #ifndef HIGH_PRECISION
    const int START_BASE = 4096;
    const int FIELD_WIDTH = 4;
    long base = START_BASE;
    unsigned int azm = 0;
    unsigned int alt = 0;
  #endif
  
  #ifdef HIGH_PRECISION
    const long START_BASE = 268435456;
    const int FIELD_WIDTH = 8;
    long base = START_BASE;    
    unsigned long azm = 0; //unsigned is important to avoid negative values
    unsigned long alt = 0;
  #endif
 
  Serial.print(response);
  Serial.print(" --> ");
  Serial.print(" Pos: ");
  
  //Parse azimuth
  base = START_BASE;
  for(int i = 0; i<FIELD_WIDTH; i++){
    azm += base * parseHex(response[i]);
    base /= 16;
  }
  float azmdeg = (360.000 * azm / START_BASE)/16;
  Serial.print(azmdeg, FIELD_WIDTH/2);
  Serial.print(", ");
  
  //Parse altitude
  base = START_BASE;
  for(int i = FIELD_WIDTH+1; i<(2*FIELD_WIDTH)+1; i++){
    alt += base * parseHex(response[i]);
    base /= 16;
  }
  float altdeg = (360.000 * alt / START_BASE)/16;
  Serial.print(altdeg, FIELD_WIDTH/2);
  
  //End line
  Serial.println();
  pos = 0;
}

//given a character '0'-'9','A'-'F', convert to an int 0-15
int parseHex(char digit){
  int val = digit - '0';
  if(val > 9) val = digit-'A'+10;
  return val;
}
