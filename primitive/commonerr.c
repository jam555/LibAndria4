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


#include <limits.h>

#include "basictypes.h"
#include "commonerr.h"
#include "commonlib.h"



static void *putc_data = 0;
static libandria4_common_putcharfuncp_int putc_func = 0;



void libandria4_error_setputc
(
	void *newdata, libandria4_common_putcharfuncp_int newputc,
		/* Optional: if provided, then the target of the pointers will */
		/*  be set to the values that are being replaced by the new */
		/*  arguments. */
	void *olddata, libandria4_common_putcharfuncp_int *oldputc
)
{
	if( olddata )
	{
		*olddata = putc_data;
	}
	if( oldputc )
	{
		*oldputc = putc_func;
	}
	
	putc_data = newdata;
	putc_func = newputc;
}
static int output_char( char c )
{
	if( putc_func )
	{
		return( putc_func( putc_data,  c ) );
	}
	
	return( 1 );
}
static int output_str( size_t len, char *text )
{
	if( text )
	{
		int res = 0;
		size_t i = 0;
		while( i < len )
		{
			res = output_char( text[ i ] );
			if( !res )
			{
				return( res );
			}
		}
		
		return( 1 );
	}
	
	return( -1 );
}



int libandria4_error_print_simplestruct
(
	libandria4_error_simplestruct *err
)
{
	if( err )
	{
		if( output_str( err->str_len, err->str ) )
		{
			return( -2 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}
libandria4_error_mayerr libandria4_error_print
(
	libandria4_error_basalstruct *err,
	int line,
	char *file
)
{
	if( err )
	{
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
					!output_str
					(
						sizeof( libandria4_error_print_STR_FUNC ),
						(char*)libandria4_error_print_STR_FUNC
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR4();
				}
				
				libandria4_error_simplestruct *simperr = (libandria4_error_simplestruct*)err;
				if( !libandria4_error_print_simplestruct( simperr->funcname ) )
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR5();
				}
				
				if( !libandria4_i2putc( putc_data, putc_func,  line ) )
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR6();
				}
				if( !output_char( ' ' ) )
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR7();
				}
				
				if
				(
					!output_str
					(
						strlen( file ),
						(char*)file
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR8();
				}
				
				if
				(
					!output_str
					(
						sizeof( libandria4_error_print_STR_SRC ),
						(char*)libandria4_error_print_STR_SRC
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR9();
				}
				
				if
				(
					!output_str
					(
						sizeof( libandria4_error_print_STR_DESC ),
						(char*)libandria4_error_print_STR_DESC
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR10();
				}
				
				if
				(
					!libandria4_error_print_simplestruct
					(
						LIBANDRIA4_STRUCTADDRfromELEMADDR(
							libandria4_error_simplestruct,
							type,
							
							simperr
						)
					)
				)
				{
					LIBANDRIA4_ERROR_MAYERR_RETERR11();
				}
				
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
