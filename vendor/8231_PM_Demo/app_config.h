/********************************************************************************************************
 * @file     app_config.h
 *
 * @brief    This is the source file for TLSR8231
 *
 * @author	 Telink
 * @date     May 12, 2019
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

#pragma once

#include "drivers.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define LED1     				GPIO_PB0
#define LED2     				GPIO_PB1
#define LED3     				GPIO_PB2

#define SUSPEND_CORE_WAKEUP   	0           //9.6uA
#define SUSPEND_PAD_WAKEUP   	1			//9.6uA
#define SUSPEND_32K_WAKEUP   	2			//9.6uA
#define DEEP_PAD_WAKEUP		 	3			//4.9uA
#define DEEP_32K_WAKEUP      	4			//4.9uA

#define PM_MODE			     	SUSPEND_32K_WAKEUP
#define DELAY_3S			 	0

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


/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif





