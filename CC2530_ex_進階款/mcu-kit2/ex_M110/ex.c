//-------------------------------------------------------------------
// Filename: ex.c
// Description: 全方向震動偵測(INT)範例
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
#include "M110.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M110 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        M110_Init();
        M110_Enable();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M110 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "  Count =");
        while (TRUE)
        {
            halLcdDisplayUint16(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, M110_GetValue());
            key = halKeypadPushed();
            halMcuWaitMs(100);
            if (key == '*')
            {
                break;
            }
        }
        M110_Disable();
    }
}
