//-------------------------------------------------------------------
// Filename: ex.c
// Description: ¥þ±mLED½Õ¥ú(PWM)½d¨Ò
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
#include "M240.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key, dutyR, dutyG, dutyB;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M240 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        M240_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M240 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "R0    G0    B0  ");
        dutyR = 0;
        dutyG = 0;
        dutyB = 0;
        M240_LEDR_On(dutyR);
        M240_LEDG_On(dutyG);
        M240_LEDB_On(dutyB);
        while (TRUE)
        {
            halMcuWaitMs(50);
            key = halKeypadPushed();
            if (key > 0)
            {
                if (key == '*')
                {
                    break;
                }
                if (key == 'A')
                {
                    if (dutyR < 100)
                    {
                        dutyR += 5;
                    }
                }
                if (key == 'D')
                {
                    if (dutyR > 0)
                    {
                        dutyR -= 5;
                    }
                }
                if (key == 'B')
                {
                    if (dutyG < 100)
                    {
                        dutyG += 5;
                    }
                }
                if (key == 'E')
                {
                    if (dutyG > 0)
                    {
                        dutyG -= 5;
                    }
                }
                if (key == 'C')
                {
                    if (dutyB < 100)
                    {
                        dutyB += 5;
                    }
                }
                if (key == 'F')
                {
                    if (dutyB > 0)
                    {
                        dutyB -= 5;
                    }
                }
                if (key == 'U')
                {
                    if (dutyR < 100)
                    {
                        dutyR += 5;
                    }
                    if (dutyG < 100)
                    {
                        dutyG += 5;
                    }
                    if (dutyB < 100)
                    {
                        dutyB += 5;
                    }
                }
                if (key == 'N')
                {
                    if (dutyR > 0)
                    {
                        dutyR -= 5;
                    }
                    if (dutyG > 0)
                    {
                        dutyG -= 5;
                    }
                    if (dutyB > 0)
                    {
                        dutyB -= 5;
                    }
                }
                M240_LEDR_On(dutyR);
                M240_LEDG_On(dutyG);
                M240_LEDB_On(dutyB);
                halLcdDisplayUint8(HAL_LCD_LINE_2, 1, HAL_LCD_RADIX_DEC, dutyR);
                halLcdDisplayUint8(HAL_LCD_LINE_2, 7, HAL_LCD_RADIX_DEC, dutyG);
                halLcdDisplayUint8(HAL_LCD_LINE_2, 13, HAL_LCD_RADIX_DEC, dutyB);
            }
        }
        M240_Off();
    }
}
