//-------------------------------------------------------------------
// Filename: light.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_lcd.h"
#include "M160.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions(定義BasicRF address)
#define PAN_ID                0x1111
#define SWITCH_ADDR           0x2222
#define LIGHT_ADDR            0x3333
#define APP_PAYLOAD_LENGTH        1
#define LIGHT1_TOGGLE_CMD         '1'
#define LIGHT2_TOGGLE_CMD         '2'

// Application states
#define IDLE                      0
#define SEND_CMD                  1

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
static uint8 pRxData[APP_PAYLOAD_LENGTH];//被宣告成static，所以記憶體不會歸還，延用著上次的值。
static basicRfCfg_t basicRfConfig;

#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif 

//-------------------------------------------------------------------
// @fn          appLight
// @brief       Application code for light application. Puts MCU in endless
//              loop waiting for user input from switch.
// @param       basicRfConfig - 文件範圍變量。 基本RF配置數據
//              pRxData - 文件範圍變量。 指向TX有效載荷緩衝區的指針(陣列裡的數字只能0)
// @return      none
//-------------------------------------------------------------------
static void appLight()
{
    // Initialize BasicRF(初始化 BasicRF)
	/*basicRfInit:
	初始化基本射頻數據結構。
	在芯片中設置通道，短地址和PAN id
	並配置數據包接收時的中斷
	*/
	/*basicRfConfig:
	初始化基本射頻數據結構。
	在芯片中設置通道，短地址和PAN id
	並配置數據包接收時的中斷
	*/
    basicRfConfig.myAddr = LIGHT_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // Keep Receiver on
    basicRfReceiveOn();

    // Main loop
	/* basicRfReceive包含:(pRxData, APP_PAYLOAD_LENGTH ,NULL)
		pRxData	:指向要填充的數據緩衝區。 此緩衝區必須由較高層分配。
		len	   	:要讀入緩衝區的字節數
		rxi		:文件範圍變量保存最後一個數據包的信息
	*/
    while (TRUE)
    {
        M160_Init();//匯入：M160.c
        while (!basicRfPacketIsReady())
        {
            halLedToggle(7);
            halMcuWaitMs(20);
        }
        if (basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
        {
            if (pRxData[0] == LIGHT1_TOGGLE_CMD)
            {
                halLcdWriteLine(HAL_LCD_LINE_1, "A");
                M160_On(100);
                halLedToggle(1);
                halLedToggle(2);
                halLedToggle(3);
                halBuzzer(300);
            }
            if (pRxData[0] == LIGHT2_TOGGLE_CMD)
            {
                halLcdWriteLine(HAL_LCD_LINE_1, "B");
                M160_Off();
                halLedToggle(4);
                halLedToggle(5);
                halLedToggle(6);
                halBuzzer(300);
            }
        }
    }
}

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "portio" application.
// @return      none
//-------------------------------------------------------------------
void main(void)
{
    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // Initalise board peripherals
    halBoardInit();
    halLcdInit();
    M160_Init();

    // Indicate that device is powered
    halLedSet(8);
    halBuzzer(300);

    //Enter Light mode
    appLight();

}
