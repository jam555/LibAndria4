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

#ifndef LIBANDRIA4_TEXT_COMMONBUFFER_H
# define LIBANDRIA4_TEXT_COMMONBUFFER_H
	
	#include "stdbuffer.h"
	
	/* This file was built for use by the VT100 parser code in the */
	/*  ../parsers folder. For a it's generic definition, look in */
	/*  stdbuffer.h */
	
	typedef struct libandria4_termbuffer_common
	{
		libandria4_termbuffer_generic common;
		
			/* Marks where the ACTUAL start of the buffer is, for copy */
			/*  optimization. Specifically a LINE offset. */
		uint32_t start_off;
			/* Measured in character cells, not in e.g. pixels, or inches. */
		libandria4_bytebuffer_pascalarray *buf;
		
	} libandria4_termbuffer_common;
	
		/* Convenience type for array access. */
	typedef union
	{
		uint8_t bytes[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		libandria4_buffercell_common cells[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		
	} libandria4_buffercell_common_accessor;
	
	
	
	int libandria4_termbuffer_common_setcell
	(
		libandria4_termbuffer_generic *term_,
			uint32_t x, uint32_t y,
			libandria4_buffercell_common val
	);
	int libandria4_termbuffer_common_setblock
	(
		libandria4_termbuffer_generic *term_,
			uint32_t x, uint32_t y,  uint32_t w, uint32_t h,
			libandria4_buffercell_common *vals
	);
	
	int libandria4_termbuffer_common_scroll
	(
		libandria4_termbuffer_generic *term_,
			libandria4_termbuffer_directions dir,
			libandria4_buffercell_common fill,
			uint32_t x, uint32_t y,
			uint32_t w, uint32_t h
	);
	int libandria4_termbuffer_common_resize
	(
		libandria4_termbuffer_generic *term_,
			uint32_t new_w, uint32_t new_h,
			libandria4_buffercell_common fill,
			int keep_old
	);
	
	
	/* Convenience functions: */
	
		/* Returns positive if "term" is believed to be valid, and if */
		/*  "term2" is non-null then a properly cast copy of "term" will be */
		/*  stored through it. */
		/* NOTE: The validation is actually very bare-bones right now, but */
		/*  this description will stay accurate. */
	int libandria4_termbuffer_validatecommon
	(
		libandria4_termbuffer_generic *term,
		libandria4_termbuffer_common **term2
	);
		/* Initializes *ret to point to a */
		/*  libandria4_buffercell_common_accessor{} instance for easier */
		/*  array access. Attempts to correct for any odd misalignment */
		/*  quirks that may be produced by padding. */
	int libandria4_align_buffercell_accessor
	(
		libandria4_termbuffer_common *term,
		
		libandria4_buffercell_common_accessor **ret
	);
	int libandria4_align_buffercell_calcoffset
	(
		libandria4_termbuffer_common *term,
			uint32_t x, uint32_t y,
			uint32_t *off
	);
	
#endif
/* End libandria4 text commonbuffer.h */
