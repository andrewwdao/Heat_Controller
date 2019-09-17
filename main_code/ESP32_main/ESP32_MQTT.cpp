/*-------------------------------------------
  Wifi MQTT - function file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019 
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
bool Wifi_begin();
/**
Connect to the MQTT broker 
**/
bool MQTT_connect();
// ------ Private variables -----------------------------------
WiFiClient client; // Create an ESP32/ESP8266 WiFiClient class to connect to the MQTT server.
Adafruit_MQTT_Client mqtt(&client, SERVER, PORT, CLIENT_ID, USERNAME, PASS); // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
//PUBLISH
//NEEDED TO BE QOS0, SO WE CAN USE OUR QOS1 FUNCTION
Adafruit_MQTT_Publish availability = Adafruit_MQTT_Publish(&mqtt,LWT_TOPIC,MQTT_QOS_0);
Adafruit_MQTT_Publish pub_kp = Adafruit_MQTT_Publish(&mqtt,KP_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish pub_ki = Adafruit_MQTT_Publish(&mqtt,KI_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish pub_kd = Adafruit_MQTT_Publish(&mqtt,KD_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp01 = Adafruit_MQTT_Publish(&mqtt,TEMP1_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp02 = Adafruit_MQTT_Publish(&mqtt,TEMP2_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp03 = Adafruit_MQTT_Publish(&mqtt,TEMP3_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish temp04 = Adafruit_MQTT_Publish(&mqtt,TEMP4_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish pub_pump1pwm = Adafruit_MQTT_Publish(&mqtt,PUMP1PWM_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish pub_pump2pwm = Adafruit_MQTT_Publish(&mqtt,PUMP2PWM_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish pub_relay01 = Adafruit_MQTT_Publish(&mqtt,RELAY01_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish pub_relay02 = Adafruit_MQTT_Publish(&mqtt,RELAY02_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish pub_relay03 = Adafruit_MQTT_Publish(&mqtt,RELAY03_FEED,MQTT_QOS_0);
//SUBCRIBE
Adafruit_MQTT_Subscribe sub_kp = Adafruit_MQTT_Subscribe(&mqtt,KP_FEED,MQTT_QOS_1);
Adafruit_MQTT_Subscribe sub_ki = Adafruit_MQTT_Subscribe(&mqtt,KI_FEED,MQTT_QOS_1);
Adafruit_MQTT_Subscribe sub_kd = Adafruit_MQTT_Subscribe(&mqtt,KD_FEED,MQTT_QOS_1);
Adafruit_MQTT_Subscribe sub_pump1pwm = Adafruit_MQTT_Subscribe(&mqtt,PUMP1PWM_FEED,MQTT_QOS_1);
Adafruit_MQTT_Subscribe sub_pump2pwm = Adafruit_MQTT_Subscribe(&mqtt,PUMP2PWM_FEED,MQTT_QOS_1);
Adafruit_MQTT_Subscribe sub_relay01 = Adafruit_MQTT_Subscribe(&mqtt,RELAY01_FEED,MQTT_QOS_1);
Adafruit_MQTT_Subscribe sub_relay02 = Adafruit_MQTT_Subscribe(&mqtt,RELAY02_FEED,MQTT_QOS_1);
Adafruit_MQTT_Subscribe sub_relay03 = Adafruit_MQTT_Subscribe(&mqtt,RELAY03_FEED,MQTT_QOS_1);

uint32_t lastmillis;
// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void MQTT_init() {
  if (Wifi_begin()) {
    mqtt.will (LWT_TOPIC, LWT_PAYLOAD, MQTT_QOS_1, LWT_RETAIN); //Set up last will
    mqtt.subscribe(&sub_kp); // Set up MQTT subscriptions.
    mqtt.subscribe(&sub_ki); // Set up MQTT subscriptions.
    mqtt.subscribe(&sub_kd); // Set up MQTT subscriptions.
    mqtt.subscribe(&sub_pump1pwm); // Set up MQTT subscriptions.
    mqtt.subscribe(&sub_pump2pwm); // Set up MQTT subscriptions.
    mqtt.subscribe(&sub_relay01); // Set up MQTT subscriptions.
    mqtt.subscribe(&sub_relay02); // Set up MQTT subscriptions.
    mqtt.subscribe(&sub_relay03); // Set up MQTT subscriptions.
    
    if (MQTT_connect()) {
      lastmillis = millis();
      publishNow(availability,"online",RETAIN,"Status Failed!","Status updated!");
      delay(500);
      publishNow(pub_kp,NVS_read_Kp(),RETAIN,"Kp Failed!","Kp updated!");
      delay(500);
      publishNow(pub_ki,NVS_read_Ki(),RETAIN,"Ki Failed!","Ki updated!");
      delay(500);
      publishNow(pub_kd,NVS_read_Kd(),RETAIN,"Kd Failed!","Kd updated!");
    }//end if
  }//end if
  
  //pinMode(LED_BUILTIN,OUTPUT);
  //digitalWrite(LED_BUILTIN,LOW);
}//end MQTT_init
//------------------------------------------
void MQTT_maintain() {//keep the MQTT connection
    if (MQTT_connect()) { //LED indicator integrated
      // Adjust PING time in seconds in Adafruit_MQTT.h:  
      //#define MQTT_CONN_KEEPALIVE 60 --> Default to 1 minutes.
      if (((millis()-lastmillis)>PING_WAIT)) {//wait for PING_WAIT msecond before ping the server to keep the mqtt connection alive
        char pingCount=0;
        while (! mqtt.ping()) {if(pingCount++>PING_TIMES) mqtt.disconnect();return;}// if ping PING_TIMES times and failed then disconnect
        lastmillis = millis(); //ping sucess
      }//end if
    }//end if
}//end MQTT_maintain
//------------------------------------------
void MQTT_subscribe() {
   if (WiFi.status() == WL_CONNECTED) {
      if (MQTT_connect()) {
        //SUBCRIBE:
        // this is our 'wait for incoming subscription packets' busy subloop. Max is 15 subs at a time, change at Adafruit_MQTT.h, #define MAXSUBSCRIPTIONS 15
        Adafruit_MQTT_Subscribe *subscription;                  
        while ((subscription = mqtt.readSubscription(5000))) {      //wait for signal
          if (subscription == &sub_kp) {                         // if something new is detected on this topic
            String sdata = (char*)sub_kp.lastread;   // Function to analize the string
            float sfloat = sdata.toFloat();
            if (sfloat!=NVS_read_Kp()) {
              PID_Kp_write(sfloat);
              UART_PIDsendToSlave();
            }//end if
            break;
          }//end if
          if (subscription == &sub_ki)  {                           // if something new is detected on this topic
            String sdata = (char*)sub_ki.lastread;   // Function to analize the string
            float sfloat = sdata.toFloat();
            if (sfloat!=NVS_read_Ki()) {
              PID_Ki_write(sfloat);
              UART_PIDsendToSlave();
            }//end if
            break;
          }//end if  
          if (subscription == &sub_kd)  {                           // if something new is detected on this topic
            String sdata = (char*)sub_kd.lastread;   // Function to analize the string
            float sfloat = sdata.toFloat();
            if (sfloat!=NVS_read_Kd()) {
              PID_Kd_write(sfloat);
              UART_PIDsendToSlave();
            }//end if
            break;
          }//end if  
          if (subscription == &sub_pump1pwm)  {                           // if something new is detected on this topic
            String sdata = (char*)sub_pump1pwm.lastread;   // Function to analize the string
            float sfloat = (float)(sdata.toInt()/100);
            pump1_wifiChange(sfloat);
            break;
          }//end if
          if (subscription == &sub_pump2pwm)  {                           // if something new is detected on this topic
            String sdata = (char*)sub_pump2pwm.lastread;   // Function to analize the string
            float sfloat = (float)(sdata.toInt()/100);
            pump1_wifiChange(sfloat);
            break;
          }//end if
          if (subscription == &sub_relay01)  {                           // if something new is detected on this topic
            String sdata = (char*)sub_relay01.lastread;   // Function to analize the string
            if (sdata=="ON") {
              relay01(ON);
              break;
            } else if (sdata=="OFF") {
              relay01(OFF);
              break;
            }//end if else
          }//end if
          if (subscription == &sub_relay02)  {                           // if something new is detected on this topic
            String sdata = (char*)sub_relay02.lastread;   // Function to analize the string
            if (sdata=="ON") {
              relay02(ON);
              break;
            } else if (sdata=="OFF") {
              relay02(OFF);
              break;
            }//end if else
          }//end if
          if (subscription == &sub_relay03)  {                           // if something new is detected on this topic
            String sdata = (char*)sub_relay03.lastread;   // Function to analize the string
            if (sdata=="ON") {
              relay03(ON);
              break;
            } else if (sdata=="OFF") {
              relay03(OFF);
              break;
            }//end if else
          }//end if
        }//end while
      }//end if
    }//end if
}//end MQTT_subscribe
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
void publishNow(Adafruit_MQTT_Publish topicPub,float MQTTmessage, bool retained, const char* failed, const char* sucess) {//--------SELF CREATED QOS1 --make sure the packet made it to the broker
  char pub=1;
  while (!topicPub.publish(MQTTmessage,retained)) {Serial.println(F(failed));delay(PUB_WAIT);if (pub++>(PUB_RETRIES-1)) break;} 
  if (pub<(PUB_RETRIES)) {Serial.println(F(sucess));}
}//end publishNow
//------------------------------------------
void MQTT_Kp_pub(float mqttKp) {
  publishNow(pub_kp,mqttKp,RETAIN,"Kp Failed!","Kp updated!");
}//end MQTT_Kp_pub
//------------------------------------------
void MQTT_Ki_pub(float mqttKi) {
  publishNow(pub_ki,mqttKi,RETAIN,"Ki Failed!","Ki updated!");
}//end MQTT_Ki_pub
//------------------------------------------
void MQTT_Kd_pub(float mqttKd) {
  publishNow(pub_kd,mqttKd,RETAIN,"Kd Failed!","Kd updated!");
}//end MQTT_Kd_pub
//------------------------------------------
void MQTT_T1_pub(int mTemp1) {
  publishNow(temp01,mTemp1,RETAIN,"Temp01 Failed!","Temp01 updated!");
}//end MQTT_T1_pub
//------------------------------------------
void MQTT_T2_pub(int mTemp2) {
  publishNow(temp02,mTemp2,RETAIN,"Temp02 Failed!","Temp02 updated!");
}//end MQTT_T2_pub
//------------------------------------------
void MQTT_T3_pub(int mTemp3) {
  publishNow(temp03,mTemp3,RETAIN,"Temp03 Failed!","Temp03 updated!");
}//end MQTT_T3_pub
//------------------------------------------
void MQTT_T4_pub(int mTemp4) {
  publishNow(temp04,mTemp4,RETAIN,"Temp04 Failed!","Temp04 updated!");
}//end MQTT_T4_pub
//------------------------------------------
void MQTT_Pump1pwm_pub(float pwmVal) {
  publishNow(pub_pump1pwm,(int)(pwmVal*100),RETAIN,"Pump1 pwm Failed!","Pump1 pwm updated!");
}//end MQTT_Pump1pwm_pub
//------------------------------------------
void MQTT_Pump2pwm_pub(float pwmVal) {
  publishNow(pub_pump2pwm,(int)(pwmVal*100),RETAIN,"Pump2 pwm Failed!","Pump2 pwm updated!");
}//end MQTT_Pump2pwm_pub
//------------------------------------------
void MQTT_relay01_pub(bool Rstate) {
  publishNow(pub_relay01,(Rstate==ON)?("ON"):("OFF"),RETAIN,"Relay01 Failed!","Relay01 updated!");
}//end MQTT_relay01_pub
//------------------------------------------
void MQTT_relay02_pub(bool Rstate) {
  publishNow(pub_relay02,(Rstate==ON)?("ON"):("OFF"),RETAIN,"Relay02 Failed!","Relay02 updated!");
}//end MQTT_relay01_pub
//------------------------------------------
void MQTT_relay03_pub(bool Rstate) {
  publishNow(pub_relay03,(Rstate==ON)?("ON"):("OFF"),RETAIN,"Relay03 Failed!","Relay03 updated!");
}//end MQTT_relay01_pub
//------------------------------------------
bool Wifi_begin() {
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print(F("Connecting to "));
  Serial.print(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  char waitTimes=0;
  while ((WiFi.status() != WL_CONNECTED)&&(waitTimes++<10)) {
    delay(500);
    Serial.print(F("."));
  }//endif
  if (waitTimes<10) {
    Serial.println(F("WiFi connected"));
    Serial.println(F("IP address: "));Serial.println(WiFi.localIP());
    Serial.println();
    return true;
  } else {
    Serial.println(F("Wifi failed!")); Serial.println();
    return false;
  }//end if else
  return false;
}//end wifi begin
//------------------------------------------
bool MQTT_connect() {// Ensure the connection to the MQTT server is alive (this will make the first connection and automatically reconnect when disconnected).
  if (WiFi.status() == WL_CONNECTED) { //if wifi is connected
    if (mqtt.connected()) {/*digitalWrite(LED_BUILTIN,HIGH);*/return true;} // Stop if already connected, turn on indicating LED

    //digitalWrite(LED_BUILTIN,LOW); //if not connected, indicate by a LED
    Serial.println(F("Connecting to MQTT... "));
    int8_t ret;
    int8_t waitTimes=0;
    while (((ret = mqtt.connect()) != 0)&&(waitTimes<4))  {         // connect will return 0 for connected
      waitTimes++;
      Serial.println(mqtt.connectErrorString(ret));
      Serial.println(F("Retrying MQTT connection in 5 seconds..."));
      mqtt.disconnect();
      delay(5000);  // wait 5 seconds
    }//end while
    if (waitTimes<3) {
      Serial.println(F("MQTT Connected!"));Serial.println();
      return true;
    } else {
      Serial.println(F("MQTT failed!")); Serial.println();
      return false;
    }//end if else
  }//end if
  return false;
}//end MQTT connect
//------------------------------------------
#endif //__ESP32_MQTT_CPP
