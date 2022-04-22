#include <Thread.h> 

#ifndef ESP32_18022022_
#define ESP32_18022022_

      //command type
      typedef struct __attribute((__packed__)) Command {
            int8_t cmd;
            byte termChar = 255;
      };

enum Commands{
      SyncTime = 1,
      ReceiveTelemetry = 2
};

typedef struct __attribute((__packed__)) Telemetry {

      float DS18B20Temperature;
      float DS18B20Shelly;
      float DHT11Temperature;
      float DHT11Humidity;

      float LM35DTemperature;
      float LM35CTemperature;
      float TMP35Temperature;
      float TMP36Temperature;

      float Lattitude;
      float Longitude;

      int16_t Year;
      int16_t Month;
      int16_t Day;
      int16_t Hour;
      int16_t Minute;
      int16_t Second;
      
      byte termChar = 255;
};
//variables
//telemetry struct
Telemetry telemetry;

//command variable
Command command;

#endif
