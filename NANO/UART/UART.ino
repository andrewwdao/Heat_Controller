/*
 * SLAVE UART
 * 
 */
#include "config.h"

String masterMes="";

void UART_init() {
  SERIAL_BEGIN();
  while (!Serial.available());
   while (1) {
    while (Serial.available()) {
      char temp = Serial.read();
      if (temp=='\n') {
        int masterCheck = masterMes.toInt();
        if (masterCheck==MASTER_READY) {
          S_PRINTLN(SLAVE_READY);
          return;
        } //end if
        masterMes="";
      }//end if
      else masterMes+=temp;
   }//end while
  }//end while 1
}//end UART_init


//------------------------
void setup(){
  UART_init();
}

void loop()
{

}
