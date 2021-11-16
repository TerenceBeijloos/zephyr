#define DT_DRV_COMPAT renesas_da1469x_gpio

#include "custom_config_ram.h"
#include <stdint.h>
#include <drivers/gpio.h>
#include "gpio_da1469x.h"
#include "DA1469xAB.h"
#include "gpio_utils.h"

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

    PX_SET_DATA_REG(cfg->port) = 1 << pin;

	return 0;
}

//TODO: add support setting multiple pins at the same time
static int gpio_da1469x_port_clear_bits_raw(const struct device *dev,
						gpio_port_value_t mask)
{
	struct gpio_da1469x_config *const cfg = DEV_CFG(dev);

    PX_RESET_DATA_REG(cfg->port) = 1 << mask;
    
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

    //TODO: look at design patterns to prevent big if else structure
    if (flags & GPIO_OUTPUT)
    {
        PXX_MODE_REG(cfg->port, pin) = HW_GPIO_MODE_OUTPUT | HW_GPIO_FUNC_GPIO;

        if (cfg->port == HW_GPIO_PORT_0) 
        {
            CRG_TOP->P0_SET_PAD_LATCH_REG = 1 << pin;
        } else if (cfg->port == HW_GPIO_PORT_1) 
        {
            CRG_TOP->P1_SET_PAD_LATCH_REG = 1 << pin;
        }
    }

    if (flags & GPIO_OUTPUT_INIT_HIGH)
    {
        gpio_da1469x_port_set_bits_raw(dev, pin);
    }
    else if (flags & GPIO_OUTPUT_INIT_LOW)
    {
        gpio_da1469x_port_clear_bits_raw(dev,pin);
    }

	return 0;
}

/* GPIO driver registration */
static const struct gpio_driver_api gpio_da1469x_driver = {
	.pin_configure = gpio_da1469x_config,
	.port_get_raw = gpio_da1469x_port_get_raw,
	// .port_set_masked_raw = gpio_da1469x_port_set_masked_raw,
	.port_set_bits_raw = gpio_da1469x_port_set_bits_raw,
	.port_clear_bits_raw = gpio_da1469x_port_clear_bits_raw,
	.port_toggle_bits = gpio_da1469x_port_toggle_bits,
	// .pin_interrupt_configure = gpio_da1469x_pin_interrupt_configure,
	// .manage_callback = gpio_da1469x_manage_callback,
};

#define DA1469X_GPIO_DEVICE_INIT(inst)                                            \
	static const struct gpio_da1469x_config gpio_da1469x_cfg_##inst = {          \
		.common = {						       \
			.port_pin_mask =                                       \
			GPIO_PORT_PIN_MASK_FROM_NGPIOS(inst),\
		},                                                             \
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
