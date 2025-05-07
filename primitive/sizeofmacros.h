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

#ifndef LIBANDRIA4_BASIC_SIZEOFMACROS_H
# define LIBANDRIA4_BASIC_SIZEOFMACROS_H
	
	#include "platformdetect.h"
	
	#if !( ( LIBANDRIA4_COMPILER & LIBANDRIA4_COMPILER_CODEBASE_GNU ) == LIBANDRIA4_COMPILER_CODEBASE_GNU )
		#error "LIBANDRIA4_PREPROCTIME_SIZEOF() in sizeofmacros.h currently "
		#error "only supports GNU: open the file and produce an adapted form "
		#error "of the macro."
	#endif
	
		/* LIBANDRIA4_PREPROCTIME_SIZEOF() only properly supports up to 16 */
		/*  arguments. To change that, then both add more "x" args to */
		/*  LIBANDRIA4_PREPROCTIME_SIZEOF_SELECT(), as well as adding the */
		/*  higher values to LIBANDRIA4_PREPROCTIME_SIZEOF() itself. */
	#define LIBANDRIA4_PREPROCTIME_SIZEOF_SELECT( \
		x1, x2, x3, x4,  x5, x6, x7, x8,  x9, x10, x11, x12,  x13, x14, x15, x16,  x17, x18, x19, x20,  \
		x21, x22, x23, x24,  x25, x26, x27, x28,  x29, x30, x31, x32,  x33, x34, x35, x36,  x37, x38, x39, x40,  \
		n, ... ) n
		/* The "dummy, ## __VA_ARGS__" is because GCC will eliminate the */
		/*  comma in this case if __VA_ARGS__ is empty, allowing us to */
		/*  detect a size of 0. */
	#define LIBANDRIA4_PREPROCTIME_SIZEOF( ... ) \
		LIBANDRIA4_PREPROCTIME_SIZEOF_SELECT( dummy, ## __VA_ARGS__,  \
			39, 38, 37,  36, 35, 34, 33,  32, 31, 30, 29,  28, 27, 26, 25,  24, 23, 22, 21,  20, \
			19, 18, 17,  16, 15, 14, 13,  12, 11, 10, 9,  8, 7, 6, 5,  4, 3, 2, 1,  0,  \
			-1 )
	
	#define LIBANDRIA4_COMPILETIME_SIZEOF( ... ) \
		( sizeof( (int[]){ __VA_ARGS__ } ) / sizeof( int ) )
	
	#define LIBANDRIA4_COMPILETIME_ARRAYELEMS( type, name ) \
		( sizeof( name ) / sizeof( type ) )
	
#endif
/* End libsndria4 basic sizeof_macros.h */
