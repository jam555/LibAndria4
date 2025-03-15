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




static libandria4_cts_innerreturn_data iret_d =
	{ 0, &libandria4_cts_innerreturn_returnstop, 0 };

static libandria4_cts_closure
	failfunc = LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_cts_framefunc_stoprun,
		(void*)&failfunc ),
	retfunc = LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_cts_innerreturn,
		(void*)&iret_d );



libandria4_cts_closure onfatal( libandria4_cts_context *ctx, void *data_ )
{
	{
		printf( "\nonfatal() was called.\n" );
		/* return( EXIT_FAILURE ); */
	}
	
	return( failfunc );
}
libandria4_cts_closure onshortfall( libandria4_cts_context *ctx, void *data_ )
{
	{
		printf( "\nonshortfall() was called.\n" );
		/* return( EXIT_FAILURE ); */
	}
	
	return( failfunc );
}
libandria4_cts_closure onoptless( libandria4_cts_context *ctx, void *data_ )
{
	{
		printf( "\nonoptless() was called.\n" );
		/* return( EXIT_FAILURE ); */
	}
	
	return( failfunc );
}

libandria4_cts_closure nullactor( libandria4_cts_context *ctx, void *data_ )
{
	if( ctx )
	{
		return( retfunc );
	}
	
	return( failfunc );
}
libandria4_cts_closure doubleint_actor( libandria4_cts_context *ctx, void *data_ )
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
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( data->arg_progress >= data->argn )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		int val;
		
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		++( data->arg_progress );
		res = libandria4_cts_push2_sint( ctx, 1,  val );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED );
		}
		
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		++( data->arg_progress );
		res = libandria4_cts_push2_sint( ctx, 1,  val );
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&doubleint_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED );
		}
		
		return( retfunc );
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&doubleint_actor,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}
	/* This was just copied from cmargs.h, to handle the "abbrev" case for a */
	/*  single-character fetch. Take that as an indication of how to actually */
	/*  et values for those cases. */
static libandria4_cts_closure char_actor( libandria4_cts_context *ctx, void *data_ )
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
				
				(libandria4_cts_framefunc)&char_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED );
		}
		if( !( data->args[ data->arg_progress ] ) )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&char_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		}
		
		char val;
		res = sscanf( data->args[ data->arg_progress ], spec, &val );
		if( res == EOF )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&char_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_EOF );
			
		} else if( res != 1 )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&char_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		++( data->arg_progress );
		
		#if CHAR_MIN < 0
			res = libandria4_cts_push2_schar( ctx, 1,  val );
		#elif CHAR_MIN >= 0
			res = libandria4_cts_push2_uchar( ctx, 1,  val );
		#else
			#error "cmargs.c couldn't find a preprocessor CHAR_MIN."
		#endif
		if( !res )
		{
			libandria4_parser_cmargs1_arginfo_RETONFATAL(
				ctx, data_,
				
				(libandria4_cts_framefunc)&char_actor,
				(void*)spec, LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED );
		}
		
		
		return( retfunc );
	}
	
	libandria4_parser_cmargs1_arginfo_RETONFATAL(
		ctx, data_,
		
		(libandria4_cts_framefunc)&char_actor,
		(void*)spec, LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}



libandria4_cts_closure cls;
libandria4_cts_context ctx;

