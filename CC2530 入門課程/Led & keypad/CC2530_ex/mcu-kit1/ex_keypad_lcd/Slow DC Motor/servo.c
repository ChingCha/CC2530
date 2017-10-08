/*****���F******/

#include "ioCC2530.h" 

 #define   LED3 P1_0
 #define   LED4 P1_1
 
void Delay(unsigned int t);
void Init_Port();
void LED_Running();
void LED_Running1();
void Init_INTP();
void PWM();
void set_main_clock();


void main()
{
   Init_Port();           // ��l�Ƴq��I/O�ݤf
   set_main_clock();
  
   Init_INTP ();           // ��l�ƥ~�����_
   
   
   while ( 1 )
   {
     LED_Running();      // �]���O
   }
} 
 
 
 
 /* ===================���ɨ��= ======================== */ 
 void Delay(unsigned int t)
 {
   while (t-- );
 }
 /* = =================�ݤf��l�ƨ��===================== */ 
 void Init_Port()
 {

   P1SEL &= ~ 0x03 ;   
   P1DIR |= 0x03 ;   
   LED3 = 0 ;
   LED4 = 0 ;
   
 }
 /* ==================�]���O�l���=============== ====== */ 
 void LED_Running()
 {
   LED4 = 1 ;
   Delay( 50000 );
   LED4 = 0 ;
   Delay( 50000 );
 }
 void LED_Running1()
 {
   LED3 = 1 ;
   Delay( 60000 );
   Delay( 60000 );
   Delay( 60000 );  //7.3v 145000 delay
   LED3 = 0 ;
 }
 /* ============= ==�~�����_��l�ƨ��================== */ 
 void Init_INTP()
 {
   IEN2 |= 0x10 ;          // �ݤf1���_�ϯ�
   P1IEN |= 0x04 ;         // �ݤfP1_2�~�����_�ϯ�
   PICTL |= 0x02 ;         // �ݤfP1_0��P1_3�U���uĲ�o
   EA = 1 ;                // �ϯ��`���_
 }
 /* ================�~�����_1�A�Ȩ��==================== */ 
 #pragma vector = P1INT_VECTOR      // �~�����_1���V�q�J�f
__interrupt void Int1_Sevice()
 {
	//T1STAT &= ~0x01;	//�M���w�ɾ�1�q�D0���_�лx
	//count++;			//�֥[�ܼ�
	PWM();
	//LED_Running1();
	
	//LED_Running1();
	/* ���M���޸}�лx��A�A�M���ݤf�лx��A�_�h�|���_�i�J���_*/ 
	P1IFG &= ~ 0x04 ;         //�n��M��P1_2�޸}���лx��
	P1IF = 0 ;                // �n��M��P1�ݤf�ժ��лx��
}
 
void PWM()
{
 
    //Timer�q�D?�m
    P1SEL |= 0x01;              //Timer1�q�D2�M�g��P1_0�A�\����
    PERCFG |= 0x40;             //�ƥΦ�m2
    P2SEL &= ~0x10;             //�۹��Timer4�ATimer1�u��
    P2DIR |= 0xC0;              //�w�ɾ��q�D2-3�㦳�Ĥ@�u������
    P1DIR |= 0x01;				//P1_0����X
    
    //Timer�Ҧ�?�m
    T1CTL = 0x02;               //250KHZ�����W�A�ҼҦ�
    
    //�ھ�Table7-1�AP1_0������Timer1�q�D2�i����
	
    T1CCTL2 = 0x1C;             //����۵���1�A�p�ƾ��^0�h�M�s
	
    //��Timer�q�D0���
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM�H���g��20ms
	
	//Timer�q�D2�����
    T1CC2H = 0x04;
    T1CC2L = 0xE2; 				//10ms

	
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//���16MHZ RCOSC���t�ή�����
	while(!(CLKCONSTA & 0X40)); //���ݮ���í�w
	CLKCONCMD &=~0XF8;			//���32MHz���D����
	
	CLKCONCMD |= 0x38;          //Timer�аO��X��250kHz
}