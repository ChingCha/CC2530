//设置主时钟
void set_main_clock(source)
{ 
if(source) 
{ 
CLKCONCMD |= 0X40; //选择16MHZ RCOSC为系统时钟源 
while(!(CLKCONSTA & 0X40)); //等待时钟稳定
}else
{ 
CLKCONCMD &= ~0X40; //选择32MHZ XOSC为系统时钟源 
while(CLKCONSTA & 0X40); //等待时钟稳定
}

