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

#ifndef LIBANDRIA4_PARSERS_VT100NET_STDBUFFER_H
# define LIBANDRIA4_PARSERS_VT100NET_STDBUFFER_H
	
	#include "../../basic/commonmacros.h"
	#include "termninal.h"
	
	
		/* Just a convenience type. */
	typedef struct vt100net_buffercell_common
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
		
	} vt100net_buffercell_common;
	/* Note: this is ABSOLUTELY expected to be just 64 bits in size. If it */
	/*  isn't, then add some compiler pragmas. */
	
		/* Another convenience type. */
	typedef union
	{
		uint8_t bytes[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		vt100net_buffercell_common cells[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		
	} vt100net_buffercell_common_accessor;
	
	
	
	/* Remember: vt100net_termbuffer_func_voidstruct{} is defined in */
	/*  terminal.h */
	
	typedef struct vt100net_termbuffer_func_uint8receiver
	{
		vt100net_termbuffer_func_voidstruct header;
		
		int (*func)( vt100net_termbuffer_func_uint8receiver*, uint8_t );
		
	} vt100net_termbuffer_func_uint8receiver;
	
#endif
/* End libandria4 parsers vt100net stdbuffer.h */

