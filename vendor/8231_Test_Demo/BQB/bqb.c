/********************************************************************************************************
 * @file	bqb.c
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
#include "bqb.h"
#include "../common/string.h"
#if(TEST_DEMO==BQB_DEMO)

#define AUTO 0

#define			CMD_RX				1
#define			CMD_TX				2
#define			CMD_END				3
#define			CMD_RESET			0

#define 	reg_rf_irq_status		REG_ADDR16(0xf20)

volatile unsigned int t0;
unsigned char tx_start_flag = 0;
unsigned char	buffer_phytest[256] __attribute__ ((aligned (4)));
unsigned char  tx_packet1[128] __attribute__ ((aligned (4))) = {0x09,0x00,0x00,0x00,0xed,0x07,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa};

unsigned char bqbtest_pkt[64] = {
		39, 0, 0, 0,
		0, 37,
		0, 1, 2, 3, 4, 5, 6, 7
};
unsigned char phyTest_Channel (unsigned char chn)
{
	if (chn == 0)
	{
		return 37;
	}
	else if (chn < 12)
	{
		return chn - 1;
	}
	else if (chn == 12)
	{
		return 38;
	}
	else if (chn < 39)
	{
		return chn - 2;
	}
	else
	{
		return 39;
	}
}
unsigned char Rf_GetBleFreChannel(unsigned char chn)
{
	WRITE_REG8 (0x40d, chn);

	if (chn < 11)
		chn += 2;
	else if (chn < 37)
		chn += 3;
	else if (chn == 37)
		chn = 1;
	else if (chn == 38)
		chn = 13;
	else
		chn = 40;

	chn = chn << 1;
	return chn;
}

static unsigned  char index=0;
unsigned char Get_Uart_Byte(void)
{

	unsigned char ret;

	ret = REG_ADDR8 (0x90+index);
	index++;
	if(index>=4)
		index = 0;

	return ret;

}
unsigned short uart_phyTestGet(unsigned short* cmd)
{
	static  unsigned int  tick_rx = 0;
	unsigned short l, h;

	if (!tick_rx && (REG_ADDR8(0x9c)&15) == 1)
	{
		tick_rx = get_sys_tick ();
	}
	else if ((REG_ADDR8(0x9c)&15) == 2)
	{
		h = Get_Uart_Byte()&0xff;
		l = Get_Uart_Byte()&0xff;

		*cmd = (l | (h<<8));

		tick_rx = 0;
		return 1;
	}
	else if (tick_rx && timeout_us (tick_rx, 5000))
	{
		tick_rx = 0;
		Get_Uart_Byte();
	}
	else if((REG_ADDR8(0x9c)&15)>2)
	{
		unsigned char i;

		unsigned char l = REG_ADDR8(0x9c)&0x0f;
		for(i=0; i<l; i++)
			Get_Uart_Byte();

	}
	return 0;
}

void uart_phyTestSend (unsigned short st)
{
	static unsigned char  index = 0;
	unsigned char  l;
	l = st>>8;

	REG_ADDR16(0x90+index) = (st<<8 | l);
	index += 2;

	index = index%4;
}

/*
 * 80 94 PRBS9
 * 80 95 0x0f
 * 80 96 0x55
 */
/*
 * 0x81 0xd3, power table index 9
 */
