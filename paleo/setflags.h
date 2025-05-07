#ifndef LIBANDRIA4_BASIC_SETFLAGS_H
 #define LIBANDRIA4_BASIC_SETFLAGS_H
 	/*
	LibAndria version 4
	A C-based general purpose utility library.
	Copyright (c) 2025 Jared A. Maddox
	
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
	
	/* This file is incomplete! And massively so! */
	/*
			This file was inspired by Kernighan, in "Why Pascal is Not My Favorite
		Programming Language", talking about Pascal's set construct. Particularly,
		it was inspired by some quick thoughts about how to semi-efficiently
		indicate set-membership for sparsly-populated sets that can be accurately
		represented on a 1-dimensional metric space with no "hash collisions" and
		IDEALLY (but not reliably, even within the "simple" case) no duplication
		of members to multiple points in the set.
			My conclusion was to start with a wrapper for an array of bits that
		added on an indication of WHERE in the set the first possibility, and
		another indicator for the distance BETWEEN possibilities, such that
		regularly-spaced members would be easy to represent with a fair density.
			From there, "make an array of them to make it easier to optimize!" and
		"make a list of them to make it easier to optimize and/or extend!" both
		quickly came to mind, and were both quickly scratched out below.
		
			This file is JUST NOT READY TO USE. If you want to use it, finish
		writing it. Look to pascalarray.h for how: we don't want to depend on any
		partcular type(s) for the start and step values, so there's a need for a
		set of macros to properly build the various types & helpers functions.
	*/
	
	
	
	#define LIBANDRIA4_SIMPLE_SETFLAGS( name, numtype ) \
		typedef struct name name; \
		struct { \
			numtype (start), (step); \
			libandria4_bitarray *barr; \
		} name;
	
	int libandria4_simple_setflags_init( libandria4_bitarray *barr,  size_t len );
	libandria4_bitarray_result libandria4_simple_setflags_build( size_t len );
	libandria4_bitarray_result libandria4_simple_setflags_rebuild( libandria4_bitarray *barr,  size_t newlen );
		libandria4_result libandria4_simple_setflags_fill( libandria4_bitarray *barr,  uint8_t *src );
		libandria4_bitarray_result libandria4_simple_setflags_buildNfill( size_t len,  uint8_t *src );
		/* read() and write() will return negatives on error, all others are successes. */
		int libandria4_simple_setflags_read( libandria4_bitarray *barr, size_t offset );
		int libandria4_simple_setflags_write( libandria4_bitarray *barr, size_t offset,  int val );
	libandria4_result libandria4_simple_setflags_destroy( libandria4_bitarray *barr );
		/* visitor() will be given access to a per-bit int pointer. The lowest */
		/*  bit will be set or cleared based on the related bit in the array, */
		/*  and the bits in the array will be updated after the visitor() calls */
		/*  have returned. Extra bits can be presented to visitor(). */
	void libandria4_simple_setflags_visit( libandria4_bitarray *barr,  void *data, void (*visitor)( void*, int ) );
	
	
	
	
	#define LIBANDRIA4_ARRAYED_SETFLAGS( name, innername, numtype ) \
		LIBANDRIA4_SIMPLE_SETFLAGS( innername, numtype ); \
		typedef struct name name; \
		struct { \
				pascalarray(< innername >) arr; \
			} name;
	
	int libandria4_arrayed_setflags_init( libandria4_bitarray *barr,  size_t len );
	libandria4_bitarray_result libandria4_arrayed_setflags_build( size_t len );
	libandria4_bitarray_result libandria4_arrayed_setflags_rebuild( libandria4_bitarray *barr,  size_t newlen );
		libandria4_result libandria4_arrayed_setflags_fill( libandria4_bitarray *barr,  uint8_t *src );
		libandria4_bitarray_result libandria4_arrayed_setflags_buildNfill( size_t len,  uint8_t *src );
		/* read() and write() will return negatives on error, all others are successes. */
		int libandria4_arrayed_setflags_read( libandria4_bitarray *barr, size_t offset );
		int libandria4_arrayed_setflags_write( libandria4_bitarray *barr, size_t offset,  int val );
	libandria4_result libandria4_arrayed_setflags_destroy( libandria4_bitarray *barr );
		/* visitor() will be given access to a per-bit int pointer. The lowest */
		/*  bit will be set or cleared based on the related bit in the array, */
		/*  and the bits in the array will be updated after the visitor() calls */
		/*  have returned. Extra bits can be presented to visitor(). */
	void libandria4_arrayed_setflags_visit( libandria4_bitarray *barr,  void *data, void (*visitor)( void*, int ) );
	
	
	
	
	#define LIBANDRIA4_LISTED_SETFLAGS( name, arrname, innername, numtype ) \
		LIBANDRIA4_ARRAYED_SETFLAGS( arrname, innername, numtype ); \
		typedef struct name name; \
		struct { \
				name (*next); \
				innername (arr); \
			} name;
	
	int libandria4_listed_setflags_init( libandria4_bitarray *barr,  size_t len );
	libandria4_bitarray_result libandria4_listed_setflags_build( size_t len );
	libandria4_bitarray_result libandria4_listed_setflags_rebuild( libandria4_bitarray *barr,  size_t newlen );
		libandria4_result libandria4_listed_setflags_fill( libandria4_bitarray *barr,  uint8_t *src );
		libandria4_bitarray_result libandria4_listed_setflags_buildNfill( size_t len,  uint8_t *src );
		/* read() and write() will return negatives on error, all others are successes. */
		int libandria4_listed_setflags_read( libandria4_bitarray *barr, size_t offset );
		int libandria4_listed_setflags_write( libandria4_bitarray *barr, size_t offset,  int val );
	libandria4_result libandria4_listed_setflags_destroy( libandria4_bitarray *barr );
		/* visitor() will be given access to a per-bit int pointer. The lowest */
		/*  bit will be set or cleared based on the related bit in the array, */
		/*  and the bits in the array will be updated after the visitor() calls */
		/*  have returned. Extra bits can be presented to visitor(). */
	void libandria4_listed_setflags_visit( libandria4_bitarray *barr,  void *data, void (*visitor)( void*, int ) );
	
	
	/* End basic/setfags.h */
	
#endif
