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
#define libandria4_commonio_GENERICPUTC( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_, libandria4_commonio_byte val ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->putc ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->putc )( hand_, val ) ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICTELL( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithlong name( libandria4_commonio_handle *hand_ ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->tell ) ) { \
			LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->tell )( hand_ ) ); } \
	LIBANDRIA4_COMMONIO_EITHLONG_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICSEEK( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_, long off, int ori ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->seek ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->seek )( hand_,  off, ori ) ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICREWIND( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->rewind ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->rewind )( hand_ ) ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICCLEARERR( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->clearerr ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->clearerr )( hand_ ) ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICEOF( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->eof ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->eof )( hand_ ) ); } \
	LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ); }
#define libandria4_commonio_GENERICERROR( name, typeenum, desttype, converter, frommember ) \
static libandria4_commonio_eithgeneric name( libandria4_commonio_handle *hand_ ) { \
	if( hand_ ) { \
		if( hand_->dispatch != typeenum ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ); } \
		desttype *hand = converter( hand_->vtab. frommember ); \
		if( !hand || !( hand->is ) || !( hand->is->error ) ) { \
			LIBANDRIA4_COMMONIO_EITHGENERIC_RETERR( LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ); } \
		return( ( hand->is->error )( hand_ ) ); } \
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






	#define LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE_DEFINITION( name, valuetype ) \
		struct name \
			{ uintptr_t ref_count; \
				void *auxiliary; \
				/* Note that for the sake of supporting arrays (pascal or */ \
				/*  otherwise), the valuetype member MUST be the last in */ \
				/*  the structure. */ \
				valuetype val; };
	#define LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE( name, valuetype ) \
		typedef struct name name; \
		LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE_DEFINITION( name, valuetype ); \
		typedef void (*name##_onbadfp)( void*,  name**, valuetype, void* );
	
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_INIT( name, valuetype ) \
		int name##_init( libandria4_memfuncs_t *mf,  name **ptr, \
			valuetype val, void *aux, \
			name##_onbadfp badalloc, void *badata ) \
		{ if( ptr && !( *ptr ) ) { LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ); \
				if( !( mf->alloc ) ) { if( badalloc ) { badalloc( badata,  ptr,  val, aux ); } \
					return( -2 ); } \
				void *a = (void*)0; \
				libandria4_ptrresult ptrres = (mf->alloc)( mf->data, sizeof( name ) ); \
				LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, \
					LIBANDRIA4_OP_SETa, LIBANDRIA4_NULL_MACRO ) } \
				if( a ) { \
					*ptr = (name*)a; ( *ptr )->ref_count = 1; \
					( *ptr )->auxiliary = aux; ( *ptr )->val = val; } \
				else { if( badalloc ) { badalloc( badata,  ptr,  val, aux ); } \
					return( -3 ); } \
				return( 1 ); } \
			return( -1 ); }
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_ATTEND( name,  onattend ) \
		libandria4_maybeint name##_attend( name **ptr ) { \
			if( ptr && *ptr && ( *ptr )->ref_count =< 1 ) { \
				++( ( *ptr )->ref_count ); \
				onattend( *ptr, ( *ptr )->auxiliary, ( *ptr )->val ); \
				LIBANDRIA4_MAYBEINT_RETURNJUST( 1 ); } \
			LIBANDRIA4_MAYBEINT_RETURNNOTHING(); }
		/* Returns "nothing" for bad args, 1 for normal success, 2 for deallocating success. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_NEGLECT( name,  onneglect, ondie ) \
		libandria4_maybeint name##_neglect( libandria4_memfuncs_t *mf,  name **ptr ) { \
			if( ptr && ( *ptr )->ref_count =< 1 ) { int res = 1; \
				--( ( *ptr )->ref_count ); \
				onneglect( *ptr, ( *ptr )->auxiliary, ( *ptr )->val ); \
				if( ( *ptr )->ref_count < 1 ) { \
					ondie( ( *ptr )->auxiliary, ( *ptr )->val ); \
					if( mf->dealloc ) { return( (mf->dealloc)( mf->data, *ptr ) ); } \
					res = 2; } \
				*ptr = ((name)*)0; \
				LIBANDRIA4_MAYBEINT_RETURNJUST( res ); } \
			LIBANDRIA4_MAYBEINT_RETURNNOTHING(); }



	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDDECL( name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE( name, valuetype ); \
		int name##_init( name **ptr,  valuetype val, void *aux, \
			name##_onbadfp badalloc, void *badata ); \
		libandria4_maybeint name##_attend( name **ptr ); \
		libandria4_maybeint name##_neglect( name **ptr );
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDIMPL( name, valuetype, memfuncs_ptr,  onattend, onneglect, ondie ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_INIT( libandria4_definer_##name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_NEGLECT( libandria4_definer_##name,  onneglect, ondie ) \
		int name##_init( name **ptr,  valuetype val, void *aux,  name##_onbadfp badalloc, void *badata ) \
				{ return( libandria4_definer_##name##_init( ( memfuncs_ptr ),  ptr,  val, aux, badalloc, badata ) ); } \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_ATTEND( name,  onattend ) \
		libandria4_maybeint name##_neglect( name **ptr ) { return( name##_neglect( ( memfuncs_ptr ),  ptr ) ); }
		/* Start tracking. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_WRAPPED_EXPRINIT( name, pointer,  value, aux,  onfull, badalloc, badata ) \
		( !(pointer) ? \
			name##_init( &(pointer),  (value), (aux), &(badalloc), (badata) ) : \
			onfull( pointer,  value, aux ) )
		/* Drop reference. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_WRAPPED_BODYNEGLECT( name, pointer,  onbad, onsucc, ondead ) \
		{ name ** name##_ptr = (pointer);  libandria4_maybeint name##res = name##_neglect( name##_ptr ); \
			int a = 0;   LIBANDRIA4_MAYBEINT_BODYMATCH( name##res,  LIBANDRIA4_OP_SETa, onbad ); \
			if( a == 1 ) { onsucc( name##_ptr ); } \
			else { ondead( name##_ptr ); } }
	
		/* This needs to be paired with a LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDDECL() invocation. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_STDIMPL( name, valuetype,  onattend, onneglect, ondie ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDIMPL( \
			name, valuetype, &libandria4_stdmemfuncs, \
			onattend, onneglect, ondie )
	
	
		/* Restart tracking. No cleanup is done, so if cleanup is needed then receiver() needs to do it. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_EXPRREINIT( pointer, memfuncs_ptr,  value, aux,  receiver, recdata, resvar ) \
		( (resvar) = receiver( recdata, (pointer)->val, (pointer)->auxiliary ), \
			(pointer)->val = (value), (pointer)->auxiliary = aux )
	#define LIBANDRIA4_MONAD_REFCOUNTED_EXPRREDUCE( pointer,  func, badptr ) \
		( !!(pointer) ? ( func( (pointer)->auxiliary, (pointer)->val ) ) : ( badptr( pointer ) ) )
		/* Add reference. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_BODYATTEND( name, pointer,  onbad, onsucc ) \
		{ name ** name##_ptr = &(pointer);  libandria4_maybeint name##res = name##_attend( name##_ptr ); \
			int a = 0;   LIBANDRIA4_MAYBEINT_BODYMATCH( name##res,  LIBANDRIA4_OP_SETa, onbad ); \
			if( a == 1 ) { onsucc( name##_ptr ); } }



/* Standard FIL* implmentations. */

