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
//static uint8 pRxData[APP_PAYLOAD_LENGTH];
static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx��ƪ��W��
static basicRfCfg_t basicRfConfig;

void B_greentea(void);
void B_blacktea(void);
void A_Water(void);
void A_Milk(void);

//�D���
int main() 
{
    // RF��l��
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // ��l���X�R�O�BLCD�B�I�x�}
    halBoardInit();
    //halLcdInit();
	//MAX7219_Init();

    // �˸m�w�g�q�q������
    halLedSet(8);
    halBuzzer(300);
	
	// ��l�� BVM_ADDR RF
    basicRfConfig.myAddr = BVM_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	// ��l�� AVM_ADDR RF
	basicRfConfig.myAddr = AVM_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // ��RF�����ݬ��`���A�Ǧ��ٹq
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
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	
}

void A_Water(void){
	
	pTxData[0] = AVM_WATER;//Tx�}�C���Ӥ�����AVM_water���ѽX
	
	basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	
}


void A_Milk(void){
	
	pTxData[0] = AVM_MILK;//Tx�}�C���Ӥ�����AVM_water���ѽX
	
	basicRfSendPacket(VM_ONE_ADDR, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	
}
