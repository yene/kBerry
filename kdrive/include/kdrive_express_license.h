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

#ifndef __KDRIVE_EXPRESS_LICENSE_H__
#define __KDRIVE_EXPRESS_LICENSE_H__

#include "kdrive_express_config.h"

/*!
	\file kdrive_express_license.h
	\brief kdriveExpress License API
	\author Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
	\defgroup kdrive_express_license kdriveExpress License API
*/

/*************************************
 ** Max Lengths
 **************************************/

#define KDRIVE_MAX_LIC_COMPANY_LEN							(50) /*!< The max length of company */
#define KDRIVE_MAX_LIC_STREET_LEN							(40) /*!< The max length of street */
#define KDRIVE_MAX_LIC_CITY_LEN								(40) /*!< The max length of city */
#define KDRIVE_MAX_LIC_COUNTRY_LEN							(40) /*!< The max length of country */

#ifdef __cplusplus
extern "C" {
#endif

/*!
	Sets the commercial license
	If you have a commercial SDK you will have received a license key.
	Simply call this function with your license configuration
	Returns InvalidLicense if the license is not valid

	\code
	error_t set_license()
	{
		char license[] =
			"[Check]\n"
			"Key=I1EkM2JvaE1HMEZtIlF5VnJuJn08KHRfV0AwTlEwRyk4NT55JFNvXnU6ZnpzMDI6QV42JWZ4"
			"fHNed11aOld9WHpGXSEibnkrSDVsZU9WIkljeSQ3NWY7eT4rdEJ6XjhpNnw+OkNEIydTYWNF"
			"RE15JVdQOno3XmtOJjZaRExwLSV8ZXxOYzlJITlhfFFdOHIjUW43SEshfSx8RWgzSipUZU5X"
			"ZiJpSnIhRS9pJyQrOis/VVAoSHMkaV5kYGFfaFxhJj5peUtdfVBgMGh7K25bITF7OnhdeTQv"
			"NiZlWCt4Nls3S31nLUU2LE1OXmhubGtxY2wqJHMxVDd0Tlg4OGlIUCE=\n"
			"\n"
			"[Customer]\n"
			"City=84508 Burgkirchen / Alz\n"
			"Company=WEINZIERL ENGINEERING GmbH\n"
			"Country=Germany\n"
			"Street=Achatz 3\n"
			"\n"
			"[LicenseData]\n"
			"LicNum=kdrive-2012-05-14\n"
			"LicVersion=71949c2a-be30-4fbe-9c96-d0a617ac6ab8\n"
			"\n"
			"[Limitations]\n"
			"DateLimit=2012-12-31\n"
			"\n"
			"[ProgramFeatures]\n"
			"kdriveAccess=0\n"
			"kdriveServices=0\n";

		return kdrive_lic_set_license(license);
	}
	\endcode
	\param [in] configuration the licence configuration
	\ingroup kdrive_express_license
*/
kdriveExpress_API error_t kdrive_lic_set_license(const char* configuration);

/**************************************************************
** Get Licence details
***************************************************************/

/*!
	\see kdrive_lic_set_license
	\ingroup kdrive_express_license
*/
typedef struct lic_customer_t
{
	char company[KDRIVE_MAX_LIC_COMPANY_LEN]; /*!< Company */
	char street[KDRIVE_MAX_LIC_STREET_LEN]; /*!< Street */
	char city[KDRIVE_MAX_LIC_CITY_LEN]; /*!< City */
	char country[KDRIVE_MAX_LIC_COUNTRY_LEN]; /*!< Country */

} lic_customer_t;

/*!
	Gets customer licence data
	\param [in] customer struct with the licenced customer
	\ingroup kdrive_express_license
*/
kdriveExpress_API error_t kdrive_lic_get_customer(lic_customer_t* customer);

#ifdef __cplusplus
}
#endif

#endif /* __KDRIVE_EXPRESS_LICENSE_H__ */
