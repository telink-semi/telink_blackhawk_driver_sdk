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
//#include "tl_common.h"
#include "drivers.h"
#include "app_config.h"
#if (__PROJECT_5313_UART_DEMO__)
extern void user_init();
extern void main_loop (void);
#define REC_BUFF_LEN    16
#define TRANS_BUFF_LEN    16

extern volatile unsigned char uart_rx_flag;
extern volatile unsigned char uart_dmairq_tx_cnt;
extern volatile unsigned char uart_dmairq_rx_cnt;
extern volatile unsigned int  uart_ndmairq_cnt;
extern volatile unsigned char uart_ndmairq_index;
extern __attribute__((aligned(4))) unsigned char rec_buff[REC_BUFF_LEN];
extern __attribute__((aligned(4))) unsigned char trans_buff[TRANS_BUFF_LEN];


_attribute_ram_code_ __attribute__((optimize("-Os"))) void irq_handler(void)
{
#if (UART_MODE==UART_DMA)

	unsigned char uart_dma_irqsrc;
	//1. UART irq
	uart_dma_irqsrc = dma_get_irq_status();///in function,interrupt flag have already been cleared,so need not to clear DMA interrupt flag here

	if(uart_dma_irqsrc & FLD_DMA_CHN_UART_RX)
	{
		dma_clr_irq_status(FLD_DMA_CHN_UART_RX);

		uart_dmairq_rx_cnt++;

		//Received uart data in rec_buff, user can copy data here

	}
	if(uart_dma_irqsrc & FLD_DMA_CHN_UART_TX)
	{
		dma_clr_irq_status(FLD_DMA_CHN_UART_TX);

		uart_dmairq_tx_cnt++;
	}

	if(uart_is_parity_error())
	{
		uart_clear_parity_error();
	}
#elif(UART_MODE==UART_NDMA)

	static unsigned char uart_ndma_irqsrc;
	uart_ndma_irqsrc = uart_ndma_get_irq();  ///get the status of uart irq.
	if(uart_ndma_irqsrc)
	{
			rec_buff[uart_ndmairq_cnt++] = reg_uart_data_buf(uart_ndmairq_index);
			uart_ndmairq_index++;
			uart_ndmairq_index &= 0x03;// cycle the four registers 0x90 0x91 0x92 0x93, it must be done like this for the design of SOC.
			if(uart_ndmairq_cnt%16==0&&uart_ndmairq_cnt!=0)
			{
				uart_ndmairq_cnt = 0;
			}
	}
#endif
}

int main (void)
{

	system_init(BSP_INTERNAL_CAP_ENABLE);

	clock_init(SYS_CLK);

	gpio_init();

	user_init();

	irq_enable();

	while (1)
	{
		main_loop ();
	}
	return 0;
}
#endif
