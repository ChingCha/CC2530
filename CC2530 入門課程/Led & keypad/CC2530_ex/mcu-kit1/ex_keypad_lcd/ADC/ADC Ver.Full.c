#include "ioCC2530.h"

unsigned char count = 0;
unsigned char F_time = 0;
unsigned char data[4];

void set_main_clock();	//設置主時鐘
void Init_UART0();		//序列埠0的初始化函數
void Init_Timer1();		//Timer1初始化函數(0.1秒定時)
void Init_ADC0();		//ADC初始化函數
void Get_ADC0_Value();		//讀取ADC數值
void UR0SendByte(unsigned char data);	//UR0發送字元函數
void UR0SendString(unsigned char *str,unsigned char count);	//UR0發送字串函數


void main()
{
	
  set_main_clock();
  Init_UART0();
  Init_Timer1();
  Init_ADC0();
  
  //UR0SendString("CC2530入門");
  
  while(1)
  {
    if(F_time == 1)      		//定時1秒時間到
    {
		Get_ADC0_Value();			//進行A/D轉換並讀取數據
		UR0SendString(data,4);	//向上位機發送數據
		F_time = 0;				//定時1秒標誌清除
    }
  }
  
}

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




#pragma vector = T1_VECTOR	
__interrupt void Timer1_Service(){
	
	T1STAT &= ~0x01;	//清除定時器1通道0中斷標誌
	count++;			//累加變數
	if(count == 10)     //定?1秒
	{
		F_time = 1;
		count = 0;
	}
}

void Init_UART0(){
	
	//對應的引腳為外設功能

	PERCFG = 0x00;	//串口0的引腳映射到位置1，即P0_2、3
	P0SEL = 0x0C;	//將P0_2、3 Port 設置成外設功能
	P2DIR &= ~0x3F;	//P0外設優先級USART0最高
	
	U0BAUD = 59;	//16MHz的系統時鐘產生9600BPS鮑率
	U0GCR = 9;
	
	U0UCR |= 0x80;	//禁止流控，8bit數據，清除緩衝器
	U0CSR |= 0x80;	//選擇UART模式(7)，致能接收器(6)
	
	UTX0IF = 0;		//清除TX發送中斷標誌
	
	//UART2.c外加
	
	U0CSR |=0X40;			//致能UART0 接收
	IEN0 |=0X04;			//致能UART0 接收中斷
	EA=1;					//開啟總中斷

}



void Init_ADC0(){
	
	P0SEL |= 0x01;			//P0_0設置為外設功能
	P0DIR &= ~0x01;			//P0_0為輸入
	APCFG |= 0x01;			//P0_0做為模擬I/O
	
}

void Get_ADC0_Value(){
	
	ADCIF = 0;
	
	//參考電壓選擇AVDD5引腳，256抽取率，AIN0通道
	ADCCON3 = (0x80 | 0x10 | 0x00);
	
	while(!ADCIF);	//等待A/D轉換完成
	data[0] = 0xaf;
	data[1] = ADCH;	//讀取ADC數據低位暫存器
	data[2] = ADCL;	//讀取ADC數據高位暫存器
	data[3] = 0xfa;
}


void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//將要發送的1字節數據寫入U0DBUF
	while(!UTX0IF);			//等待TX中斷標誌，即數據發送完成
	UTX0IF = 0;				//等待TX中斷標誌，準備下一次發送
	
}


void UR0SendString(unsigned char *str,unsigned char count){
	
	while(count--){	//發送一個字串
		UR0SendByte(*str++);//逐一發送字串的字元
	}
	
}


void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
}
