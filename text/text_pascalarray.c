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

#include <string.h>

#include "text_pascalarray.h"
#include "macrotime/simpleops.h"


	/* This currently expects ASCII! */
int libandria4_char_##parr_decincr( libandria4_char_##parr *parr )
{
	if( parr )
	{
		size_t iter = 0;
		
		while
		(
			iter < parr->len &&
			isnum( parr->body[ iter ] ) &&
			parr->body[ iter ] == '9'
		)
		{
			++iter;
		}
		if( !( iter < parr->len && isnum( parr->body[ iter ] ) ) )
		{
			return( -2 );
		}
		
		iter = 0;
		int carry = 1;
		while
		(
			iter < parr->len &&
			isnum( parr->body[ iter ] ) &&
			carry
		)
		{
			parr->body[ iter ] += carry;
			if( parr->body[ iter ] > '9' )
			{
				parr->body[ iter ] -= '0';
				
			} else {
				
				carry = 0;
			}
			
			++iter;
		}
		
		return( 1 );
	}
	
	return( -1 );
}

libandria4_char_##parrres libandria4_char_##parr_strbuild
(
	libandria4_memfuncs_t *mf,
	
	char *str
)
{
	libandria4_char_##parrres ret;
	
	if( str )
	{
		size_t len = strlen( str );
		
			/* Note: allocates an extra entry for the end-marking null. */
		ret = libandria4_char_##pascalarray_build( mf, len + 1 );
		
		#define libandria4_char_parr_strbuild_BUILD_SUCC( var ) \
			libandria4_char_##parr *res = ( var ); \
			res->body[ len ] = '\0'; \
			while( len ) { \
				res->body[ res->len - ( len + 1 ) ] = *str; \
				--len; ++str; }
		
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
			ret,
			
			libandria4_char_parr_strbuild_BUILD_SUCC,
			LIBANDRIA4_NULL_MACRO
		)
	}
	
	return( ret );
}
libandria4_char_##parrres libandria4_char_##parr_strbuildmerge
(
	libandria4_memfuncs_t *mf,
	
	char *a,
	char *b
)
{
	libandria4_char_##parrres ret;
	
	if( a && b )
	{
		size_t
			a_len = strlen( a ),
			b_len = strlen( b );
		
			/* Note: allocates an extra entry for the end-marking null. */
		ret = libandria4_char_##pascalarray_build( mf, a->len + b->len + 1 );
		
		#define libandria4_char_parr_strbuildmerge_BUILD_SUCC( var ) \
			libandria4_char_##parr *res = ( var ); \
			size_t len = 0, targ = 0; \
			while( len < a_len ) { \
				res->body[ targ ] = a[ len ]; \
				++len; ++targ; } \
			len = 0; /* Keep targ as is! Appending strings! */ \
			while( len < b_len ) { \
				res->body[ targ ] = b[ len ]; \
				++len; ++targ; } \
			res->body[ targ ] = '\0';
		
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
			ret,
			
			libandria4_char_parr_strbuildmerge_BUILD_SUCC,
			LIBANDRIA4_NULL_MACRO
		)
	}
	
	return( ret );
}

libandria4_char_##parrres libandria4_char_##parr_merge
(
	libandria4_memfuncs_t *mf,
	
	libandria4_char_##parr *a,
	libandria4_char_##parr *b
)
{
	libandria4_char_parr *ret = (libandria4_char_parr*)0;
	
	if( a && b )
	{
		ret = libandria4_char_##pascalarray_build( mf, a->len + b->len - 1 );
		
		#define libandria4_char_parr_merge_BUILD_SUCC( var ) \
			libandria4_char_##parr *res = ( var ); \
			size_t len = 0, targ = 0; \
			while( len + 1 < a->len ) { \
				res->body[ targ ] = a->body[ len ]; \
				++len; ++targ; } \
			len = 0; \
			while( len + 1 < b->len ) { \
				res->body[ targ ] = b->body[ len ]; \
				++len; ++targ; } \
			res->body[ targ ] = '\0';
		
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
			ret,
			
			libandria4_char_parr_merge_BUILD_SUCC,
			LIBANDRIA4_NULL_MACRO
		)
	}
	
	return( ret );
}

int libandria4_ascii_isnewline( char c )
{
		/* Detects form-feed, vertical-tab, true new-line, and */
		/*  carriage-return. */
	return( ( c >= 0x0A && c < 0x0D ) ? 1 : 0 );
}
