//-------------------------------------------------------------------
// Filename: keypad_lcd.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_buzzer.h"
#include "hal_uart.h"
#include "util.h"
#include "util_lcd.h"


//-------------------------------------------------------------------
void main(void)
{
    uint8 no;
    uint8 buf[3];
    halBoardInit();						//程式一開始的初始化函式
    halLedSet(8);						//標示裝置以通電

    
    utilPrintLogo("Keypad LCD Test");	//Print Logo and splash screen on LCD
    halBuzzer(300);					 	//Turn Buzzer on.  
    while(halKeypadPushed()==0);		//This function detects(查明) if the keypad is being pushed.
    halLcdClear();						//Clear all lines on display

    no = 0;								//宣告no變數
    while (TRUE)						//while迴圈內為True繼續執行，False跳出
    {
        uint8 key;						//0-255 integer with Unsigned
        key = halKeypadPushed();		
        if (key > 0)
        {
            if (key == '1')
            {
                halLedSet(1);
            }
            if (key == '2')
            {
               //條件成立後，執行的動作
            }
            if (key == 'A')
            {
                halBuzzer(500);
            }
            if (key == 'U')
            {
               //條件成立後，執行的動作
            }
            if (key == 'N')
            {
               //條件成立後，執行的動作
            }
            if (key == '*')
            {
                break;
            }
           
            
            //LCD顯示
            if (no >= 16)
            {
                halLcdWriteChar(HAL_LCD_LINE_2, no - 16, key);	//Write single character
                halUartWrite(buf,1);							//Write a buffer(傳送資料緩衝區) to the UART.
            }
            else
            {
                halLcdWriteChar(HAL_LCD_LINE_1, no, key);
                halUartWrite(buf,1);
            }
            no++;
            if (no >= 32)
            {
                halBuzzer(300);
                halLcdClear();
                no = 0;             
            } 
        }
        halMcuWaitMs(300);      
    }
}

