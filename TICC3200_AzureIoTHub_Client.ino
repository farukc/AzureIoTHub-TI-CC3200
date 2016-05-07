
#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>
#include "sha256.h"
#include "Base64.h"

//Temperature sensor TMP006 related headers
#include <Wire.h>
#include "Adafruit_TMP006.h"
#define USE_USCI_B1 
//TI CC3220 TMP006 I2C addres is 0x41 : 
//Reference : http://www.ti.com.cn/cn/lit/ug/swru372b/swru372b.pdf / http://blog.gaku.net/cc3200-launchpad/
Adafruit_TMP006 tmp006(0x41);
void printFloat(float value, int places);

// START: WiFi settings
char SSID[] = "{YourWifiSSID}";
char PASSWORD[] = "{YourWifiPassword}";
// END: WiFi settings

// START: Azure IoT Hub settings

//Azure IoT Hub connection string
String IoTHubConnectionString = "{PUT YOUR IOT HUB CONNECTION STRING HERE}";
//String IoTHubConnectionString = "HostName=youriothubname.azure-devices.net;DeviceId=TIcc3200-a;SharedAccessKey=8A0K1er45k5l3achAmda7UvVh6s4L7HTBdt/RnAdYuk=";

boolean isConnectedToIoTHub = false;
const char* IOT_HUB_END_POINT = "/messages/events?api-version=2016-02-03";
char* HOST;
char* DEVICE_ID;
char* KEY;
String strSasToken;
// END: Azure IoT Hub settings

String dataToSend; //String variable which will be containing the JSON data to send

WiFiClient client;

void setup() {
 
 //======================================================================================================
 // PART 1 : Initialize serial
 //======================================================================================================
    Serial.begin(115200);
  
 //======================================================================================================
 // PART 2 : Initialize TMP006 builtin sensor
 //======================================================================================================
 // Initalizes the TMP006 for operation and for I2C communication
  Serial.print("\nInitializing TMP006 sensor ...  ");
  if (!tmp006.begin(TMP006_CFG_8SAMPLE)) {
    Serial.println("\nNo sensor found");
    while(1);
  }
  Serial.println("OK");

 //======================================================================================================
 // PART 3 : Establish WiFi connectivity and obtain ip
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
 // PART 4 : Parse Azure IoT Hub connection string for host, device_id and key to prepare SAS
 //======================================================================================================
  HOST = (char*)GetStringValue(splitStringByIndex(splitStringByIndex(IoTHubConnectionString, ';', 0), '=', 1));
  DEVICE_ID = (char*)GetStringValue(splitStringByIndex(splitStringByIndex(IoTHubConnectionString, ';', 1), '=', 1));
  KEY = (char*)GetStringValue(splitStringByIndex(splitStringByIndex(IoTHubConnectionString, ';', 2), '=', 1));
  
  strSasToken = createIotHubSasToken((char*)KEY, urlEncode(HOST) + urlEncode("/devices/") +  urlEncode(DEVICE_ID) );

  Serial.println("\nStarting connection to Azure IoT Hub...");
  isConnectedToIoTHub = client.sslConnect(HOST, 443);

  while(!isConnectedToIoTHub){    
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("Setup is finished ...");
}

void loop() {
  //float objt = tmp006.readObjTempC();
  //Serial.print("Object Temperature: "); Serial.print(objt); Serial.println("*C");
  float diet = tmp006.readDieTempC();
  Serial.print("Die Temperature: "); Serial.print(diet); Serial.println("*C");  
  
  // START: JSON data to send  
  char outstr[15]; //buffer to use in float to char array conversion
  dtostrf(diet,4, 1, outstr);  
  dataToSend = "{temperature: '" + (String)outstr + "'}";
  // END: JSON data to send
  
  Serial.println("\Sending data to Azure IoT Hub...");

  // if you get a connection, report back via serial:
  if (isConnectedToIoTHub) {
    // https://msdn.microsoft.com/en-us/library/azure/dn790664.aspx
    
    String request = String("POST ") + "/devices/" + (String)DEVICE_ID + (String)IOT_HUB_END_POINT + " HTTP/1.1\r\n" +
                     "Host: " + HOST + "\r\n" +
                     "Authorization: SharedAccessSignature " + strSasToken + "\r\n" + 
                     "Content-Length: " + dataToSend.length() + "\r\n\r\n" +
                     dataToSend;
    client.print(request);
    //Serial.println(request);
    
    //String response = "";
    //while (client.connected()) {      
    //  response += client.readStringUntil('}');
    //}  
    //Serial.println();
    //Serial.print("Response code: ");
    //Serial.println(response.substring(9, 12));
    //Serial.println(response);
    //Serial.println("END");
  }
   
  delay(2000);
}
