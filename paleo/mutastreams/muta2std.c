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



/* TODO: go looking for the other TODOs in this file and fix them. */



#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

#include "mutablestreams.h"
#include "muta2std.h"



/* THIS FILE IS INCOMPLETE! */

/* Note: in libandria4_mutastream_2stream: */
	/* .impl has become .uget_support, with a change from */
	/*  *_FILE_substream_vtable to *_commonio_istream_vtable. */
		/* This reflects the fact that *_ungetwrapper_vtable needs a */
		/*  *_commonio_istream_vtable to defer to. */
	/* .muta has become .trk, with a change from *_substream_vtable to */
	/*  *_tracker. */
		/* Because we bothered to build all that reference-counting stuff, */
		/*  so it should be used where appropriate. */
	/* Both of these changes SEEM to have been accounted for in the code */
	/*  below, but it hasn't yet been THOROUGHLY reviewed, and IS absolutely */
	/*  wrong: */
		/* Pretty much everwhere that ->trk is referenced, it's accessed via */
		/*  a type that doesn't have it, and which needs to first be */
		/*  converted to a pointer to a libandria4_mutastream_2stream{}. */
		/*  Given that the code in question was copy-pasta'd basically */
		/*  everywhere that "trk" is referenced, the cast needs to be added */
		/*  "everywhere". Best method is probably to build a wrapper for */
		/*  LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY() that takes the same */
		/*  arguments, except for dropping ->trk from the first arg to do it */
		/*  inside the wrapper after conversion instead, and subbing in the */
		/*  new to replace the old. */
	libandria4_mutastream_2stream* muta2std_from_handle( libandria4_commonio_handle *hand_ptr )
		{ return( libandria4_commonio_mutastream2stream_FROM_HANDLE( hand_ptr ) ); }
	#define MUTA2STD_REFPOINTER_EXPRAPPLY( varptr,  func, onnull ) \
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY( muta2std_from_handle( varptr ),  func, onnull )

	#define libandria4_mutastream_2stream_GENERICONV_ONEMPTY() \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE );
	#define libandria4_mutastream_2stream_GENERICONV_ONERR( err ) \
		flags |= 1; err_val = (err);
	#define libandria4_mutastream_2stream_GENERICONV_ONREDIR( redir ) \
		flags |= 2; redir_val = (redir);
	#define libandria4_mutastream_2stream_GENERICONV_VALID( vtab, vptr ) \
		( vt = (vtab), vf = (vptr) )
#define libandria4_mutastream_2stream_GENERICONV( func ) \
	if( strm ) { int a = 0; libandria4_FILE_substream_vtable *vt; void *vf; \
		MUTA2STD_REFPOINTER_EXPRAPPLY( strm, \
			libandria4_mutastream_2stream_GENERICONV_VALID, \
			LIBANDRIA4_OP_SETaTO1 ); \
		if( a || !vt ) { LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		else if( vt-> func ) { libandria4_newstreams_bituplic2 res = (vt-> func )( vf ); \
			libandria4_newstreams_err err_val; libandria4_FILE_redirection redir_val; int flag = 0; \
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( res, \
				libandria4_mutastream_2stream_GENERICONV_ONERR, \
				libandria4_mutastream_2stream_GENERICONV_ONREDIR, \
				libandria4_mutastream_2stream_GENERICONV_ONEMPTY ); \
			if( flags & 2 ) { \
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE( strm->trk, redir_val, \
						/* TODO: Should add logging to this. */ \
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */ \
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */ \
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */ \
				); } \
			if( flags & 1 ) { LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( err_val ); } \
			else { LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( 0 ); } } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );

libandria4_commonio_eithgeneric libandria4_mutastream_2stream_flush( libandria4_commonio_handle *strm )
{
	libandria4_mutastream_2stream_GENERICONV( flush );
}

libandria4_commonio_eithbyte libandria4_mutastream_2stream_getc( libandria4_commonio_handle *strm )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY(
			strm->trk,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->get_c )
		{
			libandria4_newstreams_bituplic3 res = (vt->get_c)( vf );
			
			libandria4_commonio_eithchar2 res2;
			libandria4_FILE_redirection redir_val;
			int flag = 0;
			
#define libandria4_mutastream_2stream_getc_ONEMPTY() \
	LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE );
#define libandria4_mutastream_2stream_getc_ONVAL( val ) \
	flags |= 1; res2 = (val);
#define libandria4_mutastream_2stream_getc_ONREDIR( redir ) \
	flags |= 2; redir_val = (redir);
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
				res,
				
				libandria4_mutastream_2stream_getc_ONVAL,
				libandria4_mutastream_2stream_getc_ONREDIR,
				libandria4_mutastream_2stream_getc_ONEMPTY
			);
				
			if( flags & 2 )
			{
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE(
					strm->trk, redir_val,
					
						/* TODO: Should add logging to this. */
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */
				);
			}
			
			if( flags & 1 )
			{
				char a;
				libandria4_commonio_perr b;
				
#define libandria4_mutastream_2stream_getc_ONINT( c ) \
	a = (c); if( a <= LIBANDRIA4_COMMONIO_BYTE_MAX ) { \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETBYTE( a ); } else { \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ); }
