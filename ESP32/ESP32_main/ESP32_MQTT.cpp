/*-------------------------------------------
  Wifi MQTT - function file
  ESP32 DEVKIT V1
  (c) An Minh Dao - 2019 
  version 1.00 - 24/08/2019
-------------------------------------------- 
--------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef  __ESP32_MQTT_CPP 
#define  __ESP32_MQTT_CPP
#include "ESP32_MQTT.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
/**
Begin the Wifi 
**/
void Wifi_begin();
/**
Connect to the MQTT broker 
**/
void MQTT_connect();
// ------ Private variables -----------------------------------
uint32_t lastmillis;
// ------ PUBLIC variable definitions -------------------------
WiFiClient client; // Create an ESP32/ESP8266 WiFiClient class to connect to the MQTT server.
Adafruit_MQTT_Client mqtt(&client, SERVER, PORT, CLIENT_ID, USERNAME, PASS); // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
//PUBLISH
//NEEDED TO BE QOS0, SO WE CAN USE OUR QOS1 FUNCTION
Adafruit_MQTT_Publish availability = Adafruit_MQTT_Publish(&mqtt,LWT_TOPIC,MQTT_QOS_0);
Adafruit_MQTT_Publish temp01 = Adafruit_MQTT_Publish(&mqtt,TEMP1_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp02 = Adafruit_MQTT_Publish(&mqtt,TEMP2_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp03 = Adafruit_MQTT_Publish(&mqtt,TEMP3_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp04 = Adafruit_MQTT_Publish(&mqtt,TEMP4_FEED,MQTT_QOS_0);

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void MQTT_init() {
  Wifi_begin();
  mqtt.will (LWT_TOPIC, LWT_PAYLOAD, MQTT_QOS_1, LWT_RETAIN); //Set up last will
  //mqtt.subscribe(&cmd1); // Set up MQTT subscriptions.

  MQTT_connect();
  lastmillis = millis();
  publishNow(availability,"online",RETAIN,"Status Failed to update!","Status updated!");

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
}//end MQTT_init
//------------------------------------------
void MQTT_maintain() {//keep the MQTT connection
    MQTT_connect(); //LED indicator integrated

    // Adjust PING time in seconds in Adafruit_MQTT.h:  
    //#define MQTT_CONN_KEEPALIVE 60 --> Default to 1 minutes.
    if (((millis()-lastmillis)>PING_WAIT)) {//wait for PING_WAIT msecond before ping the server to keep the mqtt connection alive
      char pingCount=0;
      while (! mqtt.ping()) {if(pingCount++>PING_TIMES) mqtt.disconnect();return;}// if ping PING_TIMES times and failed then disconnect
      lastmillis = millis(); //ping sucess
    }//end if
}//end MQTT_maintain
//------------------------------------------
void publishNow(Adafruit_MQTT_Publish topicPub,const char* MQTTmessage, bool retained, const char* failed, const char* sucess) {//--------SELF CREATED QOS1 --make sure the packet made it to the broker
  char pub=1;
  while (!topicPub.publish(MQTTmessage,retained)) {Serial.println(F(failed));delay(PUB_WAIT);if (pub++>(PUB_RETRIES-1)) break;} 
  if (pub<(PUB_RETRIES)) {Serial.println(F(sucess));}
}//end publishNow
//------------------------------------------
void publishNow(Adafruit_MQTT_Publish topicPub,int MQTTmessage, bool retained, const char* failed, const char* sucess) {//--------SELF CREATED QOS1 --make sure the packet made it to the broker
  char pub=1;
  while (!topicPub.publish(MQTTmessage,retained)) {Serial.println(F(failed));delay(PUB_WAIT);if (pub++>(PUB_RETRIES-1)) break;} 
  if (pub<(PUB_RETRIES)) {Serial.println(F(sucess));}
}//end publishNow
//------------------------------------------
void Wifi_begin() {
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print(F("Connecting to "));
  Serial.print(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }//endif
  
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));Serial.println(WiFi.localIP());
  Serial.println();
}//end wifi begin
//------------------------------------------
void MQTT_connect() {// Ensure the connection to the MQTT server is alive (this will make the first connection and automatically reconnect when disconnected).
  //LED INDICATOR INTEGRATED INSIDE
  if (mqtt.connected()) {digitalWrite(LED_BUILTIN,HIGH);return;} // Stop if already connected, turn on indicating LED

  digitalWrite(LED_BUILTIN,LOW); //if not connected, indicate by a LED
  Serial.println(F("Connecting to MQTT... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0)  {         // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println(F("Retrying MQTT connection in 3 seconds..."));
    mqtt.disconnect();
    delay(3000);  // wait 3 seconds
  }//end while
  Serial.println(F("MQTT Connected!"));
}//end MQTT connect
//------------------------------------------
#endif //__ESP32_MQTT_CPP
