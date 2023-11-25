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


#include "stdbuffer.h"

typedef struct libandria4_termbuffer_common
{
	libandria4_termbuffer_generic common;
	
		/* Measured in character cells, not in e.g. pixels, or inches. */
	libandria4_bytebuffer_pascalarray *buf;
	
} libandria4_termbuffer_common;

	/* Another convenience type. */
typedef union
{
	uint8_t bytes[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
	libandria4_buffercell_common cells[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
	
} libandria4_buffercell_common_accessor;



static int validate_termbuffer_common( libandria4_termbuffer_common *term_,  libandria4_termbuffer_common **term_2 )
{
	if( term )
	{
		if( term_->funcs != &libandria4_termbuffer_common_vtab )
		{
			return( -2 );
		}
		
		libandria4_termbuffer_common *term =
			(libandria4_termbuffer_common*)
			(
				(char*)term_ +
				(
					(char*)( &( ( (libandria4_termbuffer_common*)0 )->common ) ) -
					(char*)( (libandria4_termbuffer_common*)0 )
				)
			);
		if( term_2 )
		{
			*term_2 = term;
		}
		if( !( term->buf ) )
		{
			return( -4 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}
static int align_buffercell_accessor
(
	libandria4_termbuffer_common *term,
	
	libandria4_buffercell_common_accessor **ret
)
{
	if( term && ret )
	{
			/* Set. */
		*ret = (libandria4_buffercell_common_accessor*)( term->buf.body );
		
			/* Adjust. */
		*ret =
			(libandria4_buffercell_common_accessor*)
			(
				(char*)( *ret ) +
				(
					(char*)( ( *ret )->bytes ) -
					(char*)( *ret )
				)
			);
		
		return( 1 );
	}
	
	return( -1 );
}

int libandria4_termbuffer_common_setcell
(
	libandria4_termbuffer_generic *term_,
		uint32_t x, uint32_t y,
		libandria4_buffercell_common val
)
{
	if( term )
	{
		libandria4_termbuffer_common *term;
		if( !validate_termbuffer_common( term_,  &term ) )
		{
			return( -2 );
		}
		if( x >= term_->width || y >= term_->height )
		{
			return( -3 );
		}
		
		libandria4_buffercell_common_accessor *acc;
		if( !align_buffercell_accessor ( term,  &acc ) )
		{
			return( -4 );
		}
		
		acc->cells[ y * term_->width + x ] = val;
		
		return( 1 );
	}
	
	return( -1 );
}
int libandria4_termbuffer_common_setblock
(
	libandria4_termbuffer_generic *term_,
		uint32_t x, uint32_t y,  uint32_t w, uint32_t h,
		libandria4_buffercell_common *vals
)
{
	if( term_ && vals )
	{
		libandria4_termbuffer_common *term;
		if( !validate_termbuffer_common( term_,  &term ) )
		{
			return( -2 );
		}
		if( x + w >= term_->width || y + h >= term_->height )
		{
			return( -3 );
		}
		
		libandria4_buffercell_common_accessor *acc;
		if( !align_buffercell_accessor ( term,  &acc ) )
		{
			return( -4 );
		}
		
		size_t h_ = 0, w_;
		while( h_ < h )
		{
			w_ = 0;
			
			while( w_ < w )
			{
				acc->cells[ ( h_ + y ) * term_->width + ( w_ + x ) ] =
					val[ h_ * w + w_ ];
				
				++w_;
			}
			
			++h_;
		}
		
		return( 1 );
	}
	
	return( -1 );
}

int libandria4_termbuffer_common_resize
(
	libandria4_termbuffer_generic *term_,
		uint32_t new_w, uint32_t new_h
)
{
	if( term_ )
	{
		libandria4_termbuffer_common *term;
		if( !validate_termbuffer_common( term_,  &term ) )
		{
			return( -2 );
		}
		
		???
			libandria4_bytebuffer_pascalarray *new_arr = ;
		???
		
		return( 1 );
	}
	
	return( -1 );
}
	struct libandria4_termbuffer_generic
	{
		libandria4_termbuffer_generic_vtab *funcs;
		
			/* Measured in character cells, not in e.g. pixels, or inches. */
		uint32_t width, height;
		
		libandria4_memfuncs_t *mfuncs;
		libandria4_commonio_handle *messaging;
	};
	typedef struct libandria4_termbuffer_common
	{
		libandria4_termbuffer_generic common;
		
			/* Measured in character cells, not in e.g. pixels, or inches. */
		libandria4_bytebuffer_pascalarray *buf;
		
	} libandria4_termbuffer_common;



libandria4_termbuffer_generic_vtab libandria4_termbuffer_common_vtab =
	{
		&libandria4_termbuffer_common_setcell,
		&libandria4_termbuffer_common_setblock,

		&libandria4_termbuffer_common_resize
	};
