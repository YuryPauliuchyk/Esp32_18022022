#include "WifiModule.h"

//constants
const char* ssid = "GTE-Meeting";//"TP-Link_EB17";
const char* password = "godelguest";//"30849518";
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.windows.com";
const char* ntpServer3 = "time.nist.gov";
const int utcOffsetInSeconds = 7200;
const int daylightOffsetInSeconds = 7200;

//variables
int startTime = 0;
int endTime = 10000;
struct tm timeinfo;
time_t now;

void ConnectToWiFi(){
      WiFi.mode(WIFI_STA);

      if ( WiFi.status() != WL_CONNECTED ){
            WiFi.begin(ssid, password);
            startTime = millis();            
            while (WiFi.status() != WL_CONNECTED && endTime > millis() - startTime ) {
                  //delay
            }
      }
      
      if ( WiFi.status() == WL_CONNECTED ){
            ConfigTime();
      }
}


void ConfigTime(){
      configTime(0 , 0, ntpServer1, ntpServer2, ntpServer3 );
}

unsigned long getTime() {
      struct tm timeinfo;
      if (!getLocalTime(&timeinfo)) {
            return(0);
      }
      time(&now);
      return now;
}
