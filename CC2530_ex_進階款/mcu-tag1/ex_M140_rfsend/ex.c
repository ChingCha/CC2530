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
#include "M140.h"

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
    
    M140_Init();
    while (TRUE)
    {
        halMcuWaitMs(200);
        halLedToggle(7);
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

        pTxData[0]= (val / 100) + '0';
        pTxData[1]= ((val / 10) % 10) + '0';
        pTxData[2]= '.';
        pTxData[3]= (val % 10) + '0';
        basicRfSendPacket(RECV_ADDR, pTxData,4);

        uint8 v = halButtonPushed();
        if (v == HAL_BUTTON_2)
        {
            pTxData[0] = 'S';
            pTxData[1] = '2';
            basicRfSendPacket(RECV_ADDR, pTxData,2);
            halLedToggle(1);
            halBuzzer(300);
            halMcuWaitMs(200);
        }
        if (v == HAL_BUTTON_1)
        {
            pTxData[0] = 'S';
            pTxData[1] = '1';
            basicRfSendPacket(RECV_ADDR, pTxData,2);
            halLedToggle(2);
            halBuzzer(300);
            halMcuWaitMs(200);
        }
    }
}
