//-------------------------------------------------------------------
// Filename: ex.c
// Description: RFIDÅª¥d¼Ò²Õ(DI)½d¨Ò 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_uart.h"
#include "hal_buzzer.h"
#include "hal_led.h"
#include "hal_rf.h"
#include "util.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "M250.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 i;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M250 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();

        halLcdWriteLine(HAL_LCD_LINE_1, "** Punch Card **");
        halLcdWriteLine(HAL_LCD_LINE_2, "UID = [        ]");
        M250_Init();
        while (TRUE)
        {
            if(M250_ReadTag()==1)
			{
				for(i=0;i<4;i++)
				{
            		halLcdDisplayUint8(HAL_LCD_LINE_2, 7+(i*2), HAL_LCD_RADIX_HEX, rfTagUID[3-i]);
				}
				halBuzzer(300);
			}
            halMcuWaitMs(100);
            if (halKeypadPushed() == '*')
            {
                break;
            }
        }
    }
}
