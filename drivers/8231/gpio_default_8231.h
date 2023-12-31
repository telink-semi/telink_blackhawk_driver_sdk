/********************************************************************************************************
 * @file	gpio_default_8231.h
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

/* PA: INPUT ENABLE */
#ifndef PA0_INPUT_ENABLE
#define PA0_INPUT_ENABLE	0
#endif
#ifndef PA1_INPUT_ENABLE
#define PA1_INPUT_ENABLE	0
#endif
#ifndef PA2_INPUT_ENABLE
#define PA2_INPUT_ENABLE	0
#endif
#ifndef PA3_INPUT_ENABLE
#define PA3_INPUT_ENABLE	0
#endif
#ifndef PA4_INPUT_ENABLE
#define PA4_INPUT_ENABLE	0
#endif
#ifndef PA5_INPUT_ENABLE
#define PA5_INPUT_ENABLE	0
#endif
#ifndef PA6_INPUT_ENABLE
#define PA6_INPUT_ENABLE	0
#endif
#ifndef PA7_INPUT_ENABLE
#define PA7_INPUT_ENABLE	0
#endif

/* PA: OUTPUT ENABLE */
#ifndef PA0_OUTPUT_ENABLE
#define PA0_OUTPUT_ENABLE	0
#endif
#ifndef PA1_OUTPUT_ENABLE
#define PA1_OUTPUT_ENABLE	0
#endif
#ifndef PA2_OUTPUT_ENABLE
#define PA2_OUTPUT_ENABLE	0
#endif
#ifndef PA3_OUTPUT_ENABLE
#define PA3_OUTPUT_ENABLE	0
#endif
#ifndef PA4_OUTPUT_ENABLE
#define PA4_OUTPUT_ENABLE	0
#endif
#ifndef PA5_OUTPUT_ENABLE
#define PA5_OUTPUT_ENABLE	0
#endif
#ifndef PA6_OUTPUT_ENABLE
#define PA6_OUTPUT_ENABLE	0
#endif
#ifndef PA7_OUTPUT_ENABLE
#define PA7_OUTPUT_ENABLE	0
#endif
//PA Data strength
#ifndef PA0_DATA_STRENGTH
#define PA0_DATA_STRENGTH	1
#endif
#ifndef PA1_DATA_STRENGTH
#define PA1_DATA_STRENGTH	1
#endif
#ifndef PA2_DATA_STRENGTH
#define PA2_DATA_STRENGTH	1
#endif
#ifndef PA3_DATA_STRENGTH
#define PA3_DATA_STRENGTH	1
#endif
#ifndef PA4_DATA_STRENGTH
#define PA4_DATA_STRENGTH	1
#endif
#ifndef PA5_DATA_STRENGTH
#define PA5_DATA_STRENGTH	1
#endif
#ifndef PA6_DATA_STRENGTH
#define PA6_DATA_STRENGTH	1
#endif
#ifndef PA7_DATA_STRENGTH
#define PA7_DATA_STRENGTH	1
#endif
//PA Output Data
#ifndef PA0_DATA_OUT
#define PA0_DATA_OUT	0
#endif
#ifndef PA1_DATA_OUT
#define PA1_DATA_OUT	0
#endif
#ifndef PA2_DATA_OUT
#define PA2_DATA_OUT	0
#endif
#ifndef PA3_DATA_OUT
#define PA3_DATA_OUT	0
#endif
#ifndef PA4_DATA_OUT
#define PA4_DATA_OUT	0
#endif
#ifndef PA5_DATA_OUT
#define PA5_DATA_OUT	0
#endif
#ifndef PA6_DATA_OUT
#define PA6_DATA_OUT	0
#endif
#ifndef PA7_DATA_OUT
#define PA7_DATA_OUT	0
#endif
//PA Function select
#ifndef PA0_FUNC
#define PA0_FUNC	AS_GPIO
#endif
#ifndef PA1_FUNC
#define PA1_FUNC	AS_GPIO
#endif
#ifndef PA2_FUNC
#define PA2_FUNC	AS_GPIO
#endif
#ifndef PA3_FUNC
#define PA3_FUNC	AS_GPIO
#endif
#ifndef PA4_FUNC
#define PA4_FUNC	AS_GPIO
#endif
#ifndef PA5_FUNC
#define PA5_FUNC	AS_GPIO
#endif
#ifndef PA6_FUNC
#define PA6_FUNC	AS_GPIO
#endif
#ifndef PA7_FUNC
#define PA7_FUNC	AS_GPIO
#endif

