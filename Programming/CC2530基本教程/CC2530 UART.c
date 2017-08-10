#include "ioCC2530.h"
#define  LED5   P1_3
#define  LED6   P1_4
unsigned char dataRecv;
unsigned char Flag = 0;
/*===================UR0初始化函数====================*/
void Init_Uart0()
{
  PERCFG = 0x00;    //串口0的引脚映射到位置1，即P0_2和P0_3
					//外設控制暫存器USART0的I/O位置0：位置1：位置2
  P0SEL = 0x0C;     //将P0_2和P0_3端口设置成外设功能
  U0BAUD = 59;      //16MHz的系统时钟产生9600BPS的波特率
  U0GCR = 9;
  U0UCR |= 0x80;    //禁止流控，8位数据，清除缓冲器
  U0CSR |= 0xC0;    //选择UART模式，致能接收器
  UTX0IF = 0;       //清除TX发送中断标志
  URX0IF = 0;       //清除RX接收中断标志
  URX0IE = 1;       //使能URAT0的接收中断
  EA = 1;           //使能总中断
}
/*================UR0接收中断服务函数================*/
#pragma vector = URX0_VECTOR
__interrupt void UR0_RecvInt()
{
  URX0IF = 0;           //清除RX接收中断标志
  dataRecv =  U0DBUF;   //将数据从接收缓冲区读出
  Flag = 1;             //设置接收指令标志
}
/*=================UR0发送单字节函数=================*/
void UR0SendByte(unsigned char dat)
{
  U0DBUF = dat;         //将要发送的1字节数据写入U0DBUF
  while(!UTX0IF);       //等待TX中断标志，即数据发送完成
  UTX0IF = 0;           //清除TX中断标志，准备下一次发送
}
/*=================UR0发送字符串函数===============*/
void UR0SendString(unsigned char *str)
{
  while(*str != '\0')       //发送一个字符串
  {
    UR0SendByte(*str++);    //逐个发送字符串中的字节
  }
}
/*================执行上位机的指令=================*/
void ExecuteTheOrder()
{
  Flag = 0 ;            //清除接收指令标志
  switch(dataRecv)
  {
    case 0xa1:
      LED5 = 1;
      UR0SendString("The LED5 is Open!\r\n");
    break;
    case 0xa2:
      LED5 = 0;
      UR0SendString("The LED5 is Closed!\r\n");
    break;
    case 0xb1:
      LED6 = 1;
      UR0SendString("The LED6 is Open!\r\n");
    break;
    case 0xb2:
      LED6 = 0;
      UR0SendString("The LED6 is Closed!\r\n");
    break;
  }
}
/*=================端口初始化函数====================*/
void Init_Port()
{
  P1SEL &= ~0x18;       //将P1_3和P1_4设置为通用I/O端口功能
  P1DIR |= 0x18;        //将P1_3和P1_4的端口设置为输出
  LED5 = 0;             //关闭LED5灯
  LED6 = 0;             //关闭LED6灯
} 
/*===================主函数=========================*/
void main()
{
  Init_Port();         //初始化端口
  Init_Uart0();        //初始化串口0
  //先发送一个字符串，测试串口0数据传输是否正确
  UR0SendString("*广东职业技术学院--欧浩源*\r\n");
  while(1)
  {
    if(Flag == 1)      //查询是否收到上位机指令
    {
      ExecuteTheOrder();    //解析并执行指令
    }
  }
}