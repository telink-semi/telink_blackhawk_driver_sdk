## V2.2.1

### Version

* SDK version : telink_blackhawk_driver_sdk v2.2.1.
* This version sdk support 8231.

### BREAKING CHANGES
* N/A

### Bug Fixes
* N/A

### Refactoring
* **rf**
  * (8231)Normalizes the naming of content related to private schemas.

### Features
* N/A

### Performance Improvements

* N/A

### Note

* N/A

<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">

### 版本

* SDK版本: telink_blackhawk_driver_sdk v2.2.1。
* 此版本SDK支持8231芯片。


### BREAKING CHANGES
* N/A

### Bug Fixes
* N/A

### Refactoring
* **rf**
  * (8231)规范化与私有模式相关内容的命名。

### Features
* N/A

### Performance Improvements

* N/A

### Note

* N/A

## V2.2.0

### Version

* SDK version : telink_blackhawk_driver_sdk v2.2.0.
* This version sdk support 8231.

### Bug Fixes

* **RF**
  * fix the following function interface：rf_ble_set_crc、rf_ble_set_crc_value、rf_set_ble_crc_adv, the previous function is wrong.
* EMI
    + Fixed the problem that the tp calibration value written in the otp in the emi program does not work.

### Features

* EMI
	+ In burst prbs9, 0x55, 0x0f mode, add a packet sending mode with a limited number of 1000 packets.* EMI.
*RF
	 + Add rf_turn_off_internal_cap, rf_update_internal_cap internal capacitance operation functions.
### Known issues

* N/A

### BREAKING CHANGES

* PM
	+ The deep retention sleep mode has been deleted, and the modified code has been tested as follows. The program burned to OTP and flash is normal.

* RF 
	+ In order to be compatible with the SMIC chip, the driver configuration compatible operation (including setting energy：rf_set_power_level_index, agc table compatible) has been carried out through the version id. In the future, if you use the SMIC factory chip for development, you need to update to this version or a later version of the driver for development, otherwise the RF function will be abnormal.

### Refactoring

* **UART**
    + add restrictions for DMA receive length in UART-DMA mode.
  
* BQB 
	+ Delete the gen_prbs9 in bqb.c and change it to call from the driver.
	
### Performance Improvements
* RF
   + Improve the performance of ble2m.
   
### Note
* RF 
   + This version is compatible with SMIC chips. RF-related rf_set_power_level_index and agc table are compatible with version id. If you use SMIC chips for development, you need to update to this version or a later version of the driver for development, otherwise the RF function will be abnormal. 
<hr style="border-bottom:2.5px solid rgb(146, 240, 161)">


### 版本

* SDK版本: telink_blackhawk_driver_sdk v2.2.0。
* 此版本SDK支持8231芯片。

### Bug Fixes

* **RF**
    * 修改以下函数接口：rf_ble_set_crc、rf_ble_set_crc_value、rf_set_ble_crc_adv，之前版本功能是错误的
* EMI 
	+ 修复了emi程序中写在otp内的tp校准值不起作用的问题。
	
### Features

* EMI
    + 在burst prbs9,0x55,0x0f模式下添加限定发送数量为1000包的发包模式. 
* RF
    + 添加rf_turn_off_internal_cap，rf_update_internal_cap内部电容操作函数. 

### Known issues

* N/A

### BREAKING CHANGES

* PM 
	+ 删除了deep retention睡眠模式，修改后的代码做了如下测试，程序烧录到OTP、flash两种情况均正常。
	
* RF
	+ 为兼容SMIC厂芯片通过version id进行了driver配置兼容操作（包括设置能量：rf_set_power_level_index，agc table 兼容）。后续如果使用SMIC厂的芯片进行开发需更新到该版本或以后版本驱动进行开发，否则RF功能会出现异常。

### Refactoring

* **UART**
	+ DEMO中增加DMA模式接收数据长度的说明。
	
* BQB 
	+ 删除bqb.c里面的gen_prbs9改为从driver中调用。
	
### Performance Improvements

* RF
    + 提高ble2m的性能.
	

### Note

* RF
	+ 该版本为兼容SMIC厂的芯片对RF相关的rf_set_power_level_index及agc table 通过version id 进行了兼容，后续如果使用SMIC厂的芯片进行开发需更新到该版本或以后版本驱动进行开发，否则RF功能会出现异常。
---

## V2.1.0
### Bug Fixes

* **pm:** 解决suspend唤后概率性出现的晶振不能起振或者起振后工作不正常的问题
* **pm:** fix suspend crash issue(xtal work abnormal after wakeup)
* **pwm:** 解决pwm_ir_dma_fifo模式错误的长度设置
* **pwm:** fix the problem of incorrect length setting in pwm_ir_dma_fifi mode

 
### Features

* **rf:** 新增内外部电容支持
* **rf:** add intenal and external cap support
  - 修改tx_power_setting
  - modify tx_power_setting
  - 修改zigee 2M设置解决丢包率高问题
  - modify zigbee 2M mode setting in order to solve the problem of high packet loss rate
  - 提高rx sensitivity以及增加pre-anble长度
  - improve rx sensitivity and pre-amble lenth
* **interrupt:** 使能中断前清除gpio中断源避免终端误触发
* **interrupt：** clear gpio interrupt source before enable to avoid a unexpected interrupt
* **uart:** 新增UART_TXPD2和UART_RX_PD3
* **uart:** add UART_TXPD2 and UART_RX_PD3
* **flash:** 修改flash_read_mid_uid with_check接口适应不同flash
* **flash:** modify flash_read_mid_uid_with_check function to supplement all flash
* **pm:** 增加32k校准函数
* **pm:** add 32k calibration function


### BREAKING CHANGES
* suspend唤醒后晶体概率性工作不正常，需要加手动kick等操作，需要各个SDK更新。
* the crystal may work abnormal after suspend wake up,need add manual kick api etc.Need SDK update.




