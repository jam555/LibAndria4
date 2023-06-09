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

#ifndef LIBANDRIA4_BASIC_EVAL_H
# define LIBANDRIA4_BASIC_EVAL_H
	
	#include "../math/math.h"
	
		/* This EVAL system is effectively a processor-instruction iterator. */
		/*  The *_FORSET macro system uses it, but you might occassionally */
		/*  need to add a few layers of eval if you give forset too much to */
		/*  do... */
	#define LIBANDRIA4_EVAL0( ... ) __VA_ARGS__
	#define LIBANDRIA4_EVAL1( ... ) \
		LIBANDRIA4_EVAL0( LIBANDRIA4_EVAL0( LIBANDRIA4_EVAL0( __VA_ARGS__ )))
	#define LIBANDRIA4_EVAL2( ... ) \
		LIBANDRIA4_EVAL1( LIBANDRIA4_EVAL1( LIBANDRIA4_EVAL1( __VA_ARGS__ )))
	#define LIBANDRIA4_EVAL3( ... ) \
		LIBANDRIA4_EVAL2( LIBANDRIA4_EVAL2( LIBANDRIA4_EVAL2( __VA_ARGS__ )))
	#define LIBANDRIA4_EVAL4( ... ) \
		LIBANDRIA4_EVAL3( LIBANDRIA4_EVAL3( LIBANDRIA4_EVAL3( __VA_ARGS__ )))
	#define LIBANDRIA4_EVAL5( ... ) \
		LIBANDRIA4_EVAL4( LIBANDRIA4_EVAL4( LIBANDRIA4_EVAL4( __VA_ARGS__ )))
	
	#define LIBANDRIA4_EVAL6( ... ) \
		LIBANDRIA4_EVAL5( LIBANDRIA4_EVAL5( LIBANDRIA4_EVAL5( __VA_ARGS__ )))
	#define LIBANDRIA4_EVAL7( ... ) \
		LIBANDRIA4_EVAL6( LIBANDRIA4_EVAL6( LIBANDRIA4_EVAL6( __VA_ARGS__ )))
	#define LIBANDRIA4_EVAL8( ... ) \
		LIBANDRIA4_EVAL7( LIBANDRIA4_EVAL7( LIBANDRIA4_EVAL7( __VA_ARGS__ )))
	#define LIBANDRIA4_EVAL9( ... ) \
		LIBANDRIA4_EVAL8( LIBANDRIA4_EVAL8( LIBANDRIA4_EVAL8( __VA_ARGS__ )))
	
	#define LIBANDRIA4_EVAL( ... )  \
		LIBANDRIA4_EVAL3( LIBANDRIA4_EVAL3( LIBANDRIA4_EVAL3( __VA_ARGS__ )))
	
	
	
	#define LIBANDRIA4_DELAY( func, ... ) LIBANDRIA4_DELAYLOOP( 60, func, __VA_ARGS__ )
			/* Note: if you get weird results on high delay values, then */
			/*  it's possibly because LIB4_SUMMATIONNUMS_* doesn't go up */
			/*  high enough. As of when this is being written, it only goes */
			/*  up to 259. Look in math.h if you want to find it. */
			/* For the current build of LIB4_EVAL() (internally three calls */
			/*  to LIB4_EVAL3()), a delay of 60 will result in the function */
			/*  being stuck in front of the args, ready to execute with only */
			/*  a single LIB4_EVAL0() wrapper. */
			/* Note that a delay of 21 will stop two steps short of letting */
			/*  the func actually execute under the influence of */
			/*  LIB4_EVAL3(). A delay of 19 WILL let it execute, as was */
			/*  determined with LIB4_IDENTITY() on corilu. */
			/* A delay of 7 & 5 are the equivalent for LIB4_EVAL2()... but */
			/*  the output of delay 6 doesn't quite match 20 for some */
			/*  reason. Not really sure why, but the difference can be */
			/*  dispelled by wrapping the output of LIB4_EVAL3() in a single */
			/*  call of LIB4_EVAL0(). */
			/* A delay of 3 & 1 are the equivalent for LIB4_EVAL1. */
			/* A delay of 1 is the equivalent to LIB4_EVAL3()'s 21 for */
			/*  LIB4_EVAL0(), but there is no equivalent to 19, as -1 just */
			/*  results in a compiler error. */
		#define LIBANDRIA4_DELAYINDIR( ... ) \
			LIBANDRIA4_DELAYLOOP LIBANDRIA4_IGNORETHIS ( __VA_ARGS__ )
		#define LIBANDRIA4_DELAYDONE( delay, func, ... ) \
			func LIBANDRIA4_IGNORETHIS ( __VA_ARGS__ )
		#define LIBANDRIA4_DELAYLOOP( delay, func, ... ) \
			LIBANDRIA4_IIF( LIBANDRIA4_BOOL( delay ) ) \
				( LIBANDRIA4_DELAYINDIR, LIBANDRIA4_DELAYDONE ) \
			LIBANDRIA4_IGNORETHIS ( LIBANDRIA4_SUB( delay, 1 ), func, __VA_ARGS__ )
	
#endif
/* End libabdria4 basic eval.h */
