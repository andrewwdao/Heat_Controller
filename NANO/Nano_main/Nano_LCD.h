/*------------------------------------------------------------*-
  LCD - header file
  ARDUINO NANO
  (c) An Minh Dao - Pham Thanh Tam 2019
  version 1.20 - 05/08/2019
---------------------------------------------------------------*/
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
