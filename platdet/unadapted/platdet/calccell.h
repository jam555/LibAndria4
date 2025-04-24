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

#if LIBANDRIA4_PRIMITIVE_PLATDET_CALCCELL_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_CALCCELL_H
	
	#include "../platformdetect.h"
	
		/* Contrary to my norm, this needs to be included AFTER */
		/*  platformdetect.h, because parts of THAT file depend on strict */
		/*  control of what macros are and aren't set... with any standard */
		/*  header LIKELY to set some that matter. */
	#include <stdint.h>
	
	
	/* TODO: Figure out how to tell whether we should use signed or unsigned! */
	#define LIBANDRIA4_CELLTYPE_TYPE uintptr_t
	
	/* TODO: Fix the comparisons, and improve the error messages! */
	#if UINTPTR_MAX <= 65535
		#error "Cell size of 2 bytes or less detected with TCC: this is not known to be possible!\n"
	#elif UINTPTR_MAX < 4294967295
		#define LIBANDRIA4_CELLTYPE_SIZE ( 4 )
	#elif UINTPTR_MAX < 18446744073709551615
		#define LIBANDRIA4_CELLTYPE_SIZE ( 8 )
	#elif UINTPTR_MAX < 340282366920938463463374607431768211455
		#define LIBANDRIA4_CELLTYPE_SIZE ( 16 )
	#else
		#error "Cell size didn't match any cases!\n"
	#endif
	
#endif /* End primitive platdet calccell.h */
