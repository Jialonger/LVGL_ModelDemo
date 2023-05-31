#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 

//STM32F407������
//������������
								  
////////////////////////////////////////////////////////////////////////////////// 	 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define NEXT 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0--��ӦK1����
#define ENTER 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)	//PA0--��ӦK1����
#define LEFT 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)	//PA0--��ӦK1����
#define RIGHT 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)	//PA0--��ӦK1����
#define PREV 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)	//PA0--��ӦK1����


/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define WK_UP 	PAin(0)		//PA0
*/
/*
*	PD9��k2
*	PD10��k1
*	PD11��k4
*	PD12��k3
*/

#define NEXT_PRES   1
#define ENTER_PRES  2 
#define LEFT_PRES  	3
#define RIGHT_PRES  4
#define PREV_PRES  	5

void KEY_Init(void);	//IO��ʼ��
uint8_t KEY_Scan(uint8_t);  		//����ɨ�躯��	

#endif
