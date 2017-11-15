//CC2530���Y��
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
	#define A_ZONE           		0x2222
	
	#define A_ZONE_1         		'1'
	#define A_ZONE_2         		'2'
	#define A_ZONE_3         		'3'
	#define A_ZONE_4         		'4'
	#define A_ZONE_5         		'5'
	
	#define B_ZONE           		0x2233	//Slave-B��}
	
	#define B_ZONE_1				'1'	//Slave-B�`��1�����ѽX
	#define B_ZONE_2				'2'	//Slave-B�`��2�����ѽX
	#define B_ZONE_3     			'3'	//Slave-B�`��3�����ѽX
	#define B_ZONE_4     			'4'	//Slave-B�`��4�����ѽX
	#define B_ZONE_5				'5'	//Slave-B�`��5�����ѽX
	#define B_ZONE_ALARM			'6'
	
#define ONE_AREA            	0x3333	//�Ĥ@��Master��}
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

//�R�A�ϰ��ܼ�-�ɮפ����s��
//static uint8 pRxData[APP_PAYLOAD_LENGTH];
static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx��ƪ��W��
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
    halLcdInit();
	//MAX7219_Init();

    // �˸m�w�g�q�q������
    halLedSet(8);
    halBuzzer(300);
	
	// ��l�� BVM_ADDR RF
    basicRfConfig.myAddr = B_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	// ��l�� AVM_ADDR RF
	basicRfConfig.myAddr = A_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // ��RF�����ݬ��`���A�Ǧ��ٹq
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
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
}

void A_Zone_2(void){
	
	pTxData[1] = A_ZONE_2;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void A_Zone_3(void){
	
	pTxData[1] = A_ZONE_3;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void A_Zone_4(void){
	
	pTxData[1] = A_ZONE_4;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void A_Zone_5(void){
	
	pTxData[1] = A_ZONE_5;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}


void B_Zone_1(void){
	
	pTxData[0] = B_ZONE_1;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
}

void B_Zone_2(void){
	
	pTxData[0] = B_ZONE_2;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void B_Zone_3(void){
	
	pTxData[0] = B_ZONE_3;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void B_Zone_4(void){
	
	pTxData[0] = B_ZONE_4;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void B_Zone_5(void){
	
	pTxData[0] = B_ZONE_5;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

void B_Zone_Alarm(void){
	
	pTxData[0] = B_ZONE_ALARM;
	
	//�o�e�ʥ]�A�ʥ]���e��{�����ت��a(VM Co-ordinator��})�BTx��ơBTx��ƤW��}
	basicRfSendPacket(ONE_AREA, pTxData, APP_PAYLOAD_LENGTH);
        
	halBuzzer(100);
	halMcuWaitMs(200);
	halLedToggle(7);
	halMcuWaitMs(200);
	
}

//�~�����_��l�ƨ��
void Init_INTP(){
	IEN1 |= 0x00;	//Port1���_�P��(Port 0�B1�B2�B3����01�B10�B11)
	P0IEN |= 0x10;	//Port1_2�~�����_�P��
	//P1CTL |= 0x04;	//PortP1_0��P1_3�t�tĲ�o
	EA = 1;
}

//�~�����_�D���
#pragma vector = P0INT_VECTOR		//�~�����_1���V�q�J�f
__interrupt void Init1_Service(){	//�~�����_���D���
	B_Zone_Alarm();	//���LED���{�A(ON/OFF)�n���ܬ����A(OFF/ON)
	
	//���M���޸}�лx��A�A�M��Port�лx��

	P0IFG &= ~0x10;	//�M��P1_2�޸}���лx��
	P0IF = 0;		//�M��P1 Port ���лx��
}
