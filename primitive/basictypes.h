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

#ifndef LIBANDRIA4_PRIMITIVE_BASICTYPES_H
# define LIBANDRIA4_PRIMITIVE_BASICTYPES_H
	
	/* This is basictypes.h. It exists for the sake of easier debugging */
	/*  compared to commontypes.h, due to less stuff being included in it, */
	/*  though it should be a quicker read too. */
	/* Note that in many cases you'll want to use the typedefs in */
		/* ../abbrevs/basictypes.h */
	/*  instead of anything directly named here. */
	
	#include <stdint.h>
	
	/* TODO: Everything in this file should get a type descriptor. Use a */
	/*  secondary set of include-guards to allow them to only appear where */
	/*  it makes sense. Look in stdmaybes.h to see how to design these */
	/*  include-guards. */
	/* TODO: Move the extent-macros at the end to their own file. Maybe a */
	/*  shared one with commontypes.h? */
	
	/* TODO: Any "release" version should ideally move all names in */
	/*  basictypes.h and commontypes.h over to the basic */
		/* "libandria4_common_ underscoreless-description */
		/*  underscore-if-functiontype return-if-functiontype" */
	/*  format used for this function-pointer type. Any shorter names should */
	/*  be listed in relevant /abbrevs/basictypes.h (or similar) files. */
	typedef void (*libandria4_common_voidfuncp_void)();
	
	
	#if __INTELLISENSE__
		#include <BaseTsd.h>
		typedef SSIZE_T libandria4_common_ssize;
	#else
		#include <sys/types.h>
		typedef ssize_t libandria4_common_ssize;
	#endif
	
	
	/* Note that these all HAD "commonio" instead of "common". */
	typedef uint8_t libandria4_common_byte;
	typedef uint32_t libandria4_common_succ;
	typedef uint32_t libandria4_common_err;
		/* This had the secondary name "libandria4_error_errint". */
	typedef uintptr_t libandria4_common_perr;
	
	
	typedef int (*libandria4_common_putcharfuncp_int)( void*, char );
	
	
	/* Note that most of the contents of this file have moved to commontypes.h */
	
	
	
	#define LIBANDRIA4_COMMONIO_BYTE_MIN 0
	#define LIBANDRIA4_COMMONIO_BYTE_MAX UINT8_MAX
	
	#define LIBANDRIA4_COMMONIO_SUCC_MIN 0
	#define LIBANDRIA4_COMMONIO_SUCC_MAX UINT32_MAX
	
	#define LIBANDRIA4_COMMONIO_ERR_MIN 0
	#define LIBANDRIA4_COMMONIO_ERR_MAX UINT32_MAX
	
	#define LIBANDRIA4_COMMONIO_PERR_MIN 0
	#define LIBANDRIA4_COMMONIO_PERR_MAX UINTPTR_MAX
	
#endif
/* End libandria4 primitive basictypes.h */
