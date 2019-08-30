/*
 * MASTER UART
 * 
 */
#include "config.h"

void UART_init() {
  SERIAL_BEGIN();
  S_PRINTLN(MASTER_READY);
}//end UART_init


//------------------------
void setup(){
  UART_init();
}
String slaveMes="";
void loop()
{

}
