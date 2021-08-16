/********************************************************************************************************
 * @file	main.c
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
#include "drivers.h"
#include "app_config.h"
//#if (__PROJECT_5313_RF_DEMO__)
extern void user_init();
extern void main_loop (void);

_attribute_ram_code_ void irq_handler(void)
{


}

int main(void) {

	system_init(BSP_INTERNAL_CAP_ENABLE);

	clock_init(SYS_CLK);
	rf_mode_init();

	#if(RF_MODE==RF_BLE_2M)//1
	rf_set_ble_2M_mode();
	#elif(RF_MODE==RF_BLE_1M)//2
	rf_set_ble_1M_mode();
	#elif(RF_MODE==RF_BLE_1M_NO_PN)//3
	rf_set_ble_1M_NO_PN_mode();
	#elif(RF_MODE==RF_BLE_2M_NO_PN)//4
	rf_set_ble_2M_NO_PN_mode();
	#elif(RF_MODE==RF_PRIVATE_250K)//5
	rf_set_pri_250K_mode();
	#elif(RF_MODE==RF_PRIVATE_500K)//6
	rf_set_pri_500K_mode();
	#elif(RF_MODE==RF_PRIVATE_1M)//7
	rf_set_pri_1M_mode();
	#elif(RF_MODE==RF_PRIVATE_2M)//8
	rf_set_pri_2M_mode();
	#elif(RF_MODE==RF_BLE_250K)//9
	rf_set_ble_250K_mode();
	#elif(RF_MODE==RF_BLE_500K)
	rf_set_ble_500K_mode();

	#endif

	gpio_init();

	user_init();

	irq_enable();

	 while(1)
	 {
		main_loop ();
	 }
}
//#endif
