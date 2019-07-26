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
#include <LiquidCrystal_I2C.h>

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
void LCD_PID(int vt); // chuong trinh con nay chi can khai bao, dung quan tam den no (^_^)
void LCD();// chuong trinh con nay cung vay chi can khai bao

void EDIT_PID();// day la chuong trinh con chinh, co chuc nang hien thi va chinh sua thong so PID
void LCD_menu();
void LCD_temp();
void LCD_flow();
// ------ Private variables -----------------------------------
// cac bien b_5,adc_buttons,c dùng trong cac ham LCD_PID,LCD(),EDIT_PID() vi no lien quan voi nhau nen de bien toan cuc
int b_5=0;
int adc_buttons;
int c; 
int CMN=1;
int Temp[4];// an array that saves temperature T1 to T4 correspondingly
int flow[2];// an array that saves flow sensor values correspondingly
float PID[3];// an array that saves kp,ki,kd correspondingly
// ------ PUBLIC variable definitions -------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void setup() {
 lcd.init();
 lcd.backlight();
 Serial.begin(115200);
}

void loop() {
  
LCD_menu();

}
//--------------------------------
void LCD_menu()
{
  LCD_menu:
  lcd.setCursor(1,0);
  lcd.print("1.PID");
  lcd.setCursor(9,0);
  lcd.print("2.TEMP");
  lcd.setCursor(1,1);
  lcd.print("3.FLOW");
  
  adc_buttons=analogRead(A1);
 
   if(adc_buttons>300& adc_buttons<500)
     { delay(250);
      if(CMN>=3)
      CMN=1;
       else
        CMN++;
       }
     if(adc_buttons>200& adc_buttons<350)
     {delay(250);
        if(CMN<=1)
         CMN=3;
         else
         CMN--;
      }
  if(CMN==1)
  {
     lcd.setCursor(0,0);
     lcd.print(">");
     lcd.setCursor(0,1);
     lcd.print(" ");
     lcd.setCursor(8,0);
     lcd.print(" ");
    }
   if(CMN==2)
  {
     lcd.setCursor(8,0);
     lcd.print(">");
     lcd.setCursor(0,0);
     lcd.print(" ");
     lcd.setCursor(0,1);
     lcd.print(" "); 
    }  
     if(CMN==3)
  {
     lcd.setCursor(0,1);
     lcd.print(">");
     lcd.setCursor(8,0);
     lcd.print(" ");
     lcd.setCursor(0,0);
     lcd.print(" ");
    }

  if (adc_buttons >=500 & adc_buttons<800&(CMN==1))  
  {
    EDIT_PID();
     goto LCD_menu;
    }
  if (adc_buttons >=500 & adc_buttons<800&(CMN==2)) 
  { delay(500);
    int k=1;
    lcd.clear();
     while(k)
    { adc_buttons=analogRead(A1);
      LCD_temp();
       if (adc_buttons >=500 & adc_buttons<800)
       {delay(500);
        k=0;}
      
      }
      lcd.clear();
    }
  if (adc_buttons >=500 & adc_buttons<800&(CMN==3)) 
  {delay(500);
  int k=1;
  lcd.clear();
       while(k)
    {
      adc_buttons=analogRead(A1);
       LCD_flow();
       if (adc_buttons >=500 & adc_buttons<800)
       {delay(500);
        k=0;}
      }
      lcd.clear();
    }
    
  
  }
//--------------------------------
void EDIT_PID()
{ 
  
  adc_buttons=analogRead(A1);

  int c;
   LCD();
        
    
    if (adc_buttons >=500 & adc_buttons<800)// nhan nut 5
    { delay(250);
      if(b_5>=2)
       {
        b_5=1;
        } 
       else
        { b_5++;}
    }
    
    if(b_5==1)
    { c=1;
      LCD_PID(c);

        if(c==1)
        {
          if(adc_buttons>50& adc_buttons<200)
             { delay(200);
              PID[0]++;
              LCD_PID(c);
              }
            else if(0<adc_buttons&200>adc_buttons) 
                 { delay(200);
                  PID[0]--;
                  LCD_PID(c);
                  } 
          }// end if(c==1)

        
        if(c==2)
        {
          if(adc_buttons>50& adc_buttons<200)
             {delay(200);
              PID[1]++;
              LCD_PID(c);
              }
            else if(0<adc_buttons&200>adc_buttons) 
                 {delay(200);
                  PID[1]--;
                  LCD_PID(c);
                  } 
          }// end if(c==1)


          
        if(c==3)
        {
          if(adc_buttons>50& adc_buttons<200)
             {delay(200);
              PID[0]++;
              LCD_PID(c);
              }
            else if(0<adc_buttons&200>adc_buttons) 
                 {delay(200);
                  PID[2]--;
                  LCD_PID(c);
                  } 
          }// end if(c==1)

         
      }// end if b_5==1

      if(b_5==2)
      {

//          LCD();
//          lcd.setCursor(0,0);
//          lcd.print(" ");
//          lcd.setCursor(8,0);
//          lcd.print(" ");
//          lcd.setCursor(0,1);
//          lcd.print(" ");
//          lcd.setCursor(8,1);
//          lcd.print(" ");
       lcd.clear();
      
            
        
        }
  
  
  }
