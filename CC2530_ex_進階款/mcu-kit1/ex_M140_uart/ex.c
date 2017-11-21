//-------------------------------------------------------------------
// Filename: ex.c
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
#include "M140.h"

//-------------------------------------------------------------------
// @fn          main
//-------------------------------------------------------------------
void main(void)
{
    uint8 ch;
    uint8 buf[20];
    uint16 val;
    
    // Initalise board peripherals
    halBoardInit();
    // Indicate that device is powered
    halLedSet(8);

    // Print Logo and splash screen on LCD
    utilPrintLogo("M140<->NET/RS232");
    halBuzzer(300);
    
    M140_Init();
    buf[0] = '0';
    buf[1] = '0';
    buf[2] = '0';
    buf[3] = '0';
    buf[4] = '0';
    while (TRUE)
    {
        val = M140_GetValue();
        if ((0x2000 &val) == 0x2000)
        //Check sign bit for negative value.
        {
            val = ((val - 16384) *10) / 32;
        }
        else
        {
            val = (val *10) / 32;
        }

        buf[0]= ' ';
        buf[1]= (val / 100) + '0';
        buf[2]=((val / 10) % 10) + '0';
        buf[3]= '.';
        buf[4]=(val % 10) + '0';
        buf[5]= 0x0D;
        buf[6]= 0x0A;
      
        halUartWrite(buf,7);
        
        halLcdWriteLine(HAL_LCD_LINE_2, " Temp. =       C");
        halLcdWriteChar(HAL_LCD_LINE_2, 14, 0xDF);
        halLcdWriteChar(HAL_LCD_LINE_2, 9, (val / 100) + '0');
        halLcdWriteChar(HAL_LCD_LINE_2, 10, ((val / 10) % 10) + '0');
        halLcdWriteChar(HAL_LCD_LINE_2, 11, '.');
        halLcdWriteChar(HAL_LCD_LINE_2, 12, (val % 10) + '0');
        halMcuWaitMs(300);
        
        
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

