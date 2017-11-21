//-------------------------------------------------------------------
// Filename: basic.c
// Description: 
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

#include "M140.h"
#include "M180.h"
#include "M230.h"
#include "M190.h"
#include "M170.h"
#include "M270.h"
#include "M160.h"
#include "M220.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                  25      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                      0x2007
#define SWITCH_ADDR                 0x2520
#define LIGHT_ADDR                  0xBEEF
#define APP_PAYLOAD_LENGTH          1
#define LIGHT_TOGGLE_CMD            '0'
#define LIGHT1_TOGGLE_CMD           '1'
#define LIGHT2_TOGGLE_CMD           '2'
#define LIGHT_UP_CMD                'U'
#define LIGHT_DN_CMD                'D'

// Application role
#define EX_NONE                     0
#define EX_SWITCH                   1
#define EX_LIGHT                    2
#define EX_M140                     3
#define EX_M180                     4
#define EX_M230                     5
#define EX_M190                     6
#define EX_M170                     7
#define EX_M270                     8
#define EX_M160                     9
#define EX_M220                     10

#define APP_MODES                   10

//-------------------------------------------------------------------
// LOCAL VARIABLES

static uint8 pTxData[APP_PAYLOAD_LENGTH];
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

// Mode menu
static menuItem_t pMenuItems[] = 
{
    "Switch", EX_SWITCH, "Light", EX_LIGHT, "M140 Test", EX_M140, "M180 Test", EX_M180, "M230 Test", EX_M230, "M190 Test", EX_M190, "M170 Test", EX_M170, "M270 Test", EX_M270, "M160 Test", EX_M160, "M220 Test", EX_M220
};

static menu_t pMenu = 
{
    pMenuItems, N_ITEMS(pMenuItems)
};


#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif 

//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------
void exLight(void);
void exSwitch(void);
void exM140(void);
void exM180(void);
void exM230(void);
void exM190(void);
void exM170(void);
void exM270(void);
void exM160(void);
void exM220(void);
uint8 exSelect(void);

//-------------------------------------------------------------------
// @fn          exLight
// @brief       Application code for light application. Puts MCU in endless
//              loop waiting for user input from joystick.
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pRxData - file scope variable. Pointer to buffer for RX data
// @return      none
//-------------------------------------------------------------------
void exLight(void)
{
    uint8 duty = 50;
    uint8 toggle = 1;

    M160_Init();
    M160_On(duty);
    halLcdWriteLine(HAL_LCD_LINE_1, "[M160]+[RF]");
    halLcdWriteLine(HAL_LCD_LINE_2, "Light Ready");

    // Initialize BasicRF
    basicRfConfig.myAddr = LIGHT_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED)
    {
        HAL_ASSERT("RfConfig Error!");
    }
    basicRfReceiveOn();

    // Main loop
    while (TRUE)
    {
        uint8 key;
        while (!basicRfPacketIsReady())
        {
            key = halKeypadPushed();
            if (key == '*')
            {
                break;
            }
        }
        if (key == '*')
        {
            break;
        }

        if (basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
        {
            if (pRxData[0] == LIGHT1_TOGGLE_CMD)
            {
                halLedToggle(1);
                halLedToggle(2);
                halLedToggle(3);
            }
            if (pRxData[0] == LIGHT2_TOGGLE_CMD)
            {
                halLedToggle(4);
                halLedToggle(5);
                halLedToggle(6);
            }
            if (pRxData[0] == LIGHT_TOGGLE_CMD)
            {
                if (toggle == 1)
                {
                    toggle = 0;
                    M160_Off();
                }
                else
                {
                    toggle = 1;
                    M160_On(duty);
                }
            }
            if (pRxData[0] == LIGHT_UP_CMD)
            {
                if (duty < 100)
                {
                    duty += 5;
                }
                M160_On(duty);
            }
            if (pRxData[0] == LIGHT_DN_CMD)
            {
                if (duty > 0)
                {
                    duty -= 5;
                }
                M160_On(duty);
            }
        }
    }
    M160_Off();
}

