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
#include "../../commonerrvals.h"
#include "../../commontypes.h"
#include "../../simpleops.h"
#include "../../monads.h"
#include "../../list.h"



LIBANDRIA4_CTS_RETURNCLOSURE(
	&libandria4_cts_framefunc_stoprun,
	(void*)0 )



/* WARNING,NOT VALID C! Replace all of the handleeither() constructs with */
/*  valid macros. */
static libandria4_cts_closure failfunc;


static libandria4_cts_closure failfunc =
	LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_cts_framefunc_stoprun,
		(void*)&failfunc );



int libandria4_parser_CSV_CSV1_validate( libandria4_parser_CSV_CSV1_file *f )
{
	if( f )
	{
		/* Prohibitions: */
		if( f->btStr && f->colonSep )
		{
			return( 0 );
		}
		
		/* Demands: */
		if( !( f->cStr || f->csvStr || f->btStr ) )
		{
			return( 0 );
		}
		if( !( f->commaSep || f->colonSep || f->semiSep || f->spaceSep || f->tabSep ) )
		{
			return( 0 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}
libandria4_parser_CSV_CSV1_sortchar_categories libandria4_parser_CSV_CSV1_sortchar
(
	libandria4_parser_CSV_CSV1_file *f,
	char character
)
{
	libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs ret =
		libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs;
	
	if( f )
	{
		ret = libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar;
		
		switch( character )
		{
			case ',':
				ret = ( data->commaSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			case ':':
				ret = ( data->colonSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			case ';':
				ret = ( data->semiSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			case ' ':
				ret = ( data->spaceSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			case '\t':
				ret = ( data->tabSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			
				/* Any line-spacing character outside of a string is */
				/*  ABSOLUTELY a "new record" marker. */
			case '\v':
			case '\n':
			case '\r':
			case '\f':
				ret = libandria4_parser_CSV_CSV1_sortchar_categories_recordsep;
				break;
			
			case '(':
				ret = ( data->parenNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener : ret;
				break;
			case '[':
				ret = ( data->sqrNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener : ret;
				break;
			case '{':
				ret = ( data->curlNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener : ret;
				break;
			case '<':
				ret = ( data->angleNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener : ret;
				break;
			
			case ')':
				ret = ( data->parenNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser : ret;
				break;
			case ']':
				ret = ( data->sqrNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser : ret;
				break;
			case '}':
				ret = ( data->curlNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser : ret;
				break;
			case '>':
				ret = ( data->angleNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser : ret;
				break;
			
			case '\"':
				ret = libandria4_parser_CSV_CSV1_sortchar_categories_doublequote;
				break;
			
			default: /* Assume it's just normal. */ break;
		}
	}
	
	return( ret );
}



	/* Expects a type on top of a character, both as uchars on stack[ 1 ], */
	/*  and a return closure on stack[ 0 ] as a libandria4_cts_closure{}. */
	/*  DOES NOT pop the type or character, but DOES pop the return closure. */
	/*  Note that while the character gets handed to *_unget(), the type is */
	/*  expected to just be recalculated if needed. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_ungetc
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		unsigned char c, type;
		int e, res = 0;
		
		
		/* Get the values. */
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
		
		/* Unget the character. */
		res = 0;
		while( res == 0 )
		{
			res = libandria4_parser_CSV_CSV1_unget( data, c );
		}
		if( res )
		{
			/* Success. Just fall-through. */
			
		} else {
			
			/* Failure. */
			return( failfunc );
		}
		c = 0;
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}
	/* Expects a type on top of a character, both as uchars on stack[ 1 ], */
	/*  and a return closure on stack[ 0 ] as a libandria4_cts_closure{}. It */
	/*  pops everything it expects, returns the closure, and otherwise does */
	/*  nothing. Meant to be used with libandria4_parser_CSV_CSV1_ungetc(). */
libandria4_cts_closure libandria4_parser_CSV_CSV1_popchar
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		unsigned char c, type;
		int e, res = 0;
		
		
		/* Pop the character and it's flag. */
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
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}



/* These two push two unsigned chars onto stack[ 1 ] (so the second stack); */
/*  the top character is a tag (0-2: error, EOF, character), and expect a */
/*  return closure on top of stack[ 0 ]. */
	/* Fetches a character outside of a string. 0 is error, 1 is token-EOF */
	/*  (the character will be un-gotten back to the source), 2 is plain */
	/*  success. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_notstring
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		if( libandria4_parser_CSV_CSV1_validate( data ) )
		{
			return( failfunc );
		}
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e = 0, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETcFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		/* Analyze. */
		if( res == 1 )
		{
			/* Success... OR IS IT??? */
			
			libandria4_parser_CSV_CSV1_sortchar_categories cat =
				libandria4_parser_CSV_CSV1_sortchar( data, c );
			switch( cat )
			{
				/* Plain success. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
					type = 2;
					break;
					
				/* "Value breakers." */
				case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
						/* Mark as EOF. */
					type = 1;
					break;
					
				/* Errors. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
				case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
				case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
				default:
					type = 0;
					break;
			}
			
		} else if( res == -1 )
		{
			if( e > 0 )
			{
				/* EOF. */
				type = 1;
				
			} else if( e == 0 )
			{
				/* Retry, so early exit + trigger repeat. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_notstring,
					data_ );
				
			} else {
				
				/* Error. */
				type = 0;
			}
			
		} else {
			
			/* This should never happen. */
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
		
		
			/* For EOF, return via unget(). */
		if( type == 1 && !e )
		{
			LIBANDRIA4_CTS_RETURNCLOSURE(
				&libandria4_parser_CSV_CSV1_ungetc,
				data_ );
		}
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}

	/* An implementation function for libandria4_parser_CSV_CSV1_getc_string(). */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_dquote
(
	libandria4_cts_context *ctx, void *data
);
static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_cescape
(
	libandria4_cts_context *ctx, void *data
);
	/* Fetches a character as a member of a string: this may consume */
	/*  MULTIPLE characters per result, or even consume a character for an */
	/*  "EOF" result (which happens as the end of a string). */
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		if( libandria4_parser_CSV_CSV1_validate( data ) )
		{
			return( failfunc );
		}
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETcFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		/* Analyze. */
		if( res == 1 )
		{
			/* Success. */
			
			libandria4_parser_CSV_CSV1_sortchar_categories cat =
				libandria4_parser_CSV_CSV1_sortchar( data, c );
			switch( cat )
			{
				case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
						/* Double-quote, so we need to dig a bit more, so delegate. */
						/* Note that this implements CSV-style double-quote */
						/*  embedding manually, so it needs to be revised. */
						/* TODO: spruce this up a bit. */
					LIBANDRIA4_CTS_RETURNCLOSURE(
						&libandria4_parser_CSV_CSV1_getc_string_dquote,
						data_ );
					
				/* Plain success. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
					if( c == '\\' && data->cStr )
					{
							/* Backslash, so we need to dig a bit more, delegate. */
							/* TODO: add more supported escape sequences. */
						LIBANDRIA4_CTS_RETURNCLOSURE(
							&libandria4_parser_CSV_CSV1_getc_string_cescape,
							data_ );
					}
				case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
					type = 2;
					break;
					
				/* Errors. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
				case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
				default:
					type = 0;
					break;
			}
			
		} else if( res == -1 )
		{
			if( e > 0 )
			{
				/* EOF. */
				type = 1;
				
			} else if( e == 0 )
			{
				/* Retry, so early exit + trigger repeat. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string,
					data_ );
				
			} else {
				
				/* Error. */
				type = 0;
			}
			
		} else {
			
			/* This should never happen. */
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
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}
static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_dquote
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		if( libandria4_parser_CSV_CSV1_validate( data ) )
		{
			return( failfunc );
		}
		
			/* Setup a default "return via return stack" route. */
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		libandria4_cts_closure ret =
			LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d );
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETcFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		/* Analyze. */
		if( res == 1 )
		{
			/* Success. */
			
			if( c == '\"' )
			{
				/* Embedded double-quote. */
				type = 2;
				
			} else {
				
				/* Not a double-quote, so unget via delegation. */
				
					/* Override the default return route, with unget() as a detour. */
				ret =
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_ungetc,
						data_ );
				
				/* We treat this as an EOF. 'c' holds the value to unget, so no touching that. */
				type = 1;
			}
			
		} else if( res == -1 )
		{
			/* Error. */
			if( e > 0 )
			{
				/* EOF. */
				type = 1;
				
			} else if( e == 0 )
			{
				/* Retry, so early exit + trigger repeat. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_dquote,
					data_ );
				
			} else {
				
				/* Error. */
				type = 0;
			}
			
		} else {
			
			/* This should never happen. */
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
		
			/* Just use the pre-set default return. */
		return( ret );
	}
	
	return( failfunc );
}
static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_cescape
(
	libandria4_cts_context *ctx, void *data
)
{
	if( ctx && data_ )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		if( libandria4_parser_CSV_CSV1_validate( data ) )
		{
			return( failfunc );
		}
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETcFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		/* Analyze. */
		if( res == 1 )
		{
			/* Success. */
			
			switch( c )
			{
				case 'a': /* Audible bell. */
					c = 0x07;
					type = 2;
					break;
				case 'b': /* Backspace. */
					c = 0x08;
					type = 2;
					break;
				case 'f': /* Formfeed. */
					c = 0x0c;
					type = 2;
					break;
				case 'n': /* New line. */
					c = 0x0a; /* Line feed. */
					type = 2;
					break;
				case 'r': /* Carriage return. */
					c = 0x0d;
					type = 2;
					break;
				case 't': /* horizontal Tab. */
					c = 0x09;
					type = 2;
					break;
				case 'v': /* Vertical tab. */
					c = 0x0;
					type = 2;
					break;
				case '\"':
				case '\'':
				case '\\':
				case '\?':
					/* Embed character. */
					type = 2;
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
					
					type = 2;
					break;
			}
			
		} else if( res == -1 )
		{
			/* Error. */
			if( e > 0 )
			{
				/* EOF. */
				type = 1;
				
			} else if( e == 0 )
			{
				/* Retry, so early exit + trigger repeat. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_cescape,
					data_ );
				
			} else {
				
				/* Error. */
				type = 0;
			}
			
		} else {
			
			/* This should never happen. */
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
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}



	/* Preemptively-retrospective note: the string gets allocated by */
	/*  *_accumulate_string(), not by it's caller. */
	/* Iteratively fetches a string. The opening double-quote should ALREADY */
	/*  BE CONSUMED. A void-pointer to the string will be on stack[1], with a */
	/*  bool (as an unsigned char) on top: the pointer will be invalid if the */
	/*  char is 0, else the string-pointer will be valid; the string itself */
	/*  will be a libandria4_char_pascalarray{}. The bool can technically be */
	/*  a 2 instead of just 0 or 1, but that is only done by the */
	/*  *_accumulate_value() function-set that this returns into, and thus */
	/*  can be ignored here. */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_string_inner
(
	libandria4_cts_context *ctx, void *data
)
{
	if( ctx && data )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_string_inner,
				data ),
			getc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_string,
				data ),
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d );
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		int res;
		unsigned char flag = 0, c;
		
		/* Get the character values. */
		res = libandria4_cts_pop_uchar( ctx, 1,  &flag );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_pop_uchar( ctx, 1,  &c );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Dispatch. */
		switch( flag )
		{
			case 2: /* character. */
				break;
				
			case 0: /* error. */
				/* Fall-through. */
			default: /* Everything else. */
					/* Well, we have a "valid" flag sitting on */
					/*  our string pointer, but we no longer know */
					/*  if the data was relevant... */
				res = libandria4_cts_pop_uchar( ctx, 1,  &flag );
				if( !res )
				{
					return( failfunc );
				}
				res = libandria4_cts_push2_uchar( ctx, 1,  0 );
				if( !res )
				{
					return( failfunc );
				}
			case 1: /* EOF. */
				/* Ok, we're actually just done. */
				/*
					( (libandria4_parser_CSV_CSV1_file*)data )->{ libandria4_cts_closure onstr, onval; }
				*/
				return( ret );
		}
		
		res = libandria4_cts_pop_uchar( ctx, 1,  &flag );
		if( !res )
		{
			return( failfunc );
		}
		libandria4_char_pascalarray *strparr = 0;
		{
			void *a;
			
			res = libandria4_cts_pop_voidp( ctx, 1,  &a );
			if( !res )
			{
				return( failfunc );
			}
			
			strparr = (libandria4_char_pascalarray*)a;
		}
		{
			libandria4_char_pascalarray *a;
			libandria4_failure_uipresult e;
			libandria4_char_pascalarray_result strres =
				libandria4_char_pascalarray_rebuild( strparr, strparr->len + 1 );
			
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
				strres,
					LIBANDRIA4_OP_ISVARaFLAGresAS1,
					LIBANDRIA4_OP_ISVAReFLAGresASn1 );
			
			if( res == 1 )
			{
				strparr = (libandria4_char_pascalarray*)a;
				flag = 1;
				
			} else if( res == -1 )
			{
				flag = 0;
				
			} else {
				
				libandria4_result res = libandria4_char_pascalarray_destroy( strparr );
				
				return( failfunc );
			}
		}
		strparr->body[ strparr->len - ( flag ? 2 : 1 ) ] = c;
		if( flag )
		{
			strparr->body[ strparr->len - 1 ] = '\0';
		}
		
		/* Push the string. */
		res = libandria4_cts_push2_voidp( ctx, 1,  (void*)strparr );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_uchar( ctx, 1,  flag );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Return. */
		if( flag )
		{
			/* Push the return target. */
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
			if( !res )
			{
				return( failfunc );
			}
			
			return( getc );
			
		} else {
			
			/*
				( (libandria4_parser_CSV_CSV1_file*)data )->{ libandria4_cts_closure onstr, onval; }
			*/
			return( ret );
		}
	}
	
	return( failfunc );
}
libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_string
(
	libandria4_cts_context *ctx, void *data
)
{
	if( ctx && data )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_string_inner,
				data ),
			getc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_string,
				data ),
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d );
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		int res = 0;
		
		libandria4_char_pascalarray *a;
		unsigned char flag = 0;
		{
			libandria4_char_pascalarray *a;
			libandria4_failure_uipresult e;
			
			libandria4_char_parrres strres = libandria4_char_parr_strbuild( "\0" );
			
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
				strres,
					LIBANDRIA4_OP_ISVARaFLAGresAS1,
					LIBANDRIA4_OP_ISVAReFLAGresASn1 );
			
			if( res == 1 )
			{
				flag = 1;
				
			} else if( res == -1 )
			{
				a = (libandria4_char_pascalarray*)0;
				
			} else {
				
				return( failfunc );
			}
		}
		
		/* Push the starter string. */
		res = libandria4_cts_push2_voidp( ctx, 1,  (void*)a );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_uchar( ctx, 1,  flag );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Return. */
		if( flag )
		{
			/* Push the return target. */
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
			if( !res )
			{
				return( failfunc );
			}
			
			return( getc );
			
		} else {
			
			return( ret );
		}
	}
	
	return( failfunc );
}





















/**************************************************************************/
/**************************************************************************/
/** NOTE: The set of functions in the following group are "current", the **/
/**  ones above need to be adapted to match those below. ******************/
/**************************************************************************/
/**************************************************************************/



#define LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL ( 0 )
#define LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF ( 1 )
#define LIBANDRIA4_PARSER_CSV_CSV1_GETC_SEMIEOF ( 2 )
#define LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS ( 3 )

#define libandria4_parser_CSV_CSV1_RETONFATAL( ctxptr, dataptr, funcptr, sec_id, thrd_id ) \
	return( \
		libandria4_parser_CSV_CSV1_onfatal( \
			(ctxptr), (dataptr), \
			(funcptr), \
			(void*)&( libandria4_commonlib_firstchars[ (sec_id) ] ), \
			(thrd_id) ) )



static libandria4_cts_closure libandria4_parser_CSV_CSV1_onfatal
(
	libandria4_cts_context *ctx, void *data_,
	libandria4_cts_framefunc tag_ptr, void *tag2, unsigned int tag3
)
{
	if( ctx && data_ )
	{
			/* Do we actually want this here? */
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data_ ) )
		{
			return( failfunc );
		}
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		if( !( data->onfatal.handler ) )
		{
			return( failfunc );
		}
		
		
		/* Push the tag unsigned. */
		int res = libandria4_cts_push2_uint( ctx, 1,  tag3 );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Push the tag void-pointer. */
		res = libandria4_cts_push2_voidp( ctx, 1,  tag2 );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Push the tag function. */
		res = libandria4_cts_push2_voidf( ctx, 1,  tag_ptr );
		if( !res )
		{
			return( failfunc );
		}
		
		return( data->onfatal );
	}
	
	return( failfunc );
}

	/*
		Possible return flags:
			0: True failure.
			1: True EOF.
			2: Sub-stream EOF (aka retry).
			3: Success.
		Stack delta: 0( return target ) 1() -> 0() 1( character, flags )
			(top listed last)
	*/
