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
	"errors"
	"fmt"
	"log"
	"unsafe"

	"github.com/yene/kBerry/knx"
)

const ERROR_MESSAGE_LEN = 128                     // kdriveExpress Error Messages
const ADDR_DPT_1 = (0x0901)                       /*!< Group Address of DTP-1 */
const ADDR_DPT_2 = (0x090A)                       /*!< Group Address of DTP-2 */
const ADDR_DPT_3 = ((ADDR_DPT_2) + 1)             /*!< Group Address of DTP-3 */
const ADDR_DPT_4 = ((ADDR_DPT_3) + 1)             /*!< Group Address of DTP-4 */
const ADDR_DPT_5 = ((ADDR_DPT_4) + 1)             /*!< Group Address of DTP-5 */
const ADDR_DPT_6 = ((ADDR_DPT_5) + 1)             /*!< Group Address of DTP-6 */
const ADDR_DPT_7 = ((ADDR_DPT_6) + 1)             /*!< Group Address of DTP-7 */
const ADDR_DPT_8 = ((ADDR_DPT_7) + 1)             /*!< Group Address of DTP-8 */
const ADDR_DPT_9 = ((ADDR_DPT_8) + 1)             /*!< Group Address of DTP-9 */
const ADDR_DPT_10_LOCAL = ((ADDR_DPT_9) + 1)      /*!< Group Address of DTP-10 Local Time */
const ADDR_DPT_10_UTC = ((ADDR_DPT_10_LOCAL) + 1) /*!< Group Address of DTP-10 UTC Time */
const ADDR_DPT_10 = ((ADDR_DPT_10_UTC) + 1)       /*!< Group Address of DTP-10 */
const ADDR_DPT_11_LOCAL = ((ADDR_DPT_10) + 1)     /*!< Group Address of DTP-11 Local Date */
const ADDR_DPT_11_UTC = ((ADDR_DPT_11_LOCAL) + 1) /*!< Group Address of DTP-11 UTC Date */
const ADDR_DPT_11 = ((ADDR_DPT_11_UTC) + 1)       /*!< Group Address of DTP-11 */
const ADDR_DPT_12 = ((ADDR_DPT_11) + 1)           /*!< Group Address of DTP-12 */
const ADDR_DPT_13 = ((ADDR_DPT_12) + 1)           /*!< Group Address of DTP-13 */
const ADDR_DPT_14 = ((ADDR_DPT_13) + 1)           /*!< Group Address of DTP-14 */
const ADDR_DPT_15 = ((ADDR_DPT_14) + 1)           /*!< Group Address of DTP-15 */
const ADDR_DPT_16 = ((ADDR_DPT_15) + 1)           /*!< Group Address of DTP-16 */

var ap C.int32_t // the Access Port descriptor

// OpenFT12 opens a connection to a KNX FT1.2 serial interface.
func OpenFT12(port string) error {
	if IsOpen() {
		Close()
		return nil
	}
	ap = C.kdrive_ap_create()
	if ap == KDRIVE_INVALID_DESCRIPTOR {
		return errors.New("unable to create access port, this is a terminal failure")
	}
	serialDevice := C.CString(port)
	res := C.kdrive_ap_open_serial_ft12(ap, serialDevice)
	C.free(unsafe.Pointer(serialDevice))
	if res != KDRIVE_ERROR_NONE {
		C.kdrive_ap_release(ap)
		return fmt.Errorf("could not access port: %s", getKdriveError(int(res)))
	}

	return nil
}

// Close closes the connection
func Close() {
	C.kdrive_ap_close(ap)
	res := C.kdrive_ap_release(ap)
	if res == 0 {
		log.Println("the descriptor wasn't found")
	}
}

// SetAddress sets the Individual Address of the Local Device (KNX Interface Device)
func SetAddress(ia knx.IndividualAddress) {
	res := C.kdrive_ap_set_ind_addr(ap, C.uint16_t(ia.Int()))
	if res != 0 {
		log.Fatalln("Could not set individual address. Error code", res)
	}
}

