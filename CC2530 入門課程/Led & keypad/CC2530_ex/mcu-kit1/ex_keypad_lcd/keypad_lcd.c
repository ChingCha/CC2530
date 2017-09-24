#include "ioCC2530.h"

#define PWM P1_0
#define S1	P0_3
#define S2	P0_4

unsigned int dutytime=45536; //65536-45536�N�O�d���g��
unsigned int ton=10000; //���q����=50%
unsigned int toff=10000; //�C�q����=50%
unsigned int temp; //���p�ɾ��u�@��

void Init_Timer1();
void InitPort();

void main(){
	
	InitPort();
	Init_Timer1();
	
	while(1)
	{
		if(S1==0)ton=2200;  //2.2ms ���� 
		if(S2==0)ton=1500;  //1.5ms ����
		toff=20000-ton;
	}
	
	
}


void Init_Timer1(){
	
	EA = 0;			//�`�P��OFF
	IEN1 |=0x02;	//Timer1���_�P��
	temp=65536-dutytime; //�]�w���_�@�����ɶ�(�w�]�Odutytime)
	T1CC2H = temp/256;
    T1CC2L = temp%256;
	T1CTL |= 0x0F;	//�}�ҭp�ƾ��G128���W�B�W�ƤU�ƼҦ�
	EA = 1;
}

void InitPort(){
	
	PERCFG |= 0x40; 	// set timer_1 I/O��m?2
	//P0_3�B4�]�m���q��I/O & ��J
	P0SEL &= ~0x18;
	P0DIR &= ~0x18;
	//P1_0�]�m���q��I/O & ��X
	P1SEL &= ~0x01;		//P1_0�]�m���q��I/O
    P1DIR |= 0x01; 		//P1_0�]�m����X
	
} 


#pragma vector = T1_VECTOR		
__interrupt void Timer1_Service(){
	if(PWM==1)
    {
    T1CTL=0x00;
    temp=65536-toff;
    T1CC2H=temp/256;
    T1CC2L=temp%256;
    T1CTL=0x0F;
    PWM=0;
    }
    else
    {
    T1CTL=0x00;
    temp=65536-ton;
    T1CC2H=temp/256;
    T1CC2L=temp%256;
    T1CTL=0x0F;
    PWM=1;
    }
}