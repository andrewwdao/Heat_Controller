/*------------------------------------------------------------*-
  LCD - functions file
  ARDUINO NANO
  (c) Pham Thanh Tam - An Minh Dao 2019
  version 1.00 - 26/07/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 *  
 * 
 --------------------------------------------------------------*/
#include "Nano_LCD.h"

// ------ Private constants -----------------------------------
#define LCD_ADRESS 	0x27
#define LCD_WIDTH 	16
#define LCD_HEIGHT	2
#define BUTTON_PIN	A1
#define	ERROR		9999
typedef enum {
	BUT_LEFT=1,
	BUT_DOWN,
	BUT_CONFIRM,
	BUT_RIGHT,
	BUT_UP
} ButtonState;
typedef enum {
	MAIN_STATE,
	PID_STATE,
	TEMP_STATE,
	FLOW_STATE
} LCDstate;
// ------ Private function prototypes -------------------------
/**
Read the buttons
*/
int buttonRead();
/**
Main user interface for the system
*/
void LCD_menu();
/**
User interface for the PID calibration
*/
void PIDdisplay_editor();
/**
User interface for the temperature monitoring
*/
void LCD_temp();
/**
User interface for the water flow monitoring
*/
void LCD_flow();
// ------ Private variables -----------------------------------
int currentState=MAIN_STATE;
// cac bien b_5,adc_buttons,c dùng trong cac ham PIDdisplay,LCD(),PIDdisplay_editor() vi no lien quan voi nhau nen de bien toan cuc
bool PIDchange=false;
int LCDpointer=1;
int Temp[4];// an array that saves temperature T1 to T4 correspondingly
int flow[2];// an array that saves flow sensor values correspondingly
float PID[3];// an array that saves kp,ki,kd correspondingly
// ------ PUBLIC variable definitions -------------------------
LiquidCrystal_I2C lcd(LCD_ADRESS, LCD_WIDTH, LCD_HEIGHT);

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void LCD_init() 
{
	currentState=MAIN_STATE;
	lcd.init();
	lcd.backlight();
}//end LCD_init
//--------------------------------
void LCD_display() {
	switch (currentState) {
	  case MAIN_STATE: 	{LCD_menu();break;}
	  case PID_STATE: 	{PIDdisplay_editor();break;}
	  case TEMP_STATE: 	{LCD_temp();break;}
	  case FLOW_STATE: 	{LCD_flow();break;}
	  case ERROR: 		{break;}
	}//end switch
}//end LCD_display
int buttonRead()
{
	int adc_buttons=analogRead(BUTTON_PIN);
	delay(250); //debounce
	if(adc_buttons<50) //button 1
	{
		return BUT_LEFT;
	}
	if(adc_buttons>50& adc_buttons<200) //button 2
	{
		return BUT_DOWN;
	}
	if(adc_buttons>200& adc_buttons<350) //button 3
	{
		return BUT_CONFIRM;
	}
	if(adc_buttons>350& adc_buttons<500) //button 4
    { 
		return BUT_RIGHT;
    }
	if (adc_buttons >=500 & adc_buttons<800)  //button 5
	{
		return BUT_UP;
    }
	return ERROR; //error
}//end buttonRead
void LCD_menu()
{
 //------------------------------Display user interface------------------
	lcd.clear();
	lcd.setCursor(1,0); lcd.print("1.PID");
	lcd.setCursor(9,0); lcd.print("2.TEMP");
	lcd.setCursor(1,1); lcd.print("3.FLOW");
	if(LCDpointer==1)
	{
		lcd.setCursor(0,0); lcd.print(">");
		lcd.setCursor(8,0); lcd.print(" ");
		lcd.setCursor(0,1); lcd.print(" ");
	}//end if
	if(LCDpointer==2)
	{
		lcd.setCursor(0,0); lcd.print(" ");
		lcd.setCursor(8,0); lcd.print(">");
		lcd.setCursor(0,1); lcd.print(" ");
	}//end if
	if(LCDpointer==3)
	{
		lcd.setCursor(0,0); lcd.print(" ");
		lcd.setCursor(8,0); lcd.print(" ");
		lcd.setCursor(0,1); lcd.print(">");
	}//end if
 //----------------------------------------------------------------------
 
	switch (buttonRead()) {
	  case BUT_LEFT: 
	  {
		break;
	  }
	  case BUT_RIGHT: 
	  {
		break;
	  }
	  case BUT_UP: 
	  {
		if(LCDpointer>2) 	LCDpointer=1;
		else				LCDpointer++;
		break;
	  }
	  case BUT_DOWN: 
	  {
		if(LCDpointer<2)	LCDpointer=3;
        else				LCDpointer--;
		break; 
	  }
	  case BUT_CONFIRM: 
	  {
		switch (LCDpointer) {
		  case 1: 	{currentState=PID_STATE; LCDpointer=1;return;}
		  case 2:	{currentState=TEMP_STATE;LCDpointer=1;return;}
		  case 3:	{currentState=FLOW_STATE;LCDpointer=1;return;}
		}
	  }
	  case ERROR:
	  {
		break;
	  }
	}//end switch
	return;
}//end LCD_menu
//--------------------------------
void PIDdisplay_editor()
{
	//------------------------------Display user interface------------------
	lcd.clear();
	lcd.setCursor(1,0);lcd.print("Kp:");
    lcd.setCursor(4,0);lcd.print(PID[0]);
    lcd.setCursor(9,0);lcd.print("Ki:");
    lcd.setCursor(12,0);lcd.print(PID[1]);
    lcd.setCursor(1,1);lcd.print("Kd:");
    lcd.setCursor(4,1);lcd.print(PID[2]); 
	if(LCDpointer==1)
	{
		lcd.setCursor(0,0); lcd.print(">");
		lcd.setCursor(8,0); lcd.print(" ");
		lcd.setCursor(0,1); lcd.print(" ");
	}//end if
	if(LCDpointer==2)
	{
		lcd.setCursor(0,0); lcd.print(" ");
		lcd.setCursor(8,0); lcd.print(">");
		lcd.setCursor(0,1); lcd.print(" ");
	}//end if
	if(LCDpointer==3)
	{
		lcd.setCursor(0,0); lcd.print(" ");
		lcd.setCursor(8,0); lcd.print(" ");
		lcd.setCursor(0,1); lcd.print(">");
	}//end if
    //----------------------------------------------------------------------

	switch (buttonRead()) {
	  case BUT_LEFT: 
	  {
		PID[LCDpointer-1]-=0.1;
		break;
	  }
	  case BUT_RIGHT: 
	  {
		PID[LCDpointer-1]+=0.1;
		break;
	  }
	  case BUT_UP: 
	  {
		if(LCDpointer>2) 	LCDpointer=1;
		else				LCDpointer++;
		break;
	  }
	  case BUT_DOWN: 
	  {
		if(LCDpointer<2)	LCDpointer=3;
        else				LCDpointer--;
		break; 
	  }
	  case BUT_CONFIRM: 
	  {
		currentState=MAIN_STATE;return;//back
	  }
	  case ERROR:
	  {
		break;
	  }
	}//end switch
	return;
  }//PIDdisplay_editor

