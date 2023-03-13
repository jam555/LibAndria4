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

#ifndef LIB4_PASCALARRAY_H
# define LIB4_PASCALARRAY_H
	
	#include "stdmem.h"
	#include "stdmonads.h"
	#include "macrotime/simpleops.h"
	
	
	#define LIB4_PASCALARRAY_MEMMANARGS LIB4_MEMFUNCS_MEMMANARGS
	
	
	
		/* Note: to allow compound literals, I've removed the size of "1" */
		/*  from the body array. THIS MAY BREAK SHIT! Especially if that */
		/*  "shit" assumes that the struct always provides 1 char... */
	#define LIB4_DEFINE_PASCALARRAY_TYPE( head, type ) \
		typedef struct head##pascalarray { \
			size_t len; type body[]; \
		} head##pascalarray; \
		LIB4_MONAD_EITHER_BUILDTYPE_DEFINITION( \
			head##pascalarray_result, \
			head##pascalarray*, lib4_failure_uipresult \
		)
	
	#define LIB4_DEFINE_PASCALARRAY_LITERAL( head, len, text ) \
		(head##pascalarray){ ( len ), ( text ) }
	#define LIB4_DEFINE_PASCALARRAY_LITERAL2( head, type, ... ) \
		LIB4_DEFINE_PASCALARRAY_LITERAL( head, sizeof( (type[]){ __VA_ARGS__ } ), (type[]){ __VA_ARGS__ } )
	
	
	#define LIB4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( head, val ) \
		LIB4_MONAD_EITHER_BUILDLEFT( \
			head##pascalarray_result, head##pascalarray*, (val) \
		)
	#define LIB4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( head, val ) \
		LIB4_MONAD_EITHER_BUILDRIGHT( \
			head##pascalarray_result, lib4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIB4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( var, matcha, matchb ) \
		LIB4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIB4_DEFINE_PASCALARRAY_RESULT_EXPRMATCH( var, matcha, matchb ) \
		LIB4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Used to make it easier to convert from one return-wrapper type to */
		/*  another. */
	#define LIB4_DEFINE_PASCALARRAY_RESULT_RETURNSUCCESS( head, val ) \
		LIB4_MONAD_EITHER_RETURNLEFT( \
			head##pascalarray_result, head##pascalarray*, (val) )	
	#define LIB4_DEFINE_PASCALARRAY_RESULT_RETURNFAIL( head, val ) \
		LIB4_MONAD_EITHER_RETURNRIGHT( \
			head##pascalarray_result, lib4_failure_uipresult, (val) )
	
	
	#define LIB4_DEFINE_PASCALARRAY_INIT( head, parrtype ) \
		int head##pascalarray_init( parrtype *parr, size_t len ) { \
			if( parr ) { parr->len = len; return( 1 ); } return( -1 ); \
		}
	
		/* Note: len gets stored UNALTERED into the pascal array. If you use */
		/*  it as an index directly, then it will point you past the legal */
		/*  end of the array. */
	#define LIB4_DEFINE_PASCALARRAY_BUILD( head, parrtype, type ) \
		head##pascalarray_result head##pascalarray_build \
		( lib4_memfuncs_t *mf,  size_t len ) \
		{ void *a = (void*)0; \
			lib4_failure_uipresult b = LIB4_RESULT_FAILURE_UNDIFFERENTIATED; \
			LIB4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ) \
			if( len ) { \
				if( !( mf->alloc ) ) { \
					return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						LIB4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				lib4_ptrresult ptrres = (mf->alloc)( mf->data, \
						sizeof( parrtype ) + sizeof( type ) * len ); \
				LIB4_PTRRESULT_BODYMATCH( ptrres, \
					LIB4_OP_SETa, LIB4_OP_SETb ) } \
			if( a ) { \
				if( head##pascalarray_init( (head##pascalarray*)a, len ) \
					< 0 ) \
				{ dealloc( data, a ); \
					return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						head, LIB4_RESULT_FAILURE_UNDIFFERENTIATED ) ); } \
				else { \
					return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( \
						head, (head##pascalarray*)a ) ); } } \
			else { return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				head, b ) ); } }
		/* This also stores newlen directly into the array. */
		/* Responds to a newlen of 0 with LIB4_RESULT_FAILURE_DOMAIN. */
	#define LIB4_DEFINE_PASCALARRAY_REBUILD( head, parrtype, type ) \
		head##pascalarray_result head##pascalarray_rebuild \
		( lib4_memfuncs_t *mf,  parrtype *parr, size_t newlen ) \
		{ \
			void *a = (void*)0; \
			lib4_failure_uipresult b = LIB4_RESULT_FAILURE_UNDIFFERENTIATED; \
			LIB4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ) \
			if( newlen ) { \
				if( !( parr && mf->realloc ) ) { \
					return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
						LIB4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				lib4_ptrresult ptrres = (mf->realloc)( mf->data, parr, \
						sizeof( parrtype ) + sizeof( type ) * newlen ); \
				LIB4_PTRRESULT_BODYMATCH( ptrres, \
					LIB4_OP_SETa, LIB4_OP_SETb ) } \
			else { return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				head, LIB4_RESULT_FAILURE_DOMAIN ) ); } \
			if( a ) { \
				a->len = newlen; \
				return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( \
					head, (head##pascalarray*)a ) ); } \
			else { return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				head, b ) ); } }
	#define LIB4_DEFINE_PASCALARRAY_DESTROY( head, parrtype, type ) \
		lib4_result head##pascalarray_destroy( \
			lib4_memfuncs_t *mf, parrtype *parr ) \
		{ if( mf->dealloc ) { return( ( mf->dealloc )( mf->data, parr ) ); } \
			return( LIB4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( \
				LIB4_RESULT_FAILURE_BADMEMADDRESS ) ); }
	
	#define LIB4_DEFINE_PASCALARRAY_VISIT( head, parrtype, type ) \
		void head##pascalarray_visit( parrtype *parr,  \
			void *data, void (*visitor)( void*, type* ) ) \
			{ size_t l = 0; if( parr && visitor ) { while( l < parr->len ) \
				{ visitor( data, parr->body[ l++ ] ); } } }
	
	
	
	#define LIB4_DEFINE_PASCALARRAY_BAREDEFINE( head, type ) \
		LIB4_DEFINE_PASCALARRAY_TYPE( head, type ) \
		LIB4_DEFINE_PASCALARRAY_INIT( head, head##pascalarray ) \
		LIB4_DEFINE_PASCALARRAY_BUILD( head, head##pascalarray, type ) \
		LIB4_DEFINE_PASCALARRAY_REBUILD( head, head##pascalarray, type ) \
		LIB4_DEFINE_PASCALARRAY_DESTROY( head, head##pascalarray, type ) \
		LIB4_DEFINE_PASCALARRAY_VISIT( head, head##pascalarray, type )
	
	
	#define LIB4_DEFINE_PASCALARRAY_WRAPEDDEFINE( head, type, memfuncs_ptr )
		LIB4_DEFINE_PASCALARRAY_TYPE( head, type ) \
		LIB4_DEFINE_PASCALARRAY_INIT( head, head##pascalarray ) \
		LIB4_DEFINE_PASCALARRAY_BUILD( lib4_definer_##head, \
			head##pascalarray, type ) \
		LIB4_DEFINE_PASCALARRAY_REBUILD( lib4_definer_##head, \
			head##pascalarray, type ) \
		LIB4_DEFINE_PASCALARRAY_DESTROY( lib4_definer_##head, \
			head##pascalarray, type ) \
		LIB4_DEFINE_PASCALARRAY_VISIT( head, head##pascalarray, type ) \
		head##pascalarray_result head##pascalarray_build( size_t len ) \
			{ return( lib4_definer_##head##pascalarray_build( \
				( memfuncs_ptr ),  len ) ); } \
		head##pascalarray_result head##pascalarray_rebuild \
			( head##pascalarray *parr, size_t newlen ) \
			{ return( lib4_definer_##head##pascalarray_rebuild( \
				( memfuncs_ptr ),  parr, newlen ) ); } \
		lib4_result head##pascalarray_destroy( head##pascalarray *parr ) \
			{ return( lib4_definer_##head##pascalarray_destroy( \
				( memfuncs_ptr ),  parr ) ); }
		
		
	#define LIB4_DEFINE_PASCALARRAY_STDDEFINE( head, type ) \
		LIB4_DEFINE_PASCALARRAY_WRAPEDDEFINE( head, type,  &lib4_stdmemfuncs )
	
#endif
/* End lib4 pascalarray.h */
