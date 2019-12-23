/********************************************************************************************************
 * @file     app_ir.c
 *
 * @brief    This is the head file for TLSR8231
 *
 * @author	 Telink
 * @date     May 24, 2019
 *
 * @par      Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd.
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
 *
 *******************************************************************************************************/
#include "app_config.h"
#if (PWM_MODE== PWM_IR)
#define PWM_ID					PWM0//Only PWM0 supports IR mode
#define PWM_PULSE_NUM			4
#define TX_GROUP_NUM			3

void user_init()
{
	delay_ms(2000);
	pwm_set_clk(CLOCK_SYS_CLOCK_HZ, CLOCK_SYS_CLOCK_HZ);
	PWM0_CFG_GPIO_A0();//set PA0 as PWM0 function output;
	pwm_set_mode( PWM0,PWM_IR_MODE);
	pwm_set_pulse_num(PWM_ID,PWM_PULSE_NUM);
	pwm_set_max_and_cmp(PWM_ID,  CLOCK_SYS_CLOCK_1S /36000, CLOCK_SYS_CLOCK_1S /(36000*3));
	pwm_set_irq_en(PWM0_PNUM_IRQ,1);
	irq_enable();
	pwm_start(PWM_ID);
#if (TX_GROUP_NUM == 1)
	pwm_set_mode( PWM0,PWM_COUNT_MODE);
#endif
}
volatile unsigned char n;

void main_loop (void)
{
#if (TX_GROUP_NUM > 1)
	if(reg_pwm_irq_state & FLD_IRQ_PWM0_PNUM){
		reg_pwm_irq_state |= FLD_IRQ_PWM0_PNUM;
		n++;
		if(n==(TX_GROUP_NUM-1)) pwm_set_mode(PWM0,PWM_COUNT_MODE);		//  5 group of IR and 1 group of count
	}
#endif
}
#endif
