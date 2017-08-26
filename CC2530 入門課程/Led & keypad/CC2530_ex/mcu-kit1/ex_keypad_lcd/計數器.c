#include "ioCC2530.h"

#define LED6 P0_6
#define LED5 P0_5

//定時器初始化函數
void Init_Timer1(){
	
	//最大計數值(選用內部系統時鐘16MHz)
	T1CC0L = 0xd4;	//最大計數值低8位元
	T1CC0H = 0x30;	//最大計數值高8位元
	
	T1CCTL0 |= 0x04;	//開啟定時器1通道0的輸出比較模式
	
	T1IE = 1;		//致能定時器1中斷，1秒定時
	T1OVFIM = 1;	//致能定時器1溢出中斷，1秒定時
	EA = 1;			//致能總中斷
	
	T1CTL = 0x0e;	//分頻係數：128(1110:e)，模模式
	
}

unsigned char count = 0;

//定時器中斷服務函數
#pragma vector = T1_VECTOR		
__interrupt void Timer1_Service(){	
	T1STAT &= ~0x01;	//清除定時器1通道0中斷標誌
	count++;			//累加變數
	
	if(count%10 == 0)	//定時器1秒到
	{	
		LED5 = ~LED5;	//轉態		
	}
	if(count == 100)	//定時器10秒到
	{	
		LED6 = ~LED6;	//LED6亮，在10秒滅
		count = 0;
	}
}

//Port初始化
void Init_Port(){
	P0SEL &= ~0x60;		//將P0_5、6設置為通用I/O         
	P0DIR |= 0x60;		//將P0_5、6設置為輸出           

	LED5 = 0;               
	LED6 = 0;
}

void main()
{
  Init_Port();		//初始化Port
  Init_Timer1();	//初始化Timer1
  while(1);  		//???
}