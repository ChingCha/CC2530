#include "ioCC2530.h"

unsigned char count = 0;
unsigned char F_time = 0;
unsigned char data[4];

void set_main_clock();	//�]�m�D����
void Init_UART0();		//�ǦC��0����l�ƨ��
void Init_Timer1();		//Timer1��l�ƨ��(0.1��w��)
void Init_ADC0();		//ADC��l�ƨ��
void Get_ADC0_Value();		//Ū��ADC�ƭ�
void UR0SendByte(unsigned char data);	//UR0�o�e�r�����
void UR0SendString(unsigned char *str,unsigned char count);	//UR0�o�e�r����


void main()
{
	
  set_main_clock();
  Init_UART0();
  Init_Timer1();
  Init_ADC0();
  
  //UR0SendString("CC2530�J��");
  
  while(1)
  {
    if(F_time == 1)      		//�w��1��ɶ���
    {
		Get_ADC0_Value();			//�i��A/D�ഫ��Ū���ƾ�
		UR0SendString(data,4);	//�V�W����o�e�ƾ�
		F_time = 0;				//�w��1��лx�M��
    }
  }
  
}

void Init_Timer1(){
	
	//�̤j�p�ƭ�(��Τ����t�ή���16MHz)
	T1CC0L = 0xd4;	//�̤j�p�ƭȧC8�줸
	T1CC0H = 0x30;	//�̤j�p�ƭȰ�8�줸
	
	T1CCTL0 |= 0x04;	//�}�ҩw�ɾ�1�q�D0����X����Ҧ�
	
	T1IE = 1;		//�P��w�ɾ�1���_�A1��w��
	T1OVFIM = 1;	//�P��w�ɾ�1���X���_�A1��w��
	EA = 1;			//�P���`���_
	
	T1CTL = 0x0e;	//���W�Y�ơG128(1110:e)�A�ҼҦ�
}




#pragma vector = T1_VECTOR	
__interrupt void Timer1_Service(){
	
	T1STAT &= ~0x01;	//�M���w�ɾ�1�q�D0���_�лx
	count++;			//�֥[�ܼ�
	if(count == 10)     //�w?1��
	{
		F_time = 1;
		count = 0;
	}
}

void Init_UART0(){
	
	//�������޸}���~�]�\��

	PERCFG = 0x00;	//��f0���޸}�M�g���m1�A�YP0_2�B3
	P0SEL = 0x0C;	//�NP0_2�B3 Port �]�m���~�]�\��
	P2DIR &= ~0x3F;	//P0�~�]�u����USART0�̰�
	
	U0BAUD = 59;	//16MHz���t�ή�������9600BPS�j�v
	U0GCR = 9;
	
	U0UCR |= 0x80;	//�T��y���A8bit�ƾڡA�M���w�ľ�
	U0CSR |= 0x80;	//���UART�Ҧ�(7)�A�P�౵����(6)
	
	UTX0IF = 0;		//�M��TX�o�e���_�лx
	
	//UART2.c�~�[
	
	U0CSR |=0X40;			//�P��UART0 ����
	IEN0 |=0X04;			//�P��UART0 �������_
	EA=1;					//�}���`���_

}



void Init_ADC0(){
	
	P0SEL |= 0x01;			//P0_0�]�m���~�]�\��
	P0DIR &= ~0x01;			//P0_0����J
	APCFG |= 0x01;			//P0_0��������I/O
	
}

void Get_ADC0_Value(){
	
	ADCIF = 0;
	
	//�Ѧҹq�����AVDD5�޸}�A256����v�AAIN0�q�D
	ADCCON3 = (0x80 | 0x10 | 0x00);
	
	while(!ADCIF);	//����A/D�ഫ����
	data[0] = 0xaf;
	data[1] = ADCH;	//Ū��ADC�ƾڧC��Ȧs��
	data[2] = ADCL;	//Ū��ADC�ƾڰ���Ȧs��
	data[3] = 0xfa;
}


void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//�N�n�o�e��1�r�`�ƾڼg�JU0DBUF
	while(!UTX0IF);			//����TX���_�лx�A�Y�ƾڵo�e����
	UTX0IF = 0;				//����TX���_�лx�A�ǳƤU�@���o�e
	
}


void UR0SendString(unsigned char *str,unsigned char count){
	
	while(count--){	//�o�e�@�Ӧr��
		UR0SendByte(*str++);//�v�@�o�e�r�ꪺ�r��
	}
	
}


void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//���16MHZ RCOSC���t�ή�����
	while(!(CLKCONSTA & 0X40)); //���ݮ���í�w
	CLKCONCMD &=~0XF8;			//���32MHz���D����
}
