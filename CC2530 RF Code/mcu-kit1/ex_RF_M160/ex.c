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
#include "hal_lcd.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_button.h"
#include "M160.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                	0x1111

	// A Vending Machine
	#define AVM_ADDR           		0x2222
	#define AVM_WATER         		'1'
	#define AVM_MILK         		'2'

	// B Vending Machine
	#define BVM_ADDR           		0x2233
	#define BVM_GREENTEA     		'3'					//B販賣機飲品(水)的辨識碼
	#define BVM_BLACKTEA     		'4'					//B販賣機飲品(牛奶)的辨識碼
	
	
#define VM_ONE_ADDR            	0x3333
#define APP_PAYLOAD_LENGTH        127


// Application states
#define IDLE                      0
#define SEND_CMD                  1

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
// @			先行宣告函數區
// @fn          appLight
// @brief       Application code for light application. Puts MCU in endless
//              loop waiting for user input from switch.
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pRxData - file scope variable. Pointer to buffer for RX data
// @return      none
//-------------------------------------------------------------------
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

void A_water(int A_drinkw);
void A_milk(int A_drinkm);
void B_greentea(int B_drinkg);		//B販賣機飲品(綠茶)的功能
void B_blacktea(int B_drinkb);		//B販賣機飲品(紅茶)的功能


//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "portio" application.
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
    halLcdInit();

    // Indicate that device is powered
    halLedSet(8);
    halBuzzer(300);
	
	// Initialize BasicRF
    basicRfConfig.myAddr = VM_ONE_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // Keep Receiver on
    basicRfReceiveOn();
	
	while(1){

		while (!basicRfPacketIsReady()){
            halLedToggle(7);
            halMcuWaitMs(10);
        }
		
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
			
			if(pRxData[0] == AVM_WATER)
				A_water(pRxData[1]);
	
			if(pRxData[0] == AVM_MILK)
				A_milk(pRxData[1]);
			
			if(pRxData[0] == BVM_GREENTEA)
				B_greentea(pRxData[1]);
			
			if(pRxData[0] == BVM_BLACKTEA)
				B_blacktea(pRxData[1]);
			
		}	
	}
	
	return 0;
}

//-------------------------------------------------------------------
// @函數定義區
//-------------------------------------------------------------------
void A_water(int A_drinkw){
	halLcdDisplayWithAVM(HAL_LCD_LINE_1,'W',A_drinkw);
}

void A_milk(int A_drinkm){
	halLcdDisplayWithAVM(HAL_LCD_LINE_2,'M',A_drinkm);
}
void B_greentea(int B_drinkg){
	halLcdDisplayWithBVM(HAL_LCD_LINE_1,'G',B_drinkg);
}		
void B_blacktea(int B_drinkb){
	halLcdDisplayWithBVM(HAL_LCD_LINE_2,'B',B_drinkb);
}		
