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


/* This is one of a series of test programs intended to hunt down the cause */
/*  of a "initializer is not const" error when using */
/*  LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD() */


#include <stdlib.h>
#include "../../basic/pascalarray.h"

LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( libandria4_char_, char )
LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( test_chararr_, char* )

int main( int argn, char *args[] )
{
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		name1,
		arr,
		
		libandria4_char_,
		char,
		
		'c','h','a','r', '\0' );
	
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		name2,
		arr,
		
		test_chararr_,
		char*,
		
		name1.arr.body );
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		name3,
		arr,
		
		test_chararr_,
		char*,
		
		&( name1.arr.body[ 0 ] ) );
	
	printf( "\nTest 3.\n    :" );
	
	int l = 0;
	while( name1.arr.len > l )
	{
		putc( name1.arr.body[ l ], stdout );
		++l;
	}
	printf( "    :%s\n", name2.arr.body[ 0 ] );
	printf( "    :%s\n", name3.arr.body[ 0 ] );
	
	putc( '\n', stdout );
}
