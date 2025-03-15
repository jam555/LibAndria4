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

typedef struct testtype
{
	int *ptr;
	
} testtype;
LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( testtype_arr_, testtype )

int dummy1;

int main( int argn, char *args[] )
{
	int dummy2;
	
	static int
		*reftest1 = &dummy1,
		*reftest2[] = { &dummy1 };
	
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		test1,
		arr,
		
		testtype_arr_,
		testtype,
		
		(testtype){ &dummy1 },
		(testtype){ &dummy1 } );
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		test2,
		arr,
		
		testtype_arr_,
		testtype,
		
		(testtype){ &dummy2 },
		(testtype){ &dummy2 } );
	
	printf( "\nTest 5." );
	
	printf( "\n    :%c %i",  'a', *( test1.arr.body[ 0 ].ptr ) );
	printf( "\n    :%c %i",  'b', *( test1.arr.body[ 1 ].ptr ) );
	
	printf( "\n    :%c %i",  'c', *( test2.arr.body[ 0 ].ptr ) );
	printf( "\n    :%c %i",  'd', *( test2.arr.body[ 1 ].ptr ) );
	
	putc( '\n', stdout );
}
