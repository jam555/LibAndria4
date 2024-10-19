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


#include <time.h>


#include "commonlib.h"
	/* For LIBANDRIA4_RESULT_FAILURE_DOMAIN. */
#include "commonerrvals.h"
#include "simpleops.h"


/* Platform-specific includes. */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include <Windows.h>
	
#elif defined(_POSIX_VERSION) || __unix__ || __linux__ || __QNX__ || __ANDROID__ || __APPLE__
	#include <unistd.h>
	
	#if __APPLE__ && !( TARGET_IPHONE_SIMULATOR || TARGET_OS_MACCATALYST || TARGET_OS_IPHONE )
		#error "commonlib.c libandria4_sleep() encountered an unrecognized Apple platform."
	#endif
	
#else
	#include <time.h>
	
#endif



	/* Works like C's strstr(), but with arbitrary memory patterns. */
	/* Note that the "needle" will only be searched for on needlegrain-sized */
	/*  alignments: this is to allow arbitrarily sized type searches to be */
	/*  performed. */
libandria4_ptrresult libandria4_memmem
(
	void *haystack_, size_t haysize,
	void *needle_, size_t needlesize, size_t needlegrain
)
{
	void *ret = haystack_;
	
	if( haystack_ && needle_ && haysize >= needlesize )
	{
		unsigned char *haystack = (char*)haystack_, *needle = (char*)needle_;
		size_t hoff = 0, noff = 0, goff = 0;
		
		if( needlesize % needlegrain )
		{
			LIBANDRIA4_PTRRESULT_RETURNFAILURE(
				LIBANDRIA4_RESULT_FAILURE_DOMAIN );
		}
		
		while( hoff + needlesize <= haysize )
		{
			while( noff < needlesize &&
				haystack[ hoff + noff + goff ] == needle[ noff + goff ] )
			{
				while( graintest < needlegrain &&
					haystack[ hoff + noff + goff ] == needle[ noff + goff ] )
				{
					++goff;
				}
				if( goff == needlegrain )
				{
					noff += needlegrain;
					goff = 0;
				}
			}
			if( noff == needlesize )
			{
				/* Success. */
				
				LIBANDRIA4_PTRRESULT_RETURNSUCCESS(
					(void*)&( haystack[ hoff ] ) );
			}
			
			hoff += needlegrain;
			noff = 0;
			goff = 0;
		}
		
		/* No match found, fall-through to null. */
	}
	
	LIBANDRIA4_PTRRESULT_RETURNFAILURE( LIBANDRIA4_RESULT_FAILURE_EOF );
}

	/* Reverses the order of the elements in the memory buffer. */
int libandria4_memreverse( void *base_, size_t count, size_t size )
{
	if( base_ && count && size )
	{
		size_t elem = 0, eoff = 0;
		unsigned char tmp, *base = (char*)base_;
		
		while( ( elem * 2 ) + 1 < count )
		{
			while( eoff < size )
			{
				tmp = base[ ( elem * size ) + eoff ];
				base[ ( elem * size ) + eoff ] =
					base[ ( ( count - ( elem + 1 )) * size ) + eoff ];
				base[ ( ( count - ( elem + 1 )) * size ) + eoff ] = tmp;
				
				++eoff;
			}
			
			++elem;
			eoff = 0;
		}
		
		return( 1 );
	}
	
	return( 0 );
}


