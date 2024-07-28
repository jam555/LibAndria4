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



	/* Pre-defs, because some of the functions need to see these names. */
static libandria4_FILE_substream_vtable lib4_FILE_vtab;



/* Virtual-table implementations below. */

static void libandria4_FILE_tracker_commonreferencing( uintptr_t *count )
{
	if( !count )
	{
		/* TODO: add logging. */
	}
	
		/* Just do nothing. */
	return;
}

static int libandria4_FILE_tracker_feof( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	return( feof( (FILE*)f ) );
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

	/* This is not directly involved in redirections. */
	/* Note: need a "permanently EOF" stream to redirect to! */
static void libandria4_FILE_tracker_commonclose( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
		
	} else {
		
		int res = fclose( (FILE*)f );
		if( res == 0 || res == EOF )
		{
				/* Good state, do nothing else... unless we add logging. */
			return;
			
		} else {
			
			/* TODO: add logging. */
		}
	}
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
