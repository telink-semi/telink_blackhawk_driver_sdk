/********************************************************************************************************
 * @file	otp.c
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
#include "bsp.h"
#include "register.h"
#include "timer.h"
#if 0
static void otp_init_clock(void){
	reg_dcdc_clk = 0x1f;    // open DCDC 6.75 clk to 8M
	delay_us(300);
	reg_dcdc_clk = 0x13;    // set DCDC 6.75 clk to 60M
	delay_us(300);
//	reg_otp_ctrl = FLD_OTP_OEN_PWDN | FLD_OTP_WEN_PWDN | FLD_OTP_PCEN_PWDN | FLD_OTP_CLK | FLD_OTP_OEN | FLD_OTP_FAST_CLK;
}
void otp_init_readwrite(void){
	/* open vpp 6.75V */
	rega_poweron_dcdc_6p75();
	delay_us(300);
	otp_init_clock();
}
void otp_init_read(void){
	otp_init_clock();
}
#endif
void otp_write(unsigned short addr, unsigned char value){
	write_reg8(0x800012, 0x7c);
	reg_otp_addr_para = addr;
	write_reg8(0x80001a, 0x02);
	reg_otp_byte_dat = value;
#if (SYS_CLOCK_RC && (DUT_8368_OTP||DUT_8368_OTP_NORMAL_READ))
	sleep_100us_offset();
#else
	delay_us(100);
#endif
	reg_otp_byte_dat = value;
}
#if 0
void otp_stop_write(void)
{
	rega_powerdn_dcdc_6p75();
}

u8 otp_read(u16 addr){
	volatile u8 value;
	addr = ((addr-4) & 0x3fff);
	write_reg8(0x800012, 0x7c);
	reg_otp_addr_para = addr;
#if(1)
	write_reg8(0x80001a, 0x06); //maginal read
#else
	write_reg8(0x80001a, 0x00);
#endif

	value = reg_otp_byte_dat;
	delay_us(1);
	value = read_reg8(0x800019);
	delay_us(1);
	return read_reg8(0x800019);
}

u8 otp_normal_read(u16 addr){
	volatile u8 value;
	addr = ((addr-4) & 0x3fff);
	write_reg8(0x800012, 0x7e);   //core12_<1> OTP  fast clk
	reg_otp_addr_para = addr;
#if(0)
	write_reg8(0x80001a, 0x06); //maginal read
#else
	write_reg8(0x80001a, 0x00); //normal read
#endif

	value = reg_otp_byte_dat;
	delay_us(1);
	value = read_reg8(0x800019);
	delay_us(1);
	return read_reg8(0x800019);
}
#else
//by congqing
unsigned char otp_read(unsigned short addr){
	volatile unsigned char value;
	addr = ((addr) & 0x3fff);
	write_reg8(0x800012, 0x7c);
	reg_otp_addr_para = addr;
#if(1)
	write_reg8(0x80001a, 0x06); //maginal read
#else
	write_reg8(0x80001a, 0x00);
#endif
	
	//value = reg_otp_byte_dat;
	//delay_us(1);
	value = read_reg8(0x800019);
	delay_us(1);
	return read_reg8(0x800019);
}

unsigned char otp_normal_read(unsigned short addr){
	volatile unsigned char value;
	addr = ((addr) & 0x3fff);
	write_reg8(0x800012, 0x7e);   //core12_<1> OTP  fast clk
	reg_otp_addr_para = addr;
#if(0)
	write_reg8(0x80001a, 0x06); //maginal read
#else
	write_reg8(0x80001a, 0x00); //normal read
#endif

	//value = reg_otp_byte_dat;
	//delay_us(1);
	value = read_reg8(0x800019);
	delay_us(1);
	return read_reg8(0x800019);
}
#endif
#if 0
void rega_poweron_dcdc_6p75(void)
{
	u8 v = 0x14;
	analog_write(rega_dcdc_ctrl, v);
	delay_us(1000);
	analog_write(rega_dcdc_ctrl, 0x54);
}

void rega_powerdn_dcdc_6p75(void)
{
	u8 v = 0x0c;
	analog_write(rega_dcdc_ctrl, v);
}
#endif
