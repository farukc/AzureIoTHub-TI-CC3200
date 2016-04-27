
#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>
#include "sha256.h"
#include "Base64.h"

// START: WiFi settings
char SSID[] = "{YourWifiSSID}";
char PASSWORD[] = "{YourWifiPassword}";
// END: WiFi settings

//Azure IoT Hub connection string
String IoTHubConnectionString = "{PUT YOUR IOT HUB CONNECTION STRING HERE}";
//String IoTHubConnectionString = "HostName=youriothubname.azure-devices.net;DeviceId=TIcc3200-a;SharedAccessKey=8A0K1er45k5l3achAmda7UvVh6s4L7HTBdt/RnAdYuk=";

//To obtain the IoT Hub Connection String for your device, install and run Device Explorer (Ref: https://github.com/Azure/azure-iot-sdks/blob/master/tools/DeviceExplorer/doc/how_to_use_device_explorer.md)
//After connecting your IoT Hub in Device Explorer tool, switch to "Management" tab and create a device by clicking "Create" button. Clicking "Refresh" button will show your device. Right-mouse click on your newly created device
//and select "Copy connection string for selected device" to have the connection string for this device and put it below 

// START: Azure IoT Hub settings
const char* IOT_HUB_END_POINT = "/messages/events?api-version=2016-02-03";
// END: Azure IoT Hub settings

// START: JSON data to send
String data = "{message: 'Hello'}";
// END: JSON data to send

WiFiClient client;

void setup() {
  
 //======================================================================================================
 // PART 1 : Initialize serial
 //======================================================================================================
    Serial.begin(115200);

 //======================================================================================================
 // PART 2 : Establish WiFi connectivity and obtain ip
 //======================================================================================================
    // attempt to connect to Wifi network:
    Serial.print("Attempting to connect to Network named: ");
    // print the network name (SSID);
    Serial.println(SSID); 
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(SSID, PASSWORD);
    while ( WiFi.status() != WL_CONNECTED) {
      // print dots while we wait to connect
      Serial.print(".");
      delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  printWifiStatus();
  
 //======================================================================================================
 // PART 3 : Parse Azure IoT Hub connection string for host, device_id and key to prepare SAS
 //======================================================================================================
  char* HOST = (char*)GetStringValue(splitStringByIndex(splitStringByIndex(IoTHubConnectionString, ';', 0), '=', 1));
  char* DEVICE_ID = (char*)GetStringValue(splitStringByIndex(splitStringByIndex(IoTHubConnectionString, ';', 1), '=', 1));
  char* KEY = (char*)GetStringValue(splitStringByIndex(splitStringByIndex(IoTHubConnectionString, ';', 2), '=', 1));
  
  String strSasToken = createIotHubSasToken((char*)KEY, urlEncode("iots1.azure-devices.net") + urlEncode("/devices/") +  "TIcc3200-a" );
  //Serial.println("\nfull sas : " + fullSas);

  Serial.println("\nStarting connection to Azure IoT Hub...");

  // if you get a connection, report back via serial:
  if (client.sslConnect(HOST, 443)) {
    Serial.println("connected to server");
    // https://msdn.microsoft.com/en-us/library/azure/dn790664.aspx
    
    String request = String("POST ") + "/devices/" + (String)DEVICE_ID + (String)IOT_HUB_END_POINT + " HTTP/1.1\r\n" +
                     "Host: " + HOST + "\r\n" +
                     "Authorization: SharedAccessSignature " + strSasToken + "\r\n" + 
                     "Content-Length: " + data.length() + "\r\n\r\n" +
                     data;
    client.print(request);
    Serial.println(request);
    
    String response = "";
    while (client.connected()) {
      response += client.readStringUntil('\n');
    }
  
    Serial.println();
    Serial.print("Response code: ");
    Serial.println(response.substring(9, 12));
    Serial.println(response);
    Serial.println("END");
  }
}

void loop() {
}
