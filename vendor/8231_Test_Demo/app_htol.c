/********************************************************************************************************
 * @file	app_htol.c
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
#if(TEST_DEMO == HTOL_TEST)

#define PWM_ID		PWM0

#define REC_BUFF_LEN    16
#define TRANS_BUFF_LEN  16

__attribute__((aligned(4))) unsigned char rec_buff[REC_BUFF_LEN]={0};
__attribute__((aligned(4))) unsigned char trans_buff[TRANS_BUFF_LEN] = {0x0c, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44,

																0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc};


#define BUFF_DATA_LEN    		16
#define SPI_CS_PIN				GPIO_PC2//SPI CS pin  GPIO_PC2 GPIO_PB5
#define SLAVE_ADDR				0x8000
#define SLAVE_ADDR_LEN			2
volatile unsigned char spi_tx_buff[BUFF_DATA_LEN]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};


#define     BUFF_DATA_LEN				16
#define     I2C_CLK_SPEED				400000

volatile unsigned char i2c_tx_buff[BUFF_DATA_LEN] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
volatile unsigned char i2c_rx_buff[BUFF_DATA_LEN] = {0};
__attribute__((aligned(128))) unsigned char i2c_slave_mapping_buff[128] = {0};

#define FLASH_ADDR				0x020000
#define FLASH_BUFF_LEN			256
volatile unsigned char Flash_Read_Buff[ FLASH_BUFF_LEN]={0};
volatile unsigned char Flash_Write_Buff[FLASH_BUFF_LEN]=
{		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
		0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
		0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,
		0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,
		0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,
		0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,
		0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,
		0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,


		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
		0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
		0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,
		0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,
		0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,
		0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,
		0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,
		0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,

		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
		0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
		0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,
		0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,
		0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,
		0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,
		0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,
		0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,

		0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
		0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,
		0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,
		0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,
		0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,
		0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,
		0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,
		0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,
};

volatile unsigned short base_val;

#define RF_FREQ					4//ble:RF_FREQ*2+2   private:2400+RF_FREQ
#define RF_POWER				RF_POWER_7dBm
#define ACCESS_CODE				0x39555539

unsigned char  rx_packet[64]  __attribute__ ((aligned (4)));
unsigned char  ble_tx_packet[48] __attribute__ ((aligned (4))) = {0x23,0x00,0x00,0x00,0x00,0x21,0x00,0x00,0x00,0x00,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};


typedef struct TIME_BLOCK
{
	unsigned int tick_bigcyc_begin;
    unsigned int tick_now;
    unsigned int tick_thiscyc_begin;
}Time_block;

Time_block time_block;


void user_init(void)
{
	gpio_set_func(GPIO_PC6 ,AS_GPIO);
	gpio_set_output_en(GPIO_PC6, 1); //enable output
	gpio_set_input_en(GPIO_PC6 ,0);//disable input
	gpio_write(GPIO_PC6, 0);

	gpio_set_func(GPIO_PD1 ,AS_GPIO);
	gpio_set_output_en(GPIO_PD1, 1); //enable output
	gpio_set_input_en(GPIO_PD1,0);//disable input
	gpio_write(GPIO_PD1, 0);

/******************PWM******************/
	pwm_set_clk(CLOCK_SYS_CLOCK_HZ, CLOCK_SYS_CLOCK_HZ);
	PWM0_CFG_GPIO_A0();
	pwm_set_mode(PWM_ID	,PWM_NORMAL_MODE);
	pwm_set_max_and_cmp(PWM_ID, 1000 * CLOCK_SYS_CLOCK_1US, 500 * CLOCK_SYS_CLOCK_1US);
	pwm_start(PWM_ID);
/******************UART******************/
	uart_reset();  //will reset uart digital registers from 0x90 ~ 0x9f, so uart setting must set after this reset
	uart_set_pin(UART_TX_PD2, UART_RX_PD3);// uart tx/rx pin set
	uart_init_baudrate(115200,CLOCK_SYS_CLOCK_HZ,(unsigned short *)&rec_buff,sizeof(rec_buff));
	uart_Parity(PARITY_NONE);
	uart_init_StopBit(STOP_BIT_ONE);
	uart_dma_en(1, 1); 	//uart data in hardware buffer moved by dma, so we need enable them first
	irq_set_mask(FLD_IRQ_DMA_EN);
	dma_set_irq_en(FLD_DMA_CHN_UART_RX | FLD_DMA_CHN_UART_TX, 1);   	//uart Rx/Tx dma irq enable
	uart_irq_en(0, 0);
