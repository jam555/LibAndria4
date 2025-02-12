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

#ifndef LIBANDRIA4_BASIC_STREAMS_H
# define LIBANDRIA4_BASIC_STREAMS_H
	
	#include "arraccess.h"
		/* commonio.h also includes this file, but does so after it's */
		/*  defined several types that we use here. */
	#include "commonio.h"
	
	
	
	/* TODO: */
		/* Convert commonio.h/.c (and anything else relevant) to use this */
		/*  new interface instead of the old one. */
		/* Add "is_valid" test functions to all of the virtual-tables: this */
		/*  SHOULDN'T indicate the stream status, just the HANDLE status. */
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
	
	
	typedef struct libandria4_commonio_handle libandria4_commonio_handle;
	
	typedef struct libandria4_commonio_handle_vtable libandria4_commonio_handle_vtable;
	typedef struct libandria4_commonio_errorable_vtable libandria4_commonio_errorable_vtable;
	typedef struct libandria4_commonio_seekable_vtable libandria4_commonio_seekable_vtable;
	typedef struct libandria4_commonio_istream_vtable libandria4_commonio_istream_vtable;
	typedef struct libandria4_commonio_ostream_vtable libandria4_commonio_ostream_vtable;
	
	typedef struct libandria4_commonio_errorable libandria4_commonio_errorable;
	typedef struct libandria4_commonio_seekable libandria4_commonio_seekable;
	
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonio_mayerrable,
		libandria4_commonio_errorable*
	);
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonio_mayseek,
		libandria4_commonio_seekable*
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
	struct libandria4_commonio_handle
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
	};
	
	struct libandria4_commonio_errorable
	{
	};
	struct libandria4_commonio_seekable
	{
	};
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
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithhandle,
			libandria4_commonio_handle,
			libandria4_commonio_err
	);
	
		/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_HANDLE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithhandle, libandria4_commonio_handle, val )
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithhandle, libandria4_commonio_err, val )
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_ERR_1() LIBANDRIA4_COMMONIO_EITHHANDLE_ERR( 1 )
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_ERR_2() LIBANDRIA4_COMMONIO_EITHHANDLE_ERR( 2 )
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_ERR_3() LIBANDRIA4_COMMONIO_EITHHANDLE_ERR( 3 )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_BODYMATCH( var,  onhand, onerr ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var,  onhand, onerr )
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_EXPRMATCH( var,  onhand, onerr ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var,  onhand, onerr )
			/* onsucc() should usually return a */
				/* LIBANDRIA4_COMMONIO_MAYERR_NOERR() */
			/*  but generally MUST return a libandria4_commonio_mayerr. */
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_EXPRCHAIN( var,  onhand ) \
		LIBANDRIA4_MONAD_EITHER_EXPRCHAIN( \
			var,  onhand, LIBANDRIA4_COMMONIO_MAYERR_JUSTERR )
			/* A shallow wrapper around *_EXPRMATCH. */
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_REDUCE( var,  reduce_hand, reduce_b ) \
		LIBANDRIA4_MONAD_EITHER_REDUCE( var,  reduce_hand, reduce_b )
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_TO_MAYERR( var ) \
		LIBANDRIA4_COMMONIO_EITHHANDLE_REDUCE( \
			var, \
				LIBANDRIA4_COMMONIO_MAYERR_FORCE_NOERR, \
				LIBANDRIA4_COMMONIO_MAYERR_JUSTERR )
	
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_RETHANDLE( val ) \
		return( LIBANDRIA4_COMMONIO_EITHHANDLE_HANDLE( val ) )
	#define LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( val ) \
		return( LIBANDRIA4_COMMONIO_EITHHANDLE_ERR( val ) )
	
	
	
	#include "pascalstring.h"
	
	libandria4_commonio_eithhandle
		libandria4_commonio_fopen
		(
			libandria4_char_pascalarray*,
			libandria4_commonio_handle_vtabtype
		);
	
	
	
	#include "streamshelpers.h"
	
#endif
/* End libandria4 basic stream.h */
