#ifndef ZEPHYR_DRIVERS_GPIO_GPIO_DA1469X_H_
#define ZEPHYR_DRIVERS_GPIO_GPIO_DA1469X_H_

#include <drivers/gpio.h>

typedef enum {
        HW_GPIO_PORT_0 = 0,     /**< GPIO Port 0 */
        HW_GPIO_PORT_1 = 1,     /**< GPIO Port 1 */
        HW_GPIO_PORT_MAX        /**< GPIO Port max */
} HW_GPIO_PORT;

struct gpio_da1469x_config {
	struct gpio_driver_config common;
    HW_GPIO_PORT port;
};

typedef enum {
        HW_GPIO_FUNC_GPIO = 0,                  /**< GPIO */
        HW_GPIO_FUNC_UART_RX = 1,               /**< GPIO as UART RX */
        HW_GPIO_FUNC_UART_TX = 2,               /**< GPIO as UART TX */
        HW_GPIO_FUNC_UART2_RX = 3,              /**< GPIO as UART2 RX */
        HW_GPIO_FUNC_UART2_TX = 4,              /**< GPIO as UART2 TX */
        HW_GPIO_FUNC_UART2_CTSN = 5,            /**< GPIO as UART2 CTSN */
        HW_GPIO_FUNC_UART2_RTSN = 6,            /**< GPIO as UART2 RTSN */
        HW_GPIO_FUNC_UART3_RX = 7,              /**< GPIO as UART3 RX */
        HW_GPIO_FUNC_UART3_TX = 8,              /**< GPIO as UART3 TX */
        HW_GPIO_FUNC_UART3_CTSN = 9,            /**< GPIO as UART3 CTSN */
        HW_GPIO_FUNC_UART3_RTSN = 10,           /**< GPIO as UART3 RTSN */
        HW_GPIO_FUNC_ISO_CLK = 11,              /**< GPIO as ISO CLK */
        HW_GPIO_FUNC_ISO_DATA = 12,             /**< GPIO as ISO DATA */
        HW_GPIO_FUNC_SPI_DI = 13,               /**< GPIO as SPI DI */
        HW_GPIO_FUNC_SPI_DO = 14,               /**< GPIO as SPI DO */
        HW_GPIO_FUNC_SPI_CLK = 15,              /**< GPIO as SPI CLK */
        HW_GPIO_FUNC_SPI_EN = 16,               /**< GPIO as SPI EN */
        HW_GPIO_FUNC_SPI2_DI = 17,              /**< GPIO as SPI2 DI */
        HW_GPIO_FUNC_SPI2_DO = 18,              /**< GPIO as SPI2 DO */
        HW_GPIO_FUNC_SPI2_CLK = 19,             /**< GPIO as SPI2 CLK */
        HW_GPIO_FUNC_SPI2_EN = 20,              /**< GPIO as SPI2 EN */
        HW_GPIO_FUNC_I2C_SCL = 21,              /**< GPIO as I2C SCL */
        HW_GPIO_FUNC_I2C_SDA = 22,              /**< GPIO as I2C SDA */
        HW_GPIO_FUNC_I2C2_SCL = 23,             /**< GPIO as I2C2 SCL */
        HW_GPIO_FUNC_I2C2_SDA = 24,             /**< GPIO as I2C2 SDA */
        HW_GPIO_FUNC_USB_SOF = 25,              /**< GPIO as USB SOF */
        HW_GPIO_FUNC_ADC = 26,                  /**< GPIO as ADC (dedicated pin) */
        HW_GPIO_FUNC_USB = 27,                  /**< GPIO as USB */
        HW_GPIO_FUNC_PCM_DI = 28,               /**< GPIO as PCM DI */
        HW_GPIO_FUNC_PCM_DO = 29,               /**< GPIO as PCM DO */
        HW_GPIO_FUNC_PCM_FSC = 30,              /**< GPIO as PCM FSC */
        HW_GPIO_FUNC_PCM_CLK = 31,              /**< GPIO as PCM CLK */
        HW_GPIO_FUNC_PDM_DATA = 32,             /**< GPIO as PDM DATA */
        HW_GPIO_FUNC_PDM_CLK = 33,              /**< GPIO as PDM CLK */
        HW_GPIO_FUNC_COEX_EXT_ACT = 34,         /**< GPIO as COEX EXT ACT0 */
        HW_GPIO_FUNC_COEX_SMART_ACT = 35,       /**< GPIO as COEX SMART ACT */
        HW_GPIO_FUNC_COEX_SMART_PRI = 36,       /**< GPIO as COEX SMART PRI */
        HW_GPIO_FUNC_PORT0_DCF = 37,            /**< GPIO as PORT0 DCF */
        HW_GPIO_FUNC_PORT1_DCF = 38,            /**< GPIO as PORT1 DCF */
        HW_GPIO_FUNC_PORT2_DCF = 39,            /**< GPIO as PORT2 DCF */
        HW_GPIO_FUNC_PORT3_DCF = 40,            /**< GPIO as PORT3 DCF */
        HW_GPIO_FUNC_PORT4_DCF = 41,            /**< GPIO as PORT4 DCF */
        HW_GPIO_FUNC_CLOCK = 42,                /**< GPIO as CLOCK */
        HW_GPIO_FUNC_PG = 43,                   /**< GPIO as PG */
        HW_GPIO_FUNC_LCD = 44,                  /**< GPIO as LCD */
        HW_GPIO_FUNC_LCD_SPI_DC = 45,           /**< GPIO as LCD SPI DC */
        HW_GPIO_FUNC_LCD_SPI_DO = 46,           /**< GPIO as LCD SPI DO */
        HW_GPIO_FUNC_LCD_SPI_CLK = 47,          /**< GPIO as LCD SPI CLK */
        HW_GPIO_FUNC_LCD_SPI_EN = 48,           /**< GPIO as LCD SPI EN */
        HW_GPIO_FUNC_TIM_PWM = 49,              /**< GPIO as TIM PWM */
        HW_GPIO_FUNC_TIM2_PWM = 50,             /**< GPIO as TIM2 PWM */
        HW_GPIO_FUNC_TIM_1SHOT = 51,            /**< GPIO as TIM 1SHOT */
        HW_GPIO_FUNC_TIM2_1SHOT = 52,           /**< GPIO as TIM2 1SHOT */
        HW_GPIO_FUNC_TIM3_PWM = 53,             /**< GPIO as TIM3 PWM */
        HW_GPIO_FUNC_TIM4_PWM = 54,             /**< GPIO as TIM4 PWM */
        HW_GPIO_FUNC_AGC_EXT = 55,              /**< GPIO as AGC EXT */
        HW_GPIO_FUNC_CMAC_DIAG0 = 56,           /**< GPIO as CMAC DIAG0 */
        HW_GPIO_FUNC_CMAC_DIAG1 = 57,           /**< GPIO as CMAC DIAG1 */
        HW_GPIO_FUNC_CMAC_DIAG2 = 58,           /**< GPIO as CMAC DIAG2 */
        HW_GPIO_FUNC_CMAC_DIAGX = 59,           /**< GPIO as CMAC DIAGX */
        HW_GPIO_FUNC_LAST,
} HW_GPIO_FUNC;

typedef enum {
        HW_GPIO_MODE_INPUT = 0,                 /**< GPIO as an input */
        HW_GPIO_MODE_INPUT_PULLUP = 0x100,      /**< GPIO as an input with pull-up */
        HW_GPIO_MODE_INPUT_PULLDOWN = 0x200,    /**< GPIO as an input with pull-down */
        HW_GPIO_MODE_OUTPUT = 0x300,            /**< GPIO as an (implicitly push-pull) output */
        HW_GPIO_MODE_OUTPUT_PUSH_PULL = 0x300,  /**< GPIO as an (explicitly push-pull) output */
        HW_GPIO_MODE_OUTPUT_OPEN_DRAIN = 0x700, /**< GPIO as an open-drain output */
        HW_GPIO_MODE_INVALID = 0xFFF,           /**< GPIO configured as nothing */
} HW_GPIO_MODE;

struct gpio_da1469x_data {
	/* gpio_driver_data needs to be first */
	struct gpio_driver_data common;
	/* device's owner of this data */
	const struct device *dev;
};
#endif /* ZEPHYR_DRIVERS_GPIO_GPIO_DA1469X_H_ */