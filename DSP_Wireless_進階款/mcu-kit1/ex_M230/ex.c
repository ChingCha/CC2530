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
#define BVM_ADDR           		0x2233		//B�c�����RF��}
#define VM_ONE_ADDR            	0x3333		//�Ĥ@��VM Co-ordinator��}
#define APP_PAYLOAD_LENGTH        127
#define BVM_GREENTEA     '3'					//B�c������~(��)�����ѽX
#define BVM_BLACKTEA     '4'					//B�c������~(����)�����ѽX

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
static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx��ƪ��W��
static basicRfCfg_t basicRfConfig;			//�ŧiRFConfig�պA

void B_greentea(int B_drinkg);		//B�c������~(���)���\��
void B_blacktea(int B_drinkb);		//B�c������~(����)���\��

int main()
{
	basicRfConfig.panId = PAN_ID;			//���wRF ID
    basicRfConfig.channel = RF_CHANNEL;		//���wRF Channel
    basicRfConfig.ackRequest = TRUE;		//�ʥ]�ǻ��|��ACK�^��
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;	//�ʥ]�ǻ��w������
    #endif 

    halBoardInit();							//CC2530�D�O��l��

    halLedSet(8);							//�q�����ܿO

	int32 greentea = 7;						//B�c������~(���)���ƶq
	int32 blacktea = 3;						//B�c������~(����)���ƶq
	
	// RF��l��
    basicRfConfig.myAddr = BVM_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    basicRfReceiveOff();					//��RF�����ݬ��`���A�Ǧ��ٹq
	
	while (1)
    {
        uint8 v = halButtonPushed();							//v������UBUTTON
		if (v == HAL_BUTTON_2){									//�Yv������BUTTON_2���T��
            if(greentea > 0)										//�YB�c������~(���)���ƶq�j��0
				greentea--;										//B�c������~(���)���ƶq��1
			halLcdDisplayWithVM(HAL_LCD_LINE_1,'G',greentea);	//��ܩ�LCD
			B_greentea(greentea);										//�N�޼�greentea�Ǧ�B_greentea��Ƥ����Ѽ�B_drinkg
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
// @��Ʃw�q��
//-------------------------------------------------------------------

void B_greentea(int B_drinkg){
	 
    do{
		pTxData[0] = BVM_GREENTEA;	//Tx�}�C���Ӥ�����AVM_greentea���ѽX
		pTxData[1] = B_drinkg;	//Tx�}�C�ĤG�Ӥ������[�W���Ƽƶq(B_drinkg)
		
        //�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
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


