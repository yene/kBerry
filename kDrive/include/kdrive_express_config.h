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

#ifndef __KDRIVE_EXPRESS_CONFIG_H__
#define __KDRIVE_EXPRESS_CONFIG_H__

#include "kdrive_express_enabled.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************
** Type Definitions
********************************/

#ifndef KDRIVE_TYPES
#define KDRIVE_TYPES

typedef unsigned char uint8_t;		/*!< 8 bit unsigned char */
typedef unsigned short uint16_t;	/*!< 16 bit unsigned char */
typedef unsigned int uint32_t;		/*!< 32 bit unsigned char */
typedef signed char int8_t;			/*!< 8 bit signed char */
typedef short int16_t;				/*!< 16 bit signed int */
typedef int int32_t;				/*!< 32 bit signed int */
typedef float float32_t;			/*!< 32 bit single precision float */

#endif /* KDRIVE_TYPES */

/*******************************
** Error Type
********************************/

#ifndef KDRIVE_ERROR_TYPE
#define KDRIVE_ERROR_TYPE

typedef int32_t error_t;

#endif /* KDRIVE_ERROR_TYPE */

/*******************************
** Bool Type
********************************/

#ifndef KDRIVE_BOOL_TYPE
#define KDRIVE_BOOL_TYPE

typedef int32_t bool_t;

#endif /* KDRIVE_BOOL_TYPE */

#ifdef __cplusplus
}
#endif

/*******************************
** WIN32 DLL Import Export
********************************/

#if defined(_WIN32) && defined(_DLL)
#if !defined(KDRIVE_EXPRESS_DLL) && !defined(KDRIVE_EXPRESS_STATIC)
#define KDRIVE_EXPRESS_DLL
#endif
#endif

#if defined(_WIN32) && defined(KDRIVE_EXPRESS_DLL)
#if defined(kdriveExpress_EXPORTS)
#define kdriveExpress_API __declspec(dllexport)
#else
#define kdriveExpress_API __declspec(dllimport)
#endif
#endif

#if defined (__GNUC__) && (__GNUC__ >= 4)
#define kdriveExpress_API __attribute__ ((visibility ("default")))
#endif

#if !defined(kdriveExpress_API)
#define kdriveExpress_API
#endif

#endif /* __KDRIVE_EXPRESS_CONFIG_H__ */