//PA pull_up/pull_down resistor
/*******************************      for digital pull_up of PA<7:0>      ******************************/
#ifndef PULL_UP_WAKEUP_SRC_PA0
#define PULL_UP_WAKEUP_SRC_PA0	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PA1
#define PULL_UP_WAKEUP_SRC_PA1	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PA2
#define PULL_UP_WAKEUP_SRC_PA2	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PA3
#define PULL_UP_WAKEUP_SRC_PA3	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PA4
#define PULL_UP_WAKEUP_SRC_PA4	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PA5
#define PULL_UP_WAKEUP_SRC_PA5	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PA6
#define PULL_UP_WAKEUP_SRC_PA6	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PA7
#define PULL_UP_WAKEUP_SRC_PA7	0
#endif
/*******************************      for analog pull_down of PA<4:0>      ******************************/
#ifndef PULL_DOWN_WAKEUP_SRC_PA0
#define PULL_DOWN_WAKEUP_SRC_PA0	0
#endif
#ifndef PULL_DOWN_WAKEUP_SRC_PA1
#define PULL_DOWN_WAKEUP_SRC_PA1	0
#endif
#ifndef PULL_DOWN_WAKEUP_SRC_PA2
#define PULL_DOWN_WAKEUP_SRC_PA2	0
#endif
#ifndef PULL_DOWN_WAKEUP_SRC_PA3
#define PULL_DOWN_WAKEUP_SRC_PA3	0
#endif
#ifndef PULL_DOWN_WAKEUP_SRC_PA4
#define PULL_DOWN_WAKEUP_SRC_PA4	0
#endif
/*******************************      for analog pull_up/pull_down of PA<7:5>      ******************************/
#ifndef PULL_WAKEUP_SRC_PA5
#define PULL_WAKEUP_SRC_PA5	0
#endif
#ifndef PULL_WAKEUP_SRC_PA6
#define PULL_WAKEUP_SRC_PA6	0
#endif
#ifndef PULL_WAKEUP_SRC_PA7
#define PULL_WAKEUP_SRC_PA7	0
#endif

