#include <regx51.h>
unsigned int dutytime=45536; //65536-45536�N�O�d���g��
unsigned int ton=10000; //���q����=50%
unsigned int toff=10000; //�C�q����=50%
unsigned int temp; //���p�ɾ��u�@��

void timer0_initialize(void)  //��l�ƭp�ɾ�0
{
    EA=0; //�������_�\��(�Ҧ����_�Ƶ{������)
    IE|=0x02; //�}�ҭp�ɾ����_�\��
    TMOD|=0x01; //�]�w�p�ɾ��Ҧ�
    temp=65536-dutytime; //�]�w���_�@�����ɶ�(�w�]�Odutytime)
    TH0=temp/256; //��J���K��
    TL0=temp%256; //��J�C�K��
    TR0=1; //�Ұʭp�ɾ�
    EA=1; //�}�Ҥ��_�\��(���_�Ƶ{���i�H����)
}

void timer0_isr(void) interrupt TF0_VECTOR using 1 //�ϥέp�ɾ����_�Ƶ{������PWM
{
    if(P2_0==1)
    {
    TR0=0;
    temp=65536-toff;
    TH0=temp/256;
    TL0=temp%256;
    TR0=1;
    P2_0=0;
    }
    else
    {
    TR0=0;
    temp=65536-ton;
    TH0=temp/256;
    TL0=temp%256;
    TR0=1;
    P2_0=1;
    }
}
void main(void) //�D�{���}�l
{
    timer0_initialize(); //�I�s�p�ɾ���l�ưƵ{��
    //�D�{�����i��������ton��toff�Y�i���ܰ��q���C�q��������
    while(1)
	{
		if(P1_0==0)ton=2200;  //2.2ms ���� 
		if(P1_1==0)ton=1500;  //1.5ms ����
		if(P1_2==0)ton=900;	  //0.9ms �k��  �d�U�O�H���N3�Ө���0.5~2.2�������i�ը���
		toff=20000-ton;
	}
}