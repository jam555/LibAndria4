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

/* parsers/CMArgs1/test1.c */
/*  This file exists to test the CMArgs1 system. It's intended behavior is */
/* to compare the result of some test strings to the expected results: */
/* fortunately, CMArgs1 takes explicitly provided string info instead of */
/* hunting down the command-line arguments directly, so this should be */
/* fairly reliable with little effort. */



#include <stdlib.h>

#include "../../basic/simpleops.h"
#include "../../basic/monads.h"
#include "../../basic/bitarray.h"
#include "../../basic/pascalarray.h"
#include "../../basic/commonparrs.h"
#include "../../basic/ctsengine.h"
#include "cmargs.h"



libandria4_cts_closure cls;
libandria4_cts_context ctx;

int test1()
{
	/* To configure: */
	/* strs is the set of strings to imitate a command-line */
	/*  with, and strn is the number of them. */
	/* opts is the set of command-line options: each option */
	/*  needs a static assignment for a name and a set of */
	/*  specs, UNLESS it has no specs, in which case the */
	/*  name is still required. */
	
	static char **strs =
		{
			"",
			"",
			""
		};
		/* ??? Is strn set correctly? */
	static size_t strn = ( sizeof( strs ) / sizeof( char* ) );
	
	
	static libandria4_char_pascalarray **names
	
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		name1,
		arr,
		
		libandria4_char_,
		char,
		
		"" );
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		subs1,
		arr,
		
		libandria4_parser_cmargs1_opt_spec_,
		libandria4_parser_cmargs1_opt_spec,
		
		(libandria4_parser_cmargs1_opt_spec) ,
		(libandria4_parser_cmargs1_opt_spec) ,
		... );
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		opts,
		arr,
		
		libandria4_parser_cmargs1_opt_,
		libandria4_parser_cmargs1_opt,
		
		(libandria4_parser_cmargs1_opt)
		{
			&( name1.arr ),
			&( subs1.arr ),
			
			/* handler */,
			/* abbrev */,
			
			(char)'' /* name_abbrev */
		},
		(libandria4_parser_cmargs1_opt)
		{
			???
		},
		... );
	
	
	static libandria4_parser_cmargs1_arginfo arginf =
		{
			strn, strs,
			
			/* onfatal */,
			/* onshortfall */,
			/* onoptless */,
			
			&( opts.arr ),
			
			(libandria4_parser_cmargs1_opt*)0,
			0, 0, 0
		};
	
	
	if( strn < ??? )
	{
		return( -1 );
	}
	
	
	ctx.run = ??? ;
	ctx.next_iteration = (libandria4_cts_closure) ??? ;
	??? ;
	
	
	res = libandria4_cts_engine( &ctx );
	if( res ??? )
	{
	}
	
	
	??? ;
}
/*
	#define LIBANDRIA4_CTS_DECPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  type *val );
	
	
	
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
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _voidf, libandria4_common_voidfuncp_void );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );
	
	
	
	
	
	
	struct libandria4_cts_closure
	{
		libandria4_cts_framefunc handler;
		void *data;
	};
*/

int main( int argn, char *args[] )
{
	int res;
	
	
	{
		libandria4_charparrptr_pascalarray_result tmp =
			libandria4_charparrptr_pascalarray_build( 3 );
		libandria4_charparrptr_pascalarray *a;
		libandria4_failure_uipresult e;
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			??? ;
			return( EXIT_FAILURE );
		}
		ctx.stacks;
	}
	{
		libandria4_char_pascalarray_result tmp;
		libandria4_char_pascalarray *a;
		libandria4_failure_uipresult e;
		
		tmp = libandria4_char_pascalarray_build
			(
				sizeof( libandria4_cts_closure ) *
				???
			);
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			??? ;
			return( EXIT_FAILURE );
		}
		ctx.stacks->body[ 0 ];
		
		tmp = libandria4_char_pascalarray_build
			(
				sizeof( ??? ) *
				???
			);
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			??? ;
			return( EXIT_FAILURE );
		}
		ctx.stacks->body[ 1 ];
		
		tmp = libandria4_char_pascalarray_build
			(
				sizeof( ??? ) *
				???
			);
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			??? ;
			return( EXIT_FAILURE );
		}
		ctx.stacks->body[ 2 ];
	}
	
	{
		libandria4_sizet_pascalarray_result tmp;
		libandria4_sizet_pascalarray *a;
		libandria4_failure_uipresult e;
		
		tmp = libandria4_sizet_pascalarray_build( ??? );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			??? ;
			return( EXIT_FAILURE );
		}
		ctx.align;
		
		tmp = libandria4_sizet_pascalarray_build( ??? );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			??? ;
			return( EXIT_FAILURE );
		}
		ctx.used;
		
		tmp = libandria4_sizet_pascalarray_build( ??? );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			??? ;
			return( EXIT_FAILURE );
		}
		ctx.alignreq;
	}
	
	{
		/* libandria4_result libandria4_bitarray_destroy( libandria4_bitarray *barr ); */
		libandria4_bitarray_result tmp =
			libandria4_bitarray_build( ??? );
		libandria4_bitsurface *a;
		int e;
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			??? ;
			return( EXIT_FAILURE );
		}
		ctx.reallocatable = a;
	}
	
	
	res = libandria4_cts_isvalid( &ctx );
	if( res ??? )
	{
	}
	res = libandria4_cts_isvalid2( &ctx );
	if( res ??? )
	{
	}
	
	
	
	??? ;
	
	
	res = test1();
	if( res ??? )
	{
	}
	
	
	??? ;
	
	
	
	/* We don't even TRY to deallocate anything. Bad for real-world */
	/*  use, but works for discrete test programs like this one. */
	
	return( EXIT_SUCCESS );
}
