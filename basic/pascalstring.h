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

#ifndef LIBANDRIA4_BASIC_PASCALSTRING_H
# define LIBANDRIA4_BASIC_PASCALSTRING_H
	
	/* TODO: */
		/* Add wide-character support. UTF-16 MAYBE shouldn't be supported */
		/*  here, but UTF-32 absolutely should. */
		/* wchar_t should be mapped to whatever type is appropriate to the */
		/*  scenario (e.g. MSWindows vs common Linux), and thus probably */
		/*  belongs in a DIFFERENT file-pair. */
	
	#include <ctype.h>
	#include <string.h>
	
	#include "stdmem.h"
	#include "pascalarray.h"
	
	/* "Pascal" strings, in addition to the functionality of "Pascal" arrays */
	/*  which they are an extension to, provide the following pre-defined */
	/*  functionalities: */
		/* LIBANDRIA4_DEFINE_PASCALSTRING_STATICBUILD() */
			/* Does the same as LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(), */
			/*  but for strings. */
		/* LIBANDRIA4_DEFINE_PASCALSTRING_STATICBUILD_NONULL() */
			/* As above, but pretends the trailing character isn't present. */
		/* int head##parr_decimalincr( head##parr *parr ) */
			/* Attempts add 1 to the string by treating it as a text-encoded */
			/*  number */
		/* head##parrres head##parr_strbuild( libandria4_memfuncs_t *mf, */
		/*    type *str ) */
			/* Builds & returns a Pascal-string from a C-string. */
		/* head##parrres head##parr_strbuildmerge( libandria4_memfuncs_t *mf,*/
		/*    type *a, type *b ) */
			/* As above, but with a merge of two strings. */
		/* head##parrres head##parr_merge( libandria4_memfuncs_t *mf, */
		/*    head##parr *a, head##parr *b ) */
			/* As above, but pre-formed Pascal-strings instead of C-strings. */
	
	/* libandria4_char_pascalarray */
		/* Defined via the *STRING_WRAPPEDDECLARE() macro to serve as a */
		/*  standard string type. May be the only Pascal-string type you */
		/*  ever need/want. */
	
	/* LIBANDRIA4_CHAR_STRINGOPS_* */
		/* A set of pre-defined operations used to provide standard */
		/*  operations for libandria4_char_pascalarray: feel free to make */
		/*  custom string types by wrapping whichever of them seem relevant. */
		/*  They are described more in the "operhead" comments below. */
	
	/* int libandria4_ascii_isnewline( char c ); */
		/* A test function to do what it's named for. */
	/* int libandria4_ascii_tonum( char var ); */
		/* Converts a single character into an integer. */
	/* int libandria4_char_stringops_ringincr( char* ); */
		/* Treats a single character as a text-encoded number, and */
		/*  increments it: overflow results in '0'. Used for "operhead" */
		/*  implementation. */
	
	
	
	/* TODO: Add more builder macros for convenience funcs. */
	
	
	
	/* Several of the following macros have an argument named "operhead", which when */
	/*  concatenated with the tokens described below, is expected to produce */
	/*  functions or function macros that match the corresponding description: */
		/* strlen( strptr ) : identical behavior to C's strlen(). */
		/* set( a, b ) : sets the var specified by "a" to the value of "b". */
		/* ringincr( var ) : numeric character, adds '1' to the variable, overflow */
		/*  results in equivalent of '0'. Returns 1 on success. */
		/* isnum( val ) : identical behavior to C's isdigit(). */
		/* isultidigit( val ) : is val the highest digit (e.g. '9' for decimal)? */
		/* zeroval() : equates to 0. */
		/* nullval() : equates to the equivalent of '\0'. */
	
	
	
		/* Note: DOES include the ending null! */
	#define LIBANDRIA4_DEFINE_PASCALSTRING_STATICBUILD( outername, innername, head, type, str ) \
		static struct { head##pascalarray innername; type libandria4_pascalarray_arrmember[ \
			sizeof( (type[]){ str } ) / sizeof( type ) ]; } outername = \
			{ (head##pascalarray){ sizeof( (type[]){ str } ) / sizeof( type ) }, \
				(type[]){ str } };
		/* Note: Does NOT include the null! Sorta. */
	#define LIBANDRIA4_DEFINE_PASCALSTRING_STATICBUILD_NONULL( outername, innername, head, type, str ) \
		static struct { head##pascalarray innername; type libandria4_pascalarray_arrmember[ \
			sizeof( (type[]){ str } ) / sizeof( type ) ]; } outername = \
			{ (head##pascalarray){ ( sizeof( (type[]){ str } ) / sizeof( type ) ) - 1 } , \
				(type[]){ str } };
	
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_DECIMALINCR( head, operhead ) \
		int head##parr_decimalincr( head##parr *parr ) { \
			if( parr ) { \
				int ret = 1; size_t iter = 0; \
				while ( \
					iter < parr->len && \
					operhead##isultidigit( parr->body[ iter ] ) ) \
				{ \
					if( !( operhead##isnum( parr->body[ iter ] ) ) ) { \
						return( -2 ); } \
					++iter; } \
				if( iter >= parr->len ) { \
					ret = 0; \
				} else { \
					operhead##ringincr( parr->body[ iter ] ); } \
				while( iter ) { \
					--iter; \
					operhead##set( parr->body[ iter ], operhead##zeroval() ); } \
				return( ret ); } \
			return( -1 ); }
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILD( head, type, operhead ) \
		head##parrres head##parr_strbuild( libandria4_memfuncs_t *mf, type *str ) { \
			head##parrres ret; \
			if( str ) { \
				size_t len = operhead##strlen( str ); \
					/* Note: allocates an extra entry for the end-marking null. */ \
				ret = head##pascalarray_build( mf, len + 1 ); \
				head##parr *a = 0; \
				LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( ret, \
					LIBANDRIA4_OP_SETa, \
					LIBANDRIA4_NULL_MACRO ) \
				if( a ) { \
					operhead##set( res->body[ len ], operhead##nullval() ); \
					while( len ) { \
						operhead##set( res->body[ res->len - ( len + 1 ) ], *str ); \
						--len; ++str; } } } \
			return( ret ); }
	#define LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILDMERGE( head, type, operhead ) \
		head##parrres head##parr_strbuildmerge( libandria4_memfuncs_t *mf, type *a, type *b ) { \
			head##parrres ret; \
			if( a && b ) { size_t \
					a_len = operhead##strlen( a ), \
					b_len = operhead##strlen( b ); \
					/* Note: allocates an extra entry for the end-marking null. */ \
				ret = head##pascalarray_build( mf, a_len + b_len + 1 ); \
				head##parr *c; \
				LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( ret, \
					LIBANDRIA4_OP_SETc, \
					LIBANDRIA4_NULL_MACRO ) \
				if( c ) { \
					size_t len = 0, targ = 0; \
					while( len < a_len ) { \
						operhead##set( c->body[ targ ], a[ len ] ); \
						++len; ++targ; } \
					len = 0; /* Keep targ as is! Appending strings! */ \
					while( len < b_len ) { \
						operhead##set( c->body[ targ ], b[ len ] ); \
						++len; ++targ; } \
					operhead##set( c->body[ targ ], operhead##nullval() ); } } \
			return( ret ); }
	#define LIBANDRIA4_DEFINE_PASCALSTRING_MERGE( head, type, operhead ) \
		head##parrres head##parr_merge( libandria4_memfuncs_t *mf, head##parr *a, head##parr *b ) { \
			head##parrres ret; \
			if( a && b ) { \
				ret = head##pascalarray_build( mf, a->len + b->len - 1 ); \
				head##parr *c; \
				LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( ret, \
					LIBANDRIA4_OP_SETc, \
					LIBANDRIA4_NULL_MACRO ) \
				if( c ) { \
					size_t len = 0, targ = 0; \
					while( len + 1 < a->len ) { \
						operhead##set( c->body[ targ ], a->body[ len ] ); \
						++len; ++targ; } \
					len = 0; \
					while( len + 1 < b->len ) { \
						operhead##set( c->body[ targ ], b->body[ len ] ); \
						++len; ++targ; } \
					operhead##set( c->body[ targ ], operhead##nullval() ); } } \
			return( ret ); }
	
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_BAREDECLARE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BAREDECLARE( head, type ) \
		typedef head##pascalarray head##parr; \
		typedef head##pascalarray_result head##parrres; \
		int head##parr_decimalincr( head##parr *parr ); \
		head##parrres head##parr_strbuild( libandria4_memfuncs_t *mf, type *str ); \
		head##parrres head##parr_strbuildmerge( libandria4_memfuncs_t *mf, type *a, type *b ); \
		head##parrres head##parr_merge( libandria4_memfuncs_t *mf, head##parr *a, head##parr *b );
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_BAREFINE( head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BAREDEFINE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_DECIMALINCR( head, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILD( head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILDMERGE( head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MERGE( head, type, operhead )
	
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDECLARE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( head, type ) \
		typedef libandria4_char_pascalarray libandria4_char_parr; \
		typedef libandria4_char_pascalarray_result libandria4_char_parrres; \
		int head##parr_decimalincr( head##parr *parr ); \
		head##parrres head##parr_strbuild( type *str ); \
		head##parrres head##parr_strbuildmerge( type *a, type *b ); \
		head##parrres head##parr_merge( head##parr *a, head##parr *b );
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDEFINE( head, type, operhead, memfuncs_ptr ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDEFINE( head, type, memfuncs_ptr ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_DECIMALINCR( head, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILD( libandria4_definer_##head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILDMERGE( libandria4_definer_##head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MERGE( libandria4_definer_##head, type, operhead ) \
		head##parrres head##parr_strbuild( type *str ) \
			{ return( libandria4_definer_##head##parr_strbuild( ( memfuncs_ptr ), str ) ); } \
		head##parrres head##parr_strbuildmerge( type *a, type *b ) \
			{ return( libandria4_definer_##head##parr_strbuildmerge( ( memfuncs_ptr ), a, b ) ); } \
		head##parrres head##parr_merge( head##parr *a, head##parr *b ) \
			{ return( libandria4_definer_##head##parr_merge( ( memfuncs_ptr ), a, b ) ); }
		
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_STDDEFINE( head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDEFINE( head, type, operhead, &libandria4_stdmemfuncs )
	
	
	
	LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDECLARE( libandria4_char_, char );
	
	
	/* These use standard language tools: change that. */
	int libandria4_ascii_isnewline( char c );
	int libandria4_ascii_tonum( char var );
	
	#include <stdint.h>
	int libandria4_utf32_isnewline( uint32_t c );
	int libandria4_utf32_halfnewline( uint32_t c );
	int libandria4_utf32_diversenewline( uint32_t c );
	
	int libandria4_char_isnewline( char c );
	int libandria4_char_tonum( char var );
	int libandria4_char_stringops_ringincr( char* );
	
	#include <wchar.h>
	int libandria4_wchar_isnewline( wchar_t c );
	int libandria4_wchar_tonum( wchar_t var );
	int libandria4_wchar_stringops_ringincr( wchar_t *var );
	
	
	
	/* These macros provide the functionality required for the "operhead" macro arguments. */
	
	/* The common C char set. */
	#include <ctype.h>
	#include <string.h>
	#define LIBANDRIA4_CHAR_STRINGOPS_set( dest, src ) ( ( dest ) = ( src ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_isnum( val ) ( isdigit( val ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_isultidigit( val ) ( ( val ) == '9' ? 1 : 0 )
	#define LIBANDRIA4_CHAR_STRINGOPS_ringincr( var ) ( libandria4_char_stringops_ringincr( &( var ) ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_zeroval() ( 0 )
	#define LIBANDRIA4_CHAR_STRINGOPS_strlen( str ) ( strlen( str ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_nullval() ( '\0' )
	
	/* The common C wide-char set. */
	#include <wctype.h>
	#define LIBANDRIA4_CHAR_STRINGOPS_set( dest, src ) ( ( dest ) = ( src ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_isnum( val ) ( iswdigit( val ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_isultidigit( val ) ( ( val ) == L'9' ? 1 : 0 )
	#define LIBANDRIA4_CHAR_STRINGOPS_ringincr( var ) ( libandria4_wchar_stringops_ringincr( &( var ) ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_zeroval() ( 0 )
		/* The header for wcslen() is wchar.h, and that's ALREADY included. */
	#define LIBANDRIA4_CHAR_STRINGOPS_strlen( str ) ( wcslen( str ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_nullval() ( L'\0' )
	
#endif
/* End libandria4 basic text_pascalstring.h */
