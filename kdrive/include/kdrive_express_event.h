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

#ifndef __KDRIVE_EXPRESS_EVENT_H__
#define __KDRIVE_EXPRESS_EVENT_H__

#include "kdrive_express_config.h"

/*************************************
 ** Event Codes
 **************************************/

#define KDRIVE_EVENT_ERROR								(0x0000)	/*!<  The error signal is emitted when an error was occurred */

#define KDRIVE_EVENT_OPENING							(0x0001)	/*!< The opening signal is emitted when the port is about to be opened */
#define KDRIVE_EVENT_OPENED								(0x0002)	/*!< The opened signal is emitted when the port was opened */
#define KDRIVE_EVENT_CLOSING							(0x0003)	/*!< The closing signal is emitted when the port is about to be closed */
#define KDRIVE_EVENT_CLOSED								(0x0004)	/*!< The closed signal is emitted when the port was closed */
#define KDRIVE_EVENT_TERMINATED							(0x0005)	/*!< The terminated signal is emitted when the port was closed (internally) on error */

#define KDRIVE_EVENT_KNX_BUS_CONNECTED					(0x0006)	/*!< The knx bus connected signal is emitted when the KNX bus was connected */
#define KDRIVE_EVENT_KNX_BUS_DISCONNECTED				(0x0007)	/*!< The knx bus disconnected signal is emitted when the KNX bus was disconnected */
#define KDRIVE_EVENT_LOCAL_DEVICE_RESET                 (0x0008)	/*!< The local device reset signal is emitted when a KNX reset.ind was received. */

#define KDRIVE_EVENT_TELEGRAM_INDICATION				(0x0009)	/*! A telegram was received from the bus */
#define KDRIVE_EVENT_TELEGRAM_CONFIRM					(0x000A)	/*! A L_Data_Confirm indication was received after sending a telegram */
#define KDRIVE_EVENT_TELEGRAM_CONFIRM_TIMEOUT			(0x000B)	/*! A L_Data_Confirm indication was not received after sending a telegram */

#define KDRIVE_EVENT_INTERNAL_01						(0x000C)	/*! Reserved for internal use */

#ifdef __cplusplus
extern "C" {
#endif

/*!
	Event Callback function type (pointer to function definition)
	\sa kdrive_set_event_callback
	\param [in] ap the access port descriptor
	\param [in] e holds the event
	\param [in] user_data pointer to user data or NULL
*/
typedef void (*kdrive_event_callback)(int32_t ap, uint32_t e, void* user_data);

/*!
	Sets the event callback, for a specific access port.
	This callback function will be called when an event occurred
	by the Access Port. A notification thread is used internally so
	this callback will be in the context of the notification thread
	(and not the main thread). That is, care should be taken when calling
	out from the callback.
	There can only be one callback per access port.
	To remove the callback add an empty callback (0).
	\param [in] ap the access port descriptor
	\param [in] c the event callback pointer to function
	\param [in] user_data (optional) pointer to user data
*/
kdriveExpress_API error_t kdrive_set_event_callback(int32_t ap, kdrive_event_callback c, void* user_data);

#ifdef __cplusplus
}
#endif

#endif /* __KDRIVE_EXPRESS_EVENT_H__ */
