#define DT_DRV_COMPAT renesas_da1469x_gpio

// #include "custom_config.h"
#include <stdint.h>
#include <drivers/gpio.h>
#include "gpio_da1469x.h"
#include "DA1469xAB.h"
#include "gpio_utils.h"
#include "sys_tcs.h"
#include <devicetree.h>

/* Register adresses */
#define PX_DATA_REG_ADDR(_port)         ((volatile uint32_t *)(GPIO_BASE + offsetof(GPIO_Type, P0_DATA_REG)) + _port)
#define PX_DATA_REG(_port)              *PX_DATA_REG_ADDR(_port)
#define PX_SET_DATA_REG_ADDR(_port)     ((volatile uint32_t *)(GPIO_BASE + offsetof(GPIO_Type, P0_SET_DATA_REG)) + _port)
#define PX_SET_DATA_REG(_port)          *PX_SET_DATA_REG_ADDR(_port)
#define PX_RESET_DATA_REG_ADDR(_port)   ((volatile uint32_t *)(GPIO_BASE + offsetof(GPIO_Type, P0_RESET_DATA_REG)) + _port)
#define PX_RESET_DATA_REG(_port)        *PX_RESET_DATA_REG_ADDR(_port)
#define PXX_MODE_REG_ADDR(_port, _pin)  ((volatile uint32_t *)(GPIO_BASE + offsetof(GPIO_Type, P0_00_MODE_REG)) + (_port * 32)  + _pin)
#define PXX_MODE_REG(_port, _pin)       *PXX_MODE_REG_ADDR(_port, _pin)
#define PX_PADPWR_CTRL_REG_ADDR(_port)  ((volatile uint32_t *)(GPIO_BASE + offsetof(GPIO_Type, P0_PADPWR_CTRL_REG)) + _port)
#define PX_PADPWR_CTRL_REG(_port)       *PX_PADPWR_CTRL_REG_ADDR(_port)

#define DEV_CFG(_dev) ((struct gpio_da1469x_config *const)(_dev)->config)

static int gpio_da1469x_init(const struct device *dev)
{
	ARG_UNUSED(dev);

    //TODO
	// __ASSERT(DRV_CONFIG(dev)->wui_size == NPCX_GPIO_PORT_PIN_NUM,
	// 		"wui_maps array size must equal to its pin number");

	hw_sys_pd_com_enable();
    sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_COMM);
    sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_SYS);
    sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_TMR);

	return 0;
}

/* GPIO api functions */

static int gpio_da1469x_port_get_raw(const struct device *dev,
				  gpio_port_value_t *value)
{
	struct gpio_da1469x_config *const cfg = DEV_CFG(dev);

	/* Get raw bits of GPIO input registers */
	*value = PX_DATA_REG(cfg->port);

	return 0;
}

//TODO: add support setting multiple pins at the same time
static int gpio_da1469x_port_set_bits_raw(const struct device *dev,
					gpio_port_pins_t pin)
{
	struct gpio_da1469x_config *const cfg = DEV_CFG(dev);

	hw_gpio_set_active(cfg->port, pin);

	return 0;
}

//TODO: add support setting multiple pins at the same time
static int gpio_da1469x_port_clear_bits_raw(const struct device *dev,
						gpio_port_value_t mask)
{
	struct gpio_da1469x_config *const cfg = DEV_CFG(dev);

    hw_gpio_set_inactive(cfg->port, mask);

	return 0;
}

//TODO: add support setting multiple pins at the same time
static int gpio_da1469x_port_toggle_bits(const struct device *dev,
						uint32_t pins)
{
	struct gpio_da1469x_config *const cfg = DEV_CFG(dev);

	if (( (PX_DATA_REG(cfg->port) & (1 << pins)) != 0 ))
    {
        gpio_da1469x_port_set_bits_raw(dev,pins);
    }
    else
    {
        gpio_da1469x_port_clear_bits_raw(dev,pins);
    }
    
	return 0;
}

//TODO: support more functionalities
static int gpio_da1469x_config(const struct device *dev,
			     gpio_pin_t pin, gpio_flags_t flags)
{
    struct gpio_da1469x_config *const cfg = DEV_CFG(dev);

	//The pin 

	//TODO: map flags to corresponding mode
    hw_gpio_set_pin_function(cfg->port, pin+1, HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_GPIO);
    hw_gpio_pad_latch_enable(cfg->port, pin+1);

	return 0;
}


static int gpio_da1469x_pin_interrupt_configure(const struct device *dev,
					       gpio_pin_t gpio_num,
					       enum gpio_int_mode mode,
					       enum gpio_int_trig trig)
{
	//TODO
	return 0;
}

static int gpio_da1469x_manage_callback(const struct device *dev,
				       struct gpio_callback *callback, bool set)
{
	//TODO
	return 0;
}

static int gpio_da1469x_port_set_masked_raw(const struct device *dev,
					   uint32_t mask,
					   uint32_t value)
{
	//TODO
	return 0;
}


/* GPIO driver registration */
static const struct gpio_driver_api gpio_da1469x_driver = {
	.pin_configure = gpio_da1469x_config,
	.port_get_raw = gpio_da1469x_port_get_raw,
	.port_set_masked_raw = gpio_da1469x_port_set_masked_raw,
	.port_set_bits_raw = gpio_da1469x_port_set_bits_raw,
	.port_clear_bits_raw = gpio_da1469x_port_clear_bits_raw,
	.port_toggle_bits = gpio_da1469x_port_toggle_bits,
	.pin_interrupt_configure = gpio_da1469x_pin_interrupt_configure,
	.manage_callback = gpio_da1469x_manage_callback,
};

#define DA1469X_GPIO_DEVICE_INIT(inst)                                            \
	static const struct gpio_da1469x_config gpio_da1469x_cfg_##inst = {          \
		.common = {						       \
			.port_pin_mask =                                       \
			GPIO_PORT_PIN_MASK_FROM_NGPIOS(inst),\
		},                                                             \
		.port = DT_INST_PROP(inst, port) 							\
	};                                                                     \
									       \
	static struct gpio_da1469x_data gpio_da1469x_data_##inst;	               \
									       \
	DEVICE_DT_INST_DEFINE(inst,					       \
			    gpio_da1469x_init,                                    \
			    NULL,					       \
			    &gpio_da1469x_data_##inst,                            \
			    &gpio_da1469x_cfg_##inst,                             \
			    POST_KERNEL,                                       \
			    CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,	       \
			    &gpio_da1469x_driver);

DT_INST_FOREACH_STATUS_OKAY(DA1469X_GPIO_DEVICE_INIT);
