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
// @fn          main
// @brief       This is the main entry of the "portio" application.
// @return      none
//-------------------------------------------------------------------
void main(void)
{
    uint8 len, oldsec;
    uint8 buf[32];

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

    halBuzzer(300);

    // Initialize BasicRF
    basicRfConfig.myAddr = RECV_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED)
    {
        HAL_ASSERT("RfConfig Error!");
    }
    basicRfReceiveOn();

    GetDateTime();
    if (Year < 2009)
    {
        Year = 2010;
        Month = 1;
        Day = 1;
        Hour = 12;
        Min = 0;
        Sec = 0;
        SetDateTime();
    }

    // Main loop
    while (TRUE)
    {
        while (!basicRfPacketIsReady())
        {
            GetDateTime();
            if (Sec != oldsec)
            {
                oldsec = Sec;
                buf[0] = '2';
                buf[1] = '0';
                buf[2] = ((Year / 10) % 10) + '0';
                buf[3] = (Year % 10) + '0';
                buf[4] = '/';
                buf[5] = (Month / 10) + '0';
                buf[6] = (Month % 10) + '0';
                buf[7] = '/';
                buf[8] = (Day / 10) + '0';
                buf[9] = (Day % 10) + '0';
                buf[10] = ' ';
                buf[11] = (Hour / 10) + '0';
                buf[12] = (Hour % 10) + '0';
                buf[13] = ':';
                buf[14] = (Min / 10) + '0';
                buf[15] = (Min % 10) + '0';
                buf[16] = ':';
                buf[17] = (Sec / 10) + '0';
                buf[18] = (Sec % 10) + '0';
                buf[19] = ' ';
                buf[20] = 0x0D;

                HAL_RS485_SET_TX();
                halMcuWaitUs(500);
                halUartWrite(buf, 21);
                halMcuWaitUs(100);
                HAL_RS485_SET_RX();

                halBuzzer(10);
            }
        }

        if (len = basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
        {
            halBuzzer(30);
            pRxData[len++] = ' ';
            pRxData[len++] = 0x0D;
            HAL_RS485_SET_TX();
            halMcuWaitUs(500);
            halUartWrite(pRxData, len);
            halMcuWaitUs(100);
            HAL_RS485_SET_RX();
        }
    }

}
