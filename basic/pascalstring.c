#include "pascalstring.h"
#include "simpleops.h"



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

int libandria4_char_stringops_ringincr( char *var )
{
	if( var )
	{
		if( !isdigit( *var ) )
		{
			return( -2 );
		}
		
		int res = libandria4_ascii_tonum( *var );
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
