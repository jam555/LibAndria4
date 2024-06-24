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

#ifndef LIBANDRIA4_BASIC_COMMONIO_H
# define LIBANDRIA4_BASIC_COMMONIO_H
	
	#include "monads.h"
	#include "nulls.h"
	#include "simpleops.h"
	
	/* Note that streams.h is included at the end of this file. */
	
	
	
	typedef uint8_t libandria4_commonio_byte;
	typedef uint32_t libandria4_commonio_succ;
	typedef uint32_t libandria4_commonio_err;
	typedef uintptr_t libandria4_commonio_perr;
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonio_maybyte,
		libandria4_commonio_byte
	);
	
	#define LIBANDRIA4_COMMONIO_MAYBYTE_JUSTBYTE( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_commonio_maybyte, libandria4_commonio_byte, val )
	#define LIBANDRIA4_COMMONIO_MAYBYTE_FORCE_NOBYTE( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_maybyte, libandria4_commonio_byte )
	#define LIBANDRIA4_COMMONIO_MAYBYTE_NOBYTE() \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_maybyte, libandria4_commonio_byte )
	
		/* *BODY* takes statements, *EXPR* takes expressions, *REDUCE */
		/*  extracts values. */
	#define LIBANDRIA4_COMMONIO_MAYBYTE_BODYMATCH( var,  onerr, onsucc ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onerr, onsucc )
	#define LIBANDRIA4_COMMONIO_MAYBYTE_EXPRMATCH( var,  onerr, onsucc ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onerr, onsucc )
		/* "onsucc" always produces a "nothing" monad, so onerr should do */
		/*  something compatible. Basically only useful for translating */
		/*  between "maybe" types. */
	#define LIBANDRIA4_COMMONIO_MAYBYTE_EXPRCHAIN( var,  name, type, onerr ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( name, type,  var,  onerr )
			/* alt gets subbed in for "nothing". */
	#define LIBANDRIA4_COMMONIO_MAYBYTE_REDUCE( var,  alttype, altval ) \
		LIBANDRIA4_MONAD_MAYBE_REDUCE( var,  alttype, altval )
	#define LIBANDRIA4_COMMONIO_MAYBYTE_NULLSUCC( var,  onerr ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onerr, LIBANDRIA4_NOACTION )
	
	#define LIBANDRIA4_COMMONIO_MAYBYTE_RETTBYTE( val ) \
		return( LIBANDRIA4_COMMONIO_MAYBYTE_JUSTBYTE( val ) );
	#define LIBANDRIA4_COMMONIO_MAYBYTE_FORCE_RETNOBYTE( ... ) \
		return( LIBANDRIA4_COMMONIO_MAYBYTE_NOBYTE() );
	#define LIBANDRIA4_COMMONIO_MAYBYTE_RETNOBYTE() \
		return( LIBANDRIA4_COMMONIO_MAYBYTE_NOBYTE() );
	
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonio_mayerr,
		libandria4_commonio_err
	);
	
	#define LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_commonio_mayerr, libandria4_commonio_err, val )
	#define LIBANDRIA4_COMMONIO_MAYERR_FORCE_NOERR( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_mayerr, libandria4_commonio_err )
	#define LIBANDRIA4_COMMONIO_MAYERR_NOERR() \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_mayerr, libandria4_commonio_err )
	
		/* *BODY* takes statements, *EXPR* takes expressions, *REDUCE */
		/*  extracts values. */
	#define LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( var,  onerr, onsucc ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onerr, onsucc )
	#define LIBANDRIA4_COMMONIO_MAYERR_EXPRMATCH( var,  onerr, onsucc ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onerr, onsucc )
		/* "onsucc" always produces a "nothing" monad, so onerr should do */
		/*  something compatible. Basically only useful for translating */
		/*  between "maybe" types. */
	#define LIBANDRIA4_COMMONIO_MAYERR_EXPRCHAIN( var,  name, type, onerr ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( name, type,  var,  onerr )
			/* alt gets subbed in for "nothing". */
	#define LIBANDRIA4_COMMONIO_MAYERR_REDUCE( var,  alttype, altval ) \
		LIBANDRIA4_MONAD_MAYBE_REDUCE( var,  alttype, altval )
	#define LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( var,  onerr ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onerr, LIBANDRIA4_NOACTION )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithbyte,
			libandria4_commonio_byte,
			libandria4_commonio_err
	);
	
		/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHBYTE_BYTE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithbyte, libandria4_commonio_byte, val )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithbyte, libandria4_commonio_err, val )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_ERR_1() LIBANDRIA4_COMMONIO_EITHBYTE_ERR( 1 )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_ERR_2() LIBANDRIA4_COMMONIO_EITHBYTE_ERR( 2 )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_ERR_3() LIBANDRIA4_COMMONIO_EITHBYTE_ERR( 3 )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var,  onsucc, onerr )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_EXPRMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var,  onsucc, onerr )
			/* onsucc() should usually return a */
				/* LIBANDRIA4_COMMONIO_MAYERR_NOERR() */
			/*  but generally MUST return a libandria4_commonio_mayerr. */
	#define LIBANDRIA4_COMMONIO_EITHBYTE_EXPRCHAIN( var,  onsucc ) \
		LIBANDRIA4_MONAD_EITHER_EXPRCHAIN( \
			var,  onsucc, LIBANDRIA4_COMMONIO_MAYERR_JUSTERR )
			/* A shallow wrapper around *_EXPRMATCH. */
	#define LIBANDRIA4_COMMONIO_EITHBYTE_REDUCE( var,  reduce_a, reduce_b ) \
		LIBANDRIA4_MONAD_EITHER_REDUCE( var,  reduce_a, reduce_b )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_TO_MAYERR( var ) \
		LIBANDRIA4_COMMONIO_EITHBYTE_REDUCE( \
			var, \
				LIBANDRIA4_COMMONIO_MAYERR_FORCE_NOERR, \
				LIBANDRIA4_COMMONIO_MAYERR_JUSTERR )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithgeneric,
			libandria4_commonio_succ,
			libandria4_commonio_err
	);
	
		/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_BYTE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithgeneric, libandria4_commonio_succ, val )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithgeneric, libandria4_commonio_err, val )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1() LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 1 )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2() LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 2 )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_3() LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 3 )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var,  onsucc, onerr )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_EXPRMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var,  onsucc, onerr )
			/* onsucc() should usually return a */
				/* LIBANDRIA4_COMMONIO_MAYERR_NOERR() */
			/*  but generally MUST return a libandria4_commonio_mayerr. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_EXPRCHAIN( var,  onsucc ) \
		LIBANDRIA4_MONAD_EITHER_EXPRCHAIN( \
			var,  onsucc, LIBANDRIA4_COMMONIO_MAYERR_JUSTERR )
			/* A shallow wrapper around *_EXPRMATCH. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_REDUCE( var,  reduce_a, reduce_b ) \
		LIBANDRIA4_MONAD_EITHER_REDUCE( var,  reduce_a, reduce_b )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_TO_MAYERR( var ) \
		LIBANDRIA4_COMMONIO_EITHBYTE_REDUCE( \
			var, \
				LIBANDRIA4_COMMONIO_MAYERR_FORCE_NOERR, \
				LIBANDRIA4_COMMONIO_MAYERR_JUSTERR )
	
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( val ) \
		return( LIBANDRIA4_COMMONIO_EITHGENERIC_BYTE( val ) );
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( val ) \
		return( LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( val ) );
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithlong,
			long,
			libandria4_commonio_err
	);
	
		/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHLONG_BYTE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithlong, long, val )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithlong, libandria4_commonio_err, val )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR_1() LIBANDRIA4_COMMONIO_EITHLONG_ERR( 1 )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR_2() LIBANDRIA4_COMMONIO_EITHLONG_ERR( 2 )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR_3() LIBANDRIA4_COMMONIO_EITHLONG_ERR( 3 )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_COMMONIO_EITHLONG_BODYMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var,  onsucc, onerr )
	#define LIBANDRIA4_COMMONIO_EITHLONG_EXPRMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var,  onsucc, onerr )
			/* onsucc() should usually return a */
				/* LIBANDRIA4_COMMONIO_MAYERR_NOERR() */
			/*  but generally MUST return a libandria4_commonio_mayerr. */
	#define LIBANDRIA4_COMMONIO_EITHLONG_EXPRCHAIN( var,  onsucc ) \
		LIBANDRIA4_MONAD_EITHER_EXPRCHAIN( \
			var,  onsucc, LIBANDRIA4_COMMONIO_MAYERR_JUSTERR )
			/* A shallow wrapper around *_EXPRMATCH. */
	#define LIBANDRIA4_COMMONIO_EITHLONG_REDUCE( var,  reduce_a, reduce_b ) \
		LIBANDRIA4_MONAD_EITHER_REDUCE( var,  reduce_a, reduce_b )
	#define LIBANDRIA4_COMMONIO_EITHLONG_TO_MAYERR( var ) \
		LIBANDRIA4_COMMONIO_EITHBYTE_REDUCE( \
			var, \
				LIBANDRIA4_COMMONIO_MAYERR_FORCE_NOERR, \
				LIBANDRIA4_COMMONIO_MAYERR_JUSTERR )
	
	
	
	/* The types below all have *2 names: this indicates that they use */
	/*  libandria4_commonio_perr instead of libandria4_commonio_err. */
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithsize2,
			size_t,
			libandria4_commonio_perr
	);
	#define LIBANDRIA4_COMMONIO_EITHSIZE2_BUILDSIZE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithsize2, size_t, val )
	#define LIBANDRIA4_COMMONIO_EITHSIZE2_BUILDERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithsize2, libandria4_commonio_perr, val )
	#define LIBANDRIA4_COMMONIO_EITHSIZE2_RETURNSIZE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_commonio_eithsize2, size_t, val )
	#define LIBANDRIA4_COMMONIO_EITHSIZE2_RETURNERR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_commonio_eithsize2, libandria4_commonio_perr, val )
	
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonio_mayerr2,
			libandria4_commonio_perr
	);
	#define LIBANDRIA4_COMMONIO_MAYERR2_BUILDJUST( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_commonio_mayerr2, libandria4_commonio_perr, val )
	#define LIBANDRIA4_COMMONIO_MAYERR2_BUILDNOTHING( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonio_mayerr2, libandria4_commonio_perr )
	#define LIBANDRIA4_COMMONIO_MAYERR2_RETURNJUST( val ) \
		LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_commonio_mayerr2, libandria4_commonio_perr, val )
	#define LIBANDRIA4_COMMONIO_MAYERR2_RETURNNOTHING( ... ) \
		LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_commonio_mayerr2, libandria4_commonio_perr )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithchar2,
			char,
			libandria4_commonio_perr
	);
	#define LIBANDRIA4_COMMONIO_EITHCHAR2_BUILDCHAR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithchar2, char, val )
	#define LIBANDRIA4_COMMONIO_EITHCHAR2_BUILDERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithchar2, libandria4_commonio_perr, val )
	#define LIBANDRIA4_COMMONIO_EITHCHAR2_RETURNCHAR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_commonio_eithchar2, char, val )
	#define LIBANDRIA4_COMMONIO_EITHCHAR2_RETURNERR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_commonio_eithchar2, libandria4_commonio_perr, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithintmax2,
			intmax_t,
			libandria4_commonio_perr
	);
	#define LIBANDRIA4_COMMONIO_EITHINTMAX2_BUILDINT( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithintmax2, intmax_t, val )
	#define LIBANDRIA4_COMMONIO_EITHINTMAX2_BUILDERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithintmax2, libandria4_commonio_perr, val )
	#define LIBANDRIA4_COMMONIO_EITHINTMAX2_RETURNINT( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_commonio_eithintmax2, intmax_t, val )
	#define LIBANDRIA4_COMMONIO_EITHINTMAX2_RETURNERR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_commonio_eithintmax2, libandria4_commonio_perr, val )
	
	
	
	
	
	/* These exist for convenience. */
	
	#define libandria4_commonio_int_RETERR1( ... ) return( -1 );
	#define libandria4_commonio_int_RETERR2( ... ) return( -2 );
	#define libandria4_commonio_int_RETERR3( ... ) return( -3 );
	#define libandria4_commonio_int_RETERR4( ... ) return( -4 );
	#define libandria4_commonio_int_RETERR5( ... ) return( -5 );
	
	#define libandria4_commonio_int_RETERR6( ... ) return( -6 );
	#define libandria4_commonio_int_RETERR7( ... ) return( -7 );
	#define libandria4_commonio_int_RETERR8( ... ) return( -8 );
	#define libandria4_commonio_int_RETERR9( ... ) return( -9 );
	
	
	
	/* libandria4_commonio_handle{} has been moved to streams.h */
		/* Various things that formerly were in this file. */
	#include "streams.h"
	
	
	
	/* Convenience wrappers. */
		/* Tests for close & error handler functionality only. */
	int libandria4_commonio_handle_hasbasics( libandria4_commonio_handle* );
		/* Clears errors, fails on EOF and failed clears. */
	int libandria4_commonio_utility_clearerr( libandria4_commonio_handle* );
	int libandria4_commonio_recursivewrapper_puts_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *str, size_t len
	);
	int libandria4_commonio_utility_putint( libandria4_commonio_handle *io,  int i );
	
	
	
	typedef struct libandria4_FILE_handle
	{
		FILE *f;
		uintptr_t ref_count;
	};
	
	
	
		/* Common values for IO systems. */
	#include "commoniovals.h"
	
#endif
/* End libandria4 basic commonio.h */
