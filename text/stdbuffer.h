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

#ifndef LIBANDRIA4_TEXT_STDBUFFER_H
# define LIBANDRIA4_TEXT_STDBUFFER_H
	
	#include "../basic/commonmacros.h"
	#include "../basic/stdmem.h"
		/* The nearly omniversal utility header... */
	#include "../basic/pascalarray.h"
	#include "../basic/pascalstring.h"
	#include "../basic/commonio.h"
		/* This include shouldn't be needed, but let's not delete it just */
		/*  yet... */
	/* include "termninal.h" */
	
	
	
	/* The terminal buffer system. */
	
	LIBANDRIA4_DEFINE_PASCALARRAY_BAREDECLARE( libandria4_bytebuffer_, uint8_t );
	
	typedef struct libandria4_termbuffer_generic libandria4_termbuffer_generic;
	
	
	
		/* Just a convenience type. */
	typedef struct libandria4_buffercell_common
	{
			/* E.g. "blink" and "vermillion". */
		struct
		{
			uint8_t r, g, b;
			uint8_t style;
		} style;
		
			/* Presumably a Unicode character, but maybe something (e.g. */
			/*  JIS, EBCDIC) incompatible. Should ALWAYS be a "resolved" */
			/*  character though, so no e.g. surrogate code points allowed. */
			/* ... probably not even combining characters for this style. */
		uint32_t chara;
		
	} libandria4_buffercell_common;
	/* Note: this is ABSOLUTELY expected to be just 64 bits in size. If it */
	/*  isn't, then add some compiler pragmas. */
	
	
	
	typedef (*libandria4_termbuffer_generic_setter)
		(
			libandria4_termbuffer_generic*,
				uint32_t /* x */, uint32_t /* y */,
				libandria4_termbuffer_func_receiver
		);
	typedef (*libandria4_termbuffer_generic_resizer)
		(
			libandria4_termbuffer_generic*,
				uint32_t /* new_w */, uint32_t /* new_h */
		);
	typedef struct libandria4_termbuffer_generic_vtab
	{
		libandria4_termbuffer_generic_setter setcell;
		libandria4_termbuffer_generic_setter setblock;
		
		libandria4_termbuffer_generic_resizer resize;
		
	} libandria4_termbuffer_generic_vtab;
	
	struct libandria4_termbuffer_generic
	{
		libandria4_termbuffer_generic_vtab *funcs;
		
			/* Measured in character cells, not in e.g. pixels, or inches. */
		uint32_t width, height;
		
		libandria4_memfuncs_t *mfuncs;
		libandria4_commonio_handle *messaging;
	};
	
	typedef struct libandria4_termbuffer_func_receiver
	{
		uintptr_t id;
		
		int (*func)
			(
				libandria4_termbuffer_func_receiver*,
					uint32_t /* width aka x */, uint32_t /* height aka y */,
					libandria4_buffercell_common
			);
		
	} libandria4_termbuffer_func_receiver;
	
	
	extern libandria4_termbuffer_generic_vtab libandria4_termbuffer_common_vtab;
	
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
	
	int libandria4_termbuffer_common_resize
	(
		libandria4_termbuffer_generic *term_,
			uint32_t new_w, uint32_t new_h,
			libandria4_buffercell_common fill,
			int keep_old
	);
	
#endif
/* End libandria4 text stdbuffer.h */

