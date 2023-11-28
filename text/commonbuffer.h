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
	
	typedef struct libandria4_termbuffer_common
	{
		libandria4_termbuffer_generic common;
		
			/* Measured in character cells, not in e.g. pixels, or inches. */
		libandria4_bytebuffer_pascalarray *buf;
		
	} libandria4_termbuffer_common;
	
		/* Another convenience type. */
	typedef union
	{
		uint8_t bytes[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		libandria4_buffercell_common cells[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		
	} libandria4_buffercell_common_accessor;
	
#endif
/* End libandria4 text commonbuffer.h */