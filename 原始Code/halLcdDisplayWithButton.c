void halLcdDisplayWithButton(uint8 line,char lChar,int32 lValue)
{
	char *pCounter;
	pCounter = convInt32ToText(lValue);
    pLcdLineBuffer[0] = lChar;
    pLcdLineBuffer[1] = ':';
	pLcdLineBuffer[2] = *pCounter;
	for(int i = 3;i<=15;i++){
		pLcdLineBuffer[i] = ' ';
	}
	lcdWriteLine(line, pLcdLineBuffer);
}