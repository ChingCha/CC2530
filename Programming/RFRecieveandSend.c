static void appRF_RTX() 
{ 
	uint8 cmd; 
    // Initialize BasicRF 
    basicRfConfig.myAddr = LIGHT_ADDR; 
    if (basicRfInit(&basicRfConfig) == FAILED){} 
    // Keep Receiver on 
    basicRfReceiveOn(); 
    pRxData[0]=0x2B;pRxData[1]=0; 
    // Main loop 
    while (1){
		
       //發射 RF 訊號 
       basicRfReceiveOff(); 
       uint8 v = 1,v2=0;//halButtonPushed(); 
        if (v == 1) 
        { 
            pTxData[2] = DevID; 
            pTxData[3] = '1'; 
            pTxData[4] = '0';             
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); 
            halLedToggle(1); 
        } 
        basicRfReceiveOff(); 
        if (v == 2) 
        { 
 
            pTxData[2] = DevID; 
            pTxData[3] = '2'; 
            pTxData[4] = '0';             
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); 
            halLedToggle(2); 
            halBuzzer(300); 
        } 

      //接收 RF 訊號 
     //basicRfReceiveOn(); 
    if(basicRfPacketIsReady()) 
      { 
      if (basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0) 
         { 
           if(pRxData[2]==DevID) 
           { 
             cmd=pRxData[3];  
             switch(cmd) 
             { 
               case '1' : 
                  halLedToggle(pRxData[4]-0x30); 
                  halBuzzer(300); 
                  break;          
              case '2' : 
                  halLedSet(pRxData[4]-0x30); 
                  halBuzzer(300); 
                  break;                    
             case '3' : 
                  halLedClear(pRxData[4]-0x30); 
                  halBuzzer(300); 
                  break; 
             case '4' : 
                  halLedSetPort(pRxData[4]); 
                  halBuzzer(300); 
                  break;       
             } 
           } 
         } 
    }  
} 
} 
 
void delay() 
{ 
  uint16 n1; 
  uint16 n2; 
  for(n1=0;n1<55;n1++) 
  { 
    for(n2=0;n2<1000;n2++); 
  } 
 
 
}