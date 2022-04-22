#include "TM1637Header.h"

//constants
const byte CLK = 2;
const byte DIO = 4;

//variables
//TM1637 tmDisplay(CLK,DIO);
TM1637 tm1637(CLK, DIO, 5);

int8_t displayTime[4] = {99, 99, 99, 99};
int8_t minute = 99;
int8_t hour = 99;

void SetupDisplay(){
      tm1637.begin();
      tm1637.displayOff();
      tm1637.clear();
      tm1637.setBrightness(5);
      tm1637.displayOn();
      //display.clear();
      //display.setBrightness(7);
      //tmDisplay.init();
      //tmDisplay.set(4);  
//      tmDisplay.point(1);     
}


uint8_t getDigits(int8_t input){
      int8_t output = 0;

      switch (input ){

            case 0: output = 0b10111111; break;
            case 1: output = 0b10000110; break;
            case 2: output = 0b11011011; break;
            case 3: output = 0b11001111; break;
            case 4: output = 0b11100110; break;
            case 5: output = 0b11101101; break;
            case 6: output = 0b11111101; break;
            case 7: output = 0b10000111; break;
            case 8: output = 0b11111111; break;
            case 9: output = 0b11101111; break;
            default: output = 0b10111111; break;
      }

      return output;
}

void SetupTime(){

      RtcDateTime currTime = GetRtcDateTime();
      
      if ( minute != currTime.Minute() ){
            minute = currTime.Minute();
            hour = currTime.Hour();
            
            displayTime[3] = getDigits( minute % 10 );
            displayTime[2] = getDigits( minute / 10 );
            displayTime[1] = getDigits( hour % 10 );
            displayTime[0] = getDigits( hour / 10 );

            tm1637.writeData (0, (const uint8_t*)displayTime, sizeof( displayTime ) );
      }
}
