//CC2530標頭檔
#include "ioCC2530.h"
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
	#define A_ZONE           		0x2222
	
	#define A_ZONE_1         		'1'
	#define A_ZONE_2         		'2'
	#define A_ZONE_3         		'3'
	#define A_ZONE_4         		'4'
	#define A_ZONE_5         		'5'
	
	#define B_ZONE           		0x2233	//Slave-B位址
	
	#define B_ZONE_1				'1'	//Slave-B節目1的辨識碼
	#define B_ZONE_2				'2'	//Slave-B節目2的辨識碼
	#define B_ZONE_3     			'3'	//Slave-B節目3的辨識碼
	#define B_ZONE_4     			'4'	//Slave-B節目4的辨識碼
	#define B_ZONE_5				'5'	//Slave-B節目5的辨識碼
	#define B_ZONE_ALARM			'6'
	
#define ONE_AREA            	0x3333	//第一區Master位址
#define APP_PAYLOAD_LENGTH        127


// Application states
#define IDLE                      0
#define SEND_CMD                  1

//Device

#define Button P0_4

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

void A_Zone_1(void);
void A_Zone_2(void);
void A_Zone_3(void);
void A_Zone_4(void);
void A_Zone_5(void);
void B_Zone_1(void);
void B_Zone_2(void);
void B_Zone_3(void);
void B_Zone_4(void);
void B_Zone_5(void);
void B_Zone_Alarm(void);
void Init_INTP();


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
    halLcdInit();
	//MAX7219_Init();

    // 裝置已經通電的提醒
    halLedSet(8);
    halBuzzer(300);
	
	// 初始化 BVM_ADDR RF
    basicRfConfig.myAddr = B_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	// 初始化 AVM_ADDR RF
	basicRfConfig.myAddr = A_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // 使RF接收端為常關，藉此省電
    basicRfReceiveOff();
	
	Init_INTP();
	
	while(1){
		
		uint8 v = halButtonPushed();
		if (v == HAL_BUTTON_2){
			while(1){
				B_Zone_1();
				A_Zone_2();
				halMcuWaitMs(5000);
				B_Zone_2();
				A_Zone_3();
				halMcuWaitMs(5000);
				B_Zone_3();
				A_Zone_4();
				halMcuWaitMs(5000);
				B_Zone_4();
				A_Zone_5();
				halMcuWaitMs(5000);
				B_Zone_5();
				A_Zone_1();
				halMcuWaitMs(5000);
			}
		}
		/*
		else if(v == HAL_BUTTON_1){
			while(1){
				A_Zone_2();
				halMcuWaitMs(5000);
				A_Zone_3();
				halMcuWaitMs(5000);
				A_Zone_4();
				halMcuWaitMs(5000);
				A_Zone_5();
				halMcuWaitMs(5000);
				A_Zone_1();
				halMcuWaitMs(5000);
			}
		}
		*/
	}
	
	return 0;
}

void A_Zone_1(void){
	
	pTxData[1] = A_ZONE_1;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
}

void A_Zone_2(void){
	
	pTxData[1] = A_ZONE_2;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void A_Zone_3(void){
	
	pTxData[1] = A_ZONE_3;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void A_Zone_4(void){
	
	pTxData[1] = A_ZONE_4;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void A_Zone_5(void){
	
	pTxData[1] = A_ZONE_5;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}


void B_Zone_1(void){
	
	pTxData[0] = B_ZONE_1;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
}

void B_Zone_2(void){
	
	pTxData[0] = B_ZONE_2;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void B_Zone_3(void){
	
	pTxData[0] = B_ZONE_3;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void B_Zone_4(void){
	
	pTxData[0] = B_ZONE_4;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void B_Zone_5(void){
	
	pTxData[0] = B_ZONE_5;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void B_Zone_Alarm(void){
	
	pTxData[0] = B_ZONE_ALARM;
	
	//發送封包，封包內容為{接收目的地(VM Co-ordinator位址)、Tx資料、Tx資料上限}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

//外部中斷初始化函數
void Init_INTP(){
	IEN1 |= 0x00;	//Port1中斷致能(Port 0、1、2、3對應01、10、11)
	P0IEN |= 0x10;	//Port1_2外部中斷致能
	//P1CTL |= 0x04;	//PortP1_0到P1_3負緣觸發
	EA = 1;
}

//外部中斷主函數
#pragma vector = P0INT_VECTOR		//外部中斷1的向量入口
__interrupt void Init1_Service(){	//外部中斷的主函數
	B_Zone_Alarm();	//原來LED的現態(ON/OFF)要轉變為次態(OFF/ON)
	
	//先清除引腳標誌位，再清除Port標誌位

	P0IFG &= ~0x10;	//清除P1_2引腳的標誌位
	P0IF = 0;		//清除P1 Port 的標誌位
}
