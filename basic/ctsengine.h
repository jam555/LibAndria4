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

#ifndef LIBANDRIA4_BASIC_CTSENGINE_H
# define LIBANDRIA4_BASIC_CTSENGINE_H
	
	/* TODO: */
		/* Add an output handle to control where error messages get routed. */
		/* Add a "delay closure" system (separate from any actual context */
		/*  instance) to allow users to easily provide a delay system that */
		/*  doesn't block other execution. Add something to commonlib.h to */
		/*  support this. */
	
	
	
	/* Closure-trampolining-style engine. */
	/* A flexible C-style route to e.g. tail-calls, even for compilers that */
	/*  won't directly support such. */
	
		/* For UCHAR_MAX. */
	#include <limits.h>
	
	#include "commontypes.h"
	#include "pascalarray.h"
		/* For libandria4_char_pascalarray{} */
	#include "pascalstring.h"
		/* For libandria4_charparrptr_pascalarray{} */
	#include "commonparrs.h"
	#include "bitarray.h"
	
	
	
		/* We ultimately need a type-recursion, but fortunately it goes via */
		/*  pointers so we just need a declaration to break the loop. */
	typedef struct libandria4_cts_context libandria4_cts_context;
	
	
	/* Our closure construct. THe void* is just whatever arbitrary data, and */
	/*  we CAN'T guess in the engine system as to how to deal with it, it */
	/*  MUST be understood by the closure by itself. Sooo... it's never set */
	/*  by the engine itself, JUST by whatever actually builds the closure. */
	/* Note: if you WANT to extend the closure, THEN DON'T, just use the */
	/*  void pointer instead. The closures get moved around BY VALUE, within */
	/*  the engine, which again CAN'T know about whatever random extensions */
	/*  you try to apply to them, so just DON'T. */
	typedef struct libandria4_cts_closure libandria4_cts_closure;
	typedef
		libandria4_cts_closure (*libandria4_cts_framefunc)
		(
			libandria4_cts_context*, void*
		);
	struct libandria4_cts_closure
	{
		libandria4_cts_framefunc handler;
		void *data;
	};
	
	
	/* The info required to directly run the engine. */
	struct libandria4_cts_context
	{
			/* Usually ->body[ 0 ] should be a return/C stack. A FORTH data */
			/*  stack should be ->body[ 1 ]. */
		libandria4_charparrptr_pascalarray *stacks;
		libandria4_sizet_pascalarray *align, *used, *alignreq;
		libandria4_bitarray *reallocatable;
		
		libandria4_cts_closure next_iteration;
			/* The number of iterations to run through: negative means */
			/*  "infinite". */
		int run;
		
		/* TODO: add an output stream here, to route error messages. */
	};
	int libandria4_cts_isvalid( libandria4_cts_context *ctx );
	int libandria4_cts_isvalid2( libandria4_cts_context *ctx );
	
		/* Performs the actual trampolining. */
	int libandria4_cts_engine( libandria4_cts_context *ctx );
	
	
	#define LIBANDRIA4_CTS_BUILDCONSTCLOSURE( funcptr, voidptr ) \
		( (const libandria4_cts_closure){ (funcptr), (voidptr) } )
	#define LIBANDRIA4_CTS_BUILDCLOSURE( funcptr, voidptr ) \
		( (libandria4_cts_closure){ (funcptr), (voidptr) } )
	#define LIBANDRIA4_CTS_RETURNCLOSURE( funcptr, voidptr ) \
		return( (libandria4_cts_closure){ (funcptr), (voidptr) } )
	
		/* The void pointer will be dereferenced and returned, so that it'll */
		/*  be the first thing to run when (if) you resume execution: you */
		/*  should generally use a static libandria_cts_closure{} pointer */
		/*  for it, but perhaps a nonstatic will work for you. As a GENERAL */
		/*  rule (it may be ok on some platforms), you should NOT give it a */
		/*  null pointer, as only the context gets checked. */
	libandria4_cts_closure libandria4_cts_framefunc_stoprun
	(
		libandria4_cts_context*, void*
	);
	/* More closure functions are near the end of this header. */
	
		/* Hide this for debugging in CMArgs1. */
	/* extern libandria4_commonio_handle libandria4_cts_errout; */
	
	
	
	int libandria4_cts_sizedpop( libandria4_cts_context *ctx, size_t stack,  void *dest_, size_t size );
	int libandria4_cts_sizedpush( libandria4_cts_context *ctx, size_t stack,  void *dest_, size_t size );
	
	
	#define LIBANDRIA4_CTS_DECPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  type *val );
	#define LIBANDRIA4_CTS_DEFPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  type *val ) { \
			if( !val ) { return( -1 ); } \
			return( libandria4_cts_sizedpop( ctx, stack,  (void*)val, sizeof( type ) ) ); }
	
	#define LIBANDRIA4_CTS_DECPUSH( prefix, postfix, type ) \
		int prefix ## push ## postfix ( libandria4_cts_context *ctx, size_t stack,  type *val ); \
		int prefix ## push2 ## postfix ( libandria4_cts_context *ctx, size_t stack,  type data );
	#define LIBANDRIA4_CTS_DEFPUSH( prefix, postfix, type ) \
		int prefix ## push ## postfix ( libandria4_cts_context *ctx, size_t stack,  type *val ) { \
			if( !val ) { return( -1 ); } \
			return( libandria4_cts_sizedpush( ctx, stack,  (void*)val, sizeof( type ) ) ); } \
		int prefix ## push2 ## postfix ( libandria4_cts_context *ctx, size_t stack,  type data ) { \
			if( ctx ) { \
				int res = prefix ## push ## postfix ( ctx, 1,  &data ); \
				if( res > 0 ) { return( 1 ); } \
				else if( res == -4 ) { \
					/* Error: out of space, fix that. */ \
					libandria4_char_pascalarray_result nalloc = \
						libandria4_char_pascalarray_rebuild ( \
							ctx->stacks->body[ stack ], \
							ctx->stacks->body[ stack ]->len + 64 ); \
					libandria4_char_pascalarray *a; \
					libandria4_failure_uipresult e; \
					res = 0; \
					LIBANDRIA4_MONAD_EITHER_BODYMATCH( nalloc, \
							LIBANDRIA4_OP_SETaFLAGresAS1, \
							LIBANDRIA4_OP_SETeFLAGresASn1 ); \
					if( 1 ) { \
						ctx->stacks->body[ stack ] = a; \
						res = prefix ## push ## postfix ( ctx, 1,  &data ); \
							if( res ) { return( 2 ); } \
							else { \
								/* Just give up. */ \
								return( -2 ); } } \
					else if( -1 ) { \
						/* We don't care anymore, just fail unto oblivion. */ \
						return( -3 ); } \
					else { \
						return( -4 ); } } \
				return( -5 ); } \
			return( -1 ); }
	
	
	#define LIBANDRIA4_CTS_DECPUSH_VAL( prefix, postfix, stack, value ) \
		int prefix ## push ## postfix ## _stk ## stack ## _val ## value \
			( libandria4_cts_context *ctx ); \
		libandria4_cts_closure prefix ## ctspush ## postfix ## _stk ## stack ## _val ## value \
			( libandria4_cts_context*, void* );
	#define LIBANDRIA4_CTS_DEFPUSH_VAL( prefix, postfix, stack, value ) \
		int prefix ## push ## postfix ## _stk ## stack ## _val ## value \
			( libandria4_cts_context *ctx ) { \
				return( \
					prefix ## push2 ## postfix ( ctx, (stack),  (value) ) ); } \
		libandria4_cts_closure prefix ## ctspush ## postfix ## _stk ## stack ## _val ## value \
			( libandria4_cts_context *ctx, void *data_ ) { \
				if( !libandria4_cts_isvalid( ctx ) && ctx->stacks->len > (stack) ) { \
					return( \
						libandria4_cts_innerreturn_returnstop( \
							(void*)0, (libandria4_cts_context*)0, 0 ) ); } \
				if( !( prefix ## push2 ## postfix ( ctx, (stack),  (value) ) ) ) { \
					return( \
						libandria4_cts_innerreturn_returnstop( \
							(void*)0, (libandria4_cts_context*)0, 0 ) ); } \
				return( *( (libandria4_cts_closure*)data_ ) ); }
	
	
	/* Note that all of the *_ctspush_*() funcs require pointer */
	/*  to a return value as their second argument. */
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _schar, signed char );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _uchar, unsigned char );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _sshort, signed short );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ushort, unsigned short );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _sint, signed int );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _uint, unsigned int );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _slong, signed long );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ulong, unsigned long );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _float, float );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _double, double );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _sizet, size_t );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ptrdifft, ptrdiff_t );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _voidp, void* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _scharp, signed char* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ucharp, unsigned char* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _voidf, libandria4_common_voidfuncp_void );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );
	
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _schar, signed char );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _uchar, unsigned char );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _sshort, signed short );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ushort, unsigned short );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _sint, signed int );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _uint, unsigned int );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _slong, signed long );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ulong, unsigned long );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _float, float );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _double, double );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _sizet, size_t );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ptrdifft, ptrdiff_t );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _voidp, void* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _scharp, signed char* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ucharp, unsigned char* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _voidf, libandria4_common_voidfuncp_void );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );
	
	
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 0, 0 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 0, 1 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 0, 2 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 0, 3 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 0, 4 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 0, UCHAR_MAX );
	
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 1, 0 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 1, 1 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 1, 2 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 1, 3 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 1, 4 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 1, UCHAR_MAX );
	
	/* These obviously depend on stack[ 2 ] actually existing. */
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 2, 0 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 2, 1 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 2, 2 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 2, 3 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 2, 4 );
	LIBANDRIA4_CTS_DECPUSH_VAL( libandria4_cts_, _uchar, 2, UCHAR_MAX );
	
	
	
	/* Common closure functions */
	
	typedef struct libandria4_cts_innerreturn_data
	{
		void *faildata;
		libandria4_cts_closure (*failfunc)( void*, libandria4_cts_context*, int );
		
		size_t stack;
		
	} libandria4_cts_innerreturn_data;
	libandria4_cts_closure libandria4_cts_innerreturn( libandria4_cts_context *ctx, void *dat );
		/* An easy value for libandria4_cts_innerreturn_data->failfunc. */
	libandria4_cts_closure libandria4_cts_innerreturn_returnstop
	(
		void *ign1, libandria4_cts_context *ign2, int ign3
	);
	
#endif
/* End libandria4 basic ctsengine.h */
