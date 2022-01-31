#include "soc.h"
#include <init.h>

#include "hw_watchdog.h"
#include "hw_sys.h"
#include "hw_clk.h"


static int da1469x_system_init_pre_kernel_wrapper(const struct device *dev)
{  
    NMI_INIT();

    /*
    * Bandgap has already been set by the bootloader.
    * Use fast clocks from now on.
    */
    hw_clk_set_hclk_div(0);
    hw_clk_set_pclk_div(0);

    //Freeze the watchdog because else the watchdog will kick in when using delay functions
    hw_watchdog_freeze();

    //Enable the sys_pd_com pre kernel so the uart can be used the provide starup information
    hw_sys_pd_com_enable();

    return 0;
}


SYS_INIT(da1469x_system_init_pre_kernel_wrapper, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
