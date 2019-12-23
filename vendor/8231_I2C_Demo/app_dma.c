/********************************************************************************************************
 * @file     app_dma.c
 *
 * @brief    This is the header file for TLSR8231
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
 * @par      History:
 * 			 1.initial release(May. 24 2019)
 *
 * @version  A001
 *
 *******************************************************************************************************/
#include "app_config.h"
#if(I2C_MODE == I2C_DMA_MODE)
/*********************************************************************************
	I2C MCK:  PA5 PB4 PB6 PC5
    I2C MSD : PA6 PB5 PB7 PC4

	I2C CK :  PA3 PA5
	I2C SD :  PA4 PA6
 *********************************************************************************/
#define  	I2C_MASTER_DEVICE        	1   //i2c master demo
#define     I2C_SLAVE_DEVICE			2   //i2c slave demo

#define     I2C_DEVICE					2
#define     BUFF_DATA_LEN				16
#define     SLAVE_DEVICE_ADDR			0x9000
#define     SLAVE_DEVICE_ADDR_LEN		2
#define     I2C_CLK_SPEED				400000

volatile unsigned char i2c_tx_buff[BUFF_DATA_LEN] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
volatile unsigned char i2c_rx_buff[BUFF_DATA_LEN] = {0};
void user_init()
{
	delay_ms(2000);

#if(I2C_DEVICE == I2C_MASTER_DEVICE)
	 CFG_PA5_MCK();//MCK : A5
	 CFG_PA6_MSD();//MCK : A6
	i2c_master_init(0x5C, (unsigned char)(CLOCK_SYS_CLOCK_HZ/(4* I2C_CLK_SPEED)) );
#elif(I2C_DEVICE == I2C_SLAVE_DEVICE)
	 CFG_PA5_CK();//CK : A5
	 CFG_PA6_SD();//SD : A6
	i2c_slave_init(0x5C, I2C_SLAVE_DMA, NULL);//reg_i2c_irq_clr_status = (FLD_HOST_CMD_IRQ | FLD_HOST_READ_IRQ);  //clean irq status
	reg_irq_mask |= FLD_IRQ_MIX_CMD_EN;  // i2c interrupt
	irq_enable();
#endif
}

void main_loop (void)
{
#if(I2C_DEVICE == I2C_MASTER_DEVICE)
	delay_ms(500);
	i2c_tx_buff[0]++;
	i2c_dma_write_buff(SLAVE_DEVICE_ADDR, SLAVE_DEVICE_ADDR_LEN, (unsigned char *)i2c_tx_buff, BUFF_DATA_LEN);
	delay_ms(500);
	i2c_dma_read_buff(SLAVE_DEVICE_ADDR,  SLAVE_DEVICE_ADDR_LEN, (unsigned char *)i2c_rx_buff, BUFF_DATA_LEN);

#endif
}
#endif
