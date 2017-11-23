//-------------------------------------------------------------------
// Filename: ex.c
// Description: ��C�O����(I2C)�d��
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "ioCC2530.h"
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_uart.h"
#include "hal_buzzer.h"
#include "hal_led.h"
#include "hal_rf.h"
#include "util.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "M230.h"
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

// Device
#define Button P0_4
#define LED1 P1_3
#define LED2 P1_4

#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif

unsigned char DataRecieve;		//Ū���w�İϸ�ƪ��ܼ�
unsigned char Flag = 0;			//�������O�лx���ܼ�

static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx��ƪ��W��
static basicRfCfg_t basicRfConfig;

void Init_Port();						//LED Port ��l�ƨ��
void Init_UART0();						//�ǦC��0����l�ƨ��
void set_main_clock();					//�]�m�D����
void ExecuteTheOrder();					//����W������O
void UR0SendByte(unsigned char data);	//UR0�o�e�r�����
void UR0SendString(unsigned char *str);	//UR0�o�e�r����


void main(void)
{
	// RF��l��
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 
	
    uint8 key;

    // Indicate that device is powered
    halLedSet(8);
	
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M230 Test  **");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0);
    utilMenuSelect(NULL);
	
	// ��l���X�R�O�BLCD�B�I�x�}
    halBoardInit();
    halLcdInit();
	MAX7219_Init();
	
	
    while (TRUE)
    {
		//M230��l�ʧ@
        halLcdClear();
        halBuzzer(300);
        M230_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "** M230 Test  **");
        halLcdWriteLine(HAL_LCD_LINE_2, "Write:   Read:  ");
        key = M230_ReadEEPROM(0);
        halLcdWriteChar(HAL_LCD_LINE_2, 14, key);
		
		//UART��l��
		Init_Port();	
		set_main_clock();
		Init_UART0();
		
		//���զr��
		UR0SendString("1\n");
		
        while (TRUE)
        {
			if(Flag == 1)      //�O�_����W������O?
			{
				ExecuteTheOrder();    //�ѪR�ùB����O
			}
            key = halKeypadPushed();
            halMcuWaitMs(100);
            if (key > 0)
            {
                if (key == '*')
                {
                    break;
                }
                M230_WriteEEPROM(0, key); //WriteEEPROM(addr, data)
                halLcdWriteChar(HAL_LCD_LINE_2, 6, key);

                key = M230_ReadEEPROM(0); //ReadEEPROM(addr)
                halLcdWriteChar(HAL_LCD_LINE_2, 14, key);
            }
        }
    }
}

void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//�N�n�o�e��1�r�`�ƾڼg�JU0DBUF
	while(!UTX0IF);			//����TX���_�лx�A�Y�ƾڵo�e����
	UTX0IF = 0;				//����TX���_�лx�A�ǳƤU�@���o�e
	
}


void UR0SendString(unsigned char *str){
	
	while(*str != '\0'){	//�o�e�@�Ӧr��
		UR0SendByte(*str++);//�v�@�o�e�r�ꪺ�r��
	}
	
}

void Init_Port(){
	
	P1SEL &= ~0x18;		//�NP1_4�B5�]�m���q��I/O
	P1DIR |= 0x18;		//�NP1_4�B5 Port �]�m����X
	LED1 = 0;
	LED2 = 0;
	
}

void Init_UART0(){
	
	//�������޸}���~�]�\��

	PERCFG = 0x00;	//��f0���޸}�M�g���m1�A�YP0_2�B3
	P0SEL = 0x0C;	//�NP0_2�B3 Port �]�m���~�]�\��
	P2DIR &= ~0x3F;	//P0�~�]�u����USART0�̰�
	
	U0BAUD = 216;	//16MHz���t�ή�������9600BPS�j�v
	U0GCR = 12;
	
	U0UCR |= 0x80;	//�T��y���A8bit�ƾڡA�M���w�ľ�
	U0CSR |= 0x80;	//���UART�Ҧ�(7)�A�P�౵����(6)
	
	UTX0IF = 0;		//�M��TX�o�e���_�лx
	
	//UART2.c�~�[
	
	U0CSR |=0X40;			//�P��UART0 ����
	IEN0 |=0X04;			//�P��UART0 �������_
	EA=1;					//�}���`���_

}

//�ƾڱ������_�A�Ȩ��
#pragma vector = URX0_VECTOR		
__interrupt void UR0_Recieve_Service(){
	
	URX0IF = 0;				//�M��RX�������_�лx
	DataRecieve = U0DBUF;	//�N�ƾڱq�����w�İ�Ū�X
	Flag = 1;				//�]�m�������O�лx
}

void ExecuteTheOrder(){
	
	Flag = 0;	//�M���������O�лx
	
	switch(DataRecieve){
		
		case 0x31:
			LED1 = 1;
			UR0SendString("The LED1 is Open!");
		break;
		
		case 0x32:
			LED1 = 0;
			UR0SendString("The LED1 is Closed!");
		break;
		
		case 0x33:
			LED2 = 1;
			UR0SendString("The LED2 is Open!");
		break;
		
		case 0x34:
			LED2 = 0;
			UR0SendString("The LED2 is Closed!");
		break;
	}
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//���16MHZ RCOSC���t�ή�����
	while(!(CLKCONSTA & 0X40)); //���ݮ���í�w
	CLKCONCMD &=~0XF8;			//���32MHz���D����
}


