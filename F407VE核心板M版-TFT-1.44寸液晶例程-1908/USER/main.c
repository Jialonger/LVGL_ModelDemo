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

//STM32F407������ 
//1.44��Һ����--��ʾʵ��-�⺯���汾


int main(void)
{ 
// 	u8 x=0;
//	u8 lcd_id[12];				//���LCD ID�ַ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	printf("\r\n ���ڽ���MPU6050��ʼ�� \r\n");
	//while(mpu6050_init() == 0);
	
	printf("\r\n STM32F4xx���İ�\r\n");
	printf("\r\n ���Գ�������\r\n");
	
	LED_Init();					  //��ʼ��LED
	TIM3_Int_Init(10-1,9000-1);
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
//	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32F4xx ");
//	Gui_DrawFont_GBK16(0,32,BLUE,GRAY0," Һ�����Գ���");	 
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
     	//Test_Demo();	//Һ������������
		delay_ms(5);
		lv_timer_handler();
		
		
	} 
}
