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

#ifndef LIBANDRIA4_PLATDET_PLATFORMDETECT_H
# define LIBANDRIA4_PLATDET_PLATFORMDETECT_H
	/* Note that if these include guards change, then so too must those in */
	/*  detect.h */
	
	/**************************************************************************/
	/**************************************************************************/
	/** WARNING! From here until a comment specifying otherwise, there must ***/
	/**  be NO inclusions of other files, due to the need to specify feature **/
	/**  enabling macros for GNU Libc. ****************************************/
	/**************************************************************************/
	/**************************************************************************/
	
	/* Note that to make this file easier to read, I'm in the middle of */
	/*  ignoring the note above! Yay! */
	
	
	
	/* Here's a list of defines that can be used as switches! */
		/* LIBANDRIA4_MACROSWITCHES_NO_LARGE_FILES */
		/* LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_NIX */
		/* LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_MSWIN */
		/* LIBANDRIA4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM */
	
	/* To use platform detection, compare LIBANDRIA4_PLATFORM0 to the */
	/*  LIBANDRIA4_PLATFORM0_* values. LIBANDRIA4_PLATFORM1 is not currently used, but */
	/*  is reserved for JUST IN CASE we want to support more than than 15 */
	/*  platforms. */
	/* Alternatively, compare LIBANDRIA4_TARGETPLATFORM to the */
	/*  LIBANDRIA4_TARGETPLATFORM_* values. */
	
	/* To use compiler detection, "and" LIBANDRIA4_COMPILER with */
	/*  LIBANDRIA4_COMPILER_ERAMASK (for the compiler's approximate time period) */
	/*  to compare with the LIBANDRIA4_COMPILER_ERA_* values, or "and" */
	/*  LIBANDRIA4_COMPILER with ~(LIBANDRIA4_COMPILER_ERAMASK) to compare with the */
	/*  LIBANDRIA4_COMPILER_CODEBASE_* values. */
	
	/* We currently don't distinguish OS variants, such as Windows CE. That */
	/*  should be changed in the future. */
	
	/* We currently don't detect platform architecture (e.g. x86 vs 68k, or */
	/*  Tandy vs IBM). We should change that in the future. */
		/* Here's two relevant macros: __i386__  __x86_64__ */
	
	/* To use pointer-size detection, look at LIBANDRIA4_CELLTYPE_KNOWN (a boolean */
	/*  flag) to determine whether the other macros in the set are even valid, */
	/*  LIBANDRIA4_CELLTYPE_SIZE for the size of a generic data-cell (which is */
	/*  defined elsewhere), LIBANDRIA4_CELLTYPE_DPTRSIZE for the size of a data */
	/*  pointer, LIBANDRIA4_CELLTYPE_FPTRSIZE for the size of a function pointer, */
	/*  LIBANDRIA4_CELLTYPE_INTSIZE for the size of a "native" integer, and */
	/*  LIBANDRIA4_CELLTYPE_REGSIZE for the size of a "normal" register: all sizes */
	/*  are in multiples of a char, so the total number of bits is the size macro */
	/*  multiplied by CHAR_BIT. */
	
	/* We probably want a "feature detect" file too, to do things like */
	/*  detect if signals are relevant to the target. */
	
	
	
	#include "platdet/predefs.h"
	
	
		/* Prepare for target-platform detection. */
	#ifdef LIBANDRIA4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM
	# define LIBANDRIA4_TARGETPLATFORM -1
	#else
	# define LIBANDRIA4_TARGETPLATFORM 0
	#endif
	
	
	#include "platdet/compiler.h"
	
	
		/* The final stage: time to merge era and compiler together. */
	#if defined( LIBANDRIA4_COMPILER )
		#if LIBANDRIA4_COMPILER & ( ~LIBANDRIA4_COMPILER_CODEBASEANTIMASK ) != LIBANDRIA4_COMPILER_CODEBASE_GNU
			#undef LIBANDRIA4_COMPILER
			#define LIBANDRIA4_COMPILER ( LIBANDRIA4_COMPILER_CODEBASE_GNU | LIBANDRIA4_COMPILER_ERA )
		#elif LIBANDRIA4_COMPILER & ( ~LIBANDRIA4_COMPILER_CODEBASEANTIMASK ) != LIBANDRIA4_COMPILER_CODEBASE_MSVC
			#undef LIBANDRIA4_COMPILER
			#define LIBANDRIA4_COMPILER ( LIBANDRIA4_COMPILER_CODEBASE_MSVC | LIBANDRIA4_COMPILER_ERA )
		#else
		#endif
	#endif
	
	
	
	#include "platdet/proc.h"
	
	
	
	#include "platdet/platform.h"
	
	
	
	/*************************************************************************/
	/*************************************************************************/
	/** WARNING! Only override files may be included from here onwards, and **/
	/**  they MUST NOT contain includes of any system files, lest conflicts **/
	/**  with e.g. Posix feature-enable macros occur. ************************/
	/*************************************************************************/
	/*************************************************************************/
	
	
	
	/* This is the proper area to perform any override inclusions that might */
	/*  activate feature-control macros. */
	
	#include "platdet/enables.h"
	
	
	
	/***********************************************************************/
	/***********************************************************************/
	/** ATTENTION! From here forwards, any desired files may be included. **/
	/***********************************************************************/
	/***********************************************************************/
	
	
	
	/* Platform detection. When this is run, it should not only detect the */
	/*  general operating system & big-file support, but also indicate the */
	/*  size of the big-file support, and set some CUSTOM macros that */
	/*  specify THE VERSION of the operating system. None of which do any of */
	/*  these currently do. */
	#include "platdet/plat2.h"
	
	
	
	/* Set the actual feature -test / -detect macros. */
	/* Note that TCC, GCC, Clang, and MSVC all use the same approach, which */
	/*  includes <stdint.h>: this may confuse error detection at some later */
	/*  point. */
	#if \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_LLVM )
		/* Supported: */
			/* __GNUC__ : GCC C/C++. */
			/* __llvm__ and/or __clang__ : LLVM C / Clang. */
		
		#if __STDC_VERSION__ >= 199901L
			
			/* These are enough to define the *CELL* macros for the normal modern compilers. */
			#include "platdet/undefcel.h"
			#include "platdet/calccell.h"
			#include "platdet/comncell.h"
			
			#include "platdet/comnjump.h"
			
			#warning "Some systems in LibAndria4 require threads, figure out which compiler versions don't support them.\n"
		#else
			#error "Unknown C support level in platformdetect.h .\n"
		#endif
		
	#elif \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_MSVC )
		/* Supported: */
			/* _MSC_VER : MSVC. */
		
		#if __STDC_VERSION__ >= 199901L
			
			/* These are enough to define the *CELL* macros for the normal modern compilers. */
			#include "platdet/undefcel.h"
			#include "platdet/calccell.h"
			#include "platdet/comncell.h"
			
			#include "platdet/comnjump.h"
			
			#warning "Some systems in LibAndria4 require threads, figure out which compiler versions don't support them.\n"
		#else
			#error "Unknown C support level in platformdetect.h .\n"
		#endif
		
	#elif \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_TCC )
		/* Supported: */
			/* __TINYC__ : Tiny C Compiler. */
		
		#if __STDC_VERSION__ >= 199901L
			
			/* These are enough to define the *CELL* macros for the normal modern compilers. */
			#include "platdet/undefcel.h"
			#include "platdet/calccell.h"
			#include "platdet/comncell.h"
			
			#include "platdet/comnjump.h"
			
			#warning "TCC isn't known to support threads, but some systems in LibAndria4 require threads.\n"
		#else
			#error "Unknown C support level in platformdetect.h .\n"
		#endif
		
		
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_COMEAU
		/* __COMO__ : Comeau C++. */
		/* Support for this should eventually be attempted. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support the Comeau C compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_DJGPP
		/*  __DJGPP__ or __GO32__ : DJGPP. For MSDOS. */
		/* Support for this should eventually be attempted. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support the DJGPP compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_WATCOM
		/* __WATCOMC__ : Watcom / OpenWatcom C/C++. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support the Watcom opr OpenWatcom compiler.\n"
		
		
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_BORLAND
		/* __TURBOC__ : Borland Turbo C. */
		/* __BORLANDC__ or __CODEGEARC__ : Borland / CodeGear / Embarcadero */
		/*  C++ Builder. Versions have targeted MSWindows, Linux, Solaris, */
		/*  OS X, iOS, and Android. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_PCC
		/* __PCC__ : Portable C Compiler. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_LCC
		/* __LCC__ : LCC. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_SDCC
		/* SDCC : Small Device C Compiler. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_ACK
		/* __ACK__ : Amsterdam Compiler Kit. For MINIX, multiple processors. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_BDS
		/* "Brain Damage Software" C Compiler. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_OPEN64
		/* __OPEN64__ or __OPENCC__ : Open64. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_AZTECC
		/* AZTEC_C or __AZTEC_C__ : Aztec C. For MSDOS, Apple II DOS 3.3 & */
		/*  ProDOS, Commodore 64, early Macs, CP/M-80, Amiga, & Atari ST. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_NORCROFTC
		/* __CC_NORCROFT : Norcroft C. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#elif ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_TENDRAC
		/* __TenDRA__ : TenDRA C/C++. */
		
		#error "LibAndria4 platformdetect.h doesn't yet support this compiler.\n"
		
	#else
		#error "Unknown compiler.\n"
		
	#endif
	
	
	
	/* Some additional stuff has moved to platformsupport.h. */
	
#endif
/* End libandria4 basic platformdetect.h */
