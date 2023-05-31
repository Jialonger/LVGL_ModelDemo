/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev_template.h"

#include "core/lv_group.h"
#include "key.h"
#include "led.h"
#include "ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void keypad_init(void);
static void keypad_read(lv_indev_t * indev, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);


/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_keypad;
extern lv_obj_t *ui_list;


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

	/*
	*	Group 
	*/

	
   
    /*------------------
     * Keypad
     * -----------------*/

    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    /*Register a keypad input device*/
    indev_keypad = lv_indev_create();
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, keypad_read);


    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/

	lv_group_t* ui_g = lv_group_create();
	
	lv_group_set_default(ui_g);
	
	//lv_group_add_obj(ui_g,ui_list);
	
	lv_indev_set_group(indev_keypad,ui_g);
	//lv_group_t *g
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


/*------------------
 * Keypad
 * -----------------*/

/*Initialize your keypad*/
static void keypad_init(void)
{
	
	KEY_Init();
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

//    /*Get the current x and y coordinates*/
//    mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
 
    uint32_t act_key = keypad_get_key();
	
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
			/*此处的代码不运行*/
            case ENTER_PRES:
                act_key = LV_KEY_ENTER ;LED2 = !LED2;
                break;
            case PREV_PRES:
                act_key = LV_KEY_PREV;LED2 = !LED2;
                break;
            case LEFT_PRES:
                act_key = LV_KEY_LEFT;LED2 = !LED2;
                break;
            case RIGHT_PRES:
                act_key = LV_KEY_RIGHT;LED2 = !LED2;
                break;
            case NEXT_PRES:
                act_key = LV_KEY_NEXT;LED2 = !LED2;
                break;
        }

        last_key = act_key;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
}


/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void)
{
    /*Your code comes here*/

//按键扫描函数	
    return 	KEY_Scan(0);  
}


#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