static libandria4_cts_closure libandria4_parser_CSV_CSV1_getc
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
			/* Do we actually want this here? */
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data_ ) )
		{
			return( failfunc );
		}
		
		
		
		/* Read, then categorize result. */
		unsigned char c, flag;
		int res = 0;
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_get( data_ );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETcFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			type = LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL;
			
		} else {
			
				/* STOP HARDWIRING! Properly process stuff! */
			type = LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS;
		}
		
		
		/* Push. */
		res = libandria4_cts_push2_uchar( ctx, 1,  c );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_RETONFATAL(
				ctx, data_,
				&libandria4_parser_CSV_CSV1_getc, 0, 0 );
		}
		res = libandria4_cts_push2_uchar( ctx, 1,  type );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_RETONFATAL(
				ctx, data_,
				&libandria4_parser_CSV_CSV1_getc, 0, 1 );
		}
		
		
		
		/* Return. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_RETONFATAL(
				ctx, data_,
				&libandria4_parser_CSV_CSV1_getc, 0, 2 );
		}
		
		return( ret );
	}
	
	return( failfunc );
}



	/* Not allowed to contain separator or newline characters. */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_nonstring_innernested
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		static libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_nonstring_innernested,
				data ),
			getc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_notstring,
				data ),
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d ),
			popchar = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_popchar,
				(void*)&iret_d );
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data_ ) )
		{
			return( failfunc );
		}
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		libandria4_cts_closure hand = { 0, 0 };
		int res, repush = 0;
		
		
		/* Sorted dispatch. */
		libandria4_parser_CSV_CSV1_sortchar_categories cat =
			libandria4_parser_CSV_CSV1_sortchar( data, c );
		switch( cat )
		{
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
			case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
			case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
				
				/* Skip these queuings if closing. We'll eventually */
				/*  fall-through to whatever is already on the return */
				/*  stack. */
				if( cat != libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser )
				{
					/* We need to recurse. */
					res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
					if( !res )
					{
						return( failfunc );
					}
					
					/* Enter the nesting. */
					if( cat == libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener )
					{
						/* Nest. */
						res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
						if( !res )
						{
							return( failfunc );
						}
						
						/* Announce. */
						res = libandria4_cts_push2_ctsclsr( ctx, 0,  data->startfield );
						if( !res )
						{
							return( failfunc );
						}
					}
				}
				
				/* We'll need the next character to be ready. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  getc );
				if( !res )
				{
					return( failfunc );
				}
				
				/* Pop the opener character. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  popchar );
				if( !res )
				{
					return( failfunc );
				}
				
				/* Set the tail-cal target. */
				hand =
					( cat == libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener ) ?
						( data->onopen ): /* Nest. */
						(
							( cat == libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser ) ?
								( data->onclose ): /* De-nest. */
								( data->onexprchar ) /* Announce character. */
						)
						();
				
				/* Repush the character for hand(). */
				repush = 1;
				break;
			case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				
				/* We need to recurse. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
				if( !res )
				{
					return( failfunc );
				}
				
				/* Announce. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  data->startfield );
				if( !res )
				{
					return( failfunc );
				}
				
				/* We'll need the next character to be ready. */
				hand = getc;
				
				repush = 0;
				
				break;
			
			/* Errors. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
				/* Absolute syntax error, there should never be a record seperator here. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
			case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
			default:
				
				/* Do some logging here. */
				
				return( failfunc );
		}
		
		if( repush )
		{
			/* Repush the character for hand(). */
			res = libandria4_cts_push2_uchar( ctx, 1,  c );
			if( !res )
			{
				libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 5 );
			}
			res = libandria4_cts_push2_uchar( ctx, 1,  LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS );
			if( !res )
			{
				libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 6 );
			}
		}
		return( hand );
	}
	
	return( failfunc );
}
	/* Requires a flag (3 equals "success") as a uchar on */
	/*  stack[ 1 ], with a character as uchar directly */
	/*  underneath it. */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_nonstring_inner
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		static libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_nonstring_inner,
				data ),
			getc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_notstring,
				data ),
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d ),
			popchar = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_popchar,
				(void*)&iret_d ),
			nested = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_nonstring_innernested,
				data_ );
		libandria4_cts_closure route = ret;
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data_ ) )
		{
			return( failfunc );
		}
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		int res;
		unsigned char flag = 0, c;
		
		
		/* Get the character values. */
		res = libandria4_cts_pop_uchar( ctx, 1,  &flag );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_pop_uchar( ctx, 1,  &c );
		if( !res )
		{
			return( failfunc );
		}
		
		
		/* Flagged dispatch. */
		switch( flag )
		{
			case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS: /* character. */
				/* This takes a fair bit of work, so break out */
				/*  into it's handler. */
				break;
				
				/* The rest of these can be handled with a single */
				/*  compact logic sequence. */
			default: /* Everything else. */
				
				/* We need to log the specific flag that was detected. */
				
				/* Fall-through. */
			case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL:
				/* Error. */
				
				if( flag == LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL )
				{
					/* We need to log an error here. */
				}
				
				if( !( data->onfatal.handler ) )
				{
					return( failfunc );
				}
				
				return( data->onfatal );
				
			case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF:
			case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SEMIEOF:
				/* EOF, including nesting characters. */
					/* Actually, should nesting characters be relevant? */
				/* ... Ok, we're actually just done. */
				/*
					( (libandria4_parser_CSV_CSV1_file*)data )->{ libandria4_cts_closure onstr, onval; }
				*/
				
				if( !( data->onEOF.handler ) )
				{
					return( failfunc );
				}
				
				return( data->onEOF );
		}
		
		
		/* Sorted dispatch. */
		libandria4_parser_CSV_CSV1_sortchar_categories cat =
			libandria4_parser_CSV_CSV1_sortchar( data, c );
		switch( cat )
		{
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
			case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
			case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
				
				/* We need to recurse. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
				if( !res )
				{
					return( failfunc );
				}
				
				/* Enter the nesting. */
				if( cat == libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener )
				{
					/* Nest. */
					res = libandria4_cts_push2_ctsclsr( ctx, 0,  nested );
					if( !res )
					{
						return( failfunc );
					}
					
					/* Announce. */
					res = libandria4_cts_push2_ctsclsr( ctx, 0,  data->startfield );
					if( !res )
					{
						return( failfunc );
					}
				}
				
				/* We'll need the next character to be ready. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  getc );
				if( !res )
				{
					return( failfunc );
				}
				
				/* Pop the opener character. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  popchar );
				if( !res )
				{
					return( failfunc );
				}
				
				/* Set the tail-cal target. */
				route =
					( cat == libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener ) ?
						( data->onopen ): /* Nest. */
						( data->onexprchar ); /* Announce character. */
				
				/* Repush the character for ret(). */
				res = libandria4_cts_push2_uchar( ctx, 1,  c );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 5 );
				}
				res = libandria4_cts_push2_uchar( ctx, 1,  LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 6 );
				}
				break;
			
			case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
			case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
					/* We'll already act appropriately. */
				break;
			
			/* Errors. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
					/* This belongs in a specialized branch function. */
				/*
				hand = data->onclose;
				break;
				*/
				return( failfunc );
			case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
			case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
			default:
				
				/* Do some logging here. */
				
				return( failfunc );
		}
		
		return( route );
	}
	
	return( failfunc );
}


	/* Fetches a character into a string: this consumes characters on a */
	/*  one-to-one basis. */
	/* Upon entry, there must be a "characters not yet read" value on */
	/*  stack[ 2 ] as a size_t, on top of a pascal-string as a */
	/*  void-pointer, where the size_t IS NOT larger than the size of */
	/*  the pascal-string. */
	/*  Further, there must be a flag as a uchar on stack[ 1 ], on top */
	/*  of a character as uchar. The flag's values must follow the */
	/*  rules for *_CSV1_getc(). */
	/* Upon return, there will be a result flag on stack[ 1 ] as a */
	/*  uchar. The result will either be: */
		/* 1 for success, with a pascal-string as a void-pointer on */
		/*  stack[ 2 ], or */
		/* 0 for a failure, with a size_t holding the number of */
		/*  incomplete characters on stack[ 2 ], with the void-pointer */
		/*  from the success case under that. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_btstring
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		static libandria4_cts_closure
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d ),
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_btstring,
				data_ ),
			push0 = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_ctspush_uchar_stk1_val0,
				data_ ),
			popc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_popchar,
				data_ ),
			ungetc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_ungetc,
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
		
		int e, res = 0;
		size_t sz = 0;
		unsigned char flag, c;
		
		
		/* Fetch progress & string. */
		res = libandria4_cts_pop_sizet( ctx, 2,  &sz );
		if( !res )
		{
			return( failfunc );
		}
		libandria4_char_pascalarray *strparr = 0;
		{
			void *a;
			
			res = libandria4_cts_pop_voidp( ctx, 2,  &a );
			if( !res )
			{
				return( failfunc );
			}
			
			strparr = (libandria4_char_pascalarray*)a;
		}
		
		/* Restore the string, and then progress. */
		res = libandria4_cts_push2_voidp( ctx, 2,  (void*)strparr );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_sizet( ctx, 2,  sz );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Validate sz value & string's existence. */
		if( !strparr || sz < strparr->len || strparr->len < 0 )
		{
			return( failfunc );
		}
		
		
		/* Verify the string progress hasn't been borked. */
		if( sz && sz == strparr->len )
		{
			/* Push the error flag once the character has been ungotten. */
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  push0 );
			if( !res )
			{
				libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 9 );
			}
			
			/* Schedule the character to be poped. */
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  popc );
			if( !res )
			{
				libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 9 );
			}
			
				/* Tail-call the unget-character code: this DOES NOT remove */
				/*  the character from the stack. */
			return( ungetc );
		}
		
		
		/* Fetch the character & grow the string. */
		res = libandria4_cts_pop_uchar( ctx, 2,  &type );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_pop_uchar( ctx, 2,  &c );
		if( !res )
		{
			return( failfunc );
		}
		strparr->body[ sz ] = c;
		sz += 1;
		
		
		
		/* Dispatch. */
		
		/* Recurse if incomplete. */
		if( sz < strparr->len )
		{
			/* Queue recursion. */
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
			if( !res )
			{
				return( failfunc );
			}
			
			if( data->onstrchar.handler )
			{
				/* Queue the character handler to let it peek a look. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  data->onstrchar );
				if( !res )
				{
					return( failfunc );
				}
			}
			
			return( getc );
			
		}
		/* Else, exit with success. */
		
		
		/* Discard the size. */
		res = libandria4_cts_pop_sizet( ctx, 2,  &sz );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Mark as success. */
		res = libandria4_cts_push2_uchar( ctx, 1,  1 );
		if( !res )
		{
			return( failfunc );
		}
		
			/* Is this right? Or do we still need to do it manually? */
		return( ret );
	}
	
	return( failfunc );
}

	/* At this point we have a length on stack[ 2 ], and 1 or */
	/*  more characters on stack[ 2 ]. */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_preaccumulate_btstring_innerhelper
