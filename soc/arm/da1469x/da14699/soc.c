#include "DA1469x_helper_defines.h"
#include "soc.h"
#include <init.h>
#include "system_DA1469x.h"
#include "hw_gpio.h"
#include "hw_watchdog.h"

#include "sys_tcs.h"

static int da1469x_system_init_post_kernel_wrapper(const struct device *dev)
{   
    hw_watchdog_freeze();
    // SystemInit();

        /* In non baremetal apps PD_COMM will be opened by the  power manager */

    // hw_sys_pd_com_enable();
    // sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_COMM);
    // sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_SYS);
    // sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_TMR);

    // hw_gpio_set_pin_function(HW_GPIO_PORT_1, HW_GPIO_PIN_1, HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_GPIO);
    // hw_gpio_pad_latch_enable(HW_GPIO_PORT_1, HW_GPIO_PIN_1);
    // hw_gpio_set_active(HW_GPIO_PORT_1, HW_GPIO_PIN_1);

    return 0;
}

static int da1469x_system_init_pre_kernel_wrapper(const struct device *dev)
{   
    extern void SystemInitPre(void);

    NMI_INIT();
    SystemInitPre();

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
