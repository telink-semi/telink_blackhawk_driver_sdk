/********************************************************************************************************
 * @file	string.h
 *
 * @brief	This is the header file for TLSR8231
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
#ifndef STRING_H_
#define STRING_H_
/**
 * @brief      This function servers copy a value to a destination place.
 * @param[in]  src -  Pointer variable of the destination place.
 * @param[in]  dest  -  Pointer variable of the source place.
 * @param[in]  len  -  The length of the value.
 * @return     none.
 */
void bbcopy(register char * src, register char * dest, int len);

/**
 * @brief      This function servers copy a value to a destination place.
 * @param[in]  src  -  Pointer variable of the destination place.
 * @param[in]  dest -  Pointer variable of the source place.
 * @param[in]  len  -  The length of the value.
 * @return     none.
 */
void bcopy(register char * src, register char * dest, int len);
/**
 * @brief      This function servers assignment a value to a destination place.
 * @param[in]  dest -  Pointer variable of the destination place.
 * @param[in]  val  -  Value need to assignment.
 * @param[in]  len  -  The length of the value.
 * @return     none.
 */
void *  memset(void * d, int c, unsigned int  n);
/**
 * @brief      This function servers copy a value to a destination place.
 * @param[in]  out -  Pointer variable of the destination place.
 * @param[in]  in  -  Pointer variable of the source place.
 * @param[in]  length  -  The length of the value.
 * @return     none.
 */
void *  memcpy(void * des_ptr, const void * src_ptr, unsigned int);
#endif /* STRING_H_ */
