/*引用********************************************/
#include <iocc2530.h>
#include <string.h>
/*宏定义*****************************************/
#define uint unsigned int
#define uchar unsigned char
#define rled P1_0
#define gled P1_1
#define yled P1_4
/*函数声明和定义*******************************/
void inituart0(void);
//初始化串口0函数
void inituart0(void)
{
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
}
/*变量定义和赋值*******************************/
uchar recdata[3]="000";//初始为关状态，双引号为字符串，单引号为字符
uchar rxtxflag=1;//接收发送标志 1：接收   3：控制LED
uchar temp=0;//无数据接收到时，设为0
uint datanumber=0;//接收字符串计数
/*主函数*******************************/
void main(void)
{
  P1DIR=0X13;//初始化LED
  rled=0;
  gled=0;
  yled=0;
    
  inituart0();//初始化串口
  U0CSR |=0X40;//USART0 接收使能
  IEN0 |=0X04;//usart0 接收中断使能
  EA=1;//开总中断
  
  while(1)
  {
    if(rxtxflag==1)//接收状态
    {
      if(temp!=0)
      {
        if((temp!='#')&&(datanumber<3))//'#'被定义为结束字符，最多能接收3个字符
        {
          recdata[datanumber++]=temp;
        }
        else
        {
          rxtxflag=3;//进入发送状态
        }
        temp=0;
      }
    }
    
    if(rxtxflag==3)//控制LED状态
    {
      if(recdata[0]=='0')//红灯状态 0：关，其他开
      {
        rled=0;
      }
      else
      {
        rled=1;
      }
      if(recdata[1]=='0')//绿灯状态 0：关，其他开
      {
        gled=0;
      }
      else
      {
        gled=1;
      }
      if(recdata[2]=='0')//黄灯状态 0：关，其他开
      {
        yled=0;
      }
      else
      {
        yled=1;
      }
      rxtxflag=1;//恢复到接收状态
      recdata[0]='0';
      recdata[1]='0';
      recdata[2]='0';
      datanumber=0;//指针归0
    }
  }
}
/*接收中断函数*******************************/
//串口接收一个字符,一旦有数据从串口传至CC2530，
//则进入中断，将接收到的数据赋值给变量temp。
#pragma vector=URX0_VECTOR
__interrupt void UART0_ISR(void)
{
  URX0IF=0;//清标志
  temp=U0DBUF;//读取缓存到temp
}