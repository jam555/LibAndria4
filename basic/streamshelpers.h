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
	
	/* This function and two macros are used "internally" to this header, */
	/*  but aren't necessarily BAD to use elsewhere. */
	int libandria4_commonio_handle_verifydispatch( libandria4_commonio_handle* );
	#define libandria4_commonio_handle_BODYMATCH( var,  fullhand, inhand, outhand,  badhand ) \
		if( libandria4_commonio_handle_verifydispatch( &( var ) ) ) { \
			if( (var).dispatch == libandria4_commonio_handle_vtabtype_handle ) { \
				(fullhand)( (var).vtab.hand ); } else \
			if( (var).dispatch == libandria4_commonio_handle_vtabtype_istream ) { \
				(inhand)( (var).vtab.istr ); } else \
			if( (var).dispatch == libandria4_commonio_handle_vtabtype_ostream ) { \
				(outhand)( (var).vtab.ostr ); } else \
			{ (badhand)( (var).dispatch, &(var) ); } \
		} else { \
			(badhand)( libandria4_commonio_handle_vtabtype_invalid, &(var) ); }
	#define libandria4_commonio_handle_EXPRMATCH( var,  fullhand, inhand, outhand,  badhand ) \
		( ( libandria4_commonio_handle_verifydispatch( &( var ) ) ) ? ( \
				( (var).dispatch == libandria4_commonio_handle_vtabtype_handle ) ? ( \
					(fullhand)( &( var ), (var).vtab.hand ) \
				) : ( \
					( (var).dispatch == libandria4_commonio_handle_vtabtype_istream ) ? ( \
						(inhand)( &( var ), (var).vtab.istr ) \
					) : ( \
						( (var).dispatch == libandria4_commonio_handle_vtabtype_ostream ) ? ( \
							(outhand)( &( var ), (var).vtab.ostr ) \
						) : ( \
							(badhand)( (var).dispatch, &(var) ) ) ) ) \
			) : ( (badhand)( libandria4_commonio_handle_vtabtype_invalid, &(var) ) ) )
	
	
	
	/*********************************************************************************/
	/*********************************************************************************/
	/** Here begin the convenience macros for calls to libandria4_commonio_handle*. **/
	/**  Note that the macros are inherently messy by virtue of being macros, so *****/
	/**  you should default to refering to the documentation a bit further up. Only **/
	/**  depend on the code if you actually need to. *********************************/
	/*********************************************************************************/
	/*********************************************************************************/
	
	
		#define libandria4_commonio_handle_FLUSH_HELPER1( hptr, vtptr ) ( (vtptr)->flush( (hptr) ) )
		#define libandria4_commonio_handle_FLUSH_HELPER2( type, hptr ) ( \
			(type) == libandria4_commonio_handle_vtabtype_seekable ? \
				libandria4_commonio_handle_FLUSH_HELPER1( (hptr), (hptr)->vtab.seek ) : ( \
					(type) == libandria4_commonio_handle_vtabtype_errorable ? \
						libandria4_commonio_handle_FLUSH_HELPER1( (hptr), (hptr)->vtab.err ) : \
						LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2() ) )
	#define libandria4_commonio_handle_FLUSH( hptr ) ( \
			libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? \
					libandria4_commonio_handle_EXPRMATCH( *( hptr ), \
						libandria4_commonio_handle_FLUSH_HELPER1, \
						libandria4_commonio_handle_FLUSH_HELPER1, \
						libandria4_commonio_handle_FLUSH_HELPER1, \
						libandria4_commonio_handle_FLUSH_HELPER2 ) : \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
	
		#define libandria4_commonio_handle_GETC_HELPER1( hptr, vtptr ) ( (vtptr)->getc( (hptr) ) )
		#define libandria4_commonio_handle_GETC_INVALID( type, hptr ) ( LIBANDRIA4_COMMONIO_EITHBYTE_ERR_2() ) )
	#define libandria4_commonio_handle_GETC( hptr ) ( \
			libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? \
					libandria4_commonio_handle_EXPRMATCH( *( hptr ), \
						libandria4_commonio_handle_GETC_HELPER1, \
						libandria4_commonio_handle_GETC_HELPER1, \
						libandria4_commonio_handle_GETC_INVALID, \
						libandria4_commonio_handle_GETC_INVALID ) : \
					LIBANDRIA4_COMMONIO_EITHBYTE_ERR_1() )
	
		#define libandria4_commonio_handle_UNGETC_HELPER1( hptr, vtptr,  val ) \
			( !!(vtptr) ? (vtptr)->ungetc( (hptr),  (val) ) : LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2 )
		#define libandria4_commonio_handle_UNGETC_INVALID( type, hptr ) ( (libandria4_commonio_handle_vtable*)0 )
	#define libandria4_commonio_handle_UNGETC( hptr,  val ) ( \
			libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? \
					libandria4_commonio_handle_UNGETC_HELPER1( (hptr), \
							libandria4_commonio_handle_EXPRMATCH( *( hptr ), \
								LIBANDRIA4_RETURN_2ND, \
								LIBANDRIA4_RETURN_2ND, \
								libandria4_commonio_handle_UNGETC_INVALID, \
								libandria4_commonio_handle_UNGETC_INVALID ), \
							(val) ) : \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
		#define libandria4_commonio_handle_GETS_S_HELPER1( hptr, vtptr,  arr, len ) \
			( !!(vtptr) ? (vtptr)->gets_s( (hptr),  (arr), (len) ) : LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2 )
		#define libandria4_commonio_handle_GETS_S_INVALID( type, hptr ) ( (libandria4_commonio_handle_vtable*)0 )
	#define libandria4_commonio_handle_GETS_S( hptr,  arr, len ) ( \
			libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? \
					libandria4_commonio_handle_GETS_S_HELPER1( (hptr), \
							libandria4_commonio_handle_EXPRMATCH( *( hptr ), \
								LIBANDRIA4_RETURN_2ND, \
								LIBANDRIA4_RETURN_2ND, \
								libandria4_commonio_handle_GETS_S_INVALID, \
								libandria4_commonio_handle_GETS_S_INVALID ), \
							(arr), (len) ) : \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
	
		#define libandria4_commonio_handle_PUTC_HELPER1( hptr, vtptr,  val ) \
			( !!(vtptr) ? (vtptr)->putc( (hptr),  (val) ) : LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2 )
		#define libandria4_commonio_handle_PUTC_INVALID( type, hptr ) ( (libandria4_commonio_handle_vtable*)0 )
	#define libandria4_commonio_handle_PUTC( hptr,  val ) ( \
			libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? \
					libandria4_commonio_handle_PUTC_HELPER1( (hptr), \
							libandria4_commonio_handle_EXPRMATCH( *( hptr ), \
								LIBANDRIA4_RETURN_2ND, \
								libandria4_commonio_handle_PUTC_INVALID, \
								LIBANDRIA4_RETURN_2ND, \
								libandria4_commonio_handle_PUTC_INVALID ), \
							(val) ) : \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
		#define libandria4_commonio_handle_PUTS_S_HELPER1( hptr, vtptr,  arr, len ) \
			( !!(vtptr) ? (vtptr)->puts_s( (hptr),  (arr), (len) ) : LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2 )
		#define libandria4_commonio_handle_PUTS_S_INVALID( type, hptr ) ( (libandria4_commonio_handle_vtable*)0 )
	#define libandria4_commonio_handle_PUTS_S( hptr,  arr, len ) ( \
			libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? \
					libandria4_commonio_handle_PUTS_S_HELPER1( (hptr), \
							libandria4_commonio_handle_EXPRMATCH( *( hptr ), \
								LIBANDRIA4_RETURN_2ND, \
								libandria4_commonio_handle_PUTS_S_INVALID, \
								LIBANDRIA4_RETURN_2ND, \
								libandria4_commonio_handle_PUTS_S_INVALID ), \
							(arr), (len) ) : \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
	
		#define libandria4_commonio_handle_TELL_HELPER1( hptr, vtptr ) \
			( (vtptr) ? \
				(vtptr)->tell( (hptr) ) : \
				LIBANDRIA4_COMMONIO_EITHLONG_ERR_2() )
		#define libandria4_commonio_handle_TELL_HELPER2( hptr, vtptr ) \
			libandria4_commonio_handle_TELL_HELPER1( (hptr), \
				LIBANDRIA4_MONAD_MAYBE_REDUCE( libandria4_commonio_seekable*, (vtptr)->seekable, 0 ) )
	#define libandria4_commonio_handle_TELL( hptr ) \
		( libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? ( \
					( hptr )->dispatch == libandria4_commonio_handle_vtabtype_handle ? \
						libandria4_commonio_handle_TELL_HELPER1( ( hptr ), (hptr)->vtab.hand ) : ( \
							( hptr )->dispatch == libandria4_commonio_handle_vtabtype_seekable ? \
								libandria4_commonio_handle_TELL_HELPER1( ( hptr ), (hptr)->vtab.seek ) : ( \
									( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_istream ? \
										libandria4_commonio_handle_TELL_HELPER2( (hptr), (hptr)->vtab.istr ) : ( \
											( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_ostream ? \
												libandria4_commonio_handle_TELL_HELPER2( (hptr), (hptr)->vtab.ostr ) : \
												LIBANDRIA4_COMMONIO_EITHLONG_ERR_3() ) ) ) ) : \
				LIBANDRIA4_COMMONIO_EITHLONG_ERR_1() )
	
		#define libandria4_commonio_handle_SEEK_HELPER1( hptr, vtptr,  dist, origin ) \
			( (vtptr) ? \
				(vtptr)->seek( (hptr),  (dist), (origin) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2() )
		#define libandria4_commonio_handle_SEEK_HELPER2( hptr, vtptr,  dist, origin ) \
			libandria4_commonio_handle_SEEK_HELPER1( (hptr), \
				LIBANDRIA4_MONAD_MAYBE_REDUCE( libandria4_commonio_seekable*, (vtptr)->seekable, 0 ), \
				(dist), (origin) )
	#define libandria4_commonio_handle_SEEK( hptr,  dist, origin ) \
		( libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? ( \
					( hptr )->dispatch == libandria4_commonio_handle_vtabtype_handle ? \
						libandria4_commonio_handle_SEEK_HELPER1( \
								( hptr ), (hptr)->vtab.hand,  (dist), (origin) ) : ( \
							( hptr )->dispatch == libandria4_commonio_handle_vtabtype_seekable ? \
								libandria4_commonio_handle_SEEK_HELPER1( \
										( hptr ), (hptr)->vtab.seek,  (dist), (origin) ) : ( \
									( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_istream ? \
										libandria4_commonio_handle_SEEK_HELPER2( \
												(hptr), (hptr)->vtab.istr,  (dist), (origin) ) : ( \
											( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_ostream ? \
												libandria4_commonio_handle_SEEK_HELPER2( \
													(hptr), (hptr)->vtab.ostr,  (dist), (origin) ) : \
												LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_3() ) ) ) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
		#define libandria4_commonio_handle_REWIND_HELPER1( hptr, vtptr ) \
			( (vtptr) ? \
				(vtptr)->rewind( (hptr) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2() )
		#define libandria4_commonio_handle_REWIND_HELPER2( hptr, vtptr ) \
			libandria4_commonio_handle_REWIND_HELPER1( (hptr), \
				LIBANDRIA4_MONAD_MAYBE_REDUCE( libandria4_commonio_seekable*, (vtptr)->seekable, 0 ) )
	#define libandria4_commonio_handle_REWIND( hptr ) \
		( libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? ( \
					( hptr )->dispatch == libandria4_commonio_handle_vtabtype_handle ? \
						libandria4_commonio_handle_REWIND_HELPER1( ( hptr ), (hptr)->vtab.hand ) : ( \
							( hptr )->dispatch == libandria4_commonio_handle_vtabtype_seekable ? \
								libandria4_commonio_handle_REWIND_HELPER1( ( hptr ), (hptr)->vtab.seek ) : ( \
									( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_istream ? \
										libandria4_commonio_handle_REWIND_HELPER2( (hptr), (hptr)->vtab.istr ) : ( \
											( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_ostream ? \
												libandria4_commonio_handle_REWIND_HELPER2( (hptr), (hptr)->vtab.ostr ) : \
												LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_3() ) ) ) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
	
		#define libandria4_commonio_handle_CLEARERR_HELPER1( hptr, vtptr ) \
			( (vtptr) ? \
				(vtptr)->clearerr( (hptr) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2() )
		#define libandria4_commonio_handle_CLEARERR_HELPER2( hptr, vtptr ) \
			libandria4_commonio_handle_CLEARERR_HELPER1( (hptr), \
				LIBANDRIA4_MONAD_MAYBE_REDUCE( libandria4_commonio_errorable*, (vtptr)->errable, 0 ) )
	#define libandria4_commonio_handle_CLEARERR( hptr ) \
		( libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? ( \
					( hptr )->dispatch == libandria4_commonio_handle_vtabtype_handle ? \
						libandria4_commonio_handle_CLEARERR_HELPER1( ( hptr ), (hptr)->vtab.hand ) : ( \
							( hptr )->dispatch == libandria4_commonio_handle_vtabtype_errorable ? \
								libandria4_commonio_handle_CLEARERR_HELPER1( ( hptr ), (hptr)->vtab.err ) : ( \
									( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_istream ? \
										libandria4_commonio_handle_CLEARERR_HELPER2( (hptr), (hptr)->vtab.istr ) : ( \
											( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_ostream ? \
												libandria4_commonio_handle_CLEARERR_HELPER2( (hptr), (hptr)->vtab.ostr ) : \
												LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_3() ) ) ) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
		#define libandria4_commonio_handle_EOF_HELPER1( hptr, vtptr ) \
			( (vtptr) ? \
				(vtptr)->eof( (hptr) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2() )
		#define libandria4_commonio_handle_EOF_HELPER2( hptr, vtptr ) \
			libandria4_commonio_handle_EOF_HELPER1( (hptr), \
				LIBANDRIA4_MONAD_MAYBE_REDUCE( libandria4_commonio_errorable*, (vtptr)->errable, 0 ) )
	#define libandria4_commonio_handle_EOF( hptr ) \
		( libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? ( \
					( hptr )->dispatch == libandria4_commonio_handle_vtabtype_handle ? \
						libandria4_commonio_handle_EOF_HELPER1( ( hptr ), (hptr)->vtab.hand ) : ( \
							( hptr )->dispatch == libandria4_commonio_handle_vtabtype_errorable ? \
								libandria4_commonio_handle_EOF_HELPER1( ( hptr ), (hptr)->vtab.err ) : ( \
									( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_istream ? \
										libandria4_commonio_handle_EOF_HELPER2( (hptr), (hptr)->vtab.istr ) : ( \
											( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_ostream ? \
												libandria4_commonio_handle_EOF_HELPER2( (hptr), (hptr)->vtab.ostr ) : \
												LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_3() ) ) ) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
		#define libandria4_commonio_handle_ERROR_HELPER1( hptr, vtptr ) \
			( (vtptr) ? \
				(vtptr)->error( (hptr) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2() )
		#define libandria4_commonio_handle_ERROR_HELPER2( hptr, vtptr ) \
			libandria4_commonio_handle_ERROR_HELPER1( (hptr), \
				LIBANDRIA4_MONAD_MAYBE_REDUCE( libandria4_commonio_errorable*, (vtptr)->errable, 0 ) )
	#define libandria4_commonio_handle_ERROR( hptr ) \
		( libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? ( \
					( hptr )->dispatch == libandria4_commonio_handle_vtabtype_handle ? \
						libandria4_commonio_handle_ERROR_HELPER1( ( hptr ), (hptr)->vtab.hand ) : ( \
							( hptr )->dispatch == libandria4_commonio_handle_vtabtype_errorable ? \
								libandria4_commonio_handle_ERROR_HELPER1( ( hptr ), (hptr)->vtab.err ) : ( \
									( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_istream ? \
										libandria4_commonio_handle_ERROR_HELPER2( (hptr), (hptr)->vtab.istr ) : ( \
											( hptr )->dispatch ==  libandria4_commonio_handle_vtabtype_ostream ? \
												libandria4_commonio_handle_ERROR_HELPER2( (hptr), (hptr)->vtab.ostr ) : \
												LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_3() ) ) ) ) : \
				LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
	
		#define libandria4_commonio_handle_CLOSE_HELPER1( hptr, vtptr ) ( (vtptr)->close( (hptr) ) )
		#define libandria4_commonio_handle_CLOSE_HELPER2( type, hptr ) ( \
			(type) == libandria4_commonio_handle_vtabtype_seekable ? \
				libandria4_commonio_handle_CLOSE_HELPER1( (hptr), (hptr)->vtab.seek ) : ( \
					(type) == libandria4_commonio_handle_vtabtype_errorable ? \
						libandria4_commonio_handle_CLOSE_HELPER1( (hptr), (hptr)->vtab.err ) : \
						LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2() ) )
	#define libandria4_commonio_handle_CLOSE( hptr ) ( \
			libandria4_commonio_handle_verifydispatch( ( hptr ) ) ? \
					libandria4_commonio_handle_EXPRMATCH( *( hptr ), \
						libandria4_commonio_handle_CLOSE_HELPER1, \
						libandria4_commonio_handle_CLOSE_HELPER1, \
						libandria4_commonio_handle_CLOSE_HELPER1, \
						libandria4_commonio_handle_CLOSE_HELPER2 ) : \
					LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() )
	
#endif
/* End libandria4 basic streamshelpers.h */
