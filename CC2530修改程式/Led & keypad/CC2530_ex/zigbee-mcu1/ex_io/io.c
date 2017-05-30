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
        if (v == HAL_BUTTON_1)
        {
            halLedSet(1);
            halLedClear(2);
            halLedClear(3);
            halLedClear(4);
            halLedClear(5);
            halLedClear(6);
            halLedClear(7);
            halLedClear(8);
            ch = 1;
            mode = 1;
            halBuzzerOn(800);
            halMcuWaitMs(300);
            halBuzzerOff();
        }
        if (v == HAL_BUTTON_2)
        {
            halLedSet(1);
            halLedClear(2);
            halLedSet(3);
            halLedClear(4);
            halLedSet(5);
            halLedClear(6);
            halLedSet(7);
            halLedClear(8);
            mode = 3;
            halBuzzerOn(2730);
            halMcuWaitMs(300);
            halBuzzerOff();
        }
        if (mode == 1)
        {
            halLedClear(ch);
            ch++;
            halLedSet(ch);
            if (ch >= 8)
            {
                mode = 2;
            }
        }
        else if (mode == 2)
        {
            halLedClear(ch);
            ch--;
            halLedSet(ch);
            if (ch <= 1)
            {
                mode = 1;
            }
        }
        else if (mode == 3)
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
