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

#include "../detect.h"

#if LIBANDRIA4_PRIMITIVE_PLATDET_COMNJUMP_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_COMNJUMP_H
	
	
		/* This is technically already included via platformdetect, but it's */
		/*  good to make things explicit. */
	#include <stdint.h>
	
	
	#undef LIBANDRIA4_JMPBUF_CELLCOUNT
	#if LIBANDRIA4_TARGETPROCESSOR0 == LIBANDRIA4_PROCESSOR0_ISA_x86
		#if LIBANDRIA4_CELLTYPE_SIZE == 2
			#error "Unverified operational size.\n"
			
			/* x86 16-bit. Except that MIGHT NOT be detectable like this. */
			#define LIBANDRIA4_JMPBUF_CELLCOUNT ( ??? )
				/* The float-buf has 1+7 entries (in 16-bit), but the size */
				/*  of each element varies between 16-bit format and 32-bit */
				/*  format, so we use uint16_t as the type universally. */
				/* 1*16 bits for the control word, then 7*16 bits for the */
				/*  float environment without data registers, including a */
				/*  second copy of the control word. Unlike 32+ bit mode, */
				/*  there is no support for the MXCSR register from SSE. */
			#define LIBANDRIA4_FLOATBUF_CELLCOUNT ( 8 )
			
				/* For x86, the register status of x87, including stack */
				/*  registers */
			#define LIBANDRIA4_MATHBUF_OPTCOUNT ( 1 )
				#define LIBANDRIA4_MATHBUF_OPT_x87 ( 0 )
				/* This has the same layout as the *_FLOATBUF_* structure, */
				/*  but with extra data stuck at the end for the actual data */
				/*  registers. */
					/* x87 asm( "fnsave" ) is the 7*16bit control registers, */
					/*  + 40*16bit data registers, so we add the 40 */
					/*  double-bytes to the float-buffer size. */
				#define LIBANDRIA4_MATHBUF_OPTSIZE_x87 ( LIBANDRIA4_FLOATBUF_CELLCOUNT + 40 )
				/* Storage sizes in uint16_s elements, so sizeof()/2. */
			#define LIBANDRIA4_MATHBUF_OPTSIZES \
				(size_t){ LIBANDRIA4_MATHBUF_OPTSIZE_x87 }
			
		#elif LIBANDRIA4_CELLTYPE_SIZE <= 4
			/* x86 32-bit or 64-bit, both are the same size. */
			#define LIBANDRIA4_JMPBUF_CELLCOUNT ( 10 )
				/* The float-buf has 1+1+7 entries (in 32-bit and 64-bit), */
				/*  but the size of the elements varies between 16-bit */
				/*  format and 32-bit format, so we use uint16_t as the */
				/*  type and double the number of entries instead of */
				/*  adjusting the storage size. */
				/* 2*16b SSE config, then 2*16b x87 control word, then 14*16b */
				/*  for ALL x87 non-data registers (including a nulled-out */
				/*  control word). Note that while the control word only is */
				/*  only 8 bits, we'll still be allocating a full 32. */
			#define LIBANDRIA4_FLOATBUF_CELLCOUNT ( 18 )
			
				/* For x86, the register status of x87, MMX, and/or SSE, */
				/*  including stack registers */
			#define LIBANDRIA4_MATHBUF_OPTCOUNT ( 4 )
					/* MMX uses the same registers as x87, so no special */
					/*  buffering for it. */
				#define LIBANDRIA4_MATHBUF_OPT_x87 ( 0 )
				#define LIBANDRIA4_MATHBUF_OPT_SSE ( 1 )
				#define LIBANDRIA4_MATHBUF_OPT_AVX1 ( 2 )
				#define LIBANDRIA4_MATHBUF_OPT_AVX512 ( 3 )
				/* These have the same layout as the *_FLOATBUF_* structure, */
				/*  but with extra data stuck at the end for the actual data */
				/*  registers. */
					/* x87 asm( "fnsave" ) is the 14*16bit control registers, */
					/*  + 40*16bit data registers, so we add the 40 */
					/*  double-bytes to the float-buffer size. */
				#define LIBANDRIA4_MATHBUF_OPTSIZE_x87 \
					( LIBANDRIA4_FLOATBUF_CELLCOUNT + 40 )
					/* asm( "fxsave" ) has a lot of data, + some empty space */
					/*  that I won't use, but also requires 8 bytes, aka 4 */
					/*  uint16_t of padding for alignment. Note that although */
					/*  64-bit adds more registers, the "fxsave" opcode is */
					/*  ALREADY supposed to be given enough data to store */
					/*  them (and STILL have unused space...), so there's no */
					/*  need to allocate more space for storage. */
					/* Verify the alignment of the usage math. */
				#define LIBANDRIA4_MATHBUF_OPTSIZE_SSE \
					( LIBANDRIA4_FLOATBUF_CELLCOUNT + 238 + 4 )
					/* asm( "xsave" ), saving the YMM registers. Note that */
					/*  this must be 64-byte aligned, so we specify 28 units */
					/*  of uint16_t as padding. */
				#define LIBANDRIA4_MATHBUF_OPTSIZE__AVX1 \
					( LIBANDRIA4_FLOATBUF_CELLCOUNT + 402 + 28 )
				#define LIBANDRIA4_MATHBUF_OPTSIZE__AVX512 ( 3 )
				/* Storage sizes in uint16_s elements, so sizeof()/2. */
			#define LIBANDRIA4_MATHBUF_OPTSIZES \
				(size_t){ LIBANDRIA4_MATHBUF_OPTSIZE_x87, \
						LIBANDRIA4_MATHBUF_OPTSIZE_SSE }
			
		#else
			#error "Unsupported cell size.\n"
		#endif
		
	#else
		#error "Unsupported processor family.\n"
	#endif
	
#endif /* End primitive platdet comncell.h */
