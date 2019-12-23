/********************************************************************************************************
 * @file     app_normal.c
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
