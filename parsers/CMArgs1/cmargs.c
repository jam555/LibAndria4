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



#include <string.h>



#include "cmargs.h"



static libandria4_cts_innerreturn_data iret_d =
	{ 0, &libandria4_cts_innerreturn_returnstop, 0 };

static libandria4_cts_closure
	failfunc = LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_cts_framefunc_stoprun,
		(void*)&failfunc ),
	retfunc = LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_cts_innerreturn,
		(void*)&iret_d );



int libandria4_parser_cmargs1_arginfo_invalid( libandria4_parser_cmargs1_arginfo *arginf )
{
	if( arginf )
	{
		if( !( arginf->argn ) != !( arginf->args ) )
		{
			return( 2 );
		}
		if( !( arginf->onfatal.handler ) )
		{
			return( 3 );
		}
		if( !( arginf->onshortfall.handler ) )
		{
			return( 3 );
		}
		
		if( !( arginf->opts_list ) )
		{
			return( 4 );
		}
		
		if( !( arginf->opts_list ) && ( arginf->acti_progress ) )
		{
			return( 5 );
		}
			/* acti_progress==0 is reserved for "none selected". */
		if( arginf->opts_list->len < arginf->acti_progress )
		{
			return( 6 );
		}
		if( arginf->argn <= arginf->arg_progress )
		{
			return( 7 );
		}
		
		if( arginf->acti_opt )
		{
			if( !( arginf->acti_opt->name ) )
			{
				return( 8 );
			}
			
			if( !( arginf->acti_opt->subarg_specifiers ) && ( arginf->sub_progress ) )
			{
				return( 9 );
			}
			if( arginf->acti_opt->subarg_specifiers->len != arginf->sub_progress )
			{
				return( 10 );
			}
		}
		
		
		if( 0 )
		{
			return( 0 );
		}
	}
	
	return( 1 );
}
int libandria4_parser_cmargs1_arginfo_invalidopts
(
	libandria4_parser_cmargs1_opt_pascalarray *opts,
	size_t *last
)
{
	if( opts )
	{
		size_t alt_, elem, bit, other;
		if( !last )
		{
			last = &alt_;
		}
		char abbrev_mask[ 32 ] = { 0 }, opt;
		*last = 0;
		
		
		/* Check all the options. */
		while( opts->len > *last )
		{
			opt = opts->body[ *last ].name_abbrev;
			bit = opt & 7;
			elem = ( opt - bit ) >> 3;
			
				/* Check for single-char overlaps. */
			if( abbrev_mask[ elem ] & ( 1 << bit ) )
			{
				return( 2 );
				
			} else {
				
				abbrev_mask[ elem ] |= ( 1 << bit );
			}
			
				/* Check for name overlaps. */
			other = 0;
			while( opts->len < other )
			{
				if
				(
					other != *last &&
					strcmp( opts->body[ *last ].name->body, opts->body[ other ].name->body )
				)
				{
					return( 3 );
				}
				
				++other;
			}
			
			/* Check the specifier values. */
			if( opts->body[ *last ].subarg_specifiers )
			{
				libandria4_parser_cmargs1_opt_spec_pascalarray *sub =
					opts->body[ *last ].subarg_specifiers;
				other = 0;
				while( sub->len > other )
				{
					if( sub->body[ other ] <= libandria4_parser_cmargs1_opt_spec__NULL )
					{
						return( 4 );
						
					} else if( sub->body[ other ] >= libandria4_parser_cmargs1_opt_spec__PASTEND )
					{
						return( 5 );
					}
					
					++other;
				}
			}
			
			++( *last );
		}
		
		
		return( 0 );
	}
	
	return( 1 );
}

