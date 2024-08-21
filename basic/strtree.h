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
	
		/* *last will contain the last value of base that was used, IF last is non-null. */
	#define LIBANDRIA4_STRTREE_BUILDINNERSEARCH( name,  pascalstrtype, elemtype ) \
		( name ## _eitherrptr ) ( name ## _innersearch )( \
			name **base, (elemtype) (*hfunc)( (elemtype) val ), int recurse, \
			size_t stroff, (pascalstrtype) *str,  name ***last ) \
			{ \
				if( !( base && str ) ) { return( ( name ## _eitherrptr_buildDomainErr )() ); } \
				if( !( *base ) ) { return( ( name ## _eitherrptr_buildIndrDomainErr )() ); } \
				if( str->len <= stroff ) { return( ( name ## _eitherrptr_buildAboveBoundsErr )() ); } \
				recurse = ( recurse > 0 ? 1 : 0 ); \
				(elemtype) hashval = hfunc( str->body[ stroff ] ); (name) *found = base[ hashval ]; \
				if( !found ) { return( ( name ## _eitherrptr_ptr )( ( (name) *)0 ) ); } \
				(pascalstrtype) *a = ( (pascalstrtype) *)0; { \
						/* We don't need the memfuncs{}. */ \
					( name ## _eitherrstrptr ) *fstr = ( name ## _fetchstrptr )( &( found->str ),  (lib4_memfuncs_t**)0 ); \
					unsigned e = 0; \
					LIBANDRIA4_MONAD_EITHER_BODYMATCH( fstr, LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); \
					while( !e && a && a->len > stroff && str->body[ stroff ] != a->body[ stroff ] ) { \
						if( found->peer ) { \
							found = found->peer; \
							fstr = ( name ## _fetchstrptr )( &( found->str ),  (lib4_memfuncs_t**)0 ); \
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
					/* At this point, *found is a node with the correct "first" character, and *a is it's pascal string. */ } \
				if( last ) { *last = base; } \
				size_t iter; { \
					iter = 1; size_t loop = 1; \
					while( loop && iter < found->excerptlen && stroff + iter < str->len && stroff + iter < a->len ) { \
						if( str->body[ stroff ] != a->body[ stroff ] ) { \
							loop = 0; } \
						else { iter += 1; } } \
					/* We now have the matching length of the strings. */ } \
				if( recurse && iter == found->excerptlen ) { \
					/* All the way through the found node, so move to the next child array. */ \
					return( \
						( name ## _innersearch )( \
							&( found->children ), hfunc, 1, \
							stroff + iter, str, \
							last ) ); } \
				return( ( name ## _eitherrptr_ptr )( found ) ); }
	
	
	#define LIBANDRIA4_STRTREE_DECLARE_nNODE( name,  nodenum, pascalstrtype, elemtype,  hashfunc,  memfuncs_ptr ) \
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_BAREDECL( ( name ## _tracker ),  pascalstrtype ); \
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
				/* peer is used in case of hash collisions to track "the other */ \
				/*  options". */ \
			(name) *children[ nodenum ], *peer; \
			size_t strstart, excerptlen; \
			( name ## _tracker ) str; }; \
		typedef struct (name ## _root) { \
			(name) *children[ nodenum ]; }; \
		libandria4_ptrresult ( name ## _generalalloc )( void* ign, size_t s ); \
		libandria4_ptrresult ( name ## _indirectrealloc )( void* ign,  void* mem, size_t s ); \
		libandria4_result ( name ## _indirectdealloc )( void* ign, void* mem ); \
		(elemtype) ( name ## _hashfunc )( (elemtype) val ); \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE_DEFINITION( ( name ## _bitup ), libandria4_commonio_err, (name)* ) \
			inline ( name ## _bitup ) ( name ## _bitup_buildError )( libandria4_commonio_err err ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( ( name ## _bitup ), \
					libandria4_commonio_err, nodetype*,  err ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildNodeptr )( (name) *ptr ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( ( name ## _bitup ), \
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
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name ## _eitherrsz, unsigned, err ) ); } \
			( name ## _eitherrptr ) ( name ## _eitherrptr_ptr )( (name) *ptr ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name ## _eitherrsz, (name)*, ptr ) ); } \
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
		inline hashfunc( name,  nodenum, pascalstrtype, elemtype,  memfuncs_ptr ); \
		inline LIBANDRIA4_STRTREE_BUILDFETCHSTRPTR( name,  pascalstrtype ); \
		( name ## _eitherrptr ) ( name ## _innersearch )( \
			name **base, (elemtype) (*hfunc)( (elemtype) val ), int recurse, \
			size_t stroff, (pascalstrtype) *str,  name ***last );
	
	#define LIBANDRIA4_STRTREE_DEFINE_nNODE( name,  nodenum, pascalstrtype, elemtype,  hashfunc,  memfuncs_ptr ) \
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_BAREIMPL( name,  pascalstrtype, \
			LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO ); \
		libandria4_ptrresult ( name ## _generalalloc )( void* ign, size_t s ) { \
			return( memfuncs_ptr->alloc( memfuncs_ptr, s ) ); } \
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
		hashfunc( name,  elemtype ); \
		LIBANDRIA4_STRTREE_BUILDFETCHSTRPTR( name,  pascalstrtype ); \
		LIBANDRIA4_STRTREE_BUILDINNERSEARCH( name,  pascalstrtype, elemtype );
	
	
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
	
	
	
	;
		struct (name) { \
				/* peer is used in case of hash collisions to track "the other */ \
				/*  options". */ \
			(name) *children[ nodenum ], *peer; \
			size_t strstart, excerptlen; \
			( name ## _tracker ) str; };
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name ## _eitherrstrptr, unsigned, (pascalstrtype)* );
	;
	
	
	
	LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYINIT( name, var, innerval, aux, memfuncs_ptr,  failinit, badalloc, badata )
	LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYSET( name, var, valptr, memfuncs_ptr,  failneglect, failattend, succneglect, succattend, ondead )
	LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYDEINIT( name, var, memfuncs_ptr,  failneglect, succneglect, ondead )
	
#endif
/* End libandria4 basic strtree.h */
