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
//#include "M160.h"
#include "M280.h"


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
    uint8 len, temp, humi, light;
    
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
    halLcdWriteLine(HAL_LCD_LINE_1, "** Garden **");
    halLcdWriteLine(HAL_LCD_LINE_2, "H=   T=   L=   ");

    // Initialize BasicRF
    basicRfConfig.myAddr = RECV_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED)
    {
        HAL_ASSERT("RfConfig Error!");
    }
    basicRfReceiveOn();

    // Main loop
    //M160_Init();
    M280_Init();
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
          
          humi = pRxData[0];
          temp = pRxData[1];
          light = pRxData[2];
        
          
          if (light>70)
          {
           M280_CW(75);
           halLcdDisplayUint8(HAL_LCD_LINE_2, 2, HAL_LCD_RADIX_DEC, humi);
           halLcdDisplayUint8(HAL_LCD_LINE_2, 7, HAL_LCD_RADIX_DEC, temp); 
           halLcdDisplayUint8(HAL_LCD_LINE_2, 12, HAL_LCD_RADIX_DEC, light);

          }
          else
          {
            M280_CCW(75);
            halLcdDisplayUint8(HAL_LCD_LINE_2, 2, HAL_LCD_RADIX_DEC, humi);
            halLcdDisplayUint8(HAL_LCD_LINE_2, 7, HAL_LCD_RADIX_DEC, temp);
            halLcdDisplayUint8(HAL_LCD_LINE_2, 12, HAL_LCD_RADIX_DEC, light);
          }

          
          
              
            
        }
            
        
            halMcuWaitMs(50);
            pRxData[len++]=' ';
            halUartWrite(pRxData,len);
                
    }
}
