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
	
	#include "monads.h"
	
	typedef uint8_t libandria4_commonio_byte;
	typedef uint32_t libandria4_commonio_succ;
	typedef uint32_t libandria4_commonio_err;
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_commonio_byteret,
			libandria4_commonio_byte,
			libandria4_commonio_err
	);
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_commonio_genericret,
			libandria4_commonio_succ,
			libandria4_commonio_err
	);
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_commonio_longret,
			long,
			libandria4_commonio_err
	);
	
	
	
	typedef struct libandria4_commonio_handle libandria4_commonio_handle;
	
	typedef libandria4_commonio_genericret (*libandria4_commonio_genericfunc)( libandria4_commonio_handle* );
	typedef libandria4_commonio_byteret (*libandria4_commonio_fetchbyte)( libandria4_commonio_handle* );
	typedef libandria4_commonio_genericret (*libandria4_commonio_storebyte)( libandria4_commonio_handle*, libandria4_commonio_byte );
	typedef libandria4_commonio_longret (*libandria4_commonio_longfunc)( libandria4_commonio_handle* );
	typedef libandria4_commonio_genericret (*libandria4_commonio_seekfunc)( libandria4_commonio_handle*, long, int /* origin */ );
	
	struct libandria4_commonio_handle
	{
		uintptr_t typeid;
		
		libandria4_commonio_genericfunc flush;
		
		libandria4_commonio_fetchbyte getc;
		libandria4_commonio_storebyte putc;
		libandria4_commonio_storebyte ungetc;

		libandria4_commonio_longfunc tell;
		libandria4_commonio_seekfunc seek;
		libandria4_commonio_genericfunc rewind;
		
		libandria4_commonio_genericfunc clearerr;
		libandria4_commonio_genericfunc eof;
		libandria4_commonio_genericfunc error;
		
		libandria4_commonio_genericfunc close;
	};
	
	
	???
	???
	???
#endif
/* End libandria4 basic commonio.h */
