/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2025 Jared A. Maddox

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

This grant of rights is subject to two conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

And:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "typeinfo.h"

#if 0
	/* This is an override for things like the CDC Cyber 200 or Intel */
	/*  8051 bit-addressing capabilities. It'll probably never be used. */
	
	#error "Dispatching only currently supports CHAR_BIT!"
	
#elif CHAR_BIT > 32
	#error "CHAR_BIT too large!"
#elif CHAR_BIT > 7
	
	static struct
	{
		lib4_typeinfo_plaintype nchar, uchar, schar;
		
		lib4_typeinfo_plaintype uint_8, uint_16, uint_32;
		
	} type_defs =
	{
		{
			{ lib4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ sizeof( char ) * CHAR_BIT,
				/* alignment */ sizeof( char ) * CHAR_BIT
			}
		},
		{
			{ lib4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ sizeof( signed char ) * CHAR_BIT,
				/* alignment */ sizeof( signed char ) * CHAR_BIT
			}
		},
		{
			{ lib4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ sizeof( unsigned char ) * CHAR_BIT,
				/* alignment */ sizeof( unsigned char ) * CHAR_BIT
			}
		},
		
			/* unsigned least 8 */
		{
			{ lib4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ 8,
				/* alignment */ sizeof( uint_least8_t ) * CHAR_BIT
			}
		},
			/* unsigned least 16 */
		{
			{ lib4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ 16,
				/* alignment */ sizeof( uint_least16_t ) * CHAR_BIT
			}
		},
			/* unsigned least 32 */
		{
			{ lib4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ 32,
				/* alignment */ sizeof( uint_least32_t ) * CHAR_BIT
			}
		}
	};
	
	lib4_typeinfo_stdtypes lib4_typeinfo_stdtypes_platform =
	{
		{
			&( type_defs.nchar ), &( type_defs.uchar ), &( type_defs.schar ),
			&( type_defs.uint_8 ), &( type_defs.uint_16 ), &( type_defs.uint_32 )
		},
		{
			&( type_defs.nchar ), &( type_defs.uchar ), &( type_defs.schar ),
			&( type_defs.uint_8 ), &( type_defs.uint_16 ), &( type_defs.uint_32 )
		}
	};
#else
	#error "CHAR_BIT too small!"
#endif
