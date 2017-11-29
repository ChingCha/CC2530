//-------------------------------------------------------------------
// Filename: ex.c
// Description: 串列記憶體(I2C)範例
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "ioCC2530.h"
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
//#include "hal_uart.h"
#include "hal_buzzer.h"
#include "hal_led.h"
#include "hal_rf.h"
#include "util.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "M230.h"

#define LED1 P1_3
#define LED2 P1_4

/*
unsigned char DataRecieve;		//讀取緩衝區資料的變數
unsigned char Flag = 0;			//接收指令標誌的變數


void Init_Port();						//LED Port 初始化函數
void Init_UART0();						//序列埠0的初始化函數
void set_main_clock();					//設置主時鐘
void ExecuteTheOrder();					//執行上位機指令
void UR0SendByte(unsigned char data);	//UR0發送字元函數
void UR0SendString(unsigned char *str);	//UR0發送字串函數
*/

void main(void)
{
	
	uint8 key;
	
	
	/*
	// UART初始化
	Init_Port();	
	set_main_clock();
	Init_UART0();
	*/
	
	// 初始化擴充板、LCD、點矩陣
    halBoardInit();
    
    // Indicate that device is powered
    halLedSet(8);
	
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M230 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
		;
    utilMenuSelect(NULL);
	
	//測試字串
	//UR0SendString("1\n");
	
	
    while (TRUE)
    {
		
		//M230初始動作
        halLcdClear();
        halBuzzer(300);
        M230_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M230 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "Write:   Read:  ");
        key = M230_ReadEEPROM(0);
        halLcdWriteChar(HAL_LCD_LINE_2, 14, key);
		
        while (TRUE)
        {
			/*
			if(Flag == 1)      //是否收到上位機指令?
			{
				ExecuteTheOrder();    //解析並運行指令
			}
			*/
			
			
            key = halKeypadPushed();
            halMcuWaitMs(100);
            if (key > 0)
            {
                if (key == '*')
                {
                    break;
                }
                M230_WriteEEPROM(0, key); //WriteEEPROM(addr, data)
                halLcdWriteChar(HAL_LCD_LINE_2, 6, key);

                key = M230_ReadEEPROM(0); //ReadEEPROM(addr)
                halLcdWriteChar(HAL_LCD_LINE_2, 14, key);
            }
        }
    }
}

/*
void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//將要發送的1字節數據寫入U0DBUF
	while(!UTX0IF);			//等待TX中斷標誌，即數據發送完成
	UTX0IF = 0;				//等待TX中斷標誌，準備下一次發送
	
}


void UR0SendString(unsigned char *str){
	
	while(*str != '\0'){	//發送一個字串
		UR0SendByte(*str++);//逐一發送字串的字元
	}
	
}

void Init_Port(){
	
	P1SEL &= ~0x18;		//將P1_4、5設置為通用I/O
	P1DIR |= 0x18;		//將P1_4、5 Port 設置為輸出
	LED1 = 0;
	LED2 = 0;
	
}

void Init_UART0(){
	
	//對應的引腳為外設功能

	PERCFG = 0x00;	//串口0的引腳映射到位置1，即P0_2、3
	P0SEL = 0x0C;	//將P0_2、3 Port 設置成外設功能
	P2DIR &= ~0x3F;	//P0外設優先級USART0最高
	
	U0BAUD = 216;	//16MHz的系統時鐘產生115200BPS鮑率
	U0GCR = 12;
	
	U0UCR |= 0x80;	//禁止流控，8bit數據，清除緩衝器
	U0CSR |= 0x80;	//選擇UART模式(7)，致能接收器(6)
	
	UTX0IF = 0;		//清除TX發送中斷標誌
	
	//UART2.c外加
	
	U0CSR |=0X40;			//致能UART0 接收
	IEN0 |=0X04;			//致能UART0 接收中斷
	EA=1;					//開啟總中斷

}

//數據接收中斷服務函數
#pragma vector = URX0_VECTOR		
__interrupt void UR0_Recieve_Service(){
	
	URX0IF = 0;				//清除RX接收中斷標誌
	DataRecieve = U0DBUF;	//將數據從接收緩衝區讀出
	Flag = 1;				//設置接收指令標誌
}

void ExecuteTheOrder(){
	
	Flag = 0;	//清除接收指令標誌
	
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
		
		case 0x34:
			LED2 = 0;
			UR0SendString("The LED2 is Closed!");
		break;
	}
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
}
*/

