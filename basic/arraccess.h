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

#ifndef LIBANDRIA4_BASIC_ARRTOOLS_H
# define LIBANDRIA4_BASIC_ARRTOOLS_H
	
	/* Note: The comment below is old, since it references forset.h... */
	
	/* ... Perhaps you were looking for strsnarrs.h instead? Or perhaps for */
	/*  forset.h is more to your interest? These tools only work on things */
	/*  formatted like a __VA_ARGS__ array. */
	
	
	
	#define LIBANDRIA4_RETURN_1ST( n, ... ) n
	#define LIBANDRIA4_RETURN_2ND( x, n, ... ) n
	#define LIBANDRIA4_RETURN_3RD( x1, x2, n, ... ) n
	#define LIBANDRIA4_RETURN_4TH( x1, x2, x3, n,  ... ) n
	#define LIBANDRIA4_RETURN_5TH( x1, x2, x3, x4,  n, ... ) n
	
	#define LIBANDRIA4_RETURN_6TH( x1, x2, x3, x4,  x5, n, ... ) n
	#define LIBANDRIA4_RETURN_7TH( x1, x2, x3, x4,  x5, x6, n, ... ) n
	#define LIBANDRIA4_RETURN_8TH( x1, x2, x3, x4,  x5, x6, x7, n,  ... ) n
	#define LIBANDRIA4_RETURN_9TH( x1, x2, x3, x4,  x5, x6, x7, x8,  n, ... ) n
	#define LIBANDRIA4_RETURN_10TH( x1, x2, x3, x4,  x5, x6, x7, x8,  x9, n, ... ) n
	
	#define LIBANDRIA4_RETURN_11TH( x1, x2, x3, x4,  x5, x6, x7, x8,  x9, x10, n, ... ) n
	#define LIBANDRIA4_RETURN_12TH( x1, x2, x3, x4,  x5, x6, x7, x8,  x9, x10, x11, n,  ... ) n
	#define LIBANDRIA4_RETURN_13TH( x1, x2, x3, x4,  x5, x6, x7, x8,  x9, x10, x11, x12,  n, ... ) n
	#define LIBANDRIA4_RETURN_14TH( x1, x2, x3, x4,  x5, x6, x7, x8,  x9, x10, x11, x12,  x13, n, ... ) n
	#define LIBANDRIA4_RETURN_15TH( x1, x2, x3, x4,  x5, x6, x7, x8,  x9, x10, x11, x12,  x13, x14, n, ... ) n
	
	#define LIBANDRIA4_RETURN_16TH( x1, x2, x3, x4,  x5, x6, x7, x8,  x9, x10, x11, x12,  x13, x14, x15, n,  ... ) n
	#define LIBANDRIA4_RETURN_17TH( x1, x2, x3, x4,  x5, x6, x7, x8,  x9, x10, x11, x12,  x13, x14, x15, x16,  n, ... ) n
	
	
	#define LIBANDRIA4_RETURN_0( ... ) 
	
	#define LIBANDRIA4_RETURN_1( ... ) LIBANDRIA4_RETURN_1ST( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_2( ... ) LIBANDRIA4_RETURN_2ND( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_3( ... ) LIBANDRIA4_RETURN_3RD( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_4( ... ) LIBANDRIA4_RETURN_4TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_5( ... ) LIBANDRIA4_RETURN_5TH( __VA_ARGS__ )
	
	#define LIBANDRIA4_RETURN_6( ... ) LIBANDRIA4_RETURN_6TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_7( ... ) LIBANDRIA4_RETURN_7TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_8( ... ) LIBANDRIA4_RETURN_8TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_9( ... ) LIBANDRIA4_RETURN_9TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_10( ... ) LIBANDRIA4_RETURN_10TH( __VA_ARGS__ )
	
	#define LIBANDRIA4_RETURN_11( ... ) LIBANDRIA4_RETURN_11TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_12( ... ) LIBANDRIA4_RETURN_12TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_13( ... ) LIBANDRIA4_RETURN_13TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_14( ... ) LIBANDRIA4_RETURN_14TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_15( ... ) LIBANDRIA4_RETURN_15TH( __VA_ARGS__ )
	
	#define LIBANDRIA4_RETURN_16( ... ) LIBANDRIA4_RETURN_16TH( __VA_ARGS__ )
	#define LIBANDRIA4_RETURN_17( ... ) LIBANDRIA4_RETURN_17TH( __VA_ARGS__ )
	
	
	
	#define LIBANDRIA4_SELECT_0( ... ) 
	
	#define LIBANDRIA4_SELECT_1( a, ... ) a
	#define LIBANDRIA4_SELECT_2( a, b, ... ) a, b
	#define LIBANDRIA4_SELECT_3( a, b, c, ... ) a, b, c
	#define LIBANDRIA4_SELECT_4( a, b, c, d,  ... ) a, b, c, d
	#define LIBANDRIA4_SELECT_5( a, b, c, d,  e, ... ) a, b, c, d,  e
	
	#define LIBANDRIA4_SELECT_6( a, b, c, d,  e, f, ... ) a, b, c, d,  e, f
	#define LIBANDRIA4_SELECT_7( a, b, c, d,  e, f, g, ... ) a, b, c, d,  e, f, g
	#define LIBANDRIA4_SELECT_8( a, b, c, d,  e, f, g, h,  ... ) \
		a, b, c, d,  e, f, g, h
	#define LIBANDRIA4_SELECT_9( a, b, c, d,  e, f, g, h,  i, ... ) \
		a, b, c, d,  e, f, g, h,  i
	#define LIBANDRIA4_SELECT_10( a, b, c, d,  e, f, g, h,  i, j, ... ) \
		a, b, c, d,  e, f, g, h,  i, j
	
	#define LIBANDRIA4_SELECT_11( a, b, c, d,  e, f, g, h,  i, j, k, ... ) \
		a, b, c, d,  e, f, g, h,  i, j, k
	#define LIBANDRIA4_SELECT_12( a, b, c, d,  e, f, g, h,  i, j, k, l,  ... ) \
		a, b, c, d,  e, f, g, h,  i, j, k, l
	#define LIBANDRIA4_SELECT_13( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, ... ) \
		a, b, c, d,  e, f, g, h,  i, j, k, l,  m
	#define LIBANDRIA4_SELECT_14( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, ... ) \
		a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n
	#define LIBANDRIA4_SELECT_15( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o, ... ) \
		a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o
	
	#define LIBANDRIA4_SELECT_16( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o, p,  ... ) \
		a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o, p
	#define LIBANDRIA4_SELECT_17( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o, p,  q, ... ) \
		a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o, p,  q
	
	#define LIBANDRIA4_SELECT_ALL( ... ) __VA_ARGS__
	
	
	
	#define LIBANDRIA4_OMIT_0( ... ) __VA_ARGS__
	
	#define LIBANDRIA4_OMIT_1( a, ... ) __VA_ARGS__
	#define LIBANDRIA4_OMIT_2( a, b, ... ) __VA_ARGS__
	#define LIBANDRIA4_OMIT_3( a, b, c, ... ) __VA_ARGS__
	#define LIBANDRIA4_OMIT_4( a, b, c, d,  ... ) __VA_ARGS__
	#define LIBANDRIA4_OMIT_5( a, b, c, d,  e, ... ) __VA_ARGS__
	#define LIBANDRIA4_OMIT_6( a, b, c, d,  e, f, ... ) __VA_ARGS__
	#define LIBANDRIA4_OMIT_7( a, b, c, d,  e, f, g, ... ) __VA_ARGS__
	#define LIBANDRIA4_OMIT_8( a, b, c, d,  e, f, g, h,  ... ) __VA_ARGS__
	
	
	
	#include "simpleops.h"
	#include "../math/math.h"
	
		/* Result: ( left ), ( right ), left_size */
	#define LIBANDRIA4_SPLIT_2( ... ) \
		LIBANDRIA4_INNER_SPLIT_2( \
			LIBANDRIA4_DIVIDE( LIBANDRIA4_PREPROCTIME_SIZEOF( __VA_ARGS__ ), 2 ), \
			__VA_ARGS__ \
		)
	#define LIBANDRIA4_INNER_SPLIT_2( part, ... ) \
		( LIBANDRIA4_CAT( LIBANDRIA4_SELECT_, part ) ( __VA_ARGS__ ) ), \
		( LIBANDRIA4_CAT( LIBANDRIA4_OMIT_, part ) ( __VA_ARGS__ ) ), \
		part
	
	
	
	#define LIBANDRIA4_PACKELEM_1( type, shiftstep,  a,  ... ) \
		( (type) )( ( (type) )a )
	#define LIBANDRIA4_PACKELEM_2( type, shiftstep,  a, b,  ... ) \
		( (type) )( \
			( ( (type) )a << ( ( shiftstep ) * 0 ) ) | \
			( ( (type) )b << ( ( shiftstep ) * 1 ) ) \
		)
	#define LIBANDRIA4_PACKELEM_3( type, shiftstep,  a, b, c,  ... ) \
		( (type) )( \
			( ( (type) )a << ( ( shiftstep ) * 0 ) ) | \
			( ( (type) )b << ( ( shiftstep ) * 1 ) ) | \
			( ( (type) )c << ( ( shiftstep ) * 2 ) ) \
		)
	#define LIBANDRIA4_PACKELEM_4( type, shiftstep,  a, b, c, d,  ... ) \
		( (type) )( \
			( ( (type) )a << ( ( shiftstep ) * 0 ) ) | \
			( ( (type) )b << ( ( shiftstep ) * 1 ) ) | \
			( ( (type) )c << ( ( shiftstep ) * 2 ) ) | \
			( ( (type) )d << ( ( shiftstep ) * 3 ) ) \
		)
	#define LIBANDRIA4_PACKELEM_5( type, shiftstep,  a, b, c, d,  e,  ... ) \
		( (type) )( \
			( ( (type) )a << ( ( shiftstep ) * 0 ) ) | \
			( ( (type) )b << ( ( shiftstep ) * 1 ) ) | \
			( ( (type) )c << ( ( shiftstep ) * 2 ) ) | \
			( ( (type) )d << ( ( shiftstep ) * 3 ) ) \
			| \
			( ( (type) )e << ( ( shiftstep ) * 4 ) ) \
		)
	#define LIBANDRIA4_PACKELEM_6( type, shiftstep,  a, b, c, d,  e, f,  ... ) \
		( (type) )( \
			( ( (type) )a << ( ( shiftstep ) * 0 ) ) | \
			( ( (type) )b << ( ( shiftstep ) * 1 ) ) | \
			( ( (type) )c << ( ( shiftstep ) * 2 ) ) | \
			( ( (type) )d << ( ( shiftstep ) * 3 ) ) \
			| \
			( ( (type) )e << ( ( shiftstep ) * 4 ) ) | \
			( ( (type) )f << ( ( shiftstep ) * 5 ) ) \
		)
	#define LIBANDRIA4_PACKELEM_7( type, shiftstep,  a, b, c, d,  e, f, g,  ... ) \
		( (type) )( \
			( ( (type) )a << ( ( shiftstep ) * 0 ) ) | \
			( ( (type) )b << ( ( shiftstep ) * 1 ) ) | \
			( ( (type) )c << ( ( shiftstep ) * 2 ) ) | \
			( ( (type) )d << ( ( shiftstep ) * 3 ) ) \
			| \
			( ( (type) )e << ( ( shiftstep ) * 4 ) ) | \
			( ( (type) )f << ( ( shiftstep ) * 5 ) ) | \
			( ( (type) )g << ( ( shiftstep ) * 6 ) ) \
		)
	#define LIBANDRIA4_PACKELEM_8( type, shiftstep,  a, b, c, d,  e, f, g, h,  ... ) \
		( (type) )( \
			( ( (type) )a << ( ( shiftstep ) * 0 ) ) | \
			( ( (type) )b << ( ( shiftstep ) * 1 ) ) | \
			( ( (type) )c << ( ( shiftstep ) * 2 ) ) | \
			( ( (type) )d << ( ( shiftstep ) * 3 ) ) \
			| \
			( ( (type) )e << ( ( shiftstep ) * 4 ) ) | \
			( ( (type) )f << ( ( shiftstep ) * 5 ) ) | \
			( ( (type) )g << ( ( shiftstep ) * 6 ) ) | \
			( ( (type) )h << ( ( shiftstep ) * 7 ) ) \
		)
	
	
	#define LIBANDRIA4_PACKELEM1_1( a,  ... ) \
		LIBANDRIA4_PACKELEM_1( uint8_t, 8,  a,  __VA_ARGS__ )
	
	#define LIBANDRIA4_PACKELEM2_1( a,  ... ) \
		LIBANDRIA4_PACKELEM_1( uint16_t, 16,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM2_2( shiftstep,  a,  ... ) \
		LIBANDRIA4_PACKELEM_2( uint16_t, 8,  a,  __VA_ARGS__ )
	
	#define LIBANDRIA4_PACKELEM4_1( a,  ... ) \
		LIBANDRIA4_PACKELEM_1( uint32_t, 32,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM4_2( a,  ... ) \
		LIBANDRIA4_PACKELEM_2( uint32_t, 16,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM4_3( a,  ... ) \
		LIBANDRIA4_PACKELEM_3( uint32_t, 8,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM4_4( a,  ... ) \
		LIBANDRIA4_PACKELEM_4( uint32_t, 8,  a,  __VA_ARGS__ )
	
	#define LIBANDRIA4_PACKELEM8_1( a,  ... ) \
		LIBANDRIA4_PACKELEM_1( uint64_t, 64,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM8_2( a,  ... ) \
		LIBANDRIA4_PACKELEM_2( uint64_t, 32,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM8_3( a,  ... ) \
		LIBANDRIA4_PACKELEM_3( uint64_t, 16,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM8_4( a,  ... ) \
		LIBANDRIA4_PACKELEM_4( uint64_t, 16,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM8_5( a,  ... ) \
		LIBANDRIA4_PACKELEM_5( uint64_t, 8,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM8_6( a,  ... ) \
		LIBANDRIA4_PACKELEM_6( uint64_t, 8,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM8_7( a,  ... ) \
		LIBANDRIA4_PACKELEM_7( uint64_t, 8,  a,  __VA_ARGS__ )
	#define LIBANDRIA4_PACKELEM8_8( a,  ... ) \
		LIBANDRIA4_PACKELEM_8( uint64_t, 8,  a,  __VA_ARGS__ )
	
	
	
	#define LIBANDRIA4_PARENPADS_1() ()
	#define LIBANDRIA4_PARENPADS_2() (), ()
	#define LIBANDRIA4_PARENPADS_3() (), (), ()
	#define LIBANDRIA4_PARENPADS_4() (), (), (), ()
	
	#define LIBANDRIA4_PARENPADS_5() (), (), (), (),  ()
	#define LIBANDRIA4_PARENPADS_6() (), (), (), (),  (), ()
	#define LIBANDRIA4_PARENPADS_7() (), (), (), (),  (), (), ()
	#define LIBANDRIA4_PARENPADS_8() (), (), (), (),  (), (), (), ()
	
		/* If you add more numbered versions to the above, then increment */
		/*  this to the hghest number. */
	#define LIBANDRIA4_PARENPADS() LIBANDRIA4_PARENPADS_8()
	
	
	
	#define LIBANDRIA4_ECHO_0( x ) 
	
	#define LIBANDRIA4_ECHO_1( x ) x
	#define LIBANDRIA4_ECHO_2( x ) x x
	#define LIBANDRIA4_ECHO_3( x ) x x x
	#define LIBANDRIA4_ECHO_4( x ) x x x x
	
	#define LIBANDRIA4_ECHO_5( x ) x x x x  x
	#define LIBANDRIA4_ECHO_6( x ) x x x x  x x
	#define LIBANDRIA4_ECHO_7( x ) x x x x  x x x
	#define LIBANDRIA4_ECHO_8( x ) x x x x  x x x x
	
	#define LIBANDRIA4_ECHO_9( x ) x x x x  x x x x  x
	#define LIBANDRIA4_ECHO_10( x ) x x x x  x x x x  x x
	#define LIBANDRIA4_ECHO_11( x ) x x x x  x x x x  x x x
	#define LIBANDRIA4_ECHO_12( x ) x x x x  x x x x  x x x x
	
	#define LIBANDRIA4_ECHO_13( x ) x x x x  x x x x  x x x x  x
	#define LIBANDRIA4_ECHO_14( x ) x x x x  x x x x  x x x x  x x
	#define LIBANDRIA4_ECHO_15( x ) x x x x  x x x x  x x x x  x x x
	#define LIBANDRIA4_ECHO_16( x ) x x x x  x x x x  x x x x  x x x x
	
	#define LIBANDRIA4_ECHO_17( x ) x x x x  x x x x  x x x x  x x x x  x
	#define LIBANDRIA4_ECHO_18( x ) x x x x  x x x x  x x x x  x x x x  x x
	
	
	
	#define LIBANDRIA4_ARGECHO_0( x ) 
	
	#define LIBANDRIA4_ARGECHO_1( x ) x
	#define LIBANDRIA4_ARGECHO_2( x ) x, x
	#define LIBANDRIA4_ARGECHO_3( x ) x, x, x
	#define LIBANDRIA4_ARGECHO_4( x ) x, x, x, x
	
	#define LIBANDRIA4_ARGECHO_5( x ) x, x, x, x,  x
	#define LIBANDRIA4_ARGECHO_6( x ) x, x, x, x,  x, x
	#define LIBANDRIA4_ARGECHO_7( x ) x, x, x, x,  x, x, x
	#define LIBANDRIA4_ARGECHO_8( x ) x, x, x, x,  x, x, x, x
	
	#define LIBANDRIA4_ARGECHO_9( x ) x, x, x, x,  x, x, x, x,  x
	#define LIBANDRIA4_ARGECHO_10( x ) x, x, x, x,  x, x, x, x,  x, x
	#define LIBANDRIA4_ARGECHO_11( x ) x, x, x, x,  x, x, x, x,  x, x, x
	#define LIBANDRIA4_ARGECHO_12( x ) x, x, x, x,  x, x, x, x,  x, x, x, x
	
	#define LIBANDRIA4_ARGECHO_13( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x
	#define LIBANDRIA4_ARGECHO_14( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x
	#define LIBANDRIA4_ARGECHO_15( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x, x
	#define LIBANDRIA4_ARGECHO_16( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x, x, x
	
	#define LIBANDRIA4_ARGECHO_17( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x, x, x,  x
	#define LIBANDRIA4_ARGECHO_18( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x
	
	
	
	#define LIBANDRIA4_ARGECHO_COMMA_0( x ) 
	
	#define LIBANDRIA4_ARGECHO_COMMA_1( x ) x,
	#define LIBANDRIA4_ARGECHO_COMMA_2( x ) x, x,
	#define LIBANDRIA4_ARGECHO_COMMA_3( x ) x, x, x,
	#define LIBANDRIA4_ARGECHO_COMMA_4( x ) x, x, x, x,
	
	#define LIBANDRIA4_ARGECHO_COMMA_5( x ) x, x, x, x,  x,
	#define LIBANDRIA4_ARGECHO_COMMA_6( x ) x, x, x, x,  x, x,
	#define LIBANDRIA4_ARGECHO_COMMA_7( x ) x, x, x, x,  x, x, x,
	#define LIBANDRIA4_ARGECHO_COMMA_8( x ) x, x, x, x,  x, x, x, x,
	
	#define LIBANDRIA4_ARGECHO_COMMA_9( x ) x, x, x, x,  x, x, x, x,  x,
	#define LIBANDRIA4_ARGECHO_COMMA_10( x ) x, x, x, x,  x, x, x, x,  x, x,
	#define LIBANDRIA4_ARGECHO_COMMA_11( x ) x, x, x, x,  x, x, x, x,  x, x, x,
	#define LIBANDRIA4_ARGECHO_COMMA_12( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,
	
	#define LIBANDRIA4_ARGECHO_COMMA_13( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x,
	#define LIBANDRIA4_ARGECHO_COMMA_14( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x,
	#define LIBANDRIA4_ARGECHO_COMMA_15( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x, x,
	#define LIBANDRIA4_ARGECHO_COMMA_16( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x, x, x,
	
	#define LIBANDRIA4_ARGECHO_COMMA_17( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x, x, x,  x,
	#define LIBANDRIA4_ARGECHO_COMMA_18( x ) x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x, x, x,  x, x,
	
#endif
/* End libandria4 basic arraccess.h */
