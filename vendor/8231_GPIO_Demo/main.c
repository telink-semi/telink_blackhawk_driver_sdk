/********************************************************************************************************
 * @file	main.c
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


extern void user_init();
extern void main_loop (void);
volatile unsigned int gpio_irq_cnt;

/**
 * @brief		This function serves to handle the interrupt of MCU
 * @param[in] 	none
 * @return 		none
 */
_attribute_ram_code_ void irq_handler(void)
{
#if (GPIO_MODE == GPIO_IRQ )

	if((reg_irq_src & FLD_IRQ_GPIO_EN)==FLD_IRQ_GPIO_EN){
		reg_irq_src |= FLD_IRQ_GPIO_EN; // clear the relevant irq
		if(gpio_read(SW1)== 0){ // press key with low level to flash light
			delay_ms(10);
			if(gpio_read(SW1)== 0){
				gpio_irq_cnt++;
				gpio_toggle(LED1);
			}
		}
	}

#elif(GPIO_MODE == GPIO_IRQ_RSIC0)

	if((reg_irq_src & FLD_IRQ_GPIO_RISC0_EN)==FLD_IRQ_GPIO_RISC0_EN){
		reg_irq_src |= FLD_IRQ_GPIO_RISC0_EN; // clear the relevant irq

		if(gpio_read(SW2)== 0){ // press key with low level to flash light
			delay_ms(10);
			if(gpio_read(SW2)== 0){
				gpio_irq_cnt++;
				pio_toggle(LED1);
			}
		}
	}

#elif(GPIO_MODE == GPIO_IRQ_RSIC1)

	if((reg_irq_src & FLD_IRQ_GPIO_RISC1_EN)==FLD_IRQ_GPIO_RISC1_EN){
		reg_irq_src |= FLD_IRQ_GPIO_RISC1_EN; // clear the relevant irq

		if(gpio_read(SW2)== 0){ // press key with low level to flash light
			delay_ms(10);
			if(gpio_read(SW2)== 0){
				gpio_irq_cnt++;
				gpio_toggle(LED1);
			}
		}
	}

#elif(GPIO_MODE == GPIO_IRQ_RSIC2)

	if((reg_irq_src & FLD_IRQ_GPIO_RISC2_EN)==FLD_IRQ_GPIO_RISC2_EN){
		reg_irq_src |= FLD_IRQ_GPIO_RISC2_EN; // clear the relevant irq

		if(gpio_read(SW2)== 0){ // press key with low level to flash light
			delay_ms(10);
			if(gpio_read(SW2)== 0){
				gpio_irq_cnt++;
				gpio_toggle(LED1);
			}
		}
	}
#endif

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

	rf_mode_init();
	rf_set_ble_1M_mode();

	gpio_init();

	user_init();

	irq_enable();

	while (1) {
		main_loop ();
	}
	return 0;
}
