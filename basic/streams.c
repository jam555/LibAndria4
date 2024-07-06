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

#include "streams.h"

#include "simpleops.h"
#include "nulls.h"



int libandria4_commonio_handle_verifydispatch( libandria4_commonio_handle *handle )
{
	if( handle )
	{
		switch( handle.dispatch )
		{
			case libandria4_commonio_handle_vtabtype_handle:
				if( !( handle.vtab.hand ) )
				{
					return( -5 );
				}
				break;
			case libandria4_commonio_handle_vtabtype_istream:
				if( !( handle.vtab.istr ) )
				{
					return( -6 );
				}
				break;
			case libandria4_commonio_handle_vtabtype_ostream:
				if( !( handle.vtab.ostr ) )
				{
					return( -7 );
				}
				break;
			default:
				if( handle.dispatch == libandria4_commonio_handle_vtabtype_invalid )
				{
					return( -2 );
					
				} else if( handle.dispatch == libandria4_commonio_handle_vtabtype__END )
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
		if( !( io->putc ) )
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
			res = io->putc( io, str[ iter ] );
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
		if( !( io->getc ) )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
		}
		if( !str && len )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_SIZEMISMATCH );
		}
						libandria4_commonio_eithbyte
							(*libandria4_commonio_fetchbyte)
								( libandria4_commonio_handle* );
		
		libandria4_commonio_eithbyte res;
		size_t iter = 0;
		libandria4_commonio_byte a;
		libandria4_commonio_err b = LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED;
		while( iter < len && b == LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED )
		{
			res = io->getc( io );
#define libandria4_commonio_common_gets_s_ONERR( err ) \
	b = (err); if( b != LIBANDRIA4_COMMONIOVALS_EOF ) { LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( b ); }
			LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
				res,
					LIBANDRIA4_OP_SETa,
					libandria4_commonio_common_gets_s_ONERR
				);
			
			str[ iter ] = a;
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
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->flush ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->flush )( hand_ ) ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICCLOSE( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->close ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->close )( hand_ ) ); } \
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
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH );
		}
		
		libandria4_commonio_istream_ungetwrapper_vtable *hand =
			libandria4_commonio_istream_ungetwrapper_vtable_FROM_ISTREAMVTABPTR( hand_->vtab.istr );
		if( !hand || !( hand->is ) || !( hand->is->getc ) )
		{
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED );
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



???
	/* Are these right? Do we need some other "hand_" value? */
???
#define libandria4_commonio_GENERICGETC( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithbyte name( libandria4_commonio_handle *hand_ ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->getc ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->getc )( hand_ ) ); } \
	LIBANDRIA4_COMMONIO_EITHBYTE_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICUNGETC( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_, libandria4_commonio_byte val ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->ungetc ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->ungetc )( hand_, val ) ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
???



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
		
		wrapper->is = host;
			wrapper->here.seekable = host->seekable;
			wrapper->here.errable = host->errable;
		
		/* ??? Might need more initialization? */
		
		return( 1 );
	}
	
	return( -1 );
}



libandria4_commonio_GENERICFLUSH(
	libandria4_commonio_ostream_vtable_wrapperflush,
		libandria4_commonio_handle_vtabtype_ostream,
		libandria4_commonio_handlevtable_2ostream,
		libandria4_commonio_handlevtable_2ostream_vtable_FROM_HANDLEVTABPTR,
		istr
);

???

libandria4_commonio_GENERICCLOSE(
	libandria4_commonio_ostream_vtable_wrapperclose,
		libandria4_commonio_handle_vtabtype_ostream,
		libandria4_commonio_handlevtable_2ostream,
		libandria4_commonio_handlevtable_2ostream_vtable_FROM_HANDLEVTABPTR,
		istr
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
		wrapper->here.putc = & putc;
		wrapper->here.puts_s = & puts_s;
		wrapper->here.close = &libandria4_commonio_ostream_vtable_wrapperclose;
		
		wrapper->is = host;
			wrapper->here.seekable = host->seekable;
			wrapper->here.errable = host->errable;
		
		/* ??? Might need more initialization? */
		
		return( 1 );
	}
	
	return( -1 );
}



libandria4_commonio_GENERICFLUSH(
	libandria4_commonio_seekable_vtable_wrapperflush,
		libandria4_commonio_handle_vtabtype_seekable,
		libandria4_commonio_handlevtable_2seekable,
		libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR,
		istr
);

???

libandria4_commonio_GENERICCLOSE(
	libandria4_commonio_seekable_vtable_wrapperclose,
		libandria4_commonio_handle_vtabtype_seekable,
		libandria4_commonio_handlevtable_2seekable,
		libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR,
		istr
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
		wrapper->here.tell = & tell;
		wrapper->here.seek = & seek;
		wrapper->here.rewind = & rewind;
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
		istr
);

???

libandria4_commonio_GENERICCLOSE(
	libandria4_commonio_errorable_vtable_wrapperclose,
		libandria4_commonio_handle_vtabtype_errorable,
		libandria4_commonio_handlevtable_2errorable,
		libandria4_commonio_handlevtable_2errorable_vtable_FROM_HANDLEVTABPTR,
		istr
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
		wrapper->here.clearerr = & clearerr;
		wrapper->here.eof = & eof;
		wrapper->here.error = & error;
		wrapper->here.close = &libandria4_commonio_errorable_vtable_wrapperclose;
		
		wrapper->is = host;
		
		/* ??? Might need more initialization? */
		
		return( 1 );
	}
	
	return( -1 );
}
