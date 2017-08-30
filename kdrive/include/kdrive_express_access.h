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

#ifndef __KDRIVE_EXPRESS_ACCESS_H__
#define __KDRIVE_EXPRESS_ACCESS_H__

#include "kdrive_express_config.h"
#include "kdrive_express_defs.h"

/*!
	\file kdrive_express_access.h
	\brief kdriveExpress Access API
	\author Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
	\defgroup kdrive_express_access kdriveExpress Access API
*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************
** Init
********************************/

/*!
	Creates an internal AccessPort interface
	This should be the first function called when
	working with the access library. It creates a
	unique access port descriptor which will be passed to all
	kdrive access functions. When finished, call kdrive_ap_release.
	If create fails the function returns KDRIVE_INVALID_DESCRIPTOR
	\return access port descriptor if succesful
	\ingroup kdrive_express_access
*/
kdriveExpress_API int32_t kdrive_ap_create(void);

/*!
	Releases the AccessPort interface.
	This should be the last function called when
	working with the access library.
	Returns true if successfully released
	false otherwise (i.e. the descriptor wasn't found).
	\param [in] ap the access port descriptor
	\ingroup kdrive_express_access
*/
kdriveExpress_API bool_t kdrive_ap_release(int32_t ap);

/*******************************
** USB
********************************/

/*!
	Scan for all KNX USB Interface devices
	\param [in] ap the access port descriptor
	\return count of successfully enumerated interface devices
	\ingroup kdrive_express_access
*/
kdriveExpress_API uint32_t kdrive_ap_enum_usb(int32_t ap);

/*!
	Structure holding usb device information
	\see kdrive_ap_enum_usb_ex
	\ingroup kdrive_express_access
*/
typedef struct usb_dev_t
{
	uint16_t ind_addr; /*!< KNX indiviual address */
	uint16_t media_tytes; /*!< knx media types (bit field, encoding is DPT_Media)*/
	uint32_t internal_usb_index; /*!< numbered in the order that the hid driver enumerates the devices*/
	uint32_t usb_vendor_id; /*!< usb device vendor id*/
	uint32_t usb_product_id; /*!< usb device product id*/

} usb_dev_t;

/*!
	Scan for all KNX USB Interface devices
	The items array must exist (should be pre-allocated by the user).
	The max size of the array must be passed in as items_length.
	items_length will be updated to correspond to the length of the
	found devices. If the array is to small than only the possible values will returned.
	\param [out] items the array of usb device struct items with the found usb devices
	\param [in,out] items_length the data array capacity (in) and actual length of the data array (out)
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_enum_usb_ex(usb_dev_t items[], uint32_t* items_length);

/*!
	Opens a connection to a KNX USB Interface device
	iface_index should be in the range 0..iface_count-1
	where iface_count is > 0
	\sa kdriveEnumerateUSB
	\param [in] ap the access port descriptor
	\param [in] iface_index the interface device enumeration index
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_open_usb(int32_t ap, uint32_t iface_index);

/*******************************
** IP
********************************/

/*!
	Structure holding ip tunneling device information
	\see kdrive_ap_enum_ip_tunn
	\ingroup kdrive_express_access
*/
typedef struct ip_tunn_dev_t
{
	char ip_address[KDRIVE_MAX_IP_ADDRESS_LEN]; /*!< IP address in the form "192.168.1.47" for example. Null-terminated string*/
	char iface_address[KDRIVE_MAX_IP_ADDRESS_LEN]; /*!< interface adaptor IP address. Null-terminated string*/
	char dev_name[KDRIVE_MAX_DEVICE_NAME_LEN]; /*!< device friendly name. Null-terminated string in utf8 encoding*/
	uint16_t ind_addr; /*!< KNX indiviual address */
	uint8_t mac_address[KDRIVE_MAC_LEN]; /*!< mac address */
	uint8_t serial_number[KDRIVE_SN_LEN]; /*!< serial number */
	bool_t prog_mode_enabled; /*!< state of the programming mode 0 = off, 1 = on*/

} ip_tunn_dev_t;

