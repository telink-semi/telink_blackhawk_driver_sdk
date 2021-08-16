/********************************************************************************************************
 * @file	app_emi.c
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
#if(TEST_DEMO==EMI_DEMO)
struct  test_list_s {
	unsigned char  cmd_id;
	void	 (*func)(RF_TxPowerTypeDef pwr,signed char rf_chn);
};
#define     RF_RSSI					0x8004
#define 	PACKTET_NUMBER_MODE		0X8005
#define		RUM_CMD					0x8006
#define		RIGIG_CMD				0X8007
#define 	RF_POWER_LEVEL			0X8008
#define 	RF_CHN					0x8009
#define 	RF_MODE					0x800a
#define 	RF_HOP_ENABLE			0x800b
#define     RF_REC_NUMB				0x800c
#if 0
#define CAP_VALUE					0x77000
#define TP_LOW_VALUE				0x77040
#define TP_HIGH_VALUE				0x77041
#else
//Modify the position of cap and tp calibration values in OTP.modified by zhiwei,confirmed by sunpeng.2021810
#define CAP_VALUE					0x3fa8
#define TP_LOW_VALUE				0x3fa6
#define TP_HIGH_VALUE				0x3fa7
#endif
unsigned char  pri_tx_packet[48]  __attribute__ ((aligned (4))) = {0x26,0x00,0x00,0x00,0x25};//{19,0,0,0,20,0,0};
unsigned char  ble_tx_packet [48]  __attribute__ ((aligned (4))) = {39, 0, 0, 0,0, 37};
unsigned char  *packet;
unsigned char  mode=0;//1
unsigned char  power_level = 1;
unsigned char  chn = 2;//2
unsigned char  cmd_now=1;//2
unsigned char  run=1;
unsigned char  tx_cnt=0;


void emicarrieronly(RF_TxPowerTypeDef pwr,signed char rf_chn);
void emi_con_prbs9(RF_TxPowerTypeDef pwr,signed char rf_chn);
void emirx(RF_TxPowerTypeDef pwr, signed char rf_chn);
void emitxprbs9(RF_TxPowerTypeDef pwr,signed char rf_chn);
void emitx55(RF_TxPowerTypeDef pwr,signed char rf_chn);
void emitx0f(RF_TxPowerTypeDef pwr,signed char rf_chn);

struct  test_list_s  ate_list[] = {
	{0x01,emicarrieronly},
	{0x02,emi_con_prbs9},
	{0x03,emirx},
	{0x04,emitxprbs9},
	{0x05,emitx55},
	{0x06,emitx0f},
	//{0x07,emi_con_tx55},
	//{0x08,emi_con_tx0f},
};
unsigned  char g_tp0;
unsigned  char g_tp1;
unsigned char cap;
#if 0
void read_flash_para(void)
{
	flash_read_page(CAP_VALUE,1,&cap);
	if(cap != 0xff && cap > 0xbf && cap < 0xe0 )
	{
		rf_update_internal_cap(cap);
	}
	else
	{
		rf_update_internal_cap(0xd0);
	}
	flash_read_page(TP_LOW_VALUE,1,&g_tp0);
	flash_read_page(TP_HIGH_VALUE,1,&g_tp1);
}
#else
void read_otp_para(void)
{

	cap = otp_read(CAP_VALUE);
	if(cap != 0xff && cap > 0xbf && cap < 0xe0 ){
		rf_update_internal_cap(cap);
	}else{
		rf_update_internal_cap(0xd0);
	}
	g_tp0 = otp_read(TP_LOW_VALUE);
	g_tp1 = otp_read(TP_HIGH_VALUE);
	if((g_tp0!=0xff) && (g_tp1!=0xff) && (g_tp1!=0) && (g_tp0!=0)){
		rf_set_tp(g_tp0,g_tp1);
	}
}
#endif
void emi_init(void)
{
	write_reg8(PACKTET_NUMBER_MODE,tx_cnt);//tx_cnt
	write_reg8(RUM_CMD,	run);//run
	write_reg8(RIGIG_CMD,	cmd_now);//cmd
	write_reg8(RF_POWER_LEVEL,	power_level);//power
	write_reg8(RF_CHN,	chn);//chn
	write_reg8(RF_MODE,	mode);//mode
	write_reg8(RF_RSSI,	0);
	write_reg32(RF_REC_NUMB,	0);
}

void emi_service_loop(void)
{
	unsigned char i=0;
	while(1)
	{
	   run = read_reg8(RUM_CMD);  // get the run state!
	   if(run!=0)
	   {
		   irq_disable();
		   power_level = read_reg8(RF_POWER_LEVEL);
		   chn = read_reg8(RF_CHN);
		   mode = read_reg8(RF_MODE);
		   cmd_now = read_reg8(RIGIG_CMD);  // get the command!
		   tx_cnt = read_reg8(PACKTET_NUMBER_MODE);
			for (i=0; i<sizeof (ate_list)/sizeof (struct test_list_s); i++)
			{
				if(cmd_now == ate_list[i].cmd_id)
				{
					if(mode==0)//ble 1M NO PN mode
					{
						rf_drv_init(RF_MODE_BLE_1M_NO_PN);
						packet = ble_tx_packet;
					}
					else if(mode==1)//ble 2M NO PN mode
					{
						rf_drv_init(RF_MODE_BLE_2M_NO_PN);
						packet = ble_tx_packet;
					}
#if PRI_2M_EN
					else if(mode==2)//pri 2M mode
					{
						rf_drv_init(RF_MODE_PRI_2M);
						packet = pri_tx_packet;
					}
#endif
					read_otp_para();
					ate_list[i].func(power_level,chn);
					rf_set_tx_rx_off();
					break;
				}

			}
			run = 0;
			write_reg8(RUM_CMD, run);
	   }
	}

}

void emicarrieronly(RF_TxPowerTypeDef pwr,signed char rf_chn)
{
	rf_emi_single_tone(pwr,rf_chn);

	while( ((read_reg8(RUM_CMD)) == run ) &&  ((read_reg8(RIGIG_CMD)) == cmd_now )\
			&& ((read_reg8(RF_POWER_LEVEL)) == power_level ) &&  ((read_reg8(RF_CHN)) == chn )\
			&& ((read_reg8(RF_MODE)) == mode ))
	{
	}
}

void emi_con_prbs9(RF_TxPowerTypeDef pwr,signed char rf_chn)
{
	rf_emi_tx_continue_setup(pwr,rf_chn,0);

	while( ((read_reg8(RUM_CMD)) == run ) &&  ((read_reg8(RIGIG_CMD)) == cmd_now )\
			&& ((read_reg8(RF_POWER_LEVEL)) == power_level ) &&  ((read_reg8(RF_CHN)) == chn )\
			&& ((read_reg8(RF_MODE)) == mode ))
	{
		rf_continue_mode_run();
	}
}

void emitxprbs9(RF_TxPowerTypeDef pwr,signed char rf_chn)
{
	unsigned int tx_num=0;//Add a mode that limits the number of packets sent to 1000.modified by zhiwei,confirmed by zhiwei.20210806
	rf_emi_tx_brust_setup(pwr,rf_chn);
	while( ((read_reg8(RUM_CMD)) == run ) &&  ((read_reg8(RIGIG_CMD)) == cmd_now )\
			&& ((read_reg8(RF_POWER_LEVEL)) == power_level ) &&  ((read_reg8(RF_CHN)) == chn )\
			&& ((read_reg8(RF_MODE)) == mode ))
	{
		if(mode == 0 || mode == 1)
		{
			packet[4] = 0;//type
			gen_prbs9 (packet + 6, 37);
			delay_us(625);
		}
		else
		{
			gen_prbs9(packet + 5,37);
			delay_us(625*2);
		}
		rf_start_stx(packet,read_reg32(0x740) + 10);

		if(tx_cnt)
		{
			tx_num++;
			if(tx_num>=1000)
				break;
		}
	}
}

void emitx0f(RF_TxPowerTypeDef pwr,signed char rf_chn)
{
	unsigned int tx_num=0;
	int i;
	rf_emi_tx_brust_setup(pwr,rf_chn);
	if(mode == 0 || mode == 1)
	{
		packet[4] = 1;//type
		for( i=0;i<37;i++)
		{
			packet[6+i] = 0x0f;
		}
	}
	else
	{
		packet[5] = 1;
		for( i=0;i<37;i++)
		{
			packet[5+i] = 0x0f;
		}
	}
	while( ((read_reg8(RUM_CMD)) == run ) &&  ((read_reg8(RIGIG_CMD)) == cmd_now )\
			&& ((read_reg8(RF_POWER_LEVEL)) == power_level ) &&  ((read_reg8(RF_CHN)) == chn )\
			&& ((read_reg8(RF_MODE)) == mode ))
	{
		rf_start_stx(packet,read_reg32(0x740) + 10);
		if(mode == 0 || mode == 1)
		{
			delay_us(625);
		}
		else
		{
			delay_us(625*2);
		}
		if(tx_cnt)
		{
			tx_num++;
			if(tx_num>=1000)
				break;
		}
	}
}

void emitx55(RF_TxPowerTypeDef pwr,signed char rf_chn)
{
	unsigned int tx_num=0;
	int i;
	rf_emi_tx_brust_setup(pwr,rf_chn);
	if(mode == 0 || mode == 1)
	{
		packet[4] = 2;//type
		for( i=0;i<37;i++)
		{
			packet[6+i] = 0x55;
		}
	}
	else
	{
		packet[5] = 2;
		for( i=0;i<37;i++)
		{
			packet[5+i] = 0x55;
		}
	}
	while( ((read_reg8(RUM_CMD)) == run ) &&  ((read_reg8(RIGIG_CMD)) == cmd_now )\
			&& ((read_reg8(RF_POWER_LEVEL)) == power_level ) &&  ((read_reg8(RF_CHN)) == chn )\
			&& ((read_reg8(RF_MODE)) == mode ))
	{
		rf_start_stx(packet,read_reg32(0x740) + 10);
		if(mode == 0 || mode == 1)
		{
			delay_us(625);
		}
		else
		{
			delay_us(625*2);
		}

		if(tx_cnt)
		{
			tx_num++;
			if(tx_num>=1000)
				break;
		}
	}
}

void emirx( RF_TxPowerTypeDef pwr, signed char rf_chn)
{
	rf_emi_rx(rf_chn);
	cmd_now = 0;//Those two sentences for dealing with the problem that click RxTest again the value of emi_rx_cnt not be cleared in emi rx test
	write_reg8(RIGIG_CMD, cmd_now);//modified by zhiwei,confirmed by zhiwei.20210806
	while( ((read_reg8(RUM_CMD)) == run ) &&  ((read_reg8(RIGIG_CMD)) == cmd_now )\
			&& ((read_reg8(RF_POWER_LEVEL)) == power_level ) &&  ((read_reg8(RF_CHN)) == chn )\
			&& ((read_reg8(RF_MODE)) == mode ))
	{
		rf_emi_rx_loop();
		write_reg8(RF_RSSI,rf_emi_get_rssi_avg());
		write_reg32(RF_REC_NUMB,rf_emi_get_rxpkt_cnt());

	}
}

void user_init()
{
	emi_init();
}

void main_loop (void)
{
	emi_service_loop();
}

#endif
