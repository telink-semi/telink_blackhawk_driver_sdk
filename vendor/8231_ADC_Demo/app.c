/********************************************************************************************************
 * @file     app.c
 *
 * @brief    This is  the ADC of application for TLSR8231
 *
 * @author   Telink
 * @date     May 12, 2019
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

volatile unsigned short base_val;
volatile unsigned short vbat_val;
volatile unsigned int rns_val;
void user_init()
{
	adc_init();

	#if(ADC_MODE==ADC_BASE_MODE)
		adc_base_init(GPIO_PB1);
	#elif(ADC_MODE==ADC_VBAT_MODE)
		adc_vbat_init(GPIO_PB0);
	#endif

	adc_power_on(1);		//After setting the ADC parameters, turn on the ADC power supply control bit
}

void main_loop (void)
{
	#if(ADC_MODE==ADC_BASE_MODE)
		base_val = adc_set_sample_and_get_result();
	#elif (ADC_MODE==ADC_VBAT_MODE)
		vbat_val = adc_set_sample_and_get_result();
	#endif
}


