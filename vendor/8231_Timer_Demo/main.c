#include "drivers.h"
#include "app_config.h"
#if (__PROJECT_5313_TIMER_DEMO__)

extern void user_init();
extern void main_loop (void);

int timer0_irq_cnt = 0;
int timer1_irq_cnt = 0;
int timer2_irq_cnt = 0;

unsigned char timer0_irq_flag = 0;
unsigned int timer0_tick = 0 ;

_attribute_ram_code_ void irq_handler(void)
{
	if(reg_tmr_sta & FLD_TMR_STA_TMR0)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR0; //clear irq status
		reg_tmr0_tick = 0;
		timer0_irq_cnt ++;
		timer0_irq_flag = !timer0_irq_flag;
	}

	if(reg_tmr_sta & FLD_TMR_STA_TMR1)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR1; //clear irq status
		reg_tmr1_tick = 0;
		timer1_irq_cnt ++;

	}

	if(reg_tmr_sta & FLD_TMR_STA_TMR2)
	{
		reg_tmr_sta = FLD_TMR_STA_TMR2; //clear irq status
		reg_tmr1_tick = 0;
		timer2_irq_cnt ++;
	}
}

int main (void)
{
	system_init(BSP_INTERNAL_CAP_ENABLE);

	clock_init(SYS_CLK);

	gpio_init();

	user_init();

	irq_enable();
	while (1)
	{
		main_loop();
	}
}




#endif



