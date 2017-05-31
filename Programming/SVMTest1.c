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
	uint8 n;
	char 
    char *10 = convInt32ToText(10);
	for (n = 0; n < 10; n++)
	{
		uint8 v = halButtonPushed();
		if (v == HAL_BUTTON_1,*10)
		{
			pLcdLineBuffer[10] = *(10--);
		}
	}
}