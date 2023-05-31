#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "key.h"

#include "GUI.h"
#include "Lcd_Driver.h"
#include "TFT_demo.h"

#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"

#include "lv_demo_stress.h"

#include "lv_demo_music.h"

#include "ui.h"

#include "mpu6050.h"

//STM32F407开发板 
//1.44寸液晶屏--显示实验-库函数版本


int main(void)
{ 
// 	u8 x=0;
//	u8 lcd_id[12];				//存放LCD ID字符串
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	printf("\r\n 正在进行MPU6050初始化 \r\n");
	//while(mpu6050_init() == 0);
	
	printf("\r\n STM32F4xx核心板\r\n");
	printf("\r\n 测试程序例程\r\n");
	
	LED_Init();					  //初始化LED
	TIM3_Int_Init(10-1,9000-1);
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
//	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32F4xx ");
//	Gui_DrawFont_GBK16(0,32,BLUE,GRAY0," 液晶测试程序");	 
//	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com ");
	
//	lv_obj_t* switch_obj = lv_switch_create(lv_scr_act());
//	lv_obj_set_size(switch_obj , 20 , 10);
//	lv_obj_align(switch_obj,LV_ALIGN_CENTER,0,0);
	ui_init( );
	//lv_demo_stress();
	//lv_demo_music();
	LED2 = 0;
	LED1 = 0;
	LED0 = 0;
	uint32_t count = 0;
  	while(1) 
	{		 
		count++;
		if(count == 200)
		{
			count = 0;
			LED0 = !LED0;
			LED1 = !LED1;
		}
     	//Test_Demo();	//液晶屏测试例程
		delay_ms(5);
		lv_timer_handler();
		
		
	} 
}
