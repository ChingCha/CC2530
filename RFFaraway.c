//專題五過遠偏移程式碼
//--------------------------------------------------------
---------- 
// Filename: ex.c 
// Description: 可變電阻(A/D)範例 
//--------------------------------------------------------
---------- 
//--------------------------------------------------------
---------- 
// INCLUDES 
//--------------------------------------------------------
---------- 
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
#include "hw_54H.h" 
 
//--------------------------------------------------------
---------- 
void main(void) { 
    uint8 key; 
    uint8 z; 
    // Initalise board peripherals 
    halBoardInit(); 

    // Indicate that device is powered 
    halLedSet(8); 
    // Print Logo and splash screen on LCD 
    utilPrintLogo("** M190 Test  **"); 
    halMcuWaitMs(300); 
    halBuzzer(300); 
    while (halKeypadPushed() == 0); 
    utilMenuSelect(NULL); 
    double DATA_END= 0; 
    uint8 DATA_END_1= 0; 
    while (TRUE) { 
        uint16 num=12; 
        uint16 CT = 0; 
        uint16 a = 0; 
        uint8 DATA_TIME = 0; 
        uint16 DATA_ADC; 
        halLcdClear(); 
       // halBuzzer(300); 
        M190_Init(); 
        halLcdWriteLine(HAL_LCD_LINE_1, "**Sersor**"); 
        DATA_END_1 = DATA_END * 10; 
        if(DATA_END < 10)  {num=12;} 
        if(DATA_END > 9)   {num=11;} 
         
        halLcdDisplayUint16(HAL_LCD_LINE_2, num , HAL_LCD_RADIX_DEC , DATA_END ); 
        halLcdWriteString(HAL_LCD_LINE_2, 13, "."); 
        halLcdDisplayUint16(HAL_LCD_LINE_2, 14 , HAL_LCD_RADIX_DEC , DATA_END_1 % 10); 
               
        DATA_ADC = M190_GetValue(); 
              DATA_ADC = DATA_ADC & 0xff00; 
               if(DATA_ADC == 0x4100){ 
        while (TRUE){ //start 
            for(CT=0;CT<230;CT++) { 
               DATA_ADC = M190_GetValue(); 
               DATA_ADC = DATA_ADC & 0xff00; 
                
               if(DATA_ADC == 0x4100) { 
					a+=1; 
					if(a == 1){ 
						DATA_TIME++; 
					} 
					halLcdDisplayUint16(HAL_LCD_LINE_2, 7 , HAL_LCD_RADIX_DEC , DATA_TIME); 
					halLcdDisplayUint16(HAL_LCD_LINE_2, num , HAL_LCD_RADIX_DEC , DATA_END ); 
					halLcdDisplayUint16(HAL_LCD_LINE_2, 1 , HAL_LCD_RADIX_HEX , DATA_ADC); 
				halMcuWaitMs(1) 
               while(a){ 
					DATA_ADC = M190_GetValue(); 
					DATA_ADC = DATA_ADC & 0xff00; 
					if(DATA_ADC != 0x4100){
						a=0;  }
					}
			   }
			}
		}
	}
}
}
