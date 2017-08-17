#include "ioCC2530.h"

#define LED1 P1_3
#define LED2 P1_4
#define SW1 P0_2
#define SW2 P0_1
unsigned char Stat_key = 0;   //按???全局?量
/*===================延?函?=========================*/
void Delay(unsigned int t)
{
  while(t--);
}
/*================端口初始化函?======================*/
void InitPort()
{
  P1SEL &= ~0x18;         //?P1_3和P1_4?置?通用I/O端口功能
  P1DIR |= 0x18;          //?P1_3和P1_4的端口??方式?置??出
  P0SEL &= ~0x06;         //?P0_1?置?通用I/O端口功能
  P0DIR &= ~0x06;         //?P0_1的端口??方式?置??入
  
  LED1 = 0;               //上?的?候，LED1不亮
  LED2 = 0;               //上?的?候，LED2不亮
}
/*=================按??描函?=======================*/
void ScanKeys()
{
  if(SW1 == 0)
  {                       //??SW1有低?平信?
    Delay(100);           //按?去抖?
    if(SW1 == 0)		//确?是有按??作
    {                      
      while(SW1 == 0);    //等待按?1松?
	  
      //判?按?1按下之前，LED?是打??是??的？
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
/*=====================主函?=========================*/
void main()
{
  InitPort();
  while(1)
  {
    ScanKeys();
  }
}