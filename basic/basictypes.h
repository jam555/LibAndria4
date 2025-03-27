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

#ifndef LIBANDRIA4_BASIC_BASICTYPES_H
# define LIBANDRIA4_BASIC_BASICTYPES_H
	
	#include "monads.h"
	#include "nulls.h"
	#include "simpleops.h"
	
	
	
	typedef uint8_t libandria4_commonio_byte;
	typedef uint32_t libandria4_commonio_succ;
	typedef uint32_t libandria4_commonio_err;
	typedef uintptr_t libandria4_commonio_perr;
	typedef libandria4_commonio_perr libandria4_error_errint;
	
	#define LIBANDRIA4_COMMONIO_BYTE_MIN 0
	#define LIBANDRIA4_COMMONIO_BYTE_MAX UINT8_MAX
	
	#define LIBANDRIA4_COMMONIO_SUCC_MIN 0
	#define LIBANDRIA4_COMMONIO_SUCC_MAX UINT32_MAX
	
	#define LIBANDRIA4_COMMONIO_ERR_MIN 0
	#define LIBANDRIA4_COMMONIO_ERR_MAX UINT32_MAX
	
	#define LIBANDRIA4_COMMONIO_PERR_MIN 0
	#define LIBANDRIA4_COMMONIO_PERR_MAX UINTPTR_MAX
	
	
	
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
	#define LIBANDRIA4_COMMONIO_MAYBYTE_BODYMATCH( var,  onval, onnothing ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onval, onnothing )
	#define LIBANDRIA4_COMMONIO_MAYBYTE_EXPRMATCH( var,  onval, onnothing ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onval, onnothing )
		/* "onsucc" always produces a "nothing" monad, so onerr should do */
		/*  something compatible. Basically only useful for translating */
		/*  between "maybe" types. */
	#define LIBANDRIA4_COMMONIO_MAYBYTE_EXPRCHAIN( var,  name, type, onval ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( name, type,  var,  onval )
			/* alt gets subbed in for "nothing". */
	#define LIBANDRIA4_COMMONIO_MAYBYTE_REDUCE( var,  alttype, altval ) \
		LIBANDRIA4_MONAD_MAYBE_REDUCE( var,  alttype, altval )
	#define LIBANDRIA4_COMMONIO_MAYBYTE_NULLSUCC( var,  onval ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onval, LIBANDRIA4_NOACTION )
	
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
	#define LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( var,  onerr, onnothing ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onerr, onnothing )
	#define LIBANDRIA4_COMMONIO_MAYERR_EXPRMATCH( var,  onerr, onnothing ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onerr, onnothing )
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
	#define LIBANDRIA4_COMMONIO_EITHBYTE_ERR_1( ... ) LIBANDRIA4_COMMONIO_EITHBYTE_ERR( 1 )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_ERR_2( ... ) LIBANDRIA4_COMMONIO_EITHBYTE_ERR( 2 )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_ERR_3( ... ) LIBANDRIA4_COMMONIO_EITHBYTE_ERR( 3 )
	
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
	
	#define LIBANDRIA4_COMMONIO_EITHBYTE_RETBYTE( val ) \
		return( LIBANDRIA4_COMMONIO_EITHBYTE_BYTE( val ) )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( val ) \
		return( LIBANDRIA4_COMMONIO_EITHBYTE_ERR( val ) )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithgeneric,
			libandria4_commonio_succ,
			libandria4_commonio_err
	);
	
		/* Just in case I used *_BYTE() somewhere. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_BYTE( val ) LIBANDRIA4_COMMONIO_EITHGENERIC_SUCC( val )
		/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_SUCC( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithgeneric, libandria4_commonio_succ, val )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithgeneric, libandria4_commonio_err, val )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1( ... ) LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 1 )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_2( ... ) LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 2 )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_3( ... ) LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 3 )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_4( ... ) LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 4 )
	
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
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_TO_ERRMAYERR( var ) \
		LIBANDRIA4_COMMONIO_EITHBYTE_REDUCE( \
			var, \
				LIBANDRIA4_ERROR_MAYERR_FORCENOERR, \
				LIBANDRIA4_ERROR_MAYERR_JUSTERR )
	
		/* Just in case I used *_BYTE() somewhere. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( val ) \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETSUCC( val )
			/* The actual returns. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_RETSUCC( val ) \
		return( LIBANDRIA4_COMMONIO_EITHGENERIC_BYTE( val ) );
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( val ) \
		return( LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( val ) );
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithlong,
			long,
			libandria4_commonio_err
	);
	
		/* *_BYTE() might be used somewhere, so it's being retained, but */
		/*  bear in mind that it's the wrong name. */
	#define LIBANDRIA4_COMMONIO_EITHLONG_BYTE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithlong, long, val )
			/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHLONG_LONG( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithlong, long, val )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithlong, libandria4_commonio_err, val )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR_1( ... ) LIBANDRIA4_COMMONIO_EITHLONG_ERR( 1 )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR_2( ... ) LIBANDRIA4_COMMONIO_EITHLONG_ERR( 2 )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR_3( ... ) LIBANDRIA4_COMMONIO_EITHLONG_ERR( 3 )
	
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
	
	/* Returns. */
		/* This one is the wrong name, but maybe it's used, so it stays. */
	#define LIBANDRIA4_COMMONIO_EITHLONG_RETBYTE( val ) \
		return( LIBANDRIA4_COMMONIO_EITHLONG_LONG( val ) )
	#define LIBANDRIA4_COMMONIO_EITHLONG_RETLONG( val ) \
		return( LIBANDRIA4_COMMONIO_EITHLONG_LONG( val ) )
	#define LIBANDRIA4_COMMONIO_EITHLONG_RETERR( val ) \
		return( LIBANDRIA4_COMMONIO_EITHLONG_ERR( val ) )
	
	
	
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/* Turn the following into just wrappers. */
	
	
		/* typedef libandria4_commonio_perr libandria4_error_errint; */
	/* LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_error_mayerr, libandria4_error_errint ); */
	/* As part of the process of merging duplicate types, this is now a typedef. */
	typedef libandria4_commonio_mayerr2 libandria4_error_mayerr;
	
	#define LIBANDRIA4_ERROR_MAYERR_JUSTERR( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_error_mayerr, libandria4_error_errint, val )
	#define LIBANDRIA4_ERROR_MAYERR_FORCENOERR( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_error_mayerr, libandria4_error_errint )
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
	#define LIBANDRIA4_ERROR_MAYERR_RETURN_FORCESUCCESS( ... ) \
		return( LIBANDRIA4_ERROR_MAYERR_NOERR() );
	
#endif
/* End libandria4 basic basictypes.h */