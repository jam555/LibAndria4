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

#ifndef LIBANDRIA4_OPERATIONS_H
# define LIBANDRIA4_OPERATIONS_H
	
		/* The math macros that were here have been moved to macwrap_operations.h */
	#include "macwrap_operations.h"
	
	
	/* Note: should convert sketchyLog2 to a macro version. */
		/* This is part of a quick-approximate inverse square root function */
		/*  first made famous by ID software's Quake 3 Arena. It */
		/*  approximates 1.5 * L ( B - tuning_number ) - 0.5 * Inum, where */
		/*  Inum is the result of interpreting the bit pattern of num as an */
		/*  integer instead of a float, B is the "Exponent Bias" and equals */
		/*  127 for 8 bits, and L equals pow( 2, 23 ) for 23 bits. It is */
		/*  optimized for 32-bit IEEE 754-1985 floating-point numbers, but */
		/*  can be adjusted for other floating-point designs. It is used */
		/*  canonically as a first-guess, which then gets refined with */
		/*  Newton's Formula to improve the accuracy of the result, usually */
		/*  with only one pass. Refinement is not used in this */
		/*  implementation. */
		/* This kludge is often associated with John Carmack, but probably */
		/*  dates back to Gary Tarolli for the SGI Indigo, or Greg Walsh & */
		/*  Cleve Moler for Ardent Computer, or William Kahan & K. C. Ng at */
		/*  Berkley. */
	float libandria4_sketchyLog2( float num )
	{
		/* Note: requires num & i to be 32 bits. */
		int32_t i = *( (int32_t*)( &num ) );
		
			/* Classic number is 0x5F3759DF. One below supposedly more */
			/*  accurate. */
		i = 0x5F375A86 - ( i >> 2 );
			/* For 64 bit, try 0x5fe6eb50c7b537a9. */
		
		num = *( (float*)( & i ) );
		return( num );
	}
	
#endif
/* End libandria4 othermath operations.h */
