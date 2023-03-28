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

#ifndef LIBANDRIA4_TEXT_PASCALARRAY_H
# define LIBANDRIA4_TEXT_PASCALARRAY_H
	
	/* There are various things to do with this, including to macro-ize the */
	/*  functions to allow them to be automatically generated for different */
	/*  character types & encodings. It would be good to create some */
	/*  insert/excerpt functions as well, though that can certainly wait for */
	/*  macroization. For now, these are sufficient. */
	
	
	
	#include "stdmem.h"
	#include "pascalarray.h"
	
	
	LIBANDRIA4_DEFINE_PASCALARRAY_BAREDEFINE( libandria4_char_, char )
	
		/* These build a compound-literal, suitable for initializing */
		/*  libandria4_char_parr instances, or even having it's address taken. */
		/*  Apparently it can be of AUTOMATIC duration instead of static in */
		/*  certain circumstances, so beware!*/
		/* Note: DOES include the ending null! */
	#define LIBANDRIA4_DEFINE_CHAR_PASCALARRAY_LITERAL( text ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_LITERAL( libandria4_char_, sizeof( text ), text )
		/* Note: Does NOT include the null! Sorta. */
	#define LIBANDRIA4_DEFINE_CHAR_PASCALARRAY_LITERAL_NNULL( text ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_LITERAL( libandria4_char_, sizeof( text ) - 1, text )
	
	typedef libandria4_char_pascalarray libandria4_char_parr;
	typedef libandria4_char_pascalarray_result libandria4_char_parrres;
		/* To get the relevant stuff out of a libandria4_char_parrres, pass a */
		/*  VARIABLE containing the value to either */
		/*  LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH() or */
		/*  LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_EXPRMATCH() (or alternatively, to */
		/*  any of the equivalents), passing functions and/or macros */
		/*  equivalent to matcha( libandria4_char_pascalarray* ) and */
		/*  matchb( libandria4_failure_uipresult ): the BODY version calls them */
		/*  within the branches of an if(), while the EXPR version sticks */
		/*  them into a ternary operator. */
	#define LIBANDRIA4_DEFINE_CHAR_PARRRES_BUILDSUCCESS( val ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDSUCCESS( libandria4_char_, val )
	#define LIBANDRIA4_DEFINE_CHAR_PARRRES_BUILDFAILURE( val ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BUILDFAILURE( libandria4_char_, val )
	
		/* These are included to make it easier to patch the result of a */
		/*  call to a different return result. It was created because the */
		/*  path-string-builder functions were doing such a thing, so this */
		/*  pulled that functionality out to a more trivially available */
		/*  form. */
	#define LIBANDRIA4_DEFINE_CHAR_PARRRES_RETURNSUCCESS( val ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_RETURNSUCCESS( libandria4_char_, val )
	#define LIBANDRIA4_DEFINE_CHAR_PARRRES_RETURNFAIL( val ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_RETURNFAIL( libandria4_char_, val )
	
	
	
		/* This currently expects ASCII! It treats the argument as a number */
		/*  in decimal text form, and increments it by 1. */
		/* Also, need to move over to the error values in stdmonads.h */
	int libandria4_char_parr_decincr( libandria4_char_parr *parr );
	
	libandria4_char_parrres libandria4_char_parr_strbuild
	(
		libandria4_memfuncs_t *mf,
		
		char *str
	);
	libandria4_char_parrres libandria4_char_parr_strbuildmerge
	(
		libandria4_memfuncs_t *mf,
		
		char *a,
		char *b
	);
	
	libandria4_char_parrres libandria4_char_parr_merge
	(
		libandria4_memfuncs_t *mf,
		
		libandria4_char_parr *a,
		libandria4_char_parr *b
	);
	
	int libandria4_ascii_isnewline( char c );
	
#endif
/* End libandria4 text text_pascalarray.h */
