#include <iostream>
using namespace std;

class RFsend{
	public:
		int32 a;
		int32 appsend();
};


int32 RFsend::appsend(){
	basicRfConfig.myAddr = SWITCH_ADDR;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	basicRfReceiveOff();
	pTxData[0] = LIGHT1_TOGGLE_CMD;//LIGHT1_TOGGLE_CMD??
	pTxData[1] = a;
	basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
	halLedToggle(1);
	halLedToggle(2);
	halLedToggle(3);
	halBuzzer(100);
    halMcuWaitMs(20);
    halLedToggle(7);
}

void main(){
	basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif
	halBoardInit();
    halLedSet(8);
	RFsend do;
	do.a = 5;
	
	while(1){
		unit8 b = halButtonPushed();
		if(b == HAL_BUTTON_2){
			halLcdDisplayWithButton(HAL_LCD_LINE_1,a,'D');
			if(a > 0){
				a--;
				do.appsend(a);
			}
		}
	}
	
	
	
}