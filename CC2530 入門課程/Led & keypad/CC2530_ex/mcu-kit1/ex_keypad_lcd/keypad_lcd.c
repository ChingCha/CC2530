#include "ioCC2530.h"

#define LED5 P0_7
#define LED6 P0_6
#define SW1 P0_5
#define SW2 P0_4
unsigned char Stat_key = 0;   //��???����?�q
/*===================��?��?=========================*/
void Delay(unsigned int t)
{
  while(t--);
}
/*================�ݤf��l�ƨ�?======================*/
void InitPort()
{
  P0SEL &= ~0xC0;         //?P1_3�MP1_4?�m?�q��I/O�ݤf�\��
  P0DIR |= 0xC0;          //?P1_3�MP1_4���ݤf??�覡?�m??�X
  P0SEL &= ~0x30;         //?P0_1?�m?�q��I/O�ݤf�\��
  P0DIR &= ~0x30;         //?P0_1���ݤf??�覡?�m??�J

  LED5 = 0;               //�W?��?�ԡALED5���G
  LED6 = 0;               //�W?��?�ԡALED6���G
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
        LED5 = 0;
      }
      else{
        Stat_key |= 0x01;
        LED5 = 1;
      } 
    }
  }
  
  
  if(SW2 == 0)
  {                       //??SW2���C?���H?
    Delay(100);           //��?�h��?
    if(SW2 == 0)
    {                     //��?�O����??�@
      while(SW2 == 0);    //���ݫ�?2�Q?
      if((Stat_key & 0x02) == 0x02)
      {
        Stat_key &= ~0x02;
        LED6 = 0;
      }
      else{
        Stat_key |= 0x02;
        LED6 = 1;
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