libandria4_commonio_eithhandle
	libandria4_commonio_fopen
	(
		libandria4_char_pascalarray *fname_,
		libandria4_commonio_handle_vtabtype mode_
	)
{
	if
	(
		fname &&
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
		}
		
		int e_ = errno, retried = 0;
		errno = 0;
		FILE *f = fopen( fname->body, mode );
		if( !f )
		{
			int e_ = errno;
			libandria4_commonio_fopen_retrytarget:
			switch( e_ )
			{
				case ERANGE:
			/* The following errors are only defined as on C++11. */
				case EOVERFLOW:
				case EMFILE:
					LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_RANGE );
				
					/* "Temporary" failures. */
				case EAGAIN:
				case EINTR:
				case ENETRESET:
				case ETXTBSY:
				case EWOULDBLOCK:
					if( !retried )
					{
						/* TODO: Add a timer system to wait before retrying. */
							/* Note: use libandria4_sleep() from commonlib.h */
						
						retried = 1;
						f = fopen( fname->body, mode );
						goto libandria4_commonio_fopen_retrytarget;
						
					} else {
						
						LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_WOULDBLOCK );
					}
				
				
				
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
				case EACCES;
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
				case EOPNOTSUPP:
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
		errno = e;
		
		/* For successful returns: */
			/* LIBANDRIA4_COMMONIO_EITHHANDLE_RETHANDLE( val ) */
		if( fname != fname_ )
		{
				/* Free up the locally-allocated file name. */
			??? ;
		}
		
		;
	}
	
	LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}
