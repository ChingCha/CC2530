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
		if(S1==0)
			ton=2200;  //2.2ms 左轉 
		if(S2==0)
			ton=1500;  //1.5ms 中間
		//toff=20000-ton;
	}
	
	
}


void Init_Timer1(){
	
	EA = 0;					//總致能OFF
	IEN1 |=0x02;			//Timer1中斷致能
	temp=65536-dutytime; 	//設定中斷一次的時間(預設是dutytime)
	T1CC2H = temp/256;		//高八位
    T1CC2L = temp%256;		//低八位
	T1CTL |= 0x02;			//開啟計數器：250KHz不分頻，模模式
	EA = 1;
}

void InitPort(){
	
	P0SEL &= ~0x18;
	P0DIR |= 0x18;
	P1SEL |= 0x01;              //Timer1通道2映射至P1_0，功能選擇
    PERCFG |= 0x40;             //備用位置2，?明信息
    P2SEL &= ~0x10;             //相對於Timer4，Timer1優先
    P2DIR |= 0xC0;              //定?器通道2-3具有第一優先順序
    P1DIR |= 0x01;				//P1_0為輸出
	
} 


#pragma vector = T1_VECTOR		
__interrupt void Timer1_Service(){
	if(PWM==1){
		
		IEN1 |=0x00;	//關閉Timer1中斷
		temp=65536-toff;
		T1CC2H=temp/256;
		T1CC2L=temp%256;
		IEN1 |=0x02;	//開啟Timer1中斷
		
    }else{
		
		IEN1 |=0x00;	//關閉Timer1中斷
		temp=65536-ton;
		T1CC2H=temp/256;
		T1CC2H=temp%256;
		IEN1 |=0x02;	//開啟Timer1中斷
		PWM=1;
    }
}