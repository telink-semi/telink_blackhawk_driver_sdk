/********************************************************************************************************
 * @file     main.c
 *
 * @brief    This is the source file for TLSR8231
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

extern void user_init();
extern void main_loop (void);


int irq_cnt = 0;
int i2c_read_cnt = 0;
int i2c_write_cnt = 0;
 _attribute_ram_code_ void irq_handler(void)
{
	irq_cnt ++;

	unsigned char  irq_status = reg_i2c_slave_irq_status;

	if(irq_status & FLD_HOST_CMD_IRQ)
	{
		reg_i2c_slave_irq_status = irq_status; //clear all irq status

		if(irq_status & FLD_HOST_READ_IRQ)
		{
			i2c_read_cnt ++;
		}
		else
		{
			i2c_write_cnt ++;
		}
	}

}

/**
 * @brief		This is main function
 * @param[in]	none
 * @return      none
 */
int main (void)
{
	system_init(BSP_INTERNAL_CAP_ENABLE);

	clock_init(SYS_CLK);

	//rf_mode_init();
	//rf_set_ble_1M_mode();

	gpio_init();

	user_init();

	while (1) {
		main_loop ();
	}
}

