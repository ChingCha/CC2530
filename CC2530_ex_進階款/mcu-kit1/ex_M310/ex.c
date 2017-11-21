//-------------------------------------------------------------------
// Filename: ex.c
// Description: ¥ú¾BÂ_°»´ú(DI/DO)½d¨Ò
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
#include "M310.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key;
    uint8 udi;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M310 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        M310_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M310 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "SENSOR = [_][_] ");
        while (TRUE)
        {
            udi = M310_GetSensor();
            halLcdWriteChar(HAL_LCD_LINE_2, 10, (udi &0x01) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 13, ((udi >> 1) &0x01) + '0');
            key = halKeypadPushed();
            halMcuWaitMs(100);
            if (key == '*')
            {
                break;
            }
        }
    }
}
