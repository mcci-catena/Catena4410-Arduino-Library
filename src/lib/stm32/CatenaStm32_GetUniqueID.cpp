/* GetUniqueID.cpp	Tue Oct 25 2016 02:20:03 tmm */

/*

Module:  GetUniqueID.cpp

Function:
	Catena4410::GetUniqueID()

Version:
	V0.1.0	Tue Oct 25 2016 02:20:03 tmm	Edit level 2

Copyright notice:
	This file copyright (C) 2016 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.

	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation.

Author:
	Terry Moore, MCCI Corporation	October 2016

Revision history:
   0.1.0  Sat Oct 15 2016 22:35:27  tmm
	Module created.

*/

#ifdef ARDUINO_ARCH_STM32

#include <CatenaStm32.h>
#include <stm32l0xx_ll_utils.h>
using namespace McciCatena;

/****************************************************************************\
|
|		Manifest constants & typedefs.
|
|	This is strictly for private types and constants which will not
|	be exported.
|
\****************************************************************************/



/****************************************************************************\
|
|	Read-only data.
|
|	If program is to be ROM-able, these must all be tagged read-only
|	using the ROM storage class; they may be global.
|
\****************************************************************************/



/****************************************************************************\
|
|	VARIABLES:
|
|	If program is to be ROM-able, these must be initialized
|	using the BSS keyword.  (This allows for compilers that require
|	every variable to have an initializer.)  Note that only those
|	variables owned by this module should be declared here, using the BSS
|	keyword; this allows for linkers that dislike multiple declarations
|	of objects.
|
\****************************************************************************/

void CatenaStm32::GetUniqueID(
	UniqueID_buffer_t *pIdBuffer
	)
	{
	uint32_t idWords[4];
	uint8_t *p;

	idWords[0] = HAL_GetDEVID() << 16 | HAL_GetREVID();
	idWords[1] = LL_GetUID_Word0();
	idWords[2] = LL_GetUID_Word1();
	idWords[3] = LL_GetUID_Word2();
	p = pIdBuffer->b;
	for (unsigned i = 0; i < sizeof(idWords) / sizeof(idWords[0]); ++i)
		{
		uint32_t idWord = idWords[i];

		for (unsigned j = 0; j < 4; ++j)
			{
			*p++ = (uint8_t) idWord;
			idWord >>= 8;
			}
		}
	}

#endif // ARDUINO_ARCH_STM32
