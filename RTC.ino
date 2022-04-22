#include "RTC.h"

//variables
RtcDS3231<TwoWire> rtc(Wire);
unsigned long epochTime = 0;
bool boolCheck = true;

RtcDateTime GetRtcDateTime(){
      return rtc.GetDateTime();
}

void SetupRtc (){
      rtc.Begin();
      RTCUpdate();
}

void RTCUpdate(){
      epochTime = getTime();
      if ( epochTime > 0 ){
            rtc.SetDateTime(epochTime);
            rtc.SetIsRunning(true);
      }
}

bool RTCValid(){
      
      if (!rtc.IsDateTimeValid()){
          Serial.println("RTC lost confidence in the DateTime!  Updating DateTime");
          boolCheck = false;
          RTCUpdate();    
      }
      
      if (!rtc.GetIsRunning())
      {
            Serial.println("RTC was not actively running, starting now.  Updating Date Time");
            rtc.SetIsRunning(true);
            boolCheck = false;
            RTCUpdate();
      }
}
