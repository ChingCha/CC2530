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
#define PAN_ID                	0x1111
#define AVM_ADDR           		0x2222		//A販賣機的RF位址
#define VM_ONE_ADDR            	0x3333		//第一區VM Co-ordinator位址
#define APP_PAYLOAD_LENGTH        127
#define AVM_WATER     '1'					
#define AVM_MILK     '2'					

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
// @			先行宣告函數區
// @fn          Drink of A vendingmachine
// @brief       Application code for switch application. Puts MCU in
//              endless loop to wait for commands from switch.
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pTxData - file scope variable. Pointer to buffer for TX
//              payload
//              appState - file scope variable. Holds application state
// @return      none
//-------------------------------------------------------------------
static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx資料的上限
static basicRfCfg_t basicRfConfig;			//宣告RFConfig組態

void A_water(int A_drinkw);
void A_milk(int A_drinkm);	

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "portion" application.
// @return      none
//-------------------------------------------------------------------
int main()
{
	basicRfConfig.panId = PAN_ID;			//指定RF ID
    basicRfConfig.channel = RF_CHANNEL;		//指定RF Channel
    basicRfConfig.ackRequest = TRUE;		//封包傳遞會有ACK回應
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;	//封包傳遞安全機制
    #endif 

    halBoardInit();							//CC2530主板初始化

    halLedSet(8);							//電源指示燈

	int32 water = 9;						
	int32 milk = 5;						
	
	// RF初始化
    basicRfConfig.myAddr = AVM_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    basicRfReceiveOff();					//使RF接收端為常關，藉此省電
	
	while (1)
    {
        uint8 v = halButtonPushed();							//v等於按下BUTTON
		if (v == HAL_BUTTON_2){									//若v接收到BUTTON_2的訊號
            if(water > 0)										//若A販賣機飲品(水)的數量大於0
				water--;										//A販賣機飲品(水)的數量扣1
			halLcdDisplayWithVM(HAL_LCD_LINE_1,'G',water);		//顯示於LCD
			A_water(water);										//將引數water傳至B_water函數中的參數A_drinkw
		}
		else if(v == HAL_BUTTON_1){
			if(milk > 0)
				milk--;
			halLcdDisplayWithVM(HAL_LCD_LINE_2,'B',milk);
			A_milk(milk);
		}
        halMcuWaitMs(100);    
    }
	return 0;
}

//-------------------------------------------------------------------
// @函數定義區
//-------------------------------------------------------------------

void A_water(int A_drinkw){
	 
    do{
		pTxData[0] = AVM_WATER;	//Tx陣列首個元素為AVM_water辨識碼
		pTxData[1] = A_drinkw;	//Tx陣列第二個元素為架上飲料數量(A_drinkw)
		
        //發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
		basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
        halBuzzer(100);
        halMcuWaitMs(200);
        halLedToggle(7);
	}while (A_drinkw<0);
}

void A_milk(int A_drinkm){

	
    do{
		pTxData[0] = AVM_MILK;
		pTxData[1] = A_drinkm;
		
		basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);

		halBuzzer(300);
		halMcuWaitMs(200);
        halLedToggle(7);
	}while (A_drinkm<0);
}
