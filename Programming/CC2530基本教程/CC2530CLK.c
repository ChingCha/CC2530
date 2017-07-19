#include "ioCC2530.h"

#define  LED5   P1_3
#define  LED6   P1_4
/*===============定时器1初始化函数==================*/
void Init_Timer1()
{
  T1CC0L = 0xd4;        //设置最大计数值的低8位
  T1CC0H = 0x30;        //设置最大计数值的高8位
  T1CCTL0 |= 0x04;      //开启通道0的输出比较模式
  T1IE = 1;             //使能定时器1中断
  T1OVFIM = 1;          //使能定时器1溢出中断
  EA = 1;               //使能总中断
  T1CTL = 0x0e;         //分频系数是128,模模式
}

unsigned char count = 0;  
/*================定时器1服务函数====================*/
#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice()
{
  T1STAT &= ~0x01;      //清除定时器1通道0中断标志
  count++;
  if(count%10 == 0)     //定时1秒到
  {
    LED5 = ~LED5;
  }
  if(count == 100)      //定时10秒到
  {
    LED6 = ~LED6;
    count = 0;
  }
}
/*=================端口初始化函数====================*/
void Init_Port()
{
  P1SEL &= ~0x18;  //将P1_3和P1_4设置为通用I/O端口
  P1DIR |= 0x18;   //将P1_3和P1_4的端口设置为输出
  LED5 = 0;
  LED6 = 0;
} 
/*===================主函数=========================*/
void main()
{
  Init_Port();
  Init_Timer1();
  while(1);
}