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

#include <stddef.h>
#include <errno.h>

#include "streams.h"
#include "streamsinner.h"

#include "simpleops.h"
#include "nulls.h"

#include "commonerrvals.h"



libandria4_commonio_eithgeneric
	libandria4_commonio_genericfunc_reterr
		( libandria4_commonio_handle *ignore )
{
	return
	(
		LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1( dummy )
	);
}
libandria4_commonio_eithlong
	libandria4_commonio_longfunc_reterr
		( libandria4_commonio_handle *ignore )
{
	return
	(
		LIBANDRIA4_COMMONIO_EITHLONG_ERR_1( dummy )
	);
}
libandria4_commonio_eithgeneric
	libandria4_commonio_seekfunc_reterr
		( libandria4_commonio_handle *ignore1, long ignore2, int ignore3 )
{
	return
	(
		LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1( dummy )
	);
}
libandria4_commonio_eithbyte
	libandria4_commonio_fetchbyte_reterr
		( libandria4_commonio_handle *ignore )
{
	return
	(
		LIBANDRIA4_COMMONIO_EITHBYTE_ERR_1( dummy )
	);
}
libandria4_commonio_eithgeneric
	libandria4_commonio_storebyte_reterr
		( libandria4_commonio_handle *ignore, libandria4_commonio_byte ignore2 )
{
	return
	(
		LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1( dummy )
	);
}
libandria4_commonio_eithgeneric
	libandria4_commonio_strfunc_reterr
		( libandria4_commonio_handle *ignore1, libandria4_commonio_byte *ignore2, size_t ignore3 )
{
	return
	(
		LIBANDRIA4_COMMONIO_EITHGENERIC_ERR_1( dummy )
	);
}



int libandria4_commonio_handle_verifydispatch( libandria4_commonio_handle *handle )
{
	if( handle )
	{
		switch( handle->dispatch )
		{
			case libandria4_commonio_handle_vtabtype_handle:
				if( !( handle->vtab.hand ) )
				{
					return( -5 );
				}
				break;
			case libandria4_commonio_handle_vtabtype_istream:
				if( !( handle->vtab.istr ) )
				{
					return( -6 );
				}
				break;
			case libandria4_commonio_handle_vtabtype_ostream:
				if( !( handle->vtab.ostr ) )
				{
					return( -7 );
				}
				break;
			default:
				if( handle->dispatch == libandria4_commonio_handle_vtabtype_invalid )
				{
					return( -2 );
					
				} else if( handle->dispatch == libandria4_commonio_handle_vtabtype__END )
				{
					return( -3 );
					
				} else {
					
					return( -4 );
				}
		}
		
		return( 1 );
	}
	
	return( -1 );
}



#define libandria4_commonio_handle_hasfunc_OMNICAPS \
	libandria4_commonio_handle_vtable_funcenums_flush | \
	libandria4_commonio_handle_vtable_funcenums_close
#define libandria4_commonio_handle_hasfunc_COMMONCAPS \
	libandria4_commonio_handle_hasfunc_OMNICAPS | \
	\
	libandria4_commonio_handle_vtable_funcenums_tell | \
	libandria4_commonio_handle_vtable_funcenums_seek | \
	libandria4_commonio_handle_vtable_funcenums_rewind | \
	\
	libandria4_commonio_handle_vtable_funcenums_clearerr | \
	libandria4_commonio_handle_vtable_funcenums_eof | \
	libandria4_commonio_handle_vtable_funcenums_error
