#include "ioCC2530.h"

#define LED5 P1_3
#define LED6 P1_4
#define SW1 P1_2
#define SW2 P0_1
unsigned char Stat_key = 0;   //按键状态全局变量
/*===================延时函数=========================*/
void Delay(unsigned int t)
{
  while(t--);
}
/*================端口初始化函数======================*/
void InitPort()
{
  P1SEL &= ~0x18;         //将P1_3和P1_4设置为通用I/O端口功能
  P1DIR |= 0x18;          //将P1_3和P1_4的端口传输方式设置为输出
  P1SEL &= ~0x04;         //将P1_2设置为通用I/O端口功能
  P1DIR &= ~0x04;         //将P1_2的端口传输方式设置为输入
  P0SEL &= ~0x02;         //将P0_1设置为通用I/O端口功能
  P0DIR &= ~0x02;         //将P0_1的端口传输方式设置为输入
  P0INP &= ~0x02;         //将P0_1的端口输入方式设置为：上拉/下拉
  P1INP &= ~0x04;         //将P1_2的端口输入方式设置为：上拉/下拉
  P2INP &= ~0x60;         //将P0端口和P1端口引脚设置为：上拉
  LED5 = 0;               //上电的时候，LED5不亮
  LED6 = 0;               //上电的时候，LED6不亮
}
/*=================按键扫描函数=======================*/
void ScanKeys()
{
  if(SW1 == 0)
  {                       //发现SW1有低电平信号
    Delay(100);           //按键去抖动
    if(SW1 == 0)
    {                      //确实是有按键动作
      while(SW1 == 0);    //等待按键1松开
      //判断按键1按下之前，LED灯是打开还是关闭的？
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
  {                       //发现SW2有低电平信号
    Delay(100);           //按键去抖动
    if(SW2 == 0)
    {                     //确实是有按键动作
      while(SW2 == 0);    //等待按键2松开
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
/*=====================主函数=========================*/
void main()
{
  InitPort();
  while(1)
  {
    ScanKeys();
  }
}