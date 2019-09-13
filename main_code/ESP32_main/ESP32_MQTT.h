/*-------------------------------------------------------------
  Wifi MQTT - header file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019 
  version 1.00 - 24/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef __ESP32_MQTT_H
#define __ESP32_MQTT_H
#include <WiFi.h> //for esp32
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "ESP32_NVS.h"
#include "ESP32_PID.h"
#include "ESP32_relay.h"
#include "ESP32_PWM_Pump.h"
#include "ESP32_UART.h"
//#include "config.h"

// ------ Public constants ------------------------------------
#define WLAN_SSID     "Thanh Tam"
#define WLAN_PASS     "19980115"

/******** MQTT Client Setup **********/
#define SERVER        "io.adafruit.com"                   //change it to your server
#define PORT          1883                                // use 8883 for SSL - change it to your port
#define USERNAME      "heatcontroller2019"                //change it to your username
#define PASS          "def9f50546334d019a3c58a4a908d1e7"  //change it to your password 36374516bd4246869ce62deac0924c15
#define CLIENT_ID     "HC01"

#define LWT_TOPIC     "heatcontroller2019/feeds/availability" //change it to your last will topic
#define LWT_PAYLOAD   "offline"
#define LWT_RETAIN    1     //The broker will store the last message as the last known good value if this flag is on
#define RETAIN        true  //The broker will store the last message as the last known good value
#define NO_RETAIN     false //The broker will not store the last message as the last known good value
#define PUB_RETRIES   10
#define PUB_WAIT      700
//MQTT_CONN_KEEPALIVE is defined inside the Adafruit_MQTT.h (default 5 minutes) --> need to change to 15 min (900)
//CLEAN_SESSION is defined as TRUE as always clean the session

#define KP_FEED         "heatcontroller2019/feeds/kp"   //command feed, chang it to yours
#define KI_FEED         "heatcontroller2019/feeds/ki"   //command feed, chang it to yours
#define KD_FEED         "heatcontroller2019/feeds/kd"   //command feed, chang it to yours
#define TEMP1_FEED      "heatcontroller2019/feeds/temp01"   //command feed, chang it to yours
#define TEMP2_FEED      "heatcontroller2019/feeds/temp02"   //command feed, chang it to yours
#define TEMP3_FEED      "heatcontroller2019/feeds/temp03"   //command feed, chang it to yours
#define TEMP4_FEED      "heatcontroller2019/feeds/temp04"   //command feed, chang it to yours
#define PUMP1PWM_FEED   "heatcontroller2019/feeds/pump01pwm"   //command feed, chang it to yours
#define PUMP2PWM_FEED   "heatcontroller2019/feeds/pump02pwm"   //command feed, chang it to yours
#define RELAY01_FEED    "heatcontroller2019/feeds/relay01"   //command feed, chang it to yours
#define RELAY02_FEED    "heatcontroller2019/feeds/relay02"   //command feed, chang it to yours
#define RELAY03_FEED    "heatcontroller2019/feeds/relay03"   //command feed, chang it to yours

#define PING_WAIT   55000
#define PING_TIMES  10

// ------ Public function prototypes --------------------------
/**
Initialize Wifi and MQTT
**/
void MQTT_init();
/**
Keep the MQTT connection even if no data was sent to the broker
**/
void MQTT_maintain();
/**
MQTT subscribe task. wait for signal from the server
**/
void MQTT_subscribe();
/**
publish the wanted value to the broker (self-created QOS1)-- make sure the packet made it to the broker
**/
void publishNow(Adafruit_MQTT_Publish,const char*,bool,const char*,const char*);
void publishNow(Adafruit_MQTT_Publish,int, bool,const char*,const char*);
void publishNow(Adafruit_MQTT_Publish,float, bool,const char*,const char*);
// ------ Public variable -------------------------------------
extern SemaphoreHandle_t baton; //declared in core0 cpp
//PUBLISH
extern Adafruit_MQTT_Publish pub_kp;
extern Adafruit_MQTT_Publish pub_ki;
extern Adafruit_MQTT_Publish pub_kd;
extern Adafruit_MQTT_Publish temp01;
extern Adafruit_MQTT_Publish temp02;
extern Adafruit_MQTT_Publish temp03;
extern Adafruit_MQTT_Publish temp04;
extern Adafruit_MQTT_Publish pub_pump1pwm;
extern Adafruit_MQTT_Publish pub_pump2pwm;
extern Adafruit_MQTT_Publish pub_relay01;
extern Adafruit_MQTT_Publish pub_relay02;
extern Adafruit_MQTT_Publish pub_relay03;
//SUBCRIBE
extern Adafruit_MQTT_Subscribe sub_kp;
extern Adafruit_MQTT_Subscribe sub_ki;
extern Adafruit_MQTT_Subscribe sub_kd;
extern Adafruit_MQTT_Subscribe sub_pump1pwm;
extern Adafruit_MQTT_Subscribe sub_pump2pwm;
extern Adafruit_MQTT_Subscribe sub_relay01;
extern Adafruit_MQTT_Subscribe sub_relay02;
extern Adafruit_MQTT_Subscribe sub_relay03;
#endif // __ESP32_MQTT_H
