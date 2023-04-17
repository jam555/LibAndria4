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
	
	#include "stdmem.h"
	#include "stdmonads.h"
	#include "simpleops.h"
	
	
	#define LIBANDRIA4_PASCALARRAY_MEMMANARGS LIBANDRIA4_MEMFUNCS_MEMMANARGS
	
	
	
		/* Note: to allow compound literals, I've removed the size of "1" */
		/*  from the body array. THIS MAY BREAK SHIT! Especially if that */
		/*  "shit" assumes that the struct always provides 1 char... */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( head, type ) \
		typedef struct head##pascalarray { \
			size_t len; type body[]; \
		} head##pascalarray; \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION( \
			head##pascalarray_result, \
			head##pascalarray*, libandria4_failure_uipresult \
		)
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_LITERAL( head, len, text ) \
		(head##pascalarray){ ( len ), ( text ) }
	#define LIBANDRIA4_DEFINE_PASCALARRAY_LITERAL2( head, type, ... ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_LITERAL( \
			head, \
			( sizeof( (type[]){ __VA_ARGS__ } ) ), \
			( (type[]){ __VA_ARGS__ } ) )
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( head, val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			head##pascalarray_result, head##pascalarray*, (val) \
		)
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( head, val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			head##pascalarray_result, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Used to make it easier to convert from one return-wrapper type to */
		/*  another. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_RETURNSUCCESS( head, val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( \
			head##pascalarray_result, head##pascalarray*, (val) )	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_RETURNFAIL( head, val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			head##pascalarray_result, libandria4_failure_uipresult, (val) )
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_INIT( head, parrtype ) \
		int head##pascalarray_init( parrtype *parr, size_t len ) { \
			if( parr ) { parr->len = len; return( 1 ); } return( -1 ); \
		}
	
		/* Note: len gets stored UNALTERED into the pascal array. If you use */
		/*  it as an index directly, then it will point you past the legal */
		/*  end of the array. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_BUILD( head, parrtype, type ) \
		head##pascalarray_result head##pascalarray_build \
		( libandria4_memfuncs_t *mf,  size_t len ) \
		{ void *a = (void*)0; \
			libandria4_failure_uipresult b = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED; \
			LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ) \
			if( len ) { \
				if( !( mf->alloc ) ) { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				libandria4_ptrresult ptrres = (mf->alloc)( mf->data, \
						sizeof( parrtype ) + sizeof( type ) * len ); \
				LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, \
					LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb ) } \
			if( a ) { \
				if( head##pascalarray_init( (head##pascalarray*)a, len ) \
					< 0 ) \
				{ dealloc( data, a ); \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						head, LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) ); } \
				else { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( \
						head, (head##pascalarray*)a ) ); } } \
			else { return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				head, b ) ); } }
		/* This also stores newlen directly into the array. */
		/* Responds to a newlen of 0 with LIB4_RESULT_FAILURE_DOMAIN. */
	#define LIBANDRIA4_DEFINE_PASCALARRAY_REBUILD( head, parrtype, type ) \
		head##pascalarray_result head##pascalarray_rebuild \
		( libandria4_memfuncs_t *mf,  parrtype *parr, size_t newlen ) \
		{ \
			void *a = (void*)0; \
			libandria4_failure_uipresult b = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED; \
			LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ) \
			if( newlen ) { \
				if( !( parr && mf->realloc ) ) { \
					return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				libandria4_ptrresult ptrres = (mf->realloc)( mf->data, parr, \
						sizeof( parrtype ) + sizeof( type ) * newlen ); \
				LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, \
					LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb ) } \
			else { return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				head, LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			if( a ) { \
				a->len = newlen; \
				return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( \
					head, (head##pascalarray*)a ) ); } \
			else { return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				head, b ) ); } }
	#define LIBANDRIA4_DEFINE_PASCALARRAY_DESTROY( head, parrtype, type ) \
		libandria4_result head##pascalarray_destroy( \
			libandria4_memfuncs_t *mf, parrtype *parr ) \
		{ if( mf->dealloc ) { return( ( mf->dealloc )( mf->data, parr ) ); } \
			return( LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); }
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_VISIT( head, parrtype, type ) \
		void head##pascalarray_visit( parrtype *parr,  \
			void *data, void (*visitor)( void*, type* ) ) \
			{ size_t l = 0; if( parr && visitor ) { while( l < parr->len ) \
				{ visitor( data, parr->body[ l++ ] ); } } }
	
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_BAREDEFINE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_INIT( head, head##pascalarray ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BUILD( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_REBUILD( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_DESTROY( head, head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_VISIT( head, head##pascalarray, type )
	
	
	#define LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDEFINE( head, type, memfuncs_ptr ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_INIT( head, head##pascalarray ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BUILD( libandria4_definer_##head, \
			head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_REBUILD( libandria4_definer_##head, \
			head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_DESTROY( libandria4_definer_##head, \
			head##pascalarray, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_VISIT( head, head##pascalarray, type ) \
		head##pascalarray_result head##pascalarray_build( size_t len ) \
			{ return( libandria4_definer_##head##pascalarray_build( \
				( memfuncs_ptr ),  len ) ); } \
		head##pascalarray_result head##pascalarray_rebuild \
			( head##pascalarray *parr, size_t newlen ) \
			{ return( libandria4_definer_##head##pascalarray_rebuild( \
				( memfuncs_ptr ),  parr, newlen ) ); } \
		libandria4_result head##pascalarray_destroy( head##pascalarray *parr ) \
			{ return( libandria4_definer_##head##pascalarray_destroy( \
				( memfuncs_ptr ),  parr ) ); }
		
		
	#define LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDEFINE( head, type,  &libandria4_stdmemfuncs )
	
#endif
/* End lib4 basic pascalarray.h */
