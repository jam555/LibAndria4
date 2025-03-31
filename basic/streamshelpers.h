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

#ifndef LIBANDRIA4_BASIC_STREAMSHELPERS_H
# define LIBANDRIA4_BASIC_STREAMSHELPERS_H
	
	#include "streams.h"
	#include "simpleops.h"
	#include "elemtools.h"
	
	
	
	/*
		This provides helper macros for streams.h/.c, which are meant to help
		reduce the size of user & backend code.
	*/
	
	
	
	/************************************************************/
	/************************************************************/
	/** Everything below here is meant for implementation, try **/
	/**  to depend on the documentation above. ******************/
	/************************************************************/
	/************************************************************/
	/* WHAT documentation? TODO: copy that documentation to here. */
	/* TODO: Add *_seekable support to libandria4_commonio_handle_*MATCH(). */
	
	/* This function and two macros are used "internally" to this header, */
	/*  but aren't necessarily BAD to use elsewhere. */
	int libandria4_commonio_handle_verifydispatch( libandria4_commonio_handle* );
	#define libandria4_commonio_handle_BODYMATCH( var,  fullhand, inhand, outhand,  badhand, ... ) \
		if( libandria4_commonio_handle_verifydispatch( ( var ) ) ) { \
			if( (var)->dispatch == libandria4_commonio_handle_vtabtype_handle ) { \
				(fullhand)( ( var ), (var)->vtab.hand, __VA_ARGS__ ); } else \
			if( (var)->dispatch == libandria4_commonio_handle_vtabtype_istream ) { \
				(inhand)( ( var ), (var)->vtab.istr, __VA_ARGS__ ); } else \
			if( (var)->dispatch == libandria4_commonio_handle_vtabtype_ostream ) { \
				(outhand)( ( var ), (var)->vtab.ostr, __VA_ARGS__ ); } else \
			{ (badhand)( (var)->dispatch, (var), __VA_ARGS__ ); } \
		} else { \
			(badhand)( libandria4_commonio_handle_vtabtype_invalid, &(var), __VA_ARGS__ ); }
		/* This specifically does mapping between handles and handlers based on */
		/*  handle type. */
	#define libandria4_commonio_handle_EXPRMATCH( var,  fullhand, inhand, outhand,  badhand, ... ) \
		( ( libandria4_commonio_handle_verifydispatch( ( var ) ) ) ? ( \
				( (var)->dispatch == libandria4_commonio_handle_vtabtype_handle ) ? ( \
					fullhand( ( var ), (var)->vtab.hand, __VA_ARGS__ ) \
				) : ( \
					( (var)->dispatch == libandria4_commonio_handle_vtabtype_istream ) ? ( \
						inhand( ( var ), (var)->vtab.istr, __VA_ARGS__ ) \
					) : ( \
						( (var)->dispatch == libandria4_commonio_handle_vtabtype_ostream ) ? ( \
							outhand( ( var ), (var)->vtab.ostr, __VA_ARGS__ ) \
						) : ( \
							badhand( (var)->dispatch, (var), __VA_ARGS__ ) ) ) ) \
			) : ( badhand( libandria4_commonio_handle_vtabtype_invalid, &(var), __VA_ARGS__ ) ) )
	
	libandria4_commonio_handle_vtable_funcenums libandria4_commonio_handle_detfuncs
	(
		libandria4_commonio_handle *hand
	);
	int libandria4_commonio_handle_hasfunc
	(
		libandria4_commonio_handle *hand,
		libandria4_commonio_handle_vtable_funcenums funcs
	);
	
	/*********************************************************************************/
	
	
			/* libandria4_commonio_genericfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_flush_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->flush )
	#define libandria4_commonio_handle_FETCH_flush( hptr ) ( \
			(libandria4_commonio_genericfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_flush_HELPER1, \
						libandria4_commonio_handle_FETCH_flush_HELPER1, \
						libandria4_commonio_handle_FETCH_flush_HELPER1, \
						libandria4_commonio_genericfunc_NULLPTR, \
						dummy ) ) )
	
	
			/* libandria4_commonio_fetchbyte_NULLPTR */
		#define libandria4_commonio_handle_FETCH_getc_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->getc )
	#define libandria4_commonio_handle_FETCH_getc( hptr ) ( \
			(libandria4_commonio_fetchbyte)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_getc_HELPER1, \
						libandria4_commonio_handle_FETCH_getc_HELPER1, \
						libandria4_commonio_fetchbyte_NULLPTR, \
						libandria4_commonio_fetchbyte_NULLPTR, \
						dummy ) ) )
	
			/* libandria4_commonio_storebyte_NULLPTR */
		#define libandria4_commonio_handle_FETCH_ungetc_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->ungetc )
	#define libandria4_commonio_handle_FETCH_ungetc( hptr ) ( \
			(libandria4_commonio_storebyte)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_ungetc_HELPER1, \
						libandria4_commonio_handle_FETCH_ungetc_HELPER1, \
						libandria4_commonio_storebyte_NULLPTR, \
						libandria4_commonio_storebyte_NULLPTR, \
						dummy ) ) )
	
			/* libandria4_commonio_strfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_gets_s_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->gets_s )
	#define libandria4_commonio_handle_FETCH_gets_s( hptr ) ( \
			(libandria4_commonio_strfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_gets_s_HELPER1, \
						libandria4_commonio_handle_FETCH_gets_s_HELPER1, \
						libandria4_commonio_strfunc_NULLPTR, \
						libandria4_commonio_strfunc_NULLPTR, \
						dummy ) ) )
	
	
			/* libandria4_commonio_storebyte_NULLPTR */
		#define libandria4_commonio_handle_FETCH_putc_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->putc )
	#define libandria4_commonio_handle_FETCH_putc( hptr ) ( \
			(libandria4_commonio_storebyte)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_putc_HELPER1, \
						libandria4_commonio_storebyte_NULLPTR, \
						libandria4_commonio_handle_FETCH_putc_HELPER1, \
						libandria4_commonio_storebyte_NULLPTR, \
						dummy ) ) )
	
			/* libandria4_commonio_strfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_puts_s_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->puts_s )
	#define libandria4_commonio_handle_FETCH_puts_s( hptr ) ( \
			(libandria4_commonio_strfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_puts_s_HELPER1, \
						libandria4_commonio_strfunc_NULLPTR, \
						libandria4_commonio_handle_FETCH_puts_s_HELPER1, \
						libandria4_commonio_strfunc_NULLPTR, \
						dummy ) ) )
	
	
			/* libandria4_commonio_longfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_tell_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->tell )
		#define libandria4_commonio_handle_FETCH_tell_HELPER2( just ) \
			( (just)->tell )
		#define libandria4_commonio_handle_FETCH_tell_HELPER3( hptr, vtab,  dummy ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->seekable, \
					libandria4_commonio_handle_FETCH_tell_HELPER2, \
					libandria4_commonio_longfunc_NULLPTR )
	#define libandria4_commonio_handle_FETCH_tell( hptr ) ( \
			(libandria4_commonio_longfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_tell_HELPER1, \
						libandria4_commonio_handle_FETCH_tell_HELPER3, \
						libandria4_commonio_handle_FETCH_tell_HELPER3, \
						libandria4_commonio_longfunc_NULLPTR, \
						dummy ) ) )
	
			/* libandria4_commonio_seekfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_seek_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->seek )
		#define libandria4_commonio_handle_FETCH_seek_HELPER2( just ) \
			( (just)->seek )
		#define libandria4_commonio_handle_FETCH_seek_HELPER3( hptr, vtab,  dummy ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->seekable, \
					libandria4_commonio_handle_FETCH_seek_HELPER2, \
					libandria4_commonio_seekfunc_NULLPTR )
	#define libandria4_commonio_handle_FETCH_seek( hptr ) ( \
			(libandria4_commonio_seekfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_seek_HELPER1, \
						libandria4_commonio_handle_FETCH_seek_HELPER3, \
						libandria4_commonio_handle_FETCH_seek_HELPER3, \
						libandria4_commonio_seekfunc_NULLPTR, \
						dummy ) ) )
	
			/* libandria4_commonio_genericfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_rewind_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->rewind )
		#define libandria4_commonio_handle_FETCH_rewind_HELPER2( just ) \
			( (just)->rewind )
		#define libandria4_commonio_handle_FETCH_rewind_HELPER3( hptr, vtab,  dummy ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->seekable, \
					libandria4_commonio_handle_FETCH_rewind_HELPER2, \
					libandria4_commonio_genericfunc_NULLPTR )
	#define libandria4_commonio_handle_FETCH_rewind( hptr ) ( \
			(libandria4_commonio_genericfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_rewind_HELPER1, \
						libandria4_commonio_handle_FETCH_rewind_HELPER3, \
						libandria4_commonio_handle_FETCH_rewind_HELPER3, \
						libandria4_commonio_genericfunc_NULLPTR, \
						dummy ) ) )
	
	
			/* libandria4_commonio_genericfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_clearerr_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->clearerr )
		#define libandria4_commonio_handle_FETCH_clearerr_HELPER2( just ) \
			( (just)->clearerr )
		#define libandria4_commonio_handle_FETCH_clearerr_HELPER3( hptr, vtab,  dummy ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->errable, \
					libandria4_commonio_handle_FETCH_clearerr_HELPER2, \
					libandria4_commonio_genericfunc_NULLPTR )
	#define libandria4_commonio_handle_FETCH_clearerr( hptr ) ( \
			(libandria4_commonio_genericfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_clearerr_HELPER1, \
						libandria4_commonio_handle_FETCH_clearerr_HELPER3, \
						libandria4_commonio_handle_FETCH_clearerr_HELPER3, \
						libandria4_commonio_genericfunc_NULLPTR, \
						dummy ) ) )
	
			/* libandria4_commonio_genericfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_eof_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->eof )
		#define libandria4_commonio_handle_FETCH_eof_HELPER2( just ) \
			( (just)->eof )
		#define libandria4_commonio_handle_FETCH_eof_HELPER3( hptr, vtab,  dummy ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->errable, \
					libandria4_commonio_handle_FETCH_eof_HELPER2, \
					libandria4_commonio_genericfunc_NULLPTR )
	#define libandria4_commonio_handle_FETCH_eof( hptr ) ( \
			(libandria4_commonio_genericfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_eof_HELPER1, \
						libandria4_commonio_handle_FETCH_eof_HELPER3, \
						libandria4_commonio_handle_FETCH_eof_HELPER3, \
						libandria4_commonio_genericfunc_NULLPTR, \
						dummy ) ) )
	
			/* libandria4_commonio_genericfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_error_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->error )
		#define libandria4_commonio_handle_FETCH_error_HELPER2( just ) \
			( (just)->error )
		#define libandria4_commonio_handle_FETCH_error_HELPER3( hptr, vtab,  dummy ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->errable, \
					libandria4_commonio_handle_FETCH_error_HELPER2, \
					libandria4_commonio_genericfunc_NULLPTR )
	#define libandria4_commonio_handle_FETCH_error( hptr ) ( \
			(libandria4_commonio_genericfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_error_HELPER1, \
						libandria4_commonio_handle_FETCH_error_HELPER3, \
						libandria4_commonio_handle_FETCH_error_HELPER3, \
						libandria4_commonio_genericfunc_NULLPTR, \
						dummy ) ) )
	
	
			/* libandria4_commonio_genericfunc_NULLPTR */
		#define libandria4_commonio_handle_FETCH_close_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->close )
	#define libandria4_commonio_handle_FETCH_close( hptr ) ( \
			(libandria4_commonio_genericfunc)( \
				libandria4_commonio_handle_EXPRMATCH( \
					hptr, \
						libandria4_commonio_handle_FETCH_close_HELPER1, \
						libandria4_commonio_handle_FETCH_close_HELPER1, \
						libandria4_commonio_handle_FETCH_close_HELPER1, \
						libandria4_commonio_genericfunc_NULLPTR, \
						dummy ) ) )
	
	
	/*********************************************************************************/
	/*********************************************************************************/
	/** Here begin the convenience macros for calls to libandria4_commonio_handle*. **/
	/**  Note that the macros are inherently messy by virtue of being macros, so *****/
	/**  you should default to refering to the documentation a bit further up. Only **/
	/**  depend on the code if you actually need to. *********************************/
	/*********************************************************************************/
	/*********************************************************************************/
	
	
			/* The previous implementation even had the bad-handler use the helper */
			/*  instead of just returning an error: should we do that again? */
		#define libandria4_commonio_handle_FLUSH_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->flush( hptr ) )
	#define libandria4_commonio_handle_FLUSH( hptr ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_FLUSH_HELPER1, \
					libandria4_commonio_handle_FLUSH_HELPER1, \
					libandria4_commonio_handle_FLUSH_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					dummy ) )
	
	
		#define libandria4_commonio_handle_GETC_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->getc( hptr ) )
	#define libandria4_commonio_handle_GETC( hptr ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_GETC_HELPER1, \
					libandria4_commonio_handle_GETC_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHBYTE_ERR_2, \
					LIBANDRIA4_COMMONIO_EITHBYTE_ERR_1, \
					dummy ) )
	
		#define libandria4_commonio_handle_UNGETC_HELPER1( hptr, vtab,  val ) \
			( (vtab)->ungetc( hptr,  val ) )
	#define libandria4_commonio_handle_UNGETC( hptr,  val ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_UNGETC_HELPER1, \
					libandria4_commonio_handle_UNGETC_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					(val) ) )
	
		#define libandria4_commonio_handle_GETS_S_HELPER1( hptr, vtab,  arr, len ) \
			( (vtab)->gets_s( hptr,  arr, len ) )
	#define libandria4_commonio_handle_GETS_S( hptr,  arr, len ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_GETS_S_HELPER1, \
					libandria4_commonio_handle_GETS_S_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					(arr), (len) ) )
	
	
		#define libandria4_commonio_handle_PUTC_HELPER1( hptr, vtab,  val ) \
			( (vtab)->putc( hptr,  val ) )
	#define libandria4_commonio_handle_PUTC( hptr,  val ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_PUTC_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2, \
					libandria4_commonio_handle_PUTC_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					(val) ) )
	
		#define libandria4_commonio_handle_PUTS_S_HELPER1( hptr, vtab,  arr, len ) \
			( (vtab)->puts_s( hptr,  arr, len ) )
	#define libandria4_commonio_handle_PUTS_S( hptr,  arr, len ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_PUTS_S_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2, \
					libandria4_commonio_handle_PUTS_S_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					(arr), (len) ) )
	
	
		#define libandria4_commonio_handle_TELL_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->tell( hptr ) )
			#define libandria4_commonio_handle_TELL_HELPER2( just ) \
				( (just)->tell )
			#define libandria4_commonio_handle_TELL_HELPER3( ... ) \
				( &libandria4_commonio_longfunc_reterr )
		#define libandria4_commonio_handle_TELL_HELPER4( hptr, vtab,  dummy ) \
			( LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->seekable, \
					libandria4_commonio_handle_TELL_HELPER2, \
					libandria4_commonio_handle_TELL_HELPER3 ) \
				( hptr ) )
	#define libandria4_commonio_handle_TELL( hptr ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_TELL_HELPER1, \
					libandria4_commonio_handle_TELL_HELPER4, \
					libandria4_commonio_handle_TELL_HELPER4, \
					LIBANDRIA4_COMMONIO_EITHLONG_ERR_1, \
					dummy ) )
	
		#define libandria4_commonio_handle_SEEK_HELPER1( hptr, vtab,  dist, origin ) \
			( (vtab)->seek( hptr,  dist, origin ) )
			#define libandria4_commonio_handle_SEEK_HELPER2( just ) \
				( (just)->seek )
			#define libandria4_commonio_handle_SEEK_HELPER3( ... ) \
				( &libandria4_commonio_seekfunc_reterr )
		#define libandria4_commonio_handle_SEEK_HELPER4( hptr, vtab,  dummy ) \
			( LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->seekable, \
					libandria4_commonio_handle_SEEK_HELPER2, \
					libandria4_commonio_handle_SEEK_HELPER3 ) \
				( hptr,  dist, origin ) )
	#define libandria4_commonio_handle_SEEK( hptr,  dist, origin ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_SEEK_HELPER1, \
					libandria4_commonio_handle_SEEK_HELPER4, \
					libandria4_commonio_handle_SEEK_HELPER4, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					(dist), (origin) ) )
	
		#define libandria4_commonio_handle_REWIND_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->rewind( hptr ) )
			#define libandria4_commonio_handle_REWIND_HELPER2( just ) \
				( (just)->rewind )
			#define libandria4_commonio_handle_REWIND_HELPER3( ... ) \
				( &libandria4_commonio_genericfunc_reterr )
		#define libandria4_commonio_handle_REWIND_HELPER4( hptr, vtab,  dummy ) \
			( LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->seekable, \
					libandria4_commonio_handle_REWIND_HELPER2, \
					libandria4_commonio_handle_REWIND_HELPER3 ) \
				( hptr ) )
	#define libandria4_commonio_handle_REWIND( hptr ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_REWIND_HELPER1, \
					libandria4_commonio_handle_REWIND_HELPER4, \
					libandria4_commonio_handle_REWIND_HELPER4, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					dummy ) )
	
	
	
		#define libandria4_commonio_handle_CLEARERR_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->clearerr( hptr ) )
			#define libandria4_commonio_handle_CLEARERR_HELPER2( just ) \
				( (just)->clearerr )
			#define libandria4_commonio_handle_CLEARERR_HELPER3( ... ) \
				( &libandria4_commonio_genericfunc_reterr )
		#define libandria4_commonio_handle_CLEARERR_HELPER4( hptr, vtab,  dummy ) \
			( LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->errable, \
					libandria4_commonio_handle_CLEARERR_HELPER2, \
					libandria4_commonio_handle_CLEARERR_HELPER3 ) \
				( hptr ) )
	#define libandria4_commonio_handle_CLEARERR( hptr ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_CLEARERR_HELPER1, \
					libandria4_commonio_handle_CLEARERR_HELPER4, \
					libandria4_commonio_handle_CLEARERR_HELPER4, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					dummy ) )
	
		#define libandria4_commonio_handle_EOF_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->eof( hptr ) )
			#define libandria4_commonio_handle_EOF_HELPER2( just ) \
				( (just)->eof )
			#define libandria4_commonio_handle_EOF_HELPER3( ... ) \
				( &libandria4_commonio_genericfunc_reterr )
		#define libandria4_commonio_handle_EOF_HELPER4( hptr, vtab,  dummy ) \
			( LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->errable, \
					libandria4_commonio_handle_EOF_HELPER2, \
					libandria4_commonio_handle_EOF_HELPER3 ) \
				( hptr ) )
	#define libandria4_commonio_handle_EOF( hptr ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_EOF_HELPER1, \
					libandria4_commonio_handle_EOF_HELPER4, \
					libandria4_commonio_handle_EOF_HELPER4, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					dummy ) )
	
		#define libandria4_commonio_handle_ERROR_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->error( hptr ) )
			#define libandria4_commonio_handle_ERROR_HELPER2( just ) \
				( (just)->error )
			#define libandria4_commonio_handle_ERROR_HELPER3( ... ) \
				( &libandria4_commonio_genericfunc_reterr )
		#define libandria4_commonio_handle_ERROR_HELPER4( hptr, vtab,  dummy ) \
			( LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( \
				(vtab)->errable, \
					libandria4_commonio_handle_ERROR_HELPER2, \
					libandria4_commonio_handle_ERROR_HELPER3 ) \
				( hptr ) )
	#define libandria4_commonio_handle_ERROR( hptr ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_ERROR_HELPER1, \
					libandria4_commonio_handle_ERROR_HELPER4, \
					libandria4_commonio_handle_ERROR_HELPER4, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					dummy ) )
	
	
		#define libandria4_commonio_handle_CLOSE_HELPER1( hptr, vtab,  dummy ) \
			( (vtab)->close( hptr ) )
	#define libandria4_commonio_handle_CLOSE( hptr ) ( \
			libandria4_commonio_handle_EXPRMATCH( \
				hptr, \
					libandria4_commonio_handle_CLOSE_HELPER1, \
					libandria4_commonio_handle_CLOSE_HELPER1, \
					libandria4_commonio_handle_CLOSE_HELPER1, \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1, \
					dummy ) )
	
#endif
/* End libandria4 basic streamshelpers.h */
