//長按按鈕機制
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_buzzer.h"
#include "hal_uart.h"
#include "hal_button.h"
#include "hal_int.h"
#include "util.h"
#include "util_lcd.h"

void main(void)
{
    halBoardInit();//程式一開始的初始化函式
    halLedSet(8);//標示裝置以通電
    int32 w = 5;
	int32 m = 10;
    while (1)
    {
        uint8 v = halButtonPushed();
		if (v == HAL_BUTTON_1){
			halLcdDisplayWithButton(HAL_LCD_LINE_1,w,'W');
            if(w > 0)
				w--;		
		}
		else if(v == HAL_BUTTON_2){
			halLcdDisplayWithButton(HAL_LCD_LINE_2,m,'M');
			if(m > 0)
				m--;
		}
        halMcuWaitMs(300);    
    }
}    