//-------------------------------------------------------------------
// @fn          exSwitch
// @brief       Application code for switch application. Puts MCU in
//              endless loop to wait for commands from from switch
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pTxData - file scope variable. Pointer to buffer for TX
//              payload
//              appState - file scope variable. Holds application state
// @return      none
//-------------------------------------------------------------------
void exSwitch(void)
{
    halLcdWriteLine(HAL_LCD_LINE_1, "Switch");
    halLcdWriteLine(HAL_LCD_LINE_2, "[Up][Down][#12]");

    // Initialize BasicRF
    basicRfConfig.myAddr = SWITCH_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED)
    {
        HAL_ASSERT("RfConfig Error!");
    }

    // Keep Receiver off when not needed to save power
    basicRfReceiveOff();

    // Main loop
    while (TRUE)
    {
        uint8 key;
        key = halKeypadPushed();
        if (key > 0)
        {
            if (key == '1')
            {
                pTxData[0] = LIGHT1_TOGGLE_CMD;
                basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            }
            if (key == '2')
            {
                pTxData[0] = LIGHT2_TOGGLE_CMD;
                basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            }
            if (key == '#')
            {
                pTxData[0] = LIGHT_TOGGLE_CMD;
                basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            }
            if (key == 'U')
            {
                pTxData[0] = LIGHT_UP_CMD;
                basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            }
            if (key == 'N')
            {
                pTxData[0] = LIGHT_DN_CMD;
                basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            }
            if (key == '*')
            {
                break;
            }
            halBuzzer(300);
        }
    }
}

//-------------------------------------------------------------------
// ·Å«×°»´ú(SPI)½d¨Ò
//-------------------------------------------------------------------
void exM140(void)
{
    uint8 key;
    uint16 val;
    M140_Init();
    halLcdWriteLine(HAL_LCD_LINE_1, "** M140 Test  **");
    halLcdWriteLine(HAL_LCD_LINE_2, " Temp. =       C");
    halLcdWriteChar(HAL_LCD_LINE_2, 14, 0xDF);
    while (TRUE)
    {
        val = M140_GetValue();
        if ((0x2000 &val) == 0x2000)
        //Check sign bit for negative value.
        {
            val = ((val - 16384) *10) / 32;
        }
        else
        {
            val = (val *10) / 32;
        }

        halLcdWriteChar(HAL_LCD_LINE_2, 9, (val / 100) + '0');
        halLcdWriteChar(HAL_LCD_LINE_2, 10, ((val / 10) % 10) + '0');
        halLcdWriteChar(HAL_LCD_LINE_2, 11, '.');
        halLcdWriteChar(HAL_LCD_LINE_2, 12, (val % 10) + '0');
        key = halKeypadPushed();
        halMcuWaitMs(100);
        if (key == '*')
        {
            break;
        }
    }
}

//-------------------------------------------------------------------
// ¶É±×¾_°Ê°»´ú(INT)½d¨Ò
//-------------------------------------------------------------------
void exM180(void)
{
    uint8 key;
    M180_Init();
    M180_Enable();
    halLcdWriteLine(HAL_LCD_LINE_1, "** M180 Test  **");
    halLcdWriteLine(HAL_LCD_LINE_2, "  Count =");
    while (TRUE)
    {
        halLcdDisplayUint16(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, M180_GetValue());
        key = halKeypadPushed();
        halMcuWaitMs(100);
        if (key == '*')
        {
            break;
        }
    }
    M180_Disable();
}

