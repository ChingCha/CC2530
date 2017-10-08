#include "ioCC2530.h"

#define LED5 P1_0

void set_main_clock();
void PortInit();
void T1Init();
void Delay(unsigned int t);

void main()
{


	//各工作週期陣列
    //int dutycycle[11]={0xF7,0xE1,0xC8,0xAF,0x96,0x7D,0x64,0x4B,0x32,0x19,0x0A};
	
	PortInit();

	set_main_clock();

	T1Init();
	

	//T1CC2H = 0x00;

	//T1CC2L = dutycycle[1];

	
		

}

void Delay(unsigned int t){
	while(t--);
}

void PortInit()
{
    P1SEL &= ~0x00;		//P1_0設置為通用I/O
    P1DIR |= 0x01; 		//P1_0設置為輸出
	LED5 = 0;			//LED初始狀態
}


void T1Init()
{
    
    //Timer通道?置
    P1SEL |= 0x01;              //Timer1通道2映射至P1_0，功能選擇
    PERCFG |= 0x40;             //備用位置2，?明信息
    P2SEL &= ~0x10;             //相對於Timer4，Timer1優先
    P2DIR |= 0xC0;              //定?器通道2-3具有第一優先順序
    P1DIR |= 0x01;				//P1_0為輸出
    
    //Timer模式?置
    T1CTL = 0x02;               //250KHZ不分頻，模模式
    
    //根據Table7-1，P1_0必須裝Timer1通道2進行比較
	
    T1CCTL2 = 0x1C;             //比較相等為1，計數器回0則清零
	
    //裝Timer通道0初值
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM信號週期20ms
	
	
	
	
	
	//?Timer通道2比?值
    T1CC2H = 0x01;
    T1CC2L = 0x77; 		//1%的正工作週期
    //T1CC2L = 0xE1; 	//10%的正工作週期
    //T1CC2L = 0xC8; 	//20%的正工作週期
    //T1CC2L = 0xAF; 	//30%的正工作週期
    //T1CC2L = 0x96; 	//40%的正工作週期
    //T1CC2L = 0xC4; 	//50%的正工作週期
    //T1CC2L = 0x64; 	//60%的正工作週期
    //T1CC2L = 0x4B; 	//70%的正工作週期
    //T1CC2L = 0x32; 	//80%的正工作週期
    //T1CC2L = 0x19; 	//90%的正工作週期
    //T1CC2L = 0x0A; 	//99%的正工作週期
	
    //T1CC2L = 0x01; 	//?置通道2比?寄存器初值
	
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
	
	CLKCONCMD |= 0x38;          //Timer標記輸出為250kHz
}

