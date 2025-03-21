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


#include <limits.h>
#include <time.h>


#include "basictypes.h"
#include "stdmonads.h"
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



const unsigned char libandria4_commonlib_firstchars[ 128 ] =
	{
		  0,   1,   2,   3,		  4,   5,   6,   7,
		  8,   9,  10,  11,		 12,  13,  14,  15,
		 16,  17,  18,  19,		 20,  21,  22,  23,
		 24,  25,  26,  27,		 28,  29,  30,  31,
		 
		 32,  33,  34,  35,		 36,  37,  38,  39,
		 40,  41,  42,  43,		 44,  45,  46,  47,
		 48,  49,  50,  51,		 52,  53,  54,  55,
		 56,  57,  58,  59,		 60,  61,  62,  63,
		 
		 64,  65,  66,  67,		 68,  69,  70,  71,
		 72,  73,  74,  75,		 76,  77,  78,  79,
		 80,  81,  82,  83,		 84,  85,  86,  87,
		 88,  89,  90,  91,		 92,  93,  94,  95,
		 
		 96,  97,  98,  99,		100, 101, 102, 103,
		104, 105, 106, 107,		108, 109, 110, 111,
		112, 113, 114, 115,		116, 117, 118, 119,
		120, 121, 122, 123,		124, 125, 126, 127
	};



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
		unsigned char *haystack = (unsigned char*)haystack_, *needle = (unsigned char*)needle_;
		size_t hoff = 0, noff = 0, goff = 0;
		
		if( needlesize % needlegrain )
		{
			LIBANDRIA4_PTRRESULT_RETURNFAILURE(
				(libandria4_failure_uipresult){
					LIBANDRIA4_RESULT_FAILURE_DOMAIN
				}
			);
		}
		
		while( hoff + needlesize <= haysize )
		{
			while( noff < needlesize &&
				haystack[ hoff + noff + goff ] == needle[ noff + goff ] )
			{
				while( goff < needlegrain &&
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
	
	LIBANDRIA4_PTRRESULT_RETURNFAILURE( 
		(libandria4_failure_uipresult)
		{
			LIBANDRIA4_RESULT_FAILURE_EOF
		}
	);
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



/* ... TODO: Move these error-reporter functions elsewhere. commonlib.h/.c */
/*  should eventually not rely on commonio.h at all, but these shouldn't be */
/*  de-coupled from it. */
	/* Remember to remove the note about this TODO in commonlib.h */
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
			case LIBANDRIA4_ERROR_TYPE_SIMPLESTRUCT:
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
				res2 = LIBANDRIA4_COMMONIO_EITHGENERIC_TO_ERRMAYERR( res1 );
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
		
		/* TODO : Adapt this to use LibAndria's centralized platform detection. */
			/* Remove the commonlib.h note when done. */
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
			libandria4_error_mayerr tmp = LIBANDRIA4_RESULT_TO_ERRMAYERR( ret );
			LIBANDRIA4_ERROR_MAYERR_BODYMATCH(
				tmp,
				
				LIBANDRIA4_OP_SETres,
				LIBANDRIA4_OP_SETresTO0 );
			ret = libandria4_errno_2result();
			errno = res;
			
			return( LIBANDRIA4_RESULT_TO_ERRMAYERR( ret ) );
			
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


int libandria4_cb_ctoi_feedint_c( void *dest, char ignore, int num )
{
	libandria4_cb_ctoi_intconv *ic = (*libandria4_cb_ctoi_intconv)dest;
	
	if( ic )
	{
		ic->stat = ( num >= 0 ? 1 : -1 );
		ic->num = ( num ? num : 0 );
	}
	
	return( num );
}
int libandria4_cb_atoi_feedint_s( void *dest,  size_t ig2, char *ig3, size_t off,  int num )
{
	libandria4_cb_ctoi_intconv *ic = (*libandria4_cb_ctoi_intconv)dest;
	
	if( ic )
	{
		ic->stat = ( off ? 1 : -1 );
		ic->num = ( off ? num : 0 );
	}
	
	return( num );
}

libandria4_commonlib_charchar_eithfork libandria4_cb_ctoi( char c,  void *data, int (*func)( void*, char, int ) )
{
#if 0
	#error "libandria4_cb_ctoi() only supports ASCII and similar formats, with all numbers in a contiguous block."
#else
	int ret =  c - '0';
	
	if( ret < 0 || ret > 9 )
	{
		LIBANDRIA4_COMMONLIB_CHARFORK_RETFOREIGN( c );
	}
	
	if( func )
	{
		LIBANDRIA4_COMMONLIB_CHARFORK_RETMATCH( func( data, c, ret ) );
		
	} else {
		
		LIBANDRIA4_COMMONLIB_CHARFORK_RETERROR( LIBANDRIA4_RESULT_FAILURE_DOMAIN );
	}
#endif
}
libandria4_commonlib_charchar_eithfork libandria4_ctoi( char c )
{
	return( libandria4_cb_ctoi( c,  (void*)0, &libandria4_cb_ctoi_feedint_c ) );
}

libandria4_commonlib_intint_eithfork libandria4_cb_atoi
(
	size_t len,
	char *c,
	
	void *data,
	int (*func)( void*,  size_t, char*, size_t,  int )
)
{
		/* The smallest value that will overflow an int if multiplied by 10. */
	static const int int_penultideci = (( INT_MAX - ( INT_MAX % 10 )) / 10 ) + 1;
	libandria4_cb_ctoi_intconv ic = { 0, 1 };
	size_t off = 0;
	int ret = 0, mul = 1;
	
	if( off >= len || !c )
	{
		LIBANDRIA4_COMMONLIB_INTFORK_RETERROR( LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS );
	}
	
	if( c[ off ] == '-' )
	{
		mul = -1;
		off++;
	}
	while( off < len && ic.stat == 1 && ret < int_penultideci )
	{
		ret *= 10;
		ret += ic.num;
		
		libandria4_cb_ctoi( c[ off ],  (void*)&ic, &libandria4_cb_ctoi_feedint_c );
		
		off++;
	}
	if( ic.stat == 1 )
	{
		/* Clean-up special cases. */
		
		if( ret >= int_penultideci )
		{
			/* Overflow impending! */
			
			ic.stat = 2;
			off--;
			
		} else {
			
			/* Last character needs to be accumulated! */
			
			ret *= 10;
			ret += ic.num;
		}
	}
	ret *= mul;
	
	if( func )
	{
		ret = func( data,  len, c, off,  ret );
	}
	if( !off )
	{
		LIBANDRIA4_COMMONLIB_INTFORK_RETERROR( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
	}
	if( ic.stat == 2 )
	{
		LIBANDRIA4_COMMONLIB_CHARFORK_RETFOREIGN( off );
	}
	
	LIBANDRIA4_COMMONLIB_INTFORK_RETMATCH( ret );
}
libandria4_commonlib_intint_eithfork libandria4_atoi( size_t len, char *c )
{
	return( libandria4_cb_atoi( len, c,  (void*)0, 0 ) );
}