//-------------------------------------------------------------------
// ¦ê¦C°O¾ÐÅé(I2C)½d¨Ò
//-------------------------------------------------------------------
void exM230(void)
{
    uint8 key;
    M230_Init();
    halLcdWriteLine(HAL_LCD_LINE_1, "** M230 Test  **");
    halLcdWriteLine(HAL_LCD_LINE_2, "Write:   Read:  ");
    key = M230_ReadEEPROM(0);
    halLcdWriteChar(HAL_LCD_LINE_2, 14, key);
    while (TRUE)
    {
        key = halKeypadPushed();
        halMcuWaitMs(100);
        if (key > 0)
        {
            if (key == '*')
            {
                break;
            }
            M230_WriteEEPROM(0, key);
            halLcdWriteChar(HAL_LCD_LINE_2, 6, key);

            key = M230_ReadEEPROM(0);
            halLcdWriteChar(HAL_LCD_LINE_2, 14, key);
        }
    }
}

//-------------------------------------------------------------------
// ¥iÅÜ¹qªý(A/D)½d¨Ò
//-------------------------------------------------------------------
void exM190(void)
{
    uint8 key;
    M190_Init();
    halLcdWriteLine(HAL_LCD_LINE_1, "** M190 Test  **");
    halLcdWriteLine(HAL_LCD_LINE_2, "  Value =");
    while (TRUE)
    {
        halLcdDisplayUint16(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, M190_GetValue());
        halMcuWaitMs(200);
        key = halKeypadPushed();
        halMcuWaitMs(100);
        if (key == '*')
        {
            break;
        }
    }
}

//-------------------------------------------------------------------
// ·Ó«×«G«×°»´ú(A/D)½d¨Ò
//-------------------------------------------------------------------
void exM170(void)
{
    uint8 key;
    uint16 val;
    M170_Init();
    halLcdWriteLine(HAL_LCD_LINE_1, "** M170 Test  **");
    halLcdWriteLine(HAL_LCD_LINE_2, " Bright =     % ");
    while (TRUE)
    {
        val = M170_GetValue();
        if (val > 2000)
        {
            val -= 2000;
        }
        else
        {
            val = 0;
        }
        val /= 120;
        if (val > 100)
        {
            val = 100;
        }
        halLcdDisplayUint8(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, val);
        key = halKeypadPushed();
        halMcuWaitMs(100);
        if (key == '*')
        {
            break;
        }
    }
}

//-------------------------------------------------------------------
// Ä~¹q¾¹/«öÁä(DI/DO)½d¨Ò
//-------------------------------------------------------------------
void exM270(void)
{
    uint8 key;
    uint8 udi;
    uint8 udo = 0;
    M270_Init();
    halLcdWriteLine(HAL_LCD_LINE_1, "** M270 Test  **");
    halLcdWriteLine(HAL_LCD_LINE_2, "DI=[1][1] DO=[0]");
    while (TRUE)
    {
        udi = M270_GetDI();
        halLcdWriteChar(HAL_LCD_LINE_2, 4, (udi &0x01) + '0');
        halLcdWriteChar(HAL_LCD_LINE_2, 7, ((udi >> 1) &0x01) + '0');
        halLcdWriteChar(HAL_LCD_LINE_2, 14, udo + '0');
        if ((udi &0x01) == 0x00)
        {
            udo = 1;
            M270_SetDO(udo);
        }
        if ((udi &0x02) == 0x00)
        {
            udo = 0;
            M270_SetDO(udo);
        }
        key = halKeypadPushed();
        halMcuWaitMs(100);
        if (key == '*')
        {
            break;
        }
    }
    HAL_RELAY_OFF();
}

//-------------------------------------------------------------------
// LED½Õ¥ú(PWM)½d¨Ò
//-------------------------------------------------------------------
void exM160(void)
{
    uint8 key, duty;
    M160_Init();
    halLcdWriteLine(HAL_LCD_LINE_1, "** M160 Test  **");
    halLcdWriteLine(HAL_LCD_LINE_2, "   Duty = 50  % ");
    duty = 50;
    M160_On(duty);
    while (TRUE)
    {
        halMcuWaitMs(50);
        key = halKeypadPushed();
        if (key > 0)
        {
            if (key == '*')
            {
                break;
            }
            if (key == 'U')
            {
                if (duty < 100)
                {
                    duty += 5;
                }
            }
            if (key == 'N')
            {
                if (duty > 0)
                {
                    duty -= 5;
                }
            }
            M160_On(duty);
            halLcdDisplayUint16(HAL_LCD_LINE_2, 10, HAL_LCD_RADIX_DEC, duty);
        }
    }
    M160_Off();
}

