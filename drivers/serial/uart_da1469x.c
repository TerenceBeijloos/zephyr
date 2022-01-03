#include <drivers/uart.h>
#include "hal_da1469x_uart.h"

#define DT_DRV_COMPAT	renesas_da1469x_uart

struct uart_da1469x_config
{
    struct uart_device_config uart_config;
	uart_id id;
};

struct uart_da1469x_data
{
    struct uart_config uart_current_config;
};

#define DEV_CFG(_dev) ((struct uart_da1469x_config *const)(_dev)->config)

#define DEV_DATA(_dev) ((struct uart_da1469x_data *const)(_dev)->data)


static int uart_da1469x_configure(const struct device *dev, struct uart_config *cfg)
{
	uart_config_abstraction config = {
		.baudrate 	= cfg->baudrate,
		.parity 	= cfg->parity,
		.stop_bits 	= cfg->stop_bits,
		.data_bits 	= cfg->data_bits,
		.flow_ctrl 	= cfg->flow_ctrl
	};

	hal_uart_da1469x_configure(&config, DEV_CFG(dev)->id);

    return 0;
}

static void uart_da1469x_poll_out(const struct device *dev,
					       unsigned char c)
{
    hal_uart_da1469x_poll_out(c, DEV_CFG(dev)->id);
}

static int uart_da1469x_init(const struct device *dev)
{
    ARG_UNUSED(dev);

	uart_da1469x_configure(dev, &(DEV_CFG(dev)->uart_config));


	return 0;
}

static const struct uart_driver_api uart_da1469x_driver = {
	.poll_in = NULL,
	.poll_out = &uart_da1469x_poll_out,
	.err_check = NULL,
};

#define DA1469X_UART_DEVICE_INIT(inst)                                      \
	static const struct uart_da1469x_config uart_da1469x_cfg_##inst = {     \
            .uart_config = (uint8_t *)DT_INST_REG_ADDR(index),              \
			.id = DT_INST_PROP(inst, uart_id)								\
	};                                                                      \
									                                        \
    static struct uart_da1469x_data uart_da1469x_data_##inst;	            \
									                                        \
	DEVICE_DT_INST_DEFINE(inst,					                            \
			    uart_da1469x_init,                                          \
			    NULL,					                                    \
			    &uart_da1469x_data_##inst,                                  \
			    &uart_da1469x_cfg_##inst,                                   \
			    PRE_KERNEL_1,                                               \
			    CONFIG_SERIAL_INIT_PRIORITY,	                            \
			    &uart_da1469x_driver);

DT_INST_FOREACH_STATUS_OKAY(DA1469X_GPIO_DEVICE_INIT);

