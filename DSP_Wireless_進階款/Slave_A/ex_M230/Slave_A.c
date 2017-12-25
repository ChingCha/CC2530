//ZigBee_PRO
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
//#include "Program.h"

//C_Compiler
#include <string.h>

//Local_Define
#define LINE1                           0x00
#define LINE2                           0x40
#define SET_DISPLAY_LINE(line)          lcdControl(0x80 | (line))

// Application parameters
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                	0x1111
#define A_ZONE           		0x2222
#define APP_PAYLOAD_LENGTH        255

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

static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

uint8 key;
uint16 ProgramDelay;
void Program(uint8 b);
void Mode(uint8 a);
uint8 ProgramTextI;
uint8 ProgramROMI[8];
void main(void)
{   
	//uint8 rssi;
	basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 
	halBoardInit();	
	
	halLedSet(8);
    halBuzzer(300);	
	basicRfConfig.myAddr = A_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}	

    basicRfReceiveOn();			
	ProgramDelay = 300;
    halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:S_A");   
    while (TRUE)
	{		
        while (!basicRfPacketIsReady())
		{
            halLedToggle(7);
            halMcuWaitMs(10);
        }				
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
		{						
			switch(pRxData[0])
			{				
				case 0x0001:				
					/*
					rssi = basicRfGetRssi();
					halBuzzer(250);
					//LcdWrite();
					halLcdClear();
					halLcdWriteString(HAL_LCD_LINE_1,0,"Mode");
					halLcdWriteChar(HAL_LCD_LINE_1, 4, '1');
					halLcdWriteString(HAL_LCD_LINE_1,5,",Program");
					halLcdDisplayUint8(HAL_LCD_LINE_2,10,HAL_LCD_RADIX_DEC,rssi);
					halMcuWaitMs(100);
					*/										
					halLcdClear();					
					while( basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
					{						
						if(pRxData[0] != 0x0001)
						{							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;			
						}
						else if(pRxData[0] == 0x0001)
						{							
							Mode(pRxData[1]);
						}
					}				
					break;				
				case 0x0002:				
/*					rssi = basicRfGetRssi();
					halBuzzer(250);
					//LcdWrite();
					halLcdClear();
					halLcdWriteString(HAL_LCD_LINE_1,0,"Mode");
					halLcdWriteChar(HAL_LCD_LINE_1, 4, '2');
					halLcdWriteString(HAL_LCD_LINE_1,5,",Program");
					halLcdDisplayUint8(HAL_LCD_LINE_2,10,HAL_LCD_RADIX_DEC,rssi);
					halMcuWaitMs(100);   
					
					KeyCount = 0;
					halLcdWriteString(HAL_LCD_LINE_2,0,"Input:");
					halMcuWaitMs(300);
						
					Client();
*/					
					halLcdClear();					
					while( basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
					{						
						if(pRxData[0] != 0x0002)
						{							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;								
						}
						else if(pRxData[0] == 0x0002)
						{								
							Mode(pRxData[1]);	
						}
					}				
					break;				
				case 3:					
/*					rssi = basicRfGetRssi();
					KeyCount = 0;
					halLcdWriteString(HAL_LCD_LINE_1,0,"Input Delay:   ");
					halLcdWriteString(HAL_LCD_LINE_2,0,"0000 ms         ");
					halLcdDisplayUint8(HAL_LCD_LINE_2,10,HAL_LCD_RADIX_DEC,rssi);
					halMcuWaitMs(100);
*/		
					halLcdClear();		
					while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
					{						
						if(pRxData[0] != 0x0003)
						{							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;							
						}
						else if(pRxData[0] == 0x0003)
						{						
							Mode(pRxData[1]);						
						}						
					}
					break;				
				default:
					halLcdWriteString(HAL_LCD_LINE_1,0,"Nothing");
			}
		}   
    }
}

void Mode(uint8 a)
{
    switch(a)
    {
		case 1:
			for(uint8 i = 0;i < 4;i++)
			{
				Program(i+1);
				//READProgram(i);
				for(uint8 j = 0;j < 8;j++)
				{
					halLedSetPort(ProgramROMI[j]);
					//LedProgram(j);
					halMcuWaitMs(250);
				}
				halBuzzer(200);
				halLedSetPort(0x00);
				halMcuWaitMs(ProgramDelay);
			}			
			break;		
		case 2:		    
			for(int i = 0;i < 8;i++)
			{
				//READProgram(pRxData[i+2]);
				for(int j = 0;j < 8;j++)
				{
					//LedProgram(j);
					halMcuWaitMs(250);
				}
				halBuzzer(200);
				halLedSetPort(0x00);
				halMcuWaitMs(ProgramDelay);
			}		
			break;		
		case 3:		
			ProgramDelay = pRxData[2] * 1000 + pRxData[3] * 100 + pRxData[4] * 10 + pRxData[5];
			halLcdWriteString(HAL_LCD_LINE_1,0,"Delay_Time");
			halLcdDisplayUint16(HAL_LCD_LINE_2,0,HAL_LCD_RADIX_DEC,ProgramDelay);		
			break;		
    }
}

void Program(uint8 b)
{   
	switch(b)
	{
		case 1:
			ProgramTextI = '1';
			halLcdWriteChar(HAL_LCD_LINE_2, 0, ProgramTextI);
			ProgramROMI[0] = 0x81;
			ProgramROMI[1] = 0x42;
			ProgramROMI[2] = 0x24;
			ProgramROMI[3] = 0x18;
			ProgramROMI[4] = 0x3C;
			ProgramROMI[5] = 0x7E;
			ProgramROMI[6] = 0xFF;
			ProgramROMI[7] = 0x00;
			break;
		case 2:
			ProgramTextI = '2';
			halLcdWriteChar(HAL_LCD_LINE_2, 0, ProgramTextI);
			ProgramROMI[0] = 0x01;
			ProgramROMI[1] = 0x02;
			ProgramROMI[2] = 0x04;
			ProgramROMI[3] = 0x08;
			ProgramROMI[4] = 0x10;
			ProgramROMI[5] = 0x20;
			ProgramROMI[6] = 0x40;
			ProgramROMI[7] = 0x80;
			break;
		case 3:
			ProgramTextI = '3';
			halLcdWriteChar(HAL_LCD_LINE_2, 0, ProgramTextI);
			ProgramROMI[0] = 0x01;
			ProgramROMI[1] = 0x03;
			ProgramROMI[2] = 0x07;
			ProgramROMI[3] = 0x0F;
			ProgramROMI[4] = 0x1F;
			ProgramROMI[5] = 0x3F;
			ProgramROMI[6] = 0x7F;
			ProgramROMI[7] = 0xFF;
			break;
		case 4:
			ProgramTextI = '4';
			halLcdWriteChar(HAL_LCD_LINE_2, 0, ProgramTextI);
			ProgramROMI[0] = 0x11;
			ProgramROMI[1] = 0x00;
			ProgramROMI[2] = 0x33;
			ProgramROMI[3] = 0x00;
			ProgramROMI[4] = 0x77;
			ProgramROMI[5] = 0x00;
			ProgramROMI[6] = 0xFF;
			ProgramROMI[7] = 0x00;
			break;
    }	
}



