//�ޤJ���Y��
#include "ioCC2530.h"

//MAX7219�Ȧs�������w�q

#define DECODE_MODE  0x09   //�ѽX����Ȧs��
#define INTENSITY    0x0A   //�G�ױ���Ȧs��
#define SCAN_LIMIT   0x0B   //���y�ɭ��Ȧs��
#define SHUT_DOWN    0x0C   //���_�Ҧ��Ȧs��
#define DISPLAY_TEST 0x0F   //���ձ���Ȧs�� 

#define INTENSITY_MIN     0x00   // �̤p��ܫG��
#define INTENSITY_MAX     0x0F   // �̤j��ܫG��

//CC2530�}��\�२���w�q

#define MAX7219DIN    P0_4		//CC2530 P0_4>>>�Ҳ�DIN�}��
#define MAX7219LOAD     P0_5		//CC2530 P0_5>>>�Ҳ�CS(LOAD)�}��
#define MAX7219CLK    P0_6		//CC2530 P0_6>>>�Ҳ�CLK�}��

unsigned char value[1]={0x80};

//��ƫŧi
void MAX7219_Init(void);
void MAX7219_SendByte (unsigned char dataout);
void MAX7219_Write (unsigned char reg_number, unsigned char dataout);

//CC2530 Port & MAX7219��l�ƨ�ơA�ó]�mMAX7219����������Ȧs��
void MAX7219_Init(){
	
	P0SEL &= ~0x70;	//��P0_4�B5�B6�]�m���q��I/O Port�\��
	P1DIR |= 0x70;	//��P0_4�B5�B6 Prot�ǿ��V�]�m����X
	
	MAX7219_Write(SHUT_DOWN,0x01);         //�}�ҥ��`�u�@�Ҧ��]0xX1�^
    MAX7219_Write(DISPLAY_TEST,0x00);      //��ܤu�@�Ҧ��]0xX0�^
    MAX7219_Write(DECODE_MODE,0xff);       //��Υ��ѽX�Ҧ�
    MAX7219_Write(SCAN_LIMIT,0x07);        //8�uLED����
    MAX7219_Write(INTENSITY,0x04);          //�]�m��l�G��   
	
}

int main(){
	
	MAX7219_Init();
	MAX7219_SendByte(value[1]);
	
	return 0;
}




/*
*********************************************************************************************************
* MAX7219_SendByte()
*
* Description: Send one byte to the MAX7219
* Arguments  : dataout = data to send
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_SendByte (unsigned char dataout)
{
  char i;
  for (i=8; i>0; i--) {
    unsigned char mask = 1 << (i - 1);                // calculate bitmask
    MAX7219CLK=0;                                     // bring CLK low
    if (dataout & mask)                               // output one data bit
      MAX7219DIN=1;                                   //  "1"
    else                                              //  or
      MAX7219DIN=0;                                       //  "0"
    MAX7219CLK=1;                                          // bring CLK high
	}
}

/*
*********************************************************************************************************
* MAX7219_Write()
*
* Description: Write to MAX7219
* Arguments  : reg_number = register to write to
*              dataout = data to write to MAX7219
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_Write (unsigned char reg_number, unsigned char dataout)
{
  MAX7219LOAD=1;                                           // take LOAD high to begin
  MAX7219_SendByte(reg_number);                       // write register number to MAX7219
  MAX7219_SendByte(dataout);                          // write data to MAX7219
  MAX7219LOAD=0;                                           // take LOAD low to latch in data
  MAX7219LOAD=1;                                           // take LOAD high to end
}

