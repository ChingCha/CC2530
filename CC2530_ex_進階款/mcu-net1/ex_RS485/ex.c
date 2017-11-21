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
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_uart.h"
#include "hal_relay.h"
#include "hal_buzzer.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                12      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                    0x1111
#define SEND_ADDR                 0x2222
#define RECV_ADDR                 0x0000

#define APP_PAYLOAD_LENGTH        20
#define RS485_PAYLOAD_LEN         20

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
// The RF transmit variable
static uint8 pTxData[APP_PAYLOAD_LENGTH];
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif 

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "RS485" application.
//-------------------------------------------------------------------
void main(void)
{ 
  // The RS485 transmit variable
  uint8 RX_buf[32];
  uint8 len; 

  // Config basicRF
  basicRfConfig.panId = PAN_ID;
  basicRfConfig.channel = RF_CHANNEL;
  basicRfConfig.ackRequest = TRUE;
  #ifdef SECURITY_CCM
    basicRfConfig.securityKey = key;
  #endif 
   
   // Initalise board peripherals
   halBoardInit();
   halBuzzer(300);
   
   basicRfConfig.myAddr = SEND_ADDR;
   if (basicRfInit(&basicRfConfig) == FAILED){}
   
   while(TRUE)
      {
        len = halUartRxLen();
        halUartRead(RX_buf, len);
        if (len > 0)
        {
          for(uint8 cnt=0;cnt<len;cnt++)
          {
            pTxData[cnt] = RX_buf[cnt];
          }
          basicRfSendPacket(RECV_ADDR, pTxData,len);
        }
      }
}
