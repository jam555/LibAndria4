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



#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

#include "mutablestreams.h"



	/* Pre-defs, because some of the functions need to see these names. */
static libandria4_FILE_substream_vtable lib4_FILE_EOFvtab;

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

static int libandria4_FILE_tracker_deathlessEOFfeof( void *f )
{
	if( !f )
	{
		/* TODO: add logging. */
	}
	
	return( LIBANDRIA4_COMMONIOVALS_EOF );
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
