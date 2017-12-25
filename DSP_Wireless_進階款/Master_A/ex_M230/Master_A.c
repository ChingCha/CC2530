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
	
	#define B_ZONE           			0x2233	//Slave-B位址
	
	#define B_ZONE_1				0x0001	//Slave-B節目1的辨識碼
	#define B_ZONE_2				0x0002	//Slave-B節目2的辨識碼
	#define B_ZONE_3     			0x0003	//Slave-B節目3的辨識碼
	#define B_ZONE_4     			0x0004	//Slave-B節目4的辨識碼
	#define B_ZONE_5				0x0005	//Slave-B節目5的辨識碼
	
	#define C_ZONE           			0x2244	//Slave-B位址
	
	#define C_ZONE_1				0x0001	//Slave-B節目1的辨識碼
	#define C_ZONE_2				0x0002	//Slave-B節目2的辨識碼
	#define C_ZONE_3     			0x0003	//Slave-B節目3的辨識碼
	#define C_ZONE_4     			0x0004	//Slave-B節目4的辨識碼
	#define C_ZONE_5				0x0005	//Slave-B節目5的辨識碼
	
#define ONE_AREA            	0x3333	//第一區Master位址
#define APP_PAYLOAD_LENGTH        255	//定義封包傳遞大小


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

static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx資料的上限
static basicRfCfg_t basicRfConfig;			//宣告RFConfig組態

//system.c Variables
uint16 ProgramDelayI[4];
uint8 key;
uint8 KeyCount;
uint16 ProgramDelay;
uint16 ProgramA[8];
uint8 ShowMode[3];
uint8 Reading;
//system.c Function
void Program(uint8 a);
void Client_Program_Order(void);
void Client_Program_Time(void);
uint8 ReadKeyInt(void);
void CommandZone(uint8 zone,uint8 rom);
uint8 CommandAction(uint8 zone);
//void ShowZoneMode(void);
void ReadEEPRom(void);
void halLcdWriteIntToChar(uint8 lcd_line,uint8 lcd_col,uint8 lcd_text);
void ShowZoneMode(void);

//主函數
void main(void) 
{
    // 配置RF參數
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif
	
	// 初始化擴充板、LCD、點矩陣、M230
    halBoardInit();
    halLcdInit();
	M230_Init();
	
	// 裝置已經通電的提醒
    halLedSet(8);
    halBuzzer(300);
	
	// 初始化 BVM_ADDR RF
    basicRfConfig.myAddr = A_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	// 初始化 AVM_ADDR RF
	basicRfConfig.myAddr = B_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	basicRfConfig.myAddr = C_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // 使RF接收端為常關，藉此省電
    basicRfReceiveOff();

	halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:M_A");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target : ABC___");
	
	ShowMode[0] = 0;
	ShowMode[1] = 0;
	ShowMode[2] = 0;
	Reading = 0;
	//ReadEEPRom();
	while(1)
	{
		key = halKeypadPushed();
		if(key == 'A' || key == 'B' || key == 'C') CommandZone(key,0);
		halMcuWaitMs(300); 
	}
	
}
/***************************
Client_Program_Order()
1.輸入00~99之間的數值，輸入完按下#(Enter進行儲存)
2.最多自訂8個節目順序
3.完成後傳值，返回
****************************/
void Client_Program_Order(void)
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
halLcdWriteIntToChar(LCD第幾行,的第幾個字,顯示的數值)
可將數值自動轉換為字串顯示在LCD上(限定一個字?未測試)
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
}
/********************
ReadKeyInt()
用數值型態回傳鍵盤值
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
1.判斷要送給哪一區A~F
2.清除LCD，LCD顯示要傳送的點
3.進入CommandAction副程式讀取要進行的模式
4.將資料一併送出
5.預覽全狀態
*************************/
void CommandZone(uint8 zone,uint8 rom)
{
	halBuzzer(100);
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target : 1 2 3");
	switch(zone)
	{
		case 'A':			
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_A ");
			if(rom != 0) pTxData[1] = CommandAction(rom);
			if(rom == 0) pTxData[1] = CommandAction(1);
			ShowMode[0] = pTxData[1];
			M230_WriteEEPROM(0, pTxData[1]);
			basicRfSendPacket(A_ZONE,pTxData,APP_PAYLOAD_LENGTH);
			break;
		case 'B':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_B ");
			if(rom != 0) pTxData[1] = CommandAction(rom);
			if(rom == 0) pTxData[1] = CommandAction(2);
			ShowMode[1] = pTxData[1];
			M230_WriteEEPROM(1, pTxData[1]);
			basicRfSendPacket(B_ZONE,pTxData,APP_PAYLOAD_LENGTH);
			break;
		case 'C':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_C ");
			if(rom != 0) pTxData[1] = CommandAction(rom);
			if(rom == 0) pTxData[1] = CommandAction(3);
			ShowMode[2] = pTxData[1];
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
/****************************
CommandAction(uint8 zone)
1.判斷輸入的模式1~3
2.設定區域地址?
3.LCD顯示
4.回傳模式的數值
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
			Client_Program_Order();
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
顯示當前每個模式所進行的節目(方便監測)
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
	M230	位置		功能
			0			S_A		模式紀錄1 or 2
			1			S_B		""
			2			S_C		""
			10~18     	S_A     MODE2節目紀錄
			20~28   	S_B     ""
			30~38   	S_C     ""
			40~44       S_A     延遲數值紀錄
			50~54       S_B     ""
			60~64       S_C     ""
	**************************************************/
void ReadEEPRom(void)
{
	uint8 ReadMode[3];
	ReadMode[0] = M230_ReadEEPROM(0);
	if(ReadMode[0] == 1) CommandZone('A',1);
	ReadMode[1] = M230_ReadEEPROM(1);
	if(ReadMode[1] == 1) CommandZone('B',1);
	ReadMode[2] = M230_ReadEEPROM(2);
	if(ReadMode[2] == 1) CommandZone('C',1);
}
