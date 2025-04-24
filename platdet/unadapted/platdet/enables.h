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

#if LIBANDRIA4_PRIMITIVE_PLATDET_ENABLES_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_ENABLES_H
	
	#include "../platformdetect.h"
	
	
	/* This file is just for feature-enabling macros. It needs further */
	/*  research, but at least gnu's libc supports the one below. Also, look */
	/*  in ../commonlib.c (or .h?) for anything usage that probably should */
	/*  move here. */
	
	#if ( LIBANDRIA4_PLATFORMPREVIEW0 == LIBANDRIA4_PLATFORM0_NIX ) && ( LIBANDRIA4_COMPILER & ( ~LIBANDRIA4_COMPILER_CODEBASEANTIMASK ) != LIBANDRIA4_COMPILER_CODEBASE_GNU )
			/* This is some weird thing that might be GNU specific, or */
			/*  might not. You define some mix of _POSIX_VERSION, */
			/*  _POSIX_C_SOURCE, _XOPEN_SOURCE, etc., to enable extra */
			/*  features in system headers. Some will cause the others to be */
			/*  defined as well. */
		#define _POSIX_C_VERSION 200112L
		#warning "Warning: Defining POSIX C version macro. This needs to allow an override to be specified."
	#endif
	
#endif /* End primitive platdet enables.h */
