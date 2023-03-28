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

#ifndef LIBANDRIA4_MATH_MONALIKEMATH_H
# define LIBANDRIA4_MATH_MONALIKEMATH_H
	
	/* Monadic math - monalike_math.h */
	/* This file implements some monad-based math functions. The intent is */
	/*  for non-float values to represent errors in the computation, instead */
	/*  of just shoving all of that through operations blindly. */
	
	/* "monalike" from monad-like. */
	/* Todo: detect infinites, errors, etc., and represent them via the */
	/*  monadic value. They currently just get treated like ordinary */
	/*  numbers, which is wrong/bad/suboptimal. */
	/* Note that this file combines a header and a ".c" file: these should */
	/*  be separated out for design reasons. */
	/* Also, should probably do versions for u- and int8_t, int, u- and */
	/*  intptr_t, and u- and intmax_t, and conversion functions. Maybe for */
	/*  fixed-point and ASN types as well, though that would require */
	/*  building the respective systems first. A purely software-based float */
	/*  implementation would be nice too. */
	/* Note: it may be desirable to use LIBANDRIA4_ADD_KAHAN() from stddefs.h to */
	/*  provide an improved-accuracy addition option. */
	
		/* For LIBANDRIA4_SETa( val ) & similar. */
	#include "../basic/simpleops.h"
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_monadouble, double )
	
	
	libandria4_monadouble libandria4_monadouble_just( double dbl )
	{
		return( LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_monadouble, double, dbl ) );
	}
	libandria4_monadouble libandria4_monadouble_nothing()
	{
		return( LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_monadouble, double ) );
	}
	#define LIBANDRIA4_MONADOUBLE_RETURN_NOTHING( ... ) \
		return( libandria4_monadouble_nothing() )
	
	libandria4_monadouble libandria4_monadouble_identity( libandria4_monadouble mdbl )
	{
		return( mdbl );
	}
	
		/* Indicates whether mdbl contains the result of a successful */
		/*  execution or not. */
	int libandria4_monadouble_didsucceed( libandria4_monadouble mdbl, double *dbl )
	{
		double d;
		
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( mdbl, LIBANDRIA4_OP_SETd, LIBANDRIA4_OP_RETURNVAL_0 )

		if( dbl )
		{
			*dbl = d;
		}
		
		return( 1 );
	}
	
	
	#define LIBANDRIA4_MONADOUBLE_BUILDUNARYOP( nametag, opfunc ) \
		libandria4_monadouble libandria4_monadouble_ ## nametag( libandria4_monadouble mdbl ) { \
			return( \
				LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( mdbl, opfunc, libandria4_monadouble_nothing ) ); }
	#define LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( nametag, opfunc ) \
		libandria4_monadouble libandria4_monadouble_ ## nametag \
			( libandria4_monadouble a_, libandria4_monadouble b_ ) { double a, b; \
			LIBANDRIA4_MONAD_MAYBE_BODYMATCH( a_, LIBANDRIA4_OP_SETa, LIBANDRIA4_MONADOUBLE_RETURN_NOTHING ) \
			LIBANDRIA4_MONAD_MAYBE_BODYMATCH( b_, LIBANDRIA4_OP_SETb, LIBANDRIA4_MONADOUBLE_RETURN_NOTHING ) \
			return( libandria4_monadouble_just( opfunc( a, b ) ) ); }
	
	
	#define LIBANDRIA4_MONADOUBLE_NOT( val ) \
		libandria4_monadouble_just( !( val ) )
	LIBANDRIA4_MONADOUBLE_BUILDUNARYOP( not, LIBANDRIA4_MONADOUBLE_NOT )
	
	#define LIBANDRIA4_MONADOUBLE_NEGATIVE( val ) \
		libandria4_monadouble_just( -( val ) )
	LIBANDRIA4_MONADOUBLE_BUILDUNARYOP( negative, LIBANDRIA4_MONADOUBLE_NEGATIVE )
	
	/* No complement, because the logic of bitwise operations on floats & */
	/*  doubles is dubious. */
	
	
	#define LIBANDRIA4_MONADOUBLE_ADD( a, b ) ( ( a ) + ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( add, LIBANDRIA4_MONADOUBLE_ADD )
	
	#define LIBANDRIA4_MONADOUBLE_SUB( a, b ) ( ( a ) - ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( sub, LIBANDRIA4_MONADOUBLE_SUB )
	
	#define LIBANDRIA4_MONADOUBLE_MUL( a, b ) ( ( a ) * ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( mul, LIBANDRIA4_MONADOUBLE_MUL )
	
	#define LIBANDRIA4_MONADOUBLE_DIV( a, b ) ( ( a ) / ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( div, LIBANDRIA4_MONADOUBLE_DIV )
	
	#define LIBANDRIA4_MONADOUBLE_MOD( a, b ) ( ( a ) % ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( mod, LIBANDRIA4_MONADOUBLE_MOD )
	
	#define LIBANDRIA4_MONADOUBLE_EQ( a, b ) ( ( a ) == ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( eq, LIBANDRIA4_MONADOUBLE_EQ )
	
	#define LIBANDRIA4_MONADOUBLE_NEQ( a, b ) ( ( a ) != ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( neq, LIBANDRIA4_MONADOUBLE_NEQ )
	
	#define LIBANDRIA4_MONADOUBLE_GREATER( a, b ) ( ( a ) > ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( greater, LIBANDRIA4_MONADOUBLE_GREATER )
	
	#define LIBANDRIA4_MONADOUBLE_LESSER( a, b ) ( ( a ) < ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( lesser, LIBANDRIA4_MONADOUBLE_LESSER )
	
	#define LIBANDRIA4_MONADOUBLE_GREQ( a, b ) ( ( a ) >= ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( greq, LIBANDRIA4_MONADOUBLE_GREQ )
	
	#define LIBANDRIA4_MONADOUBLE_LSEQ( a, b ) ( ( a ) <= ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( lseq, LIBANDRIA4_MONADOUBLE_LSEQ )
	
	#define LIBANDRIA4_MONADOUBLE_LAND( a, b ) ( ( a ) && ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( land, LIBANDRIA4_MONADOUBLE_LAND )
	
	#define LIBANDRIA4_MONADOUBLE_LOR( a, b ) ( ( a ) || ( b ) )
	LIBANDRIA4_MONADOUBLE_BUILDBINARYOP( lor, LIBANDRIA4_MONADOUBLE_LOR )
	
#endif
/* End libandria4 math monalike_math.h */
