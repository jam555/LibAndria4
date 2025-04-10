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

#ifndef LIBANDRIA4_BASIC_PASCALARRAY_H
# define LIBANDRIA4_BASIC_PASCALARRAY_H
	
	#include <stddef.h>
	
	#include "commonmacros.h"
	#include "stdmem.h"
	#include "simpleops.h"
	#include "stdmonads.h"
	#include "commonerrvals.h"
	
	
	#define LIBANDRIA4_PASCALARRAY_MEMMANARGS LIBANDRIA4_MEMFUNCS_MEMMANARGS
	
	/* LIBANDRIA4_FLEXARRAY_FILLERLENGTH is now provided by commonmacros.h */
	
	
	
		/* Note: to allow compound literals, I've removed the size of "1" */
		/*  from the body array. THIS MAY BREAK SHIT! Especially if that */
		/*  "shit" assumes that the struct always provides 1 char... */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( head, type ) \
		typedef struct head##pascalarray { \
			size_t len; type body[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ]; \
		} head##pascalarray; \
		typedef head##pascalarray head##parr;\
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( \
			head##pascalarray_result, \
			head##pascalarray*, libandria4_failure_uipresult \
		) \
		typedef head##pascalarray_result head##parres;\
		typedef head##pascalarray_result head##parrres;\
		typedef struct head##pascalarray_excerpt { \
			head##pascalarray *arr; size_t start, len; \
		} head##pascalarray_excerpt; \
		typedef head##pascalarray_excerpt head##parrexrp; \
		typedef head##pascalarray_excerpt head##parrexrpt; \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( \
			head##pascalarray_excerpt_result, \
			head##pascalarray_excerpt, libandria4_failure_uipresult \
		) \
		typedef head##pascalarray_excerpt_result head##parrexrpres; \
		typedef head##pascalarray_excerpt_result head##parrexrptres;
	
	
	
	/* Both LIBANDRIA4_DEFINE_PASCALARRAY_LITERAL() and */
	/*  LIBANDRIA4_DEFINE_PASCALARRAY_LITERAL2() used to be here. They */
	/*  attempted to initialize a "flexible array member" as part of the */
	/*  containing struct, which even for gloabals/statics and even at */
	/*  compile-time is illegal. Thus, they've been deleted. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD( outername, innername, head, type, ... ) \
		static struct { head##pascalarray innername; type libandria4_pascalarray_arrmember[ \
			sizeof( (type[]){ __VA_ARGS__ } ) / sizeof( type ) ]; } outername = \
			{ (head##pascalarray){ sizeof( (type[]){ __VA_ARGS__ } ) / sizeof( type ) }, \
				/* (type[]) *//*Using an aggregate initializer HERE causes parse errors, nowhere else.*/ \
				{ __VA_ARGS__ } };
	/* These should work fine. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_LITERAL( parrtype,  parrptr, start, len ) \
		( (parrtype##parrexrpt){ (parrptr),  (start), (len) } )
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_LITERAL2( parrtype,  parrptr, extentA, extentB ) \
		( (parrtype##parrexrpt){ (parrptr), \
			( (extentA) < (extentB) ? (extentA) : (extentB) ), \
			( (extentA) < (extentB) ? (extentB) - (extentA) : (extentA) - (extentB) ) } )
	
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( parrtype, val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			parrtype##_result, parrtype*, (val) \
		)
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( parrtype, val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			parrtype##_result, \
			libandria4_failure_uipresult, \
			(libandria4_failure_uipresult){ val } \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( var, onsucc, onfail ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, onsucc, onfail )
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_EXPRMATCH( var, onsucc, onfail ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, onsucc, onfail )
	
		/* Used to make it easier to convert from one return-wrapper type to */
		/*  another. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_RETURNSUCCESS( head, val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( \
			head##pascalarray_result, head##pascalarray*, (val) )	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_RETURNFAIL( head, val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			head##pascalarray_result, libandria4_failure_uipresult, (val) )
	
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_BUILDSUCCESS( parrtype, val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			parrtype##_excerpt_result, parrtype##_excerpt, (val) \
		)
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_BUILDFAILURE( parrtype, val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			parrtype##_excerpt_result, \
			libandria4_failure_uipresult, \
			(libandria4_failure_uipresult){ (val) } \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_BODYMATCH( var, onsucc, onfail ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, onsucc, onfail )
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_EXPRMATCH( var, onsucc, onfail ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, onsucc, onfail )
	
		/* Used to make it easier to convert from one return-wrapper type to */
		/*  another. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_RETURNSUCCESS( head, val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( \
			head##pascalarray_excerpt_result, head##pascalarray_excerpt, (val) )
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_RETURNFAIL( head, val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			head##pascalarray_excerpt_result, libandria4_failure_uipresult, (val) )
	
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_INIT( head, parrtype ) \
		int head##pascalarray_init( parrtype *parr, size_t len ) { \
			if( parr ) { parr->len = len; return( 1 ); } return( -1 ); \
		}
	
		/* Note: len gets stored UNALTERED into the pascal array. If you use */
		/*  it as an index directly, then it will point you past the legal */
		/*  end of the array. */
		/* Note that if len is 0, then NO allocation will be performed. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_BUILD( head, parrtype, type ) \
		parrtype##_result head##pascalarray_build( \
			libandria4_memfuncs_t *mf,  size_t len ) \
		{ void *a = (void*)0; \
			libandria4_failure_uipresult b; \
			b.val = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED; \
			LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ); \
			if( len ) { \
				if( !( mf->alloc ) ) { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						parrtype, LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				libandria4_ptrresult ptrres = (mf->alloc)( mf->data, \
						sizeof( parrtype ) + sizeof( type ) * len ); \
				LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, \
					LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb ) } \
			if( a ) { \
				if( head##pascalarray_init( (parrtype*)a, len ) \
					< 0 ) \
				{ (mf->dealloc)( mf->data, a ); \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						parrtype, LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) ); } \
				else { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( \
						parrtype, (parrtype*)a ) ); } } \
			else { return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				parrtype, b.val ) ); } }
		/* This also stores newlen directly into the array. */
		/* Responds to a newlen of 0 with LIBANDRIA4_RESULT_FAILURE_DOMAIN. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_REBUILD( head, parrtype, type ) \
		parrtype##_result head##pascalarray_rebuild \
		( libandria4_memfuncs_t *mf,  parrtype *parr, size_t newlen ) \
		{ \
			void *a = (void*)0; \
			libandria4_failure_uipresult b; \
			b.val = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED; \
			LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ); \
			if( newlen ) { \
				if( !( parr && mf->realloc ) ) { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						parrtype, LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				libandria4_ptrresult ptrres = (mf->realloc)( mf->data, parr, \
						sizeof( parrtype ) + sizeof( type ) * newlen ); \
				LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, \
					LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb ) } \
			else { return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				parrtype, LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			if( a ) { \
				( (parrtype*)a )->len = newlen; \
				return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( \
					parrtype, (parrtype*)a ) ); } \
			else { return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				parrtype, b.val ) ); } }
	#define LIBANDRIA4_DEFINE_PASCALARRAY_DESTROY( head, parrtype, type ) \
		libandria4_result head##pascalarray_destroy( \
			libandria4_memfuncs_t *mf, parrtype *parr ) \
		{ if( mf->dealloc ) { return( (mf->dealloc)( mf->data, parr ) ); } \
			return( LIBANDRIA4_RESULT_BUILDFAILURE( \
				LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); }
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_FILL( head, parrtype, type ) \
		libandria4_result head##pascalarray_fill( parrtype *parr, type *src ) \
			{ if( !parr || !src ) { \
					return( LIBANDRIA4_RESULT_BUILDFAILURE( \
							LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
				size_t len = 0; while( len < parr->len ) { \
					parr->body[ len ] = src[ len ]; ++len; } \
				return ( LIBANDRIA4_RESULT_BUILDSUCCESS( \
						LIBANDRIA4_RESULT_GENERICTRUE ) ); }
		#define LIBANDRIA4_DEFINE_PASCALARRAY_BUILDnFILL_ONFAIL( err ) \
			fail.val = err.val; goto on_err;
	#define LIBANDRIA4_DEFINE_PASCALARRAY_BUILDnFILL( head, parrtype, type ) \
		parrtype##_result head##pascalarray_buildNfill( \
			libandria4_memfuncs_t *mf,  size_t len, type *src ) \
		{ if( !src ) { \
				return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
					parrtype, LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ); \
			parrtype *a; libandria4_failure_uipresult fail; \
			parrtype##_result res1 = head##pascalarray_build( mf,  len ); \
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( res1, \
				LIBANDRIA4_OP_SETa, \
				LIBANDRIA4_DEFINE_PASCALARRAY_BUILDnFILL_ONFAIL ); \
			libandria4_result res2 = head##pascalarray_fill( a, src ); \
			LIBANDRIA4_RESULT_BODYMATCH( res2, \
				LIBANDRIA4_NULL_MACRO, \
				LIBANDRIA4_DEFINE_PASCALARRAY_BUILDnFILL_ONFAIL ); \
			return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( parrtype, a ) ); \
			on_err: return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( parrtype, fail.val ) ); }
	#define LIBANDRIA4_DEFINE_PASCALARRAY_VISIT( head, parrtype, type ) \
		void head##pascalarray_visit( parrtype *parr,  \
			void *data, void (*visitor)( void*, type* ) ) \
			{ size_t l = 0; if( parr && visitor ) { while( l < parr->len ) \
				{ visitor( data, &( parr->body[ l++ ] ) ); } } }
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_ISVALID( head, parrtype, type ) \
		int head##pascalarray_excerpt_isvalid( head##pascalarray_excerpt *exc ) { \
			if( exc ) { \
				if( exc->arr ) { return( -2 ); } \
				\
				if( exc->arr->len <= exc->start ) { return( -3 ); } \
				if( exc->arr->len < exc->start + exc->len ) { return( -4 ); } \
				\
				if( !( exc->len ) ) { return( 0 ); } \
				return( 1 ); } \
			return( -1 ); }
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_BAREARRAYIFY( head, parrtype, type ) \
		parrtype##_result head##pascalarray_excerpt_arrayify( \
			libandria4_memfuncs_t *mf, parrtype##_excerpt *exc, \
			size_t padsize, type padval ) \
		{ if( exc ) { \
				if( parrtype##_excerpt_isvalid( exc ) < 0 ) { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						parrtype, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ) ); } \
				\
				padsize = ( padsize ? padsize : 0 ); parrtype *a = 0; \
				\
				parrtype##_result res = \
						/* Note that using head## ALWAYS gets us the builder that we want HERE. */ \
					head##pascalarray_build( mf,  exc->len + padsize ); \
				LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( \
					res, LIBANDRIA4_OP_SETa, LIBANDRIA4_NULL_MACRO ); \
				\
				size_t iter = 0; \
				while( a && iter < exc->len ) { \
					a->body[ iter ] = exc->arr->body[ exc->start + iter ]; ++iter; } \
				while( a && iter < a->len ) { a->body[ iter ] = padval; ++iter; } \
				\
				return( res ); } \
			\
			return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				parrtype, LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); }
	#define LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_BAREINVARRAYIFY( head, parrtype, type ) \
		parrtype##_result head##pascalarray_excerpt_inversearrayify( \
			libandria4_memfuncs_t *mf, parrtype##_excerpt *exc, \
			size_t padsize, type padval ) \
		{ if( exc ) { \
				if( parrtype##_excerpt_isvalid( exc ) < 0 ) { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						parrtype, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ) ); } \
				\
				padsize = ( padsize ? padsize : 0 ); parrtype *a = 0; \
				\
				parrtype##_result res = \
						/* Note that using head## ALWAYS gets us the builder that we want HERE. */ \
					head##pascalarray_build( mf,  ( exc->arr->len - exc->len ) + padsize ); \
				\
				size_t iter = 0; \
				while( a && iter < exc->start ) { \
					a->body[ iter ] = exc->arr->body[ iter ]; ++iter; } \
				while( a && exc->len + iter < exc->arr->len ) { \
					a->body[ iter ] = exc->arr->body[ exc->len + iter ]; ++iter; } \
				while( a && iter < a->len ) { a->body[ iter ] = padval; ++iter; } \
				\
				return( res ); } \
			\
			return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				parrtype, LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); }
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_BAREDECLARE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( head, type ) \
			/* *init(), *build(), & *rebuild() all store len into the array. */ \
		int head##pascalarray_init( head##pascalarray *parr, size_t len ); \
		head##pascalarray_result head##pascalarray_build( libandria4_memfuncs_t *mf,  size_t len ); \
			/* *rebuild() responds to a newlen of 0 with LIBANDRIA4_RESULT_FAILURE_DOMAIN. */ \
		head##pascalarray_result head##pascalarray_rebuild( libandria4_memfuncs_t *mf,  head##pascalarray *parr, size_t newlen ); \
		libandria4_result head##pascalarray_fill( head##pascalarray *parr, type *src ); \
		head##pascalarray_result head##pascalarray_buildNfill( libandria4_memfuncs_t *mf,  size_t len, type *src ); \
		libandria4_result head##pascalarray_destroy( libandria4_memfuncs_t *mf, head##pascalarray *parr ); \
		void head##pascalarray_visit( head##pascalarray *parr,  void *data, void (*visitor)( void*, type* ) ); \
		\
		int head##pascalarray_excerpt_isvalid( head##pascalarray_excerpt *exc ); \
		head##pascalarray_result head##pascalarray_excerpt_arrayify( libandria4_memfuncs_t *mf, \
			head##pascalarray_excerpt *exc,  size_t padsize, (type) padval ); \
		head##pascalarray_result head##pascalarray_excerpt_inversearrayify( libandria4_memfuncs_t *mf, \
			head##pascalarray_excerpt *exc,  size_t padsize, (type) padval );
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_BAREDEFINE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BAREDECLARE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_INIT( head, head##pascalarray ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BUILD( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_REBUILD( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_FILL( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BUILDnFILL( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_DESTROY( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_VISIT( head, head##pascalarray, type ) \
		\
		LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_ISVALID( head, parrtype, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_BAREARRAYIFY( head, parrtype, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_BAREINVARRAYIFY( head, parrtype, type )
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_WRAPPEDDECLARE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( head, type ) \
			/* *init(), *build(), & *rebuild() all store len into the array. */ \
		int head##pascalarray_init( head##pascalarray *parr, size_t len ); \
		head##pascalarray_result head##pascalarray_build( size_t len ); \
			/* *rebuild() responds to a newlen of 0 with LIBANDRIA4_RESULT_FAILURE_DOMAIN. */ \
		head##pascalarray_result head##pascalarray_rebuild( head##pascalarray *parr, size_t newlen ); \
		libandria4_result head##pascalarray_fill( head##pascalarray *parr, type *src ); \
		head##pascalarray_result head##pascalarray_buildNfill( size_t len, type *src ); \
		libandria4_result head##pascalarray_destroy( head##pascalarray *parr ); \
		void head##pascalarray_visit( head##pascalarray *parr,  void *data, void (*visitor)( void*, type* ) ); \
		\
		int head##pascalarray_excerpt_isvalid( head##pascalarray_excerpt *exc ); \
		head##pascalarray_result head##pascalarray_excerpt_arrayify( head##pascalarray_excerpt *exc, \
			size_t padsize, type padval ); \
		head##pascalarray_result head##pascalarray_excerpt_inversearrayify( head##pascalarray_excerpt *exc, \
			size_t padsize, type padval );
	
		/* This needs to be paired with a LIBANDRIA4_DEFINE_PASCALARRAY_WRAPPEDDECLARE() invocation. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_WRAPPEDDEFINE( head, type, memfuncs_ptr ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_INIT( libandria4_definer_##head, head##pascalarray ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BUILD( libandria4_definer_##head, \
			head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_REBUILD( libandria4_definer_##head, \
			head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_DESTROY( libandria4_definer_##head, \
			head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_FILL( libandria4_definer_##head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BUILDnFILL( libandria4_definer_##head, \
			head##pascalarray, type ) \
		int head##pascalarray_init( head##pascalarray *parr, size_t len ) \
			{ return( libandria4_definer_##head##pascalarray_init( \
				parr, len ) ); } \
		head##pascalarray_result head##pascalarray_build( size_t len ) \
			{ return( libandria4_definer_##head##pascalarray_build( \
				( memfuncs_ptr ),  len ) ); } \
		head##pascalarray_result head##pascalarray_rebuild \
			( head##pascalarray *parr, size_t newlen ) \
			{ return( libandria4_definer_##head##pascalarray_rebuild( \
				( memfuncs_ptr ),  parr, newlen ) ); } \
		libandria4_result head##pascalarray_fill( head##pascalarray *parr, type *src ) \
			{ return( libandria4_definer_##head##pascalarray_fill( \
				parr, src ) ); } \
		head##pascalarray_result head##pascalarray_buildNfill( size_t len, type *src ) \
			{ return( libandria4_definer_##head##pascalarray_buildNfill( \
				( memfuncs_ptr ), len, src ) ); } \
		libandria4_result head##pascalarray_destroy( head##pascalarray *parr ) \
			{ return( libandria4_definer_##head##pascalarray_destroy( \
				( memfuncs_ptr ),  parr ) ); } \
		LIBANDRIA4_DEFINE_PASCALARRAY_VISIT( head, head##pascalarray, type ) \
		\
		LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_ISVALID( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_BAREARRAYIFY( libandria4_definer_##head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_BAREINVARRAYIFY( libandria4_definer_##head, head##pascalarray, type ) \
		head##pascalarray_result head##pascalarray_excerpt_arrayify( head##pascalarray_excerpt *exc, \
			size_t padsize, type padval ) \
			{ return( libandria4_definer_##head##pascalarray_excerpt_arrayify( \
				(memfuncs_ptr), exc, padsize, padval ) ); } \
		head##pascalarray_result head##pascalarray_excerpt_inversearrayify( head##pascalarray_excerpt *exc, \
			size_t padsize, type padval ) \
			{ return( libandria4_definer_##head##pascalarray_excerpt_inversearrayify( \
				(memfuncs_ptr), exc, padsize, padval ) ); }
		
		
		/* This needs to be paired with a LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE() invocation. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_WRAPPEDDEFINE( head, type,  &libandria4_stdmemfuncs )
	
#endif
/* End libandria4 basic pascalarray.h */
