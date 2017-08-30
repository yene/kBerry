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

#ifndef __KDRIVE_EXPRESS_SERVICES_H__
#define __KDRIVE_EXPRESS_SERVICES_H__

#include "kdrive_express_config.h"
#include "kdrive_express_defs.h"

/*!
	\file kdrive_express_services.h
	\brief kdriveExpress Services API
	\author Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
	\defgroup kdrive_express_services kdriveExpress Services API
*/

#if KDRIVE_EXPRESS_SERVICES_INCLUDED == 1

#define KDRIVE_LOAD_STATE_ADDITIONAL_INFO_LEN (9) /*!< The length of the additional info in a A_LoadSate_Write service */

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************
** Init
***************************************************************/

/*!
	Creates an internal ServicePort interface
	This should be the first function called when
	working with the services library. It creates a
	unique service port descriptor which will be passed to all
	kdrive services functions. When finished, call kdrive_sp_release.
	If create fails the function returns KDRIVE_INVALID_DESCRIPTOR
	\param [in] ap the access port descriptor
	\return service port descriptor if succesful
	\ingroup kdrive_express_services
*/
kdriveExpress_API int32_t kdrive_sp_create(int32_t ap);

/*!
	Releases the ServicePort interface.
	This should be the last function called when
	working with the services library.
	Returns true if successfully released
	false otherwise (i.e. the descriptor wasn't found).
	\param [in] sp the service port descriptor
	\ingroup kdrive_express_services
*/
kdriveExpress_API bool_t kdrive_sp_release(int32_t sp);

/**************************************************************
** Device Services: Response Timeout
***************************************************************/

/*!
	Sets the response timeout. If the parameter timeout is 0 than use the service specific default timeout.
	\note For normal usage this timeout haven't be edit.
	\param [in] sp the service port descriptor
	\param [in] timeout response timeout in ms. 0 means use service specific default timeout
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_set_response_timeout(int32_t sp, uint32_t timeout);

/*!
	Gets the response timeout.
	\param [in] sp the service port descriptor
	\param [out] timeout response timeout in ms. 0 means use service specific default timeout
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_get_response_timeout(int32_t sp, uint32_t* timeout);

/**************************************************************
** Device Services: Connection-oriented
***************************************************************/

/*!
	Sets whether the device services are run as connection-oriented or
	connection-less. The default is connection-less.
	\param [in] sp the service port descriptor
	\param [in] connection_oriented 1: connection-oriented 0: connection-less
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_set_co(int32_t sp, bool_t connection_oriented);

/*!
	Returns whether the device services are run as connection-oriented or
	connection-less. If there is an error, i.e. the service port sp doesn't exist
	the function will return 0.
	\param [in] sp the service port descriptor
	\ingroup kdrive_express_services
*/
kdriveExpress_API bool_t kdrive_sp_is_co(int32_t sp);

/**************************************************************
** Device Services: Max APDU length (for long frames support)
***************************************************************/

/*!
	Sets the maximum apdu length for device services. The default is 15 (standard frame).
	\note For normal usage this define haven't be edit.
	\param [in] sp the service port descriptor
	\param [in] max_apdu_length the maximum apdu length which supports the interface and device
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_set_max_apdu_length(int32_t sp, uint32_t max_apdu_length);

/*!
	Gets the maximum apdu length for device services.
	\param [in] sp the service port descriptor
	\param [out] max_apdu_length the set device services maximum apdu length
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_get_max_apdu_length(int32_t sp, uint32_t* max_apdu_length);

/**************************************************************
** Device Service: DeviceDescriptorType0Read
***************************************************************/

/*!
	Reads device descriptor 0 (mask version) from a device
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [out] mask_version mask version
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_device_descriptor_type0_read(int32_t sp, uint16_t ind_addr,
        uint16_t* mask_version);

/**************************************************************
** Device Service: DeviceDescriptorType2Read
***************************************************************/

