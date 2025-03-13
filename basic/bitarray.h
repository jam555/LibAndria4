#ifndef LIBANDRIA4_BASIC_BITARRAY_H
# define LIBANDRIA4_BASIC_BITARRAY_H
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
	
	#include "pascalarray.h"
	
	
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_bitarray_, uint8_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_bitsurface_, libandria4_bitarray_pascalarray* );
	
	typedef struct libandria4_bitarray
	{
		size_t width;
		libandria4_bitarray_pascalarray arr;
		
	} libandria4_bitarray;
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE( libandria4_bitarray_result,  libandria4_bitarray*, int );
	#define LIBANDRIA4_BITARRAY_RESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_bitarray_result, libandria4_bitarray*, (val) )
	#define LIBANDRIA4_BITARRAY_RESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_bitarray_result, int, (val) )
	
	typedef struct libandria4_bitsurface
	{
		size_t width;
		libandria4_bitsurface_pascalarray surf;
		
	} libandria4_bitsurface;
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE( libandria4_bitsurface_result,  libandria4_bitsurface*, int );
	#define LIBANDRIA4_BITSURFACE_RESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_bitsurface_result, libandria4_bitsurface*, (val) )
	#define LIBANDRIA4_BITSURFACE_RESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_bitsurface_result, int, (val) )
	
	
	
	
	/* TODO: Build versions of libandria4_bitsurface_copy() and */
	/*  libandria4_bitsurface_result libandria4_bitsurface_excerpt() for */
	/*  libandria4_bitarray{}. */
	/* Functions for the basic operations on bit arrays. */
	int libandria4_bitarray_init( libandria4_bitarray *barr,  size_t len );
	libandria4_bitarray_result libandria4_bitarray_build( size_t len );
	libandria4_bitarray_result libandria4_bitarray_rebuild( libandria4_bitarray *barr,  size_t newlen );
		libandria4_result libandria4_bitarray_fill( libandria4_bitarray *barr,  uint8_t *src );
		libandria4_bitarray_result libandria4_bitarray_buildNfill( size_t len,  uint8_t *src );
		/* read() and write() will return negatives on error, all others are successes. */
		int libandria4_bitarray_read( libandria4_bitarray *barr, size_t offset );
		int libandria4_bitarray_write( libandria4_bitarray *barr, size_t offset,  int val );
	libandria4_result libandria4_bitarray_destroy( libandria4_bitarray *barr );
		/* visitor() will be given access to a per-bit int pointer. The lowest */
		/*  bit will be set or cleared based on the related bit in the array, */
		/*  and the bits in the array will be updated after the visitor() calls */
		/*  have returned. Extra bits can be presented to visitor(). */
	void libandria4_bitarray_visit( libandria4_bitarray *barr,  void *data, void (*visitor)( void*, int ) );
	
	
	
	/* Functions for the basic operations on bit surfaces (two dimensional bit arrays). */
	int libandria4_bitsurface_init( libandria4_bitsurface *bsurf,  size_t width, size_t height );
	libandria4_bitsurface_result libandria4_bitsurface_build( size_t width, size_t height );
	libandria4_bitsurface_result libandria4_bitsurface_rebuild( libandria4_bitsurface *bsurf,  size_t width, size_t height );
		libandria4_result libandria4_bitsurface_fill( libandria4_bitsurface *bsurf,  uint8_t **src );
		libandria4_bitsurface_result libandria4_bitsurface_buildNfill( size_t width, size_t height,  uint8_t **src );
		libandria4_bitsurface_result libandria4_bitsurface_copy( libandria4_bitsurface *src );
			/* Copy a rectangular subset of src. */
		libandria4_bitsurface_result libandria4_bitsurface_excerpt
		(
			libandria4_bitsurface *src,
				/* basal_x and width are measured in BITS, not bytes. */
				/* basal_y and height are measured in "scan lines", or whatever. */
			size_t basal_x, size_t basal_y,
			size_t width, size_t height
		);
		/* read() and write() will return negatives on error, all others are successes. */
		int libandria4_bitsurface_read( libandria4_bitsurface *bsurf, size_t x, size_t y );
		int libandria4_bitsurface_write( libandria4_bitsurface *bsurf, size_t x, size_t y,  int val );
	libandria4_result libandria4_bitsurface_destroy( libandria4_bitsurface *bsurf );
		/* Acts like libandria4_bitarray_visit(), but hinc() will also be */
		/*  called at the end (NOT between) the relevant component arrays. */
	void libandria4_bitsurface_visit
	(
		libandria4_bitsurface *bsurf,
		
		void *data,
		void (*visitor)( void*, int* ),
			/* Called once at the end of EACH visited 1 dimensional bit array. */
		void (*hinc)( void* )
	);
	
#endif
/* End libandria4 basic bitarray.h */
