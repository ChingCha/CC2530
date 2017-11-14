switch(pRxData[0]){
	case '1':
		A_water(pRxData[1]);
		MAX7219_Write(DIGIT0,0x01);
		break;
	case '2':
		A_milk(pRxData[1]);
		MAX7219_Write(DIGIT0,0x02);
		break;
	case '3':
		B_greentea(pRxData[1]);
		MAX7219_Write(DIGIT1,0x01);
		break;
	case '4':
		B_blacktea(pRxData[1]);
		MAX7219_Write(DIGIT1,0x02);
		break;
}