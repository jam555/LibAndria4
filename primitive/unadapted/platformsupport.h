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

#ifndef LIBANDRIA4_BASIC_PLATFORMSUPPORT_H
# define LIBANDRIA4_BASIC_PLATFORMSUPPORT_H
	
	#include <stdio.h>
	
	#include "platformdetect.h"
	
	#include "monads.h"
	
	#if LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS > 32
		#if LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_MSWIN
			typedef __int64 libandria4_foff_t;
		#elif LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_NIX
			typedef off_t libandria4_foff_t;
		#else
			#warning "Unknown platform: ftello/_ftelli64 equivalent not known."
			typedef long libandria4_foff_t;
		#endif
	#else
		typedef long libandria4_foff_t;
	#endif
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE( libandria4_either_fofft_int, libandria4_foff_t, int );
	typedef libandria4_either_fofft_int libandria4_either_fofft;
	#define LIBANDRIA4_EITHER_FOFFT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_either_fofft, libandria4_foff_t, ( val ) )
	#define LIBANDRIA4_EITHER_FOFFT_BUILDERROR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_either_fofft, int, ( val ) )
	#define LIBANDRIA4_EITHER_FOFFT_BODYMATCH( var, succmatch, errmatch ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, succmatch, errmatch )
	#define LIBANDRIA4_EITHER_FOFFT_EXPRMATCH( var, succmatch, errmatch ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, succmatch, errmatch )
	
	typedef struct libandria4_int_errint
	{
		int val, err;
		
	} libandria4_int_errint;
	
		/* origin expects the standard SEEK_SET, SEEK_CUR, and SEEK_END macros from C. */
	libandria4_int_errint libandria4_fseek( FILE *stream, libandria4_either_fofft offset, int origin );
	libandria4_either_fofft libandria4_ftell( FILE *stream );
	
	
	
	int libandria4_endiancheck_islittleendian();
	int libandria4_endiancheck_isbigendian();
	int libandria4_endiancheck_ispdp11endian();
	int libandria4_endiancheck_ishoneywell316endian();
	
#endif
/* End libandria4 basic platformsupport.h */