/*!
	Structure holding device descriptor 2 (easy channel information)
	\see kdrive_sp_device_descriptor_type2_read
	\ingroup kdrive_express_services
*/
typedef struct device_descriptor_type2_t
{
	uint16_t manufacturer; /*!< application manufacturer Code */
	uint16_t app_id; /*!< application id */
	uint8_t app_ver; /*!< application version */
	uint8_t mgmt_profile; /*!< management profile */
	uint8_t ch_count_a; /*!< channel count type A */
	uint16_t ch_code_a; /*!< channel code type A */
	uint8_t ch_count_b; /*!< channel count type B */
	uint16_t ch_code_b; /*!< channel code type B */
	uint8_t ch_count_c; /*!< channel count type C */
	uint16_t ch_code_c; /*!< channel code type C */
	uint8_t ch_count_d; /*!< channel count type D */
	uint16_t ch_code_d; /*!< channel code type D */

} device_descriptor_type2_t;

/*!
	Reads device descriptor 2 (easy channel information) from a device
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [out] desc struct with the data from the device descriptor 2
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_device_descriptor_type2_read(int32_t sp,
        uint16_t ind_addr, device_descriptor_type2_t* desc);

/**************************************************************
** Device Service: RestartDeviceType0
***************************************************************/

/*!
	Restarts the device using restart (type 0)
	There is no response to this telegram so it is not possible to know when the device is ready.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_restart_device_type0(int32_t sp, uint16_t ind_addr);

/**************************************************************
** Device Service: RestartDeviceType1
***************************************************************/

/*!
	Restarts the device using restart (type 1)
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] erase_code erase code
	\param [in] channel_number channel number
	\param [out] error_code error code
	\param [out] process_time process time
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_restart_device_type1(int32_t sp,
        uint16_t ind_addr,
        uint8_t erase_code,
        uint8_t channel_number,
        uint8_t* error_code,
        uint16_t* process_time);

/**************************************************************
** Device Service: PropertyDescriptionRead
***************************************************************/

/*!
	Structure holding a property description
	\see kdrive_sp_property_description_read
	\ingroup kdrive_express_services
*/
typedef struct property_description_t
{
	uint8_t prop_id; /*!< property id */
	uint8_t prop_index; /*!< property index */
	bool_t write_enable; /*!< is write enable */
	uint8_t type; /*!< type */
	uint16_t max_nr_of_elems; /*!< max number of elements */
	uint8_t read_level; /*!< read access level */
	uint8_t write_level; /*!< write access level */

} property_description_t;

/*!
      Reads a property description from a device
      \note Only available in the Commercial kdriveExpress SDK
	  \param [in] sp the service port descriptor
      \param [in] ind_addr individual address
      \param [in] object_index object index
      \param [in] prop_id property iD
      \param [in] prop_index property index
      \param [out] property_description property description (write enabled, read level, ...)
      \return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
      \ingroup kdrive_express_services
 */
kdriveExpress_API error_t kdrive_sp_property_description_read(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t prop_id,
        uint8_t prop_index,
        property_description_t* property_description);

/**************************************************************
** Device Service: PropertyValueRead
***************************************************************/

/*!
	Reads a property value from a device
	The data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the property value to be read.
	The max size of the buffer must be passed in as data_length.
	data_length will be updated to correspond to the length of the value read.
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] object_index Object Index
	\param [in] prop_id Property ID
	\param [in] nr_of_elems Element Count
	\param [in] start_index Start Index
	\param [out] data the property value read from the device
	\param [in,out] data_length the data array capacity (in) and actual length of the data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_prop_value_read(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t prop_id,
        uint8_t nr_of_elems,
        uint16_t start_index,
        uint8_t data[],
        uint32_t* data_length);

/**************************************************************
** Device Service: PropertyValueWrite
***************************************************************/