/*!
	Scans for all KNX IP Tunneling Interface devices
	The items array must exist (should be pre-allocated by the user).
	The max size of the array must be passed in as items_length.
	items_length will be updated to correspond to the length of the
	found devices. If the array is to small than only the possible values will returned.
	\param [in] ap the access port descriptor
	\param [out] items the array of tunneling device struct items with the found ip tunning devices
	\param [in,out] items_length the data array capacity (in) and actual length of the data array (out)
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_enum_ip_tunn(int32_t ap,
        ip_tunn_dev_t items[],
        uint32_t* items_length);

/*!
	Opens a connection to a KNX IP Tunneling Interface device
	\sa kdrive_ap_open_ip_ex
	\sa kdrive_ap_open_ip_nat
	\param [in] ap the access port descriptor
	\param [in] ip_address The IP Address and (optional) the port which is separated by a colon.
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_open_ip(int32_t ap, const char* ip_address);

/*!
	Opens a connection to a KNX IP Tunneling Interface device
	on a specific network interface
	\sa kdrive_ap_open_ip
	\sa kdrive_ap_open_ip_nat
	\param [in] ap the access port descriptor
	\param [in] ip_address The IP Address and (optional) the port which is separated by a colon.
				When the port is not set then the default port for KNXnet/IP (3671) is used
				e.g.
				"192.168.1.47"
				"192.168.1.47:3671"
	\param [in] iface_address (optional) The Interface Adaptor IP Address <br />
	            If iface_address = 0 (null pointer) then the default network interface is used
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_open_ip_ex(int32_t ap, const char* ip_address, const char* iface_address);

/*!
	Opens a connection to a KNX IP Tunneling Interface device
	on a specific network interface in Network Address Translation (NAT) mode.
	\sa kdrive_ap_open_ip
	\sa kdrive_ap_open_ip_ex
	\param [in] ap the access port descriptor
	\param [in] ip_address The IP Address and (optional) the port which is separated by a colon.
				When the port is not set then the default port for KNXnet/IP (3671) is used
				e.g.
				"192.168.1.47"
				"192.168.1.47:3671"
	\param [in] iface_address (optional) The Interface Adaptor IP Address <br />
	            If iface_address = 0 (null pointer) then the default network interface is used
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_open_ip_nat(int32_t ap, const char* ip_address, const char* iface_address);

/*******************************
** Serial FT1.2
********************************/

/*!
	Opens a connection to a KNX FT1.2 serial interface
	\param [in] ap the access port descriptor
	\param [in] serial_device is the device where the interface is attached, i.e. COM1 or /dev/ttyS0 etc
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_open_serial_ft12(int32_t ap, const char* serial_device);

/*******************************
** TinySerial
********************************/

/*!
	Opens a connection to the KNX Tiny Serial Interface 810.
	This is a modified TP-UART Protocol without real-time requirements to the host
	\param [in] ap the access port descriptor
	\param [in] serial_device is the device where the interface is attached, i.e. COM1 or /dev/ttyS0 etc
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_open_tiny_serial(int32_t ap, const char* serial_device);

/*******************************
** Connection Management
********************************/

/*!
	Closes the access port
	If the access port is not open nothing happens
	\param [in] ap the access port descriptor
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_close(int32_t ap);

/*!
	Returns whether the access port is open
	\param [in] ap the access port descriptor
	\return 1 if the access port is open, 0 otherwise
	\ingroup kdrive_express_access
*/
kdriveExpress_API bool_t kdrive_ap_is_open(int32_t ap);

/*******************************
** Send KNX Telegrams
********************************/

