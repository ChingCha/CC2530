//�ޤJ���Y��
#include "ioCC2530.h"

//MAX7219�Ȧs�������w�q

#define DIGIT0		 0x01	//DIGIT0�Ȧs��
#define REG_DECODE        0x09                        // "decode mode" register
#define REG_INTENSITY     0x0a                        // "intensity" register
#define REG_SCAN_LIMIT    0x0b                        // "scan limit" register
#define REG_SHUTDOWN      0x0c                        // "shutdown" register
#define REG_DISPLAY_TEST  0x0f                        // "display test" register

#define INTENSITY_MIN     0x00                        // minimum display intensity
#define INTENSITY_MAX     0x0f                        // maximum display intensity

//CC2530�}��\�२���w�q

#define MAX7219DIN    P0_4		//CC2530 P0_4>>>�Ҳ�DIN�}��
#define MAX7219LOAD   P0_5		//CC2530 P0_5>>>�Ҳ�CS(LOAD)�}��
#define MAX7219CLK    P0_6		//CC2530 P0_6>>>�Ҳ�CLK�}��

//��ƫŧi
static void MAX7219_SendByte (unsigned char DINout);
static void MAX7219_Write (unsigned char reg_number, unsigned char DINout);
void MAX7219_Init(void);
void MAX7219_DisplayTestStart (void);
void MAX7219_ShutdownStop (void);
void MAX7219_DisplayTestStop (void);
void MAX7219_Clear (void);
void MAX7219_SetBrightness (char brightness);

//������
void Delay(unsigned int t)
{
  while(t--);
}

//CC2530 Port & MAX7219��l�ƨ�ơA�ó]�mMAX7219����������Ȧs��
void MAX7219_Init(){
	
	P0SEL &= ~0x70;	//��P0_4�B5�B6�]�m���q��I/O Port�\��
	P0DIR |= 0x70;	//��P0_4�B5�B6 Prot�ǿ��V�]�m����X
	
	MAX7219_Write(REG_DECODE, 0x00);          	// set to "no decode" for all digits
	MAX7219_Write(REG_SCAN_LIMIT, 8);      	// set up to scan all eight digits                 
	MAX7219_ShutdownStop(); 
	MAX7219_DisplayTestStop(); 
	MAX7219_Clear(); 
	MAX7219_SetBrightness(0x06); 
}

int main(){
	
	MAX7219_Init();
	MAX7219_Write(DIGIT0,0x04);
	Delay(60000);
	
	return 0;
}

/*
*********************************************************************************************************
* MAX7219_SendByte()
*
* Description: Send one byte to the MAX7219
* Arguments  : DINout = DIN to send
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_SendByte (unsigned char DINout)
{
  char i;
  for (i=8; i>0; i--) {
    unsigned char mask = 1 << (i - 1);                // calculate bitmask
	MAX7219CLK=0;                                     
    if (DINout & mask)                               // output one DIN bit
	  MAX7219DIN=1;                                   
    else                                              
	  MAX7219DIN=0;										  // bring CLK high
    MAX7219CLK=1;                                          
	}
}

/*
*********************************************************************************************************
* MAX7219_Write()
*
* Description: Write to MAX7219
* Arguments  : reg_number = register to write to
*              DINout = DIN to write to MAX7219
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_Write (unsigned char reg_number, unsigned char DINout)
{
  MAX7219LOAD=1;                                           // take LOAD high to begin
  MAX7219_SendByte(reg_number);                       // write register number to MAX7219
  MAX7219_SendByte(DINout);                          // write DIN to MAX7219
  MAX7219LOAD=0;                                           // take LOAD low to latch in DIN
  MAX7219LOAD=1;                                           // take LOAD high to end
}

/*
*********************************************************************************************************
* MAX7219_DisplayTestStart()
*
* Description: Start a display test.
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/


void MAX7219_DisplayTestStart (void)
{
  MAX7219_Write(REG_DISPLAY_TEST, 1);                 // put MAX7219 into "display test" mode
}
/*
*********************************************************************************************************
* MAX7219_ShutdownStop()
*
* Description: Take the display out of shutdown mode.
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_ShutdownStop (void)
{
  MAX7219_Write(REG_SHUTDOWN, 1);                     // put MAX7219 into "normal" mode
}
/*
*********************************************************************************************************
* MAX7219_DisplayTestStop()
*
* Description: Stop a display test.
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_DisplayTestStop (void)
{
  MAX7219_Write(REG_DISPLAY_TEST, 0);                 // put MAX7219 into "normal" mode
}

/*
*********************************************************************************************************
* MAX7219_Clear()
*
* Description: Clear the display (all digits blank)
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_Clear (void)
{
  char i;
  for (i=0; i < 8; i++)
    MAX7219_Write(i, 0x00);                           // turn all segments off
}

/*
*********************************************************************************************************
* MAX7219_SetBrightness()
*
* Description: Set the LED display brightness
* Arguments  : brightness (0-15)
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_SetBrightness (char brightness)
{
  brightness &= 0x0f;                                 // mask off extra bits
  MAX7219_Write(REG_INTENSITY, brightness);           // set brightness
}
