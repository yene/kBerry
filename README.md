# kBerry

> The SDK may only be used in conjuction with KNX Interface Devices from Weinzierl Engineering.

Please respect the license and use this only with Weinzierl products.


### Setup KNX BAOS Module 838 kBerry
<img align="right" src="kberry_838.jpg">

Open `sudo nano /boot/cmdline.txt` and remove `console=serial0,115200`.

On PI3: There is now a device tree file called pi3-miniuart-bt which makes the Raspberry Pi 3 disable the Bluetooth and map pl011 UART on pins 14 and 15 as before.
`sudo sh -c "echo dtoverlay=pi3-miniuart-bt >>/boot/config.txt"`

[Official kBerry Setup](https://github.com/weinzierl-engineering/baos/blob/master/docs/Raspbian.adoc#kberry)

### Links and Material
* [kdriveExpress SDK Documentation](http://www.weinzierl.de/doxygen/kdrive/kdriveExpress-16.1.0/c/index.html)
* [KNX BAOS Module 838 kBerry](http://www.weinzierl.de/index.php/en/all-knx/knx-module-en/knx-baos-module-838-en)
* [Download SDK](http://www.weinzierl.de/images/download/software_tools/WzSDK/kdrive/kdriveExpress-16.1.0-raspbian.tar.gz)
