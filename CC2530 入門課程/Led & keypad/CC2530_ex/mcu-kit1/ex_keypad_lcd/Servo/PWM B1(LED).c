#include <ioCC2530.h>  
  
typedef unsigned char uchar;  
typedef unsigned int  uint;  
  
void InitP01(void);
void InitT1();
void set_main_clock();
void Delay(unsigned int t);


void main(void)  
{  
    int i;

	//各工作週期陣列
    int dutycycle[11]={0xF7,0xE1,0xC8,0xAF,0x96,0x7D,0x64,0x4B,0x32,0x19,0x0A};
	
	InitP01();					//初始化Port
	set_main_clock();			//設置主時鐘
    InitT1();                	//Timer1初始化及PWM配置  
    while(1)  
    {  
		for(i=0;i<11;i++){	

			T1CC2H = 0x00;

			T1CC2L = dutycycle[i];

			Delay(60000);

		}
    }  
}    
  
  
/**************************************************************************** 
* 名    称: InitLed() 
* 功    能: 设置LED灯相应的IO口 
* 入口参数: 无 
* 出口参数: 无 
****************************************************************************/  
void InitP01(void)  
{  
    P1DIR |= 0x01;           //P1.0定义为输出  
    P1_0= 1;                     
}  
  
/**************************************************************************** 
 
功    能: 定时器初始化，TICKSPD 是16 MHz系统不配置时默认是2分频，即16MHz 
 
****************************************************************************/  
void InitT1()  
{  
    
    //Timer通道設置
	PERCFG |= 0x40;          //定时器1 的IO位置   1:备用位置2   
    P2SEL &= ~0x10;          //定时器1优先  
    P2DIR |= 0xC0;           //第1优先级：定时器1通道2-3  
    P1DIR |= 0xff;           //端口1为输出      
    P1SEL |= 0x01;           //timer1 通道2映射口P1_0  
    
	//根據Table7-1，P1_0必須有Timer1_2的值進行比較
	
	//20%占空比为200us
    T1CC2H = 0x00;             
    T1CC2L = 0x32;

	//1ms的周期时钟,频率为976.516HZ
    T1CC0H = 0x00;             
    T1CC0L = 0xff;

    T1CCTL2 = 0x1c;          // 模式选择 通道2比较模式  
    T1CTL = 0x02;            //250KHz8分频  
}  

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
	
	CLKCONCMD |= 0x38;          //Timer標記輸出為250kHz
}  

void Delay(unsigned int t){
	while(t--);
}