(
	libandria4_cts_context *ctx, void *data,
	
	libandria4_cts_closure acc,
	libandria4_cts_closure getc,
	libandria4_cts_closure announce
)
{
	if( ctx && data )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		static libandria4_cts_closure
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d );
		libandria4_cts_closure tmpa = announce, tmpb = getc, tmpc = acc;
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		
		/* First-pass blank-killer. */
		if( !( getc.handler ) )
		{
			getc = acc;
			acc.handler = 0;
		}
		if( !( announce.handler ) )
		{
			announce = getc;
			getc = acc;
			acc.handler = 0;
		}
		
		
		/* Queue the extra handlers. */
		if( !( acc.handler ) )
		{
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
			if( !res )
			{
				return( failfunc );
			}
		}
		if( !( getc.handler ) )
		{
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  getc );
			if( !res )
			{
				return( failfunc );
			}
		}
		
		
		/* Final-pass blank-killer. */
		if( !( announce.handler ) )
		{
			announce = ret;
		}
		
		return( announce );
	}
	
	return( failfunc );
}
	/* Used if it turns out to not be a BitTorrent-style string. */
	/* Requires a size_t string length on stack[ 2 ], and the */
	/*  string itself (first character on top) on stack[ 1 ]; it */
	/*  will push a 3 (as a "success" flag) onto stack[ 1 ], */
	/*  either decrement or (if already just 1) simply remove */
	/*  the string length, if the length was decremented will */
	/*  queue itself for recursion, and directly return the */
	/*  ->onexprchar closure. */
	/* This will cause the string on stack[ 1 ] to appear to */
	/*  have never been treated as the start of a BitTorrent-style */
	/*  string, which is what we want for those cases where such a */
	/*  string wasn't encountered. */
	/* TODO: rename to "unspin", to better reflect it's purpose. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_preaccumulate_btstring_unravel
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		static libandria4_cts_closure
			recur = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_preaccumulate_btstring_unravel,
				data_ );
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		
		int res;
		size_t sz;
		
			/* Fetch size. */
		res = libandria4_cts_pop_sizet( ctx, 2,  &sz );
		if( !res )
		{
			return( failfunc );
		}
		
			/* if len > 1 then push( len - 1 ) && push recursion. */
		if( sz > 1 )
		{
			res = libandria4_cts_push2_sizet( ctx, 2,  sz - 1 );
			if( !res )
			{
				return( failfunc );
			}
			
			res = libandria4_cts_push_ctsclsr( ctx, 0,  recur );
			if( !res )
			{
				libandria4_parser_CSV_CSV1_RETONFATAL(
					ctx, data_,
					&libandria4_parser_CSV_CSV1_preaccumulate_btstring_unravel, 0, 2 );
			}
		}
		
		
			/* We need to push a "success" flag on top of the */
			/*  stack for each character as the character comes. */
		LIBANDRIA4_CTS_RETURNCLOSURE(
			&libandria4_cts_ctspush_uchar_stk1_val3,
			(void*)&( data->onexprchar ) );
	}
	
	return( failfunc );
}
	/* This does the actual dispatch into *_unravel(), and exists */
	/*  to reduce the size of *_preaccumulate_*(). */
