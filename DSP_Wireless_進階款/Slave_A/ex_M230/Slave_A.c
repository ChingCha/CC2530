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
#define A_ZONE           		0x2222		//Slave-A位址
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
static basicRfCfg_t basicRfConfig;			//宣告RFConfig組態

uint8 ProgramROM[8];
uint8 ProgramText;
uint8 key;
uint16 ProgramDelay;

void Program(uint8 b);
void Mode(uint8 a);

void main(void){   

	uint8 rssi;

	basicRfConfig.panId = PAN_ID;			//指定RF ID
    basicRfConfig.channel = RF_CHANNEL;		//指定RF Channel
    basicRfConfig.ackRequest = TRUE;		//封包傳遞會有ACK回應
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;	//封包傳遞安全機制
    #endif 

	//初始化板子
	halBoardInit();
	
	//已通電提示
	halLedSet(8);
    halBuzzer(300);
	
	basicRfConfig.myAddr = A_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	//使RF接收端為常開
    basicRfReceiveOn();		
	
	ProgramDelay = 300;
    halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:S_A");
    
    while (TRUE){
		
        while (!basicRfPacketIsReady()){
            halLedToggle(7);
            halMcuWaitMs(10);
        }
		
		
		//將RSSI參數塞到API_basicRfReceive()，進行被動式擴充
		
		//實際複製到緩衝區的字節數
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
						
			//將RSSI參數塞到switch(pRxData[0])，進行主動式擴充
			switch(pRxData[0]){
				
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
					
					while( basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
						
						if(pRxData[0] != 0x0001){
							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;
			
						}else if(pRxData[0] == 0x0001){
							
							//Mode()以無線封包代替
							Mode(pRxData[1]);
						}
					}
				
				break;
				
				case 0x0002:
				
					/*
					rssi = basicRfGetRssi();
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
					
					while( basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
						
						if(pRxData[0] != 0x0002){
							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;
								
						}else if(pRxData[0] == 0x0002){
								
							Mode(pRxData[5]);	
						}
					}
				
				break;
				
				case 3:
					
					/*
					rssi = basicRfGetRssi();
					KeyCount = 0;
					halLcdWriteString(HAL_LCD_LINE_1,0,"Input Delay:   ");
					halLcdWriteString(HAL_LCD_LINE_2,0,"0000 ms         ");
					halLcdDisplayUint8(HAL_LCD_LINE_2,10,HAL_LCD_RADIX_DEC,rssi);
					halMcuWaitMs(100);
					*/
		
					halLcdClear();
		
					while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
						
						if(pRxData[0] != 0x0003){
							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;
							
						}else if(pRxData[0] == 0x0003){
						
							Mode(pRxData[2]);
						
						}
						
					}

				break;
				
				default:
				
					halLcdWriteString(HAL_LCD_LINE_1,0,"Nothing");
			}
		}   
    }
}

void Mode(uint8 a){
    switch(a)
    {
		case 1:

			for(int i = 0;i < 4;i++)
			{
				Program(i+1);
				for(int j = 0;j < 8;j++)
				{
					halLedSetPort(ProgramROM[j]);
					halMcuWaitMs(250);
				}
				halBuzzer(200);
				halLedSetPort(0x00);
				halMcuWaitMs(ProgramDelay);
			}
			
		break;
		
		case 2:
		    
			for(int i = 0;i < 4;i++)
			{
				Program(pRxData[i+1]);
				for(int j = 0;j < 8;j++)
				{
					halLedSetPort(ProgramROM[j]);
					halMcuWaitMs(250);
				}
				halBuzzer(200);
				halLedSetPort(0x00);
				halMcuWaitMs(ProgramDelay);
			}
		
		break;
		
		case 3:
		
			ProgramDelay = pRxData[1] * 1000;
			halLcdWriteString(HAL_LCD_LINE_1,0,"Delay_Time");
			halLcdDisplayUint16(HAL_LCD_LINE_2,0,HAL_LCD_RADIX_DEC,ProgramDelay);
		
		break;
		
    }
}

void Program(uint8 b){
    
	switch(b){
		case 1:
			ProgramText = '1';
			halLcdWriteChar(HAL_LCD_LINE_2, 0, ProgramText);
			ProgramROM[0] = 0x81;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x24;
			ProgramROM[3] = 0x18;
			ProgramROM[4] = 0x3C;
			ProgramROM[5] = 0x7E;
			ProgramROM[6] = 0xFF;
			ProgramROM[7] = 0x00;
			break;
		case 2:
			ProgramText = '2';
			halLcdWriteChar(HAL_LCD_LINE_2, 0, ProgramText);
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x02;
			ProgramROM[2] = 0x04;
			ProgramROM[3] = 0x08;
			ProgramROM[4] = 0x10;
			ProgramROM[5] = 0x20;
			ProgramROM[6] = 0x40;
			ProgramROM[7] = 0x80;
			break;
		case 3:
			ProgramText = '3';
			halLcdWriteChar(HAL_LCD_LINE_2, 0, ProgramText);
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x03;
			ProgramROM[2] = 0x07;
			ProgramROM[3] = 0x0F;
			ProgramROM[4] = 0x1F;
			ProgramROM[5] = 0x3F;
			ProgramROM[6] = 0x7F;
			ProgramROM[7] = 0xFF;
			break;
		case 4:
			ProgramText = '4';
			halLcdWriteChar(HAL_LCD_LINE_2, 0, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x33;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x77;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xFF;
			ProgramROM[7] = 0x00;
			break;
    }	
}