static const libandria4_commonio_handle_vtable_funcenums
	libandria4_commonio_handle_vtable_funcenums_masks[] =
		{
			/* libandria4_commonio_handle_vtabtype_invalid */
				libandria4_commonio_handle_vtable_funcenums__INVALID,
			
			/* libandria4_commonio_handle_vtabtype_handle */
				libandria4_commonio_handle_vtable_funcenums__ALLFLAGS,
			/* libandria4_commonio_handle_vtabtype_istream */
				libandria4_commonio_handle_hasfunc_COMMONCAPS |
					libandria4_commonio_handle_vtable_funcenums_getc |
					libandria4_commonio_handle_vtable_funcenums_gets_s |
					libandria4_commonio_handle_vtable_funcenums_ungetc,
			/* libandria4_commonio_handle_vtabtype_ostream */
				libandria4_commonio_handle_hasfunc_COMMONCAPS |
					libandria4_commonio_handle_vtable_funcenums_putc |
					libandria4_commonio_handle_vtable_funcenums_puts_s,
			/* libandria4_commonio_handle_vtabtype_seekable */
				libandria4_commonio_handle_hasfunc_OMNICAPS |
					libandria4_commonio_handle_vtable_funcenums_tell |
					libandria4_commonio_handle_vtable_funcenums_seek |
					libandria4_commonio_handle_vtable_funcenums_rewind,
			/* libandria4_commonio_handle_vtabtype_errorable */
				libandria4_commonio_handle_hasfunc_OMNICAPS |
					libandria4_commonio_handle_vtable_funcenums_clearerr |
					libandria4_commonio_handle_vtable_funcenums_eof |
					libandria4_commonio_handle_vtable_funcenums_error,
			
			/* libandria4_commonio_handle_vtabtype__END */
				libandria4_commonio_handle_vtable_funcenums__PASTEND
		};

