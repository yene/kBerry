//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#ifndef __KDRIVE_EXPRESS_ERROR_H__
#define __KDRIVE_EXPRESS_ERROR_H__

#include "kdrive_express_config.h"

/*************************************
 ** Error Codes
 **************************************/

#define KDRIVE_ERROR_NONE								(0x0000)	/*!< No Error, Everything OK */

#define KDRIVE_UNKNOWN_ERROR							(0x0001)	/*!< Unknown Error Condition */
#define KDRIVE_POCO_ERROR								(0x0002)	/*!< Error from the POCO Libraries */
#define KDRIVE_TIMEOUT_ERROR							(0x0003)	/*!< Timeout */
#define KDRIVE_SOCKET_ERROR								(0x0004)	/*!< Socket Error */
#define KDRIVE_UNSUPPORTED_DEVICE_ERROR					(0x0005)	/*!< The Interface Device is not a kdriveExpress supported Device */
#define KDRIVE_BUFFER_TOO_SMALL_ERROR					(0x0006)	/*!< The data buffer is too small to receive copied data */
#define KDRIVE_AP_DESCRIPTOR_NOT_FOUND_ERROR			(0x0007)	/*!< The access port descriptor wasn't found */
#define KDRIVE_SP_DESCRIPTOR_NOT_FOUND_ERROR			(0x0008)	/*!< The service port descriptor wasn't found */
#define KDRIVE_UNSUPPORTED_ERROR						(0x0009)	/*!< The service or function is not supported */
#define KDRIVE_INVALID_LICENSE_ERROR					(0x000A)	/*!< The license is invalid */
// 0x000B reserved. Was KDRIVE_OBJSER_DESCRIPTOR_NOT_FOUND_ERROR */
// 0x000C reserved. Was KDRIVE_FORMATER_DESCRIPTOR_NOT_FOUND_ERROR */
#define KDRIVE_GODIAG_DESCRIPTOR_NOT_FOUND_ERROR		(0x000D)	/*!< The group object descriptor wasn't found */

#define KDRIVE_AP_ACCESS_PORT_ERROR						(0x1000)	/*!< kdriveAccess error */
#define KDRIVE_AP_NOT_FOUND_AVAILABLE_PORTS_ERROR		(0x1001)	/*!< There are no available access ports */
#define KDRIVE_AP_PORT_NOT_OPEN_ERROR					(0x1002)	/*!< The port is not open. */
#define KDRIVE_AP_UNSUPPORTED_PORT_TYPE_ERROR			(0x1003)	/*!< The port type is not supported. */
#define KDRIVE_AP_UNSUPPORTED_PROTOCOL_ERROR			(0x1004)	/*!< The protocol is not supported. */
#define KDRIVE_AP_UNSUPPORTED_LAYER_ERROR				(0x1005)	/*!< The layer is not supported. */
#define KDRIVE_AP_PROTOCOL_WRITE_VALIDATION_ERROR		(0x1006)	/*!< Protocol write validation failed.*/
#define KDRIVE_AP_LDM_MGMT_PROPERTY_ERROR				(0x1007)	/*!< The local device mangement property is not supported. */
#define KDRIVE_AP_LDM_WRITE_ERROR						(0x1008)	/*!< Write local device management falied. */
#define KDRIVE_AP_NO_RESPONSE_LOCAL_DEVICE_ERROR		(0x1009)	/*!< No response from local device. */
#define KDRIVE_AP_L_DATA_CONFIRM_TIMEOUT_ERROR			(0x100A)	/*!< L_Data.con timeout. */
#define KDRIVE_AP_KNX_NET_IP_ERROR						(0x100B)	/*!< KNXnet/IP exception */
#define KDRIVE_AP_HOST_PROTOCOL_TYPE_ERROR				(0x100C)	/*!< The requested host protocol is not supported. */
#define KDRIVE_AP_VERSION_NOT_SUPPORTED_ERROR			(0x100D)	/*!< The requested protocol version is not supported. */
#define KDRIVE_AP_SEQUENCE_NUMBER_ERROR					(0x100E)	/*!< The received sequence number is out of order. */
#define KDRIVE_AP_CONNECTION_TYPE_ERROR					(0x100F)	/*!< The device does not support the requested connection type. */
#define KDRIVE_AP_CONNECTION_OPTION_ERROR				(0x1010)	/*!< The device does not support one or more requested connection options. */
#define KDRIVE_AP_NO_MORE_CONNECTIONS_ERROR				(0x1011)	/*!< Device can not open any more connections. */
#define KDRIVE_AP_TUNNELING_LAYER_ERROR					(0x1012)	/*!< The device does not support the requested tunneling layer. */
#define KDRIVE_AP_CONNECTION_ID_ERROR					(0x1013)	/*!< The device cannot find an active data connection with the specified ID. */
#define KDRIVE_AP_DATA_CONNECTION_ERROR					(0x1014)	/*!< The device detects an error concerning the data connection with the specified ID. */
#define KDRIVE_AP_KNX_CONNECTION_ERROR					(0x1015)	/*!< No connection to the KNX bus. */
#define KDRIVE_AP_INVALID_TELEGRAM_ERROR				(0x1016)	/*!< Invalid Telegram. */
#define KDRIVE_AP_TELEGRAM_TIMEOUT_ERROR				(0x1017)	/*!< Telegram timeout. */

