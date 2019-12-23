/********************************************************************************************************
 * @file     main.c
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
extern void user_init();
extern void main_loop (void);

_attribute_ram_code_ void irq_handler(void)
{

}

int main (void)
{
	system_init(BSP_INTERNAL_CAP_ENABLE);

	clock_init(SYS_CLK );
	gpio_init();
	user_init();
	//void qdec_clk_en();
	while (1)
	{

		main_loop();
	}
}



