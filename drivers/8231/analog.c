/********************************************************************************************************
 * @file	analog.c
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
#include "analog.h"
#include "compiler.h"
#include "register.h"
#include "irq.h"

/**
 * @brief      This function serves to wait for analog register ready.
 * @param[in]  none.
 * @return     none.
 */
static inline void analog_wait(void){
	while(reg_ana_ctrl & FLD_ANA_BUSY){}
}
/**
 * @brief      This function serves to analog register read.
 * @param[in]  addr - address need to be read.
 * @return     the result of read.
 */
_attribute_ram_code_ unsigned char analog_read(unsigned char addr){
	unsigned char r = irq_disable();

	reg_ana_addr = addr;
	reg_ana_ctrl = (FLD_ANA_START);
	analog_wait();
	unsigned char data = reg_ana_data;
	reg_ana_ctrl = 0;		// finish
	irq_restore(r);
	return data;
}

/**
 * @brief      This function serves to analog register write.
 * @param[in]  addr - address need to be write.
 * @param[in]  v - the value need to be write.
 * @return     none.
 */
_attribute_ram_code_ void analog_write(unsigned char addr, unsigned char v){
	unsigned char r = irq_disable();

	reg_ana_addr = addr;
	reg_ana_data = v;
	reg_ana_ctrl = (FLD_ANA_START | FLD_ANA_RW);
	analog_wait();
	reg_ana_ctrl = 0;
	irq_restore(r);
}

/**
 * @brief      This function serves to analog register read.
 * @param[in]  addr - address need to be read.
 * @param[in]  v	- data buffer
 * @param[in]  len  - the length of buffer
 * @return     the result of read.
 */
void analog_read_multi(unsigned char addr, unsigned char *v, int len){
	unsigned char r = irq_disable();

	reg_ana_ctrl = 0;		// issue clock
	reg_ana_addr = addr;
	while(len--){
		reg_ana_ctrl = FLD_ANA_CYC | FLD_ANA_START;
		analog_wait();
		*v++ = reg_ana_data;
	}
	reg_ana_ctrl = 0; 		// finish

	irq_restore(r);
}

/**
 * @brief      This function serves to analog register read.
 * @param[in]  addr - address need to be written.
 * @param[in]  v	- data buffer
 * @param[in]  len  - the length of buffer
 * @return     none.
 */
void analog_write_multi(unsigned char addr, unsigned char *v, int len){
	unsigned char r = irq_disable();

	reg_ana_addr = addr;
	while(len--){
		reg_ana_data = *v++;
		reg_ana_ctrl = FLD_ANA_CYC | FLD_ANA_START | FLD_ANA_RW; 	// multi write
		analog_wait();
	}
	reg_ana_ctrl = 0; 		// finish
	irq_restore(r);
}


