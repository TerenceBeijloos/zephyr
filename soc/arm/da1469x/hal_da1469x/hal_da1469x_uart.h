#ifndef __HAL_DA1469X_UART__
#define __HAL_DA1469X_UART__

// This file is used to convert the uart functions from zephyr to the da1469x. 
// Zephyr and the da1469x sdk use the same name for some data types, uart_config for example. Therefore, this file is needed to add an abstraction.
 

#include <stdint.h>

typedef struct 
{
	uint32_t baudrate;
	uint8_t parity;
	uint8_t stop_bits;
	uint8_t data_bits;
	uint8_t flow_ctrl;
} uart_config_abstraction;

typedef enum 
{
    UART_1 = 0,
    UART_2 = 1,
    UART_3 = 2
} uart_id;

int hal_uart_da1469x_configure(const uart_config_abstraction* config, uart_id id);

int hal_uart_da1469x_poll_out(unsigned char byte, uart_id id);

int hal_uart_da1469x_poll_in(unsigned char* byte, uart_id id);

#endif //__HAL_DA1469X_UART__