libandria4_cts_closure libandria4_parser_CSV_CSV1_preaccumulate_btstring_nonstring
(
	libandria4_cts_context *ctx, void *data_,
	unsigned char flag, unsigned char c
)
{
	if( ctx && data )
	{
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		int res;
		unsigned char e;
		size_t sz;
		
		/* Fetch the string size. */
		res = libandria4_cts_pop_sizet( ctx, 2,  &sz );
		if( !res )
		{
			return( failfunc );
		}
		
			/* Push the new character, and it's flag. */
		res = libandria4_cts_push_uchar( ctx, 1,  c );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push_uchar( ctx, 1,  flag );
		if( !res )
		{
			return( failfunc );
		}
			/* Transfer the accumulated string. */
		{
			size_t l = 0;
			while( l < sz )
			{
				res = libandria4_cts_pop_uchar( ctx, 2,  &c );
				if( !res )
				{
					return( failfunc );
				}
				res = libandria4_cts_push_uchar( ctx, 1,  c );
				if( !res )
				{
					return( failfunc );
				}
				
				--sz;
			}
		}
		
		/* Repush the string length. */
		res = libandria4_cts_push2_sizet( ctx, 2,  sz );
		if( !res )
		{
			return( failfunc );
		}
		
		
		/* Push the dedicated non-string handler, it'll receive */
		/*  the character that we popped. */
		res =
			libandria4_cts_push2_ctsclsr
			(
				ctx, 0,
				LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_accumulate_nonstring_inner,
					data_ )
			);
		if( !res )
		{
			libandria4_parser_CSV_CSV1_record_RETONFATAL( 2, 0 );
		}
		
		
			/* At this point we have a length in sz, and 1 or */
			/*  more characters on stack[ 1 ]. The character we */
			/*  initially popped is one of those, but instead of */
			/*  being counted in the length it has it's result */
			/*  flag between that character and the rest of the */
			/*  characters. */
		LIBANDRIA4_CTS_RETURNCLOSURE(
			&libandria4_parser_CSV_CSV1_preaccumulate_btstring_unravel,
			data_ );
	}
	
	return( failfunc );
}
	/* Used if we got the entire prefix of a BitTorrent-style */
	/*  string, including colon. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_preaccumulate_btstring_calclen
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data )
	{
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		libandria4_char_pascalarray *a;
		
		/* End of length, so dispatch accordingly. */
		{
			static size_t pretest =
				( SIZE_MAX - ( SIZE_MAX % 10 ) ) / 10;
			int res, d = -1;
			size_t sz;
			unsigned char c;
			
			/* Fetch the length string. */
				/* Fetch size. */
			res = libandria4_cts_pop_sizet( ctx, 2,  &sz );
			{
				libandria4_failure_uipresult e;
				
				{
					libandria4_char_pascalarray_result strres =
						libandria4_char_pascalarray_build( sz + (int)1 );
					
					LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
						strres,
							LIBANDRIA4_OP_ISVARaFLAGresAS1,
							LIBANDRIA4_OP_ISVAReFLAGresASn1 );
				}
				
				if( res == 1 )
				{
					/* Populate the string. */
					a->body[ sz ] = '\0';
					
					while( sz )
					{
						--sz;
						
						/* Fetch the character. */
						res = libandria4_cts_pop_uchar( ctx, 2,  &c );
						if( !res )
						{
							return( failfunc );
						}
						
						a->body[ sz ] = c;
					}
					
				} else {
					
					/* Note for improvement: e theoretically holds an error code. */
					
					return( failfunc );
				}
			}
			
			/* Lex/parse the length. */
				/* Requires basic/commonlib.h */
			if( a->len )
			{
				libandria4_result res2;
				libandria4_commonlib_intint_eithfork ef = libandria4_atoi( a->len - 1, a->body );
				LIBANDRIA4_COMMONLIB_FORKINGTYPE_BODYMATCH(
					ef,
						LIBANDRIA4_OP_SETdFLAGresAS1,
						LIBANDRIA4_OP_SETeFLAGresASn1 );
				if( res < 0 || d < 0 )
				{
					res2 = libandria4_char_pascalarray_destroy( a );
					/* At least log res2? */
					
					return( failfunc );
				}
				
				res2 =  libandria4_char_pascalarray_rebuild( a, d );
				LIBANDRIA4_COMMONLIB_FORKINGTYPE_BODYMATCH(
					ef,
						LIBANDRIA4_OP_SETaFLAGresAS1,
						LIBANDRIA4_OP_SETeFLAGresASn1 );
				if( res < 0 )
				{
					res2 = libandria4_char_pascalarray_destroy( a );
					/* At least log res2? */
					
					return( failfunc );
				}
				
			} else {
				
				d = 0;
			}
		}
		
		/* Store the receiving string-container. */
		res = libandria4_cts_push2_voidp( ctx, 2,  a );
		if( !res )
		{
			return( failfunc );
		}
		/* Store the string's accumulated length... which is inherently */
		/*  0 right now, since we haven't read the proper string yet, */
		/*  just it's prologue. */
		res = libandria4_cts_push2_sizet( ctx, 2,  0 );
		if( !res )
		{
			return( failfunc );
		}
		
			/* Reroute to the BT-string accumulator code. */
			/* Remember: we have the length as a size_t on stack[ 2 ], on */
			/*  top of a receptacle string as a */
			/*  libandria4_char_pascalarray*. */
		LIBANDRIA4_CTS_RETURNCLOSURE(
				/* We need to get this pointed at the correct target. */
				/* Use libandria4_parser_CSV_CSV1_accumulate_btstring() ? */
			&libandria4_parser_CSV_CSV1_accumulate_btstring,
			data_ );
	}
	
	return( failfunc );
}
	/* The length string gets stored on stack[ 2 ] with it's length as */
	/*  a size_t on top of the string as a sequence of characters on the */
	/*  stack: the first character read will be stored deepest. */
	/* While it thinks that it's reading a decimal-length, this function */
	/*  will continue to loop: */
		/* TODO: add restraints to stop this from becoming a security */
		/*  risk via a stack-smash or something. */
	/*  If a colon (the ':' character) is detected then the */
	/*  decimal-length will considered complete, any other non-decimal */
	/*  character will be interpreted to mean that the collected */
	/*  characters are NOT part of a BitTorrent-style string. Anything */
	/*  other than recursion returns the result of a helper function. */
	/*  For strings: */
		/* libandria4_parser_CSV_CSV1_preaccumulate_btstring_calclen */
	/*  while for non-strings: */
		/* libandria4_parser_CSV_CSV1_preaccumulate_btstring_nonstring */
