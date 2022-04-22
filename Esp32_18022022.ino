#include "WifiModule.h"
#include "IoTHub.h"
#include "RTC.h"
#include "TM1637Header.h"
#include "Esp32_18022022.h"
#include "Common.h"

//variables

//constants

//RX and TX pins
const int8_t RXD2 = 16;
const int8_t TXD2 = 17;

//Baud rate
const int16_t BaudRate = 9600;

//update time interval, ms
const int16_t TimeInterval = 300;

//delay loop
const int16_t LoopDelayInterval = 200;

//json string
const int16_t jsonStrSize = 512;
char json[jsonStrSize];

//serial size
int8_t serialSize;


//buffer
byte buf[128];
//time sync
long currentTime;
char timeSyncOut[10];

//variables

//time thread
Thread timeThread = Thread();

void setup() {
      Serial.begin( BaudRate );
      Serial2.begin( BaudRate, SERIAL_8N1, RXD2, TXD2 );
      if ( Serial2.available() > 0 ){
            Serial2.read();
      }
      ConfigEnvironment();
}

void ConfigEnvironment (){
      ConnectToWiFi();
      if ( WiFi.status() == WL_CONNECTED ){
            SetupRtc();
            SetupDisplay();
            timeThread.onRun( SetupTime );
            timeThread.setInterval( TimeInterval );
      }
}

void PrepareSendJSON(){
      
      
}

void loop() {
      if (!RTCValid()){
            RTCUpdate();
      }
      else{
            if (timeThread.shouldRun()){
                  timeThread.run();
            }
            
             if ( Serial2.available() ){
                    Delay( LoopDelayInterval );
                    serialSize = Serial2.available();
                    Serial2.readBytesUntil( 255, buf, serialSize );
                          
                    if ( serialSize == sizeof( Command ) ){
                          memcpy(&command, buf, sizeof(Command) );
                          if ( command.cmd == SyncTime ){
                                currentTime = getTime();
                                ltoa(currentTime, timeSyncOut, 10 );
                                Serial2.write ( timeSyncOut, 10);
                          }
                    }
                    else if ( serialSize == sizeof(Telemetry) ){
                          memcpy(&telemetry, buf, sizeof(Telemetry) );
                          PrepareJSON(json, jsonStrSize, telemetry);
                    }
                    else{
                          while (Serial2.available() ){
                                Serial2.read() ;
                          }
                    }
              }
            
      }

      Delay( LoopDelayInterval );
       
}
