//-------------------------------------------------------------------
// Filename: keypad_lcd.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_buzzer.h"
#include "hal_uart.h"
#include "util.h"
#include "util_lcd.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 ch, no;
    uint8 buf[3];

    // Initalise board peripherals
    halBoardInit();
    // Indicate that device is powered
    halLedSet(8);

    // Print Logo and splash screen on LCD
    utilPrintLogo("Keypad LCD Test");
    halBuzzer(300);
    while(halKeypadPushed()==0);
    halLcdClear();

    no = 0;
    while (TRUE)
    {
        ch = halKeypadPushed();
        if (ch > 0)
        {
          buf[0] = ch;
          
            if (no >= 16)
            {
                halLcdWriteChar(HAL_LCD_LINE_2, no - 16, ch);
                halUartWrite(buf,1);
            }
            else
            {
                halLcdWriteChar(HAL_LCD_LINE_1, no, ch);
                halUartWrite(buf,1);
            }
            no++;
            if (no >= 32)
            {
                halBuzzer(300);
                halLcdClear();
                no = 0;             
            }
            halMcuWaitMs(200);
        }
        halMcuWaitMs(10);
        
        
        ch = halUartRxLen();
        if (ch > 0)
        {
            if (ch > 16)
            {
                ch = 16;
            }
            halUartRead(buf, ch);
            buf[ch] = 0;
            halLcdWriteLine(HAL_LCD_LINE_2, (char*)buf);            
        }
        halMcuWaitMs(300);
        
    }
}

