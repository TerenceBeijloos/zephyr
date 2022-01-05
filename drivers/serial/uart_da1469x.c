#include <drivers/uart.h>
#include "hal_da1469x_uart.h"

#define DT_DRV_COMPAT	renesas_da1469x_uart

struct uart_da1469x_config
{
    struct uart_device_config uart_dev_config;
	uart_id id;
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

	uart_da1469x_configure(dev, &(DEV_DATA(dev)->uart_config));


	return 0;
}

static const struct uart_driver_api uart_da1469x_driver = {
	.poll_in = NULL,
	.poll_out = &uart_da1469x_poll_out,
	.err_check = NULL,
};

#define DA1469X_UART_DEVICE_INIT(inst)                                      					\
	static const struct uart_da1469x_config uart_da1469x_cfg_##inst = {     					\
			.uart_dev_config = {							       								\
				.base =							       											\
		   		 		(uint8_t *)DT_INST_REG_ADDR(inst), 										\
						},																		\
			.id = DT_INST_PROP(inst, uart_id)-1													\
	};                                                                      					\
									                                        					\
    static struct uart_da1469x_data uart_da1469x_data_##inst = {	        					\
		.uart_config = {						       											\
			.baudrate = DT_INST_PROP(inst, current_speed),										\
			.parity = DT_ENUM_IDX_OR(DT_DRV_INST(index), parity, UART_CFG_PARITY_NONE),			\							
			.stop_bits = DT_INST_PROP(inst, stop_bits),											\
			.data_bits = DT_INST_PROP(inst, data_bits),											\
			.flow_ctrl = DT_INST_PROP(inst, hw_flow_control),									\
			}								       												\
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


// #define DA1469X_UART_DEVICE_INIT(inst)						       \
// static const struct uart_da1469x_config uart_da1469x_cfg_port_##inst = {	       \
// 	.uart_dev_config = {							       \
// 		.base =							       \
// 		    (uint8_t *)DT_REG_ADDR(DT_NODELABEL(uart##idx)), \
// 	},								       \
// 	},								       \
// 									       \
// 	.pins = {							       \
// 		.tx = DT_PROP(DT_NODELABEL(uart##idx), tx_pin),	       \
// 		.rx = DT_PROP(DT_NODELABEL(uart##idx), rx_pin),	       \
// 		IF_ENABLED(						       \
// 			DT_PROP(DT_NODELABEL(uart##idx), hw_flow_control),  \
// 			(.rts = DT_PROP(DT_NODELABEL(uart##idx), rts_pin),  \
// 			.cts = DT_PROP(DT_NODELABEL(uart##idx), cts_pin),   \
// 			))						       \
// 	},								       \
// 											   \
// 	.clock_subsys = (clock_control_subsys_t)DT_CLOCKS_CELL(DT_NODELABEL(uart##idx), offset), \
// 	.irq_source = DT_IRQN(DT_NODELABEL(uart##idx))			       \
// };									       \
// 									       \
// static struct uart_esp32_data uart_esp32_data_##idx = {			       \
// 	.uart_config = {						       \
// 		.baudrate = DT_PROP(DT_NODELABEL(uart##idx), current_speed),\
// 		.parity = UART_CFG_PARITY_NONE,				       \
// 		.stop_bits = UART_CFG_STOP_BITS_1,			       \
// 		.data_bits = UART_CFG_DATA_BITS_8,			       \
// 		.flow_ctrl = IS_ENABLED(				       \
// 			DT_PROP(DT_NODELABEL(uart##idx), hw_flow_control)) ?\
// 			UART_CFG_FLOW_CTRL_RTS_CTS : UART_CFG_FLOW_CTRL_NONE   \
// 	}								       \
// };									       \
// 									       \
// DEVICE_DT_DEFINE(DT_NODELABEL(uart##idx),				       \
// 		    &uart_esp32_init,					       \
// 		    NULL,				       \
// 		    &uart_esp32_data_##idx,				       \
// 		    &uart_esp32_cfg_port_##idx,				       \
// 		    PRE_KERNEL_1,					       \
// 		    CONFIG_SERIAL_INIT_PRIORITY,			       \
// 		    &uart_esp32_api);