//-------------------------------------------------------------------
// Filename: switch.c
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
#include "hal_button.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "basic_rf.h"

//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Application parameters
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions(定義BasicRF address)
#define PAN_ID                0x1111	//網路ID
#define SWITCH_ADDR           0x2222	//發送器ID
#define LIGHT_ADDR            0x3333	//接收器ID
#define APP_PAYLOAD_LENGTH        1		//數據長度
#define LIGHT1_TOGGLE_CMD         '1'	//指標？
#define LIGHT2_TOGGLE_CMD         '2'	//指標？

// Application states 
#define IDLE                      0
#define SEND_CMD                  1

//-------------------------------------------------------------------
//LOCAL FUNCTIONS
//-------------------------------------------------------------------
static void appSwitch();

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
static uint8 pTxData[APP_PAYLOAD_LENGTH];//被宣告成static，所以記憶體不會歸還，延用著上次的值。
static basicRfCfg_t basicRfConfig;

#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif 

//-------------------------------------------------------------------
// @fn          appSwitch
// @brief       Application code for switch application. Puts MCU in
//              endless loop to wait for commands from switch.
// @param       basicRfConfig - file scope variable. Basic RF configuration data
//              pTxData - file scope variable. Pointer to buffer for TX
//              payload
//              appState - file scope variable. Holds application state
// @Chinese		basicRfConfig 	文件範圍變量。 基本RF配置數據
//				pTxData 		文件範圍變量。 指向TX有效載荷緩衝區的指針(陣列裡的數字取決於APP_PAYLOAD_LENGTH)
//				appState 		文件範圍變量。 保持應用狀態
// @return      none
//-------------------------------------------------------------------
static void appSwitch()
{
    // Initialize BasicRF(初始化BasicRF)
    basicRfConfig.myAddr = SWITCH_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}

    // Keep Receiver off when not needed to save power
    basicRfReceiveOff();

    // Main loop
	/* basicRfSendPacket包含:(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH)
		destAddr:目的地短地址
		pPayload:指向有效負載緩衝區的指針。 此緩衝區必須由較高層分配。
		length	:有效載荷長度
	*/ 
    while (TRUE)
    {
        uint8 v = halButtonPushed();
        if (v == HAL_BUTTON_2)
        {
            pTxData[0] = LIGHT1_TOGGLE_CMD;//LIGHT1_TOGGLE_CMD??
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            halLedToggle(1);
            halLedToggle(2);
            halLedToggle(3);
            halBuzzer(100);
            halMcuWaitMs(200);
        }
        if (v == HAL_BUTTON_1)
        {
            pTxData[0] = LIGHT2_TOGGLE_CMD;//LIGHT2_TOGGLE_CMD??
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            halLedToggle(4);
            halLedToggle(5);
            halLedToggle(6);
            halBuzzer(300);
            halMcuWaitMs(200);
        }
        halMcuWaitMs(20);
        halLedToggle(7);
    }
}

//-------------------------------------------------------------------
// @fn          main
// @brief       This is the main entry of the "portion" application.
// @return      none
//-------------------------------------------------------------------
void main(void)
{
    // Config basicRF(配置Basic RF)
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif 

    // Initalise board peripherals
	/*halBoardInit
		@fn      halBoardInit
		@brief   Set up board. Initialize MCU, configure I/O pins and user interfaces
 		@param   none
 		@return  none
	*/
    halBoardInit();

    // Indicate that device is powered
    halLedSet(8);

    // Enter Switch mode
    appSwitch();
}
