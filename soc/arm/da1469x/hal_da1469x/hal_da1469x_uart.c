#include "hal_da1469x_uart.h"
#include "hw_uart.h"

static void set_uart_baudrate(const uart_config_abstraction* source, uart_config* destination)
{
       switch (source->baudrate)
    {
    case 1000000:
        destination->baud_rate = HW_UART_BAUDRATE_1000000;
        break;
    case 500000:
        destination->baud_rate = HW_UART_BAUDRATE_500000;
        break;
    case 230400:
        destination->baud_rate = HW_UART_BAUDRATE_230400;
        break;
    case 115200:
        destination->baud_rate = HW_UART_BAUDRATE_115200;
        break;
    case 57600:
        destination->baud_rate = HW_UART_BAUDRATE_57600;
        break;
    case 38400:
        destination->baud_rate = HW_UART_BAUDRATE_38400;
        break;
    case 28800:
        destination->baud_rate = HW_UART_BAUDRATE_28800;
        break;
    case 19200:
        destination->baud_rate = HW_UART_BAUDRATE_19200;
        break;
    case 14400:
        destination->baud_rate = HW_UART_BAUDRATE_14400;
        break;
    case 9600:
        destination->baud_rate = HW_UART_BAUDRATE_9600;
        break;
    case 4800:
        destination->baud_rate = HW_UART_BAUDRATE_4800;
        break;
    default:
        destination->baud_rate = HW_UART_BAUDRATE_115200;
        break;
    }
}

static void set_uart_databits(const uart_config_abstraction* source, uart_config* destination)
{
    if (source->data_bits <= HW_UART_DATABITS_8)
    {
        destination->data = source->data_bits;
    }
    else
    {
        destination->data = HW_UART_DATABITS_8;
    }
}

static void set_uart_parity(const uart_config_abstraction* source, uart_config* destination)
{
    switch (source->parity)
    {
    case 0: //uart_config_parity::UART_CFG_PARITY_NONE
        destination->parity = HW_UART_PARITY_NONE;
        break;
    case 1: //uart_config_parity::UART_CFG_PARITY_ODD
        destination->parity = HW_UART_PARITY_ODD;
        break;
    case 2://uart_config_parity::UART_CFG_PARITY_EVEN
        destination->parity = HW_UART_PARITY_EVEN;
        break;
    default:
        destination->parity = HW_UART_PARITY_NONE;
        break;
    }
}

static void set_uart_stopbits(const uart_config_abstraction* source, uart_config* destination)
{
    switch (source->stop_bits)
    {
    case 1: //uart_config_stop_bits::UART_CFG_STOP_BITS_1
        destination->stop = HW_UART_STOPBITS_1;
        break;
    case 3: //uart_config_stop_bits::UART_CFG_STOP_BITS_2
        destination->stop = HW_UART_STOPBITS_2;
        break;
    default:
        destination->stop = HW_UART_STOPBITS_1;
        break;
    }
}

static void set_uart_flow_control(const uart_config_abstraction* source, uart_config* destination, uart_id id)
{
    destination->auto_flow_control = (id > UART_1) ? source->flow_ctrl > 0 : 0;
}

static void set_uart_dma(const uart_config_abstraction* source, uart_config* destination)
{
    //TODO
    destination->use_dma = 0;
    destination->tx_dma_channel = HW_DMA_CHANNEL_INVALID;
    destination->rx_dma_channel = HW_DMA_CHANNEL_INVALID;
}

static void set_uart_use_fifo(const uart_config_abstraction* source, uart_config* destination)
{
    //TODO
    destination->use_fifo = 0;
}

static void convert_uart_config(const uart_config_abstraction* source, uart_config* destination, uart_id id)
{
    set_uart_baudrate(source,destination);
    set_uart_databits(source,destination);
    set_uart_parity(source,destination);
    set_uart_stopbits(source,destination);
    set_uart_flow_control(source,destination, id);
    set_uart_dma(source,destination);
    set_uart_use_fifo(source,destination);
}   

static HW_UART_ID convert_uart_id(uart_id id)
{
    switch (id)
    {
    case UART_1:
        return HW_UART1;
        break;
    case UART_2:
        return HW_UART2;
        break;
    case UART_3:
        return HW_UART3;
        break;    
    default:
        return HW_UART1;
        break;
    }
}

int hal_uart_da1469x_configure(const uart_config_abstraction* config, uart_id id)
{
    uart_config sdk_da1469x_config;

    convert_uart_config(config, &sdk_da1469x_config, id);
    hw_uart_init(convert_uart_id(id), &sdk_da1469x_config);

    return 0;
}

int hal_uart_da1469x_poll_out(unsigned char byte, uart_id id)
{
    hw_uart_write(convert_uart_id(id), byte);
}
