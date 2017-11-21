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
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_buzzer.h"
#include "hal_led.h"
#include "util.h"
#include "util_lcd.h"
#include "hal_uart.h"

//-------------------------------------------------------------------
void main(void)
{
    uint8 ch, no;
    uint8 write[5], read[5];

    // Initalise board peripherals
    halBoardInit();
    // Indicate that device is powered
    halLedSet(8);
    halLcdDrawLogo();
    halBuzzer(300);
    while(halKeypadPushed() == 0);

    // Print Logo and splash screen on LCD
    utilPrintLogo("Keypad LCD Test");
    no = 0;
    halLcdClear();
    
    halLcdWriteString(HAL_LCD_LINE_1, 0, "KeyPad LCD Test");
    halLcdWriteString(HAL_LCD_LINE_2, 0, "Keyin Word:");
    
    while (TRUE)
    {
        ch = halKeypadPushed();
        if (ch > 0)
        {
            if (no >= 16)
            {
                halLcdWriteChar(HAL_LCD_LINE_4, no - 16, ch);
            }
            else
            {
                halLcdWriteChar(HAL_LCD_LINE_3, no, ch);
            }
            no++;
            if (no >= 32)
            {
                halBuzzer(300);
                halLcdClearLine(HAL_LCD_LINE_3);
                halLcdClearLine(HAL_LCD_LINE_4);
                no = 0;             
            }
            halMcuWaitMs(200);
          
          halLcdWriteChar(HAL_LCD_LINE_2, 11, ch);
          write[0] = ch;
          write[1]= 0x0D;
          write[2]= 0x0A;
          halUartWrite(write,3);
          
          ch = halUartRxLen();
          if (ch > 0)
          {
            if (ch > 16)
            {
                ch = 16;
            }
            halUartRead(read, ch);
            read[ch] = 0;
            halLcdWriteLine(HAL_LCD_LINE_3, (char*)read);
          }
        }
        halMcuWaitMs(10);
    }
}

