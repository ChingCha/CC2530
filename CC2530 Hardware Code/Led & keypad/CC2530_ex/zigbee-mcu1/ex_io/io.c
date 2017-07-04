//-------------------------------------------------------------------
// Filename: io.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_button.h"
#include "hal_buzzer.h"

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "io" application.
// @return      none
//-------------------------------------------------------------------
void main(void)
{
    uint8 ch, mode;
    // Initalise board peripherals
    halBoardInit();

    halLedSet(1);
    ch = 1;
    mode = 1;
    // Wait for user to press S1,S2 to set LED and Buzzer
    while (1)
    {
        uint8 v = halButtonPushed();
        if (v == HAL_BUTTON_1)	//左邊按鈕按下會從最右邊0LED開始
        {
            halLedSet(1);
            halLedClear(2);
            halLedClear(3);
            halLedClear(4);
            halLedClear(5);
            halLedClear(6);
            halLedClear(7);
            halLedClear(8);
            ch = 1;				//halLedClear引數：ch = 1
            mode = 1;			//LED模式引數：mode = 1
            halBuzzerOn(800);
            halMcuWaitMs(300);
            halBuzzerOff();
        }
        if (v == HAL_BUTTON_2)	//右邊按鈕按下，奇數偶數燈相互亮滅
        {
            halLedSet(1);
            halLedClear(2);
            halLedSet(3);
            halLedClear(4);
            halLedSet(5);
            halLedClear(6);
            halLedSet(7);
            halLedClear(8);
            mode = 3;			//LED模式引數：mode = 3
            halBuzzerOn(2730);
            halMcuWaitMs(300);
            halBuzzerOff();
        }
        if (mode == 1)			//LED模式引數：mode = 1 ： 遞增
        {
            halLedClear(ch);
            ch++;				//halLedClear引數ch遞增
            halLedSet(ch);
            if (ch >= 8)		//halLedClear由右至左clear到最後一顆燈，觸發mode：2
            {
                mode = 2;		
            }
        }
        else if (mode == 2)		//LED模式引數：mode = 2 ： 遞減
        {
            halLedClear(ch);
            ch--;				//halLedClear引數ch遞減
            halLedSet(ch);
            if (ch <= 1)
            {
                mode = 1;		//halLedClear由左至右clear到最後一顆燈，觸發mode：1
            }
        }
        else if (mode == 3)		//LED模式引數：mode = 3 ： 
        {
            halLedToggle(1);
            halLedToggle(2);
            halLedToggle(3);
            halLedToggle(4);
            halLedToggle(5);
            halLedToggle(6);
            halLedToggle(7);
            halLedToggle(8);
            halMcuWaitMs(150);
        }

        halMcuWaitMs(50);
    }
}