//-----------------------------
void LCD_PID( int vt)
{ 
  
  switch (vt)
  { out3:
    case 1: while(b_5==1)
           { lcd.setCursor(0,1);
            lcd.print(" ");
            lcd.setCursor(8,0);
            lcd.print(" ");
            lcd.setCursor(0,0);
            lcd.print(">");
           
            adc_buttons=analogRead(A1);
           c=1;
            if(adc_buttons>300& adc_buttons<500)// nut 4
         { delay(250);
              c++;
          
            if(c==2){goto out1;}
          }

           if (adc_buttons>200& adc_buttons<350)// nut 3
      { delay(200);

          c=3;
          if(c==3){goto out2;}
        }

         if(adc_buttons<200&adc_buttons>50)// nut 2
           {delay(200);
            PID[0]++;
            LCD();
            lcd.setCursor(0,0);
            lcd.print(">");
            }
           if(adc_buttons<50)// nut 1
           {delay(200);
            PID[0]--;
            LCD();
            lcd.setCursor(0,0);
            lcd.print(">");
             }

             if (adc_buttons >=500 & adc_buttons<800)
             {delay(200);
              b_5=2;
              return;
              }
           } 

          
            break;
            
       out1:     
    case 2: while(b_5==1)
           {
            lcd.setCursor(0,0);
            lcd.print(" ");
            lcd.setCursor(0,1);
            lcd.print(" ");
            lcd.setCursor(8,0);
            lcd.print(">");
          
            adc_buttons=analogRead(A1);
             if(adc_buttons>300& adc_buttons<500)
         {delay(200); 
          c++;
           if(c==3){goto out2;}
           }
            if (adc_buttons>200& adc_buttons<350)
              {
                delay(200);
                c--;
                if(c==1){ goto out3;}
              }
         if(adc_buttons<200&adc_buttons>50)
           {
            delay(200);
            PID[1]++;
            LCD();
            lcd.setCursor(8,0);
            lcd.print(">");
            }
           if(adc_buttons<50)
           {delay(200);
            PID[1]--;
            LCD();
            lcd.setCursor(8,0);
            lcd.print(">");
             }
           if (adc_buttons >=500 & adc_buttons<800)
             {
              delay(200);
              b_5=2;
              return;
              }//end if
           }//end while
            break;
          out2:  
        
    case 3: while(b_5==1)
           { 
            lcd.setCursor(8,0);
            lcd.print(" ");
            lcd.setCursor(0,0);
            lcd.print(" ");
            lcd.setCursor(0,1);
            lcd.print(">");
            
            adc_buttons=analogRead(A1);
            if(adc_buttons>300& adc_buttons<500)
         { delay(250);
         if(c>=3) c=1;
            else c++;
           if (c==1) {goto out3;}
           }
            if (adc_buttons>200& adc_buttons<350)
      { delay(200);
      c--;
        
          if(c==2){goto out1;}
        }
          if(adc_buttons<200&adc_buttons>50)
           {delay(250);
            PID[2]++;
            LCD();
            lcd.setCursor(0,1);
            lcd.print(">");
            lcd.setCursor(8,1);
            lcd.print(" ");
            
            }
           if(adc_buttons<50)
           { delay(250);
            PID[2]--;
            LCD();
            lcd.setCursor(0,1);
            lcd.print(">");
            lcd.setCursor(8,1);
            lcd.print(" ");
             }
             if (adc_buttons >=500 & adc_buttons<800)
             {
              delay(200);
              b_5=2;
              return;
              }//end if
           }//end while
    }// end switch 
  }// end LCD_PID

  void LCD()
  {
    
    lcd.setCursor(1,0);
    lcd.print("Kp:");
    lcd.setCursor(4,0);
    lcd.print(PID[0]);
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.setCursor(9,0);
    lcd.print("Ki:");
    lcd.setCursor(12,0);
    lcd.print(PID[1]);
    lcd.setCursor(8,0);
    lcd.print(" ");
    lcd.setCursor(1,1);
    lcd.print("Kd:");
    lcd.setCursor(4,1);
    lcd.print(PID[2]);
    lcd.setCursor(0,1);
    lcd.print(" "); 
    lcd.setCursor(8,1);
    lcd.print(" "); 
    lcd.setCursor(11,1);
    lcd.print("Back");
}
void LCD_flow()
{ 
  lcd.setCursor(0,0); lcd.print("FlowPulse1:");
  lcd.setCursor(11,0); lcd.print(flow[0]);
  lcd.setCursor(14,0); lcd.print("Hz");
  lcd.setCursor(0,1); lcd.print("FlowPulse2:");
  lcd.setCursor(11,1); lcd.print(flow[1]);
  lcd.setCursor(14,1); lcd.print("Hz");
}// end LCD_flow()
void LCD_temp()
{
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
}// end LCD_temp
