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



libandria4_parser_CSV_CSV1_sortchar_categories libandria4_parser_CSV_CSV1_sortchar
(
	libandria4_parser_CSV_CSV1_file *f,
	char character
)
{
	libandria4_parser_CSV_CSV1_sortchar_categories ret =
		libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs;
	
	if( f )
	{
		ret = libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar;
		
		switch( character )
		{
			case ',':
				ret = ( f->commaSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			case ':':
				ret = ( f->colonSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			case ';':
				ret = ( f->semiSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			case ' ':
				ret = ( f->spaceSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
				break;
			case '\t':
				ret = ( f->tabSep ) ? libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep : ret;
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
				ret = ( f->parenNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener : ret;
				break;
			case '[':
				ret = ( f->sqrNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener : ret;
				break;
			case '{':
				ret = ( f->curlNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener : ret;
				break;
			case '<':
				ret = ( f->angleNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener : ret;
				break;
			
			case ')':
				ret = ( f->parenNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser : ret;
				break;
			case ']':
				ret = ( f->sqrNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser : ret;
				break;
			case '}':
				ret = ( f->curlNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser : ret;
				break;
			case '>':
				ret = ( f->angleNest ) ? libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser : ret;
				break;
			
			case '\"':
				ret = libandria4_parser_CSV_CSV1_sortchar_categories_doublequote;
				break;
			
			default: /* Assume it's just normal. */ break;
		}
	}
	
	return( ret );
}
int libandria4_parser_CSV_CSV1_validate( libandria4_parser_CSV_CSV1_file *f )
{
	if( f )
	{
		/* Prohibitions: */
		if( f->btStr && f->colonSep )
		{
			return( 0 );
		}
		/* Do we want to restrict ->recordindex? */
		
		/* Demands: */
		if( !( f->cStr || f->csvStr || f->btStr ) )
		{
			/* At least one string type is required. */
			return( 0 );
		}
		if( !( f->commaSep || f->colonSep || f->semiSep || f->spaceSep || f->tabSep ) )
		{
				/* At least one field seperator is required. */
			return( 0 );
		}
		if( !( f->onfatal.handler && f->onEOF.handler ) )
		{
			return( 0 );
		}
		if( !( f->onopen.handler && f->onclose.handler && f->startfield.handler ) )
		{
			return( 0 );
		}
		if( !( f->onstrchar.handler && f->onexprchar.handler ) )
		{
			return( 0 );
		}
		
		/* Nesting options are neither restricted nor required. */
		/* The ->*rec closures are allowed to be null. */
		
		return( 1 );
	}
	
	return( -1 );
}
libandria4_cts_closure libandria4_parser_CSV_CSV1_onfatal
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
		res = libandria4_cts_push2_voidf( ctx, 1,  (libandria4_common_voidfuncp_void)tag_ptr );
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
			Never return any other values, they're reserved for other
				purposes.
		Stack delta: 0( return target ) 1() -> 0() 1( character, flags )
			(top listed last)
	*/
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc
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
		unsigned char c, type;
		int e, res = 0;
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
		
		
		return( retfunc );
	}
	
	return( failfunc );
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
		unsigned char c, type;
		int res = 0;
		
		
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
			res =
				libandria4_parser_CSV_CSV1_unget
				(
					(libandria4_parser_CSV_CSV1_file*)data_, c
				);
		}
		if( !res )
		{
			/* Failure. */
			return( failfunc );
		}
		
		
		return( retfunc );
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
	if( ctx )
	{
		unsigned char c, type;
		int res = 0;
		
		
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
		
		
		return( retfunc );
	}
	
	return( failfunc );
}




