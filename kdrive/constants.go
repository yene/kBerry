package kdrive

/*******************************
** Defines
*******************************/

const KDRIVE_MAX_GROUP_VALUE_LEN = 14  // The Maximum Length of a Datapoint Value in a GroupValue Telegram
const KDRIVE_SN_LEN = 6                // The Length of a KNX Serial Number
const KDRIVE_DA_LEN = 6                // The Length of a KNX Domain Address
const KDRIVE_MAC_LEN = 6               // The Length of a MAC Address
const KDRIVE_INVALID_DESCRIPTOR = -1   // Indicates an invalid descriptor
const KDRIVE_DPT16_LENGTH = 14         // The length of a KNX character string for DPT-16 is 112 bits or 14 bytes
const KDRIVE_MAX_IP_ADDRESS_LEN = 16   // The max length of a formated ip address string e.g. 192.168.234.123; (inclusive 1 byte for zero)
const KDRIVE_MAX_DEVICE_NAME_LEN = 121 // The max length of a device friendly name (30 char); (inclusive 1 byte for zero + max utf8 char)

// Logger
const KDRIVE_LOGGER_NONE = 0        // No logger
const KDRIVE_LOGGER_FATAL = 1       // A fatal error. The application will most likely terminate. This is the highest priority.
const KDRIVE_LOGGER_CRITICAL = 2    // A critical error. The application might not be able to continue running successfully.
const KDRIVE_LOGGER_ERROR = 3       // An error. An operation did not complete successfully, but the application as a whole is not affected.
const KDRIVE_LOGGER_WARNING = 4     // A warning. An operation completed with an unexpected result.
const KDRIVE_LOGGER_NOTICE = 5      // A notice, which is an information with just a higher priority.
const KDRIVE_LOGGER_INFORMATION = 6 // An informational message, usually denoting the successful completion of an operation.
const KDRIVE_LOGGER_DEBUG = 7       // A debugging message.
const KDRIVE_LOGGER_TRACE = 8       // A tracing message. This is the lowest priority.

// Message codes
const KDRIVE_CEMI_L_DATA_REQ = 0x11 // cEMI message code for L_Data.req
const KDRIVE_CEMI_L_DATA_CON = 0x2E // cEMI message code for L_Data.con
const KDRIVE_CEMI_L_DATA_IND = 0x29 // cEMI message code for L_Data.ind

// KNX Layer
const KDRIVE_LAYER_LINK = 1   // Link Layer
const KDRIVE_LAYER_BUSMON = 2 // Busmonitor
const KDRIVE_LAYER_RAW = 4    // Raw

// DPT_Media
const KDRIVE_MEDIUM_TP = 0x02 // Medium TP 1
const KDRIVE_MEDIUM_PL = 0x04 // Medium PL 110
const KDRIVE_MEDIUM_RF = 0x10 // Medium RF
const KDRIVE_MEDIUM_IP = 0x20 // Medium IP

// Packet Direction
const KDRIVE_PACKET_DIR_RX = 0 // Packet Direction: Rx
const KDRIVE_PACKET_DIR_TX = 1 // Packet Direction: Tx

/*************************************
 ** Error Codes
 **************************************/

const KDRIVE_ERROR_NONE = 0x0000 // No Error, Everything OK

const KDRIVE_UNKNOWN_ERROR = 0x0001                 // Unknown Error Condition
const KDRIVE_POCO_ERROR = 0x0002                    // Error from the POCO Libraries
const KDRIVE_TIMEOUT_ERROR = 0x0003                 // Timeout
const KDRIVE_SOCKET_ERROR = 0x0004                  // Socket Error
const KDRIVE_UNSUPPORTED_DEVICE_ERROR = 0x0005      // The Interface Device is not a kdriveExpress supported Device
const KDRIVE_BUFFER_TOO_SMALL_ERROR = 0x0006        // The data buffer is too small to receive copied data
const KDRIVE_AP_DESCRIPTOR_NOT_FOUND_ERROR = 0x0007 // The access port descriptor wasn't found
const KDRIVE_SP_DESCRIPTOR_NOT_FOUND_ERROR = 0x0008 // The service port descriptor wasn't found
const KDRIVE_UNSUPPORTED_ERROR = 0x0009             // The service or function is not supported
const KDRIVE_INVALID_LICENSE_ERROR = 0x000A         // The license is invalid
// 0x000B reserved. Was KDRIVE_OBJSER_DESCRIPTOR_NOT_FOUND_ERROR
// 0x000C reserved. Was KDRIVE_FORMATER_DESCRIPTOR_NOT_FOUND_ERROR
const KDRIVE_GODIAG_DESCRIPTOR_NOT_FOUND_ERROR = 0x000D // The group object descriptor wasn't found

