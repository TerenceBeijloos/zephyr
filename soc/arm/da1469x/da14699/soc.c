#include "DA1469x_helper_defines.h"
#include "soc.h"
#include <init.h>
// #include "system_DA1469x.h"
#include "hw_gpio.h"
#include "hw_watchdog.h"



static int da1469x_system_init_pre_kernel_wrapper(const struct device *dev)
{   
    NMI_INIT();

    return 0;
}

static int da1469x_system_init_post_kernel_wrapper(const struct device *dev)
{   
    extern void SystemInitPre(void);
    hw_watchdog_freeze();
    SystemInitPre();
    SystemInit();

    return 0;
}

void
hal_system_init(void)
{
    CRG_TOP->RESET_STAT_REG = 0;    
}

SYS_INIT(da1469x_system_init_pre_kernel_wrapper, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
SYS_INIT(da1469x_system_init_post_kernel_wrapper, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
// SYS_INIT(da1469x_system_init_pre_kernel_wrapper, PRE_KERNEL_1, 0);
