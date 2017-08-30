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

#ifndef __KDRIVE_EXPRESS_UTILS_H__
#define __KDRIVE_EXPRESS_UTILS_H__

#include "kdrive_express_config.h"
#include "kdrive_express_defs.h"

/*!
	\file kdrive_express_utils.h
	\brief kdriveExpress Utils API
	\author Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
	\defgroup kdrive_express_access kdriveExpress Access API
*/

#ifdef __cplusplus
extern "C" {
#endif

/*!
	Converts telegram emi1 (in EMI1 format) into teletgram cemi (in Common EMI format)
	\param emi1 the emi1 telegram
	\param emi1_len the length of the emi1 telegram
	\param cemi a buffer to hold the converted CEMI telegram
	\param cemi_len holds the max size of cemi [in] and returns the acutal length of cemi [out]
*/
kdriveExpress_API error_t kdrive_utils_emi1_to_cemi(const uint8_t emi1[], uint32_t emi1_len,
        uint8_t cemi[], uint32_t* cemi_len);

#ifdef __cplusplus
}
#endif

#endif /* __KDRIVE_EXPRESS_UTILS_H__ */
