//引入標頭檔
#include "ioCC2530.h"

//MAX7219暫存器巨集定義

#define DIGIT0		 	0x01	//DIGIT0暫存器
#define DIGIT1		 	0x02	//B販賣機暫存器
#define DIGIT2			0x03
#define DIGIT7			0x08
#define REG_DECODE        0x09                        // "decode mode" register
#define REG_INTENSITY     0x0a                        // "intensity" register
#define REG_SCAN_LIMIT    0x0b                        // "scan limit" register
#define REG_SHUTDOWN      0x0c                        // "shutdown" register
#define REG_DISPLAY_TEST  0x0f                        // "display test" register

//CC2530腳位功能巨集定義

#define MAX7219DIN    P0_4		//CC2530 P0_4>>>模組DIN腳位
#define MAX7219LOAD   P0_5		//CC2530 P0_5>>>模組CS(LOAD)腳位
#define MAX7219CLK    P0_6		//CC2530 P0_6>>>模組CLK腳位

//函數宣告
void MAX7219_SendByte (unsigned char DINout);
void MAX7219_Write (unsigned char reg_number, unsigned char DINout);
void MAX7219_Init(void);
void MAX7219_Clear (void);
void MAX7219_SetBrightness (char brightness);

//延遲函數
void Delay(unsigned int t)
{
  while(t--);
}

//CC2530 Port & MAX7219初始化函數，並設置MAX7219內部的控制暫存器
void MAX7219_Init(){
	
	P0SEL &= ~0x70;	//把P0a_4、5、6設置為通用I/O Port功能
	P0DIR |= 0x70;	//把P0_4、5、6 Prot傳輸方向設置為輸出
	
	MAX7219_Write(REG_DECODE, 0x00);          	// set to "no decode" for all digits
	MAX7219_Write(REG_SCAN_LIMIT, 0x07);      	// set up to scan all eight digits
	MAX7219_Write(REG_SHUTDOWN, 1);
	MAX7219_Write(REG_DISPLAY_TEST, 0);	
	MAX7219_Clear(); 
	MAX7219_SetBrightness(0x06); 
}

int main(){
	
	MAX7219_Init();
	MAX7219_Write(DIGIT1,0x01);
	
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
