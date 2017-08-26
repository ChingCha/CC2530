#include "ioCC2530.h"
#include "string.h"

#define LED1 P1_3
#define LED2 P1_4

unsigned char dataRecv;
unsigned char Flag = 0;
/*===================UR0��l�ƨ�?====================*/
void Init_Uart0()
{
  

	PERCFG = 0x00;    //��f0����?�M�g���m1�A�YP0_2�MP0_3
						//�~�]����Ȧs��USART0��I/O��m0�G��m1�G��m2
	P0SEL = 0x0C;     //?P0_2�MP0_3�ݤf?�m���~?�\��
	
	
	U0BAUD = 59;      //16MHz���t????��9600BPS���i�S�v
	U0GCR = 9;
	U0UCR |= 0x80;    //�T��y���A8��?�u�A�M��??��
	U0CSR |= 0xC0;    //??UART�Ҧ��A�P�౵����
	
	UTX0IF = 0;       //�M��TX?�e��??��
	URX0IF = 0;       //�M��RX������??��
	URX0IE = 1;       //�ϯ�URAT0��������?
	EA = 1;           //�ϯ�?��?
}
/*================UR0������?�A?��?================*/
#pragma vector = URX0_VECTOR
__interrupt void UR0_RecvInt()
{
  URX0IF = 0;           //�M��RX������??��
  dataRecv =  U0DBUF;   //??�u?����????�X
  Flag = 1;             //?�m�������O?��
}

/*=================UR0?�e?�r?��?=================*/
void UR0SendByte(unsigned char dat)
{
  U0DBUF = dat;         //?�n?�e��1�r??�u?�JU0DBUF
  while(!UTX0IF);       //����TX��??�ӡA�Y?�u?�e����
  UTX0IF = 0;           //�M��TX��??�ӡA��?�U�@��?�e
}
/*=================UR0?�e�r�Ŧ��?===============*/
void UR0SendString(unsigned char *str)
{
  while(*str != '\0')       //?�e�@?�r�Ŧ�
  {
    UR0SendByte(*str++);    //�v??�e�r�Ŧꤤ���r?
  }
}
/*================?��W���󪺫��O=================*/
void ExecuteTheOrder()
{
  Flag = 0 ;            //�M���������O?��
  switch(dataRecv)
  {
    case 0x01:
      LED1 = 1;
      UR0SendString("The LED1 is Open!\r\n");
    break;
    case 0x02:
      LED1 = 0;
      UR0SendString("The LED1 is Closed!\r\n");
    break;
    case 0x03:
      LED2 = 1;
      UR0SendString("The LED2 is Open!\r\n");
    break;
    case 0x04:
      LED2 = 0;
      UR0SendString("The LED2 is Closed!\r\n");
    break;
  }
}
/*=================�ݤf��l�ƨ�?====================*/
void Init_Port()
{
	P1SEL &= ~0x18;       //?P1_3�MP1_4?�m?�q��I/O�ݤf�\��
	P1DIR |= 0x18;        //?P1_3�MP1_4���ݤf?�m??�X
	LED1 = 0;             //??LED5?
	LED2 = 0; 
} 
/*===================�D��?=========================*/
void main()
{
  Init_Port();         //��l�ƺݤf
  Init_Uart0();        //��l�Ʀ�f0

  UR0SendByte('A');

  while(1)
  {
    if(Flag == 1)      //�d?�O�_����W������O
    {
      ExecuteTheOrder();    //�ѪR�}?����O
    }
  }
}