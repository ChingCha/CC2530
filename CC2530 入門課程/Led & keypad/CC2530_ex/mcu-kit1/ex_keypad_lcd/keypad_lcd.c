#include "ioCC2530.h"

#define PWM P1_0

unsigned int dutytime=45536; //65536-45536就是責任週期
unsigned int ton=10000; //高電位比例=50%
unsigned int toff=10000; //低電位比例=50%
unsigned int temp; //給計時器工作用

void init_port(void);
void init_timer(void);
void start_pwm(void);

void main(){
	
	start_pwm();
} 


/*使用P1_0口??出、外?端口，??出PWM波形*/
void init_port(void)
{
    P1SEL |= 0x01;              //Timer1通道2映射至P1_0，功能選擇
    PERCFG |= 0x40;             //備用位置2，?明信息
    P2SEL &= ~0x10;             //相對於Timer4，Timer1優先
    P2DIR |= 0xC0;              //定?器通道2-3具有第一優先順序
    P1DIR |= 0x01;				//P1_0為輸出
    return ;
}

/*
    ?基准值放入T1CC0 寄存器, ?被比?值放入T1CC2寄存器
    ?T1CC2中的值与T1CC0中的值相等?，?T1CC2 ?置or清除
*/

void init_timer(void)
{
	EA = 0;

    //根據Table7-1，P1_0必須裝Timer1通道2進行比較
	
	temp=65536-dutytime;
	
    //裝Timer通道0初值
    T1CC0H = temp/256;
    T1CC0L = temp%256;              //PWM信號週期20ms
	T1CTL = 0x02;               //250KHZ不分頻，模模式

    return ;
}

void start_pwm(void) 
{
    init_port();
    init_timer();
    IEN1 |=0x02;     //Timer 1 中?使能
    EA = 1;            //全局中?使能
	while(1) {;}
    return ;
}

#if 0
/*irq function*/
#pragma vector=T1_VECTOR
//__interrupt void T1_IRQ(void)
volatile unsigned char count = 0;
__interrupt void _irq_timer1(void)
{
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

#endif /*_irq_timer1*/