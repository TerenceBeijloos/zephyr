#include "DA1469x_helper_defines.h"
#include "custom_config.h"
#include "soc.h"
#include <init.h>
#include "system_DA1469x.h"
#include "hw_gpio.h"

static int da1469x_system_init_wrapper(const struct device *dev)
{   
    // SystemInit();

    CoreDebug->DEMCR = 0;

    return 0;
}

SYS_INIT(da1469x_system_init_wrapper, PRE_KERNEL_1, 1);