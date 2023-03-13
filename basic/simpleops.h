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

#ifndef LIB4_MACROTIME_SIMPLEOPS_H
# define LIB4_MACROTIME_SIMPLEOPS_H
	
	
		/* For LIB4_RETURN_* macros. */
	#include "arraccess.h"
	
	
		/* These are somewhat "special": they're used when you need to embed */
		/*  a "set" operation via macro. You can always define more of these */
		/*  if needed. Try not to though. */
	#define LIB4_OP_SETa( val ) ( a = (val) )
	#define LIB4_OP_SETb( val ) ( b = (val) )
	#define LIB4_OP_SETc( val ) ( c = (val) )
	#define LIB4_OP_SETd( val ) ( d = (val) )
	#define LIB4_OP_SETe( val ) ( e = (val) )
	
	
	#define LIB4_STRINGIFY( a ) LIB4_INNER_STRINGIFY( a )
	#define LIB4_INNER_STRINGIFY( a ) #a
	
	
	#define LIB4_TRUEFUNC() 1
	#define LIB4_FALSEFUNC() 0
	
	#define LIB4_BOOLCAT( a, b ) \
		LIB4_CAT( LIB4_BOOL( a ), LIB4_BOOL( b ) )
	#define LIB4_CAT( a, ... ) LIB4_PRIMITIVE_CAT( a, __VA_ARGS__ )
	#define LIB4_PRIMITIVE_CAT( a, ... ) a ## __VA_ARGS__
	
	#define LIB4_CONCAT( ... ) LIB4_CAT( __VA_ARGS__ )
	#define LIB4_CONCATENATE( ... ) LIB4_CAT( __VA_ARGS__ )
	#define LIB4_JOIN( ... ) LIB4_CAT( __VA_ARGS__ )
	
	
		/* LIB4_PREPROCTIME_SIZEOF() only properly supports up to 16 */
		/*  arguments. If you change that, then remember that things in */
		/*  ./math.h and ./arraccess.h will need to be updated as well. */
		/* The "dummy, ## __VA_ARGS__" is because GCC will eliminate the */
		/*  comma in this case if __VA_ARGS__ is empty, allowing us to */
		/*  detect a size of 0. */
	#define LIB4_PREPROCTIME_SIZEOF( ... ) \
		LIB4_RETURN_17TH( dummy, ## __VA_ARGS__,  15, 14, 13,  12, 11, 10, 9,  8, 7, 6, 5,  4, 3, 2, 1,  0,  -1 )
	
	#define LIB4_COMPILETIME_SIZEOF( ... ) \
		( sizeof( (int[]){ __VA_ARGS__ } ) / sizeof( int ) )
	
	#define LIB4_APPLY( func, ... ) func( __VA_ARGS__ )
	#define LIB4_APPLY_GATE( flag, func ) \
		LIB4_IIF( flag ) ( func, LIB4_APPLY_GATE( 1, func ) )
			/* This will initially result in an UNPROCESSED call to */
			/*  *_APPLY_GATE() just sitting amidst your code, but when you */
			/*  run it through EVAL() later it SHOULD get processed. The */
			/*  basic design was created for macrotime/tree.h. You should */
			/*  generally wrap it in another function of your own. */
			/* See also LIB4_IDENTITY_LATER() in this same file. */
	#define LIB4_APPLY_LATER( func ) LIB4_APPLY_GATE( 0, func )
	
	
	/* These generate a function that returns an integer that uniquely */
	/*  identifies the provided type. Extra differentiation via tag, just in */
	/*  case. Use *_IDFUNC() for POD types, use *_IDFUNC2() for non-POD */
	/*  types. And yes, it's ok to use the statics as variables, as long as */
	/*  you know what you're doing. */
	#define LIB4_BUILDIDFUNC( type, tag, inner_type ) \
		uintptr_t lib4_idfunc_type_##type##tag() { \
			static inner_type t; return( (uintptr_t)&t ); }
		/* As above, but with call-once configuration, for more advanced */
		/*  type info. */
	#define LIB4_BUILDIDFUNC2( type, tag, inner_type, config_func ) \
		uintptr_t lib4_idfunc_type_##type##tag() { \
			static inner_type t, *t_ = (inner_type*)0; \
			if( !t_ ) { t_ = &t; config_func( t_ ); } \
			return( (uintptr_t)t_ ); }
	
	
		/* These exist for the sake of doing nothing, when you would */
		/*  otherwise do something. */
	#define LIB4_NOACTION() 
	
	#define LIB4_IGNORETHIS 
	#define LIB4_IGNORETHIS_ 
	#define LIB4_PUSH_IGNORETHIS( ... ) LIB4_IGNORETHIS ( __VA_ARGS__ )
	
	#define LIB4_NULL_MACRO( ... )
	#define LIB4_PUSH_NULLMACRO( ... ) LIB4_NULL_MACRO
	#define LIB4_DOUBLEPUSH_NULLMACRO( ... ) LIB4_PUSH_NULLMACRO
	
	
	#define LIB4_STRIPPARENS( ... ) LIB4_STRIPPARENS_INNER __VA_ARGS__
	#define LIB4_STRIPPARENS_INNER( ... ) __VA_ARGS__
	
	#define LIB4_NULL_SIZEDMACRO( size ) \
		LIB4_PRIMITIVE_CAT( LIB4_NULL_SIZEDMACRO_, size )
	
	#define LIB4_NULL_SIZEDMACRO_0()
	
	#define LIB4_NULL_SIZEDMACRO_1( a )
	#define LIB4_NULL_SIZEDMACRO_2( a, b )
	#define LIB4_NULL_SIZEDMACRO_3( a, b, c )
	#define LIB4_NULL_SIZEDMACRO_4( a, b, c, d )
	
	#define LIB4_NULL_SIZEDMACRO_5( a, b, c, d,  e )
	#define LIB4_NULL_SIZEDMACRO_6( a, b, c, d,  e, f )
	#define LIB4_NULL_SIZEDMACRO_7( a, b, c, d,  e, f, g )
	#define LIB4_NULL_SIZEDMACRO_8( a, b, c, d,  e, f, g, h )
	
	#define LIB4_NULL_SIZEDMACRO_9( a, b, c, d,  e, f, g, h,  i )
	#define LIB4_NULL_SIZEDMACRO_10( a, b, c, d,  e, f, g, h,  i, j )
	#define LIB4_NULL_SIZEDMACRO_11( a, b, c, d,  e, f, g, h,  i, j, k )
	#define LIB4_NULL_SIZEDMACRO_12( a, b, c, d,  e, f, g, h,  i, j, k, l )
	
	#define LIB4_NULL_SIZEDMACRO_13( a, b, c, d,  e, f, g, h,  i, j, k, l,  m )
	#define LIB4_NULL_SIZEDMACRO_14( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n )
	#define LIB4_NULL_SIZEDMACRO_15( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o )
	#define LIB4_NULL_SIZEDMACRO_16( a, b, c, d,  e, f, g, h,  i, j, k, l,  m, n, o, p )
	
	
	#define LIB4_IGNORETHIS_LIB4_UNPARENTHESIZE_RECURSE 
	#define LIB4_UNPARENTHESIZE( x ) \
		LIB4_CAT( LIB4_IGNORETHIS_, LIB4_UNPARENTHESIZE_RECURSE x )
	#define LIB4_UNPARENTHESIZE_RECURSE( ... ) \
		LIB4_UNPARENTHESIZE_RECURSE __VA_ARGS__
	
		/* If the first argument has paired parentheses, then this returns */
		/*  1, else 0. */
	#define LIB4_PARENTHESIZE_ISHEADED( ... )
		LIB4_RETURN_1( \
			LIB4_CAT( \
				LIB4_PARENTHESIZE_ISHEADED_FLAG_, LIB4_TRUEFUNC __VA_ARGS__ \
			) \
		)
	#define LIB4_PARENTHESIZE_ISHEADED_FLAG_1 1, ~
	#define LIB4_PARENTHESIZE_ISHEADED_FLAG_LIB4_TRUEFUNC 0, ~
	
	
	#define LIB4_PUSH_COMMA( ... ) ,
	
	
	#define LIB4_CHECK( ... ) LIB4_RETURN_2ND( __VA_ARGS__, 0 )
		/* Should x be wrapped in parens for this to work right? */
	#define LIB4_PROBE( x ) x, 1,
	
	
	#define LIB4_IS_PAREN( x ) LIB4_CHECK( LIB4_IS_PAREN_PROBE x )
	#define LIB4_IS_PAREN_PROBE( ... ) LIB4_PROBE( ~ )
	
	
	#define LIB4_PAREN_GATE( func, flag, ... ) \
	    LIB4_IIF( LIB4_IS_PAREN( flag ) )( func, LIB4_NULL_MACRO )
	#define LIB4_PAREN_UNGATE( func, flag, ... ) \
	    LIB4_IIF( LIB4_IS_PAREN( flag ) )( LIB4_NULL_MACRO, func )
	
	
	#define LIB4_IDENTITY( ... ) __VA_ARGS__
	#define LIB4_IDENTITY_GATE( flag ) \
		LIB4_IIF( flag ) ( LIB4_IDENTITY, LIB4_IDENTITY_GATE( 1 ) )
			/* This will initially result in an UNPROCESSED call to */
			/*  *_IDENTITY_GATE() just sitting amidst your code, but when */
			/*  you run it through EVAL() later it SHOULD get processed. The */
			/*  basic design was created for macrotime/tree.h. You should */
			/*  generally wrap it in another function of your own. */
			/* See also LIB4_APPLY_LATER() in this same file. */
	#define LIB4_IDENTITY_LATER( ... ) LIB4_IDENTITY_GATE( 0 )( __VA_ARGS__ )
	
	#define LIB4_BOOL( x ) LIB4_NEGATE( LIB4_NEGATE( x ) )
	
	#define LIB4_NEGATE( x ) LIB4_CHECK( LIB4_CAT( LIB4_NEGATE_, x ) )
	#define LIB4_NEGATE_0 LIB4_PROBE( ~ )
	
	#define LIB4_IS0( x ) LIB4_CHECK( LIB4_CAT( LIB4_IS0_, x ) )
	#define LIB4_IS0_0 LIB4_PROBE( ~ )
	#define LIB4_IS1( x ) LIB4_CHECK( LIB4_CAT( LIB4_IS1_, x ) )
	#define LIB4_IS1_1 LIB4_PROBE( ~ )
	#define LIB4_IS2( x ) LIB4_CHECK( LIB4_CAT( LIB4_IS2_, x ) )
	#define LIB4_IS2_2 LIB4_PROBE( ~ )
	#define LIB4_IS3( x ) LIB4_CHECK( LIB4_CAT( LIB4_IS3_, x ) )
	#define LIB4_IS3_3 LIB4_PROBE( ~ )
	
	#define LIB4_AND( a, b ) \
		LIB4_CAT( LIB4_AND_, LIB4_BOOLCAT( a, b ) )
	#define LIB4_AND_00 0
	#define LIB4_AND_01 0
	#define LIB4_AND_10 0
	#define LIB4_AND_11 1
	
	#define LIB4_IOR( a, b ) \
		LIB4_CAT( LIB4_IOR_, LIB4_BOOLCAT( a, b ) )
	#define LIB4_IOR_00 0
	#define LIB4_IOR_01 1
	#define LIB4_IOR_10 1
	#define LIB4_IOR_11 1
	
	#define LIB4_XOR( a, b ) \
		LIB4_CAT( LIB4_XOR_, LIB4_BOOLCAT( a, b ) )
	#define LIB4_XOR_00 0
	#define LIB4_XOR_01 1
	#define LIB4_XOR_10 1
	#define LIB4_XOR_11 0
	
	#define LIB4_NAND( a, b ) \
		LIB4_CAT( LIB4_NAND_, LIB4_BOOLCAT( a, b ) )
	#define LIB4_NAND_00 1
	#define LIB4_NAND_01 1
	#define LIB4_NAND_10 1
	#define LIB4_NAND_11 0
	
	#define LIB4_INOR( a, b ) \
		LIB4_CAT( LIB4_INOR_, LIB4_BOOLCAT( a, b ) )
	#define LIB4_INOR_00 1
	#define LIB4_INOR_01 0
	#define LIB4_INOR_10 0
	#define LIB4_INOR_11 0
	
	#define LIB4_XNOR( a, b ) \
		LIB4_CAT( LIB4_XNOR_, LIB4_BOOLCAT( a, b ) )
	#define LIB4_XNOR_00 1
	#define LIB4_XNOR_01 0
	#define LIB4_XNOR_10 0
	#define LIB4_XNOR_11 1
	
	
	#define LIB4_IIF( cond ) LIB4_PRIMITIVE_CAT( LIB4_IIF_, cond )
	#define LIB4_IIF_0( t, ... ) __VA_ARGS__
	#define LIB4_IIF_1( t, ... ) t
	
	#define LIB4_NNIF( cond ) LIB4_PRIMITIVE_CAT( LIB4_NNIF_, cond )
	#define LIB4_NNIF_0( t, ... ) t
	#define LIB4_NNIF_1( t, ... ) __VA_ARGS__
	
	
		/* Used as follows: */
			/* LIB4_IF_ELSE( cond )( if cond == 1 )( if cond == 0 ) */
	#define LIB4_IF_ELSE( cond ) \
		LIB4_IIF( LIB4_BOOL( cond ) )( LIB4_IF_1, LIB4_IF_0 )
	
	#define LIB4_IF_0( ... ) LIB4_IF_ELSE_0
	#define LIB4_IF_1( ... ) __VA_ARGS__ LIB4_IF_ELSE_1
	
	#define LIB4_IF_ELSE_0( ... ) __VA_ARGS__
	#define LIB4_IF_ELSE_1( ... ) 
	
	
		/* Used as follows: */
			/* LIB4_WHEN( cond )( if cond == 1 ) */
	#define LIB4_WHEN_DISCARD( ... )
	#define LIB4_WHEN_PERPETUATE( ... ) __VA_ARGS__
	#define LIB4_WHEN( cond ) \
		LIB4_IIF( LIB4_BOOL( cond ) ) \
			( LIB4_WHEN_PERPETUATE, LIB4_WHEN_DISCARD )
	
	#define LIB4_WHENx( match, flag ) \
		LIB4_WHEN( LIB4_CHECK( LIB4_PRIMITIVE_CAT( \
			LIB4_PRIMITIVE_CAT( LIB4_WHEN, match ), \
			LIB4_PRIMITIVE_CAT( _, flag ) ), 0 ) )
	
	#define LIB4_WHEN0_0 x, 1
	#define LIB4_WHEN0( flag ) LIB4_WHENx( 0, flag )
	#define LIB4_WHEN1_1 x, 1
	#define LIB4_WHEN1( flag ) LIB4_WHENx( 1, flag )
	#define LIB4_WHEN2_2 x, 1
	#define LIB4_WHEN2( flag ) LIB4_WHENx( 2, flag )
	#define LIB4_WHEN3_3 x, 1
	#define LIB4_WHEN3( flag ) LIB4_WHENx( 3, flag )
	
	
		/* Look in normchar.h if you want to know what this exists for. */
	#define LIB4_DEFAULTABLE_VALUE( val, default ) \
		LIB4_IIF( LIB4_IS_PAREN( val ) ) ( default, val )
	
	
		/* These probably belong in a counting system, but they also */
		/*  describe something somewhat basic. */
	#define LIB4_ADJACENTNUMS_0 9, 1
	#define LIB4_ADJACENTNUMS_1 0, 2
	#define LIB4_ADJACENTNUMS_2 1, 3
	#define LIB4_ADJACENTNUMS_3 2, 4
	#define LIB4_ADJACENTNUMS_4 3, 5
	#define LIB4_ADJACENTNUMS_5 4, 6
	#define LIB4_ADJACENTNUMS_6 5, 7
	#define LIB4_ADJACENTNUMS_7 6, 8
	#define LIB4_ADJACENTNUMS_8 7, 9
	#define LIB4_ADJACENTNUMS_9 8, 0
	
#endif
/* End lib4 macrotime simpleops.h */
