 /*****************************************
//by 虚幻代码
//名称：UART0收发字符串
//说明：从PC上通过串口调试助手发送字符串给目标板，并以“#”结束。
//目标板再将收到的信息通过串口回传给PC.实验使用UART0,波特率为19200
*****************************************/
/*引用********************************************/
#include <iocc2530.h>
#include <string.h>
/*宏定义*****************************************/
#define uint unsigned int
#define uchar unsigned char
#define rled P1_0
#define gled P1_1
/*函数声明和定义*******************************/
void inituart0(void);
void uarttx_send_string(uchar *data,int len);
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
//串口发送字符串函数
void uarttx_send_string(uchar *data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF=*data++;
    while(UTX0IF==0);
    UTX0IF=0;
  }
}
/*变量定义和赋值*******************************/
uchar recdata[30]="";
uchar rxtxflag=1;//接收发送标志 1：接收   3：发送
uchar temp=0;//无数据接收到时，设为0
uint datanumber=0;//接收字符串计数
/*主函数*******************************/
void main(void)
{
  P1DIR=0X03;//初始化LED
  rled=0;
  gled=0;
    
  inituart0();//初始化串口
  U0CSR |=0X40;//USART0 接收使能
  IEN0 |=0X04;//usart0 接收中断使能
  EA=1;//开总中断
  
  while(1)
  {
    if(rxtxflag==1)//接收状态
    {
      gled=!gled;//接收指示
      if(temp!=0)
      {
        if((temp!='#')&&(datanumber<20))//'#'被定义为结束字符，最多能接收20个字符
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
    
    if(rxtxflag==3)//发送状态
    {
      gled=0;
      rled=1;//发送状态指示
      U0CSR &=~0X40;//USART0 接收禁止
      uarttx_send_string(recdata,datanumber);//发送字符串
      uarttx_send_string("\n",sizeof("\n"));//发送换行符
      U0CSR |=0X40;//USART0 接收使能
      rxtxflag=1;//恢复到接收状态
      datanumber=0;//指针归0
      rled=0;//关发送指示
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