//CC2530模組(KIT板)標頭檔
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
//自定義標頭檔
#include "hal_ledmatrix.h"
#include "hal_drink.h"

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

//靜態區域變數-檔案內部連結
//static uint8 pRxData[APP_PAYLOAD_LENGTH];
static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx資料的上限
static basicRfCfg_t basicRfConfig;

void B_greentea(void);
void B_blacktea(void);
void A_Water(void);
void A_Milk(void);

//主函數
int main() 
{
    // RF初始化
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // 初始化擴充板、LCD、點矩陣
    halBoardInit();
    //halLcdInit();
	//MAX7219_Init();

    // 裝置已經通電的提醒
    halLedSet(8);
    halBuzzer(300);
	
	// 初始化 BVM_ADDR RF
    basicRfConfig.myAddr = BVM_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	// 初始化 AVM_ADDR RF
	basicRfConfig.myAddr = AVM_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // 使RF接收端為常關，藉此省電
    basicRfReceiveOff();
	
	while(1){
		
		uint8 v = halButtonPushed();
		if (v == HAL_BUTTON_2){
			while (v == HAL_BUTTON_1){
				B_greentea();
				B_blacktea();
			}
		}
		else if(v == HAL_BUTTON_1){
			while (v == HAL_BUTTON_2){
				A_Water();
				A_Milk();
			}
		}
		/*
		while (!basicRfPacketIsReady()){
            halLedToggle(7);
            halMcuWaitMs(10);
        }
		
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
			
			switch(pRxData[0]){
				case '1':
					A1_Recieve(pRxData[1]);
					MAX7219_Write(DIGIT0,0x01);
					if(pRxData[1]==0)
						A1_Warning();
					break;
				case '2':
					A2_Recieve(pRxData[1]);
					MAX7219_Write(DIGIT0,0x02);
					if(pRxData[1]==0)
						A2_Warning();
					break;
				case '3':
					B1_Recieve(pRxData[1]);
					MAX7219_Write(DIGIT1,0x01);
					if(pRxData[1]==0)
						B1_Warning();
					break;
				case '4':
					B2_Recieve(pRxData[1]);
					MAX7219_Write(DIGIT1,0x02);
					if(pRxData[1]==0)
						B2_Warning();
					break;
			}
		}
		*/
	}
	
	return 0;
}

void B_greentea(void){
	
	pTxData[0] = BVM_GREENTEA;
	
		
	basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
}

void B_blacktea(void){
	
	pTxData[0] = BVM_BLACKTEA;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	
}

void A_Water(void){
	
	pTxData[0] = AVM_WATER;//Tx陣列首個元素為AVM_water辨識碼
	
	basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	
}


void A_Milk(void){
	
	pTxData[0] = AVM_MILK;//Tx陣列首個元素為AVM_water辨識碼
	
	basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	
}
