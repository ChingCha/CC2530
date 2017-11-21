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
     uint8  udo=0;
     uint16 udi;
     uint8 buf[10];
    
    // Initalise board peripherals
    halBoardInit();

    while(TRUE)
    {
      // Indicate that device is powered
      halBuzzer(300);
      RELAY_Init();
      
      while(TRUE)
      {
        //Relay control
        udi = RELAY_GetDI();
          
        if ((udi &0x01) == 0x00)
        {
          udo = 1;
          RELAY_SetDO(udo);
          buf[0] = 'R';
          buf[1] = 'E';
          buf[2] = 'L';
          buf[3] = 'A';
          buf[4] = 'Y';
          buf[5] = '-';
          buf[6] = '1';
          buf[7] = ' ';
          buf[8] = 'O';
          buf[9] = 'N';
          halUartWrite(buf, 10);
          halMcuWaitMs(100);
          for(uint8 i = 0; i < 11; i++)
          {
            buf[i] = 0;
          }
        }
        
        
        if ((udi &0x02) == 0x00)
        {
          udo = 0;
          RELAY_SetDO(udo);
          buf[0] = 'R';
          buf[1] = 'E';
          buf[2] = 'L';
          buf[3] = 'A';
          buf[4] = 'Y';
          buf[5] = '-';
          buf[6] = '2';
          buf[7] = ' ';
          buf[8] = 'O';
          buf[9] = 'N';
          halUartWrite(buf, 10);
          halMcuWaitMs(100);
          for(uint8 i = 0; i < 11; i++)
          {
            buf[i] = 0;
          } 
        }
      }
    }
}
