//-------------------------------------------------------------------
// Filename: system.c
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
#include "hal_keypad.h"
#include "hal_buzzer.h"
#include "hal_uart.h"
#include "util.h"
#include "util_lcd.h"
uint8 ProgramROM[8];
uint8 ProgramText;
uint8 key;
void LcdWrite(void);
void Program(uint8 a);
void Mode(uint8 b);
//-------------------------------------------------------------------
void main(void)
{   
    halBoardInit();
    halBuzzer(300);
    halLcdWriteString(HAL_LCD_LINE_1,0,"Press 1 or 2 Mode");
    //------------------------------------------------------------------------------
    while(halKeypadPushed()==0);
    halLcdClear();
    //------------------------------------------------------------------------------
    while (TRUE)
    {
        key = halKeypadPushed();		
        if (key > 0)
        {
            if (key == '1')
            {
               halBuzzer(250);
               LcdWrite();
               Mode(1);
            }
            if (key == '2')
            {
               halBuzzer(250);
               LcdWrite();
               Mode(2);
            }              
        }
        halMcuWaitMs(300);      
    }
}
void LcdWrite(void)
{
     halLcdWriteString(HAL_LCD_LINE_1,0,"Mode");
     halLcdWriteChar(HAL_LCD_LINE_1, 4, key);
     halLcdWriteString(HAL_LCD_LINE_1,5,",Program");
}
void Mode(uint8 a) //Mode1循環,Mode2輸入節目後依照輸入順序循環
{
    switch(a)
    {
      case 1:
        while(1)
        {
			for(int i = 0;i < 4;i++)
			{
				Program(i+1);
				for(int j = 0;j < 8;j++)
				{
					HAL_LED_PORT(ProgramROM[j]);
					halMcuWaitMs(250);
				}
				halBuzzer(100);
				HAL_LED_PORT(0x00);
				halMcuWaitMs(300);
			}
        }
    }
}
void Program(uint8 b)
{
    switch(b)
    {
		case 1:
			ProgramText = '1';
			halLcdWriteChar(HAL_LCD_LINE_1, 13, ProgramText);
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
			halLcdWriteChar(HAL_LCD_LINE_1, 13, ProgramText);
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
			halLcdWriteChar(HAL_LCD_LINE_1, 13, ProgramText);
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
			halLcdWriteChar(HAL_LCD_LINE_1, 13, ProgramText);
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
