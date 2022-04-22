#include <Wire.h>
#include <RtcDS3231.h>
void RTCUpdate();
bool RTCValid();
void SetupRtc();
RtcDateTime GetRtcDateTime();
