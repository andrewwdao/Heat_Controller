/*------------------------------------------------------------*-
  LCD - header file
  ARDUINO NANO
  (c) Can Tho University 2019
  version 1.00 - 26/07/2019
 --------------------------------------------------------------
 * Have to change the ADC in every power supply if buttons do not work
 * Also need to turn the LCD potentiometer if the LCD is too dark
 -------------------------------------------------------------- */
#ifndef __NANO_LCD_H
#define __NANO_LCD_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Nano_UART.h"
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
/**
Change Value temp and flow to display on the LCD
*/
void changeVal(uint16_t,uint16_t,uint16_t,uint16_t,uint16_t,uint16_t);
/**
Change Set Value: PID parameters, temp and flow to display on the LCD
*/
void changeSetVal(float*,uint16_t*,uint16_t*);
/**
Change Set Value: PID parameters to display on the LCD
*/
void changeSetVal(float*);
// ------ Public variable -------------------------------------

#endif //_NANO_LCD_H
