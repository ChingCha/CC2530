//�ޤJ���Y��
#include "ioCC2530.h"

//MAX7219�Ȧs�������w�q

#define DIGIT0		 0x01	//DIGIT0�Ȧs��
#define DECODE_MODE  0x09   //�ѽX����Ȧs��
#define INTENSITY    0x0A   //�G�ױ���Ȧs��
#define SCAN_LIMIT   0x0B   //���y�ɭ��Ȧs��
#define SHUT_DOWN    0x0C   //���_�Ҧ��Ȧs��
#define DISPLAY_TEST 0x0F   //���ձ���Ȧs��



//CC2530�}��\�२���w�q

#define MAX7219DIN    P0_4		//CC2530 P0_4>>>�Ҳ�DIN�}��
#define MAX7219CS     P0_5		//CC2530 P0_5>>>�Ҳ�CS(LOAD)�}��
#define MAX7219CLK    P0_6		//CC2530 P0_6>>>�Ҳ�CLK�}��

//��ƫŧi
void Write7219(unsigned char address,unsigned char dat);
void MAX7219_Init(void);
void delay(unsigned int t);
static void MAX7219_SendByte (unsigned char dataout);
static void MAX7219_Write (unsigned char reg_number, unsigned char dataout);

int main(){
	
    MAX7219_Init();               //MAX7219��l��
    MAX7219_Write(DIGIT0,0x40);      //�ƽX�����1~8
	delay(6000);
	return 0;

}


//CC2530 Port & MAX7219��l�ƨ�ơA�ó]�mMAX7219����������Ȧs��
void MAX7219_Init(){
	
	P0SEL &= ~0x70;						//��P0_4�B5�B6�]�m���q��I/O Port�\��
	P1DIR |= 0x70;						//��P0_4�B5�B6 Prot�ǿ��V�]�m����X
	
	Write7219(SHUT_DOWN,0x01);         //�}�ҥ��`�u�@�Ҧ��]0xX1�^
    Write7219(DISPLAY_TEST,0x00);      //��ܤu�@�Ҧ��]0xX0�^
    Write7219(DECODE_MODE,0x00);       //No decode
    Write7219(SCAN_LIMIT,0x07);        //8�uLED����
    Write7219(INTENSITY,0x04);         //�]�m��l�G��   
	
}


//��}�B��Ƶo�e�Ƶ{��
void Write7219(unsigned char address,unsigned char dat)
{   
    unsigned char i;
    MAX7219CS=0;    //�ԧC����u�A�襤�Ȧs��
	
    //�o�e�a�}
    for (i=0;i<8;i++)        //����j��8��(�e�K�줸D15~8)           
    {   
       MAX7219CLK=0;        //�M�s�����׬y��
       MAX7219DIN=address&0x80; //�C�������줸��      
       address<<=1;             //�����@��
       MAX7219CLK=1;        //�����W�ɪu�A�o�e��}
    }
	
    //�o�e���
    for (i=0;i<8;i++)   	//����j��8��(��K�줸D7~0)             
    {   
       MAX7219CLK=0;
       MAX7219DIN=dat&0x80;     
       dat<<=1;  
       MAX7219CLK=1;        //�����W�ɪu�A�o�e���
    }
    MAX7219CS=1;    //�o�e�����A�W�ɪu��s���                       
}

void delay(unsigned int t)
{
  while(t--);
}

static void MAX7219_SendByte (unsigned char dataout)
{
  char i;
  for (i=8; i>0; i--) {
    unsigned char mask = 1 << (i - 1);                // calculate bitmask
    MAX7219CLK=0;                                          // bring CLK low
    if (dataout & mask)                               // output one data bit
      MAX7219DIN=1;                                       //  "1"
    else                                              //  or
      MAX7219DIN=0;                                       //  "0"
    MAX7219CLK=1;                                          // bring CLK high
	}
}

static void MAX7219_Write (unsigned char reg_number, unsigned char dataout)
{
  MAX7219CS=1;                                           // take LOAD high to begin
  MAX7219_SendByte(reg_number);                       // write register number to MAX7219
  MAX7219_SendByte(dataout);                          // write data to MAX7219
  MAX7219CS=0;                                           // take LOAD low to latch in data
  MAX7219CS=1;                                           // take LOAD high to end
}