libandria4_cts_closure libandria4_parser_CSV_CSV1_preaccumulate_btstring
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_preaccumulate_btstring,
				data ),
			nstr = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_nonstring_inner,
				data ),
			getc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_notstring,
				data ),
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d ),
			popchar = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_popchar,
				(void*)&iret_d );
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data_ ) )
		{
			return( failfunc );
		}
		
		int res;
		unsigned char flag = 0, c, e;
		size_t sz;
		
		/* Get the character values. */
		res = libandria4_cts_pop_uchar( ctx, 1,  &flag );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_pop_uchar( ctx, 1,  &c );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Dispatch. */
		switch( flag )
		{
			case LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS: /* character. */
				/* This takes a fair bit of work, so break out */
				/*  into it's handler. */
				break;
				
				/* The rest of these can be handled with a single */
				/*  compact logic sequence. */
			case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL: /* error. */
				/* Fall-through. */
			case LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF: /* EOF. */
			default: /* Everything else. */
					/* Well, we have a "valid" flag sitting on */
					/*  our string pointer, but we no longer know */
					/*  if the data was relevant... */
				res = libandria4_cts_pop_sizet( ctx, 2,  &sz );
				if( !res )
				{
					return( failfunc );
				}
				
					/* Discard the accumulated string. */
				while( sz )
				{
					res = libandria4_cts_pop_uchar( ctx, 2,  &flag );
					if( !res )
					{
						return( failfunc );
					}
					
					--sz;
				}
				return( failfunc );
		}
		
		
		/* The code above is basically identical to *_nonstring_inner(), */
		/*  the switch below is specific to BT-strings. */
		
		
		/* "Standard character" handling. */
		switch( c )
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				/* Decimal number, just treat plainly. */
				
				/* Fetch the current string length. */
				res = libandria4_cts_pop_sizet( ctx, 2,  &sz );
				if( !res )
				{
					return( failfunc );
				}
					/* Stow the character. */
					res = libandria4_cts_push_uchar( ctx, 2,  c );
					if( !res )
					{
						return( failfunc );
					}
				/* Store the updated length. */
				res = libandria4_cts_push2_sizet( ctx, 2,  sz + 1 );
				if( !res )
				{
					return( failfunc );
				}
				
				break;
			case ':':
				return
				(
					libandria4_parser_CSV_CSV1_preaccumulate_btstring_calclen
					(
						ctx, data_
					)
				);
			default:
				/* Neither a length character, nor a begin-body */
				/*  character, so re-route to *_nonstring_inner(). */
				
				return 
				(
					libandria4_parser_CSV_CSV1_preaccumulate_btstring_nonstring
						( ctx, data_,  flag, c )
				);
		}
		
		/* Delegate the string handling & return value. */
		return
		(
			libandria4_parser_CSV_CSV1_preaccumulate_btstring_innerhelper
			(
				ctx, data_,
				LIBANDRIA4_CTS_BUILDCLOSURE( 0, 0 ), acc, getc
			)
		);
	}
	
	return( failfunc );
}



