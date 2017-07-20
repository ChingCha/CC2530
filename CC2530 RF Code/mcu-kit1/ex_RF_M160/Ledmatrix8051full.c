//引入標頭檔
#include "ioCC2530.h"

//MAX7219暫存器巨集定義

#define DECODE_MODE  0x09   //解碼控制暫存器
#define INTENSITY    0x0A   //亮度控制暫存器
#define SCAN_LIMIT   0x0B   //掃描界限暫存器
#define SHUT_DOWN    0x0C   //關斷模式暫存器
#define DISPLAY_TEST 0x0F   //測試控制暫存器 

#define INTENSITY_MIN     0x00   // 最小顯示亮度
#define INTENSITY_MAX     0x0F   // 最大顯示亮度

//CC2530腳位功能巨集定義

#define MAX7219DIN    P0_4		//CC2530 P0_4>>>模組DIN腳位
#define MAX7219LOAD     P0_5		//CC2530 P0_5>>>模組CS(LOAD)腳位
#define MAX7219CLK    P0_6		//CC2530 P0_6>>>模組CLK腳位

unsigned char value[1]={0x80};

//函數宣告
void MAX7219_Init(void);
void MAX7219_SendByte (unsigned char dataout);
void MAX7219_Write (unsigned char reg_number, unsigned char dataout);

//CC2530 Port & MAX7219初始化函數，並設置MAX7219內部的控制暫存器
void MAX7219_Init(){
	
	P0SEL &= ~0x70;	//把P0_4、5、6設置為通用I/O Port功能
	P1DIR |= 0x70;	//把P0_4、5、6 Prot傳輸方向設置為輸出
	
	MAX7219_Write(SHUT_DOWN,0x01);         //開啟正常工作模式（0xX1）
    MAX7219_Write(DISPLAY_TEST,0x00);      //選擇工作模式（0xX0）
    MAX7219_Write(DECODE_MODE,0xff);       //選用全解碼模式
    MAX7219_Write(SCAN_LIMIT,0x07);        //8只LED全用
    MAX7219_Write(INTENSITY,0x04);          //設置初始亮度   
	
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