/*!
	Writes the value of a property to a device
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] object_index object index
	\param [in] prop_id property id
	\param [in] nr_of_elems element count
	\param [in] start_index start index
	\param [in] data the data array
	\param [in] data_length the length of the data array
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_prop_value_write(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t prop_id,
        uint8_t nr_of_elems,
        uint16_t start_index,
        const uint8_t data[],
        uint32_t data_length);

/*!
	Writes the value of a property to a device.
	This function do not verify the field data from the A_PropertyValue_Response.
	The output_data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the output value of the response
	(normally the same size as the input_data_length).
	The max size of the buffer must be passed in as output_data_length.
	output_data_length will be updated to correspond to the length of the value response.
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] object_index object index
	\param [in] prop_id property id
	\param [in] nr_of_elems element count
	\param [in] start_index start index
	\param [in] input_data the input data array
	\param [in] input_data_length the length of the input_data array
	\param [out] output_data the output data (from the response)
	\param [in,out] output_data_length the output_data array capacity (in) and actual length of the output_data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_prop_value_write_without_verify(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t prop_id,
        uint8_t nr_of_elems,
        uint16_t start_index,
        const uint8_t input_data[],
        uint32_t input_data_length,
        uint8_t output_data[],
        uint32_t* output_data_length);

/**************************************************************
** Device Service: FunctionPropertyCommand
***************************************************************/

/*!
	Calls a function property of an interface object in a device.
	The output_data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the output value of the function response.
	The max size of the buffer must be passed in as output_data_length.
	output_data_length will be updated to correspond to the length of the value response.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] object_index object index
	\param [in] prop_id property id
	\param [in] input_data the function specific input data
	\param [in] input_data_length the length of the input_data array
	\param [out] return_code return code
	\param [out] output_data the function specific output data
	\param [in,out] output_data_length the output_data array capacity (in) and actual length of the output_data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_function_property_command(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t prop_id,
        const uint8_t input_data[],
        uint32_t input_data_length,
        uint8_t* return_code,
        uint8_t output_data[],
        uint32_t* output_data_length);

/**************************************************************
** Device Service: FunctionPropertyStateRead
***************************************************************/

/*!
	Calls a function property of an interface object in a device.
	The output_data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the output value of the function response.
	The max size of the buffer must be passed in as output_data_length.
	output_data_length will be updated to correspond to the length of the value response.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] object_index object index
	\param [in] prop_id property id
	\param [in] input_data the function specific input data
	\param [in] input_data_length the length of the input_data array
	\param [out] return_code return code
	\param [out] output_data the function specific output data
	\param [in,out] output_data_length the output_data array capacity (in) and actual length of the output_data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_function_property_state_read(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t prop_id,
        const uint8_t input_data[],
        uint32_t input_data_length,
        uint8_t* return_code,
        uint8_t output_data[],
        uint32_t* output_data_length);

/**************************************************************
** Device Service: MemoryRead
***************************************************************/

/*!
	Reads data via DMA.
	The data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the property value to be read.
	The max size of the buffer must be passed in as data_length.
	data_length will be updated to correspond to the length of the value read.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] memory_addr start memory address
	\param [in] number number of octect to be read
	\param [out] data the memory data read from the device
	\param [in,out] data_length the data array capacity (in) and actual length of the data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_memory_read(int32_t sp,
        uint16_t ind_addr,
        uint16_t memory_addr,
        uint8_t number,
        uint8_t data[],
        uint32_t* data_length);

/**************************************************************
** Device Service: MemoryWrite
***************************************************************/

/*!
	Writes data via DMA.
	The field data from the A_Memory_Response will verify with the field data from the A_Memory_Write.
	\see kdrive_sp_memory_write
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] memory_addr start memory address
	\param [in] data the data array
	\param [in] data_length the length of the data array
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_memory_write(int32_t sp,
        uint16_t ind_addr,
        uint16_t memory_addr,
        const uint8_t data[],
        uint32_t data_length);

/*!
	Writes data via DMA.
	This service do not verify the field data from the A_Memory_Response.
	The output_data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the output value of the response
	(normally the same size as the input_data_length).
	The max size of the buffer must be passed in as output_data_length.
	output_data_length will be updated to correspond to the length of the value response.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] memory_addr start memory address
	\param [in] input_data the input data array
	\param [in] input_data_length the length of the input_data array
	\param [out] output_data the output data (from the response)
	\param [in,out] output_data_length the output_data array capacity (in) and actual length of the output_data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_memory_write_without_verify(int32_t sp,
        uint16_t ind_addr,
        uint16_t memory_addr,
        const uint8_t input_data[],
        uint32_t input_data_length,
        uint8_t output_data[],
        uint32_t* output_data_length);

/**************************************************************
** Device Service: UserMemoryRead
***************************************************************/

