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

#if LIBANDRIA4_PRIMITIVE_PLATDET_COMPILER_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_COMPILER_H
	
	#include "../platformdetect.h"
	
	
	/* This is just a convenience file, to "purify" the contents of */
	/*  ../platformdetect.h, making it easier to read. It is meant to contain */
	/*  all of the direct-detection logic for compilers, so that later */
	/*  feature-detect code can know what it's dealing with. Notice how it's */
	/*  pretty short? Yeah, that needs to change. At the very least, the Tiny */
	/*  C Compiler and Clang should be fairly easy to detect. */
	/* Note that the actual id macros are defined inside ./predefs.h . */
	
	/* Still need id macros for: */
	/*  Small C. */
	/*  BDS C. */
	/*  Lattice C. */
	/* Except, do we? I think they may now exist. */
	
	/* TRy to support https://github.com/alexfru/SmallerC */
	
	/* Other detect macros: */
	/*  _ACC_ : ACC is not QUITE C. Targets MSDOS. */
	/*  __CMB__ : Altium MicroBlaze C. */
	/*  __CHC__ : Altium C-to-Hardware. */
	/*  __CC_ARM : ARM Compiler.*/
	/*  __CC65__ : cc65, descendent of Small C. Targets 8-bit Atari, 6502, */
	/*    GEOS, Commodore 64 & others, Apple II, Oric Atmos, NES, Watara */
	/*    Supervision, Ohio Scientific Challenger 1P. */
	/*  __DECC or __DECCXX or __VAXC or VAXC : Compaq C/C++. */
	/*  __convexc__ : Convex C. */
	/*  _CRAYC : Cray C. */
	/*  __DCC__ : Diab C/C++. */
	/*  _DICE : Dice C. */
	/*  __DMC__ : Digital Mars C. */
	/*  __SYSC__ : Dignus Systems/C++. */
	/*  __PATHCC__ : EKOPath. */
	/*  __EDG__ : EDG C++ Frontend. */
	/*  __ghs__ : Green Hill C/C++. */
	/*  __HP_cc : HP ANSI C. */
	/*  __HP_aCC : HP aC++. */
	/*  __IAR_SYSTEMS_ICC__ : IAR C/C++. */
	/*  __xlc__ or __xlC__ or __IBMC__ or __IBMCPP__ : IBM XL C/C++. */
	/*  __IBMC__ or __IBMCPP__ : IBM z/OS C/C++. */
	/*  __IMAGECRAFT__ : ImageCraft C. */
	/*  __INTEL_COMPILER or __ICC or __ECC or __ICL : Intel C/C++. */
	/* These need to be used for actual detections. */
	
	
	
	#if defined( __GNUC__ )
		#if defined( __INTEL_COMPILER ) || defined( __ICC ) || defined( __ECC ) || defined( __ICL )
			#warning "Warning: Detected Intel C compiler masquerading as GNU C compiler!"
		#endif
		
		
		#if defined( LIBANDRIA4_COMPILER ) && LIBANDRIA4_COMPILER & ( ~LIBANDRIA4_COMPILER_CODEBASEANTIMASK ) != LIBANDRIA4_COMPILER_CODEBASE_GNU
			#error "Error: Libandria4 platformdetect.h LIBANDRIA4_COMPILER"
			#error " already had a non-null value when detecting GNU C compiler."
		#else
			#ifdef LIBANDRIA4_COMPILER
				#undef LIBANDRIA4_COMPILER
			#endif
			#define LIBANDRIA4_COMPILER LIBANDRIA4_COMPILER_CODEBASE_GNU
		#endif
	#endif
	
		/* This might not actually detect the earliest Microsoft C compilers. */
		/*  Supposedly versions before 3.0 might register as Lattice C */
		/*  instead, as Microsoft apparently licensed that codebase. */
	#if defined( _MSC_VER )
		#if defined( LIBANDRIA4_COMPILER ) && LIBANDRIA4_COMPILER & ( ~LIBANDRIA4_COMPILER_CODEBASEANTIMASK ) != LIBANDRIA4_COMPILER_CODEBASE_MSVC
			#error "Error: Libandria4 platformdetect.h LIBANDRIA4_COMPILER"
			#error " already had a non-null value when detecting Microsoft C compiler."
		#else
			#ifdef LIBANDRIA4_COMPILER
				#undef LIBANDRIA4_COMPILER
			#endif
			#define LIBANDRIA4_COMPILER LIBANDRIA4_COMPILER_CODEBASE_MSVC
		#endif
	#endif
	
#endif /* End primitive platdet platform.h */
