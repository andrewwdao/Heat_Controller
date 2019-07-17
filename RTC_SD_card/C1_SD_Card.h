/*------------------------------------------------------------*-
  Module SD card reader - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.00 - 15/02/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RFID125_init();
 *  bool hasID();  //check if there is any new ID by interrupt
 *  void RFID125_interrupt();
 *   
 *  PRIVATE FUNCTIONS CONTAIN:
 *  void GetID();
 *  long hexstr_to_value(unsigned char *str, unsigned int str_length);
 * 
 **** NOTE: ESP32 DEVKIT V1 cannot use MMC bus to communicate with SD card
 *        even though MMC is faster than SPI
 * 
 * Connect the pure SD card to the following pins (SPI):
 *   SD Card | ESP32
 *    D2       -
 *    D3       SS - D5
 *    CMD      MOSI - D23
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK - D18
 *    VSS      GND
 *    D0       MISO - D19
 *    D1       -
 * 
 * Connect SD card module to the following pins (SPI):
 *   SD Card | ESP32
 *    CS       D5
 *    CLK      D18
 *    MOSI     D23
 *    MISO     D19
 *    VCC      5V  (Cannot use 3.3V because it has a 3.3V power regulator inside)
 *    GND      GND
 * 
 * - Make long filename in SD card:
 *    make menuconfig --> Components config --> FAT filesystem support --> Long filename support in heap
 *  --> Current setting: short filename (<=8 characters) - a 8.3 filename 
 *  --> in a 8.3 filename system, file and directory names are uppercase!
 *  readmore: https://en.m.wikipedia.org/wiki/8.3_filename
 * 
 * CAUTION: must include config.h
 --------------------------------------------------------------*/
#ifndef _C1_SD_CARD_H
#define _C1_SD_CARD_H
#include "config.h"
#include "pins.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <string.h>
#include <stdio.h>
#include "C1_OLED.h"
#include "C1_RFID_125Khz.h"
#include "C1_Switch.h"
#include "N_RAM_RTC.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
void SD_init();

void SD_getClass(String*,char*,String);//number of class, string array hold classes, mode location
void SD_ACheck_make(String*,char*,char);
void SD_deleteClass(String*,char*,char,String);
void SD_deleteAllClass(String);

bool SD_checkClass(String);

void SD_updateDatabase(String*,char*,char);
/*Use for Mode 10 - clear all data sent (file DATA.TXT)*/
void SD_ClearSent();
bool SD_moveDATA();
void SD_deleteFile(String path);

// void SD_readfile(const char * path);
// void SD_writeFile(const char * path, const char * message);
// void SD_appendFile(const char * path, const char * message);
// void SD_renameFile(const char * path1, const char * path2);
// void SD_createDir(const char * path);
// void SD_removeDir(const char * path);

// ------ Public variable -------------------------------------
// extern boolean SD_classAdded;
#endif //_C1_SD_CARD_H