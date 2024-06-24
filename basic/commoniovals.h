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

	/* This won't result in an infinit inclusion loop, because all of the */
	/*  includes in commonio.h are wrapped by it's include-guard and thus */
	/*  will only be included once. */
#include "commonio.h"

#ifndef LIBANDRIA4_BASIC_COMMONIOVALS_H
# define LIBANDRIA4_BASIC_COMMONIOVALS_H
	
		/* EOF is 0, because EOF isn't really an error, and ( error * 0 ) */
		/*  should "obviously" be no error at all. */
	const libandria4_commonio_perr libandria4_commoniovals_eof =
		(libandria4_commonio_perr)0;
	
	#define LIBANDRIA4_COMONIOVALS_EOF ( libandria4_commoniovals_eof )
	
#endif
/* End libandria4 basic commoniovals.h */
