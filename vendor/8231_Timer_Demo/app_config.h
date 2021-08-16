/********************************************************************************************************
 * @file	app_config.h
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
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif



#define TIMER_SYS_CLOCK_MODE 	1
#define TIMER_GPIO_TRIGGER_MODE 2
#define TIMER_GPIO_WIDTH_MODE 	3
#define TIMER_GPIO_TICK_MODE 	4
#define TIMER_WATCHDOG_MODE 	5  /* ONLY TIMER2 SUPPORT THIS MODE*/

#define TIMER_MODE				TIMER_SYS_CLOCK_MODE





/* System clock initialization -----------------------------------------------*/
#define CLOCK_SYS_CLOCK_HZ      16000000
#if(CLOCK_SYS_CLOCK_HZ==12000000)
	#define SYS_CLK  	SYS_CLK_12M_XTAL
#elif (CLOCK_SYS_CLOCK_HZ==16000000)
	#define SYS_CLK  	SYS_CLK_16M_XTAL
#elif (CLOCK_SYS_CLOCK_HZ==24000000)
	#define SYS_CLK  	SYS_CLK_24M_XTAL
#elif (CLOCK_SYS_CLOCK_HZ==32000000)
	#define SYS_CLK  	SYS_CLK_32M_XTAL
#elif (CLOCK_SYS_CLOCK_HZ==48000000)
	#define SYS_CLK  	SYS_CLK_48M_XTAL
#endif

enum{
	CLOCK_SYS_CLOCK_1S  = CLOCK_SYS_CLOCK_HZ,
	CLOCK_SYS_CLOCK_1MS = (CLOCK_SYS_CLOCK_1S / 1000),
	CLOCK_SYS_CLOCK_1US = (CLOCK_SYS_CLOCK_1S / 1000000),
};

/* WatchDog ------------------------------------------------------------------*/
#define MODULE_WATCHDOG_ENABLE	0
#define WATCHDOG_INIT_TIMEOUT	500  //Unit:ms


/* Debug Interface -----------------------------------------------------------*/
#define  DEBUG_GPIO_ENABLE					1

#if(DEBUG_GPIO_ENABLE)
	#define PB4_FUNC				AS_GPIO //debug gpio chn0 : PB4
	#define PB5_FUNC				AS_GPIO //debug gpio chn1 : PB5
	#define PB6_FUNC                AS_GPIO //debug gpio chn2 : PB6
	#define PB7_FUNC                AS_GPIO //debug gpio chn3 : PB7
	#define PB3_FUNC                AS_GPIO //debug gpio chn4 : PB3
	#define PB2_FUNC                AS_GPIO //debug gpio chn5 : PB2

	#define PB4_INPUT_ENABLE					0
	#define PB5_INPUT_ENABLE					0
	#define PB6_INPUT_ENABLE					0
	#define PB7_INPUT_ENABLE					0
	#define PB3_INPUT_ENABLE					0
	#define PB2_INPUT_ENABLE					0



	#define DBG_CHN0_LOW		( *(unsigned char *)0x80058b &= (~(1<<4)) )
	#define DBG_CHN0_HIGH		( *(unsigned char *)0x80058b |= (1<<4) )
	#define DBG_CHN0_TOGGLE		( *(unsigned char *)0x80058b ^= (1<<4) )

	#define DBG_CHN1_LOW		( *(unsigned char *)0x80058b &= (~(1<<5)) )
	#define DBG_CHN1_HIGH		( *(unsigned char *)0x80058b |= (1<<5) )
	#define DBG_CHN1_TOGGLE		( *(unsigned char *)0x80058b ^= (1<<5) )

	#define DBG_CHN2_LOW		( *(unsigned char *)0x80058b &= (~(1<<6)) )
	#define DBG_CHN2_HIGH		( *(unsigned char *)0x80058b |= (1<<6) )
	#define DBG_CHN2_TOGGLE		( *(unsigned char *)0x80058b ^= (1<<6) )

	#define DBG_CHN3_LOW		( *(unsigned char *)0x80058b &= (~(1<<7)) )
	#define DBG_CHN3_HIGH		( *(unsigned char *)0x80058b |= (1<<7) )
	#define DBG_CHN3_TOGGLE		( *(unsigned char *)0x80058b ^= (1<<7) )

	#define DBG_CHN4_LOW		( *(unsigned char *)0x80058b &= (~(1<<3)) )
	#define DBG_CHN4_HIGH		( *(unsigned char *)0x80058b |= (1<<3) )
	#define DBG_CHN4_TOGGLE		( *(unsigned char *)0x80058b ^= (1<<3) )

	#define DBG_CHN5_LOW		( *(unsigned char *)0x80058b &= (~(1<<2)) )
	#define DBG_CHN5_HIGH		( *(unsigned char *)0x80058b |= (1<<2) )
	#define DBG_CHN5_TOGGLE		( *(unsigned char *)0x80058b ^= (1<<2) )
#else
	#define DBG_CHN0_LOW
	#define DBG_CHN0_HIGH
	#define DBG_CHN0_TOGGLE
	#define DBG_CHN1_LOW
	#define DBG_CHN1_HIGH
	#define DBG_CHN1_TOGGLE
	#define DBG_CHN2_LOW
	#define DBG_CHN2_HIGH
	#define DBG_CHN2_TOGGLE
	#define DBG_CHN3_LOW
	#define DBG_CHN3_HIGH
	#define DBG_CHN3_TOGGLE
	#define DBG_CHN4_LOW
	#define DBG_CHN4_HIGH
	#define DBG_CHN4_TOGGLE
	#define DBG_CHN5_LOW
	#define DBG_CHN5_HIGH
	#define DBG_CHN5_TOGGLE
#endif  //end of DEBUG_GPIO_ENABLE











/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
