#include "ioCC2530.h"

#define PWM P1_0
#define S1	P0_3
#define S2	P0_4

char defjump1=0;	//除彈跳變數1(one)
char defjump2=0;	//除彈跳變數2(zero)
unsigned char timeout=0;	//PWM信號輸出時間長度
unsigned char key=0xff;		//鍵值
unsigned char keyTemp=0xff;	//未除彈跳鍵值
unsigned char keyData=0xff;	//已除彈跳鍵值
unsigned char triwave=0;	//三角波
unsigned char degree45=(200-11);	//45度
unsigned char degree135=(200-19);//135度

void InitPort();
void KeyScan(void);
void InitTimer1();


void main(){
	
	//KeyScan();
	InitPort();		//Port初始化
	InitTimer1();	//Timer1初始化
	while(1){
		KeyScan();	//按鍵掃描
		if(keyData!=0xFF){	//按任何鍵?
			key=keyData;	//儲存鍵值至Key變數中
			keyData=0xff;	//清除鍵值
			timeout=0;		//清除timeout
			T1CTL = 0x0f;	//輸出PWM信號
		}
		if(S1 == 1){		//如果按S1
			if(triwave>=degree45)	//輸出Duty Cycle為1.1ms的PWM
				PWM = 1;
			else
				PWM = 0;
		}
		if(S2 == 1){
			if(triwave>=degree135)	//輸出Duty Cycle為1.9ms的PWM
				PWM = 1;
			else
				PWM = 0;
		}
		
	}
	
	
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

void KeyScan(void){
	
	unsigned char keyStatus;	//按鍵狀態
	keyStatus = S1;				//讀取S1狀態
	keyStatus = S2;				//讀取S2狀態
	if(keyStatus!=0){			//按任何鍵?
		
		defjump1 = 0;
		if(keyTemp!=keyStatus){	//與上次鍵值不同
			keyTemp = keyStatus;	//儲存未除彈跳值
			defjump2 = 1;		//開始除彈跳
		}else{
			if(defjump2<5){
				defjump2+=1;	//defjump2加1
				if(defjump2==5)	//已完全除彈跳?
					keyData = keyTemp;	//儲存已儲彈跳值
			}
		}	
	}
	defjump1+=1;
	if(defjump1==5){
		
		defjump2=0;		//重新掃描按鍵
		keyTemp = 0xff;	//清除鍵值
		keyData = 0xff;	//清除鍵值
	}
	
}

void InitTimer1(){
	
	EA = 1;				//致能總中斷
	IEN1 |= 0x02;		//致能Timer1中斷
	
	T1CTL = 0x00;			//1分頻，停止運行
	T1CTL = 0x0e;  			// 128KHz分頻，up-down mode(三角波)
	
	T1CCTL0 |= 0x04;		//開啟定時器1通道0的輸出比較模式
	
	T1CC0L = (256-100); 	//PWM duty cycle  周期
    T1CC0H = (256-100);
    
    T1CC2L = (65536-5000)/256;	//PWM signal period 占空比
    T1CC2H = (65536-5000)%256;
    

	IRCON &= ~0x02;		//為了先清除Timer1對應的中斷標誌位

}

#pragma vector = T1_VECTOR		
__interrupt void Timer1_Service(){
	T1STAT &= ~0x01;	//清除定時器1通道0中斷標誌
	if(triwave<200)
		triwave++;
	else
		triwave=0;
	
	T1CC2L = (65536-5000)/256;	//PWM signal period 占空比
    T1CC2H = (65536-5000)%256;
	
	timeout++;
	
	if(timeout>180){
		timeout = 0;
		T1CTL = 0x00;
	}
}
