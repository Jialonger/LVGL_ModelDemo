#include "key.h"
#include "delay.h" 
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 

// STM32F407������
//����������������	   
							  
////////////////////////////////////////////////////////////////////////////////// 	 

//������ʼ������
/*
*	PD9��k2
*	PD10��k1
*	PD11��k4
*	PD12��k3
*/
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOA,ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOA,ʱ��
 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0--K1����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//WK_UP��Ӧ����PD9--K1����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOD9
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//WK_UP��Ӧ����PD10--K1����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOD10
 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//WK_UP��Ӧ����PD11--K1����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOD11
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//WK_UP��Ӧ����PD12--K1����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOD12
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��WKUP���� --��ӦK1����

uint8_t KEY_Scan(uint8_t mode)
{	 
	static u8 key_up = 1;//�������ɿ���־

	
//	if(mode)key_up=1;  //֧������		  
//	if(key_up&&(NEXT==1))
//	{
//		delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(NEXT==1)return 1;
//	}else if(NEXT==0)key_up=1; 	    
// 	return 0;// �ް�������
	
//	if(mode)
//		key_up=1;  //֧������		  
//	if(key_up&&(ENTER==0))
//	{
//		delay_ms(10);//ȥ���� 
//		key_up=0;
//		if(ENTER==0)
//			return ENTER_PRES;
//	}else if(ENTER==1)
//		key_up=1; 	

//    key_up = 0;
// 	return 0;// �ް�������
	
	if(mode)
	key_up = 1;  //֧������	
	if( (key_up == 1) &&((NEXT==1)||(ENTER==0)||(LEFT==0)||(RIGHT==0)||(PREV==0)))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		//LED0 = !LED0;
		if(NEXT==1)return NEXT_PRES;
		if(ENTER==1)return ENTER_PRES;
		if(LEFT==1)	return LEFT_PRES;
		if(RIGHT==1)return RIGHT_PRES;
		if(PREV==1)	return PREV_PRES; 
	}else if((NEXT==0)&&(ENTER==1)&&(LEFT==1)&&(RIGHT==1)&&(PREV==1))
	{
		key_up = 1;
	}
 	return 0;// �ް�������
}




















