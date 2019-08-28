/*-------------------------------------------
  RS232_485 - functions file
  ESP32 DEVKIT V1
  (c) An Minh Dao 2019 
  version 1.00 - 28/08/2019
 --------------------------------------------*/ 
#ifndef  __ESP32_RS232_485_CPP
#define  __ESP32_RS232_485_CPP
#include "ESP32_RS232_485.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
/**

**/
//void sendSD(int,int,int,int,int,int);
// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void RS232_485_init() {
  Serial2.begin(115200);
}//end RS232_485_init
//--------------------------------
bool RS232_available() {
  return Serial2.available();
}//end RS232_read
//--------------------------------
bool RS485_available() {
  return Serial2.available();
}//end RS232_read
//--------------------------------
void RS232_write(String str232) {
  Serial2.print(str232);
}//end RS232_write
//--------------------------------
char RS232_read() {
  return Serial2.read();
}//end RS232_read
//--------------------------------
void RS485_write(String str485) {
  Serial2.print(str485);
}//end RS485_write
//--------------------------------
char RS485_read() {
  return Serial2.read();
}//end RS485_read
//--------------------------------
#endif // __ESP32_RS232_485_CPP
