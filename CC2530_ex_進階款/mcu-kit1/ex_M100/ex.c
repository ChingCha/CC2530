//-------------------------------------------------------------------
// Filename: ex.c
// Description: RTC®ÉÄÁ(I2C)½d¨Ò
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
#include "M100.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key;
    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M100 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halLcdWriteLine(HAL_LCD_LINE_1, "** 2010/01/01 **");
        halLcdWriteLine(HAL_LCD_LINE_2, "**  12:00:00  **");
        M100_Init();
        GetDateTime();
        if(Year<2009)
        {
            Year = 2010;
            Month = 1;
            Day = 1;
            Hour = 12;
            Min = 0;
            Sec = 0;
            SetDateTime();
        }
        while (TRUE)
        {
            GetDateTime();
            halLcdWriteChar(HAL_LCD_LINE_1, 5, ((Year / 10) % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 6, (Year % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 8, (Month / 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 9, (Month % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 11, (Day / 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_1, 12, (Day % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 4, (Hour / 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 5, (Hour % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 7, (Min / 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 8, (Min % 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 10, (Sec / 10) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 11, (Sec % 10) + '0');
            key=halKeypadPushed();
            halMcuWaitMs(100);
            if (key == '*')
            {
                break;
            }
            if (key == 'A')
            {
                Year++;
                if(Year>2099)
                    Year=2099;
                SetDateTime();
            }
            if (key == 'D')
            {
                Year--;
                if(Year<2000)
                    Year=2000;
                SetDateTime();
            }
            if (key == 'B')
            {
                Month++;
                if(Month>12)
                   Month=1; 
                SetDateTime();
            }
            if (key == 'E')
            {
                Day++;
                if(Day>31)
                   Day=1; 
                SetDateTime();
            }
            if (key == 'C')
            {
                Hour++;
                if(Hour>23)
                   Hour=0; 
                SetDateTime();
            }
            if (key == 'F')
            {
                Min++;
                if(Min>59)
                   Min=0; 
                SetDateTime();
            }
            if (key == '#')
            {
                Sec=0;
                SetDateTime();
            }
        }
    }
}
