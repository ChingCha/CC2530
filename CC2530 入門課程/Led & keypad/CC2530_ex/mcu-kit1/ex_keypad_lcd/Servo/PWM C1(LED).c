#include "ioCC2530.h"

void init_port(void);
void init_timer(void);
void start_pwm(void);

void main(){
	
	start_pwm();
} 


/*使用P1_0口为输出、外设端口，来输出PWM波形*/
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
    将基准值放入T1CC0 寄存器, 将被比较值放入T1CC2寄存器
    当T1CC2中的值与T1CC0中的值相等时，则T1CC2 设置or清除
*/

void init_timer(void)
{
    T1CTL = 0x02;               //250KHZ不分頻，模模式
    
    //根據Table7-1，P1_0必須裝Timer1通道2進行比較
	
    T1CCTL2 = 0x1C;             //比較相等為1，計數器回0則清零
	
    //裝Timer通道0初值
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM信號週期20ms
	
	
	
	
	
	//?Timer通道2比?值
    T1CC2H = 0x01;
    T1CC2L = 0x77; 		//1%的正工作週期
    return ;
}

void start_pwm(void) 
{
    init_port();
    init_timer();
//    IEN1 |=0x02;     //Timer 1 中断使能
//    EA = 1;            //全局中断使能
//    while(1) {;}
    return ;
}

#if 0
/*irq function*/
#pragma vector=T1_VECTOR
//__interrupt void T1_IRQ(void)
volatile unsigned char count = 0;
__interrupt void _irq_timer1(void)
{
    //TODO....
}

#endif /*_irq_timer1*/