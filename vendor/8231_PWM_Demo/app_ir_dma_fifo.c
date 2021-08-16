/********************************************************************************************************
 * @file	app_ir_dma_fifo.c
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
#if (PWM_MODE==PWM_IR_DMA_FIFO)
#define PWM_ID					PWM0//Only PWM0 supports IR FIFO mode
#define IR_DMA_CARRIER_FREQ				38000
#define IR_DMA_MAX_TICK					(CLOCK_SYS_CLOCK_HZ/IR_DMA_CARRIER_FREQ)
#define IR_DMA_CMP_TICK					(IR_DMA_MAX_TICK/3)

#define IR_DMA_SHADOW_CARRIER_FREQ		56000
#define IR_DMA_SHADOW_MAX_TICK			(CLOCK_SYS_CLOCK_HZ/IR_DMA_SHADOW_CARRIER_FREQ)
#define IR_DMA_SHADOW_CMP_TICK			(IR_DMA_SHADOW_MAX_TICK/2)


unsigned short IR_DMA_Buff[64]={0};

void user_init()
{     delay_ms(2000);

pwm_set_clk(CLOCK_SYS_CLOCK_HZ, CLOCK_SYS_CLOCK_HZ);

PWM0_CFG_GPIO_A0();//set PA0 as PWM0 function output;
pwm_set_mode(PWM0,PWM_IR_DMA_FIFO_MODE);
pwm_set_max_and_cmp(PWM_ID, IR_DMA_MAX_TICK, IR_DMA_CMP_TICK);
pwm_set_shadow_max_and_cmp(PWM_ID,IR_DMA_SHADOW_MAX_TICK, IR_DMA_SHADOW_CMP_TICK);
unsigned char index=2;
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(1, PWM0_PULSE_NORMAL, 9000 * CLOCK_SYS_CLOCK_1US/IR_DMA_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(0, PWM0_PULSE_NORMAL, 4500 * CLOCK_SYS_CLOCK_1US/IR_DMA_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(1, PWM0_PULSE_NORMAL, 560 * CLOCK_SYS_CLOCK_1US/IR_DMA_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(0, PWM0_PULSE_NORMAL, 560 * CLOCK_SYS_CLOCK_1US/IR_DMA_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(1, PWM0_PULSE_NORMAL, 560 * CLOCK_SYS_CLOCK_1US/IR_DMA_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(0, PWM0_PULSE_NORMAL, 1690 * CLOCK_SYS_CLOCK_1US/IR_DMA_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(1, PWM0_PULSE_NORMAL, 560 * CLOCK_SYS_CLOCK_1US/IR_DMA_MAX_TICK);

IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(1, PWM0_PULSE_SHADOW, 9000 * CLOCK_SYS_CLOCK_1US/IR_DMA_SHADOW_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(0, PWM0_PULSE_SHADOW, 4500 * CLOCK_SYS_CLOCK_1US/IR_DMA_SHADOW_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(1, PWM0_PULSE_SHADOW, 560 * CLOCK_SYS_CLOCK_1US/IR_DMA_SHADOW_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(0, PWM0_PULSE_SHADOW, 560 * CLOCK_SYS_CLOCK_1US/IR_DMA_SHADOW_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(1, PWM0_PULSE_SHADOW, 560 * CLOCK_SYS_CLOCK_1US/IR_DMA_SHADOW_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(0, PWM0_PULSE_SHADOW, 1690 * CLOCK_SYS_CLOCK_1US/IR_DMA_SHADOW_MAX_TICK);
IR_DMA_Buff[index++]= pwm_ir_dma_fifo_set_waveform(1, PWM0_PULSE_SHADOW, 560 * CLOCK_SYS_CLOCK_1US/IR_DMA_SHADOW_MAX_TICK);

unsigned int length = index*2 - 4;//The first four bytes are data length bytes, not included in the actual length to be sent
unsigned char* buff = &IR_DMA_Buff[0];
buff[0]= length&0xff;
buff[1]= (length>>8)&0xff;
buff[2]= (length>>16)&0xff;
buff[3]= (length>>24)&0xff;
pwm_set_dma_addr(&IR_DMA_Buff);

//enable pwm0 ir dma fifo done irq
reg_irq_mask |= FLD_IRQ_SW_PWM_EN;
reg_pwm_irq_mask |= FLD_IRQ_PWM0_IR_DMA_FIFO_DONE;
irq_enable();

pwm_ir_dma_fifo_start_tx();
}

void main_loop (void)
{

	delay_ms(50);
}

#endif
