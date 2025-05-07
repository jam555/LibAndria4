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



/* TODO: go looking for the other TODOs in this file and fix them. */



#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

#include "mutablestreams.h"



	/* We do need to define the types instead of just declaring. */
LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDDECL(
	libandria4_FILE_tracker,
		libandria4_FILE_substream_vtable*
);



	/* Complete. Note that THE POINTER ITSELF is null. */
int libandria4_FILE_tracker_initialize_null( libandria4_FILE_tracker *trk )
{
	if( trk )
	{
		return( LIBANDRIA4_MONAD_REFPOINTER_EXPRINIT_NULL( libandria4_FILE_tracker, *trk ) );
	}
	
	return( -1 );
}
		/* This is just a logging function for */
		/*  libandria4_FILE_tracker_initialize(). */
		/* ??? It does no logging. Fix that. ??? */
	static void libandria4_FILE_tracker_initialize_badalloc
	(
		void*, /* "this" pointer. */
		
		libandria4_FILE_tracker_counttype**,
			libandria4_FILE_substream_vtable*,
			void* /* FILE* */
	)
	{
		/* Do nothing, but we REALLY SHOULD log an error. */
		
		return;
	}
	/* Complete? */
int libandria4_FILE_tracker_initialize( libandria4_FILE_tracker *trk,  FILE *f )
{
	if( trk )
	{
		if( !libandria4_FILE_tracker_initialize_null( trk ) )
		{
			return( -2 );
		}
	/* Signature:  void (*onfull)( libandria4_FILE_substream**,  libandria4_FILE_substream_vtable*, void* (FILE*) ) */
#define libandria4_FILE_tracker_initialize_ONFULL( ctr_ptr, vtab_ptr, f_p ) \
	( ( (vtab_ptr) != &lib4_FILE_vtab ? return( -3 ) : 1 ) \
		, ( (f_p) != f ? return( -4 ) : 1 ) \
		, return( 2 ) )
		
		static void *badalloc_data = (void*)0;
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYINIT(
			libandria4_FILE_tracker, *trk, &lib4_FILE_vtab, (void*)f,
			libandria4_FILE_tracker_initialize_ONFULL,
			libandria4_FILE_tracker_initialize_badalloc, badalloc_data );
		
		return( 1 );
	}
	
	return( -1 );
}
	/* The "event handlers" need to be set. */
int libandria4_FILE_tracker_redirect( libandria4_FILE_tracker *tracker, libandria4_FILE_tracker *donor )
{
	if( tracker & donor )
	{
		/* Switch to LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE( FILE_tracker, redir_var,  on_failattend, on_failneglect, on_redir )? */
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYSET(
			??? libandria4_FILE_tracker, var, valptr, ???
					/* These five need to actually be set to something. */
				LIBANDRIA4_NULL_MACRO /* failneglect */, LIBANDRIA4_NULL_MACRO /* failattend */,
					/* These two are successes. */
				LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO,
				LIBANDRIA4_NULL_MACRO /* ondead */
		);
		
		return( 1 );
	}
	
	return( -1 );
}
	/* This looks complete? */
	/* Complete, but pointless. Build some more-proper wrappers. */
int libandria4_FILE_tracker_apply
(
	libandria4_FILE_tracker *trk,
	int *res,
	
		/* The argument in the va_list* will be the relevant FILE*. */
	int (*operation)( void*, va_list* ),
	void *op_data,
	
		/* The argument in the va_list* will be the provided */
		/*  libandria4_FILE_tracker{} BY VALUE. */
	int (*on_null)( void*, va_list* ),
	void *null_data
)
{
	if( trk && operation && on_null )
	{
			/* The value of "a" just doesn't matter. */
		int a;
		libandria4_op_indirfunc_int_voidp_valist_data functor1, functor2;
		int (*LIBANDRIA4_OP_runable1)( void *dat_, ... ) =
			&libandria4_op_indirfunc_int_voidp;
		int (*LIBANDRIA4_OP_runable2)( void *dat_, ... ) =
			&libandria4_op_indirfunc_int_voidp;
		void *LIBANDRIA4_OP_runabledata1, *LIBANDRIA4_OP_runabledata2;
		
		LIBANDRIA4_OP_runabledata1 = (void*)&functor1;
		functor1.func = operation;
		functor1.data = op_data;
		
		LIBANDRIA4_OP_runabledata2 = (void*)&functor2;
		functor2.func = on_null;
		functor2.data = null_data;
		
		
		int res_ =
			LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY(
				*trk,
					LIBANDRIA4_OP_RUNifABLE1_ELSEa,
					LIBANDRIA4_OP_RUNifABLE2_ELSEa
			);
		if( res )
		{
			*res = res_;
		}
		
		
		return( 1 );
	}
	
	return( -1 );
}
	/* Is this complete? Are those LIBANDRIA4_NULL_MACRO references both appropriate? */
int libandria4_FILE_tracker_deinitialize
(
	libandria4_FILE_tracker *trk,
	
	/* Both of these function pointers can be null if desired. */
		/* Just ignore the va_list*, there won't be any provided arguments. */
	void (*on_failedrelease)( void*, va_list* ),
	void *failedrelease_data
)
{
	if( trk )
	{
			/* The value of "a" just doesn't matter. */
		int a;
		libandria4_op_indirfunc_int_voidp_valist_data functor1, functor2;
		int (*LIBANDRIA4_OP_runable1)( void *dat_, ... ) =
			&libandria4_op_indirfunc_int_voidp;
		int (*LIBANDRIA4_OP_runable2)( void *dat_, ... ) =
			&libandria4_op_indirfunc_int_voidp;
		void *LIBANDRIA4_OP_runabledata1, *LIBANDRIA4_OP_runabledata2;
		
		LIBANDRIA4_OP_runabledata1 = (void*)&functor1;
		functor1.func = on_failedrelease;
		functor1.data = failedrelease_data;
		
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYDEINIT
		(
			libandria4_FILE_tracker, *trk,
				LIBANDRIA4_OP_RUNifABLE1_ELSEa, /* failneglect */
				LIBANDRIA4_NULL_MACRO, /* succneglect */
				LIBANDRIA4_NULL_MACRO /* ondead */
		);
		
		return( 1 );
	}
	
	return( -1 );
}
