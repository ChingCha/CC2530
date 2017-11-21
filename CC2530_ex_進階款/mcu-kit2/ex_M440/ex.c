//-------------------------------------------------------------------
// Filename: ex.c
// Description: ·ÅÀã«×°»´ú(I2C)½d¨Ò
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
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
#include "M440.h"

//-------------------------------------------------------------------
void main(void)
{ 
    // Initalise board peripherals
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);
    
    // Print Logo and splash screen on LCD
    utilPrintLogo("** M440 Test  **");
    halMcuWaitMs(300);
    //halBuzzer(300);
    
    while (halKeypadPushed() == 0);
    utilMenuSelect(NULL);
    
    while (TRUE)
    {
        halLcdClear();
//        halBuzzer(300);
        M440_Init();
        halLcdWriteLine(HAL_LCD_LINE_1, "X:      Y:      ");
        halLcdWriteLine(HAL_LCD_LINE_2, "Z:              ");
        
        while (TRUE)
        {   
            M440_Pooling();
            
            M440_X_AXIS_Value = 65535 - M440_X_AXIS_Value;
            M440_Y_AXIS_Value = 65535 - M440_Y_AXIS_Value;
            M440_Z_AXIS_Value = 65535 - M440_Z_AXIS_Value;
            
            if(M440_X_AXIS_Value >135 && M440_X_AXIS_Value < 155)
            {
                halLcdWriteString(HAL_LCD_LINE_2, 8, "South"); // Direction North
            }
            if(M440_X_AXIS_Value > 10 && M440_X_AXIS_Value < 25)
            {
                halLcdWriteString(HAL_LCD_LINE_2, 8, "North"); // Direction South
            }
            if(M440_X_AXIS_Value > 175 && M440_X_AXIS_Value < 195)
            {
                halLcdWriteString(HAL_LCD_LINE_2, 8, "East"); // Direction East
            }
            if(M440_X_AXIS_Value > 80 && M440_X_AXIS_Value < 100)
            {
                halLcdWriteString(HAL_LCD_LINE_2, 8, "Western"); // Direction Western
            }
            
            // Show the X,Y,Z value and direction on the LCD
            halLcdDisplayUint16(HAL_LCD_LINE_1, 2, HAL_LCD_RADIX_DEC, M440_X_AXIS_Value); 
            halLcdDisplayUint16(HAL_LCD_LINE_1, 10, HAL_LCD_RADIX_DEC, M440_Y_AXIS_Value);
            halLcdDisplayUint16(HAL_LCD_LINE_2, 2, HAL_LCD_RADIX_DEC, M440_Z_AXIS_Value);
            
        }
    }
}
