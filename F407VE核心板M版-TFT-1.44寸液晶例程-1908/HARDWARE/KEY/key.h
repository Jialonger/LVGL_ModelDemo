#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 

//STM32F407开发板
//按键输入驱动
								  
////////////////////////////////////////////////////////////////////////////////// 	 

/*下面的方式是通过直接操作库函数方式读取IO*/
#define NEXT 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0--对应K1按键
#define ENTER 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)	//PA0--对应K1按键
#define LEFT 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)	//PA0--对应K1按键
#define RIGHT 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)	//PA0--对应K1按键
#define PREV 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)	//PA0--对应K1按键


/*下面方式是通过位带操作方式读取IO*/
/*
#define WK_UP 	PAin(0)		//PA0
*/
/*
*	PD9：k2
*	PD10：k1
*	PD11：k4
*	PD12：k3
*/

#define NEXT_PRES   1
#define ENTER_PRES  2 
#define LEFT_PRES  	3
#define RIGHT_PRES  4
#define PREV_PRES  	5

void KEY_Init(void);	//IO初始化
uint8_t KEY_Scan(uint8_t);  		//按键扫描函数	

#endif