// GetAddress gets the Individual Address of the Local Device (KNX Interface Device)
func GetAddress() knx.IndividualAddress {
	var address C.uint16_t
	C.kdrive_ap_get_ind_addr(ap, &address)
	return knx.IAFromInt(int(address))
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
	C.kdrive_logger_set_level(KDRIVE_LOGGER_INFORMATION)
	C.kdrive_logger_console()
	C.kdrive_register_error_callback((*[0]byte)(C.ErrorCallback), nil)
}

/*
Called when a kdrive error exception is raised.
The handling in the error callback is typically
application specific. And here we simply show
the error message.
*/

//export ErrorCallback
func ErrorCallback(e C.error_t, user_data unsafe.Pointer) {
	fmt.Println("Error callback called:", getKdriveError(int(e)))
	var error_message [ERROR_MESSAGE_LEN]C.char
	C.kdrive_get_error_message(e, &error_message[0], ERROR_MESSAGE_LEN)
	C.kdrive_logger(KDRIVE_LOGGER_ERROR, &error_message[0])
}

func ConnectPacketTrace() {
	// Connect the Packet Trace logging mechanism to see the Rx and Tx packets
	C.kdrive_ap_packet_trace_connect(ap)
}

func RegisterCallback() {
	var key C.uint32_t // used by the telegram callback mechanism. uniquely identifies a callback

	C.kdrive_ap_register_telegram_callback(ap, (*[0]byte)(C.OnTelegramCallback), nil, &key)
}

