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

#ifndef LIBANDRIA4_PRIMITIVE_COMMONERR_H
# define LIBANDRIA4_PRIMITIVE_COMMONERR_H
	
	#include "basictypes.h"
	#include "monads.h"
	
	
	
	/* An error reporting facility. */
	/* TODO: Continue developing this stuff. Particularly look at extending */
	/*  libandria4_error_print(), and whatever the VT100 stuff near the end */
	/*  was originally about. */
	
	
	
	void libandria4_error_setputc
	(
		void *newdata, libandria4_common_putcharfuncp_int newputc,
			/* Optional: if provided, then the target of the pointers will */
			/*  be set to the values that are being replaced by the new */
			/*  arguments. */
		void *olddata, libandria4_common_putcharfuncp_int *oldputc
	);
	
	
	
	typedef struct libandria4_error_basalstruct
	{
		uint32_t typeid;
		
	} libandria4_error_basalstruct;
	typedef struct libandria4_error_simplestruct libandria4_error_simplestruct;
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
	
	
	/* These are both implemented in commonlib.c */
	libandria4_error_mayerr libandria4_error_print
	(
		libandria4_error_basalstruct *err,
		int line,
		char *file
	);
		/* Just prints ->str[]. */
	int libandria4_error_print_simplestruct
	(
		libandria4_error_simplestruct *err
	);
	
	
	
	
	#if 0
	/* We aren't currently running test compiles on the */
	/*  VT100 stuff, and this probably doesn't belong */
	/*  here anyways. */
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
	
#endif
/* End libandria4 primitive commonerr.h */
