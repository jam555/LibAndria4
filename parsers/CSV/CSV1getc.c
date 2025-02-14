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



#include "CSV1.h"



/* CSV1.c: A parser for simple comma-separated-value files. */
/* At the base level, values are separated by commas. */
	/* The values themselves may be wrapped by double-quotes. */
		/* If a comma or whitespace is part of the value, then the value */
		/*  should/must be so wrapped. */
		/* If a double-quote is to be part of a value, then the value MUST */
		/*  be double-quote wrapped, and the contained double-quotes must be */
		/*  encoded as DOUBLE souble-quotes. */


	/* For libandria4_common_monadicchar8{}. */
#include "../../basic/commonerrvals.h"
#include "../../basic/commontypes.h"
#include "../../basic/simpleops.h"
#include "../../basic/monads.h"



static libandria4_cts_closure failfunc;

static libandria4_cts_innerreturn_data iret_d =
	{ 0, &libandria4_cts_innerreturn_returnstop, 0 };

static libandria4_cts_closure
	failfunc = LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_cts_framefunc_stoprun,
		(void*)&failfunc ),
	retfunc = LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_cts_innerreturn,
		(void*)&iret_d ),
	popchar = LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_parser_CSV_CSV1_popchar,
		(void*)&iret_d );



/* These two push two unsigned chars onto stack[ 1 ] (so the second stack); */
/*  the top character is a tag (same as *_getc(), and both functions expect */
/*  a return closure on top of stack[ 0 ]. */
	static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_notstring_inner
	(
		libandria4_cts_context *ctx, void *data_
	)
	{
		if( ctx && data_ )
		{
			libandria4_cts_closure
				acc = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_notstring_inner,
					data_ ),
				getc = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc,
					data_ );
			
			libandria4_parser_CSV_CSV1_file *data =
				(libandria4_parser_CSV_CSV1_file*)data_;
			if( libandria4_parser_CSV_CSV1_validate( data ) )
			{
				return( failfunc );
			}
			
			unsigned char c, type;
			int res = 0;
			
			
			/* Get the character values. */
			res = libandria4_cts_pop_uchar( ctx, 1,  &type );
			if( !res )
			{
				return( failfunc );
			}
			res = libandria4_cts_pop_uchar( ctx, 1,  &c );
			if( !res )
			{
				return( failfunc );
			}
			
			
			/* Dispatch per getc category. */
			switch( type )
			{
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS:
					break;
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SEMIEOF:
						/* Queue acc. */
					res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
					if( !res )
					{
						return( failfunc );
					}
					
					return( getc );
					
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF:
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL:
				default:
					/* Should be logging here. */
					
					return( failfunc );
			}
			
			
			/* Success... OR IS IT??? */
			libandria4_parser_CSV_CSV1_sortchar_categories cat =
				libandria4_parser_CSV_CSV1_sortchar( data, c );
			switch( cat )
			{
				/* "Value breakers." */
				case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
					/* Fall through. */
				/* Plain success. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
					break;
				case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
					type = LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL;
					break;
					
				/* Errors. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
				case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
				default:
					return( failfunc );
			}
			
			
			/* Push. */
			res = libandria4_cts_push2_uchar( ctx, 1,  c );
			if( !res )
			{
				return( failfunc );
			}
			res = libandria4_cts_push2_uchar( ctx, 1,  type );
			if( !res )
			{
				return( failfunc );
			}
			
			
			return( retfunc );
		}
		
		return( failfunc );
	}
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_notstring
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_notstring_inner,
				data_ ),
			getc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc,
				data_ );
		
		if( libandria4_parser_CSV_CSV1_validate( data_ ) )
		{
			return( failfunc );
		}
		
		int res;
		
		/* Schedule interpreter. */
		res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
		if( !res )
		{
			return( failfunc );
		}
		
			/* Fetch unprocessed character. */
		return( getc );
	}
	
	return( failfunc );
}



