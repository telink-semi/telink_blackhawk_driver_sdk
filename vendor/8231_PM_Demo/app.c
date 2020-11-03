/********************************************************************************************************
 * @file     app.c
 *
 * @brief    This is the source file for TLSR8231
 *
 * @author	 Telink
 * @date     May 8, 2018
 *
 * @par      Copyright (c) 2018, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *           The information contained herein is confidential property of Telink
 *           Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *           of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *           Co., Ltd. and the licensee or the terms described here-in. This heading
 *           MUST NOT be removed from this file.
 *
 *           Licensees are granted free, non-transferable use of the information in this
 *           file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 * @par      History:
 * 			 1.initial release(DEC. 26 2018)
 *
 * @version  A001
 *
 *******************************************************************************************************/

#include "app_config.h"

void user_init()
{
	delay_ms(2000);  //leave enough time for SWS_reset when power on

	//1.init the LED pin,for indication
	gpio_set_func(LED1 ,AS_GPIO);
	gpio_set_output_en(LED1, 1);      //enable output
	gpio_set_input_en(LED1 ,0);       //disable input
	gpio_write(LED1, 0);              //LED Off

	gpio_set_func(LED2 ,AS_GPIO);
	gpio_set_output_en(LED2, 1);      //enable output
	gpio_set_input_en(LED2 ,0);       //disable input
	gpio_write(LED2, 0);              //LED Off

	gpio_set_func(LED3 ,AS_GPIO);
	gpio_set_output_en(LED3, 1);      //enable output
	gpio_set_input_en(LED3 ,0);       //disable input
	gpio_write(LED3, 0);              //LED On

//Since not all GPIOs has analog pull_up,(just PA<7:5>,PB<7:0> has).So use this function:gpio_set_up_30k to set pull_up.
#if(PM_MODE==SUSPEND_CORE_WAKEUP)
        unsigned char result=0;
        result=gpio_set_wakeup(GPIO_PD2, LEVEL_HIGH, 1);   //gpio core wakeup
		if(result==1){
			gpio_set_up_down_resistor(GPIO_PD2,GPIO_PULL_DN_100K);
		}
		else{
			gpio_set_up_30k(GPIO_PD2);
		}
#elif(PM_MODE==SUSPEND_PAD_WAKEUP)
	pm_set_gpio_wakeup(GPIO_PB3, LEVEL_HIGH, 1);  //gpio pad wakeup
	gpio_set_up_down_resistor(GPIO_PB3, GPIO_PULL_DN_100K);
#elif(PM_MODE == DEEP_PAD_WAKEUP)
	pm_set_gpio_wakeup(GPIO_PB7, LEVEL_LOW, 1);
	gpio_set_up_down_resistor(GPIO_PB7, GPIO_PULL_UP_10K);
	pm_sleep_wakeup(RETENTION_DEEPSLEEP_MODE , PM_WAKEUP_PAD, 0);

#elif(PM_MODE==DEEP_32K_WAKEUP)

#if DELAY_3S
	delay_ms(3000);
#else
	delay_ms(1000);
	gpio_write(LED1,0);
	delay_ms(1000);
	gpio_write(LED1,1);
	delay_ms(1000);
#endif
	pm_sleep_wakeup(RETENTION_DEEPSLEEP_MODE , PM_WAKEUP_TIMER,(get_sys_tick()+5000*CLOCK_SYS_TIMER_CLK_1MS));
#endif
}


/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
#if(PM_MODE==SUSPEND_CORE_WAKEUP)

	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_CORE, 0);//PM_WAKEUP_CORE

#elif(PM_MODE==SUSPEND_PAD_WAKEUP)

	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_PAD, 0);

#elif(PM_MODE==SUSPEND_32K_WAKEUP)

	pm_sleep_wakeup(SUSPEND_MODE, PM_WAKEUP_TIMER, get_sys_tick() + 1000*CLOCK_SYS_TIMER_CLK_1MS);

#endif

#if DELAY_3S
	delay_ms(3000);
#else
	gpio_write(LED1, 0);
	delay_ms(1000);
	gpio_write(LED1, 1);
	delay_ms(1000);
#endif
}



