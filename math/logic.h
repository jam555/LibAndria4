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

#ifndef LIBANDRIA4_MATH_LOGIC_H
# define LIBANDRIA4_MATH_LOGIC_H
	
	
	
	#define LIBANDRIA4_LOGICPRIMITIVECAT( a, ... ) a ## __VA_ARGS__
	#define LIBANDRIA4_LOGICCAT( a, ... ) LIBANDRIA4_LOGICPRIMITIVECAT( a, __VA_ARGS__ )
	
	#define LIBANDRIA4_LOGICSELECT_1ST( select, ... ) select
	#define LIBANDRIA4_LOGICSELECT_2ND( a, select, ... ) select
	
	
	#define LIBANDRIA4_LOGICCHECK( ... ) LIBANDRIA4_LOGICSELECT_2ND( __VA_ARGS__, 0 )
		/* Should x be wrapped in parens for this to work right? */
	#define LIBANDRIA4_LOGICPROBE( x ) x, 1,
	
	
	#define LIBANDRIA4_LOGICIS_PAREN( x ) \
		LIBANDRIA4_LOGICCHECK( LIBANDRIA4_LOGICIS_PAREN_PROBE x )
	#define LIBANDRIA4_LOGICIS_PAREN_PROBE( ... ) \
		LIBANDRIA4_LOGICPROBE( ~ )
	
	
	
	#define LIBANDRIA4_IDENTITY( ... ) __VA_ARGS__
	#define LIBANDRIA4_IDENTITY_GATE( flag ) \
		LIBANDRIA4_IIF( flag ) ( LIBANDRIA4_IDENTITY, LIBANDRIA4_IDENTITY_GATE( 1 ) )
			/* This will initially result in an UNPROCESSED call to */
			/*  *_IDENTITY_GATE() just sitting amidst your code, but when */
			/*  you run it through EVAL() later it SHOULD get processed. The */
			/*  basic design was created for macrotime/tree.h. You should */
			/*  generally wrap it in another function of your own. */
			/* See also LIBANDRIA4_APPLY_LATER() via simpleops.h. */
	#define LIBANDRIA4_IDENTITY_LATER( ... ) LIBANDRIA4_IDENTITY_GATE( 0 )( __VA_ARGS__ )
	
	
		/* Lets you use parentheses to use a default value, or else use the */
		/*  provided value. A convenient primitive. */
	#define LIBANDRIA4_DEFAULTABLE_VALUE( val, default ) \
		LIBANDRIA4_IIF( LIBANDRIA4_LOGICIS_PAREN( val ) ) ( default, val )
	
	
	#define LIBANDRIA4_NEGATE( x ) LIBANDRIA4_CHECK( LIBANDRIA4_LOGICCAT( LIBANDRIA4_NEGATE_, x ) )
	#define LIBANDRIA4_NEGATE_0 LIBANDRIA4_LOGICPROBE( ~ )
	
	#define LIBANDRIA4_BOOL( x ) LIBANDRIA4_NEGATE( LIBANDRIA4_NEGATE( x ) )
	
	
	#define LIBANDRIA4_AND( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_AND_, LIBANDRIA4_BOOLCAT( a, b ) )
	#define LIBANDRIA4_AND_00 0
	#define LIBANDRIA4_AND_01 0
	#define LIBANDRIA4_AND_10 0
	#define LIBANDRIA4_AND_11 1
	
	#define LIBANDRIA4_IOR( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_IOR_, LIBANDRIA4_BOOLCAT( a, b ) )
	#define LIBANDRIA4_IOR_00 0
	#define LIBANDRIA4_IOR_01 1
	#define LIBANDRIA4_IOR_10 1
	#define LIBANDRIA4_IOR_11 1
	
	#define LIBANDRIA4_XOR( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_XOR_, LIBANDRIA4_BOOLCAT( a, b ) )
	#define LIBANDRIA4_XOR_00 0
	#define LIBANDRIA4_XOR_01 1
	#define LIBANDRIA4_XOR_10 1
	#define LIBANDRIA4_XOR_11 0
	
	#define LIBANDRIA4_NAND( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_NAND_, LIBANDRIA4_BOOLCAT( a, b ) )
	#define LIBANDRIA4_NAND_00 1
	#define LIBANDRIA4_NAND_01 1
	#define LIBANDRIA4_NAND_10 1
	#define LIBANDRIA4_NAND_11 0
	
	#define LIBANDRIA4_INOR( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_INOR_, LIBANDRIA4_BOOLCAT( a, b ) )
	#define LIBANDRIA4_INOR_00 1
	#define LIBANDRIA4_INOR_01 0
	#define LIBANDRIA4_INOR_10 0
	#define LIBANDRIA4_INOR_11 0
	
	#define LIBANDRIA4_XNOR( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_XNOR_, LIBANDRIA4_BOOLCAT( a, b ) )
	#define LIBANDRIA4_XNOR_00 1
	#define LIBANDRIA4_XNOR_01 0
	#define LIBANDRIA4_XNOR_10 0
	#define LIBANDRIA4_XNOR_11 1
	
	
	
	#define LIBANDRIA4_IS0( x ) LIBANDRIA4_LOGICCHECK( LIBANDRIA4_CAT( LIBANDRIA4_IS0_, x ) )
	#define LIBANDRIA4_IS0_0 LIBANDRIA4_LOGICPROBE( ~ )
	#define LIBANDRIA4_IS1( x ) LIBANDRIA4_LOGICCHECK( LIBANDRIA4_CAT( LIBANDRIA4_IS1_, x ) )
	#define LIBANDRIA4_IS1_1 LIBANDRIA4_LOGICPROBE( ~ )
	#define LIBANDRIA4_IS2( x ) LIBANDRIA4_LOGICCHECK( LIBANDRIA4_CAT( LIBANDRIA4_IS2_, x ) )
	#define LIBANDRIA4_IS2_2 LIBANDRIA4_LOGICPROBE( ~ )
	#define LIBANDRIA4_IS3( x ) LIBANDRIA4_LOGICCHECK( LIBANDRIA4_CAT( LIBANDRIA4_IS3_, x ) )
	#define LIBANDRIA4_IS3_3 LIBANDRIA4_LOGICPROBE( ~ )
	
	
	
	#define LIBANDRIA4_IIF( cond ) LIBANDRIA4_LOGICCAT( LIBANDRIA4_IIF_, cond )
	#define LIBANDRIA4_IIF_0( t, ... ) __VA_ARGS__
	#define LIBANDRIA4_IIF_1( t, ... ) t
	
	#define LIBANDRIA4_NNIF( cond ) LIBANDRIA4_LOGICCAT( LIBANDRIA4_NNIF_, cond )
	#define LIBANDRIA4_NNIF_0( t, ... ) t
	#define LIBANDRIA4_NNIF_1( t, ... ) __VA_ARGS__
	
	
		/* Used as follows: */
			/* LIB4_IF_ELSE( cond )( if cond == 1 )( if cond == 0 ) */
	#define LIBANDRIA4_IF_ELSE( cond ) \
		LIBANDRIA4_IIF( LIBANDRIA4_BOOL( cond ) )( LIBANDRIA4_IF_1, LIBANDRIA4_IF_0 )
	
	#define LIBANDRIA4_IF_0( ... ) LIBANDRIA4_IF_ELSE_0
	#define LIBANDRIA4_IF_1( ... ) __VA_ARGS__ LIBANDRIA4_IF_ELSE_1
	
	#define LIBANDRIA4_IF_ELSE_0( ... ) __VA_ARGS__
	#define LIBANDRIA4_IF_ELSE_1( ... ) 
	
	
		/* Used as follows: */
			/* LIBANDRIA4_WHEN( cond )( if cond == 1 ) */
	#define LIBANDRIA4_WHEN_DISCARD( ... )
	#define LIBANDRIA4_WHEN_PERPETUATE( ... ) __VA_ARGS__
	#define LIBANDRIA4_WHEN( cond ) \
		LIBANDRIA4_IIF( LIBANDRIA4_BOOL( cond ) ) \
			( LIBANDRIA4_WHEN_PERPETUATE, LIBANDRIA4_WHEN_DISCARD )
	
	
	#define LIBANDRIA4_WHENx( match, flag ) \
		LIBANDRIA4_WHEN( LIBANDRIA4_LOGICCHECK( LIBANDRIA4_LOGICPRIMITIVECAT( \
			LIBANDRIA4_LOGICPRIMITIVECAT( LIBANDRIA4_WHEN, match ), \
			LIBANDRIA4_LOGICPRIMITIVECAT( _, flag ) ), 0 ) )
	
	#define LIBANDRIA4_WHEN0_0 x, 1
	#define LIBANDRIA4_WHEN0( flag ) LIBANDRIA4_WHENx( 0, flag )
	#define LIBANDRIA4_WHEN1_1 x, 1
	#define LIBANDRIA4_WHEN1( flag ) LIBANDRIA4_WHENx( 1, flag )
	#define LIBANDRIA4_WHEN2_2 x, 1
	#define LIBANDRIA4_WHEN2( flag ) LIBANDRIA4_WHENx( 2, flag )
	#define LIBANDRIA4_WHEN3_3 x, 1
	#define LIBANDRIA4_WHEN3( flag ) LIBANDRIA4_WHENx( 3, flag )
	
#endif
/* End libsndria4 math logic.h */