/*!
	Reads data via DMA.
	The data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the property value to be read.
	The max size of the buffer must be passed in as data_length.
	data_length will be updated to correspond to the length of the value read.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] memory_addr start memory address
	\param [in] number number of octect to be read
	\param [out] data the memory data read from the device
	\param [out] data_length the data array capacity (in) and actual length of the data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_user_memory_read(int32_t sp,
        uint16_t ind_addr,
        uint16_t memory_addr,
        uint8_t number,
        uint8_t data[],
        uint32_t* data_length);

/**************************************************************
** Device Service: UserMemoryWrite
***************************************************************/

/*!
	Writes data via DMA.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] memory_addr start memory address
	\param [in] data the data array
	\param [in] data_length the length of the data array
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_user_memory_write(int32_t sp,
        uint16_t ind_addr,
        uint16_t memory_addr,
        const uint8_t data[],
        uint32_t data_length);

/*!
	Writes data via DMA.
	This service do not verify the field data from the A_UserMemory_Response.
	The output_data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the output value of the response
	(normally the same size as the input_data_length).
	The max size of the buffer must be passed in as output_data_length.
	output_data_length will be updated to correspond to the length of the value response.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] memory_addr start memory address
	\param [in] input_data the input data array
	\param [in] input_data_length the length of the input_data array
	\param [out] output_data the output data (from the response)
	\param [in,out] output_data_length the output_data array capacity (in) and actual length of the output_data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_user_memory_write_without_verify(int32_t sp,
        uint16_t ind_addr,
        uint16_t memory_addr,
        const uint8_t input_data[],
        uint32_t input_data_length,
        uint8_t output_data[],
        uint32_t* output_data_length);

/**************************************************************
** Device Service: AuthorizeRequest
***************************************************************/

/*!
	Sends an authorize request
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] key authorize key
	\param [out] level access level
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_authorize_request(int32_t sp,
        uint16_t ind_addr,
        uint32_t key,
        uint8_t* level);

/**************************************************************
** Device Service: KeyWrite
***************************************************************/

/*!
	Writes an authorization key
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] key authorize key
	\param [in,out] level requested access level (in) and reponsed access level (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_key_write(int32_t sp,
        uint16_t ind_addr,
        uint32_t key,
        uint8_t* level);

/**************************************************************
** Device Service: IsIndividualAddressFree
***************************************************************/

/*!
	Checks if the given individual address is free (not used by a device on the bus)
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [out] is_free 1 when the address is not used otherwise 0
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_is_ind_addr_free(int32_t sp,
        uint16_t ind_addr,
        bool_t* is_free);

/**************************************************************
** Device Service: LoadStateRead
***************************************************************/

/*!
	Reads the load state via PropertyValueRead (PID_LOAD_STATE_CONTROL).
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] object_index object index
	\param [out] load_state load state
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_load_state_read(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t* load_state);

/**************************************************************
** Device Service: LoadStateWrite
***************************************************************/

/*!
	Writes the load state via PropertyValueWrite (PID_LOAD_STATE_CONTROL).
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] object_index object index
	\param [in] load_event load event
	\param [out] load_state load state
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_load_state_write(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t load_event,
        uint8_t* load_state);

/*!
	Writes the load state via PropertyValueWrite (PID_LOAD_STATE_CONTROL).
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] object_index object index
	\param [in] load_event load event
	\param [in] additional_info additional load information
	\param [out] load_state load state
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_load_state_write_ex(int32_t sp,
        uint16_t ind_addr,
        uint8_t object_index,
        uint8_t load_event,
        const uint8_t additional_info[KDRIVE_LOAD_STATE_ADDITIONAL_INFO_LEN],
        uint8_t* load_state);

/**************************************************************
** Device Service: ReadProgMode
***************************************************************/

/*!
	Reads the current programming mode.
	Try it PropertyBased and if this was failed than try it MemoryMapped.
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [out] enabled Is the programming mode enabled
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
	\sa kdrive_sp_read_prog_mode_property_based and kdrive_sp_read_prog_mode_memory_mapped
*/
kdriveExpress_API error_t kdrive_sp_read_prog_mode(int32_t sp,
        uint16_t ind_addr,
        bool_t* enabled);