#define libandria4_parser_CSV_CSV1_accval_RETONFATAL( sec_id, thrd_id ) \
	libandria4_parser_CSV_CSV1_RETONFATAL( \
		ctx, data_, \
		&libandria4_parser_CSV_CSV1_accumulate_value, sec_id, thrd_id )
/* NOTE! This function-group should never return to it's caller-closure unless: */
/*  A: A field-ender has been encountered, or */
/*  B: The field-type is non-string. */
/* Even error returns should follow this pattern. */
	/* Fetches the actual value. May use e.g. *_string(). Returns a */
	/*  pstring-pointer underneath of uchar-flag on stack[ 1 ]. Flag 0 == */
	/*  "no string"/error, flag 1 == string/success, flag 2 == */
	/*  nesting-modification character (WHEN that is a configured thing). */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_value_inner
(
	libandria4_cts_context *ctx, void *data
)
{
	if( ctx && data )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		libandria4_cts_closure
			getstr = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_string,
				data ),
			gettok = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_nonstring_inner,
				data_ ),
			getbtstr = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_preaccumulate_btstring,
				data_ );
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		
		/* Fetch the character. */
		res = libandria4_cts_pop_uchar( ctx, 1,  &flag );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 0 );
		}
		res = libandria4_cts_pop_uchar( ctx, 1,  &c );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 1 );
		}
		
		
		/* Handle errors. */
		if( flag == LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF )
		{
			libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 2 );
		}
		else if( flag == LIBANDRIA4_PARSER_CSV_CSV1_GETC_SEMIEOF )
		{
			libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 3 );
		}
		else if( flag != LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS )
		{
			libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 4 );
		}
		
		
		libandria4_parser_CSV_CSV1_sortchar_categories cat =
			libandria4_parser_CSV_CSV1_sortchar( data, c );
		switch( cat )
		{
			case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
				/* Push the return target. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  getstr );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 7 );
				}
				
				/* We aren't repushing the character we've read, so fetch the next instead. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc,
					data_ );
			case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
				/* Token accumulation. */
				/* Repush the character for *_accumulate_nonstring(). */
				res = libandria4_cts_push2_uchar( ctx, 1,  c );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 5 );
				}
				res = libandria4_cts_push2_uchar( ctx, 1,  type );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 6 );
				}
				
				/* If a BitTorrent string, push a length of 0 for initial accumulation. */
				if( data->btStr )
				{
					res = libandria4_cts_push2_uchar( ctx, 2,  0 );
					if( !res )
					{
						libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 5 );
					}
				}
				
					/* Build the string via unget(). */
				return( ( data->btStr ) ? getbtstr : gettok );
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
			case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
			case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				return( LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_cts_innerreturn,
						(void*)&iret_d ) );
			
			/* Errors. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
			case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
			default:
				libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 8 );
		}
		
		/* This should actually never happen. */
		libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 9 );
	}
	
	return( failfunc );
}
libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_value
(
	libandria4_cts_context *ctx, void *data
)
{
	if( ctx && data )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_value_inner,
				data ),
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d );
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETcFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		
		if( res == 1 )
		{
			libandria4_parser_CSV_CSV1_sortchar_categories cat =
				libandria4_parser_CSV_CSV1_sortchar( data, c );
			switch( cat )
			{
				case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
				case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
					type = LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS;
					break;
				
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
				case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
				case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
				case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
					/* Refer back to the record handler entry point on stack[ 0 ]. */
					type = LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS;
					acc = ret;
					break;
					
				/* Errors. */
				case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
				case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
				default:
					/* Store a "bad string". */
					res = libandria4_cts_push2_voidp( ctx, 1,  (void*)0 );
					if( !res )
					{
						libandria4_parser_CSV_CSV1_accval_RETONFATAL( 0, 0 );
					}
					res = libandria4_cts_push2_uchar( ctx, 1,  0 );
					if( !res )
					{
						libandria4_parser_CSV_CSV1_accval_RETONFATAL( 0, 1 );
					}
					
					return( ret );
			}
			
		} else {
			
			type = LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEFAIL;
		}
		
		/* Push. */
		res = libandria4_cts_push2_uchar( ctx, 1,  c );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_accval_RETONFATAL( 0, 2 );
		}
			/*
				Possible return flags:
					0: True failure.
					1: True EOF.
					2: Sub-stream EOF (aka retry).
					3: Success.
				Stack delta: 0( return target ) 1() -> 0() 1( character, flags )
					(top listed last)
			*/
		res = libandria4_cts_push2_uchar( ctx, 1,  type );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_accval_RETONFATAL( 0, 3 );
		}
		
		/* Return. */
		return( acc );
	}
	
	return( failfunc );
}



