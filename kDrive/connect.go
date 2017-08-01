package kdrive

/*
#cgo linux,amd64 LDFLAGS: -L${SRCDIR}/lib/ubuntu_1404 -Wl,-rpath=\$ORIGIN -lkdriveExpress
#cgo windows,386 LDFLAGS: -L${SRCDIR}/lib/Win32 -lkdriveExpress
#cgo linux,arm LDFLAGS: -L${SRCDIR}/lib/raspbian -Wl,-rpath=\$ORIGIN -lkdriveExpress
#cgo LDFLAGS: -L${SRCDIR}/lib/raspbian -lkdriveExpress
#cgo CFLAGS: -Iinclude/

#include <stdlib.h>
#include "kdrive_express.h"
void ErrorCallback(error_t e, void* user_data);
void OnTelegramCallback(uint8_t* telegram, uint32_t telegram_len, void* user_data);
*/
import "C"
import (
	"fmt"
	"unsafe"
)

var ap C.int32_t // the Access Port descriptor

// ScanIPTunnels scans for all KNX IP Tunneling Interface devices.
func ScanIPTunnels() {
	ap = C.kdrive_ap_create()
	var buffer [4]C.struct_ip_tunn_dev_t
	var length C.uint32_t = 4
	C.kdrive_ap_enum_ip_tunn(ap, &buffer[0], &length)
	fmt.Println("found routers", length)
	fmt.Println(buffer[0])
	C.kdrive_ap_release(ap)
}

// ScanAndOpen searches for IP tunnels and opens the first.
func ScanAndOpen() {
	ap = C.kdrive_ap_create()
	var buffer [1]C.struct_ip_tunn_dev_t
	var length C.uint32_t = 1
	C.kdrive_ap_enum_ip_tunn(ap, &buffer[0], &length)
	if length == 0 {
		fmt.Println("Did not find an IP router")
		return
	}
	var d C.ip_tunn_dev_t = buffer[0]
	fmt.Println("Found IP Router", C.GoString(&d.ip_address[0]))

	res := C.kdrive_ap_open_ip(ap, &d.ip_address[0])
	if res != C.KDRIVE_ERROR_NONE {
		fmt.Printf("could not access %x\n", res)
		C.kdrive_ap_release(ap)
		return
	}

	fmt.Println("opened connection")

}

// OpenIP opens a connection to a KNX IP Tunneling Interface device.
func OpenIP(ipAddress string) {
	if IsOpen() {
		Close()
		return
	}

	ap = C.kdrive_ap_create()

	if ap == C.KDRIVE_INVALID_DESCRIPTOR {
		fmt.Println("Unable to create access port. This is a terminal failure")
	}

	ip := C.CString(ipAddress)
	// eth0 is 4 in my docker
	//var iface C.char = 4
	//res := C.kdrive_ap_open_ip_ex(ap, ip, &iface)

	res := C.kdrive_ap_open_ip(ap, ip)
	C.free(unsafe.Pointer(ip))
	if res != C.KDRIVE_ERROR_NONE {
		fmt.Printf("could not access %x\n", res)
		C.kdrive_ap_release(ap)
		return
	}

	fmt.Println("opened connection")

}

// OpenFT12 opens a connection to a KNX FT1.2 serial interface.
func OpenFT12(port string) {
	if IsOpen() {
		Close()
		return
	}

	ap = C.kdrive_ap_create()

	if ap == C.KDRIVE_INVALID_DESCRIPTOR {
		fmt.Println("Unable to create access port. This is a terminal failure")
	}

	serialDevice := C.CString(port)
	res := C.kdrive_ap_open_serial_ft12(ap, serialDevice)
	C.free(unsafe.Pointer(serialDevice))
	if res != C.KDRIVE_ERROR_NONE {
		fmt.Printf("could not access %x\n", res)
		C.kdrive_ap_release(ap)
		return
	}

	fmt.Println("opened connection")
}

// Close closes the connection
func Close() {
	C.kdrive_ap_close(ap)
	C.kdrive_ap_release(ap)
}

func IsOpen() bool {
	return C.kdrive_ap_is_open(ap) == 1
}

func GAWrite(addr uint16, v bool) {
	var value C.uint8_t = 0
	if v {
		value = 1
	}

	var address C.uint16_t = C.uint16_t(addr)
	C.kdrive_ap_group_write(ap, address, &value, 1)
}

// EnableLogger enables the log.
func EnableLogger() {
	C.kdrive_logger_set_level(C.KDRIVE_LOGGER_INFORMATION)
	C.kdrive_logger_console()
}

func ConnectPacketTrace() {
	/*
	  Connect the Packet Trace logging mechanism
	  to see the Rx and Tx packets
	*/
	C.kdrive_ap_packet_trace_connect(ap)
}
