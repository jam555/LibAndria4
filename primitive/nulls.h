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

#ifndef LIBANDRIA4_PRIMITIVE_NULLS_H
# define LIBANDRIA4_PRIMITIVE_NULLS_H
	
		/* Required for LIBANDRIA4_NULL_SIZEDMACRO() \ LIBANDRIA4_PRIMITIVE_CAT(). */
	#include "simpleops.h"
	
		/* These exist for the sake of doing nothing, when you would */
		/*  otherwise do something. */
	#define LIBANDRIA4_NOACTION() 
	
	#define LIBANDRIA4_IGNORETHIS 
	#define LIBANDRIA4_IGNORETHIS_ 
	#define LIBANDRIA4_PUSH_IGNORETHIS( ... ) LIBANDRIA4_IGNORETHIS ( __VA_ARGS__ )
	
	#define LIBANDRIA4_NULL_MACRO( ... )
	#define LIBANDRIA4_PUSH_NULLMACRO( ... ) LIBANDRIA4_NULL_MACRO
	#define LIBANDRIA4_DOUBLEPUSH_NULLMACRO( ... ) LIBANDRIA4_PUSH_NULLMACRO
	
	
	#define LIBANDRIA4_NULL_SIZEDMACRO( size ) \
		LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_NULL_SIZEDMACRO_, size )
	
	#define LIBANDRIA4_NULL_SIZEDMACRO_0()
	
	#define LIBANDRIA4_NULL_SIZEDMACRO_1( a )
	#define LIBANDRIA4_NULL_SIZEDMACRO_2( a, b )
	#define LIBANDRIA4_NULL_SIZEDMACRO_3( a, b, c )
	#define LIBANDRIA4_NULL_SIZEDMACRO_4( a, b, c, d )
	
	#define LIBANDRIA4_NULL_SIZEDMACRO_5( a, b, c, d,  e )
	#define LIBANDRIA4_NULL_SIZEDMACRO_6( a, b, c, d,  e, f )
	#define LIBANDRIA4_NULL_SIZEDMACRO_7( a, b, c, d,  e, f, g )
	#define LIBANDRIA4_NULL_SIZEDMACRO_8( a, b, c, d,  e, f, g, h )
	
	#define LIBANDRIA4_NULL_SIZEDMACRO_9( a, b, c, d,  e, f, g, h,  i )
	#define LIBANDRIA4_NULL_SIZEDMACRO_10( a, b, c, d,  e, f, g, h,  i, j )
	#define LIBANDRIA4_NULL_SIZEDMACRO_11( a, b, c, d,  e, f, g, h,  i, j, k )
	#define LIBANDRIA4_NULL_SIZEDMACRO_12( a, b, c, d,  e, f, g, h,  i, j, k, l )
	
	#define LIBANDRIA4_NULL_SIZEDMACRO_13( a, b, c, d,  e, f, g, h,  i, j, k, l,  m )
	#define LIBANDRIA4_NULL_SIZEDMACRO_14( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n )
	#define LIBANDRIA4_NULL_SIZEDMACRO_15( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o )
	#define LIBANDRIA4_NULL_SIZEDMACRO_16( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o, p )
	
#endif
/* End libsndria4 primitive nulls.h */
