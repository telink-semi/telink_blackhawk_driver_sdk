/********************************************************************************************************
 * @file     app.c
 *
 * @brief    This is the RF file for TLSR8231
 *
 * @author	 Telink
 * @date     May 8, 2018
 *
 * @par      Copyright (c) 2018, Telink Semiconductor (Shanghai) Co., Ltd.
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
 * 			 1.initial release(DEC. 26 2018)
 *
 * @version  A001
 *
 *******************************************************************************************************/

#include "drivers.h"
#include "app_config.h"
#if(RF_MODE==RF_PRIVATE_250K)

#define LED1     				GPIO_PB0
#define TX	1
#define RX	2
#define RF_TRX_MODE				RX

#define AUTO  	1
#define MANUAL  2
#define AUTO_MODE 			    AUTO


#define ESB_MODE  1
#define SB_MODE   2
#define NORDIC_MODE			    ESB_MODE
#define RX_PAYLOAD_LEN			32

#define RF_FREQ					47//ble:RF_FREQ*2+2   private&nordic:2400+RF_FREQ
#define RF_POWER				RF_POWER_0dBm
#define ACCESS_CODE				0x39517696

volatile unsigned int rx_cnt=0;
volatile unsigned int tx_cnt=0;
unsigned char  rx_packet[64]  __attribute__ ((aligned (4)));
unsigned char  ble_tx_packet[48] __attribute__ ((aligned (4))) = {0x23,0x00,0x00,0x00,0x00,0x21,0,0,0,0,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
unsigned char  Nordic_SB_tx_packet[48] __attribute__ ((aligned (4))) = {0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
unsigned char  Nordic_ESB_tx_packet[48] __attribute__ ((aligned (4))) = {0x21,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x33,0x04,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};




#if(AUTO_MODE == AUTO)

#define TX_INTERVAL_MS    1

void user_init()
{
	//1.init the LED pin,for indication
	gpio_set_func(LED1 ,AS_GPIO);
	gpio_set_output_en(LED1, 1); //enable output
	gpio_set_input_en(LED1 ,0);	 //disable input
	gpio_write(LED1, 0);         //LED On

	rf_set_power_level_index (RF_POWER);
	rf_set_tx_rx_off_auto();

	rf_set_channel(RF_FREQ,0);
	rf_set_acc_code(ACCESS_CODE);
	#if(NORDIC_MODE == ESB_MODE)

	#elif(NORDIC_MODE == SB_MODE)
		rf_pri_set_shockburst_len(RX_PAYLOAD_LEN);
	#endif
}

void main_loop (void)
{
#if(RF_TRX_MODE==TX)
	while(1)
	{
		#if(NORDIC_MODE == ESB_MODE)
			rf_start_stx (Nordic_ESB_tx_packet, get_sys_tick() + 16*1000*TX_INTERVAL_MS);
		#elif(NORDIC_MODE == SB_MODE)
			rf_start_stx (Nordic_SB_tx_packet, get_sys_tick() + 16*1000*TX_INTERVAL_MS);
		#endif
			while(!rf_is_tx_finish());
			rf_clr_tx_finish();
			tx_cnt++;
	}


#elif(RF_TRX_MODE==RX)
	rf_set_rx_buff(rx_packet,64, 0);
	rf_start_srx(get_sys_tick() + 100*16);

	while(1)
	{
		if(rf_is_rx_finish())
		{
		#if(NORDIC_MODE == ESB_MODE)
			if(RF_250K_PACKET_CRC_OK(rx_packet)&&RF_PRI_PACKET_LENGTH_OK(rx_packet))
		#elif(NORDIC_MODE == SB_MODE)
			if(RF_250K_PACKET_CRC_OK(rx_packet))
		#endif
			{
				gpio_toggle(LED1);
				rx_cnt++;
			}
			rf_clr_rx_finish();
			rf_set_tx_rx_off_auto();
			rf_start_srx(get_sys_tick() + 100*16);
		}
	}
#endif
}


#elif(AUTO_MODE == MANUAL)
void user_init()
{
	//1.init the LED pin,for indication
	gpio_set_func(LED1 ,AS_GPIO);
	gpio_set_output_en(LED1, 1); //enable output
	gpio_set_input_en(LED1 ,0);	//disable input
	gpio_write(LED1, 0);       //LED On

	rf_set_power_level_index (RF_POWER);
	rf_set_tx_rx_off();
	rf_set_channel(RF_FREQ,0);
	rf_set_acc_code(ACCESS_CODE);

#if(NORDIC_MODE == ESB_MODE)

#elif(NORDIC_MODE == SB_MODE)
	rf_pri_set_shockburst_len(RX_PAYLOAD_LEN);
#endif
}

void main_loop (void)
{
#if(RF_TRX_MODE==TX)

	rf_set_tx_on();
		delay_us(150);
	while(1)
	{
		delay_ms(1);
		Nordic_ESB_tx_packet[5]+=1;
		#if(NORDIC_MODE == ESB_MODE)
		rf_tx_pkt (Nordic_ESB_tx_packet);
		#elif(NORDIC_MODE == SB_MODE)
		rf_tx_pkt (Nordic_SB_tx_packet);
		#endif
		while(!rf_is_tx_finish());
		rf_clr_tx_finish();
		tx_cnt++;

	}

#elif(RF_TRX_MODE==RX)
	rf_set_rx_buff(rx_packet,128, 0);
	rf_set_rx_on();
	delay_us(150);

	while(1)
	{
		if(rf_is_rx_finish())
		{
		#if(NORDIC_MODE == ESB_MODE)
			if(RF_250K_PACKET_CRC_OK(rx_packet)&&RF_PRI_PACKET_LENGTH_OK(rx_packet))
		#elif(NORDIC_MODE == SB_MODE)
			if(RF_250K_PACKET_CRC_OK(rx_packet))
		#endif
			{
				gpio_toggle(LED1);
				rx_cnt++;
			}
			rf_clr_rx_finish();
			rf_set_tx_rx_off_auto();
		}
	}
#endif
}
#endif
#endif