/******************SPI******************/
	spi_master_init((unsigned char)(CLOCK_SYS_CLOCK_HZ/(2*500000)-1),SPI_MODE0);//div_clock. spi_clk = sys_clk/((div_clk+1)*2),mode select
	spi_master_set_pin(SPI_GPIO_GROUP_C2C3C4C5);//master mode: spi pin set
	spi_master_set_cs_pin(SPI_CS_PIN);
/******************I2C******************/
	CFG_PB4_MCK();//MCK : B4
	CFG_PB5_MSD();//MSD : B5
	i2c_master_init(0x5C, (unsigned char)(CLOCK_SYS_CLOCK_HZ/(4* I2C_CLK_SPEED)) ); //200kb
/******************Timer******************/
	timer0_set_mode(TIMER_MODE_SYSCLK,0,500 * CLOCK_SYS_CLOCK_1MS);
	timer_start(TIMER0);
/******************ADC******************/
	adc_init();
    adc_base_init(GPIO_PB1);
	adc_power_on(1);
/******************RF******************/
	rf_set_power_level_index (RF_POWER);
	rf_set_tx_rx_off();
	rf_set_ble_channel(RF_FREQ);
	rf_set_acc_code(ACCESS_CODE);


	irq_enable();

}

unsigned char AAA=0;

void main_loop(void)
{

	time_block.tick_thiscyc_begin = get_sys_tick();
	/******************UART******************/
	uart_dma_send((unsigned short*)&trans_buff);
	while(!timeout_ms(time_block.tick_thiscyc_begin,2));

	/*****************SPI******************/
	spi_write_buff(SLAVE_ADDR, SLAVE_ADDR_LEN,(unsigned char*)spi_tx_buff, BUFF_DATA_LEN,SPI_CS_PIN);
	while(!timeout_ms(time_block.tick_thiscyc_begin,4));

	/*****************I2C*****************/
	i2c_map_write_buff((unsigned char*)i2c_tx_buff, BUFF_DATA_LEN);
	while(!timeout_ms(time_block.tick_thiscyc_begin,6));

	/*****************FLASH*****************/
	flash_write_page(FLASH_ADDR, FLASH_BUFF_LEN,(unsigned char *)Flash_Write_Buff);
	flash_read_page(FLASH_ADDR, FLASH_BUFF_LEN,(unsigned char *)Flash_Read_Buff);
	while(!timeout_ms(time_block.tick_thiscyc_begin,8));

	/*****************ADC*****************/
	base_val = adc_set_sample_and_get_result();
	while(!timeout_ms(time_block.tick_thiscyc_begin,10));

	/*****************RF*****************/
	if((get_sys_tick() - time_block.tick_bigcyc_begin > 1000*CLOCK_SYS_TIMER_CLK_1MS)){
        AAA++;
		/***************GPIO Toggle*************/
		gpio_toggle(GPIO_PD1);
		/******************TX******************/
		rf_set_tx_on();
		delay_ms(1);
		rf_tx_pkt (ble_tx_packet);
		while(!rf_is_tx_finish());
		rf_clr_tx_finish();
		while( !(get_sys_tick() - time_block.tick_thiscyc_begin > 13*CLOCK_SYS_TIMER_CLK_1MS) );
		/******************RX******************/
		rf_set_rx_buff(rx_packet,64, 0);
		rf_set_rx_on ();
		time_block.tick_bigcyc_begin = get_sys_tick();
	}
	/*****************PM*****************/
//	pm_sleep_wakeup(DEEPSLEEP_MODE, PM_WAKEUP_TIMER,(get_sys_tick()+5000*CLOCK_SYS_TIMER_CLK_1MS));




}
#endif
