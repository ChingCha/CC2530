void halLcdDisplayWithButton(uint8 line,char First_Char,int32 First_Value,char Second_Char,int32 Second_Value)
{
	char *FirstV;	//字串指標化，FirstV指向char型態的指標
	
	/*convInt32ToText()：將括弧裏頭的int轉為Text ; 
	FirstV指向convInt32ToText(First_Value)
	*/
	FirstV = convInt32ToText(First_Value);	
	
	char *SecondV;
	SecondV = convInt32ToText(Second_Value);		
	
    pLcdLineBuffer[0] = First_Char;
    pLcdLineBuffer[1] = ':';
	pLcdLineBuffer[2] = *FirstV;
	pLcdLineBuffer[3] = Second_Char;
    pLcdLineBuffer[4] = ':';
	pLcdLineBuffer[5] = *SecondV;
	
	//迴圈處理剩餘pLcdLineBuffer[]
	for(int i = 6;i<=15;i++){
		pLcdLineBuffer[i] = ' ';
	}
	
	/*	Write line on display
	@line:顯示餘第幾行
	@pLcdLineBuffer[LCD_LINE_LENGTH] //陣列元素數量限制(16)
	*/
	lcdWriteLine(line, pLcdLineBuffer);		
}