/*!
	Reads the current programming mode via PropertyValueRead. PID_PROG_MODE
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [out] enabled Is the programming mode enabled
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
	\sa kdrive_sp_read_prog_mode
*/
kdriveExpress_API error_t kdrive_sp_read_prog_mode_property_based(int32_t sp,
        uint16_t ind_addr,
        bool_t* enabled);

/*!
	Reads the current programming mode via MemoryRead. Memory Address 0x0060
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [out] enabled Is the programming mode enabled
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
	\sa kdrive_sp_read_prog_mode
*/
kdriveExpress_API error_t kdrive_sp_read_prog_mode_memory_mapped(int32_t sp,
        uint16_t ind_addr,
        bool_t* enabled);

/**************************************************************
** Device Service: SwitchProgMode
***************************************************************/

/*!
	Enable / Disable the programming mode (switches the learn
	LED). Try it PropertyBased and if this was failed than try it MemoryMapped.
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] enable Enable programming mode
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
	\sa kdrive_sp_switch_prog_mode_property_based and kdrive_sp_switch_prog_mode_memory_mapped
*/
kdriveExpress_API error_t kdrive_sp_switch_prog_mode(int32_t sp,
        uint16_t ind_addr,
        bool_t enable);

/*!
	Enable / Disable the programming mode (switches the learn
	LED). Reads the current value via service
	PropertyValueRead and writes the new value via PropertyValueWrite. PID_PROG_MODE
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] enable Enable programming mode
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
	\sa kdrive_sp_switch_prog_mode
*/
kdriveExpress_API error_t kdrive_sp_switch_prog_mode_property_based(int32_t sp,
        uint16_t ind_addr,
        bool_t enable);

/*!
	Enable / Disable the programming mode (switches the learn
	LED). Reads the current value via service
	MemoryRead and writes the new value via MemoryWrite. Memory Address 0x0060
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] enable Enable programming mode
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
	\sa kdrive_sp_switch_prog_mode
*/
kdriveExpress_API error_t kdrive_sp_switch_prog_mode_memory_mapped(int32_t sp,
        uint16_t ind_addr,
        bool_t enable);

/**************************************************************
** Device Service: MemoryBlockRead
***************************************************************/

/*!
	Reads a contiguous memory block via DMA.

	The data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the memory block to be read.
	The max size of the buffer must be passed in as data_length.
	data_length will be updated to correspond to the length of the memory read.

	The service supports the reading of blocks where the exact start and end address in unknown.<br>
	For example, we want to read from 0x4000 and read 512 bytes.<br>
	The following cases are possible:<br>

	- The entire memory range is valid.<br>
	  Return memory_addr of 0x4000, data_length of 512, and memory buffer.

	- The start address and less than 512 bytes are valid (for example, 32 bytes).<br>
	  Return memory_addr of 0x4000 and data_length of 32 bytes, with the corresponding buffer.<br>
	  Note: There could be additional valid memory blocks in the range 0x4020 to 0x4200 and these
	  can be "discovered" with subsequent reads, see next case.

	- The start address is not valid.<br>
	  Return the first valid memory block in the range.

	- There are no valid memory blocks in the range.<br>
	  Return data_length of 0 and an empty buffer. The return address in this case is undefined.

	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in,out] memory_addr start memory address (in), start address of the first valid data (out)
	\param [in] number number of octect to be read
	\param [out] data the memory data read from the device
	\param [in,out] data_length the data array capacity (in) and actual length of the data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_memory_block_read(int32_t sp,
        uint16_t ind_addr,
        uint16_t* memory_addr,
        uint8_t number,
        uint8_t data[],
        uint32_t* data_length);

/**************************************************************
** Device Service: MemoryBlockWrite
***************************************************************/

/*!
	Writes a contiguous memory block via DMA.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] ind_addr individual address
	\param [in] memory_addr start memory address
	\param [in] data the data array
	\param [in] data_length the length of the data array
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_memory_block_write(int32_t sp,
        uint16_t ind_addr,
        uint16_t memory_addr,
        const uint8_t data[],
        uint32_t data_length);

/**************************************************************
** Broadcast Service: IndividualAddressProgModeRead
***************************************************************/

