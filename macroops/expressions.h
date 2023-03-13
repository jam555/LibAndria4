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



/* Expression macros. */
/* These macros exist to provide a framework for writing algorithms & */
/*  functions in an abstract fashion. You should never begin with these, but */
/*  instead translate to them from something else. */

#define EXPR_SET( dest, src ) ( ( dest ) = (src ) )

#define EXPR_MONOPRE( a, op ) \
	( ( op ) ( a ) )
#define EXPR_MONOPOST( a, op ) \
	( ( a ) ( op ) )
#define EXPR_BININF( a, b, op ) \
	( ( a ) ( op ) ( b ) )
#define EXPR_TRIINF( a, b, c, opa, opb ) \
	( ( a ) (opa) ( b ) (opb) ( c ) )
#define EXPR_MONOCONF( a, opa, opb ) \
	( (opa) ( a ) (opb) )

#define EXPR_NOT( a ) EXPR_MONOPRE( ( a ), ! )
#define EXPR_TOGGLETOP( a ) \
	EXPR_BXOR( \
		EXPR_ONESCOMPL( a ), \
		1 << ( ( sizeof( ( a ) ) * CHAR_BIT ) - 1 ) )
#define EXPR_NOOPIDENT( a ) ( a )
#define EXPR_POSIDENT( a ) EXPR_MONOPRE( ( a ), + )
#define EXPR_NEGATE( a ) EXPR_MONOPRE( ( a ), - )
#define EXPR_ONESCOMPL( a ) EXPR_MONOPRE( ( a ), ~ )
#define EXPR_TWOSCOMPL( a ) EXPR_ADD( EXPR_ONESCOMPL( a ), 1 )
#define EXPR_PREINC( a ) EXPR_MONOPRE( ( a ), ++ )
#define EXPR_POSTINCR( a ) EXPR_MONOPOST( ( a ), ++ )
#define EXPR_PREDECR( a ) EXPR_MONOPRE( ( a ), -- )
#define EXPR_POSTDECR( a ) EXPR_MONOPOST( ( a ), -- )
#define EXPR_DEREF( a ) EXPR_MONOPRE( ( a ), * )
#define EXPR_REFOF( a ) EXPR_MONOPRE( ( a ), & )
#define EXPR_ARRWRAP( a ) EXPR_MONOCONF( ( a ), [, ] )

#define EXPR_CTERNARY( test, succ, fail ) \
	EXPR_TRIINF( test, succ, fail, ?, : )

	/* The *PY* are Python style logicals: instead of returning true/false, */
	/*  they return the last computed value. */
#define EXPR_PYAND( a, b ) EXPR_CTERNARY( ( a ), ( b ), ( a ) )
#define EXPY_PYOR( a, b ) EXPR_CTERNARY( ( a ), ( a ), ( b ) )
#define EXPR_LAND( a, b ) EXPR_BININF( ( a ), ( b ), && )
#define EXPR_LOR( a, b ) EXPR_BININF( ( a ), ( b ), || )
#define EXPR_BAND( a, b ) EXPR_BININF( ( a ), ( b ), & )
#define EXPR_BIOR( a, b ) EXPR_BININF( ( a ), ( b ), | )
#define EXPR_BXOR( a, b ) EXPR_BININF( ( a ), ( b ), ^ )
#define EXPR_ADD( a, b ) EXPR_BININF( ( a ), ( b ), + )
#define EXPR_SUB( a, b )  EXPR_BININF( ( a ), ( b ), - )
#define EXPR_MUL( a, b )  EXPR_BININF( ( a ), ( b ), * )
#define EXPR_DIV( a, b )  EXPR_BININF( ( a ), ( b ), / )
#define EXPR_MOD( a, b )  EXPR_BININF( ( a ), ( b ), % )
#define EXPR_LSHFT( a, b )  EXPR_BININF( ( a ), ( b ), << )
#define EXPR_RSHFT( a, b )  EXPR_BININF( ( a ), ( b ), >> )
#define EXPR_ARRACC( a, b ) ( ( a ) EXPR_ARRWRAP( b ) )
#define EXPR_NAMEACC( a, b ) EXPR_BININF( ( a ), ( b ), . )
#define EXPR_PTRACC( a, b ) EXPR_BININF( ( a ), ( b ), -> )
