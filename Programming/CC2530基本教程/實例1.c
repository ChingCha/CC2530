#include "ioCC2530.h"

#define LED1 P0_0
#define LED2 P0_1
#define LED3 P0_2
#define LED4 P0_3
#define LED5 P0_4
#define LED6 P0_5
#define LED7 P0_6
#define LED8 P0_7


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
	LED3 = 1;
	delay(60000);
	LED4 = 1;
	delay(60000);
	LED5 = 1;
	delay(60000);
	LED6 = 1;
	delay(60000);
	LED7 = 1;
	delay(60000);
	LED8 = 1;
	delay(60000);
	
	LED1 = 0;
    delay(60000);
    LED2 = 0;
    delay(60000);
	LED3 = 0;
	delay(60000);
	LED4 = 0;
	delay(60000);
	LED5 = 0;
	delay(60000);
	LED6 = 0;
	delay(60000);
	LED7 = 0;
	delay(60000);
	LED8 = 0;
	delay(60000);
}

void main(void)
{
   P0SEL &= ~0xFF;	//通用I/O Port
   P0DIR |= 0xFF;	//設置為輸出
  
   P0_0 = 0;
   P0_1 = 0;
   P0_2 = 0;
   P0_3 = 0;
   P0_4 = 0;
   P0_5 = 0;
   P0_6 = 0;
   P0_7 = 0;
  
   while(1)
   {
    LEDRunning();
   }
}