/*!
	Reads the individual addresses of devices in Programming Mode
	(i.e. with the Learn LED enabled)
	The data buffer must exist (should be pre-allocated by the user) and its size
	should be equal to or greater than the number of individual addresses to be read.
	The max number of elements in data (its capacity) must be passed in as data_length.
	data_length will be updated to correspond to the actual number of elements written.
	\param [in] sp the service port descriptor
	\param [in] wait_time the time to wait in milliseconds for all responses, i.e. 500ms or so
	\param [out] data the array of individual addresses generated by the service
	\param [in,out] data_length the data array capacity (in) and actual length of the data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_ind_addr_prog_mode_read(int32_t sp,
        uint32_t wait_time,
        uint16_t data[],
        uint32_t* data_length);

/**************************************************************
** Broadcast Service: IndividualAddressProgModeWrite
***************************************************************/

/*!
	Writes the specified individual address to a device in Programming Mode
	(i.e. with the Learn LED enabled)
	This function validates that there is only one device in programming mode
	and verifies that the individual address was successfully written
	\param [in] sp the service port descriptor
	\param [in] new_ind_addr the individual address that is written to the device
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_ind_addr_prog_mode_write(int32_t sp, uint16_t new_ind_addr);

/**************************************************************
** Broadcast Service: IndividualAddressSerialNumberRead
***************************************************************/

/*!
	Reads the individual address of a device that matches the specified Serial Number
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] sn the KNX Serial Number of the device to be addressed
	\param [out] ind_addr the individual address (if found) of the corresponding device
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_ind_addr_sn_read(int32_t sp,
        const uint8_t sn[KDRIVE_SN_LEN],
        uint16_t* ind_addr);

/**************************************************************
** Broadcast Service: IndividualAddressSerialNumberWrite
***************************************************************/

/*!
	Writes the individual address of a device that matches the specified Serial Number
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] sn the KNX Serial Number of the device to be addressed
	\param [in] new_ind_addr the individual address that is written to the device
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_ind_addr_sn_write(int32_t sp,
        const uint8_t sn[KDRIVE_SN_LEN],
        uint16_t new_ind_addr);

/**************************************************************
** Broadcast Service: NetworkParameterWriteBroadcast
***************************************************************/

/*!
	Writes a parameter with the NetworkParameterWriteBroadcast service.
	Sends the service as broadcast.
	\note Only available in the Commercial kdriveExpress SDK
	\see kdrive_sp_network_param_write_systembroadcast
	\param [in] sp the service port descriptor
	\param [in] object_type the object type
	\param [in] prop_id the property id
	\param [in] data the data to write
	\param [in] data_length the length of the data to write
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_network_param_write_broadcast(int32_t sp,
        uint16_t object_type,
        uint8_t prop_id,
        const uint8_t data[],
        uint32_t data_length);

/**************************************************************
** System Broadcast Service: NetworkParameterWriteBroadcast
***************************************************************/

/*!
	Writes a parameter with the NetworkParameterWriteBroadcast service.
	Sends the service as system broadcast.
	\note Only available in the Commercial kdriveExpress SDK
	\see kdrive_sp_network_param_write_broadcast
	\param [in] sp the service port descriptor
	\param [in] object_type the object type
	\param [in] prop_id the property id
	\param [in] data The data to write
	\param [in] data_length the length of the data to write
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_network_param_write_systembroadcast(int32_t sp,
        uint16_t object_type,
        uint8_t prop_id,
        const uint8_t data[],
        uint32_t data_length);

/**************************************************************
** System Broadcast Service: SystemNetworkParameterWrite
***************************************************************/

/*!
	Writes a system parameter with the SystemNetworkParameterWrite service.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] object_type the object type
	\param [in] prop_id the property id
	\param [in] data The data to write
	\param [in] data_length the length of the data to write
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_system_network_param_write(int32_t sp,
        uint16_t object_type,
        uint16_t prop_id,
        const uint8_t data[],
        uint32_t data_length);

/**************************************************************
** System Broadcast Service: SystemNetworkParameterRead
***************************************************************/