/* PB ------------------------------------------------------------------------*/
//PB Input
#ifndef PB0_INPUT_ENABLE
#define PB0_INPUT_ENABLE	0
#endif
#ifndef PB1_INPUT_ENABLE
#define PB1_INPUT_ENABLE	0
#endif
#ifndef PB2_INPUT_ENABLE
#define PB2_INPUT_ENABLE	0
#endif
#ifndef PB3_INPUT_ENABLE
#define PB3_INPUT_ENABLE	0
#endif
#ifndef PB4_INPUT_ENABLE
#define PB4_INPUT_ENABLE	0
#endif
#ifndef PB5_INPUT_ENABLE
#define PB5_INPUT_ENABLE	0
#endif
#ifndef PB6_INPUT_ENABLE
#define PB6_INPUT_ENABLE	0
#endif
#ifndef PB7_INPUT_ENABLE
#define PB7_INPUT_ENABLE	0
#endif
//PB Output
#ifndef PB0_OUTPUT_ENABLE
#define PB0_OUTPUT_ENABLE	0
#endif
#ifndef PB1_OUTPUT_ENABLE
#define PB1_OUTPUT_ENABLE	0
#endif
#ifndef PB2_OUTPUT_ENABLE
#define PB2_OUTPUT_ENABLE	0
#endif
#ifndef PB3_OUTPUT_ENABLE
#define PB3_OUTPUT_ENABLE	0
#endif
#ifndef PB4_OUTPUT_ENABLE
#define PB4_OUTPUT_ENABLE	0
#endif
#ifndef PB5_OUTPUT_ENABLE
#define PB5_OUTPUT_ENABLE	0
#endif
#ifndef PB6_OUTPUT_ENABLE
#define PB6_OUTPUT_ENABLE	0
#endif
#ifndef PB7_OUTPUT_ENABLE
#define PB7_OUTPUT_ENABLE	0
#endif
//PB data strength
#ifndef PB0_DATA_STRENGTH
#define PB0_DATA_STRENGTH	1
#endif
#ifndef PB1_DATA_STRENGTH
#define PB1_DATA_STRENGTH	1
#endif
#ifndef PB2_DATA_STRENGTH
#define PB2_DATA_STRENGTH	1
#endif
#ifndef PB3_DATA_STRENGTH
#define PB3_DATA_STRENGTH	1
#endif
#ifndef PB4_DATA_STRENGTH
#define PB4_DATA_STRENGTH	1
#endif
#ifndef PB5_DATA_STRENGTH
#define PB5_DATA_STRENGTH	1
#endif
#ifndef PB6_DATA_STRENGTH
#define PB6_DATA_STRENGTH	1
#endif
#ifndef PB7_DATA_STRENGTH
#define PB7_DATA_STRENGTH	1
#endif
//PB output data
#ifndef PB0_DATA_OUT
#define PB0_DATA_OUT	0
#endif
#ifndef PB1_DATA_OUT
#define PB1_DATA_OUT	0
#endif
#ifndef PB2_DATA_OUT
#define PB2_DATA_OUT	0
#endif
#ifndef PB3_DATA_OUT
#define PB3_DATA_OUT	0
#endif
#ifndef PB4_DATA_OUT
#define PB4_DATA_OUT	0
#endif
#ifndef PB5_DATA_OUT
#define PB5_DATA_OUT	0
#endif
#ifndef PB6_DATA_OUT
#define PB6_DATA_OUT	0
#endif
#ifndef PB7_DATA_OUT
#define PB7_DATA_OUT	0
#endif
//PB function select
#ifndef PB0_FUNC
#define PB0_FUNC	AS_GPIO
#endif
#ifndef PB1_FUNC
#define PB1_FUNC	AS_GPIO
#endif
#ifndef PB2_FUNC
#define PB2_FUNC	AS_GPIO
#endif
#ifndef PB3_FUNC
#define PB3_FUNC	AS_GPIO
#endif
#ifndef PB4_FUNC
#define PB4_FUNC	AS_GPIO
#endif
#ifndef PB5_FUNC
#define PB5_FUNC	AS_GPIO
#endif
#ifndef PB6_FUNC
#define PB6_FUNC	AS_GPIO
#endif
#ifndef PB7_FUNC
#define PB7_FUNC	AS_GPIO
#endif
//PB pull_up/pull_down resistor
/*******************************      for digital pull_up of PB<7:0>      ******************************/
#ifndef PULL_UP_WAKEUP_SRC_PB0
#define PULL_UP_WAKEUP_SRC_PB0	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PB1
#define PULL_UP_WAKEUP_SRC_PB1	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PB2
#define PULL_UP_WAKEUP_SRC_PB2	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PB3
#define PULL_UP_WAKEUP_SRC_PB3	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PB4
#define PULL_UP_WAKEUP_SRC_PB4	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PB5
#define PULL_UP_WAKEUP_SRC_PB5	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PB6
#define PULL_UP_WAKEUP_SRC_PB6	0
#endif
#ifndef PULL_UP_WAKEUP_SRC_PB7
#define PULL_UP_WAKEUP_SRC_PB7	0
#endif
/*******************************      for analog pull_up/pull_down of PB<7:0>      ******************************/
#ifndef PULL_WAKEUP_SRC_PB0
#define PULL_WAKEUP_SRC_PB0	0
#endif
#ifndef PULL_WAKEUP_SRC_PB1
#define PULL_WAKEUP_SRC_PB1	0
#endif
#ifndef PULL_WAKEUP_SRC_PB2
#define PULL_WAKEUP_SRC_PB2	0
#endif
#ifndef PULL_WAKEUP_SRC_PB3
#define PULL_WAKEUP_SRC_PB3	0
#endif
#ifndef PULL_WAKEUP_SRC_PB4
#define PULL_WAKEUP_SRC_PB4	0
#endif
#ifndef PULL_WAKEUP_SRC_PB5
#define PULL_WAKEUP_SRC_PB5	0
#endif
#ifndef PULL_WAKEUP_SRC_PB6
#define PULL_WAKEUP_SRC_PB6	0
#endif
#ifndef PULL_WAKEUP_SRC_PB7
#define PULL_WAKEUP_SRC_PB7	0
#endif

