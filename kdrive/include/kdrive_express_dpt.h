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

#ifndef __KDRIVE_EXPRESS_DPT_H__
#define __KDRIVE_EXPRESS_DPT_H__

#include "kdrive_express_config.h"
#include "kdrive_express_defs.h"

/*!
	\file kdrive_express_dpt.h
	\brief kdriveExpress Datapoint API
	\author Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
	\defgroup kdrive_express_dpt kdriveExpress Datapoint API

	\verbatim

	|----------|----------|-----------------------------|-------------|---------------|
	|  Id      |  Number  |  Name                       |  SizeInBit  |  Implemented  |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-1    | 1        | 1 bit                       | 1           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-2    | 2        | 1 bit controlled            | 2           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-3    | 3        | 3 bit controlled            | 4           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-4    | 4        | Character                   | 8           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-5    | 5        | 8 bit unsigned value        | 8           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-6    | 6        | 8 bit signed value          | 8           | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-7    | 7        | 2 byte unsigned value       | 16          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-8    | 8        | 2 byte signed value         | 16          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-9    | 9        | 2 byte float value          | 16          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-10   | 10       | Time                        | 24          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-11   | 11       | Date                        | 24          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-12   | 12       | 4 byte unsigned value       | 32          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-13   | 13       | 4 byte signed value         | 32          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-14   | 14       | 4 byte float value          | 32          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-15   | 15       | Entrance access             | 32          | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-16   | 16       | Character string            | 112         | Yes           |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-17   | 17       | Scene Number                | 8           | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-18   | 18       | Scene Control               | 8           | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-19   | 19       | Date Time                   | 64          | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-20   | 20       | 1 byte                      | 8           | use DPT-5/6   |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-217  | 217      | Version                     | 16          | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-219  | 219      | Alarm Info                  | 48          | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	| DPT-222  | 222      | 3x 16-Float Value           | 48          | No            |
	|----------|----------|-----------------------------|-------------|---------------|
	\endverbatim
*/

#define KDRIVE_MAX_DP_TYPE_ID_LEN		(13) /*!< The max length of a datapoint type id */
#define KDRIVE_MAX_DP_TYPE_NAME_LEN		(30) /*!< The max length of a datapoint type name */

#define KDRIVE_DPT1_SIZE_IN_BITS		(1)  /*!< The size in bits of DPT1 */
#define KDRIVE_DPT2_SIZE_IN_BITS		(2)  /*!< The size in bits of DPT2 */
#define KDRIVE_DPT3_SIZE_IN_BITS		(4)  /*!< The size in bits of DPT3 */
#define KDRIVE_DPT4_SIZE_IN_BITS		(8)  /*!< The size in bits of DPT4 */
#define KDRIVE_DPT5_SIZE_IN_BITS		(8)  /*!< The size in bits of DPT5 */
#define KDRIVE_DPT6_SIZE_IN_BITS		(8)  /*!< The size in bits of DPT6 */
#define KDRIVE_DPT7_SIZE_IN_BITS		(16) /*!< The size in bits of DPT7 */
#define KDRIVE_DPT8_SIZE_IN_BITS		(16) /*!< The size in bits of DPT8 */
#define KDRIVE_DPT9_SIZE_IN_BITS		(16) /*!< The size in bits of DPT9 */
#define KDRIVE_DPT10_SIZE_IN_BITS		(24) /*!< The size in bits of DPT10 */
#define KDRIVE_DPT11_SIZE_IN_BITS		(24) /*!< The size in bits of DPT11 */
#define KDRIVE_DPT12_SIZE_IN_BITS		(32) /*!< The size in bits of DPT12 */
#define KDRIVE_DPT13_SIZE_IN_BITS		(32) /*!< The size in bits of DPT13 */
#define KDRIVE_DPT14_SIZE_IN_BITS		(32) /*!< The size in bits of DPT14 */
#define KDRIVE_DPT15_SIZE_IN_BITS		(32) /*!< The size in bits of DPT15 */
#define KDRIVE_DPT16_SIZE_IN_BITS		(112) /*!< The size in bits of DPT16 */

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************
** Datapoint
***************************************************************/

