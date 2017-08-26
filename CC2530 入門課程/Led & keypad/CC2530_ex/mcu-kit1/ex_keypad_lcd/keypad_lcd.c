#include "ioCC2530.h"
#include "string.h"

#define LED1 P1_3
#define LED2 P1_4

unsigned char dataRecv;
unsigned char Flag = 0;
/*===================UR0初始化函?====================*/
void Init_Uart0()
{
  

	PERCFG = 0x00;    //串口0的引?映射到位置1，即P0_2和P0_3
						//外設控制暫存器USART0的I/O位置0：位置1：位置2
	P0SEL = 0x0C;     //?P0_2和P0_3端口?置成外?功能
	
	
	U0BAUD = 59;      //16MHz的系????生9600BPS的波特率
	U0GCR = 9;
	U0UCR |= 0x80;    //禁止流控，8位?据，清除??器
	U0CSR |= 0xC0;    //??UART模式，致能接收器
	
	UTX0IF = 0;       //清除TX?送中??志
	URX0IF = 0;       //清除RX接收中??志
	URX0IE = 1;       //使能URAT0的接收中?
	EA = 1;           //使能?中?
}
/*================UR0接收中?服?函?================*/
#pragma vector = URX0_VECTOR
__interrupt void UR0_RecvInt()
{
  URX0IF = 0;           //清除RX接收中??志
  dataRecv =  U0DBUF;   //??据?接收????出
  Flag = 1;             //?置接收指令?志
}

/*=================UR0?送?字?函?=================*/
void UR0SendByte(unsigned char dat)
{
  U0DBUF = dat;         //?要?送的1字??据?入U0DBUF
  while(!UTX0IF);       //等待TX中??志，即?据?送完成
  UTX0IF = 0;           //清除TX中??志，准?下一次?送
}
/*=================UR0?送字符串函?===============*/
void UR0SendString(unsigned char *str)
{
  while(*str != '\0')       //?送一?字符串
  {
    UR0SendByte(*str++);    //逐??送字符串中的字?
  }
}
/*================?行上位机的指令=================*/
void ExecuteTheOrder()
{
  Flag = 0 ;            //清除接收指令?志
  switch(dataRecv)
  {
    case 0x01:
      LED1 = 1;
      UR0SendString("The LED1 is Open!\r\n");
    break;
    case 0x02:
      LED1 = 0;
      UR0SendString("The LED1 is Closed!\r\n");
    break;
    case 0x03:
      LED2 = 1;
      UR0SendString("The LED2 is Open!\r\n");
    break;
    case 0x04:
      LED2 = 0;
      UR0SendString("The LED2 is Closed!\r\n");
    break;
  }
}
/*=================端口初始化函?====================*/
void Init_Port()
{
	P1SEL &= ~0x18;       //?P1_3和P1_4?置?通用I/O端口功能
	P1DIR |= 0x18;        //?P1_3和P1_4的端口?置??出
	LED1 = 0;             //??LED5?
	LED2 = 0; 
} 
/*===================主函?=========================*/
void main()
{
  Init_Port();         //初始化端口
  Init_Uart0();        //初始化串口0

  UR0SendByte('A');

  while(1)
  {
    if(Flag == 1)      //查?是否收到上位机指令
    {
      ExecuteTheOrder();    //解析并?行指令
    }
  }
}