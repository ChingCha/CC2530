//-------------------------------------------------------------------
// Filename: ex.c
// Description: 霍爾元件電流偵測(A/D)範例 
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
#include "M150.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key, i;
    uint16 val, sum;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M150 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        M150_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M150 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "Current = _.__ A");
        while (TRUE)
        {
            sum = 0;
            for (i = 0; i <30; i++)
            {
                val = M150_GetValue();
                if (val > 0x5C50)
                {
                    val -= 0x5C50;
                }
                else
                {
                    val = 0;
                }
                val /= 17;
                sum += val;
                halMcuWaitMs(20);
            }
            val = sum / 30;
            halLcdWriteChar(HAL_LCD_LINE_2, 10, (val / 100) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 11, '.');
            halLcdWriteChar(HAL_LCD_LINE_2, 12, ((val / 10) % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 13, (val % 10) + '0');
            key = halKeypadPushed();
            if (key == '*')
            {
                break;
            }
        }
    }
}
