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

#include "streams.h"
#include "nulls.h"



int libandria4_commonio_handle_verifydispatch( libandria4_commonio_handle *handle )
{
	if( handle )
	{
		switch( handle.dispatch )
		{
			case libandria4_commonio_handle_vtabtype_handle:
				if( !( handle.vtab.hand ) )
				{
					return( -5 );
				}
				break;
			case libandria4_commonio_handle_vtabtype_istream:
				if( !( handle.vtab.istr ) )
				{
					return( -6 );
				}
				break;
			case libandria4_commonio_handle_vtabtype_ostream:
				if( !( handle.vtab.ostr ) )
				{
					return( -7 );
				}
				break;
			default:
				if( handle.dispatch == libandria4_commonio_handle_vtabtype_invalid )
				{
					return( -2 );
					
				} else if( handle.dispatch == libandria4_commonio_handle_vtabtype__END )
				{
					return( -3 );
					
				} else {
					
					return( -4 );
				}
		}
		
		return( 1 );
	}
	
	return( -1 );
}

libandria4_commonio_eithgeneric libandria4_commonio_common_puts_s
(
	libandria4_commonio_handle *io,
		libandria4_commonio_byte *str, size_t len
)
{
	if( io )
	{
		if( libandria4_commonio_handle_verifydispatch( io ) )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( 2 );
		}
		if( !( io->putc ) )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( 3 );
		}
		if( !str && len )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( 4 );
		}
		
		libandria4_commonio_eithgeneric res;
		size_t iter = 0;
		int a;
		while( iter < len )
		{
			res = io->putc( io, str[ iter ] );
			LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH(
				res,
					LIBANDRIA4_NULL_MACRO,
					LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR
				);
			
			++iter;
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( iter );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( 1 );
}
