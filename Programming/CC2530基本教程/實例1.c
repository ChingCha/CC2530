#include "ioCC2530.h"

 #define LED1 P1_2
 #define LED2 P1_3


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
   P1SEL &= ~0x0C;	//通用I/O Port
   P1DIR |= 0x0C;	//設置為輸出
  
   P1_2 = 0;
   P1_3 = 0;
  
   while(1)
   {
    LEDRunning();
   }
}