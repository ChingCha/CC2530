//飲料函數意義

#include "hal_drink.h"
#include "hal_ledmatrix.h"
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "util.h"
#include <string.h>
//-------------------------------------------------------------------
// CONSTANTS AND DEFINES
//-------------------------------------------------------------------
// LCD instruction set definitions

// Function set
#define DOT_5X10_OFF                    0x00
#define DOT_5X10_ON                     0x04
#define DUAL_LINE_OFF                   0x00
#define DUAL_LINE_ON                    0x08
#define BUS_8BIT_OFF                    0x00
#define BUS_8BIT_ON                     0x10
#define FUNCTION_SET(options)           lcdControl(0x20 | (options))

// Display clear
#define DISPLAY_CLEAR()                 lcdControl(0x01)

// Set display control
#define DISPLAY_CTRL_ON                 0x04
#define DISPLAY_CTRL_OFF                0x00
#define DISPLAY_CTRL_BLINK_ON           0x01
#define DISPLAY_CTRL_BLINK_OFF          0x00
#define DISPLAY_CTRL_CURSOR_ON          0x02
#define DISPLAY_CTRL_CURSOR_OFF         0x00
#define SET_DISPLAY_CTRL(options)       lcdControl(0x08 | (options))

// Set enter mode
#define INCREMENT_ON                    0x02
#define INCREMENT_OFF                   0x00
#define DISPLAY_SHIFT_ON                0x01
#define DISPLAY_SHIFT_OFF               0x00
#define SET_ENTER_MODE(options)         lcdControl(0x04 | (options))

// Set display control
#define SHITF_DISPLAY_ON                0x04
#define SHITF_DISPLAY_OFF               0x00
#define SHITF_RIGHT_ON                  0x02
#define SHITF_RIGHT_OFF                 0x00
#define SET_CURSOR_SHIFT(options)       lcdControl(0x10 | (options))

// Set Display Start Line
#define LINE1                           0x00
#define LINE2                           0x40
#define SET_DISPLAY_LINE(line)          lcdControl(0x80 | (line))

// Set DD/CGRAM address
#define SET_DDRAM_ADDR(charIndex)       lcdControl(0x80 | (charIndex))
#define SET_GCRAM_CHAR(specIndex)       lcdControl(0x40 | (specIndex))

// LCD lines
#define LCD_LINE_COUNT                  2
#define LCD_LINE_LENGTH                 16

void A_water(int A_drinkw){
	halLcdDisplayWithVM(HAL_LCD_LINE_1,'W',A_drinkw);
	MAX7219_Write(DIGIT0,0x01);
}

void A_milk(int A_drinkm){
	halLcdDisplayWithVM(HAL_LCD_LINE_2,'M',A_drinkm);
	MAX7219_Write(DIGIT1,0x02);
}
void B_greentea(int B_drinkg){
	halLcdDisplayWithVM(HAL_LCD_LINE_1,'G',B_drinkg);
}		
void B_blacktea(int B_drinkb){
	halLcdDisplayWithVM(HAL_LCD_LINE_2,'B',B_drinkb);
}	