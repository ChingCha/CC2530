/*****馬達******/

#include "ioCC2530.h" 

 #define   LED3 P1_0
 #define   LED4 P1_1
 
void Delay(unsigned int t);
void Init_Port();
void LED_Running();
void LED_Running1();
void Init_INTP();
void PWM();
void set_main_clock();


void main()
{
   Init_Port();           // 初始化通用I/O端口
   set_main_clock();
  
   Init_INTP ();           // 初始化外部中斷
   
   
   while ( 1 )
   {
     LED_Running();      // 跑馬燈
   }
} 
 
 
 
 /* ===================延時函數= ======================== */ 
 void Delay(unsigned int t)
 {
   while (t-- );
 }
 /* = =================端口初始化函數===================== */ 
 void Init_Port()
 {

   P1SEL &= ~ 0x03 ;   
   P1DIR |= 0x03 ;   
   LED3 = 0 ;
   LED4 = 0 ;
   
 }
 /* ==================跑馬燈子函數=============== ====== */ 
 void LED_Running()
 {
   LED4 = 1 ;
   Delay( 50000 );
   LED4 = 0 ;
   Delay( 50000 );
 }
 void LED_Running1()
 {
   LED3 = 1 ;
   Delay( 60000 );
   Delay( 60000 );
   Delay( 60000 );  //7.3v 145000 delay
   LED3 = 0 ;
 }
 /* ============= ==外部中斷初始化函數================== */ 
 void Init_INTP()
 {
   IEN2 |= 0x10 ;          // 端口1中斷使能
   P1IEN |= 0x04 ;         // 端口P1_2外部中斷使能
   PICTL |= 0x02 ;         // 端口P1_0到P1_3下降沿觸發
   EA = 1 ;                // 使能總中斷
 }
 /* ================外部中斷1服務函數==================== */ 
 #pragma vector = P1INT_VECTOR      // 外部中斷1的向量入口
__interrupt void Int1_Sevice()
 {
	//T1STAT &= ~0x01;	//清除定時器1通道0中斷標誌
	//count++;			//累加變數
	PWM();
	//LED_Running1();
	
	//LED_Running1();
	/* 先清除引腳標誌位，再清除端口標誌位，否則會不斷進入中斷*/ 
	P1IFG &= ~ 0x04 ;         //軟件清除P1_2引腳的標誌位
	P1IF = 0 ;                // 軟件清除P1端口組的標誌位
}
 
void PWM()
{
 
    //Timer通道?置
    P1SEL |= 0x01;              //Timer1通道2映射至P1_0，功能選擇
    PERCFG |= 0x40;             //備用位置2
    P2SEL &= ~0x10;             //相對於Timer4，Timer1優先
    P2DIR |= 0xC0;              //定時器通道2-3具有第一優先順序
    P1DIR |= 0x01;				//P1_0為輸出
    
    //Timer模式?置
    T1CTL = 0x02;               //250KHZ不分頻，模模式
    
    //根據Table7-1，P1_0必須裝Timer1通道2進行比較
	
    T1CCTL2 = 0x1C;             //比較相等為1，計數器回0則清零
	
    //裝Timer通道0初值
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM信號週期20ms
	
	//Timer通道2比較值
    T1CC2H = 0x04;
    T1CC2L = 0xE2; 				//10ms

	
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
	
	CLKCONCMD |= 0x38;          //Timer標記輸出為250kHz
}