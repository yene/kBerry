package kDrive

/*
#cgo LDFLAGS: -L. -lkdriveExpress
#include "include/kdrive_express.h"
void ErrorCallback(error_t e, void* user_data);
void OnTelegramCallback(uint8_t* telegram, uint32_t telegram_len, void* user_data);
*/
import "C"
import "fmt"

var ap C.int32_t // the Access Port descriptor

// Connect to the bus.
func Connect(port string) {
	ap = C.kdrive_ap_create()

	if ap == C.KDRIVE_INVALID_DESCRIPTOR {
		fmt.Println("Unable to create access port. This is a terminal failure")
	}

	serialDevice := C.CString(port)
	res := C.kdrive_ap_open_serial_ft12(ap, serialDevice)
	if res != C.KDRIVE_ERROR_NONE {
		fmt.Printf("could not access %x\n", res)
		C.kdrive_ap_release(ap)
	}

	fmt.Println("opened connection")
}

// Close closes the connection
func Close() {
	C.kdrive_ap_close(ap)
	C.kdrive_ap_release(ap)
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