int test1()
{
	static libandria4_parser_cmargs1_arginfo arginf;
	
	/* To configure: */
	/* opts is the set of command-line options: each option */
	/*  needs a static assignment for a name and a set of */
	/*  specs, UNLESS it has no specs, in which case the */
	/*  name is still required. */
	/* strs is the set of strings to imitate a command-line */
	/*  with, and strn is the number of them. */
	
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		name_dint,
		arr,
		
		libandria4_char_,
		char,
		
		"int*2" );
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		name_char,
		arr,
		
		libandria4_char_,
		char,
		
		"char*1" );
	
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		subs_dint,
		arr,
		
		libandria4_parser_cmargs1_opt_spec_,
		libandria4_parser_cmargs1_opt_spec,
		
		libandria4_parser_cmargs1_opt_spec__generint,
		libandria4_parser_cmargs1_opt_spec__generint );
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		subs_char,
		arr,
		
		libandria4_parser_cmargs1_opt_spec_,
		libandria4_parser_cmargs1_opt_spec,
		
		libandria4_parser_cmargs1_opt_spec__char );
	
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		opts,
		arr,
		
		libandria4_parser_cmargs1_opt_,
		libandria4_parser_cmargs1_opt,
		
		(const libandria4_parser_cmargs1_opt)
		{
			&( name_dint.arr ),
			&( subs_dint.arr ),
			
			LIBANDRIA4_CTS_BUILDCONSTCLOSURE( &nullactor, (void*)&arginf ) /* handler */,
			LIBANDRIA4_CTS_BUILDCONSTCLOSURE( &doubleint_actor, (void*)&arginf ) /* abbreviation handler */,
			
			(char)'I' /* name_abbrev */
		},
		(const libandria4_parser_cmargs1_opt)
		{
			&( name_char.arr ),
			&( subs_char.arr ),
			
			LIBANDRIA4_CTS_BUILDCONSTCLOSURE( &nullactor, (void*)&arginf ) /* handler */,
			LIBANDRIA4_CTS_BUILDCONSTCLOSURE( &char_actor, (void*)&arginf ) /* abbreviation handler */,
			
			(char)'c' /* name_abbrev */
		} );
	
	
	
	
	static char
		*str1[] = { "--int*2", "2", "3", "\0" },
		*str2[] = { "--char*1", "c", "\0" },
		*str3[] = { "--int*2", "5", "9", "--char*1", "q", "\0" },
		**strs[] = { str1, str2, str3 };
		/* ??? Is strn set correctly? */
	static size_t strn[ 3 ] =
		{
			( sizeof( strs[ 0 ] ) / sizeof( char* ) ) - 1,
			( sizeof( strs[ 1 ] ) / sizeof( char* ) ) - 1,
			( sizeof( strs[ 2 ] ) / sizeof( char* ) ) - 1
		};
	if( strn[ 0 ] != 3 )
	{
		return( -1 );
	}
	if( strn[ 1 ] != 2 )
	{
		return( -1 );
	}
	if( strn[ 2 ] != 5 )
	{
		return( -1 );
	}
	arginf =
		(libandria4_parser_cmargs1_arginfo)
		{
			0, (char**)0,
			
			&onfatal,
			&onshortfall,
			&onoptless,
			
			&( opts.arr ),
			
			/* (libandria4_parser_cmargs1_opt*)0 */
			(libandria4_cts_closure (*)(libandria4_cts_context *, void *))0, /* ??? */
			0, 0, 0
		};
	
	
	int res, l, r;
	char c;
	
	
		/* This runs: "--int*2" with "2", "3", "\0" .*/
	ctx.next_iteration =
		(libandria4_cts_closure)
		{
			&libandria4_parser_cmargs1_arginfo_parse,
			&arginf
		};
	ctx.run = -1;
	arginf.argn = strn[ 0 ];
	arginf.args = strs[ 0 ];
	res = libandria4_cts_engine( &ctx );
	if( !res )
	{
		printf( "  libandria4_cts_engine( double-int ) returned %i.\n", res );
		return( -1 );
	}
	res = libandria4_cts_pop_sint( &ctx, 1,  &r );
	if( !res )
	{
		printf( "  libandria4_cts_pop_sint()::right returned %i.\n", res );
		return( -1 );
	}
	if( r != 3 )
	{
		printf( "  libandria4_cts_pop_sint()::right popped %i instead of 3.\n", r );
		return( -1 );
	}
	res = libandria4_cts_pop_sint( &ctx, 1,  &l );
	if( !res )
	{
		printf( "  libandria4_cts_pop_sint()::left returned %i.\n", res );
		return( -1 );
	}
	if( l != 2 )
	{
		printf( "  libandria4_cts_pop_sint()::left popped %i instead of 2.\n", l );
		return( -1 );
	}
	
	
		/* This runs: "--char*1" with "c", "\0" .*/
	ctx.next_iteration =
		(libandria4_cts_closure)
		{
			&libandria4_parser_cmargs1_arginfo_parse,
			&arginf
		};
	ctx.run = -1;
	arginf.argn = strn[ 1 ];
	arginf.args = strs[ 1 ];
	res = libandria4_cts_engine( &ctx );
	if( !res )
	{
		printf( "  libandria4_cts_engine( double-int ) returned %i.\n", res );
		return( -1 );
	}
	#if !defined( CHAR_MIN )
		#error "cmargs test1.c couldn't find a preprocessor CHAR_MIN."
	#elif CHAR_MIN < 0
		res = libandria4_cts_pop_schar( &ctx, 1,  &c );
	#elif CHAR_MIN >= 0
		res = libandria4_cts_pop_uchar( &ctx, 1,  &c );
	#endif
	if( !res )
	{
		printf( "  libandria4_cts_pop_ * char() returned %i.\n", res );
		return( -1 );
	}
	if( c != 'c' )
	{
		printf( "  libandria4_cts_pop_ * char() popped %c instead of \'c\'.\n", c );
		return( -1 );
	}
	
	
		/* This runs: "--int*2", then "--char*1", with  "5", "9", "q", "\0" .*/
	ctx.next_iteration =
		(libandria4_cts_closure)
		{
			&libandria4_parser_cmargs1_arginfo_parse,
			&arginf
		};
	ctx.run = -1;
	arginf.argn = strn[ 2 ];
	arginf.args = strs[ 2 ];
	res = libandria4_cts_engine( &ctx );
	if( !res )
	{
		printf( "  libandria4_cts_engine( double-int, char ) returned %i.\n", res );
		return( -1 );
	}
	#if !defined( CHAR_MIN )
		#error "cmargs test1.c couldn't find a preprocessor CHAR_MIN."
	#elif CHAR_MIN < 0
		res = libandria4_cts_pop_schar( &ctx, 1,  &c );
	#elif CHAR_MIN >= 0
		res = libandria4_cts_pop_uchar( &ctx, 1,  &c );
	#endif
	if( !res )
	{
		printf( "  libandria4_cts_pop_ * char() returned %i.\n", res );
		return( -1 );
	}
	if( c != 'q' )
	{
		printf( "  libandria4_cts_pop_ * char() popped %c instead of \'q\'.\n", c );
		return( -1 );
	}
	res = libandria4_cts_pop_sint( &ctx, 1,  &r );
	if( !res )
	{
		printf( "  libandria4_cts_pop_sint()::right returned %i.\n", res );
		return( -1 );
	}
	if( r != 9 )
	{
		printf( "  libandria4_cts_pop_sint()::right popped %i instead of 9.\n", r );
		return( -1 );
	}
	res = libandria4_cts_pop_sint( &ctx, 1,  &l );
	if( !res )
	{
		printf( "  libandria4_cts_pop_sint()::left returned %i.\n", res );
		return( -1 );
	}
	if( l != 5 )
	{
		printf( "  libandria4_cts_pop_sint()::left popped %i instead of 5.\n", l );
		return( -1 );
	}
	
	
	
	return( 1 );
}

