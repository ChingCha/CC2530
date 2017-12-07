//LED_Matrix
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

//M230.h
#include "hal_cc8051.h"
#include "hal_keypad.h"
#include "hal_uart.h"
#include "util.h"
#include "M230.h"
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                	0x1111
#define BVM_ADDR           		0x2233		//B販賣機的RF位址
#define VM_ONE_ADDR            	0x3333		//第一區VM Co-ordinator位址
#define APP_PAYLOAD_LENGTH        127
#define BVM_GREENTEA     '3'					//B販賣機飲品(水)的辨識碼
#define BVM_BLACKTEA     '4'					//B販賣機飲品(牛奶)的辨識碼

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

void B_greentea(int B_drinkg);		//B販賣機飲品(綠茶)的功能
void B_blacktea(int B_drinkb);		//B販賣機飲品(紅茶)的功能

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

	int32 greentea = 7;						//B販賣機飲品(綠茶)的數量
	int32 blacktea = 3;						//B販賣機飲品(紅茶)的數量
	
	// RF初始化
    basicRfConfig.myAddr = BVM_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    basicRfReceiveOff();					//使RF接收端為常關，藉此省電
	
	while (1)
    {
        uint8 v = halButtonPushed();							//v等於按下BUTTON
		if (v == HAL_BUTTON_2){									//若v接收到BUTTON_2的訊號
            if(greentea > 0)										//若B販賣機飲品(綠茶)的數量大於0
				greentea--;										//B販賣機飲品(綠茶)的數量扣1
			halLcdDisplayWithVM(HAL_LCD_LINE_1,'G',greentea);	//顯示於LCD
			B_greentea(greentea);										//將引數greentea傳至B_greentea函數中的參數B_drinkg
		}
		else if(v == HAL_BUTTON_1){
			if(blacktea > 0)
				blacktea--;
			halLcdDisplayWithVM(HAL_LCD_LINE_2,'B',blacktea);
			B_blacktea(blacktea);
		}
        halMcuWaitMs(100);    
    }
	return 0;
}

//-------------------------------------------------------------------
// @函數定義區
//-------------------------------------------------------------------

void B_greentea(int B_drinkg){
	 
    do{
		pTxData[0] = BVM_GREENTEA;	//Tx陣列首個元素為AVM_greentea辨識碼
		pTxData[1] = B_drinkg;	//Tx陣列第二個元素為架上飲料數量(B_drinkg)
		
        //發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
		basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
        halBuzzer(100);
        halMcuWaitMs(200);
        halLedToggle(7);
	}while (B_drinkg<0);
}

void B_blacktea(int B_drinkb){

	
    do{
		pTxData[0] = BVM_BLACKTEA;
		pTxData[1] = B_drinkb;
		
		basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);

		halBuzzer(300);
		halMcuWaitMs(200);
        halLedToggle(7);
	}while (B_drinkb<0);
}