#define libandria4_mutastream_2stream_getc_ONERR( err ) \
	b = (err); if( B <= LIBANDRIA4_COMMONIO_ERR_MAX ) { \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( b ); } else { \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ); }
				LIBANDRIA4_MONAD_EITHER_BODYMATCH(
					res2,
						libandria4_mutastream_2stream_getc_ONINT,
						libandria4_mutastream_2stream_getc_ONERR
				);
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_ungetc( libandria4_commonio_handle*, libandria4_commonio_byte );
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_putc( libandria4_commonio_handle *strm, libandria4_commonio_byte val )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		MUTA2STD_REFPOINTER_EXPRAPPLY(
			strm,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->put_c )
		{
			libandria4_newstreams_bituplic2 res = (vt->put_c)( vf, val );
			
			libandria4_newstreams_err err_val;
			libandria4_FILE_redirection redir_val;
			int flag = 0;
			
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
				res,
				
				libandria4_mutastream_2stream_GENERICONV_ONERR,
				libandria4_mutastream_2stream_GENERICONV_ONREDIR,
				libandria4_mutastream_2stream_GENERICONV_ONEMPTY
			);
				
			if( flags & 2 )
			{
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE(
					strm->trk, redir_val,
					
						/* TODO: Should add logging to this. */
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */
				);
			}
			
			if( flags & 1 )
			{
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( err_val );
				
			} else {
				
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( 0 );
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}

/* Note: gets_s() and puts_s() should be implemented by simple wrapper from */
/*  streams.c for now. They can be properly built later if justified. The signatures are as follows: */
	/*
		libandria4_commonio_eithgeneric
			libandria4_mutastream_2stream_gets_s
			(
				libandria4_commonio_handle *strm,
				
				libandria4_commonio_byte *arr,
				size_t len
			);
	*/
	/*
		libandria4_commonio_eithgeneric
			libandria4_mutastream_2stream_puts_s
			(
				libandria4_commonio_handle *strm,
				
				libandria4_commonio_byte *arr,
				size_t len
			);
	*/

