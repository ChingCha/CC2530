#include <iocc2530.h>
#include <string.h>

#define uint unsigned int
#define uchar unsigned char

//定义LED
#define rled P1_0
#define gled P1_1

//函数声明
void delay(uint);
void uarttx_send_string(char *data,int len);
//延迟函数
void delay(uint n)
{
  uint i;
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
}
//串口发送字符串函数
void uarttx_send_string(char *data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF=*data++;
    while(UTX0IF==0);
    UTX0IF=0;
  }
}

char txdata[25]="start transmit:\n";

//主函数
void main(void)
{
  //初始化LED
  P1DIR=0X03;
  rled=1;
  gled=1;
  
  //初始化串口
  CLKCONCMD &=0XBF;//系统时钟为32MHZ
  while(CLKCONSTA & 0X40);//等待时钟稳定
  CLKCONCMD &=0XF8;//主时钟频率为32MHZ
  
  PERCFG &=0XFE;//设USART0的ALT 1
  P0SEL |=0X3C;//P0口2、3、4、5做外设
  P2DIR &=0X3F;//P0外设优先级USART0最高
  
  U0CSR |=0X80;//设USART0 工作方式为 UART
  U0GCR |=9;
  U0BAUD |=59;//设波特率
  UTX0IF=0;//UART0 TX中断标志位清0
  
  //传送字符串
  uarttx_send_string(txdata,25);
    
  uint i;
  for(i=0;i<30;i++)
    txdata[i]=' ';
  strcpy(txdata,"hello,cc2530\n");
  
  while(1)
  {
    uarttx_send_string(txdata,sizeof("hello,cc2530\n"));
    delay(60000);
    gled=!gled;
    delay(60000);
    delay(60000);
  }
}