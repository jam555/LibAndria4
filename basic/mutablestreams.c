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

	/* Pre-defs, because some of the functions need to see these names. */
static libandria4_FILE_substream_vtable
	lib4_FILE_EOFvtab, lib4_FILE_vtab;



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










/* Virtual-table implementations below. */

/* ??? Warning! Go back through and add code to check for null pointers! ??? */

static void libandria4_FILE_tracker_commonreferencing( uintptr_t *count )
{
	if( !count )
	{
		/* TODO: add logging. */
	}
	
		/* Just do nothing. */
	return;
}
	/* These are only used for stuff that MUST NOT participate in normal */
	/*  memory allocationsw, because it's allocated during compile-time */
	/*  instead of run-time. */
static void libandria4_FILE_tracker_deathlessattending( uintptr_t *count )
{
	if( count )
	{
		--( *count );
		
	} else {
		
		/* TODO: add logging. */
	}
}
static void libandria4_FILE_tracker_deathlessneglecting( uintptr_t *count )
{
	if( count )
	{
		++( *count );
		
	} else {
		
		/* TODO: add logging. */
	}
}

static int libandria4_FILE_tracker_feof( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	return( feof( (FILE*)f ) );
}
static int libandria4_FILE_tracker_deathlessEOFfeof( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	return( EOF );
}
static libandria4_commonio_mayerr2 libandria4_FILE_tracker_geterror( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	int tmperr = errno;
	errno = 0;
		int res = ferror( (FILE*)f );
		if( errno != 0 )
		{
			if( res == EOF )
			{
				res = errno;
				
			} else if( res != errno )
			{
				/* TODO: Add an auxiliary reporting method here. */
			}
		}
	errno = tmperr;
	
	if( res )
	{
		LIBANDRIA4_NEWSTREAMS_RESULT2_RETURNJUST( res );
	}
	
	LIBANDRIA4_NEWSTREAMS_RESULT2_RETURNNOTHING();
}
static libandria4_newstreams_result2 libandria4_FILE_tracker_deathlessEOFgeterror( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	LIBANDRIA4_NEWSTREAMS_RESULT2_RETURNJUST(
		LIBANDRIA4_COMMONIOVALS_EOF
	);
}
static libandria4_newstreams_bituplic2 libandria4_FILE_tracker_clearerr( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	libandria4_newstreams_bituplic2 ret =
		LIBANDRIA4_MONAD_BITUP2_BUILDJUSTSTREAM(
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	
	int tmperr = errno;
	errno = 0;
	clearerr( (FILE*)f );
	if( errno != 0 )
	{
		int tmp = errno;
		ret =
			LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTBOTH(
				tmp,
				LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
			);
	}
	errno = tmperr;
	
	return( ret );
}
static libandria4_newstreams_bituplic2 libandria4_FILE_tracker_deathlessEOFclearerr( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTBOTH(
			LIBANDRIA4_COMMONIOVALS_EOF,
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
}

static libandria4_newstreams_bituplic4 libandria4_FILE_tracker_tell( void* f, int refpt )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	if( refpt != SEEK_SET )
	{
		LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR(
				LIBANDRIA4_COMMONIOVALS_ERR_BADARGS /* libandria4_newstreams_err */
			),
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	}
	
	long pos = ftell( (FILE*)f );
	if( pos >= 0 )
	{
		if( pos > INTMAX_MAX )
		{
			/* But how??? */
			
			LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
				LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR(
					LIBANDRIA4_COMMONIOVALS_ERR_OVERFLOW /* libandria4_newstreams_err */
				),
				LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
			);
		}
		
		LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDINT( pos ), /* intmax_t */
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
		
	} else {
		
		int tmp = errno;
		errno = 0;
		
		LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR( tmp ), /* libandria4_newstreams_err */
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	}
}
static libandria4_newstreams_bituplic4 libandria4_FILE_tracker_deathlessEOFtell( void* f, int refpt )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR(
				LIBANDRIA4_COMMONIOVALS_EOF
			), /* libandria4_newstreams_err */
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
}
static libandria4_newstreams_bituplic4 libandria4_FILE_tracker_seek( void* f, intmax_t off, int refpt )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	if( off > LONG_MAX )
	{
		LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR(
				LIBANDRIA4_COMMONIOVALS_ERR_OVERFLOW /* libandria4_newstreams_err */
			),
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	}
	switch( refpt )
	{
		case SEEK_SET:   case SEEK_CUR:   case SEEK_END:
				/* Same handling for all three. */
			break;
		default:
			{
				LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
					LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR(
						LIBANDRIA4_COMMONIOVALS_ERR_BADARGS /* libandria4_newstreams_err */
					),
					LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
				);
			}
	}
	
	int res = fseek( (FILE*)f, off, refpt );
	if( res != 0 )
	{
		LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR( res ), /* libandria4_newstreams_err */
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
		
	} else {
		
		LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDINT( pos ), /* intmax_t */
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	}
}
static libandria4_newstreams_bituplic4 libandria4_FILE_tracker_deathlessEOFseek( void* f, intmax_t off, int refpt )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR(
				LIBANDRIA4_COMMONIOVALS_EOF
			), /* libandria4_newstreams_err */
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
}

