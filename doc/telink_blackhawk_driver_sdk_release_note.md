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




