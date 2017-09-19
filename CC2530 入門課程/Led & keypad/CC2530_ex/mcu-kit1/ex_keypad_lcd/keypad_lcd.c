#include <ioCC2530.h>

/*使用P1_0口??出、外?端口，??出PWM波形*/
void init_port(void)
{
    P1DIR |= 0x01;    // p1_0 output
    P1SEL |= 0x01;    // p1_0  peripheral
    P2SEL &= 0xEE;    // Give priority to Timer 1
    PERCFG |= 0x40; // set timer_1 I/O位置?2
    return ;
}

/*
    ?基准值放入T1CC0 寄存器, ?被比?值放入T1CC2寄存器
    ?T1CC2中的值与T1CC0中的值相等?，?T1CC2 ?置or清除
*/

void init_timer(void)
{
    T1CC0L = 0xFA;   //PWM duty cycle  周期(LED閃爍週期)1KHz
    T1CC0H = 0x00;
    
    T1CC2L = 0x4B;  //     PWM signal period 占空比()
    T1CC2H = 0x00;
    
    T1CCTL2 = 0x34;    // 等于T1CC0中的?值?候，?出高?平 1； 等于T1CC2中的?值?候，?出低?平 0  ，其?整?占空比就?50%了
    T1CTL |= 0x0f; // divide with 128 and to do i up-down mode
    return ;
}

void start_pwm(void) 
{
    init_port();
    init_timer();
//    IEN1 |=0x02;     //Timer 1 中?使能
//    EA = 1;            //全局中?使能
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


void main(){
	start_pwm();
}