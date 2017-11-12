#include "ioCC2530.h"

/*
當定時器的計數值小於比較暫存器的設定值時
定時器比較Com Port電壓保持不變

當定時器的計數值小於比較暫存器的設定值時
定時器比較Com Port發生旋轉?

*/

void Timer4_PWM_Init();

void main(){
	
	Timer4_PWM_Init();
	while(1);
	
}



void Timer4_PWM_Init(){

	//配置定時器3的IO位置為備用位置2
	PERCFG |= 0x10;

	//配置P2_0為外設I/O
	P2SEL |= 0x01;
	
	//定時器輸出比較配置
	T4CCTL0 = 0xAC;
	
	//定時器比較暫存器配置
	T4CC0 = 0x00;
	
	//啟動定時器3，128分頻
	T4CTL = 0xF4;

}


