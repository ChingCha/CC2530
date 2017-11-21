//-------------------------------------------------------------------
// Filename: ex.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_board.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_rtc.h"
#include "hal_buzzer.h"
#include "hal_uart.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "M170.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "portio" application.
//-------------------------------------------------------------------
void main(void)
{
    uint16 val;
    uint8 buf[3];
    
    // Initalise board peripherals
    halBoardInit();

     while (TRUE)
    {
      // Indicate that device is powered
      M170_Init();
      halBuzzer(300);
        
        while (TRUE)
        {
            val = M170_GetValue();
            
            if (val > 2000)
            {
                val -= 2000;
            }
            else
            {
                val = 0;
            }
            val /= 120;
            if (val > 100)
            {
                val = 100;
            }
            
            buf[0] = (val / 100) + '0';
            buf[1] = (val / 10) % 10 + '0';
            buf[2] = (val % 10) + '0';
            
            halUartWrite(buf, 3); 
            
            halMcuWaitMs(300);

        }
    }

}
