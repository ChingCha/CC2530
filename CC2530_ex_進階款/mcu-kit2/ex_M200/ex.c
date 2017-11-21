//-------------------------------------------------------------------
// Filename: ex.c
// Description: ·ÅÀã«×°»´ú(I2C)½d¨Ò
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
#include "M200.h"

//-------------------------------------------------------------------
void main(void)
{
    uint16 temp, humi;
    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M200 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    //while (halKeypadPushed() == 0)
    //    ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        halLcdWriteLine(HAL_LCD_LINE_1, "Humidity=      %");
        halLcdWriteLine(HAL_LCD_LINE_2, " Temp. =       C");
        halLcdWriteChar(HAL_LCD_LINE_2, 14, 0xDF);
        M200_Init();
        while (TRUE)
        {
            M200_GetValue();
            temp = (uint16)(((((float)M200_Temp) *0.01) - 40.0) *10.0);
            humi = (uint16)(((((float)M200_Humi) *0.0405) - (((float)M200_Humi)*((float)M200_Humi) *0.0000028) - 4.0) *10.0);

            if (humi > 999)
            {
                humi = 999;
            }
            if (temp > 999)
            {
                temp = 999;
            }
            halLcdWriteChar(HAL_LCD_LINE_1, 10, (humi / 100) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 11, ((humi / 10) % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 12, '.');
            halLcdWriteChar(HAL_LCD_LINE_1, 13, (humi % 10) + '0');

            halLcdWriteChar(HAL_LCD_LINE_2, 9, (temp / 100) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 10, ((temp / 10) % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 11, '.');
            halLcdWriteChar(HAL_LCD_LINE_2, 12, (temp % 10) + '0');

            halMcuWaitMs(300);
            if (halKeypadPushed() == '*')
            {
                break;
            }
        }
    }
}
