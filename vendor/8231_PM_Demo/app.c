/********************************************************************************************************
 * @file	app.c
 *
 * @brief	This is the source file for TLSR8231
 *
 * @author	Driver Group
 * @date	May 12, 2019
 *
 * @par     Copyright (c) 2018, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions
 *              in binary form must reproduce the above copyright notice, this list of
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *
 *              3. Neither the name of TELINK, nor the names of its contributors may be
 *              used to endorse or promote products derived from this software without
 *              specific prior written permission.
 *
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or
 *              relating to such deletion(s), modification(s) or alteration(s).
 *
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
	gpio_write(LED1, 1);
	delay_ms(1000);
	pm_set_gpio_wakeup(GPIO_PB7, LEVEL_LOW, 1);
	gpio_set_up_down_resistor(GPIO_PB7, GPIO_PULL_UP_10K);
	pm_sleep_wakeup(DEEPSLEEP_MODE , PM_WAKEUP_PAD, 0);

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
	pm_sleep_wakeup(DEEPSLEEP_MODE , PM_WAKEUP_TIMER,(get_sys_tick()+5000*CLOCK_SYS_TIMER_CLK_1MS));
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



