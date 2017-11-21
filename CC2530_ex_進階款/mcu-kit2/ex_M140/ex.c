//-------------------------------------------------------------------
// Filename: ex.c
// Description: ·Å«×°»´ú(SPI)½d¨Ò 
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
#include "M140.h"

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
    utilPrintLogo("** M140 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        M140_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M140 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_3, " Temp. =       C");
        halLcdWriteChar(HAL_LCD_LINE_3, 14, 0xDF);
        while (TRUE)
        {
            val = M140_GetValue();
            if ((0x2000 &val) == 0x2000)
            //Check sign bit for negative value.
            {
                val = ((val - 16384) *10) / 32;
            }
            else
            {
                val = (val *10) / 32;
            }

            halLcdWriteChar(HAL_LCD_LINE_2, 9, (val / 100) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 10, ((val / 10) % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 11, '.');
            halLcdWriteChar(HAL_LCD_LINE_2, 12, (val % 10) + '0');
            key = halKeypadPushed();
            halMcuWaitMs(100);
            if (key == '*')
            {
                break;
            }
        }
    }
}
