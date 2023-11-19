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
	
	#include "commonio.h"
	
	
	
	/* TODO: convert this to a "generic" version. */
	
	/* An error reporting facility. */
	
	typedef struct vt100net_errorstruct
	{
		uint32_t typeid;
	};
	struct vt100net_errorstruct_simple
	{
		vt100net_errorstruct type;
		
		vt100net_errorstruct_simple *funcname;
		
		size_t str_len;
		char *str;
	};
	#define VT100NET_ERRORSTRUCT_NULLTYPE ( 0 )
	#define VT100NET_ERRORSTRUCT_SIMPLETYPE ( 1 )
	
	#define VT100NET_BUILDERRORSTRUCT_SIMPLETYPE( funcname_ptr, varname, strptr ) \
		static vt100net_errorstruct_simple ( varname ) = { { VT100NET_ERRORSTRUCT_SIMPLETYPE }, 0, 0, strptr }; \
		if( ( name ).str_len == 0 ) { \
			( name ).funcname = ( funcname_ptr ); ( name ).str_len = strlen( ( name ).str ); }
	#define VT100NET_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME( varname, namestrptr ) \
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE( &( varname ), varname, namestrptr )
	
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
/* End libandria4 basic commonerr.h */