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
		/* This include shouldn't be needed, but let's not delete it just */
		/*  yet... */
	/* include "termninal.h" */
	
	
	
	/* The terminal buffer system. */
	
	LIBANDRIA4_DEFINE_PASCALARRAY_BAREDECLARE( libandria4_bytebuffer_, uint8_t );
	
	typedef struct libandria4_termbuffer_generic libandria4_termbuffer_generic;
	
	#define libandria4_termbuffer_NAMECOMMAND( outername, str ) \
		LIBANDRIA4_DEFINE_PASCALSTRING_STATICBUILD_NONULL( \
			outername, text, libandria4_bytebuffer_, uint8_t, str )
	
		/* The variations on void struct are defined in stdbuffer.h */
	typedef struct libandria4_termbuffer_func_voidstruct libandria4_termbuffer_func_voidstruct;
	struct libandria4_termbuffer_func_voidstruct
	{
		uint32_t typeid;
		
			/* Because we obviously will want this, it's standard. */
		int (*err)( libandria4_termbuffer_func_voidstruct*, vt100net_errorstruct* );
	};
			/* The direct return indicates success or failure, nothing else. */
			/*  Positive for success, negative for failure. */
	typedef
		int (*libandria4_termbuffer_func)
		(
			libandria4_termbuffer_generic*,
			
				/* Essentially a set of arguments. Treat it sort of like */
				/*  a printf() formator string. Names are defined below */
				/*  by vt100net_termbuffer_NAMECOMMAND(), but you could */
				/*  always add your own... */
				/* Warning, commands may require the addition of arguments! */
				/* Note that space-separated arguments FOLLOWED by a */
				/*  command (so, RPN style) should be what you universally */
				/*  use, due to ease of parsing. If spaces might be needed */
				/*  INSIDE an argument or command, then enclose in a */
				/*  C-style string (e.g. with double-quotes). This is NOT */
				/*  the place for a complex parser. */
			libandria4_char_pascalarray*,
			
				/* A generic return vector for actual data (as opposed to */
				/*  a success/failure signal). */
			void*
		);
		/* Fetches the contents of a "bounded box". Requires a pointer to a */
		/*  vt100net_termbuffer_func_uint8receiver instance, and the area */
		/*  must be represented as a space-seperated decimal-encoded list */
		/*  of left-x upper-y fetch-width fetch-height encoded as the FRONT */
		/*  (for FORTH-ish RPN convenience) of the command pstr. */
	libandria4_termbuffer_NAMECOMMAND( outername, "fetch" );
	... /* TO BE CONTINUED! We need more commands. */
	
	struct libandria4_termbuffer_generic
	{
			/* Measured in character cells, not in e.g. pixels, or inches. */
		uint32_t width, height;
		
		libandria4_memfuncs_t *mfuncs;
		
		libandria4_bytebuffer_pascalarray *buf;
	};
	
	
	
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
	
		/* Another convenience type. */
	typedef union
	{
		uint8_t bytes[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		libandria4_buffercell_common cells[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		
	} libandria4_buffercell_common_accessor;
	
	
	
	/* Remember: vt100net_termbuffer_func_voidstruct{} is defined in */
	/*  terminal.h */
	
	typedef struct libandria4_termbuffer_func_uint8receiver
	{
		libandria4_termbuffer_func_voidstruct header;
		
		int (*func)( libandria4_termbuffer_func_uint8receiver*, uint8_t );
		
	} libandria4_termbuffer_func_uint8receiver;
	
#endif
/* End libandria4 text stdbuffer.h */