libandria4_commonio_handle_vtable_funcenums libandria4_commonio_handle_detfuncs
(
	libandria4_commonio_handle *hand
)
{
	if( hand )
	{
		if
		(
			hand->dispatch < libandria4_commonio_handle_vtabtype_invalid ||
			hand->dispatch > libandria4_commonio_handle_vtabtype__END
		)
		{
			return( libandria4_commonio_handle_vtable_funcenums__INVALID );
		}
		
		
		libandria4_commonio_handle_vtable_funcenums ret =
			libandria4_commonio_handle_vtable_funcenums_masks[ hand->dispatch ];
		
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_flush ) ?
				( libandria4_commonio_handle_FETCH_flush( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_flush : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_getc ) ?
				( libandria4_commonio_handle_FETCH_getc( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_getc : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_ungetc ) ?
				( libandria4_commonio_handle_FETCH_ungetc( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_ungetc : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_putc ) ?
				( libandria4_commonio_handle_FETCH_putc( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_putc : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_gets_s ) ?
				( libandria4_commonio_handle_FETCH_gets_s( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_gets_s : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_puts_s ) ?
				( libandria4_commonio_handle_FETCH_puts_s( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_puts_s : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_tell ) ?
				( libandria4_commonio_handle_FETCH_tell( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_tell : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_seek ) ?
				( libandria4_commonio_handle_FETCH_seek( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_seek : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_rewind ) ?
				( libandria4_commonio_handle_FETCH_rewind( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_rewind : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_clearerr ) ?
				( libandria4_commonio_handle_FETCH_clearerr( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_clearerr : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_eof ) ?
				( libandria4_commonio_handle_FETCH_eof( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_eof : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_error ) ?
				( libandria4_commonio_handle_FETCH_error( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_error : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		
		ret ^=
			( ret & libandria4_commonio_handle_vtable_funcenums_close ) ?
				( libandria4_commonio_handle_FETCH_close( hand ) ?
					libandria4_commonio_handle_vtable_funcenums_close : 
					libandria4_commonio_handle_vtable_funcenums__NULL ) :
				( libandria4_commonio_handle_vtable_funcenums__NULL );
		
		
		return( ret );
	}
	
	return( libandria4_commonio_handle_vtable_funcenums__INVALID );
}
int libandria4_commonio_handle_hasfunc
(
	libandria4_commonio_handle *hand,
	libandria4_commonio_handle_vtable_funcenums funcs
)
{
	if( hand && funcs >= libandria4_commonio_handle_vtable_funcenums__NULL )
	{
		if( funcs >= libandria4_commonio_handle_vtable_funcenums__PASTEND )
		{
			return( -2 );
		}
		
		
		return
		(
			( libandria4_commonio_handle_detfuncs( hand ) & funcs == funcs ) ?
				1 : 0
		);
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
		if( libandria4_commonio_handle_verifydispatch( io ) )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
		}
		if
		(
			!libandria4_commonio_handle_hasfunc
			(
				io,
				libandria4_commonio_handle_vtable_funcenums_putc
			)
		)
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
		}
		if( !str && len )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_SIZEMISMATCH );
		}
		
		libandria4_commonio_eithgeneric res;
		size_t iter = 0;
		int a;
		while( iter < len )
		{
			res = libandria4_commonio_handle_PUTC( io,  str[ iter ] );
			LIBANDRIA4_COMMONIO_EITHGENERIC_BODYMATCH(
				res,
					LIBANDRIA4_NULL_MACRO,
					LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR
				);
			
			++iter;
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( iter );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}
libandria4_commonio_eithgeneric libandria4_commonio_common_gets_s
(
	libandria4_commonio_handle *io,
		libandria4_commonio_byte *dest, size_t len
)
{
	if( io )
	{
		if( libandria4_commonio_handle_verifydispatch( io ) )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
		}
		if
		(
			!libandria4_commonio_handle_hasfunc
			(
				io,
				libandria4_commonio_handle_vtable_funcenums_getc
			)
		)
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
		}
		if( !dest && len )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_SIZEMISMATCH );
		}
						/* TODO: delete this! libandria4_commonio_eithbyte
							(*libandria4_commonio_fetchbyte)
								( libandria4_commonio_handle* ); */
		
		libandria4_commonio_eithbyte res;
		size_t iter = 0;
		libandria4_commonio_byte a;
		libandria4_commonio_err b = LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED;
		while( iter < len && b == LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED )
		{
			res = libandria4_commonio_handle_GETC( io );
#define libandria4_commonio_common_gets_s_ONERR( err ) \
	b = (err); if( b != LIBANDRIA4_COMMONIOVALS_EOF ) { LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( b ); }
			LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
				res,
					LIBANDRIA4_OP_SETa,
					libandria4_commonio_common_gets_s_ONERR
				);
			
			dest[ iter ] = a;
			++iter;
		}
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( iter );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}




#define libandria4_commonio_GENERICFLUSH( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_flush ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_FLUSH( hand_ ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICCLOSE( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_close ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_CLOSE( hand_ ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }



libandria4_commonio_GENERICFLUSH(
	libandria4_commonio_istream_ungetwrapper_flush,
		libandria4_commonio_handle_vtabtype_istream,
		libandria4_commonio_istream_ungetwrapper_vtable,
		libandria4_commonio_istream_ungetwrapper_vtable_FROM_ISTREAMVTABPTR,
		istr
);

static libandria4_commonio_eithbyte
	libandria4_commonio_istream_ungetwrapper_getc( libandria4_commonio_handle *hand_ )
{
	if( hand_ )
	{
		if( hand_->dispatch != libandria4_commonio_handle_vtabtype_istream )
		{
			LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH );
		}
		
		libandria4_commonio_istream_ungetwrapper_vtable *hand =
			libandria4_commonio_istream_ungetwrapper_vtable_FROM_ISTREAMVTABPTR( hand_->vtab.istr );
		if( !hand || !( hand->is ) || !( hand->is->getc ) )
		{
			LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
		}
		
		libandria4_commonio_byte a;
#define getc_ONVAL( chara ) \
	a = chara; \
	hand->buffer = LIBANDRIA4_COMMONIO_MAYBYTE_NOBYTE(); \
	LIBANDRIA4_COMMONIO_EITHBYTE_RETBYTE( a );
		LIBANDRIA4_COMMONIO_MAYBYTE_BODYMATCH( hand->buffer,  getc_ONVAL, LIBANDRIA4_NULL_MACRO );
		
		return( ( hand->is->getc )( hand_ ) );
	}
	
	LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}

static libandria4_commonio_eithgeneric
	libandria4_commonio_istream_ungetwrapper_ungetc( libandria4_commonio_handle *hand_, libandria4_commonio_byte val )
{
	if( hand_ )
	{
		if( hand_->dispatch != libandria4_commonio_handle_vtabtype_istream )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH );
		}
		
		libandria4_commonio_istream_ungetwrapper_vtable *hand =
			libandria4_commonio_istream_ungetwrapper_vtable_FROM_ISTREAMVTABPTR( hand_->vtab.istr );
		if( !hand || !( hand->is ) || !( hand->is->ungetc ) )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
		}
		
#define ungetc_EMPTY() \
	hand->buffer = LIBANDRIA4_COMMONIO_MAYBYTE_JUSTBYTE( val ); \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETBYTE( val );
		LIBANDRIA4_COMMONIO_MAYBYTE_BODYMATCH( hand->buffer,  LIBANDRIA4_NULL_MACRO, ungetc_EMPTY );
		
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_OVERFLOW );
	}
	
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS );
}

