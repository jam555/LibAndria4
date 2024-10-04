/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2024 Jared A. Maddox

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

#include "pascalstring.h"
#include "simpleops.h"



/* char-type; look further down for NOTES on wchar stuff. */

LIBANDRIA4_DEFINE_PASCALSTRING_STDDEFINE( libandria4_char_, char, LIBANDRIA4_CHAR_STRINGOPS_ );


int libandria4_ascii_isnewline( char c )
{
		/* Detects form-feed, vertical-tab, true new-line, and */
		/*  carriage-return. */
	return( ( c >= 0x0A && c < 0x0D ) ? 1 : 0 );
}
int libandria4_ascii_tonum( char var )
{
	if( !isdigit( *var ) )
	{
		return( -2 );
	}
	
	return( var - '0' );
}



#include <stdint.h>

int libandria4_utf32_isnewline( uint32_t c )
{
	switch( c )
	{
			/* There's also 0x8D Reverse-line-feed, which we don't handle. */
		case 0x0A: /* Line-feed. */
		case 0x0B: /* Vertical-tab. */
		case 0x0C: /* Form-feed. */
		case 0x0D: /* Carriage-return. */
		case 0x85: /* Next-line. */
		case 0x2028: /* Line-separator. */
		case 0x2029: /* Paragraph-separator. */
			return( 1 );
		default:
			break;
	}
	
	return( 0 );
}
int libandria4_utf32_halfnewline( uint32_t c )
{
		/* Partial-line-forward. There's also a backwards version. */
	return( ( c == 0x8B ) ? 1 : 0 );
}
int libandria4_utf32_diversenewline( uint32_t c )
{
	return
	(
		( libandria4_utf32_isnewline( c ) && libandria4_utf32_halfnewline( c ) )
			? 1
			: 0
	);
}



#include <ctype.h>

	/* Only supports newlines. Need to support some other stuff too. */
int libandria4_char_isnewline( char c )
{
	switch( c )
	{
		case '\v': /* Vertical-tab. */
		case '\f': /* Form-feed. */
		case '\r': /* Carriage return. */
		case '\n': /* Newline, usually ASCII line-feed, but beware e.g. MS OSes and old Macs. */
			return( 1 );
		default:
			break;
	}
	
	return( 0 );
}
int libandria4_char_tonum( char var )
{
	int ret = 0;
	
	switch( var )
	{
		case '9':
			ret += 1;
		case '8':
			ret += 1;
		case '7':
			ret += 1;
		case '6':
			ret += 1;
		case '5':
			ret += 1;
		
		case '4':
			ret += 1;
		case '3':
			ret += 1;
		case '2':
			ret += 1;
		case '1':
			ret += 1;
		case '0':
			return( ret );
		default:
			break;
	}
	
	return( -2 );
}
int libandria4_char_stringops_ringincr( char *var )
{
	if( var )
	{
		if( !isdigit( *var ) )
		{
			return( -2 );
		}
		
		int res = libandria4_char_tonum( *var );
		if( !res )
		{
			return( -3 );
		}
		
		res += 1;
		while( res > 9 )
		{
			res -= 10;
		}
		
		*var = "0123456789"[ res ];
		return( 1 );
	}
	
	return( -1 );
}



#include <wchar.h>
#include <wctype.h>

	/* Only supports newlines. Need to support some other stuff too. */
int libandria4_wchar_isnewline( wchar_t c )
{
	switch( c )
	{
		case L'\v': /* Vertical-tab. */
		case L'\f': /* Form-feed. */
		case L'\r': /* Carriage return. */
		case L'\n': /* Newline, usually ASCII line-feed, but beware e.g. MS OSes and old Macs. */
			return( 1 );
		default:
			break;
	}
	
	return( 0 );
}
int libandria4_wchar_tonum( wchar_t var )
{
	int ret = 0;
	
	switch( var )
	{
		case L'9':
			ret += 1;
		case L'8':
			ret += 1;
		case L'7':
			ret += 1;
		case L'6':
			ret += 1;
		case L'5':
			ret += 1;
		
		case L'4':
			ret += 1;
		case L'3':
			ret += 1;
		case L'2':
			ret += 1;
		case L'1':
			ret += 1;
		case L'0':
			return( ret );
		default:
			break;
	}
	
	return( -2 );
}
int libandria4_wchar_stringops_ringincr( wchar_t *var )
{
	if( var )
	{
		if( !iswdigit( *var ) )
		{
			return( -2 );
		}
		
		int res = libandria4_wchar_tonum( *var );
		if( !res )
		{
			return( -3 );
		}
		
		res += 1;
		while( res > 9 )
		{
			res -= 10;
		}
		
		*var = L"0123456789"[ res ];
		return( 1 );
	}
	
	return( -1 );
}




/* wchar_t type SHOULD NOT be directly supported in this file. Instead, */
/*  another file should wrap/translate, because the relevant details vary */
/*  between platforms. */
