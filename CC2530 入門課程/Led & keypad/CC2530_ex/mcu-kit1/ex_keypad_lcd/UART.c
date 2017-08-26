#include "ioCC2530.h"
#include "string.h"

#define LED1 P1_4
#define LED2 P1_5

#define uint unsigned int

unsigned char DataRecieve;		//讀取緩衝區資料的變數
unsigned char Flag = 0;			//接收指令標誌的變數

//延遲函數
void Delay(unsigned int t)
{
	while (t-- );
}

//序列埠0的初始化函數
void Init_UART0(){
	
	//設置主時鐘
	CLKCONCMD |= 0X40;			//系統時鐘源：16MHz
	while(CLKCONSTA & 0X40);	//等待時鐘穩定
	CLKCONCMD &= ~0x47;	 		//主時鐘頻率：32MHz
	
	//對應的引腳為外設功能
	PERCFG = 0x00;	//串口0的引腳映射到位置1，即P0_2、3
	P0SEL = 0x0C;	//將P0_2、3 Port 設置成外設功能
	P2DIR &= 0x3F;	//P0外設優先級USART0最高
	
	U0BAUD = 59;	//16MHz的系統時鐘產生9600BPS鮑率
	U0GCR = 9;
	
	U0UCR |= 0x80;	//禁止流控，8bit數據，清除緩衝器
	U0CSR |= 0x80;	//選擇UART模式(7)，致能接收器(6)
	
	UTX0IF = 0;		//清除TX發送中斷標誌
	//URX0IF = 0;		//清除RX接收中斷標誌
	//URX0IE = 1;		//致能URAT0的接收中斷
	EA = 1;			//致能總中斷

}

//LED Port 初始化函數
void Init_Port(){
	
	P1SEL &= ~0x30;		//將P1_4、5設置為通用I/O
	P1DIR |= 0x30;		//將P1_4、5 Port 設置為輸出
	LED1 = 1;
	LED2 = 1;
}

//串口0發送字串
void Uart_Send_string(char *data,int len)
{
	int j;
	for(j=0;j<len;j++)
	{
		U0DBUF=*data++;
		while(UTX0IF==0);
		UTX0IF=0;
	}
}

char Txdata[25] = "Start Transmit:\n";


/*
//數據接收中斷服務函數
#pragma vector = URX0_VECTOR		
__interrupt void UR0_Recieve_Service(){
	
	URX0IF = 0;				//清除RX接收中斷標誌
	DataRecieve = U0DBUF;	//將數據從接收緩衝區讀出
	Flag = 1;				//設置接收指令標誌
}
*/

/*
//UR0發送字元函數
void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//將要發送的1字節數據寫入U0DBUF
	while(!UTX0IF);			//等待TX中斷標誌，即數據發送完成
	UTX0IF = 0;				//等待TX中斷標誌，準備下一次發送
	
}
*/

/*
//UR0發送字串函數
void UR0SendString(unsigned char *str){
	
	while(*str != '\0'){	//發送一個字串
		UR0SendByte(*str++);//逐一發送字串的字元
	}
	
}
*/

/*
//執行上位機指令
void ExecuteTheOrder(){
	
	Flag = 0;	//清除接收指令標誌
	switch(DataRecieve){
		
		case 0xa1:
			LED1 = 1;
			UR0SendString("The LED1 is Open!\r\n");
		break;
		
		case 0xa2:
			LED1 = 0;
			UR0SendString("The LED1 is Closed!\r\n");
		break;
		
		case 0xb1:
			LED2 = 1;
			UR0SendString("The LED2 is Open!\r\n");
		break;
		
		case 0xb2:
			LED2 = 0;
			UR0SendString("The LED2 is Closed!\r\n");
		break;
	}
}
*/

void main()
{
  Init_Port();		//初始化Port
  Init_UART0();		//序列埠0的初始化函數
  
  Uart_Send_string(Txdata,25);
  
  //???
  for(int i=0;i<30;i++)
	Txdata[i]=' ';
  strcpy(txdata,"hello,cc2530\n");
  
  while(1){
	uarttx_send_string(txdata,sizeof("hello,cc2530\n"));
 	Delay(60000);
	LED1=!LED1;
	Delay(60000);
	Delay(60000);
  }
  
}