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
#include "hal_keypad.h"

//C_Compiler
#include <string.h>

//M230.h
#include "hal_cc8051.h"
#include "hal_uart.h"
#include "util.h"
#include "M230.h"

#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                	0x1111

	#define A_ZONE           		0x2222
	
	#define A_ZONE_1         		0x0001
	#define A_ZONE_2         		0x0002
	#define A_ZONE_3         		0x0003
	#define A_ZONE_4         		0x0004
	#define A_ZONE_5         		0x0005
	
	#define B_ZONE           			0x2233	//Slave-B��}
	
	#define B_ZONE_1				0x0001	//Slave-B�`��1�����ѽX
	#define B_ZONE_2				0x0002	//Slave-B�`��2�����ѽX
	#define B_ZONE_3     			0x0003	//Slave-B�`��3�����ѽX
	#define B_ZONE_4     			0x0004	//Slave-B�`��4�����ѽX
	#define B_ZONE_5				0x0005	//Slave-B�`��5�����ѽX
	
	#define C_ZONE           			0x2244	//Slave-B��}
	
	#define C_ZONE_1				0x0001	//Slave-B�`��1�����ѽX
	#define C_ZONE_2				0x0002	//Slave-B�`��2�����ѽX
	#define C_ZONE_3     			0x0003	//Slave-B�`��3�����ѽX
	#define C_ZONE_4     			0x0004	//Slave-B�`��4�����ѽX
	#define C_ZONE_5				0x0005	//Slave-B�`��5�����ѽX
	
#define ONE_AREA            	0x3333	//�Ĥ@��Master��}
#define APP_PAYLOAD_LENGTH        255	//�w�q�ʥ]�ǻ��j�p


// Application states
#define IDLE                      0
#define SEND_CMD                  1

#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif

static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx��ƪ��W��
static basicRfCfg_t basicRfConfig;			//�ŧiRFConfig�պA

//system.c Variables
uint16 ProgramDelayI[4];
uint8 key;
uint8 KeyCount;
uint16 ProgramDelay;
uint16 ProgramA[8];
uint8 ShowMode[3];