void LCD_flow()
{ 
    //------------------------------Display user interface------------------
    lcd.clear();
	lcd.setCursor(0,0); lcd.print("FlowPulse1:");
	lcd.setCursor(11,0); lcd.print(flow[0]);
	lcd.setCursor(14,0); lcd.print("Hz");
	lcd.setCursor(0,1); lcd.print("FlowPulse2:");
	lcd.setCursor(11,1); lcd.print(flow[1]);
	lcd.setCursor(14,1); lcd.print("Hz");
  //----------------------------------------------------------------------
 
	switch (buttonRead()) {
	  case BUT_LEFT: 
	  {
		break;
	  }
	  case BUT_RIGHT: 
	  {
		break;
	  }
	  case BUT_UP: 
	  {
		break;
	  }
	  case BUT_DOWN: 
	  {
		break; 
	  }
	  case BUT_CONFIRM: 
	  {
		currentState=MAIN_STATE;return;//back
	  }
	  case ERROR:
	  {
		break;
	  }
	}//end switch
	return;
}// end LCD_flow()
void LCD_temp()
{
  //------------------------------Display user interface------------------
    lcd.clear();
	lcd.setCursor(0,0); lcd.print("T1:");
	lcd.setCursor(3,0); lcd.print(Temp[0]);
	lcd.setCursor(5,0); lcd.print("oC");
	lcd.setCursor(9,0); lcd.print("T2:");
	lcd.setCursor(12,0); lcd.print(Temp[1]);
	lcd.setCursor(14,0); lcd.print("oC");
	lcd.setCursor(0,1); lcd.print("T3:");
	lcd.setCursor(3,1); lcd.print(Temp[2]);
	lcd.setCursor(5,1); lcd.print("oC");
	lcd.setCursor(9,1); lcd.print("T4:");
	lcd.setCursor(12,1); lcd.print(Temp[3]);
	lcd.setCursor(14,1); lcd.print("oC");
  //----------------------------------------------------------------------
 
	switch (buttonRead()) {
	  case BUT_LEFT: 
	  {
		break;
	  }
	  case BUT_RIGHT: 
	  {
		break;
	  }
	  case BUT_UP: 
	  {
		break;
	  }
	  case BUT_DOWN: 
	  {
		break; 
	  }
	  case BUT_CONFIRM: 
	  {
		currentState=MAIN_STATE;return;//back
	  }
	  case ERROR:
	  {
		break;
	  }
	}//end switch
	return;
}// end LCD_temp
