//引入標頭檔
#include "ioCC2530.h"

//MAX7219暫存器巨集定義

#define REG_DECODE        0x09                        // "decode mode" register
#define REG_INTENSITY     0x0a                        // "intensity" register
#define REG_SCAN_LIMIT    0x0b                        // "scan limit" register
#define REG_SHUTDOWN      0x0c                        // "shutdown" register
#define REG_DISPLAY_TEST  0x0f                        // "display test" register

#define INTENSITY_MIN     0x00                        // minimum display intensity
#define INTENSITY_MAX     0x0f                        // maximum display intensity

//CC2530腳位功能巨集定義

#define MAX7219DIN    P0_4		//CC2530 P0_4>>>模組DIN腳位
#define MAX7219LOAD     P0_5		//CC2530 P0_5>>>模組CS(LOAD)腳位
#define MAX7219CLK    P0_6		//CC2530 P0_6>>>模組CLK腳位

unsigned char value[1]={0x80};

//函數宣告
void MAX7219_Init(void);
void MAX7219_SendByte (unsigned char dataout);
void MAX7219_Write (unsigned char reg_number, unsigned char dataout);
void MAX7219_DisplayTestStart (void);

//CC2530 Port & MAX7219初始化函數，並設置MAX7219內部的控制暫存器
void MAX7219_Init(){
	
	P0SEL &= ~0x70;	//把P0_4、5、6設置為通用I/O Port功能
	P1DIR |= 0x70;	//把P0_4、5、6 Prot傳輸方向設置為輸出
	
	MAX7219_Write(REG_SCAN_LIMIT, 7);                   // set up to scan all eight digits
	MAX7219_Write(REG_DECODE, 0x00);                    // set to "no decode" for all digitsMAX7219_ShutdownStop();                             // select normal operation (i.e. not shutdown)
	MAX7219_DisplayTestStop();                          // select normal operation (i.e. not test mode)
	MAX7219_Clear();                                    // clear all digits
	MAX7219_SetBrightness(INTENSITY_MAX);               // set to maximum intensity
	
}

int main(){
	
	MAX7219_Init();

	
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
