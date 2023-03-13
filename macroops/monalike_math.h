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

#ifndef LIB4_MONALIKEMATH_H
# define LIB4_MONALIKEMATH_H
	
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
	/* Note: it may be desirable to use LIB4_ADD_KAHAN() from stddefs.h to */
	/*  provide an improved-accuracy addition option. */
	
		/* For LIB4_SETa( val ) & similar. */
	#include "stddefs.h"
	
		/* err_monads.h has actually not been brought fully localized yet. */
	#include "err_monads.h"
	
	BUILD_MAYBETYPE( lib4_monadouble, double )
	
	
	lib4_monadouble lib4_monadouble_just( double dbl )
	{
		return( BUILD_JUST( lib4_monadouble, double, dbl ) );
	}
	lib4_monadouble lib4_monadouble_nothing()
	{
		return( BUILD_NOTHING( lib4_monadouble, double ) );
	}
	#define LIB4_MONADOUBLE_RETURN_NOTHING() \
		return( lib4_monadouble_nothing() )
	
	lib4_monadouble lib4_monadouble_identity( lib4_monadouble mdbl )
	{
		return( mdbl );
	}
	
		/* Indicates whether mdbl contains the result of a successful */
		/*  execution or not. */
	int lib4_monadouble_didsucceed( lib4_monadouble mdbl, double *dbl )
	{
		double d;
		#define lib4_monadouble_resolvable_MATCH( val ) d = ( val )
		
		MAYBE_BODYMATCH( mdbl, lib4_monadouble_resolvable_MATCH, LIB4_RETURN0 )

		if( dbl )
		{
			*dbl = d;
		}
		
		return( 1 );
	}
	
	
	#define LIB4_MONADOUBLE_BUILDUNARYOP( nametag, opfunc ) \
		lib4_monadouble lib4_monadouble_ ## nametag( lib4_monadouble mdbl ) { \
			return( \
				MAYBE_EXPRMATCH( mdbl, opfunc, lib4_monadouble_nothing ) ); }
	#define LIB4_MONADOUBLE_BUILDBINARYOP( nametag, opfunc ) \
		lib4_monadouble lib4_monadouble_ ## nametag \
			( lib4_monadouble a_, lib4_monadouble b_ ) { double a, b; \
			MAYBE_BODYMATCH( a_, LIB4_SETa, LIB4_MONADOUBLE_RETURN_NOTHING ) \
			MAYBE_BODYMATCH( b_, LIB4_SETb, LIB4_MONADOUBLE_RETURN_NOTHING ) \
			return( lib4_monadouble_just( opfunc( a, b ) ) ); }
	
	
	#define LIB4_MONADOUBLE_NOT( val ) \
		lib4_monadouble_just( !( val ) )
	LIB4_MONADOUBLE_BUILDUNARYOP( not, LIB4_MONADOUBLE_NOT )
	
	#define LIB4_MONADOUBLE_NEGATIVE( val ) \
		lib4_monadouble_just( -( val ) )
	LIB4_MONADOUBLE_BUILDUNARYOP( negative, LIB4_MONADOUBLE_NEGATIVE )
	
	/* No complement, because the logic of bitwise operations on floats & */
	/*  doubles is dubious. */
	
	
	#define LIB4_MONADOUBLE_ADD( a, b ) ( ( a ) + ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( add, LIB4_MONADOUBLE_ADD )
	
	#define LIB4_MONADOUBLE_SUB( a, b ) ( ( a ) - ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( sub, LIB4_MONADOUBLE_SUB )
	
	#define LIB4_MONADOUBLE_MUL( a, b ) ( ( a ) * ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( mul, LIB4_MONADOUBLE_MUL )
	
	#define LIB4_MONADOUBLE_DIV( a, b ) ( ( a ) / ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( div, LIB4_MONADOUBLE_DIV )
	
	#define LIB4_MONADOUBLE_MOD( a, b ) ( ( a ) % ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( mod, LIB4_MONADOUBLE_MOD )
	
	#define LIB4_MONADOUBLE_EQ( a, b ) ( ( a ) == ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( eq, LIB4_MONADOUBLE_EQ )
	
	#define LIB4_MONADOUBLE_NEQ( a, b ) ( ( a ) != ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( neq, LIB4_MONADOUBLE_NEQ )
	
	#define LIB4_MONADOUBLE_GREATER( a, b ) ( ( a ) > ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( greater, LIB4_MONADOUBLE_GREATER )
	
	#define LIB4_MONADOUBLE_LESSER( a, b ) ( ( a ) < ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( lesser, LIB4_MONADOUBLE_LESSER )
	
	#define LIB4_MONADOUBLE_GREQ( a, b ) ( ( a ) >= ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( greq, LIB4_MONADOUBLE_GREQ )
	
	#define LIB4_MONADOUBLE_LSEQ( a, b ) ( ( a ) <= ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( lseq, LIB4_MONADOUBLE_LSEQ )
	
	#define LIB4_MONADOUBLE_LAND( a, b ) ( ( a ) && ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( land, LIB4_MONADOUBLE_LAND )
	
	#define LIB4_MONADOUBLE_LOR( a, b ) ( ( a ) || ( b ) )
	LIB4_MONADOUBLE_BUILDBINARYOP( lor, LIB4_MONADOUBLE_LOR )
	
#endif
/* End lib4 monalike_math.h */
