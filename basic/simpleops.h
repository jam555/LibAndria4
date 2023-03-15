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

#ifndef LIBANDRIA4_MACROTIME_SIMPLEOPS_H
# define LIBANDRIA4_MACROTIME_SIMPLEOPS_H
	
	
		/* For LIBANDRIA4_RETURN_* macros. */
	#include "arraccess.h"
	
	
		/* These are somewhat "special": they're used when you need to embed */
		/*  a "set" operation via macro. You can always define more of these */
		/*  if needed. Try not to though. */
	#define LIBANDRIA4_OP_SETa( val ) ( a = (val) )
	#define LIBANDRIA4_OP_SETb( val ) ( b = (val) )
	#define LIBANDRIA4_OP_SETc( val ) ( c = (val) )
	#define LIBANDRIA4_OP_SETd( val ) ( d = (val) )
	#define LIBANDRIA4_OP_SETe( val ) ( e = (val) )
	
	
	#define LIBANDRIA4_OP_RETURNVAL_n1() return( -1 )
	#define LIBANDRIA4_OP_RETURNVAL_0() return( 0 )
	#define LIBANDRIA4_OP_RETURNVAL_1() return( 1 )
	#define LIBANDRIA4_OP_RETURNVAL_2() return( 2 )
	#define LIBANDRIA4_OP_RETURNVAL_3() return( 3 )
	#define LIBANDRIA4_OP_RETURNVAL_4() return( 4 )
	#define LIBANDRIA4_OP_RETURNVAL_8() return( 8 )
	#define LIBANDRIA4_OP_RETURNVAL_9() return( 9 )
	#define LIBANDRIA4_OP_RETURNVAL_10() return( 10 )
	#define LIBANDRIA4_OP_RETURNVAL_16() return( 16 )
	#define LIBANDRIA4_OP_RETURNVAL_99() return( 99 )
	#define LIBANDRIA4_OP_RETURNVAL_100() return( 100 )
	#define LIBANDRIA4_OP_RETURNVAL_255() return( 255 )
	#define LIBANDRIA4_OP_RETURNVAL_256() return( 256 )
	#define LIBANDRIA4_OP_RETURNVAL_999() return( 999 )
	#define LIBANDRIA4_OP_RETURNVAL_1000() return( 1000 )
	#define LIBANDRIA4_OP_RETURNVAL_1023() return( 1023 )
	#define LIBANDRIA4_OP_RETURNVAL_1024() return( 1024 )
	
	
	#define LIBANDRIA4_STRINGIFY( a ) LIBANDRIA4_INNER_STRINGIFY( a )
	#define LIBANDRIA4_INNER_STRINGIFY( a ) #a
	
	
	#define LIBANDRIA4_TRUEFUNC() 1
	#define LIBANDRIA4_FALSEFUNC() 0
	
	#define LIBANDRIA4_BOOLCAT( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_BOOL( a ), LIBANDRIA4_BOOL( b ) )
	#define LIBANDRIA4_CAT( a, ... ) LIBANDRIA4_PRIMITIVE_CAT( a, __VA_ARGS__ )
	#define LIBANDRIA4_PRIMITIVE_CAT( a, ... ) a ## __VA_ARGS__
	
	#define LIBANDRIA4_CONCAT( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	#define LIBANDRIA4_CONCATENATE( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	#define LIBANDRIA4_JOIN( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	
	
		/* LIBANDRIA4_PREPROCTIME_SIZEOF() only properly supports up to 16 */
		/*  arguments. If you change that, then remember that things in */
		/*  ./math.h and ./arraccess.h will need to be updated as well. */
		/* The "dummy, ## __VA_ARGS__" is because GCC will eliminate the */
		/*  comma in this case if __VA_ARGS__ is empty, allowing us to */
		/*  detect a size of 0. */
	#define LIBANDRIA4_PREPROCTIME_SIZEOF( ... ) \
		LIBANDRIA4_RETURN_17TH( dummy, ## __VA_ARGS__,  15, 14, 13,  12, 11, 10, 9,  8, 7, 6, 5,  4, 3, 2, 1,  0,  -1 )
	
	#define LIBANDRIA4_COMPILETIME_SIZEOF( ... ) \
		( sizeof( (int[]){ __VA_ARGS__ } ) / sizeof( int ) )
	
	#define LIBANDRIA4_APPLY( func, ... ) func( __VA_ARGS__ )
	#define LIBANDRIA4_APPLY_GATE( flag, func ) \
		LIBANDRIA4_IIF( flag ) ( func, LIBANDRIA4_APPLY_GATE( 1, func ) )
			/* This will initially result in an UNPROCESSED call to */
			/*  *_APPLY_GATE() just sitting amidst your code, but when you */
			/*  run it through EVAL() later it SHOULD get processed. The */
			/*  basic design was created for macrotime/tree.h. You should */
			/*  generally wrap it in another function of your own. */
			/* See also LIBANDRIA4_IDENTITY_LATER() in this same file. */
	#define LIBANDRIA4_APPLY_LATER( func ) LIBANDRIA4_APPLY_GATE( 0, func )
	
	
	/* These generate a function that returns an integer that uniquely */
	/*  identifies the provided type. Extra differentiation via tag, just in */
	/*  case. Use *_IDFUNC() for POD types, use *_IDFUNC2() for non-POD */
	/*  types. And yes, it's ok to use the statics as variables, as long as */
	/*  you know what you're doing. */
	#define LIBANDRIA4_BUILDIDFUNC( type, tag, inner_type ) \
		uintptr_t libandria4_idfunc_type_##type##tag() { \
			static inner_type t; return( (uintptr_t)&t ); }
		/* As above, but with call-once configuration, for more advanced */
		/*  type info. */
	#define LIBANDRIA4_BUILDIDFUNC2( type, tag, inner_type, config_func ) \
		uintptr_t libandria4_idfunc_type_##type##tag() { \
			static inner_type t, *t_ = (inner_type*)0; \
			if( !t_ ) { t_ = &t; config_func( t_ ); } \
			return( (uintptr_t)t_ ); }
	
	
		/* These exist for the sake of doing nothing, when you would */
		/*  otherwise do something. */
	#define LIBANDRIA4_NOACTION() 
	
	#define LIBANDRIA4_IGNORETHIS 
	#define LIBANDRIA4_IGNORETHIS_ 
	#define LIBANDRIA4_PUSH_IGNORETHIS( ... ) LIBANDRIA4_IGNORETHIS ( __VA_ARGS__ )
	
	#define LIBANDRIA4_NULL_MACRO( ... )
	#define LIBANDRIA4_PUSH_NULLMACRO( ... ) LIBANDRIA4_NULL_MACRO
	#define LIBANDRIA4_DOUBLEPUSH_NULLMACRO( ... ) LIBANDRIA4_PUSH_NULLMACRO
	
	
	#define LIBANDRIA4_STRIPPARENS( ... ) LIBANDRIA4_STRIPPARENS_INNER __VA_ARGS__
	#define LIBANDRIA4_STRIPPARENS_INNER( ... ) __VA_ARGS__
	
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
	
	
	#define LIBANDRIA4_IGNORETHIS_LIBANDRIA4_UNPARENTHESIZE_RECURSE 
	#define LIBANDRIA4_UNPARENTHESIZE( x ) \
		LIBANDRIA4_CAT( LIBANDRIA4_IGNORETHIS_, LIBANDRIA4_UNPARENTHESIZE_RECURSE x )
	#define LIBANDRIA4_UNPARENTHESIZE_RECURSE( ... ) \
		LIBANDRIA4_UNPARENTHESIZE_RECURSE __VA_ARGS__
	
		/* If the first argument has paired parentheses, then this returns */
		/*  1, else 0. */
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED( ... )
		LIBANDRIA4_RETURN_1( \
			LIBANDRIA4_CAT( \
				LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_, LIBANDRIA4_TRUEFUNC __VA_ARGS__ \
			) \
		)
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_1 1, ~
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_LIBANDRIA4_TRUEFUNC 0, ~
	
	
	#define LIBANDRIA4_PUSH_COMMA( ... ) ,
	
	
	#define LIBANDRIA4_CHECK( ... ) LIBANDRIA4_RETURN_2ND( __VA_ARGS__, 0 )
		/* Should x be wrapped in parens for this to work right? */
	#define LIBANDRIA4_PROBE( x ) x, 1,
	
	
	#define LIBANDRIA4_IS_PAREN( x ) LIBANDRIA4_CHECK( LIBANDRIA4_IS_PAREN_PROBE x )
	#define LIBANDRIA4_IS_PAREN_PROBE( ... ) LIBANDRIA4_PROBE( ~ )
	
	
	#define LIBANDRIA4_PAREN_GATE( func, flag, ... ) \
	    LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( flag ) )( func, LIBANDRIA4_NULL_MACRO )
	#define LIBANDRIA4_PAREN_UNGATE( func, flag, ... ) \
	    LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( flag ) )( LIBANDRIA4_NULL_MACRO, func )
	
	
	#define LIBANDRIA4_IDENTITY( ... ) __VA_ARGS__
	#define LIBANDRIA4_IDENTITY_GATE( flag ) \
		LIBANDRIA4_IIF( flag ) ( LIBANDRIA4_IDENTITY, LIBANDRIA4_IDENTITY_GATE( 1 ) )
			/* This will initially result in an UNPROCESSED call to */
			/*  *_IDENTITY_GATE() just sitting amidst your code, but when */
			/*  you run it through EVAL() later it SHOULD get processed. The */
			/*  basic design was created for macrotime/tree.h. You should */
			/*  generally wrap it in another function of your own. */
			/* See also LIBANDRIA4_APPLY_LATER() in this same file. */
	#define LIBANDRIA4_IDENTITY_LATER( ... ) LIBANDRIA4_IDENTITY_GATE( 0 )( __VA_ARGS__ )
	
	#define LIBANDRIA4_BOOL( x ) LIBANDRIA4_NEGATE( LIBANDRIA4_NEGATE( x ) )
	
	#define LIBANDRIA4_NEGATE( x ) LIBANDRIA4_CHECK( LIBANDRIA4_CAT( LIBANDRIA4_NEGATE_, x ) )
	#define LIBANDRIA4_NEGATE_0 LIBANDRIA4_PROBE( ~ )
	
	#define LIBANDRIA4_IS0( x ) LIBANDRIA4_CHECK( LIBANDRIA4_CAT( LIBANDRIA4_IS0_, x ) )
	#define LIBANDRIA4_IS0_0 LIBANDRIA4_PROBE( ~ )
	#define LIBANDRIA4_IS1( x ) LIBANDRIA4_CHECK( LIBANDRIA4_CAT( LIBANDRIA4_IS1_, x ) )
	#define LIBANDRIA4_IS1_1 LIBANDRIA4_PROBE( ~ )
	#define LIBANDRIA4_IS2( x ) LIBANDRIA4_CHECK( LIBANDRIA4_CAT( LIBANDRIA4_IS2_, x ) )
	#define LIBANDRIA4_IS2_2 LIBANDRIA4_PROBE( ~ )
	#define LIBANDRIA4_IS3( x ) LIBANDRIA4_CHECK( LIBANDRIA4_CAT( LIBANDRIA4_IS3_, x ) )
	#define LIBANDRIA4_IS3_3 LIBANDRIA4_PROBE( ~ )
	
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
	
	
	#define LIBANDRIA4_IIF( cond ) LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_IIF_, cond )
	#define LIBANDRIA4_IIF_0( t, ... ) __VA_ARGS__
	#define LIBANDRIA4_IIF_1( t, ... ) t
	
	#define LIBANDRIA4_NNIF( cond ) LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_NNIF_, cond )
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
		LIBANDRIA4_WHEN( LIBANDRIA4_CHECK( LIBANDRIA4_PRIMITIVE_CAT( \
			LIBANDRIA4_PRIMITIVE_CAT( LIBANDRIA4_WHEN, match ), \
			LIBANDRIA4_PRIMITIVE_CAT( _, flag ) ), 0 ) )
	
	#define LIBANDRIA4_WHEN0_0 x, 1
	#define LIBANDRIA4_WHEN0( flag ) LIBANDRIA4_WHENx( 0, flag )
	#define LIBANDRIA4_WHEN1_1 x, 1
	#define LIBANDRIA4_WHEN1( flag ) LIBANDRIA4_WHENx( 1, flag )
	#define LIBANDRIA4_WHEN2_2 x, 1
	#define LIBANDRIA4_WHEN2( flag ) LIBANDRIA4_WHENx( 2, flag )
	#define LIBANDRIA4_WHEN3_3 x, 1
	#define LIBANDRIA4_WHEN3( flag ) LIBANDRIA4_WHENx( 3, flag )
	
	
		/* Look in normchar.h if you want to know what this exists for. */
	#define LIBANDRIA4_DEFAULTABLE_VALUE( val, default ) \
		LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( val ) ) ( default, val )
	
	
		/* These probably belong in a counting system, but they also */
		/*  describe something somewhat basic. */
	#define LIBANDRIA4_ADJACENTNUMS_0 9, 1
	#define LIBANDRIA4_ADJACENTNUMS_1 0, 2
	#define LIBANDRIA4_ADJACENTNUMS_2 1, 3
	#define LIBANDRIA4_ADJACENTNUMS_3 2, 4
	#define LIBANDRIA4_ADJACENTNUMS_4 3, 5
	#define LIBANDRIA4_ADJACENTNUMS_5 4, 6
	#define LIBANDRIA4_ADJACENTNUMS_6 5, 7
	#define LIBANDRIA4_ADJACENTNUMS_7 6, 8
	#define LIBANDRIA4_ADJACENTNUMS_8 7, 9
	#define LIBANDRIA4_ADJACENTNUMS_9 8, 0
	
#endif
/* End libsndria4 macrotime simpleops.h */
