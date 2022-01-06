See [Application Development](https://docs.zephyrproject.org/latest/application/index.html) to learn how to create a project.

```c
#include zephyr.h
#include sysprintk.h

#include device.h
#include devicetree.h
#include driversuart.h

void main(void)
{
	const struct device dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
	char received_byte;

	if (dev == NULL)
	{
		return;
	}

	while (1)
	{
		if(uart_poll_in(dev, &received_byte) == 0)
		{
			printk(%c, received_byte);
		}
	}
}
```