//export OnTelegramCallback
func OnTelegramCallback(telegram *C.uint8_t, telegram_len C.uint32_t, user_data unsafe.Pointer) {
	//slice := (*[1 << 30]C.uint8_t)(unsafe.Pointer(telegram))[:telegram_len:telegram_len]
	//fmt.Println("callback called", slice)
	// callback called [41 0 188 224 255 100 10 3 1 0 128] = 1/2/3 1bit OFF, source 15.15.100

	var data [KDRIVE_MAX_GROUP_VALUE_LEN]C.uint8_t
	var dataLength C.uint32_t = KDRIVE_MAX_GROUP_VALUE_LEN
	var address C.uint16_t

	if (C.kdrive_ap_is_group_write(telegram, telegram_len) == C.bool_t(1)) &&
		(C.kdrive_ap_get_dest(telegram, telegram_len, &address) == KDRIVE_ERROR_NONE) &&
		(C.kdrive_ap_get_group_data(telegram, telegram_len, &data[0], &dataLength) == KDRIVE_ERROR_NONE) {

		ga := knx.GAFromInt(int(address))
		dpt, ok := addresses[ga]
		if ok {
			fmt.Println("I found", dpt, "for", ga)
		}

		switch address {
		case ADDR_DPT_1:
			var value C.bool_t
			C.kdrive_dpt_decode_dpt1(&data[0], dataLength, &value)
			fmt.Printf("DPT 1 - [1 Bit] %d\n", value)
		case ADDR_DPT_2:
			var control C.bool_t
			var value C.bool_t
			C.kdrive_dpt_decode_dpt2(&data[0], dataLength, &control, &value)
			fmt.Printf("DPT 2 - [1 Bit controlled] %d %d\n", control, value)
		case ADDR_DPT_3:
			var control C.bool_t
			var value C.uint8_t
			C.kdrive_dpt_decode_dpt3(&data[0], dataLength, &control, &value)
			fmt.Printf("DPT 3 - [3 Bit controlled] %d %d\n", control, value)
		case ADDR_DPT_4:
			var character C.uint8_t
			C.kdrive_dpt_decode_dpt4(&data[0], dataLength, &character)
			fmt.Printf("DPT 4 - [Character] %c\n", character)
		case ADDR_DPT_5:
			var value C.uint8_t
			C.kdrive_dpt_decode_dpt5(&data[0], dataLength, &value)
			fmt.Printf("DPT 5 - [8 bit unsigned] 0x%02x\n", value)
		case ADDR_DPT_6:
			var value C.int8_t
			C.kdrive_dpt_decode_dpt6(&data[0], dataLength, &value)
			fmt.Printf("DPT 6 - [8 bit signed] %d\n", value)
		case ADDR_DPT_7:
			var value C.uint16_t
			C.kdrive_dpt_decode_dpt7(&data[0], dataLength, &value)
			fmt.Printf("DPT 7 - [2 byte unsigned] 0x%04x\n", value)
		case ADDR_DPT_8:
			var value C.int16_t
			C.kdrive_dpt_decode_dpt8(&data[0], dataLength, &value)
			fmt.Printf("DPT 8 - [2 byte signed] %d\n", value)
		case ADDR_DPT_9:
			var value C.float32_t
			C.kdrive_dpt_decode_dpt9(&data[0], dataLength, &value)
			fmt.Printf("DPT 9 - [2 byte float] %f\n", value)
		case ADDR_DPT_10_LOCAL, ADDR_DPT_10_UTC, ADDR_DPT_10:
			var day C.int32_t
			var hour C.int32_t
			var minute C.int32_t
			var second C.int32_t
			C.kdrive_dpt_decode_dpt10(&data[0], dataLength, &day, &hour, &minute, &second)
			fmt.Printf("DPT 10 - [time] %d %d %d %d\n", day, hour, minute, second)
		case ADDR_DPT_11_LOCAL, ADDR_DPT_11_UTC, ADDR_DPT_11:
			var year C.int32_t
			var month C.int32_t
			var day C.int32_t
			C.kdrive_dpt_decode_dpt11(&data[0], dataLength, &year, &month, &day)
			fmt.Printf("DPT 11 - [date] %d %d %d\n", year, month, day)
		case ADDR_DPT_12:
			var value C.uint32_t
			C.kdrive_dpt_decode_dpt12(&data[0], dataLength, &value)
			fmt.Printf("DPT 12 - [4 byte unsigned] 0x%08x\n", value)
		case ADDR_DPT_13:
			var value C.int32_t
			C.kdrive_dpt_decode_dpt13(&data[0], dataLength, &value)
			fmt.Printf("DPT 13 - [4 byte signed] %d\n", value)
		case ADDR_DPT_14:
			var value C.float32_t
			C.kdrive_dpt_decode_dpt14(&data[0], dataLength, &value)
			fmt.Printf("DPT 14 - [4 byte float] %f\n", value)
		case ADDR_DPT_15:
			var accessCode C.int32_t
			var err C.bool_t
			var permission C.bool_t
			var direction C.bool_t
			var encrypted C.bool_t
			var index C.int32_t
			C.kdrive_dpt_decode_dpt15(&data[0], dataLength, &accessCode, &err, &permission, &direction, &encrypted, &index)
			fmt.Printf("DPT 15 - [entrance access] %d %d %d %d %d %d\n", accessCode, err, permission, direction, encrypted, index)
		case ADDR_DPT_16:
			// NOTE: kdrive_dpt_decode_dpt16 is not null terminated.
			var value [KDRIVE_DPT16_LENGTH]C.char
			C.kdrive_dpt_decode_dpt16(&data[0], dataLength, &value[0])
			fmt.Printf("DPT 16 - [character string] %s \n", value)
		default:
			fmt.Printf("A_GroupValue_Write: 0x%04x \n", address)
			fmt.Println("A_GroupValue_Write Data :", data, dataLength)
		}
	}
}

