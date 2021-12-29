#include "DA1469x_helper_defines.h"
#include "soc.h"
#include <init.h>
#include "system_DA1469x.h"
#include "hw_gpio.h"
#include "hw_watchdog.h"
#include "sys_tcs.h"

#include "hw_uart.h"

static int da1469x_system_init_pre_kernel_wrapper(const struct device *dev)
{   
    extern void SystemInitPre(void);

    NMI_INIT();
    SystemInitPre();
    hw_watchdog_freeze();
    hw_sys_pd_com_enable();
    
    hw_gpio_set_pin_function(HW_GPIO_PORT_0, HW_GPIO_PIN_8, HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_UART_RX);
    hw_gpio_pad_latch_enable(HW_GPIO_PORT_0, HW_GPIO_PIN_8);

    hw_gpio_set_pin_function(HW_GPIO_PORT_0, HW_GPIO_PIN_9, HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_UART_TX);
    hw_gpio_pad_latch_enable(HW_GPIO_PORT_0, HW_GPIO_PIN_9);

    uart_config uart_init = {
            .baud_rate = HW_UART_BAUDRATE_115200,
            .data = HW_UART_DATABITS_8,
            .stop = HW_UART_STOPBITS_1,
            .parity = HW_UART_PARITY_NONE,
            .use_dma = 0,
            .use_fifo = 0 };

    hw_uart_init(HW_UART1, &uart_init);
    char buffer[] = {"\n\nHello World!"};
    hw_uart_write_buffer(HW_UART1,buffer,sizeof(buffer));

    return 0;
}


SYS_INIT(da1469x_system_init_pre_kernel_wrapper, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
