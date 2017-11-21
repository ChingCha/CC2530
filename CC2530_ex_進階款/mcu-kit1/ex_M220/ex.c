//-------------------------------------------------------------------
// Filename: ex.c
// Description: 三軸位移加速度(SPI)範例
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
#include "M220.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M220 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        M220_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M220 Test  **");
        while (TRUE)
        {
            M220_Pooling();
            if ((M220_X_AXIS_Value &0x8000) == 0x8000)
            {
                M220_X_AXIS_Value = 65535-M220_X_AXIS_Value;
                halLcdWriteChar(HAL_LCD_LINE_2, 0, '-');
            }
            else
            {
                halLcdWriteChar(HAL_LCD_LINE_2, 0, '+');
            }
            if ((M220_Y_AXIS_Value &0x8000) == 0x8000)
            {
                M220_Y_AXIS_Value = 65535-M220_Y_AXIS_Value;
                halLcdWriteChar(HAL_LCD_LINE_2, 6, '-');
            }
            else
            {
                halLcdWriteChar(HAL_LCD_LINE_2, 6, '+');
            }
            if ((M220_Z_AXIS_Value &0x8000) == 0x8000)
            {
                M220_Z_AXIS_Value = 65535-M220_Z_AXIS_Value;
                halLcdWriteChar(HAL_LCD_LINE_2, 12, '-');
            }
            else
            {
                halLcdWriteChar(HAL_LCD_LINE_2, 12, '+');
            }
            halLcdDisplayUint16(HAL_LCD_LINE_2, 1, HAL_LCD_RADIX_DEC, M220_X_AXIS_Value);
            halLcdDisplayUint16(HAL_LCD_LINE_2, 7, HAL_LCD_RADIX_DEC, M220_Y_AXIS_Value);
            halLcdDisplayUint16(HAL_LCD_LINE_2, 13, HAL_LCD_RADIX_DEC, M220_Z_AXIS_Value);
            key = halKeypadPushed();
            halMcuWaitMs(200);
            if (key == '*')
            {
                break;
            }
        }
    }
}
