#include <drivers/uart.h>
#include "hal_da1469x_uart.h"
#include <drivers/gpio.h>
#include "hw_gpio.h"

#define DT_DRV_COMPAT	renesas_da1469x_uart

struct uart_da1469x_config
{
    struct uart_device_config uart_dev_config;
	uart_id id;
	
	const struct device* rx_port;
	uint8_t rx_pin;

	const struct device* tx_port;
	uint8_t tx_pin;
};

struct uart_da1469x_data
{
    struct uart_config uart_config;
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

	if (DEV_CFG(dev)->rx_port == NULL|| DEV_CFG(dev)->tx_port == NULL) {
		return;
	}

	gpio_pin_configure(DEV_CFG(dev)->rx_port, DEV_CFG(dev)->rx_pin, GPIO_OUTPUT_ACTIVE | HW_GPIO_FUNC_UART_RX);
	gpio_pin_configure(DEV_CFG(dev)->tx_port, DEV_CFG(dev)->tx_pin, GPIO_OUTPUT_ACTIVE | HW_GPIO_FUNC_UART_TX);

	hal_uart_da1469x_configure(&config, DEV_CFG(dev)->id);

    return 0;
}

static void uart_da1469x_poll_out(const struct device *dev,
					       unsigned char c)
{
    hal_uart_da1469x_poll_out(c, DEV_CFG(dev)->id);
}

static int uart_da1469x_poll_in(const struct device *dev, unsigned char* byte)
{
	hal_uart_da1469x_poll_in(byte, DEV_CFG(dev)->id);
	return 0;
}

static int uart_da1469x_init(const struct device *dev)
{
    ARG_UNUSED(dev);

	uart_da1469x_configure(dev, &(DEV_DATA(dev)->uart_config));

	return 0;
}

static const struct uart_driver_api uart_da1469x_driver = {
	.poll_in = &uart_da1469x_poll_in,
	.poll_out = &uart_da1469x_poll_out,
	.err_check = NULL,
};


#define DA1469X_UART_DEVICE_INIT(inst)                                      					\
	static const struct uart_da1469x_config uart_da1469x_cfg_##inst = {     					\
			.uart_dev_config = {							       								\
				.base =							       											\
		   		 		(uint8_t *)DT_INST_REG_ADDR(inst), 										\
						},																		\
			.id = DT_INST_PROP(inst, uart_id)-1,												\
			.rx_port = DEVICE_DT_GET(DT_INST_PROP(inst,rx_port)),								\
			.rx_pin = DT_INST_PROP(inst, rx_pin),  												\
			.tx_port = DEVICE_DT_GET(DT_INST_PROP(inst,tx_port)),								\
			.tx_pin = DT_INST_PROP(inst, tx_pin)  												\
	};                                                                      					\
									                                        					\
    static struct uart_da1469x_data uart_da1469x_data_##inst = {	        					\
		.uart_config = {						       											\
			.baudrate = DT_INST_PROP(inst, current_speed),										\
			.parity = DT_ENUM_IDX_OR(DT_DRV_INST(index), parity, UART_CFG_PARITY_NONE),			\							
			.stop_bits = DT_INST_PROP(inst, stop_bits),											\
			.data_bits = DT_INST_PROP(inst, data_bits),											\
			.flow_ctrl = DT_INST_PROP(inst, hw_flow_control),									\
			},								       												\
	};									       													\
									                                        					\
	DEVICE_DT_INST_DEFINE(inst,					                            					\
			    uart_da1469x_init,                                          					\
			    NULL,					                                    					\
			    &uart_da1469x_data_##inst,                                  					\
			    &uart_da1469x_cfg_##inst,                                   					\
			    PRE_KERNEL_1,                                               					\
			    CONFIG_SERIAL_INIT_PRIORITY,	                            					\
			    &uart_da1469x_driver);

DT_INST_FOREACH_STATUS_OKAY(DA1469X_UART_DEVICE_INIT);
