//-------------------------------------------------------------------
// Filename: ex.c
// Description: ¦ê¦C°O¾ÐÅé(I2C)½d¨Ò
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
#include "M230.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M230 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        M230_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M230 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "Write:   Read:  ");
        key = M230_ReadEEPROM(0);
        halLcdWriteChar(HAL_LCD_LINE_2, 14, key);
        while (TRUE)
        {
            key = halKeypadPushed();
            halMcuWaitMs(100);
            if (key > 0)
            {
                if (key == '*')
                {
                    break;
                }
                M230_WriteEEPROM(0, key); //WriteEEPROM(addr, data)
                halLcdWriteChar(HAL_LCD_LINE_2, 6, key);

                key = M230_ReadEEPROM(0); //ReadEEPROM(addr)
                halLcdWriteChar(HAL_LCD_LINE_2, 14, key);
            }
        }
    }
}
