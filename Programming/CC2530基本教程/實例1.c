#include "ioCC2530.h"

 #define LED1 P0_4
 #define LED2 P0_5


void delay(unsigned int t)
{
  while(t--);
}
void LEDRunning()
{
    LED1 = 1;
    delay(60000);
    LED2 = 1;
    delay(60000);
    LED1 = 0;
    delay(60000);
    LED2 = 0;
	delay(60000);
}

void main(void)
{
   P0SEL &= ~0x30;	//通用I/O Port
   P0DIR |= 0x30;	//設置為輸出
  
   P0_4=0;
   P0_5=0;
  
   while(1)
   {
    LEDRunning();
   }
}