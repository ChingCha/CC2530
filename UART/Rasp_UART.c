#include "ioCC2530.h"

#define LED1 P1_3
#define LED2 P1_4

unsigned char DataRecieve;		//讀取緩衝區資料的變數
unsigned char Flag = 0;			//接收指令標誌的變數


void Init_Port();		//LED Port 初始化函數
void set_main_clock();	//設置主時鐘
void Init_UART0();		//序列埠0的初始化函數
void UR0SendByte(unsigned char data);	//UR0發送字元函數
void UR0SendString(unsigned char *str);	//UR0發送字串函數
void ExecuteTheOrder();					//執行上位機指令
void Delay(unsigned int t);				//延遲函數


void main()
{
	Init_Port();	
	set_main_clock();
	Init_UART0();
    
   
    UR0SendString("1\n");
    
    
    
 
    
    
    /*
    while(1){
        if(Flag == 1)      //是否收到上位機指令?
        {
            ExecuteTheOrder();    //解析並運行指令
        }
    }
    */
        
	/*
	while(1){
		UR0SendByte('A');
		Delay(60000);
	}
        */

}

void Init_UART0(){
	
	//對應的引腳為外設功能

	PERCFG = 0x00;	//串口0的引腳映射到位置1，即P0_2、3
	P0SEL = 0x0C;	//將P0_2、3 Port 設置成外設功能
	P2DIR &= ~0x3F;	//P0外設優先級USART0最高
	
	U0BAUD = 216;	//16MHz的系統時鐘產生9600BPS鮑率
	U0GCR = 12;
	
	U0UCR |= 0x80;	//禁止流控，8bit數據，清除緩衝器
	U0CSR |= 0x80;	//選擇UART模式(7)，致能接收器(6)
	
	UTX0IF = 0;		//清除TX發送中斷標誌
	
	//UART2.c外加
	
	U0CSR |=0X40;			//致能UART0 接收
	IEN0 |=0X04;			//致能UART0 接收中斷
	EA=1;					//開啟總中斷

}


void Init_Port(){
	
	P1SEL &= ~0x18;		//將P1_4、5設置為通用I/O
	P1DIR |= 0x18;		//將P1_4、5 Port 設置為輸出
	LED1 = 0;
	LED2 = 0;
	
}


//數據接收中斷服務函數
#pragma vector = URX0_VECTOR		
__interrupt void UR0_Recieve_Service(){
	
	URX0IF = 0;				//清除RX接收中斷標誌
	DataRecieve = U0DBUF;	//將數據從接收緩衝區讀出
	Flag = 1;				//設置接收指令標誌
}


void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//將要發送的1字節數據寫入U0DBUF
	while(!UTX0IF);			//等待TX中斷標誌，即數據發送完成
	UTX0IF = 0;				//等待TX中斷標誌，準備下一次發送
	
}


void UR0SendString(unsigned char *str){
	
	while(*str != '\0'){	//發送一個字串
		UR0SendByte(*str++);//逐一發送字串的字元
	}
	
}


void ExecuteTheOrder(){
	
	Flag = 0;	//清除接收指令標誌
	
	/*
	if(DataRecieveTime==1){
		Buzzer = 1
		if(Button==1){
			Buzzer = 0
			Running1()
		}
	else
		Buzzer = 0
		Running0()
	}
	*/
	
	
	
	switch(DataRecieve){
		
		case 0x31:
			LED1 = 1;
			UR0SendString("The LED1 is Open!");
		break;
		
		case 0x32:
			LED1 = 0;
			UR0SendString("The LED1 is Closed!");
		break;
		
		case 0x33:
			LED2 = 1;
			UR0SendString("The LED2 is Open!");
		break;
		
		case 0x04:
			LED2 = 0;
			UR0SendString("The LED2 is Closed!");
		break;
	}
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
}

void Delay(unsigned int t){
	while(t--);
}
