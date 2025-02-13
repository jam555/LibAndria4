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
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data )
	{
		libandria4_cts_closure
			getstr = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_string,
				data_ ),
			gettok = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_nonstring_inner,
				data_ ),
			getbtstr = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_preaccumulate_btstring,
				data_ );
		
		if( libandria4_parser_CSV_CSV1_validate(
			(libandria4_parser_CSV_CSV1_file*)data_ ) )
		{
			return( failfunc );
		}
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		
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
				if( data->cStr || data->csvStr )
				{
					/* Push the return target. */
					res = libandria4_cts_push2_ctsclsr( ctx, 0,  getstr );
					if( !res )
					{
						libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 7 );
					}
					
					/* We aren't repushing the character we've read, so fetch the next instead. */
					LIBANDRIA4_CTS_RETURNCLOSURE(
						&libandria4_parser_CSV_CSV1_getc_string,
						data_ );
				}
				
				/* We aren't supporting C-style OR CSV-style strings, */
				/*  so just fall-through. */
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
				
					/* If we're going for the BT-string, we need to prep the receiver string. */
				??? ;
				
				/* If a BitTorrent string, push a length of 0 for initial accumulation. */
				if( data->btStr )
				{
					res = libandria4_cts_push2_uchar( ctx, 2,  0 );
					if( !res )
					{
						libandria4_parser_CSV_CSV1_accval_RETONFATAL( 1, 5 );
					}
				}
				
				return( ( data->btStr ) ? getbtstr : gettok );
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener:
			case libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser:
			case libandria4_parser_CSV_CSV1_sortchar_categories_recordsep:
			case libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep:
				return( retfunc );
			
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
		libandria4_cts_closure
			acc = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_CSV_CSV1_accumulate_value_inner,
				data );
		
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
					
					return( retfunc );
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
				cls = popchar;
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

libandria4_cts_closure libandria4_parser_CSV_CSV1_record
(
	libandria4_cts_context *ctx, void *data_
)
{
	return
	(
		LIBANDRIA4_CTS_BUILDCLOSURE(
			&libandria4_parser_CSV_CSV1_record,
			data_ )
	);
}
