//-------------------------------------------------------------------
// Filename: ex.c
// Description: ³Á§J­·¿é¤J(A/D)½d¨Ò
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
#include "M290.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key, i, j;
    uint16 val, valmax;
    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M290 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        M290_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M290 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, " Sound =     dB");
        while (TRUE)
        {
            valmax = 0;
            for (j = 0; j < 50; j++)
            {
                for (i = 0; i < 100; i++)
                {
                    val = M290_GetValue();
                    if (val > valmax)
                    {
                        valmax = val;
                    }
                }
                key = halKeypadPushed();
                if (key == '*')
                {
                    break;
                }
                halLedToggle(1);
            }
            if (valmax > 15000)
            {
                valmax -= 15000;
            }
            else
            {
                valmax = 0;
            }
            valmax /= 400;
            valmax += 35;
            if (valmax > 130)
            {
                valmax = 130;
            }
            if (valmax < 35)
            {
                valmax = 35;
            }
            halLcdDisplayUint8(HAL_LCD_LINE_2, 9, HAL_LCD_RADIX_DEC, valmax);
            if (key == '*')
            {
                break;
            }
        }
    }
}
