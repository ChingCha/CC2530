#include "ioCC2530.h"

#define LED1 P1_3
#define LED2 P1_4
#define SW1 P0_2
#define SW2 P0_1
unsigned char Stat_key = 0;   //��???����?�q
/*===================��?��?=========================*/
void Delay(unsigned int t)
{
  while(t--);
}
/*================�ݤf��l�ƨ�?======================*/
void InitPort()
{
  P1SEL &= ~0x18;         //?P1_3�MP1_4?�m?�q��I/O�ݤf�\��
  P1DIR |= 0x18;          //?P1_3�MP1_4���ݤf??�覡?�m??�X
  P0SEL &= ~0x06;         //?P0_1?�m?�q��I/O�ݤf�\��
  P0DIR &= ~0x06;         //?P0_1���ݤf??�覡?�m??�J
  
  LED1 = 0;               //�W?��?�ԡALED1���G
  LED2 = 0;               //�W?��?�ԡALED2���G
}
/*=================��??�y��?=======================*/
void ScanKeys()
{
  if(SW1 == 0)
  {                       //??SW1���C?���H?
    Delay(100);           //��?�h��?
    if(SW1 == 0)		//��?�O����??�@
    {                      
      while(SW1 == 0);    //���ݫ�?1�Q?
	  
      //�P?��?1���U���e�ALED?�O��??�O??���H
      if((Stat_key & 0x01) == 0x01)
      {
        Stat_key &= ~0x01;  
        LED1 = 0;
      }
      else{
        Stat_key |= 0x01;
        LED1 = 1;
      } 
    }
  }
}
/*=====================�D��?=========================*/
void main()
{
  InitPort();
  while(1)
  {
    ScanKeys();
  }
}