static libandria4_newstreams_bituplic2 libandria4_FILE_tracker_rewind( void* f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	libandria4_newstreams_bituplic2 ret =
		LIBANDRIA4_MONAD_BITUP2_BUILDJUSTSTREAM(
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	
	int tmp = errno;
	errno = 0;
	rewind( (FILE*)f );
	if( errno != 0 )
	{
		int tmp = errno;
		ret =
			LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTBOTH(
				tmp,
				LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
			);
	}
	errno = tmp;
	
	return( ret );
}
static libandria4_newstreams_bituplic2 libandria4_FILE_tracker_deathlessEOFrewind( void* f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTBOTH(
			LIBANDRIA4_COMMONIOVALS_EOF,
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
}

static libandria4_newstreams_bituplic2 libandria4_FILE_tracker_flush( void* f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	libandria4_newstreams_bituplic2 ret =
		LIBANDRIA4_MONAD_BITUP2_BUILDJUSTSTREAM(
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	
	int res = fflush( (FILE*)f );
	if( res != 0 )
	{
		if( res != EOF )
		{
			/* TODO: Add some extra reporting for "res". */
			
			ret =
				LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTBOTH(
					LIBANDRIA4_COMMONIOVALS_ERR_GENERIC,
					LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
				);
			
		} else {
			
			ret =
				LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTBOTH(
					LIBANDRIA4_COMMONIOVALS_EOF,
					LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
				);
		}
	}
	
	return( ret );
}
static libandria4_newstreams_bituplic2 libandria4_FILE_tracker_deathlessEOFflush( void* f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTBOTH(
			LIBANDRIA4_COMMONIOVALS_EOF,
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
}

static libandria4_newstreams_bituplic3 libandria4_FILE_tracker_getc( void* f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	libandria4_newstreams_bituplic3 ret =
		LIBANDRIA4_MONAD_BITUP3_BUILDJUSTSTREAM(
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	
	int res = fgetc( (FILE*)f );
	if( res == EOF )
	{
		ret =
			LIBANDRIA4_NEWSTREAMS_BITUP3_BUILDJUSTBOTH(
				LIBANDRIA4_NEWSTREAMS_RESULT3_BUILDERR(
					LIBANDRIA4_COMMONIOVALS_EOF
				),
				LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
			);
		
	} else {
		
		ret =
			LIBANDRIA4_NEWSTREAMS_BITUP3_BUILDJUSTBOTH(
				LIBANDRIA4_NEWSTREAMS_RESULT3_BUILDCHAR( res ),
				LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
			);
	}
	
	return( ret );
}
static libandria4_newstreams_bituplic3 libandria4_FILE_tracker_deathlessEOFgetc( void* f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	LIBANDRIA4_NEWSTREAMS_BITUP3_RETURNJUSTBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT3_BUILDERR(
				LIBANDRIA4_COMMONIOVALS_EOF
			),
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
}

static libandria4_newstreams_bituplic1 libandria4_FILE_tracker_putc( void* f, char ch )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	libandria4_newstreams_bituplic1 ret =
		LIBANDRIA4_MONAD_BITUP1_BUILDJUSTSTREAM(
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
	
	int res = fputc( ch, (FILE*)f );
	if( res == EOF )
	{
		ret =
			LIBANDRIA4_NEWSTREAMS_BITUP1_BUILDJUSTBOTH(
				LIBANDRIA4_NEWSTREAMS_RESULT1_BUILDERR(
					LIBANDRIA4_COMMONIOVALS_EOF
				),
				LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
			);
		
	} else {
		
		ret =
			LIBANDRIA4_NEWSTREAMS_BITUP1_BUILDJUSTBOTH(
				LIBANDRIA4_NEWSTREAMS_RESULT1_BUILDSIZET( 1 ),
				LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
			);
	}
	
	return( ret );
}
static libandria4_newstreams_bituplic1 libandria4_FILE_tracker_deathlessEOFputc( void* f, char ch )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	LIBANDRIA4_NEWSTREAMS_BITUP1_BUILDJUSTBOTH(
			LIBANDRIA4_NEWSTREAMS_RESULT1_BUILDERR(
				LIBANDRIA4_COMMONIOVALS_EOF
			),
			LIBANDRIA4_FILE_REDIRECTION_TOCURRENT()
		);
}

	/* This is not directly involved in redirections. */
	/* Note: need a "permanently EOF" stream to redirect to! */
static void libandria4_FILE_tracker_commonclose( void *f )
{
	/* TODO: add logging everywhere ??? appears. */
	
	if( !f )
	{
		???
	}
	
	int res = fclose( (FILE*)f );
	if( res != EOF )
	{
		???
		
	} else {
		
		???
	}
}
static void libandria4_FILE_tracker_deathlessclose( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
		/* There's nothing to do. */
	return;
}


static libandria4_FILE_substream_vtable
	lib4_FILE_vtab =
	{
		&libandria4_FILE_tracker_commonreferencing,
		&libandria4_FILE_tracker_commonreferencing,
		
		&libandria4_FILE_tracker_feof,
			/* If there isn't an error, then it MIGHT still indicate eof. */
		&libandria4_FILE_tracker_geterror,
		
		&libandria4_FILE_tracker_clearerr,
		
		
		&libandria4_FILE_tracker_tell,
		&libandria4_FILE_tracker_seek,
		
		&libandria4_FILE_tracker_rewind,
		
		&libandria4_FILE_tracker_flush,
		
		
		&libandria4_FILE_tracker_getc,
		&libandria4_FILE_tracker_putc,
		
		&libandria4_FILE_tracker_commonclose
	};



static libandria4_FILE_substream_vtable
	lib4_FILE_EOFvtab =
	{
		&libandria4_FILE_tracker_deathlessattending,
		&libandria4_FILE_tracker_deathlessneglecting,
	
		&libandria4_FILE_tracker_deathlessEOFfeof,
			/* If there isn't an error, then it MIGHT still indicate eof. */
		&libandria4_FILE_tracker_deathlessEOFgeterror,
		
		&libandria4_FILE_tracker_deathlessEOFclearerr,
		
		
		&libandria4_FILE_tracker_deathlessEOFtell,
		&libandria4_FILE_tracker_deathlessEOFseek,
		
		&libandria4_FILE_tracker_deathlessEOFrewind,
		
		&libandria4_FILE_tracker_deathlessEOFflush,
		
		
		&libandria4_FILE_tracker_deathlessEOFgetc,
		&libandria4_FILE_tracker_deathlessEOFputc,
		
		&libandria4_FILE_tracker_deathlessclose
	};
libandria4_FILE_substream lib4_FILE_EOFsubstream =
	{
			/* ref_count */
		1,
			/* auxiliary, currently FILE*, should be the virtual table. */
		(void*)0,
			/* val, should be FILE*, currently the vtab. */
		(libandria4_FILE_substream_vtable*)&lib4_FILE_EOFvtab
	};


/*  */


	struct libandria4_FILE_substream_vtable
	{
		void (*attending)( uintptr_t *count );
		void (*neglecting)( uintptr_t *count );
		
		...
		
			/* See LIBANDRIA4_NEWSTREAMS_ONDIE() for the cannonical approach to */
			/*  this return value... but feel free to do otherwise if it makes */
			/*  sense for your case. */
		void (*close)( void* /* FILE* */ );
	};

	#define libandria4_mutastream_2stream_GENERICONV_ONEMPTY() \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE );
	#define libandria4_mutastream_2stream_GENERICONV_ONERR( err ) \
		flags |= 1; err_val = (err);
	#define libandria4_mutastream_2stream_GENERICONV_ONREDIR( redir ) \
		flags |= 2; redir_val = (redir);
	#define libandria4_mutastream_2stream_GENERICONV_VALID( vtab, vptr ) \
		( vt = (vtab), vf = (vptr) )
#define libandria4_mutastream_2stream_GENERICONV( func ) \
	if( strm ) { int a = 0; libandria4_FILE_substream_vtable *vt; void *vf; \
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY( strm->trk,  libandria4_mutastream_2stream_GENERICONV_VALID, LIBANDRIA4_OP_SETaTO1 ); \
		if( a || !vt ) { LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		else if( vt-> func ) { libandria4_newstreams_bituplic2 res = (vt-> func )( vf ); \
			libandria4_newstreams_err err_val; libandria4_FILE_redirection redir_val; int flag = 0; \
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( res, \
				libandria4_mutastream_2stream_GENERICONV_ONERR, \
				libandria4_mutastream_2stream_GENERICONV_ONREDIR, \
				libandria4_mutastream_2stream_GENERICONV_ONEMPTY ); \
			if( flags & 2 ) { \
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE( strm->trk, redir_val, \
						/* TODO: Should add logging to this. */ \
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */ \
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */ \
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */ \
				); } \
			if( flags & 1 ) { LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( err_val ); } \
			else { LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( 0 ); } } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );

libandria4_commonio_eithgeneric libandria4_mutastream_2stream_flush( libandria4_commonio_handle *strm )
{
	libandria4_mutastream_2stream_GENERICONV( flush );
}

libandria4_commonio_eithbyte libandria4_mutastream_2stream_getc( libandria4_commonio_handle *strm )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY(
			strm->trk,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->get_c )
		{
			libandria4_newstreams_bituplic3 res = (vt->get_c)( vf );
			
			libandria4_commonio_eithchar2 res2;
			libandria4_FILE_redirection redir_val;
			int flag = 0;
			
#define libandria4_mutastream_2stream_getc_ONEMPTY() \
	LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE );
#define libandria4_mutastream_2stream_getc_ONVAL( val ) \
	flags |= 1; res2 = (val);
#define libandria4_mutastream_2stream_getc_ONREDIR( redir ) \
	flags |= 2; redir_val = (redir);
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
				res,
				
				libandria4_mutastream_2stream_getc_ONVAL,
				libandria4_mutastream_2stream_getc_ONREDIR,
				libandria4_mutastream_2stream_getc_ONEMPTY
			);
				
			if( flags & 2 )
			{
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE(
					strm->trk, redir_val,
					
						/* TODO: Should add logging to this. */
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */
				);
			}
			
			if( flags & 1 )
			{
				char a;
				libandria4_commonio_perr b;
				
#define libandria4_mutastream_2stream_getc_ONINT( c ) \
	a = (c); if( a <= LIBANDRIA4_COMMONIO_BYTE_MAX ) { \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETBYTE( a ); } else { \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ); }
#define libandria4_mutastream_2stream_getc_ONERR( err ) \
	b = (err); if( B <= LIBANDRIA4_COMMONIO_ERR_MAX ) { \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( b ); } else { \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ); }
				LIBANDRIA4_MONAD_EITHER_BODYMATCH(
					res2,
						libandria4_mutastream_2stream_getc_ONINT,
						libandria4_mutastream_2stream_getc_ONERR
				);
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_ungetc( libandria4_commonio_handle*, libandria4_commonio_byte );
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_putc( libandria4_commonio_handle *strm, libandria4_commonio_byte val )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY(
			strm->trk,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->put_c )
		{
			libandria4_newstreams_bituplic2 res = (vt->put_c)( vf, val );
			
			libandria4_newstreams_err err_val;
			libandria4_FILE_redirection redir_val;
			int flag = 0;
			
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
				res,
				
				libandria4_mutastream_2stream_GENERICONV_ONERR,
				libandria4_mutastream_2stream_GENERICONV_ONREDIR,
				libandria4_mutastream_2stream_GENERICONV_ONEMPTY
			);
				
			if( flags & 2 )
			{
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE(
					strm->trk, redir_val,
					
						/* TODO: Should add logging to this. */
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */
				);
			}
			
			if( flags & 1 )
			{
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( err_val );
				
			} else {
				
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( 0 );
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}

/* Note: gets_s() and puts_s() should be implemented by simple wrapper from */
/*  streams.c for now. They can be properly built later if justified. The signatures are as follows: */
	/*
		libandria4_commonio_eithgeneric
			libandria4_mutastream_2stream_gets_s
			(
				libandria4_commonio_handle *strm,
				
				libandria4_commonio_byte *arr,
				size_t len
			);
	*/
	/*
		libandria4_commonio_eithgeneric
			libandria4_mutastream_2stream_puts_s
			(
				libandria4_commonio_handle *strm,
				
				libandria4_commonio_byte *arr,
				size_t len
			);
	*/

libandria4_commonio_eithlong libandria4_mutastream_2stream_tell( libandria4_commonio_handle *strm )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY(
			strm->trk,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->tell )
		{
			libandria4_newstreams_bituplic4 res = (vt->tell)( vf, int /* Reference point. */ );
			
			libandria4_commonio_eithintmax2 res2;
			libandria4_FILE_redirection redir_val;
			int flag = 0;
			
#define libandria4_mutastream_2stream_tell_ONEMPTY() \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE );
#define libandria4_mutastream_2stream_tell_ONVAL( val ) \
	flags |= 1; res2 = (val);
#define libandria4_mutastream_2stream_tell_ONREDIR( redir ) \
	flags |= 2; redir_val = (redir);
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
				res,
				
				libandria4_mutastream_2stream_tell_ONVAL,
				libandria4_mutastream_2stream_tell_ONREDIR,
				libandria4_mutastream_2stream_tell_ONEMPTY
			);
				
			if( flags & 2 )
			{
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE(
					strm->trk, redir_val,
					
						/* TODO: Should add logging to this. */
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */
				);
			}
			
			if( flags & 1 )
			{
				intmax_t a;
				libandria4_commonio_perr b;
				
#define libandria4_mutastream_2stream_tell_ONINT( i ) \
	a = (i); if( a <= LONG_MAX ) { \
		LIBANDRIA4_COMMONIO_EITHLONG_RETBYTE( a ); } else { \
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ); }
#define libandria4_mutastream_2stream_tell_ONERR( err ) \
	b = (err); if( B <= LIBANDRIA4_COMMONIO_ERR_MAX ) { \
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( b ); } else { \
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ); }
				LIBANDRIA4_MONAD_EITHER_BODYMATCH(
					res2,
						libandria4_mutastream_2stream_tell_ONINT,
						libandria4_mutastream_2stream_tell_ONERR
				);
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_seek( libandria4_commonio_handle *strm, long dist, int ori )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY(
			strm->trk,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->seek )
		{
			libandria4_newstreams_bituplic2 res = (vt->seek)( vf, dist, ori );
			
			libandria4_newstreams_err err_val;
			libandria4_FILE_redirection redir_val;
			int flag = 0;
			
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
				res,
				
				libandria4_mutastream_2stream_GENERICONV_ONERR,
				libandria4_mutastream_2stream_GENERICONV_ONREDIR,
				libandria4_mutastream_2stream_GENERICONV_ONEMPTY
			);
				
			if( flags & 2 )
			{
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE(
					strm->trk, redir_val,
					
						/* TODO: Should add logging to this. */
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */
				);
			}
			
			if( flags & 1 )
			{
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( err_val );
				
			} else {
				
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( 0 );
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_rewind( libandria4_commonio_handle *strm )
{
	libandria4_mutastream_2stream_GENERICONV( rewind );
}

libandria4_commonio_eithgeneric libandria4_mutastream_2stream_clearerr( libandria4_commonio_handle *strm )
{
	libandria4_mutastream_2stream_GENERICONV( clear_err );
}
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_eof( libandria4_commonio_handle *strm )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY(
			strm->trk,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->is_eof )
		{
			int res = (vt->is_eof)( vf );
			
			if( res )
			{
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( LIBANDRIA4_COMMONIOVALS_EOF );
				
			} else {
				
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED );
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
	/* If there isn't an error, then it MIGHT still indicate eof. */
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_error( libandria4_commonio_handle *strm )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY(
			strm->trk,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->get_error )
		{
			libandria4_newstreams_result2 res = (vt->get_error)( vf );
			
			LIBANDRIA4_MONAD_MAYBE_BODYMATCH(
				res,
					LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE,
					LIBANDRIA4_NULL_MACRO
			);
			
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED );
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}

libandria4_commonio_eithgeneric libandria4_mutastream_2stream_close( libandria4_commonio_handle* );
	typedef struct libandria4_mutastream_2stream
	{
		libandria4_commonio_handle handle;
		libandria4_commonio_istream_ungetwrapper_vtable uget_host;
		libandria4_FILE_substream_vtable impl;
		
		libandria4_FILE_substream_vtable *muta;
		
	} libandria4_mutastream_2stream;

typedef struct libandria4_commonio_istream_ungetwrapper_vtable
{
	libandria4_commonio_istream here;
	libandria4_commonio_istream *is;
	
	libandria4_commonio_maybyte buffer;
	
} libandria4_commonio_istream_ungetwrapper;
typedef struct libandria4_commonio_handle
{
	union
	{
		libandria4_commonio_handle_vtable *hand;
		libandria4_commonio_istream_vtable *istr;
		libandria4_commonio_ostream_vtable *ostr;
		libandria4_commonio_seekable_vtable *seek;
		libandria4_commonio_errorable_vtable *err;
		
	} vtab;
	libandria4_commonio_handle_vtabtype dispatch;
	
} libandria4_commonio_handle;