int main( int argn, char *args[] )
{
	int res;
	
	
	printf( "\n\nStarting cmargs1 test1.c.\n" );
	
	
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
			printf( "  cmargs failed to allocate ctx.stacks. Exiting.\n" );
			return( EXIT_FAILURE );
		}
		ctx.stacks = a;
	}
	{
		libandria4_char_pascalarray_result tmp;
		libandria4_char_pascalarray *a;
		libandria4_failure_uipresult e;
		
		tmp = libandria4_char_pascalarray_build
			(
				sizeof( libandria4_cts_closure ) *
				16 /* Just some rando value. I don't recall if this will be enough. */
			);
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			printf( "  cmargs failed to allocate ctx.stacks->body[ 0 ]. Exiting.\n" );
			return( EXIT_FAILURE );
		}
		ctx.stacks->body[ 0 ] = a;
		
		tmp = libandria4_char_pascalarray_build
			(
				sizeof( char ) *
				25 /* The characters in the largest case are 25, */ +
				sizeof( int ) *
				2 /*  which encodes two ints, */ +
				sizeof( char ) *
				1 /*  and 1 more char. */
			);
			/* Maybe that's enough data space? */
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			printf( "  cmargs failed to allocate ctx.stacks->body[ 1 ]. Exiting.\n" );
			return( EXIT_FAILURE );
		}
		ctx.stacks->body[ 1 ] = a;
		
		tmp = libandria4_char_pascalarray_build
			(
				sizeof( void* ) *
				4 /* Honestly, I don't think this is even used, so let's just allocate some nonsense amount. */
			);
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			printf( "  cmargs failed to allocate ctx.stacks->body[ 2 ]. Exiting.\n" );
			return( EXIT_FAILURE );
		}
		ctx.stacks->body[ 2 ] = a;
	}
	/* All of the other arrays need to be the same size as ctx.stacks, so we'll just use it's length value for them. */
	
	{
		libandria4_sizet_pascalarray_result tmp;
		libandria4_sizet_pascalarray *a;
		libandria4_failure_uipresult e;
		
		tmp = libandria4_sizet_pascalarray_build( ctx.stacks->len );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			printf( "  cmargs failed to allocate ctx.align. Exiting.\n" );
			return( EXIT_FAILURE );
		}
		ctx.align = a;
		
		tmp = libandria4_sizet_pascalarray_build( ctx.stacks->len );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			printf( "  cmargs failed to allocate ctx.used. Exiting.\n" );
			return( EXIT_FAILURE );
		}
		ctx.used = a;
		
		tmp = libandria4_sizet_pascalarray_build( ctx.stacks->len );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			printf( "  cmargs failed to allocate ctx.alignreq. Exiting.\n" );
			return( EXIT_FAILURE );
		}
		ctx.alignreq = a;
	}
	
	{
		/* libandria4_result libandria4_bitarray_destroy( libandria4_bitarray *barr ); */
		libandria4_bitarray_result tmp =
			libandria4_bitarray_build( ctx.stacks->len );
		libandria4_bitarray *a;
		int e;
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( tmp,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		if( res != 1 )
		{
			printf( "  cmargs failed to allocate ctx.reallocatable. Exiting.\n" );
			return( EXIT_FAILURE );
		}
		ctx.reallocatable = a;
	}
	
	
	res = libandria4_cts_isvalid( &ctx );
	if( !res )
	{
		printf( "  cmargs libandria4_cts_isvalid() failed. Exiting.\n" );
		return( EXIT_FAILURE );
	}
	res = libandria4_cts_isvalid2( &ctx );
	if( !res )
	{
		printf( "  cmargs libandria4_cts_isvalid2() failed. Exiting.\n" );
		return( EXIT_FAILURE );
	}
	
	
	
	/* Actually run our tests. */
	res = test1();
	if( !res )
	{
		printf( "  cmargs test1() failed. Exiting.\n" );
		return( EXIT_FAILURE );
	}
	
	
	
	/* We don't even TRY to deallocate anything. Bad for real-world */
	/*  use, but works for discrete test programs like this one. */
	
	printf( " cmargs test1.c succeeded. Exiting.\n" );
	return( EXIT_SUCCESS );
}
