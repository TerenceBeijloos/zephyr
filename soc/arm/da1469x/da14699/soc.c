#include "custom_config_ram.h"
#include "soc.h"
#include <init.h>
#include "system_DA1469x.h"

static int da1469x_system_init_wrapper(const struct device *dev)
{
    SystemInit();
    return 0;
}

SYS_INIT(da1469x_system_init_wrapper, PRE_KERNEL_1, 1);