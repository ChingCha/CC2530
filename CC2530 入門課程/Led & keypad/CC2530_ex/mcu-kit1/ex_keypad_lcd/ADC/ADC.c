#include "ioCC2530.h"
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
unsigned char F_time = 0;
/*================定时器1服务函数====================*/
#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice()
{
  T1STAT &= ~0x01;      //清除定时器1通道0中断标志
  count++;
  if(count == 10)       //定时1秒到
  {
    F_time = 1;
    count = 0;
  }
}
/*===================UR0初始化函数====================*/
void Init_Uart0()
{
  PERCFG = 0x00;    //串口0的引脚映射到位置1，即P0_2和P0_3
  P0SEL = 0x0C;     //将P0_2和P0_3端口设置成外设功能
  U0BAUD = 59;      //16MHz的系统时钟产生9600BPS的波特率
  U0GCR = 9;
  U0UCR |= 0x80;    //禁止流控，8位数据，清除缓冲器
  U0CSR |= 0xC0;    //选择UART模式，使能接收器
  UTX0IF = 0;       //清除TX发送中断标志
  URX0IF = 0;       //清除RX接收中断标志
  URX0IE = 1;       //使能URAT0的接收中断
  EA = 1;           //使能总中断
}
unsigned char dat[4];
/*===================UR0发送字符串函数==================*/
void UR0SendString(unsigned char *str, unsigned char count)
{
  while(count--)       
  {
    U0DBUF = *str++;    //将要发送的1字节数据写入U0DBUF
    while(!UTX0IF);     //等待TX中断标志，即数据发送完成
    UTX0IF = 0;  
  }
}
/*===================ADC初始化函数====================*/
void Init_ADC0()
{
  P0SEL |= 0x01;      //P0_0端口设置为外设功能
  P0DIR &= ~0x01;     //P0_0端口设置为输入端口
  APCFG |= 0x01;      //P0_0作为模拟I/O使用
}
/*===================读取ADC的数据====================*/
void Get_ADC0_Value()
{
  ADCIF = 0;
  //参考电压选择AVDD5引脚，256抽取率，AIN0通道0
  ADCCON3 = (0x80 | 0x10 | 0x00);
  while(!ADCIF);      //等待A/D转换完成，
  dat[0] = 0xaf;
  dat[1] = ADCH;      //读取ADC数据低位寄存器
  dat[2] = ADCL;      //读取ADC数据高位寄存器
  dat[3] = 0xfa;
}
/*=======================主函数======================*/
void main()
{
  Init_Uart0();
  Init_Timer1();
  Init_ADC0();
  while(1)
  {
    if(F_time == 1)           //定时1秒时间到
    {
      Get_ADC0_Value();       //进行A/D转换并读取数据
      UR0SendString(dat,4);   //向上位机发送数据
      F_time = 0;             //定时1秒标志清0
    }
  }
}