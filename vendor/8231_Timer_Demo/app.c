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
#include "drivers.h"
#include "app_config.h"
#define LED1	GPIO_PA7
#define LED2	GPIO_PA0

#define GPIO_CHN4 GPIO_PB0





extern unsigned char timer0_irq_flag ;
extern unsigned int timer0_tick;
void user_init()
{
	delay_ms(2000);  //leave enough time for SWS_reset when power on
	//1.init the LED pin,for indication
	gpio_set_func(LED1 ,AS_GPIO);
	gpio_set_output_en(LED1, 1); //enable output
	gpio_set_input_en(LED1 ,0);//disable input
	gpio_write(LED1, 0);              //LED On

	gpio_set_func(LED2 ,AS_GPIO);
	gpio_set_output_en(LED2, 1); //enable output
	gpio_set_input_en(LED2 ,0);//disable input
	gpio_write(LED2, 0);              //LED On


#if (TIMER_MODE==TIMER_SYS_CLOCK_MODE)

	timer0_set_mode(TIMER_MODE_SYSCLK,0,1000 * CLOCK_SYS_CLOCK_1MS);
	timer_start(TIMER0);

#elif(TIMER_MODE == TIMER_GPIO_TRIGGER_MODE)
	timer0_gpio_init(GPIO_CHN4, pol_falling);
	irq_enable();
	timer0_set_mode(TIMER_MODE_GPIO_TRIGGER,0,3);
	timer_start(TIMER0);

#elif(TIMER_MODE==TIMER_GPIO_WIDTH_MODE)
	timer0_gpio_init(GPIO_CHN4, pol_falling);
	irq_enable();
	timer0_set_mode(TIMER_MODE_GPIO_WIDTH,0,400);
	timer_start(TIMER0);

#elif(TIMER_MODE==TIMER_GPIO_TICK_MODE)
	timer0_set_mode(TIMER_MODE_TICK,0,0);
	timer_start(TIMER0);
#elif(TIMER_MODE==TIMER_WATCHDOG_MODE)
	//reg_tmr2_tick = 0;
	wd_set_interval_ms(1000,CLOCK_SYS_CLOCK_1MS);
	gpio_write(LED2, 0);
	delay_ms(300);
	gpio_write(LED2, 1);
	delay_ms(300);
	wd_start();
#endif

}


/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
void main_loop (void)
{
#if(TIMER_MODE==TIMER_GPIO_WIDTH_MODE)
	gpio_write(LED2, 0);
	delay_ms(300);
	gpio_write(LED2, 1);
	delay_ms(300);
#elif(TIMER_MODE==TIMER_GPIO_TICK_MODE)
	timer0_tick =READ_REG32(0x630); //read timer0 tick
	if(timer0_tick >= 0x9fffff)
	{
		reg_tmr0_tick = 0;
		timer0_irq_flag = !timer0_irq_flag;
	}
#endif
	if(timer0_irq_flag)
		gpio_write(LED2, 1);
	else
		gpio_write(LED2, 0);

	gpio_write(LED1, 1);
	delay_ms(300);
	gpio_write(LED1, 0);
	delay_ms(300);
}



