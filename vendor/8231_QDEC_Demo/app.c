/********************************************************************************************************
 * @file     app.c
 *
 * @brief    This is the head file for TLSR8231
 *
 * @author	 Telink
 * @date     may 24, 2019
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
/*********************************************************************************
    PD1A,PD1B
	PD3A,PD3B,
	PC3A,PC3B,
	PB3A,PB3B,
	PB4A,PB4B,
	PB5A,PB5B,
	PA0A,PA0B
	PA1A,PA1B,

 *********************************************************************************/
#define QDEC_CHA GPIO_PA0
#define QDEC_CHB GPIO_PA1
char qdec_count = 0;
void user_init()
{
	delay_ms(2000);  //leave enough time for SWS_reset when power on


	gpio_set_qdec_func(QDEC_CHA,AS_GPIO);
	gpio_set_output_en(QDEC_CHA,0);
	gpio_set_input_en(QDEC_CHA,1);


	gpio_set_qdec_func(QDEC_CHB,AS_GPIO);
	gpio_set_output_en(QDEC_CHB,0);
	gpio_set_input_en(QDEC_CHB,1);
	qdec_clk_en ();
	qdec_set_mode(DOUBLE_ACCURACY_MODE);
	qdec_set_pin(PA0A,PA1B);
	//qdec_set_debouncing(1);



}


void main_loop (void)
{

	qdec_count = qdec_get_count_value();

	delay_ms(100);

}



