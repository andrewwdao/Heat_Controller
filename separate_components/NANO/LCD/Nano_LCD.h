/*------------------------------------------------------------*-
  LCD - header file
  ARDUINO NANO
  (c) Can Tho University 2019
  version 1.00 - 26/07/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 * 
 *  PRIVATE FUNCTIONS CONTAIN:
 * 
 *  CAUTION: must include config.h
--------------------------------------------------------------*/
#ifndef __NANO_LCD_H
#define __NANO_LCD_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
//#include "config.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
Start the LCD
*/
void LCD_init();
/**
LCD display function
*/
void LCD_display();

// ------ Public variable -------------------------------------

#endif //_NANO_LCD_H
