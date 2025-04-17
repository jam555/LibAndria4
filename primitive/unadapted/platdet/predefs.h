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

#if LIBANDRIA4_PRIMITIVE_PLATDET_PREDEFS_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_PREDEFS_H
	
	#include "../platformdetect.h"
	
	
	#define LIBANDRIA4_PLATFORMPREVIEW0 0
	#define LIBANDRIA4_PLATFORM0 0
	
	#define LIBANDRIA4_PLATFORM0_NIX 1
	#define LIBANDRIA4_PLATFORM0_DOS 2
	#define LIBANDRIA4_PLATFORM0_MSWIN 4
	#define LIBANDRIA4_PLATFORM0_ATARIOS 8
	#define LIBANDRIA4_PLATFORM0_COMMODOREOS 16
	#define LIBANDRIA4_PLATFORM0_CPM 32
	#define LIBANDRIA4_PLATFORM0_IBMPCBIOS 64
	
	#define LIBANDRIA4_PLATFORM0_OVERFLOW 32768
		/* Note: no values over 32768! Must support 16-bit ints! */
	
	#define LIBANDRIA4_PLATFORM1 0
	
		/* For the platform defines below, the values correspond to the bit */
		/*  index of the LIBANDRIA4_PLATFORM* values above, + 1. So e.g. the value */
		/*  "3" would correspond to LIBANDRIA4_PLATFORM0's "4" value, while the */
		/*  value "4" would correspond to LIBANDRIA4_PLATFORM0's "8" value, and */
		/*  the value "17" would correspond to LIBANDRIA4_PLATFORM1's "1" value. */
	#define LIBANDRIA4_TARGETPLATFORM_NIX 1
	#define LIBANDRIA4_TARGETPLATFORM_DOS 2
	#define LIBANDRIA4_TARGETPLATFORM_MSWIN 3
	#define LIBANDRIA4_TARGETPLATFORM_ATARIOS 4
	#define LIBANDRIA4_TARGETPLATFORM_COMMODOREOS 5
	#define LIBANDRIA4_TARGETPLATFORM_CPM 6
	#define LIBANDRIA4_TARGETPLATFORM_IBMPCBIOS 7
	
	
	#define LIBANDRIA4_JMPBUF_CELLCOUNT \
		#error "LIBANDRIA4_JMPBUF_CELLCOUNT has not been defined.\n"
	
	
		/* This essentially says whether we've detected a type for intptr_t or */
		/*  uintptr_t. It's essentially used to figure out things like what size */
		/*  processor registers are, as pointer-size is USUALLY a match to the */
		/*  "native size" of a particular execution mode, such as 16-bit x86, */
		/*  64-bit arm, or 32-bit 68k. Beware that some platforms and memory */
		/*  models (e.g. "small" DOS memory models) DO NOT follow that pattern. */
	#define LIBANDRIA4_CELLTYPE_KNOWN ( 0 )
		#define LIBANDRIA4_CELLTYPE_TYPE \
			#error "LIBANDRIA4_CELLTYPE_TYPE has not been defined.\n"
			/* The number of char per data cell. Data cell type defined elsewhere. */
		#define LIBANDRIA4_CELLTYPE_SIZE \
			#error "LIBANDRIA4_CELLTYPE_SIZE has not been defined.\n"
			/* The number of char per data pointer. */
		#define LIBANDRIA4_CELLTYPE_DPTRSIZE \
			#error "LIBANDRIA4_CELLTYPE_DPTRSIZE has not been defined.\n"
			/* The number of char per function pointer. */
		#define LIBANDRIA4_CELLTYPE_FPTRSIZE \
			#error "LIBANDRIA4_CELLTYPE_FPTRSIZE has not been defined.\n"
			/* The number of char per "native" integer. */
		#define LIBANDRIA4_CELLTYPE_INTSIZE \
			#error "LIBANDRIA4_CELLTYPE_INTSIZE has not been defined.\n"
			/* The number of char per "common" register. */
		#define LIBANDRIA4_CELLTYPE_REGSIZE \
			#error "LIBANDRIA4_CELLTYPE_REGSIZE has not been defined.\n"
	
	
	#define LIBANDRIA4_BIGFILES_SEEK 0
	
	
		/* This value needs to be built by detection logic to contain an */
		/*  era, and a codebase. Other macros should then be set to nail */
		/*  down any interesting quirks. */
	#define LIBANDRIA4_COMPILER 0
	
	#define LIBANDRIA4_COMPILER_ERAMASK 31
	#define LIBANDRIA4_COMPILER_ERA_CURRENT 0
	#define LIBANDRIA4_COMPILER_ERA_1970S 1
	#define LIBANDRIA4_COMPILER_ERA_1980S 2
	#define LIBANDRIA4_COMPILER_ERA_1990S 3
	#define LIBANDRIA4_COMPILER_ERA_2000S 4
	#define LIBANDRIA4_COMPILER_ERA_2010S 5
	#define LIBANDRIA4_COMPILER_ERA_2020S 6
	#define LIBANDRIA4_COMPILER_ERA_OVERFLOWED LIBANDRIA4_COMPILER_ERAMASK
		/* This should be set in lock-step with ( LIBANDRIA4_COMPILER & */
		/*  LIBANDRIA4_COMPILER_ERAMASK ), unless the value is 31 or above. Note */
		/*  that if value is "0", then it actually just hasn't been set. */
		/* This is a lazy hack, we should really detect language era here. */
	#define LIBANDRIA4_COMPILER_ERA LIBANDRIA4_COMPILER_ERA_CURRENT
	
	#define LIBANDRIA4_COMPILER_CODEBASEANTIMASK LIBANDRIA4_COMPILER_ERAMASK
	#define LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER ( LIBANDRIA4_COMPILER_CODEBASEANTIMASK + 1 )
		/* __TINYC__ : Tiny C Compiler. */
	#define LIBANDRIA4_COMPILER_CODEBASE_TCC ( 0 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __GNUC__ : GCC C/C++. */
	#define LIBANDRIA4_COMPILER_CODEBASE_GNU ( 1 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __llvm__ and/or __clang__ : LLVM C / Clang. */
	#define LIBANDRIA4_COMPILER_CODEBASE_LLVM ( 2 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* _MSC_VER : MSVC. */
	#define LIBANDRIA4_COMPILER_CODEBASE_MSVC ( 3 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __TURBOC__ : Borland Turbo C. */
		/* __BORLANDC__ or __CODEGEARC__ : Borland / CodeGear / Embarcadero */
		/*  C++ Builder. Versions have targeted MSWindows, Linux, Solaris, */
		/*  OS X, iOS, and Android. */
	#define LIBANDRIA4_COMPILER_CODEBASE_BORLAND ( 4 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __WATCOMC__ : Watcom / OpenWatcom C/C++. */
	#define LIBANDRIA4_COMPILER_CODEBASE_WATCOM ( 5 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __PCC__ : Portable C Compiler. */
	#define LIBANDRIA4_COMPILER_CODEBASE_PCC ( 6 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __LCC__ : LCC. */
	#define LIBANDRIA4_COMPILER_CODEBASE_LCC ( 7 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* SDCC : Small Device C Compiler. */
	#define LIBANDRIA4_COMPILER_CODEBASE_SDCC ( 8 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
	#define LIBANDRIA4_COMPILER_CODEBASE_SMALLC ( 9 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __ACK__ : Amsterdam Compiler Kit. For MINIX, multiple processors. */
	#define LIBANDRIA4_COMPILER_CODEBASE_ACK ( 10 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* "Brain Damage Software" C Compiler. */
	#define LIBANDRIA4_COMPILER_CODEBASE_BDS ( 11 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
	#define LIBANDRIA4_COMPILER_CODEBASE_LATTICEC ( 12 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __OPEN64__ or __OPENCC__ : Open64. */
	#define LIBANDRIA4_COMPILER_CODEBASE_OPEN64 ( 13 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* AZTEC_C or __AZTEC_C__ : Aztec C. For MSDOS, Apple II DOS 3.3 & */
		/*  ProDOS, Commodore 64, early Macs, CP/M-80, Amiga, & Atari ST. */
	#define LIBANDRIA4_COMPILER_CODEBASE_AZTECC ( 14 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __CC_NORCROFT : Norcroft C. */
	#define LIBANDRIA4_COMPILER_CODEBASE_NORCROFTC ( 15 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __TenDRA__ : TenDRA C/C++. */
	#define LIBANDRIA4_COMPILER_CODEBASE_TENDRAC ( 16 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* __COMO__ : Comeau C++. */
	#define LIBANDRIA4_COMPILER_CODEBASE_COMEAU ( 17 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/*  __DJGPP__ or __GO32__ : DJGPP. For MSDOS. */
	#define LIBANDRIA4_COMPILER_CODEBASE_DJGPP ( 18 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* Note: Highest allowable value is 65504! Not that anyone should */
		/*  reach that. */
	
#endif /* End primitive platdet predefs.h */
