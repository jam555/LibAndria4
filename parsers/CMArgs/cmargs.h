#ifndef LIBANDRIA4_PARSER_CMARGS1_CMARGS_H
 #define LIBANDRIA4_PARSER_CMARGS1_CMARGS_H
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
	
	
	#include <stdio.h>
	#include <ctype.h>
	
		/* For libandria4_commonlib_firstchars[]. */
	#include "../../basic/commonlib.h"
		/* For the continuation-trampoline-style engine & related definitions. */
		/* Usually stack[ 0 ] should be a return/C stack. A FORTH data */
		/*  stack should be stack[ 1 ]. Stack[ 2 ] is used for string building. */
	#include "../../basic/ctsengine.h"
		/* For pascal-array, libandria4_char_pascalarray{}, and */
		/*  libandria4_charparrptr_pascalarray{}. */
	#include "../../basic/commonparrs.h"
	
	
	
	typedef struct libandria4_parser_cmargs1_arginfo libandria4_parser_cmargs1_arginfo;
	typedef struct libandria4_parser_cmargs1_opt libandria4_parser_cmargs1_opt;
	
	struct libandria4_parser_cmargs1_opt
	{
		libandria4_char_pascalarray *name;
			/* Note: switch this to an array of ints or something. */
		libandria4_charparrptr_pascalarray *subarg_specifiers;
		
		char name_abbrev;
	};
	
	LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( libandria4_parser_cmargs1_opt_, libandria4_parser_cmargs1_opt );
	/* libandria4_parser_cmargs1_opt_pascalarray{} is now available. */
	
	struct libandria4_parser_cmargs1_arginfo
	{
		int argn;
		char **argc;
		libandria4_parser_cmargs1_opt_pascalarray *opts_list;
			/* Use this to restrict the risk of reading past the end of a buffer. */
		size_t arglenmax;
		
		libandria4_parser_cmargs1_opt *acti_opt;
		size_t acti_progress, arg_progress;
	};
	
	
	
	
	int libandria4_parser_cmargs1_arginfo_validate( libandria4_parser_cmargs1_arginfo* );
	libandria4_cts_closure libandria4_parser_cmargs1_arginfo_onfatal
	(
		libandria4_cts_context *ctx, void *data_,
		libandria4_cts_framefunc tag_ptr, void *tag2, unsigned int tag3
	);
	
	#define libandria4_parser_cmargs1_arginfo_RETONFATAL( ctxptr, dataptr, funcptr, sec_id, thrd_id ) \
		return( \
			libandria4_parser_cmargs1_arginfo_onfatal( \
				(ctxptr), (dataptr), \
				(funcptr), \
				(void*)&( libandria4_commonlib_firstchars[ (sec_id) ] ), \
				(thrd_id) ) )
	
	
	
	
	
	libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse( libandria4_cts_context *ctx, void *data_ );
	
	/* End parsers/cmargs1/cmargs.h */
	
#endif

/* This line and below belong to the .c file. */




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
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		int val;
		res = sscanf( data->argc[ data->arg_progress ], spec, &val );
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
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		int val;
		res = sscanf( data->argc[ data->arg_progress ], spec, &val );
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
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		unsigned val;
		res = sscanf( data->argc[ data->arg_progress ], spec, &val );
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
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		unsigned val;
		res = sscanf( data->argc[ data->arg_progress ], spec, &val );
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
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		unsigned val;
		res = sscanf( data->argc[ data->arg_progress ], spec, &val );
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
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		float val;
		res = sscanf( data->argc[ data->arg_progress ], spec, &val );
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
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		float val;
		res = sscanf( data->argc[ data->arg_progress ], spec, &val );
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
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		char val;
		res = sscanf( data->argc[ data->arg_progress ], spec, &val );
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

/*
*/
static libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse_string( libandria4_cts_context *ctx, void *data_ )
{
		/* This is just for the sake of using the same error reporting pattern. */
	char *spec = " %s";
	
	if( ctx && data_ )
	{
		libandria4_parser_cmargs1_arginfo *data =
			(libandria4_parser_cmargs1_arginfo*)data_;
		int res = libandria4_parser_cmargs1_arginfo_validate( data );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->argc[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&libandria4_parser_cmargs1_arginfo_parse,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		
		
			/* Retrieve the string from the (theoretically) program argument, and store into a pascal-string. */
		??? ;
		
		/* data->argc[ data->arg_progress ] */
		
		??? ;
		
		
		
		res = libandria4_cts_push2_voidp( ctx, 1,  (void*) ??? );
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