//system.c Function
void Program(uint8 a);
void Client_Program_Order(uint8 zone);
void Client_Program_Time(void);
uint8 ReadKeyInt(void);
void CommandZone(uint8 zone);
uint8 CommandAction(uint8 zone);
void ReadEEPRom(void);
void halLcdWriteIntToChar(uint8 lcd_line,uint8 lcd_col,uint8 lcd_text);
void ShowZoneMode(void);
void EEPROMAction(uint8 zone,uint8 mode, uint8 delay);
//�D���
void main(void) 
{
    // �t�mRF�Ѽ�
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif
	
	// ��l���X�R�O�BLCD�B�I�x�}�BM230
    halBoardInit();
    halLcdInit();
	M230_Init();
	
	// �˸m�w�g�q�q������
    halLedSet(8);
    halBuzzer(300);
	
	// ��l�� BVM_ADDR RF
    basicRfConfig.myAddr = A_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	// ��l�� AVM_ADDR RF
	basicRfConfig.myAddr = B_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	basicRfConfig.myAddr = C_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // ��RF�����ݬ��`���A�Ǧ��ٹq
    basicRfReceiveOff();

	halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:M_A");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target:ABC___");
	
	ShowMode[0] = 0;
	ShowMode[1] = 0;
	ShowMode[2] = 0;
	uint8 i = 0;
	while(1)
	{		
		key = halKeypadPushed();
		if(key == 'A' || key == 'B' || key == 'C') 
		{
			CommandZone(key);
			break;
		}
		if(i == 10)
		{
			halLcdWriteString(HAL_LCD_LINE_2,13,"ROM");
			ReadEEPRom();
			break;
		}
		halLcdWriteIntToChar(HAL_LCD_LINE_2,14,i);
		halMcuWaitMs(1000);
		i++;
	}
	while(1)
	{
		key = halKeypadPushed();
		if(key == 'A' || key == 'B' || key == 'C') CommandZone(key);
		if(key == '0') ShowZoneMode();
		halMcuWaitMs(300); 
	}
}
/***************************
Client_Program_Order()
1.��J00~99�������ƭȡA��J�����U#(Enter�i���x�s)
2.�̦h�ۭq8�Ӹ`�ض���
3.������ǭȡA��^
****************************/
void Client_Program_Order(uint8 zone)
{	
	KeyCount = 0;
	uint8 ProgramXY[2];
	uint8 ProgramZ = 1;
	halLcdClear();
	halMcuWaitMs(300);
	halLcdWriteString(HAL_LCD_LINE_1,0,"Input Program_1");
	while(ProgramZ < 9)
	{
		halLcdWriteIntToChar(HAL_LCD_LINE_1,14,ProgramZ);
		while(KeyCount < 2)
		{			
			ProgramXY[KeyCount] = ReadKeyInt();
			if(ProgramXY[KeyCount] != 11)
			{		
				key = halKeypadPushed();
				halLcdWriteChar(HAL_LCD_LINE_2,KeyCount,key);
				halBuzzer(100);
				KeyCount ++;
			}
			halMcuWaitMs(300);
		}
		ProgramA[ProgramZ] = ProgramXY[0] * 10 + ProgramXY[1];
		pTxData[ProgramZ+1] = ProgramA[ProgramZ];
		uint8 k = (zone +1) * 10 + (ProgramZ - 1);
		M230_WriteEEPROM(k, pTxData[ProgramZ+1]);
		halLcdWriteString(HAL_LCD_LINE_2,3,"Press * or #");
		key = halKeypadPushed();
		if(key == '#')
		{
			halBuzzer(100);
			ProgramZ ++;
			KeyCount = 0;
			halLcdWriteString(HAL_LCD_LINE_2,0,"__ Press * or #");
		}
		if(key == '*') 
		{
			halBuzzer(100);
			KeyCount = 0;
			halLcdWriteString(HAL_LCD_LINE_2,0,"__ Press * or #");
		}
		halMcuWaitMs(300);
	}
}
/*********************************************************
halLcdWriteIntToChar(LCD�ĴX��,���ĴX�Ӧr,��ܪ��ƭ�)
�i�N�ƭȦ۰��ഫ���r����ܦbLCD�W(���w�@�Ӧr?������)
*********************************************************/
void halLcdWriteIntToChar(uint8 lcd_line,uint8 lcd_col,uint8 lcd_text)
{
	char *pValue = convInt32ToText(lcd_text);
	if(lcd_line == HAL_LCD_LINE_1) halLcdWriteString(HAL_LCD_LINE_1,lcd_col,pValue);
	if(lcd_line == HAL_LCD_LINE_2) halLcdWriteString(HAL_LCD_LINE_2,lcd_col,pValue);
}
/***************************
Client_Program_Time()
***************************/
void Client_Program_Time(void)
{		
	halLcdWriteString(HAL_LCD_LINE_2,0,"____ms Delay    ");
	while(KeyCount<4)
	{		
		halMcuWaitMs(300);
		if(ReadKeyInt() >= 0 && ReadKeyInt() < 10)
		{
			ProgramDelayI[KeyCount] = ReadKeyInt();
			halLcdWriteIntToChar(HAL_LCD_LINE_2,KeyCount,ProgramDelayI[KeyCount]);
			halBuzzer(100);
			//halLcdDisplayUint8(HAL_LCD_LINE_2,KeyCount,HAL_LCD_RADIX_DEC,ProgramDelayI[KeyCount]);
			KeyCount++;
		}				
	}
    halBuzzer(100);	
	ProgramDelay = (ProgramDelayI[0] * 1000) + (ProgramDelayI[1] * 100) + (ProgramDelayI[2] * 10) + ProgramDelayI[3];
	uint8 i = 40;
	while(i < 61)
	{
		M230_WriteEEPROM(i,ProgramDelayI[0] * 1000);
		M230_WriteEEPROM(i + 1,ProgramDelayI[1] * 100);
		M230_WriteEEPROM(i + 2,ProgramDelayI[2] * 10);
		M230_WriteEEPROM(i + 3,ProgramDelayI[3]);
		i += 10;
	}
}
/********************
ReadKeyInt()
�μƭȫ��A�^����L��
********************/
uint8 ReadKeyInt(void)
{
	key = halKeypadPushed();
	if(key == '1') return 1;
	else if(key == '2') return 2;
	else if(key == '3') return 3;
	else if(key == '4') return 4;
	else if(key == '5') return 5;
	else if(key == '6') return 6;
	else if(key == '7') return 7;
	else if(key == '8') return 8;
	else if(key == '9') return 9;
	else if(key == '0') return 0;
	else return 11;
}
/*************************
CommandZone(uint8 zone)
1.�P�_�n�e�����@��A~F
2.�M��LCD�ALCD��ܭn�ǰe���I
3.�i�JCommandAction�Ƶ{��Ū���n�i�檺�Ҧ�
4.�N��Ƥ@�ְe�X
5.�w�������A
*************************/
void CommandZone(uint8 zone)
{
	halBuzzer(100);
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target : 1 2 3");
	switch(zone)
	{
		case 'A':			
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_A ");
			pTxData[1] = CommandAction(1);
			if(pTxData[1] != 3) ShowMode[0] = pTxData[1];
			M230_WriteEEPROM(0, pTxData[1]);
			basicRfSendPacket(A_ZONE,pTxData,APP_PAYLOAD_LENGTH);
			break;
		case 'B':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_B ");
			pTxData[1] = CommandAction(2);
			if(pTxData[1] != 3) ShowMode[1] = pTxData[1];
			M230_WriteEEPROM(1, pTxData[1]);
			basicRfSendPacket(B_ZONE,pTxData,APP_PAYLOAD_LENGTH);
			break;
		case 'C':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_C ");
			pTxData[1] = CommandAction(3);
			if(pTxData[1] != 3) ShowMode[2] = pTxData[1];
			M230_WriteEEPROM(2, pTxData[1]);
			basicRfSendPacket(C_ZONE,pTxData,APP_PAYLOAD_LENGTH);
			break;
/*		case 'D':
			break;
		case 'E':
			break;
		case 'F':
			break;
*/
		default:
			break;
	}
	halMcuWaitMs(1000);
	ShowZoneMode();
}
/*****************************
CommandAction(uint8 zone)
1.�P�_��J���Ҧ�1~3
2.�]�w�ϰ�a�}?
3.LCD���
4.�^�ǼҦ����ƭ�
*****************************/
uint8 CommandAction(uint8 zone)
{
	uint8 Mode;
	while(1)
	{
		Mode = ReadKeyInt();
		if(Mode > 0 && Mode < 4) break;
	}
	halBuzzer(100);
	switch(Mode)
	{			
		case 1:
			if(zone == 1) pTxData[0] = A_ZONE_1;
			else if(zone == 2) pTxData[0] = B_ZONE_1;
			else if(zone == 3) pTxData[0] = C_ZONE_1;
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 1 ");
			return 1;
			break;			
		case 2:
			Client_Program_Order(zone);
			if(zone == 1) pTxData[0] = A_ZONE_2;
			else if(zone == 2) pTxData[0] = B_ZONE_2;
			else if(zone == 3) pTxData[0] = C_ZONE_2;
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 2 ");
			return 2;
			break;
		case 3:
			Client_Program_Time();
			if(zone == 1) pTxData[0] = A_ZONE_3;
			else if(zone == 2) pTxData[0] = B_ZONE_3;
			else if(zone == 3) pTxData[0] = C_ZONE_3;
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 3 ");
			return 3;
			break;
	}
}
/*********************
ShowZoneMode()
��ܷ�e�C�ӼҦ��Ҷi�檺�`��(��K�ʴ�)
*********************/
void ShowZoneMode(void)
{
    halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"Show Zone:Mode");
	halLcdWriteString(HAL_LCD_LINE_2,0,"S_A:");
	halLcdWriteString(HAL_LCD_LINE_2,5,"S_B:");
	halLcdWriteString(HAL_LCD_LINE_2,10,"S_C:");
	halLcdWriteIntToChar(HAL_LCD_LINE_2,4,ShowMode[0]);
	halLcdWriteIntToChar(HAL_LCD_LINE_2,9,ShowMode[1]);
	halLcdWriteIntToChar(HAL_LCD_LINE_2,14,ShowMode[2]);
}
	/**************************************************
M230	��m	�\��
		0			S_A_Mode 1 or 2
		1			S_B_Mode 1 or 2
		2			S_C_Mode 1 or 2
		10~17	S_A_Mode2 Program1~8
		20~27	S_B_Mode2 Program1~8
		30~37	S_C_Mode2 Program1~8
		40~43	S_A_Delay 4��Ƥ���4����(uint8 �u��255�A�ѩ�}�C��4�����A���ڦs���覡�]�Τ@4����)
		50~53	S_B_Delay 4��Ƥ���4����
		60~63	S_C_Delay 4��Ƥ���4����
	**************************************************/
