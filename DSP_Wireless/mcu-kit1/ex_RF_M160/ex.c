//C++ Compile
#include <iostream>

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
	int a = 5;
	
	//halLcdWriteString(Line,LCD Text,Value)
	halLcdWriteString(HAL_LCD_LINE_1,1,&a)
	
	return 0;
	
	
}
