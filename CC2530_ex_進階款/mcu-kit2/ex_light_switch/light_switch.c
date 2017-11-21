//-------------------------------------------------------------------
// Filename: light_switch.c
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

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                25 // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                0x2007
#define SWITCH_ADDR           0x2520
#define LIGHT_ADDR            0xBEEF
#define APP_PAYLOAD_LENGTH        1
#define LIGHT1_TOGGLE_CMD        '1'
#define LIGHT2_TOGGLE_CMD        '2'

// Application states
#define IDLE       0
#define SEND_CMD   1

// Application role
#define NONE       0
#define SWITCH     1
#define LIGHT      2
#define APP_MODES  2

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
static uint8 pTxData[APP_PAYLOAD_LENGTH];
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;
static uint8 pLight1Status;
static uint8 pLight2Status;

// Mode menu
static menuItem_t pMenuItems[] = { "Switch", SWITCH, "Light", LIGHT };

static menu_t pMenu = { pMenuItems, N_ITEMS(pMenuItems) };


#ifdef SECURITY_CCM
    static uint8 key[] = // Security key
    { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, };
#endif 

//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn          appLight
// @brief       Application code for light application. Puts MCU in endless
//              loop waiting for user input from joystick.
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pRxData - file scope variable. Pointer to buffer for RX data
// @return      none
//-------------------------------------------------------------------
void appLight()
{
    pLight1Status=0;
    pLight2Status=0;
    halLedClear(1);
    halLedClear(2);
    halLedClear(3);
    halLedClear(4);
    halLedClear(5);
    halLedClear(6);
    halLcdWriteLine(HAL_LCD_LINE_1, "Light Off");
    halLcdWriteLine(HAL_LCD_LINE_2, "Esc[*]");

    // Initialize BasicRF
    basicRfConfig.myAddr = LIGHT_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED)
    {
        HAL_ASSERT("RfConfig Error!");
    }
    basicRfReceiveOn();

    // Main loop
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

        if (basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
        {
            if (pRxData[0] == LIGHT1_TOGGLE_CMD)
            {
                halBuzzer(300);
                if(pLight1Status==0)
                {
                    pLight1Status=1;
                    halLedSet(1);
                    halLedSet(2);
                    halLedSet(3);
                    halLcdWriteLine(HAL_LCD_LINE_1, "Light 1 On");
                }
                else
                {
                    pLight1Status=0;
                    halLedClear(1);
                    halLedClear(2);
                    halLedClear(3);
                    halLcdWriteLine(HAL_LCD_LINE_1, "Light 1 Off");
                }
            }
            if (pRxData[0] == LIGHT2_TOGGLE_CMD)
            {
                halBuzzer(300);
                if(pLight2Status==0)
                {
                    pLight2Status=1;
                    halLedSet(4);
                    halLedSet(5);
                    halLedSet(6);
                    halLcdWriteLine(HAL_LCD_LINE_1, "Light 2 On");
                }
                else
                {
                    pLight2Status=0;
                    halLedClear(4);
                    halLedClear(5);
                    halLedClear(6);
                    halLcdWriteLine(HAL_LCD_LINE_1, "Light 2 Off");
                }
            }
        }
    }
}

//-------------------------------------------------------------------
// @fn          appSwitch
// @brief       Application code for switch application. Puts MCU in
//              endless loop to wait for commands from from switch
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pTxData - file scope variable. Pointer to buffer for TX
//              payload
//              appState - file scope variable. Holds application state
// @return      none
//-------------------------------------------------------------------
void appSwitch()
{
    halLcdWriteLine(HAL_LCD_LINE_1, "Switch[1][2]");
    halLcdWriteLine(HAL_LCD_LINE_2, "Esc[*]");

    // Initialize BasicRF
    basicRfConfig.myAddr = SWITCH_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED)
    {
        HAL_ASSERT("RfConfig Error!");
    }

    // Keep Receiver off when not needed to save power
    basicRfReceiveOff();

    // Main loop
    while (TRUE)
    {
        uint8 key;
        key = halKeypadPushed();
        if (key == '1')
        {
            pTxData[0] = LIGHT1_TOGGLE_CMD;
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            halMcuWaitMs(200);
        }
        if (key == '2')
        {
            pTxData[0] = LIGHT2_TOGGLE_CMD;
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            halMcuWaitMs(200);
        }
        if (key == '*')
        {
            break;
        }
    }
}

//-------------------------------------------------------------------
// @fn          appSelectMode
// @brief       Select application mode
// @param       none
// @return      uint8 - Application mode chosen
//-------------------------------------------------------------------
uint8 appSelectMode(void)
{
    halLcdWriteLine(HAL_LCD_LINE_1, "Device Mode:");
    return utilMenuSelect(&pMenu);
}

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "Light Switch" application.
//              After the application modes are chosen the switch can
//              send toggle commands to a light device.
// @param       basicRfConfig - file scope variable. Basic RF configuration
//              data
//              appState - file scope variable. Holds application state
// @return      none
//-------------------------------------------------------------------
void main(void)
{
    uint8 appMode = NONE;

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
    halLcdDrawLogo();
    halBuzzer(300);
    while(halKeypadPushed()==0);
    
    // Print Logo and splash screen on LCD
    utilPrintLogo("Light Switch");
    halLcdWriteLine(HAL_LCD_LINE_3, "Change[Up][Down]");
    halLcdWriteLine(HAL_LCD_LINE_4, "Select[#]");
    halMcuWaitMs(1500);
    halBuzzer(300);
    halLcdClear();

    while (1)
    {
        // Set application role
        appMode = appSelectMode();
        halLcdClear();

        // Transmitter application
        if (appMode == SWITCH)
        {
            // No return from here
            appSwitch();
        }
        // Receiver application
        else if (appMode == LIGHT)
        {
            // No return from here
            appLight();
        }
    }
}

