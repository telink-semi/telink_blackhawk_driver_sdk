/********************************************************************************************************
 * @file     app_ir_dma_fifo.c
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

unsigned int length = index*2;
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
