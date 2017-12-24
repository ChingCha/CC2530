//-------------------------------------------------------------------
// Filename: Program.c
// Description: I.O.L Program 00~99
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_int.h"
#include "Program.h"
//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
uint8 ProgramText;
uint8 ProgramROM[8];
//-------------------------------------------------------------------
void LedProgram(uint8 a)
{
	halLedSetPort(ProgramROM[a]);
}
void READProgram(uint8 b)
{   
	switch(b)
	{
		case 1:
			ProgramText = '01';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x00;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0x00;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0x00;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x00;
			ProgramROM[7] = 0xFF;
			break;
		case 2:
			ProgramText = '02';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
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
			ProgramText = '03';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x80;
			ProgramROM[1] = 0x40;
			ProgramROM[2] = 0x20;
			ProgramROM[3] = 0x10;
			ProgramROM[4] = 0x08;
			ProgramROM[5] = 0x04;
			ProgramROM[6] = 0x02;
			ProgramROM[7] = 0x01;
			break;
		case 4:
			ProgramText = '04';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x03;
			ProgramROM[2] = 0x07;
			ProgramROM[3] = 0x0F;
			ProgramROM[4] = 0x1F;
			ProgramROM[5] = 0x3F;
			ProgramROM[6] = 0x7F;
			ProgramROM[7] = 0xFF;
			break;
		case 5:
			ProgramText = '05';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x80;
			ProgramROM[1] = 0xC0;
			ProgramROM[2] = 0xE0;
			ProgramROM[3] = 0xF0;
			ProgramROM[4] = 0xF8;
			ProgramROM[5] = 0xFC;
			ProgramROM[6] = 0xFE;
			ProgramROM[7] = 0xFF;
			break;
		case 6:
			ProgramText = '06';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x00;
			break;
		case 7:
			ProgramText = '07';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0xFF;
			break;
		case 8:
			ProgramText = '08';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x88;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x44;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x22;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x11;
			ProgramROM[7] = 0x00;
			break;
		case 9:
			ProgramText = '09';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x88;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0x44;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0x22;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x11;
			ProgramROM[7] = 0xFF;
			break;
		case 10:
			ProgramText = '10';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x81;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x24;
			ProgramROM[3] = 0x18;
			ProgramROM[4] = 0x24;
			ProgramROM[5] = 0x42;
			ProgramROM[6] = 0x81;
			ProgramROM[7] = 0x00;
			break;
		case 11:
			ProgramText = '11';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x81;
			ProgramROM[1] = 0xC3;
			ProgramROM[2] = 0xE7;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xE7;
			ProgramROM[5] = 0xC3;
			ProgramROM[6] = 0x81;
			ProgramROM[7] = 0x00;
			break;
		case 12:
			ProgramText = '12';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x13;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x23;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x43;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x83;
			ProgramROM[7] = 0x00;
			break;
		case 13:
			ProgramText = '13';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x2A;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x4A;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xA8;
			ProgramROM[7] = 0x00;
			break;
		case 14:
			ProgramText = '14';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x71;
			ProgramROM[1] = 0x61;
			ProgramROM[2] = 0x51;
			ProgramROM[3] = 0x41;
			ProgramROM[4] = 0x31;
			ProgramROM[5] = 0x21;
			ProgramROM[6] = 0x11;
			ProgramROM[7] = 0x01;
			break;
		case 15:
			ProgramText = '15';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x17;
			ProgramROM[1] = 0x27;
			ProgramROM[2] = 0x37;
			ProgramROM[3] = 0x47;
			ProgramROM[4] = 0x57;
			ProgramROM[5] = 0x67;
			ProgramROM[6] = 0x77;
			ProgramROM[7] = 0x87;
			break;
		case 16:
			ProgramText = '16';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x7A;
			ProgramROM[1] = 0x6B;
			ProgramROM[2] = 0x5C;
			ProgramROM[3] = 0x4D;
			ProgramROM[4] = 0x3E;
			ProgramROM[5] = 0x2F;
			ProgramROM[6] = 0x10;
			ProgramROM[7] = 0x01;
			break;
		case 17:
			ProgramText = '17';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xC1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xA4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x98;
			ProgramROM[7] = 0x00;
			break;
		case 18:
			ProgramText = '18';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x67;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x68;
			ProgramROM[3] = 0x48;
			ProgramROM[4] = 0x69;
			ProgramROM[5] = 0x54;
			ProgramROM[6] = 0x65;
			ProgramROM[7] = 0x30;
			break;
		case 19:
			ProgramText = '19';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x31;
			ProgramROM[1] = 0x03;
			ProgramROM[2] = 0x32;
			ProgramROM[3] = 0x06;
			ProgramROM[4] = 0x33;
			ProgramROM[5] = 0x09;
			ProgramROM[6] = 0x34;
			ProgramROM[7] = 0x12;
			break;
		case 20:
			ProgramText = '20';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x35;
			ProgramROM[1] = 0x15;
			ProgramROM[2] = 0x36;
			ProgramROM[3] = 0x18;
			ProgramROM[4] = 0x37;
			ProgramROM[5] = 0x21;
			ProgramROM[6] = 0x38;
			ProgramROM[7] = 0x24;
			break;
		case 21:
			ProgramText = '21';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x39;
			ProgramROM[1] = 0x27;
			ProgramROM[2] = 0x41;
			ProgramROM[3] = 0x04;
			ProgramROM[4] = 0x42;
			ProgramROM[5] = 0x08;
			ProgramROM[6] = 0x43;
			ProgramROM[7] = 0x12;
			break;
		case 22:
			ProgramText = '22';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x44;
			ProgramROM[1] = 0x16;
			ProgramROM[2] = 0x45;
			ProgramROM[3] = 0x20;
			ProgramROM[4] = 0x46;
			ProgramROM[5] = 0x24;
			ProgramROM[6] = 0x47;
			ProgramROM[7] = 0x28;
			break;
		case 23:
			ProgramText = '23';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x48;
			ProgramROM[1] = 0x32;
			ProgramROM[2] = 0x49;
			ProgramROM[3] = 0x36;
			ProgramROM[4] = 0x51;
			ProgramROM[5] = 0x05;
			ProgramROM[6] = 0x52;
			ProgramROM[7] = 0x10;
			break;
		case 24:
			ProgramText = '24';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x53;
			ProgramROM[1] = 0x15;
			ProgramROM[2] = 0x54;
			ProgramROM[3] = 0x20;
			ProgramROM[4] = 0x55;
			ProgramROM[5] = 0x25;
			ProgramROM[6] = 0x56;
			ProgramROM[7] = 0x30;
			break;
		case 25:
			ProgramText = '25';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x57;
			ProgramROM[1] = 0x35;
			ProgramROM[2] = 0x58;
			ProgramROM[3] = 0x40;
			ProgramROM[4] = 0x59;
			ProgramROM[5] = 0x45;
			ProgramROM[6] = 0x61;
			ProgramROM[7] = 0x06;
			break;
		case 26:
			ProgramText = '26';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x62;
			ProgramROM[1] = 0x12;
			ProgramROM[2] = 0x63;
			ProgramROM[3] = 0x18;
			ProgramROM[4] = 0x64;
			ProgramROM[5] = 0x24;
			ProgramROM[6] = 0x71;
			ProgramROM[7] = 0x07;
			break;
		case 27:
			ProgramText = '27';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x72;
			ProgramROM[1] = 0x14;
			ProgramROM[2] = 0x73;
			ProgramROM[3] = 0x21;
			ProgramROM[4] = 0x74;
			ProgramROM[5] = 0x28;
			ProgramROM[6] = 0x75;
			ProgramROM[7] = 0x35;
			break;
		case 28:
			ProgramText = '28';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x76;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x77;
			ProgramROM[3] = 0x49;
			ProgramROM[4] = 0x78;
			ProgramROM[5] = 0x56;
			ProgramROM[6] = 0x79;
			ProgramROM[7] = 0x63;
			break;
		case 29:
			ProgramText = '29';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x81;
			ProgramROM[1] = 0x08;
			ProgramROM[2] = 0x82;
			ProgramROM[3] = 0x16;
			ProgramROM[4] = 0x83;
			ProgramROM[5] = 0x24;
			ProgramROM[6] = 0x84;
			ProgramROM[7] = 0x32;
			break;
		case 30:
			ProgramText = '30';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x85;
			ProgramROM[1] = 0x40;
			ProgramROM[2] = 0x86;
			ProgramROM[3] = 0x48;
			ProgramROM[4] = 0x87;
			ProgramROM[5] = 0x56;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x64;
			break;
		case 31:
			ProgramText = '31';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x89;
			ProgramROM[1] = 0x72;
			ProgramROM[2] = 0x91;
			ProgramROM[3] = 0x09;
			ProgramROM[4] = 0x92;
			ProgramROM[5] = 0x18;
			ProgramROM[6] = 0x93;
			ProgramROM[7] = 0x27;
			break;
		case 32:
			ProgramText = '32';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x94;
			ProgramROM[1] = 0x36;
			ProgramROM[2] = 0x95;
			ProgramROM[3] = 0x48;
			ProgramROM[4] = 0x96;
			ProgramROM[5] = 0x54;
			ProgramROM[6] = 0x97;
			ProgramROM[7] = 0x63;
			break;
		case 33:
			ProgramText = '33';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x98;
			ProgramROM[1] = 0x72;
			ProgramROM[2] = 0x99;
			ProgramROM[3] = 0x81;
			ProgramROM[4] = 0xA1;
			ProgramROM[5] = 0x0A;
			ProgramROM[6] = 0xA2;
			ProgramROM[7] = 0x20;
			break;
		case 34:
			ProgramText = '34';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xA3;
			ProgramROM[1] = 0x30;
			ProgramROM[2] = 0xA4;
			ProgramROM[3] = 0x40;
			ProgramROM[4] = 0xA5;
			ProgramROM[5] = 0x50;
			ProgramROM[6] = 0xA6;
			ProgramROM[7] = 0x60;
			break;
		case 35:
			ProgramText = '35';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xA7;
			ProgramROM[1] = 0x70;
			ProgramROM[2] = 0xA8;
			ProgramROM[3] = 0x80;
			ProgramROM[4] = 0xA9;
			ProgramROM[5] = 0x90;
			ProgramROM[6] = 0xB1;
			ProgramROM[7] = 0x11;
			break;
		case 36:
			ProgramText = '36';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xB2;
			ProgramROM[1] = 0x22;
			ProgramROM[2] = 0xB3;
			ProgramROM[3] = 0x33;
			ProgramROM[4] = 0xB4;
			ProgramROM[5] = 0x44;
			ProgramROM[6] = 0xB5;
			ProgramROM[7] = 0x55;
			break;
		case 37:
			ProgramText = '37';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xB6;
			ProgramROM[1] = 0x66;
			ProgramROM[2] = 0xB7;
			ProgramROM[3] = 0x77;
			ProgramROM[4] = 0xB8;
			ProgramROM[5] = 0x88;
			ProgramROM[6] = 0xB9;
			ProgramROM[7] = 0x99;
			break;
		case 38:
			ProgramText = '38';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x21;
			ProgramROM[1] = 0x02;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x04;
			ProgramROM[4] = 0x23;
			ProgramROM[5] = 0x06;
			ProgramROM[6] = 0x24;
			ProgramROM[7] = 0x08;
			break;
		case 39:
			ProgramText = '39';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x25;
			ProgramROM[1] = 0x10;
			ProgramROM[2] = 0x26;
			ProgramROM[3] = 0x12;
			ProgramROM[4] = 0x27;
			ProgramROM[5] = 0x14;
			ProgramROM[6] = 0x28;
			ProgramROM[7] = 0x16;
			break;
		case 40:
			ProgramText = '40';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x29;
			ProgramROM[1] = 0x18;
			ProgramROM[2] = 0x2A;
			ProgramROM[3] = 0x08;
			ProgramROM[4] = 0xC8;
			ProgramROM[5] = 0x76;
			ProgramROM[6] = 0x03;
			ProgramROM[7] = 0x74;
			break;
		case 41:
			ProgramText = '41';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x61;
			ProgramROM[1] = 0x50;
			ProgramROM[2] = 0x2D;
			ProgramROM[3] = 0xD5;
			ProgramROM[4] = 0x4B;
			ProgramROM[5] = 0x06;
			ProgramROM[6] = 0x98;
			ProgramROM[7] = 0x34;
			break;
		case 42:
			ProgramText = '42';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x03;
			ProgramROM[2] = 0x05;
			ProgramROM[3] = 0x07;
			ProgramROM[4] = 0x09;
			ProgramROM[5] = 0x11;
			ProgramROM[6] = 0x13;
			ProgramROM[7] = 0x15;
			break;
		case 43:
			ProgramText = '43';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x17;
			ProgramROM[1] = 0x19;
			ProgramROM[2] = 0x21;
			ProgramROM[3] = 0x23;
			ProgramROM[4] = 0x25;
			ProgramROM[5] = 0x27;
			ProgramROM[6] = 0x29;
			ProgramROM[7] = 0x31;
			break;
		case 44:
			ProgramText = '44';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x33;
			ProgramROM[1] = 0x35;
			ProgramROM[2] = 0x37;
			ProgramROM[3] = 0x39;
			ProgramROM[4] = 0x41;
			ProgramROM[5] = 0x43;
			ProgramROM[6] = 0x45;
			ProgramROM[7] = 0x47;
			break;
		case 45:
			ProgramText = '45';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x51;
			ProgramROM[1] = 0x53;
			ProgramROM[2] = 0x55;
			ProgramROM[3] = 0x57;
			ProgramROM[4] = 0x59;
			ProgramROM[5] = 0x61;
			ProgramROM[6] = 0x63;
			ProgramROM[7] = 0x65;
			break;
		case 46:
			ProgramText = '46';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x67;
			ProgramROM[1] = 0x69;
			ProgramROM[2] = 0x71;
			ProgramROM[3] = 0x73;
			ProgramROM[4] = 0x75;
			ProgramROM[5] = 0x77;
			ProgramROM[6] = 0x79;
			ProgramROM[7] = 0x81;
			break;
		case 47:
			ProgramText = '47';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x83;
			ProgramROM[1] = 0x85;
			ProgramROM[2] = 0x87;
			ProgramROM[3] = 0x89;
			ProgramROM[4] = 0x91;
			ProgramROM[5] = 0x93;
			ProgramROM[6] = 0x95;
			ProgramROM[7] = 0x97;
			break;
		case 48:
			ProgramText = '48';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x99;
			ProgramROM[1] = 0x02;
			ProgramROM[2] = 0x03;
			ProgramROM[3] = 0x05;
			ProgramROM[4] = 0x07;
			ProgramROM[5] = 0x11;
			ProgramROM[6] = 0x13;
			ProgramROM[7] = 0x17;
			break;
		case 49:
			ProgramText = '49';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x19;
			ProgramROM[1] = 0x23;
			ProgramROM[2] = 0x29;
			ProgramROM[3] = 0x31;
			ProgramROM[4] = 0x37;
			ProgramROM[5] = 0x41;
			ProgramROM[6] = 0x43;
			ProgramROM[7] = 0x47;
			break;
		case 50:
			ProgramText = '50';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x51;
			ProgramROM[1] = 0x53;
			ProgramROM[2] = 0x57;
			ProgramROM[3] = 0x59;
			ProgramROM[4] = 0x61;
			ProgramROM[5] = 0x67;
			ProgramROM[6] = 0x71;
			ProgramROM[7] = 0x73;
			break;
		case 51:
			ProgramText = '51';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x77;
			ProgramROM[1] = 0x79;
			ProgramROM[2] = 0x83;
			ProgramROM[3] = 0x87;
			ProgramROM[4] = 0x89;
			ProgramROM[5] = 0x91;
			ProgramROM[6] = 0x97;
			ProgramROM[7] = 0x00;
			break;
		case 52:
			ProgramText = '52';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xC4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xD8;
			ProgramROM[7] = 0x00;
			break;
		case 53:
			ProgramText = '53';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x1A;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x2B;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x4C;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x8D;
			ProgramROM[7] = 0x00;
			break;
		case 54:
			ProgramText = '54';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xC4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xD8;
			ProgramROM[7] = 0xFF;
			break;
		case 55:
			ProgramText = '55';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x1A;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0x2B;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0x4C;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x8D;
			ProgramROM[7] = 0xFF;
			break;
		case 56:
			ProgramText = '56';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x19;
			ProgramROM[1] = 0x28;
			ProgramROM[2] = 0x37;
			ProgramROM[3] = 0x45;
			ProgramROM[4] = 0x55;
			ProgramROM[5] = 0x64;
			ProgramROM[6] = 0x73;
			ProgramROM[7] = 0x82;
			break;
		case 57:
			ProgramText = '57';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0xB0;
			ProgramROM[2] = 0xC2;
			ProgramROM[3] = 0xD0;
			ProgramROM[4] = 0xE4;
			ProgramROM[5] = 0xF0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x10;
			break;
		case 58:
			ProgramText = '58';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x1A;
			ProgramROM[1] = 0x0B;
			ProgramROM[2] = 0x2C;
			ProgramROM[3] = 0x0D;
			ProgramROM[4] = 0x4E;
			ProgramROM[5] = 0x0F;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x01;
			break;
		case 59:
			ProgramText = '59';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x01;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x02;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x16;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x64;
			break;
		case 60:
			ProgramText = '60';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x76;
			ProgramROM[1] = 0x54;
			ProgramROM[2] = 0x32;
			ProgramROM[3] = 0x10;
			ProgramROM[4] = 0x01;
			ProgramROM[5] = 0x02;
			ProgramROM[6] = 0x04;
			ProgramROM[7] = 0x06;
			break;
		case 61:
			ProgramText = '61';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x08;
			ProgramROM[1] = 0x10;
			ProgramROM[2] = 0x12;
			ProgramROM[3] = 0x14;
			ProgramROM[4] = 0x16;
			ProgramROM[5] = 0x18;
			ProgramROM[6] = 0x20;
			ProgramROM[7] = 0x22;
			break;
		case 62:
			ProgramText = '62';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x24;
			ProgramROM[1] = 0x26;
			ProgramROM[2] = 0x28;
			ProgramROM[3] = 0x30;
			ProgramROM[4] = 0x32;
			ProgramROM[5] = 0x34;
			ProgramROM[6] = 0x36;
			ProgramROM[7] = 0x38;
			break;
		case 63:
			ProgramText = '63';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x40;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x44;
			ProgramROM[3] = 0x46;
			ProgramROM[4] = 0x48;
			ProgramROM[5] = 0x50;
			ProgramROM[6] = 0x52;
			ProgramROM[7] = 0x54;
			break;
		case 64:
			ProgramText = '64';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x56;
			ProgramROM[1] = 0x58;
			ProgramROM[2] = 0x60;
			ProgramROM[3] = 0x62;
			ProgramROM[4] = 0x64;
			ProgramROM[5] = 0x68;
			ProgramROM[6] = 0x70;
			ProgramROM[7] = 0x72;
			break;
		case 65:
			ProgramText = '65';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x74;
			ProgramROM[1] = 0x76;
			ProgramROM[2] = 0x78;
			ProgramROM[3] = 0x80;
			ProgramROM[4] = 0x82;
			ProgramROM[5] = 0x84;
			ProgramROM[6] = 0x86;
			ProgramROM[7] = 0x88;
			break;
		case 66:
			ProgramText = '66';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x90;
			ProgramROM[1] = 0x92;
			ProgramROM[2] = 0x94;
			ProgramROM[3] = 0x96;
			ProgramROM[4] = 0x98;
			ProgramROM[5] = 0xA0;
			ProgramROM[6] = 0x82;
			ProgramROM[7] = 0x83;
			break;
		case 67:
			ProgramText = '67';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xC8;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xC4;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xC2;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xC1;
			ProgramROM[7] = 0x00;
			break;
		case 68:
			ProgramText = '68';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xC8;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xC2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xC4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xC8;
			ProgramROM[7] = 0xFF;
			break;
		case 69:
			ProgramText = '69';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x1C;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x2C;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x4C;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x8C;
			ProgramROM[7] = 0x00;
			break;
		case 70:
			ProgramText = '70';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x0C;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0xC0;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x0C;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0xC0;
			break;
		case 71:
			ProgramText = '71';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xA2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xA4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xA8;
			ProgramROM[7] = 0x00;
			break;
		case 72:
			ProgramText = '72';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x1A;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0x2A;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0x4A;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x8A;
			ProgramROM[7] = 0xFF;
			break;
		case 73:
			ProgramText = '73';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xA0;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x0A;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xA0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x0A;
			break;
		case 74:
			ProgramText = '74';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xB1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xB4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xB8;
			ProgramROM[7] = 0x00;
			break;
		case 75:
			ProgramText = '75';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xB1;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xB4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xB8;
			ProgramROM[7] = 0xFF;
			break;
		case 76:
			ProgramText = '76';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xB0;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x0B;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xB0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x0B;
			break;
		case 77:
			ProgramText = '77';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xD1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xD2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xD4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xD8;
			ProgramROM[7] = 0x00;
			break;
		case 78:
			ProgramText = '78';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xD1;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xD2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xD4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xD8;
			ProgramROM[7] = 0xFF;
			break;
		case 79:
			ProgramText = '79';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xD0;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x0D;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xD0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x0D;
			break;
		case 80:
			ProgramText = '80';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xE1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xE2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xE4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xE8;
			ProgramROM[7] = 0x00;
			break;
		case 81:
			ProgramText = '81';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xE1;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xE2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xE4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xE8;
			ProgramROM[7] = 0xFF;
			break;
		case 82:
			ProgramText = '82';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xE0;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x0E;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xE0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x0E;
			break;
		case 83:
			ProgramText = '83';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xF1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xF2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xF4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xF8;
			ProgramROM[7] = 0x00;
			break;
		case 84:
			ProgramText = '84';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x1F;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x2F;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x4F;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x8F;
			ProgramROM[7] = 0x00;
			break;
		case 85:
			ProgramText = '85';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xFF;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xFF;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xFF;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xFF;
			ProgramROM[7] = 0x00;
			break;
		case 86:
			ProgramText = '86';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x11;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x11;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x11;
			ProgramROM[7] = 0x00;
			break;
		case 87:
			ProgramText = '87';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x22;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x22;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x22;
			ProgramROM[7] = 0x00;
			break;
		case 88:
			ProgramText = '88';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x44;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x44;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x44;
			ProgramROM[7] = 0x00;
			break;
		case 89:
			ProgramText = '89';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x88;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x88;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x88;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x00;
			break;
		case 90:
			ProgramText = '90';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x10;
			ProgramROM[1] = 0x24;
			ProgramROM[2] = 0x05;
			ProgramROM[3] = 0x12;
			ProgramROM[4] = 0x02;
			ProgramROM[5] = 0x56;
			ProgramROM[6] = 0x01;
			ProgramROM[7] = 0x28;
			break;
		case 91:
			ProgramText = '91';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x00;
			ProgramROM[1] = 0x64;
			ProgramROM[2] = 0x00;
			ProgramROM[3] = 0x32;
			ProgramROM[4] = 0x00;
			ProgramROM[5] = 0x16;
			ProgramROM[6] = 0x00;
			ProgramROM[7] = 0x08;
			break;
		case 92:
			ProgramText = '92';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x00;
			ProgramROM[1] = 0x04;
			ProgramROM[2] = 0x00;
			ProgramROM[3] = 0x02;
			ProgramROM[4] = 0x00;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x00;
			break;
		case 93:
			ProgramText = '93';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x93;
			ProgramROM[1] = 0x39;
			ProgramROM[2] = 0x84;
			ProgramROM[3] = 0x48;
			ProgramROM[4] = 0x75;
			ProgramROM[5] = 0x57;
			ProgramROM[6] = 0x65;
			ProgramROM[7] = 0x56;
			break;
		case 94:
			ProgramText = '94';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x94;
			ProgramROM[1] = 0x49;
			ProgramROM[2] = 0x85;
			ProgramROM[3] = 0x58;
			ProgramROM[4] = 0x76;
			ProgramROM[5] = 0x67;
			ProgramROM[6] = 0x68;
			ProgramROM[7] = 0x86;
			break;
		case 95:
			ProgramText = '95';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x31;
			ProgramROM[1] = 0x13;
			ProgramROM[2] = 0x25;
			ProgramROM[3] = 0x52;
			ProgramROM[4] = 0xC8;
			ProgramROM[5] = 0x8C;
			ProgramROM[6] = 0x76;
			ProgramROM[7] = 0x67;
			break;
		case 96:
			ProgramText = '96';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xD8;
			ProgramROM[1] = 0x8D;
			ProgramROM[2] = 0xB7;
			ProgramROM[3] = 0x7B;
			ProgramROM[4] = 0x6A;
			ProgramROM[5] = 0xA6;
			ProgramROM[6] = 0x5F;
			ProgramROM[7] = 0xF5;
			break;
		case 97:
			ProgramText = '97';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0xE4;
			ProgramROM[1] = 0x4E;
			ProgramROM[2] = 0xA8;
			ProgramROM[3] = 0x9C;
			ProgramROM[4] = 0x67;
			ProgramROM[5] = 0x77;
			ProgramROM[6] = 0x96;
			ProgramROM[7] = 0x53;
			break;
		case 98:
			ProgramText = '98';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x98;
			ProgramROM[1] = 0x89;
			ProgramROM[2] = 0x88;
			ProgramROM[3] = 0x86;
			ProgramROM[4] = 0x40;
			ProgramROM[5] = 0x04;
			ProgramROM[6] = 0x69;
			ProgramROM[7] = 0x96;
			break;
		case 99:
			ProgramText = '99';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x70;
			ProgramROM[1] = 0x06;
			ProgramROM[2] = 0x50;
			ProgramROM[3] = 0x04;
			ProgramROM[4] = 0x30;
			ProgramROM[5] = 0x02;
			ProgramROM[6] = 0x10;
			ProgramROM[7] = 0x08;
			break;
		case 0:
			ProgramText = '00';
			halLcdWriteChar(HAL_LCD_LINE_2, 1, ProgramText);
			ProgramROM[0] = 0x00;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x00;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x00;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x00;
			ProgramROM[7] = 0x00;
			break;
    }	
}