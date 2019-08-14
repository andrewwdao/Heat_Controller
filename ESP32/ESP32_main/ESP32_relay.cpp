
#define clk 18
#define str 5
#define data595 4

void hc595 (unsigned int d );

void setup() {
 pinMode (clk,OUTPUT);
 pinMode (str, OUTPUT);
 pinMode (data595, OUTPUT);

}

void loop() {
  hc595(5);


}

//---------Chuong Trinh con-------------
/*
 * ON 1=>1
 * ON 2=>2
 * ON 3=>4
 */
void hc595 (unsigned int d ) 
{
 unsigned int t=0x80;
 digitalWrite (str,LOW); 
// shiftOut(data595, clk, LSBFIRST, d) ;
for (int i=0;i<8;i++)
{
if ((d&0x80)==0x80)
{
  digitalWrite(data595,LOW);
  }// end if
  else
  {
    digitalWrite(data595,HIGH);
    } //end else 
 d=d<<1;
 digitalWrite(clk,LOW);
 delay(10);
 digitalWrite(clk,HIGH);
   
}// end for 
digitalWrite (str,HIGH);
delay(10);
digitalWrite (str,LOW);  

  }// end hc595
