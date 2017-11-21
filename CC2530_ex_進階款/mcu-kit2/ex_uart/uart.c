//-------------------------------------------------------------------
// Filename: uart.c
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
#include "hal_uart.h"
#include "hal_buzzer.h"
#include "hal_led.h"
#include "util.h"
#include "util_lcd.h"



//-------------------------------------------------------------------
void main(void)
{
    uint8 ch, no;
    uint8 buf[20];
    
    // Initalise board peripherals
    halBoardInit();
    // Indicate that device is powered
    halLedSet(8);
    halLcdDrawLogo();
    halBuzzer(300);
    while(halKeypadPushed()==0);

    halLcdClear();
    // Print Logo and splash screen on LCD
    utilPrintLogo("UART<->NET/RS232");
    halLcdWriteLine(HAL_LCD_LINE_3, "Press[#] to Send");
    no = 0;
    
    
    
    while (TRUE)
    {
        ch = halKeypadPushed();
        if (ch > 0)
        {
            if (ch == '#')
            {
                halUartWrite(buf,no);
                halMcuWaitMs(200);
                no=0;
                halLcdWriteLine(HAL_LCD_LINE_4, "");
            }
            else
            {
                halLcdWriteChar(HAL_LCD_LINE_4, no, ch);
                buf[no] = ch;
                no++;
                if(no>=16)
                {
                    halUartWrite(buf,no);
                    halMcuWaitMs(200);
                    no=0;
                    halLcdWriteLine(HAL_LCD_LINE_4, "");
                }
            }
            halMcuWaitMs(200);
        }
        ch = halUartRxLen();
        if (ch > 0)
        { 
            /*
            if (ch > 16)
            {
                ch = 16;
            }
            halUartRead(buf, ch);
            buf[ch] = 0;
            halLcdWriteLine(HAL_LCD_LINE_4, (char*)buf);
            */
            halMcuWaitMs(50);
            if (ch > 8)
            {
                ch = 8;
            }
            halUartRead(buf, ch);
            buf[ch] = 0;
            halLcdClearLine(HAL_LCD_LINE_4);
            for(uint8 i=0;i<ch;i++)
            {
                halLcdDisplayUint8(HAL_LCD_LINE_4, i*2,HAL_LCD_RADIX_HEX,buf[i]);              
            }
            no=0;
        }
        //halMcuWaitMs(10);
    }    

}

