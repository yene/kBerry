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
	"encoding/binary"
	"errors"
	"fmt"
	"log"
	"unsafe"

	"github.com/yene/kBerry/knx"
)

const ERROR_MESSAGE_LEN = 128 // kdriveExpress Error Messages

var ap C.int32_t // the Access Port descriptor

// OpenFT12 opens a connection to a KNX FT1.2 serial interface.
func OpenFT12(port string) error {
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

// Close closes the connection.
// If the access port is not open nothing happens
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

// IsOpen returns whether the access port is open
func IsOpen() bool {
	return C.kdrive_ap_is_open(ap) == 1
}

// EnableLogger enables the log.
func EnableLogger() {
	C.kdrive_logger_set_level(KDRIVE_LOGGER_INFORMATION)
	C.kdrive_logger_console()
	C.kdrive_register_error_callback((*[0]byte)(C.ErrorCallback), nil)
}

// ErrorCallback is called when a kdrive error exception is raised.
//export ErrorCallback
func ErrorCallback(e C.error_t, user_data unsafe.Pointer) {
	fmt.Println("Error callback called:", getKdriveError(int(e)))
	var error_message [ERROR_MESSAGE_LEN]C.char
	C.kdrive_get_error_message(e, &error_message[0], ERROR_MESSAGE_LEN)
	C.kdrive_logger(KDRIVE_LOGGER_ERROR, &error_message[0])
}

// ConnectPacketTrace	starts the Packet Trace, for a specific access port.
// When no packet trace callback was set (the default) then it write Rx and Tx packets to the logger (level: information), otherwise it calls the callback function.
// precondition: the access port is open
func ConnectPacketTrace() {
	// Connect the Packet Trace logging mechanism to see the Rx and Tx packets
	C.kdrive_ap_packet_trace_connect(ap)
}

// DisconnectPacketTrace stops the Packet Trace
func DisconnectPacketTrace() {
	C.kdrive_ap_packet_trace_disconnect(ap)
}

func RegisterCallback() {
	var key C.uint32_t // used by the telegram callback mechanism. uniquely identifies a callback
	/* Registers a callback function.
	This callback function will be called when a telegram is received
	by the Access Port. A notification thread is used internally so
	this callback will be in the context of the notification thread
	(and not the main thread). That is, care should be taken when calling out from the callback.
	This function generates a unique key to represent the callback. This key
	can be used to remove the callback at a later state. */
	C.kdrive_ap_register_telegram_callback(ap, (*[0]byte)(C.OnTelegramCallback), nil, &key)
}

func handmadeTelegramExtractor(b []byte) {
	// [46 0 188 224 | 17 200 | 9 1 | 1 0 | 129]
	messageCode := b[0:1]
	noidea := b[1:4]
	ainda := binary.BigEndian.Uint16(b[4:6])
	aga := binary.BigEndian.Uint16(b[6:8])
	alength := int(b[8])
	//noidea2 := b[9] // I guess the end is the TPCI and half APCI
	avalue := b[10]
	fmt.Println(messageCode, noidea, ainda, aga, alength, avalue)

	if alength == 1 { // the value is 4 bit and inside the APCI
		realvalue := uint(avalue) & 0x0F
		fmt.Println("real value", realvalue)
	} else { // the value is at the end
		realvalue := b[11:]
		fmt.Println("real value", realvalue)
	}

	fmt.Println("length", alength)
}

//export OnTelegramCallback
func OnTelegramCallback(telegram *C.uint8_t, telegram_len C.uint32_t, user_data unsafe.Pointer) {

	var data [KDRIVE_MAX_GROUP_VALUE_LEN]C.uint8_t
	var dataLength C.uint32_t = KDRIVE_MAX_GROUP_VALUE_LEN
	var address C.uint16_t

	if C.kdrive_ap_is_group_write(telegram, telegram_len) == 1 &&
		C.kdrive_ap_get_dest(telegram, telegram_len, &address) == KDRIVE_ERROR_NONE &&
		C.kdrive_ap_get_group_data(telegram, telegram_len, &data[0], &dataLength) == KDRIVE_ERROR_NONE {

		//b := C.GoBytes(unsafe.Pointer(telegram), C.int(telegram_len))
		ga := knx.GAFromInt(int(address))
		dpt, ok := addresses[ga]
		if !ok {
			log.Println("I did not find", ga)
			log.Println("Please add it to the GA.")
			return
		}

		switch dpt.Main {
		case 1:
			var value C.bool_t
			C.kdrive_dpt_decode_dpt1(&data[0], dataLength, &value)
			log.Printf("DPT 1 - [1 Bit] %d\n", value)
		case 2:
			var control, value C.bool_t
			C.kdrive_dpt_decode_dpt2(&data[0], dataLength, &control, &value)
			log.Printf("DPT 2 - [1 Bit controlled] %d %d\n", control, value)
		case 3:
			var control C.bool_t
			var value C.uint8_t
			C.kdrive_dpt_decode_dpt3(&data[0], dataLength, &control, &value)
			log.Printf("DPT 3 - [3 Bit controlled] %d %d\n", control, value)
		case 4:
			var character C.uint8_t
			C.kdrive_dpt_decode_dpt4(&data[0], dataLength, &character)
			log.Printf("DPT 4 - [Character] %c\n", character)
		case 5:
			var value C.uint8_t
			C.kdrive_dpt_decode_dpt5(&data[0], dataLength, &value)
			log.Printf("DPT 5 - [8 bit unsigned] 0x%02x\n", value)
		case 6:
			var value C.int8_t
			C.kdrive_dpt_decode_dpt6(&data[0], dataLength, &value)
			log.Printf("DPT 6 - [8 bit signed] %d\n", value)
		case 7:
			var value C.uint16_t
			C.kdrive_dpt_decode_dpt7(&data[0], dataLength, &value)
			log.Printf("DPT 7 - [2 byte unsigned] 0x%04x\n", value)
		case 8:
			var value C.int16_t
			C.kdrive_dpt_decode_dpt8(&data[0], dataLength, &value)
			log.Printf("DPT 8 - [2 byte signed] %d\n", value)
		case 9:
			var value C.float32_t
			C.kdrive_dpt_decode_dpt9(&data[0], dataLength, &value)
			log.Printf("DPT 9 - [2 byte float] %f\n", value)
		case 10:
			var day, hour, minute, second C.int32_t
			C.kdrive_dpt_decode_dpt10(&data[0], dataLength, &day, &hour, &minute, &second)
			log.Printf("DPT 10 - [time] %d %d %d %d\n", day, hour, minute, second)
		case 11:
			var year, month, day C.int32_t
			C.kdrive_dpt_decode_dpt11(&data[0], dataLength, &year, &month, &day)
			log.Printf("DPT 11 - [date] %d %d %d\n", year, month, day)
		case 12:
			var value C.uint32_t
			C.kdrive_dpt_decode_dpt12(&data[0], dataLength, &value)
			log.Printf("DPT 12 - [4 byte unsigned] 0x%08x\n", value)
		case 13:
			var value C.int32_t
			C.kdrive_dpt_decode_dpt13(&data[0], dataLength, &value)
			log.Printf("DPT 13 - [4 byte signed] %d\n", value)
		case 14:
			var value C.float32_t
			C.kdrive_dpt_decode_dpt14(&data[0], dataLength, &value)
			log.Printf("DPT 14 - [4 byte float] %f\n", value)
		case 15:
			var accessCode, index C.int32_t
			var err, permission, direction, encrypted C.bool_t
			C.kdrive_dpt_decode_dpt15(&data[0], dataLength, &accessCode, &err, &permission, &direction, &encrypted, &index)
			log.Printf("DPT 15 - [entrance access] %d %d %d %d %d %d\n", accessCode, err, permission, direction, encrypted, index)
		case 16:
			// NOTE: kdrive_dpt_decode_dpt16 is not null terminated.
			var value [KDRIVE_DPT16_LENGTH]C.char
			C.kdrive_dpt_decode_dpt16(&data[0], dataLength, &value[0])
			s := C.GoStringN(&value[0], C.int(dataLength))
			log.Printf("DPT 16 - [character string] %s \n", s)
		default:
			log.Printf("A_GroupValue_Write: 0x%04x \n", address)
			log.Println("A_GroupValue_Write Data :", data, dataLength)
		}
	}
}

// GAWrite sends a value to a group address.
func GAWrite(ga knx.GroupAddress, v ...interface{}) {
	var buffer [KDRIVE_MAX_GROUP_VALUE_LEN]C.uint8_t
	var length C.uint32_t = KDRIVE_MAX_GROUP_VALUE_LEN

	dpt, ok := addresses[ga]
	if !ok {
		log.Println("I did not find", ga)
		log.Println("Please add it to the group address.")
		return
	}

	switch dpt.Main {
	case 1: // DPT-1 (1 bit)
		C.kdrive_dpt_encode_dpt1(&buffer[0], &length, C.bool_t(v[0].(int)))
	case 2: // DPT-2: 1 bit controlled
		C.kdrive_dpt_encode_dpt2(&buffer[0], &length, C.bool_t(v[0].(int)), C.bool_t(v[1].(int)))
	case 3: // DPT-3: 3 bit controlled
		C.kdrive_dpt_encode_dpt3(&buffer[0], &length, C.bool_t(v[0].(int)), C.uint8_t(v[1].(int)))
	case 4: //D PT-4: Character
		char := v[0].(string)
		C.kdrive_dpt_encode_dpt4(&buffer[0], &length, C.uint8_t([]rune(char)[0]))
	case 5: // DPT-5: 8 bit unsigned value
		C.kdrive_dpt_encode_dpt5(&buffer[0], &length, C.uint8_t(v[0].(int)))
	case 6: // DPT-6: 8 bit signed value
		C.kdrive_dpt_encode_dpt6(&buffer[0], &length, C.int8_t(v[0].(int)))
	case 7: // DPT-7: 2 byte unsigned value
		C.kdrive_dpt_encode_dpt7(&buffer[0], &length, C.uint16_t(v[0].(int)))
	case 8: // DPT-8: 2 byte signed value
		C.kdrive_dpt_encode_dpt8(&buffer[0], &length, C.int16_t(v[0].(int)))
	case 9: // DPT-9: 2 byte float value
		C.kdrive_dpt_encode_dpt9(&buffer[0], &length, C.float32_t(v[0].(float64)))
	case 10: // DPT-10: Time
		C.kdrive_dpt_encode_dpt10(&buffer[0], &length, 1, 11, 11, 11)
	case 11: // DPT-11: Date
		C.kdrive_dpt_encode_dpt11(&buffer[0], &length, 2012, 03, 12)
	case 12: // DPT-12: 4 byte unsigned value
		C.kdrive_dpt_encode_dpt12(&buffer[0], &length, C.uint32_t(v[0].(uint)))
	case 13: // DPT-13: 4 byte signed value
		C.kdrive_dpt_encode_dpt13(&buffer[0], &length, C.int32_t(v[0].(int)))
	case 14: // DPT-14: 4 byte float value
		C.kdrive_dpt_encode_dpt14(&buffer[0], &length, C.float32_t(v[0].(float64)))
	case 15: // DPT-15: Entrance access
		C.kdrive_dpt_encode_dpt15(&buffer[0], &length, 1234, 0, 1, 1, 0, 10)
	case 16: // DPT-16: Character string, 14 bytes
		s := C.CString(v[0].(string))
		C.kdrive_dpt_encode_dpt16(&buffer[0], &length, s)
		C.free(unsafe.Pointer(s))
	default:
		log.Println("DPT not found")
		return
	}

	C.kdrive_ap_group_write(ap, C.uint16_t(ga.Int()), &buffer[0], length)
}