/* PC ------------------------------------------------------------------------*/
//PC Input Enable Macro
#ifndef PC0_INPUT_ENABLE
#define PC0_INPUT_ENABLE	0
#endif
#ifndef PC1_INPUT_ENABLE
#define PC1_INPUT_ENABLE	0
#endif
#ifndef PC2_INPUT_ENABLE
#define PC2_INPUT_ENABLE	0
#endif
#ifndef PC3_INPUT_ENABLE
#define PC3_INPUT_ENABLE	0
#endif
#ifndef PC4_INPUT_ENABLE
#define PC4_INPUT_ENABLE	0
#endif
#ifndef PC5_INPUT_ENABLE
#define PC5_INPUT_ENABLE	0
#endif
#ifndef PC6_INPUT_ENABLE
#define PC6_INPUT_ENABLE	0
#endif
#ifndef PC7_INPUT_ENABLE
#define PC7_INPUT_ENABLE	1 //SWS
#endif

//PC Output Enable Macro
#ifndef PC0_OUTPUT_ENABLE
#define PC0_OUTPUT_ENABLE	0
#endif
#ifndef PC1_OUTPUT_ENABLE
#define PC1_OUTPUT_ENABLE	0
#endif
#ifndef PC2_OUTPUT_ENABLE
#define PC2_OUTPUT_ENABLE	0
#endif
#ifndef PC3_OUTPUT_ENABLE
#define PC3_OUTPUT_ENABLE	0
#endif
#ifndef PC4_OUTPUT_ENABLE
#define PC4_OUTPUT_ENABLE	0
#endif
#ifndef PC5_OUTPUT_ENABLE
#define PC5_OUTPUT_ENABLE	0
#endif
#ifndef PC6_OUTPUT_ENABLE
#define PC6_OUTPUT_ENABLE	0
#endif
#ifndef PC7_OUTPUT_ENABLE
#define PC7_OUTPUT_ENABLE	0
#endif

//PC Data Strength Macro
#ifndef PC0_DATA_STRENGTH
#define PC0_DATA_STRENGTH	1
#endif
#ifndef PC1_DATA_STRENGTH
#define PC1_DATA_STRENGTH	1
#endif
#ifndef PC2_DATA_STRENGTH
#define PC2_DATA_STRENGTH	1
#endif
#ifndef PC3_DATA_STRENGTH
#define PC3_DATA_STRENGTH	1
#endif
#ifndef PC4_DATA_STRENGTH
#define PC4_DATA_STRENGTH	1
#endif
#ifndef PC5_DATA_STRENGTH
#define PC5_DATA_STRENGTH	1
#endif
#ifndef PC6_DATA_STRENGTH
#define PC6_DATA_STRENGTH	1
#endif
#ifndef PC7_DATA_STRENGTH
#define PC7_DATA_STRENGTH	1
#endif