/*
  Sends Group Value Write telegrams
  for Datapoint Types 1 through 16
*/
func TestCallback() {

	// CGO: When passing an Array to C you have to pass the location of the first value.
	var buffer [KDRIVE_MAX_GROUP_VALUE_LEN]C.uint8_t
	var length C.uint32_t

	/* DPT-1 (1 bit) */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt1(&buffer[0], &length, 1)
	C.kdrive_ap_group_write(ap, ADDR_DPT_1, &buffer[0], length)
	fmt.Println("dpt1 length", length)

	/* DPT-2: 1 bit controlled */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt2(&buffer[0], &length, 1, 1)
	C.kdrive_ap_group_write(ap, ADDR_DPT_2, &buffer[0], length)
	fmt.Println("dpt2 length", length)

	/* DPT-3: 3 bit controlled */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt3(&buffer[0], &length, 1, 0x05)
	C.kdrive_ap_group_write(ap, ADDR_DPT_3, &buffer[0], length)
	fmt.Println("dpt3 length", length)

	/* DPT-4: Character */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt4(&buffer[0], &length, 'A')
	C.kdrive_ap_group_write(ap, ADDR_DPT_4, &buffer[0], length)

	/* DPT-5: 8 bit unsigned value */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt5(&buffer[0], &length, 0x23)
	C.kdrive_ap_group_write(ap, ADDR_DPT_5, &buffer[0], length)

	/* DPT-6: 8 bit signed value */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt6(&buffer[0], &length, -5)
	C.kdrive_ap_group_write(ap, ADDR_DPT_6, &buffer[0], length)

	/* DPT-7: 2 byte unsigned value */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt7(&buffer[0], &length, 0xAFFE)
	C.kdrive_ap_group_write(ap, ADDR_DPT_7, &buffer[0], length)

	/* DPT-8: 2 byte signed value */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt8(&buffer[0], &length, -1024)
	C.kdrive_ap_group_write(ap, ADDR_DPT_8, &buffer[0], length)

	/* DPT-9: 2 byte float value */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt9(&buffer[0], &length, 12.25)
	C.kdrive_ap_group_write(ap, ADDR_DPT_9, &buffer[0], length)

	/* DPT-10: Local Time */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt10_local(&buffer[0], &length)
	C.kdrive_ap_group_write(ap, ADDR_DPT_10_LOCAL, &buffer[0], length)

	/* DPT-10: UTC Time */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt10_utc(&buffer[0], &length)
	C.kdrive_ap_group_write(ap, ADDR_DPT_10_UTC, &buffer[0], length)

	/* DPT-10: Time */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt10(&buffer[0], &length, 1, 11, 11, 11)
	C.kdrive_ap_group_write(ap, ADDR_DPT_10, &buffer[0], length)

	/* DPT-11: Local Date */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt11_local(&buffer[0], &length)
	C.kdrive_ap_group_write(ap, ADDR_DPT_11_LOCAL, &buffer[0], length)

	/* DPT-11: UTC Date */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt11_utc(&buffer[0], &length)
	C.kdrive_ap_group_write(ap, ADDR_DPT_11_UTC, &buffer[0], length)

	/* DPT-11: Date */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt11(&buffer[0], &length, 2012, 03, 12)
	C.kdrive_ap_group_write(ap, ADDR_DPT_11, &buffer[0], length)

	/* DPT-12: 4 byte unsigned value */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt12(&buffer[0], &length, 0xDEADBEEF)
	C.kdrive_ap_group_write(ap, ADDR_DPT_12, &buffer[0], length)

	/* DPT-13: 4 byte signed value */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt13(&buffer[0], &length, -30000)
	C.kdrive_ap_group_write(ap, ADDR_DPT_13, &buffer[0], length)

	/* DPT-14: 4 byte float value */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt14(&buffer[0], &length, 2025.12345)
	C.kdrive_ap_group_write(ap, ADDR_DPT_14, &buffer[0], length)

	/* DPT-15: Entrance access */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	C.kdrive_dpt_encode_dpt15(&buffer[0], &length, 1234, 0, 1, 1, 0, 10)
	C.kdrive_ap_group_write(ap, ADDR_DPT_15, &buffer[0], length)

	/* DPT-16: Character string, 14 bytes */
	length = KDRIVE_MAX_GROUP_VALUE_LEN
	s := C.CString("Weinzierl Eng!")
	C.kdrive_dpt_encode_dpt16(&buffer[0], &length, s)
	C.kdrive_ap_group_write(ap, ADDR_DPT_16, &buffer[0], length)
	C.free(unsafe.Pointer(s))
}
