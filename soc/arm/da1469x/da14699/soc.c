#include "DA1469x_helper_defines.h"
#include "soc.h"
#include <init.h>
#include "system_DA1469x.h"
#include "hw_gpio.h"
#include "hw_watchdog.h"
#include "sys_tcs.h"

#include "hw_uart.h"
#include "hal_da1469x_uart.h"

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

    uart_config_abstraction config = 
    {
        .baudrate = 115200,
	    .parity = 0,    //UART_CFG_PARITY_NONE
	    .stop_bits = 1, //UART_CFG_STOP_BITS_1
	    .data_bits = 3, //UART_CFG_DATA_BITS_8
	    .flow_ctrl = 0
    };

    hal_uart_da1469x_configure(&config, 0);
    hal_uart_da1469x_poll_out('H', 0);

    return 0;
}


SYS_INIT(da1469x_system_init_pre_kernel_wrapper, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
