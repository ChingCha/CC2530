# ex_M230:system.c

## Ver0.3
- 新增Mode3 自訂節目間隔時間(預設為300ms 輸入範圍為0000~9999 單位：ms)

- 近期改善

	- 新增中斷指令 改善Mode1與2之間切換
	
	- 可以控制多個節點
	
	- 藍牙接收手機封包

## Ver0.2
- 新增Mode2(自訂節目順序之循環模式)

- 近期改善

	- 在Mode2狀態下要能重新輸入節目順序
 
	- 完善Mode2
 
## Ver0.1
- 新增Mode1(預設節目順序之循環模式)

# ex_M230:

- 內容I：嘗試以UART暫存器與M230之API媒合

- 結果I：失敗

- 內容II：將LED_Matrix移植至此

# RF_LED_Matrix_RECV&SEND:

- 內容I：嘗試移植LED_Matrix

- 結果I：失敗