static libandria4_cts_closure libandria4_parser_CSV_CSV1_record_inner
(
	libandria4_cts_context *ctx, void *data_
);
#define libandria4_parser_CSV_CSV1_record_RETONFATAL( sec_id, thrd_id ) \
	libandria4_parser_CSV_CSV1_RETONFATAL( \
		ctx, data_, \
		&libandria4_parser_CSV_CSV1_record, sec_id, thrd_id )
	/* Note: Finish this function! */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_record_inner_helper
(
	libandria4_cts_closure direct, void *data_
)
{
		/* Do we actually want this here? */
	if( libandria4_parser_CSV_CSV1_validate(
		(libandria4_parser_CSV_CSV1_file*)data_ ) )
	{
		return( failfunc );
	}
	libandria4_parser_CSV_CSV1_file *data =
		(libandria4_parser_CSV_CSV1_file*)data_;
	
	
	int res =
		libandria4_cts_push2_ctsclsr
		(
			ctx, 0,
			LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_record_inner,
				data_ )
		);
	if( !res )
	{
		libandria4_parser_CSV_CSV1_record_RETONFATAL( 2, 0 );
	}
	
		/* NOTE! We need to queue up a non-string accumulator here. I */
		/*  believe the correct entry point does not yet exist, but should */
		/*  be derived from *_accumulate_nonstring(), which contrary to */
		/*  it's name can actually accumulate BitTorrent-style strings */
		/*  (because they start with a number). We need to do this because */
		/*  we should only encounter "non"-string values on any route that */
		/*  calls this function. */
	??? ;
	
	return( direct );
}
static libandria4_cts_closure libandria4_parser_CSV_CSV1_record_inner
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
			/* Do we actually want this here? */
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data_ ) )
		{
			return( failfunc );
		}
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		
		unsigned char c, flag;
		int res = 0;
		/* Fetch the character. */
		res = libandria4_cts_pop_uchar( ctx, 1,  &flag );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 0 );
		}
		res = libandria4_cts_pop_uchar( ctx, 1,  &c );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 1 );
		}
		
		
		/* Handle flag. */
		if( flag == LIBANDRIA4_PARSER_CSV_CSV1_GETC_TRUEEOF )
		{
			/* Full EOF. */
			return( data->onEOF );
			
		} else if( flag == LIBANDRIA4_PARSER_CSV_CSV1_GETC_SEMIEOF )
		{
			/* Sub-stream EOF, retry. */
			
			/* Push the handler-body for indirect recursion. */
			res =
				libandria4_cts_push2_ctsclsr
				(
					ctx, 0,
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_record_inner,
						data_ )
				);
			if( !res )
			{
				libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 3 );
			}
			
			
			/* Tail-call to get the character. */
			return
			(
				LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc,
					data_ )
			);
			
		} else if( flag != LIBANDRIA4_PARSER_CSV_CSV1_GETC_SUCCESS )
		{
			/* Some sort of error. */
			
			libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 4 );
		}
		
		
		libandria4_parser_CSV_CSV1_sortchar_categories cat =
			libandria4_parser_CSV_CSV1_sortchar( data_, c );
		switch( cat )
		{
			case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
				/* We can safely just tail-call into our entry point. */
				return
				(
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_record,
						data_ )
				);
			
			/* "Non-string" options. Really they're still strings, but they're */
			/*  ANTI-PATTERN strings, instead of normal ones. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
				return( libandria4_parser_CSV_CSV1_record_inner_helper
							( data->onopen, data_ ) );
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
				return( libandria4_parser_CSV_CSV1_record_inner_helper
							( data->onclose, data_ ) );
				
			case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				/* Push recursion, to continue parsing the record. */
				res =
					libandria4_cts_push2_ctsclsr(
						ctx, 0,
						LIBANDRIA4_CTS_BUILDCLOSURE(
							&libandria4_parser_CSV_CSV1_record_inner,
							data_
						)
					);
				if( !res )
				{
					libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 7 );
				}
				
				/* Announce the start of the new field. */
				res =
					libandria4_cts_push2_ctsclsr(
						ctx, 0,
						data->startfield
					);
				if( !res )
				{
					libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 7 );
				}
				
				/* Tail-call the character reader. */
				return
				(
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_getc,
						data_ )
				);
			case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
			case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
				/* Push recursion, to continue parsing the record. */
				libandria4_cts_closure cls =
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_record_inner,
						data_
					);
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  cls );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 7 );
				}
				
				/* Push value-fetcher, to build up the field's value. It WILL */
				/*  NOT have a character available on the stack when first */
				/*  entered. */
				cls =
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_accumulate_value,
						data_
					);
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  cls );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 8 );
				}
				
				
				/* Repush character. */
				res = libandria4_cts_push2_uchar( ctx, 1,  c );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 5 );
				}
				res = libandria4_cts_push2_uchar( ctx, 1,  type );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 6 );
				}
				
				
				/* Push character popper (to clean the character off the stack). */
				cls =
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_popchar,
						data_
					);
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  cls );
				if( !res )
				{
					libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 9 );
				}
				
				
					/* Tail-call the unget-character code: this DOES NOT remove */
					/*  the character from the stack. */
				return
				(
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_ungetc,
						data_
					)
				);
			
			/* Errors. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
				libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 10 );
			case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
				libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 11 );
			default:
				libandria4_parser_CSV_CSV1_record_RETONFATAL( 1, 12 );
		}
	}
	
	return( failfunc );
}
	/* Fetches a full line (excepting that newlines inside strings don't */
	/*  count for defining lines...) of values. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_record
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data_ )
	{
		static libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE( 0, 0 );
		int res = 0;
		
		if( libandria4_parser_CSV_CSV1_validate( data ) )
		{
			return( failfunc );
		}
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		
			/* Tailor dispatching. */
		++( data->recordindex );
		switch( data->recordindex )
		{
			case 0:
					/* This is an error, because of roll-over. */
				libandria4_parser_CSV_CSV1_record_RETONFATAL( 0, 0 );
			case 1:
				acc = data->firstrec;
				break;
			case 2:
				acc = data->secondrec;
				break;
			default:
				acc = data->restrec;
				break;
		}
		
		/* Push the handler-body for indirect dispatch. */
		res =
			libandria4_cts_push2_ctsclsr
			(
				ctx, 0,
				LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_record_inner,
					data_ )
			);
		if( !res )
		{
			libandria4_parser_CSV_CSV1_record_RETONFATAL( 0, 1 );
		}
		
			/* Announce the start of this record's first field. */
		if( !( acc.handler ) )
		{
			acc = data->startfield;
			
		} else {
			
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  data->startfield );
			if( !res )
			{
				libandria4_parser_CSV_CSV1_record_RETONFATAL( 0, 2 );
			}
		}
		
		/* Push the direct recipient. */
		res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
		if( !res )
		{
			libandria4_parser_CSV_CSV1_record_RETONFATAL( 0, 3 );
		}
		
		
		/* Tail-call the character reader. */
		return
		(
			LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc,
				data_ )
		);
	}
	
	return( failfunc );
}






















