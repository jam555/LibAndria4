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
	
	
	
	/* Closure-trampolining-style engine. */
	/* A flexible C-style route to e.g. tail-calls, even for compilers that */
	/*  won't directly support such. */
	
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
		libandria4_charparrptr_pascalarray *stacks;
		libandria4_sizet_pascalarray *align, *used, *alignreq;
		libandria4_bitarray *reallocatable;
		
		libandria4_cts_closure next_iteration;
			/* The number of iterations to run through: negative means */
			/*  "infinite". */
		int run;
		
		/* TODO: add an output stream here, to route error messages. */
	};
	int libandria4_cts_isvalid( libandria4_cts_context *ctx )
	{
		if( ctx->stacks && ctx->align && ctx->used && ctx->alignreq && ctx->reallocatable )
		{
			size_t len = ctx->stacks->len;
			if
			(
				len == ctx->align->len &&
				len == ctx->used->len &&
				len == ctx->alignreq->len &&
				len == ctx->reallocatable->len
			)
			{
				if( ctx->next_iteration.handler )
				{
					return( 2 );
				}
				
				return( 1 );
			}
			
			return( 0 );
		}
		
		return( -1 );
	}
	int libandria4_cts_isvalid2( libandria4_cts_context *ctx )
	{
		if( libandria4_cts_isvalid( ctx ) )
		{
			size_t iter = 0;
			while( iter < ctx->stacks->len )
			{
				if( !( ctx->stacks->body[ iter ] ) )
				{
					return( -2 );
				}
				if
				(
					ctx->stacks->body[ iter ]->len <
					ctx->align->body[ iter ] + ctx->used->body[ iter ]
				)
				{
					return( -3 );
				}
				
				++iter;
			}
			
			return( 1 );
		}
		
		return( -1 );
	}
	
		/* Performs the actual trampolining. */
	int libandria4_cts_engine( libandria4_cts_context *ctx );
	
	
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
	
	
	
	int libandria4_cts_sizedpop( libandria4_cts_context *ctx, size_t stack,  void *dest, size_t size );
	
	#define LIBANDRIA4_CTS_DECPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val );
	#define LIBANDRIA4_CTS_DEFPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val ) { \
			if( !val ) { return( -1 ); } \
			return( libandria4_cts_sizedpop( ctx, stack,  (void*)val, sizeof( type ) ) ); }
	
	
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
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _voidf, void (*)() );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );
	
#endif
/* End libandria4 basic ctsengine.h */
