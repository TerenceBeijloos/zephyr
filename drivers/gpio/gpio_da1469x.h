#ifndef ZEPHYR_DRIVERS_GPIO_GPIO_DA1469X_H_
#define ZEPHYR_DRIVERS_GPIO_GPIO_DA1469X_H_

#include <drivers/gpio.h>

struct gpio_da1469x_config {
	/* gpio_driver_config needs to be first */
	struct gpio_driver_config common;
    uint8_t port;
};

struct gpio_da1469x_data {
	/* gpio_driver_data needs to be first */
	struct gpio_driver_data common;
	/* device's owner of this data */
	const struct device *dev;
};
#endif /* ZEPHYR_DRIVERS_GPIO_GPIO_DA1469X_H_ */