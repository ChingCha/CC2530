//-------------------------------------------------------------------
// Filename: ex.c
// Description: °¨¹F±±¨î(PWM)½d¨Ò 
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
#include "M280.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key, duty, ccw;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M280 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        M280_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M280 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, " CW Duty = 100 %");
        duty = 100;
        ccw = 0;
        M280_CW(duty);
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
                if (key == 'C')
                {
                    halLcdWriteChar(HAL_LCD_LINE_2, 0, 'C');
                    ccw = 1;
                    M280_Stop();
                    halMcuWaitMs(200);
                }
                if (key == 'F')
                {
                    halLcdWriteChar(HAL_LCD_LINE_2, 0, ' ');
                    ccw = 0;
                    M280_Stop();
                    halMcuWaitMs(200);
                }
                if (key == 'U')
                {
                    if (duty < 100)
                    {
                        duty += 5;
                    }
                }
                if (key == 'N')
                {
                    if (duty > 0)
                    {
                        duty -= 5;
                    }
                }
                if (ccw == 0)
                {
                    M280_CW(duty);
                }
                else
                {
                    M280_CCW(duty);
                }
                halLcdDisplayUint8(HAL_LCD_LINE_2, 11, HAL_LCD_RADIX_DEC, duty);
            }
        }
        M280_Stop();
    }
}
