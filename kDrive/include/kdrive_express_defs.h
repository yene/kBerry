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

#ifndef __KDRIVE_EXPRESS_DEFS_H__
#define __KDRIVE_EXPRESS_DEFS_H__

#include "kdrive_express_config.h"

/*!
	\file kdrive_express_defs.h
	\brief kdriveExpress Defines
	\author Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
*/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************
** Defines
********************************/

#define KDRIVE_MAX_GROUP_VALUE_LEN		(14)	/*!< The Maximum Length of a Datapoint Value in a GroupValue Telegram */
#define KDRIVE_SN_LEN					(6)		/*!< The Length of a KNX Serial Number */
#define KDRIVE_DA_LEN					(6)		/*!< The Length of a KNX Domain Address */
#define KDRIVE_MAC_LEN					(6)		/*!< The Length of a MAC Address */
#define KDRIVE_INVALID_DESCRIPTOR		(-1)	/*!< Indicates an invalid descriptor */
#define KDRIVE_DPT16_LENGTH				(14)	/*!< The length of a KNX character string for DPT-16 is 112 bits or 14 bytes */
#define KDRIVE_MAX_IP_ADDRESS_LEN		(16)	/*!< The max length of a formated ip address string e.g. 192.168.234.123; (inclusive 1 byte for zero)*/
#define KDRIVE_MAX_DEVICE_NAME_LEN		(121)	/*!< The max length of a device friendly name (30 char); (inclusive 1 byte for zero + max utf8 char)*/

// Message codes
#define KDRIVE_CEMI_L_DATA_REQ			(0x11)	/*!< cEMI message code for L_Data.req */
#define KDRIVE_CEMI_L_DATA_CON			(0x2E)	/*!< cEMI message code for L_Data.con */
#define KDRIVE_CEMI_L_DATA_IND			(0x29)	/*!< cEMI message code for L_Data.ind */

// KNX Layer
#define KDRIVE_LAYER_LINK				(1)		/*!< Link Layer */
#define KDRIVE_LAYER_BUSMON				(2)		/*!< Busmonitor */
#define KDRIVE_LAYER_RAW				(4)		/*!< Raw */

// DPT_Media
#define KDRIVE_MEDIUM_TP				(0x02)	/*!< Medium TP 1 */
#define KDRIVE_MEDIUM_PL				(0x04)	/*!< Medium PL 110 */
#define KDRIVE_MEDIUM_RF				(0x10)	/*!< Medium RF */
#define KDRIVE_MEDIUM_IP				(0x20)	/*!< Medium IP */

// Packet Direction
#define KDRIVE_PACKET_DIR_RX			(0)		/*!< Packet Direction: Rx */
#define KDRIVE_PACKET_DIR_TX			(1)		/*!< Packet Direction: Tx */

/*******************************
** Macros
********************************/

/*!
	converts the length of a byte buffer into length in bits
*/
#define KDRIVE_BITS(length)				((length) * 8)

#ifdef __cplusplus
}
#endif

#endif /* __KDRIVE_EXPRESS_DEFS_H__ */
