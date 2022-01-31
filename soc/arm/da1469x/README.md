1. follow [Zephyr getting started guide](https://docs.zephyrproject.org/latest/getting_started/installation_win.html). The Zephyr-SDK installation is required to build MicroPython

2. Set zephyr toolchain variant to zephyr
```
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr 
```

3. Set zephyr sdk directory
```
export ZEPHYR_SDK_INSTALL_DIR=(path to zephyr sdk)
```

4. Install zephyr requirements, from <i>da1469x_zephyr</i>, make sure that python is added to your path
```
pip install -r zephyr/scripts/requirements.txt
```

5. From the directory <i>da1469x_zephyr</i>, export zephyr
```
west zephyr-export
```

6. [Download or clone MicroPython](https://github.com/micropython/micropython)

7. Copy <i>da1469x_zephyr/da1469x_dev_kit_pro.conf</i> to <i>(path to micropython)micropython/ports/zephyr/boards</i>

8. from the directory <i>da1469x_zephyr/zephyr</i>, build MicroPython
```
west build -b da1469x_dev_kit_pro (path to micropython)micropython/ports/zephyr -- -DCONF_FILE=boards/da1469x_dev_kit_pro.conf
```

9. Connect the DA1469x

10. Install ezFlashCLI
```
pip install ezFlashCLI
```

11. Erase the flash
```
ezFlashCLI erase_flash
```

12. from the directory <i>da1469x_zephyr/zephyr</i>, program the flash
```
ezFlashCLI image_flash build/zephyr/zephyr.bin
```

13. Open a serial terminal, PuTTY for example, with the following settings
```
COM port: lowest of the DA1469x
Baudrate: 115200
Data bits: 8
Stop bits: 1
Parity: None
Flow control: XON/XOFF
```

14. Press the reset button on the DA1469x to start MicroPython

15. Blinky example:
```
import time
from machine import Pin

LED = Pin(("GPIO_1", 1), Pin.OUT)
for i in range(10):
    LED.on()
    time.sleep(0.5)
    LED.off()
    time.sleep(0.5)
```
