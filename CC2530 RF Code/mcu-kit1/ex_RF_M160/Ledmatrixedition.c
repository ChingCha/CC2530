//引入標頭檔
#include "ioCC2530.h"
#include "hal_defs.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_button.h"
#include "M160.h"

//MAX7219暫存器巨集定義

#define DECODE_MODE  0x09   //解碼控制暫存器
#define INTENSITY    0x0A   //亮度控制暫存器
#define SCAN_LIMIT   0x0B   //掃描界限暫存器
#define SHUT_DOWN    0x0C   //關斷模式暫存器
#define DISPLAY_TEST 0x0F   //測試控制暫存器
#define DIGIT0		 0x01	//DIGIT0暫存器

#define INTENSITY_MIN     0x00   // 最小顯示亮度
#define INTENSITY_MAX     0x0F   // 最大顯示亮度

//CC2530腳位功能巨集定義

#define MAX7219DIN    P0_4		//CC2530 P0_4>>>模組DIN腳位
#define MAX7219CS     P0_5		//CC2530 P0_5>>>模組CS(LOAD)腳位
#define MAX7219CLK    P0_6		//CC2530 P0_6>>>模組CLK腳位

//函數宣告
void Write7219(unsigned char address,unsigned char dat);
void MAX7219_Init(void);
void Delay(unsigned int t);

int main(){
	
	//KIT板初始化
	halBoardInit();
	halLcdInit();
	
	
    MAX7219_Init();               //MAX7219初始化
    Write7219(DIGIT0,0x80);      //數碼管顯示1~8

}


//CC2530 Port & MAX7219初始化函數，並設置MAX7219內部的控制暫存器
void MAX7219_Init(){
	
	P0SEL &= ~0x70;	//把P0_4、5、6設置為通用I/O Port功能
	P1DIR |= 0x70;	//把P0_4、5、6 Prot傳輸方向設置為輸出
	
	Write7219(SHUT_DOWN,0x01);         //開啟正常工作模式（0xX1）
    Write7219(DISPLAY_TEST,0x00);      //選擇工作模式（0xX0）
    Write7219(DECODE_MODE,0xff);       //選用全解碼模式
    Write7219(SCAN_LIMIT,0x07);        //8只LED全用
    Write7219(INTENSITY,0x04);          //設置初始亮度   
	
}


//位址、資料發送副程式
void Write7219(unsigned char address,unsigned char dat)
{   
    unsigned char i;
    MAX7219CS=0;    //拉低片選線，選中暫存器
	
    //發送地址
    for (i=0;i<8;i++)        //移位迴圈8次(前八位元D15~8)           
    {   
       MAX7219CLK=0;        //清零時鐘匯流排
       MAX7219DIN=(bit)(address&0x80); //每次取高位元組      
       address<<=1;             //左移一位
       MAX7219CLK=1;        //時鐘上升沿，發送位址
    }
	
    //發送資料
    for (i=0;i<8;i++)   	//移位迴圈8次(後八位元D7~0)             
    {   
       MAX7219CLK=0;
       MAX7219DIN=(bit)(dat&0x80);     
       dat<<=1;  
       MAX7219CLK=1;        //時鐘上升沿，發送資料
    }
    MAX7219CS=1;    //發送結束，上升沿鎖存資料                       
}

