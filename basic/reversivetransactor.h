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

#ifndef LIBANDRIA4_BASIC_REVERSIVETRANSACTOR_H
# define LIBANDRIA4_BASIC_REVERSIVETRANSACTOR_H
	
	#include "pascalarray.h"
	#include "nulls.h"
		/* For libandria4_result */
	#include "stdmonads.h"
	/* Probably missing 1+ headers. */
	
		/* A primitive transaction tracking system. Used specifically */
		/*  to UNDO actions that have been registered, instead of */
		/*  waiting for validation before applying them. It only accepts */
		/*  a single data type. */
	#define LIBANDRIA4_RECURSIVETRANSACTOR_DECLARE( head, nodetype ) \
		typedef struct ( head ## transactionelement ) ( head ## transactionelement ; \
		struct ( head ## transactionelement ) { nodetype **loc, *val; }; \
			/* BARE so the user can use their own allocator. */ \
		LIBANDRIA4_DEFINE_PASCALARRAY_BAREDECLARE( \
			head, ( head ## transactionelement ) ); \
		typedef struct ( head ## transactionset ) ( head ## transactionset ); \
		struct ( head ## transactionset ) { \
			( head ## pascalarray ) *arr; \
			size_t unusedlen; /* Hide old elems instead of deallocating. */ }; \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( \
			head##transactionset_result, \
			head##transactionset*, uintptr_t /* Error type */ ) \
		int ( head ## track ) ( libandria4_memfuncs_t *mf, \
			( head ## transactionset ) *set, ( head ## transactionelement ) elem ); \
		head##transactionset_result ( head ## build ) ( libandria4_memfuncs_t *mf ); \
		int ( head ## revert ) ( ( head ## transactionset ) *set ); \
		int ( head ## clear ) ( ( head ## transactionset ) *set ); \
		int ( head ## destroyarr ) \
			( libandria4_memfuncs_t *mf,  ( head ## transactionset ) *set ); \
		libandria4_result ( head ## destroyset ) \
			( libandria4_memfuncs_t *mf,  ( head ## transactionset ) *set )
	
		/* Builds an actual element. You should wrap this with something */
		/*  that has a shorter name and hardwires the first two arguments. */
	#define LIBANDRIA4_RECURSIVETRANSACTOR_ELEMENT_BUILD( head, nodetype,  targptr, oldval ) \
		( head ## transactionelement ){ (nodetype**){ targptr }, (nodetype*){ oldval } }
	/* Note that the following array and set builders, the data type */
	/*  REALLY ISN'T needed, because the type-system will handle that */
	/*  already. */
			/* Produces a statically allocated transaction array. */
	#define LIBANDRIA4_RECURSIVETRANSACTOR_ARRAY_STATICBUILD( outername, innername, head,  ... ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD( \
			outername, innername, head, ( head ## transactionelement ), __VA_ARGS__ );
		/* Produces an actual transaction set. */
	#define LIBANDRIA4_RECURSIVETRANSACTOR_SET_STATICBUILD( setname, arrhostname, head,  ... ) \
		LIBANDRIA4_RECURSIVETRANSACTOR_ARRAY_STATICBUILD( \
			arrhostname, inner, head, ( head ## transactionelement ), __VA_ARGS__ ); \
		static ( head ## transactionset ) setname = { &( (arrhostname).inner ), 0 };
	
	#define LIBANDRIA4_RECURSIVETRANSACTOR_BUILDTRACK( head, nodetype ) \
		int ( head ## track ) \
			( libandria4_memfuncs_t *mf, \
				( head ## transactionset ) *set, ( head ## transactionelement ) elem ) { \
			if( mf && set ) { \
				if( !( elem.loc ) ) { return( -2 ); } \
				head##pascalarray_result allocres; head ## pascalarray *a; int ret = -5; \
				if( !( set->arr ) ) { /* No array, allocate one. */ \
					allocres = head##pascalarray_build( mf,  1 ); \
					LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( \
						allocres, \
							LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_RETURNVAL_n3 ); \
					set->arr = a; ret = 1; } \
				else if( set->unusedlen < 1 ) { /* Have array, but no extra space: enlarge. */ \
					allocres = head##pascalarray_rebuild( mf,  set->arr, set->arr->len + 1 ); \
					LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( \
						allocres, \
							LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_RETURNVAL_n4 ); \
					set->arr = a; ret = 2; } \
				else { /* We have the spare entries, we just need to expose them. */ \
					--( set->unusedlen ); ++( set->arr->len ); ret = 3; } \
				if( ret ) { set->arr->body[ set->arr->len - 1 ] = elem; } \
				return( ret ); } \
			return( -1 ); }\
		head##transactionset_result ( head##build ) ( libandria4_memfuncs_t *mf ) { \
			void *a = (void*)0; \
			uintptr_t b = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED; \
			LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ); \
			if( len ) { \
				if( !( mf->alloc ) ) { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						parrtype, LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				libandria4_ptrresult ptrres = (mf->alloc)( mf->data, \
						sizeof( head##transactionset ) ); \
				LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb ) } \
			if( a ) { \
				( ( head ## transactionset *) a )->arr = 0; \
				( ( head ## transactionset *) a )->unusedlen = 0; \
				LIBANDRIA4_MONAD_EITHER_RETURNLEFT( head##transactionset_result, head##transactionset*, a ); } \
			else { \
				LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
					head##transactionset_result, uintptr_t, b ); } }
	#define LIBANDRIA4_RECURSIVETRANSACTOR_BUILDREVERT( head ) \
		int ( head ## revert ) ( ( head ## transactionset ) *set ) { \
			if( set && set->arr ) { \
					/* Restore the previous values. */ \
				while( set->arr->len ) { --( set->arr->len ); ++( set->unusedlen ); \
					*( set->arr->body[ set->arr->len ].loc ) = \
						( set->arr->body[ set->arr->len ].val ); } \
				return( 1 ); } \
			return( -1 ); }
	#define LIBANDRIA4_RECURSIVETRANSACTOR_CLEAR( head ) \
		int ( head ## clear ) ( ( head ## transactionset ) *set ) { \
			if( set ) { \
				if( !( set->arr ) ) { return( -2 ); } \
				set->unusedlen += set->arr->len; set->arr->len = 0; \
				return( 1 ); } \
			return( -1 ); }
	#define LIBANDRIA4_RECURSIVETRANSACTOR_FREE( head ) \
		int ( head ## destroyarr ) ( libandria4_memfuncs_t *mf,  ( head ## transactionset ) *set ) { \
			if( mf && set ) { \
				if( !( set->arr ) ) { set->unusedlen = 0; return( 0 ); } \
				libandria4_result res = head##pascalarray_destroy( mf, set->arr ); \
				LIBANDRIA4_RESULT_BODYMATCH( res, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_OP_RETURNVAL_n3 ); \
				set->unusedlen = 0; \
				return( -2 ); } \
			return( -1 ); } \
		libandria4_result ( head ## destroyset ) ( libandria4_memfuncs_t *mf,  ( head ## transactionset ) *set ) { \
			if( !set ) { LIBANDRIA4_RESULT_RETURNSUCCESS( (libandria4_success_result){ 0 } ); } \
			if( mf ) { \
				if( !( mf->dealloc ) ) { \
					LIBANDRIA4_RESULT_RETURNFAILURE( \
						(libandria4_failure_result){ LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS } ); } \
				int res = ( head ## destroyarr ) ( mf,  set ); if( res < 0 ) { \
					LIBANDRIA4_RESULT_RETURNFAILURE( \
						(libandria4_failure_result){ LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED } ); } \
				return( (mf->dealloc)( mf->data, set ) ); } \
			LIBANDRIA4_RESULT_RETURNFAILURE( \
				(libandria4_failure_result){ LIBANDRIA4_RESULT_FAILURE_DOMAIN } ); }
	
	#define LIBANDRIA4_RECURSIVETRANSACTOR_DEFINE( head, nodetype ) \
		LIBANDRIA4_RECURSIVETRANSACTOR_DECLARE( head, nodetype ); \
		LIBANDRIA4_RECURSIVETRANSACTOR_BUILDTRACK( head, nodetype ); \
		LIBANDRIA4_RECURSIVETRANSACTOR_BUILDREVERT( head ); \
		LIBANDRIA4_RECURSIVETRANSACTOR_CLEAR( head ); \
		LIBANDRIA4_RECURSIVETRANSACTOR_FREE( head );
	
#endif
/* End libandria4 basic reversivetransactor.h */