/*!
	Sends a KNX Telegram on the Access Port
	\param [in] ap the access port descriptor
	\param [in] telegram is the EMIC encoded KNX Telegram
	\param [in] telegram_len indicates the length of the telegram
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_send(int32_t ap, const uint8_t telegram[], uint32_t telegram_len);

/*!
	Sends a GroupValue_Write Telegram
	The length is specified in bits to enable values less than one byte
	to be sent (i.e. 1 bit boolean) etc.
	\param [in] ap the access port descriptor
	\param [in] address is the Group Address (destination)
	\param [in] value is the datapoint value to be sent
	\param [in] bits respresents the length of the datapoint value, in bits
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_group_write(int32_t ap, uint16_t address, const uint8_t* value, uint32_t bits);

/*!
	Sends a GroupValue_Read Telegram on the Access Port
	This function does not wait for a GroupValue_Response telegram
	\param [in] ap the access port descriptor
	\param [in] address is the Group Address (destination)
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_group_read(int32_t ap, uint16_t address);

/*!
	Sends a GroupValue_Response Telegram
	\sa kdriveGroupValueWrite
	\param [in] ap the access port descriptor
	\param [in] address is the Group Address (destination)
	\param [in] value is the datapoint value to be sent
	\param [in] bits respresents the length of the datapoint value, in bits
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_group_response(int32_t ap, uint16_t address, const uint8_t* value, uint32_t bits);

/*!
	Sends a GroupValue_Read Telegram on the Access Port
	and waits for a GroupValue_Response indication telegram
	(with a matching Group Address).
	If the response telegram has been received you can use
	kdrive_ap_get_group_data to get the response data.
	This function waits until either a telegram is received
	or the timeout elapses. If the timeout elapses the
	number of bytes returned is 0. On receipt of a matching
	GroupValue_Response telegram indication the corresponding
	telegram length is returned.
	\param [in] ap the access port descriptor
	\param [in] address is the Group Address (destination)
	\param [out] telegram buffer to hold the inbound telegram
	\param [in] telegram_len  As an input this holds the size of the telegram buffer
	\param [in] timeout The time period to wait in milliseconds for the response to arrive
	\ingroup kdrive_express_access
*/
kdriveExpress_API uint32_t kdrive_ap_read_group_object(int32_t ap, uint16_t address,
        uint8_t telegram[], uint32_t telegram_len, uint32_t timeout);

/*******************************
** Receive KNX Telegrams
********************************/

/*!
	Enables/Disables the receive queue for the access port.
	\param [in] ap the access port descriptor
	\param [in] enabled true enables the receive queue false disables the queue
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_enable_queue(int32_t ap, bool_t enabled);

/*!
	Waits for an inbound KNX telegram and (if received)
	copies the data into the telegram buffer.
	This function waits until either a telegram is received
	or the timeout elapses. If the timeout elapses the
	number of bytes returned is 0. On receipt of a telegram the
	corresponding telegram length is returned.
	\param [in] ap the access port descriptor
	\param [out] telegram buffer to hold the inbound telegram
	\param [in] telegram_len  As an input this holds the size of the telegram buffer
	\param [out] telegram_len Holds the length of the received telegram
	\param [in] timeout The time period to wait in milliseconds for a telegram to arrive
	\ingroup kdrive_express_access
*/
kdriveExpress_API uint32_t kdrive_ap_receive(int32_t ap,
        uint8_t telegram[], uint32_t telegram_len, uint32_t timeout);

/*******************************
** KNX Telegram Callback
********************************/

/*!
	Callback function type (pointer to function definition)
	\sa kdrive_ap_register_telegram_callback
	\param [in] telegram holds the received telegram, the buffer is temporary
	\param [in] telegram_len indicates the length of the telegram
	\param [in] user_data pointer to user data or NULL
	\ingroup kdrive_express_access
*/
typedef void (*kdrive_ap_telegram_callback)(const uint8_t telegram[], uint32_t telegram_len, void* user_data);

/*!
	Registers a callback function.
	This callback function will be called when a telegram is received
	by the Access Port. A notification thread is used internally so
	this callback will be in the context of the notification thread
	(and not the main thread). That is, care should be taken when calling
	out from the callback.
	This function generates a unique key to represent the callback. This key
	can be used to remove the callback at a later state.
	\sa kdrive_ap_remove_telegram_callback
	\param [in] ap the access port descriptor
	\param [in] c the telegram callback pointer to function
	\param [in] user_data (optional) pointer to user data
	\param [out] key is set as a unique internal handle representing the callback function
	and can be used to remove the callback
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_register_telegram_callback(int32_t ap,
        kdrive_ap_telegram_callback c, void* user_data, uint32_t* key);

/*!
	Removes (de-registers) a telegram callback
	\param [in] ap the access port descriptor
	\param [in] key is the key returned from kdrive_ap_register_telegram_callback
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_remove_telegram_callback(int32_t ap, uint32_t key);

/*******************************
** Telegram Attributes
********************************/