/*! 0x1018 to 0x1022 are reserved. Were EPB access port error messages */

#define KDRIVE_AP_NO_PREFERRED_PROTOCOL_FOUND_ERROR		(0x1023)	/*!< No prefered protocol found */
#define KDRIVE_AP_NO_PREFERRED_LAYER_FOUND_ERROR		(0x1024)	/*!< No prefered layer found */
#define KDRIVE_AP_PROTOCOL_NOT_SET_ERROR				(0x1025)	/*!< The protocol is not set */

#define KDRIVE_SP_SERVICES_ERROR						(0x2000)	/*!< kdriveServices error */
#define KDRIVE_SP_UNKNOWN_SERVICE_TYPE_ERROR			(0x2001)	/*!< Unknown service type */
#define KDRIVE_SP_SERVICE_PORT_NOT_SET_ERROR			(0x2002)	/*!< Service port has not been set  */
#define KDRIVE_SP_OPERATION_CANCELLED_ERROR				(0x2003)	/*!< Service operation was cancelled  */
#define KDRIVE_SP_NEGATIVE_CONFIRM_ERROR				(0x2004)	/*!< Negative confirm (L_DATA_Con was not received)  */
#define KDRIVE_SP_INVALID_INPUT_PARAMETER_ERROR			(0x2005)	/*!< Invalid service input parameter */
#define KDRIVE_SP_DEVICE_ERROR							(0x2006)	/*!< Device error (valid response but invalid data) */
#define KDRIVE_SP_OBJECT_TYPE_NOT_SUPPORTED_ERROR		(0x2007)	/*!< Object Type not supported  */
#define KDRIVE_SP_PROPERTY_ID_NOT_SUPPORTED_ERROR		(0x2008)	/*!< Property Id not supported  */
#define KDRIVE_SP_NO_DEVICE_IN_PROG_MODE_ERROR			(0x2009)	/*!< No devices were found in programming mode (expected 1)  */
#define KDRIVE_SP_MORE_DEVICES_IN_PROG_MODE_ERROR		(0x200A)	/*!< Too many devices were found in programming mode (expected 1)  */
#define KDRIVE_SP_WRITE_IND_ADDR_FAILED_ERROR			(0x200B)	/*!< Individual address write failed  */
#define KDRIVE_SP_WRITE_DOMAIN_ADDR_FAILED_ERROR		(0x200C)	/*!< Domain address write failed  */
#define KDRIVE_SP_ACCESS_PORT_NOT_SET_ERROR				(0x200D)	/*!< The Access Port has not been set in the Service Port  */
#define KDRIVE_SP_NEGATIVE_RESPONSE_ERROR				(0x200E)	/*!< Negative response from device (valid response received) */

#define KDRIVE_KER_PROTOCOL_ERROR						(0x3000)	/*!* kdriveKernel error */
#define KDRIVE_KER_REPEATED_ERROR						(0x3001)	/*!* Telegram Repeated */
#define KDRIVE_KER_SEQUENCE_NUMBER_ERROR				(0x3002)	/*!* Sequence Number Error */
#define KDRIVE_KER_IGNORED_ERROR						(0x3003)	/*!* Telegram Ignored */
#define KDRIVE_KER_DISCONNECTED_ERROR					(0x3004)	/*!* Connection Disconnected */
#define KDRIVE_KER_REJECTED_ERROR						(0x3005)	/*!* Telegram Rejected */
#define KDRIVE_KER_NO_LAYERS_DEFINED_ERROR				(0x3006)	/*!* No response from device */
#define KDRIVE_KER_NO_RESPONSE_FROM_DEVICE_ERROR		(0x3007)	/*!* No layers defined */
#define KDRIVE_KER_PACKET_ERROR							(0x3008)	/*!* Packet type not supported */
#define KDRIVE_KER_NO_MORE_CONNECTIONS_ERROR			(0x3009)	/*!* No more connections allowed */
#define KDRIVE_KER_CONNECTION_FAILED_ERROR				(0x300A)	/*!* Could not open transport layer connection */
#define KDRIVE_KER_CONFIRM_TIMEOUT_ERROR				(0x300B)	/*!* No confirm from device (T-Ack missing) */

#ifdef __cplusplus
extern "C" {
#endif

/*!
	Gets the error message
	\param [in] e holds the error code
	\param [out] str the error message as null-terminated string
	\param [in] str_len indicates the max buffer length for str
*/
kdriveExpress_API void kdrive_get_error_message(error_t e, char* str, uint32_t str_len);

/*!
	Error Callback function type (pointer to function definition)
	\sa kdrive_register_error_callback
	\param [in] e holds the error code
	\param [in] user_data pointer to user data or NULL
*/
typedef void (*kdrive_error_callback)(error_t e, void* user_data);

/*!
	Registers the error callback function.
	This callback function will be called when an error occurred.
	A notification thread is used internally so
	this callback will be in the context of the notification thread
	(and not the main thread). That is, care should be taken when calling
	out from the callback.
	There can only be one callback. To remove the callback egister an empty callback (0).
	\sa kdrive_ap_register_telegram_callback
	\param [in] c the telegram callback pointer to function
	\param [in] user_data (optional) pointer to user data
*/
kdriveExpress_API void kdrive_register_error_callback(kdrive_error_callback c, void* user_data);

#ifdef __cplusplus
}
#endif

#endif /* __KDRIVE_EXPRESS_ERROR_H__ */
