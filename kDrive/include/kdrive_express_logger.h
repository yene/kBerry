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

#ifndef __KDRIVE_EXPRESS_LOGGER_H__
#define __KDRIVE_EXPRESS_LOGGER_H__

#include "kdrive_express_config.h"

/*!
	\file kdrive_express_logger.h
	\brief kdriveExpress Logger API
	\author Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
	\defgroup kdrive_express_logger kdriveExpress Logger API
*/

#define KDRIVE_LOGGER_NONE			(0) /*!< No logger */
#define KDRIVE_LOGGER_FATAL			(1) /*!< A fatal error. The application will most likely terminate. This is the highest priority. */
#define KDRIVE_LOGGER_CRITICAL		(2) /*!< A critical error. The application might not be able to continue running successfully. */
#define KDRIVE_LOGGER_ERROR			(3) /*!< An error. An operation did not complete successfully, but the application as a whole is not affected. */
#define KDRIVE_LOGGER_WARNING		(4) /*!< A warning. An operation completed with an unexpected result. */
#define KDRIVE_LOGGER_NOTICE		(5) /*!< A notice, which is an information with just a higher priority. */
#define KDRIVE_LOGGER_INFORMATION	(6) /*!< An informational message, usually denoting the successful completion of an operation. */
#define KDRIVE_LOGGER_DEBUG			(7) /*!< A debugging message. */
#define KDRIVE_LOGGER_TRACE			(8) /*!< A tracing message. This is the lowest priority. */

#ifdef __cplusplus
extern "C" {
#endif

/*!
	Sets the root logger level
	This is once of:
		- KDRIVE_LOGGER_NONE (turns off logging)
		- KDRIVE_LOGGER_FATAL
		- KDRIVE_LOGGER_CRITICAL
		- KDRIVE_LOGGER_ERROR
		- KDRIVE_LOGGER_WARNING
		- KDRIVE_LOGGER_NOTICE
		- KDRIVE_LOGGER_INFORMATION
		- KDRIVE_LOGGER_DEBUG
		- KDRIVE_LOGGER_TRACE
	Sets the level of the root logger. All loggers that
	are added to this logger inherit this value.
	This should be called before creating the logger
	i.e. via kdrive_logger_console etc
	\param [in] level the logger level
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger_set_level(uint8_t level);

/*!
	Sets the logger to write to the console
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger_console(void);

/*!
	Set the logger to write to a file
	The file is written to the current path
	as logfile_pid where pid is the process id
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger_file(void);

/*!
	Set the logger to write to a specified file
	\param [in] filename the logger filename
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger_file_ex(const char* filename);

/*!
	Set the logger to write to a remote host with the syslog protocol
	\param [in] address the remote host either as IP or IP:PORT
	\param [in] name the target name
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger_syslog(const char* address, const char* name);

/*!
	Logger Callback function type (pointer to function definition)
	\sa kdrive_logger_callback
	\param [in] level the logger level (priority)
	\param [in] message the log message
*/
typedef void(*kdrive_logger_callback)(uint8_t level, const char* message);

/*!
	Set the logger to call a user callback function
	\param [in] c the logger callback pointer to function
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger_set_callback(kdrive_logger_callback c);

/*!
	Writes to the kdrive express logger
	\param [in] level the logger level
	\param [in] message the log message
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger(uint8_t level, const char* message);

/*!
	Writes to the kdrive express logger
	\param [in] level the logger level
	\param [in] fmt the log message with format
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger_ex(uint8_t level, const char* fmt, ...);

/*!
	Logs the given message, followed by the data in buffer.
	The data in buffer is written in canonical hex+ASCII form:
	Offset (4 bytes) in hexadecimal, followed by sixteen
	space-separated, two column, hexadecimal bytes,
	followed by the same sixteen bytes as ASCII characters.
	For bytes outside the range 32 .. 127, a dot is printed.
	\param [in] level the logger level
	\param [in] message the log message
	\param [in] buffer the data array
	\param [in] buffer_len the buffer length
	\ingroup kdrive_express_logger
*/
kdriveExpress_API void kdrive_logger_dump(uint8_t level, const char* message, const void* buffer, uint32_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif /* __KDRIVE_EXPRESS_LOGGER_H__ */
