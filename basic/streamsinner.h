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

#ifndef LIBANDRIA4_BASIC_STREAMSINNER_H
# define LIBANDRIA4_BASIC_STREAMSINNER_H
	
	#include "streams.h"
	
	
	
	/*
		This provides various things meant to be useful for backend
		implementations for streams.h/.c
	*/
	
	
	
	/*************************************************************/
	/*************************************************************/
	/** Common implementations, for cases where it's practical. **/
	/*************************************************************/
	/*************************************************************/
	
		/* Uses ->putc() to implement puts_s(). */
	libandria4_commonio_eithgeneric libandria4_commonio_common_puts_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *str, size_t len
	);
		/* Uses ->getc() to implement gets_s(). */
	libandria4_commonio_eithgeneric libandria4_commonio_common_gets_s
	(
		libandria4_commonio_handle *io,
			libandria4_commonio_byte *dest, size_t len
	);
	
	
	
		/* TODO: Should be a wrapper for a version in */
		/*  simpleops.h ... which I think doesn't exist. */
	#define libandria4_commonio_handlevtable_FROM_SRCVTABLE( src_type, dest_type, vtab_ptr ) \
		(dest_type*)( \
			(char*)( (src_type*)(vtab_ptr) ) + ( \
				( (char*)&( ( ( (dest_type*)0 )[ 1 ] ).here ) ) - \
				( (char*)&( ( (dest_type*)0 )[ 1 ] ) ) ) )
	
	
	
	/* TODO: Build a variant on libandria4_commonio_istream_ungetwrapper_vtable{} */
	/*  that DOESN'T CARE if .is points to an istream or a full stream. Requiring */
	/*  that is an unnecessary space consumer for something that gets allocated */
	/*  arbitrarily often. */
	
		/* Provides single-byte-only unget capabilities. */
	typedef struct libandria4_commonio_istream_ungetwrapper_vtable
		libandria4_commonio_istream_ungetwrapper_vtable;
	typedef struct libandria4_commonio_istream_ungetwrapper_vtable
	{
		libandria4_commonio_istream_vtable here;
		libandria4_commonio_istream_vtable *is;
		
		libandria4_commonio_maybyte buffer;
		
	} libandria4_commonio_istream_ungetwrapper;
	#define libandria4_commonio_istream_ungetwrapper_vtable_FROM_ISTREAMVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_istream_vtable, libandria4_commonio_istream_ungetwrapper_vtable, \
			vtab_ptr )
	int libandria4_commonio_istream_ungetwrapper_init
	(
		libandria4_commonio_istream_ungetwrapper_vtable *ugvtab,
		libandria4_commonio_istream_vtable *host
	);
	
	
	
	typedef struct libandria4_commonio_handlevtable_2istream
	{
		libandria4_commonio_istream_vtable here;
		libandria4_commonio_seekable_vtable seekable;
		libandria4_commonio_errorable_vtable errable;
		libandria4_commonio_handle_vtable *is;
		
	} libandria4_commonio_handlevtable_2istream;
	#define libandria4_commonio_handlevtable_2istream_vtable_FROM_HANDLEVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_istream_vtable, libandria4_commonio_handlevtable_2istream, \
			vtab_ptr )
	int libandria4_commonio_handlevtable_2istream_init
	(
		libandria4_commonio_handlevtable_2istream *wrapper,
		libandria4_commonio_handle_vtable *host
	);
	
	typedef struct libandria4_commonio_handlevtable_2ostream
	{
		libandria4_commonio_ostream_vtable here;
		libandria4_commonio_seekable_vtable seekable;
		libandria4_commonio_errorable_vtable errable;
		libandria4_commonio_handle_vtable *is;
		
	} libandria4_commonio_handlevtable_2ostream;
	#define libandria4_commonio_handlevtable_2ostream_vtable_FROM_HANDLEVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_handlevtable_2ostream, libandria4_commonio_handlevtable_2istream, \
			vtab_ptr )
	int libandria4_commonio_handlevtable_2ostream_init
	(
		libandria4_commonio_handlevtable_2ostream *wrapper,
		libandria4_commonio_handle_vtable *host
	);
	
	typedef struct libandria4_commonio_handlevtable_2seekable
	{
		libandria4_commonio_seekable_vtable here;
		libandria4_commonio_handle_vtable *is;
		
	} libandria4_commonio_handlevtable_2seekable;
	#define libandria4_commonio_handlevtable_2seekable_vtable_FROM_HANDLEVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_handlevtable_2seekable, libandria4_commonio_handlevtable_2istream, \
			vtab_ptr )
	int libandria4_commonio_handlevtable_seekable_init
	(
		libandria4_commonio_handlevtable_2seekable *wrapper,
		libandria4_commonio_handle_vtable *host
	);
	
	typedef struct libandria4_commonio_handlevtable_2errorable
	{
		libandria4_commonio_errorable_vtable here;
		libandria4_commonio_handle_vtable *is;
		
	} libandria4_commonio_handlevtable_2errorable;
	#define libandria4_commonio_handlevtable_2errorable_vtable_FROM_HANDLEVTABPTR( vtab_ptr ) \
		libandria4_commonio_handlevtable_FROM_SRCVTABLE( \
			libandria4_commonio_handlevtable_2errorable, libandria4_commonio_handlevtable_2istream, \
			vtab_ptr )
	int libandria4_commonio_handlevtable_errorable_init
	(
		libandria4_commonio_handlevtable_2errorable *wrapper,
		libandria4_commonio_handle_vtable *host
	);
	
	
	
	
	typedef struct libandria4_commonio_handle_vtableset
	{
		union
		{
			libandria4_commonio_handle_vtable libandria4_commonio_handle_vtable;
			libandria4_commonio_errorable_vtable libandria4_commonio_errorable_vtable;
			libandria4_commonio_seekable_vtable libandria4_commonio_seekable_vtable;
			libandria4_commonio_istream_vtable libandria4_commonio_istream_vtable;
			libandria4_commonio_ostream_vtable libandria4_commonio_ostream_vtable;
			
		} vtab;
		libandria4_commonio_handle_vtabtype dispatch;
		
	} libandria4_commonio_handle_vtableset;
	
	
	
	#include <stdio.h>
	
	typedef struct libandria4_commonio_handlevtable_FILE
	{
		libandria4_commonio_handle_vtableset vtab;
		FILE *handle;
		
	} libandria4_commonio_handlevtable_FILE;
	
#endif
/* End libandria4 basic streamsinner.h */
