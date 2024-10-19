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

#ifndef LIBANDRIA4_BASIC_COMMONLIB_H
# define LIBANDRIA4_BASIC_COMMONLIB_H
	
	
	/* TODO: */
		/* Add more time functions. */
	
	
		/* For size_t. */
	#include <stddef.h>
		/* For uintprt_t and uint32_t. */
	#include <stdint.h>
		/* For libandria4_ptrresult{} and libandria4_errno_2result(). */
	#include "stdmonads.h"
		/* For libandria4_error_mayerr{}. */
	#include "commonerr.h"
	
	
	
		/* This literally just exists to waste a very small amount of time. */
		/*  It's implemented in commonlib2.h to stop it from being optimized */
		/*  into oblivion. */
	int libandria4_timesink( int dummy );
	
	
	
		/* Works like C's strstr(), but with arbitrary memory patterns. */
		/* Note that the "needle" will only be searched for on */
		/*  needlegrain-sized alignments: this is to allow arbitrarily sized */
		/*  type searches to be performed. */
		/* The only errors that will be returned are */
			/* LIBANDRIA4_RESULT_FAILURE_DOMAIN and */
			/* LIBANDRIA4_RESULT_FAILURE_EOF. */
		/*  DOMAIN will always mean that the needle size isn't an integer */
		/*  multiple of the needle grain, while EOF will always mean  that */
		/*  the needle wasn't found for some reason (note that null pointers */
		/*  are also included: check explicitly if you care). */
	libandria4_ptrresult libandria4_memmem
	(
		void *haystack_, size_t haysize,
		void *needle_, size_t needlesize, size_t needlegrain
	);
	
		/* Reverses the order of the elements in the memory buffer. "size" */
		/*  is the size of the elements, while "count" is how many of them */
		/*  exist. */
	int libandria4_memreverse( void *base_, size_t count, size_t size );
	
		/* Waits for AT LEAST the provided number of milliseconds. */
	libandria4_error_mayerr libandria4_sleep( uint32_t millisecs );
	
#endif
/* End libandria4 basic commonlib.h */
