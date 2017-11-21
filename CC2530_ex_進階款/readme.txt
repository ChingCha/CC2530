CC2530_ex 範例程式目錄檔案說明

zigbee-mcu1 --- ZIGBEE-MCU1 單板範例程式
|---ex_io --- 按鍵LED蜂鳴器範例
|   |---io.eww io.ewp --- 按鍵LED蜂鳴器專案
|   \---ic.c --- 按鍵LED蜂鳴器主程式
|
|---ex_switch --- 無線開關範例 802.15.4 standard ,RF channel = 25 
|   |---switch.eww switch.ewp --- 無線開關專案
|   \---switch.c --- 無線開關主程式
|
|---ex_light ---  無線燈具範例 802.15.4 standard ,RF channel = 25 
|   |---light.eww light.ewp --- 無線燈具專案
|   \---light.c --- 無線燈具主程式
|
mcu-kit1 --- ZIGBEE-MCU1+MCU-KIT1 實驗板範例程式
mcu-kit2 --- ZIGBEE-MCU1+MCU-KIT2 實驗板範例程式
|---ex_keypad_lcd --- 鍵盤顯示範例
|   |---keypad_lcd.eww keypad_lcd.ewp --- 鍵盤顯示專案
|   \---keypad_lcd.c --- 鍵盤顯示主程式
|
|---ex_uart --- 串列通訊範例
|   |---uart.eww uart.ewp --- 串列通訊專案
|   \---uart.c --- 串列通訊主程式
|
|---ex_light_switch --- 無線開關燈具範例 802.15.4 standard ,RF channel = 25 
|   |---light_switch.eww light_switch.ewp --- 無線開關燈具專案
|   \---light_switch.c --- 無線開關燈具主程式
|
|---ex_basic --- 基本模組範例
|   |---basic.eww basic.ewp --- 基本模組專案
|   \---basic.c --- 基本模組主程式
|
|---ex_rfrecv --- 無線接收通訊範例 802.15.4 standard ,RF channel = 18
|
|---ex_M140_uart --- 溫度偵測通訊範例
|
|---ex_M100 --- RTC時鐘(I2C)範例
|---ex_M110 --- 全方向震動偵測(INT)範例
|---ex_M120 --- 串列記憶體(SPI)範例
|---ex_M130 --- 紅外線接收模組(DI)範例
|---ex_M140 --- 溫度偵測(SPI)範例
|---ex_M150 --- 霍爾元件電流偵測(A/D)範例
|---ex_M160 --- LED調光(PWM)範例
|---ex_M170 --- 照度亮度偵測(A/D)範例
|---ex_M180 --- 傾斜震動偵測(INT)範例
|---ex_M190 --- 可變電阻(A/D)範例
|---ex_M200 --- 溫濕度偵測(I2C)範例
|---ex_M210 --- 語音電壓輸出D/A(SPI)範例
|---ex_M220 --- 三軸位移加速度(SPI)範例
|---ex_M230 --- 串列記憶體(I2C)範例
|---ex_M240 --- 全彩LED調光(PWM)範例
|---ex_M250 --- RFID讀卡模組(DI)範例
|---ex_M260 --- 角速度偵測陀螺儀(SPI)範例
|---ex_M270 --- 繼電器/按鍵(DI/DO)範例
|---ex_M280 --- 馬達風扇控制(PWM)範例
|---ex_M290 --- 麥克風輸入(A/D)範例
|---ex_M300 --- 超音波收發(DI/Timer)
|---ex_M310 --- 光遮斷偵測(DI/DO)
|---ex_M320 --- 紅外線溫度感測(I2C)範例
|
mcu-net1 --- MCU-NET1 通訊介面板範例程式
|---ex_light_uart --- 燈控接收通訊範例 802.15.4 standard ,RF channel = 25
|---ex_rfrecv --- 無線接收通訊範例 802.15.4 standard ,RF channel = 18
|
mcu-tag1 --- MCU-TAG1 電池板範例程式
|---ex_M140_rfsend --- 無線發送溫度範例 802.15.4 standard ,RF channel = 18
|---ex_M320_rfsend --- 無線發送紅外線溫度感測範例 802.15.4 standard ,RF channel = 18
|
components --- 共用元件
|---targets
|   |---zigbee-mcu1 --- ZIGBEE-MCU1 MCU主板函數庫
|   |   |---hal_board.c --- 機板初始函數庫
|   |   |---hal_board.h --- 機板初始函數庫定義
|   |   |---hal_buzzer.c --- 蜂鳴器函數庫
|   |   |---hal_buzzer.h --- 蜂鳴器函數庫定義
|   |   |---hal_button.c --- 按鍵函數庫
|   |   |---hal_button.h --- 按鍵函數庫定義
|   |   |---hal_led.c --- LED函數庫
|   |   \---hal_led.h --- LED函數庫定義
|   |
|   |---mcu-kit1 --- MCU-KIT1+ZIGBEE-MCU1 實驗主板函數庫
|   |   |---hal_board.c --- 機板初始函數庫
|   |   |---hal_board.h --- 機板初始函數庫定義
|   |   |---hal_buzzer.c --- 蜂鳴器函數庫
|   |   |---hal_buzzer.h --- 蜂鳴器函數庫定義
|   |   |---hal_keypad.c --- 鍵盤函數庫
|   |   |---hal_keypad.h --- 鍵盤函數庫定義
|   |   |---hal_lcd.c --- LCD函數庫
|   |   |---hal_lcd.h --- LCD函數庫定義
|   |   |---hal_led.c --- LED函數庫
|   |   |---hal_led.h --- LED函數庫定義
|   |   |---hal_uart.c --- UART通訊函數庫
|   |   \---hal_uart.h --- UART通訊函數庫定義
|   |
|   |---mcu-kit2 --- MCU-KIT2+ZIGBEE-MCU1 實驗主板函數庫
|   |   |---hal_board.c --- 機板初始函數庫
|   |   |---hal_board.h --- 機板初始函數庫定義
|   |   |---hal_buzzer.c --- 蜂鳴器函數庫
|   |   |---hal_buzzer.h --- 蜂鳴器函數庫定義
|   |   |---hal_keypad.c --- 鍵盤函數庫
|   |   |---hal_keypad.h --- 鍵盤函數庫定義
|   |   |---hal_lcd.c --- LCD函數庫
|   |   |---hal_lcd.h --- LCD函數庫定義
|   |   |---hal_led.c --- LED函數庫
|   |   |---hal_led.h --- LED函數庫定義
|   |   |---hal_uart.c --- UART通訊函數庫
|   |   \---hal_uart.h --- UART通訊函數庫定義
|   |
|   |---mcu-net1 --- MCU-NET1+ZIGBEE-MCU1 通訊介面板函數庫
|   |   |---hal_board.c --- 機板初始函數庫
|   |   |---hal_board.h --- 機板初始函數庫定義
|   |   |---hal_buzzer.c --- 蜂鳴器函數庫
|   |   |---hal_buzzer.h --- 蜂鳴器函數庫定義
|   |   |---hal_rtc.c --- RTC函數庫
|   |   |---hal_rtc.h --- RTC函數庫定義
|   |   |---hal_uart.c --- UART通訊函數庫
|   |   \---hal_uart.h --- UART通訊函數庫定義
|   |
|   |---mcu-tag1 --- MCU-TAG1 電池板函數庫
|   |   |---hal_board.c --- 機板初始函數庫
|   |   |---hal_board.h --- 機板初始函數庫定義
|   |   |---hal_buzzer.c --- 蜂鳴器函數庫
|   |   |---hal_buzzer.h --- 蜂鳴器函數庫定義
|   |   |---hal_button.c --- 按鍵函數庫
|   |   |---hal_button.h --- 按鍵函數庫定義
|   |   |---hal_led.c --- LED函數庫
|   |   \---hal_led.h --- LED函數庫定義
|   |
|   \---module --- 模組函數庫
|       |---M100.c --- RTC時鐘(I2C)函數庫
|       |---M100.h --- RTC時鐘(I2C)函數庫定義
|       |---M110.c --- 全方向震動偵測(INT)函數庫
|       |---M110.h --- 全方向震動偵測(INT)函數庫定義
|       |---M120.c --- 串列記憶體(SPI)函數庫
|       |---M120.h --- 串列記憶體(SPI)函數庫定義
|       |---M130.c --- 紅外線接收模組(DI)函數庫
|       |---M130.h --- 紅外線接收模組(DI)函數庫定義
|       |---M140.c --- 溫度偵測(SPI)函數庫
|       |---M140.h --- 溫度偵測(SPI)函數庫定義
|       |---M150.c --- 霍爾元件電流偵測(A/D)函數庫
|       |---M150.h --- 霍爾元件電流偵測(A/D)函數庫定義
|       |---M160.c --- LED調光(PWM)函數庫
|       |---M160.h --- LED調光(PWM)函數庫定義
|       |---M170.c --- 照度亮度偵測(A/D)函數庫
|       |---M170.h --- 照度亮度偵測(A/D)函數庫定義
|       |---M180.c --- 傾斜震動偵測(INT)函數庫
|       |---M180.h --- 傾斜震動偵測(INT)函數庫定義
|       |---M190.c --- 可變電阻(A/D)函數庫
|       |---M190.h --- 可變電阻(A/D)函數庫定義
|       |---M200.c --- 溫濕度偵測(I2C)函數庫
|       |---M200.h --- 溫濕度偵測(I2C)函數庫定義
|       |---M210.c --- 電壓輸出D/A(SPI)函數庫
|       |---M210.h --- 電壓輸出D/A(SPI)函數庫定義
|       |---M220.c --- 三軸位移加速度(SPI)函數庫
|       |---M220.h --- 三軸位移加速度(SPI)函數庫定義
|       |---M230.c --- 串列記憶體(I2C)函數庫
|       |---M230.h --- 串列記憶體(I2C)函數庫定義
|       |---M240.c --- 全彩LED調光(PWM)函數庫
|       |---M240.h --- 全彩LED調光(PWM)函數庫定義
|       |---M250.c --- RFID讀卡模組(DI)函數庫
|       |---M250.h --- RFID讀卡模組(DI)函數庫定義
|       |---M260.c --- 角速度偵測陀螺儀(SPI)函數庫
|       |---M260.h --- 角速度偵測陀螺儀(SPI)函數庫定義
|       |---M270.c --- 繼電器/按鍵(DI/DO)函數庫
|       |---M270.h --- 繼電器/按鍵(DI/DO)函數庫定義
|       |---M280.c --- 馬達控制(PWM)函數庫
|       |---M280.h --- 馬達控制(PWM)函數庫定義
|       |---M290.c --- 麥克風輸入(A/D)函數庫
|       |---M290.h --- 麥克風輸入(A/D)函數庫定義
|       |---M300.c --- 超音波收發(DI/Timer)函數庫
|       |---M300.h --- 超音波收發(DI/Timer)函數庫定義
|       |---M310.c --- 光遮斷偵測(DI/DO)函數庫
|       |---M310.h --- 光遮斷偵測(DI/DO)函數庫定義
|       |---M320.c --- 紅外線溫度感測(I2C)函數庫
|       \---M320.h --- 紅外線溫度感測(I2C)函數庫定義
|
|---common
|   |---hal_cc8051.h --- MCU 輸入輸出巨集定義
|   |---hal_defs.h --- 通用定義
|   |---hal_mcu.c --- MCU函數庫
|   |---hal_mcu.h --- MCU函數庫定義
|   |---hal_clock.c --- 函數庫
|   |---hal_clock.h --- MCU函數庫定義
|   |---hal_digio.c --- 輸入輸出中斷函數庫
|   |---hal_digio.h --- 輸入輸出中斷函數庫定義
|   |---hal_adc.c --- ADC函數庫
|   |---hal_adc.h --- ADC函數庫定義
|   |---hal_int.c --- 中斷函數庫
|   |---hal_int.h --- 中斷函數庫定義
|   |---hal_rf.c --- 無線函數庫
|   |---hal_rf.h --- 無線函數庫定義
|   |---hal_rf_security.c --- 無線加密函數庫
|   |---hal_rf_security.h --- 無線加密函數庫定義
|   |---hal_rf_util.c --- 無線通用函數庫
|   |---hal_rf_util.h --- 無線通用函數庫定義
|   |---hal_timer_32k.c --- 32K定時器函數庫
|   \---hal_timer_32k.h --- 32K定時器函數庫定義
|
|---basicrf
|   |---basic_rf.c --- 基本無線函數庫
|   |---basic_rf.h --- 基本無線函數庫定義
|   |---basic_rf_security.c --- 基本無線加密函數庫
|   \---basic_rf_security.h --- 基本無線加密函數庫定義
|
\---utils
    |---util.c --- 工具函數庫
    |---util.h --- 工具函數庫定義
    |---util_buffer.c --- 暫存函數庫
    |---util_buffer.h --- 暫存函數庫定義
    |---util_lcd.c --- 顯示與選單函數庫
    \---util_lcd.h --- 顯示與選單函數庫定義

