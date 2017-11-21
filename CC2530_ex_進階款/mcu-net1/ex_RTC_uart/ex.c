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
#include "hal_relay.h"

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
    uint8 buf[12];
  
    // Initalise board peripherals
    halBoardInit();

    while(TRUE)
    {
      // Indicate that device is powered
      halBuzzer(300); 
      
      RTC_Init();
      GetDateTime();
      if(Year<2009)
      {
        Year = 2010;
        Month = 1;
        Day = 1;
        Hour = 12;
        Min = 0;
        Sec = 0;
        SetDateTime();
      }
      
      while(TRUE)
      {
         // RTC control
         GetDateTime();
         buf[0] = ((Year / 10) % 10) + '0';
         buf[1] = (Year % 10) + '0';
         buf[2] = (Month / 10) + '0';
         buf[3] = (Month % 10) + '0';
         buf[4] = (Day / 10) + '0';
         buf[5] = (Day % 10) + '0';
         buf[6] = (Hour / 10) + '0';
         buf[7] = (Hour % 10) + '0';
         buf[8] = (Min / 10) + '0';
         buf[9] = (Min % 10) + '0';
         buf[10] = (Sec / 10) + '0';
         buf[11] = (Sec % 10) + '0';
         
         halUartWrite(buf, 12);
         halMcuWaitMs(300);
      }
    }
    
    

}