libandria4_commonio_GENERICCLOSE(
	libandria4_commonio_istream_ungetwrapper_close,
		libandria4_commonio_handle_vtabtype_istream,
		libandria4_commonio_istream_ungetwrapper_vtable,
		libandria4_commonio_istream_ungetwrapper_vtable_FROM_ISTREAMVTABPTR,
		istr
);


int libandria4_commonio_istream_ungetwrapper_init
(
	libandria4_commonio_istream_ungetwrapper_vtable *ugvtab,
	libandria4_commonio_istream_vtable *host
)
{
	if( ugvtab && host )
	{
		ugvtab->here.flush = &libandria4_commonio_istream_ungetwrapper_flush;
		ugvtab->here.getc = &libandria4_commonio_istream_ungetwrapper_getc;
		ugvtab->here.gets_s = &libandria4_commonio_common_gets_s;
		ugvtab->here.ungetc = &libandria4_commonio_istream_ungetwrapper_ungetc;
		ugvtab->here.close = &libandria4_commonio_istream_ungetwrapper_close;
		
		ugvtab->is = host;
			ugvtab->here.seekable = host->seekable;
			ugvtab->here.errable = host->errable;
		
		ugvtab->buffer = LIBANDRIA4_COMMONIO_MAYBYTE_NOBYTE();
		
		return( 1 );
	}
	
	return( -1 );
}



