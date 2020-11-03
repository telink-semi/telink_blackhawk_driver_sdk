//#include "tl_common.h"
#include "drivers.h"
#include "app_config.h"
#if (__PROJECT_5313_UART_DEMO__)
extern void user_init();
extern void main_loop (void);
#define REC_BUFF_LEN    16
#define TRANS_BUFF_LEN    16

extern volatile unsigned char uart_rx_flag;
extern volatile unsigned char uart_dmairq_tx_cnt;
extern volatile unsigned char uart_dmairq_rx_cnt;
extern volatile unsigned int  uart_ndmairq_cnt;
extern volatile unsigned char uart_ndmairq_index;
extern __attribute__((aligned(4))) unsigned char rec_buff[REC_BUFF_LEN];
extern __attribute__((aligned(4))) unsigned char trans_buff[TRANS_BUFF_LEN];


_attribute_ram_code_ __attribute__((optimize("-Os"))) void irq_handler(void)
{
#if (UART_MODE==UART_DMA)

	unsigned char uart_dma_irqsrc;
	//1. UART irq
	uart_dma_irqsrc = dma_get_irq_status();///in function,interrupt flag have already been cleared,so need not to clear DMA interrupt flag here

	if(uart_dma_irqsrc & FLD_DMA_CHN_UART_RX)
	{
		dma_clr_irq_status(FLD_DMA_CHN_UART_RX);

		uart_dmairq_rx_cnt++;

		//Received uart data in rec_buff, user can copy data here

	}
	if(uart_dma_irqsrc & FLD_DMA_CHN_UART_TX)
	{
		dma_clr_irq_status(FLD_DMA_CHN_UART_TX);

		uart_dmairq_tx_cnt++;
	}

	if(uart_is_parity_error())
	{
		uart_clear_parity_error();
	}
#elif(UART_MODE==UART_NDMA)

	static unsigned char uart_ndma_irqsrc;
	uart_ndma_irqsrc = uart_ndma_get_irq();  ///get the status of uart irq.
	if(uart_ndma_irqsrc)
	{
			rec_buff[uart_ndmairq_cnt++] = reg_uart_data_buf(uart_ndmairq_index);
			uart_ndmairq_index++;
			uart_ndmairq_index &= 0x03;// cycle the four registers 0x90 0x91 0x92 0x93, it must be done like this for the design of SOC.
			if(uart_ndmairq_cnt%16==0&&uart_ndmairq_cnt!=0)
			{
				uart_ndmairq_cnt = 0;
			}
	}
#endif
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
		main_loop ();
	}
	return 0;
}
#endif