/* Implementation functions for libandria4_parser_CSV_CSV1_getc_string(). */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_dquote
(
	libandria4_cts_context *ctx, void *data
);
static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_cescape
(
	libandria4_cts_context *ctx, void *data
);



	static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_cescape
	(
		libandria4_cts_context *ctx, void *data_
	)
	{
		if( ctx && data_ )
		{
			libandria4_cts_closure
				acc = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_cescape,
					data_ ),
				getc = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string,
					data_ );
			
			libandria4_parser_CSV_CSV1_file *data =
				(libandria4_parser_CSV_CSV1_file*)data_;
			if( libandria4_parser_CSV_CSV1_validate( data ) )
			{
				return( failfunc );
			}
			
			unsigned char c, type;
			int res = 0;
			
			
			/* Get the character values. */
			res = libandria4_cts_pop_uchar( ctx, 1,  &type );
			if( !res )
			{
				return( failfunc );
			}
			res = libandria4_cts_pop_uchar( ctx, 1,  &c );
			if( !res )
			{
				return( failfunc );
			}
			
			
			/* Dispatch per getc category. */
			switch( type )
			{
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS:
					break;
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SEMIEOF:
						/* Queue acc. */
					res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
					if( !res )
					{
						return( failfunc );
					}
					
					return( getc );
					
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF:
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL:
				default:
					/* Should be logging here. */
					
					return( failfunc );
			}
			
			
			/* Dispatch per character. */
			switch( c )
			{
				/* BEWARE! The values assigned below are ASCII, */
				/*  this could be a problem for someone. If you */
				/*  are that someone, then look at swapping these */
				/*  hard-coded values for macros from */
					/* /text/charsets/ */
				/*  , with some facility to choose which charset */
				/*  to actually use. */
				
				case 'a': /* Audible bell. */
					c = 0x07;
					break;
				case 'b': /* Backspace. */
					c = 0x08;
					break;
				case 'f': /* Formfeed. */
					c = 0x0c;
					break;
				case 'n': /* New line. */
					c = 0x0a; /* Line feed. */
					break;
				case 'r': /* Carriage return. */
					c = 0x0d;
					break;
				case 't': /* horizontal Tab. */
					c = 0x09;
					break;
				case 'v': /* Vertical tab. */
					c = 0x0b;
					break;
				case '\"':
				case '\'':
				case '\\':
				case '\?':
					/* Embed character. */
					break;
				default:
					/* Not recognized, treat it as a "boring" literal. */
					
					/* Unhandled meaningfull characters: */
						/* A number starts an octal value to be embedded. */
						/* An 'x' starts a hexadecimal number. */
						/* A 'u' or 'U' starts a Unicode character. */
					/* These all should preferably be handled, but currently */
					/*  aren't: they honestly call for their own functions, */
					/*  and I don't want to implement that just yet. */
					
					break;
			}
			
			
			/* Repush. */
			res = libandria4_cts_push2_uchar( ctx, 1,  c );
			if( !res )
			{
				return( failfunc );
			}
			res = libandria4_cts_push2_uchar( ctx, 1,  type );
			if( !res )
			{
				return( failfunc );
			}
			
			
			/* Return to calling closure. */
			return( retfunc );
		}
		
		return( failfunc );
	}
		/* This is a bit odd. It implements CSV-style embedding of */
		/*  double quotes, where you just stick two of them together. */
		/*  Not how I would do it, but apparently they thought it */
		/*  made sense. */
		/* Note that a flag/character pair should be on stack[ 1 ] */
		/*  already. */
	static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_dquote
	(
		libandria4_cts_context *ctx, void *data_
	)
	{
		if( ctx && data_ )
		{
			libandria4_cts_closure
				acc = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_dquote,
					data_ ),
				getc = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string,
					data_ ),
				unget = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_ungetc,
					data_ );
			libandria4_cts_closure route = retfunc;
			
			libandria4_parser_CSV_CSV1_file *data =
				(libandria4_parser_CSV_CSV1_file*)data_;
			if( libandria4_parser_CSV_CSV1_validate( data ) )
			{
				return( failfunc );
			}
			
			unsigned char c, type;
			int res = 0;
			
			
			/* Get the character values. */
			res = libandria4_cts_pop_uchar( ctx, 1,  &type );
			if( !res )
			{
				return( failfunc );
			}
			res = libandria4_cts_pop_uchar( ctx, 1,  &c );
			if( !res )
			{
				return( failfunc );
			}
			
			
			/* Dispatch per getc category. */
			switch( type )
			{
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS:
					break;
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SEMIEOF:
						/* Queue acc. */
					res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
					if( !res )
					{
						return( failfunc );
					}
					
					return( getc );
					
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF:
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL:
				default:
					/* Should be logging here. */
					
					return( failfunc );
			}
			
			
			/* Dispatch character category. */
			libandria4_parser_CSV_CSV1_sortchar_categories cat =
				libandria4_parser_CSV_CSV1_sortchar( data, c );
			switch( cat )
			{
				/* Plain success. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
						/* Override normal treatment of double-quotes. */
					type = LIBANDRIA4_PARSER_CSV_CSV1_GETC_FORCE;
					break;
					
				/* Valid followers to a closing double-quote. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
					/* Repush. */
					res = libandria4_cts_push2_uchar( ctx, 1,  '\"' );
					if( !res )
					{
						return( failfunc );
					}
					res = libandria4_cts_push2_uchar( ctx, 1,  LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS );
					if( !res )
					{
						return( failfunc );
					}
					
					route = unget;
					break;
					
				/* Errors. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
				case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
					return( data->onfatal );
				case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
				case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
				default:
					return( failfunc );
			}
			
			
			/* Repush. */
			res = libandria4_cts_push2_uchar( ctx, 1,  c );
			if( !res )
			{
				return( failfunc );
			}
			res = libandria4_cts_push2_uchar( ctx, 1,  type );
			if( !res )
			{
				return( failfunc );
			}
			
				/* Just use the pre-set default return. */
			return( route );
		}
		
		return( failfunc );
	}
		/* Fetches a character as a member of a string: this may consume */
		/*  MULTIPLE characters per result, or even consume a character for an */
		/*  "EOF" result (which happens as the end of a string). */
	static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_inner
	(
		libandria4_cts_context *ctx, void *data_
	)
	{
		if( ctx && data_ )
		{
				/* We don't WANT recursion, so no "acc" here. */
			libandria4_cts_closure
				dquote = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_dquote,
					data_ ),
				cesc = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_cescape,
					data_ ),
				getc = LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string,
					data_ );
			
			
			libandria4_parser_CSV_CSV1_file *data =
				(libandria4_parser_CSV_CSV1_file*)data_;
			if( libandria4_parser_CSV_CSV1_validate( data ) )
			{
				return( failfunc );
			}
			
			unsigned char c, type;
			int res = 0;
			
			
			/* Get the character values. */
			res = libandria4_cts_pop_uchar( ctx, 1,  &type );
			if( !res )
			{
				return( failfunc );
			}
			res = libandria4_cts_pop_uchar( ctx, 1,  &c );
			if( !res )
			{
				return( failfunc );
			}
			
			
			/* Dispatch get-result. */
			switch( type )
			{
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_FORCE:
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS:
					break;
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SEMIEOF:
					LIBANDRIA4_CTS_RETURNCLOSURE(
						&libandria4_parser_CSV_CSV1_getc_string,
						data_ );
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF:
				case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL:
				default:
					/* Should be logging here. */
					
					return( failfunc );
			}
			
			
			/* Dispatch character category. */
			libandria4_parser_CSV_CSV1_sortchar_categories cat =
				libandria4_parser_CSV_CSV1_sortchar( data, c );
			switch( cat )
			{
				case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
					/* Double-quote, so we need to dig a bit more, so delegate. */
					/* Note that this implements CSV-style double-quote */
					/*  embedding manually, so it needs to be revised. */
					/* TODO: spruce this up a bit. */
					
					if( data->csvStr )
					{
						/* Schedule interpreter. */
						res = libandria4_cts_push2_ctsclsr( ctx, 0,  dquote );
						if( !res )
						{
							return( failfunc );
						}
						
						/* Get next character. */
						return( getc );
					}
					
					/* We aren't acknowledging CSV-style strings, so just exit */
					/*  the string handling. */
					break;
					
				/* Plain success. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
					if( c == '\\' && data->cStr )
					{
						/* Backslash, so we need to dig a bit more, delegate. */
						/* TODO: add more supported escape sequences. */
						
						/* Schedule interpreter. */
						res = libandria4_cts_push2_ctsclsr( ctx, 0,  cesc );
						if( !res )
						{
							return( failfunc );
						}
						
						/* Get next character. */
						return( getc );
					}
					/* Fall-through. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
					break;
					
				/* Errors. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
				case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
				default:
					type = LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL;
					break;
			}
			
			
			/* Repush. */
			res = libandria4_cts_push2_uchar( ctx, 1,  c );
			if( !res )
			{
				return( failfunc );
			}
			res = libandria4_cts_push2_uchar( ctx, 1,  type );
			if( !res )
			{
				return( failfunc );
			}
			
			return( retfunc );
		}
		
		return( failfunc );
	}
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_string_inner,
				data_ ),
			getc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc,
				data_ );
		
		if( libandria4_parser_CSV_CSV1_validate( data_ ) )
		{
			return( failfunc );
		}
		
		int res;
		
		/* Schedule interpreter. */
		res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
		if( !res )
		{
			return( failfunc );
		}
		
			/* Fetch unprocessed character. */
		return( getc );
	}
	
	return( failfunc );
}
