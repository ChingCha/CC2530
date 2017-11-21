//-------------------------------------------------------------------
// Filename: ex.c
// Description: ¬õ¥~½u·Å«×°»´ú(I2C)½d¨Ò 
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
#include "M320.h"

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
    utilPrintLogo("** M320 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        M320_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "Die T. =       C");
        halLcdWriteLine(HAL_LCD_LINE_2, "Obj T. =       C");
        halLcdWriteChar(HAL_LCD_LINE_1, 14, 0xDF);
        halLcdWriteChar(HAL_LCD_LINE_2, 14, 0xDF);
        while (TRUE)
        {
            val = M320_GetDieTemperature();
            val=((val *2) - 27315) / 10;
            halLcdWriteChar(HAL_LCD_LINE_1, 9, (val / 100) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 10, ((val / 10) % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 11, '.');
            halLcdWriteChar(HAL_LCD_LINE_1, 12, (val % 10) + '0');
            halMcuWaitMs(100);

            val = M320_GetObjTemperature();
            val=((val *2) - 27315) / 10;
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
