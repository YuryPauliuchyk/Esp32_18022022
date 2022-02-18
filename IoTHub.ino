#include "IoTHub.h"

//constants
const char* connectionString = "DEVICE_CONNECTION_STRING";

//variables
bool g_continueRunning = false;

//SetupIoTHub
IOTHUB_DEVICE_CLIENT_LL_HANDLE device_ll_handle;
int diag_off = 0;
bool urlEncodeOn = true;
int receiveContext = 0;

//GetConnectionStatusCallback
bool iotHubIsConnected = false;

//ReceiveMessageCallback
bool messageReceived = false;

IOTHUBMESSAGE_DISPOSITION_RESULT ReceiveMessageCallback (IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    int* counter = (int*)userContextCallback;
    const unsigned char* buffer;
    size_t size;

    // Message content
    if (IoTHubMessage_GetByteArray(message, (const unsigned char**)&buffer, &size) != IOTHUB_MESSAGE_OK)
    {
          return IOTHUBMESSAGE_REJECTED ;
    }
    else
    {
          g_continueRunning = false;
          (*counter)++;
          return IOTHUBMESSAGE_ACCEPTED;
    }
}

void GetConnectionStatusCallback (IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* user_context)
{
    (void)reason;
    (void)user_context;
   
    if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
    {
        iotHubIsConnected = true;
    }
    else
    {
        iotHubIsConnected = false;
    }
}

void SetupIoTHub() {
  
    IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;
    (void)IoTHub_Init();    
    device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(connectionString, protocol);
   
    if (device_ll_handle == NULL)
    {
        LogInfo("Error AZ002: Failure creating Iothub device. Hint: Check you connection string.\r\n");
    }
    else
    {
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_DIAGNOSTIC_SAMPLING_PERCENTAGE, &diag_off);
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_TRUSTED_CERT, certificates);
        IoTHubDeviceClient_LL_SetOption(device_ll_handle, OPTION_AUTO_URL_ENCODE_DECODE, &urlEncodeOn);
      
        if (IoTHubClient_LL_SetMessageCallback(device_ll_handle, ReceiveMessageCallback, &receiveContext) != IOTHUB_CLIENT_OK)
        {
            LogInfo("ERROR: IoTHubClient_LL_SetMessageCallback..........FAILED!\r\n");
        }

        (void)IoTHubDeviceClient_LL_SetConnectionStatusCallback(device_ll_handle, GetConnectionStatusCallback, NULL);

    }
}
