#include "ioCC2530.h"

#define LED1 P1_3
#define LED2 P1_4

unsigned char DataRecieve;		//Ū���w�İϸ�ƪ��ܼ�
unsigned char Flag = 0;			//�������O�лx���ܼ�


void Init_Port();		//LED Port ��l�ƨ��
void set_main_clock();	//�]�m�D����
void Init_UART0();		//�ǦC��0����l�ƨ��
void UR0SendByte(unsigned char data);	//UR0�o�e�r�����
void UR0SendString(unsigned char *str);	//UR0�o�e�r����
void ExecuteTheOrder();					//����W������O
void Delay(unsigned int t);				//������


void main()
{
	Init_Port();	
	set_main_clock();
	Init_UART0();
    
   
    UR0SendString("1\n");
    
    
    
 
    
    
    /*
    while(1){
        if(Flag == 1)      //�O�_����W������O?
        {
            ExecuteTheOrder();    //�ѪR�ùB����O
        }
    }
    */
        
	/*
	while(1){
		UR0SendByte('A');
		Delay(60000);
	}
        */

}

void Init_UART0(){
	
	//�������޸}���~�]�\��

	PERCFG = 0x00;	//��f0���޸}�M�g���m1�A�YP0_2�B3
	P0SEL = 0x0C;	//�NP0_2�B3 Port �]�m���~�]�\��
	P2DIR &= ~0x3F;	//P0�~�]�u����USART0�̰�
	
	U0BAUD = 216;	//16MHz���t�ή�������9600BPS�j�v
	U0GCR = 12;
	
	U0UCR |= 0x80;	//�T��y���A8bit�ƾڡA�M���w�ľ�
	U0CSR |= 0x80;	//���UART�Ҧ�(7)�A�P�౵����(6)
	
	UTX0IF = 0;		//�M��TX�o�e���_�лx
	
	//UART2.c�~�[
	
	U0CSR |=0X40;			//�P��UART0 ����
	IEN0 |=0X04;			//�P��UART0 �������_
	EA=1;					//�}���`���_

}


void Init_Port(){
	
	P1SEL &= ~0x18;		//�NP1_4�B5�]�m���q��I/O
	P1DIR |= 0x18;		//�NP1_4�B5 Port �]�m����X
	LED1 = 0;
	LED2 = 0;
	
}


//�ƾڱ������_�A�Ȩ��
#pragma vector = URX0_VECTOR		
__interrupt void UR0_Recieve_Service(){
	
	URX0IF = 0;				//�M��RX�������_�лx
	DataRecieve = U0DBUF;	//�N�ƾڱq�����w�İ�Ū�X
	Flag = 1;				//�]�m�������O�лx
}


void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//�N�n�o�e��1�r�`�ƾڼg�JU0DBUF
	while(!UTX0IF);			//����TX���_�лx�A�Y�ƾڵo�e����
	UTX0IF = 0;				//����TX���_�лx�A�ǳƤU�@���o�e
	
}


void UR0SendString(unsigned char *str){
	
	while(*str != '\0'){	//�o�e�@�Ӧr��
		UR0SendByte(*str++);//�v�@�o�e�r�ꪺ�r��
	}
	
}


void ExecuteTheOrder(){
	
	Flag = 0;	//�M���������O�лx
	
	/*
	if(DataRecieveTime==1){
		Buzzer = 1
		if(Button==1){
			Buzzer = 0
			Running1()
		}
	else
		Buzzer = 0
		Running0()
	}
	*/
	
	
	
	switch(DataRecieve){
		
		case 0x31:
			LED1 = 1;
			UR0SendString("The LED1 is Open!");
		break;
		
		case 0x32:
			LED1 = 0;
			UR0SendString("The LED1 is Closed!");
		break;
		
		case 0x33:
			LED2 = 1;
			UR0SendString("The LED2 is Open!");
		break;
		
		case 0x04:
			LED2 = 0;
			UR0SendString("The LED2 is Closed!");
		break;
	}
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//���16MHZ RCOSC���t�ή�����
	while(!(CLKCONSTA & 0X40)); //���ݮ���í�w
	CLKCONCMD &=~0XF8;			//���32MHz���D����
}

void Delay(unsigned int t){
	while(t--);
}
