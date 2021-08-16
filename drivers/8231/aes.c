/********************************************************************************************************
 * @file	aes.c
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
#include "aes.h"
#include "register.h"
#include "irq.h"

/**
 * @brief       This function servers to initials a array as key.
 * @param[in]   key - the pointer to the 16-Byte Key
 * @return      0: success;
 *              not 0: failure
 */
unsigned char aes_initKey(unsigned char *key){
    unsigned short aesKeyStart = 0x550;
    for (unsigned char i=0; i<16; i++) {
     REG_ADDR8(aesKeyStart + i) = key[i];
    }
	return AES_SUCC;
}

/**
 * @brief       This function servers to perform aes_128 encryption for 16-Byte input data
 *              with specific 16-Byte key
 * @param[in]   key - the pointer to the 16-Byte Key
 * @param[in]   data - the pointer to the 16-Byte plain text
 * @param[out]  result - the pointer to the encryption result cipher text
 * @return      0: success;
 *              not 0: failure
 */
unsigned char hwAes_encrypt(unsigned char *key, unsigned char *data, unsigned char *result){
	unsigned char r = irq_disable();
    while ( reg_aes_ctrl & BIT(1) ) {
    	reg_aes_data = (data[0]) | (data[1]<<8) | (data[2]<<16) | (data[3]<<24);
        data += 4;
    }

    /* start encrypt */
    reg_aes_ctrl = 0x00;

    /* wait for aes ready */
    while ( !(reg_aes_ctrl & BIT(2)) );

    /* read out the result */
    for (unsigned char i=0; i<4; i++) {
		unsigned int temp = reg_aes_data;
		result[0] = temp; result[1] = temp >> 8; result[2] = temp >> 16;  result[3] = temp >> 24;
		result += 4;
    }
	irq_restore(r);
    return 0;
}

/**
 * @brief       This function servers to perform aes_128 encryption for 16-Byte input data
 *              with specific 16-Byte key
 * @param[in]   Key - the pointer to the 16-Byte Key
 * @param[in]   Data - the pointer to the 16-Byte plain text
 * @param[out]  Result - the pointer to the encryption result cipher text
 * @return      0: success;
 *              not 0: failure
 */
unsigned char aes_encrypt(unsigned char *key, unsigned char *data, unsigned char *result){
    return hwAes_encrypt(key, data, result);
}

/**
 * @brief       This function servers to perform aes_128 decryption for 16-Byte input data
 *              with specific 16-Byte key
 * @param[in]   Key - the pointer to the 16-Byte Key
 * @param[in]   Data - the pointer to the 16-Byte cipher text
 * @param[out]  Result - the pointer to the decryption result plain text
 * @return      0: success;
 *              not 0: failure
 */
int aes_decrypt(unsigned char *Key, unsigned char *Data, unsigned char *Result)
{
    unsigned int tmp = 0;
    unsigned char *p = Data;
    unsigned char i = 0;

    //trig decrypt operation
    reg_aes_ctrl |= FLD_AES_CTRL_CODEC_TRIG;

    //feed the data
    while (reg_aes_ctrl & FLD_AES_CTRL_DATA_FEED)
    {
        tmp = p[0] + (p[1]<<8) + (p[2]<<16) + (p[3]<<24);
        reg_aes_data = tmp;
        p += 4;
    }

    //wait for aes ready
    while ((reg_aes_ctrl & FLD_AES_CTRL_CODEC_FINISHED) == 0);

    //read out the result
    p = Result;
    for (i = 0; i < 4; i++) {
        tmp = reg_aes_data;
        *p++ = tmp & 0xff;
        *p++ = (tmp>>8) & 0xff;
        *p++ = (tmp>>16) & 0xff;
        *p++ = (tmp>>24) & 0xff;
    }
    return 0;
}