void phytest (void)
{
	static unsigned short cmd;
	static unsigned char chn;
	static unsigned short st = 0;
	static unsigned short pkts = 0;

	unsigned int tick_tx=0; //initial
	do
	{
		//uart_phyTestSend(22);
		if((st==1) || (st==2))
		{
	    	if(timeout_us(t0, 1000*300))
			{
	    		t0 = get_sys_tick();
			}
		}


		if (uart_phyTestGet (&cmd))
		{
			tick_tx = get_sys_tick ();
			chn = (cmd >> 8) & 0x3f;/////frequency
			unsigned char  len =  (cmd >> 2) & 0x3f;
			unsigned char  type = cmd & 3;
			unsigned char  ct = cmd >> 14;

			if (type == 0)
			{
				gen_prbs9 (bqbtest_pkt + 6, len);
			}
			else if (type == 1)
			{
				memset (bqbtest_pkt + 6, 0x0f, len);
			}
			else
			{
				memset (bqbtest_pkt + 6, 0x55, len);
			}

			bqbtest_pkt[4] = type;

			if (ct == CMD_RESET)		//reset
			{
				pkts = 0;
				rf_set_tx_rx_off();
				uart_phyTestSend (0);
			}
			else if (ct == CMD_RX)	//rx
			{
				pkts = 0;
				chn = Rf_GetBleFreChannel(phyTest_Channel(chn));
				rf_set_trx_state(RF_MODE_RX,chn);
				uart_phyTestSend (0);

			}
			else if (ct == CMD_TX)	//tx
			{
				pkts = 0;
				chn = Rf_GetBleFreChannel(phyTest_Channel(chn));
#if AUTO
				//rf_set_trx_state(RF_MODE_AUTO ,chn);
				rf_set_trx_state(RF_MODE_TX ,chn);
#else
				tx_start_flag = 1;
				//rf_set_power_level_index(RF_POWER_7dBm);  //////////////x/////
				rf_set_trx_state(RF_MODE_TX ,chn);
#endif
				uart_phyTestSend (0);
			}
			else  if(ct == CMD_END)				//end
			{
				rf_set_tx_rx_off();

				uart_phyTestSend (BIT(15) | (pkts & 0x7fff));
			}
			else {
				WRITE_REG8(0x8004,0x99);//ERR
			}
			st = ct;
		}


		if (st == CMD_TX)
		{
#if AUTO
			if ((rf_is_tx_finish()) || (pkts == 0))
#else
			if (timeout_us(tick_tx,625*1) || (tx_start_flag == 1))
#endif
			{
#if AUTO
				rf_clr_tx_finish();
				rf_start_stx(bqbtest_pkt, tick_tx);

				tick_tx += 625*tl_sys_tick_per_us;

#else
				if(tx_start_flag)
					tx_start_flag = 0;
				tick_tx =  get_sys_tick();
				rf_tx_pkt(bqbtest_pkt);
				while(!rf_is_tx_finish());
				rf_clr_tx_finish();
#endif
				pkts++;
			}
		}
		else if (st == CMD_RX)
		{
			if (READ_REG8(0xf20) & BIT(0))
			{
				BM_SET(REG_ADDR8(0xf20) , BIT(0));
				if	(RF_BLE_PACKET_LENGTH_OK(buffer_phytest) && RF_1M_500K_PACKET_CRC_OK(buffer_phytest) )
				{
					pkts++;
				}
			}
		}
	} while (st == 1 || st == 2);

}

unsigned char uart_phyTest_init(unsigned short uartCLKdiv, unsigned char bwpc){

	if(bwpc<3)
		return 0;
	WRITE_REG16(0x94,(uartCLKdiv|0x8000));//set uart clk divider and enable clock divider
	WRITE_REG8(0x96,bwpc);			//register mode
	WRITE_REG8(0x9a,(bwpc+1)*10);
	WRITE_REG8(0x9b,1);//For save

	WRITE_REG8(0x97,0x00);//No clts and rts
	return 1;
}

void  phy_test_init(void)
{
	gen_prbs9 (bqbtest_pkt + 6, 37);
	rf_set_rx_buff(buffer_phytest,256,0);
#if 1
	REG_ADDR8(0x401) = 0;				//disable PN
	WRITE_REG32 (0x408, 0x29417671);	//accesscode: 1001-0100 1000-0010 0110-1110 1000-1110   29 41 76 71
	//analog_write(0x8b, 0x43);//BQB test fix by kaixin ,confirm by wenfeng
#endif
	rf_set_power_level_index(RF_POWER_7dBm);
}





#endif
