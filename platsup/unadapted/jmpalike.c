/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2025 Jared A. Maddox

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

/* Based on https://nullprogram.com/blog/2023/02/12/ , visited on 11/Apr/2025. */
/*  Look in the references directory for a saved copy of the page. */

#include "support.h"
#include "jmpalike.h"



#if \
	LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
	LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LLVM )
	
	#if \
		( LIBANDRIA4_TARGETPROCESSOR0 != LIBANDRIA4_PROCESSOR0_ISA_x86 ) && \
			( LIBANDRIA4_CELLTYPE_REGSIZE == 8 )
		#include "jumps/x86gnu64.c"
	#endif
	
#else
	
	#error "jmpalike.c doesn't recognize this compiler yet.\n"
	
#endif



LIBANDRIA4_SETJMPATTR
intptr_t libandria4_jmpalike_setcore( libandria4_jmpalike_buf buf )
{
	intptr_t ret;
	
	ret = jmpalike_setcore( buf );
	if( ret == 0 )
	{
		/* Hide the real value of these three with an xor. */
		buf[ 0 ] = LIBANDRIA4_MASK_PTR( buf[ 0 ] ); /* rip. */
		buf[ 1 ] = LIBANDRIA4_MASK_PTR( buf[ 1 ] ); /* rsp. */
		buf[ 2 ] = LIBANDRIA4_MASK_PTR( buf[ 2 ] ); /* rbp. */
	}
	
	return( ret );
}
void libandria4_jmpalike_setothers( libandria4_jmpalike_buf buf )
{
	jmpalike_setothers( buf );
}

LIBANDRIA4_SETJMPATTR
intptr_t libandria4_jmpalike_set( libandria4_jmpalike_buf buf )
{
	intptr_t ret;
	
	jmpalike_setothers( buf );
	ret = jmpalike_setcore( buf );
	if( ret == 0 )
	{
		/* Hide the real value of these three with an xor. */
		buf[ 0 ] = LIBANDRIA4_MASK_PTR( buf[ 0 ] ); /* rip. */
		buf[ 1 ] = LIBANDRIA4_MASK_PTR( buf[ 1 ] ); /* rsp. */
		buf[ 2 ] = LIBANDRIA4_MASK_PTR( buf[ 2 ] ); /* rbp. */
	}
	
	return( ret );
}
int libandria4_jmpalike_jmp( libandria4_jmpalike_buf buf, intptr_t ret )
{
	if( !buf )
	{
		return( -1 );
	}
	if( !ret )
	{
		return( -2 );
	}
	
	/* The real value of these three were hidden with an xor. */
	buf[ 0 ] = LIBANDRIA4_MASK_PTR( buf[ 0 ] ); /* rip. */
	buf[ 1 ] = LIBANDRIA4_MASK_PTR( buf[ 1 ] ); /* rsp. */
	buf[ 2 ] = LIBANDRIA4_MASK_PTR( buf[ 2 ] ); /* rbp. */
	
	jmpalike_loadothers( tmp );
	jmpalike_jmpcore( tmp, ret );
}
int libandria4_jmpalike_rebasestack
(
	libandria4_jmpalike_buf buf,
	  void *oldref, void *newref
)
{
	intmax_t diff = (intmax_t)newref - (intmax_t)oldref;
	
	if( !buf )
	{
		return( -1 );
	}
	
	buf[ 1 ] = LIBANDRIA4_MASK_PTR( buf[ 1 ] ); /* rsp. */
	buf[ 2 ] = LIBANDRIA4_MASK_PTR( buf[ 2 ] ); /* rbp. */
	
	buf[ 1 ] += diff;
	buf[ 2 ] += diff;
	
	buf[ 1 ] = LIBANDRIA4_MASK_PTR( buf[ 1 ] ); /* rsp. */
	buf[ 2 ] = LIBANDRIA4_MASK_PTR( buf[ 2 ] ); /* rbp. */
	
	return( 1 );
}



	/* Just establish some named values. */
enum
{
	coro_WORKING = 1,
	coro_DONE
};

void libandria_coro1_yield( libandria4_coro1_buf *coro )
{
		/* Store the current state... */
	if( !libandria4_jmpalike_set( coro->callee ) )
	{
			/* ... and then jump to the next context. */
		libandria4_jmpalike_jmp( coro->caller,  coro_WORKING );
	}
	/* ... unless we're resuming, in which case just return. */
}

int libandria4_coro1_next( libandria4_coro1_buf *coro )
{
	intptr_t ret = libandria4_jmpalike_set( coro->caller );
	if( ret != 0 )
	{
		libandria4_jmpalike_jmp( coro->callee, coro_WORKING );
	} else {
		return( ret == coro_WORKING );
	}
}

void libandria4_coro1_start
(
	libandria4_coro1_buf *coro,
	
	func fun,
	void *arg,
	libandria4_coro1_start *st_params,
	
	void *dummy1,
	void *dummy2
)
{
	/* Surpress "unused argument" warnings. */
	(void)dummy1;
	(void)dummy2;
	
	/* Save the arguments to our impending stack-frame. */
	st_params->coro = coro;
	st_params->fun = fun;
	st_params->arg = arg;
	st_params->thisptr = st_params;
	LIBANDRIA4_PLATSUPP_PROC_GETSP( st_params->old_sp );
	LIBANDRIA4_PLATSUPP_PROC_GETFP( st_params->old_fp );
	
	LIBANDRIA4_SIGNAL_FENCE(  );
	#if 1
		/* TODO: Verify this! My code doesn't actually match the original! */
		
			/* st_params should point at the lowest address of the start */
			/*  structure (at least on x86), so ALMOST the correct stack */
			/*  pointer, and we need this for later anyways. */
		LIBANDRIA4_PLATSUPP_PROC_SETSP( st_params );
			/* This breaks all locals, including st_params... */
		LIBANDRIA4_PLATSUPP_PROC_SETFP( st_params + FRAME_SZ  );
			/* ... so we read st_params back from $fp. */
		LIBANDRIA4_PLATSUPP_PROC_GETSP( st_params );
			/* Adjust 0 to the value we actually want! It's important to not */
			/*  allow pushes to overwrite our structure! */
		LIBANDRIA4_PLATSUPP_PROC_SETSP( st_params - 0 );
	#else
		#error "Only a single call convention is currently supported.\n"
	#endif
	LIBANDRIA4_SIGNAL_FENCE(  );
	
	//and now we read our params.
	if( !libandria4_jmpalike_set( st_params->coro->callee ) )
	{
		LIBANDRIA4_PLATSUPP_PROC_SETSP( st_params->old_sp );
		LIBANDRIA4_PLATSUPP_PROC_SETFP( st_params->old_fp );
		return;
	}
	
	( *( st_params->fun ) )( st_params->arg );
	libandria4_jmpalike_jmp( st_params->coro->caller, coro_DONE );
}

/* Add the coroutine stuff! */
/* Also, figure out how to deal with the shadow-stack. */

