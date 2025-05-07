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

#ifndef LIBANDRIA4_BASIC_STRTREE_H
# define LIBANDRIA4_BASIC_STRTREE_H
	
	
	#include "simpleops.h"
	#include "stdmem.h"
	#include "pascalarray.h"
	#include "monads.h"
		/* For libandria4_ptrresult{} and libandria4_result{} . */
	#include "stdmonads.h"
		/* libandria4_commonio_err */
	#include "commonio.h"
	
	
	
	/* Note: rename to "prefix tree" or something similar, since I */
	/*  apparently got the name screwed up... We want this to be some */
	/*  radix-tree variant. */
	/* TODO: */
		/* Update _parentsearch() to match the _root{} changes. */
		/* Build a parent-function for _hashsearch() taking _root{}*. */
		/* Finish up the "TODO: Search" entries further down. */
		/* Add debugging hooks (need debugging system to be defined */
		/*  elsewhere). */
		/* Decide if the node-merging code needs to be seperated out. */
	
	/* TODO: Search variants to build, in order of construction/complexity: */
		/* Find all deep (all of the nodes, IN GENERAL) children. */
	/* Note that while predecessor / successor (using "alphabetic" order) */
	/*  searches are real things, they won't be included here due to being */
	/*  more of a specialized thing than prefix trees in general. */
		/* Predecessor: the largest string that's smaller than the given */
		/*  string, per lexographic ("alphabetic") order. */
		/* Successor: the smallest string that's larger than the given */
		/*  string. */
	
	
	
	#define LIBANDRIA4_STRTREE_PASSTHROUGHHASHFUNC( name,  ign1, ign2, elemtype,  ign3 ) \
		(elemtype) ( name ## _hashfunc )( (elemtype) val ) { \
			return( val ); }
	#define LIBANDRIA4_STRTREE_8NODEHASHFUNC( name,  ign1, ign2, elemtype,  ign3 ) \
		(elemtype) ( name ## _hashfunc )( (elemtype) val ) { \
			const (elemtype) anti7 = ~( (elemtype)7 ); \
			(elemtype) ret = val & 7; val = ( val & anti7 ) >> 3; \
			while( val ) { \
				ret += val & 7; val = ( val & anti7 ) >> 3; \
				while( ret > ret & 7 ) { \
					ret = ( ret & 7 ) + ( ( ret & anti7 ) >> 3 ); } } \
			return( ret ); }
	
	
	#define LIBANDRIA4_STRTREE_BUILDFETCHSTRPTR( name,  pascalstrtype ) \
		( name ## _eitherrstrptr ) ( name ## _fetchstrptr )( ( name ## _tracker ) *dblptr,  lib4_memfuncs_t **mf ) { \
			if( !dblptr ) { \
				return( ( name ## _eitherrstrptr_buildDomainErr )() ); } \
			(pascalstrtype) *a = ( (pascalstrtype) *)0; void *b = (void*)0; int c = 0; \
			LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY( *dblptr, \
						/* We need a pointer to the pstring, not the contents */ \
						/*  of the pstring's stub. */ \
					LIBANDRIA4_OP_SETaPTRb, LIBANDRIA4_OP_SETcTO1 ); \
			if( c ) { \
				return( ( name ## _eitherrstrptr_buildIndrDomainErr )() ); } \
			if( mf ) { *mf = b; } \
			return( ( name ## _eitherrstrptr_ptr )( a ) ); }
	#define LIBANDRIA4_STRTREE_BUILDBUILD( name,  nodenum,  memfuncs_ptr ) \
		( name ## _eitherrptr ) ( name ## _build ) (  ) { \
			void *b; unsigned e = 0; \
			libandria4_ptrresult alc = ( memfuncs_ptr )->alloc( (memfuncs_ptr)->data, sizeof( (name) ) ); { \
				libandria4_failure_uipresult e = { 0 }; \
				LIBANDRIA4_PTRRESULT_BODYMATCH( alc, LIBANDRIA4_OP_SETb, LIBANDRIA4_OP_SETe ); \
				if( !b ) { return( ( name ## _eitherrptr_ptr )( e.val ) ); } } \
			\
			/* Initialize the new node. */ \
			size_t len = 0; \
			(name) *res = ((name) *)b; \
				while( len < (nodenum) ) { \
					res->children[ len ] = ((name) *)0; len += 1; } \
				res->peer = ((name) *)0; \
				res->strstart = 0; res->excerptlen = 0; \
				( name ## _tracker_nullinit )( &( res->str ) ); \
			return( ( name ## _eitherrptr_ptr )( res ) ); }
	#define LIBANDRIA4_STRTREE_BUILDSPLIT( name,  nodenum, pascalstrtype, elemtype,  hashfuncptr,  memfuncs_ptr ) \
		int ( name ## _split ) ( (name) **base,  size_t newstart ) { \
			if( !base || !( *base ) || base->strstart >= newstart ) { \
				/* Require something TO split, and don't allow it's first byte to be the first byte of the new node. */ \
				return( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			\
			/* Get the string. */ \
			(pascalstrtype) *a = 0; unsigned e = 0; \
			( name ## _eitherrstrptr ) fstr = \
				( name ## _fetchstrptr )( &( n->str ),  (lib4_memfuncs_t**)0 ); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); \
			if( e ) { return( e ); } \
			\
			if( !a || a->len <= newstart || base->strstart + ( *base )->excerptlen <= newstart ) { \
				/* Require the start of the new node to be inside BOTH the byte string AND the current node. */ \
				return( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ); } \
			\
			void *b; ( name ## _eitherrptr ) mem = ( name ## _build )(); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( mem, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETb ); \
			if( !b ) { return( e ); } \
			(name) *res = ((name) *)b; \
				res->strstart = ( *base )->strstart; \
				res->excerptlen = newstart - res->strstart; \
					/* Inject the new node. */ \
				(elemtype) hash = ( name ## _hashfunc )( a->body[ newstart ] ); \
				res->children[ hash ] = ( *base ); \
				( *base ) = res; \
				/* Edit both to complete coverage. */ \
				( *base )->strstart = newstart; \
				( *base )->excerptlen -= res->excerptlen; \
				LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYSET( \
					name ## _tracker, res->str, ( *base )->str.counted, memfuncs_ptr, \
					LIBANDRIA4_NULL_MACRO, LIBANDRIA4_OP_SETeTO1, \
					LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO, \
					LIBANDRIA4_NULL_MACRO ); \
				if( e ) { return( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ); } \
			return( 0 ); }
		#define LIBANDRIA4_STRTREE_BUILDSHALLOWFREE_RETINDIRDOMAIN( ... ) \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN )
	#define LIBANDRIA4_STRTREE_BUILDSHALLOWFREE( name,  nodenum,  memfuncs_ptr ) \
		libandria4_commonio_eithgeneric ( name ## _shallowfree ) ( (name) **node ) { \
			if( !node || !( *node ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			/* Clear out the string. */ \
			( *node )->excerptlen = 0; ( *node )->strstart = 0; \
			LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYDEINIT( \
				name ## _tracker, ( *node )->str, memfuncs_ptr, \
				LIBANDRIA4_STRTREE_BUILDSHALLOWFREE_RETINDIRDOMAIN, \
					LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO ); \
			/* Delink the node. */ \
			size_t l = 0; while( l < (nodenum) ) { ( *node )->children[ l ] = 0;  ++l; } \
			( *node )->peer = 0; \
			libandria4_result res = (memfuncs_ptr)->dealloc( (memfuncs_ptr)->data, (void*)*node ); \
				libandria4_success_result a; libandria4_failure_result e; \
				LIBANDRIA4_RESULT_BODYMATCH( res, LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETe ); \
				if( e.val ) { LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( e.val ); } \
			/* Success. */ \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETSUCC( a.val ); }
	#define LIBANDRIA4_STRTREE_BUILDDATANODEDETECT( name,  pascalstrtype ) \
		int ( name ## _isdatanode ) ( (name) *base ) { \
			if( !base ) { return( -1 ); } \
			\
			/* Get the string. */ \
			(pascalstrtype) *a = 0; unsigned e = 0; \
			( name ## _eitherrstrptr ) fstr = \
				( name ## _fetchstrptr )( &( n->str ),  (lib4_memfuncs_t**)0 ); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); \
			if( e ) { return( -e ); } \
			\
			size_t off = base->strstart + base->excerptlen; \
			if( off > a->len ) { return( LIBANDRIA4_RESULT_FAILURE_OVERFLOW ); } \
			if( off == a->len ) { \
				return( LIBANDRIA4_RESULT_GENERICTRUE ); } \
			else { return( LIBANDRIA4_RESULT_GENERICFALSE ); } }
	
		/* Count all shallow (the non-null members of the nearest array) */
		/*  children. */
	#define LIBANDRIA4_STRTREE_BUILDSHALLOWCHILDCOUNT( name,  nodenum, pascalstrtype, elemtype ) \
		libandria4_commonio_eithgeneric ( name ## _shallowchildcount ) ( (name) *node ) { \
			if( !node ) { \
				return( LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			/* Early count. */ \
			size_t iter = 0, count = 0; \
			while( iter < (nodenum) ) { \
				if( node->children[ iter ] ) { ++count; } \
				++iter; } \
			return( LIBANDRIA4_COMMONIO_EITHGENERIC_SUCC( count ) ); }
		/* Find all shallow (the non-null members of the nearest array) */
		/*  children. */
	#define LIBANDRIA4_STRTREE_BUILDSHALLOWCHILDLIST( name,  nodenum, pascalstrtype, elemtype ) \
		( name ## _eitherrnamptrarr ) ( name ## _shallowchildlist ) ( (name) *node ) { \
			if( !node ) { \
				return( ( name ## _eitherrnamptrarr_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			/* Early count; */ size_t iter = 0, count = 0; \
			while( iter < (nodenum) ) { \
				if( node->children[ iter ] ) { ++count; } ++iter; } \
			if( !count ) { return( ( name ## _eitherrnamptrarr_ptr )( 0 ) ); } \
			/* Allocate. */ libandria4_failure_uipresult e = { 0 }; \
			(name ## _ptrarr_pascalarray) *a = ((name ## _ptrarr_pascalarray) *)0; \
			name##pascalarray_result mem = ( name ## _ptrarr_pascalarray_build )( count ); \
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( mem, LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETe ); \
			if( e.val != 0 ) { return( ( name ## _eitherrnamptrarr_err )( e.val ) ); } \
			/* Fill. */ size_t dest = 0; iter = 0; \
			while( dest < count && iter < (nodenum) ) { \
				if( node->children[ iter ] ) { \
					a->body[ dest ] = node->children[ iter ]; ++dest; } \
				++iter; } \
			while( dest < count ) { \
				a->body[ dest ] = 0; ++dest; } \
			/* Done. */ return( ( name ## _eitherrnamptrarr_ptr )( a ) ); }
	#define LIBANDRIA4_STRTREE_BUILDHASHSEARCH( name,  nodenum, pascalstrtype, elemtype ) \
		( name ## _eitherrptr ) ( name ## _hashsearch )( \
			name **base, (elemtype) (*hfunc)( (elemtype) val ), \
			size_t stroff, (pascalstrtype) *str,  name ***host ) \
			{ \
				if( !( base && str ) ) { return( ( name ## _eitherrptr_buildDomainErr )() ); } \
				if( !( *base ) ) { return( ( name ## _eitherrptr_buildIndrDomainErr )() ); } \
				if( str->len <= stroff ) { return( ( name ## _eitherrptr_buildAboveBoundsErr )() ); } \
				(elemtype) hashval = hfunc( str->body[ stroff ] ); if( hashval >= nodenum ) { \
					return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_OVERFLOW ) ); } \
				(name) **tmp = ((name) **)0; if( !host ) { host = &tmp; } **host = &( base[ hashval ] ); \
				if( !( **host ) ) { return( ( name ## _eitherrptr_ptr )( ( (name) *)0 ) ); } \
				(pascalstrtype) *a = ( (pascalstrtype) *)0; { \
						/* We don't need the memfuncs{}. */ \
					( name ## _eitherrstrptr ) *fstr = \
						( name ## _fetchstrptr )( &( ( **host )->str ),  (lib4_memfuncs_t**)0 ); \
					unsigned e = 0; \
					LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); \
					while( !e && a && a->len > stroff && str->body[ stroff ] != a->body[ stroff ] ) { \
						if( ( **host )->peer ) { \
							*host = &( ( **host )->peer ); \
							fstr = ( name ## _fetchstrptr )( &( ( **host )->str ),  (lib4_memfuncs_t**)0 ); \
							LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); } \
						else { /* No match. */ \
							return( ( name ## _eitherrptr_ptr )( ( (name) *)0 ) ); } } \
					if( a->len <= stroff ) { \
							/* This should NEVER happen, so if it ever DOES, then that's a corruption issue. */ \
						return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ) ); } \
					if( e ) { \
						return( ( name ## _eitherrptr_err )( e ) ); } \
					if( !a ) { \
						return( ( name ## _eitherrptr_buildNotInitedErr )( ) ); } \
					/* At this point, ***host is a node with the correct "first" character, and *a is it's pascal string. */ } \
				return( ( name ## _eitherrptr_ptr )( **host ) ); }
		/* *last will contain the last value of base that was used, IF last */
		/*  is non-null. */
		/*
			The returns will be as follows:
				Errors are errors, surprising noone.
				Null pointers == nothing found.
				Else true match found.
		*/
	#define LIBANDRIA4_STRTREE_BUILDINNERSEARCH( name,  nodenum, pascalstrtype, elemtype ) \
		( name ## _eitherrptr ) ( name ## _innersearch )( \
			name **base, (elemtype) (*hfunc)( (elemtype) val ), int recurse, \
			size_t stroff, (pascalstrtype) *str,  name ***last ) { \
				if( !( base && hfunc && str ) ) { return( ( name ## _eitherrptr_buildDomainErr )() ); } \
				if( !( *base ) ) { return( ( name ## _eitherrptr_buildIndrDomainErr )() ); } \
				if( str->len <= stroff ) { return( ( name ## _eitherrptr_buildAboveBoundsErr )() ); } \
				\
				recurse = ( recurse > 0 ? 1 : 0 ); if( last ) { *last = base; } \
				\
				/* Fetch the base's string. */ (pascalstrtype) *a = ( (pascalstrtype) *)0; unsigned e = 0; { \
						/* We don't need the memfuncs{}. */ \
					( name ## _eitherrstrptr ) *fstr = ( name ## _fetchstrptr )( &( ( *base )->str ),  (lib4_memfuncs_t**)0 ); \
					LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); \
					if( a->len <= stroff ) { \
							/* This should NEVER happen, so if it ever DOES, */ \
							/*  then that's a corruption issue. */ \
						return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ) ); } \
					if( e ) { return( ( name ## _eitherrptr_err )( e ) ); } \
					if( !a ) { return( ( name ## _eitherrptr_buildNotInitedErr )( ) ); } } \
				\
				/* String check. */ size_t iter = 0; { \
					while( iter < ( *base )->excerptlen && stroff + iter < str->len && stroff + iter < a->len ) { \
						if( str->body[ stroff + iter ] != a->body[ stroff + iter ] ) { \
							/* No match: divergent strings. */ return( ( name ## _eitherrptr_ptr )( 0 ) ); } \
						else { iter += 1; } } \
					if( iter != ( *base )->excerptlen ) { \
							/* Invalid result: the body string was shorter than the excerpt length. */ \
						return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_SIZEMISMATCH ) ); } \
					if( stroff + iter < a->len ) { \
						/* No match: short target. */ return( ( name ## _eitherrptr_ptr )( 0 ) ); } } \
				/* We've confirmed the relevant length. */ \
				\
				/* Hash stuff. */ \
				(elemtype) hashval = hfunc( str->body[ stroff ] ); \
				if( hashval >= (nodenum) ) { \
					return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_OVERFLOW ) ); } \
				(name) *found = base[ hashval ]; \
				if( !found ) { return( ( name ## _eitherrptr_ptr )( ( (name) *)0 ) ); } \
				\
				/* Peer check. */ { \
					while( !e && a && a->len > stroff && str->body[ stroff ] != a->body[ stroff ] ) { \
						if( found->peer ) { \
							found = found->peer; \
							fstr = ( name ## _fetchstrptr )( &( found->str ),  (lib4_memfuncs_t**)0 ); \
							LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); } \
						else { /* No match. */ \
							return( ( name ## _eitherrptr_ptr )( ( (name) *)0 ) ); } } \
					/* At this point, *found is a node with the correct */ \
					/*  "first" character, and *a is it's pascal string. */ } \
				\
				/* Return steering. */ \
				if( recurse && iter == found->excerptlen && iter + stroff < str->len ) { \
					/* All the way through the found node, so move to the */ \
					/*  next child array. */ \
					return( ( name ## _innersearch )( \
							&( found->children ), hfunc, 1, \
							stroff + iter, str, \
							last ) ); } \
				return( ( name ## _eitherrptr_ptr )( found ) ); }
				
	#define LIBANDRIA4_STRTREE_BUILDPARENTSEARCH( name,  pascalstrtype, elemtype ) \
		( name ## _eitherrptr ) ( name ## _parentsearch )( \
			name **base, (elemtype) (*hfunc)( (elemtype) val ), (pascalstrtype) *str ) \
		{ \
			if( !base ) { \
				return( ( name ## _eitherrptr_buildDomainErr )( ) ); } \
			(name) **last_arr = ( (name) **)0; \
			( name ## _eitherrptr ) res = ( name ## _innersearch )( base, hfunc, 1,  0, str,  &( last_arr ) ); \
			(name) *a = ( (name) *)0; \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( res, LIBANDRIA4_OP_RETres, LIBANDRIA4_OP_SETa ); \
			if( !a ) { \
				return( ( name ## _eitherrptr_buildNotInitedErr )( ) ); } \
			if( base == last_arr ) { \
				return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_TYPEMISMATCH ) ); } \
				/* Calculate the parent-node's address (usually will be */ \
				/*  (name*)last_arr, BUT...). */ \
			return( \
				( name ## _eitherrptr_ptr ) ( \
					LIBANDRIA4_STRUCTADDRfromELEMADDR( name, children,  last_arr ) ) ); }
	#define LIBANDRIA4_STRTREE_BUILDFULLSEARCH( name,  pascalstrtype, elemtype ) \
		( name ## _eitherrptr ) ( name ## _search )( \
			( name ## _root ) *root, (elemtype) (*hfunc)( (elemtype) val ), (pascalstrtype) *str ) \
		{ \
			if( !root || !( root->tree ) ) { \
				return( ( name ## _eitherrptr_buildDomainErr )( ) ); } \
			(name) **last_arr = ( (name) **)0; \
			( name ## _eitherrptr ) res = \
				( name ## _innersearch )( &( root->tree ), hfunc, 1,  0, str,  &( last_arr ) ); \
			(name) *a = ( (name) *)0; \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( res, LIBANDRIA4_OP_RETres, LIBANDRIA4_OP_SETa ); \
			if( !a ) { \
				return( ( name ## _eitherrptr_buildNotInitedErr )( ) ); } \
			return( \
				( name ## _eitherrptr_ptr ) ( a ) ); }
	#define LIBANDRIA4_STRTREE_BUILDVISIT( name,  nodenum ) \
		( name ## _bitup ) ( name ## _visit ) ( \
			( name ## _root ) *base,  void *data, void (*func)( void*,  (name)**, uintptr_t ) ) { \
				if( !base || !func ) { \
					return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_DOMAIN, *base ) ); } \
				return( ( name ## _innervisit )( &( base->tree ), 0,  data, func ) ); }
	#define LIBANDRIA4_STRTREE_BUILDINNERVISIT( name,  nodenum ) \
		( name ## _bitup ) ( name ## _innervisit ) ( \
			(name) **base, uintptr_t depth, \
			void *data, void (*func)( void*,  (name)**, uintptr_t ) ) { \
				if( !base || !func ) { \
					return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_DOMAIN, *base ) ); } \
				\
				( name ## _bitup ) res; size_t iter; \
				while( *base ) { func( data,  base, depth ); \
					\
					iter = 0; while( iter < (nodenum) ) { \
						if( ( *base )->children[ iter ] ) { \
							res = ( name ## _innervisit )( &( ( *base )->children[ iter ] ), depth + 1,  data, func ); } \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( res, \
							LIBANDRIA4_OP_RETres, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO ); \
						iter += 1; } \
					\
					base = &( ( *base )->peer ); } \
				\
				return( ( name ## _bitup_buildNone )() ); }
	#define LIBANDRIA4_STRTREE_BUILDNODECOUNT_VISITORFUNCS( name,  prefix ) \
		prefix void ( name ## _totalnodecount_visitor )( void *dat_,  (name) **node, uintptr_t depth ) { \
			long *data = (long*)dat_; ++( *data ); } \
		prefix void ( name ## _datanodecount_visitor )( void *dat_,  (name) **node, uintptr_t depth ) { \
			long *data = (long*)dat_; \
			if( ( name ## _isdatanode )( *node ) == LIBANDRIA4_RESULT_GENERICTRUE ) { \
				++( *data ); } } \
		prefix void ( name ## _heightcount_visitor )( void *dat_,  (name) **node, uintptr_t depth ) { \
			long *data = (long*)dat_; if( *data < depth ) { *data = depth; } }
	#define LIBANDRIA4_STRTREE_BUILDTOTALNODECOUNT( name ) \
		libandria4_commonio_eithlong ( name ## _totalnodecount )( ( name ## _root ) *base ) { \
			if( !base ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			\
			long ret = 0; libandria4_commonio_err e = 0, a = 1; \
			( name ## _bitup ) res = \
				( name ## _innervisit ) \
					( &( base->tree ), 0,  (void*)&ret, &( name ## _totalnodecount_visitor ) ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( res, \
					LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_OP_SETaTO1 ); \
				if( e ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( e ); } \
				if( a ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); } \
			LIBANDRIA4_COMMONIO_EITHLONG_RETLONG( ret ); }
	#define LIBANDRIA4_STRTREE_BUILDDATANODECOUNT( name ) \
		libandria4_commonio_eithlong ( name ## _datanodecount )( ( name ## _root ) *base ) { \
			if( !base ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			\
			long ret = 0; libandria4_commonio_err e = 0, a = 1; \
			( name ## _bitup ) res = \
				( name ## _innervisit ) \
					( &( base->tree ), 0,  (void*)&ret, &( name ## _datanodecount_visitor ) ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( res, \
					LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_OP_SETaTO1 ); \
				if( e ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( e ); } \
				if( a ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); } \
			LIBANDRIA4_COMMONIO_EITHLONG_RETLONG( ret ); }
	#define LIBANDRIA4_STRTREE_BUILDHEIGHTCOUNT( name ) \
		libandria4_commonio_eithlong ( name ## _heightcount )( ( name ## _root ) *base ) { \
			if( !base ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			\
			long ret = 0; libandria4_commonio_err e = 0, a = 1; \
			( name ## _bitup ) res = \
				( name ## _innervisit ) \
					( &( base->tree ), 1,  (void*)&ret, &( name ## _heightcount_visitor ) ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( res, \
					LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_OP_SETaTO1 ); \
				if( e ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( e ); } \
				if( a ) { LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); } \
			LIBANDRIA4_COMMONIO_EITHLONG_RETLONG( ret ); }
	
	#define LIBANDRIA4_STRTREE_BUILDINSERT( name,  pascalstrtype, elemtype,  hashfuncptr ) \
		( name ## _bitup ) ( name ## _insert )( ( name ## _root ) *base,  (name) *n ) { \
			if( !base || !n ) { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			\
			/* Get the string. */ \
			(pascalstrtype) *a = 0; unsigned e = 0; \
			( name ## _eitherrstrptr ) fstr = ( name ## _fetchstrptr )( &( n->str ),  (lib4_memfuncs_t**)0 ); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); \
			if( e ) { return( ( name ## _bitup_buildError )( e ) ); } \
			\
			return( ( name ## _innerinsert )( &( base->tree ),  n, a ) ); }
	#define LIBANDRIA4_STRTREE_BUILDINNERINSERT( name,  pascalstrtype, elemtype,  hashfuncptr ) \
		( name ## _bitup ) ( name ## _innerinsert )( (name) **base,  (name) *n, (pascalstrtype) *srch ) { \
			if( !base || !( *base ) || !n || !srch ) { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
				/* You know, normally 'a' would come first, but this DOES */ \
				/*  seem poetic... */ \
			(pascalstrtype) *b = 0; unsigned e = 0; \
			fstr = ( name ## _fetchstrptr )( &( ( *base )->str ),  (lib4_memfuncs_t**)0 ); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETb ); \
			if( e ) { return( ( name ## _bitup_buildBoth )( e, *base ) ); } \
			size_t strstart = ( *base )->strstart; \
			if( strstart => srch->len ) { \
				return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS, *base ) ); } \
			size_t strmatch = 0; \
			/* Get the match length, and insert accordingly. */ \
			while ( \
				strstart + strmatch < srch->len && \
				strstart + strmatch < b->len && \
				strmatch < ( *base )->excerptlen && \
				srch->body[ strstart + strmatch ] == b->body[ strstart + strmatch ] \
			) { strmatch += 1; } \
			if( strmatch < ( *base )->excerptlen ) { \
				/* Split *host so that our matched characters are still in */ \
				/*  *host, and it's children[] array moves into it's new */ \
				/*  SOLITARY child. */ \
				int res = ( name ## _split )( base,  strstart + strmatch ); \
				if( res != 0 ) { \
					return( ( name ## _bitup_buildBoth )( res, *base ) ); } \
				/* Now we fall-through to the NEXT if() block. */ } \
			/* Exact length match. */ \
			if( strmatch == ( *base )->excerptlen ) { \
					/* Is this the RIGHT array element? Should we be using */ \
					/*  strstart + host->excerptlen ? Find out! */ \
				(name) *a, **found; \
				( name ## _eitherrptr ) eep = ( name ## _hashsearch ) ( \
					base, &hashfuncptr, strstart + strmatch, srch,  &found ); \
				LIBANDRIA4_MONAD_EITHER_BODYMATCH( eep, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); \
				if( e ) { \
					return( ( name ## _bitup_buildBoth )( e, *base ) ); } \
					/* If a, then a FULL match was found for the first byte */ \
					/*  checked. */ \
				if( a ) { \
						/* + 1, because the hash-search did a seaerch over an */ \
						/*  extra byte, so we need to factor that in. */ \
					if( srch->len > strstart + strmatch + 1 ) { \
						return( ( name ## _innerinsert )( a,  n, srch ) ); } \
					else { \
						/* Error, node already exists. */ \
						return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_EXISTS, a ) ); } } \
				else { \
					/* Insert directly. */ \
					n->peer = *found; ( *found ) = n; \
					n->strstart = strstart + strmatch; \
					n->excerptlen = ( srch->len ) - n->strstart; \
					return( ( name ## _bitup_buildNodeptr )( n ) ); } } \
				/* Error, strmatch != base->excerptlen . */ \
				/*  The split-if() above should prevent this, so reaching */ \
				/*  this return GUARANTEES the existence of an error. */ \
			return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT, *base ) ); }
	
	#define LIBANDRIA4_STRTREE_BUILDDELETE( name,  pascalstrtype, elemtype ) \
		( name ## _bitup ) ( name ## _delete )( ( name ## _root ) *base,  (pascalstrtype) *srch ) { \
			if( !base || !srch ) { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			return( ( name ## _innerdelete )( &( base->tree ),  srch ) ); }
	#define LIBANDRIA4_STRTREE_BUILDINNERDELETE( name,  nodenum, pascalstrtype, elemtype ) \
		( name ## _bitup ) ( name ## _innerdelete )( (name) **base,  (pascalstrtype) *srch ) { \
			if( !base || !( *base ) || !n || !srch ) { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			\
				/* You know, normally 'a' would come first, but this DOES seem poetic... */ \
			(pascalstrtype) *b = 0; (name) *ret = ((name) *)0; unsigned e = 0; \
			\
			/* Get the string of our current active node. */ \
			fstr = ( name ## _fetchstrptr )( &( ( *base )->str ),  (lib4_memfuncs_t**)0 ); \
				LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETb ); \
				if( e ) { return( ( name ## _bitup_buildBoth )( e, *base ) ); } \
			size_t strstart = ( *base )->strstart; if( strstart => srch->len ) \
				{ return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS, *base ) ); } \
			\
			/* Get the match length. */ size_t strmatch = 0; \
			while ( strstart + strmatch < srch->len && strstart + strmatch < b->len && strmatch < ( *base )->excerptlen && \
				srch->body[ strstart + strmatch ] == b->body[ strstart + strmatch ] ) { strmatch += 1; } \
			if( strmatch < ( *base )->excerptlen ) { /* Incomplete match, the name just doesn't have a node. */ \
				return( ( name ## _bitup_buildNone )() ); }\
			\
			/* Get the number of direct children. */ libandria4_commonio_succ a; \
			libandria4_commonio_eithgeneric gen = ( name ## _shallowchildcount )( *base ); \
				LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH( gen,  LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETe ); \
				if( e ) { return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ) ); } \
			\
			/* Get the hash value for a child. */ (elemtype) hash = 0; (name) *d = ((name)*)0; \
			while( a && hash < (nodenum) && !d ) { d = ( *base )->children[ hash ]; ++hash; } \
			if( a && !d ) { /* There's a child, but we didn't find it? Well THAT'S bad! */ \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ) ); } \
			/* So that we don't need a lot of "hash - 1" all over the place. */ if( hash ) { --hash; } \
			\
			if( strstart + strmatch == srch->len ) { /* Found the node to delete. */ \
				ret = *base; \
				\
				if( a < 1 ) { /* No children, direct replacement, even if peer is null. */ \
					*base = ret->peer; \
					/* Reset deleted node. */ ret->excerptlen += ret->strstart; ret->strstart = 0; \
					/* Because perhaps there IS a peer. */ ret->peer = 0; \
					return( ( name ## _bitup_buildNodeptr )( ret ) ); } \
				else if( a == 1 && !( d->peer ) ) { /* One child, CHILD has no peer, direct replacement. */ \
					*base = d; \
					\
					if( *base ) { \
						/* Patch excerpt info. */ d->strstart = ret->strstart; \
						d->excerptlen += ret->excerptlen; d->peer = ret->peer; \
						\
						/* Reset deleted node. */ ret->excerptlen += ret->strstart; \
						ret->strstart = 0; ret->peer = 0; ret->children[ hash ] = 0; } \
					return( ( name ## _bitup_buildNodeptr )( ret ) ); } \
				\
				/* Multiple direct children, AND/OR a "d" peer. */ \
				\
				void *c; ( name ## _eitherrptr ) mem = ( name ## _build )(); \
					LIBANDRIA4_MONAD_EITHER_BODYMATCH( mem, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETc ); \
					if( !c ) { return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_MEMORYFULL ) ); } \
				\
				(name) *res = ((name) *)c; \
					/* Inject the new node. */ hash = 0; \
					while( hash < (nodenum) ) { res->children[ hash ] = ret->children[ hash ]; ++hash; } \
					res->peer = ret->peer; ( *base ) = res; \
					/* Link the string used by the first-found child. */ \
					res->strstart = ret->strstart; res->excerptlen = ret->excerptlen; \
					LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYSET( \
						name ## _tracker, res->str, d->str.counted, memfuncs_ptr, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_OP_SETeTO1, \
						LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO ); \
						if( e ) { return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_CORRUPTED, ret ) ); } \
				\
				/* Reset deleted node. */ hash = 0; \
				while( hash < (nodenum) ) { ret->children[ hash ] = 0; ++hash; } \
				ret->peer = 0; ret->excerptlen += ret->strstart; ret->strstart = 0; \
				\
				/* Deletion is done, just return the removed node. */ } \
			else { /* We have NOT reached the node */ \
				\
				/* Let's get our recursion target. */ (name) **dblptr; { \
					/* Let's not overwrite the base-string value we have. */ (pascalstrtype) *b = 0; \
					\
					dblptr = &( ( *base )->children[ hash ] ); \
						if( !( *dblptr ) ) { \
							return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS, ret ) ); } \
					\
					/* Get the string to check. */ \
					fstr = ( name ## _fetchstrptr )( &( ( *dblptr )->str ),  (lib4_memfuncs_t**)0 ); \
						LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETb ); \
						if( e ) { return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED, ret ) ); } \
						if( !b ) { return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED, ret ) ); } \
					while( b->body[ strstart + strmatch ] != srch->body[ strstart + strmatch ] ) { \
						dblptr = &( ( *dblptr )->peer ); \
							if( !( *dblptr ) ) { \
								return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS, ret ) ); } \
						\
							/* Get the next string to check. */ \
						fstr = ( name ## _fetchstrptr )( &( ( *dblptr )->str ),  (lib4_memfuncs_t**)0 ); \
							LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETb ); \
							if( e ) { return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED, ret ) ); } \
							if( !b ) { return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED, ret ) ); } } \
				} \
				\
				/* Recurse. */ \
				( name ## _bitup ) res = ( name ## _innerdelete )( dblptr,  srch ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( res, LIBANDRIA4_OP_RETres, LIBANDRIA4_OP_SETret, LIBANDRIA4_OP_SETeTO1 ); \
					if( e ) { /* There was NO return value, that's bad. */ \
						/* Note that if an explicit error is returned, then the entire */ \
						/*  bitup was already returned via the _RETres, so execution */ \
						/*  would never even reach here. */ \
						return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_BROKEN , ret ) ); } \
				\
				/* Recalculate the number of direct children, in case we dropped one. */ \
				gen = ( name ## _shallowchildcount )( *base ); \
					LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH( gen,  LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETe ); \
					if( e ) { return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN, ret ) ); } \
				\
				/* Try to replace this node with a peer or lone child, and if able then list it for freeing. */ \
				(name) *tmp = ((name)*)0; if ( a == 1 && \
						/* This is how we test to see if we're at a manually inserted */ \
						/* node instead of an automatically generated node. */ \
					b->len != ( *base )->strstart + ( *base )->excerptlen && \
					( ( !d && !( ( *base )->peer ) ) || !( d->peer ) ) ) \
				{ /* Replace this node with the solitary child node. */ \
					\
					/* Swap and restore consistency. */ tmp = *base; *base = d; \
					if( d ) { d->strstart = tmp->strstart; d->excerptlen += tmp->excerptlen; d->peer = tmp->peer; } } \
				else if( a == 0 && /* As above. */ b->len != ( *base )->strstart + ( *base )->excerptlen ) \
				{ /* Replace this node with it's peer node, even if that doesn't exist. */ \
					tmp = *base; *base = ( *base )->peer; } \
				\
				if( tmp ) { /* The current node was replaced, so free the original. */ \
					libandria4_commonio_eithgeneric freeres = ( name ## _shallowfree ) ( &tmp ); \
						libandria4_commonio_succ childcount = a; \
						LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH( freeres,  LIBANDRIA4_NULL_MACRO, LIBANDRIA4_OP_SETe ); \
						if( e ) { /* Range error, because we only have the ability to return a single node pointer. */ \
							return( ( name ## _bitup_buildBoth )( LIBANDRIA4_RESULT_FAILURE_RANGE, ret ) ); } } } \
			return( ( name ## _bitup_buildNodeptr )( ret ) ); }
	
		/* Use in headers. Use the *_DEFINE_* version DIRECTLY in .c files. */
	#define LIBANDRIA4_STRTREE_DECLARE_nNODE( name,  nodenum, pascalstrtype, elemtype,  hashfunc,  memfuncs_ptr ) \
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_BAREDECL( ( name ## _tracker ),  pascalstrtype ); \
		inline void ( name ## _tracker_nullinit ) ( ( name ## _tracker ) *trk ) { \
			LIBANDRIA4_MONAD_REFPOINTER_EXPRINIT_NULL( name ## _tracker, trk ); } \
		typedef (name##_tracker_counttype) (name##_strtype); \
		typedef struct (name) (name); \
			/* Unlike other tree builders I've defined, this one is meant */ \
			/*  to be wrappable instead of the user providing their own */ \
			/*  form: there really isn't much room for variation, but more */ \
			/*  importantly the insertion algorithm needs to know enough */ \
			/*  to build nodes itself to resolve string forks. I could */ \
			/*  have allowed a macro-set style facility to solve that, but */ \
			/*  for now I've decided no to do so. */ \
		struct (name) { \
				/* peer is used in case of hash collisions to track "the */ \
				/*  other options". */ \
			(name) *children[ nodenum ], *peer; \
			size_t strstart, excerptlen; \
			( name ## _tracker ) str; }; \
		typedef struct (name ## _root) { (name) *tree; }; \
		inline LIBANDRIA4_STRTREE_BUILDDATANODEDETECT( name,  pascalstrtype ); \
		libandria4_ptrresult ( name ## _generalalloc )( void* ign, size_t s ); \
		libandria4_ptrresult ( name ## _indirectrealloc )( void* ign,  void* mem, size_t s ); \
		libandria4_result ( name ## _indirectdealloc )( void* ign, void* mem ); \
		(elemtype) ( name ## _hashfunc )( (elemtype) val ); \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE_DEFINITION( ( name ## _bitup ), libandria4_commonio_err, (name)* ) \
			inline ( name ## _bitup ) ( name ## _bitup_buildNone )(  ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNNOTHING( ( name ## _bitup ), \
					libandria4_commonio_err, nodetype* ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildError )( libandria4_commonio_err err ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( ( name ## _bitup ), \
					libandria4_commonio_err, nodetype*,  err ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildNodeptr )( (name) *ptr ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURRIGHT( ( name ## _bitup ), \
					libandria4_commonio_err, (name)*,  ptr ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildBoth )( libandria4_commonio_err err, (name) *ptr ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( ( name ## _bitup ), \
					libandria4_commonio_err, (name)*,  err, ptr ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildIOErr )( ) { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_IOERROR ) ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildDomainErr )( ) { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildIndrDomainErr )( ) { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ) ); } \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name ## _eitherrptr, unsigned, (name)* ); \
			( name ## _eitherrptr ) ( name ## _eitherrptr_err )( unsigned err ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name ## _eitherrptr, unsigned, err ) ); } \
			( name ## _eitherrptr ) ( name ## _eitherrptr_ptr )( (name) *ptr ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name ## _eitherrptr, (name)*, ptr ) ); } \
			inline ( name ## _eitherrptr ) ( name ## _eitherrptr_buildDomainErr )( ) { \
				return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			inline ( name ## _eitherrptr ) ( name ## _eitherrptr_buildIndrDomainErr )( ) { \
				return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ) ); } \
			inline ( name ## _eitherrptr ) ( name ## _eitherrptr_buildAboveBoundsErr )( ) { \
				return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS ) ); } \
			inline ( name ## _eitherrptr ) ( name ## _eitherrptr_buildNotInitedErr )( ) { \
				return( ( name ## _eitherrptr_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name ## _eitherrstrptr, unsigned, (pascalstrtype)* ); \
			( name ## _eitherrstrptr ) ( name ## _eitherrstrptr_err )( unsigned err ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name ## _eitherrstrptr, unsigned, err ) ); } \
			( name ## _eitherrstrptr ) ( name ## _eitherrstrptr_ptr )( (pascalstrtype) *ptr ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name ## _eitherrstrptr, (pascalstrtype)*, ptr ) ); } \
			inline ( name ## _eitherrstrptr ) ( name ## _eitherrstrptr_buildDomainErr )( ) { \
				return( ( name ## _eitherrstrptr_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			inline ( name ## _eitherrstrptr ) ( name ## _eitherrstrptr_buildIndrDomainErr )( ) { \
				return( ( name ## _eitherrstrptr_err )( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ) ); } \
		LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( name ## _ptrarr_, (name)* ); \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name ## _eitherrnamptrarr, unsigned, (name ## _ptrarr_pascalarray)* ); \
			( name ## _eitherrnamptrarr ) ( name ## _eitherrnamptrarr_err )( unsigned err ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name ## _eitherrnamptrarr, unsigned, err ) ); } \
			( name ## _eitherrnamptrarr ) ( name ## _eitherrnamptrarr_ptr )( (name ## _ptrarr_pascalarray) *ptr ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name ## _eitherrnamptrarr, (name ## _ptrarr_pascalarray)*, ptr ) ); } \
		inline hashfunc( name,  nodenum, pascalstrtype, elemtype,  memfuncs_ptr ); \
		inline LIBANDRIA4_STRTREE_BUILDFETCHSTRPTR( name,  pascalstrtype ); \
		inline LIBANDRIA4_STRTREE_BUILDBUILD( name,  nodenum,  memfuncs_ptr ); \
		LIBANDRIA4_STRTREE_BUILDSPLIT( name,  nodenum, pascalstrtype, elemtype,  hashfuncptr,  memfuncs_ptr ); \
		inline LIBANDRIA4_STRTREE_BUILDSHALLOWFREE( name,  nodenum,  memfuncs_ptr ); \
		inline LIBANDRIA4_STRTREE_BUILDSHALLOWCHILDCOUNT( name,  nodenum, pascalstrtype, elemtype ); \
		inline LIBANDRIA4_STRTREE_BUILDSHALLOWCHILDLIST( name,  nodenum, pascalstrtype, elemtype ); \
		inline LIBANDRIA4_STRTREE_BUILDHASHSEARCH( name,  nodenum, pascalstrtype, elemtype ); \
		( name ## _eitherrptr ) ( name ## _innersearch )( \
			name **base, (elemtype) (*hfunc)( (elemtype) val ), int recurse, \
			size_t stroff, (pascalstrtype) *str,  name ***last ); \
		inline LIBANDRIA4_STRTREE_BUILDPARENTSEARCH( name,  pascalstrtype, elemtype ); \
		inline LIBANDRIA4_STRTREE_BUILDFULLSEARCH( name,  pascalstrtype, elemtype ); \
		int ( name ## _split )( (name) **base,  size_t newstart ); \
		( name ## _bitup ) ( name ## _innerinsert )( (name) **base,  (name) *n, (pascalstrtype) *srch ); \
		( name ## _bitup ) ( name ## _innerdelete )( (name) **base,  (pascalstrtype) *srch ); \
		inline LIBANDRIA4_STRTREE_BUILDINSERT( name,  pascalstrtype, elemtype,  hashfuncptr ); \
		inline LIBANDRIA4_STRTREE_BUILDDELETE( name,  pascalstrtype, elemtype ); \
		( name ## _bitup ) ( name ## _innerinsert )( (name) **base,  (name) *n, (pascalstrtype) *srch ); \
		inline LIBANDRIA4_STRTREE_BUILDVISIT( name,  nodenum ); \
		inline LIBANDRIA4_STRTREE_BUILDTOTALNODECOUNT( name ); \
		inline LIBANDRIA4_STRTREE_BUILDDATANODECOUNT( name ); \
		inline LIBANDRIA4_STRTREE_BUILDHEIGHTCOUNT( name );
	
		/* Use in a .c file, not in headers. */
	#define LIBANDRIA4_STRTREE_DEFINE_nNODE( name,  nodenum, pascalstrtype, elemtype,  hashfunc,  memfuncs_ptr ) \
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_BAREIMPL( name,  pascalstrtype, \
			LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO ); \
		void ( name ## _tracker_nullinit ) ( ( name ## _tracker ) *trk ) { \
			LIBANDRIA4_MONAD_REFPOINTER_EXPRINIT_NULL( name ## _tracker, trk ); } \
		LIBANDRIA4_STRTREE_BUILDDATANODEDETECT( name,  pascalstrtype ); \
		libandria4_ptrresult ( name ## _generalalloc )( void* ign, size_t s ) { \
			return( memfuncs_ptr->alloc( (memfuncs_ptr)->data, s ) ); } \
		libandria4_ptrresult ( name ## _indirectrealloc )( void* ign,  void* mem, size_t s ) { \
			if( !mem ) { \
				LIBANDRIA4_PTRRESULT_RETURNFAILURE( \
					(libandria4_failure_uipresult){ \
						LIBANDRIA4_RESULT_FAILURE_DOMAIN } ); } \
			(name##_strtype) *n = ((name##_strtype) *)mem; \
			lib4_memfuncs_t *mf = (lib4_memfuncs_t*)( n->auxiliary ); \
			if( !mf || !( mf->realloc ) ) { \
				LIBANDRIA4_PTRRESULT_RETURNFAILURE( \
					(libandria4_failure_uipresult){ \
						LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED } ); } \
			return( mf->realloc( mf, mem, s ) ); } \
		libandria4_result ( name ## _indirectdealloc )( void* ign, void* mem ) { \
			if( !mem ) { \
				LIBANDRIA4_RESULT_RETURNFAILURE( (libandria4_failure_result){ \
					LIBANDRIA4_RESULT_FAILURE_DOMAIN } ); } \
			(name##_strtype) *n = ((name##_strtype) *)mem; \
			lib4_memfuncs_t *mf = (lib4_memfuncs_t*)( n->auxiliary ); \
			if( !mf || !( mf->dealloc ) ) { \
				LIBANDRIA4_RESULT_RETURNFAILURE( (libandria4_failure_result){ \
					LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED } ); } \
			return( mf->dealloc( mf, mem ) ); } \
		LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDEFINE( name ## _ptrarr_, (name)*, memfuncs_ptr ); \
		hashfunc( name,  elemtype ); \
		LIBANDRIA4_STRTREE_BUILDFETCHSTRPTR( name,  pascalstrtype ); \
		LIBANDRIA4_STRTREE_BUILDBUILD( name,  nodenum,  memfuncs_ptr ); \
		LIBANDRIA4_STRTREE_BUILDSPLIT( name,  nodenum, pascalstrtype, elemtype,  hashfuncptr,  memfuncs_ptr ); \
		LIBANDRIA4_STRTREE_BUILDSHALLOWFREE( name,  nodenum,  memfuncs_ptr ); \
		LIBANDRIA4_STRTREE_BUILDSHALLOWCHILDCOUNT( name,  nodenum, pascalstrtype, elemtype ); \
		LIBANDRIA4_STRTREE_BUILDSHALLOWCHILDLIST( name,  nodenum, pascalstrtype, elemtype ); \
		LIBANDRIA4_STRTREE_BUILDHASHSEARCH( name,  nodenum, pascalstrtype, elemtype ); \
		LIBANDRIA4_STRTREE_BUILDINNERSEARCH( name,  pascalstrtype, elemtype ); \
		LIBANDRIA4_STRTREE_BUILDPARENTSEARCH( name,  pascalstrtype, elemtype ); \
		LIBANDRIA4_STRTREE_BUILDFULLSEARCH( name,  pascalstrtype, elemtype ); \
		LIBANDRIA4_STRTREE_BUILDSPLIT( name,  nodenum, pascalstrtype, elemtype,  hashfuncptr,  memfuncs_ptr ); \
		LIBANDRIA4_STRTREE_BUILDINNERINSERT( name,  pascalstrtype, elemtype,  hashfuncptr ); \
		LIBANDRIA4_STRTREE_BUILDINSERT( name,  pascalstrtype, elemtype,  hashfuncptr ); \
		LIBANDRIA4_STRTREE_BUILDINNERDELETE( name,  nodenum, pascalstrtype, elemtype ); \
		LIBANDRIA4_STRTREE_BUILDDELETE( name,  pascalstrtype, elemtype ); \
		LIBANDRIA4_STRTREE_BUILDINNERVISIT( name,  nodenum ); \
		LIBANDRIA4_STRTREE_BUILDVISIT( name,  nodenum ); \
		LIBANDRIA4_STRTREE_BUILDNODECOUNT_VISITORFUNCS( name,  ); \
		LIBANDRIA4_STRTREE_BUILDTOTALNODECOUNT( name ); \
		LIBANDRIA4_STRTREE_BUILDDATANODECOUNT( name ); \
		LIBANDRIA4_STRTREE_BUILDHEIGHTCOUNT( name );
	
	
	#define LIBANDRIA4_STRTREE_DECLARE_8NODE( name,  pascalstrtype, elemtype,  memfuncs_ptr ) \
		LIBANDRIA4_STRTREE_DECLARE_nNODE( name, \
			8, pascalstrtype, elemtype, \
			LIBANDRIA4_STRTREE_8NODEHASHFUNC, \
			memfuncs_ptr )
	#define LIBANDRIA4_STRTREE_DEFINE_8NODE( name,  pascalstrtype, elemtype,  memfuncs_ptr ) \
		LIBANDRIA4_STRTREE_DEFINE_nNODE( name, \
			8, pascalstrtype, elemtype, \
			LIBANDRIA4_STRTREE_8NODEHASHFUNC, \
			memfuncs_ptr )
	
	/* Note that YOU MUST know the needed number of node pointers per node */
	/*  for this to work reliably. */
	#define LIBANDRIA4_STRTREE_DECLARE_PASSTHROUGH( name,  nodenum, pascalstrtype, elemtype,  memfuncs_ptr ) \
		LIBANDRIA4_STRTREE_DECLARE_nNODE( name, \
			nodenum, pascalstrtype, elemtype, \
			LIBANDRIA4_STRTREE_PASSTHROUGHHASHFUNC, \
			memfuncs_ptr )
	#define LIBANDRIA4_STRTREE_DEFINE_PASSTHROUGH( name,  nodenum, pascalstrtype, elemtype,  memfuncs_ptr ) \
		LIBANDRIA4_STRTREE_DEFINE_nNODE( name, \
			nodenum, pascalstrtype, elemtype, \
			LIBANDRIA4_STRTREE_PASSTHROUGHHASHFUNC, \
			memfuncs_ptr )
	
	
	
	
	
	
#endif
/* End libandria4 basic strtree.h */
