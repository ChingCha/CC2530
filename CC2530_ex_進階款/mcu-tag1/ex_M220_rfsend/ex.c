//-------------------------------------------------------------------
// Filename: ex.c
// Description: ¾_°Ê°»´ú(SPI)½d¨Ò 
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
#include "M220.h"

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
    //halMcuWaitMs(300);
    //halBuzzer(300);
    
    basicRfConfig.myAddr = SEND_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}
    
    M220_Init();
    while (TRUE)
    {
        halMcuWaitMs(300);
        halLedToggle(7);
   
        M220_Pooling();
        if ((M220_X_AXIS_Value &0x8000) == 0x8000)
        {
            M220_X_AXIS_Value = 65535-M220_X_AXIS_Value;
            pTxData[0]= '-';
        }
        else
        {
            pTxData[0]= '+';
        }
        //pTxData[1]= (M220_X_AXIS_Value / 10000) + '0';
        //pTxData[2]= ((M220_X_AXIS_Value / 1000) % 10) + '0';
        pTxData[1]= ((M220_X_AXIS_Value / 100) % 10) + '0';
        pTxData[2]= ((M220_X_AXIS_Value / 10) % 10) + '0';
        pTxData[3]= (M220_X_AXIS_Value % 10) + '0';
        pTxData[4]= ' ';

        if ((M220_Y_AXIS_Value &0x8000) == 0x8000)
        {
            M220_Y_AXIS_Value = 65535-M220_Y_AXIS_Value;
            pTxData[5]= '-';
        }
        else
        {
            pTxData[5]= '+';
        }
        //pTxData[8]= (M220_Y_AXIS_Value / 10000) + '0';
        //pTxData[9]= ((M220_Y_AXIS_Value / 1000) % 10) + '0';
        pTxData[6]= ((M220_Y_AXIS_Value / 100) % 10) + '0';
        pTxData[7]= ((M220_Y_AXIS_Value / 10) % 10) + '0';
        pTxData[8]= (M220_Y_AXIS_Value % 10) + '0';
        pTxData[9]= ' ';

        if ((M220_Z_AXIS_Value &0x8000) == 0x8000)
        {
            M220_Z_AXIS_Value = 65535-M220_Z_AXIS_Value;
            pTxData[10]= '-';
        }
        else
        {
            pTxData[10]= '+';
        }
        //pTxData[15]= (M220_Z_AXIS_Value / 10000) + '0';
        //pTxData[16]= ((M220_Z_AXIS_Value / 1000) % 10) + '0';
        pTxData[11]= ((M220_Z_AXIS_Value / 100) % 10) + '0';
        pTxData[12]= ((M220_Z_AXIS_Value / 10) % 10) + '0';
        pTxData[13]= (M220_Z_AXIS_Value % 10) + '0';

        basicRfSendPacket(RECV_ADDR, pTxData, 14);

        
    }
}
