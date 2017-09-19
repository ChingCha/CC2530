#include <ioCC2530.h>

/*�ϥ�P1_0�f??�X�B�~?�ݤf�A??�XPWM�i��*/
void init_port(void)
{
    P1DIR |= 0x01;    // p1_0 output
    P1SEL |= 0x01;    // p1_0  peripheral
    P2SEL &= 0xEE;    // Give priority to Timer 1
    PERCFG |= 0x40; // set timer_1 I/O��m?2
    return ;
}

/*
    ?���ȩ�JT1CC0 �H�s��, ?�Q��?�ȩ�JT1CC2�H�s��
    ?T1CC2�������OT1CC0�����Ȭ۵�?�A?T1CC2 ?�mor�M��
*/

void init_timer(void)
{
    T1CC0L = 0xFA;   //PWM duty cycle  �P��(LED�{�{�g��)1KHz
    T1CC0H = 0x00;
    
    T1CC2L = 0x4B;  //     PWM signal period �e�Ť�()
    T1CC2H = 0x00;
    
    T1CCTL2 = 0x34;    // ���_T1CC0����?��?�ԡA?�X��?�� 1�F ���_T1CC2����?��?�ԡA?�X�C?�� 0  �A��?��?�e�Ť�N?50%�F
    T1CTL |= 0x0f; // divide with 128 and to do i up-down mode
    return ;
}

void start_pwm(void) 
{
    init_port();
    init_timer();
//    IEN1 |=0x02;     //Timer 1 ��?�ϯ�
//    EA = 1;            //������?�ϯ�
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