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
#define B_ZONE           		0x2233		//Slave-B��}
#define ONE_AREA            	0x3333		//�Ĥ@��Master��}
#define APP_PAYLOAD_LENGTH        127
#define B_ZONE_1				'1'	//Slave-B�`��1�����ѽX
#define B_ZONE_2				'2'	//Slave-B�`��2�����ѽX
#define B_ZONE_3     			'3'	//Slave-B�`��3�����ѽX
#define B_ZONE_4     			'4'	//Slave-B�`��4�����ѽX
#define B_ZONE_5				'5'	//Slave-B�`��5�����ѽX

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
// @			����ŧi��ư�
// @fn          Drink of A vendingmachine
// @brief       Application code for switch application. Puts MCU in
//              endless loop to wait for commands from switch.
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pTxData - file scope variable. Pointer to buffer for TX
//              payload
//              appState - file scope variable. Holds application state
// @return      none
//-------------------------------------------------------------------
//static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx��ƪ��W��
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;			//�ŧiRFConfig�պA

/*
void B_greentea(int B_drinkg);		//B�c������~(���)���\��
void B_blacktea(int B_drinkb);		//B�c������~(����)���\��
*/

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "portion" application.
// @return      none
//-------------------------------------------------------------------
int main()
{
	basicRfConfig.panId = PAN_ID;			//���wRF ID
    basicRfConfig.channel = RF_CHANNEL;		//���wRF Channel
    basicRfConfig.ackRequest = TRUE;		//�ʥ]�ǻ��|��ACK�^��
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;	//�ʥ]�ǻ��w������
    #endif 

    halBoardInit();							//CC2530�D�O��l��
	halLcdInit();							//LCD��ܪ�l��

	// �˸m�w�g�q�q������
    halLedSet(8);
    halBuzzer(300);
	/*
	int32 greentea = 7;						//B�c������~(���)���ƶq
	int32 blacktea = 3;						//B�c������~(����)���ƶq
	*/
	
	// ��l�� ONE_AREA RF
    basicRfConfig.myAddr = ONE_AREA;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	//��RF�����ݬ��`�}
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
// @��Ʃw�q��
//-------------------------------------------------------------------
/*
void B_greentea(int B_drinkg){
	 
    do{
		pTxData[0] = BVM_GREENTEA;	//Tx�}�C���Ӥ�����AVM_greentea���ѽX
		pTxData[1] = B_drinkg;	//Tx�}�C�ĤG�Ӥ������[�W���Ƽƶq(B_drinkg)
		
        //�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
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
