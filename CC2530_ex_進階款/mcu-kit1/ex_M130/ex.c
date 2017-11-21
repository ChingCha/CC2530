//-------------------------------------------------------------------
// Filename: ex.c
// Description: 紅外線接收模組(DI)範例
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
#include "M130.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 i;
    // Initalise board peripherals
    halBoardInit();
    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M130 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        M130_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M130 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "Code =");
        while (TRUE)
        {
            if (M130_GetData() > 0)
            {
                halBuzzer(300);
                for (i = 0; i < 4; i++)
                {
                    halLcdDisplayUint8(HAL_LCD_LINE_2, ((i *2) + 7), HAL_LCD_RADIX_HEX, M130_Buf[i]);
                }
            }
            if (halKeypadPushed() == '*')
            {
                break;
            }
        }
    }
}
