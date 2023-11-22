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
	#include "simpleops.h
	
	typedef uint8_t libandria4_commonio_byte;
	typedef uint32_t libandria4_commonio_succ;
	typedef uint32_t libandria4_commonio_err;
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_commonio_mayerr,
		libandria4_commonio_err
	);
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithbyte,
			libandria4_commonio_byte,
			libandria4_commonio_err
	);
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithgeneric,
			libandria4_commonio_succ,
			libandria4_commonio_err
	);
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_commonio_eithlong,
			long,
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
	
	
		/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHBYTE_BYTE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithbyte, libandria4_commonio_byte, val )
	#define LIBANDRIA4_COMMONIO_EITHBYTE_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithbyte, libandria4_commonio_err, val )
	
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
	
	
		/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_BYTE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithgeneric, libandria4_commonio_succ, val )
	#define LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithgeneric, libandria4_commonio_err, val )
	
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
	
	
		/* These produce the actual values. */
	#define LIBANDRIA4_COMMONIO_EITHLONG_BYTE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_commonio_eithlong, long, val )
	#define LIBANDRIA4_COMMONIO_EITHLONG_ERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_commonio_eithlong, libandria4_commonio_err, val )
	
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
	
	
	#define libandria4_commonio_int_RETERR1( ... ) return( -1 );
	#define libandria4_commonio_int_RETERR2( ... ) return( -2 );
	#define libandria4_commonio_int_RETERR3( ... ) return( -3 );
	#define libandria4_commonio_int_RETERR4( ... ) return( -4 );
	#define libandria4_commonio_int_RETERR5( ... ) return( -5 );
	
	#define libandria4_commonio_int_RETERR6( ... ) return( -6 );
	#define libandria4_commonio_int_RETERR7( ... ) return( -7 );
	#define libandria4_commonio_int_RETERR8( ... ) return( -8 );
	#define libandria4_commonio_int_RETERR9( ... ) return( -9 );
	
	
	
	typedef struct libandria4_commonio_handle libandria4_commonio_handle;
	
	typedef libandria4_commonio_eithgeneric (*libandria4_commonio_genericfunc)( libandria4_commonio_handle* );
	typedef libandria4_commonio_eithbyte (*libandria4_commonio_fetchbyte)( libandria4_commonio_handle* );
	typedef libandria4_commonio_eithgeneric (*libandria4_commonio_storebyte)( libandria4_commonio_handle*, libandria4_commonio_byte );
	typedef libandria4_commonio_eithlong (*libandria4_commonio_longfunc)( libandria4_commonio_handle* );
	typedef libandria4_commonio_eithgeneric (*libandria4_commonio_seekfunc)( libandria4_commonio_handle*, long, int /* origin */ );
	typedef libandria4_commonio_eithgeneric (*libandria4_commonio_strfunc)( libandria4_commonio_handle*, libandria4_commonio_byte*, size_t );
	
	/* Common implementations, for cases where it's practical. */
	libandria4_commonio_eithgeneric libandria4_commonio_common_puts_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *str, size_t len
	);
	
	/* Convenience functions. */
		/* Tests for close & error handler functionality only. */
	int libandria4_commonio_handle_hasbasics( libandria4_commonio_handle* );
	int libandria4_commonio_recursivewrapper_puts_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *str, size_t len
	);
	int libandria4_commonio_utility_putint( libandria4_commonio_handle *io,  int i );
	
	struct libandria4_commonio_handle
	{
			/* Use a pointer as the ID. */
		uintptr_t typeid;
		
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
	
	
	
	
	
	int libandria4_commonio_handle_hasbasics( libandria4_commonio_handle *io )
	{
		if( io )
		{
			if( !( io->close ) )
			{
				return( -2 );
			}
			
			if( !( io->error ) )
			{
				return( -2 );
			}
			if( !( io->eof ) )
			{
				return( -2 );
			}
			if( !( io->clearerr ) )
			{
				return( -2 );
			}
			
			
			return( 1 );
		}
		
		return( -1 );
	}
	int libandria4_commonio_utility_clearerr( libandria4_commonio_handle *io )
	{
		if( io )
		{
			if( !( io->putc ) )
			{
				return( -2 );
			}
			if( !( io->eof && io->clearerr ) )
			{
				return( -3 );
			}
			
			
			libandria4_commonio_eithgeneric res1;
			libandria4_commonio_mayerr res2;
			
			res1 = io->eof( io );
			res2 = LIBANDRIA4_COMMONIO_EITHGENERIC_TO_MAYERR( res1 );
			LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  libandria4_commonio_int_RETERR4 );
			
			res1 = io->clearerr( io );
			res2 = LIBANDRIA4_COMMONIO_EITHGENERIC_TO_MAYERR( res );
			LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( res2,  libandria4_commonio_int_RETERR5 );
			
			
			return( 1 );
		}
		
		return( -1 );
	}
	int libandria4_commonio_recursivewrapper_puts_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *str, size_t len
	)
	{
		if( io )
		{
			if( !str && len )
			{
				return( -2 );
			}
			if( !( io->puts_s ) )
			{
				return( -3 );
			}
			if( !( io->eof && io->clearerr ) )
			{
				return( -4 );
			}
			
			libandria4_commonio_eithgeneric res1;
			libandria4_commonio_mayerr res2;
			size_t a;
			
			while( len )
			{
				res1 = io->puts_s( io, (libandria4_commonio_byte*)str, len );
				LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH(
					res1,
						LIBANDRIA4_OP_SETa,
						libandria4_commonio_int_RETERR5
				);
				if( a != len && !libandria4_commonio_utility_clearerr( io ) )
				{
					libandria4_commonio_int_RETERR6();
				}
				len -= a;
			}
			
			return( 1 );
		}
		
		return( -1 );
	}
	int libandria4_commonio_utility_putint( libandria4_commonio_handle *io,  int i )
	{
		if( io )
		{
			if( !( io->putc ) )
			{
				return( -2 );
			}
			if( !( io->eof && io->clearerr ) )
			{
				return( -3 );
			}
			
			libandria4_commonio_succ a;
			libandria4_commonio_succ b;
			libandria4_commonio_eithgeneric res1;
#define libandria4_commonio_utility_putint_PUTLOOP( reterr, chara ) \
			b = 1; while( b ) { b = 0; \
				res1 = io->putc( io, (libandria4_commonio_byte)( chara ) ); \
				LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH( res1, \
					LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb ); \
				if( b && !libandria4_commonio_utility_clearerr( io ) ) { ( reterr )(); } }
			
			int tmp = ( i < 0 ? 1 : 0 );
			i *= ( tmp ? -1 : 1 );
			if( tmp )
			{
				libandria4_commonio_utility_putint_PUTLOOP(
					libandria4_commonio_int_RETERR4,
					'-'
				);
			}
			
				/* Make some space so modmask can't overflow. */
			int ilast = i % 10;
			i -= ilast;
			i /= 10;
			
				/* We won't be bothering with leading 0s. */
			int modmask = 10;
			while( i % modmask >= 10 )
			{
				modmask *= 10;
			}
			
			static char *charas = "0123456789";
			
				/* tmp =,-=,/= results in: */
					/* The DECIMAL digit we want gets stored, along with those */
					/*  under it; */
					/* Those under it get removed; and */
					/* It gets pulled down to the 1s column. */
				/*  So, it isolates a digit, and then drops it so it can directly */
				/*  be used as an index. */
			tmp = i % modmask;
			while( modmask > 1 )
			{
				modmask /= 10;
				tmp -= tmp % modmask;
				tmp /= modmask;
				
				libandria4_commonio_utility_putint_PUTLOOP(
					libandria4_commonio_int_RETERR5,
					charas[ tmp ]
				);
			}
			
				/* Now we write out that digit we separated earlier. */
			libandria4_commonio_utility_putint_PUTLOOP(
				libandria4_commonio_int_RETERR6,
				charas[ ilast ]
			);
			
			return( 1 );
		}
		
		return( -1 );
	}
	
	libandria4_commonio_eithgeneric libandria4_commonio_common_puts_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *str, size_t len
	)
	{
		if( io )
		{
			if( !( io->putc ) )
			{
				return( LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 2 ) );
			}
			if( !str && len )
			{
				return( LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 3 ) );
			}
			
			size_t iter = 0;
			while( iter < len )
			{
				??? io->putc( io, str[ iter ] ); ???
				
				++iter;
			}
			
			return( LIBANDRIA4_COMMONIO_EITHGENERIC_BYTE( iter ) );
		}
		
		return( LIBANDRIA4_COMMONIO_EITHGENERIC_ERR( 1 ) );
	}
	
#endif
/* End libandria4 basic commonio.h */
