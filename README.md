## (Documentation is not finished yet!)
# Sample Energia code connecting Microsoft Azure IoT Hub with a TI CC3200 Launchpad XL
Texas Instruments is one of the [Microsoft Azure Certified IoT partner] (https://azure.microsoft.com/en-us/marketplace/certified-iot-partners/) and TI CC3200 is listed in [Microsoft Azure IoT Developer Center](https://azure.microsoft.com/en-us/develop/iot/get-started/). Documentation in Azure IoT Developer Center includes an example for C code only. This document is prepared for TI CC3200 users who wants to connect to Azure IoT Hub using their  [Energia](http://www.energia.nu) IDE to start exploring the IoT world quickly.

### Requirements:
- TI CC3200 Launchpad XL
- A Microsoft Account (if you have any @hotmail.com, @live.com etc. email you already have one)
- Microsoft Azure Subscription (Azure free trial is OK as well)
- Following (http://www.ti.com/cc3200start) if you're just starting to write code for TI CC3200 Launchpad XL using Energia(http://www.energia.nu)

### Overview : 
In this document (and the code in the repo) you will 
 1. Connect your TI CC3200 to Azure IoT Hub
  1. Create an Azure free trial account
  2. Create an Azure IoT Hub
 2. Learn how to get your telemetry data out of Azure Stream Analytics
  1. Create an Azure Stream Analytics service and define the input and output to it
  2. Create an Azure Stream Analytics job and write your query retrieving your telemetry data from IoT Hub to PowerBI
 3. Learn how to show your telemetry data in Microsoft PowerBI
  1. Create your free trial Microsoft PowerBI account
  2. Learn how to use the "dataset" and the table to show your telemetry data live in a PowerBI dashboard

### Step-by-step instructions:
 1. Preparation of Microsoft Azure IoT Hub  : 
   1. Create a Microsoft Azure free trial account from [here](https://azure.microsoft.com/en-us/pricing/free-trial/) if you haven't used Microsoft Azure IoT Hub. 
   2. Create Azure IoT Hub :
      1. Go to http://portal.azure.com and login to the portal
      2. Click "New" as shown below : 
      ![](images/01_Azure_IoT_Hub_creation.png)
      3. Select "Internet of Things" and then "Azure IoT Hub" as shown below : 
      ![](images/02_Azure_IoT_Hub_creation.png)
      4. Give a "Name" to your IoT Hub being sure that you received check mark after typing your iot hub name, pick "Pricing and scale tier" as Free (you can have only one Free IoT Hub per each Azure subscription), keep "IoT Hub units" value as one and pick the lowes value for "Device-to-cloud partitions" as we will not put this system on production yet, give a name to your "Resource group", pick the right Azure Subscription in case if you have multiple Azure subscriptions, pick the "Location" and check the "Pin to dashboard" to be able to reach your Azure IoT Hub quickly through your portal dashboard.
      ![](images/03_Azure_IoT_Hub_creation.png)
      5. You will see that your IoT Hub started to be created : 
      ![](images/04_Azure_IoT_Hub_creation.png)
      6. When your IoT Hub created, click on its tile and you should see its details similar to the shown below : 
      ![](images/05_Azure_IoT_Hub_creation.png)
      7. Click on "Shared access policies", "iothubowner" to see the "Connection String"(s) 
      ![](images/06_Azure_IoT_Hub_creation.png)
      8. Just copy and note either of primary/secondary connection strings somewhere which will be using in coming steps
   3. Connect your Azure IoT Hub using "Device Explorer" : 
      1. Go ahead and download free tool [Azure Devic Explorer](https://github.com/Azure/azure-iot-sdks/blob/master/tools/DeviceExplorer/doc/how_to_use_device_explorer.md) and install
      2. 
      
   4. Create a "device" in your IoT Hub : 
  
 2. Modifying necesary lines in "TICC3200_AzureIoTHub_Client.ino"
 3. Run the code and see that it is sending data to IoT Hub

After connecting your IoT Hub in Device Explorer tool, switch to "Management" tab and create a device by clicking "Create" button. Clicking "Refresh" button will show your device. Right-mouse click on your newly created device and select "Copy connection string for selected device" to have the connection string for this device and put this in "AzureIoTHub.ino" file by finding the line below : 

```
  String IoTHubConnectionString = "{PUT YOUR IOT HUB CONNECTION STRING HERE}";
```

Now you are ready to program your TI CC3200




