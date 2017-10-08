#include "ioCC2530.h"

#define PWM P1_0

unsigned int dutytime=45536; //65536-45536�N�O�d���g��
unsigned int ton=10000; //���q����=50%
unsigned int toff=10000; //�C�q����=50%
unsigned int temp; //���p�ɾ��u�@��

void init_port(void);
void init_timer(void);
void start_pwm(void);

void main(){
	
	start_pwm();
} 


/*�ϥ�P1_0�f??�X�B�~?�ݤf�A??�XPWM�i��*/
void init_port(void)
{
    P1SEL |= 0x01;              //Timer1�q�D2�M�g��P1_0�A�\����
    PERCFG |= 0x40;             //�ƥΦ�m2�A?���H��
    P2SEL &= ~0x10;             //�۹��Timer4�ATimer1�u��
    P2DIR |= 0xC0;              //�w?���q�D2-3�㦳�Ĥ@�u������
    P1DIR |= 0x01;				//P1_0����X
    return ;
}

/*
    ?���ȩ�JT1CC0 �H�s��, ?�Q��?�ȩ�JT1CC2�H�s��
    ?T1CC2�������OT1CC0�����Ȭ۵�?�A?T1CC2 ?�mor�M��
*/

void init_timer(void)
{
	EA = 0;

    //�ھ�Table7-1�AP1_0������Timer1�q�D2�i����
	
	temp=65536-dutytime;
	
    //��Timer�q�D0���
    T1CC0H = temp/256;
    T1CC0L = temp%256;              //PWM�H���g��20ms
	T1CTL = 0x02;               //250KHZ�����W�A�ҼҦ�

    return ;
}

void start_pwm(void) 
{
    init_port();
    init_timer();
    IEN1 |=0x02;     //Timer 1 ��?�ϯ�
    EA = 1;            //������?�ϯ�
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
		
		IEN1 |=0x00;	//����Timer1���_
		temp=65536-toff;
		T1CC2H=temp/256;
		T1CC2L=temp%256;
		IEN1 |=0x02;	//�}��Timer1���_
		
    }else{
		
		IEN1 |=0x00;	//����Timer1���_
		temp=65536-ton;
		T1CC2H=temp/256;
		T1CC2H=temp%256;
		IEN1 |=0x02;	//�}��Timer1���_
		PWM=1;
    }
	
}

#endif /*_irq_timer1*/