libandria4_error_mayerr libandria4_error_print_simplestruct
(
	libandria4_commonio_handle *io,
	libandria4_error_simplestruct *err
)
{
	if( io && err )
	{
		if( !libandria4_commonio_handle_hasbasics( io ) )
		{
			LIBANDRIA4_ERROR_MAYERR_RETERR2();
		}
		if( !( io->puts_s ) )
		{
			LIBANDRIA4_ERROR_MAYERR_RETERR3();
		}
		if( !( err->str ) && err->str_len )
		{
			LIBANDRIA4_ERROR_MAYERR_RETERR4();
		}
		
		
		if
		(
			!libandria4_commonio_recursivewrapper_puts_s
			(
				io,  (libandria4_commonio_byte*)( err->str ), err->str_len
			)
		)
		{
			LIBANDRIA4_ERROR_MAYERR_RETERR5();
		}
		
		LIBANDRIA4_ERROR_MAYERR_RETURN_SUCCESS();
	}
	LIBANDRIA4_ERROR_MAYERR_RETERR1();
}
libandria4_error_mayerr libandria4_error_print
(
	libandria4_commonio_handle *io,
		libandria4_error_basalstruct *err,
		int line,
		char *file
)
{
	if( io && err )
	{
		if( !libandria4_commonio_handle_hasbasics( io ) )
		{
			LIBANDRIA4_ERROR_MAYERR_RETERR2();
		}
		if( !( io->putc && io->puts_s && io->flush ) )
		{
			LIBANDRIA4_ERROR_MAYERR_RETERR3();
		}
		
		libandria4_commonio_eithgeneric res1;
		libandria4_error_mayerr res2;
		
		switch( err->typeid )
		{
			case LIBANDRIA4_ERRORSTRUCT_SIMPLETYPE:
#define libandria4_error_print_STR_FUNC "function: "
#define libandria4_error_print_STR_SRC " at "
#define libandria4_error_print_STR_DESC " announces this error: "
				if
				(
					!libandria4_commonio_recursivewrapper_puts_s
					(
						io,
							(libandria4_commonio_byte*)libandria4_error_print_STR_FUNC,
							sizeof( libandria4_error_print_STR_FUNC )
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR4();
				}
				
				res2 = libandria4_error_print_simplestruct( io, err->funcname );
				LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  LIBANDRIA4_ERROR_MAYERR_RETERR5 );
				
				if( !libandria4_commonio_utility_putint( io,  line ) )
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR6();
				}
				libandria4_commonio_eithgeneric res1 = io->putc( io,  (libandria4_commonio_byte)' ' );
				res2 = LIBANDRIA4_COMMONIO_EITHGENERIC_TO_MAYERR( res1 );
				LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  LIBANDRIA4_ERROR_MAYERR_RETERR7 );
				if
				(
					!libandria4_commonio_recursivewrapper_puts_s
					(
						io,
							(libandria4_commonio_byte*)file,
							strlen( file )
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR8();
				}
				
				if
				(
					!libandria4_commonio_recursivewrapper_puts_s
					(
						io,
							(libandria4_commonio_byte*)libandria4_error_print_STR_SRC,
							sizeof( libandria4_error_print_STR_SRC )
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR9();
				}
				
				if
				(
					!libandria4_commonio_recursivewrapper_puts_s
					(
						io,
							(libandria4_commonio_byte*)libandria4_error_print_STR_DESC,
							sizeof( libandria4_error_print_STR_DESC )
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR10();
				}
				
				res2 = libandria4_error_print_simplestruct( io, err );
				LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  LIBANDRIA4_ERROR_MAYERR_RETERR11 );
				
				break;
				
			case LIBANDRIA4_ERROR_TYPE_BASALSTRUCT:
				LIBANDRIA4_ERROR_MAYERR_RETERR12();
				
			default:
				LIBANDRIA4_ERROR_MAYERR_RETERR13();
		}
		
		LIBANDRIA4_ERROR_MAYERR_RETURN_SUCCESS();
	};
	
	LIBANDRIA4_ERROR_MAYERR_RETERR1();
}


libandria4_error_mayerr libandria4_sleep( uint32_t millisecs )
{
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
		
		Sleep( millisecs );
		
		LIBANDRIA4_ERROR_MAYERR_RETURN_SUCCESS();
		
	#elif defined(_POSIX_VERSION) || __unix__ || __linux__ || __QNX__ || __ANDROID__ || __APPLE__
		
		libandria4_result ret = libandria4_errno_2result();
		
			/* usleep() takes microseconds */
			/* Linux docs list the following two errors: EINTR and EINVAL */
		int res = usleep( ( (uintmax_t)millisecs ) * 1000 );
		
		if( res == 0 )
		{
			LIBANDRIA4_ERROR_MAYERR_RETURN_SUCCESS();
			
		} else if( res == -1 )
		{
			res = ret.val;
			ret = libandria4_errno_2result();
			errno = res;
			
			LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( ret.val );
			
		} else {
			
				/* What did it even return??? */
			LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR(
				LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED );
		}
		
	#else
		
		/* Generic case. */
		
		clock_t waittime, tmptime = clock();
		waittime = tmptime;
			/* On Windows the accuracy is often 1/64 of a second, on at */
			/*  least Ubuntu the actual GRANULARITY (precision, not */
			/*  accuracy) ius in milliseconds. */
		waittime += ( (double)millisecs / 1000 ) * ( CLOCKS_PER_SECOND );
			/* Force at least SOME step. */
		waittime += ( (millisecs > 0) && (waittime == tmptime) ? 1 : 0 );
			/* The actual value doesn't matter, it's just make-work. */
		int dummy;
		
		while( tmptime > -1 && waittime > tmptime )
		{
			dummy = libandria4_timesink( dummy );
			tmptime = clock();
		}
		if( tmptime < 0 )
		{
			LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR(
				LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED );
		}
		
		LIBANDRIA4_ERROR_MAYERR_RETURN_SUCCESS();
		
	#endif
}
