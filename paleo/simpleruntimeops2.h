/* This header exists to contain stuff that would be nice for simpleruntimeops.h, but which I don't want to work on right now. */

#ifdef ???
# define ???
	
	#include "arraccess.h"
	
	/* Note: libandria4_selectint_*( ... ) needs to return a LIST or an ARRAY, and that makes this more complicated. */
		/* *_select_*() should go from 0 to 17, and also include "all". */
	/* The same note applies to *_omit_*(), except that macro versions only cover 0 - 8 right now. */
	/* The same note applies to *_echo_*() for 0-18 */
	
	int libandria4_packelem_1( size_t shiftstep, int a, ... )
	{
		return( LIBANDRIA4_PACKELEM_1( int, shiftstep,  a,  __VA_ARGS__ ) );
	}
	either libandria4_packelem_2( size_t shiftstep, int a, ... )
	{
		if( sizeof( int ) ??? shiftstep ??? )
		{
			ret_error();
		}
		
		return( LIBANDRIA4_PACKELEM_2( int, shiftstep,  a,  __VA_ARGS__ ) );
	}
	either libandria4_packelem_8( size_t shiftstep, int a, ... )
	{
		if( sizeof( int ) ??? shiftstep ??? )
		{
			ret_error();
		}
		
		return( LIBANDRIA4_PACKELEM_8( int, shiftstep,  a,  __VA_ARGS__ ) );
	}
	
	
	uint8_t libandria4_packelem1_1( uint8_t a, ... )
	{
		return( libandria4_packelem_1( 8, a, __VA_ARGS__ ) );
	}
	
	uint16_t libandria4_packelem2_1( uint8_t a, ... )
	{
		return( libandria4_packelem_1( 16, a, __VA_ARGS__ ) );
	}
	uint16_t libandria4_packelem2_2( uint8_t a, ... )
	{
		return( libandria4_packelem_2( 8, a, __VA_ARGS__ ) );
	}
	
	uint32_t libandria4_packelem4_1( uint8_t a, ... )
	{
		return( libandria4_packelem_1( 32, a, __VA_ARGS__ ) );
	}
	uint32_t libandria4_packelem4_2( uint8_t a, ... )
	{
		return( libandria4_packelem_2( 16, a, __VA_ARGS__ ) );
	}
	uint32_t libandria4_packelem4_3( uint8_t a, ... )
	{
		return( libandria4_packelem_3( 8, a, __VA_ARGS__ ) );
	}
	uint32_t libandria4_packelem4_4( uint8_t a, ... )
	{
		return( libandria4_packelem_4( 8, a, __VA_ARGS__ ) );
	}
	
	uint64_t libandria4_packelem8_1( uint8_t a, ... )
	{
		return( libandria4_packelem_1( 64, a, __VA_ARGS__ ) );
	}
	uint64_t libandria4_packelem8_2( uint8_t a, ... )
	{
		return( libandria4_packelem_2( 32, a, __VA_ARGS__ ) );
	}
	uint64_t libandria4_packelem8_3( uint8_t a, ... )
	{
		return( libandria4_packelem_3( 16, a, __VA_ARGS__ ) );
	}
	uint64_t libandria4_packelem8_4( uint8_t a, ... )
	{
		return( libandria4_packelem_4( 16, a, __VA_ARGS__ ) );
	}
	uint64_t libandria4_packelem8_5( uint8_t a, ... )
	{
		return( libandria4_packelem_5( 8, a, __VA_ARGS__ ) );
	}
	uint64_t libandria4_packelem8_6( uint8_t a, ... )
	{
		return( libandria4_packelem_6( 8, a, __VA_ARGS__ ) );
	}
	uint64_t libandria4_packelem8_7( uint8_t a, ... )
	{
		return( libandria4_packelem_7( 8, a, __VA_ARGS__ ) );
	}
	uint64_t libandria4_packelem8_8( uint8_t a, ... )
	{
		return( libandria4_packelem_8( 8, a, __VA_ARGS__ ) );
	}
	
	
#endif