void ReadEEPRom(void)
{
	uint8 ReadMode[3];
	uint8 ReadDelayI[3][4];
	uint8 ReadDelay[3];
	for(uint8 i = 0;i < 3;i++)
	{
		ReadMode[i] = M230_ReadEEPROM(i);
		for(uint8 j = 0;j < 4;j++)
		{
			uint8 k = (i + 4) * 10 + j;
			ReadDelayI[i][j] =  M230_ReadEEPROM(k);
		}
		if(ReadMode[i] != 0)
		{
			ReadDelay[i] = ReadDelayI[i][0] * 1000 + ReadDelayI[i][1] * 100 + ReadDelayI[i][2] * 10 + ReadDelayI[i][3];
			EEPROMAction(i,ReadMode[i],ReadDelay[i]);
		}
	}
}

void EEPROMAction(uint8 zone,uint8 mode, uint8 delay)
{
	switch(mode)
	{
		case 1:
			pTxData[1] = 1;
			switch(zone) 
			{
				case 1:
					pTxData[0] = A_ZONE_1;
					basicRfSendPacket(A_ZONE,pTxData,APP_PAYLOAD_LENGTH);
					ShowMode[0] = 1;
				case 2:
					pTxData[0] = B_ZONE_1;
					basicRfSendPacket(B_ZONE,pTxData,APP_PAYLOAD_LENGTH);
					ShowMode[1] = 1;
				case 3:
					pTxData[0] = C_ZONE_1;
					basicRfSendPacket(C_ZONE,pTxData,APP_PAYLOAD_LENGTH);
					ShowMode[2] = 1;
			}
		case 2:
			pTxData[1] = 2;
			for(uint8 i = 0;i < 3;i ++)
			{
				for(uint8 j = 0; j < 8;j++)
				{
					uint8 k = (i + 1) * 10 + j;
					pTxData[j + 2] = M230_ReadEEPROM(k);
				}
			}
			switch(zone) 
			{
				case 1:
					pTxData[0] = A_ZONE_2;
					basicRfSendPacket(A_ZONE,pTxData,APP_PAYLOAD_LENGTH);
					ShowMode[0] = 2;
				case 2:
					pTxData[0] = B_ZONE_2;
					basicRfSendPacket(B_ZONE,pTxData,APP_PAYLOAD_LENGTH);
					ShowMode[1] = 2;
				case 3:
					pTxData[0] = C_ZONE_2;
					basicRfSendPacket(C_ZONE,pTxData,APP_PAYLOAD_LENGTH);
					ShowMode[2] = 2;
			}
	}
}
