//引入標頭檔
#include "ioCC2530.h"

//MAX7219暫存器巨集定義

#define DECODE_MODE  0x09   //解碼控制暫存器
#define INTENSITY    0x0A   //亮度控制暫存器
#define SCAN_LIMIT   0x0B   //掃描界限暫存器
#define SHUT_DOWN    0x0C   //關斷模式暫存器
#define DISPLAY_TEST 0x0F   //測試控制暫存器 

#define INTENSITY_MIN     0x00   // 最小顯示亮度
#define INTENSITY_MAX     0x0f   // 最大顯示亮度

//CC2530腳位功能巨集定義

#define MAX7219DIN P0_4		//CC2530 P0_4>>>模組DIN腳位
#define MAX7219CS P0_5		//CC2530 P0_5>>>模組CS腳位
#define MAX7219CLK P0_6		//CC2530 P0_6>>>模組CLK腳位

//延時函數
void Delay(unsigned int t)
{
  while(t--);
}
