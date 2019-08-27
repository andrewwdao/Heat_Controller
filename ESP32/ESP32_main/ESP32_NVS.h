/*------------------------------------------------------------*-
  RAM usage of the RTC module DS3231 (AT24C32) - header file
  ESP32 CORE0 - PROTOCOL CORE
  (c) An Minh Dao 2019
  version 1.00 - 13/02/2019
---------------------------------------------------------------
 *  IC: AT24C32
 *  Share space and battery with IC RTC DS3231
 *  Data will be maintained as long as the battery is alive
 *  Available RAM: 32kB
 *  Address start from 0 to 32768 (an address coresponding to a byte)
 *  Communication: I2C
 *  ESP32 GPIO:
 *      SDA:21
 *      SCL:22
 * 
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RAM_write(unsigned int RAMaddress, byte data); //write in 1 byte
 *  void RAM_page_write(unsigned int RAMaddress, byte* RAMdata, byte RAMlength); //write an array, should be less than 30 bytes
 *  byte RAM_read(unsigned int RAMaddress); //read in 1 byte
 *  void RAM_page_read(unsigned int RAMaddress, byte* RAMbuffer, byte RAMlength); //read an array, should be less than 30 bytes
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 * 
 * 
 *  CAUTION: must include config.h
--------------------------------------------------------------*/
#ifndef _ESP32_NVS_H
#define _ESP32_NVS_H
#include "config.h"
//#include "pins.h"
#include "Preferences.h" // this library save in NVS - non volatile storage memory (in flash! not EEPROM, perfect!)
#include <nvs.h>
#include <nvs_flash.h>
//#include "C1_SD_Card.h"
// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
void NVS_system_write(SystemState);
SystemState NVS_system_read();

bool NVS_AExMode_read();
void NVS_AExMode_write(bool Emode);

void NVS_WIFIdata_write(String, String);
void NVS_WIFIdata_delete();
String NVS_wifiSSID_read();
String NVS_wifiPASS_read();

void   NVS_WebAP_write(String);
String NVS_WebAP_read();
// ------ Public variable -------------------------------------

#endif //_ESP32_NVS_H
