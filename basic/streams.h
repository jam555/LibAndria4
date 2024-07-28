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

#ifndef LIBANDRIA4_TEXT_STREAMS_H
# define LIBANDRIA4_TEXT_STREAMS_H
	
	#include "arraccess.h"
		/* commonio.h also includes this file, but does so after it's */
		/*  defined several types that we use here. */
	#include "commonio.h"
	
	
	
	/* TODO: */
		/* Convert commonio.h/.c (and anything else relevant) to use this */
		/*  new interface instead of the old one. */
	/*
		This is the mostly new LibAndria4 I/O stream system. Previous stabs at
		this have variously been incomplete, or gotten things very wrong
		(treating the virtual table as the actual stream pointer). This version
		is meant to fix all of that. Note that while some incomplete attempts
		have included a "get descriptors" function that itself took a callback
		pointer, this version does not: that may need to be changed in the
		future, but will be left alone for now. The system is slightly complex,
		and thus several function-macros have been provided: they are
		documented in a big block comment to the extent that they need to be,
		so use them.
	*/
	
	
	/* TODO: I think we need: */
		/* typedef struct libandria4_commonio_handle libandria4_commonio_handle; */
	/* here? */
	
	typedef struct libandria4_commonio_handle_vtable libandria4_commonio_handle_vtable;
	typedef struct libandria4_commonio_errorable_vtable libandria4_commonio_errorable_vtable;
	typedef struct libandria4_commonio_seekable_vtable libandria4_commonio_seekable_vtable;
	typedef struct libandria4_commonio_istream_vtable libandria4_commonio_istream_vtable;
	typedef struct libandria4_commonio_ostream_vtable libandria4_commonio_ostream_vtable;
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonio_mayerrable,
		( libandria4_commonio_errorable* )
	);
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonio_mayseek,
		( libandria4_commonio_seekable* )
	);
	
	/* Do I even use these macros anywhere? They may need to be moved */
	/*  to the bottom and added to documentation. */
	
	#define LIBANDRIA4_COMMONIO_MAYERR_JUSTERRABLE( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_commonio_mayerrable, ( libandria4_commonio_errorable* ), val )
	#define LIBANDRIA4_COMMONIO_MAYERR_FORCE_NOERRABLE( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_mayerrable, ( libandria4_commonio_errorable* ) )
	#define LIBANDRIA4_COMMONIO_MAYERR_NOERRABLE() \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_mayerrable, ( libandria4_commonio_errorable* ) )
	
	#define LIBANDRIA4_COMMONIO_MAYERR_JUSTSEEKABLE( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_commonio_mayseek, ( libandria4_commonio_seekable* ), val )
	#define LIBANDRIA4_COMMONIO_MAYERR_FORCE_NOSEEKABLE( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_mayseek, ( libandria4_commonio_seekable* ) )
	#define LIBANDRIA4_COMMONIO_MAYERR_NOSEEKABLE() \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_mayseek, ( libandria4_commonio_seekable* ) )
	
	
	/* Function pointers for the various stream I/O operations. */
	
	typedef
		libandria4_commonio_eithgeneric
			(*libandria4_commonio_genericfunc)
				( libandria4_commonio_handle* );
	
	typedef
		libandria4_commonio_eithbyte
			(*libandria4_commonio_fetchbyte)
				( libandria4_commonio_handle* );
	typedef
		libandria4_commonio_eithgeneric
			(*libandria4_commonio_storebyte)
				( libandria4_commonio_handle*, libandria4_commonio_byte );
	
	typedef
		libandria4_commonio_eithgeneric
			(*libandria4_commonio_strfunc)
				( libandria4_commonio_handle*, libandria4_commonio_byte*, size_t );
	
	typedef
		libandria4_commonio_eithlong
			(*libandria4_commonio_longfunc)
				( libandria4_commonio_handle* );
	typedef
		libandria4_commonio_eithgeneric
			(*libandria4_commonio_seekfunc)
				( libandria4_commonio_handle*, long, int /* origin */ );
	
	
		/* This, with the addition of "uintptr_t typeid;", was */
		/*  formerly called libandria4_commonio_handle{}. A new */
		/*  version of libandria4_commonio_handle{} now exists */
		/*  further below. */
	struct libandria4_commonio_handle_vtable
	{
		libandria4_commonio_genericfunc flush;
		
		libandria4_commonio_fetchbyte getc;
		libandria4_commonio_storebyte ungetc;
		libandria4_commonio_storebyte putc;
		
		libandria4_commonio_strfunc gets_s;
		libandria4_commonio_strfunc puts_s;
		
		libandria4_commonio_longfunc tell;
		libandria4_commonio_seekfunc seek;
		libandria4_commonio_genericfunc rewind;
		
		libandria4_commonio_genericfunc clearerr;
		libandria4_commonio_genericfunc eof;
		libandria4_commonio_genericfunc error;
		
		libandria4_commonio_genericfunc close;
	};
	struct libandria4_commonio_istream_vtable
	{
			/* Must not be needed for istreams, just intended to */
			/*  give the backend of the stream a chance to */
			/*  optimize/improve/whatever it's internal works */
			/*  without calling another function.. */
		libandria4_commonio_genericfunc flush;
		
		libandria4_commonio_fetchbyte getc;
		libandria4_commonio_strfunc gets_s;
		
		libandria4_commonio_storebyte ungetc;
		
			/* Note: these are maybes, NOT function pointers. */
		libandria4_commonio_mayseek seekable;
		libandria4_commonio_mayerrable errable;
		
		libandria4_commonio_genericfunc close;
	};
	struct libandria4_commonio_ostream_vtable
	{
		libandria4_commonio_genericfunc flush;
		
		libandria4_commonio_storebyte putc;
		libandria4_commonio_strfunc puts_s;
		
			/* Note: these are maybes, NOT function pointers. */
		libandria4_commonio_mayseek seekable;
		libandria4_commonio_mayerrable errable;
		
		libandria4_commonio_genericfunc close;
	};
	struct libandria4_commonio_seekable_vtable
	{
		libandria4_commonio_genericfunc flush;
		
		libandria4_commonio_longfunc tell;
		libandria4_commonio_seekfunc seek;
		libandria4_commonio_genericfunc rewind;
		
		libandria4_commonio_genericfunc close;
	};
	struct libandria4_commonio_errorable_vtable
	{
		libandria4_commonio_genericfunc flush;
		
		libandria4_commonio_genericfunc clearerr;
		libandria4_commonio_genericfunc eof;
		libandria4_commonio_genericfunc error;
		
		libandria4_commonio_genericfunc close;
	};
	
		/* Welcome to the NEW libandria4_commonio_handle{} system. I */
		/*  have no idea why I did it the previous way. */
	typedef enum
	{
		libandria4_commonio_handle_vtabtype_invalid = 0,
		
		libandria4_commonio_handle_vtabtype_handle = 1,
		libandria4_commonio_handle_vtabtype_istream,
		libandria4_commonio_handle_vtabtype_ostream,
		libandria4_commonio_handle_vtabtype_seekable,
		libandria4_commonio_handle_vtabtype_errorable,
		
		libandria4_commonio_handle_vtabtype__END
	} libandria4_commonio_handle_vtabtype;
	typedef struct libandria4_commonio_handle
	{
		union
		{
			libandria4_commonio_handle_vtable *hand;
			libandria4_commonio_istream_vtable *istr;
			libandria4_commonio_ostream_vtable *ostr;
			libandria4_commonio_seekable_vtable *seek;
			libandria4_commonio_errorable_vtable *err;
			
		} vtab;
		libandria4_commonio_handle_vtabtype dispatch;
		
	} libandria4_commonio_handle;
	/*
		For the sake of convenience, a comprehensive set of function macros
		have been created to access the various standard functions accessible
		through (libandria4_commonio_handle*)->vtab. These macros are
		implemented as expressions returning a per-macro type that corresponds
		to the relevant function's return. Attempting to call a function on
		the wrong vtable type is properly handled, as to return an error
		instead of attempting the call anyways. The functions themselves are
		fairly standard ones based on C's standard file I/O system.
		
		"hptr" is universally meant to be a libandria4_commonio_handle* in
		these.
		
		Macros:
		
		libandria4_commonio_eithgeneric libandria4_commonio_handle_FLUSH( hptr )
		
		libandria4_commonio_eithbyte libandria4_commonio_handle_GETC( hptr )
		libandria4_commonio_eithgeneric libandria4_commonio_handle_UNGETC( hptr,  val )
			"val" is meant to be a libandria4_commonio_byte value.
		libandria4_commonio_eithgeneric libandria4_commonio_handle_GETS_S( hptr,  arr, len )
			"arr" is meant to be a libandria4_commonio_byte pointer.
			"len" is the number of elements pointed to be "arr".
		
		libandria4_commonio_eithgeneric libandria4_commonio_handle_PUTC( hptr,  val )
			"val" is meant to be a libandria4_commonio_byte value.
		libandria4_commonio_eithgeneric libandria4_commonio_handle_PUTS_S( hptr,  arr, len )
			"arr" is meant to be a libandria4_commonio_byte pointer.
			"len" is the number of elements pointed to be "arr".
		
		libandria4_commonio_eithlong libandria4_commonio_handle_TELL( hptr )
		libandria4_commonio_eithgeneric libandria4_commonio_handle_SEEK( hptr,  dist, origin )
			"dist" is meant to be a long value.
			"origin" is meant to be any of the values to the third argument of
				C's standard fseek() function.
		libandria4_commonio_eithgeneric libandria4_commonio_handle_REWIND( hptr )
		
		libandria4_commonio_eithgeneric libandria4_commonio_handle_CLEARERR( hptr )
		libandria4_commonio_eithgeneric libandria4_commonio_handle_EOF( hptr )
		libandria4_commonio_eithgeneric libandria4_commonio_handle_ERROR( hptr )
		
		libandria4_commonio_eithgeneric libandria4_commonio_handle_CLOSE( hptr )
	*/
	
	
	
	/*************************************************************/
	/*************************************************************/
	/** Common implementations, for cases where it's practical. **/
	/*************************************************************/
	/*************************************************************/
	
		/* Uses ->putc() to implement puts_s(). */
	libandria4_commonio_eithgeneric libandria4_commonio_common_puts_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *str, size_t len
	);
		/* Uses ->getc() to implement gets_s(). */
	libandria4_commonio_eithgeneric libandria4_commonio_common_gets_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *dest, size_t len
	);
	
	
	
		/* TODO: Should be a wrapper for a version in */
		/*  simpleops.h ... which I think doesn't exist. */
	#define libandria4_commonio_handlevtable_FROM_SRCVTABLE( src_type, dest_type, vtab_ptr ) \
		(dest_type*)( \
			(char*)( (src_type*)(vtab_ptr) ) + ( \
				( (char*)&( ( ( (dest_type*)0 )[ 1 ] ).here ) ) - \
				( (char*)&( ( (dest_type*)0 )[ 1 ] ) ) ) )
	
	
	
	/* TODO: Build a variant on libandria4_commonio_istream_ungetwrapper_vtable{} */
	/*  that DOESN'T CARE if .is points to an istream or a full stream. Requiring */
	/*  that is an unnecessary space consumer for something that gets allocated */
	/*  arbitrarily often. */
	
		/* Provides single-byte-only unget capabilities. */
	typedef struct libandria4_commonio_istream_ungetwrapper_vtable
	{
		libandria4_commonio_istream_vtable here;
		libandria4_commonio_istream_vtable *is;
		
		libandria4_commonio_maybyte buffer;
		
	} libandria4_commonio_istream_ungetwrapper;
	#define libandria4_commonio_istream_ungetwrapper_vtable_FROM_ISTREAMVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_istream_vtable, libandria4_commonio_istream_ungetwrapper_vtable, \
			vtab_ptr )
	int libandria4_commonio_istream_ungetwrapper_init
	(
		libandria4_commonio_istream_ungetwrapper_vtable *ugvtab,
		libandria4_commonio_istream_vtable *host
	);
	
	
	
	typedef struct libandria4_commonio_handlevtable_2istream
	{
		libandria4_commonio_istream_vtable here;
		libandria4_commonio_handle_vtable *is;
		
	} libandria4_commonio_handlevtable_2istream;
	#define libandria4_commonio_handlevtable_2istream_vtable_FROM_HANDLEVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_istream_vtable, libandria4_commonio_handlevtable_2istream, \
			vtab_ptr )
	int libandria4_commonio_handlevtable_2istream_init
	(
		libandria4_commonio_handlevtable_2istream *wrapper,
		libandria4_commonio_handle_vtable *host
	);
	
	typedef struct libandria4_commonio_handlevtable_2ostream
	{
		libandria4_commonio_ostream_vtable here;
		libandria4_commonio_handle_vtable *is;
		
	} libandria4_commonio_handlevtable_2ostream;
	#define libandria4_commonio_handlevtable_2ostream_vtable_FROM_HANDLEVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_handlevtable_2ostream, libandria4_commonio_handlevtable_2istream, \
			vtab_ptr )
	int libandria4_commonio_handlevtable_2ostream_init
	(
		libandria4_commonio_handlevtable_2ostream *wrapper,
		libandria4_commonio_handle_vtable *host
	);
	
	typedef struct libandria4_commonio_handlevtable_2seekable
	{
		libandria4_commonio_seekable_vtable here;
		libandria4_commonio_handle_vtable *is;
		
	} libandria4_commonio_handlevtable_2seekable;
	#define libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_handlevtable_2seekable, libandria4_commonio_handlevtable_2istream, \
			vtab_ptr )
	int libandria4_commonio_handlevtable_seekable_init
	(
		libandria4_commonio_handlevtable_2seekable *wrapper,
		libandria4_commonio_handle_vtable *host
	);
	
	typedef struct libandria4_commonio_handlevtable_2errorable
	{
		libandria4_commonio_errorable_vtable here;
		libandria4_commonio_handle_vtable *is;
		
	} libandria4_commonio_handlevtable_2errorable;
	#define libandria4_commonio_handlevtable_2errorable_vtable_FROM_HANDLEVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_handlevtable_2errorable, libandria4_commonio_handlevtable_2istream, \
			vtab_ptr )
	int libandria4_commonio_handlevtable_errorable_init
	(
		libandria4_commonio_handlevtable_2errorable *wrapper,
		libandria4_commonio_handle_vtable *host
	);
	
	
	
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
/* End libandria4 text stream.h */