/*!
	Represents a single datapoint type
	\ingroup kdrive_express_dpt
*/
typedef struct datapoint_type_t
{
	char id[KDRIVE_MAX_DP_TYPE_ID_LEN]; /*! datapoint type id e.g. "DPT-1" */
	char name[KDRIVE_MAX_DP_TYPE_NAME_LEN]; /*!< datapoint type name e.g. "DPT_Switch" */
	int32_t size_in_bit; /*!< the data size in bits */

} datapoint_type_t;

/*!
	Returns the datapoint type information associated with a datapoint type id
	\param [in] dpt_id the datapoint type id
	\param [out] dpt_desc the struct with the datapoint type informations
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_get_dpt_descriptor(char* dpt_id, datapoint_type_t* dpt_desc);

/**************************************************************
** Encode and Decode
***************************************************************/

/*!
	Sets DPT-1 (1 bit)
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt1(uint8_t* data,
        uint32_t* length, bool_t value);

/*!
	Gets DPT-1 (1 bit)
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt1(const uint8_t* data,
        uint32_t length, bool_t* value);

/*!
	Sets DPT-2: 1 bit controlled
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] control the value written to the data buffer
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt2(uint8_t* data,
        uint32_t* length, bool_t control, bool_t value);

/*!
	Gets DPT-2: 1 bit controlled
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] control the value extracted from the data buffer
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt2(const uint8_t* data,
        uint32_t length, bool_t* control, bool_t* value);

/*!
	Sets DPT-3: 3 bit controlled
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] control the value written to the data buffer
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt3(uint8_t* data,
        uint32_t* length, bool_t control, uint8_t value);

/*!
	Gets DPT-3: 3 bit controlled
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] control the value extracted from the data buffer
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt3(const uint8_t* data,
        uint32_t length, bool_t* control, uint8_t* value);

/*!
	Sets DPT-4: Character
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] character the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt4(uint8_t* data,
        uint32_t* length, uint8_t character);

/*!
	Gets DPT-4: Character
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] character the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt4(const uint8_t* data,
        uint32_t length, uint8_t* character);

/*!
	Sets DPT-5: 8 bit unsigned value
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt5(uint8_t* data,
        uint32_t* length, uint8_t value);

/*!
	Gets DPT-5: 8 bit unsigned value
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt5(const uint8_t* data,
        uint32_t length, uint8_t* value);

/*!
	Sets DPT-6: 8 bit signed value
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt6(uint8_t* data,
        uint32_t* length, int8_t value);

/*!
	Gets DPT-6: 8 bit signed value
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt6(const uint8_t* data,
        uint32_t length, int8_t* value);

/*!
	Sets DPT-7: 2 byte unsigned value
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt7(uint8_t* data,
        uint32_t* length, uint16_t value);

/*!
	Gets DPT-7: 2 byte unsigned value
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt7(const uint8_t* data,
        uint32_t length, uint16_t* value);

/*!
	Sets DPT-8: 2 byte signed value
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt8(uint8_t* data,
        uint32_t* length, int16_t value);

/*!
	Gets DPT-8: 2 byte signed value
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt8(const uint8_t* data,
        uint32_t length, int16_t* value);

/*!
	Sets DPT-9: 2 byte float value
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt9(uint8_t* data,
        uint32_t* length, float32_t value);

/*!
	Gets DPT-9: 2 byte float value
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt9(const uint8_t* data,
        uint32_t length, float32_t* value);

/*!
	Sets DPT-10: local time
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt10_local(uint8_t* data, uint32_t* length);

/*!
	Sets DPT-10: UTC time
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt10_utc(uint8_t* data, uint32_t* length);

/*!
	Sets DPT-10: time
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] day the day value written to the data buffer
	\param [in] hour the hour value written to the data buffer
	\param [in] minute the minute value written to the data buffer
	\param [in] second the second value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt10(uint8_t* data, uint32_t* length,
        int32_t day, int32_t hour, int32_t minute, int32_t second);

/*!
	Gets DPT-10: time
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [out] day the day value extracted from the data buffer
	\param [out] hour the hour value extracted from the data buffer
	\param [out] minute the minute extracted from the data buffer
	\param [out] second the second extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt10(const uint8_t* data, uint32_t length,
        int32_t* day, int32_t* hour, int32_t* minute, int32_t* second);

/*!
	Sets DPT-11: local date
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt11_local(uint8_t* data, uint32_t* length);

/*!
	Sets DPT-11: UTC date
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt11_utc(uint8_t* data, uint32_t* length);

/*!
	Sets DPT-11: date
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] year the year value written to the data buffer
	\param [in] month the month value written to the data buffer
	\param [in] day the day value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt11(uint8_t* data, uint32_t* length,
        int32_t year, int32_t month, int32_t day);

/*!
	Gets DPT-11: date
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [out] year the year value extracted from the data buffer
	\param [out] month the month value extracted from the data buffer
	\param [out] day the day value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt11(const uint8_t* data, uint32_t length,
        int32_t* year, int32_t* month, int32_t* day);

/*!
	Sets DPT-12: 4 byte unsigned value
	\param [in] data the group value data buffer to be encoded
	\param [in,out] length the length of the group value data buffer (in bytes) (in) and
	the length of the formatted group value data buffer (in bits) (out)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt12(uint8_t* data,
        uint32_t* length, uint32_t value);

/*!
	Gets DPT-12: 4 byte unsigned value
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt12(const uint8_t* data,
        uint32_t length, uint32_t* value);

/*!
	Sets DPT-13: 4 byte signed value
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt13(uint8_t* data,
        uint32_t* length, int32_t value);

/*!
	Gets DPT-13: 4 byte signed value
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt13(const uint8_t* data,
        uint32_t length, int32_t* value);

/*!
	Sets DPT-14: 4 byte float value
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt14(uint8_t* data,
        uint32_t* length, float32_t value);

/*!
	Gets DPT-14: 4 byte float value
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt14(const uint8_t* data,
        uint32_t length, float32_t* value);

/*!
	Sets DPT-15: Entrance access
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] accessCode the accessCode written to the data buffer
	\param [in] error the error written to the data buffer
	\param [in] permission the permission written to the data buffer
	\param [in] direction the direction written to the data buffer
	\param [in] encrypted the encrypted written to the data buffer
	\param [in] index the index written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt15(uint8_t* data, uint32_t* length,
        int32_t accessCode, bool_t error, bool_t permission,
        bool_t direction, bool_t encrypted, int32_t index);

/*!
	Gets DPT-15: Entrance access
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] accessCode the accessCode extracted from the data buffer
	\param [out] error the error extracted from the data buffer
	\param [out] permission the permission extracted from the data buffer
	\param [out] direction the direction extracted from the data buffer
	\param [out] encrypted the encrypted extracted from the data buffer
	\param [out] index the index extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt15(const uint8_t* data, uint32_t length,
        int32_t* accessCode, bool_t* error, bool_t* permission,
        bool_t* direction, bool_t* encrypted, int32_t* index);

/*!
	Sets DPT-16: Character string
	\param [in] data the group value data buffer to be encoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] length the length of the formatted group value data buffer (in bits)
	\param [in] value the value written to the data buffer
	\return success if the datapoint value can be written
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_encode_dpt16(uint8_t* data,
        uint32_t* length, const char value[KDRIVE_DPT16_LENGTH]);

/*!
	Gets DPT-16: Character string
	Note: this string is not null terminated! and is simply the 14 bytes
	from the KNX telegram.
	\param [in] data the group value data buffer to be decoded
	\param [in] length the length of the group value data buffer (in bytes)
	\param [out] value the value extracted from the data buffer
	\return success if the datapoint value can be extracted
	\ingroup kdrive_express_dpt
*/
kdriveExpress_API error_t kdrive_dpt_decode_dpt16(const uint8_t* data,
        uint32_t length, char value[KDRIVE_DPT16_LENGTH]);

#ifdef __cplusplus
}
#endif

#endif /* __KDRIVE_EXPRESS_DPT_H__ */
