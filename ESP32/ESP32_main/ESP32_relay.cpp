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
#define CLK_595   18
#define STR_595   5
#define DATA_595  4

// ------ Private function prototypes -------------------------
/**
Send byte to the HC595
**/
void HC595_sendByte(uint16_t);
// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void relay_init() {
  pinMode(CLK_595,OUTPUT);
  pinMode(STR_595,OUTPUT);
  pinMode(DATA_595,OUTPUT);
}//end relay_init
//------------------------------------------
void HC595_sendByte(uint16_t d) {
  unsigned int t=0x80;
  digitalWrite(STR_595,LOW); 
  // shiftOut(data595, clk, LSBFIRST, d) ;
  for (int i=0;i<8;i++)
  {
    if ((d&0x80)==0x80){
      digitalWrite(DATA_595,LOW);
    } else {
      digitalWrite(DATA_595,HIGH);
    } //end if else 
    d=d<<1;
    digitalWrite(CLK_595,LOW);
    delay(10);
    digitalWrite(CLK_595,HIGH);  
  }// end for 
  digitalWrite (STR_595,HIGH);
  delay(10);
  digitalWrite (STR_595,LOW);
}//end HC595_sendByte
//------------------------------------------
void relay01(bool Status) {
  if (Status) {HC595_sendByte(1);}
  else        {HC595_sendByte(0);}
}//end relay01
//------------------------------------------
void relay02(bool Status) {
  if (Status) {HC595_sendByte(2);}
  else        {HC595_sendByte(0);}
}//end relay02
//------------------------------------------
void relay03(bool Status) {
  if (Status) {HC595_sendByte(4);}
  else        {HC595_sendByte(0);}
}//end relay03
#endif //__ESP32_RELAY_CPP
