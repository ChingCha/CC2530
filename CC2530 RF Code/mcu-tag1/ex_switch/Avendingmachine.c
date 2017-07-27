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
#define AVM_ADDR           		0x2222		//A�c�����RF��}
#define VM_ONE_ADDR            	0x3333		//�Ĥ@��VM Co-ordinator��}
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

void A_water(int A_drinkw);
void A_milk(int A_drinkm);	

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

    halLedSet(8);							//�q�����ܿO

	int32 water = 9;						
	int32 milk = 5;						
	
	// RF��l��
    basicRfConfig.myAddr = AVM_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    basicRfReceiveOff();					//��RF�����ݬ��`���A�Ǧ��ٹq
	
	while (1)
    {
        uint8 v = halButtonPushed();							//v������UBUTTON
		if (v == HAL_BUTTON_2){									//�Yv������BUTTON_2���T��
            if(water > 0)										//�YA�c������~(��)���ƶq�j��0
				water--;										//A�c������~(��)���ƶq��1
			halLcdDisplayWithVM(HAL_LCD_LINE_1,'G',water);		//��ܩ�LCD
			A_water(water);										//�N�޼�water�Ǧ�B_water��Ƥ����Ѽ�A_drinkw
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
// @��Ʃw�q��
//-------------------------------------------------------------------

void A_water(int A_drinkw){
	 
    do{
		pTxData[0] = AVM_WATER;	//Tx�}�C���Ӥ�����AVM_water���ѽX
		pTxData[1] = A_drinkw;	//Tx�}�C�ĤG�Ӥ������[�W���Ƽƶq(A_drinkw)
		
        //�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
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
