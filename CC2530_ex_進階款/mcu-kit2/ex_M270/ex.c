//-------------------------------------------------------------------
// Filename: ex.c
// Description: Ä~¹q¾¹/«öÁä(DI/DO)½d¨Ò
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
#include "M270.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 key;
    uint8 udi;
    uint8 udo = 0;

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M270 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;
    utilMenuSelect(NULL);
    while (TRUE)
    {
        halLcdClear();
        M270_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M270 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "DI=[1][1] DO=[0]");
        while (TRUE)
        {
            udi = M270_GetDI();
            halLcdWriteChar(HAL_LCD_LINE_2, 4, (udi &0x01) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 7, ((udi >> 1) &0x01) + '0');
            halLcdWriteChar(HAL_LCD_LINE_2, 14, udo + '0');
            if ((udi &0x01) == 0x00)
            {
                udo = 1;
                M270_SetDO(udo);
            }
            if ((udi &0x02) == 0x00)
            {
                udo = 0;
                M270_SetDO(udo);
            }
            key = halKeypadPushed();
            halMcuWaitMs(100);
            if (key == '*')
            {
                break;
            }
        }
        HAL_RELAY_OFF();
    }
}