/*!
	Extracts the Destination Address from the Telegram
	\param [in] telegram the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\param [out] address the destination address
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_dest(const uint8_t telegram[],
        uint32_t telegram_len, uint16_t* address);

/*!
	Extracts the Source Address from the Telegram
	\param [in] telegram the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\param [out] address the source address
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_src(const uint8_t telegram[],
        uint32_t telegram_len, uint16_t* address);

/*!
	Extracts the APCI from the Telegram
	\param [in] telegram the the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\param [out] apci APCI
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_apci(const uint8_t telegram[],
        uint32_t telegram_len, uint16_t* apci);

/*!
	Extracts the Message Code from the Telegram
	\see KDRIVE_CEMI_L_DATA_REQ
	\see KDRIVE_CEMI_L_DATA_CON
	\see KDRIVE_CEMI_L_DATA_IND
	\param [in] telegram the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\param [out] message_code the Message Code
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_message_code(const uint8_t telegram[],
        uint32_t telegram_len, uint8_t* message_code);

/*!
	Extracts the Serial Number from the Additional Info (if available)
	This is extracted from the Additional Info field
	i.e. for KNX-RF telegrams
	\param [in] telegram the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\param [out] sn the Serial Number
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_serial_number(const uint8_t telegram[],
        uint32_t telegram_len, uint8_t sn[KDRIVE_SN_LEN]);

/*******************************
** Group Values
********************************/

/*!
	Determines if the specified telegram is a GroupValue telegram
	This is, one of GroupValue_Read, GroupValue_Write or GroupValue_Response.
	\param [in] telegram the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\return true if a Group Telegram false otherwise
	\ingroup kdrive_express_access
*/
kdriveExpress_API bool_t kdrive_ap_is_group(const uint8_t telegram[], uint32_t telegram_len);

/*!
	Determines if the specified telegram is a GroupValue_Write telegram
	\param [in] telegram the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\return true if a GroupValue_Write telegram false otherwise
	\ingroup kdrive_express_access
*/
kdriveExpress_API bool_t kdrive_ap_is_group_write(const uint8_t telegram[], uint32_t telegram_len);

/*!
	Determines if the specified telegram is a GroupValue_Read telegram
	\param [in] telegram the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\return true if a GroupValue_Read telegram false otherwise
	\ingroup kdrive_express_access
*/
kdriveExpress_API bool_t kdrive_ap_is_group_read(const uint8_t telegram[], uint32_t telegram_len);

/*!
	Determines if the specified telegram is a GroupValue_Response telegram
	\param [in] telegram the KNX telegram
	\param [in] telegram_len the length of the KNX telegram
	\return true if a GroupValue_Response telegram false otherwise
	\ingroup kdrive_express_access
*/
kdriveExpress_API bool_t kdrive_ap_is_group_response(const uint8_t telegram[], uint32_t telegram_len);

/*!
	Extracts the Group Value data from the KNX telegram.
	If the telegram is not a GroupValue_Write or GroupValue_Response telegram
	an Invalid Telegram error is returned.
	The data buffer should be large enough to hold the data from the telegram.
	This length is checked against the length held in the telegram and if insufficient
	an Access Port Error is returned (Buffer Overflow).
	\param [in] telegram the KNX Telegram (Group Value Telegram)
	\param [in] telegram_len the length of the telegram
	\param [out] data The data buffer
	\param [in,out] data_len the data buffer capacity (in) and actual length of the data buffer (out)
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_group_data(const uint8_t telegram[],
        uint32_t telegram_len, uint8_t* data, uint32_t* data_len);

/*!
	Determines if the group value size is compressed (6 bits or less).
	If the telegram is not a GroupValue_Write or GroupValue_Response telegram
	an Invalid Telegram error is returned.
	\param [in] telegram the KNX Telegram (Group Value Telegram)
	\param [in] telegram_len the length of the telegram
	\param [out] is_commpressed 1 : compressed (6 bits or less) or 0 : not compressed (>= 1 byte)
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_is_compressed_group_data(const uint8_t telegram[],
        uint32_t telegram_len, bool_t* is_commpressed);

/*******************************
** Access Port Properties
********************************/

