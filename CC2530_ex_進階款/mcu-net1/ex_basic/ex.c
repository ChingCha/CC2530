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
#include "M180.h"
#include "M190.h"
#include "M240.h"
#include "hal_relay.h"
#include "hal_rtc.h"

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
    uint16 val=0, udi, m180;
    uint8  dutyR, dutyG, dutyB;
    uint8  udo=0;
    uint8 buf[30];

    // Initalise board peripherals
    halBoardInit();

    // Main loop
    while (TRUE)
    {
        // Indicate that device is powered
        halBuzzer(300);
        
        M180_Init();
        M180_Enable();
        M190_Init();
        M240_Init();
        RELAY_Init();
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
          // M190 and M240 control
          val = M190_GetValue();
          
          if(val > 20000)
          {
            dutyR = 0;
            dutyG = 0;
            dutyB = 100;
            M240_LEDR_On(dutyR);
            M240_LEDG_On(dutyG);
            M240_LEDB_On(dutyB);
          }
          if(val < 10000)
          {
            dutyR = 0;
            dutyG = 100;
            dutyB = 0;
            M240_LEDR_On(dutyR);
            M240_LEDG_On(dutyG);
            M240_LEDB_On(dutyB);
          }

          //Relay control
          udi = RELAY_GetDI();
          
           if ((udi &0x01) == 0x00)
            {
                udo = 1;
                RELAY_SetDO(udo);
            }
            if ((udi &0x02) == 0x00)
            {
                udo = 0;
                RELAY_SetDO(udo);
            }
          
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
            buf[12] = ',';
          
            // M180 control
            m180 = M180_GetValue();
            
            buf[13] = (m180 / 1000) + '0';
            buf[14] = (m180 / 100) + '0';
            buf[15] = (m180 / 10) % 10 + '0';
            buf[16] = (m180 % 10) + '0';
            buf[17]= 0x0D;
            buf[18]= 0x0A;
            
            halUartWrite(buf, 19);
            halMcuWaitMs(300);
        }
    }
}
