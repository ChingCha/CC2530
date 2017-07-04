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
    halBoardInit();//�{���@�}�l����l�ƨ禡
    halLedSet(8);//�Хܸ˸m�H�q�q
    int32 a = 5;
    while (1)
    {
        uint8 v = halButtonPushed();
		if (v == HAL_BUTTON_1)
		{
			halLcdDisplayWithButton(HAL_LCD_LINE_1,a,'D');
            if(a > 0)
				a--;		
		}
        halMcuWaitMs(300);    
    }
}    

