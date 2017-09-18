/*********************************************************************

上面就是簡單的3個按鈕,
1個按下去會讓SERVO置中 , 送PWM:1.5ms
1個按下去會讓SERVO的目前PWM減小0.1ms 模擬往左轉, 最小到0.5ms就不動了
1個按下去會讓SERVO的目前PWM增加0.1ms 模擬往右轉, 最大到2.5ms就不動了


SERVO的電流和版子的電流分開供應
第一次開機要先按置中的按鈕之後才能按其他2顆按鈕

**********************************************************************/
#include <regx51.h>
unsigned int dutytime=45536; //65536-45536就是責任週期
unsigned int ton=10000; //高電位比例=50%
unsigned int toff=10000; //低電位比例=50%
unsigned int temp; //給計時器工作用
unsigned int presscount; //按下計時用
void delay(unsigned int b)
{
	unsigned int x;
	for(x=0;x<b;x++);
}
void timer0_initialize(void)  //初始化計時器0
{
    EA=0; //關閉中斷功能(所有中斷副程式失效)
    IE|=0x02; //開啟計時器中斷功能
    TMOD|=0x01; //設定計時器模式
    temp=65536-dutytime; //設定中斷一次的時間(預設是dutytime)
    TH0=temp/256; //填入高八位
    TL0=temp%256; //填入低八位
    TR0=1; //啟動計時器
    EA=1; //開啟中斷功能(中斷副程式可以執行)
}
void timer0_isr(void) interrupt TF0_VECTOR using 1 //使用計時器中斷副程式產生PWM
{
    toff=20000-ton;
	if(P2_0==1)
    {
    TR0=0;
    temp=65536-toff;
    TH0=temp/256;
    TL0=temp%256;
    TR0=1;
    P2_0=0;
    }
    else
    {
    TR0=0;
    temp=65536-ton;
    TH0=temp/256;
    TL0=temp%256;
    TR0=1;
    P2_0=1;
    }
}
void main(void) //主程式開始
{
    timer0_initialize(); //呼叫計時器初始化副程式
    //主程式中可直接改變ton或toff即可改變高電位跟低電位佔的比例
    while(1)
	{
		if(P1_0==0)
		{
			while(P1_0==0)	 //按下不動作,放開才動作
			{
				if(presscount<30000)presscount++;  //按住一段時間後開始每0.5秒轉0.1ms直到2.5ms
				if(presscount==30000&&ton<2500) 
				{
					ton=ton+100; 
					delay(20000);
				}
			}
			if(ton<2500)ton=ton+100;
			presscount=0;
		}
		if(P1_1==0)ton=1500;  		//按一次轉回中間1.5ms
		if(P1_2==0)
		{							  
			while(P1_2==0)	 //按下不動作,放開才動作
			{
				if(presscount<30000)presscount++;  //按住一段時間後開始每0.5秒轉0.1ms直到2.5ms
				if(presscount==30000&&ton>500) 
				{
					ton=ton-100; 
					delay(20000);
				}
			}
			if(ton>500)ton=ton-100;
			presscount=0;
		}
	}
}