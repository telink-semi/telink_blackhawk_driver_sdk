/********************************************************************************************************
 * @file	app_bqb.c
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
#include "BQB/bqb.h"
#if(TEST_DEMO==BQB_DEMO)
unsigned char cap;
unsigned  char g_tp0;
unsigned  char g_tp1;
#define BQB_UART_BUAD	   115200
void read_otp_para(void)
{
	cap = otp_read(CAP_VALUE);
	if(cap != 0xff && cap > 0xbf && cap < 0xe0 ){
		analog_write(0x81,cap);
	}else{
		analog_write(0x81,0xd0);
	}
	g_tp0 = otp_read(TP_LOW_VALUE);
	g_tp1 = otp_read(TP_HIGH_VALUE);
	if((g_tp0!=0xff) && (g_tp1!=0xff) && (g_tp1!=0) && (g_tp0!=0)){
		rf_set_tp(g_tp0,g_tp1);
	}
}
void user_init(void)
{
	rf_set_ble_1M_NO_PN_mode();

	read_otp_para();

	uart_reset();  //will reset uart digital registers from 0x90 ~ 0x9f, so uart setting must set after this reset

	uart_set_pin(UART_TX_PB4, UART_RX_PB5);// uart tx/rx pin set

	uart_init_baudrate(BQB_UART_BUAD,CLOCK_SYS_CLOCK_HZ,0, 0);

	uart_Parity(PARITY_NONE);

	uart_init_StopBit(STOP_BIT_ONE);

	uart_dma_en(0, 0);

	irq_clr_mask(FLD_IRQ_DMA_EN);

	dma_set_irq_en(FLD_DMA_CHN_UART_RX | FLD_DMA_CHN_UART_TX, 0);

	uart_irq_en(1,0);   //uart RX irq enable

	uart_ndma_set_triglevel(1,0);	//set the trig level. 1 indicate one byte will occur interrupt

	phy_test_init();
}

void main_loop(void)
{
	phytest ();
}

#endif