#define libandria4_commonio_GENERICGETC( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithbyte name( libandria4_commonio_handle *hand_ ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_getc ) ) { \
				LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_GETC( hand_ ) ); } \
		LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICUNGETC( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_, libandria4_commonio_byte val ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_ungetc ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_UNGETC( hand_, val ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICPUTC( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_, libandria4_commonio_byte val ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_putc ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_PUTC( hand_, val ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICTELL( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithlong name( libandria4_commonio_handle *hand_ ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_tell ) ) { \
				LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_TELL( hand_ ) ); } \
		LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICSEEK( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_, long off, int ori ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_seek ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_SEEK( hand_,  off, ori ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICREWIND( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_rewind ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_REWIND( hand_ ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICCLEARERR( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_clearerr ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_CLEARERR( hand_ ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICEOF( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_eof ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_EOF( hand_ ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICERROR( name, typeenum, desttype, converter, frommember ) \
	static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
		if( hand_ ) { \
			if( hand_->dispatch != typeenum ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
			if( !hand_ || !libandria4_commonio_handle_hasfunc( hand_, \
					libandria4_commonio_handle_vtable_funcenums_error ) ) { \
				LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
			return( libandria4_commonio_handle_ERROR( hand_ ) ); } \
		LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }



libandria4_commonio_GENERICFLUSH(
	libandria4_commonio_istream_vtable_wrapperflush,
		libandria4_commonio_handle_vtabtype_istream,
		libandria4_commonio_handlevtable_2istream,
		libandria4_commonio_handlevtable_2istream_vtable_FROM_HANDLEVTABPTR,
		istr
);

libandria4_commonio_GENERICGETC(
	libandria4_commonio_istream_vtable_wrappergetc,
		libandria4_commonio_handle_vtabtype_istream,
		libandria4_commonio_handlevtable_2istream,
		libandria4_commonio_handlevtable_2istream_vtable_FROM_HANDLEVTABPTR,
		istr
);
libandria4_commonio_GENERICUNGETC(
	libandria4_commonio_istream_vtable_wrapperungetc,
		libandria4_commonio_handle_vtabtype_istream,
		libandria4_commonio_handlevtable_2istream,
		libandria4_commonio_handlevtable_2istream_vtable_FROM_HANDLEVTABPTR,
		istr
);

libandria4_commonio_GENERICCLOSE(
	libandria4_commonio_istream_vtable_wrapperclose,
		libandria4_commonio_handle_vtabtype_istream,
		libandria4_commonio_handlevtable_2istream,
		libandria4_commonio_handlevtable_2istream_vtable_FROM_HANDLEVTABPTR,
		istr
);

int libandria4_commonio_handlevtable_2istream_init
(
	libandria4_commonio_handlevtable_2istream *wrapper,
	libandria4_commonio_handle_vtable *host
)
{
	if( wrapper && host )
	{
		wrapper->here.flush = &libandria4_commonio_istream_vtable_wrapperflush;
		wrapper->here.getc = &libandria4_commonio_istream_vtable_wrappergetc;
		wrapper->here.gets_s = &libandria4_commonio_common_gets_s;
		wrapper->here.ungetc = &libandria4_commonio_istream_vtable_wrapperungetc;
		wrapper->here.close = &libandria4_commonio_istream_vtable_wrapperclose;
		
		wrapper->seekable.flush = host->flush;
		wrapper->seekable.tell = host->tell;
		wrapper->seekable.seek = host->seek;
		wrapper->seekable.rewind = host->rewind;
		wrapper->seekable.close = host->close;
		
		wrapper->errable.flush = host->flush;
		wrapper->errable.clearerr = host->clearerr;
		wrapper->errable.eof = host->eof;
		wrapper->errable.error = host->error;
		wrapper->errable.close = host->close;
		
		wrapper->is = host;
		wrapper->here.seekable =
			LIBANDRIA4_COMMONIO_MAYERR_JUSTSEEKABLE(
				&( wrapper->seekable )
			);
		wrapper->here.errable =
			LIBANDRIA4_COMMONIO_MAYERR_JUSTERRABLE(
				&( wrapper->errable )
			);
		
		return( 1 );
	}
	
	return( -1 );
}



libandria4_commonio_GENERICFLUSH(
	libandria4_commonio_ostream_vtable_wrapperflush,
		libandria4_commonio_handle_vtabtype_ostream,
		libandria4_commonio_handlevtable_2ostream,
			/* This is defined in streamsinner.h: re-examine it to figure out */
			/*  WHY it casts between istream and ostream. */
		libandria4_commonio_handlevtable_2ostream_vtable_FROM_HANDLEVTABPTR,
		ostr
);

libandria4_commonio_GENERICPUTC(
	libandria4_commonio_ostream_vtable_wrapperputc,
		libandria4_commonio_handle_vtabtype_ostream,
		libandria4_commonio_handlevtable_2ostream,
		libandria4_commonio_handlevtable_2ostream_vtable_FROM_HANDLEVTABPTR,
		ostr
);

libandria4_commonio_GENERICCLOSE(
	libandria4_commonio_ostream_vtable_wrapperclose,
		libandria4_commonio_handle_vtabtype_ostream,
		libandria4_commonio_handlevtable_2ostream,
		libandria4_commonio_handlevtable_2ostream_vtable_FROM_HANDLEVTABPTR,
		ostr
);

int libandria4_commonio_handlevtable_2ostream_init
(
	libandria4_commonio_handlevtable_2ostream *wrapper,
	libandria4_commonio_handle_vtable *host
)
{
	if( wrapper && host )
	{
		wrapper->here.flush = &libandria4_commonio_ostream_vtable_wrapperflush;
		wrapper->here.putc = &libandria4_commonio_ostream_vtable_wrapperputc;
		wrapper->here.puts_s = &libandria4_commonio_common_puts_s;
		wrapper->here.close = &libandria4_commonio_ostream_vtable_wrapperclose;
		
		wrapper->seekable.flush = host->flush;
		wrapper->seekable.tell = host->tell;
		wrapper->seekable.seek = host->seek;
		wrapper->seekable.rewind = host->rewind;
		wrapper->seekable.close = host->close;
		
		wrapper->errable.flush = host->flush;
		wrapper->errable.clearerr = host->clearerr;
		wrapper->errable.eof = host->eof;
		wrapper->errable.error = host->error;
		wrapper->errable.close = host->close;
		
		wrapper->is = host;
		wrapper->here.seekable =
			LIBANDRIA4_COMMONIO_MAYERR_JUSTSEEKABLE(
				&( wrapper->seekable )
			);
		wrapper->here.errable =
			LIBANDRIA4_COMMONIO_MAYERR_JUSTERRABLE(
				&( wrapper->errable )
			);
		
		return( 1 );
	}
	
	return( -1 );
}



libandria4_commonio_GENERICFLUSH(
	libandria4_commonio_seekable_vtable_wrapperflush,
		libandria4_commonio_handle_vtabtype_seekable,
		libandria4_commonio_handlevtable_2seekable,
		libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR,
		seek
);

libandria4_commonio_GENERICTELL(
	libandria4_commonio_seekable_vtable_wrappertell,
		libandria4_commonio_handle_vtabtype_seekable,
		libandria4_commonio_handlevtable_2seekable,
		libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR,
		seek
);
libandria4_commonio_GENERICSEEK(
	libandria4_commonio_seekable_vtable_wrapperseek,
		libandria4_commonio_handle_vtabtype_seekable,
		libandria4_commonio_handlevtable_2seekable,
		libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR,
		seek
);
libandria4_commonio_GENERICREWIND(
	libandria4_commonio_seekable_vtable_wrapperrewind,
		libandria4_commonio_handle_vtabtype_seekable,
		libandria4_commonio_handlevtable_2seekable,
		libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR,
		seek
);

libandria4_commonio_GENERICCLOSE(
	libandria4_commonio_seekable_vtable_wrapperclose,
		libandria4_commonio_handle_vtabtype_seekable,
		libandria4_commonio_handlevtable_2seekable,
		libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR,
		seek
);

int libandria4_commonio_handlevtable_seekable_init
(
	libandria4_commonio_handlevtable_2seekable *wrapper,
	libandria4_commonio_handle_vtable *host
)
{
	if( wrapper && host )
	{
		wrapper->here.flush = &libandria4_commonio_seekable_vtable_wrapperflush;
		wrapper->here.tell = &libandria4_commonio_seekable_vtable_wrappertell;
		wrapper->here.seek = &libandria4_commonio_seekable_vtable_wrapperseek;
		wrapper->here.rewind = &libandria4_commonio_seekable_vtable_wrapperrewind;
		wrapper->here.close = &libandria4_commonio_seekable_vtable_wrapperclose;
		
		wrapper->is = host;
		
		/* ??? Might need more initialization? */
		
		return( 1 );
	}
	
	return( -1 );
}



libandria4_commonio_GENERICFLUSH(
	libandria4_commonio_errorable_vtable_wrapperflush,
		libandria4_commonio_handle_vtabtype_errorable,
		libandria4_commonio_handlevtable_2errorable,
		libandria4_commonio_handlevtable_2errorable_vtable_FROM_HANDLEVTABPTR,
		err
);

libandria4_commonio_GENERICCLEARERR(
	libandria4_commonio_errorable_vtable_wrapperclearerr,
		libandria4_commonio_handle_vtabtype_errorable,
		libandria4_commonio_handlevtable_2errorable,
		libandria4_commonio_handlevtable_2errorable_vtable_FROM_HANDLEVTABPTR,
		err
);
libandria4_commonio_GENERICEOF(
	libandria4_commonio_errorable_vtable_wrappereof,
		libandria4_commonio_handle_vtabtype_errorable,
		libandria4_commonio_handlevtable_2errorable,
		libandria4_commonio_handlevtable_2errorable_vtable_FROM_HANDLEVTABPTR,
		err
);
libandria4_commonio_GENERICERROR(
	libandria4_commonio_errorable_vtable_wrappererror,
		libandria4_commonio_handle_vtabtype_errorable,
		libandria4_commonio_handlevtable_2errorable,
		libandria4_commonio_handlevtable_2errorable_vtable_FROM_HANDLEVTABPTR,
		err
);

libandria4_commonio_GENERICCLOSE(
	libandria4_commonio_errorable_vtable_wrapperclose,
		libandria4_commonio_handle_vtabtype_errorable,
		libandria4_commonio_handlevtable_2errorable,
		libandria4_commonio_handlevtable_2errorable_vtable_FROM_HANDLEVTABPTR,
		err
);

int libandria4_commonio_handlevtable_errorable_init
(
	libandria4_commonio_handlevtable_2errorable *wrapper,
	libandria4_commonio_handle_vtable *host
)
{
	if( wrapper && host )
	{
		wrapper->here.flush = &libandria4_commonio_errorable_vtable_wrapperflush;
		wrapper->here.clearerr = &libandria4_commonio_errorable_vtable_wrapperclearerr;
		wrapper->here.eof = &libandria4_commonio_errorable_vtable_wrappereof;
		wrapper->here.error = &libandria4_commonio_errorable_vtable_wrappererror;
		wrapper->here.close = &libandria4_commonio_errorable_vtable_wrapperclose;
		
		wrapper->is = host;
		
		/* ??? Might need more initialization? */
		
		return( 1 );
	}
	
	return( -1 );
}



/*
	LIBANDRIA4_MONAD_REFPOINTER_COMMONIMPL(
		libandria4_commonio_handle_data,
		libandria4_commonio_handle_opaquedata*,
		libandria4_commonio_handle_opaquedata_ondie );
*/
typedef struct libandria4_commonio_handle_opaquedata libandria4_commonio_handle_opaquedata;
LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDDECL(
	libandria4_commonio_handle_data,
	libandria4_commonio_handle_opaquedata* );
struct libandria4_commonio_handle_opaquedata
{
	uintptr_t key_id;
};
void libandria4_commonio_handle_opaquedata_ondie( void *ign1, libandria4_commonio_handle_opaquedata *ign2 )
{
	/* This is needed for future debug-mode stuff. */
}









/* Standard FILE* implmentations. */

#include <string.h>

libandria4_commonio_eithhandle
	libandria4_commonio_fopen
	(
		libandria4_char_pascalarray *fname_,
		libandria4_commonio_handle_vtabtype mode_
	)
{
	if
	(
		fname_ &&
		mode_ > libandria4_commonio_handle_vtabtype_invalid &&
		mode_ < libandria4_commonio_handle_vtabtype__END
	)
	{
		char *mode, *options[] =
			{
				"r+b", /* libandria4_commonio_handle_vtabtype_handle == 1 */
				"rb", /* libandria4_commonio_handle_vtabtype_istream */
				"r+b", /* libandria4_commonio_handle_vtabtype_ostream */
				"rb", /* libandria4_commonio_handle_vtabtype_seekable */
				"rb" /* libandria4_commonio_handle_vtabtype_errorable */
			};
		switch( mode_ )
		{
			case libandria4_commonio_handle_vtabtype_handle:
			case libandria4_commonio_handle_vtabtype_istream:
			case libandria4_commonio_handle_vtabtype_ostream:
			case libandria4_commonio_handle_vtabtype_seekable:
			case libandria4_commonio_handle_vtabtype_errorable:
				mode = options[ mode_ - 1 ];
				break;
			
			default:
				LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR(
					LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		size_t i = 0;
		while( i < fname_->len && fname_->body[ i ] != '\0' )
			{ ++i; }
		libandria4_char_pascalarray *fname = 0;
		if( i < fname_->len )
		{
			fname = fname_;
			
		} else {
			
			/* Allocate a new p-string with one extra character, copy over fname, set the last character to null. */
			
			libandria4_char_pascalarray_result res =
				libandria4_char_pascalarray_build( fname_->len + 1 );
#define libandria4_commonio_fopen_OPERR_RET( var ) \
	LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( var.val )
			libandria4_char_pascalarray *a;
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
				res,
					LIBANDRIA4_OP_SETa,
					libandria4_commonio_fopen_OPERR_RET );
			void* memcpy( a->body, fname_->body, std::size_t count );
			a->body[ a->len - 1 ] = '\0';
			
			fname = a;
		}
		
		int e_ = errno, retried = 0;
		errno = 0;
		FILE *f = fopen( fname->body, mode );
		libandria4_commonio_fopen_retrytarget:
		if( !f )
		{
			int e2_ = errno;
			switch( e2_ )
			{
				case ERANGE:
			/* The following errors are only defined as on C++11. */
				case EOVERFLOW:
				case EMFILE:
					LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_RANGE );
				
					/* "Temporary" failures. */
				case EINTR:
				case ENETRESET:
				case ETXTBSY:
				case EAGAIN:
#if EAGAIN != EWOULDBLOCK
				case EWOULDBLOCK:
#endif
					if( !retried )
					{
						errno = 0;
						
						/* TODO: Add a timer system to wait before retrying. */
							/* Note: use libandria4_sleep() from commonlib.h */
						
						retried = 1;
						f = fopen( fname->body, mode );
						goto libandria4_commonio_fopen_retrytarget;
						
					} else {
						
						errno = e_;
						LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_WOULDBLOCK );
					}
					
					LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR(
						LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
				
				
				
					/* Uncertain errors. */
				case ECANCELED:
				case ECONNREFUSED:
				case ECONNRESET:
				case EDEADLK:
				case EEXIST:
				case ECONNABORTED:
				case EALREADY:
				case EBUSY:
				case EINPROGRESS:
				case EISCONN:
				case EMLINK:
				case ENETDOWN:
				case ENETUNREACH:
				case ENFILE:
				case ENOBUFS:
				case ENODATA:
				case ENOLCK:
				case ENOMEM:
				case ENOSR:
				case ENOTCONN:
				case ENOTDIR:
				case ENOTEMPTY:
				case ENOTSOCK:
				case EPIPE:
				case EPROTO:
				case ETIME:
				
					/* Simple failures. */
				case EBADF:
				case EACCES:
				case EFAULT:
				case EFBIG:
				case EHOSTUNREACH:
				case EIDRM:
				case EILSEQ:
				case EINVAL:
				case EIO:
				case EISDIR:
				case ELOOP:
				case ENAMETOOLONG:
				case ENODEV:
				case ENOENT:
				case ENOPROTOOPT:
				case ENOSPC:
				case ENOSTR:
				case ENOSYS:
				case ENOTRECOVERABLE:
				case ENOTSUP:
				case ENOTTY:
				case ENXIO:
#if EOPNOTSUPP != ENOTSUP
				case EOPNOTSUPP:
#endif
				case EOWNERDEAD:
				case EPERM:
				case EPROTONOSUPPORT:
				case EPROTOTYPE:
				case EROFS:
				case ESPIPE:
				case ESRCH:
				case ETIMEDOUT:
				case EXDEV:
				
					/* Explicitly unsupported errors. */
				case EBADMSG:
				case EADDRINUSE:
				case EADDRNOTAVAIL:
				case EAFNOSUPPORT:
				case EDESTADDRREQ:
				case EMSGSIZE:
				case ENOEXEC:
				case ENOLINK:
				case ENOMSG:
					/* Everything else. */
				default:
					LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR(
						LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED );
			}
		}
		errno = e_;
		
		if( fname != fname_ )
		{
			/* Free up the locally-allocated file name. */
			
			libandria4_result res = libandria4_char_pascalarray_destroy( fname );
#define libandria4_commonio_fopen_CLERR_RET( var ) \
	fclose( f ); f = 0; \
	LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( var.val )
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
				res,
					LIBANDRIA4_NULL_MACRO,
					libandria4_commonio_fopen_CLERR_RET );
			
			fname = 0;
		}
		
		LIBANDRIA4_COMMONIO_EITHHANDLE_RETHANDLE( f );
	}
	
	LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}
