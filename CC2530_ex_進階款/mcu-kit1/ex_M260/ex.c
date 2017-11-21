//-------------------------------------------------------------------
// Filename: ex.c
// Description: ¨¤³t«×°»´úªûÁ³»ö(SPI)½d¨Ò
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
#include "M260.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 posi;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M260 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halLcdWriteLine(HAL_LCD_LINE_1, "  Rate = ");
        M260_Init();
        posi = 8;
        halLcdWriteChar(HAL_LCD_LINE_2, posi, 'o');
        while (TRUE)
        {
            M260_Pooling();
            halLcdDisplayUint16(HAL_LCD_LINE_1, 9, HAL_LCD_RADIX_DEC, M260_Rate);
            if (M260_Rate > 1100)
            {
                if (posi < 15)
                {
                    posi++;
                }
                halLcdClearLine(HAL_LCD_LINE_2);
                halLcdWriteChar(HAL_LCD_LINE_2, posi, 'o');
            }
            if (M260_Rate < 850)
            {
                if (posi > 0)
                {
                    posi--;
                }
                halLcdClearLine(HAL_LCD_LINE_2);
                halLcdWriteChar(HAL_LCD_LINE_2, posi, 'o');
            }
            halMcuWaitMs(100);
            if (halKeypadPushed() == '*')
            {
                break;
            }
        }
    }
}
