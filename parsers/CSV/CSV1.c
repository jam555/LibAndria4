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
static libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_nonstring_innerhelper
(
	libandria4_cts_context *ctx, void *data,
	
	libandria4_cts_closure acc,
	libandria4_cts_closure getc,
	libandria4_cts_closure ret,
	libandria4_cts_closure popchar,
	
	char c
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
		unsigned char flag = 0;
		
		
		/* The code below was pulled from the end of */
			/* *_nonstring_inner(), */
		/*  for better synergy with */
			/* *_preaccumulate_btstring() */
		/*  by sharing common code. */
		
		
		/* Fetch the in-progress string. */
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
		
		/* Grow the existing string with the new character. */
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
		
		/* Push the grown string. */
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
	/* As string, but not a string. Not allowed to contain whitespace, commas, */
	/*  or double-quotes. The storage-string gets allocated by this */
	/*  accumulator, just like the *string() version, including with the */
	/*  tag-uchar stored on top of it on stack[1]. */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_nonstring_inner
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
				/* This takes a fair bit of work, so break out */
				/*  into it's handler. */
				break;
				
				/* The rest of these can be handled with a single */
				/*  compact logic sequence. */
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
			case 1: /* EOF, including nesting characters. */
				/* Ok, we're actually just done. */
				/*
					( (libandria4_parser_CSV_CSV1_file*)data )->{ libandria4_cts_closure onstr, onval; }
				*/
				return( ret );
		}
		
		/* Delegate the string handling & return value. */
		return
		(
			libandria4_parser_CSV_CSV1_accumulate_nonstring_innerhelper
			(
				ctx, data,
				acc, getc, ret, popchar,
				c
			)
		);
	}
	
	return( failfunc );
}
	/* Fetches a character into a string: this consumes characters on a */
	/*  one-to-one basis. */
	/* Upon entry, there must be a "characters not yet read" value on */
	/*  stack[ 1 ] as a size_t, on top of a pascal-string as a */
	/*  void-pointer, where the size_t IS NOT larger than the size of */
	/*  the pascal-string. */
	/* Upon return, there will be a result flag on stack[ 1 ] as a */
	/*  uchar, on top of a pascal-string as a void-pointer. The result */
	/*  will either be 1 for success, or 0 for a failure. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_btstring
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
		
		/* Fetch progress & string. */
		size_t sz = 0;
		res = libandria4_cts_pop_sizet( ctx, 1,  &sz );
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
		
		/* Restore the string, and then progress. */
		res = libandria4_cts_push2_voidp( ctx, 1,  (void*)strparr );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_sizet( ctx, 1,  sz - ( sz ? 1 : 0 ) );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Validate sz value & string's existence. */
		if( !strparr || sz > strparr->len )
		{
			return( failfunc );
		}
		
		/* Safely handle the null-length & end-of-string cases, even if */
		/*  a doofus called us. */
		if( sz )
		{
			/* Fetch character. */
			libandria4_common_monadicchar8 ec =
				libandria4_parser_CSV_CSV1_getc( data );
			unsigned char c, type;
			int e, res = 0;
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
				LIBANDRIA4_OP_SETcFLAGresAS1,
				LIBANDRIA4_OP_SETeFLAGresASn1 );
				/* Push failure, then return to caller. */
			if( !res )
			{
				/* Pop the size, we don't want it anymore. */
				res = libandria4_cts_pop_sizet( ctx, 1,  &sz );
				if( !res )
				{
					return( failfunc );
				}
				
				/* Push the error. */
				res = libandria4_cts_push2_uchar( ctx, 1,  0 );
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
			
				/* Store the current character. */
			strparr->body[ strparr->len - sz ] = c;
			sz -= 1;
		}
		
		if( sz )
		{
			/* Loop. */
			LIBANDRIA4_CTS_RETURNCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_btstring,
				data_ );
			
		} else {
			
			/* Discard the size. */
			res = libandria4_cts_pop_sizet( ctx, 1,  &sz );
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
			
			/* Get the return value. */
			libandria4_cts_closure ret;
			res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
			if( !res )
			{
				return( failfunc );
			}
			
			/*
				( (libandria4_parser_CSV_CSV1_file*)data )->{ libandria4_cts_closure onstr, onval; }
			*/
			return( ret );
		}
	}
	
	return( failfunc );
}
	/* Eventually delegates to either: */
			/* Fetches a character into a string: this consumes characters on a */
			/*  one-to-one basis. */
			/* Upon entry, there must be a "characters not yet read" value on */
			/*  stack[ 1 ] as a size_t, on top of a pascal-string as a */
			/*  void-pointer, where the size_t IS NOT larger than the size of */
			/*  the pascal-string. */
			/* Upon return, there will be a result flag on stack[ 1 ] as a */
			/*  uchar, on top of a "characters not yet read" as a size_t, on */
			/*  top of a pascal-string as a void-pointer. The result will */
			/*  either be 0 for success, or larger than one for a failure. */
		/* libandria4_parser_CSV_CSV1_accumulate_btstring(), */
	/*  or */
			/* As string, but not a string. Not allowed to contain whitespace, commas, */
			/*  or double-quotes. The storage-string gets allocated by this */
			/*  accumulator, just like the *string() version, including with the */
			/*  tag-uchar stored on top of it on stack[1]. */
		/* libandria4_parser_CSV_CSV1_accumulate_nonstring_inner(), */
	/*  depending on whether the "full" bit-torrent string header is */
	/*  detected. Thus, this MUST act like *_nonstring_inner() until */
	/*  either a colon (':') or a non-decimal character. */
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
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		int res;
		unsigned char flag = 0, c, e;
		
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
				/* This takes a fair bit of work, so break out */
				/*  into it's handler. */
				break;
				
				/* The rest of these can be handled with a single */
				/*  compact logic sequence. */
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
			case 1: /* EOF, including nesting characters. */
				/* Ok, we're actually just done. */
				/*
					( (libandria4_parser_CSV_CSV1_file*)data )->{ libandria4_cts_closure onstr, onval; }
				*/
				return( ret );
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
				break;
			case ':':
				/* End of length, so dispatch accordingly. */
				{
					static size_t pretest =
						( SIZE_MAX - ( SIZE_MAX % 10 ) ) / 10;
					int d;
					
					/* Fetch the length string. */
					res = libandria4_cts_pop_uchar( ctx, 1,  &flag );
					if( !res )
					{
						return( failfunc );
					}
					{
						void *a;
						res = libandria4_cts_pop_voidp( ctx, 1,  &a );
						if( !res )
						{
							return( failfunc );
						}
						libandria4_char_pascalarray *b =
							(libandria4_char_pascalarray*)a;
					}
					
					/* Lex/parse the length. */
						/* Requires basic/commonlib.h */
					libandria4_commonlib_intint_eithfork ef = libandria4_atoi( b->len, b->body );
					LIBANDRIA4_COMMONLIB_FORKINGTYPE_BODYMATCH(
						ef,
							LIBANDRIA4_OP_SETdFLAGresAS1,
							LIBANDRIA4_OP_SETeFLAGresASn1 );
					{
						libandria4_result res = libandria4_char_pascalarray_destroy( b );
						b = 0;
					}
					if( res < 0 || d < 0 )
					{
						return( failfunc );
					}
					
					/* Allocate the new string. */
					libandria4_char_pascalarray_result res2 =
						libandria4_char_pascalarray_build( d );
					LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
						res2,
							LIBANDRIA4_OP_SETbFLAGresAS1,
							LIBANDRIA4_OP_SETeFLAGresASn1 );
					if( res < 0 )
					{
						return( failfunc );
					}
					
					/* Store the string and it's length. */
					res = libandria4_cts_push2_voidp( ctx, 1,  (void*)b );
					if( !res )
					{
						return( failfunc );
					}
					res = libandria4_cts_push2_sizet( ctx, 1,  d );
					if( !res )
					{
						return( failfunc );
					}
				}
				
					/* Reroute to the BT-string accumulator code. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_btstring,
					data_ );
			default:
				/* Neither a length character, nor a begin-body */
				/*  character, so re-route to *_nonstring_inner(). */
				
				/* Re-store the character values. */
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
				
				return( nstr );
		}
		
		/* Delegate the string handling & return value. */
		return
		(
			libandria4_parser_CSV_CSV1_accumulate_nonstring_innerhelper
			(
				ctx, data,
				acc, getc, ret, popchar,
				c
			)
		);
	}
	
	return( failfunc );
}
libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_nonstring
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
				&libandria4_parser_CSV_CSV1_accumulate_nonstring_inner,
				data_ ),
			btstr = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_preaccumulate_btstring,
				data_ ),
			getc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_getc_notstring,
				data_ ),
			ret = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d );
		
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		if( libandria4_parser_CSV_CSV1_validate( data ) )
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
			res =
				libandria4_cts_push2_ctsclsr
				(
					ctx, 0,
					( ( data->btStr ) ? btstr : acc )
				);
			if( !res )
			{
				return( failfunc );
			}
			
			/* Route via getc(), to "prime the pump". */
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
				&libandria4_parser_CSV_CSV1_accumulate_nonstring,
				data );
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data ) )
		{
			return( failfunc );
		}
		
		
			??? /* This ios wrong, the character is already on stack[ 1 ]. */
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, flag;
		int res = 0;
		
		??? ( ec ) ;
		??? ( flag ) ;
		
		
		/* Fetch the character. */
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
		
		/* String accumulation. */
		if( flag == 1 )
		{
			return( getstr );
			
		}
		
		/* Token accumulation. */
		if( flag == 0 )
		{
			/* Repush the character for unget(). */
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
			
			/* Push the return target. */
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  gettok );
			if( !res )
			{
				return( failfunc );
			}
			
				/* Build the string via unget(). */
			LIBANDRIA4_CTS_RETURNCLOSURE(
				&libandria4_parser_CSV_CSV1_ungetc,
				data_ );
		}
		
		/* Just fall through for failures. */
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
			
		??? ( res ) ;
		
		
		libandria4_parser_CSV_CSV1_sortchar_categories cat =
			libandria4_parser_CSV_CSV1_sortchar( data, c );
		switch( cat )
		{
			case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
				type = 1;
				break;
				
			/* Plain success. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
				type = 2;
				break;
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
			case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
			case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
				/* We need something "special" for this: it's time to */
				/*  add a "EOF string" value for the return string. */
				??? ;
				
				break;
				
			/* Errors. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
			case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
			default:
				/* Store a "bad string". */
				res = libandria4_cts_push2_voidp( ctx, 1,  (void*)0 );
				if( !res )
				{
					return( failfunc );
				}
				res = libandria4_cts_push2_uchar( ctx, 1,  0 );
				if( !res )
				{
					return( failfunc );
				}
				
				return( ret );
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
		
		/* Return. */
		return( acc );
	}
	
	return( failfunc );
}