libandria4_commonio_eithlong libandria4_mutastream_2stream_tell( libandria4_commonio_handle *strm )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		MUTA2STD_REFPOINTER_EXPRAPPLY(
			strm,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->tell )
		{
			libandria4_newstreams_bituplic4 res = (vt->tell)( vf, int /* Reference point. */ );
			
			libandria4_commonio_eithintmax2 res2;
			libandria4_FILE_redirection redir_val;
			int flag = 0;
			
#define libandria4_mutastream_2stream_tell_ONEMPTY() \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE );
#define libandria4_mutastream_2stream_tell_ONVAL( val ) \
	flags |= 1; res2 = (val);
#define libandria4_mutastream_2stream_tell_ONREDIR( redir ) \
	flags |= 2; redir_val = (redir);
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
				res,
				
				libandria4_mutastream_2stream_tell_ONVAL,
				libandria4_mutastream_2stream_tell_ONREDIR,
				libandria4_mutastream_2stream_tell_ONEMPTY
			);
				
			if( flags & 2 )
			{
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE(
					strm->trk, redir_val,
					
						/* TODO: Should add logging to this. */
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */
				);
			}
			
			if( flags & 1 )
			{
				intmax_t a;
				libandria4_commonio_perr b;
				
#define libandria4_mutastream_2stream_tell_ONINT( i ) \
	a = (i); if( a <= LONG_MAX ) { \
		LIBANDRIA4_COMMONIO_EITHLONG_RETBYTE( a ); } else { \
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ); }
#define libandria4_mutastream_2stream_tell_ONERR( err ) \
	b = (err); if( B <= LIBANDRIA4_COMMONIO_ERR_MAX ) { \
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( b ); } else { \
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ); }
				LIBANDRIA4_MONAD_EITHER_BODYMATCH(
					res2,
						libandria4_mutastream_2stream_tell_ONINT,
						libandria4_mutastream_2stream_tell_ONERR
				);
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_seek( libandria4_commonio_handle *strm, long dist, int ori )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		MUTA2STD_REFPOINTER_EXPRAPPLY(
			strm,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->seek )
		{
			libandria4_newstreams_bituplic2 res = (vt->seek)( vf, dist, ori );
			
			libandria4_newstreams_err err_val;
			libandria4_FILE_redirection redir_val;
			int flag = 0;
			
			LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH(
				res,
				
				libandria4_mutastream_2stream_GENERICONV_ONERR,
				libandria4_mutastream_2stream_GENERICONV_ONREDIR,
				libandria4_mutastream_2stream_GENERICONV_ONEMPTY
			);
				
			if( flags & 2 )
			{
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE(
					strm->trk, redir_val,
					
						/* TODO: Should add logging to this. */
					LIBANDRIA4_NULL_MACRO, /* on_failattend( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_failneglect( void ) */
					LIBANDRIA4_NULL_MACRO, /* on_redir( FILE_tracker ) */
				);
			}
			
			if( flags & 1 )
			{
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( err_val );
				
			} else {
				
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( 0 );
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_rewind( libandria4_commonio_handle *strm )
{
	libandria4_mutastream_2stream_GENERICONV( rewind );
}

libandria4_commonio_eithgeneric libandria4_mutastream_2stream_clearerr( libandria4_commonio_handle *strm )
{
	libandria4_mutastream_2stream_GENERICONV( clear_err );
}
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_eof( libandria4_commonio_handle *strm )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		MUTA2STD_REFPOINTER_EXPRAPPLY(
			strm,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->is_eof )
		{
			int res = (vt->is_eof)( vf );
			
			if( res )
			{
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( LIBANDRIA4_COMMONIOVALS_EOF );
				
			} else {
				
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED );
			}
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
	/* If there isn't an error, then it MIGHT still indicate eof. */
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_error( libandria4_commonio_handle *strm )
{
	if( strm )
	{
		int a = 0;
		libandria4_FILE_substream_vtable *vt;
		void *vf;
		
		MUTA2STD_REFPOINTER_EXPRAPPLY(
			strm,
			
			libandria4_mutastream_2stream_GENERICONV_VALID,
			LIBANDRIA4_OP_SETaTO1
		);
		
		if( a || !vt )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
			
		} else if( vt->get_error )
		{
			libandria4_newstreams_result2 res = (vt->get_error)( vf );
			
			LIBANDRIA4_MONAD_MAYBE_BODYMATCH(
				res,
					LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE,
					LIBANDRIA4_NULL_MACRO
			);
			
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED );
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}

	/* This should redirect libandria4_mutastream_2stream.trk to point at the EOF */
	/*  stream and other such stuff, it shouldn't care about the mutable stream's */
	/*  close() at all. */
libandria4_commonio_eithgeneric libandria4_mutastream_2stream_close( libandria4_commonio_handle* )
{
	???
};
/* Reminder, this is out real type:
	typedef struct libandria4_mutastream_2stream
	{
		libandria4_commonio_handle handle;
		libandria4_commonio_istream_ungetwrapper_vtable uget_host;
		libandria4_commonio_istream_vtable uget_support;
		libandria4_FILE_tracker trk;
		
	} libandria4_mutastream_2stream;
*/


		/* This is just here to track the functions that HAVEN'T been */
		/*  implemented yet. Given the current state of the */
		/*  libandria4_mutastream_2stream{} type, I think the correct */
		/*  approach is to just do the norm for these three, but have the */
		/*  close() accessed via the .handle member just set .trk to the EOF */
		/*  stream. Then we just handle allocation and deallocation of */
		/*  libandria4_mutastream_2stream{} happen through a different */
		/*  mechanism, probably tracked in a per-variant array so that it's */
		/*  easier to just free them through a discrete function. */
	struct libandria4_FILE_substream_vtable
	{
		void (*attending)( uintptr_t *count );
		void (*neglecting)( uintptr_t *count );
		
		...
		
		void (*close)( void* /* FILE* */ );
	};