//PC out data
#ifndef PC0_DATA_OUT
#define PC0_DATA_OUT	0
#endif
#ifndef PC1_DATA_OUT
#define PC1_DATA_OUT	0
#endif
#ifndef PC2_DATA_OUT
#define PC2_DATA_OUT	0
#endif
#ifndef PC3_DATA_OUT
#define PC3_DATA_OUT	0
#endif
#ifndef PC4_DATA_OUT
#define PC4_DATA_OUT	0
#endif
#ifndef PC5_DATA_OUT
#define PC5_DATA_OUT	0
#endif
#ifndef PC6_DATA_OUT
#define PC6_DATA_OUT	0
#endif
#ifndef PC7_DATA_OUT
#define PC7_DATA_OUT	0
#endif

//PC default Function Macro
#ifndef PC0_FUNC
#define PC0_FUNC	AS_GPIO
#endif
#ifndef PC1_FUNC
#define PC1_FUNC	AS_GPIO
#endif
#ifndef PC2_FUNC
#define PC2_FUNC	AS_GPIO
#endif
#ifndef PC3_FUNC
#define PC3_FUNC	AS_GPIO
#endif
#ifndef PC4_FUNC
#define PC4_FUNC	AS_GPIO
#endif
#ifndef PC5_FUNC
#define PC5_FUNC	AS_GPIO
#endif
#ifndef PC6_FUNC
#define PC6_FUNC	AS_GPIO
#endif
#ifndef PC7_FUNC
#define PC7_FUNC	AS_SWS  // SWS
#endif

//PC Pull-down Macro
#ifndef PULL_WAKEUP_SRC_PC0
#define PULL_WAKEUP_SRC_PC0	0
#endif
#ifndef PULL_WAKEUP_SRC_PC1
#define PULL_WAKEUP_SRC_PC1	0
#endif
#ifndef PULL_WAKEUP_SRC_PC2
#define PULL_WAKEUP_SRC_PC2	0
#endif
#ifndef PULL_WAKEUP_SRC_PC3
#define PULL_WAKEUP_SRC_PC3	0
#endif
#ifndef PULL_WAKEUP_SRC_PC4
#define PULL_WAKEUP_SRC_PC4	0
#endif
#ifndef PULL_WAKEUP_SRC_PC5
#define PULL_WAKEUP_SRC_PC5	0
#endif
#ifndef PULL_WAKEUP_SRC_PC6
#define PULL_WAKEUP_SRC_PC6	0
#endif
#ifndef PULL_WAKEUP_SRC_PC7
#define PULL_WAKEUP_SRC_PC7 0
#endif


/* PD ------------------------------------------------------------------------*/
//PD Input Enable Macro
#ifndef PD0_INPUT_ENABLE
#define PD0_INPUT_ENABLE	0
#endif
#ifndef PD1_INPUT_ENABLE
#define PD1_INPUT_ENABLE	0
#endif
#ifndef PD2_INPUT_ENABLE
#define PD2_INPUT_ENABLE	0
#endif
#ifndef PD3_INPUT_ENABLE
#define PD3_INPUT_ENABLE	0
#endif


//PD Output Enable Macro
#ifndef PD0_OUTPUT_ENABLE
#define PD0_OUTPUT_ENABLE	0
#endif
#ifndef PD1_OUTPUT_ENABLE
#define PD1_OUTPUT_ENABLE	0
#endif
#ifndef PD2_OUTPUT_ENABLE
#define PD2_OUTPUT_ENABLE	0
#endif
#ifndef PD3_OUTPUT_ENABLE
#define PD3_OUTPUT_ENABLE	0
#endif


//PD Data Strength Macro
#ifndef PD0_DATA_STRENGTH
#define PD0_DATA_STRENGTH	1
#endif
#ifndef PD1_DATA_STRENGTH
#define PD1_DATA_STRENGTH	1
#endif
#ifndef PD2_DATA_STRENGTH
#define PD2_DATA_STRENGTH	1
#endif
#ifndef PD3_DATA_STRENGTH
#define PD3_DATA_STRENGTH	1
#endif


