#include "ioCC2530.h"

#define LED7 P0_7
#define LED6 P0_6
#define LED5 P0_5

//延遲函數
void Delay(unsigned int t){
	while(t--);
}

//Port初始化
void Init_Port(){
	P0SEL &= ~0xE0;		//將P0_5、6、7設置為通用I/O         
	P0DIR |= 0xE0;		//將P0_5、6、7設置為輸出           

	LED5 = 0;               
	LED6 = 0;
	LED7 = 0;
}

//主函式跑馬燈
void LED_Running(){
	LED5 = 1;
	Delay(60000);
	LED6 = 1;
	Delay(60000);
	LED5 = 0;
	Delay(60000);
	LED6 = 0;
	Delay(60000);
}

//外部中斷初始化函數
void Init_INTP(){
	IEN2 |= 0x10;	//Port1中斷致能(Port 0、1、2、3對應01、10、11)
	P1IEN |= 0x04;	//Port1_2外部中斷致能
	PICTL |= 0x02;	//PortP1_0到P1_3負緣觸發
	EA = 1;
}

//外部中斷主函數
#pragma vector = P1INT_VECTOR		//外部中斷1的向量入口
__interrupt void Init1_Service(){	//外部中斷的主函數
	LED7 = ~LED7;	//原來LED的現態(ON/OFF)要轉變為次態(OFF/ON)
	
	//先清除引腳標誌位，再清除Port標誌位

	P1IFG &= ~0x04;	//清除P1_2引腳的標誌位
	P1IF = 0;		//清除P1 Port 的標誌位
}


void main()
{
  Init_Port();	//初始化Port
  Init_INTP();	//初始化外部中斷
  while(1)
  {
    LED_Running();
  }
  
}