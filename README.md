# kBerry

> The SDK may only be used in conjuction with KNX Interface Devices from Weinzierl Engineering.

Please respect the license and use this only with 


### Setup KNX BAOS Module 838 kBerry
Open `sudo nano /boot/cmdline.txt` and remove `console=serial0,115200`.

On PI3: There is now a device tree file called pi3-miniuart-bt which makes the Raspberry Pi 3 disable the Bluetooth and map pl011 UART on pins 14 and 15 as before.
`sudo sh -c "echo dtoverlay=pi3-miniuart-bt >>/boot/config.txt"`

[Download SDK](http://www.weinzierl.de/images/download/software_tools/WzSDK/kdrive/kdriveExpress-16.1.0-raspbian.tar.gz)

### My notes on CGO
[cgo](https://github.com/golang/go/wiki/cgo)
* When passing an array to CGO, pass the pointer for the first value `&bufer[0]`
* How to terminate an array with CGO? `'\0'` = `C.CString("\x00")`
* How to call a C function with "const char * fmt" from Go?

### Material
* [kdriveExpress SDK Documentation](http://www.weinzierl.de/doxygen/kdrive/kdriveExpress-16.1.0/c/index.html)
* [KNX BAOS Module 838 kBerry](http://www.weinzierl.de/index.php/en/all-knx/knx-module-en/knx-baos-module-838-en)
* [kBerry setup](https://github.com/weinzierl-engineering/baos/blob/561ef2a1c3b92d577f16d059bc07a2fd56fe0b72/docs/Raspbian.adoc#kberry)

