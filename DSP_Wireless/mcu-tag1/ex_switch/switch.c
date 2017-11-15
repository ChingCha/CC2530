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
#define B_ZONE           		0x2233		//Slave-B位址
#define ONE_AREA            	0x3333		//第一區Master位址
#define APP_PAYLOAD_LENGTH        127
#define B_ZONE_1				'1'	//Slave-B節目1的辨識碼
#define B_ZONE_2				'2'	//Slave-B節目2的辨識碼
#define B_ZONE_3     			'3'	//Slave-B節目3的辨識碼
#define B_ZONE_4     			'4'	//Slave-B節目4的辨識碼
#define B_ZONE_5				'5'	//Slave-B節目5的辨識碼

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
//static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx資料的上限
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;			//宣告RFConfig組態

/*
void B_greentea(int B_drinkg);		//B販賣機飲品(綠茶)的功能
void B_blacktea(int B_drinkb);		//B販賣機飲品(紅茶)的功能
*/

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
	halLcdInit();							//LCD顯示初始化

	// 裝置已經通電的提醒
    halLedSet(8);
    halBuzzer(300);
	/*
	int32 greentea = 7;						//B販賣機飲品(綠茶)的數量
	int32 blacktea = 3;						//B販賣機飲品(紅茶)的數量
	*/
	
	// 初始化 ONE_AREA RF
    basicRfConfig.myAddr = ONE_AREA;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	//使RF接收端為常開
    basicRfReceiveOn();					
	
	while (1)
    {
		
		while (!basicRfPacketIsReady()){
            halLedToggle(7);
            halMcuWaitMs(10);
        }
		
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
			
			switch(pRxData[0]){
				
				case '1':
					for(int i = 0;i <7;i++){
					halLedSet(i);
					halMcuWaitMs(100);
					halLedClear(i);
					halMcuWaitMs(100);
					}
					break;
				case '2':
					for(int i = 7;i >= 1;i--){
						halLedSet(i);
						halMcuWaitMs(100);
						halLedClear(i);
						halMcuWaitMs(100);
					}
					break;
				case '3':
					for(int i = 0;i <4;i++){
						halLedSet(i);
						halMcuWaitMs(100);
						halLedClear(i);
						halMcuWaitMs(100);
					}
					break;
					
				case '4':
					for(int i = 4;i >= 1;i--){
						halLedSet(i);
						halMcuWaitMs(100);
						halLedClear(i);
						halMcuWaitMs(100);
					}
					break;
					
				case '5':
					for(int i = 0;i <7;i++){
						halLedSet(i);
						halMcuWaitMs(100);
						halLedClear(i);
						halMcuWaitMs(100);
					}
					for(int i = 7;i >= 1;i--){
						halLedSet(i);
						halMcuWaitMs(100);
						halLedClear(i);
						halMcuWaitMs(100);
					}
					break;
				
				case '6':
					halLedSet(1);
					halMcuWaitMs(100);
					halLedClear(1);
					halMcuWaitMs(100);
					break;
			}
		}
    }
	return 0;
}

//-------------------------------------------------------------------
// @函數定義區
//-------------------------------------------------------------------
/*
void B_greentea(int B_drinkg){
	 
    do{
		pTxData[0] = BVM_GREENTEA;	//Tx陣列首個元素為AVM_greentea辨識碼
		pTxData[1] = B_drinkg;	//Tx陣列第二個元素為架上飲料數量(B_drinkg)
		
        //發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
		basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
        halBuzzer(100);
        halMcuWaitMs(200);
        halLedToggle(7);
	}while (B_drinkg<0);
}

void B_blacktea(int B_drinkb){

	
    do{
		pTxData[0] = BVM_BLACKTEA;
		pTxData[1] = B_drinkb;
		
		basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);

		halBuzzer(300);
		halMcuWaitMs(200);
        halLedToggle(7);
	}while (B_drinkb<0);
}
*/
