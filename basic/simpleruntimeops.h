/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2024 Jared A. Maddox

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

#ifndef LIBANDRIA4_BASIC_SIMPLERUNTIMEOPS_H
# define LIBANDRIA4_BASIC_SIMPLERUNTIMEOPS_H
	
	#include "stdmaybes.h"
	
	
	
	/* The following are indirection function/data pairs, for when that's */
	/*  useful (specifically designed for the */
		/* LIBANDRIA4_OP_RUNifABLE num _ELSE letter () */
	/*  macros defined in simpleops.h). */
	
	typedef struct libandria4_op_indirfunc_int_voidp_valist_data
	{
		int (*func)( void*, va_list* );
		void *data;
		
	} libandria4_op_indirfunc_int_voidp_valist_data;
	int libandria4_op_indirfunc_int_voidp( void *dat_, ... );
	
	
	
	/* The functions below all need to be transformed to a */
	/*  libandria4_op_* format, for better namespacing. */
	
		/* offset is an offset within the set of integers available through argi. */
		/* len is the number of integers available through argi.  */
		/* Returns "nothing" on error, else returns an integer. */
	libandria4_maybeint libandria4_op_returnint_Nth_valist( size_t offset,  size_t len, va_list *argi );
		/* recv must be the name of an already-existing libandria4_maybeint{}. */
		/* vaname must be the name of an already-existint va_list. */
		/* refarg is just the last named argument before the list of arguments to choose from. */
		/* All other arguments are the same as for libandria4_returnint_Nth_valist(). */
	#define libandria4_op_returnint_GENERICBODY( recv, offset,  vaname, len, refarg ) \
		{ va_start( argi, refarg ); \
				(recv) = libandria4_op_returnint_Nth_valist( offset,  len, &( vaname ) ); \
			va_end( vaname ); }
	#define libandria4_op_returnint_BUILD_GENERICFUNC( name, numeric_offset ) \
		libandria4_maybeint (name)( size_t len, ... ) { \
			va_list argi; libandria4_maybeint res; \
			libandria4_op_returnint_GENERICBODY( res, (offset),  argi, len, len ); \
			return( res ); }
	
		/* This, and the other similar functions below, use */
		/*  libandria4_op_returnint_Nth_valist(), and give it their size_t as */
		/*  it's SECOND size_t: their names indicate the offset value. */
	libandria4_maybeint libandria4_op_returnint_1st( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_2nd( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_3rd( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_4th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_5th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_6th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_7th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_8th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_9th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_10th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_11th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_12th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_13th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_14th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_15th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_16th( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_17th( size_t, ... );
		/* Same arguments as libandria4_op_returnint_Nth_valist(), except this */
		/*  uses var-args instead of va_list*. */
	libandria4_maybeint libandria4_op_returnint_Nth( size_t,  size_t, ... );
	
	
	
		/* As a special case, this JUST returns "nothing". */
	libandria4_maybeint libandria4_op_returnint_0( size_t, ... );
		/* This, and the other similar functions below, use */
		/*  libandria4_op_returnint_Nth_valist(), and give it their size_t as */
		/*  it's SECOND size_t: their names indicate the offset value, */
		/*  though a 1 is universally subtracted. */
	libandria4_maybeint libandria4_op_returnint_1( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_2( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_3( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_4( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_5( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_6( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_7( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_8( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_9( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_10( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_11( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_12( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_13( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_14( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_15( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_16( size_t, ... );
	libandria4_maybeint libandria4_op_returnint_17( size_t, ... );
	
#endif
/* End libandria4 basic simpleruntimeops.h */
