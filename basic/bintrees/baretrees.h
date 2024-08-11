/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2024 Jared A. Maddox

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

#ifndef LIBANDRIA4_BASIC_BINTREES_BARETREES_H
# define LIBANDRIA4_BASIC_BINTREES_BARETREES_H
	
	#include <stddef.h>
	#include "../simpleops.h"
	#include "../monads.h"
	#include "../commonerrvals.h"
		/* For libandria4_commonio_err. */
	#include "../commonio.h"
	
	#include "bintrees.h"
	
		/* I don't know if this is the best algorithm, and perhaps it doesn't */
		/*  even work RIGHT, but it's my current version. Partially because */
		/*  the results I've found when looking up the algorithm seem to be */
		/*  AVL trees instead of vanilla binary trees. */
		/* Note that this isn't C, or even C++: it's pseudo-code. */
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( name ## _maynodp, nodetype* );
	( name ## _maynodep ) ( name ## _maynodp_nothing )()
		{ return( LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( name ## _maynodp, nodetype* ) ); }
	( name ## _maynodep ) ( name ## _maynodp_just )( nodetype *n )
		{ return( LIBANDRIA4_MONAD_MAYBE_BUILDJUST( name ## _maynodp, nodetype*, n ) ); }
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name ## _eitherrsz, unsigned, size_t );
	( name ## _eitherrsz ) ( name ## _eitherrsz_err )( unsigned err )
		{ return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name ## _maynodp, unsigned, err ) ); }
	( name ## _eitherrsz ) ( name ## _eitherrsz_size )( size_t sz )
		{ return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name ## _maynodp, size_t, sz ) ); }
	
	typedef struct ( name ## _bitup_errsznodp ) ( name ## _bitup_errsznodp );
	struct ( name ## _bitup_errsznodp )
	{
		( name ## _eitherrsz ) left;
		( name ## _maynodp ) right;
	};
	( name ## _bitup_errsznodp ) ( name ## _bitup_errsznodp_nodeless ) ( ( name ## _eitherrsz ) ersz )
		{ return( ( name ## _bitup_errsznodp ){ ersz, ( ( name ## _maynodp_nothing )() ) } ); }
	( name ## _bitup_errsznodp ) ( name ## _bitup_errsznodp_nodal ) ( ( name ## _eitherrsz ) ersz, nodetype *n )
		{ return( ( name ## _bitup_errsznodp ){ ersz, ( ( name ## _maynodp_just )( n ) ) } ); }
	( name ## _bitup_errsznodp ) ( name ## _bitup_errsznodp_nullreterr ) (  )
	{
		return
		(
			( name ## _bitup_errsznodp_nodeless )
			(
				( name ## _eitherrsz_err )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED )
			)
		);
	}
	
	#define LIBANDRIA4_BARETREES_HEIGHTBALANCE_SETdANDtrip( val ) \
		( d = (val), trip = 1 )
	( name ## _bitup_errsznodp ) ( node ## _heightbalance )( nodetype *n )
	{
		if( !n )
		{
			return
			(
				( name ## _bitup_errsznodp_nodeless )
					(
						( name ## _eitherrsz_size )( 1 )
					)
			);
		}
		
		size_t a, b;
		nodetype *c = 0, *d = 0;
		( name ## _bitup_errsznodp ) tmp;
		( name ## _bitup ) rot;
		( name ## _bitup_errsznodp ) (*LIBANDRIA4_OP_runable1)() =
			&( name ## _bitup_errsznodp_nullreterr );
		
		tmp = ( node ## _heightbalance )( ??? n->left ??? );
		??? a = tmp.left; ??? /* No longer legal, tmp.left is now a ( name ## _eitherrsz ){}! */
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right, LIBANDRIA4_OP_SETc, LIBANDRIA4_NULL_MACRO );
		
		tmp = ( node ## _heightbalance )( ??? n->left ??? );
		b = tmp.left; ??? /* No longer legal, tmp.left is now a ( name ## _eitherrsz ){}! */
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right, LIBANDRIA4_OP_SETd, LIBANDRIA4_NULL_MACRO );
		
			/* Keep looping until we either need to apply a rotation happening */
			/*  at this node (which will trigger a return from inside this */
			/*  loop), or this node and it's children are "perfectly" (within */
			/*  1) balanced. */
		while( a + 1 < b || a > b + 1 || c || d )
		{
			if( c )
			{
				/* The left sub-tree has been rotated: complete and loop. */
				
				n->left = c;
				c = 0;
				tmp = ( node ## _heightbalance )( ??? n->left ??? );
				a = tmp.left; ??? /* No longer legal, tmp.left is now a ( name ## _eitherrsz ){}! */
				LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right, LIBANDRIA4_OP_SETc, LIBANDRIA4_NULL_MACRO );
				
			} else if( d )
			{
				/* The right sub-tree has been rotated: complete and loop. */
				
				n->right = d;
				d = 0;
				tmp = ( node ## _heightbalance )( ??? n->right ??? );
				b = tmp.left; ??? /* No longer legal, tmp.left is now a ( name ## _eitherrsz ){}! */
				LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right, LIBANDRIA4_OP_SETd, LIBANDRIA4_NULL_MACRO );
				
			} else {
				
				/* Imbalanced in this node, rotate: */
				??? /* Is this correct? Couldn't the tallest sub-branch get transfered, keeping the height the same? */ ???
				
				libandria4_commonio_err d;
				int trip = 0;
				
				if( a + 1 < b )
				{
					/* Case: b is AT LEAST two larger than a. Which is illegal */
					/*  and must be rebalanced. */
					
					static ( name ## _bitup_errsznodp ) a = ??? ;
					
					c = 0;
					rot = ( name ## _rotateleft )( n );
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
						rot,
							LIBANDRIA4_BARETREES_HEIGHTBALANCE_SETdANDtrip,
							LIBANDRIA4_OP_SETc,
							LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa );
					
					if( trip )
					{
						return
						(
							( name ## _bitup_errsznodp_nodal )
								( ( name ## _eitherrsz_err )( d ), c )
						);
					}
					
						/* Always return the tallest height, minus 1 to */
						/*  compensate for the rotation. */
						/* Shouldn't we drop the "- 1", since we need to add THIS node's height? */
					return( ( name ## _bitup_errsznodp_nodal ) ( ( name ## _eitherrsz_size )( b - 1 ), c ) );
					
				} else {
					
					/* Case: a is AT LEAST two larger than b. Which is illegal */
					/*  and must be rebalanced. */
					
					static ( name ## _bitup_errsznodp ) b = ??? ;
					
					c = 0;
					rot = ( name ## _rotateright )( n );
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
						rot,
							LIBANDRIA4_BARETREES_HEIGHTBALANCE_SETdANDtrip,
							LIBANDRIA4_OP_SETc,
							LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEb );
					
					if( trip )
					{
						return
						(
							( name ## _bitup_errsznodp_nodal )
								( ( name ## _eitherrsz_err )( d ), c )
						);
					}
					
						/* Always return the tallest height, minus 1 to */
						/*  compensate for the rotation. */
						/* Shouldn't we drop the "- 1", since we need to add THIS node's height? */
					return( ( name ## _bitup_errsznodp_nodal ) ( ( name ## _eitherrsz_size )( a - 1 ), c ) );
				}
			}
		}
		
		return
		(
			( name ## _bitup_errsznodp_nodeless )
				(
						/* "1 +" to add the CURRENT node to the height. */
					( name ## _eitherrsz_size )( 1 + ( a > b ? a : b ) )
				)
		);
	}
	
	bitup< size_t, nodetype* > Hbal( nodetype *n )
	{
		if( !n )
		{
			return( bitup::left( 1 ) );
		}
		
		size_t a, b;
		nodetype *c = 0, *d = 0;
		
		{ a, c } = Hbal( n->left );
		{ b, d } = Hbal( n->right );
		
		while( a + 1 < b || a > b + 1 || c || d )
		{
			if( c )
			{
				n->left = c;
				c = 0;
				{ a, c } = Hbal( n->left );
				
			} else if( d )
			{
				n->right = d;
				d = 0;
				{ b, d } = Hbal( n->right );
				
			} else if( a + 1 < b )
			{
				return( bitup::both( b - 1, rotleft( n ) ) );
				
			} else {
				return( bitup::both( a - 1, rotleft( n ) ) );
				
			}
		}
		
		return( bitup::left( a > b ? a : b ) );
	}
	
#endif
/* End libandria4 basic bintrees baretrees.h */
