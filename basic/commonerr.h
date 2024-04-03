/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2019 Jared A. Maddox

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

#ifndef LIBANDRIA4_BASIC_COMMONERR_H
# define LIBANDRIA4_BASIC_COMMONERR_H
	
	??? /* We need a .c file too! */
	
	#include "monads.h"
	#include "commonio.h"
	
	
	
	/* An error reporting facility. */
	
	typedef uintptr_t libandria4_error_errint;
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_error_mayerr, libandria4_error_errint );
	
	#define LIBANDRIA4_ERROR_MAYERR_JUSTERR( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_error_mayerr, libandria4_error_errint, val )
	#define LIBANDRIA4_ERROR_MAYERR_NOERR() \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_error_mayerr, libandria4_error_errint )
	
		/* The *BODY* takes statements, *EXPR* takes expressions, */
		/*  *REDUCE extracts values. */
	#define LIBANDRIA4_ERROR_MAYERR_BODYMATCH( var,  onerr, onsucc ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onerr, onsucc )
	#define LIBANDRIA4_ERROR_MAYERR_EXPRMATCH( var,  onerr, onsucc ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onerr, onsucc )
		/* "onsucc" always produces a "nothing" monad, so onerr should do */
		/*  something compatible. Basically only useful for translating */
		/*  "maybe" types. */
	#define LIBANDRIA4_ERROR_MAYERR_EXPRCHAIN( var,  name, type, onerr ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( name, type,  var,  onerr )
			/* alt gets subbed in for "nothing". */
	#define LIBANDRIA4_ERROR_MAYERR_REDUCE( var,  alttype, altval ) \
		LIBANDRIA4_MONAD_MAYBE_REDUCE( var,  alttype, altval )
	
	#define LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( val ) \
		return( LIBANDRIA4_ERROR_MAYERR_JUSTERR( val ) );
	#define LIBANDRIA4_ERROR_MAYERR_RETURN_SUCCESS() \
		return( LIBANDRIA4_ERROR_MAYERR_NOERR() );
	
	
	
	#define LIBANDRIA4_ERROR_MAYERR_RETERR1( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 1 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR2( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 2 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR3( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 3 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR4( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 4 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR5( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 5 );
	
	#define LIBANDRIA4_ERROR_MAYERR_RETERR6( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 6 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR7( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 7 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR8( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 8 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR9( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 9 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR10( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 10 );
	
	#define LIBANDRIA4_ERROR_MAYERR_RETERR11( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 11 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR12( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 12 );
	#define LIBANDRIA4_ERROR_MAYERR_RETERR13( ... ) LIBANDRIA4_ERROR_MAYERR_RETURN_ERROR( 13 );
	
	
	
	
	
	typedef struct libandria4_error_basalstruct
	{
		uint32_t typeid;
	};
	struct libandria4_error_simplestruct
	{
		libandria4_error_basalstruct type;
		
		libandria4_error_simplestruct *funcname;
		
		size_t str_len;
		char *str;
	};
		/* LIBANDRIA4_ERROR_TYPE_BASALSTRUCT used to be LIBANDRIA4_ERRORSTRUCT_NULLTYPE, */
		/*  adjust user text appropriately. Also, the names got reformatted to be more */
		/*  organized, but all of the parts are still there. */
	#define LIBANDRIA4_ERROR_TYPE_BASALSTRUCT ( 0 )
	#define LIBANDRIA4_ERROR_TYPE_SIMPLESTRUCT ( 1 )
	
		/* A very generic error type. Was named LIBANDRIA4_BUILDERRORSTRUCT_SIMPLETYPE. */
	#define LIBANDRIA4_ERROR_BUILD_SIMPLESTRUCT( funcname_ptr, varname, strptr ) \
		static libandria4_error_simplestruct ( varname ) = { { LIBANDRIA4_ERRORSTRUCT_SIMPLETYPE }, 0, 0, strptr }; \
		if( ( name ).str_len == 0 ) { \
			( name ).funcname = ( funcname_ptr ); ( name ).str_len = strlen( ( name ).str ); }
		/* Was LIBANDRIA4_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME. */
	#define LIBANDRIA4_ERROR_BUILDFUNCNAME_SIMPLESTRUCT( varname, namestrptr ) \
		LIBANDRIA4_ERROR_BUILD_SIMPLESTRUCT( &( varname ), varname, namestrptr )
	
	
	libandria4_error_mayerr libandria4_error_print
	(
		libandria4_commonio_handle *io,
			libandria4_error_basalstruct *err,
			int line,
			char *file
	);
	
	
	
	#include "simpleops.h"
	
	libandria4_error_mayerr libandria4_error_print_simplestruct
	(
		libandria4_commonio_handle *io,
		libandria4_error_simplestruct *err
	)
	{
		if( io && err )
		{
			if( !libandria4_commonio_handle_hasbasics( io ) )
			{
				LIBANDRIA4_ERROR_MAYERR_RETERR2();
			}
			if( !( io->puts_s ) )
			{
				LIBANDRIA4_ERROR_MAYERR_RETERR3();
			}
			if( !( err->str ) && err->str_len )
			{
				LIBANDRIA4_ERROR_MAYERR_RETERR4();
			}
			
			
			if
			(
				!libandria4_commonio_recursivewrapper_puts_s
				(
					io,  (libandria4_commonio_byte*)( err->str ), err->str_len
				)
			)
			{
				LIBANDRIA4_ERROR_MAYERR_RETERR5();
			}
			
			LIBANDRIA4_ERROR_MAYERR_RETURN_SUCCESS();
		}
		LIBANDRIA4_ERROR_MAYERR_RETERR1();
	}
	libandria4_error_mayerr libandria4_error_print
	(
		libandria4_commonio_handle *io,
			libandria4_error_basalstruct *err,
			int line,
			char *file
	)
	{
		if( io && err )
		{
			if( !libandria4_commonio_handle_hasbasics( io ) )
			{
				LIBANDRIA4_ERROR_MAYERR_RETERR2();
			}
			if( !( io->putc && io->puts_s && io->flush ) )
			{
				LIBANDRIA4_ERROR_MAYERR_RETERR3();
			}
			
			libandria4_commonio_eithgeneric res1;
			libandria4_error_mayerr res2;
			
			switch( err->typeid )
			{
				case LIBANDRIA4_ERRORSTRUCT_SIMPLETYPE:
#define libandria4_error_print_STR_FUNC "function: "
#define libandria4_error_print_STR_SRC " at "
#define libandria4_error_print_STR_DESC " announces this error: "
					if
					(
						!libandria4_commonio_recursivewrapper_puts_s
						(
							io,
								(libandria4_commonio_byte*)libandria4_error_print_STR_FUNC,
								sizeof( libandria4_error_print_STR_FUNC )
						)
					)
					{
						LIBANDRIA4_ERROR_MAYERR_RETERR4();
					}
					
					res2 = libandria4_error_print_simplestruct( io, err->funcname );
					LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  LIBANDRIA4_ERROR_MAYERR_RETERR5 );
					
					if( !libandria4_commonio_utility_putint( io,  line ) )
					{
						LIBANDRIA4_ERROR_MAYERR_RETERR6();
					}
					libandria4_commonio_eithgeneric res1 = io->putc( io,  (libandria4_commonio_byte)' ' );
					res2 = LIBANDRIA4_COMMONIO_EITHGENERIC_TO_MAYERR( res1 );
					LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  LIBANDRIA4_ERROR_MAYERR_RETERR7 );
					if
					(
						!libandria4_commonio_recursivewrapper_puts_s
						(
							io,
								(libandria4_commonio_byte*)file,
								strlen( file )
						)
					)
					{
						LIBANDRIA4_ERROR_MAYERR_RETERR8();
					}
					
					if
					(
						!libandria4_commonio_recursivewrapper_puts_s
						(
							io,
								(libandria4_commonio_byte*)libandria4_error_print_STR_SRC,
								sizeof( libandria4_error_print_STR_SRC )
						)
					)
					{
						LIBANDRIA4_ERROR_MAYERR_RETERR9();
					}
					
					if
					(
						!libandria4_commonio_recursivewrapper_puts_s
						(
							io,
								(libandria4_commonio_byte*)libandria4_error_print_STR_DESC,
								sizeof( libandria4_error_print_STR_DESC )
						)
					)
					{
						LIBANDRIA4_ERROR_MAYERR_RETERR10();
					}
					
					res2 = libandria4_error_print_simplestruct( io, err );
					LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  LIBANDRIA4_ERROR_MAYERR_RETERR11 );
					
					break;
					
				case LIBANDRIA4_ERROR_TYPE_BASALSTRUCT:
					LIBANDRIA4_ERROR_MAYERR_RETERR12();
					
				default:
					LIBANDRIA4_ERROR_MAYERR_RETERR13();
			}
			
			LIBANDRIA4_ERROR_MAYERR_RETURN_SUCCESS();
		};
		
		LIBANDRIA4_ERROR_MAYERR_RETERR1();
	}
	
	
	
	
	
	#define VT100NET_REPORT_ERR( ctx, rep_type_mmbr_ptr, filename, linenum ) \
		{ int res = vt100net_report_parser_error( (vt100net_termcontext*)( ctx ), (uint32_t*)( rep_type_mmbr_ptr ) ); \
			if( res != -1 ) { \
				term_ctx->error_values.file = ( filename ); term_ctx->error_values.line = ( linenum ); } \
			switch( res ) \
			{ case -1: \
					fprintf( stderr, \
						"ERROR: VT100NET_REPORT_ERR() received a \"bad args\" error in %s at %i.\n", \
						(char*)(filename), (int)(linenum) ); return( -5 ); \
				case -4: return( -6 ); \
				case -2: case -3: return( -7 ); \
				default: break; } }
	int vt100net_report_parser_error( vt100net_termcontext *term_ctx, uint32_t *report_type_member );
	
#endif
/* End libandria4 basic commonerr.h */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          