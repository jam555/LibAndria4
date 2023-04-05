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

#ifndef LIBANDRIA4_MATH_MATH_H
# define LIBANDRIA4_MATH_MATH_H
	
	#include "../basic/simpleops.h"
	#include "numerics.h"
	
	/* NOTE! : LIBANDRIA4_SUB( x, y ) has now been actually tested, but add, mul, */
	/*  etc., have not, and probably don't work (because of expansion */
	/*  problems). Also, LIBANDRIA4_INCREMENT( x ) can probably be used to */
	/*  compress down the *_SUB(), etc., functions to just a single pair */
	/*  each, via eliminating the hard-wired LIBANDRIA4_RETURN_*() call in the */
	/*  inner macros. */
	/* Use http://coliru.stacked-crooked.com/ to develop further. */
	
	#define LIBANDRIA4_DECREMENT( x ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_1ST, \
			LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_ADJACENTNUMS_, x ), () )
	#define LIBANDRIA4_INCREMENT( x ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_2ND, \
			LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_ADJACENTNUMS_, x ), () )
	
	
		/* Equivalent to x + y. */
	#define LIBANDRIA4_ADD( x, y ) \
		LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_ADD_, y ) ( \
			LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_1ST, \
				LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_SUMMATIONNUMS_, x ) ) \
		)
	
	#define LIBANDRIA4_ADD_0( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_1, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_ADD_1( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_2, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_ADD_2( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_3, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_ADD_3( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_4, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_ADD_4( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_5, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_ADD_5( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_6, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_ADD_6( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_7, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_ADD_7( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_8, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_ADD_8( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_9, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_ADD_9( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_10, LIBANDRIA4_STRIPPARENS( array ) )
	
	
		/* Equivalent to x - y. */
	#define LIBANDRIA4_SUB( x, y ) \
		LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_SUB_, y ) ( \
			LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_2ND, \
				LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_SUMMATIONNUMS_, x ) ) \
		)
	
	#define LIBANDRIA4_SUB_0( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_1, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_SUB_1( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_2, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SUB_2( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_3, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SUB_3( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_4, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SUB_4( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_5, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_SUB_5( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_6, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SUB_6( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_7, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SUB_7( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_8, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SUB_8( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_9, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_SUB_9( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_10, LIBANDRIA4_STRIPPARENS( array ) )
	
	
		/* As LIBANDRIA4_SUB(), but negative numbers are swapped with parenthese */
		/*  pairs. */
	#define LIBANDRIA4_SENSESUB( x, y ) \
		LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_SENSESUB_, y ) ( \
			LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_4TH, \
				LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_SUMMATIONNUMS_, x ) ) \
		)
	
	#define LIBANDRIA4_SENSESUB_0( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_1, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_SENSESUB_1( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_2, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SENSESUB_2( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_3, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SENSESUB_3( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_4, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SENSESUB_4( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_5, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_SENSESUB_5( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_6, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SENSESUB_6( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_7, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SENSESUB_7( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_8, LIBANDRIA4_STRIPPARENS( array ) )
	#define LIBANDRIA4_SENSESUB_8( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_9, LIBANDRIA4_STRIPPARENS( array ) )
	
	#define LIBANDRIA4_SENSESUB_9( array ) \
		LIBANDRIA4_APPLY( LIBANDRIA4_RETURN_10, LIBANDRIA4_STRIPPARENS( array ) )
	
	
		/* x / y */
	#define LIBANDRIA4_DIVIDE( x, y ) \
		LIBANDRIA4_DIVIDE_APPLY( \
			LIBANDRIA4_RETURN_2, \
			LIBANDRIA4_STRIPPARENS( LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_DIVIDE_, y ) \
				( LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_DIVISIONNUMS_, x ) ) ) \
		)
	#define LIBANDRIA4_DIVIDE_APPLY( func, ... ) func( __VA_ARGS__ )
	
	#define LIBANDRIA4_DIVIDE_1( ... ) \
		LIBANDRIA4_DIVIDE_APPLY( LIBANDRIA4_RETURN_1, __VA_ARGS__ )
	#define LIBANDRIA4_DIVIDE_2( ... ) \
		LIBANDRIA4_DIVIDE_APPLY( LIBANDRIA4_RETURN_2, __VA_ARGS__ )
	#define LIBANDRIA4_DIVIDE_3( ... ) \
		LIBANDRIA4_DIVIDE_APPLY( LIBANDRIA4_RETURN_3, __VA_ARGS__ )
	
#endif
/* End libandria4 math math.h */
