/********************************************************************************************************
 * @file	app_ir.c
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
