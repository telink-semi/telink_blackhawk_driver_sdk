/********************************************************************************************************
 * @file	bsp.c
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
#include "clock.h"
#include "analog.h"
#include "timer.h"

#define XINYI_SPECIAL_PROCESS		0

/**
 * @brief      This function writes a byte data to analog register
 * @param[in]  addr - the address of the analog register needs to write
 * @param[in]  value  - the data will be written to the analog register
 * @param[in]  e - the end address of value
 * @param[in]  s - the start address of the value
 * @return     none
 */
void sub_wr_ana(unsigned int addr, unsigned char value, unsigned char e, unsigned char s)
{
	unsigned char v, mask, tmp1, target, tmp2;

	v = analog_read(addr);
	mask = BIT_MASK_LEN(e - s + 1);
	tmp1 = value & mask;

	tmp2 = v & (~BIT_RNG(s,e));

	target = (tmp1 << s) | tmp2;
	analog_write(addr, target);
}

/**
 * @brief      This function writes a byte data to a specified analog register
 * @param[in]  addr - the address of the analog register needs to write
 * @param[in]  value  - the data will be written to the analog register
 * @param[in]  e - the end address of value
 * @param[in]  s - the start address of the value
 * @return     none
 */
void sub_wr(unsigned int addr, unsigned char value, unsigned char e, unsigned char s)
{
	unsigned char v, mask, tmp1, target, tmp2;

	v = READ_REG8(addr);
	mask = BIT_MASK_LEN(e - s + 1);
	tmp1 = value & mask;

	tmp2 = v & (~BIT_RNG(s,e));

	target = (tmp1 << s) | tmp2;
	WRITE_REG8(addr, target);
}
#if XINYI_SPECIAL_PROCESS
volatile unsigned char close_24M_RC_flag = 0;
/**
 * @brief   This function serves to open | close 24M RC.
 * @param   flag -- the value for deciding whether to open 24M RC.
 * 			flag: 1->close 24M RC, 0->open 24M RC
 * @return  none
 */
_attribute_ram_code_ void open_close_24M_RC(unsigned char flag)
{
	close_24M_RC_flag = flag;
}
#endif
/**
 * @brief   This function serves to initialize the related analog registers
 *          to default values after MCU is waked up from deep sleep mode.
 * @param   internal_cap -- the value to set internal cap.
 * @return  none
 */
