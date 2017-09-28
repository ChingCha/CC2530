//-------------------------------------------------------------------
// Filename: ex.c
// Description: ·Ó«×«G«×°»´ú(A/D)½d¨Ò
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
#include "M170.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key;
    uint16 val;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M170 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        M170_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M170 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, " Bright =     % ");
        while (TRUE)
        {
            val = M170_GetValue();
            if (val > 2000)
            {
                val -= 2000;
            }
            else
            {
                val = 0;
            }
            val /= 120;
            if (val > 100)
            {
                val = 100;
            }
            halLcdDisplayUint8(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, val);
            key = halKeypadPushed();
            halMcuWaitMs(100);
            if (key == '*')
            {
                break;
            }
        }
    }
}
