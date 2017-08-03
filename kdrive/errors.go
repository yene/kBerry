package kdrive

type kdriveError struct {
	name        string
	code        int
	description string
}

var kdriveErrors []kdriveError

func getKdriveError(ecode int) string {
	if len(kdriveErrors) == 0 {
		loadKdriveErrors()
	}

	for _, e := range kdriveErrors {
		if e.code == ecode {
			return e.description
		}
	}

	return "Error was not defined by kDrive."
}

func loadKdriveErrors() {
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_ERROR_NONE", 0x0000, "No Error, Everything OK"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_UNKNOWN_ERROR", 0x0001, "Unknown Error Condition"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_POCO_ERROR", 0x0002, "Error from the POCO Libraries"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_TIMEOUT_ERROR", 0x0003, "Timeout"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SOCKET_ERROR", 0x0004, "Socket Error"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_UNSUPPORTED_DEVICE_ERROR", 0x0005, "The Interface Device is not a kdriveExpress supported Device"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_BUFFER_TOO_SMALL_ERROR", 0x0006, "The data buffer is too small to receive copied data"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_DESCRIPTOR_NOT_FOUND_ERROR", 0x0007, "The access port descriptor wasn't found"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_DESCRIPTOR_NOT_FOUND_ERROR", 0x0008, "The service port descriptor wasn't found"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_UNSUPPORTED_ERROR", 0x0009, "The service or function is not supported"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_INVALID_LICENSE_ERROR", 0x000A, "The license is invalid"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_GODIAG_DESCRIPTOR_NOT_FOUND_ERROR", 0x000D, "The group object descriptor wasn't found"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_ACCESS_PORT_ERROR", 0x1000, "kdriveAccess error"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_NOT_FOUND_AVAILABLE_PORTS_ERROR", 0x1001, "There are no available access ports"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_PORT_NOT_OPEN_ERROR", 0x1002, "The port is not open."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_UNSUPPORTED_PORT_TYPE_ERROR", 0x1003, "The port type is not supported."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_UNSUPPORTED_PROTOCOL_ERROR", 0x1004, "The protocol is not supported."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_UNSUPPORTED_LAYER_ERROR", 0x1005, "The layer is not supported."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_PROTOCOL_WRITE_VALIDATION_ERROR", 0x1006, "Protocol write validation failed."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_LDM_MGMT_PROPERTY_ERROR", 0x1007, "The local device mangement property is not supported."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_LDM_WRITE_ERROR", 0x1008, "Write local device management falied."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_NO_RESPONSE_LOCAL_DEVICE_ERROR", 0x1009, "No response from local device."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_L_DATA_CONFIRM_TIMEOUT_ERROR", 0x100A, "L_Data.con timeout."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_KNX_NET_IP_ERROR", 0x100B, "KNXnet/IP exception"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_HOST_PROTOCOL_TYPE_ERROR", 0x100C, "The requested host protocol is not supported."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_VERSION_NOT_SUPPORTED_ERROR", 0x100D, "The requested protocol version is not supported."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_SEQUENCE_NUMBER_ERROR", 0x100E, "The received sequence number is out of order."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_CONNECTION_TYPE_ERROR", 0x100F, "The device does not support the requested connection type."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_CONNECTION_OPTION_ERROR", 0x1010, "The device does not support one or more requested connection options."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_NO_MORE_CONNECTIONS_ERROR", 0x1011, "Device can not open any more connections."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_TUNNELING_LAYER_ERROR", 0x1012, "The device does not support the requested tunneling layer."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_CONNECTION_ID_ERROR", 0x1013, "The device cannot find an active data connection with the specified ID."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_DATA_CONNECTION_ERROR", 0x1014, "The device detects an error concerning the data connection with the specified ID."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_KNX_CONNECTION_ERROR", 0x1015, "No connection to the KNX bus."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_INVALID_TELEGRAM_ERROR", 0x1016, "Invalid Telegram."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_TELEGRAM_TIMEOUT_ERROR", 0x1017, "Telegram timeout."})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_NO_PREFERRED_PROTOCOL_FOUND_ERROR", 0x1023, "No prefered protocol found"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_NO_PREFERRED_LAYER_FOUND_ERROR", 0x1024, "No prefered layer found"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_AP_PROTOCOL_NOT_SET_ERROR", 0x1025, "The protocol is not set"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_SERVICES_ERROR", 0x2000, "kdriveServices error"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_UNKNOWN_SERVICE_TYPE_ERROR", 0x2001, "Unknown service type"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_SERVICE_PORT_NOT_SET_ERROR", 0x2002, "Service port has not been set"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_OPERATION_CANCELLED_ERROR", 0x2003, "Service operation was cancelled"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_NEGATIVE_CONFIRM_ERROR", 0x2004, "Negative confirm (L_DATA_Con was not received) "})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_INVALID_INPUT_PARAMETER_ERROR", 0x2005, "Invalid service input parameter"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_DEVICE_ERROR", 0x2006, "Device error (valid response but invalid data)"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_OBJECT_TYPE_NOT_SUPPORTED_ERROR", 0x2007, "Object Type not supported "})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_PROPERTY_ID_NOT_SUPPORTED_ERROR", 0x2008, "Property Id not supported "})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_NO_DEVICE_IN_PROG_MODE_ERROR", 0x2009, "No devices were found in programming mode (expected 1)"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_MORE_DEVICES_IN_PROG_MODE_ERROR", 0x200A, "Too many devices were found in programming mode (expected 1)"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_WRITE_IND_ADDR_FAILED_ERROR", 0x200B, "Individual address write failed"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_WRITE_DOMAIN_ADDR_FAILED_ERROR", 0x200C, "Domain address write failed"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_ACCESS_PORT_NOT_SET_ERROR", 0x200D, "The Access Port has not been set in the Service Port "})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_SP_NEGATIVE_RESPONSE_ERROR", 0x200E, "Negative response from device (valid response received)"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_PROTOCOL_ERROR", 0x3000, "kdriveKernel error"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_REPEATED_ERROR", 0x3001, "Telegram Repeated"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_SEQUENCE_NUMBER_ERROR", 0x3002, "Sequence Number Error"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_IGNORED_ERROR", 0x3003, "Telegram Ignored"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_DISCONNECTED_ERROR", 0x3004, "Connection Disconnected"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_REJECTED_ERROR", 0x3005, "Telegram Rejected"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_NO_LAYERS_DEFINED_ERROR", 0x3006, "No response from device"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_NO_RESPONSE_FROM_DEVICE_ERROR", 0x3007, "No layers defined"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_PACKET_ERROR", 0x3008, "Packet type not supported"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_NO_MORE_CONNECTIONS_ERROR", 0x3009, "No more connections allowed"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_CONNECTION_FAILED_ERROR", 0x300A, "Could not open transport layer connection"})
	kdriveErrors = append(kdriveErrors, kdriveError{"KDRIVE_KER_CONFIRM_TIMEOUT_ERROR", 0x300B, "No confirm from device (T-Ack missing)"})

}
