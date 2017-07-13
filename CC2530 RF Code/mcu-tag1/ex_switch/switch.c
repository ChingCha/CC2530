//-------------------------------------------------------------------
// Filename: switch.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_int.h"
#include "hal_button.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "basic_rf.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters

#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                0x1111
#define SWITCH_ADDR           0x2222
#define LIGHT_ADDR            0x3333
#define APP_PAYLOAD_LENGTH        127
#define LIGHT1_TOGGLE_CMD         '1'
#define LIGHT2_TOGGLE_CMD         '2'

// Application states
#define IDLE                      0
#define SEND_CMD                  1


//-------------------------------------------------------------------
//LOCAL FUNCTIONS
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------

#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif


//-------------------------------------------------------------------
// @fn          appSwitch
// @brief       Application code for switch application. Puts MCU in
//              endless loop to wait for commands from switch.
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pTxData - file scope variable. Pointer to buffer for TX
//              payload
//              appState - file scope variable. Holds application state
// @return      none
// @?¡æ??ˆè?å®??
//-------------------------------------------------------------------
static uint8 pTxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

void appSwitch1(int drinkw);
void appSwitch2(int drinkm);

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "portion" application.
// @return      none
//-------------------------------------------------------------------
int main()
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

	int32 water = 5;
	int32 milk = 9;
	
	// Initialize BasicRF
    basicRfConfig.myAddr = SWITCH_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // Keep Receiver off when not needed to save power
    basicRfReceiveOff();
	
	while (1)
    {
        uint8 v = halButtonPushed();
		if (v == HAL_BUTTON_2){
            if(water > 0)
				water--;
			halLcdDisplayWithButton(HAL_LCD_LINE_1,'W',water);
			appSwitch1(water);				
		}
		else if(v == HAL_BUTTON_1){
			if(milk > 0)
				milk--;
			halLcdDisplayWithButton(HAL_LCD_LINE_2,'M',milk);
			appSwitch2(milk);
		}
        halMcuWaitMs(100);    
    }
	return 0;
}

void appSwitch1(int drinkw){
	
    // Main loop 
    do{
		pTxData[0] = LIGHT1_TOGGLE_CMD;
		pTxData[1] = drinkw;
		
        basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        halLedToggle(1);
        halLedToggle(2);
        halLedToggle(3);
        halBuzzer(100);
        halMcuWaitMs(200);
        halLedToggle(7);
	}while (drinkw<0);
}

void appSwitch2(int drinkm){

	
    // Main loop
    do{
		pTxData[0] = LIGHT2_TOGGLE_CMD;
		pTxData[1] = drinkm;
		
		basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
		halLedToggle(4);
		halLedToggle(5);
		halLedToggle(6);
		halBuzzer(300);
		halMcuWaitMs(200);
        halLedToggle(7);
	}while (drinkm<0);
}
