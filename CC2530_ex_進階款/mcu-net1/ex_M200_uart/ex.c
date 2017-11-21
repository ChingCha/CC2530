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
#include "M200.h"

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
    uint8 buf[10];
    uint16 temp, humi;
     
    // Initalise board peripherals
    halBoardInit();

     while (TRUE)
    {
      // Indicate that device is powered
      M200_Init();
      halBuzzer(300);
        
        while (TRUE)
        {
            M200_GetValue();
            temp = (uint16)(((((float)M200_Temp) *0.01) - 40.0) *10.0);
            humi = (uint16)(((((float)M200_Humi) *0.0405) - (((float)M200_Humi)*((float)M200_Humi) *0.0000028) - 4.0) *10.0);

            if (humi > 999)
            {
                humi = 999;
            }
            if (temp > 999)
            {
                temp = 999;
            }
            buf[0] = (humi / 100) + '0';
            buf[1] = ((humi / 10) % 10) + '0';
            buf[2] = '.';
            buf[3] = (humi % 10) + '0';
            buf[4] = ' ';
            buf[5] = (temp / 100) + '0';
            buf[6] = ((temp / 10) % 10) + '0';
            buf[7] = '.';
            buf[8] = (temp % 10) + '0';
            
            halUartWrite(buf, 9); 
            
            halMcuWaitMs(300);

        }
    }

}
