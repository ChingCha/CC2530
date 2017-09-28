//-------------------------------------------------------------------
// Filename: ex.c
// Description: LED½Õ¥ú(PWM)½d¨Ò
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
#include "M160.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key, duty;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M160 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        M160_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M160 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "   Duty = 50  % ");
        duty = 50;
        M160_On(duty);
        while (TRUE)
        {
            halMcuWaitMs(20);
            key = halKeypadPushed();
            if (key > 0)
            {
                if (key == '*')
                {
                    break;
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
                M160_On(duty);
                halLcdDisplayUint8(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, duty);
            }
        }
        M160_Off();
    }
}