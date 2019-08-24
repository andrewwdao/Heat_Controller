/**
* (c) 2019 Can Tho University. All Rights Reserved.
*/
#ifndef _CONFIG_H
#define _CONFIG_H

//----------------------------------------------------------------
// MAIN LIBRARY - WILL NEED TO EDIT THIS SECTION FOR EVERY PROJECT
//----------------------------------------------------------------
//--- WIFI ------------------------------
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//--------------------------------------------------------------
// WIFI ASSIGNING PROCEDURE
//--------------------------------------------------------------
//SSID DECLARATION
const char WLAN_SSID[]  PROGMEM = "Home";
const char WLAN_PASS[]  PROGMEM = "minhan74";

TaskHandle_t TaskSub;
#define STACK 10000 //STACK size of the wifi task (in core0)
/******** MQTT Client Setup **********/
const char SERVER[]      PROGMEM = "io.adafruit.com"; //change it to your server
const int  PORT          PROGMEM =  1883;      // use 8883 for SSL - change it to your port
const char USERNAME[]    PROGMEM = "heatcontroller2019"; //change it to your username
const char PASS[]        PROGMEM = "36374516bd4246869ce62deac0924c15"; //change it to your password
const char CLIENT_ID[]   PROGMEM = "HC01";

const char LWT_TOPIC[]   PROGMEM = "heatcontroller2019/feeds/availability"; //change it to your last will topic
const char LWT_PAYLOAD[] PROGMEM = "offline";
const char LWT_RETAIN    PROGMEM =  1;   //The broker will store the last message as the last known good value if this flag is on
#define    RETAIN                  true  //The broker will store the last message as the last known good value
#define    NO_RETAIN               false //The broker will not store the last message as the last known good value
const char PUB_RETRIES     PROGMEM = 10;
const char PUB_WAIT        PROGMEM = 700;
//MQTT_CONN_KEEPALIVE is defined inside the Adafruit_MQTT.h (default 5 minutes) --> need to change to 15 min (900)
//CLEAN_SESSION is defined as TRUE as always clean the session

const char TEMP1_FEED[]   PROGMEM = "heatcontroller2019/feeds/temp01"; //command feed, chang it to yours
const char TEMP2_FEED[]   PROGMEM = "heatcontroller2019/feeds/temp02"; //command feed, chang it to yours
const char TEMP3_FEED[]   PROGMEM = "heatcontroller2019/feeds/temp03"; //command feed, chang it to yours
const char TEMP4_FEED[]   PROGMEM = "heatcontroller2019/feeds/temp04"; //command feed, chang it to yours

const int  PING_WAIT            PROGMEM = 55000;
const char PING_TIMES           PROGMEM = 10;

//--------------------------------------------------------------
// PIN ASSIGNING AND CONSTANT DECLARATION PROCEDURE
//--------------------------------------------------------------

#endif //_CONFIG_H