/*Explication:WRITE_REG8(0x66,0x00);
 * When we burn the program into sram twice in a row ,the program can not run normally at the the second time.
  During the second burning, the system clock has been switched to crystal. After the second burning, the program is reinitialized.
  When Bit5 of ana_0x81 is set to "0", 16MHz clock to bbpll will power down.The crystal clock does not work.
  NOW set system clock to 24MHZ RC before oprating ana_0x81.
*/
volatile unsigned char internal_cap_flag;
_attribute_ram_code_ void system_init(Bsp_InternalCapDef internal_cap)    //must on ramcode
{
#if XINYI_SPECIAL_PROCESS
	internal_cap_flag = internal_cap;
	WRITE_REG8(0x60,0x00);   //open all the clk,disable all the rst
	WRITE_REG8(0x61,0x00);   //open all the clk,disable all the rst
	WRITE_REG8(0x62,0x00);   //open all the clk,disable all the rst
	WRITE_REG8(0x63,0xff);   //open all the clk,disable all the rst
	WRITE_REG8(0x64,0xff);   //open all the clk,disable all the rst
	WRITE_REG8(0x65,0xff);
	WRITE_REG8(0x66,0x00);   //RC clock, confirmed by peng.sun and wenfeng
	WRITE_REG8(0x5b5,0x0c);  //Enable gpio(core) irq and wakeup for keyboard
	if(close_24M_RC_flag)
	{
		analog_write(0x80, 0x21); //disable internal cap
		analog_write(0x81, 0xc0); //disable internal cap
	}
	analog_write(0x03, 0x43);	//Increase reternant current
	analog_write(0x06, 0x00);	//turn on baseband
	analog_write(0x20, 0x00);	//wakeup reset time: (0xff - 0xc1)*32 = 2000 us
	if(close_24M_RC_flag)
	{
		analog_write(0x2d, 0);//close 24M xtl kick
	}
	else
	{
		analog_write(0x2d, 0x68);	//quick settle: 200 us
		if(internal_cap){
			analog_write(0x81, 0xe8); // increase xtal current
		}
		else{
			analog_write(0x81, 0xe0); //increase xtal current (confirmed by peng.sun and wenfeng)
		}
		/* Open 24M XTAL. */
		analog_write(0x05, 0xca);
		for(volatile unsigned int i =0; i<10*24; i++);
		analog_write(0x05, 0xc2);
		for(volatile unsigned int i =0; i<210*24; i++);
	}
	reg_dma_chn_en = 0;
	reg_dma_chn_irq_msk = 0;
	if(!close_24M_RC_flag)
	{
		if(internal_cap){
			 /* Set 24M XTAL buffer and doubler. */
			 analog_write(0x80, 0x61); //Enable 24M clk buf
			 analog_write(0x81, 0xd4); //Enable 24M clk buf -> 0x4f
		}else{
			 analog_write(0x80, 0x21); //disable internal cap
			 analog_write(0x81, 0xc0); //disable internal cap
		}
	}
	analog_write(0x82, 0x5f); //Enable 48M doubler
	for(volatile int i =0;i<24*50;i++);


	/* 24M RC calibrate. */
	rc_24m_cal();
	rc_32k_cal();
	/* initiate the value of 32k count */
	WRITE_REG16(0x748, 8000); //set 32k 16cyle avoid err use in a very quick suspend/deepsleep
	/* System Timer enable. */
	reg_sys_timer_ctrl |= FLD_SYSTEM_TICK_START;

	/* Must */
	WRITE_REG8(0x74a,0x29);//Enable calibration and close system timer 0x29
	WRITE_REG8(0x74a,0x28);//End calibration,calibration value is to be written to register 0x749|0x748.0x28
	WRITE_REG8(0x74a,0xa8);//Enable system timer and disable calibration
	for(volatile int i =0;i<16*1000;i++);

#else
	internal_cap_flag = internal_cap;
	WRITE_REG8(0x60,0x00);   //open all the clk,disable all the rst
	WRITE_REG8(0x61,0x00);   //open all the clk,disable all the rst
	WRITE_REG8(0x62,0x00);   //open all the clk,disable all the rst
	WRITE_REG8(0x63,0xff);   //open all the clk,disable all the rst
	WRITE_REG8(0x64,0xff);   //open all the clk,disable all the rst
	WRITE_REG8(0x65,0xff);
	WRITE_REG8(0x66,0x00);   //RC clock, confirmed by peng.sun and wenfeng
	WRITE_REG8(0x5b5,0x0c);  //Enable gpio(core) irq and wakeup for keyboard
	analog_write(0x03, 0x43);	//Increase reternant current
	analog_write(0x06, 0x00);	//turn on baseband
	analog_write(0x20, 0x00);	//wakeup reset time: (0xff - 0xc1)*32 = 2000 us
	analog_write(0x2d, 0x68);	//quick settle: 200 us

	analog_write(0x81, 0xe8);

	if(internal_cap){
		analog_write(0x81, 0xe8); // increase xtal current
	}
	else{
		analog_write(0x81, 0xe0); //increase xtal current (confirmed by peng.sun and wenfeng)
	}
    /* Open 24M XTAL. */
    analog_write(0x05, 0xca);
    for(volatile unsigned int i =0; i<10*24; i++);
	analog_write(0x05, 0xc2);
	for(volatile unsigned int i =0; i<210*24; i++);
	reg_dma_chn_en = 0;
	reg_dma_chn_irq_msk = 0;
	if(internal_cap){
	     /* Set 24M XTAL buffer and doubler. */
	     analog_write(0x80, 0x61); //Enable 24M clk buf
	     analog_write(0x81, 0xd4); //Enable 24M clk buf -> 0x4f
	}else{
		 analog_write(0x80, 0x21); //disable internal cap
         analog_write(0x81, 0xc0); //disable internal cap
	}
	analog_write(0x82, 0x5f); //Enable 48M doubler
	for(volatile int i =0;i<24*50;i++);


	/* 24M RC calibrate. */
	rc_24m_cal();
	rc_32k_cal();
	/* initiate the value of 32k count */
	WRITE_REG16(0x748, 8000); //set 32k 16cyle avoid err use in a very quick suspend/deepsleep
	/* System Timer enable. */
	reg_sys_timer_ctrl |= FLD_SYSTEM_TICK_START;

	/* Must */
	WRITE_REG8(0x74a,0x29);//Enable calibration and close system timer 0x29
	WRITE_REG8(0x74a,0x28);//End calibration,calibration value is to be written to register 0x749|0x748.0x28
	WRITE_REG8(0x74a,0xa8);//Enable system timer and disable calibration
	for(volatile int i =0;i<16*1000;i++);
#endif
}




