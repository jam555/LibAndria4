/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2024 Jared A. Maddox

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

#include <stdarg.h>
#include "simpleruntimeops.h"



int libandria4_op_indirfunc_int_voidp( void *dat_, ... )
{
	libandria4_op_indirfunc_int_voidp_valist_data *dat = (*)dat_;
	
	if( dat )
	{
		int ret = -2;
		
		if( dat->func )
		{
			va_list args;
			
			va_start( args, dat );
				ret = dat->func( dat->data, &args );
			va_end( args );
		}
		
		return( ret );
	}
	
	return( -1 );
}



	/* The first size_t is an INDEX, not the length that all the others take. */
libandria4_maybeint libandria4_op_returnint_Nth_valist( size_t offset,  size_t len, va_list *argi )
{
	if( !argi || offset >= len )
	{
		LIBANDRIA4_MAYBEINT_RETURNNOTHING();
	}
	
	int res;
	
	while( offset )
	{
		res = va_arg( argi, int );
		--offset;
	}
	
	LIBANDRIA4_MAYBEINT_RETURNJUST( res );
}

libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1st, 0 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_2nd, 1 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_3rd, 2 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_4th, 3 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_5th, 4 );

libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_6th, 5 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_7th, 6 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_8th, 7 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_9th, 8 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_10th, 9 );

libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_11th, 10 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_12th, 11 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_13th, 12 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_14th, 13 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_15th, 14 );

libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_16th, 15 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_17th, 16 );

libandria4_maybeint libandria4_op_returnint_Nth( size_t offset,  size_t len, ... )
{
	va_list argi;
	libandria4_maybeint res;
	libandria4_op_returnint_GENERICBODY( res, offset,  argi, len, len );
	
	return( res );
}



libandria4_maybeint libandria4_op_returnint_0( size_t len, ... )
{
	LIBANDRIA4_MAYBEINT_RETURNNOTHING();
}

libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1, 0 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_2, 1 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_3, 2 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_4, 3 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_5, 4 );

libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_6, 5 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_7, 6 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_8, 7 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_9, 8 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_10, 9 );

libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1, 10 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1, 11 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1, 12 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1, 13 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1, 14 );

libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1, 15 );
libandria4_op_returnint_BUILD_GENERICFUNC( libandria4_op_returnint_1, 16 );
