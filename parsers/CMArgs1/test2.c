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

/* parsers/CMArgs1/test1.c */
/*  This file exists to test the CMArgs1 system. It's intended behavior is */
/* to compare the result of some test strings to the expected results: */
/* fortunately, CMArgs1 takes explicitly provided string info instead of */
/* hunting down the command-line arguments directly, so this should be */
/* fairly reliable with little effort. */



#include <stdio.h>

#include "../../basic/pascalstring.h"



LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD( text1, arr, libandria4_char_, char, 'c', 'h', 'a', 'r', '\0' );

int main( int argn, char *args[] )
{
	printf( "\nCMArgs1 test2(): the pascalstring.h version.\n" );
	
	printf( "  Test string: %s\n", text1.arr.body );
}
