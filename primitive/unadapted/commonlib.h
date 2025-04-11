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

#ifndef LIBANDRIA4_BASIC_COMMONLIB_H
# define LIBANDRIA4_BASIC_COMMONLIB_H
	
	
	/* TODO: */
		/* Add more time functions. */
	/* NOTE: commonlib.c has the following TODOs: */
		/* Some code needs to be moved OUT of it. */
		/* *_sleep() needs to use LibAndria's platform-detection. */
	
	
		/* For size_t. */
	#include <stddef.h>
		/* For uintptr_t and uint*_t. */
	#include <stdint.h>
	#include "monads.h"
		/* For libandria4_ptrresult{} and libandria4_errno_2result(). */
	#include "stdmonads.h"
		/* For libandria4_error_mayerr{}. */
	#include "commonerr.h"
	
	
	
		/* A simple identity-mapping array: the index is the output. */
	extern const unsigned char libandria4_commonlib_firstchars[ 128 ];
	
	typedef uint8_t libandria4_commonlib_byte;
	typedef uint32_t libandria4_commonlib_succ;
	typedef uint32_t libandria4_commonlib_err;
	typedef uintptr_t libandria4_commonlib_perr;
	
	#define LIBANDRIA4_COMMONLIB_BYTE_MIN 0
	#define LIBANDRIA4_COMMONLIB_BYTE_MAX UINT8_MAX
	
	#define LIBANDRIA4_COMMONLIB_SUCC_MIN 0
	#define LIBANDRIA4_COMMONLIB_SUCC_MAX UINT32_MAX
	
	#define LIBANDRIA4_COMMONLIB_ERR_MIN 0
	#define LIBANDRIA4_COMMONLIB_ERR_MAX UINT32_MAX
	
	#define LIBANDRIA4_COMMONLIB_PERR_MIN 0
	#define LIBANDRIA4_COMMONLIB_PERR_MAX UINTPTR_MAX
	
	
	
		/* TODO: Move forking-type and it's macros into monads.h. */
		/* This is used here, so it's defined here. The common macros for it */
		/*  are further down. */
	#define LIBANDRIA4_COMMONLIB_FORKINGTYPE( prefix, type ) \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( prefix ## fork,  type, type ); \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( prefix ## eithfork, \
			prefix ## fork, libandria4_commonlib_err );
	
	
	
	/* TODO: Merge these (including the forking-types) into basictypes.h. */
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonlib_maybyte,
		libandria4_commonlib_byte
	);
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonlib_mayerr,
		libandria4_commonlib_err
	);
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonlib_eithbyte,
			libandria4_commonlib_byte,
			libandria4_commonlib_err
	);
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonlib_eithvoidp,
			void*,
			libandria4_commonlib_err
	);
	
		/* Defines libandria4_commonlib_charchar_fork{} and */
		/*  libandria4_commonlib_charchar_eithfork{}. */
	LIBANDRIA4_COMMONLIB_FORKINGTYPE( libandria4_commonlib_charchar_, char );
		/* Defines libandria4_commonlib_intint_fork{} and */
		/*  libandria4_commonlib_intint_eithfork{}. */
	LIBANDRIA4_COMMONLIB_FORKINGTYPE( libandria4_commonlib_intint_, int );
	
	/* The utility macros for all of those types are further down. */
	
	
	
		/* This literally just exists to waste a very small amount of time. */
		/*  It's implemented in commonlib2.c to stop it from being optimized */
		/*  into oblivion. */
	int libandria4_timesink( int dummy );
	
	
	
		/* Works like C's strstr(), but with arbitrary memory patterns. */
		/* Note that the "needle" will only be searched for on */
		/*  needlegrain-sized alignments: this is to allow arbitrarily sized */
		/*  type searches to be performed. */
		/* The only errors that will be returned are */
			/* LIBANDRIA4_RESULT_FAILURE_DOMAIN and */
			/* LIBANDRIA4_RESULT_FAILURE_EOF. */
		/*  DOMAIN will always mean that the needle size isn't an integer */
		/*  multiple of the needle grain, while EOF will always mean  that */
		/*  the needle wasn't found for some reason (note that null pointers */
		/*  are also included: check explicitly if you care). */
	libandria4_ptrresult libandria4_memmem
	(
		void *haystack_, size_t haysize,
		void *needle_, size_t needlesize, size_t needlegrain
	);
	
		/* Reverses the order of the elements in the memory buffer. "size" */
		/*  is the size of the elements, while "count" is how many of them */
		/*  exist. */
	int libandria4_memreverse( void *base_, size_t count, size_t size );
	
		/* Waits for AT LEAST the provided number of milliseconds. */
	libandria4_error_mayerr libandria4_sleep( uint32_t millisecs );
	
	
	
		/* Of type libandria4_common_putcharfuncp_int, which itself is */
		/*  defined in basictypes.h. */
	int libandria4_null_putchar( void*, char );
	
		/* *_itoputc() seemed a bit too cryptic of a name. */
	int libandria4_i2putc
	(
		void *outdata, libandria4_common_putcharfuncp_int outfunc,
		int i
	);
	
	
	
	/* Convert numeric characters into actual numbers. */
	
	typedef struct libandria4_cb_ctoi_intconv
	{
			/* The converted number. */
		int num;
			/* 1 for "number", -1 for "not a number" */
		int stat;
		
	} libandria4_cb_ctoi_intconv;
	
		/* Simply returns num: for ASCII, this will always be the correct */
		/*  number. If *_ctoi()'s data is given a pointer to a */
		/*  libandria4_cb_ctoi_intconv{}, then it will be initialized. */
			/* Note that num is simply c - '0'. */
	int libandria4_cb_ctoi_feedint_c( void *dest, char c, int num );
		/* Does for libandria4_cb_atoi() the same thing as *_feedint_c() */
		/*  does for *_ctoi(). */
		/* Arguments: */
			/* 1: The void-pointer provided to *_atoi(). If set, then */
			/*  it'll be initialized as if it points to an instance of */
			/*  libandria4_cb_ctoi_intconv{}. */
			/* 2 & 3: The string arguments provided to *_atoi(). */
			/* 4: The last FULLY PROCESSED character from the string: */
			/*  if it's a number but NOT the last character in the */
			/*  string then the number was big enough to risk overflow. */
			/*  It IS NOT possible for the return value of *_atoi() to */
			/*  be altered at this point. */
			/* 5: The calculated number. */
		/* Return: argument number 5, and thus the calculated number. */
	int libandria4_cb_atoi_feedint_s( void *dest,  size_t ig2, char *ig3, size_t off,  int num );
	
		/* Returns a character as foreign for a non-numeric character, an */
		/*  integer as match for a numeric character, and an error... */
		/*  never, unless something like memory corruption has happened. */
		/*  Uses libandria4_cb_ctoi(). */
	libandria4_commonlib_charchar_eithfork libandria4_ctoi( char c );
		/* The function pointer IS required, it's return will be used as a */
		/*  match-return. Only works for ASCII-like number encodings. */
	libandria4_commonlib_charchar_eithfork libandria4_cb_ctoi( char c,  void *data, int (*func)( void*, char, int ) );
	
		/* Unlike *_ctoi(), this DOES handle negation. */
		/* Returns: */
			/* a below-bounds error if a null string (length and/or */
			/*  characters) was provided; */
			/* an indirect-domain error if NO characters were valid for */
			/*  a number (a negation sign DOES count as a valid */
			/*  character for this purpose); */
			/* a string-offset foreign pointing to a numeric character */
			/*  that MIGHT have caused an integer overflow, and was */
			/*  thus left unprocessed, or; */
			/* an int match (modified by the OPTIONAL function-pointer */
			/*  if provided) if everything went perfectly. */
		/* Note that IF the function-pointer is provided, then unless a */
		/*  below-bounds error is returned it WILL be called, and it's */
		/*  return will be used for any successful return from this */
		/*  function. */
		/* The first and second arguments define the string: a null */
		/*  string will return an error. A minus as the first character */
		/*  is fine, but ALL other characters must be decimal digits. */
		/* The third argument will be used as the first argument to the */
		/*  function pointer. */
		/* The fourth argument is expected to be either null, or a */
		/*  pointer to libandria4_cb_atoi_feedint_s(), but there SHOULD */
		/*  be enough documentation in this header to make a custom one. */
	libandria4_commonlib_intint_eithfork libandria4_cb_atoi
	(
		size_t len,
		char *c,
		
		void *data,
		int (*func)( void*,  size_t, char*, size_t,  int )
	);
	libandria4_commonlib_intint_eithfork libandria4_atoi( size_t len, char *c );
		/* TODO : Create versions for Pascal-strings. */
	
	
	
	
	
	/* The common macros for forking-type monad sets. */
	
	#define LIBANDRIA4_COMMONLIB_FORKINGTYPE_LEFT(  prefix, type, val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( prefix ## fork, type, val )
	#define LIBANDRIA4_COMMONLIB_FORKINGTYPE_RIGHT( prefix, type, val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( prefix ## fork, type, val )
	
	#define LIBANDRIA4_COMMONLIB_EITHERFORK_SUCCESS( prefix, type, forkval ) \
			LIBANDRIA4_MONAD_EITHER_BUILDLEFT( prefix ## eithfork, prefix ## fork, forkval )
		#define LIBANDRIA4_COMMONLIB_EITHERFORK_LEFT( prefix, type, val ) \
			LIBANDRIA4_COMMONLIB_EITHERFORK_SUCCESS( prefix, type, \
				LIBANDRIA4_MONAD_EITHER_BUILDLEFT( prefix ## fork, type, val ) )
		#define LIBANDRIA4_COMMONLIB_EITHERFORK_RIGHT( prefix, type, val ) \
			LIBANDRIA4_COMMONLIB_EITHERFORK_SUCCESS( prefix, type, \
				LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( prefix ## fork, type, val ) )
	#define LIBANDRIA4_COMMONLIB_EITHERFORK_ERROR( prefix, type, errval ) \
			LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( prefix ## eithfork, libandria4_commonlib_err, errval )
	
	#define LIBANDRIA4_COMMONLIB_FORKINGTYPE_BODYMATCH( var,  onmatch, onforeign ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var,  onmatch, onforeign )
	#define LIBANDRIA4_COMMONLIB_FORKINGTYPE_EXPRMATCH( var,  onmatch, onforeign ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var,  onmatch, onforeign )
	#define LIBANDRIA4_COMMONLIB_EITHERFORK_BODYMATCH( var, type,  onmatch, onforeign, onerr ) \
		{ \
			(type) dummy; \
			int libandria4_commonlib_eithtest = \
				LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
					LIBANDRIA4_OP_ISVAL1, LIBANDRIA4_OP_ISVAL0 ); \
			if( libandria4_commonlib_eithtest ) { \
				libandria4_commonlib_eithtest = \
					LIBANDRIA4_COMMONLIB_FORKINGTYPE_BODYMATCH( \
						LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
							LIBANDRIA4_OP_UNARYIDENTITY, LIBANDRIA4_OP_ISVARdummy ), \
						onmatch, onforeign ) } \
			else { LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
				LIBANDRIA4_OP_ISVAL0, onerr ) } }
		/* The pointer cast, and the "direct" invocation of onerr, are to */
		/*  compensate from the combination of expression-mode and nested */
		/*  eithers. In a richer pair of languages, we'd be defining helper */
		/*  functions inline or something. */
	#define LIBANDRIA4_COMMONLIB_EITHERFORK_EXPRMATCH( var, type,  onmatch, onforeign, onerr ) \
		( ( LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
				LIBANDRIA4_OP_ISVAL1, LIBANDRIA4_OP_ISVAL0 ) ) ? \
				( LIBANDRIA4_MONAD_EITHER_EXPRMATCH( \
					*( ((type)*)LIBANDRIA4_MONAD_EITHER_EXPRMATCH( \
						var, LIBANDRIA4_OP_UNARYTOPTR, LIBANDRIA4_OP_ISVAL0 ) ), \
					onmatch, onforeign ) ) : \
			( onerr( (libandria4_commonlib_err)( LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
				LIBANDRIA4_OP_ISVAL0, LIBANDRIA4_OP_UNARYIDENTITY ) ) ) ) )
	#define LIBANDRIA4_COMMONLIB_EITHERFORK_TO_MAYERR( var ) \
		( LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
				LIBANDRIA4_COMMONLIB_MAYERR_FORCE_NOERR, \
				LIBANDRIA4_COMMONLIB_MAYERR_JUSTERR ) )
	
	#define LIBANDRIA4_COMMONLIB_EITHERFORK_RETMATCH( prefix, type, val ) \
		return( LIBANDRIA4_COMMONLIB_EITHERFORK_LEFT( prefix, type, val ) )
	#define LIBANDRIA4_COMMONLIB_EITHERFORK_RETFOREIGN( prefix, type, val ) \
		return( LIBANDRIA4_COMMONLIB_EITHERFORK_RIGHT( prefix, type, val ) )
	#define LIBANDRIA4_COMMONLIB_EITHERFORK_RETERROR( prefix, type, errval ) \
		return( LIBANDRIA4_COMMONLIB_EITHERFORK_ERROR( prefix, type, errval ) )
	
	
	
	
	
	/* The utility macros for the monad-types defined in this file. */
	
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_JUSTBYTE( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_commonlib_maybyte, libandria4_commonlib_byte, val )
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_FORCE_NOBYTE( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonlib_maybyte, libandria4_commonlib_byte )
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_NOBYTE() \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonlib_maybyte, libandria4_commonlib_byte )
	
		/* *BODY* takes statements, *EXPR* takes expressions, *REDUCE */
		/*  extracts values. */
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_BODYMATCH( var,  onval, onnothing ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onval, onnothing )
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_EXPRMATCH( var,  onval, onnothing ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onval, onnothing )
		/* "onsucc" always produces a "nothing" monad, so onerr should do */
		/*  something compatible. Basically only useful for translating */
		/*  between "maybe" types. */
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_EXPRCHAIN( var,  name, type, onval ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( name, type,  var,  onval )
			/* alt gets subbed in for "nothing". */
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_REDUCE( var,  alttype, altval ) \
		LIBANDRIA4_MONAD_MAYBE_REDUCE( var,  alttype, altval )
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_NULLSUCC( var,  onval ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onval, LIBANDRIA4_NOACTION )
	
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_RETTBYTE( val ) \
		return( LIBANDRIA4_COMMONLIB_MAYBYTE_JUSTBYTE( val ) );
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_FORCE_RETNOBYTE( ... ) \
		return( LIBANDRIA4_COMMONLIB_MAYBYTE_NOBYTE() );
	#define LIBANDRIA4_COMMONLIB_MAYBYTE_RETNOBYTE() \
		return( LIBANDRIA4_COMMONLIB_MAYBYTE_NOBYTE() );
	
	
	
	#define LIBANDRIA4_COMMONLIB_MAYERR_JUSTERR( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_commonlib_mayerr, libandria4_commonlib_err, val )
	#define LIBANDRIA4_COMMONLIB_MAYERR_FORCE_NOERR( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonlib_mayerr, libandria4_commonlib_err )
	#define LIBANDRIA4_COMMONLIB_MAYERR_NOERR() \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_commonlib_mayerr, libandria4_commonlib_err )
	
		/* *BODY* takes statements, *EXPR* takes expressions, *REDUCE */
		/*  extracts values. */
	#define LIBANDRIA4_COMMONLIB_MAYERR_BODYMATCH( var,  onerr, onnothing ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onerr, onnothing )
	#define LIBANDRIA4_COMMONLIB_MAYERR_EXPRMATCH( var,  onerr, onnothing ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onerr, onnothing )
		/* "onsucc" always produces a "nothing" monad, so onerr should do */
		/*  something compatible. Basically only useful for translating */
		/*  between "maybe" types. */
	#define LIBANDRIA4_COMMONLIB_MAYERR_EXPRCHAIN( var,  name, type, onerr ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( name, type,  var,  onerr )
			/* alt gets subbed in for "nothing". */
	#define LIBANDRIA4_COMMONLIB_MAYERR_REDUCE( var,  alttype, altval ) \
		LIBANDRIA4_MONAD_MAYBE_REDUCE( var,  alttype, altval )
	#define LIBANDRIA4_COMMONLIB_MAYERR_NULLSUCC( var,  onerr ) \
		LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onerr, LIBANDRIA4_NOACTION )
	
	
	
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_BYTE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonlib_eithbyte, libandria4_commonlib_byte, val )
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonlib_eithbyte, libandria4_commonlib_err, val )
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_ERR_1() LIBANDRIA4_COMMONLIB_EITHBYTE_ERR( 1 )
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_ERR_2() LIBANDRIA4_COMMONLIB_EITHBYTE_ERR( 2 )
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_ERR_3() LIBANDRIA4_COMMONLIB_EITHBYTE_ERR( 3 )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_BODYMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var,  onsucc, onerr )
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_EXPRMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var,  onsucc, onerr )
			/* onsucc() should usually return a */
				/* LIBANDRIA4_COMMONIO_MAYERR_NOERR() */
			/*  but generally MUST return a libandria4_commonio_mayerr. */
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_EXPRCHAIN( var,  onsucc ) \
		LIBANDRIA4_MONAD_EITHER_EXPRCHAIN( \
			var,  onsucc, LIBANDRIA4_COMMONLIB_MAYERR_JUSTERR )
			/* A shallow wrapper around *_EXPRMATCH. */
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_REDUCE( var,  reduce_a, reduce_b ) \
		LIBANDRIA4_MONAD_EITHER_REDUCE( var,  reduce_a, reduce_b )
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_TO_MAYERR( var ) \
		LIBANDRIA4_COMMONIO_EITHBYTE_REDUCE( \
			var, \
				LIBANDRIA4_COMMONLIB_MAYERR_FORCE_NOERR, \
				LIBANDRIA4_COMMONLIB_MAYERR_JUSTERR )
	
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_RETBYTE( val ) \
		return( LIBANDRIA4_COMMONLIB_EITHBYTE_BYTE( val ) )
	#define LIBANDRIA4_COMMONLIB_EITHBYTE_RETERR( val ) \
		return( LIBANDRIA4_COMMONLIB_EITHBYTE_ERR( val ) )
	
	
	
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_VOIDP( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonlib_eithvoidp, void*, val )
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonlib_eithvoidp, libandria4_commonlib_err, val )
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR_1() LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR( 1 )
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR_2() LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR( 2 )
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR_3() LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR( 3 )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_BODYMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var,  onsucc, onerr )
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_EXPRMATCH( var,  onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var,  onsucc, onerr )
			/* onsucc() should usually return a */
				/* LIBANDRIA4_COMMONIO_MAYERR_NOERR() */
			/*  but generally MUST return a libandria4_commonio_mayerr. */
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_EXPRCHAIN( var,  onsucc ) \
		LIBANDRIA4_MONAD_EITHER_EXPRCHAIN( \
			var,  onsucc, LIBANDRIA4_COMMONLIB_MAYERR_JUSTERR )
			/* A shallow wrapper around *_EXPRMATCH. */
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_REDUCE( var,  reduce_a, reduce_b ) \
		LIBANDRIA4_MONAD_EITHER_REDUCE( var,  reduce_a, reduce_b )
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_TO_MAYERR( var ) \
		LIBANDRIA4_COMMONIO_EITHBYTE_REDUCE( \
			var, \
				LIBANDRIA4_COMMONLIB_MAYERR_FORCE_NOERR, \
				LIBANDRIA4_COMMONLIB_MAYERR_JUSTERR )
	
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_RETBYTE( val ) \
		return( LIBANDRIA4_COMMONLIB_EITHVOIDP_BYTE( val ) )
	#define LIBANDRIA4_COMMONLIB_EITHVOIDP_RETERR( val ) \
		return( LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR( val ) )
	
	
	
	/* For libandria4_commonlib_charchar_fork{} and */
	/*  libandria4_commonlib_charchar_eithfork{}. */
	
	#define LIBANDRIA4_COMMONLIB_CHARCHAR_MATCH(  val ) \
		LIBANDRIA4_COMMONLIB_FORKINGTYPE_LEFT( libandria4_commonlib_charchar_, char, val )
	#define LIBANDRIA4_COMMONLIB_CHARCHAR_FOREIGN( val ) \
		LIBANDRIA4_COMMONLIB_FORKINGTYPE_RIGHT( libandria4_commonlib_charchar_, char, val )
	
	#define LIBANDRIA4_COMMONLIB_CHARCHAR_BODYMATCH( var,  onmatch, onforeign ) \
		LIBANDRIA4_COMMONLIB_FORKINGTYPE_BODYMATCH( var,  onmatch, onforeign )
	#define LIBANDRIA4_COMMONLIB_CHARCHAR_EXPRMATCH( var,  onmatch, onforeign ) \
		LIBANDRIA4_COMMONLIB_FORKINGTYPE_EXPRMATCH( var,  onmatch, onforeign )
	
	#define LIBANDRIA4_COMMONLIB_CHARFORK_MATCH( val ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_LEFT( libandria4_commonlib_charchar_, char, val )
	#define LIBANDRIA4_COMMONLIB_CHARFORK_FOREIGN( val ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_RIGHT( libandria4_commonlib_charchar_, char, val )
	#define LIBANDRIA4_COMMONLIB_CHARFORK_ERROR( errval ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_ERROR( libandria4_commonlib_charchar_, char, errval )
	
	#define LIBANDRIA4_COMMONLIB_CHARFORK_BODYMATCH( var,  onmatch, onforeign, onerr ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_BODYMATCH( var, char,  onmatch, onforeign, onerr )
	#define LIBANDRIA4_COMMONLIB_CHARFORK_EXPRMATCH( var,  onmatch, onforeign, onerr ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_EXPRMATCH( var, char,  onmatch, onforeign, onerr )
	#define LIBANDRIA4_COMMONLIB_CHARFORK_TO_MAYERR( var ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_TO_MAYERR( var )
	
	#define LIBANDRIA4_COMMONLIB_CHARFORK_RETMATCH( val ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_RETMATCH( libandria4_commonlib_charchar_, char, val )
	#define LIBANDRIA4_COMMONLIB_CHARFORK_RETFOREIGN( val ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_RETFOREIGN( libandria4_commonlib_charchar_, char, val )
	#define LIBANDRIA4_COMMONLIB_CHARFORK_RETERROR( errval ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_RETERROR( libandria4_commonlib_charchar_, char, errval )
	
	
	
	/* For libandria4_commonlib_intint_fork{} and */
	/*  libandria4_commonlib_intint_eithfork{}. */
	
	#define LIBANDRIA4_COMMONLIB_INTINT_MATCH(  val ) \
		LIBANDRIA4_COMMONLIB_FORKINGTYPE_LEFT( libandria4_commonlib_intint_, int, val )
	#define LIBANDRIA4_COMMONLIB_INTINT_FOREIGN( val ) \
		LIBANDRIA4_COMMONLIB_FORKINGTYPE_RIGHT( libandria4_commonlib_intint_, int, val )
	
	#define LIBANDRIA4_COMMONLIB_INTINT_BODYMATCH( var,  onmatch, onforeign ) \
		LIBANDRIA4_COMMONLIB_FORKINGTYPE_BODYMATCH( var,  onmatch, onforeign )
	#define LIBANDRIA4_COMMONLIB_INTINT_EXPRMATCH( var,  onmatch, onforeign ) \
		LIBANDRIA4_COMMONLIB_FORKINGTYPE_EXPRMATCH( var,  onmatch, onforeign )
	
	#define LIBANDRIA4_COMMONLIB_INTFORK_MATCH( val ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_LEFT( libandria4_commonlib_intint_, int, val )
	#define LIBANDRIA4_COMMONLIB_INTFORK_FOREIGN( val ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_RIGHT( libandria4_commonlib_intint_, int, val )
	#define LIBANDRIA4_COMMONLIB_INTFORK_ERROR( errval ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_ERROR( libandria4_commonlib_intint_, int, errval )
	
	#define LIBANDRIA4_COMMONLIB_INTFORK_BODYMATCH( var,  onmatch, onforeign, onerr ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_BODYMATCH( var, char,  onmatch, onforeign, onerr )
	#define LIBANDRIA4_COMMONLIB_INTFORK_EXPRMATCH( var,  onmatch, onforeign, onerr ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_EXPRMATCH( var, char,  onmatch, onforeign, onerr )
	#define LIBANDRIA4_COMMONLIB_INTFORK_TO_MAYERR( var ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_TO_MAYERR( var )
	
	#define LIBANDRIA4_COMMONLIB_INTFORK_RETMATCH( val ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_RETMATCH( libandria4_commonlib_intint_, int, val )
	#define LIBANDRIA4_COMMONLIB_INTFORK_RETFOREIGN( val ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_RETFOREIGN( libandria4_commonlib_intint_, int, val )
	#define LIBANDRIA4_COMMONLIB_INTFORK_RETERROR( errval ) \
		LIBANDRIA4_COMMONLIB_EITHERFORK_RETERROR( libandria4_commonlib_intint_, int, errval )
	
#endif
/* End libandria4 basic commonlib.h */
