//-------------------------------------------------------------------
// Filename: M330.h
// Description: hal M130 module library header file
//-------------------------------------------------------------------

#define HAL_BOARD_IO_IR_LED_PORT           0
#define HAL_BOARD_IO_IR_LED_PIN            5
#define HAL_BOARD_IO_IR_IN_PORT            0
#define HAL_BOARD_IO_IR_IN_PIN             4


#define HAL_IRIN_DIR_IN()           MCU_IO_INPUT(HAL_BOARD_IO_IR_IN_PORT, HAL_BOARD_IO_IR_IN_PIN, MCU_IO_PULLUP)
#define HAL_IRIN()                  MCU_IO_GET(HAL_BOARD_IO_IR_IN_PORT, HAL_BOARD_IO_IR_IN_PIN)

#define HAL_IRLED_DIR_OUT()         MCU_IO_OUTPUT(HAL_BOARD_IO_IR_LED_PORT, HAL_BOARD_IO_IR_LED_PIN, 1)
#define HAL_IRLED_OFF()             MCU_IO_SET_HIGH(HAL_BOARD_IO_IR_LED_PORT, HAL_BOARD_IO_IR_LED_PIN)
#define HAL_IRLED_ON()              MCU_IO_SET_LOW(HAL_BOARD_IO_IR_LED_PORT, HAL_BOARD_IO_IR_LED_PIN)

extern uint16 M330_Val;
//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M330_Init(void);
void M330_TX(uint8 delay);
void M330_NTX(uint8 delay);
void M330_SendCode(uint16 val);
uint8 M330_GetData(void);
