//-------------------------------------------------------------------
// Filename: ex.c
// Description: �_�ʰ���(SPI)�d�� 
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
#include "M180.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                    0x1111
#define SEND_ADDR                 0x2222
#define RECV_ADDR                 0x3333
#define APP_PAYLOAD_LENGTH        32

// Application states
#define IDLE                      0
#define SEND_CMD                  1

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
static uint8 pTxData[APP_PAYLOAD_LENGTH];
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
    uint16 val;

    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    // Print Logo and splash screen on LCD
    halMcuWaitMs(300);
    halBuzzer(300);
    
    basicRfConfig.myAddr = SEND_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}
    
    
        
   
   
    

    while (TRUE)
    {
        halMcuWaitMs(200);
        halLedToggle(7);
        M180_Init();
        M180_Enable();
        
        while (TRUE)
        {
        val = M180_GetValue();
        pTxData[0]= val + '0';
        basicRfSendPacket(RECV_ADDR, pTxData,1);
        }
         //M180_Disable();
         val = 1;
         pTxData[0]= val + '0';
         basicRfSendPacket(RECV_ADDR, pTxData,1);
    } 
    
          
}