//PD out data
#ifndef PD0_DATA_OUT
#define PD0_DATA_OUT	0
#endif
#ifndef PD1_DATA_OUT
#define PD1_DATA_OUT	0
#endif
#ifndef PD2_DATA_OUT
#define PD2_DATA_OUT	0
#endif
#ifndef PD3_DATA_OUT
#define PD3_DATA_OUT	0
#endif


//PD default Function Macro
#ifndef PD0_FUNC
#define PD0_FUNC	AS_GPIO
#endif
#ifndef PD1_FUNC
#define PD1_FUNC	AS_GPIO
#endif
#ifndef PD2_FUNC
#define PD2_FUNC	AS_GPIO
#endif
#ifndef PD3_FUNC
#define PD3_FUNC	AS_GPIO
#endif

//PD Pull-down Macro
#ifndef PULL_WAKEUP_SRC_PD0
#define PULL_WAKEUP_SRC_PD0	0
#endif
#ifndef PULL_WAKEUP_SRC_PD1
#define PULL_WAKEUP_SRC_PD1	0
#endif
#ifndef PULL_WAKEUP_SRC_PD2
#define PULL_WAKEUP_SRC_PD2	0
#endif
#ifndef PULL_WAKEUP_SRC_PD3
#define PULL_WAKEUP_SRC_PD3	0
#endif

/* PE ------------------------------------------------------------------------*/
//PE Input Enable Macro
#ifndef PE0_INPUT_ENABLE
#define PE0_INPUT_ENABLE	0
#endif
#ifndef PE1_INPUT_ENABLE
#define PE1_INPUT_ENABLE	0
#endif
#ifndef PE2_INPUT_ENABLE
#define PE2_INPUT_ENABLE	0
#endif
#ifndef PE3_INPUT_ENABLE
#define PE3_INPUT_ENABLE	0
#endif


//PE Output Enable Macro
#ifndef PE0_OUTPUT_ENABLE
#define PE0_OUTPUT_ENABLE	0
#endif
#ifndef PE1_OUTPUT_ENABLE
#define PE1_OUTPUT_ENABLE	0
#endif
#ifndef PE2_OUTPUT_ENABLE
#define PE2_OUTPUT_ENABLE	0
#endif
#ifndef PE3_OUTPUT_ENABLE
#define PE3_OUTPUT_ENABLE	0
#endif


//PE Data Strength Macro
#ifndef PE0_DATA_STRENGTH
#define PE0_DATA_STRENGTH	1
#endif
#ifndef PE1_DATA_STRENGTH
#define PE1_DATA_STRENGTH	1
#endif
#ifndef PE2_DATA_STRENGTH
#define PE2_DATA_STRENGTH	1
#endif
#ifndef PE3_DATA_STRENGTH
#define PE3_DATA_STRENGTH	1
#endif


//PE out data
#ifndef PE0_DATA_OUT
#define PE0_DATA_OUT	0
#endif
#ifndef PE1_DATA_OUT
#define PE1_DATA_OUT	0
#endif
#ifndef PE2_DATA_OUT
#define PE2_DATA_OUT	0
#endif
#ifndef PE3_DATA_OUT
#define PE3_DATA_OUT	0
#endif


//PE default Function Macro
#ifndef PE0_FUNC
#define PE0_FUNC	AS_GPIO
#endif
#ifndef PE1_FUNC
#define PE1_FUNC	AS_GPIO
#endif
#ifndef PE2_FUNC
#define PE2_FUNC	AS_GPIO
#endif
#ifndef PE3_FUNC
#define PE3_FUNC	AS_GPIO
#endif

//PE Pull-up/Pull-down Macro
#ifndef PULL_WAKEUP_SRC_PE0
#define PULL_WAKEUP_SRC_PE0	0
#endif
#ifndef PULL_WAKEUP_SRC_PE1
#define PULL_WAKEUP_SRC_PE1	0
#endif
#ifndef PULL_WAKEUP_SRC_PE2
#define PULL_WAKEUP_SRC_PE2	0
#endif
#ifndef PULL_WAKEUP_SRC_PE3
#define PULL_WAKEUP_SRC_PE3	0
#endif



