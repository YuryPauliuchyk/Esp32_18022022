#include "WifiModule.h"

//constants
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

//variables
int startTime = 0;
int endTime = 10000;
struct tm timeinfo;

void ConnectToWiFi(){
      WiFi.mode(WIFI_STA);

      if ( WiFi.status() != WL_CONNECTED ){
            WiFi.begin(ssid, password);

            startTime = millis();
            
            while (WiFi.status() != WL_CONNECTED && endTime > millis() - startTime ) {
                  //delay
            }

            if ( WiFi.status() == WL_CONNECTED ){
                  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
            }
      }
      else{
            configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      }
}


tm GetLocalTime()
{
      getLocalTime(&timeinfo);
      return timeinfo;
}
