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
	
	
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_NOOP( tracked, file_p, vtab_p ) \
		( /* No-op. */ )
	#define LIBANDRIA4_DEFINE_PASCALSTRING_ONDIE( pstr_p, vtab_p ) \
		( ( mf && mf->dealloc ) ? \
			(mf->dealloc)( mf->data, (pstr_p) ) ), \
		(pstr_p) = 0
	
	
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
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILD( head, parrtype, simptype, operhead ) \
		parrtype##parrres head##parr_strbuild( libandria4_memfuncs_t *mf, simptype *str ) { \
			parrtype##parrres ret; \
			if( str ) { \
				size_t len = operhead##strlen( str ); \
					/* Note: allocates an extra entry for the end-marking null. */ \
				ret = head##pascalarray_build( mf, len + 1 ); \
				parrtype##parr *a = 0; \
				LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH( ret, \
					LIBANDRIA4_OP_SETa, \
					LIBANDRIA4_NULL_MACRO ) \
				if( a ) { \
					operhead##set( a->body[ len ], operhead##nullval() ); \
					while( len ) { \
						operhead##set( a->body[ a->len - ( len + 1 ) ], *str ); \
						--len; ++str; } } } \
			return( ret ); }
	#define LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILDMERGE( head, parrtype, simptype, operhead ) \
		parrtype##parrres head##parr_strbuildmerge( libandria4_memfuncs_t *mf, simptype *a, simptype *b ) { \
			parrtype##parrres ret; \
			if( a && b ) { size_t \
					a_len = operhead##strlen( a ), \
					b_len = operhead##strlen( b ); \
					/* Note: allocates an extra entry for the end-marking null. */ \
				ret = head##pascalarray_build( mf, a_len + b_len + 1 ); \
				parrtype##parr *c; \
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
	#define LIBANDRIA4_DEFINE_PASCALSTRING_MERGE( head, parrtype, simptype, operhead ) \
		parrtype##parrres head##parr_merge( libandria4_memfuncs_t *mf, parrtype##parr *a, parrtype##parr *b ) { \
			parrtype##parrres ret; \
			if( a && b ) { \
				ret = head##pascalarray_build( mf, a->len + b->len - 1 ); \
				parrtype##parr *c; \
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
	#define LIBANDRIA4_DEFINE_PASCALSTRING_MUTADEL( head, type, operhead ) \
		int head##mutatingdelete( \
			type *str, size_t strlen, size_t delstart, size_t dellen, type fill ) \
		{ \
			if( str && delstart + dellen <= strlen ) { \
				size_t iter = 0; \
				while( iter < dellen && delstart + dellen + iter < strlen ) { \
					operhead##set( \
						str[ delstart + iter ], str[ delstart + dellen + iter ] ); \
					++iter; } \
				while( delstart + iter < strlen ) { \
					operhead##set( str[ delstart + iter ], fill ); ++iter; } \
				return( 1 ); } \
			return( -1 ); }
	#define LIBANDRIA4_DEFINE_PASCALSTRING_MUTAINS( head, type, operhead ) \
		int head##mutatinginsert( type *str, size_t strlen, \
			size_t inspoint, type insval, type fillval, int force ) \
		{ if( str ) { \
				if( inspoint >= strlen ) { \
					/* Indirect Domain error. */ return( -2 ); } \
				if( !( force || operhead##isequal( str[ strlen - 1 ], fillval ) ) ) { \
					/* Overflow error. */ return( -3 ); } \
				while( strlen > inspoint && strlen > 1 ) { \
					--strlen; str[ strlen ] = str[ strlen - 1 ]; } \
				str[ strlen ] = insval; \
				/* Success. */ return( 1 ); } \
			/* Direct Domain error. */ return( -1 ); }
	#define LIBANDRIA4_DEFINE_PASCALSTRING_MUTAOVER( head, type, operhead ) \
		int head##mutatingoverwrite( type *str, size_t strlen, \
			size_t ovrpoint, type ovrval, type ign1, int ign2 ) \
		{ if( str ) { \
				if( ovrpoint >= strlen ) { \
					/* Indirect Domain error. */ return( -2 ); } \
				str[ ovrpoint ] = ovrval; \
				/* Success. */ return( 1 ); } \
			/* Direct Domain error. */ return( -1 ); }
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_MEMEQSPN( head, type, parrtype, operhead ) \
		parrtype##parrexrptres head##memeqspn( \
			parrtype##parr *str, parrtype##parr *matches, \
			size_t curPos, int stepForward, int spanMatch ) \
		{ \
			parrtype##parrexrpt ret = \
				LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_LITERAL( \
					parrtype,  str, 0, 0 );\
				/* Members: arr ptr; start; len.  */\
			stepForward = ( stepForward ? 1 : -1 ); \
			intmax_t bounds = ( !stepForward ? -1 : str->len ); \
			int curOff = 0; uintptr_t sepOff = 0, found; \
			void *a; libandria4_failure_uipresult e = { 0 }; \
			\
				/* Search for a separator. */ \
			while( curPos + curOff != bounds ) { \
				libandria4_ptrresult res = libandria4_memmem ( \
					(void*)( matches->body ), matches->len, \
						/* We only check the CURRENT string character, not all */ \
						/*  of them. */ \
					(void*)&( str->body[ curPos + curOff ] ), \
					sizeof( char ), sizeof( char ) ); \
				LIBANDRIA4_PTRRESULT_BODYMATCH( \
					res, LIBANDRIA4_OP_SETa, LIBANDRIA4_OP_SETe ); \
				if( e.val == LIBANDRIA4_RESULT_FAILURE_DOMAIN ) { \
					/* The last argument wasn't an integer multiple of the */ \
					/*  next-to-last, which obviously shouldn't be possible, */ \
					/*  so logic fault. */ \
					LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_RETURNFAIL( \
						parrtype, LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); } \
				if( !( e.val ) ) { \
					/* No failure, thus success. */ \
					curPos += curOff; curOff = 0; \
					found = (uintptr_t)a; \
					sepOff = (uintptr_t)a + 1; \
					/* Exit the while loop. */ break; } \
				\
				curOff += stepForward; } \
			if( !sepOff ) { /* No match, lets return. */ \
				LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_RETURNFAIL( \
					parrtype, LIBANDRIA4_RESULT_FAILURE_EOF ); } \
			/* curPos has been updated. */ \
			\
				/* Move past all adjacent duplicate separators. */ \
			while( sepOff && spanMatch > 0 ) { \
				curOff += stepForward; \
				if( !( curPos + curOff ) || curPos + curOff >= bounds ) { \
					/* Limits check. */ break; } \
				sepOff = \
					( ( matches->body[ found ] == \
						str->body[ curPos + curOff ] ) ? \
							1 : 0 ); \
				if( !sepOff ) { break; } } \
			\
			if( spanMatch <= 0 ) { curOff = stepForward; } \
				/* Getting here requires at least one match. */ \
				ret.start = ( curOff > 0 ? curPos : curPos + curOff + 1 ); \
				ret.len = ( curOff > 0 ? curOff : -curOff ); \
			LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_RESULT_RETURNSUCCESS( \
				parrtype, ret ); }
	
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_BAREDECLARE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BAREDECLARE( head, type ) \
		typedef head##pascalarray head##parr; \
		typedef head##pascalarray_result head##parrres; \
		int head##parr_decimalincr( head##parr *parr ); \
		head##parrres head##parr_strbuild( libandria4_memfuncs_t *mf, type *str ); \
		head##parrres head##parr_strbuildmerge( libandria4_memfuncs_t *mf, type *a, type *b ); \
		head##parrres head##parr_merge( libandria4_memfuncs_t *mf, head##parr *a, head##parr *b ); \
		\
		int head##stringops_mutatingdelete( type *str, size_t strlen, \
			size_t delstart, size_t dellen, type fill ); \
		int head##stringops_mutatinginsert( type *str, size_t strlen, \
			size_t inspoint, type insval, type fillval, int force ); \
		int head##stringops_mutatingoverwrite( type *str, size_t strlen, \
			size_t ovrpoint, type ovrval, type ign1, int ign2 ); \
		head##pascalarray_excerpt_result head##stringops_memeqspn( head##pascalarray *str, \
			head##pascalarray *matches, size_t curPos, int stepForward, int spanMatch ); \
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_BAREDECL( \
			head##pascalarray_tracker, head##pascalarray* ); \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( \
			head##pascalarray_tracker_result, \
			head##pascalarray_tracker, libandria4_failure_uipresult );
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_BAREDEFINE( head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_BAREDEFINE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_DECIMALINCR( head, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILD( head, head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILDMERGE( head, head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MERGE( head, head, type, operhead ) \
		\
		LIBANDRIA4_DEFINE_PASCALSTRING_MUTADEL( head##stringops_, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MUTAINS( head##stringops_, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MUTAOVER( head##stringops_, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MEMEQSPN( head##stringops_, type, head, operhead ) \
		\
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_BAREIMPL( \
			head##pascalarray_tracker, head##pascalarray*, \
				LIBANDRIA4_DEFINE_PASCALSTRING_NOOP, \
				LIBANDRIA4_DEFINE_PASCALSTRING_NOOP, \
				LIBANDRIA4_DEFINE_PASCALSTRING_ONDIE );
	
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDECLARE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( head, type ) \
		typedef head ## pascalarray head ## parr; \
		typedef head ## pascalarray_result head ## parrres; \
		int head##parr_decimalincr( head##parr *parr ); \
		head##parrres head##parr_strbuild( type *str ); \
		head##parrres head##parr_strbuildmerge( type *a, type *b ); \
		head##parrres head##parr_merge( head##parr *a, head##parr *b ); \
		\
		int head##stringops_mutatingdelete( type *str, size_t strlen, \
			size_t delstart, size_t dellen, type fill ); \
		int head##stringops_mutatinginsert( type *str, size_t strlen, \
			size_t inspoint, type insval, type fillval, int force ); \
		int head##stringops_mutatingoverwrite( type *str, size_t strlen, \
			size_t ovrpoint, type ovrval, type ign1, int ign2 ); \
		head##pascalarray_excerpt_result head##stringops_memeqspn( head##pascalarray *str, \
			head##pascalarray *matches, size_t curPos, int stepForward, int spanMatch ); \
		\
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDDECL( \
			head##pascalarray_tracker, head##pascalarray* ); \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( \
			head##pascalarray_tracker_result, \
			head##pascalarray_tracker, libandria4_failure_uipresult );
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDEFINE( head, type, operhead, memfuncs_ptr ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDEFINE( head, type, memfuncs_ptr ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_DECIMALINCR( head, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILD( libandria4_definer_##head, head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STRBUILDMERGE( libandria4_definer_##head, head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MERGE( libandria4_definer_##head, head, type, operhead ) \
		head##parrres head##parr_strbuild( type *str ) \
			{ return( libandria4_definer_##head##parr_strbuild( ( memfuncs_ptr ), str ) ); } \
		head##parrres head##parr_strbuildmerge( type *a, type *b ) \
			{ return( libandria4_definer_##head##parr_strbuildmerge( ( memfuncs_ptr ), a, b ) ); } \
		head##parrres head##parr_merge( head##parr *a, head##parr *b ) \
			{ return( libandria4_definer_##head##parr_merge( ( memfuncs_ptr ), a, b ) ); } \
		\
		LIBANDRIA4_DEFINE_PASCALSTRING_MUTADEL( head##stringops_, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MUTAINS( head##stringops_, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MUTAOVER( head##stringops_, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_MEMEQSPN( head##stringops_, type, head, operhead ) \
		\
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDIMPL( \
			head##pascalarray_tracker , head##pascalarray* , \
				memfuncs_ptr ,\
				LIBANDRIA4_DEFINE_PASCALSTRING_NOOP, \
				LIBANDRIA4_DEFINE_PASCALSTRING_NOOP, \
				LIBANDRIA4_DEFINE_PASCALSTRING_ONDIE );
		
	
	#define LIBANDRIA4_DEFINE_PASCALSTRING_STDDEFINE( head, type, operhead ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDEFINE( head, type, operhead, (&libandria4_stdmemfuncs) )
	
	
	
	#include <wchar.h>
	#include <stdint.h>
	
	
	/* These use standard language tools: change that. */
	int libandria4_ascii_isnewline( char c );
	int libandria4_ascii_tonum( char var );
	
	int libandria4_utf32_isnewline( uint32_t c );
	int libandria4_utf32_halfnewline( uint32_t c );
	int libandria4_utf32_diversenewline( uint32_t c );
	#define LIBANDRIA4_UTF32_REFPOINTER_BODYINIT( targvar, newval, aux,  failinit, badalloc, badata ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYINIT( \
			libandria4_utf32_pascalarray_tracker, targvar, newval, aux, \
			failinit, badalloc, badata )
	#define LIBANDRIA4_UTF32_REFPOINTER_WRAPPED_BODYSET( targvar, valptr,  failneglect, failattend, succneglect, succattend, ondead ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYSET( \
			libandria4_utf32_pascalarray_tracker, targvar, valptr, \
			failneglect, failattend, succneglect, succattend, ondead )
	#define LIBANDRIA4_UTF32_REFPOINTER_WRAPPED_BODYDEINIT( targvar,  failneglect, succneglect, ondead ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYDEINIT( \
			libandria4_utf32_pascalarray_tracker, targvar, \
			failneglect, succneglect, ondead )
	#define LIBANDRIA4_UTF32_REFPOINTER_EXPRINIT_NULL( targvar ) \
		LIBANDRIA4_MONAD_REFPOINTER_EXPRINIT_NULL( \
			libandria4_utf32_pascalarray_tracker, targvar )
	
	int libandria4_char_isnewline( char c );
	int libandria4_char_tonum( char var );
	int libandria4_char_stringops_ringincr( char* );
	#define LIBANDRIA4_CHARPSTR_REFPOINTER_BODYINIT( targvar, newval, aux,  failinit, badalloc, badata ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYINIT( \
			libandria4_char_pascalarray_tracker, targvar, newval, aux, \
			failinit, badalloc, badata )
	#define LIBANDRIA4_CHARPSTR_REFPOINTER_WRAPPED_BODYSET( targvar, valptr,  failneglect, failattend, succneglect, succattend, ondead ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYSET( \
			libandria4_char_pascalarray_tracker, targvar, valptr, \
			failneglect, failattend, succneglect, succattend, ondead )
	#define LIBANDRIA4_CHARPSTR_REFPOINTER_WRAPPED_BODYDEINIT( targvar,  failneglect, succneglect, ondead ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYDEINIT( \
			libandria4_char_pascalarray_tracker, targvar, \
			failneglect, succneglect, ondead )
	#define LIBANDRIA4_CHARPSTR_REFPOINTER_EXPRINIT_NULL( targvar ) \
		LIBANDRIA4_MONAD_REFPOINTER_EXPRINIT_NULL( \
			libandria4_char_pascalarray_tracker, targvar )
	
	int libandria4_wchar_isnewline( wchar_t c );
	int libandria4_wchar_tonum( wchar_t var );
	int libandria4_wchar_stringops_ringincr( wchar_t *var );
	#define LIBANDRIA4_WCHARPSTR_REFPOINTER_BODYINIT( targvar, newval, aux,  failinit, badalloc, badata ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYINIT( \
			libandria4_wchar_pascalarray_tracker, targvar, newval, aux, \
			failinit, badalloc, badata )
	#define LIBANDRIA4_WCHARPSTR_REFPOINTER_WRAPPED_BODYSET( targvar, valptr,  failneglect, failattend, succneglect, succattend, ondead ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYSET( \
			libandria4_wchar_pascalarray_tracker, targvar, valptr, \
			failneglect, failattend, succneglect, succattend, ondead )
	#define LIBANDRIA4_WCHARPSTR_REFPOINTER_WRAPPED_BODYDEINIT( targvar,  failneglect, succneglect, ondead ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYDEINIT( \
			libandria4_wchar_pascalarray_tracker, targvar, \
			failneglect, succneglect, ondead )
	#define LIBANDRIA4_WCHARPSTR_REFPOINTER_EXPRINIT_NULL( targvar ) \
		LIBANDRIA4_MONAD_REFPOINTER_EXPRINIT_NULL( \
			libandria4_wchar_pascalarray_tracker, targvar )
	
	/* Note: LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY( var,  func, onnull ) can */
	/*  be used with ANY of the libandria4_*_pascalarray_tracker{} types. */
	
	
	
	/* These macros provide the functionality required for the "operhead" */
	/*  macro arguments. Various bits of support stuff should be moved to */
	/*  somewhere in the text/ directory eventually. */
	
	/* The common C char set. */
	#include <ctype.h>
	#include <string.h>
	#define LIBANDRIA4_CHAR_STRINGOPS_set( dest, src ) ( ( dest ) = ( src ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_isnum( val ) ( isdigit( val ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_isultidigit( val ) ( ( val ) == '9' ? 1 : 0 )
	#define LIBANDRIA4_CHAR_STRINGOPS_isequal( a, b ) ( ( a ) == ( b ) ? 1 : 0 )
	#define LIBANDRIA4_CHAR_STRINGOPS_ringincr( var ) ( libandria4_char_stringops_ringincr( &( var ) ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_zeroval() ( 0 )
	#define LIBANDRIA4_CHAR_STRINGOPS_strlen( str ) ( strlen( str ) )
	#define LIBANDRIA4_CHAR_STRINGOPS_nullval() ( '\0' )
	
	/* The common C wide-char set. */
	#include <wctype.h>
	#define LIBANDRIA4_WCHAR_STRINGOPS_set( dest, src ) ( ( dest ) = ( src ) )
	#define LIBANDRIA4_WCHAR_STRINGOPS_isnum( val ) ( iswdigit( val ) )
	#define LIBANDRIA4_WCHAR_STRINGOPS_isultidigit( val ) ( ( val ) == L'9' ? 1 : 0 )
	#define LIBANDRIA4_WCHAR_STRINGOPS_isequal( a, b ) ( ( a ) == ( b ) ? 1 : 0 )
	#define LIBANDRIA4_WCHAR_STRINGOPS_ringincr( var ) ( libandria4_wchar_stringops_ringincr( &( var ) ) )
	#define LIBANDRIA4_WCHAR_STRINGOPS_zeroval() ( 0 )
		/* The header for wcslen() is wchar.h, and that's ALREADY included. */
	#define LIBANDRIA4_WCHAR_STRINGOPS_strlen( str ) ( wcslen( str ) )
	#define LIBANDRIA4_WCHAR_STRINGOPS_nullval() ( L'\0' )
	
	/* The UTF32 character set. */
	#define LIBANDRIA4_UTF32_STRINGOPS_set( dest, src ) ( ( dest ) = ( src ) )
	#define LIBANDRIA4_UTF32_STRINGOPS_isnum( val ) ( libandria4_utf32_isdigit( val ) )
	#define LIBANDRIA4_UTF32_STRINGOPS_isultidigit( val ) ( ( val ) == 57 ? 1 : 0 )
	#define LIBANDRIA4_UTF32_STRINGOPS_isequal( a, b ) ( ( a ) == ( b ) ? 1 : 0 )
	#define LIBANDRIA4_UTF32_STRINGOPS_ringincr( var ) ( libandria4_utf32_stringops_ringincr( &( var ) ) )
	#define LIBANDRIA4_UTF32_STRINGOPS_zeroval() ( 0 )
	#define LIBANDRIA4_UTF32_STRINGOPS_strlen( str ) ( libandria4_utf32_strlen( str ) )
	#define LIBANDRIA4_UTF32_STRINGOPS_nullval() ( 48 )
	
	
	
	LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDECLARE( libandria4_char_, char );
	LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDECLARE( libandria4_wchar_, wchar_t );
	LIBANDRIA4_DEFINE_PASCALSTRING_WRAPEDDECLARE( libandria4_utf32_, uint32_t );
	
	#include "commonlib.h"
	#include "stdmem.h"
	
	/* Note that the following types will be produced for all three of the */
	/*  declares above: */
		/*
			* pascalarray
			* parr (a duplicate of * pascalarray)
			* pascalarray_result
			* parrres (a duplicate of * pascalarray_result)
			* pascalarray_excerpt
			* pascalarray_excerpt_result
			* pascalarray_tracker
			* pascalarray_tracker_result
		*/
	/* The *_result types follow the usual base-type/alt-type order, and all */
	/*  of the alternate types are struct-wrapped integer members named val. */
	/* For the *_excerpt types, look at pascalarray.h, but it's the obvious. */
	/* The *_tracker types are ref-pointer instantiations, ala monads.h */
	
#endif
/* End libandria4 basic text_pascalstring.h */
