#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif



#define RF_BLE_2M		     	1//ok
#define RF_BLE_1M			    2//ok
#define RF_BLE_1M_NO_PN			3//ok
#define RF_BLE_2M_NO_PN			4//ok
#define RF_PRIVATE_250K			5//ok
#define RF_PRIVATE_500K			6//ok
#define RF_PRIVATE_1M			7//ok
#define RF_PRIVATE_2M			8//ok
#define RF_BLE_250K				9//ok
#define RF_BLE_500K				10//ok



#define RF_MODE					RF_PRIVATE_1M

#define LED1     				GPIO_PB0



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
