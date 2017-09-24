#include "ioCC2530.h"

#define PWM P1_0
#define S1	P0_3
#define S2	P0_4

unsigned int dutytime=45536; //65536-45536就是責任週期
unsigned int ton=10000; //高電位比例=50%
unsigned int toff=10000; //低電位比例=50%
unsigned int temp; //給計時器工作用

void Init_Timer1();
void InitPort();

void main(){
	
	InitPort();
	Init_Timer1();
	
	while(1)
	{
		if(S1==0)ton=2200;  //2.2ms 左轉 
		if(S2==0)ton=1500;  //1.5ms 中間
		toff=20000-ton;
	}
	
	
}


void Init_Timer1(){
	
	EA = 0;			//總致能OFF
	IEN1 |=0x02;	//Timer1中斷致能
	temp=65536-dutytime; //設定中斷一次的時間(預設是dutytime)
	T1CC2H = temp/256;
    T1CC2L = temp%256;
	T1CTL |= 0x0F;	//開啟計數器：128分頻、上數下數模式
	EA = 1;
}

void InitPort(){
	
	PERCFG |= 0x40; 	// set timer_1 I/O位置为2
	//P0_3、4設置為通用I/O & 輸入
	P0SEL &= ~0x18;
	P0DIR &= ~0x18;
	//P1_0設置為通用I/O & 輸出
	P1SEL &= ~0x01;		//P1_0設置為通用I/O
    P1DIR |= 0x01; 		//P1_0設置為輸出
	
} 


#pragma vector = T1_VECTOR		
__interrupt void Timer1_Service(){
	if(PWM==1)
    {
    T1CTL=0x00;
    temp=65536-toff;
    TH0=temp/256;
    TL0=temp%256;
    T1CTL=0x0F;
    PWM=0;
    }
    else
    {
    T1CTL=0x00;
    temp=65536-ton;
    TH0=temp/256;
    TL0=temp%256;
    T1CTL=0x0F;
    PWM=1;
    }
}