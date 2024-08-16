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
	
	
	
	/* Existing systems: */
		/* Batch-balanced binary balanced-height tree. */
		/* Replace LIBANDRIA4_BARETREES_heightbalance_nullrot with */
		/*  LIBANDRIA4_BINTREES_countnodes_nullrot. */
	
	
	
	/*
		Need to build for the basic tree:
			Add node
			Delete node
			Get height
	*/
	/* Need to build a splay tree system. */
	
	
	
	/* I don't know if this is the best algorithm, and perhaps it doesn't */
	/*  even work RIGHT, but it's my current version. Partially because the */
	/*  results I've found when looking up the algorithm seem to be AVL */
	/*  trees instead of vanilla binary trees. */
		#define LIBANDRIA4_BARETREES_HEIGHTBALANCE_PATCHleftTOcANDRETtmp( ... ) \
			c ? ( n->left = c ) : c; return( tmp );
		#define LIBANDRIA4_BARETREES_HEIGHTBALANCE_PATCHrightTOdANDRETtmp( ... ) \
			d ? ( n->right = d ) : d; return( tmp );
		#define LIBANDRIA4_BARETREES_HEIGHTBALANCE_SETdANDtrip( val ) \
			( d = (val), trip = 1 )
		#define LIBANDRIA4_BARETREES_heightbalance_nullrot( ... ) \
			return( ( name ## _bitup_errsznodp_nodal ) \
				( ( name ## _eitherrsz_err )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ), c ) );
	#define LIBANDRIA4_BARETREES_BUILDHBALANCE( name,  nodetype,  macroset ) \
		( name ## _bitup_errsznodp ) ( name ## _heightbalance_inner )( nodetype *n, int usedouble ) { \
			if( !n ) { \
				return ( ( name ## _bitup_errsznodp_nodeless ) ( ( name ## _eitherrsz_size )( 1 ) ) ); } \
			size_t a, b; \
			nodetype *c = 0, *d = 0, *oldc[ 2 ] = { 0, 0 }, *oldd[ 2 ] = { 0, 0 }; \
			( name ## _bitup_errsznodp ) tmp; ( name ## _bitup ) rot; int test; \
			usedouble = ( usedouble > 0 ? 1 : 0 ); \
			tmp = ( name ## _heightbalance_inner )( macroset ## _GETLEFT( n ), 0 ); \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right, LIBANDRIA4_OP_SETc, LIBANDRIA4_NULL_MACRO ); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
				tmp.left, \
					LIBANDRIA4_BARETREES_HEIGHTBALANCE_PATCHleftTOcANDRETtmp, \
					LIBANDRIA4_OP_SETa ); \
			tmp = ( name ## _heightbalance_inner )( macroset ## _GETRIGHT( n ), 0 ); \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right, LIBANDRIA4_OP_SETd, LIBANDRIA4_NULL_MACRO ); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
				tmp.left, \
					LIBANDRIA4_BARETREES_HEIGHTBALANCE_PATCHrightTOdANDRETtmp, \
					LIBANDRIA4_OP_SETb ); \
				/* Keep looping until we either need to apply a rotation happening */ \
				/*  at this node (which will trigger a return from inside this */ \
				/*  loop), or this node and it's children are "perfectly" (within */ \
				/*  1) balanced. */ \
			while( a + 1 < b || a > b + 1 || c || d ) { \
				if( c ) { \
					/* The left sub-tree has been rotated: complete and loop. */ \
					test = ( oldc[ 1 ] == c ) ? 1 : 0; \
					oldc[ 1 ] = oldc[ 0 ]; oldc[ 0 ] = c; n->left = c; c = 0; \
					tmp = ( name ## _heightbalance_inner )( macroset ## _GETLEFT( n ), test ); \
					LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right, LIBANDRIA4_OP_SETc, LIBANDRIA4_NULL_MACRO ); \
					LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
						tmp.left, \
							LIBANDRIA4_BARETREES_HEIGHTBALANCE_PATCHleftTOcANDRETtmp, \
							LIBANDRIA4_OP_SETa ); } \
				else if( d ) { \
					/* The right sub-tree has been rotated: complete and loop. */ \
					oldc[ 1 ] = 0; oldc[ 0 ] = 0; \
					test = ( oldd[ 1 ] == d ) ? 1 : 0; \
					oldd[ 1 ] = oldd[ 0 ]; oldd[ 0 ] = d; n->right = d; d = 0; \
					tmp = ( name ## _heightbalance_inner )( macroset ## _GETRIGHT( n ), test ); \
					LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right, LIBANDRIA4_OP_SETd, LIBANDRIA4_NULL_MACRO ); \
					LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
						tmp.left, \
							LIBANDRIA4_BARETREES_HEIGHTBALANCE_PATCHrightTOdANDRETtmp, \
							LIBANDRIA4_OP_SETb ); } \
				else { \
					/* Imbalanced in this node, rotate: */ \
					libandria4_commonio_err d; \
					oldc[ 1 ] = 0; oldc[ 0 ] = 0; oldd[ 1 ] = 0; oldd[ 0 ] = 0; \
					int trip = 0; c = 0; \
					if( a + 1 < b ) { \
						/* Case: b is AT LEAST two larger than a. Which is illegal */ \
						/*  and must be rebalanced. */ \
						a = b; \
						if( usedouble ) { \
							rot = ( name ## _doublerotateleft )( n ); } \
						else { \
							rot = ( name ## _rotateleft )( n ); } } \
					else { \
						/* Case: a is AT LEAST two larger than b. Which is illegal */ \
						/*  and must be rebalanced. */ \
						if( usedouble ) { \
							rot = ( name ## _doublerotateright )( n ); } \
						else { \
							rot = ( name ## _rotateright )( n ); } } \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						rot, \
							LIBANDRIA4_BARETREES_HEIGHTBALANCE_SETdANDtrip, \
							LIBANDRIA4_OP_SETc, \
								/* Bug! We'll leak a node or more because of the rotation! */ \
							??? LIBANDRIA4_BARETREES_heightbalance_nullrot ??? ); \
					if( trip ) { \
						return( \
							( name ## _bitup_errsznodp_nodal ) ( ( name ## _eitherrsz_err )( d ), c ) ); } \
					/* Note that the height doesn't matter, because the node being */ \
					/*  returned will force another invocation of _heightbalance() */ \
					/*  on this branch, thereby overwriting the height returned */ \
					/*  here. */ \
					return( ( name ## _bitup_errsznodp_nodal ) ( ( name ## _eitherrsz_size )( a ), c ) ); } } \
			return( \
				( name ## _bitup_errsznodp_nodeless )(  \
						/* "1 +" to add the CURRENT node to the height. */ \
					( name ## _eitherrsz_size )( 1 + ( a > b ? a : b ) ) ) ); } \
		( name ## _bitup_errsznodp ) ( name ## _heightbalance )( nodetype **n ) { \
			if( !n ) { \
				return( ( name ## _bitup_errsznodp_nodeless )( \
					( name ## _eitherrsz_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) ); } \
			if( !( *n ) ) { \
				return ( \
					( name ## _bitup_errsznodp_nodeless )( ( name ## _eitherrsz_size )( 1 ) ) ); } \
			size_t a; int test; \
			nodetype *c = 0, *oldc[ 2 ] = { 0, 0 }; ( name ## _bitup_errsznodp ) tmp; \
			tmp = ( name ## _heightbalance_inner )( *n, 0 ); \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right,   LIBANDRIA4_OP_SETc, LIBANDRIA4_NULL_MACRO ); \
			if( c ) { *n = c; } \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp.left,   LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); \
			while( c ) { \
				test = ( oldc[ 1 ] == c ) ? 1 : 0; \
				oldc[ 1 ] = oldc[ 0 ]; oldc[ 0 ] = c; n->left = c; c = 0; \
				tmp = ( name ## _heightbalance_inner )( *n, test ); \
				LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( tmp.right,  LIBANDRIA4_OP_SETc, LIBANDRIA4_NULL_MACRO ); \
				if( c ) { *n = c; } \
				LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp.left,   LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); } \
			return ( \
				( name ## _bitup_errsznodp_nodeless ) ( \
							/* "1 +" to add the CURRENT node to the height. */ \
						( name ## _eitherrsz_size )( a ) ) ) ); }
	
	#define LIBANDRIA4_BARETREES_insert_RETURNlogicfault( ... ) \
		return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT, old ) );
	#define LIBANDRIA4_BARETREES_BUILDINSERT( name,  nodetype, keytype,  macroset ) \
		( name ## _bitup ) ( name ## _insert )( (nodetype) *base,  (keytype) keyval, (nodetype) *addition ) { \
			if( !addition ) { /* Fast exit: no node to add. */ \
				return( ( name ## _bitup_buildDomainErr )() ); } \
			if( !base ) { /* Fast exit: no tree to climb. */ \
				return( ( name ## _bitup_buildNodeptr )( addition ) ); \
			(nodetype) *old = 0, *a = 0; \
			( name ## _bitup ) tmp = name ## _searchk( base, keyval, &old ); \
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( tmp, \
					LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa, LIBANDRIA4_NULL_MACRO ); \
			if( a ) { /* Key found, so can't insert node. */ \
				return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_EXISTS, a ) ); } \
			if( !old ) { /* We REQUIRE old to be set. */ old = base; } \
			int test = macroset ## _COMPAREk( old, libandria4_key ); \
			switch( test ) { \
				case -1: tmp = macroset ## _GETLEFT( old ); break; \
				case 0: LIBANDRIA4_BARETREES_insert_RETURNlogicfault( ignorearg ); \
				case 1: tmp = macroset ## _GETRIGHT( old ); break; \
				default: return( \
					( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED, old ) ); } a = 0; \
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
				tmp, \
					LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa, \
					LIBANDRIA4_BARETREES_insert_RETURNlogicfault ); \
			if( a ) { /* This needs to be a null, so we can store "addition" in it without losing data. */ \
				LIBANDRIA4_BARETREES_insert_RETURNlogicfault( ignorearg ); } \
			switch( test ) { \
				case -1: tmp = macroset ## _SETLEFT( old,  addition ); break; \
				case 1: tmp = macroset ## _SETRIGHT( old,  addition ); break; } \
			return( tmp ); }
	
	#define LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( var, onnode ) \
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
				( var ),  LIBANDRIA4_OP_SETeTO2, ( onnode ), LIBANDRIA4_OP_SETeTO1 );
	#define LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( cond, macroset, transact, retval ) \
		if( cond ) { macroset ## _CANCELTRANSACTION( transact ); return( retval ); }
	#define LIBANDRIA4_BARETREES_BUILDDELETE( name,  nodetype, keytype,  macroset ) \
		( name ## _bitup ) ( name ## delete )( nodetype **base, keytype key ) { \
			if( !base ) { \
				/* No tree, so no deletions can be made. */ \
				return( ( name ## _bitup_buildDomainErr )() ); } \
			if( !( *base ) ) { \
				/* No tree, so no deletions can be made. */ \
				return( ( name ## _bitup_buildIndrDomainErr )() ); } \
			(nodetype) *old = 0, *a = 0, *b = 0, *c = 0; \
			( name ## _bitup ) tmp = name ## _searchk( base, keyval, &old ); \
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
				tmp, \
					LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa, LIBANDRIA4_NULL_MACRO ); \
			if( !a ) { \
				/* There's no match, so just exit. */ \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			int test = macroset ## _COMPAREk( old, key ); \
			if( test < -1 || test > 1 ) { \
				/* Filter illegal comparison results. */ \
				return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED, old ) ); } \
			else if( test == 0 ) { \
				/* Filter paternal immitation. */ \
				LIBANDRIA4_BARETREES_insert_RETURNlogicfault( ignorearg ); } \
			tmp = macroset ## _GETLEFT( a ); \
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
				tmp, \
					LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETb, \
					LIBANDRIA4_BARETREES_insert_RETURNlogicfault ); \
			tmp = macroset ## _GETRIGHT( a ); \
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
				tmp, \
					LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETc, \
					LIBANDRIA4_BARETREES_insert_RETURNlogicfault ); \
			libandria4_commonio_err e = 0; \
			( macroset ## _TRANSTRACKPTRTYPE ) transact; \
			macroset ## _STARTTRANSACTION( transact ); \
			if( !b ) { \
				/* Only right sub-tree exists, swap target out for it's sole */ \
				/*  child. */ \
				switch( test ) { \
					case -1: tmp = macroset ## _SETLEFT( old,  c ); break; \
					case 1: tmp = macroset ## _SETRIGHT( old,  c ); break; } \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
					/* The rotation code only actually returns on direct */ \
					/*  error... do we WANT to return on null? */ \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
				tmp = macroset ## _SETRIGHT( a,  b ); } \
			else if( !c ) { \
				/* Only left sub-tree exists, swap target out for it's sole */ \
				/*  child. */ \
				switch( test ) { \
					case -1: tmp = macroset ## _SETLEFT( old,  b ); break; \
					case 1: tmp = macroset ## _SETRIGHT( old,  b ); break; } \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
				tmp = macroset ## _SETLEFT( a,  c ); } \
			else { \
				/* Time for the complicated part: the target node has both */ \
				/*  sub-trees set, so search for an "inner-most" child to swap */ \
				/*  positions with. We'll be using the left sub-tree, so b. */ \
				\
				(nodetype) *d = b, *oldd[ 2 ] = { 0, 0 }; \
				oldd[ 1 ] = oldd[ 0 ]; oldd[ 0 ] = d; \
				tmp = macroset ## _GETRIGHT( d ); \
					LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_OP_SETd ); \
					LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
				if( !d ) { \
					/* There is NO right grandchild on the left sub-tree. "b" */ \
					/*  and "c" start as siblings, but "b" becomes "c"'s parent. */ \
					\
						/* Copy "c" to the right-child spot on "b" (which is */ \
						/*  null). */ \
					tmp = macroset ## _SETRIGHT( b,  c ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
						/* Patch the node to be removed out with "b". */ \
					tmp = macroset ## _SETLEFT( old,  d ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
					/* Clear the child pointers of the node to be removed. */ \
					tmp = macroset ## _SETLEFT( a,  0 ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
					tmp = macroset ## _SETRIGHT( a,  0 ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); } \
				else { \
					/* Fully or partially disconnected areas: no more than "b" */ \
					/*  is linked to both the node to be deleted, and the */ \
					/*  swap-node. */ \
					while( d ) { \
						oldd[ 1 ] = oldd[ 0 ]; oldd[ 0 ] = d; \
						tmp = macroset ## _GETRIGHT( d ); \
							LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_OP_SETd ); \
							LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); } \
					/* Rewind. */ d = oldd[ 0 ]; oldd[ 0 ] = oldd[ 1 ]; \
						/* Copy the original right sub-tree to the equivalent */ \
						/*  spot on the swap-node (which is null). */ \
					tmp = macroset ## _SETRIGHT( d,  c ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
						/* Move the left sub-tree of the swap-node into the */ \
						/*  swap-node's now-previous location. */ \
					tmp = macroset ## _GETLEFT( d ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_OP_SETc ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
					tmp = macroset ## _SETRIGHT( oldd[ 0 ],  c ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
						/* Copy the original left sub-tree to the equivalent */ \
						/*  spot on the swap-node (which isn't null, but is now */ \
						/*  at the swap-node's location). */ \
					tmp = macroset ## _SETLEFT( d,  b ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
						/* Patch the node to be removed out with the swap-node. */ \
					tmp = macroset ## _SETLEFT( old,  d ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_cancelNret( e, macroset, transact, tmp ); \
					/* Clear the child pointers of the node to be removed. */ \
					tmp = macroset ## _SETLEFT( a,  0 ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); \
					tmp = macroset ## _SETRIGHT( a,  0 ); \
						LIBANDRIA4_BARETREES_BUILDDELETE_errmark_bodymatch( tmp, LIBANDRIA4_NULL_MACRO ); } \
				/* This space intentionally left blank. */ } \
			macroset ## _COMPLETETRANSACTION( transact ); \
			if( e ) { \
				e = LIBANDRIA4_RESULT_FAILURE_BROKEN; \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					tmp,  LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO ); \
				return( ( name ## _bitup_buildBoth )( e, a ) ); } \
			return( ( name ## _bitup_buildNodeptr )( a ) ); }
	
	#define LIBANDRIA4_BARETREES_BASICSBUILDER( name,  nodetype, keytype,  macroset ) \
		LIBANDRIA4_BINTREES_BASICSBUILDER( name,  nodetype, keytype,  macroset ) \
		LIBANDRIA4_BARETREES_BUILDHBALANCE( name,  nodetype,  macroset ); \
		LIBANDRIA4_BARETREES_BUILDINSERT( name,  nodetype, keytype,  macroset ); \
		LIBANDRIA4_BARETREES_BUILDDELETE( name,  nodetype, keytype );
	
#endif
/* End libandria4 basic bintrees baretrees.h */
