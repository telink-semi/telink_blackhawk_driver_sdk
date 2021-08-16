/********************************************************************************************************
 * @file	app_map.c
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
#if(I2C_MODE == I2C_MAPPING_MODE)
/*********************************************************************************
	I2C MCK:  PA5 PB4 PB6 PC5
    I2C MSD : PA6 PB5 PB7 PC4

	I2C CK :  PA3 PA5
	I2C SD :  PA4 PA6
 *********************************************************************************/
#define  	I2C_MASTER_DEVICE        	1   //i2c master demo
#define     I2C_SLAVE_DEVICE			2   //i2c slave demo
#define     I2C_DEVICE					I2C_MASTER_DEVICE
#define     BUFF_DATA_LEN				64
#define     I2C_CLK_SPEED				400000

volatile unsigned char i2c_tx_buff[BUFF_DATA_LEN] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
volatile unsigned char i2c_rx_buff[BUFF_DATA_LEN] = {0};
__attribute__((aligned(128))) unsigned char i2c_slave_mapping_buff[128] = {0};

void user_init()
{
	delay_ms(2000);

#if(I2C_DEVICE == I2C_MASTER_DEVICE)
	CFG_PB4_MCK();//MCK : B4
	CFG_PB5_MSD();//MSD : B5
	i2c_master_init(0x5C, (unsigned char)(CLOCK_SYS_CLOCK_HZ/(4* I2C_CLK_SPEED)) ); //200kb
#elif(I2C_DEVICE == I2C_SLAVE_DEVICE)
	CFG_PA3_CK();//CK : A3
	CFG_PA4_SD();//SD : A4
	i2c_slave_init(0x5C, I2C_SLAVE_MAP, (unsigned char *)i2c_slave_mapping_buff+64);
	reg_irq_mask |= FLD_IRQ_MIX_CMD_EN;
	irq_enable();
#endif
}

void main_loop (void)
{
#if(I2C_DEVICE == I2C_MASTER_DEVICE)
	delay_ms(500);
	i2c_tx_buff[0]++;
	i2c_map_write_buff((unsigned char*)i2c_tx_buff, BUFF_DATA_LEN);
	delay_ms(500);
	i2c_map_read_buff((unsigned char*)i2c_rx_buff, BUFF_DATA_LEN);
#endif
}
#endif
