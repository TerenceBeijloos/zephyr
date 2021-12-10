#include "DA1469x_helper_defines.h"
#include "soc.h"
#include <init.h>
#include "system_DA1469x.h"
#include "hw_gpio.h"
#include "hw_watchdog.h"


static int da1469x_system_init_pre_kernel_wrapper(const struct device *dev)
{   
    extern void SystemInitPre(void);
    hw_watchdog_freeze();
    SystemInitPre();
    SystemInit();
    return 0;
}

static int da1469x_system_init_post_kernel_wrapper(const struct device *dev)
{   
    SystemInit();
    hw_gpio_set_pin_function(HW_GPIO_PORT_1, HW_GPIO_PIN_1, HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_GPIO);
    hw_gpio_pad_latch_enable(HW_GPIO_PORT_1, HW_GPIO_PIN_1);
    hw_gpio_set_active(HW_GPIO_PORT_1, HW_GPIO_PIN_1);

    return 0;
}

void
hal_system_init(void)
{
    CRG_TOP->RESET_STAT_REG = 0;    
}

SYS_INIT(da1469x_system_init_pre_kernel_wrapper, PRE_KERNEL_1, 0);
// SYS_INIT(da1469x_system_init_post_kernel_wrapper, PRE_KERNEL_2, 0);
