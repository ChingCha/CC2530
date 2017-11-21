//-------------------------------------------------------------------
// Filename: ex.c
// Description: ¤ß¹q¹Ï(A/D)½d¨Ò
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
#include "M430.h"

//-------------------------------------------------------------------
void main(void)
{
   uint16 val;
   uint16 valold;
   uint16 Count;
   uint16 Count_1,Count_2,Count_d;
  
    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M430 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);  
    valold=0;
    while (TRUE)
    {
        halLcdClear();
        halBuzzer(300);
        
        TIMER4_Init();
        M430_Init();
        
        halLcdWriteLine(HAL_LCD_LINE_1, "ADC Val :       ");
        halLcdWriteLine(HAL_LCD_LINE_2, "ECG :           ");
        
        Count_2 = 0;
        
        while (TRUE)
        {   
            TIMER4_On();      
            val = M430_GetValue();
            if(val > (valold + 30)) // 30 is value range
            {
                Count = M430_Count; /* The high point value count */
                M430_Count = 0;
                
                Count_1 = 4724 / (Count / 100); 
                
                if(Count_1 > Count_2)
                {
                  Count_d = Count_1 - Count_2;
                }
                else
                {
                  Count_d = Count_2 - Count_1;
                }
                if(Count_d < 10 && Count_1 > 30 && Count_1 < 160)
                {                
                  halLcdDisplayUint16(HAL_LCD_LINE_1, 10, HAL_LCD_RADIX_DEC, val);
                  halLcdDisplayUint16(HAL_LCD_LINE_2, 6, HAL_LCD_RADIX_DEC, Count_1);
                }
                Count_2 = Count_1; 
                halMcuWaitMs(200);
            }
            valold = (valold + val) / 2;
        }
    }
}