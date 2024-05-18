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

#ifndef LIBANDRIA4_BASIC_SIMPLEOPS_H
# define LIBANDRIA4_BASIC_SIMPLEOPS_H
	
	
	#include "simpleruntimeops.h"
	
		/* For LIBANDRIA4_RETURN_* macros. */
	#include "arraccess.h"
		/* Mostly for true/false defines. */
	#include "../math/numerics.h"
	#include "../math/logic.h"
	#include "sizeofmacros.h"
	#include "nulls.h"
	
	
	#define LIBANDRIA4_OP_UNARYIDENTITY( val ) (val)
	
		/* These are somewhat "special": they're used when you need to embed */
		/*  a "set" operation via macro. You can always define more of these */
		/*  if needed. Try not to though. */
	#define LIBANDRIA4_OP_SETa( val ) ( a = (val) )
	#define LIBANDRIA4_OP_SETb( val ) ( b = (val) )
	#define LIBANDRIA4_OP_SETc( val ) ( c = (val) )
	#define LIBANDRIA4_OP_SETd( val ) ( d = (val) )
	#define LIBANDRIA4_OP_SETe( val ) ( e = (val) )
	
	#define LIBANDRIA4_OP_SETaTOn1( ... ) ( a = -1 )
	#define LIBANDRIA4_OP_SETbTOn1( ... ) ( b = -1 )
	#define LIBANDRIA4_OP_SETcTOn1( ... ) ( c = -1 )
	#define LIBANDRIA4_OP_SETdTOn1( ... ) ( d = -1 )
	#define LIBANDRIA4_OP_SETeTOn1( ... ) ( e = -1 )
	
	#define LIBANDRIA4_OP_SETaTO0( ... ) ( a = 0 )
	#define LIBANDRIA4_OP_SETbTO0( ... ) ( b = 0 )
	#define LIBANDRIA4_OP_SETcTO0( ... ) ( c = 0 )
	#define LIBANDRIA4_OP_SETdTO0( ... ) ( d = 0 )
	#define LIBANDRIA4_OP_SETeTO0( ... ) ( e = 0 )
	
	#define LIBANDRIA4_OP_SETaTO1( ... ) ( a = 1 )
	#define LIBANDRIA4_OP_SETbTO1( ... ) ( b = 1 )
	#define LIBANDRIA4_OP_SETcTO1( ... ) ( c = 1 )
	#define LIBANDRIA4_OP_SETdTO1( ... ) ( d = 1 )
	#define LIBANDRIA4_OP_SETeTO1( ... ) ( e = 1 )
	
	#define LIBANDRIA4_OP_SETaTO2( ... ) ( a = 2 )
	#define LIBANDRIA4_OP_SETbTO2( ... ) ( b = 2 )
	#define LIBANDRIA4_OP_SETcTO2( ... ) ( c = 2 )
	#define LIBANDRIA4_OP_SETdTO2( ... ) ( d = 2 )
	#define LIBANDRIA4_OP_SETeTO2( ... ) ( e = 2 )
	
	
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
	#define LIBANDRIA4_OP_RETURNVAL_32() return( 32 )
	#define LIBANDRIA4_OP_RETURNVAL_64() return( 64 )
	#define LIBANDRIA4_OP_RETURNVAL_99() return( 99 )
	#define LIBANDRIA4_OP_RETURNVAL_100() return( 100 )
	#define LIBANDRIA4_OP_RETURNVAL_128() return( 128 )
	#define LIBANDRIA4_OP_RETURNVAL_255() return( 255 )
	#define LIBANDRIA4_OP_RETURNVAL_256() return( 256 )
	#define LIBANDRIA4_OP_RETURNVAL_512() return( 512 )
	#define LIBANDRIA4_OP_RETURNVAL_999() return( 999 )
	#define LIBANDRIA4_OP_RETURNVAL_1000() return( 1000 )
	#define LIBANDRIA4_OP_RETURNVAL_1023() return( 1023 )
	#define LIBANDRIA4_OP_RETURNVAL_1024() return( 1024 )
	#define LIBANDRIA4_OP_RETURNVAL_1k() return( 1024 )
	#define LIBANDRIA4_OP_RETURNVAL_1K() return( 1024 )
	
	
		/* Reserved: LIBANDRIA4_OP_runable1 MUST be equivalent to a function */
		/*  pointer, and LIBANDRIA4_OP_runabledata1 MUST be equivalent to a */
		/*  pointer that it can take as it's first argument. Depending on */
		/*  your usage case, it CAN accept any variety of other arguments, */
		/*  and/or return any type. If The pointer is NULL, then the value */
		/*  of the variable named after *_ELSE will be returned instead of */
		/*  invoking the function pointer. */
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEa( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : a )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEb( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : b )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEc( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : c )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEd( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : d )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEe( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : e )
	
	/* The definitions below are as above, but the hook names have their */
	/*  contained number swapped to match the relevant macro. */
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEa( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : a )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEb( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : b )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEc( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : c )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEd( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : d )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEe( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : e )
	
	
	
	#define LIBANDRIA4_STRINGIFY( a ) LIBANDRIA4_INNER_STRINGIFY( a )
	#define LIBANDRIA4_INNER_STRINGIFY( a ) #a
	
	
	#define LIBANDRIA4_BOOLCAT( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_BOOL( a ), LIBANDRIA4_BOOL( b ) )
	#define LIBANDRIA4_CAT( a, ... ) LIBANDRIA4_PRIMITIVE_CAT( a, __VA_ARGS__ )
	#define LIBANDRIA4_PRIMITIVE_CAT( a, ... ) a ## __VA_ARGS__
	
	#define LIBANDRIA4_CONCAT( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	#define LIBANDRIA4_CONCATENATE( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	#define LIBANDRIA4_JOIN( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	
	
	#define LIBANDRIA4_CHECK( ... ) LIBANDRIA4_SELECT_2ND( __VA_ARGS__, 0 )
		/* Should x be wrapped in parens for this to work right? */
	#define LIBANDRIA4_PROBE( x ) x, 1,
	
	
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
	
	
	
	#define LIBANDRIA4_STRIPPARENS( ... ) LIBANDRIA4_STRIPPARENS_INNER __VA_ARGS__
	#define LIBANDRIA4_STRIPPARENS_INNER( ... ) __VA_ARGS__
	
	
	#define LIBANDRIA4_IGNORETHIS_LIBANDRIA4_UNPARENTHESIZE_RECURSE 
	#define LIBANDRIA4_UNPARENTHESIZE( x ) \
		LIBANDRIA4_CAT( LIBANDRIA4_IGNORETHIS_, LIBANDRIA4_UNPARENTHESIZE_RECURSE x )
	#define LIBANDRIA4_UNPARENTHESIZE_RECURSE( ... ) \
		LIBANDRIA4_UNPARENTHESIZE_RECURSE __VA_ARGS__
	
		/* If the first argument has paired parentheses, then this returns */
		/*  1, else 0. */
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED( ... ) \
		LIBANDRIA4_RETURN_1( \
			LIBANDRIA4_CAT( \
				LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_, LIBANDRIA4_TRUEFUNC __VA_ARGS__ \
			) \
		)
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_1 1, ~
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_LIBANDRIA4_TRUEFUNC 0, ~
	
	
	#define LIBANDRIA4_PUSH_COMMA( ... ) ,
	
	
	#define LIBANDRIA4_IS_PAREN( x ) LIBANDRIA4_CHECK( LIBANDRIA4_IS_PAREN_PROBE x )
	#define LIBANDRIA4_IS_PAREN_PROBE( ... ) LIBANDRIA4_PROBE( ~ )
	
	
	#define LIBANDRIA4_PAREN_GATE( func, flag, ... ) \
	    LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( flag ) )( func, LIBANDRIA4_NULL_MACRO )
	#define LIBANDRIA4_PAREN_UNGATE( func, flag, ... ) \
	    LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( flag ) )( LIBANDRIA4_NULL_MACRO, func )
	
#endif
/* End libsndria4 basic simpleops.h */
