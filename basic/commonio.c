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

#include "commonio.h"
#include "simpleops.h"



const libandria4_commonio_perr libandria4_commoniovals_eof =
	LIBANDRIA4_COMMONIOVALS_EOF;
const libandria4_commonio_mayerr libandria4_commoniovals_justeof =
	LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_COMMONIOVALS_EOF );
const libandria4_commonio_mayerr2 libandria4_commoniovals_justeof2 =
	LIBANDRIA4_COMMONIO_MAYERR2_BUILDJUST( LIBANDRIA4_COMMONIOVALS_EOF );



int libandria4_commonio_handle_hasbasics( libandria4_commonio_handle *io )
{
	if( io )
	{
		return
		(
			(
				libandria4_commonio_handle_hasfunc
				(
					io,
					
					libandria4_commonio_handle_vtable_funcenums_clearerr |
					libandria4_commonio_handle_vtable_funcenums_eof |
					libandria4_commonio_handle_vtable_funcenums_error |
					
					libandria4_commonio_handle_vtable_funcenums_close
				)
				
			) ? 1 : -2
		);
	}
	
	return( -1 );
}



int libandria4_commonio_utility_clearerr( libandria4_commonio_handle *io )
{
	if( io )
	{
		if
		(
			libandria4_commonio_handle_hasfunc
			(
				io,
				
				libandria4_commonio_handle_vtable_funcenums_clearerr |
				libandria4_commonio_handle_vtable_funcenums_eof
			)
		)
		{
			return( -3 );
		}
		
		
		libandria4_commonio_eithgeneric res1;
		libandria4_commonio_mayerr res2;
		
		res1 = libandria4_commonio_handle_EOF( io );
		res2 = LIBANDRIA4_COMMONIO_EITHGENERIC_TO_MAYERR( res1 );
		LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  libandria4_commonio_int_RETERR4 );
		
		res1 = libandria4_commonio_handle_CLEARERR( io );
		res2 = LIBANDRIA4_COMMONIO_EITHGENERIC_TO_MAYERR( res );
		LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  libandria4_commonio_int_RETERR5 );
		
		
		return( 1 );
	}
	
	return( -1 );
}

int libandria4_commonio_recursivewrapper_puts_s
(
	libandria4_commonio_handle *io,
		libandria4_commonio_byte *str, size_t len
)
{
	if( io )
	{
		if( !str && len )
		{
			return( -2 );
		}
		if
		(
			libandria4_commonio_handle_hasfunc
			(
				io,
				
				libandria4_commonio_handle_vtable_funcenums_puts_s
			)
		)
		{
			return( -3 );
		}
		if
		(
			libandria4_commonio_handle_hasfunc
			(
				io,
				
				libandria4_commonio_handle_vtable_funcenums_clearerr |
				libandria4_commonio_handle_vtable_funcenums_eof
			)
		)
		{
			return( -4 );
		}
		
		libandria4_commonio_eithgeneric res1;
		libandria4_commonio_mayerr res2;
		size_t a, iter = 0;
		
		while( len - iter )
		{
			res1 = libandria4_commonio_handle_PUTS_S(
					io,
					(libandria4_commonio_byte*)( str + iter ), len - iter
				);
			LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH(
				res1,
					LIBANDRIA4_OP_SETa,
					libandria4_commonio_int_RETERR5
			);
			if( a != len && !libandria4_commonio_utility_clearerr( io ) )
			{
				libandria4_commonio_int_RETERR6();
			}
			iter += a;
		}
		
		return( (int)iter );
	}
	
	return( -1 );
}
int libandria4_commonio_utility_putint( libandria4_commonio_handle *io,  int i )
{
	if( io )
	{
		if
		(
			libandria4_commonio_handle_hasfunc
			(
				io,
				
				libandria4_commonio_handle_vtable_funcenums_putc
			)
		)
		{
			return( -2 );
		}
		if
		(
			libandria4_commonio_handle_hasfunc
			(
				io,
				
				libandria4_commonio_handle_vtable_funcenums_clearerr |
				libandria4_commonio_handle_vtable_funcenums_eof
			)
		)
		{
			return( -3 );
		}
		
		libandria4_commonio_succ a;
		libandria4_commonio_succ b;
		libandria4_commonio_eithgeneric res1;
#define libandria4_commonio_utility_putint_PUTLOOP( reterr, chara ) \
		b = 1; while( b ) { b = 0; \
			res1 = libandria4_commonio_handle_PUTC( \
				io, (libandria4_commonio_byte)( chara ) ); \
			LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH( res1, \
				LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb ); \
			if( b && !libandria4_commonio_utility_clearerr( io ) ) { ( reterr )(); } }
		
			/* Write any negative signs. */
		int tmp = ( i < 0 ? 1 : 0 );
		i *= ( tmp ? -1 : 1 );
		if( tmp )
		{
			libandria4_commonio_utility_putint_PUTLOOP(
				libandria4_commonio_int_RETERR4,
				'-'
			);
		}
		
			/* Make some space so modmask can't overflow. */
		int ilast = i % 10;
		i -= ilast;
		i /= 10;
		
			/* We won't be bothering with leading 0s. */
		int modmask = 10;
		while( i % modmask >= 10 )
		{
			modmask *= 10;
		}
		
		static char *charas = "0123456789";
		
			/* tmp =,-=,/= results in: */
				/* The DECIMAL digit we want gets stored, along with those */
				/*  under it; */
				/* Those under it get removed; and */
				/* It gets pulled down to the 1s column. */
			/*  So, it isolates a digit, and then drops it so it can directly */
			/*  be used as an index. */
		tmp = i % modmask;
		while( modmask > 1 )
		{
			modmask /= 10;
			tmp -= tmp % modmask;
			tmp /= modmask;
			
			libandria4_commonio_utility_putint_PUTLOOP(
				libandria4_commonio_int_RETERR5,
				charas[ tmp ]
			);
		}
		
			/* Now we write out that digit we separated earlier. */
		libandria4_commonio_utility_putint_PUTLOOP(
			libandria4_commonio_int_RETERR6,
			charas[ ilast ]
		);
		
		return( 1 );
	}
	
	return( -1 );
}