/*!
	Structure holding individual address and test info and test result
	for the SystemNetworkParameterRead service. The service returns 0 or more
	of these tuples.
	\see kdrive_sp_system_network_param_read
	\ingroup kdrive_express_services
*/
typedef struct system_network_param_read_t
{
	uint16_t ind_addr; /*!< indiviual address */
	uint8_t test_info_result[10]; /*!< test info and test result */
	uint32_t length;  /*!< the length of test info and test result */

} system_network_param_read_t;

/*!
	Reads system parameter with the SystemNetworkParameterRead service.
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] object_type the object type
	\param [in] prop_id the property id
	\param [in] data The test info to send
	\param [in] data_length the length of the test info to send
	\param [in] wait_time the time to wait in milliseconds for all responses, i.e. 2500ms or so
	\param [out] items the array of (individual address, test info and result) items generated by the service
	\param [in,out] items_length the data array capacity (in) and actual length of the data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_system_network_param_read(int32_t sp,
        uint16_t object_type,
        uint16_t prop_id,
        const uint8_t data[],
        uint32_t data_length,
        uint32_t wait_time,
        system_network_param_read_t items[],
        uint32_t* items_length);

/**************************************************************
** System Broadcast Service: DomainAddressProgModeRead
***************************************************************/

/*!
	Structure holding individual address, serial number, domain address
	for the DomainAddressProgModeRead service. The service returns 0 or more
	of these tuples.
	\see kdrive_sp_domain_addr_prog_mode_read
	\ingroup kdrive_express_services
*/
typedef struct domain_addr_prog_mode_read_t
{
	uint16_t ind_addr; /*!< indiviual address */
	uint8_t serial_number[KDRIVE_SN_LEN]; /*!< serial number */
	uint8_t domain_address[KDRIVE_DA_LEN]; /*!< domain address */

} domain_addr_prog_mode_read_t;

/*!
	Reads the Domain Addresses of devices in Programming Mode
	(i.e. with the Learn LED enabled)
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] wait_time the time to wait in milliseconds for all responses, i.e. 500ms or so
	\param [out] items the array of (individual address, serial number, domain address) items generated by the service
	\param [in,out] items_length the data array capacity (in) and actual length of the data array (out)
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_domain_addr_prog_mode_read(int32_t sp,
        uint32_t wait_time,
        domain_addr_prog_mode_read_t items[],
        uint32_t* items_length);

/**************************************************************
** System Broadcast Service: DomainAddressProgModeWrite
***************************************************************/

/*!
	Writes the Domain Address to a device in Programming Mode
	(i.e. with the Learn LED enabled)
	This function validates that there is only one device in programming mode
	and verifies that the domain address was successfully written
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] da the new domain address
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_domain_addr_prog_mode_write(int32_t sp, const uint8_t da[KDRIVE_DA_LEN]);

/**************************************************************
** System Broadcast Service: DomainAddressSerialNumberRead
***************************************************************/

/*!
	Reads the Domain Address of a device that matches the specified
	Serial Number
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] sn the serial number
	\param [out] ind_addr the individual address read from the device
	\param [out] da the domain address read from the device
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_domain_addr_sn_read(int32_t sp,
        const uint8_t sn[KDRIVE_SN_LEN],
        uint16_t* ind_addr,
        uint8_t da[KDRIVE_DA_LEN]);

/**************************************************************
** System Broadcast Service: DomainAddressSerialNumberWrite
***************************************************************/

/*!
	Writes the Domain Address of a device
	This function validates that the domain address was successfully written
	\note Only available in the Commercial kdriveExpress SDK
	\param [in] sp the service port descriptor
	\param [in] sn the serial number
	\param [in] da the domain address read from the device
	\return KDRIVE_ERROR_NONE if the service was succesful or the error code if an error was raised
	\ingroup kdrive_express_services
*/
kdriveExpress_API error_t kdrive_sp_domain_addr_sn_write(int32_t sp,
        const uint8_t sn[KDRIVE_SN_LEN],
        const uint8_t da[KDRIVE_DA_LEN]);

#ifdef __cplusplus
}
#endif

#endif /* KDRIVE_EXPRESS_SERVICES_INCLUDED == 1 */
#endif /* __KDRIVE_EXPRESS_SERVICES_H__ */