libandria4_cts_closure libandria4_parser_cmargs1_arginfo_onfatal
(
	libandria4_cts_context *ctx, void *data_,
	libandria4_cts_framefunc tag_ptr, void *tag2, unsigned int tag3
)
{
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		if( libandria4_parser_cmargs1_arginfo_invalid( data ) )
		{
			return( failfunc );
		}
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



static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse__errdispatch1
(
	libandria4_cts_context *ctx, void *data_,
	
	char *spec, int res
)
{
	if( ctx && data_ )
	{
		switch( res )
		{
			case 1:
			case 2:
				res = LIBANDRIA4_RESULT_GENERICTRUE;
				break;
			case -1: /* Null ctx. */
				res = LIBANDRIA4_RESULT_FAILURE_NOTCONN;
				break;
			case -2: /* Persistent push failure. */
				res = LIBANDRIA4_RESULT_FAILURE_TOODEEP;
				break;
			case -3: /* Couldn't grow stack. */
				res = LIBANDRIA4_RESULT_FAILURE_MEMORYFULL;
				break;
			case -4: /* Abnormal monad decode. */
				res = LIBANDRIA4_RESULT_FAILURE_CORRUPTED;
				break;
			case -5: /* Unknown push result. */
				res = LIBANDRIA4_RESULT_FAILURE_RANGE;
				break;
			default: /* Unknown. */
				res = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED;
				break;
		}
		if( res != LIBANDRIA4_RESULT_GENERICTRUE )
		{
				libandria4_parser_cmargs1_arginfo_RETONFATAL(
					ctx, data_,
					
					(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
					(void*)spec, res );
		}
		
		return( retfunc );
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}



/*
	i			 Integer				 Any number of digits,
	 optionally preceded by a sign (+ or -). Decimal digits
	 assumed by default (0-9), but a 0 prefix introduces octal
	 digits (0-7), and 0x hexadecimal digits (0-f). Signed
	 argument.
*/
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_genint( libandria4_cts_context *ctx, void *data_ )
{
	char *spec = " %i";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		int val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		res = libandria4_cts_push2_sint( ctx, 1,  val );
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}

/*
	d or u		 Decimal integer		 Any number of decimal
	 digits (0-9), optionally preceded by a sign (+ or -). d is
	 for a signed argument, and u for an unsigned.
*/
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_sdec( libandria4_cts_context *ctx, void *data_ )
{
	char *spec = " %d";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		int val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		res = libandria4_cts_push2_sint( ctx, 1,  val );
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_udec( libandria4_cts_context *ctx, void *data_ )
{
	char *spec = " %u";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		unsigned val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		res = libandria4_cts_push2_uint( ctx, 1,  val );
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}

/*
	o			 Octal integer			 Any number of octal
	 digits (0-7), optionally preceded by a sign (+ or -).
	 Unsigned argument.
*/
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_octdec( libandria4_cts_context *ctx, void *data_ )
{
	char *spec = " %o";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		unsigned val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		res = libandria4_cts_push2_uint( ctx, 1,  val );
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}

/*
	x			 Hexadecimal integer	 Any number of
	 hexadecimal digits (0-9, a-f, A-F), optionally preceded by
	 0x or 0X, and all optionally preceded by a sign (+ or -).
	 Unsigned argument.
*/
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_hexdec( libandria4_cts_context *ctx, void *data_ )
{
	char *spec = " %x";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		unsigned val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		res = libandria4_cts_push2_uint( ctx, 1,  val );
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}

/*
	f, e, g	 Floating point number	 A series of decimal
	 digits, optionally containing a decimal point, optionally
	 preceeded by a sign (+ or -) and optionally followed by
	 the e or E character and a decimal integer (or some of the
	 other sequences supported by strtod).
*/
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_float( libandria4_cts_context *ctx, void *data_ )
{
	char *spec = " %f";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		float val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		res = libandria4_cts_push2_float( ctx, 1,  val );
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}

/*
	a			 Floating point number	 As f, e, or g, but
	 implementations complying with C99 also support
	 hexadecimal floating-point format when preceded by 0x or
	 0X.
*/
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_altfloat( libandria4_cts_context *ctx, void *data_ )
{
	char *spec = " %a";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		float val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		res = libandria4_cts_push2_float( ctx, 1,  val );
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}

/*
	c			 Character				 The next character. If
	 a width other than 1 is specified, the function reads
	 exactly width characters and stores them in the successive
	 locations of the array passed as argument. No null
	 character is appended at the end.
*/
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_char( libandria4_cts_context *ctx, void *data_ )
{
	char *spec = " %a";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		char val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		#if CHAR_MIN < 0
			res = libandria4_cts_push2_schar( ctx, 1,  val );
		#elif CHAR_MIN >= 0
			res = libandria4_cts_push2_uchar( ctx, 1,  val );
		#else
			#error "cmargs.c couldn't find a preprocessor CHAR_MIN."
		#endif
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}

static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_string( libandria4_cts_context *ctx, void *data_ )
{
		/* This is just for the sake of using the same error reporting pattern. */
	char *spec = " %s";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		
		
		/* Retrieve the string from the (theoretically) program argument, and store into a pascal-string. */
		size_t len = strlen( data->args[ data->arg_progress ] );
		libandria4_char_pascalarray_result strres =
			libandria4_char_pascalarray_buildNfill( len, data->args[ data->arg_progress ] );
		
		libandria4_char_pascalarray *a;
		libandria4_failure_uipresult e;
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( strres,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		if( res == -1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
			
		} else if( res != 1 )
		{
			
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_CORRUPTED );
		}
		
		
		
		res = libandria4_cts_push2_voidp( ctx, 1,  (void*)a );
		return
		(
			libandria4_parser_cmargs1_arginfo_parse__errdispatch1( ctx, data_, spec, res )
		);
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}


	/* The entry-function. Oversees the parsing of the set of strings provided by data_. */
libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse( libandria4_cts_context *ctx, void *data_ )
{
		/* This is just for the sake of using the same error reporting pattern. */
	char *spec = " ";
	
	if( ctx && data_ )
	{
			/* Must be kept in alignment with */
			/*  libandria4_parser_cmargs1_opt_spec{}. */
		static libandria4_cts_framefunc handlers[] =
			{
				&libandria4_parser_cmargs1_arginfo_parse_genint,
				&libandria4_parser_cmargs1_arginfo_parse_sdec,
				&libandria4_parser_cmargs1_arginfo_parse_udec,
				&libandria4_parser_cmargs1_arginfo_parse_octdec,
				&libandria4_parser_cmargs1_arginfo_parse_hexdec,
				
				&libandria4_parser_cmargs1_arginfo_parse_float,
				&libandria4_parser_cmargs1_arginfo_parse_altfloat,
				&libandria4_parser_cmargs1_arginfo_parse_char,
				&libandria4_parser_cmargs1_arginfo_parse_string
			};
		
		libandria4_cts_closure
			iter = LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_parser_cmargs1_arginfo_parse,
				data_ );
		
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_invalid( data );
		if( res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		
		
		++( data->arg_progress );
		libandria4_parser_cmargs1_opt *opt = 0;
		if( data->argn <= data->arg_progress )
		{
			/* Done with args, clean up. */
			
			if( data->acti_opt->subarg_specifiers->len > data->sub_progress + 1 )
			{
				/* This only works right if we run the first subarg BEFORE cycling around again. */
				
				return( arginf->onshortfall );
				
			} else {
				
				return( retfunc );
			}
			
		} else if( data->acti_progress )
		{
			/* Triggered option has sub-args. */
			
			if
			(
				data->acti_opt->subarg_specifiers->len > data->sub_progress + 1
			)
			{
				++( data->sub_progress );
				
				/* We need to recurse. */
				res = libandria4_cts_push2_ctsclsr( ctx, 0,  iter );
				if( !res )
				{
					return( failfunc );
				}
				
				LIBANDRIA4_CTS_RETURNCLOSURE(
					handlers
					[
						data->acti_opt->subarg_specifiers->body
						[
							data->sub_progress
						] - 1
					],
					data_ );
				
			} else {
				
				opt = data->acti_opt;
				data->acti_opt = 0;
				data->acti_progress = 0;
				
				if( data->argn > data->arg_progress )
				{
					/* We need to recurse. */
					res = libandria4_cts_push2_ctsclsr( ctx, 0,  iter );
					if( !res )
					{
						return( failfunc );
					}
				}
				
				return( opt->handler );
			}
			
		} else {
			
			/* Look for the next option. */
			
			size_t i = 0;
			
			/* We need to prepare to recurse. */
			res = libandria4_cts_push2_ctsclsr( ctx, 0,  iter );
			if( !res )
			{
				return( failfunc );
			}
			
			if( data->args[ data->arg_progress - 1 ] )
			{
				if( data->args[ data->arg_progress - 1 ][ 0 ] == '-' )
				{
					/* "Proper" args. */
					
					if( data->args[ data->arg_progress - 1 ][ 1 ] == '-' )
					{
						/* Long args. */
						
						while( data->opts_list->len > i && !opt )
						{
							if( strcmp( opts->body[ i ].name, ( data->args[ data->arg_progress - 1 ] ) + 2 ) != 0 )
							{
								opt = &( opts->body[ i ] );
							}
							
							++i;
						}
						
						if( opt )
						{
							/* Match found. */
							
							if( !( opt->subarg_specifiers ) || opt->subarg_specifiers->len <= 0 )
							{
								iter = opt->handler;
								
							} else {
								
								/* Queue up the first sub-argument hook. */
								iter = LIBANDRIA4_CTS_BUILDCLOSURE(
									handlers
									[
										data->acti_opt->subarg_specifiers->body
										[
											data->sub_progress
										] - 1
									],
									data_ );
								
								/* Bookkeeping. */
								data->acti_progress = 1;
								data->acti_opt = opt;
							}
							
						} else {
							
							/* Didn't find a match. */
							
							iter = data->onoptless;
						}
						
					} else {
						
						/* Short args (no sub-arguments allowed). */
						
						size_t ci = 0;
						
						while( data->args[ data->arg_progress - 1 ][ ci ] != '\0' )
						{
							++ci;
						}
						
						while( ci )
						{
							i == 0;
							iter = data->onoptless;
							while( data->opts_list->len > i && !opt )
							{
								if( opts->body[ i ]->name_abbrev == data->args[ data->arg_progress - 1 ][ ci ] )
								{
									iter = opts->body[ i ]->abbrev;
								}
								
								++i;
							}
							
							--ci;
							
							if( ci )
							{
								/* We need to recurse. */
								res = libandria4_cts_push2_ctsclsr( ctx, 0,  iter );
								if( !res )
								{
									iter = failfunc;
									
								}
							}
						}
					}
					
				} else {
					
					/* "Improper" args. */
					
					iter = data->onoptless;
				}
				
			} else {
				
				/* There WAS NO string for the argument. */
			}
		}
		
		return( iter );
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}
