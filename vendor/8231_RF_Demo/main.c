
#include "drivers.h"
#include "app_config.h"
//#if (__PROJECT_5313_RF_DEMO__)
extern void user_init();
extern void main_loop (void);
/*
RF_MODE_BLE_2M,
RF_MODE_BLE_1M,
RF_MODE_BLE_1M_NO_PN,
RF_MODE_NORDIC_1M,
RF_MODE_NORDIC_2M,
RF_MODE_PRIVATE_250K,
RF_MODE_PRIVATE_500K,
RF_MODE_BLE_2M_NO_PN
*/
//#define  RF_MODE RF_BLE_1M_NO_PN

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
