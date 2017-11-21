//-------------------------------------------------------------------
// Filename: ex.c
// Description: ·Å«×°»´ú(SPI)½d¨Ò 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_buzzer.h"
#include "hal_button.h"
#include "hal_led.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_uart.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                18     // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                    0x1111
#define SEND_ADDR                 0x2222
#define RECV_ADDR                 0x0000
#define APP_PAYLOAD_LENGTH        32

// Application states
#define IDLE                      0
#define SEND_CMD                  1

#define VOLTAGE           64
#define AMP               32
#define KW                16

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
//static uint8 pTxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif 


//-------------------------------------------------------------------
void main(void)
{
//    uint16 val;
    uint8 pBuffer[9];
    uint8 temp=48;
    uint8 pBuf[7];
    
    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // Initalise board peripherals
    halBoardInit();
    
    // Initilization PA-2591
    halPAInit();

    // Indicate that device is powered
    halLedSet(8);
    
    // Print Logo and splash screen on LCD
    halMcuWaitMs(300);
    halBuzzer(300);
    
    basicRfConfig.myAddr = SEND_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}
    
    while (TRUE)
    {
//      while( halUartRxLen()<8)
//      {   
//       halMcuWaitMs(1000);
//       halUartWrite(&temp, 1);
//      };

       halUartWrite(&temp, 1);
      
       halUartRead( pBuffer, 9);       
//       switch(pBuffer[1])
//       {
//          case VOLTAGE:
//             pBuf[5]='V';
//             break;
//          case AMP:
//             pBuf[5]='A';
//             break;
//          case KW:
//             pBuf[5]='W';
//             break;
//          default:
//             break;
//       }
//       
       pBuf[0]=((pBuffer[2] & 0xf0)>>4)+48;
       trans[0] = pBuf[0];
       pBuf[1]=(pBuffer[2] & 0x0f)+48;
       pBuf[2]=((pBuffer[3] &0xf0)>>4)+48;
       pBuf[3]='.';
       pBuf[4]=(pBuffer[3] & 0x0f)+ 48;
       pBuf[6]=0 + '0';
       
       basicRfSendPacket(RECV_ADDR,trans,7);
       halMcuWaitMs(20);
       
    }
}
