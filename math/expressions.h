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

#ifndef LIBANDRIA4_MATH_EXPRESSIONS_H
# define LIBANDRIA4_MATH_EXPRESSIONS_H
	
	/* Expression macros. */
	/* These macros exist to provide a framework for writing algorithms & */
	/*  functions in an abstract fashion. You should never begin with these, but */
	/*  instead translate to them from something else. */
	
	#define LIBANDRIA4_EXPR_SET( dest, src ) ( ( dest ) = (src ) )
	
	#define LIBANDRIA4_EXPR_MONOPRE( a, op ) \
		( ( op ) ( a ) )
	#define LIBANDRIA4_EXPR_MONOPOST( a, op ) \
		( ( a ) ( op ) )
	#define LIBANDRIA4_EXPR_BININF( a, b, op ) \
		( ( a ) ( op ) ( b ) )
	#define LIBANDRIA4_EXPR_TRIINF( a, b, c, opa, opb ) \
		( ( a ) (opa) ( b ) (opb) ( c ) )
	#define LIBANDRIA4_EXPR_MONOCONF( a, opa, opb ) \
		( (opa) ( a ) (opb) )
	
	#define LIBANDRIA4_EXPR_NOT( a ) LIBANDRIA4_EXPR_MONOPRE( ( a ), ! )
	#define LIBANDRIA4_EXPR_TOGGLETOP( a ) \
		LIBANDRIA4_EXPR_BXOR( \
			LIBANDRIA4_EXPR_ONESCOMPL( a ), \
			1 << ( ( sizeof( ( a ) ) * CHAR_BIT ) - 1 ) )
	#define LIBANDRIA4_EXPR_NOOPIDENT( a ) ( a )
	#define LIBANDRIA4_EXPR_POSIDENT( a ) LIBANDRIA4_EXPR_MONOPRE( ( a ), + )
	#define LIBANDRIA4_EXPR_NEGATE( a ) LIBANDRIA4_EXPR_MONOPRE( ( a ), - )
	#define LIBANDRIA4_EXPR_ONESCOMPL( a ) LIBANDRIA4_EXPR_MONOPRE( ( a ), ~ )
	#define LIBANDRIA4_EXPR_TWOSCOMPL( a ) LIBANDRIA4_EXPR_ADD( LIBANDRIA4_EXPR_ONESCOMPL( a ), 1 )
	#define LIBANDRIA4_EXPR_PREINC( a ) LIBANDRIA4_EXPR_MONOPRE( ( a ), ++ )
	#define LIBANDRIA4_EXPR_POSTINCR( a ) LIBANDRIA4_EXPR_MONOPOST( ( a ), ++ )
	#define LIBANDRIA4_EXPR_PREDECR( a ) LIBANDRIA4_EXPR_MONOPRE( ( a ), -- )
	#define LIBANDRIA4_EXPR_POSTDECR( a ) LIBANDRIA4_EXPR_MONOPOST( ( a ), -- )
	#define LIBANDRIA4_EXPR_DEREF( a ) LIBANDRIA4_EXPR_MONOPRE( ( a ), * )
	#define LIBANDRIA4_EXPR_REFOF( a ) LIBANDRIA4_EXPR_MONOPRE( ( a ), & )
	#define LIBANDRIA4_EXPR_ARRWRAP( a ) LIBANDRIA4_EXPR_MONOCONF( ( a ), [, ] )
	
	#define LIBANDRIA4_EXPR_CTERNARY( test, succ, fail ) \
		LIBANDRIA4_EXPR_TRIINF( test, succ, fail, ?, : )
	
		/* The *PY* are Python style logicals: instead of returning true/false, */
		/*  they return the last computed value. */
	#define LIBANDRIA4_EXPR_PYAND( a, b ) LIBANDRIA4_EXPR_CTERNARY( ( a ), ( b ), ( a ) )
	#define LIBANDRIA4_EXPY_PYOR( a, b ) LIBANDRIA4_EXPR_CTERNARY( ( a ), ( a ), ( b ) )
	#define LIBANDRIA4_EXPR_LAND( a, b ) LIBANDRIA4_EXPR_BININF( ( a ), ( b ), && )
	#define LIBANDRIA4_EXPR_LOR( a, b ) LIBANDRIA4_EXPR_BININF( ( a ), ( b ), || )
	#define LIBANDRIA4_EXPR_BAND( a, b ) LIBANDRIA4_EXPR_BININF( ( a ), ( b ), & )
	#define LIBANDRIA4_EXPR_BIOR( a, b ) LIBANDRIA4_EXPR_BININF( ( a ), ( b ), | )
	#define LIBANDRIA4_EXPR_BXOR( a, b ) LIBANDRIA4_EXPR_BININF( ( a ), ( b ), ^ )
	#define LIBANDRIA4_EXPR_ADD( a, b ) LIBANDRIA4_EXPR_BININF( ( a ), ( b ), + )
	#define LIBANDRIA4_EXPR_SUB( a, b )  LIBANDRIA4_EXPR_BININF( ( a ), ( b ), - )
	#define LIBANDRIA4_EXPR_MUL( a, b )  LIBANDRIA4_EXPR_BININF( ( a ), ( b ), * )
	#define LIBANDRIA4_EXPR_DIV( a, b )  LIBANDRIA4_EXPR_BININF( ( a ), ( b ), / )
	#define LIBANDRIA4_EXPR_MOD( a, b )  LIBANDRIA4_EXPR_BININF( ( a ), ( b ), % )
	#define LIBANDRIA4_EXPR_LSHFT( a, b )  LIBANDRIA4_EXPR_BININF( ( a ), ( b ), << )
	#define LIBANDRIA4_EXPR_RSHFT( a, b )  LIBANDRIA4_EXPR_BININF( ( a ), ( b ), >> )
	#define LIBANDRIA4_EXPR_ARRACC( a, b ) ( ( a ) LIBANDRIA4_EXPR_ARRWRAP( b ) )
	#define LIBANDRIA4_EXPR_NAMEACC( a, b ) LIBANDRIA4_EXPR_BININF( ( a ), ( b ), . )
	#define LIBANDRIA4_EXPR_PTRACC( a, b ) LIBANDRIA4_EXPR_BININF( ( a ), ( b ), -> )
	
#endif
/* End libandria4 math expressions.h */