/*
			libandria4_result ( libandria4_parser_CSV_CSV1_list_destroylist )( \
					lib4_memfuncs_t *mf_ptr, libandria4_parser_CSV_CSV1_list *a,  void *data, void (*nodefunc)( void*, (nodetype)* ) )
*/



/* Note: all of that stuff about lists and triethers and stuff? Yeah, that */
/*  doesn't belong there. Take that stuff, and move it into some helper */
/*  implementations that CAN be used if the application wants to build a */
/*  parse-tree or something, and have easy wrappers to make that a simple */
/*  one-liner, but don't get invoked if the application doesn't want (as in */
/*  the "splitter" application described a bit further down...). That stuff */
/*  CAN be useful, and SHOULD be pre-written, but ISN'T correct for */
/*  automatic integration. So stop trying to automatically integrate it. */



/* Note: next we need to write some stuff to specially handle the first two */
/*  records (the first two "lines") if (and only if) special handlers for */
/*  them are detected. */

/* Write that here. */



/* Then we need to go back through and actually call the handlers (the */
	/* ( (libandria4_parser_CSV_CSV1_file*)data )->{ libandria4_cts_closure onstr, onval, outrec; } */
/*  stuff) when the proper conditions are reached. */

/* Write that here. */



/* Then we need to write a program that will do all of that, but dispatches */
/*  the resulting stuff to other programs via fork: remember to include */
/*  record and field numbers as part of the data! */

/* DON'T write that here, write that in another file. It should be a full program. */
















libandria4_parser_CSV_CSV1_listnode**
	libandria4_parser_CSV_CSV1_listnode_getneighbor( libandria4_parser_CSV_CSV1_listnode *ref, int getright )
{
	if( ref )
	{
		return( &( ref->peers[ getright ? 1 : 0 ] ) );
	}
	
	return( (libandria4_parser_CSV_CSV1_listnode**)0 );
}




















/**********************************************************************/
/**********************************************************************/
/** All of the stuff below is JUST references pulled from elsewhere. **/
/**********************************************************************/
/**********************************************************************/





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
	
	extern libandria4_commonio_handle libandria4_cts_errout;
	
	
	
	int libandria4_cts_sizedpop( libandria4_cts_context *ctx, size_t stack,  void *dest_, size_t size );
	int libandria4_cts_sizedpush( libandria4_cts_context *ctx, size_t stack,  void *dest_, size_t size );
	
	
	#define LIBANDRIA4_CTS_DECPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val );
	#define LIBANDRIA4_CTS_DEFPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val ) { \
			if( !val ) { return( -1 ); } \
			return( libandria4_cts_sizedpop( ctx, stack,  (void*)val, sizeof( type ) ) ); }
	
	#define LIBANDRIA4_CTS_DECPUSH( prefix, postfix, type ) \
		int prefix ## push ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val );
	#define LIBANDRIA4_CTS_DEFPUSH( prefix, postfix, type ) \
		int prefix ## push ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val ) { \
			if( !val ) { return( -1 ); } \
			return( libandria4_cts_sizedpush( ctx, stack,  (void*)val, sizeof( type ) ) ); }
	
	
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
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _voidf, void (*)() );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );

