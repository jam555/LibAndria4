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

#include "bitarray.h"


/*
		Do these belong in this file? Where did the file declarations below
		come from?
*/
LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( libandria4_bitarray_, uint8_t );
LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( libandria4_bitsurface_, libandria4_bitarray_pascalarray* );


/* WARNING: libandria4_bitarray_visit_helper() is used by */
/*  libandria4_bitsurface_visit_helper(), so if you edit one then verify */
/*  against the other. */

static int libandria4_bitarray_calcoffsets( size_t *byte, size_t *bit,  size_t offset )
{
	if( byte && bit )
	{
		*bit = offset % 8;
		*byte = ( offset - *bit ) / 8;
		
		return( 1 );
	}
	
	return( -1 );
}



int libandria4_bitarray_init( libandria4_bitarray *barr,  size_t len )
{
	if( barr )
	{
		barr->width = len;
		return
		(
			libandria4_bitarray_pascalarray_init
			(
				&( barr->arr ),
				( ( len - ( len % 8 ) ) / 8 ) + ( len % 8 ? 1 : 0 )
			)
		);
	}
	
	return( -1 );
}
libandria4_bitarray_result libandria4_bitarray_build( size_t len )
{
	void *a;
	libandria4_failure_uipresult b;
	b.val = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED;
	/* LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( &libandria4_stdmemfuncs ); */
	
	if( len )
	{
		if( !( libandria4_stdmemfuncs.alloc ) )
		{
			return
			(
				LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE(
					LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS
				)
			);
		}
		
		libandria4_ptrresult ptrres =
			(libandria4_stdmemfuncs.alloc)
			(
				libandria4_stdmemfuncs.data,
				
				sizeof( libandria4_bitarray ) + sizeof( uint8_t ) * len
			);
		LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb )
	}
	
	if( a )
	{
		if( libandria4_bitarray_init( (libandria4_bitarray*)a,  len ) < 0 )
		{
			(libandria4_stdmemfuncs.dealloc)
			(
				libandria4_stdmemfuncs.data,
				
				a
			);
			
			return
			(
				LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE(
					LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED
				)
			);
			
		} else {
			
			return( LIBANDRIA4_BITARRAY_RESULT_BUILDSUCCESS( (libandria4_bitarray*)a ) );
		}
		
	} else {
		
		return( LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE( b.val ) );
	}
}
libandria4_bitarray_result libandria4_bitarray_rebuild( libandria4_bitarray *barr,  size_t newlen )
{
	if( barr )
	{
		libandria4_bitarray_result res1 = libandria4_bitarray_build( newlen );
		void *a;
#define libandria4_bitarray_rebuild_FAIL1( err ) \
	return( LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( res1, LIBANDRIA4_OP_SETa, libandria4_bitarray_rebuild_FAIL1 )
		
		size_t iter = 0;
		libandria4_bitarray *a_ = (libandria4_bitarray*)a;
		barr->width = ( ( newlen - ( newlen % 8 ) ) / 8 ) + ( newlen % 8 ? 1 : 0 );
		while( iter < newlen && iter < barr->arr.len )
		{
			a_->arr.body[ iter ] = barr->arr.body[ iter ];
			
			++iter;
		}
		
		return( LIBANDRIA4_BITARRAY_RESULT_BUILDSUCCESS( a_ ) );
	}
	
	return( LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) );
}
libandria4_result libandria4_bitarray_fill2( libandria4_bitarray_pascalarray *parr,  uint8_t *src )
{
	if( parr && src )
	{
		return( libandria4_bitarray_pascalarray_fill( parr,  src ) );
	}
	
	return
	(
		LIBANDRIA4_RESULT_BUILDFAILURE(
			/* (libandria4_failure_result) */ LIBANDRIA4_RESULT_FAILURE_DOMAIN
		)
	);
}
libandria4_result libandria4_bitarray_fill( libandria4_bitarray *barr,  uint8_t *src )
{
	return( libandria4_bitarray_fill2( &( barr->arr ),  src ) );
}
libandria4_bitarray_result libandria4_bitarray_buildNfill( size_t len,  uint8_t *src )
{
	if( src )
	{
		libandria4_bitarray_result res1 = libandria4_bitarray_build( len );
		libandria4_bitarray *a;
#define libandria4_bitarray_buildNfill_FAIL1( err ) \
	return( LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH(
			res1,
				LIBANDRIA4_OP_SETa,
				libandria4_bitarray_buildNfill_FAIL1 );
		
		libandria4_result res2 = libandria4_bitarray_fill( a,  src );
#define libandria4_bitarray_buildNfill_FAIL2( err ) \
	libandria4_result res3 = libandria4_bitarray_destroy( a ); \
	return( LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH(
			res2,
				LIBANDRIA4_NULL_MACRO,
				libandria4_bitarray_buildNfill_FAIL2 );
		
		
		return( res1 );
	}
	
	return( LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) );
}
int libandria4_bitarray_read( libandria4_bitarray *barr, size_t offset )
{
	if( barr )
	{
		if( barr->width <= offset )
		{
			return( -2 );
		}
		
		size_t bitmask, byte;
		if( !libandria4_bitarray_calcoffsets( &byte, &bitmask,  offset ) )
		{
			return( -3 );
		}
		
		return( ( ( barr->arr.body[ byte ] ) & ( 1 << bitmask ) ) > 0 ? 1 : 0 );
	}
	
	return( -1 );
}
int libandria4_bitarray_write( libandria4_bitarray *barr, size_t offset,  int val )
{
	if( barr )
	{
		if( barr->width <= offset )
		{
			return( -2 );
		}
		
		size_t bitmask, byte;
		if( !libandria4_bitarray_calcoffsets( &byte, &bitmask,  offset ) )
		{
			return( -3 );
		}
		
		barr->arr.body[ byte ] =
			( barr->arr.body[ byte ] & ~( 1 << bitmask ) ) |
			( val ? 1 << bitmask : 0 );
		return( 1 );
	}
	
	return( -1 );
}
libandria4_result libandria4_bitarray_destroy( libandria4_bitarray *barr )
{
	return( (libandria4_stdmemfuncs.dealloc)( libandria4_stdmemfuncs.data,  (void*)barr ) );
}
	typedef struct libandria4_bitarray_visit_struct
	{
		void *data;
		void (*visitor)( void*, int* );
		
	} libandria4_bitarray_visit_struct;
		/* Note that this is also used by libandria4_bitsurface_visit_helper(). */
	static void libandria4_bitarray_visit_helper( void *data, uint8_t *value )
	{
		libandria4_bitarray_visit_struct *vis = (libandria4_bitarray_visit_struct*)data;
		
		if( vis && vis->visitor )
		{
				/* Extract the individual bits. */
			int bits[ 8 ] =
				{
					(int)( ( *value & ( 1 << 0 ) ) >> 0 ),
					(int)( ( *value & ( 1 << 1 ) ) >> 1 ),
					(int)( ( *value & ( 1 << 2 ) ) >> 2 ),
					(int)( ( *value & ( 1 << 3 ) ) >> 3 ),
					
					(int)( ( *value & ( 1 << 4 ) ) >> 4 ),
					(int)( ( *value & ( 1 << 5 ) ) >> 5 ),
					(int)( ( *value & ( 1 << 6 ) ) >> 6 ),
					(int)( ( *value & ( 1 << 7 ) ) >> 7 )
				};
			
			
			/* Run the visitations. */
			
			vis->visitor( vis->data, bits + 0 );
			vis->visitor( vis->data, bits + 1 );
			vis->visitor( vis->data, bits + 2 );
			vis->visitor( vis->data, bits + 3 );
			
			vis->visitor( vis->data, bits + 4 );
			vis->visitor( vis->data, bits + 5 );
			vis->visitor( vis->data, bits + 6 );
			vis->visitor( vis->data, bits + 7 );
			
			
				/* Merge the bits back. */
			*value =
				(uint8_t)( bits[ 0 ] ? ( 1 << 0 ) : 0 ) |
				(uint8_t)( bits[ 1 ] ? ( 1 << 1 ) : 0 ) |
				(uint8_t)( bits[ 2 ] ? ( 1 << 2 ) : 0 ) |
				(uint8_t)( bits[ 3 ] ? ( 1 << 3 ) : 0 ) |
				
				(uint8_t)( bits[ 4 ] ? ( 1 << 4 ) : 0 ) |
				(uint8_t)( bits[ 5 ] ? ( 1 << 5 ) : 0 ) |
				(uint8_t)( bits[ 6 ] ? ( 1 << 6 ) : 0 ) |
				(uint8_t)( bits[ 7 ] ? ( 1 << 7 ) : 0 );
		}
	}
void libandria4_bitarray_visit( libandria4_bitarray *barr,  void *data, void (*visitor)( void*, int* ) )
{
	libandria4_bitarray_visit_struct vis = { data, visitor };
	
	libandria4_bitarray_pascalarray_visit( &( barr->arr ),  (void*)&vis, &libandria4_bitarray_visit_helper );
}



/***********************************************************/
/***********************************************************/
/** All of the bitsurface{} stuff below has been updated! **/
/**  Just needs reviews! ***********************************/
/***********************************************************/
/***********************************************************/

int libandria4_bitsurface_init( libandria4_bitsurface *bsurf,  size_t width, size_t height )
{
	if( bsurf )
	{
			/* Mark how many BITS are used: the pascal array's ->len specifies */
			/*  the number of ELEMENTS. */
		bsurf->width = width;
		
		width = ( ( width - ( width % 8 ) ) / 8 ) + ( width % 8 ? 1 : 0 );
		size_t iter = 0;
		void *a;
#define libandria4_bitsurface_init_UNWIND( err ) \
	size_t res = iter; \
	while( res < height ) { \
			bsurf->surf.body[ res ] = (libandria4_bitarray_pascalarray*)0; \
			++res; } \
	while( iter ) { --iter; \
		libandria4_result res2 = libandria4_bitarray_pascalarray_destroy( bsurf->surf.body[ iter ] ); \
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_EXPRMATCH( res2, \
			LIBANDRIA4_OP_SETresTO0, \
			LIBANDRIA4_OP_SETresTO1 ); \
		if( res != 0 ) { return( -3 ); } \
		bsurf->surf.body[ iter ] = (libandria4_bitarray_pascalarray*)0; } \
	return( -2 );
		while( iter < height )
		{
			libandria4_bitarray_pascalarray_result res =
				libandria4_bitarray_pascalarray_build( width );
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
				res,
					LIBANDRIA4_OP_SETa,
					libandria4_bitsurface_init_UNWIND
			);
			
			bsurf->surf.body[ iter ] = (libandria4_bitarray_pascalarray*)a;
			++iter;
		}
		
		return( libandria4_bitsurface_pascalarray_init( &( bsurf->surf ), height ) );
	}
	
	return( -1 );
}
libandria4_bitsurface_result libandria4_bitsurface_build( size_t width, size_t height )
{
	void *a = (void*)0;
	libandria4_failure_uipresult b;
	b.val = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED;
	/* LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( &libandria4_stdmemfuncs ); */
	
	if( height )
	{
		if( !( libandria4_stdmemfuncs.alloc ) )
		{
			return
			(
				LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE(
					LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS
				)
			);
		}
		
		libandria4_ptrresult ptrres =
			(libandria4_stdmemfuncs.alloc)
			(
				libandria4_stdmemfuncs.data,
				
				sizeof( libandria4_bitsurface ) + sizeof( uint8_t ) * height
			);
		LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETb )
	}
	
	if( a )
	{
		if( libandria4_bitsurface_init( (libandria4_bitsurface*)a,  width, height ) < 0 )
		{
			(libandria4_stdmemfuncs.dealloc)
			(
				libandria4_stdmemfuncs.data,
				
				a
			);
			
			return
			(
				LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE(
					LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED
				)
			);
			
		} else {
			
			return( LIBANDRIA4_BITSURFACE_RESULT_BUILDSUCCESS( (libandria4_bitsurface*)a ) );
		}
		
	} else {
		
		return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( b.val ) );
	}
}
libandria4_bitsurface_result libandria4_bitsurface_rebuild( libandria4_bitsurface *bsurf,  size_t width, size_t height )
{
	if( bsurf )
	{
		libandria4_bitsurface_result res1 = libandria4_bitsurface_build( width, height );
		void *a;
#define libandria4_bitsurface_rebuild_FAIL1( err ) \
	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( res1, LIBANDRIA4_OP_SETa, libandria4_bitsurface_rebuild_FAIL1 )
		
		size_t iter = 0;
		libandria4_bitsurface *a_ = (libandria4_bitsurface*)a;
		libandria4_bitarray_pascalarray *arr;
		while( iter < height && iter < bsurf->surf.len )
		{
			arr = a_->surf.body[ iter ];
			a_->surf.body[ iter ] = bsurf->surf.body[ iter ];
			bsurf->surf.body[ iter ] = arr;
			
			++iter;
		}
		
		libandria4_result res2 = libandria4_bitsurface_destroy( bsurf );
#define libandria4_bitsurface_rebuild_FAIL2( err ) \
	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( res1, LIBANDRIA4_NULL_MACRO, libandria4_bitsurface_rebuild_FAIL2 )
		
		width = ( ( width - ( width % 8 ) ) / 8 ) + ( width % 8 ? 1 : 0 );
		iter = 0;
		while( iter < height )
		{
			if( width != a_->surf.len )
			{
				libandria4_bitarray_pascalarray_result res3 =
					libandria4_bitarray_pascalarray_rebuild( a_->surf.body[ iter ], width );
#define libandria4_bitsurface_rebuild_FAIL3( err ) \
	libandria4_bitsurface_destroy( a_ ); \
	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) );
				LIBANDRIA4_MONAD_EITHER_BODYMATCH( res3, LIBANDRIA4_OP_SETa, libandria4_bitsurface_rebuild_FAIL3 )
				
				a_->surf.body[ iter ] = (libandria4_bitarray_pascalarray*)a;
			}
			
			++iter;
		}
		
		return( LIBANDRIA4_BITSURFACE_RESULT_BUILDSUCCESS( a_ ) );
	}
	
	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) );
}
libandria4_result libandria4_bitsurface_fill( libandria4_bitsurface *bsurf,  uint8_t **src )
{
	if( bsurf && src )
	{
		size_t iter = 0;
		
		while( iter < bsurf->surf.len )
		{
#define libandria4_bitsurface_fill_FAIL( err ) \
	LIBANDRIA4_RESULT_RETURNFAILURE( (libandria4_failure_result){ iter } );
			libandria4_result res =
				libandria4_bitarray_fill2( bsurf->surf.body[ iter ],  src[ iter ] );
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( res,  LIBANDRIA4_NULL_MACRO, libandria4_bitsurface_fill_FAIL );
			
			++iter;
		}
		
		LIBANDRIA4_RESULT_RETURNSUCCESS( (libandria4_success_result){ 1 } );
	}
	
	LIBANDRIA4_RESULT_RETURNFAILURE( (libandria4_failure_result){ -1 } );
}
libandria4_bitsurface_result libandria4_bitsurface_buildNfill( size_t width, size_t height,  uint8_t **src )
{
	if( src )
	{
		libandria4_bitsurface_result res1 = libandria4_bitsurface_build( width, height );
		libandria4_bitsurface *a;
#define libandria4_bitsurface_buildNfill_FAIL1( err ) \
	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH(
			res1,
				LIBANDRIA4_OP_SETa,
				libandria4_bitsurface_buildNfill_FAIL1 );
		
		
		libandria4_result res2 = libandria4_bitsurface_fill( a,  src );
#define libandria4_bitsurface_buildNfill_FAIL2( err ) \
	libandria4_result res3 = libandria4_bitsurface_destroy( a ); \
	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH(
			res2,
				LIBANDRIA4_NULL_MACRO,
				libandria4_bitsurface_buildNfill_FAIL2 );
		
		
		return( res1 );
	}
	
	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) );
}
	/* The logic behind this one MUST be verified, it's too easy for it to be wrong. */
libandria4_bitsurface_result libandria4_bitsurface_excerpt
(
	libandria4_bitsurface *src,
	
		/* basal_x and width are measured in BITS, not bytes. */
		/* basal_y and height are measured in "scan lines", or whatever. */
	size_t basal_x, size_t basal_y,
	size_t width, size_t height
)
{
	if( src )
	{
		/* What happens if height or width are 0? Well, for pascal arrays */
		/*  and bit surfaces both, there is simply NO allocation performed, */
		/*  so no array or surface. */
		
		libandria4_bitsurface_result res1 = libandria4_bitsurface_build( width, height );
		libandria4_bitsurface *a;
#define libandria4_bitsurface_excerpt_FAIL1( err ) \
	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) );
		LIBANDRIA4_MONAD_EITHER_BODYMATCH(
			res1,
				LIBANDRIA4_OP_SETa,
				libandria4_bitsurface_excerpt_FAIL1 );
		
		if( a )
		{
			size_t w_ = basal_x, bitoffset = basal_x % 8, w = 0, h = 0;
			w_ -= bitoffset;
			w_ /= 8;
			uint8_t
				highmask,
				lowmask = ~( (uint8_t)( ( ( (uint16_t)1 ) << bitoffset ) - 1 ) ),
				endmask = (uint8_t)( ( ( (uint16_t)1 ) << ( width % 8 ) ) - 1 );
			highmask = 255 ^ lowmask;
			while( h < src->surf.len && h < height )
			{
				a->surf.body[ h ]->body[ w_ + w ] = 0;
				
				/*
					Various lines HAD BEEN structured as:
						src->surf[ basal_y + h ]->body[ w_ + w ] ,
					but src->surf is a scalar instead of an array, so that doesn't work.
					
					TODO: Figure out the correct formulation, this may be tied to some future bug!
						Look for "CHECKPTR" comments!
				*/
				
					/* (libandria4_bitsurface*)->width is in bits, not bytes. */
				while( ( w_ + w + 1 ) * 8 < src->width && w * 8 < width )
				{
					a->surf.body[ h ]->body[ w ] =
						(
								/* CHECKPTR */
							src->surf.body[ basal_y + h ]->body[ w_ + w ] &
							highmask
						) >> bitoffset;
					
						/* Fetch the next piece of the byte, and adjust for */
						/*  its new alignment. */
					a->surf.body[ h ]->body[ w ] |=
						(
							src->surf.body[ basal_y + h ]->body[ w_ + w + 1 ] &
							lowmask
						) << bitoffset;
					
					++w;
				}
				if( ( w_ + w ) * 8 < src->width )
				{
					a->surf.body[ h ]->body[ w ] =
						(
							src->surf.body[ basal_y + h ]->body[ w_ + w ] &
							highmask
						) >> bitoffset;
					
					++w;
				}
				if( endmask > 0 && w )
				{
						/* Mask off anything that we're supposed to NOT duplicate. */
					a->surf.body[ h ]->body[ w - 1 ] &= endmask;
				}
				
				++h;
				w = 0;
			}
		}
		
		return( res1 );
	}

	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) );
}
	/* Simple wrapper is simple. */
libandria4_bitsurface_result libandria4_bitsurface_copy( libandria4_bitsurface *src )
{
	if( src )
	{
		return( libandria4_bitsurface_excerpt( src,  0, 0,  src->width, src->surf.len ) );
	}

	return( LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) );
}
int libandria4_bitsurface_read( libandria4_bitsurface *bsurf, size_t x, size_t y )
{
	if( bsurf )
	{
		if( bsurf->width <= x || bsurf->surf.len <= y )
		{
			return( -2 );
		}
		
		size_t bitmask, byte;
		if( !libandria4_bitarray_calcoffsets( &byte, &bitmask,  x ) )
		{
			return( -3 );
		}
		
		return( ( ( bsurf->surf.body[ y ]->body[ byte ] ) & ( 1 << bitmask ) ) > 0 ? 1 : 0 );
	}
	
	return( -1 );
}
int libandria4_bitsurface_write( libandria4_bitsurface *bsurf, size_t x, size_t y,  int val )
{
	if( bsurf )
	{
		if( bsurf->width <= x || bsurf->surf.len <= y )
		{
			return( -2 );
		}
		
		size_t bitmask, byte;
		if( !libandria4_bitarray_calcoffsets( &byte, &bitmask,  x ) )
		{
			return( -3 );
		}
		
		bsurf->surf.body[ y ]->body[ byte ] =
			( bsurf->surf.body[ y ]->body[ byte ] & ~( 1 << bitmask ) ) |
			( val ? 1 << bitmask : 0 );
		return( 1 );
	}
	
	return( -1 );
}
	void libandria4_bitsurface_destroy_helper( void *ignore, libandria4_bitarray_pascalarray **barr )
	{
		libandria4_result res = libandria4_bitarray_pascalarray_destroy( *barr );
			/* You know what? Use ignore to pass in some error reporting thing. */
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( res, LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO );
		*barr = (libandria4_bitarray_pascalarray*)0;
	}
	/* *_destroy() needs to deallocate the sub-arrays, NOT JUST bsurf itself. */
	/*  It also needs to be tolerant of individual sub-arrays not being present. */
libandria4_result libandria4_bitsurface_destroy( libandria4_bitsurface *bsurf )
{
	libandria4_bitsurface_pascalarray_visit( &( bsurf->surf ),  (void*)0, &libandria4_bitsurface_destroy_helper );
	
	return( (libandria4_stdmemfuncs.dealloc)( libandria4_stdmemfuncs.data,  (void*)bsurf ) );
}
	typedef struct libandria4_bitsurface_visit_struct
	{
		libandria4_bitarray_visit_struct vis;
		void (*hinc)( void* );
		
	} libandria4_bitsurface_visit_struct;
	static void libandria4_bitsurface_visit_helper( void *data, libandria4_bitarray_pascalarray **barr )
	{
		libandria4_bitsurface_visit_struct *vis = (libandria4_bitsurface_visit_struct*)data;
		
		libandria4_bitarray_pascalarray_visit( *barr,  (void*)&( vis->vis ), &libandria4_bitarray_visit_helper );
		vis->hinc( vis->vis.data );
	}
void libandria4_bitsurface_visit( libandria4_bitsurface *bsurf,  void *data, void (*visitor)( void*, int* ), void (*hinc)( void* ) )
{
	libandria4_bitsurface_visit_struct vis = { { data, visitor }, hinc };
	
	libandria4_bitsurface_pascalarray_visit( &( bsurf->surf ),  (void*)&vis, &libandria4_bitsurface_visit_helper );
}
