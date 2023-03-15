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

#ifndef LIBANDRIA4_MACROTIME_MATH_H
# define LIBANDRIA4_MACROTIME_MATH_H
	
	#include "simpleops.h"
	
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
	
	
	
		/* Addition, then subtraction. */
		/* Sumands: 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 */
	#define LIBANDRIA4_SUMMATIONNUMS_() \
		( \
			(), (), (), (), (), \
			(), (), (), (), () \
		), \
		( \
			(), (), (), (), (), \
			(), (), (), (), () \
		), \
		( \
			(), (), (), (), (), \
			(), (), (), (), () \
		), \
		( \
			(), (), (), (), (), \
			(), (), (), (), () \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_0 \
		( \
			0, 1, 2, 3, 4, \
			5, 6, 7, 8, 9 \
		), \
		( \
			0, -1, -2, -3, -4, \
			-5, -6, -7, -8, -9 \
		), \
		( \
			0, 1, 2, 3, 4, \
			5, 6, 7, 8, 9 \
		), \
		( \
			0, (), (), (), (), \
			(), (), (), (), () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_1 \
		( \
			1, 2, 3, 4, 5, \
			6, 7, 8, 9, 10 \
		), \
		( \
			1, 0, -1, -2, -3, \
			-4, -5, -6, -7, -8 \
		), \
		( \
			1, 2, 3, 4, 5, \
			6, 7, 8, 9, 10 \
		), \
		( \
			1, 0, (), (), (), \
			(), (), (), (), () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_2 \
		( \
			2, 3, 4, 5, 6, \
			7, 8, 9, 10, 11 \
		), \
		( \
			2, 1, 0, -1, -2, \
			-3, -4, -5, -6, -7 \
		), \
		( \
			2, 3, 4, 5, 6, \
			7, 8, 9, 10, 11 \
		), \
		( \
			2, 1, 0, (), (), \
			(), (), (), (), () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_3 \
		( \
			3, 4, 5, 6, 7, \
			8, 9, 10, 11, 12 \
		), \
		( \
			3, 2, 1, 0, -1, \
			-2, -3, -4, -5, -6 \
		), \
		( \
			3, 4, 5, 6, 7, \
			8, 9, 10, 11, 12 \
		), \
		( \
			3, 2, 1, 0, (), \
			(), (), (), (), () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_4 \
		( \
			4, 5, 6, 7, 8, \
			9, 10, 11, 12, 13 \
		), \
		( \
			4, 3, 2, 1, 0, \
			-1, -2, -3, -4, -5 \
		), \
		( \
			4, 5, 6, 7, 8, \
			9, 10, 11, 12, 13 \
		), \
		( \
			4, 3, 2, 1, 0, \
			(), (), (), (), () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_5 \
		( \
			5, 6, 7, 8, 9, \
			10, 11, 12, 13, 14 \
		), \
		( \
			5, 4, 3, 2, 1, \
			0, -1, -2, -3, -4 \
		), \
		( \
			5, 6, 7, 8, 9, \
			10, 11, 12, 13, 14 \
		), \
		( \
			5, 4, 3, 2, 1, \
			0, (), (), (), () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_6 \
		( \
			6, 7, 8, 9, 10, \
			11, 12, 13, 14, 15 \
		), \
		( \
			6, 5, 4, 3, 2, \
			1, 0, -1, -2, -3 \
		), \
		( \
			6, 7, 8, 9, 10, \
			11, 12, 13, 14, 15 \
		), \
		( \
			6, 5, 4, 3, 2, \
			1, 0, (), (), () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_7 \
		( \
			7, 8, 9, 10, 11, \
			12, 13, 14, 15, 16 \
		), \
		( \
			7, 6, 5, 4, 3, \
			2, 1, 0, -1, -2 \
		), \
		( \
			7, 8, 9, 10, 11, \
			12, 13, 14, 15, 16 \
		), \
		( \
			7, 6, 5, 4, 3, \
			2, 1, 0, (), () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_8 \
		( \
			8, 9, 10, 11, 12, \
			13, 14, 15, 16, 17 \
		), \
		( \
			8, 7, 6, 5, 4, \
			3, 2, 1, 0, -1 \
		), \
		( \
			8, 9, 10, 11, 12, \
			13, 14, 15, 16, 17 \
		), \
		( \
			8, 7, 6, 5, 4, \
			3, 2, 1, 0, () \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_9 \
		( \
			9, 10, 11, 12, 13, \
			14, 15, 16, 17, 18 \
		), \
		( \
			9, 8, 7, 6, 5, \
			4, 3, 2, 1, 0 \
		), \
		( \
			9, 10, 11, 12, 13, \
			14, 15, 16, 17, 18 \
		), \
		( \
			9, 8, 7, 6, 5, \
			4, 3, 2, 1, 0 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_10 \
		( \
			10, 11, 12, 13, 14, \
			15, 16, 17, 18, 19 \
		), \
		( \
			10, 9, 8, 7, 6, \
			5, 4, 3, 2, 1 \
		), \
		( \
			10, 11, 12, 13, 14, \
			15, 16, 17, 18, 19 \
		), \
		( \
			10, 9, 8, 7, 6, \
			5, 4, 3, 2, 1 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_11 \
		( \
			11, 12, 13, 14, 15, \
			16, 17, 18, 19, 20 \
		), \
		( \
			11, 10, 9, 8, 7, \
			6, 5, 4, 3, 2 \
		), \
		( \
			11, 12, 13, 14, 15, \
			16, 17, 18, 19, 20 \
		), \
		( \
			11, 10, 9, 8, 7, \
			6, 5, 4, 3, 2 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_12 \
		( \
			12, 13, 14, 15, 16, \
			17, 18, 19, 20, 21 \
		), \
		( \
			12, 11, 10, 9, 8, \
			7, 6, 5, 4, 3 \
		), \
		( \
			12, 13, 14, 15, 16, \
			17, 18, 19, 20, 21 \
		), \
		( \
			12, 11, 10, 9, 8, \
			7, 6, 5, 4, 3 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_13 \
		( \
			13, 14, 15, 16, 17, \
			18, 19, 20, 21, 22 \
		), \
		( \
			13, 12, 11, 10, 9, \
			8, 7, 6, 5, 4 \
		), \
		( \
			13, 14, 15, 16, 17, \
			18, 19, 20, 21, 22 \
		), \
		( \
			13, 12, 11, 10, 9, \
			8, 7, 6, 5, 4 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_14 \
		( \
			14, 15, 16, 17, 18, \
			19, 20, 21, 22, 23 \
		), \
		( \
			14, 13, 12, 11, 10, \
			9, 8, 7, 6, 5 \
		), \
		( \
			14, 15, 16, 17, 18, \
			19, 20, 21, 22, 23 \
		), \
		( \
			14, 13, 12, 11, 10, \
			9, 8, 7, 6, 5 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_15 \
		( \
			15, 16, 17, 18, 19, \
			20, 21, 22, 23, 24 \
		), \
		( \
			15, 14, 13, 12, 11, \
			10, 9, 8, 7, 6 \
		), \
		( \
			15, 16, 17, 18, 19, \
			20, 21, 22, 23, 24 \
		), \
		( \
			15, 14, 13, 12, 11, \
			10, 9, 8, 7, 6 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_16 \
		( \
			16, 17, 18, 19, 20, \
			21, 22, 23, 24, 25 \
		), \
		( \
			16, 15, 14, 13, 12, \
			11, 10, 9, 8, 7 \
		), \
		( \
			16, 17, 18, 19, 20, \
			21, 22, 23, 24, 25 \
		), \
		( \
			16, 15, 14, 13, 12, \
			11, 10, 9, 8, 7 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_17 \
		( \
			17, 18, 19, 20, 21, \
			22, 23, 24, 25, 26 \
		), \
		( \
			17, 16, 15, 14, 13, \
			12, 11, 10, 9, 8 \
		), \
		( \
			17, 18, 19, 20, 21, \
			22, 23, 24, 25, 26 \
		), \
		( \
			17, 16, 15, 14, 13, \
			12, 11, 10, 9, 8 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_18 \
		( \
			18, 19, 20, 21, 22, \
			23, 24, 25, 26, 27 \
		), \
		( \
			18, 17, 16, 15, 14, \
			13, 12, 11, 10, 9 \
		), \
		( \
			18, 19, 20, 21, 22, \
			23, 24, 25, 26, 27 \
		), \
		( \
			18, 17, 16, 15, 14, \
			13, 12, 11, 10, 9 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_19 \
		( \
			19, 20, 21, 22, 23, \
			24, 25, 26, 27, 28 \
		), \
		( \
			19, 18, 17, 16, 15, \
			14, 13, 12, 11, 10 \
		), \
		( \
			19, 20, 21, 22, 23, \
			24, 25, 26, 27, 28 \
		), \
		( \
			19, 18, 17, 16, 15, \
			14, 13, 12, 11, 10 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_20 \
		( \
			20, 21, 22, 23, 24, \
			25, 26, 27, 28, 29 \
		), \
		( \
			20, 19, 18, 17, 16, \
			15, 14, 13, 12, 11 \
		), \
		( \
			20, 21, 22, 23, 24, \
			25, 26, 27, 28, 29 \
		), \
		( \
			20, 19, 18, 17, 16, \
			15, 14, 13, 12, 11 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_21 \
		( \
			21, 22, 23, 24, 25, \
			26, 27, 28, 29, 30 \
		), \
		( \
			21, 20, 19, 18, 17, \
			16, 15, 14, 13, 12 \
		), \
		( \
			21, 22, 23, 24, 25, \
			26, 27, 28, 29, 30 \
		), \
		( \
			21, 20, 19, 18, 17, \
			16, 15, 14, 13, 12 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_22 \
		( \
			22, 23, 24, 25, 26, \
			27, 28, 29, 30, 31 \
		), \
		( \
			22, 21, 20, 19, 18, \
			17, 16, 15, 14, 13 \
		), \
		( \
			22, 23, 24, 25, 26, \
			27, 28, 29, 30, 31 \
		), \
		( \
			22, 21, 20, 19, 18, \
			17, 16, 15, 14, 13 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_23 \
		( \
			23, 24, 25, 26, 27, \
			28, 29, 30, 31, 32 \
		), \
		( \
			23, 22, 21, 20, 19, \
			18, 17, 16, 15, 14 \
		), \
		( \
			23, 24, 25, 26, 27, \
			28, 29, 30, 31, 32 \
		), \
		( \
			23, 22, 21, 20, 19, \
			18, 17, 16, 15, 14 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_24 \
		( \
			24, 25, 26, 27, 28, \
			29, 30, 31, 32, 33 \
		), \
		( \
			24, 23, 22, 21, 20, \
			19, 18, 17, 16, 15 \
		), \
		( \
			24, 25, 26, 27, 28, \
			29, 30, 31, 32, 33 \
		), \
		( \
			24, 23, 22, 21, 20, \
			19, 18, 17, 16, 15 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_25 \
		( \
			25, 26, 27, 28, 29, \
			30, 31, 32, 33, 34 \
		), \
		( \
			25, 24, 23, 22, 21, \
			20, 19, 18, 17, 16 \
		), \
		( \
			25, 26, 27, 28, 29, \
			30, 31, 32, 33, 34 \
		), \
		( \
			25, 24, 23, 22, 21, \
			20, 19, 18, 17, 16 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_26 \
		( \
			26, 27, 28, 29, 30, \
			31, 32, 33, 34, 35 \
		), \
		( \
			26, 25, 24, 23, 22, \
			21, 20, 19, 18, 17 \
		), \
		( \
			26, 27, 28, 29, 30, \
			31, 32, 33, 34, 35 \
		), \
		( \
			26, 25, 24, 23, 22, \
			21, 20, 19, 18, 17 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_27 \
		( \
			27, 28, 29, 30, 31, \
			32, 33, 34, 35, 36 \
		), \
		( \
			27, 26, 25, 24, 23, \
			22, 21, 20, 19, 18 \
		), \
		( \
			27, 28, 29, 30, 31, \
			32, 33, 34, 35, 36 \
		), \
		( \
			27, 26, 25, 24, 23, \
			22, 21, 20, 19, 18 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_28 \
		( \
			28, 29, 30, 31, 32, \
			33, 34, 35, 36, 37 \
		), \
		( \
			28, 27, 26, 25, 24, \
			23, 22, 21, 20, 19 \
		), \
		( \
			28, 29, 30, 31, 32, \
			33, 34, 35, 36, 37 \
		), \
		( \
			28, 27, 26, 25, 24, \
			23, 22, 21, 20, 19 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_29 \
		( \
			29, 30, 31, 32, 33, \
			34, 35, 36, 37, 38 \
		), \
		( \
			29, 28, 27, 26, 25, \
			24, 23, 22, 21, 20 \
		), \
		( \
			29, 30, 31, 32, 33, \
			34, 35, 36, 37, 38 \
		), \
		( \
			29, 28, 27, 26, 25, \
			24, 23, 22, 21, 20 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_30 \
		( \
			30, 31, 32, 33, 34, \
			35, 36, 37, 38, 39 \
		), \
		( \
			30, 29, 28, 27, 26, \
			25, 24, 23, 22, 21 \
		), \
		( \
			30, 31, 32, 33, 34, \
			35, 36, 37, 38, 39 \
		), \
		( \
			30, 29, 28, 27, 26, \
			25, 24, 23, 22, 21 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_31 \
		( \
			31, 32, 33, 34, 35, \
			36, 37, 38, 39, 40 \
		), \
		( \
			31, 30, 29, 28, 27, \
			26, 25, 24, 23, 22 \
		), \
		( \
			31, 32, 33, 34, 35, \
			36, 37, 38, 39, 40 \
		), \
		( \
			31, 30, 29, 28, 27, \
			26, 25, 24, 23, 22 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_32 \
		( \
			32, 33, 34, 35, 36, \
			37, 38, 39, 40, 41 \
		), \
		( \
			32, 31, 30, 29, 28, \
			27, 26, 25, 24, 23 \
		), \
		( \
			32, 33, 34, 35, 36, \
			37, 38, 39, 40, 41 \
		), \
		( \
			32, 31, 30, 29, 28, \
			27, 26, 25, 24, 23 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_33 \
		( \
			33, 34, 35, 36, 37, \
			38, 39, 40, 41, 42 \
		), \
		( \
			33, 32, 31, 30, 29, \
			28, 27, 26, 25, 24 \
		), \
		( \
			33, 34, 35, 36, 37, \
			38, 39, 40, 41, 42 \
		), \
		( \
			33, 32, 31, 30, 29, \
			28, 27, 26, 25, 24 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_34 \
		( \
			34, 35, 36, 37, 38, \
			39, 40, 41, 42, 43 \
		), \
		( \
			34, 33, 32, 31, 30, \
			29, 28, 27, 26, 25 \
		), \
		( \
			34, 35, 36, 37, 38, \
			39, 40, 41, 42, 43 \
		), \
		( \
			34, 33, 32, 31, 30, \
			29, 28, 27, 26, 25 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_35 \
		( \
			35, 36, 37, 38, 39, \
			40, 41, 42, 43, 44 \
		), \
		( \
			35, 34, 33, 32, 31, \
			30, 29, 28, 27, 26 \
		), \
		( \
			35, 36, 37, 38, 39, \
			40, 41, 42, 43, 44 \
		), \
		( \
			35, 34, 33, 32, 31, \
			30, 29, 28, 27, 26 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_36 \
		( \
			36, 37, 38, 39, 40, \
			41, 42, 43, 44, 45 \
		), \
		( \
			36, 35, 34, 33, 32, \
			31, 30, 29, 28, 27 \
		), \
		( \
			36, 37, 38, 39, 40, \
			41, 42, 43, 44, 45 \
		), \
		( \
			36, 35, 34, 33, 32, \
			31, 30, 29, 28, 27 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_37 \
		( \
			37, 38, 39, 40, 41, \
			42, 43, 44, 45, 46 \
		), \
		( \
			37, 36, 35, 34, 33, \
			32, 31, 30, 29, 28 \
		), \
		( \
			37, 38, 39, 40, 41, \
			42, 43, 44, 45, 46 \
		), \
		( \
			37, 36, 35, 34, 33, \
			32, 31, 30, 29, 28 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_38 \
		( \
			38, 39, 40, 41, 42, \
			43, 44, 45, 46, 47 \
		), \
		( \
			38, 37, 36, 35, 34, \
			33, 32, 31, 30, 29 \
		), \
		( \
			38, 39, 40, 41, 42, \
			43, 44, 45, 46, 47 \
		), \
		( \
			38, 37, 36, 35, 34, \
			33, 32, 31, 30, 29 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_39 \
		( \
			39, 40, 41, 42, 43, \
			44, 45, 46, 47, 48 \
		), \
		( \
			39, 38, 37, 36, 35, \
			34, 33, 32, 31, 30 \
		), \
		( \
			39, 40, 41, 42, 43, \
			44, 45, 46, 47, 48 \
		), \
		( \
			39, 38, 37, 36, 35, \
			34, 33, 32, 31, 30 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_40 \
		( \
			40, 41, 42, 43, 44, \
			45, 46, 47, 48, 49 \
		), \
		( \
			40, 39, 38, 37, 36, \
			35, 34, 33, 32, 31 \
		), \
		( \
			40, 41, 42, 43, 44, \
			45, 46, 47, 48, 49 \
		), \
		( \
			40, 39, 38, 37, 36, \
			35, 34, 33, 32, 31 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_41 \
		( \
			41, 42, 43, 44, 45, \
			46, 47, 48, 49, 50 \
		), \
		( \
			41, 40, 39, 38, 37, \
			36, 35, 34, 33, 32 \
		), \
		( \
			41, 42, 43, 44, 45, \
			46, 47, 48, 49, 50 \
		), \
		( \
			41, 40, 39, 38, 37, \
			36, 35, 34, 33, 32 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_42 \
		( \
			42, 43, 44, 45, 46, \
			47, 48, 49, 50, 51 \
		), \
		( \
			42, 41, 40, 39, 38, \
			37, 36, 35, 34, 33 \
		), \
		( \
			42, 43, 44, 45, 46, \
			47, 48, 49, 50, 51 \
		), \
		( \
			42, 41, 40, 39, 38, \
			37, 36, 35, 34, 33 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_43 \
		( \
			43, 44, 45, 46, 47, \
			48, 49, 50, 51, 52 \
		), \
		( \
			43, 42, 41, 40, 39, \
			38, 37, 36, 35, 34 \
		), \
		( \
			43, 44, 45, 46, 47, \
			48, 49, 50, 51, 52 \
		), \
		( \
			43, 42, 41, 40, 39, \
			38, 37, 36, 35, 34 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_44 \
		( \
			44, 45, 46, 47, 48, \
			49, 50, 51, 52, 53 \
		), \
		( \
			44, 43, 42, 41, 40, \
			39, 38, 37, 36, 35 \
		), \
		( \
			44, 45, 46, 47, 48, \
			49, 50, 51, 52, 53 \
		), \
		( \
			44, 43, 42, 41, 40, \
			39, 38, 37, 36, 35 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_45 \
		( \
			45, 46, 47, 48, 49, \
			50, 51, 52, 53, 54 \
		), \
		( \
			45, 44, 43, 42, 41, \
			40, 39, 38, 37, 36 \
		), \
		( \
			45, 46, 47, 48, 49, \
			50, 51, 52, 53, 54 \
		), \
		( \
			45, 44, 43, 42, 41, \
			40, 39, 38, 37, 36 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_46 \
		( \
			46, 47, 48, 49, 50, \
			51, 52, 53, 54, 55 \
		), \
		( \
			46, 45, 44, 43, 42, \
			41, 40, 39, 38, 37 \
		), \
		( \
			46, 47, 48, 49, 50, \
			51, 52, 53, 54, 55 \
		), \
		( \
			46, 45, 44, 43, 42, \
			41, 40, 39, 38, 37 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_47 \
		( \
			47, 48, 49, 50, 51, \
			52, 53, 54, 55, 56 \
		), \
		( \
			47, 46, 45, 44, 43, \
			42, 41, 40, 39, 38 \
		), \
		( \
			47, 48, 49, 50, 51, \
			52, 53, 54, 55, 56 \
		), \
		( \
			47, 46, 45, 44, 43, \
			42, 41, 40, 39, 38 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_48 \
		( \
			48, 49, 50, 51, 52, \
			53, 54, 55, 56, 57 \
		), \
		( \
			48, 47, 46, 45, 44, \
			43, 42, 41, 40, 39 \
		), \
		( \
			48, 49, 50, 51, 52, \
			53, 54, 55, 56, 57 \
		), \
		( \
			48, 47, 46, 45, 44, \
			43, 42, 41, 40, 39 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_49 \
		( \
			49, 50, 51, 52, 53, \
			54, 55, 56, 57, 58 \
		), \
		( \
			49, 48, 47, 46, 45, \
			44, 43, 42, 41, 40 \
		), \
		( \
			49, 50, 51, 52, 53, \
			54, 55, 56, 57, 58 \
		), \
		( \
			49, 48, 47, 46, 45, \
			44, 43, 42, 41, 40 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_50 \
		( \
			50, 51, 52, 53, 54, \
			55, 56, 57, 58, 59 \
		), \
		( \
			50, 49, 48, 47, 46, \
			45, 44, 43, 42, 41 \
		), \
		( \
			50, 51, 52, 53, 54, \
			55, 56, 57, 58, 59 \
		), \
		( \
			50, 49, 48, 47, 46, \
			45, 44, 43, 42, 41 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_51 \
		( \
			51, 52, 53, 54, 55, \
			56, 57, 58, 59, 60 \
		), \
		( \
			51, 50, 49, 48, 47, \
			46, 45, 44, 43, 42 \
		), \
		( \
			51, 52, 53, 54, 55, \
			56, 57, 58, 59, 60 \
		), \
		( \
			51, 50, 49, 48, 47, \
			46, 45, 44, 43, 42 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_52 \
		( \
			52, 53, 54, 55, 56, \
			57, 58, 59, 60, 61 \
		), \
		( \
			52, 51, 50, 49, 48, \
			47, 46, 45, 44, 43 \
		), \
		( \
			52, 53, 54, 55, 56, \
			57, 58, 59, 60, 61 \
		), \
		( \
			52, 51, 50, 49, 48, \
			47, 46, 45, 44, 43 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_53 \
		( \
			53, 54, 55, 56, 57, \
			58, 59, 60, 61, 62 \
		), \
		( \
			53, 52, 51, 50, 49, \
			48, 47, 46, 45, 44 \
		), \
		( \
			53, 54, 55, 56, 57, \
			58, 59, 60, 61, 62 \
		), \
		( \
			53, 52, 51, 50, 49, \
			48, 47, 46, 45, 44 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_54 \
		( \
			54, 55, 56, 57, 58, \
			59, 60, 61, 62, 63 \
		), \
		( \
			54, 53, 52, 51, 50, \
			49, 48, 47, 46, 45 \
		), \
		( \
			54, 55, 56, 57, 58, \
			59, 60, 61, 62, 63 \
		), \
		( \
			54, 53, 52, 51, 50, \
			49, 48, 47, 46, 45 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_55 \
		( \
			55, 56, 57, 58, 59, \
			60, 61, 62, 63, 64 \
		), \
		( \
			55, 54, 53, 52, 51, \
			50, 49, 48, 47, 46 \
		), \
		( \
			55, 56, 57, 58, 59, \
			60, 61, 62, 63, 64 \
		), \
		( \
			55, 54, 53, 52, 51, \
			50, 49, 48, 47, 46 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_56 \
		( \
			56, 57, 58, 59, 60, \
			61, 62, 63, 64, 65 \
		), \
		( \
			56, 55, 54, 53, 52, \
			51, 50, 49, 48, 47 \
		), \
		( \
			56, 57, 58, 59, 60, \
			61, 62, 63, 64, 65 \
		), \
		( \
			56, 55, 54, 53, 52, \
			51, 50, 49, 48, 47 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_57 \
		( \
			57, 58, 59, 60, 61, \
			62, 63, 64, 65, 66 \
		), \
		( \
			57, 56, 55, 54, 53, \
			52, 51, 50, 49, 48 \
		), \
		( \
			57, 58, 59, 60, 61, \
			62, 63, 64, 65, 66 \
		), \
		( \
			57, 56, 55, 54, 53, \
			52, 51, 50, 49, 48 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_58 \
		( \
			58, 59, 60, 61, 62, \
			63, 64, 65, 66, 67 \
		), \
		( \
			58, 57, 56, 55, 54, \
			53, 52, 51, 50, 49 \
		), \
		( \
			58, 59, 60, 61, 62, \
			63, 64, 65, 66, 67 \
		), \
		( \
			58, 57, 56, 55, 54, \
			53, 52, 51, 50, 49 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_59 \
		( \
			59, 60, 61, 62, 63, \
			64, 65, 66, 67, 68 \
		), \
		( \
			59, 58, 57, 56, 55, \
			54, 53, 52, 51, 50 \
		), \
		( \
			59, 60, 61, 62, 63, \
			64, 65, 66, 67, 68 \
		), \
		( \
			59, 58, 57, 56, 55, \
			54, 53, 52, 51, 50 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_60 \
		( \
			60, 61, 62, 63, 64, \
			65, 66, 67, 68, 69 \
		), \
		( \
			60, 59, 58, 57, 56, \
			55, 54, 53, 52, 51 \
		), \
		( \
			60, 61, 62, 63, 64, \
			65, 66, 67, 68, 69 \
		), \
		( \
			60, 59, 58, 57, 56, \
			55, 54, 53, 52, 51 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_61 \
		( \
			61, 62, 63, 64, 65, \
			66, 67, 68, 69, 70 \
		), \
		( \
			61, 60, 59, 58, 57, \
			56, 55, 54, 53, 52 \
		), \
		( \
			61, 62, 63, 64, 65, \
			66, 67, 68, 69, 70 \
		), \
		( \
			61, 60, 59, 58, 57, \
			56, 55, 54, 53, 52 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_62 \
		( \
			62, 63, 64, 65, 66, \
			67, 68, 69, 70, 71 \
		), \
		( \
			62, 61, 60, 59, 58, \
			57, 56, 55, 54, 53 \
		), \
		( \
			62, 63, 64, 65, 66, \
			67, 68, 69, 70, 71 \
		), \
		( \
			62, 61, 60, 59, 58, \
			57, 56, 55, 54, 53 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_63 \
		( \
			63, 64, 65, 66, 67, \
			68, 69, 70, 71, 72 \
		), \
		( \
			63, 62, 61, 60, 59, \
			58, 57, 56, 55, 54 \
		), \
		( \
			63, 64, 65, 66, 67, \
			68, 69, 70, 71, 72 \
		), \
		( \
			63, 62, 61, 60, 59, \
			58, 57, 56, 55, 54 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_64 \
		( \
			64, 65, 66, 67, 68, \
			69, 70, 71, 72, 73 \
		), \
		( \
			64, 63, 62, 61, 60, \
			59, 58, 57, 56, 55 \
		), \
		( \
			64, 65, 66, 67, 68, \
			69, 70, 71, 72, 73 \
		), \
		( \
			64, 63, 62, 61, 60, \
			59, 58, 57, 56, 55 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_65 \
		( \
			65, 66, 67, 68, 69, \
			70, 71, 72, 73, 74 \
		), \
		( \
			65, 64, 63, 62, 61, \
			60, 59, 58, 57, 56 \
		), \
		( \
			65, 66, 67, 68, 69, \
			70, 71, 72, 73, 74 \
		), \
		( \
			65, 64, 63, 62, 61, \
			60, 59, 58, 57, 56 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_66 \
		( \
			66, 67, 68, 69, 70, \
			71, 72, 73, 74, 75 \
		), \
		( \
			66, 65, 64, 63, 62, \
			61, 60, 59, 58, 57 \
		), \
		( \
			66, 67, 68, 69, 70, \
			71, 72, 73, 74, 75 \
		), \
		( \
			66, 65, 64, 63, 62, \
			61, 60, 59, 58, 57 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_67 \
		( \
			67, 68, 69, 70, 71, \
			72, 73, 74, 75, 76 \
		), \
		( \
			67, 66, 65, 64, 63, \
			62, 61, 60, 59, 58 \
		), \
		( \
			67, 68, 69, 70, 71, \
			72, 73, 74, 75, 76 \
		), \
		( \
			67, 66, 65, 64, 63, \
			62, 61, 60, 59, 58 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_68 \
		( \
			68, 69, 70, 71, 72, \
			73, 74, 75, 76, 77 \
		), \
		( \
			68, 67, 66, 65, 64, \
			63, 62, 61, 60, 59 \
		), \
		( \
			68, 69, 70, 71, 72, \
			73, 74, 75, 76, 77 \
		), \
		( \
			68, 67, 66, 65, 64, \
			63, 62, 61, 60, 59 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_69 \
		( \
			69, 70, 71, 72, 73, \
			74, 75, 76, 77, 78 \
		), \
		( \
			69, 68, 67, 66, 65, \
			64, 63, 62, 61, 60 \
		), \
		( \
			69, 70, 71, 72, 73, \
			74, 75, 76, 77, 78 \
		), \
		( \
			69, 68, 67, 66, 65, \
			64, 63, 62, 61, 60 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_70 \
		( \
			70, 71, 72, 73, 74, \
			75, 76, 77, 78, 79 \
		), \
		( \
			70, 69, 68, 67, 66, \
			65, 64, 63, 62, 61 \
		), \
		( \
			70, 71, 72, 73, 74, \
			75, 76, 77, 78, 79 \
		), \
		( \
			70, 69, 68, 67, 66, \
			65, 64, 63, 62, 61 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_71 \
		( \
			71, 72, 73, 74, 75, \
			76, 77, 78, 79, 80 \
		), \
		( \
			71, 70, 69, 68, 67, \
			66, 65, 64, 63, 62 \
		), \
		( \
			71, 72, 73, 74, 75, \
			76, 77, 78, 79, 80 \
		), \
		( \
			71, 70, 69, 68, 67, \
			66, 65, 64, 63, 62 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_72 \
		( \
			72, 73, 74, 75, 76, \
			77, 78, 79, 80, 81 \
		), \
		( \
			72, 71, 70, 69, 68, \
			67, 66, 65, 64, 63 \
		), \
		( \
			72, 73, 74, 75, 76, \
			77, 78, 79, 80, 81 \
		), \
		( \
			72, 71, 70, 69, 68, \
			67, 66, 65, 64, 63 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_73 \
		( \
			73, 74, 75, 76, 77, \
			78, 79, 80, 81, 82 \
		), \
		( \
			73, 72, 71, 70, 69, \
			68, 67, 66, 65, 64 \
		), \
		( \
			73, 74, 75, 76, 77, \
			78, 79, 80, 81, 82 \
		), \
		( \
			73, 72, 71, 70, 69, \
			68, 67, 66, 65, 64 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_74 \
		( \
			74, 75, 76, 77, 78, \
			79, 80, 81, 82, 83 \
		), \
		( \
			74, 73, 72, 71, 70, \
			69, 68, 67, 66, 65 \
		), \
		( \
			74, 75, 76, 77, 78, \
			79, 80, 81, 82, 83 \
		), \
		( \
			74, 73, 72, 71, 70, \
			69, 68, 67, 66, 65 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_75 \
		( \
			75, 76, 77, 78, 79, \
			80, 81, 82, 83, 84 \
		), \
		( \
			75, 74, 73, 72, 71, \
			70, 69, 68, 67, 66 \
		), \
		( \
			75, 76, 77, 78, 79, \
			80, 81, 82, 83, 84 \
		), \
		( \
			75, 74, 73, 72, 71, \
			70, 69, 68, 67, 66 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_76 \
		( \
			76, 77, 78, 79, 80, \
			81, 82, 83, 84, 85 \
		), \
		( \
			76, 75, 74, 73, 72, \
			71, 70, 69, 68, 67 \
		), \
		( \
			76, 77, 78, 79, 80, \
			81, 82, 83, 84, 85 \
		), \
		( \
			76, 75, 74, 73, 72, \
			71, 70, 69, 68, 67 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_77 \
		( \
			77, 78, 79, 80, 81, \
			82, 83, 84, 85, 86 \
		), \
		( \
			77, 76, 75, 74, 73, \
			72, 71, 70, 69, 68 \
		), \
		( \
			77, 78, 79, 80, 81, \
			82, 83, 84, 85, 86 \
		), \
		( \
			77, 76, 75, 74, 73, \
			72, 71, 70, 69, 68 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_78 \
		( \
			78, 79, 80, 81, 82, \
			83, 84, 85, 86, 87 \
		), \
		( \
			78, 77, 76, 75, 74, \
			73, 72, 71, 70, 69 \
		), \
		( \
			78, 79, 80, 81, 82, \
			83, 84, 85, 86, 87 \
		), \
		( \
			78, 77, 76, 75, 74, \
			73, 72, 71, 70, 69 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_79 \
		( \
			79, 80, 81, 82, 83, \
			84, 85, 86, 87, 88 \
		), \
		( \
			79, 78, 77, 76, 75, \
			74, 73, 72, 71, 70 \
		), \
		( \
			79, 80, 81, 82, 83, \
			84, 85, 86, 87, 88 \
		), \
		( \
			79, 78, 77, 76, 75, \
			74, 73, 72, 71, 70 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_80 \
		( \
			80, 81, 82, 83, 84, \
			85, 86, 87, 88, 89 \
		), \
		( \
			80, 79, 78, 77, 76, \
			75, 74, 73, 72, 71 \
		), \
		( \
			80, 81, 82, 83, 84, \
			85, 86, 87, 88, 89 \
		), \
		( \
			80, 79, 78, 77, 76, \
			75, 74, 73, 72, 71 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_81 \
		( \
			81, 82, 83, 84, 85, \
			86, 87, 88, 89, 90 \
		), \
		( \
			81, 80, 79, 78, 77, \
			76, 75, 74, 73, 72 \
		), \
		( \
			81, 82, 83, 84, 85, \
			86, 87, 88, 89, 90 \
		), \
		( \
			81, 80, 79, 78, 77, \
			76, 75, 74, 73, 72 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_82 \
		( \
			82, 83, 84, 85, 86, \
			87, 88, 89, 90, 91 \
		), \
		( \
			82, 81, 80, 79, 78, \
			77, 76, 75, 74, 73 \
		), \
		( \
			82, 83, 84, 85, 86, \
			87, 88, 89, 90, 91 \
		), \
		( \
			82, 81, 80, 79, 78, \
			77, 76, 75, 74, 73 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_83 \
		( \
			83, 84, 85, 86, 87, \
			88, 89, 90, 91, 92 \
		), \
		( \
			83, 82, 81, 80, 79, \
			78, 77, 76, 75, 74 \
		), \
		( \
			83, 84, 85, 86, 87, \
			88, 89, 90, 91, 92 \
		), \
		( \
			83, 82, 81, 80, 79, \
			78, 77, 76, 75, 74 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_84 \
		( \
			84, 85, 86, 87, 88, \
			89, 90, 91, 92, 93 \
		), \
		( \
			84, 83, 82, 81, 80, \
			79, 78, 77, 76, 75 \
		), \
		( \
			84, 85, 86, 87, 88, \
			89, 90, 91, 92, 93 \
		), \
		( \
			84, 83, 82, 81, 80, \
			79, 78, 77, 76, 75 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_85 \
		( \
			85, 86, 87, 88, 89, \
			90, 91, 92, 93, 94 \
		), \
		( \
			85, 84, 83, 82, 81, \
			80, 79, 78, 77, 76 \
		), \
		( \
			85, 86, 87, 88, 89, \
			90, 91, 92, 93, 94 \
		), \
		( \
			85, 84, 83, 82, 81, \
			80, 79, 78, 77, 76 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_86 \
		( \
			86, 87, 88, 89, 90, \
			91, 92, 93, 94, 95 \
		), \
		( \
			86, 85, 84, 83, 82, \
			81, 80, 79, 78, 77 \
		), \
		( \
			86, 87, 88, 89, 90, \
			91, 92, 93, 94, 95 \
		), \
		( \
			86, 85, 84, 83, 82, \
			81, 80, 79, 78, 77 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_87 \
		( \
			87, 88, 89, 90, 91, \
			92, 93, 94, 95, 96 \
		), \
		( \
			87, 86, 85, 84, 83, \
			82, 81, 80, 79, 78 \
		), \
		( \
			87, 88, 89, 90, 91, \
			92, 93, 94, 95, 96 \
		), \
		( \
			87, 86, 85, 84, 83, \
			82, 81, 80, 79, 78 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_88 \
		( \
			88, 89, 90, 91, 92, \
			93, 94, 95, 96, 97 \
		), \
		( \
			88, 87, 86, 85, 84, \
			83, 82, 81, 80, 79 \
		), \
		( \
			88, 89, 90, 91, 92, \
			93, 94, 95, 96, 97 \
		), \
		( \
			88, 87, 86, 85, 84, \
			83, 82, 81, 80, 79 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_89 \
		( \
			89, 90, 91, 92, 93, \
			94, 95, 96, 97, 98 \
		), \
		( \
			89, 88, 87, 86, 85, \
			84, 83, 82, 81, 80 \
		), \
		( \
			89, 90, 91, 92, 93, \
			94, 95, 96, 97, 98 \
		), \
		( \
			89, 88, 87, 86, 85, \
			84, 83, 82, 81, 80 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_90 \
		( \
			90, 91, 92, 93, 94, \
			95, 96, 97, 98, 99 \
		), \
		( \
			90, 89, 88, 87, 86, \
			85, 84, 83, 82, 81 \
		), \
		( \
			90, 91, 92, 93, 94, \
			95, 96, 97, 98, 99 \
		), \
		( \
			90, 89, 88, 87, 86, \
			85, 84, 83, 82, 81 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_91 \
		( \
			91, 92, 93, 94, 95, \
			96, 97, 98, 99, 100 \
		), \
		( \
			91, 90, 89, 88, 87, \
			86, 85, 84, 83, 82 \
		), \
		( \
			91, 92, 93, 94, 95, \
			96, 97, 98, 99, 100 \
		), \
		( \
			91, 90, 89, 88, 87, \
			86, 85, 84, 83, 82 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_92 \
		( \
			92, 93, 94, 95, 96, \
			97, 98, 99, 100, 101 \
		), \
		( \
			92, 91, 90, 89, 88, \
			87, 86, 85, 84, 83 \
		), \
		( \
			92, 93, 94, 95, 96, \
			97, 98, 99, 100, 101 \
		), \
		( \
			92, 91, 90, 89, 88, \
			87, 86, 85, 84, 83 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_93 \
		( \
			93, 94, 95, 96, 97, \
			98, 99, 100, 101, 102 \
		), \
		( \
			93, 92, 91, 90, 89, \
			88, 87, 86, 85, 84 \
		), \
		( \
			93, 94, 95, 96, 97, \
			98, 99, 100, 101, 102 \
		), \
		( \
			93, 92, 91, 90, 89, \
			88, 87, 86, 85, 84 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_94 \
		( \
			94, 95, 96, 97, 98, \
			99, 100, 101, 102, 103 \
		), \
		( \
			94, 93, 92, 91, 90, \
			89, 88, 87, 86, 85 \
		), \
		( \
			94, 95, 96, 97, 98, \
			99, 100, 101, 102, 103 \
		), \
		( \
			94, 93, 92, 91, 90, \
			89, 88, 87, 86, 85 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_95 \
		( \
			95, 96, 97, 98, 99, \
			100, 101, 102, 103, 104 \
		), \
		( \
			95, 94, 93, 92, 91, \
			90, 89, 88, 87, 86 \
		), \
		( \
			95, 96, 97, 98, 99, \
			100, 101, 102, 103, 104 \
		), \
		( \
			95, 94, 93, 92, 91, \
			90, 89, 88, 87, 86 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_96 \
		( \
			96, 97, 98, 99, 100, \
			101, 102, 103, 104, 105 \
		), \
		( \
			96, 95, 94, 93, 92, \
			91, 90, 89, 88, 87 \
		), \
		( \
			96, 97, 98, 99, 100, \
			101, 102, 103, 104, 105 \
		), \
		( \
			96, 95, 94, 93, 92, \
			91, 90, 89, 88, 87 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_97 \
		( \
			97, 98, 99, 100, 101, \
			102, 103, 104, 105, 106 \
		), \
		( \
			97, 96, 95, 94, 93, \
			92, 91, 90, 89, 88 \
		), \
		( \
			97, 98, 99, 100, 101, \
			102, 103, 104, 105, 106 \
		), \
		( \
			97, 96, 95, 94, 93, \
			92, 91, 90, 89, 88 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_98 \
		( \
			98, 99, 100, 101, 102, \
			103, 104, 105, 106, 107 \
		), \
		( \
			98, 97, 96, 95, 94, \
			93, 92, 91, 90, 89 \
		), \
		( \
			98, 99, 100, 101, 102, \
			103, 104, 105, 106, 107 \
		), \
		( \
			98, 97, 96, 95, 94, \
			93, 92, 91, 90, 89 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_99 \
		( \
			99, 100, 101, 102, 103, \
			104, 105, 106, 107, 108 \
		), \
		( \
			99, 98, 97, 96, 95, \
			94, 93, 92, 91, 90 \
		), \
		( \
			99, 100, 101, 102, 103, \
			104, 105, 106, 107, 108 \
		), \
		( \
			99, 98, 97, 96, 95, \
			94, 93, 92, 91, 90 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_100 \
		( \
			100, 101, 102, 103, 104, \
			105, 106, 107, 108, 109 \
		), \
		( \
			100, 99, 98, 97, 96, \
			95, 94, 93, 92, 91 \
		), \
		( \
			100, 101, 102, 103, 104, \
			105, 106, 107, 108, 109 \
		), \
		( \
			100, 99, 98, 97, 96, \
			95, 94, 93, 92, 91 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_101 \
		( \
			101, 102, 103, 104, 105, \
			106, 107, 108, 109, 110 \
		), \
		( \
			101, 100, 99, 98, 97, \
			96, 95, 94, 93, 92 \
		), \
		( \
			101, 102, 103, 104, 105, \
			106, 107, 108, 109, 110 \
		), \
		( \
			101, 100, 99, 98, 97, \
			96, 95, 94, 93, 92 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_102 \
		( \
			102, 103, 104, 105, 106, \
			107, 108, 109, 110, 111 \
		), \
		( \
			102, 101, 100, 99, 98, \
			97, 96, 95, 94, 93 \
		), \
		( \
			102, 103, 104, 105, 106, \
			107, 108, 109, 110, 111 \
		), \
		( \
			102, 101, 100, 99, 98, \
			97, 96, 95, 94, 93 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_103 \
		( \
			103, 104, 105, 106, 107, \
			108, 109, 110, 111, 112 \
		), \
		( \
			103, 102, 101, 100, 99, \
			98, 97, 96, 95, 94 \
		), \
		( \
			103, 104, 105, 106, 107, \
			108, 109, 110, 111, 112 \
		), \
		( \
			103, 102, 101, 100, 99, \
			98, 97, 96, 95, 94 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_104 \
		( \
			104, 105, 106, 107, 108, \
			109, 110, 111, 112, 113 \
		), \
		( \
			104, 103, 102, 101, 100, \
			99, 98, 97, 96, 95 \
		), \
		( \
			104, 105, 106, 107, 108, \
			109, 110, 111, 112, 113 \
		), \
		( \
			104, 103, 102, 101, 100, \
			99, 98, 97, 96, 95 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_105 \
		( \
			105, 106, 107, 108, 109, \
			110, 111, 112, 113, 114 \
		), \
		( \
			105, 104, 103, 102, 101, \
			100, 99, 98, 97, 96 \
		), \
		( \
			105, 106, 107, 108, 109, \
			110, 111, 112, 113, 114 \
		), \
		( \
			105, 104, 103, 102, 101, \
			100, 99, 98, 97, 96 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_106 \
		( \
			106, 107, 108, 109, 110, \
			111, 112, 113, 114, 115 \
		), \
		( \
			106, 105, 104, 103, 102, \
			101, 100, 99, 98, 97 \
		), \
		( \
			106, 107, 108, 109, 110, \
			111, 112, 113, 114, 115 \
		), \
		( \
			106, 105, 104, 103, 102, \
			101, 100, 99, 98, 97 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_107 \
		( \
			107, 108, 109, 110, 111, \
			112, 113, 114, 115, 116 \
		), \
		( \
			107, 106, 105, 104, 103, \
			102, 101, 100, 99, 98 \
		), \
		( \
			107, 108, 109, 110, 111, \
			112, 113, 114, 115, 116 \
		), \
		( \
			107, 106, 105, 104, 103, \
			102, 101, 100, 99, 98 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_108 \
		( \
			108, 109, 110, 111, 112, \
			113, 114, 115, 116, 117 \
		), \
		( \
			108, 107, 106, 105, 104, \
			103, 102, 101, 100, 99 \
		), \
		( \
			108, 109, 110, 111, 112, \
			113, 114, 115, 116, 117 \
		), \
		( \
			108, 107, 106, 105, 104, \
			103, 102, 101, 100, 99 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_109 \
		( \
			109, 110, 111, 112, 113, \
			114, 115, 116, 117, 118 \
		), \
		( \
			109, 108, 107, 106, 105, \
			104, 103, 102, 101, 100 \
		), \
		( \
			109, 110, 111, 112, 113, \
			114, 115, 116, 117, 118 \
		), \
		( \
			109, 108, 107, 106, 105, \
			104, 103, 102, 101, 100 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_110 \
		( \
			110, 111, 112, 113, 114, \
			115, 116, 117, 118, 119 \
		), \
		( \
			110, 109, 108, 107, 106, \
			105, 104, 103, 102, 101 \
		), \
		( \
			110, 111, 112, 113, 114, \
			115, 116, 117, 118, 119 \
		), \
		( \
			110, 109, 108, 107, 106, \
			105, 104, 103, 102, 101 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_111 \
		( \
			111, 112, 113, 114, 115, \
			116, 117, 118, 119, 120 \
		), \
		( \
			111, 110, 109, 108, 107, \
			106, 105, 104, 103, 102 \
		), \
		( \
			111, 112, 113, 114, 115, \
			116, 117, 118, 119, 120 \
		), \
		( \
			111, 110, 109, 108, 107, \
			106, 105, 104, 103, 102 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_112 \
		( \
			112, 113, 114, 115, 116, \
			117, 118, 119, 120, 121 \
		), \
		( \
			112, 111, 110, 109, 108, \
			107, 106, 105, 104, 103 \
		), \
		( \
			112, 113, 114, 115, 116, \
			117, 118, 119, 120, 121 \
		), \
		( \
			112, 111, 110, 109, 108, \
			107, 106, 105, 104, 103 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_113 \
		( \
			113, 114, 115, 116, 117, \
			118, 119, 120, 121, 122 \
		), \
		( \
			113, 112, 111, 110, 109, \
			108, 107, 106, 105, 104 \
		), \
		( \
			113, 114, 115, 116, 117, \
			118, 119, 120, 121, 122 \
		), \
		( \
			113, 112, 111, 110, 109, \
			108, 107, 106, 105, 104 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_114 \
		( \
			114, 115, 116, 117, 118, \
			119, 120, 121, 122, 123 \
		), \
		( \
			114, 113, 112, 111, 110, \
			109, 108, 107, 106, 105 \
		), \
		( \
			114, 115, 116, 117, 118, \
			119, 120, 121, 122, 123 \
		), \
		( \
			114, 113, 112, 111, 110, \
			109, 108, 107, 106, 105 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_115 \
		( \
			115, 116, 117, 118, 119, \
			120, 121, 122, 123, 124 \
		), \
		( \
			115, 114, 113, 112, 111, \
			110, 109, 108, 107, 106 \
		), \
		( \
			115, 116, 117, 118, 119, \
			120, 121, 122, 123, 124 \
		), \
		( \
			115, 114, 113, 112, 111, \
			110, 109, 108, 107, 106 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_116 \
		( \
			116, 117, 118, 119, 120, \
			121, 122, 123, 124, 125 \
		), \
		( \
			116, 115, 114, 113, 112, \
			111, 110, 109, 108, 107 \
		), \
		( \
			116, 117, 118, 119, 120, \
			121, 122, 123, 124, 125 \
		), \
		( \
			116, 115, 114, 113, 112, \
			111, 110, 109, 108, 107 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_117 \
		( \
			117, 118, 119, 120, 121, \
			122, 123, 124, 125, 126 \
		), \
		( \
			117, 116, 115, 114, 113, \
			112, 111, 110, 109, 108 \
		), \
		( \
			117, 118, 119, 120, 121, \
			122, 123, 124, 125, 126 \
		), \
		( \
			117, 116, 115, 114, 113, \
			112, 111, 110, 109, 108 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_118 \
		( \
			118, 119, 120, 121, 122, \
			123, 124, 125, 126, 127 \
		), \
		( \
			118, 117, 116, 115, 114, \
			113, 112, 111, 110, 109 \
		), \
		( \
			118, 119, 120, 121, 122, \
			123, 124, 125, 126, 127 \
		), \
		( \
			118, 117, 116, 115, 114, \
			113, 112, 111, 110, 109 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_119 \
		( \
			119, 120, 121, 122, 123, \
			124, 125, 126, 127, 128 \
		), \
		( \
			119, 118, 117, 116, 115, \
			114, 113, 112, 111, 110 \
		), \
		( \
			119, 120, 121, 122, 123, \
			124, 125, 126, 127, 128 \
		), \
		( \
			119, 118, 117, 116, 115, \
			114, 113, 112, 111, 110 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_120 \
		( \
			120, 121, 122, 123, 124, \
			125, 126, 127, 128, 129 \
		), \
		( \
			120, 119, 118, 117, 116, \
			115, 114, 113, 112, 111 \
		), \
		( \
			120, 121, 122, 123, 124, \
			125, 126, 127, 128, 129 \
		), \
		( \
			120, 119, 118, 117, 116, \
			115, 114, 113, 112, 111 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_121 \
		( \
			121, 122, 123, 124, 125, \
			126, 127, 128, 129, 130 \
		), \
		( \
			121, 120, 119, 118, 117, \
			116, 115, 114, 113, 112 \
		), \
		( \
			121, 122, 123, 124, 125, \
			126, 127, 128, 129, 130 \
		), \
		( \
			121, 120, 119, 118, 117, \
			116, 115, 114, 113, 112 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_122 \
		( \
			122, 123, 124, 125, 126, \
			127, 128, 129, 130, 131 \
		), \
		( \
			122, 121, 120, 119, 118, \
			117, 116, 115, 114, 113 \
		), \
		( \
			122, 123, 124, 125, 126, \
			127, 128, 129, 130, 131 \
		), \
		( \
			122, 121, 120, 119, 118, \
			117, 116, 115, 114, 113 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_123 \
		( \
			123, 124, 125, 126, 127, \
			128, 129, 130, 131, 132 \
		), \
		( \
			123, 122, 121, 120, 119, \
			118, 117, 116, 115, 114 \
		), \
		( \
			123, 124, 125, 126, 127, \
			128, 129, 130, 131, 132 \
		), \
		( \
			123, 122, 121, 120, 119, \
			118, 117, 116, 115, 114 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_124 \
		( \
			124, 125, 126, 127, 128, \
			129, 130, 131, 132, 133 \
		), \
		( \
			124, 123, 122, 121, 120, \
			119, 118, 117, 116, 115 \
		), \
		( \
			124, 125, 126, 127, 128, \
			129, 130, 131, 132, 133 \
		), \
		( \
			124, 123, 122, 121, 120, \
			119, 118, 117, 116, 115 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_125 \
		( \
			125, 126, 127, 128, 129, \
			130, 131, 132, 133, 134 \
		), \
		( \
			125, 124, 123, 122, 121, \
			120, 119, 118, 117, 116 \
		), \
		( \
			125, 126, 127, 128, 129, \
			130, 131, 132, 133, 134 \
		), \
		( \
			125, 124, 123, 122, 121, \
			120, 119, 118, 117, 116 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_126 \
		( \
			126, 127, 128, 129, 130, \
			131, 132, 133, 134, 135 \
		), \
		( \
			126, 125, 124, 123, 122, \
			121, 120, 119, 118, 117 \
		), \
		( \
			126, 127, 128, 129, 130, \
			131, 132, 133, 134, 135 \
		), \
		( \
			126, 125, 124, 123, 122, \
			121, 120, 119, 118, 117 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_127 \
		( \
			127, 128, 129, 130, 131, \
			132, 133, 134, 135, 136 \
		), \
		( \
			127, 126, 125, 124, 123, \
			122, 121, 120, 119, 118 \
		), \
		( \
			127, 128, 129, 130, 131, \
			132, 133, 134, 135, 136 \
		), \
		( \
			127, 126, 125, 124, 123, \
			122, 121, 120, 119, 118 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_128 \
		( \
			128, 129, 130, 131, 132, \
			133, 134, 135, 136, 137 \
		), \
		( \
			128, 127, 126, 125, 124, \
			123, 122, 121, 120, 119 \
		), \
		( \
			128, 129, 130, 131, 132, \
			133, 134, 135, 136, 137 \
		), \
		( \
			128, 127, 126, 125, 124, \
			123, 122, 121, 120, 119 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_129 \
		( \
			129, 130, 131, 132, 133, \
			134, 135, 136, 137, 138 \
		), \
		( \
			129, 128, 127, 126, 125, \
			124, 123, 122, 121, 120 \
		), \
		( \
			129, 130, 131, 132, 133, \
			134, 135, 136, 137, 138 \
		), \
		( \
			129, 128, 127, 126, 125, \
			124, 123, 122, 121, 120 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_130 \
		( \
			130, 131, 132, 133, 134, \
			135, 136, 137, 138, 139 \
		), \
		( \
			130, 129, 128, 127, 126, \
			125, 124, 123, 122, 121 \
		), \
		( \
			130, 131, 132, 133, 134, \
			135, 136, 137, 138, 139 \
		), \
		( \
			130, 129, 128, 127, 126, \
			125, 124, 123, 122, 121 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_131 \
		( \
			131, 132, 133, 134, 135, \
			136, 137, 138, 139, 140 \
		), \
		( \
			131, 130, 129, 128, 127, \
			126, 125, 124, 123, 122 \
		), \
		( \
			131, 132, 133, 134, 135, \
			136, 137, 138, 139, 140 \
		), \
		( \
			131, 130, 129, 128, 127, \
			126, 125, 124, 123, 122 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_132 \
		( \
			132, 133, 134, 135, 136, \
			137, 138, 139, 140, 141 \
		), \
		( \
			132, 131, 130, 129, 128, \
			127, 126, 125, 124, 123 \
		), \
		( \
			132, 133, 134, 135, 136, \
			137, 138, 139, 140, 141 \
		), \
		( \
			132, 131, 130, 129, 128, \
			127, 126, 125, 124, 123 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_133 \
		( \
			133, 134, 135, 136, 137, \
			138, 139, 140, 141, 142 \
		), \
		( \
			133, 132, 131, 130, 129, \
			128, 127, 126, 125, 124 \
		), \
		( \
			133, 134, 135, 136, 137, \
			138, 139, 140, 141, 142 \
		), \
		( \
			133, 132, 131, 130, 129, \
			128, 127, 126, 125, 124 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_134 \
		( \
			134, 135, 136, 137, 138, \
			139, 140, 141, 142, 143 \
		), \
		( \
			134, 133, 132, 131, 130, \
			129, 128, 127, 126, 125 \
		), \
		( \
			134, 135, 136, 137, 138, \
			139, 140, 141, 142, 143 \
		), \
		( \
			134, 133, 132, 131, 130, \
			129, 128, 127, 126, 125 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_135 \
		( \
			135, 136, 137, 138, 139, \
			140, 141, 142, 143, 144 \
		), \
		( \
			135, 134, 133, 132, 131, \
			130, 129, 128, 127, 126 \
		), \
		( \
			135, 136, 137, 138, 139, \
			140, 141, 142, 143, 144 \
		), \
		( \
			135, 134, 133, 132, 131, \
			130, 129, 128, 127, 126 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_136 \
		( \
			136, 137, 138, 139, 140, \
			141, 142, 143, 144, 145 \
		), \
		( \
			136, 135, 134, 133, 132, \
			131, 130, 129, 128, 127 \
		), \
		( \
			136, 137, 138, 139, 140, \
			141, 142, 143, 144, 145 \
		), \
		( \
			136, 135, 134, 133, 132, \
			131, 130, 129, 128, 127 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_137 \
		( \
			137, 138, 139, 140, 141, \
			142, 143, 144, 145, 146 \
		), \
		( \
			137, 136, 135, 134, 133, \
			132, 131, 130, 129, 128 \
		), \
		( \
			137, 138, 139, 140, 141, \
			142, 143, 144, 145, 146 \
		), \
		( \
			137, 136, 135, 134, 133, \
			132, 131, 130, 129, 128 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_138 \
		( \
			138, 139, 140, 141, 142, \
			143, 144, 145, 146, 147 \
		), \
		( \
			138, 137, 136, 135, 134, \
			133, 132, 131, 130, 129 \
		), \
		( \
			138, 139, 140, 141, 142, \
			143, 144, 145, 146, 147 \
		), \
		( \
			138, 137, 136, 135, 134, \
			133, 132, 131, 130, 129 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_139 \
		( \
			139, 140, 141, 142, 143, \
			144, 145, 146, 147, 148 \
		), \
		( \
			139, 138, 137, 136, 135, \
			134, 133, 132, 131, 130 \
		), \
		( \
			139, 140, 141, 142, 143, \
			144, 145, 146, 147, 148 \
		), \
		( \
			139, 138, 137, 136, 135, \
			134, 133, 132, 131, 130 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_140 \
		( \
			140, 141, 142, 143, 144, \
			145, 146, 147, 148, 149 \
		), \
		( \
			140, 139, 138, 137, 136, \
			135, 134, 133, 132, 131 \
		), \
		( \
			140, 141, 142, 143, 144, \
			145, 146, 147, 148, 149 \
		), \
		( \
			140, 139, 138, 137, 136, \
			135, 134, 133, 132, 131 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_141 \
		( \
			141, 142, 143, 144, 145, \
			146, 147, 148, 149, 150 \
		), \
		( \
			141, 140, 139, 138, 137, \
			136, 135, 134, 133, 132 \
		), \
		( \
			141, 142, 143, 144, 145, \
			146, 147, 148, 149, 150 \
		), \
		( \
			141, 140, 139, 138, 137, \
			136, 135, 134, 133, 132 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_142 \
		( \
			142, 143, 144, 145, 146, \
			147, 148, 149, 150, 151 \
		), \
		( \
			142, 141, 140, 139, 138, \
			137, 136, 135, 134, 133 \
		), \
		( \
			142, 143, 144, 145, 146, \
			147, 148, 149, 150, 151 \
		), \
		( \
			142, 141, 140, 139, 138, \
			137, 136, 135, 134, 133 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_143 \
		( \
			143, 144, 145, 146, 147, \
			148, 149, 150, 151, 152 \
		), \
		( \
			143, 142, 141, 140, 139, \
			138, 137, 136, 135, 134 \
		), \
		( \
			143, 144, 145, 146, 147, \
			148, 149, 150, 151, 152 \
		), \
		( \
			143, 142, 141, 140, 139, \
			138, 137, 136, 135, 134 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_144 \
		( \
			144, 145, 146, 147, 148, \
			149, 150, 151, 152, 153 \
		), \
		( \
			144, 143, 142, 141, 140, \
			139, 138, 137, 136, 135 \
		), \
		( \
			144, 145, 146, 147, 148, \
			149, 150, 151, 152, 153 \
		), \
		( \
			144, 143, 142, 141, 140, \
			139, 138, 137, 136, 135 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_145 \
		( \
			145, 146, 147, 148, 149, \
			150, 151, 152, 153, 154 \
		), \
		( \
			145, 144, 143, 142, 141, \
			140, 139, 138, 137, 136 \
		), \
		( \
			145, 146, 147, 148, 149, \
			150, 151, 152, 153, 154 \
		), \
		( \
			145, 144, 143, 142, 141, \
			140, 139, 138, 137, 136 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_146 \
		( \
			146, 147, 148, 149, 150, \
			151, 152, 153, 154, 155 \
		), \
		( \
			146, 145, 144, 143, 142, \
			141, 140, 139, 138, 137 \
		), \
		( \
			146, 147, 148, 149, 150, \
			151, 152, 153, 154, 155 \
		), \
		( \
			146, 145, 144, 143, 142, \
			141, 140, 139, 138, 137 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_147 \
		( \
			147, 148, 149, 150, 151, \
			152, 153, 154, 155, 156 \
		), \
		( \
			147, 146, 145, 144, 143, \
			142, 141, 140, 139, 138 \
		), \
		( \
			147, 148, 149, 150, 151, \
			152, 153, 154, 155, 156 \
		), \
		( \
			147, 146, 145, 144, 143, \
			142, 141, 140, 139, 138 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_148 \
		( \
			148, 149, 150, 151, 152, \
			153, 154, 155, 156, 157 \
		), \
		( \
			148, 147, 146, 145, 144, \
			143, 142, 141, 140, 139 \
		), \
		( \
			148, 149, 150, 151, 152, \
			153, 154, 155, 156, 157 \
		), \
		( \
			148, 147, 146, 145, 144, \
			143, 142, 141, 140, 139 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_149 \
		( \
			149, 150, 151, 152, 153, \
			154, 155, 156, 157, 158 \
		), \
		( \
			149, 148, 147, 146, 145, \
			144, 143, 142, 141, 140 \
		), \
		( \
			149, 150, 151, 152, 153, \
			154, 155, 156, 157, 158 \
		), \
		( \
			149, 148, 147, 146, 145, \
			144, 143, 142, 141, 140 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_150 \
		( \
			150, 151, 152, 153, 154, \
			155, 156, 157, 158, 159 \
		), \
		( \
			150, 149, 148, 147, 146, \
			145, 144, 143, 142, 141 \
		), \
		( \
			150, 151, 152, 153, 154, \
			155, 156, 157, 158, 159 \
		), \
		( \
			150, 149, 148, 147, 146, \
			145, 144, 143, 142, 141 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_151 \
		( \
			151, 152, 153, 154, 155, \
			156, 157, 158, 159, 160 \
		), \
		( \
			151, 150, 149, 148, 147, \
			146, 145, 144, 143, 142 \
		), \
		( \
			151, 152, 153, 154, 155, \
			156, 157, 158, 159, 160 \
		), \
		( \
			151, 150, 149, 148, 147, \
			146, 145, 144, 143, 142 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_152 \
		( \
			152, 153, 154, 155, 156, \
			157, 158, 159, 160, 161 \
		), \
		( \
			152, 151, 150, 149, 148, \
			147, 146, 145, 144, 143 \
		), \
		( \
			152, 153, 154, 155, 156, \
			157, 158, 159, 160, 161 \
		), \
		( \
			152, 151, 150, 149, 148, \
			147, 146, 145, 144, 143 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_153 \
		( \
			153, 154, 155, 156, 157, \
			158, 159, 160, 161, 162 \
		), \
		( \
			153, 152, 151, 150, 149, \
			148, 147, 146, 145, 144 \
		), \
		( \
			153, 154, 155, 156, 157, \
			158, 159, 160, 161, 162 \
		), \
		( \
			153, 152, 151, 150, 149, \
			148, 147, 146, 145, 144 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_154 \
		( \
			154, 155, 156, 157, 158, \
			159, 160, 161, 162, 163 \
		), \
		( \
			154, 153, 152, 151, 150, \
			149, 148, 147, 146, 145 \
		), \
		( \
			154, 155, 156, 157, 158, \
			159, 160, 161, 162, 163 \
		), \
		( \
			154, 153, 152, 151, 150, \
			149, 148, 147, 146, 145 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_155 \
		( \
			155, 156, 157, 158, 159, \
			160, 161, 162, 163, 164 \
		), \
		( \
			155, 154, 153, 152, 151, \
			150, 149, 148, 147, 146 \
		), \
		( \
			155, 156, 157, 158, 159, \
			160, 161, 162, 163, 164 \
		), \
		( \
			155, 154, 153, 152, 151, \
			150, 149, 148, 147, 146 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_156 \
		( \
			156, 157, 158, 159, 160, \
			161, 162, 163, 164, 165 \
		), \
		( \
			156, 155, 154, 153, 152, \
			151, 150, 149, 148, 147 \
		), \
		( \
			156, 157, 158, 159, 160, \
			161, 162, 163, 164, 165 \
		), \
		( \
			156, 155, 154, 153, 152, \
			151, 150, 149, 148, 147 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_157 \
		( \
			157, 158, 159, 160, 161, \
			162, 163, 164, 165, 166 \
		), \
		( \
			157, 156, 155, 154, 153, \
			152, 151, 150, 149, 148 \
		), \
		( \
			157, 158, 159, 160, 161, \
			162, 163, 164, 165, 166 \
		), \
		( \
			157, 156, 155, 154, 153, \
			152, 151, 150, 149, 148 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_158 \
		( \
			158, 159, 160, 161, 162, \
			163, 164, 165, 166, 167 \
		), \
		( \
			158, 157, 156, 155, 154, \
			153, 152, 151, 150, 149 \
		), \
		( \
			158, 159, 160, 161, 162, \
			163, 164, 165, 166, 167 \
		), \
		( \
			158, 157, 156, 155, 154, \
			153, 152, 151, 150, 149 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_159 \
		( \
			159, 160, 161, 162, 163, \
			164, 165, 166, 167, 168 \
		), \
		( \
			159, 158, 157, 156, 155, \
			154, 153, 152, 151, 150 \
		), \
		( \
			159, 160, 161, 162, 163, \
			164, 165, 166, 167, 168 \
		), \
		( \
			159, 158, 157, 156, 155, \
			154, 153, 152, 151, 150 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_160 \
		( \
			160, 161, 162, 163, 164, \
			165, 166, 167, 168, 169 \
		), \
		( \
			160, 159, 158, 157, 156, \
			155, 154, 153, 152, 151 \
		), \
		( \
			160, 161, 162, 163, 164, \
			165, 166, 167, 168, 169 \
		), \
		( \
			160, 159, 158, 157, 156, \
			155, 154, 153, 152, 151 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_161 \
		( \
			161, 162, 163, 164, 165, \
			166, 167, 168, 169, 170 \
		), \
		( \
			161, 160, 159, 158, 157, \
			156, 155, 154, 153, 152 \
		), \
		( \
			161, 162, 163, 164, 165, \
			166, 167, 168, 169, 170 \
		), \
		( \
			161, 160, 159, 158, 157, \
			156, 155, 154, 153, 152 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_162 \
		( \
			162, 163, 164, 165, 166, \
			167, 168, 169, 170, 171 \
		), \
		( \
			162, 161, 160, 159, 158, \
			157, 156, 155, 154, 153 \
		), \
		( \
			162, 163, 164, 165, 166, \
			167, 168, 169, 170, 171 \
		), \
		( \
			162, 161, 160, 159, 158, \
			157, 156, 155, 154, 153 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_163 \
		( \
			163, 164, 165, 166, 167, \
			168, 169, 170, 171, 172 \
		), \
		( \
			163, 162, 161, 160, 159, \
			158, 157, 156, 155, 154 \
		), \
		( \
			163, 164, 165, 166, 167, \
			168, 169, 170, 171, 172 \
		), \
		( \
			163, 162, 161, 160, 159, \
			158, 157, 156, 155, 154 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_164 \
		( \
			164, 165, 166, 167, 168, \
			169, 170, 171, 172, 173 \
		), \
		( \
			164, 163, 162, 161, 160, \
			159, 158, 157, 156, 155 \
		), \
		( \
			164, 165, 166, 167, 168, \
			169, 170, 171, 172, 173 \
		), \
		( \
			164, 163, 162, 161, 160, \
			159, 158, 157, 156, 155 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_165 \
		( \
			165, 166, 167, 168, 169, \
			170, 171, 172, 173, 174 \
		), \
		( \
			165, 164, 163, 162, 161, \
			160, 159, 158, 157, 156 \
		), \
		( \
			165, 166, 167, 168, 169, \
			170, 171, 172, 173, 174 \
		), \
		( \
			165, 164, 163, 162, 161, \
			160, 159, 158, 157, 156 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_166 \
		( \
			166, 167, 168, 169, 170, \
			171, 172, 173, 174, 175 \
		), \
		( \
			166, 165, 164, 163, 162, \
			161, 160, 159, 158, 157 \
		), \
		( \
			166, 167, 168, 169, 170, \
			171, 172, 173, 174, 175 \
		), \
		( \
			166, 165, 164, 163, 162, \
			161, 160, 159, 158, 157 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_167 \
		( \
			167, 168, 169, 170, 171, \
			172, 173, 174, 175, 176 \
		), \
		( \
			167, 166, 165, 164, 163, \
			162, 161, 160, 159, 158 \
		), \
		( \
			167, 168, 169, 170, 171, \
			172, 173, 174, 175, 176 \
		), \
		( \
			167, 166, 165, 164, 163, \
			162, 161, 160, 159, 158 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_168 \
		( \
			168, 169, 170, 171, 172, \
			173, 174, 175, 176, 177 \
		), \
		( \
			168, 167, 166, 165, 164, \
			163, 162, 161, 160, 159 \
		), \
		( \
			168, 169, 170, 171, 172, \
			173, 174, 175, 176, 177 \
		), \
		( \
			168, 167, 166, 165, 164, \
			163, 162, 161, 160, 159 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_169 \
		( \
			169, 170, 171, 172, 173, \
			174, 175, 176, 177, 178 \
		), \
		( \
			169, 168, 167, 166, 165, \
			164, 163, 162, 161, 160 \
		), \
		( \
			169, 170, 171, 172, 173, \
			174, 175, 176, 177, 178 \
		), \
		( \
			169, 168, 167, 166, 165, \
			164, 163, 162, 161, 160 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_170 \
		( \
			170, 171, 172, 173, 174, \
			175, 176, 177, 178, 179 \
		), \
		( \
			170, 169, 168, 167, 166, \
			165, 164, 163, 162, 161 \
		), \
		( \
			170, 171, 172, 173, 174, \
			175, 176, 177, 178, 179 \
		), \
		( \
			170, 169, 168, 167, 166, \
			165, 164, 163, 162, 161 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_171 \
		( \
			171, 172, 173, 174, 175, \
			176, 177, 178, 179, 180 \
		), \
		( \
			171, 170, 169, 168, 167, \
			166, 165, 164, 163, 162 \
		), \
		( \
			171, 172, 173, 174, 175, \
			176, 177, 178, 179, 180 \
		), \
		( \
			171, 170, 169, 168, 167, \
			166, 165, 164, 163, 162 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_172 \
		( \
			172, 173, 174, 175, 176, \
			177, 178, 179, 180, 181 \
		), \
		( \
			172, 171, 170, 169, 168, \
			167, 166, 165, 164, 163 \
		), \
		( \
			172, 173, 174, 175, 176, \
			177, 178, 179, 180, 181 \
		), \
		( \
			172, 171, 170, 169, 168, \
			167, 166, 165, 164, 163 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_173 \
		( \
			173, 174, 175, 176, 177, \
			178, 179, 180, 181, 182 \
		), \
		( \
			173, 172, 171, 170, 169, \
			168, 167, 166, 165, 164 \
		), \
		( \
			173, 174, 175, 176, 177, \
			178, 179, 180, 181, 182 \
		), \
		( \
			173, 172, 171, 170, 169, \
			168, 167, 166, 165, 164 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_174 \
		( \
			174, 175, 176, 177, 178, \
			179, 180, 181, 182, 183 \
		), \
		( \
			174, 173, 172, 171, 170, \
			169, 168, 167, 166, 165 \
		), \
		( \
			174, 175, 176, 177, 178, \
			179, 180, 181, 182, 183 \
		), \
		( \
			174, 173, 172, 171, 170, \
			169, 168, 167, 166, 165 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_175 \
		( \
			175, 176, 177, 178, 179, \
			180, 181, 182, 183, 184 \
		), \
		( \
			175, 174, 173, 172, 171, \
			170, 169, 168, 167, 166 \
		), \
		( \
			175, 176, 177, 178, 179, \
			180, 181, 182, 183, 184 \
		), \
		( \
			175, 174, 173, 172, 171, \
			170, 169, 168, 167, 166 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_176 \
		( \
			176, 177, 178, 179, 180, \
			181, 182, 183, 184, 185 \
		), \
		( \
			176, 175, 174, 173, 172, \
			171, 170, 169, 168, 167 \
		), \
		( \
			176, 177, 178, 179, 180, \
			181, 182, 183, 184, 185 \
		), \
		( \
			176, 175, 174, 173, 172, \
			171, 170, 169, 168, 167 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_177 \
		( \
			177, 178, 179, 180, 181, \
			182, 183, 184, 185, 186 \
		), \
		( \
			177, 176, 175, 174, 173, \
			172, 171, 170, 169, 168 \
		), \
		( \
			177, 178, 179, 180, 181, \
			182, 183, 184, 185, 186 \
		), \
		( \
			177, 176, 175, 174, 173, \
			172, 171, 170, 169, 168 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_178 \
		( \
			178, 179, 180, 181, 182, \
			183, 184, 185, 186, 187 \
		), \
		( \
			178, 177, 176, 175, 174, \
			173, 172, 171, 170, 169 \
		), \
		( \
			178, 179, 180, 181, 182, \
			183, 184, 185, 186, 187 \
		), \
		( \
			178, 177, 176, 175, 174, \
			173, 172, 171, 170, 169 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_179 \
		( \
			179, 180, 181, 182, 183, \
			184, 185, 186, 187, 188 \
		), \
		( \
			179, 178, 177, 176, 175, \
			174, 173, 172, 171, 170 \
		), \
		( \
			179, 180, 181, 182, 183, \
			184, 185, 186, 187, 188 \
		), \
		( \
			179, 178, 177, 176, 175, \
			174, 173, 172, 171, 170 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_180 \
		( \
			180, 181, 182, 183, 184, \
			185, 186, 187, 188, 189 \
		), \
		( \
			180, 179, 178, 177, 176, \
			175, 174, 173, 172, 171 \
		), \
		( \
			180, 181, 182, 183, 184, \
			185, 186, 187, 188, 189 \
		), \
		( \
			180, 179, 178, 177, 176, \
			175, 174, 173, 172, 171 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_181 \
		( \
			181, 182, 183, 184, 185, \
			186, 187, 188, 189, 190 \
		), \
		( \
			181, 180, 179, 178, 177, \
			176, 175, 174, 173, 172 \
		), \
		( \
			181, 182, 183, 184, 185, \
			186, 187, 188, 189, 190 \
		), \
		( \
			181, 180, 179, 178, 177, \
			176, 175, 174, 173, 172 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_182 \
		( \
			182, 183, 184, 185, 186, \
			187, 188, 189, 190, 191 \
		), \
		( \
			182, 181, 180, 179, 178, \
			177, 176, 175, 174, 173 \
		), \
		( \
			182, 183, 184, 185, 186, \
			187, 188, 189, 190, 191 \
		), \
		( \
			182, 181, 180, 179, 178, \
			177, 176, 175, 174, 173 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_183 \
		( \
			183, 184, 185, 186, 187, \
			188, 189, 190, 191, 192 \
		), \
		( \
			183, 182, 181, 180, 179, \
			178, 177, 176, 175, 174 \
		), \
		( \
			183, 184, 185, 186, 187, \
			188, 189, 190, 191, 192 \
		), \
		( \
			183, 182, 181, 180, 179, \
			178, 177, 176, 175, 174 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_184 \
		( \
			184, 185, 186, 187, 188, \
			189, 190, 191, 192, 193 \
		), \
		( \
			184, 183, 182, 181, 180, \
			179, 178, 177, 176, 175 \
		), \
		( \
			184, 185, 186, 187, 188, \
			189, 190, 191, 192, 193 \
		), \
		( \
			184, 183, 182, 181, 180, \
			179, 178, 177, 176, 175 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_185 \
		( \
			185, 186, 187, 188, 189, \
			190, 191, 192, 193, 194 \
		), \
		( \
			185, 184, 183, 182, 181, \
			180, 179, 178, 177, 176 \
		), \
		( \
			185, 186, 187, 188, 189, \
			190, 191, 192, 193, 194 \
		), \
		( \
			185, 184, 183, 182, 181, \
			180, 179, 178, 177, 176 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_186 \
		( \
			186, 187, 188, 189, 190, \
			191, 192, 193, 194, 195 \
		), \
		( \
			186, 185, 184, 183, 182, \
			181, 180, 179, 178, 177 \
		), \
		( \
			186, 187, 188, 189, 190, \
			191, 192, 193, 194, 195 \
		), \
		( \
			186, 185, 184, 183, 182, \
			181, 180, 179, 178, 177 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_187 \
		( \
			187, 188, 189, 190, 191, \
			192, 193, 194, 195, 196 \
		), \
		( \
			187, 186, 185, 184, 183, \
			182, 181, 180, 179, 178 \
		), \
		( \
			187, 188, 189, 190, 191, \
			192, 193, 194, 195, 196 \
		), \
		( \
			187, 186, 185, 184, 183, \
			182, 181, 180, 179, 178 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_188 \
		( \
			188, 189, 190, 191, 192, \
			193, 194, 195, 196, 197 \
		), \
		( \
			188, 187, 186, 185, 184, \
			183, 182, 181, 180, 179 \
		), \
		( \
			188, 189, 190, 191, 192, \
			193, 194, 195, 196, 197 \
		), \
		( \
			188, 187, 186, 185, 184, \
			183, 182, 181, 180, 179 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_189 \
		( \
			189, 190, 191, 192, 193, \
			194, 195, 196, 197, 198 \
		), \
		( \
			189, 188, 187, 186, 185, \
			184, 183, 182, 181, 180 \
		), \
		( \
			189, 190, 191, 192, 193, \
			194, 195, 196, 197, 198 \
		), \
		( \
			189, 188, 187, 186, 185, \
			184, 183, 182, 181, 180 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_190 \
		( \
			190, 191, 192, 193, 194, \
			195, 196, 197, 198, 199 \
		), \
		( \
			190, 189, 188, 187, 186, \
			185, 184, 183, 182, 181 \
		), \
		( \
			190, 191, 192, 193, 194, \
			195, 196, 197, 198, 199 \
		), \
		( \
			190, 189, 188, 187, 186, \
			185, 184, 183, 182, 181 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_191 \
		( \
			191, 192, 193, 194, 195, \
			196, 197, 198, 199, 200 \
		), \
		( \
			191, 190, 189, 188, 187, \
			186, 185, 184, 183, 182 \
		), \
		( \
			191, 192, 193, 194, 195, \
			196, 197, 198, 199, 200 \
		), \
		( \
			191, 190, 189, 188, 187, \
			186, 185, 184, 183, 182 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_192 \
		( \
			192, 193, 194, 195, 196, \
			197, 198, 199, 200, 201 \
		), \
		( \
			192, 191, 190, 189, 188, \
			187, 186, 185, 184, 183 \
		), \
		( \
			192, 193, 194, 195, 196, \
			197, 198, 199, 200, 201 \
		), \
		( \
			192, 191, 190, 189, 188, \
			187, 186, 185, 184, 183 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_193 \
		( \
			193, 194, 195, 196, 197, \
			198, 199, 200, 201, 202 \
		), \
		( \
			193, 192, 191, 190, 189, \
			188, 187, 186, 185, 184 \
		), \
		( \
			193, 194, 195, 196, 197, \
			198, 199, 200, 201, 202 \
		), \
		( \
			193, 192, 191, 190, 189, \
			188, 187, 186, 185, 184 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_194 \
		( \
			194, 195, 196, 197, 198, \
			199, 200, 201, 202, 203 \
		), \
		( \
			194, 193, 192, 191, 190, \
			189, 188, 187, 186, 185 \
		), \
		( \
			194, 195, 196, 197, 198, \
			199, 200, 201, 202, 203 \
		), \
		( \
			194, 193, 192, 191, 190, \
			189, 188, 187, 186, 185 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_195 \
		( \
			195, 196, 197, 198, 199, \
			200, 201, 202, 203, 204 \
		), \
		( \
			195, 194, 193, 192, 191, \
			190, 189, 188, 187, 186 \
		), \
		( \
			195, 196, 197, 198, 199, \
			200, 201, 202, 203, 204 \
		), \
		( \
			195, 194, 193, 192, 191, \
			190, 189, 188, 187, 186 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_196 \
		( \
			196, 197, 198, 199, 200, \
			201, 202, 203, 204, 205 \
		), \
		( \
			196, 195, 194, 193, 192, \
			191, 190, 189, 188, 187 \
		), \
		( \
			196, 197, 198, 199, 200, \
			201, 202, 203, 204, 205 \
		), \
		( \
			196, 195, 194, 193, 192, \
			191, 190, 189, 188, 187 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_197 \
		( \
			197, 198, 199, 200, 201, \
			202, 203, 204, 205, 206 \
		), \
		( \
			197, 196, 195, 194, 193, \
			192, 191, 190, 189, 188 \
		), \
		( \
			197, 198, 199, 200, 201, \
			202, 203, 204, 205, 206 \
		), \
		( \
			197, 196, 195, 194, 193, \
			192, 191, 190, 189, 188 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_198 \
		( \
			198, 199, 200, 201, 202, \
			203, 204, 205, 206, 207 \
		), \
		( \
			198, 197, 196, 195, 194, \
			193, 192, 191, 190, 189 \
		), \
		( \
			198, 199, 200, 201, 202, \
			203, 204, 205, 206, 207 \
		), \
		( \
			198, 197, 196, 195, 194, \
			193, 192, 191, 190, 189 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_199 \
		( \
			199, 200, 201, 202, 203, \
			204, 205, 206, 207, 208 \
		), \
		( \
			199, 198, 197, 196, 195, \
			194, 193, 192, 191, 190 \
		), \
		( \
			199, 200, 201, 202, 203, \
			204, 205, 206, 207, 208 \
		), \
		( \
			199, 198, 197, 196, 195, \
			194, 193, 192, 191, 190 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_200 \
		( \
			200, 201, 202, 203, 204, \
			205, 206, 207, 208, 209 \
		), \
		( \
			200, 199, 198, 197, 196, \
			195, 194, 193, 192, 191 \
		), \
		( \
			200, 201, 202, 203, 204, \
			205, 206, 207, 208, 209 \
		), \
		( \
			200, 199, 198, 197, 196, \
			195, 194, 193, 192, 191 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_201 \
		( \
			201, 202, 203, 204, 205, \
			206, 207, 208, 209, 210 \
		), \
		( \
			201, 200, 199, 198, 197, \
			196, 195, 194, 193, 192 \
		), \
		( \
			201, 202, 203, 204, 205, \
			206, 207, 208, 209, 210 \
		), \
		( \
			201, 200, 199, 198, 197, \
			196, 195, 194, 193, 192 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_202 \
		( \
			202, 203, 204, 205, 206, \
			207, 208, 209, 210, 211 \
		), \
		( \
			202, 201, 200, 199, 198, \
			197, 196, 195, 194, 193 \
		), \
		( \
			202, 203, 204, 205, 206, \
			207, 208, 209, 210, 211 \
		), \
		( \
			202, 201, 200, 199, 198, \
			197, 196, 195, 194, 193 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_203 \
		( \
			203, 204, 205, 206, 207, \
			208, 209, 210, 211, 212 \
		), \
		( \
			203, 202, 201, 200, 199, \
			198, 197, 196, 195, 194 \
		), \
		( \
			203, 204, 205, 206, 207, \
			208, 209, 210, 211, 212 \
		), \
		( \
			203, 202, 201, 200, 199, \
			198, 197, 196, 195, 194 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_204 \
		( \
			204, 205, 206, 207, 208, \
			209, 210, 211, 212, 213 \
		), \
		( \
			204, 203, 202, 201, 200, \
			199, 198, 197, 196, 195 \
		), \
		( \
			204, 205, 206, 207, 208, \
			209, 210, 211, 212, 213 \
		), \
		( \
			204, 203, 202, 201, 200, \
			199, 198, 197, 196, 195 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_205 \
		( \
			205, 206, 207, 208, 209, \
			210, 211, 212, 213, 214 \
		), \
		( \
			205, 204, 203, 202, 201, \
			200, 199, 198, 197, 196 \
		), \
		( \
			205, 206, 207, 208, 209, \
			210, 211, 212, 213, 214 \
		), \
		( \
			205, 204, 203, 202, 201, \
			200, 199, 198, 197, 196 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_206 \
		( \
			206, 207, 208, 209, 210, \
			211, 212, 213, 214, 215 \
		), \
		( \
			206, 205, 204, 203, 202, \
			201, 200, 199, 198, 197 \
		), \
		( \
			206, 207, 208, 209, 210, \
			211, 212, 213, 214, 215 \
		), \
		( \
			206, 205, 204, 203, 202, \
			201, 200, 199, 198, 197 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_207 \
		( \
			207, 208, 209, 210, 211, \
			212, 213, 214, 215, 216 \
		), \
		( \
			207, 206, 205, 204, 203, \
			202, 201, 200, 199, 198 \
		), \
		( \
			207, 208, 209, 210, 211, \
			212, 213, 214, 215, 216 \
		), \
		( \
			207, 206, 205, 204, 203, \
			202, 201, 200, 199, 198 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_208 \
		( \
			208, 209, 210, 211, 212, \
			213, 214, 215, 216, 217 \
		), \
		( \
			208, 207, 206, 205, 204, \
			203, 202, 201, 200, 199 \
		), \
		( \
			208, 209, 210, 211, 212, \
			213, 214, 215, 216, 217 \
		), \
		( \
			208, 207, 206, 205, 204, \
			203, 202, 201, 200, 199 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_209 \
		( \
			209, 210, 211, 212, 213, \
			214, 215, 216, 217, 218 \
		), \
		( \
			209, 208, 207, 206, 205, \
			204, 203, 202, 201, 200 \
		), \
		( \
			209, 210, 211, 212, 213, \
			214, 215, 216, 217, 218 \
		), \
		( \
			209, 208, 207, 206, 205, \
			204, 203, 202, 201, 200 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_210 \
		( \
			210, 211, 212, 213, 214, \
			215, 216, 217, 218, 219 \
		), \
		( \
			210, 209, 208, 207, 206, \
			205, 204, 203, 202, 201 \
		), \
		( \
			210, 211, 212, 213, 214, \
			215, 216, 217, 218, 219 \
		), \
		( \
			210, 209, 208, 207, 206, \
			205, 204, 203, 202, 201 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_211 \
		( \
			211, 212, 213, 214, 215, \
			216, 217, 218, 219, 220 \
		), \
		( \
			211, 210, 209, 208, 207, \
			206, 205, 204, 203, 202 \
		), \
		( \
			211, 212, 213, 214, 215, \
			216, 217, 218, 219, 220 \
		), \
		( \
			211, 210, 209, 208, 207, \
			206, 205, 204, 203, 202 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_212 \
		( \
			212, 213, 214, 215, 216, \
			217, 218, 219, 220, 221 \
		), \
		( \
			212, 211, 210, 209, 208, \
			207, 206, 205, 204, 203 \
		), \
		( \
			212, 213, 214, 215, 216, \
			217, 218, 219, 220, 221 \
		), \
		( \
			212, 211, 210, 209, 208, \
			207, 206, 205, 204, 203 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_213 \
		( \
			213, 214, 215, 216, 217, \
			218, 219, 220, 221, 222 \
		), \
		( \
			213, 212, 211, 210, 209, \
			208, 207, 206, 205, 204 \
		), \
		( \
			213, 214, 215, 216, 217, \
			218, 219, 220, 221, 222 \
		), \
		( \
			213, 212, 211, 210, 209, \
			208, 207, 206, 205, 204 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_214 \
		( \
			214, 215, 216, 217, 218, \
			219, 220, 221, 222, 223 \
		), \
		( \
			214, 213, 212, 211, 210, \
			209, 208, 207, 206, 205 \
		), \
		( \
			214, 215, 216, 217, 218, \
			219, 220, 221, 222, 223 \
		), \
		( \
			214, 213, 212, 211, 210, \
			209, 208, 207, 206, 205 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_215 \
		( \
			215, 216, 217, 218, 219, \
			220, 221, 222, 223, 224 \
		), \
		( \
			215, 214, 213, 212, 211, \
			210, 209, 208, 207, 206 \
		), \
		( \
			215, 216, 217, 218, 219, \
			220, 221, 222, 223, 224 \
		), \
		( \
			215, 214, 213, 212, 211, \
			210, 209, 208, 207, 206 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_216 \
		( \
			216, 217, 218, 219, 220, \
			221, 222, 223, 224, 225 \
		), \
		( \
			216, 215, 214, 213, 212, \
			211, 210, 209, 208, 207 \
		), \
		( \
			216, 217, 218, 219, 220, \
			221, 222, 223, 224, 225 \
		), \
		( \
			216, 215, 214, 213, 212, \
			211, 210, 209, 208, 207 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_217 \
		( \
			217, 218, 219, 220, 221, \
			222, 223, 224, 225, 226 \
		), \
		( \
			217, 216, 215, 214, 213, \
			212, 211, 210, 209, 208 \
		), \
		( \
			217, 218, 219, 220, 221, \
			222, 223, 224, 225, 226 \
		), \
		( \
			217, 216, 215, 214, 213, \
			212, 211, 210, 209, 208 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_218 \
		( \
			218, 219, 220, 221, 222, \
			223, 224, 225, 226, 227 \
		), \
		( \
			218, 217, 216, 215, 214, \
			213, 212, 211, 210, 209 \
		), \
		( \
			218, 219, 220, 221, 222, \
			223, 224, 225, 226, 227 \
		), \
		( \
			218, 217, 216, 215, 214, \
			213, 212, 211, 210, 209 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_219 \
		( \
			219, 220, 221, 222, 223, \
			224, 225, 226, 227, 228 \
		), \
		( \
			219, 218, 217, 216, 215, \
			214, 213, 212, 211, 210 \
		), \
		( \
			219, 220, 221, 222, 223, \
			224, 225, 226, 227, 228 \
		), \
		( \
			219, 218, 217, 216, 215, \
			214, 213, 212, 211, 210 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_220 \
		( \
			220, 221, 222, 223, 224, \
			225, 226, 227, 228, 229 \
		), \
		( \
			220, 219, 218, 217, 216, \
			215, 214, 213, 212, 211 \
		), \
		( \
			220, 221, 222, 223, 224, \
			225, 226, 227, 228, 229 \
		), \
		( \
			220, 219, 218, 217, 216, \
			215, 214, 213, 212, 211 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_221 \
		( \
			221, 222, 223, 224, 225, \
			226, 227, 228, 229, 230 \
		), \
		( \
			221, 220, 219, 218, 217, \
			216, 215, 214, 213, 212 \
		), \
		( \
			221, 222, 223, 224, 225, \
			226, 227, 228, 229, 230 \
		), \
		( \
			221, 220, 219, 218, 217, \
			216, 215, 214, 213, 212 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_222 \
		( \
			222, 223, 224, 225, 226, \
			227, 228, 229, 230, 231 \
		), \
		( \
			222, 221, 220, 219, 218, \
			217, 216, 215, 214, 213 \
		), \
		( \
			222, 223, 224, 225, 226, \
			227, 228, 229, 230, 231 \
		), \
		( \
			222, 221, 220, 219, 218, \
			217, 216, 215, 214, 213 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_223 \
		( \
			223, 224, 225, 226, 227, \
			228, 229, 230, 231, 232 \
		), \
		( \
			223, 222, 221, 220, 219, \
			218, 217, 216, 215, 214 \
		), \
		( \
			223, 224, 225, 226, 227, \
			228, 229, 230, 231, 232 \
		), \
		( \
			223, 222, 221, 220, 219, \
			218, 217, 216, 215, 214 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_224 \
		( \
			224, 225, 226, 227, 228, \
			229, 230, 231, 232, 233 \
		), \
		( \
			224, 223, 222, 221, 220, \
			219, 218, 217, 216, 215 \
		), \
		( \
			224, 225, 226, 227, 228, \
			229, 230, 231, 232, 233 \
		), \
		( \
			224, 223, 222, 221, 220, \
			219, 218, 217, 216, 215 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_225 \
		( \
			225, 226, 227, 228, 229, \
			230, 231, 232, 233, 234 \
		), \
		( \
			225, 224, 223, 222, 221, \
			220, 219, 218, 217, 216 \
		), \
		( \
			225, 226, 227, 228, 229, \
			230, 231, 232, 233, 234 \
		), \
		( \
			225, 224, 223, 222, 221, \
			220, 219, 218, 217, 216 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_226 \
		( \
			226, 227, 228, 229, 230, \
			231, 232, 233, 234, 235 \
		), \
		( \
			226, 225, 224, 223, 222, \
			221, 220, 219, 218, 217 \
		), \
		( \
			226, 227, 228, 229, 230, \
			231, 232, 233, 234, 235 \
		), \
		( \
			226, 225, 224, 223, 222, \
			221, 220, 219, 218, 217 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_227 \
		( \
			227, 228, 229, 230, 231, \
			232, 233, 234, 235, 236 \
		), \
		( \
			227, 226, 225, 224, 223, \
			222, 221, 220, 219, 218 \
		), \
		( \
			227, 228, 229, 230, 231, \
			232, 233, 234, 235, 236 \
		), \
		( \
			227, 226, 225, 224, 223, \
			222, 221, 220, 219, 218 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_228 \
		( \
			228, 229, 230, 231, 232, \
			233, 234, 235, 236, 237 \
		), \
		( \
			228, 227, 226, 225, 224, \
			223, 222, 221, 220, 219 \
		), \
		( \
			228, 229, 230, 231, 232, \
			233, 234, 235, 236, 237 \
		), \
		( \
			228, 227, 226, 225, 224, \
			223, 222, 221, 220, 219 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_229 \
		( \
			229, 230, 231, 232, 233, \
			234, 235, 236, 237, 238 \
		), \
		( \
			229, 228, 227, 226, 225, \
			224, 223, 222, 221, 220 \
		), \
		( \
			229, 230, 231, 232, 233, \
			234, 235, 236, 237, 238 \
		), \
		( \
			229, 228, 227, 226, 225, \
			224, 223, 222, 221, 220 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_230 \
		( \
			230, 231, 232, 233, 234, \
			235, 236, 237, 238, 239 \
		), \
		( \
			230, 229, 228, 227, 226, \
			225, 224, 223, 222, 221 \
		), \
		( \
			230, 231, 232, 233, 234, \
			235, 236, 237, 238, 239 \
		), \
		( \
			230, 229, 228, 227, 226, \
			225, 224, 223, 222, 221 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_231 \
		( \
			231, 232, 233, 234, 235, \
			236, 237, 238, 239, 240 \
		), \
		( \
			231, 230, 229, 228, 227, \
			226, 225, 224, 223, 222 \
		), \
		( \
			231, 232, 233, 234, 235, \
			236, 237, 238, 239, 240 \
		), \
		( \
			231, 230, 229, 228, 227, \
			226, 225, 224, 223, 222 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_232 \
		( \
			232, 233, 234, 235, 236, \
			237, 238, 239, 240, 241 \
		), \
		( \
			232, 231, 230, 229, 228, \
			227, 226, 225, 224, 223 \
		), \
		( \
			232, 233, 234, 235, 236, \
			237, 238, 239, 240, 241 \
		), \
		( \
			232, 231, 230, 229, 228, \
			227, 226, 225, 224, 223 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_233 \
		( \
			233, 234, 235, 236, 237, \
			238, 239, 240, 241, 242 \
		), \
		( \
			233, 232, 231, 230, 229, \
			228, 227, 226, 225, 224 \
		), \
		( \
			233, 234, 235, 236, 237, \
			238, 239, 240, 241, 242 \
		), \
		( \
			233, 232, 231, 230, 229, \
			228, 227, 226, 225, 224 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_234 \
		( \
			234, 235, 236, 237, 238, \
			239, 240, 241, 242, 243 \
		), \
		( \
			234, 233, 232, 231, 230, \
			229, 228, 227, 226, 225 \
		), \
		( \
			234, 235, 236, 237, 238, \
			239, 240, 241, 242, 243 \
		), \
		( \
			234, 233, 232, 231, 230, \
			229, 228, 227, 226, 225 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_235 \
		( \
			235, 236, 237, 238, 239, \
			240, 241, 242, 243, 244 \
		), \
		( \
			235, 234, 233, 232, 231, \
			230, 229, 228, 227, 226 \
		), \
		( \
			235, 236, 237, 238, 239, \
			240, 241, 242, 243, 244 \
		), \
		( \
			235, 234, 233, 232, 231, \
			230, 229, 228, 227, 226 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_236 \
		( \
			236, 237, 238, 239, 240, \
			241, 242, 243, 244, 245 \
		), \
		( \
			236, 235, 234, 233, 232, \
			231, 230, 229, 228, 227 \
		), \
		( \
			236, 237, 238, 239, 240, \
			241, 242, 243, 244, 245 \
		), \
		( \
			236, 235, 234, 233, 232, \
			231, 230, 229, 228, 227 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_237 \
		( \
			237, 238, 239, 240, 241, \
			242, 243, 244, 245, 246 \
		), \
		( \
			237, 236, 235, 234, 233, \
			232, 231, 230, 229, 228 \
		), \
		( \
			237, 238, 239, 240, 241, \
			242, 243, 244, 245, 246 \
		), \
		( \
			237, 236, 235, 234, 233, \
			232, 231, 230, 229, 228 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_238 \
		( \
			238, 239, 240, 241, 242, \
			243, 244, 245, 246, 247 \
		), \
		( \
			238, 237, 236, 235, 234, \
			233, 232, 231, 230, 229 \
		), \
		( \
			238, 239, 240, 241, 242, \
			243, 244, 245, 246, 247 \
		), \
		( \
			238, 237, 236, 235, 234, \
			233, 232, 231, 230, 229 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_239 \
		( \
			239, 240, 241, 242, 243, \
			244, 245, 246, 247, 248 \
		), \
		( \
			239, 238, 237, 236, 235, \
			234, 233, 232, 231, 230 \
		), \
		( \
			239, 240, 241, 242, 243, \
			244, 245, 246, 247, 248 \
		), \
		( \
			239, 238, 237, 236, 235, \
			234, 233, 232, 231, 230 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_240 \
		( \
			240, 241, 242, 243, 244, \
			245, 246, 247, 248, 249 \
		), \
		( \
			240, 239, 238, 237, 236, \
			235, 234, 233, 232, 231 \
		), \
		( \
			240, 241, 242, 243, 244, \
			245, 246, 247, 248, 249 \
		), \
		( \
			240, 239, 238, 237, 236, \
			235, 234, 233, 232, 231 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_241 \
		( \
			241, 242, 243, 244, 245, \
			246, 247, 248, 249, 250 \
		), \
		( \
			241, 240, 239, 238, 237, \
			236, 235, 234, 233, 232 \
		), \
		( \
			241, 242, 243, 244, 245, \
			246, 247, 248, 249, 250 \
		), \
		( \
			241, 240, 239, 238, 237, \
			236, 235, 234, 233, 232 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_242 \
		( \
			242, 243, 244, 245, 246, \
			247, 248, 249, 250, 251 \
		), \
		( \
			242, 241, 240, 239, 238, \
			237, 236, 235, 234, 233 \
		), \
		( \
			242, 243, 244, 245, 246, \
			247, 248, 249, 250, 251 \
		), \
		( \
			242, 241, 240, 239, 238, \
			237, 236, 235, 234, 233 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_243 \
		( \
			243, 244, 245, 246, 247, \
			248, 249, 250, 251, 252 \
		), \
		( \
			243, 242, 241, 240, 239, \
			238, 237, 236, 235, 234 \
		), \
		( \
			243, 244, 245, 246, 247, \
			248, 249, 250, 251, 252 \
		), \
		( \
			243, 242, 241, 240, 239, \
			238, 237, 236, 235, 234 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_244 \
		( \
			244, 245, 246, 247, 248, \
			249, 250, 251, 252, 253 \
		), \
		( \
			244, 243, 242, 241, 240, \
			239, 238, 237, 236, 235 \
		), \
		( \
			244, 245, 246, 247, 248, \
			249, 250, 251, 252, 253 \
		), \
		( \
			244, 243, 242, 241, 240, \
			239, 238, 237, 236, 235 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_245 \
		( \
			245, 246, 247, 248, 249, \
			250, 251, 252, 253, 254 \
		), \
		( \
			245, 244, 243, 242, 241, \
			240, 239, 238, 237, 236 \
		), \
		( \
			245, 246, 247, 248, 249, \
			250, 251, 252, 253, 254 \
		), \
		( \
			245, 244, 243, 242, 241, \
			240, 239, 238, 237, 236 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_246 \
		( \
			246, 247, 248, 249, 250, \
			251, 252, 253, 254, 255 \
		), \
		( \
			246, 245, 244, 243, 242, \
			241, 240, 239, 238, 237 \
		), \
		( \
			246, 247, 248, 249, 250, \
			251, 252, 253, 254, 255 \
		), \
		( \
			246, 245, 244, 243, 242, \
			241, 240, 239, 238, 237 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_247 \
		( \
			247, 248, 249, 250, 251, \
			252, 253, 254, 255, 256 \
		), \
		( \
			247, 246, 245, 244, 243, \
			242, 241, 240, 239, 238 \
		), \
		( \
			247, 248, 249, 250, 251, \
			252, 253, 254, 255, 256 \
		), \
		( \
			247, 246, 245, 244, 243, \
			242, 241, 240, 239, 238 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_248 \
		( \
			248, 249, 250, 251, 252, \
			253, 254, 255, 256, 257 \
		), \
		( \
			248, 247, 246, 245, 244, \
			243, 242, 241, 240, 239 \
		), \
		( \
			248, 249, 250, 251, 252, \
			253, 254, 255, 256, 257 \
		), \
		( \
			248, 247, 246, 245, 244, \
			243, 242, 241, 240, 239 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_249 \
		( \
			249, 250, 251, 252, 253, \
			254, 255, 256, 257, 258 \
		), \
		( \
			249, 248, 247, 246, 245, \
			244, 243, 242, 241, 240 \
		), \
		( \
			249, 250, 251, 252, 253, \
			254, 255, 256, 257, 258 \
		), \
		( \
			249, 248, 247, 246, 245, \
			244, 243, 242, 241, 240 \
		)
	
	#define LIBANDRIA4_SUMMATIONNUMS_250 \
		( \
			250, 251, 252, 253, 254, \
			255, 256, 257, 258, 259 \
		), \
		( \
			250, 249, 248, 247, 246, \
			245, 244, 243, 242, 241 \
		), \
		( \
			250, 251, 252, 253, 254, \
			255, 256, 257, 258, 259 \
		), \
		( \
			250, 249, 248, 247, 246, \
			245, 244, 243, 242, 241 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_251 \
		( \
			251, 252, 253, 254, 255, \
			256, 257, 258, 259, 260 \
		), \
		( \
			251, 250, 249, 248, 247, \
			246, 245, 244, 243, 242 \
		), \
		( \
			251, 252, 253, 254, 255, \
			256, 257, 258, 259, 260 \
		), \
		( \
			251, 250, 249, 248, 247, \
			246, 245, 244, 243, 242 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_252 \
		( \
			252, 253, 254, 255, 256, \
			257, 258, 259, 260, 261 \
		), \
		( \
			252, 251, 250, 249, 248, \
			247, 246, 245, 244, 243 \
		), \
		( \
			252, 253, 254, 255, 256, \
			257, 258, 259, 260, 261 \
		), \
		( \
			252, 251, 250, 249, 248, \
			247, 246, 245, 244, 243 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_253 \
		( \
			253, 254, 255, 256, 257, \
			258, 259, 260, 261, 262 \
		), \
		( \
			253, 252, 251, 250, 249, \
			248, 247, 246, 245, 244 \
		), \
		( \
			253, 254, 255, 256, 257, \
			258, 259, 260, 261, 262 \
		), \
		( \
			253, 252, 251, 250, 249, \
			248, 247, 246, 245, 244 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_254 \
		( \
			254, 255, 256, 257, 258, \
			259, 260, 261, 262, 263 \
		), \
		( \
			254, 253, 252, 251, 250, \
			249, 248, 247, 246, 245 \
		), \
		( \
			254, 255, 256, 257, 258, \
			259, 260, 261, 262, 263 \
		), \
		( \
			254, 253, 252, 251, 250, \
			249, 248, 247, 246, 245 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_255 \
		( \
			255, 256, 257, 258, 259, \
			260, 261, 262, 263, 264 \
		), \
		( \
			255, 254, 253, 252, 251, \
			250, 249, 248, 247, 246 \
		), \
		( \
			255, 256, 257, 258, 259, \
			260, 261, 262, 263, 264 \
		), \
		( \
			255, 254, 253, 252, 251, \
			250, 249, 248, 247, 246 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_256 \
		( \
			256, 257, 258, 259, 260, \
			261, 262, 263, 264, 265 \
		), \
		( \
			256, 255, 254, 253, 252, \
			251, 250, 249, 248, 247 \
		), \
		( \
			256, 257, 258, 259, 260, \
			261, 262, 263, 264, 265 \
		), \
		( \
			256, 255, 254, 253, 252, \
			251, 250, 249, 248, 247 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_257 \
		( \
			257, 258, 259, 260, 261, \
			262, 263, 264, 265, 266 \
		), \
		( \
			257, 256, 255, 254, 253, \
			252, 251, 250, 249, 248 \
		), \
		( \
			257, 258, 259, 260, 261, \
			262, 263, 264, 265, 266 \
		), \
		( \
			257, 256, 255, 254, 253, \
			252, 251, 250, 249, 248 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_258 \
		( \
			258, 259, 260, 261, 262, \
			263, 264, 265, 266, 267 \
		), \
		( \
			258, 257, 256, 255, 254, \
			253, 252, 251, 250, 249 \
		), \
		( \
			258, 259, 260, 261, 262, \
			263, 264, 265, 266, 267 \
		), \
		( \
			258, 257, 256, 255, 254, \
			253, 252, 251, 250, 249 \
		)
	#define LIBANDRIA4_SUMMATIONNUMS_259 \
		( \
			259, 260, 261, 262, 263, \
			264, 265, 266, 267, 268 \
		), \
		( \
			259, 258, 257, 256, 255, \
			254, 253, 252, 251, 250 \
		), \
		( \
			259, 260, 261, 262, 263, \
			264, 265, 266, 267, 268 \
		), \
		( \
			259, 258, 257, 256, 255, \
			254, 253, 252, 251, 250 \
		)
	
	
		/* Entry format: ( round-down, round-norm, round-up, fractional ) */
		/* Divisors: 1, 2, 3 */
	#define LIBANDRIA4_DIVISIONNUMS_() \
		( (), (), (), () ), \
		( (), (), (), () ), \
		( (), (), (), () )
	
	#define LIBANDRIA4_DIVISIONNUMS_0 \
		( 0, 0, 0, 0 ), \
		( 0, 0, 0, 0 ), \
		( 0, 0, 0, 0 )
	
	#define LIBANDRIA4_DIVISIONNUMS_1 \
		( 1, 1, 1, 1 ), \
		( 0, 1, 1, 0.5 ), \
		( 0, 0, 1, 1.0/3 )
	#define LIBANDRIA4_DIVISIONNUMS_2 \
		( 2, 2, 2, 2 ), \
		( 1, 1, 1, 1 ), \
		( 0, 1, 1, 2.0/3 )
	#define LIBANDRIA4_DIVISIONNUMS_3 \
		( 3, 3, 3, 3 ), \
		( 1, 2, 2, 1.5 ), \
		( 1, 1, 1, 1 )
	#define LIBANDRIA4_DIVISIONNUMS_4 \
		( 4, 4, 4, 4 ), \
		( 2, 2, 2, 2 ), \
		( 1, 1, 2, 4.0/3 )
	
	#define LIBANDRIA4_DIVISIONNUMS_5 \
		( 5, 5, 5, 5 ), \
		( 2, 3, 3, 2.5 ), \
		( 1, 2, 2, 5.0/3 )
	#define LIBANDRIA4_DIVISIONNUMS_6 \
		( 6, 6, 6, 6 ), \
		( 3, 3, 3, 3 ), \
		( 2, 2, 2, 2 )
	#define LIBANDRIA4_DIVISIONNUMS_7 \
		( 7, 7, 7, 7 ), \
		( 3, 4, 4, 3.5 ), \
		( 2, 2, 3, 7.0/3 )
	#define LIBANDRIA4_DIVISIONNUMS_8 \
		( 8, 8, 8, 8 ), \
		( 4, 4, 4, 4 ), \
		( 2, 3, 3, 8.0/3 )
	
	#define LIBANDRIA4_DIVISIONNUMS_9 \
		( 9, 9, 9, 9 ), \
		( 4, 5, 5, 4.5 ), \
		( 3, 3, 3, 3 )
	#define LIBANDRIA4_DIVISIONNUMS_10 \
		( 10, 10, 10, 10 ), \
		( 5, 5, 5, 5 ), \
		( 3, 3, 4, 10.0/3 )
	#define LIBANDRIA4_DIVISIONNUMS_11 \
		( 11, 11, 11, 11 ), \
		( 5, 6, 6, 5.5 ), \
		( 3, 4, 4, 11.0/3 )
	#define LIBANDRIA4_DIVISIONNUMS_12 \
		( 12, 12, 12, 12 ), \
		( 6, 6, 6, 6 ), \
		( 4, 4, 4, 4 )
	
	#define LIBANDRIA4_DIVISIONNUMS_13 \
		( 13, 13, 13, 13 ), \
		( 6, 7, 7, 6.5 ), \
		( 4, 4, 5, 13.0/3 )
	#define LIBANDRIA4_DIVISIONNUMS_14 \
		( 14, 14, 14, 14 ), \
		( 7, 7, 7, 7 ), \
		( 4, 5, 5, 14.0/3 )
	#define LIBANDRIA4_DIVISIONNUMS_15 \
		( 15, 15, 15, 15 ), \
		( 7, 8, 8, 7.5 ), \
		( 5, 5, 5, 5 )
	#define LIBANDRIA4_DIVISIONNUMS_16 \
		( 16, 16, 16, 16 ), \
		( 8, 8, 8, 8 ), \
		( 5, 5, 6, 16.0/3 )
	
#endif
/* End libandria4 macroops math.h */
