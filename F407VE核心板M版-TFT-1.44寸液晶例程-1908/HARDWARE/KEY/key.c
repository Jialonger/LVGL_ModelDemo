#include "key.h"
#include "delay.h" 
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 

// STM32F407开发板
//按键输入驱动代码	   
							  
////////////////////////////////////////////////////////////////////////////////// 	 

//按键初始化函数
/*
*	PD9：k2
*	PD10：k1
*	PD11：k4
*	PD12：k3
*/
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA,时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOA,时钟
 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP对应引脚PA0--K1按键
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//WK_UP对应引脚PD9--K1按键
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOD9
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//WK_UP对应引脚PD10--K1按键
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOD10
 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//WK_UP对应引脚PD11--K1按键
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOD11
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//WK_UP对应引脚PD12--K1按键
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOD12
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，WKUP按下 --对应K1按键

uint8_t KEY_Scan(uint8_t mode)
{	 
	static u8 key_up = 1;//按键按松开标志

	
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(NEXT==1))
//	{
//		delay_ms(10);//去抖动 
//		key_up=0;
//		if(NEXT==1)return 1;
//	}else if(NEXT==0)key_up=1; 	    
// 	return 0;// 无按键按下
	
//	if(mode)
//		key_up=1;  //支持连按		  
//	if(key_up&&(ENTER==0))
//	{
//		delay_ms(10);//去抖动 
//		key_up=0;
//		if(ENTER==0)
//			return ENTER_PRES;
//	}else if(ENTER==1)
//		key_up=1; 	

//    key_up = 0;
// 	return 0;// 无按键按下
	
	if(mode)
	key_up = 1;  //支持连按	
	if( (key_up == 1) &&((NEXT==1)||(ENTER==0)||(LEFT==0)||(RIGHT==0)||(PREV==0)))
	{
		delay_ms(10);//去抖动 
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
 	return 0;// 无按键按下
}




