/*!
	Gets the Layer of the Local Device (KNX Interface Device)
	The default value is Link Layer.
	\param [in] ap the access port descriptor
	\param [out] layer the KNX layer of the local device
	\ingroup kdrive_express_access
	\see kdrive_ap_set_ind_addr
*/
kdriveExpress_API error_t kdrive_ap_get_layer(int32_t ap, uint16_t* layer);

/*!
	Sets the Layer of the Local Device (KNX Interface Device)
	\note Only available in the Commercial Access kdriveExpress SDK
	\param [in] ap the access port descriptor
	\param [in] layer the KNX layer of the local device
	KDRIVE_LAYER_LINK, KDRIVE_LAYER_BUSMON or KDRIVE_LAYER_RAW
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_set_layer(int32_t ap, uint16_t layer);

/*!
	Gets the Individual Address of the Local Device (KNX Interface Device)
	\param [in] ap the access port descriptor
	\param [out] address the individual address of the local device
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_ind_addr(int32_t ap, uint16_t* address);

/*!
	Sets the Individual Address of the Local Device (KNX Interface Device)
	\param [in] ap the access port descriptor
	\param [in] address the individual address of the local device
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_set_ind_addr(int32_t ap, uint16_t address);

/*!
	Gets the Domain Address of the Local Device (KNX Interface Device)
	\param [in] ap the access port descriptor
	\param [out] da the domain address of the local device
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_rf_domain_addr(int32_t ap, uint8_t da[KDRIVE_DA_LEN]);

/*!
	Sets the Domain Address of the Local Device (KNX Interface Device)
	\param [in] ap the access port descriptor
	\param [in] da the new domain address of the local device
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_set_rf_domain_addr(int32_t ap, const uint8_t da[KDRIVE_DA_LEN]);

/*!
	Gets the Serial Number of the Local Device (KNX Interface Device)
	\param [in] ap the access port descriptor
	\param [out] sn the serial number of the local device
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_serial_no(int32_t ap, uint8_t sn[KDRIVE_SN_LEN]);

/*!
	Sets the Serial Number of the Local Device (KNX Interface Device)
	\param [in] ap the access port descriptor
	\param [in] sn the new serial number of the local device
	\ingroup kdrive_express_access
	\note Normally the serial number is write protected. Only some interfaces for testing are support writing.
*/
kdriveExpress_API error_t kdrive_ap_set_serial_no(int32_t ap, const uint8_t sn[KDRIVE_SN_LEN]);

/*!
	Gets the used Individual Address of the tunnel connection (KNX Interface Device).
	This address is the device address PID_KNX_INDIVIDUAL_ADDRESS or
	a additional individual address PID_ADDITIONAL_INDIVIDUAL_ADDRESSES (normal case).
	The interface communicates it at the connecting procedure.
	So if somebody changed the additional individual addresses than this value is not up to data!
	\note This function is only for tunneling access ports.
	\param [in] ap the access port descriptor of a tunneling access port
	\param [out] address the used individual address for the tunnel
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_tunnel_ind_addr(int32_t ap, uint16_t* address);

/*!
	Sets the used Individual Address of the tunnel connection (KNX Interface Device).
	Returns an error, if it can not changed because for the tunnel address is the device individual address used.
	\note This function is only for tunneling access ports
	\param [in] ap the access port descriptor of a tunneling access port
	\param [in] address the individual address of the tunnel
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_set_tunnel_ind_addr(int32_t ap, uint16_t address);

/*!
	Gets the Additional Individual Addresses of the Local Device (KNX Interface Device)
	\note This function is only for tunneling access ports
	\param [in] ap the access port descriptor of a tunneling access port
	\param [out] addresses the array of additional individual addresses
	\param [in,out] addresses_len the array capacity (in) and actual length of the array (out)
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_additional_ind_addr(int32_t ap, uint16_t addresses[], uint32_t* addresses_len);

/*!
	Sets the Additional Individual Addresses of the Local Device (KNX Interface Device)
	\note This function is only for tunneling access ports
	\param [in] ap the access port descriptor of a tunneling access port
	\param [out] addresses the array of additional individual addresses
	\param [in] addresses_len the array length
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_set_additional_ind_addr(int32_t ap, const uint16_t addresses[], uint16_t addresses_len);

/*!
	Gets the destination individual address filter setting.
	The default is 1 (filter is enabled).
	\note This function is only for cEMI FT1.2 interfaces.
	\param [in] ap the access port descriptor of a FT1.2 access port
	\param [out] is_enabled 1 if filter is enabled or 0 otherwise
	\ingroup kdrive_express_access
	\see kdrive_ap_set_filter_dest_addr
*/
kdriveExpress_API error_t kdrive_ap_get_filter_dest_addr(int32_t ap, bool_t* is_enabled);

