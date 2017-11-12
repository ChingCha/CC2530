//-------------------------------------------------------------------
// Filename: M330.c
// Description: hal M330 module library 紅外線接收發射模組(DI)
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M330.h"

uint8 M330_Buf[4];
uint16 M330_Val;
//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
// @fn      M330_Init
// @return  none
//-------------------------------------------------------------------
void M330_Init(void)
{
    HAL_IRIN_DIR_IN();
    HAL_IRLED_DIR_OUT();
}

//-------------------------------------------------------------------
void M330_Wait(uint8 usec)
{
    usec >>= 1;
    while (usec--)
    {
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
    }
}

//-------------------------------------------------------------------
void M330_TX(uint8 delay)
{
    uint8 i;
    
    for(i=0;i<delay;i++)
    {
        HAL_IRLED_ON();
        M330_Wait(28);
        HAL_IRLED_OFF();
        M330_Wait(28);
    }
}

//-------------------------------------------------------------------
void M330_NTX(uint8 delay)
{
    uint8 i;
    
    for(i=0;i<delay;i++)
    {
        HAL_IRLED_OFF();
        M330_Wait(28);
        HAL_IRLED_OFF();
        M330_Wait(28);
    }
}

//-------------------------------------------------------------------
void M330_SendCode(uint16 val)
{
    uint8 i;
    
    for(i=0;i<12;i++)
    {
        if((val&(0x0800 >> i))==0)
        {
            M330_TX(15);
            M330_NTX(48);
        }
        else
        {
            M330_TX(48);
            M330_NTX(15);
        }
    }
}

//-------------------------------------------------------------------
// @fn      M330_GetValue
// @brief   Get this M330 module value
// @param   none
// @return  none
//-------------------------------------------------------------------
uint8 M330_GetData(void)
{    
    uint8 i, n;
    uint16 j;

    M330_Val=0;
    i = 0;
    while (TRUE)
    {
        if (HAL_IRIN() == 0)
        {
            break;
        }
        M330_Wait(50);
        j++;
        if (j > 2000)
        {
            return 0;
        }
    }
    for (n = 0; n <12; n++)
    {
        i = 0;
        while (TRUE)
        {
            if (HAL_IRIN() != 0)
            {                
                if (i>40)
                {
                    M330_Val |= (0x0800 >> n);
                }
                if(n==11)
                    return 1;
                break;
            }
            M330_Wait(50);
            i++;
            if (i > 200)
            {
                return 0;
            }
        }
        i=0;
        while (TRUE)
        {
            if (HAL_IRIN() == 0)
            {
                break;
            }
            halMcuWaitUs(50);
            i++;
            if (i > 200)
            {
                return 0;
            }
        }
    }
    return 1;
}
