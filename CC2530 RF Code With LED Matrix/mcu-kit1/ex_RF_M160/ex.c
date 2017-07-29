//CC2530���h���Y��
#include "ioCC2530.h"
//CC2530�Ҳ�(KIT�O)���Y��
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
//�۩w�q���Y��
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
	#define BVM_GREENTEA     		'3'					//B�c������~(��)�����ѽX
	#define BVM_BLACKTEA     		'4'					//B�c������~(����)�����ѽX

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

//�R�A�ϰ��ܼ�-�ɮפ����s��
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

//�D���
int main() 
{
    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // Initalise board peripherals & LED Matrix
    halBoardInit();
    halLcdInit();
	MAX7219_Init();

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
			
			if(pRxData[0] == AVM_WATER){
				A_water(pRxData[1]);
				MAX7219_Write(DIGIT0,0x01);
			}
				
		
			if(pRxData[0] == AVM_MILK){
				A_milk(pRxData[1]);
				MAX7219_Write(DIGIT0,0x02);
			}
				
			
			if(pRxData[0] == BVM_GREENTEA){
				B_greentea(pRxData[1]);
			}
				
			
			if(pRxData[0] == BVM_BLACKTEA){
				B_blacktea(pRxData[1]);
			}
				
		}	
	}
	
	return 0;
}