/*!
	Enable or disable filter destination individual address for L-Data.ind telegrams.
	If enabled (=1) than individual addressed telegrams for other destinations will not route.
	Only available for Weinzierl cEMI FT1.2 Interface.
	The other interfaces filter the individual address already self in the link layer.
	\note This function is only for cEMI FT1.2 interfaces.
	\note Only available in the Commercial Access kdriveExpress SDK
	\param [in] ap the access port descriptor of a FT1.2 access port
	\param [in] enable enable (1) or disable (0) the filter
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_set_filter_dest_addr(int32_t ap, bool_t enable);

/*!
	Gets the rf domain adrress filter setting.
	The default is 1 (filter is enabled).
	\note This function is only for RF interfaces.
	\param [in] ap the access port descriptor
	\param [out] is_enabled 1 if filter is enabled or 0 otherwise
	\ingroup kdrive_express_access
	\see kdrive_ap_set_filter_rf_domain_addr
*/
kdriveExpress_API error_t kdrive_ap_get_filter_rf_domain_addr(int32_t ap, bool_t* is_enabled);

/*!
	Enable or disable filter rf domain address for L-Data.ind telegrams.
	If enabled (=1) than telegrams for other domains will not route.
	Only available, if medium of interface is RF. If it has a other medium nothing happens.
	\note This function is only for RF interfaces.
	\note Only available in the Commercial Access kdriveExpress SDK
	\param [in] ap the access port descriptor
	\param [in] enable enable (1) or disable (0) the filter
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_set_filter_rf_domain_addr(int32_t ap, bool_t enable);

/*!
	Gets the maximum suported apdu length of the Local Device (KNX Interface Device)
	\param [in] ap the access port descriptor
	\param [out] max_apdu_length the maximum apdu length from the interface
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_get_max_apdu_length(int32_t ap, uint32_t* max_apdu_length);

/*******************************
** Packet Trace
********************************/

/*!
	Starts the Packet Trace, for a specific access port.
	When no packet trace callback was set (the default) then it
	write Rx and Tx packets to the logger (level: information),
	otherwise it calls the callback function.
	precondition: the access port is open
	\param [in] ap the access port descriptor
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_packet_trace_connect(int32_t ap);

/*!
	Stops the Packet Trace
	\param [in] ap the access port descriptor
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_packet_trace_disconnect(int32_t ap);

/*!
	Packet Trace callback function type (pointer to function definition)
	\sa kdrive_ap_set_packet_trace_callback
	\param [in] telegram holds the received telegram, the buffer is temporary
	\param [in] telegram_len indicates the length of the telegram
	\param [in] direction the packet direction: KDRIVE_PACKET_DIR_TX (send) or KDRIVE_PACKET_DIR_RX (received)
	\param [in] user_data pointer to user data or NULL
	\ingroup kdrive_express_access
*/
typedef void(*kdrive_ap_packet_trace_callback)(const uint8_t telegram[], uint32_t telegram_len, int32_t direction, void* user_data);

/*!
	Sets the packet trace callback function, for a specific access port.
	This callback function will be called when a packet rx or tx by the Access Port.
	A notification thread is used internally so
	this callback will be in the context of the notification thread
	(and not the main thread). That is, care should be taken when calling
	out from the callback.
	There can only be one callback per access port.
	To remove the callback add an empty callback (0).
	\param [in] ap the access port descriptor
	\param [in] c the packet trace callback pointer to function
	\param [in] user_data (optional) pointer to user data
	\ingroup kdrive_express_access
*/
kdriveExpress_API error_t kdrive_ap_set_packet_trace_callback(int32_t ap, kdrive_ap_packet_trace_callback c, void* user_data);

#ifdef __cplusplus
}
#endif

#endif /* __KDRIVE_EXPRESS_ACCESS_H__ */
