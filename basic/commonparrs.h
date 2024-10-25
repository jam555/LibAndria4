/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2019 Jared A. Maddox

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

#ifndef LIBANDRIA4_BASIC_COMMONPARRS_H
# define LIBANDRIA4_BASIC_COMMONPARRS_H
	
	/* Remember to link with commonparrs.c and pascalstring.c */
	
	#include "pascalarray.h"
	
	
		/* size_t and ptrdiff_t. */
	#include <stddef.h>
		/* The uint*_t and int*_t types. */
	#include <stdint.h>
	
	/* The following are pascal arrays for common types.  */
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_short_, short );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_int_, int );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_long_, long );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_voidptr_, void* );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_float_, float );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_double_, double );
	
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_sizet_, size_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_ptrdifft_, ptrdiff_t );
	
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_int8t_, int8_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_int16t_, int16_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_int32t_, int32_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_intptrt_, intptr_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_intmaxt_, intmax_t );
	
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_uint8t_, uint8_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_uint16t_, uint16_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_uint32t_, uint32_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_uintptrt_, uintptr_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_uintmaxt_, uintmax_t );
	
	
		/* For libandria4_char_pascalarray{}, which just has some extras */
		/*  defined for it (various string operations). */
	#include "pascalstring.h"
	
		/* Declares libandria4_charparrptr_pascalarray{}, and matching types */
		/*  for wchar_t and utf32 strings. */
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_charparrptr_, libandria4_char_pascalarray* );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_wcharparrptr_, libandria4_wchar_pascalarray* );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_utf32parrptr_, libandria4_utf32_pascalarray* );
	
#endif
/* End lib4 basic commonparrs.h */
