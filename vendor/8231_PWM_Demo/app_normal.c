/********************************************************************************************************
 * @file	app_normal.c
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
#if (PWM_MODE==PWM_NORMAL)
/*********************************************************************************
	PWM0   :  PA0  PA7 PB2 PD1 PD3
	PWM0_N :  PB6  PC3 PD0

	PWM1   :  PB1  PB7  PC2 PD0
	PWM1_N :  PA2  PD1

	PWM2   :  PA4  PB3 PD2
	PWM2_N :  PA5  PB4 PC1

	PWM3   :  PA0  PC7 PD2
	PWM3_N :  PA1  PB3

	PWM4   :  PA3  PB0 PB5 PC6
	PWM4_N :  PA6


 *********************************************************************************/
#define PWM_ID		PWM2
void user_init()
{       delay_ms(2000);
	  pwm_set_clk(CLOCK_SYS_CLOCK_HZ, CLOCK_SYS_CLOCK_HZ);
	  //PWM0_CFG_GPIO_A0();
	  //PWM2_CFG_GPIO_A4();
	  PWM2_N_CFG_GPIO_A5();
	    //PWM4_CFG_GPIO_C6();//set C6 as PWM4 function output
		pwm_set_mode(PWM_ID	,PWM_NORMAL_MODE);
		pwm_set_max_and_cmp(PWM_ID, 1000 * CLOCK_SYS_CLOCK_1US, 500 * CLOCK_SYS_CLOCK_1US);
		pwm_start(PWM_ID);
		 delay_ms(200);
		 pwm_stop(PWM_ID);
}


void main_loop (void)
{
	delay_ms(50);

}

#endif