const KDRIVE_AP_ACCESS_PORT_ERROR = 0x1000               // kdriveAccess error
const KDRIVE_AP_NOT_FOUND_AVAILABLE_PORTS_ERROR = 0x1001 // There are no available access ports
const KDRIVE_AP_PORT_NOT_OPEN_ERROR = 0x1002             // The port is not open.
const KDRIVE_AP_UNSUPPORTED_PORT_TYPE_ERROR = 0x1003     // The port type is not supported.
const KDRIVE_AP_UNSUPPORTED_PROTOCOL_ERROR = 0x1004      // The protocol is not supported.
const KDRIVE_AP_UNSUPPORTED_LAYER_ERROR = 0x1005         // The layer is not supported.
const KDRIVE_AP_PROTOCOL_WRITE_VALIDATION_ERROR = 0x1006 // Protocol write validation failed.*/
const KDRIVE_AP_LDM_MGMT_PROPERTY_ERROR = 0x1007         // The local device mangement property is not supported.
const KDRIVE_AP_LDM_WRITE_ERROR = 0x1008                 // Write local device management falied.
const KDRIVE_AP_NO_RESPONSE_LOCAL_DEVICE_ERROR = 0x1009  // No response from local device.
const KDRIVE_AP_L_DATA_CONFIRM_TIMEOUT_ERROR = 0x100A    // L_Data.con timeout.
const KDRIVE_AP_KNX_NET_IP_ERROR = 0x100B                // KNXnet/IP exception
const KDRIVE_AP_HOST_PROTOCOL_TYPE_ERROR = 0x100C        // The requested host protocol is not supported.
const KDRIVE_AP_VERSION_NOT_SUPPORTED_ERROR = 0x100D     // The requested protocol version is not supported.
const KDRIVE_AP_SEQUENCE_NUMBER_ERROR = 0x100E           // The received sequence number is out of order.
const KDRIVE_AP_CONNECTION_TYPE_ERROR = 0x100F           // The device does not support the requested connection type.
const KDRIVE_AP_CONNECTION_OPTION_ERROR = 0x1010         // The device does not support one or more requested connection options.
const KDRIVE_AP_NO_MORE_CONNECTIONS_ERROR = 0x1011       // Device can not open any more connections.
const KDRIVE_AP_TUNNELING_LAYER_ERROR = 0x1012           // The device does not support the requested tunneling layer.
const KDRIVE_AP_CONNECTION_ID_ERROR = 0x1013             // The device cannot find an active data connection with the specified ID.
const KDRIVE_AP_DATA_CONNECTION_ERROR = 0x1014           // The device detects an error concerning the data connection with the specified ID.
const KDRIVE_AP_KNX_CONNECTION_ERROR = 0x1015            // No connection to the KNX bus.
const KDRIVE_AP_INVALID_TELEGRAM_ERROR = 0x1016          // Invalid Telegram.
const KDRIVE_AP_TELEGRAM_TIMEOUT_ERROR = 0x1017          // Telegram timeout.

// 0x1018 to 0x1022 are reserved. Were EPB access port error messages

const KDRIVE_AP_NO_PREFERRED_PROTOCOL_FOUND_ERROR = 0x1023 // No prefered protocol found
const KDRIVE_AP_NO_PREFERRED_LAYER_FOUND_ERROR = 0x1024    // No prefered layer found
const KDRIVE_AP_PROTOCOL_NOT_SET_ERROR = 0x1025            // The protocol is not set

const KDRIVE_SP_SERVICES_ERROR = 0x2000                  // kdriveServices error
const KDRIVE_SP_UNKNOWN_SERVICE_TYPE_ERROR = 0x2001      // Unknown service type
const KDRIVE_SP_SERVICE_PORT_NOT_SET_ERROR = 0x2002      // Service port has not been set
const KDRIVE_SP_OPERATION_CANCELLED_ERROR = 0x2003       // Service operation was cancelled
const KDRIVE_SP_NEGATIVE_CONFIRM_ERROR = 0x2004          // Negative confirm (L_DATA_Con was not received
const KDRIVE_SP_INVALID_INPUT_PARAMETER_ERROR = 0x2005   // Invalid service input parameter
const KDRIVE_SP_DEVICE_ERROR = 0x2006                    // Device error (valid response but invalid data)
const KDRIVE_SP_OBJECT_TYPE_NOT_SUPPORTED_ERROR = 0x2007 // Object Type not supported
const KDRIVE_SP_PROPERTY_ID_NOT_SUPPORTED_ERROR = 0x2008 // Property Id not supported
const KDRIVE_SP_NO_DEVICE_IN_PROG_MODE_ERROR = 0x2009    // No devices were found in programming mode (expected 1
const KDRIVE_SP_MORE_DEVICES_IN_PROG_MODE_ERROR = 0x200A // Too many devices were found in programming mode (expected 1
const KDRIVE_SP_WRITE_IND_ADDR_FAILED_ERROR = 0x200B     // Individual address write failed
const KDRIVE_SP_WRITE_DOMAIN_ADDR_FAILED_ERROR = 0x200C  // Domain address write failed
const KDRIVE_SP_ACCESS_PORT_NOT_SET_ERROR = 0x200D       // The Access Port has not been set in the Service Port
const KDRIVE_SP_NEGATIVE_RESPONSE_ERROR = 0x200E         // Negative response from device (valid response received)

const KDRIVE_KER_PROTOCOL_ERROR = 0x3000                // kdriveKernel error
const KDRIVE_KER_REPEATED_ERROR = 0x3001                // Telegram Repeated
const KDRIVE_KER_SEQUENCE_NUMBER_ERROR = 0x3002         // Sequence Number Error
const KDRIVE_KER_IGNORED_ERROR = 0x3003                 // Telegram Ignored
const KDRIVE_KER_DISCONNECTED_ERROR = 0x3004            // Connection Disconnected
const KDRIVE_KER_REJECTED_ERROR = 0x3005                // Telegram Rejected
const KDRIVE_KER_NO_LAYERS_DEFINED_ERROR = 0x3006       // No response from device
const KDRIVE_KER_NO_RESPONSE_FROM_DEVICE_ERROR = 0x3007 // No layers defined
const KDRIVE_KER_PACKET_ERROR = 0x3008                  // Packet type not supported
const KDRIVE_KER_NO_MORE_CONNECTIONS_ERROR = 0x3009     // No more connections allowed
const KDRIVE_KER_CONNECTION_FAILED_ERROR = 0x300A       // Could not open transport layer connection
const KDRIVE_KER_CONFIRM_TIMEOUT_ERROR = 0x300B         // No confirm from device (T-Ack missing)