//-------------------------------------------------------------------
// ¤T¶b¦ì²¾¥[³t«×(SPI)½d¨Ò
//-------------------------------------------------------------------
void exM220(void)
{
    uint8 key;

    M220_Init();
    halLcdWriteLine(HAL_LCD_LINE_1, "** M220 Test  **");
    while (TRUE)
    {
        M220_Pooling();
        if ((M220_X_AXIS_Value &0x8000) == 0x8000)
        {
            M220_X_AXIS_Value = 65535-M220_X_AXIS_Value;
            halLcdWriteChar(HAL_LCD_LINE_2, 0, '-');
        }
        else
        {
            halLcdWriteChar(HAL_LCD_LINE_2, 0, '+');
        }
        if ((M220_Y_AXIS_Value &0x8000) == 0x8000)
        {
            M220_Y_AXIS_Value = 65535-M220_Y_AXIS_Value;
            halLcdWriteChar(HAL_LCD_LINE_2, 6, '-');
        }
        else
        {
            halLcdWriteChar(HAL_LCD_LINE_2, 6, '+');
        }
        if ((M220_Z_AXIS_Value &0x8000) == 0x8000)
        {
            M220_Z_AXIS_Value = 65535-M220_Z_AXIS_Value;
            halLcdWriteChar(HAL_LCD_LINE_2, 12, '-');
        }
        else
        {
            halLcdWriteChar(HAL_LCD_LINE_2, 12, '+');
        }
        halLcdDisplayUint16(HAL_LCD_LINE_2, 1, HAL_LCD_RADIX_DEC, M220_X_AXIS_Value);
        halLcdDisplayUint16(HAL_LCD_LINE_2, 7, HAL_LCD_RADIX_DEC, M220_Y_AXIS_Value);
        halLcdDisplayUint16(HAL_LCD_LINE_2, 13, HAL_LCD_RADIX_DEC, M220_Z_AXIS_Value);
        halMcuWaitMs(200);
        key = halKeypadPushed();
        halMcuWaitMs(100);
        if (key == '*')
        {
            break;
        }
    }
}

//-------------------------------------------------------------------
// @fn          exSelect
// @brief       Select example
// @param       none
// @return      uint8 - Example chosen
//-------------------------------------------------------------------
uint8 exSelect(void)
{
    halLcdWriteLine(HAL_LCD_LINE_1, "Select Example");
    return utilMenuSelect(&pMenu);
}

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "basic" application.
// @return      none
//-------------------------------------------------------------------
void main(void)
{
    uint8 exSel = EX_NONE;

    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // Initalise board peripherals
    halBoardInit();
    // Indicate that device is powered
    halLedSet(8);
    utilPrintLogo("* Basic Module *");
    halMcuWaitMs(300);
    halBuzzer(300);
    while (halKeypadPushed() == 0)
        ;

    while (TRUE)
    {
        // Print Logo and splash screen on LCD
        halLcdClear();
        // Set example role
        exSel = exSelect();
        halLcdClear();
        switch (exSel)
        {
            case EX_SWITCH:
                exSwitch();
                break;
            case EX_LIGHT:
                exLight();
                break;
            case EX_M140:
                exM140();
                break;
            case EX_M180:
                exM180();
                break;
            case EX_M230:
                exM230();
                break;
            case EX_M190:
                exM190();
                break;
            case EX_M170:
                exM170();
                break;
            case EX_M270:
                exM270();
                break;
            case EX_M160:
                exM160();
                break;
            case EX_M220:
                exM220();
                break;
        }
    }
}
