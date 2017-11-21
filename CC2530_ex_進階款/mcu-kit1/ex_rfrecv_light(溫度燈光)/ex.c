//-------------------------------------------------------------------
// Filename: ex.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_uart.h"
#include "hal_buzzer.h"
#include "hal_led.h"
#include "hal_rf.h"
#include "util.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "M160.h"


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
//-------------------------------------------------------------------
void main(void)
{
    uint8 len, val;
    
    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // Initalise board peripherals
    halBoardInit();
    halLedSet(8);

    // Print Logo and splash screen on LCD
    utilPrintLogo("* Rf Recv Uart *");
    //halBuzzer(300);
    halMcuWaitMs(1000);
    halLcdClear();
    halLcdWriteLine(HAL_LCD_LINE_1, "* Light Detect *");
    halLcdWriteLine(HAL_LCD_LINE_2, "* Temp =      C*");

    // Initialize BasicRF
    basicRfConfig.myAddr = RECV_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED)
    {
        HAL_ASSERT("RfConfig Error!");
    }
    basicRfReceiveOn();

    // Main loop
    M160_Init();
    while (TRUE)
    {
        while (!basicRfPacketIsReady())
        {
            uint8 key;
            key = halKeypadPushed();
            if (key == '*')
            {
              return ;
            }
        }

        len = basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL);
        
        if(len>0)
        {  
              
          val = (pRxData[0] - '0') * 10 + (pRxData[1] - '0');
              
              if(val > 28)
              {
                M160_On(80);
                halBuzzer(300);
                halLcdDisplayUint8(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, val);
              }
              else
              {
               M160_Off();
               halLcdDisplayUint8(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, val);
              }
            
        }
            //halBuzzer(30);
        
            halMcuWaitMs(50);
        
            //halLcdWriteLine(HAL_LCD_LINE_2, (char*)pRxData);
            pRxData[len++]=' ';
            halUartWrite(pRxData,len);
                 
    }
}
