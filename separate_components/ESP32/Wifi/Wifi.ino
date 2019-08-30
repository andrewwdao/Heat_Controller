/**
* (c) 2019 Can Tho University. All Rights Reserved.
* 
* NOTE: change all setting in config.h
* 
*/

#include "config.h"

WiFiClient client; // Create an ESP32/ESP8266 WiFiClient class to connect to the MQTT server.
Adafruit_MQTT_Client mqtt(&client, SERVER, PORT, CLIENT_ID, USERNAME, PASS); // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
//PUBLISH
//NEEDED TO BE QOS0, SO WE CAN USE OUR QOS1 FUNCTION
Adafruit_MQTT_Publish availability = Adafruit_MQTT_Publish(&mqtt,LWT_TOPIC,MQTT_QOS_0);
Adafruit_MQTT_Publish temp01 = Adafruit_MQTT_Publish(&mqtt,TEMP1_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp02 = Adafruit_MQTT_Publish(&mqtt,TEMP2_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp03 = Adafruit_MQTT_Publish(&mqtt,TEMP3_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp04 = Adafruit_MQTT_Publish(&mqtt,TEMP4_FEED,MQTT_QOS_0);
//SUBCRIBE
//Adafruit_MQTT_Subscribe cmd1 = Adafruit_MQTT_Subscribe(&mqtt,CMD_FEED,MQTT_QOS_1);

unsigned long lastmillis=0;
///////////////////////////////////////MAIN FUNCTION/////////////////////////////////////
void setup() {
  Serial.begin(115200); //initialize communication with PC
  MQTT_init();
  Serial.println("Ready");

    publishNow(temp01,104,RETAIN,"Temp01 Failed!","Temp01 updated!");
    publishNow(temp02,206,RETAIN,"Temp02 Failed!","Temp02 updated!");
    publishNow(temp03,308,RETAIN,"Temp03 Failed!","Temp03 updated!");
    publishNow(temp04,409,RETAIN,"Temp04 Failed!","Temp04 updated!");
}//end setup

void loop() {
  MQTT_maintain();
  
}//end loop
