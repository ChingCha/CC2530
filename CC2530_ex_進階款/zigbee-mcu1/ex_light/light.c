//-------------------------------------------------------------------
// Filename: light.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_button.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "basic_rf.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                25      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                0x2007
#define SWITCH_ADDR           0x2520
#define LIGHT_ADDR            0xBEEF
#define APP_PAYLOAD_LENGTH        1
#define LIGHT1_TOGGLE_CMD         '1'
#define LIGHT2_TOGGLE_CMD         '2'

// Application states
#define IDLE                      0
#define SEND_CMD                  1

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
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
// @fn          appLight
// @brief       Application code for light application. Puts MCU in endless
//              loop waiting for user input from switch.
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pRxData - file scope variable. Pointer to buffer for RX data
// @return      none
//-------------------------------------------------------------------
static void appLight()
{
    // Initialize BasicRF
    basicRfConfig.myAddr = LIGHT_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // Keep Receiver on
    basicRfReceiveOn();

    // Main loop
    while (TRUE)
    {
        while (!basicRfPacketIsReady())
        {
            halLedToggle(7);
            halMcuWaitMs(20);
        }
        if (basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
        {
            if (pRxData[0] == LIGHT1_TOGGLE_CMD)
            {
                halLedToggle(1);
                halLedToggle(2);
                halLedToggle(3);
                halBuzzer(300);
            }
            if (pRxData[0] == LIGHT2_TOGGLE_CMD)
            {
                halLedToggle(4);
                halLedToggle(5);
                halLedToggle(6);
                halBuzzer(300);
            }
        }
    }
}

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "portio" application.
// @return      none
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
    halBuzzer(300);

    //Enter Light mode
    appLight();

}
