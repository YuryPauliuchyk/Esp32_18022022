#include "WifiModule.h"


//constants
const int RXD2 = 16;
const int TXD2 = 17;

void setup() {
  // put your setup code here, to run once:
      Serial.begin(9600);
      Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

      ConnectToWiFi();
}


void ConfigEnvironment (){

      ConnectToWiFi();

      if ( WiFi.status() == WL_CONNECTED ){
            
      }
      
}


void loop() {
  // put your main code here, to run repeatedly:

}
