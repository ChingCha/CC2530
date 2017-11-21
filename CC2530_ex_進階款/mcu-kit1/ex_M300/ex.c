//-------------------------------------------------------------------
// Filename: ex.c
// Description: ¶W­µªi´ú¶Z(DI/DO)½d¨Ò
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
#include "M300.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key;
    uint8 uval;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M300 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        M300_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M300 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "Distance  _._ cm");
        while (TRUE)
        {
            M300_TX();
            uval = M300_GetValue();
            if(uval>=13)
                uval-=13;
            else
                uval=0;
            if(uval>=200)
                uval=200;
            halLcdWriteChar(HAL_LCD_LINE_2, 9, (uval/100) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 10, ((uval/10)%10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 12, (uval%10) + '0');
            key = halKeypadPushed();
            halMcuWaitMs(100);
            halMcuWaitMs(100);
            if (key == '*')
            {
                break;
            }
        }
    }
}
