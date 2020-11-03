/********************************************************************************************************
 * @file     clock.c
 *
 * @brief    This is the source file for TLSR8231
 *
 * @author	 Telink
 * @date     May 9, 2019
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
 *
 *******************************************************************************************************/

#include "register.h"
#include "clock.h"
#include "irq.h"
#include "analog.h"
#include "timer.h"


unsigned char sdk_clock_state = 0;


#if(BLE_SDK_EN)

/**
 * @brief       This function to select the system clock source.
 * @return      none
 */
void clockInit(){
	if(CLOCK_USE_RC_BROADCAST && !sdk_clock_state){
		reg_clk_sel = 0;
	}else if(CLOCK_SYS_TYPE == CLOCK_TYPE_PLL){
		if(CLOCK_RUN_CLOCK_HZ == 48000000){
			reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, 0, FLD_CLK_SEL_SRC, CLOCK_PLL_48M_NO_DIV);
		}else if(CLOCK_RUN_CLOCK_HZ == 32000000){
			reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, 1, FLD_CLK_SEL_SRC, CLOCK_PLL_32M_DIV);
		}else{
			reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, (CLOCK_PLL_CLOCK / CLOCK_RUN_CLOCK_HZ), FLD_CLK_SEL_SRC, CLOCK_SEL_HS_DIV);
		}
	}else{

		if(CLOCK_RUN_CLOCK_HZ <= 16000000){
			reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, (16000000 / CLOCK_RUN_CLOCK_HZ), FLD_CLK_SEL_SRC, CLOCK_RC_16M_DIV);
		}
	}
}
#else
/**
 * @brief       This function to select the system clock source.
 * @param[in]   SYS_CLK - the clock source of the system clock.
 * @return      none
 */
void clock_init(SYS_CLK_TYPEDEF SYS_CLK)
{
	WRITE_REG8(0x70,READ_REG8(0x70)&0xfe);
	WRITE_REG8(0x66,SYS_CLK);
}
#endif

/**
 * @Brief:  24M RC Calibration.(error: 0.01%)
 * @Param:  None.
 * @Return: None.
 */
void rc_24m_cal(void)
{
	unsigned char temp = 0;

	temp = analog_read(0x02);
	temp |= (1<<4);
	analog_write(0x02,temp);

	/* Enable 24M RC calibration. */
	temp = analog_read(0x83);
	temp |= (1<<0);
	temp &= ~(1<<1);
	analog_write(0x83,temp);

	/* Wait Calibration completely. */
	while(!(analog_read(0x84) & 0x01));

	unsigned char CalValue = 0;
	CalValue = analog_read(0x85);
	analog_write(0x30,CalValue);

	/* Disable 24M RC calibration. */
	temp = analog_read(0x83);
	temp &= ~(1<<0);
	analog_write(0x83,temp);

	temp = analog_read(0x02);
	temp &= ~(1<<4);
	analog_write(0x02,temp);
}

/**
 * @Brief: MCU internal 32K RC calibrate.Calibration accuracy is 1.6%
 * @Param: None.
 * @ReVal: None.
 */
void rc_32k_cal(void){
	unsigned char temp = 0;

	temp = analog_read(0x02);
	temp |= (1<<2);
	analog_write(0x02, temp);

	/* Enable 32K RC calibration. */
	temp = analog_read(0x83);
	temp |= (1<<0);//Enable
	temp |= (1<<1);//Select calibrate 32k RC
	analog_write(0x83,temp);

	/* Wait Calibration completely. */
	while(!(analog_read(0x84) & 0x01));

	unsigned char CalValue = 0;
	CalValue = analog_read(0x85);
	analog_write(0x2f,CalValue);

	/* Disable 32K RC calibration. */
	temp = analog_read(0x83);
	temp &= ~(1<<0);
	analog_write(0x83,temp);

	temp = analog_read(0x02);
	temp &= ~(1<<2);
	analog_write(0x02, temp);
}

