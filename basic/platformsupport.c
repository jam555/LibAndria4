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

#include <errno.h>
#include "platformdetect.h"


#if LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS > 32
	#if LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_MSWIN
		#define LIBANDRIA4_FSEEK_FUNCTION _fseeki64
		#define LIBANDRIA4_FTELL_FUNCTION _ftelli64
	#elif LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_NIX
		#define LIBANDRIA4_FSEEK_FUNCTION fseeko
		#define LIBANDRIA4_FTELL_FUNCTION ftello
	#else
		#define LIBANDRIA4_FSEEK_FUNCTION fseek
		#define LIBANDRIA4_FTELL_FUNCTION ftell
	#endif
#else
	#define LIBANDRIA4_FSEEK_FUNCTION fseek
	#define LIBANDRIA4_FTELL_FUNCTION ftell
#endif


#ifdef LIBANDRIA4_FSEEK_INNER
	#define LIBANDRIA4_FSEEK( stream, offset, origin ) \
		LIBANDRIA4_FSEEK_INNER( ( stream ), ( offset ), ( origin ) )
#else
	#define LIBANDRIA4_FSEEK( stream, offset, origin ) \
		LIBANDRIA4_FSEEK_FUNCTION( ( stream ), ( offset ), ( origin ) )
#endif

#ifdef LIBANDRIA4_FTELL_INNER
	#define LIBANDRIA4_FTELL( stream ) LIBANDRIA4_FTELL_INNER( ( stream ) )
#else
	#define LIBANDRIA4_FTELL( stream ) LIBANDRIA4_FTELL_FUNCTION( ( stream ) )
#endif


libandria4_int_errint libandria4_fseek( FILE *stream, libandria4_either_fofft offset, int origin )
{
		/* Used internally. */
	#define libandria4_fseek_ONSUCC( val ) \
		res = LIBANDRIA4_FSEEK( stream, val, origin );
	#define libandria4_fseek_ONERR( val ) \
		ret = (libandria4_int_errint){ -2, val }; errno = err; return( ret );
	
	int res, err = errno;
	errno = 0;
	libandria4_int_errint ret;
	
	LIBANDRIA4_EITHER_FOFFT_BODYMATCH(
		offset,
		
		libandria4_fseek_ONSUCC,
		libandria4_fseek_ONERR
	)
	
	ret = (libandria4_int_errint){ res, errno };
	
	errno = err;
	
	return( ret );
}
libandria4_either_fofft libandria4_ftell( FILE *stream )
{
	libandria4_either_fofft ret;
	libandria4_foff_t res;
	int err = errno;
	errno = 0;
	
	res = LIBANDRIA4_FTELL( stream );
	
	if( res >= 0 )
	{
		ret = LIBANDRIA4_EITHER_FOFFT_BUILDSUCCESS( res );
		
	} else {
		
		ret = LIBANDRIA4_EITHER_FOFFT_BUILDERROR( errno );
	}
	
	errno = err;
	
	return( ret );
}
