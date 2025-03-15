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

#ifndef LIBANDRIA4_BASIC_COMMONIO_H
# define LIBANDRIA4_BASIC_COMMONIO_H
	
	#include "commoniotypes.h"
	
	
	
	
	
	/* These exist for convenience. */
	
	#define libandria4_commonio_int_RETERR1( ... ) return( -1 );
	#define libandria4_commonio_int_RETERR2( ... ) return( -2 );
	#define libandria4_commonio_int_RETERR3( ... ) return( -3 );
	#define libandria4_commonio_int_RETERR4( ... ) return( -4 );
	#define libandria4_commonio_int_RETERR5( ... ) return( -5 );
	
	#define libandria4_commonio_int_RETERR6( ... ) return( -6 );
	#define libandria4_commonio_int_RETERR7( ... ) return( -7 );
	#define libandria4_commonio_int_RETERR8( ... ) return( -8 );
	#define libandria4_commonio_int_RETERR9( ... ) return( -9 );
	
	
	
	/* libandria4_commonio_handle{} has been moved to streams.h */
		/* Various things that formerly were in this file. */
	#include "streams.h"
	
	
	
	/* Convenience wrappers. */
		/* Tests for close & error handler functionality only. */
	int libandria4_commonio_handle_hasbasics( libandria4_commonio_handle* );
		/* Clears errors, fails on EOF and failed clears. */
	int libandria4_commonio_utility_clearerr( libandria4_commonio_handle* );
	int libandria4_commonio_recursivewrapper_puts_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *str, size_t len
	);
	int libandria4_commonio_utility_putint( libandria4_commonio_handle *io,  int i );
	
	
	
		/* Does this get used ANYWHERE? */
	typedef struct libandria4_FILE_handle
	{
		FILE *f;
		uintptr_t ref_count;
	} libandria4_FILE_handle;
	
	
	
		/* Common values for IO systems. */
	#include "commoniovals.h"
	
#endif
/* End libandria4 basic commonio.h */