/**************************************************************************/
/**************************************************************************/
/** NOTE: The set of functions in the following group are "current", the **/
/**  ones above need to be adapted to match those below. ******************/
/**************************************************************************/
/**************************************************************************/


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
			??? /* If EOF, then retry! Or maybe just fail? */ ;
			
			type = 0;
			
		} else {
			
				/* STOP HARDWIRING! Properly process stuff! */
			type = 3;
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
		
		
		
		/* Return. */
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


/* Note: Finish this function! */
static libandria4_cts_closure libandria4_parser_CSV_CSV1_record_inner
(
	libandria4_cts_context *ctx, void *data_
);
static libandria4_cts_closure libandria4_parser_CSV_CSV1_record_inner_helper
(
	libandria4_cts_closure direct, void *data_
)
{
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
		return( failfunc );
	}
	
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
			return( failfunc );
		}
		res = libandria4_cts_pop_uchar( ctx, 1,  &c );
		if( !res )
		{
			return( failfunc );
		}
		
		
		/* Handle flag. */
		if( flag == 1 )
		{
			/* Full EOF. */
			
			res = libandria4_cts_push2_voidf(
				ctx, 1,
				(void (*)()) &libandria4_parser_CSV_CSV1_record );
			if( !res )
			{
				return( failfunc );
			}
			
			return( data->onfullEOF );
			
		} else if( flag == 2 )
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
				return( failfunc );
			}
			
			
			/* Tail-call to get the character. */
			return
			(
				LIBANDRIA4_CTS_BUILDCLOSURE(
					&libandria4_parser_CSV_CSV1_getc,
					data_ )
			);
			
		} else if( flag != 3 )
		{
			/* Some sort of error. */
			
			res = libandria4_cts_push2_voidf(
				ctx, 1,
				(void (*)()) &libandria4_parser_CSV_CSV1_record );
			if( !res )
			{
				return( failfunc );
			}
			
			return( data->onfatal );
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
			
			/* "Type agnostic" options. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
				return( libandria4_parser_CSV_CSV1_record_inner_helper
							( data->onopen, data_ ) );
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
				return( libandria4_parser_CSV_CSV1_record_inner_helper
							( data->onclose, data_ ) );
			case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				return( libandria4_parser_CSV_CSV1_record_inner_helper
							( data->startfield, data_ ) );
				
			case libandria4_parser_CSV_CSV1_sortchar_categories_doublequote:
			case libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar:
				??? ;
			
			/* Errors. */
			case libandria4_parser_CSV_CSV1_sortchar_categories_invalid:
			case libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs:
			default:
				??? ;
		}
		
		
		
		
		
		
		??? ;
		
		
			LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_value,
				data_ );
			
			
			
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
			
			
			
			/* Fetch the character. */
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
		
		
		??? ;
		
		??? ;
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
				return( data->onfatal );
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
			return( failfunc );
		}
		
			/* Announce the start of this record's first field. */
		if( !( acc.handler ) )
		{
			acc = data->startfield;
			
		} else {
			
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  data->startfield );
			if( !res )
			{
				return( failfunc );
			}
		}
		
		/* Push the direct recipient. */
		res = libandria4_cts_push2_ctsclsr( ctx, 0,  acc );
		if( !res )
		{
			return( failfunc );
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

