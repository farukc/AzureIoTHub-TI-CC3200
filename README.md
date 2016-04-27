# (Documentation is not finished yet!)
# Sample Energia code connecting Microsoft Azure IoT Hub with a TI CC3200 Launchpad XL
Texas Instruments is a certified partner for Microsoft Azure and TI CC3200 is shown Microsoft Azure IoT Developer Center

## Requirements:
- TI CC3200 Launchpad XL
- Microsoft Azure IoT Hub

**P.S.** : Please follow http://www.ti.com/cc3200start if you haven't write code to run on TI CC3200 Launchpad XL using Energia(http://www.energia.nu)

## Step-by-step instructions:
 1. Preparation of Microsoft Azure IoT Hub  : 
   1. Create a Microsoft Azure free trial account from [here](https://azure.microsoft.com/en-us/pricing/free-trial/) if you haven't used Microsoft Azure IoT Hub. 
   2. Create Azure IoT Hub :
      1. Go to http://portal.azure.com and login to the portal
      2. Click "New" as shown below : 
      ![](images/01_Azure_IoT_Hub_creation.png)
      3. Select "Internet of Things" and then "Azure IoT Hub" as shown below : 
      ![](images/02_Azure_IoT_Hub_creation.png)
      4. Give a "Name" to your IoT Hub being sure that you received green check after typing your iot hub name, pick "Pricing and scale tier" as Free (you can have only one Free IoT Hub per each Azure subscription), keep "IoT Hub units" value as one and pick the lowes value for "Device-to-cloud partitions" as we will not put this system on production yet, give a name to your "Resource group", pick the right Azure Subscription in case if you have multiple Azure subscriptions, pick the "Location" and check the "Pin to dashboard" to be able to reach your Azure IoT Hub quickly through your portal dashboard.
      ![](images/03_Azure_IoT_Hub_creation.png)
      5. You will see that your IoT Hub started to be created : 
      ![](images/04_Azure_IoT_Hub_creation.png)
      6. When your IoT Hub created, click on its tile and you should see its details similar to the shown below : 
      ![](images/04_Azure_IoT_Hub_creation.png)
      7. 
  
 2. 
   
 2 - 



Go to "Settings" of your Azure IoT Hub and obtain your connection string

Go ahead and download free tool [Azure Device Explorer](https://github.com/Azure/azure-iot-sdks/blob/master/tools/DeviceExplorer/doc/how_to_use_device_explorer.md) and connect using the connection string.

After connecting your IoT Hub in Device Explorer tool, switch to "Management" tab and create a device by clicking "Create" button. Clicking "Refresh" button will show your device. Right-mouse click on your newly created device and select "Copy connection string for selected device" to have the connection string for this device and put this in "AzureIoTHub.ino" file by finding the line below : 

```
  String IoTHubConnectionString = "{PUT YOUR IOT HUB CONNECTION STRING HERE}";
```

Now you are ready to program your TI CC3200




