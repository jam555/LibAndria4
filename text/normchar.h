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

#ifndef LIB4_MACROTIME_NORMCHAR_H
# define LIB4_MACROTIME_NORMCHAR_H
	
	#include "simpleops.h"
	
	
	/* These accept a mixture of character constants and parentheses. All */
	/*  parentheses will be replaced with the default value, which is the */
	/*  character-null, since these are in fact characters. */
	
	#define LIB4_NORMALIZECHAR_1( a ) \
		( LIB4_DEFAULTABLE_VALUE( a, '\0' ), ) ( a )
	#define LIB4_NORMALIZECHAR_2( a, b ) \
		( \
			LIB4_DEFAULTABLE_VALUE( a, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( b, '\0' ), \
		) ( b )
	#define LIB4_NORMALIZECHAR_4( a, b, c, d ) \
		( \
			LIB4_DEFAULTABLE_VALUE( a, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( b, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( c, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( d, '\0' ), \
		) ( d )
	#define LIB4_NORMALIZECHAR_8( a, b, c, d,  e, f, g, h ) \
		( \
			LIB4_DEFAULTABLE_VALUE( a, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( b, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( c, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( d, '\0' ), \
			\
			LIB4_DEFAULTABLE_VALUE( e, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( f, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( g, '\0' ), \
			LIB4_DEFAULTABLE_VALUE( h, '\0' ) \
		) ( h )
	
#endif
/* End lib4 macrotime normchar.h */
