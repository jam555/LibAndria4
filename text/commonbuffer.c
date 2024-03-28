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


#include "../basic/simpleops.h"
#include "../basic/nulls.h"
#include "stdbuffer.h"
#include "commonbuffer.h"



int libandria4_termbuffer_validatecommon
(
	libandria4_termbuffer_generic *term,
	libandria4_termbuffer_common **term2
)
{
	if( term )
	{
		if( term->funcs != &libandria4_termbuffer_common_vtab )
		{
			return( -2 );
		}
		
		libandria4_termbuffer_common *term3 =
			(libandria4_termbuffer_common*)
			(
				(char*)term +
				(
					(char*)( &( ( (libandria4_termbuffer_common*)0 )->common ) ) -
					(char*)( (libandria4_termbuffer_common*)0 )
				)
			);
		if( term2 )
		{
			*term2 = term3;
		}
		if( !( term3->buf ) )
		{
				/* We managed the conversion, but the buffer isn't setup right. */
			return( -4 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}
int libandria4_align_buffercell_accessor
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
int libandria4_align_buffercell_calcoffset
(
	libandria4_termbuffer_common *term,
		uint32_t x, uint32_t y,
		uint32_t *off
)
{
	if( term && off )
	{
		*off = x + ( y * term->start_off ) + term->common.width;
		*off %= term->common.width * term->common.height;
		
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
		if( !libandria4_termbuffer_validatecommon( term_,  &term ) )
		{
			return( -2 );
		}
		if( x >= term_->width || y >= term_->height )
		{
			return( -3 );
		}
		
		libandria4_buffercell_common_accessor *acc;
		if( !libandria4_align_buffercell_accessor( term,  &acc ) )
		{
			return( -4 );
		}
		
		uint32_t elem;
		if( !libandria4_align_buffercell_calcoffset( term,  x, y,  &elem ) )
		{
			return( -5 );
		}
		acc->cells[ elem ] = val;
		
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
		if( !libandria4_termbuffer_validatecommon( term_,  &term ) )
		{
			return( -2 );
		}
		if( x + w >= term_->width || y + h >= term_->height )
		{
			return( -3 );
		}
		
		libandria4_buffercell_common_accessor *acc;
		if( !libandria4_align_buffercell_accessor( term,  &acc ) )
		{
			return( -4 );
		}
		
		size_t h_ = 0, w_;
		uint32_t elem;
		while( h_ < h )
		{
			w_ = 0;
			
			while( w_ < w )
			{
				if( !libandria4_align_buffercell_calcoffset( term,  x + w_, y + h_,  &elem ) )
				{
					return( -5 );
				}
				acc->cells[ elem ] = val[ h_ * w + w_ ];
				
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
		uint32_t new_w, uint32_t new_h,
		libandria4_buffercell_common fill,
		int keep_old
)
{
	if( term_ )
	{
		
		libandria4_termbuffer_common *term;
		if( !libandria4_termbuffer_validatecommon( term_,  &term ) )
		{
			return( -2 );
		}
		
		libandria4_bytebuffer_pascalarray_result res1 =
			libandria4_bytebuffer_pascalarray_build
			(
				term_->mfuncs,
				sizeof( libandria4_buffercell_common ) * new_w * new_h
			);
		
#define libandria4_termbuffer_common_resize_ONERR3( ... ) return( -3 );
		libandria4_bytebuffer_pascalarray *a;
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
			res1,
				LIBANDRIA4_OP_SETa,
				libandria4_termbuffer_common_resize_ONERR3
		)
		
		libandria4_buffercell_common_accessor *src, *dest, val;
		if( !libandria4_align_buffercell_accessor( term,  &src ) )
		{
			return( -4 );
		}
		{
			libandria4_bytebuffer_pascalarray *tmp = a;
			a = term->buf;
			term->buf = tmp;
		}
		if( !libandria4_align_buffercell_accessor( term,  &dest ) )
		{
			return( -5 );
		}
		
		size_t h_ = 0, w_;
		uint32_t elem;
		while( h_ < new_h )
		{
			w_ = 0;
			
			while( w_ < new_w )
			{
				if( keep_old > 0 && h_ < term_->height && w_ < term_->width )
				{
					if( !libandria4_align_buffercell_calcoffset( term,  w_, h_,  &elem ) )
					{
						return( -6 );
					}
					val = src->cells[ elem ];
					
				} else {
					
					val = fill;
				}
				
				dest->cells[ h_ * term_->width + w_ ] = val;
				
				++w_;
			}
			
			++h_;
		}
		
		term_->height = new_h;
		term_->width = new_w;
		
#define libandria4_termbuffer_common_resize_ONERR6( ... ) return( -7 );
		libandria4_result res2 =
			libandria4_bytebuffer_pascalarray_destroy
			(
				term_->mfuncs,
				a
			);
		LIBANDRIA4_MONAD_EITHER_BODYMATCH(
			res2,
				LIBANDRIA4_NULL_MACRO,
				libandria4_termbuffer_common_resize_ONERR6
		)
		
		return( 1 );
	}
	
	return( -1 );
}

int libandria4_termbuffer_common_scroll
(
	libandria4_termbuffer_generic *term_,
		libandria4_termbuffer_directions dir,
		libandria4_buffercell_common fill
		uint32_t x, uint32_t y,
		uint32_t w, uint32_t h
)
{
	if( term_ )
	{
		if
		(
			!(
				dir > libandria4_termbuffer_directions_invalid &&
				dir < libandria4_termbuffer_directions_pastmax
			)
		)
		{
			return( -2 );
		}
		if( !( dir < libandria4_termbuffer_directions_islineend ) )
		{
			return( -3 );
		}
		if( !( w == term_->width && x == 0 && y + h <= term_->height ) )
		{
			return( -4 );
		}
		
		if
		(
			dir == libandria4_termbuffer_directions_right ||
			dir == libandria4_termbuffer_directions_left ||
			h < 1
		)
		{
			return( 0 );
		}
		
		libandria4_termbuffer_common *term;
		if( !libandria4_termbuffer_validatecommon( term_,  &term ) )
		{
			return( -5 );
		}
		libandria4_buffercell_common_accessor *acc;
		if( !libandria4_align_buffercell_accessor( term,  &acc ) )
		{
			return( -6 );
		}
		
		uint32_t elem;
		if( h == term_->height )
		{
			/* Full-screen scrolling. */
			/*  The fast option: just shift around ->start_off instead of moving character cells. */
			
			if( dir == libandria4_termbuffer_directions_up )
			{
				if( term->start_off <= 0 )
				{
					term->start_off == term_->height;
					if( term->start_off )
					{
						term->start_off -= 1;
					}
					
				} else {
					
					--( term->start_off );
				}
				
					/* Set which line we're clearing. */
				h = 0;
				
			} else if( dir == libandria4_termbuffer_directions_down )
			{
				if( term_->height <= term->start_off )
				{
					term->start_off = 0;
					
				} else {
					
					++( term->start_off );
				}
				
					/* Set which line we're clearing. */
				h = term_->height - 1;
			}
			
		} else {
			
			/* Partial-screen scrolling. */
			/* This is the slow option, we have to move a lot of characters. */
			
			int res;
			size_t h_ = 0;
			if( dir == libandria4_termbuffer_directions_up )
			{
				h_ = h;
				while( h_ > 1 )
				{
					--h_;
					
					if( !libandria4_align_buffercell_calcoffset( term,  x, y + ( h_ - 1 ),  &elem ) )
					{
						return( -7 );
					}
					
					res =
						libandria4_termbuffer_common_setblock
						(
							term_,
							x, y + h_,  w, 1,
							
							&( acc->cells[ elem ] )
						);
				}
				
					/* Set which line we're clearing. */
				h = y;
				
			} else if( dir == libandria4_termbuffer_directions_down )
			{
				h_ = 0;
				while( h_ + 1 < h )
				{
					if( !libandria4_align_buffercell_calcoffset( term,  x, y + 1 + h_,  &elem ) )
					{
						return( -8 );
					}
					
					res =
						libandria4_termbuffer_common_setblock
						(
							term_,
							x, y + h_,  w, 1,
							
							&( acc->cells[ elem ] )
						);
					
					++h_;
				}
				
					/* Set which line we're clearing. */
				h = y + ( h - 1 );
			}
		}
		
			/* Clear the newly blank line. */
		uint32_t loop = 0;
		while( loop < term_->width )
		{
			if( !libandria4_align_buffercell_calcoffset( term,  loop, h,  &elem ) )
			{
				return( -9 );
			}
			acc->cells[ elem ] = fill;
			
			++loop;
		}
		
		return( 1 );
	}
	
	return( -1 );
}



#error "TODO: finish populating libandria4_termbuffer_common_vtab{} in commonbuffer.c"
libandria4_termbuffer_generic_vtab libandria4_termbuffer_common_vtab =
	{
		&libandria4_termbuffer_common_setcell,
		&libandria4_termbuffer_common_setblock,

		&libandria4_termbuffer_common_resize
	};
