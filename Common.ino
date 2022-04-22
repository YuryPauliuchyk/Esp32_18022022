#include "Common.h"

//variables
int startTimeDelay = 0;
int strPosition = 0;

//buffer to keep floating digits
const int16_t digitsBufferSize = 16;
char digitsBuffer[digitsBufferSize];

//length and precision
int8_t temperatureLength = 7;
int8_t temperaturePrecision = 2;

void Delay( int period ){
      startTimeDelay = millis();
      while ( millis() - startTimeDelay <= period ){
            //delay
      }
}

void PrepareFloatDigitsChar(char * json, char * deviceName, float measure, int16_t len, int16_t precision){
      strcat( json, deviceName );          
      memset( digitsBuffer, 0x00, digitsBufferSize );
      dtostrf(measure, len, precision, digitsBuffer);
      RemoveExtraDigits( digitsBuffer, digitsBufferSize);
      strcat( json, digitsBuffer );
}

void PrepareJSON(char * json, int16_t jsonStrSize, Telemetry telemetry){
      memset(json, 0x00, jsonStrSize);

      //open json
      strcat( json, "{" );
      
          //add temperature
          strcat( json, "Temperature:" );
          strcat( json, "{" );

              PrepareFloatDigitsChar(json, "DS18B20:", telemetry.DS18B20Temperature, temperatureLength, temperaturePrecision);
              
//              strcat( json, "DS18B20:" );          
//              memset( digitsBuffer, 0x00, digitsBufferSize );
//              dtostrf(telemetry.DS18B20Temperature, 7, 2, digitsBuffer);
//              RemoveExtraDigits (digitsBuffer, 16);
//               
//              strcat( json, digitsBuffer );
              strcat( json, ",");

             PrepareFloatDigitsChar(json, "DS18B20 SHELLY:", telemetry.DS18B20Shelly, temperatureLength, temperaturePrecision);
    
//              strcat( json, "DS18B20 SHELLY:" );
//              memset( digitsBuffer, 0x00, digitsBufferSize );
//              dtostrf(telemetry.DS18B20Shelly, 7, 2, digitsBuffer);
//              RemoveExtraDigits (digitsBuffer, 16);
//              strcat( json, digitsBuffer );
              strcat( json, ",");

              PrepareFloatDigitsChar(json, "DHT11:", telemetry.DHT11Temperature, temperatureLength, temperaturePrecision);
              
//              strcat( json, "DHT11:" );
//              memset( digitsBuffer, 0x00, digitsBufferSize );
//              dtostrf(telemetry.DHT11Temperature, 7, 2, digitsBuffer);
//              RemoveExtraDigits (digitsBuffer, 16);
//              strcat( json, digitsBuffer );
              strcat( json, ",");

              PrepareFloatDigitsChar(json, "LM35D:", telemetry.LM35DTemperature, temperatureLength, temperaturePrecision);
              
//              strcat( json, "LM35D:" );
//              memset( digitsBuffer, 0x00, digitsBufferSize );
//              dtostrf(telemetry.LM35DTemperature, 7, 2, digitsBuffer);
//              RemoveExtraDigits (digitsBuffer, digitsBufferSize);
//              strcat( json, digitsBuffer );
              strcat( json, ",");
          
              PrepareFloatDigitsChar(json, "LM35C:", telemetry.LM35CTemperature, temperatureLength, temperaturePrecision);
                  
//              strcat( json, "LM35C:" );
//              memset( digitsBuffer, 0x00, digitsBufferSize );
//              dtostrf(telemetry.LM35CTemperature, 7, 2, digitsBuffer);
//              RemoveExtraDigits (digitsBuffer, digitsBufferSize);
//              strcat( json, digitsBuffer );
              strcat( json, ",");
              
              PrepareFloatDigitsChar(json, "TMP35:", telemetry.TMP35Temperature, temperatureLength, temperaturePrecision);
                  
//              strcat( json, "TMP35:" );
//              memset( digitsBuffer, 0x00, digitsBufferSize );
//              dtostrf(telemetry.TMP35Temperature, 7, 2, digitsBuffer);
//              RemoveExtraDigits (digitsBuffer, digitsBufferSize);
//              strcat( json, digitsBuffer );
              strcat( json, ",");
              
              PrepareFloatDigitsChar(json, "TMP36:", telemetry.TMP36Temperature, temperatureLength, temperaturePrecision);
                  
//              strcat( json, "TMP36:" );
//              memset( digitsBuffer, 0x00, digitsBufferSize );
//              dtostrf(telemetry.TMP36Temperature, 7, 2, digitsBuffer);
//              RemoveExtraDigits (digitsBuffer, digitsBufferSize);
//              strcat( json, digitsBuffer );

          
          strcat( json, "}");
          strcat( json, ",");

          //coordinates
          strcat( json, "Coordinates:");
          strcat( json, "{" );

              strcat( json, "NEO-6M:" );
              strcat( json, "{" );

                  strcat( json, "LAT:" );
                  memset( digitsBuffer, 0x00, 16 );
                  dtostrf(telemetry.Lattitude, 10, 6, digitsBuffer);
                  RemoveExtraDigits (digitsBuffer, 16);
                  strcat( json, digitsBuffer );
                  strcat( json, ",");

                  strcat( json, "LON:" );
                  memset( digitsBuffer, 0x00, 16 );
                  dtostrf(telemetry.Longitude, 10, 6, digitsBuffer);
                  RemoveExtraDigits (digitsBuffer, 16);
                  strcat( json, digitsBuffer );
          strcat( json, "}");

          Serial.println( json );
}


void RemoveExtraDigits(char * sourceStr, int16_t sourceStrSize){

      strPosition = 0 ;

      for (int16_t i = 0; i < sourceStrSize; i++ ){

            if ( sourceStr[i] != ' ' ){
                  strPosition = i;
                  break;
            }
      }
      char * tmp = new char[sourceStrSize];
      strncpy(tmp, sourceStr + strPosition, sourceStrSize - strPosition);
      memset(sourceStr, 0x00, sourceStrSize);
      strncpy(sourceStr, tmp, sourceStrSize - strPosition);

}
