#include "ioCC2530.h"

#define LED5 P1_0

void set_main_clock();
void PortInit();
void T1Init();
void Delay(unsigned int t);

void main()
{


	//�U�u�@�g���}�C
    //int dutycycle[11]={0xF7,0xE1,0xC8,0xAF,0x96,0x7D,0x64,0x4B,0x32,0x19,0x0A};
	
	PortInit();

	set_main_clock();

	T1Init();
	

	//T1CC2H = 0x00;

	//T1CC2L = dutycycle[1];

	
		

}

void Delay(unsigned int t){
	while(t--);
}

void PortInit()
{
    P1SEL &= ~0x00;		//P1_0�]�m���q��I/O
    P1DIR |= 0x01; 		//P1_0�]�m����X
	LED5 = 0;			//LED��l���A
}


void T1Init()
{
    
    //Timer�q�D?�m
    P1SEL |= 0x01;              //Timer1�q�D2�M�g��P1_0�A�\����
    PERCFG |= 0x40;             //�ƥΦ�m2�A?���H��
    P2SEL &= ~0x10;             //�۹��Timer4�ATimer1�u��
    P2DIR |= 0xC0;              //�w?���q�D2-3�㦳�Ĥ@�u������
    P1DIR |= 0x01;				//P1_0����X
    
    //Timer�Ҧ�?�m
    T1CTL = 0x02;               //250KHZ�����W�A�ҼҦ�
    
    //�ھ�Table7-1�AP1_0������Timer1�q�D2�i����
	
    T1CCTL2 = 0x1C;             //����۵���1�A�p�ƾ��^0�h�M�s
	
    //��Timer�q�D0���
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM�H���g��20ms
	
	
	
	
	
	//?Timer�q�D2��?��
    T1CC2H = 0x01;
    T1CC2L = 0x77; 		//1%�����u�@�g��
    //T1CC2L = 0xE1; 	//10%�����u�@�g��
    //T1CC2L = 0xC8; 	//20%�����u�@�g��
    //T1CC2L = 0xAF; 	//30%�����u�@�g��
    //T1CC2L = 0x96; 	//40%�����u�@�g��
    //T1CC2L = 0xC4; 	//50%�����u�@�g��
    //T1CC2L = 0x64; 	//60%�����u�@�g��
    //T1CC2L = 0x4B; 	//70%�����u�@�g��
    //T1CC2L = 0x32; 	//80%�����u�@�g��
    //T1CC2L = 0x19; 	//90%�����u�@�g��
    //T1CC2L = 0x0A; 	//99%�����u�@�g��
	
    //T1CC2L = 0x01; 	//?�m�q�D2��?�H�s�����
	
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//���16MHZ RCOSC���t�ή�����
	while(!(CLKCONSTA & 0X40)); //���ݮ���í�w
	CLKCONCMD &=~0XF8;			//���32MHz���D����
	
	CLKCONCMD |= 0x38;          //Timer�аO��X��250kHz
}

