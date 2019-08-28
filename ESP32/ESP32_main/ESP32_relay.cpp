/*------------------------------------------------------------*-
  RELAY configuration - function file
  ESP32 DEVKIT V1
  (c) An Minh Dao 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef __ESP32_RELAY_CPP
#define __ESP32_RELAY_CPP
#include "ESP32_relay.h"

// ------ Private constants -----------------------------------
#define CLOCK_PIN   18
#define LATCH_PIN   5
#define DATA_PIN  4

// ------ Private function prototypes -------------------------
/**
Send byte to the HC595
**/
void HC595_sendByte(uint16_t);
// ------ Private variables -----------------------------------
uint8_t sendData=0;
// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void relay_init() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  //shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0xFF); //Data send to the 74HC595
  relay01(OFF);relay02(OFF);relay03(OFF);
}//end relay_init
//------------------------------------------
void HC595_sendByte(uint8_t Data) {
  digitalWrite(LATCH_PIN, LOW); //make sure the relay status don't change while you're sending in bits
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, Data); //Data send to the 74HC595
  digitalWrite(LATCH_PIN, HIGH);//take the latch pin high so the relay status will be updated  
}//end HC595_sendByte
//------------------------------------------
void relay01(bool Status) {
  if (Status) {sendData|=0x02;}
  else        {sendData&=~0x02;}
  HC595_sendByte(sendData);
}//end relay01
//------------------------------------------
void relay02(bool Status) {
  if (Status) {sendData|=0x04;}
  else        {sendData&=~0x04;}
  HC595_sendByte(sendData);
}//end relay02
//------------------------------------------
void relay03(bool Status) {
  if (Status) {sendData|=0x08;}
  else        {sendData&=~0x08;}
  HC595_sendByte(sendData);
}//end relay03
#endif //__ESP32_RELAY_CPP
