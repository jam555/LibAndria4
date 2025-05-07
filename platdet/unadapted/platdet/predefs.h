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
		#define LIBANDRIA4_FLOATTYPE_SIZE \
			#error "LIBANDRIA4_FLOATTYPE_SIZE has not been defined.\n"
		#define LIBANDRIA4_LFLOATTYPE_SIZE \
			#error "LIBANDRIA4_LFLOATTYPE_SIZE has not been defined.\n"
		#define LIBANDRIA4_LLFLOATTYPE_SIZE \
			#error "LIBANDRIA4_LLFLOATTYPE_SIZE has not been defined.\n"
		#define LIBANDRIA4_FLOATTYPE_TYPE \
			#error "LIBANDRIA4_FLOATTYPE_TYPE has not been defined.\n"
		#define LIBANDRIA4_LFLOATTYPE_TYPE \
			#error "LIBANDRIA4_LFLOATTYPE_TYPE has not been defined.\n"
		#define LIBANDRIA4_LLFLOATTYPE_TYPE \
			#error "LIBANDRIA4_LLFLOATTYPE_TYPE has not been defined.\n"
	
	
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
	#define LIBANDRIA4_COMPILER_ERA_2030S 7
	#define LIBANDRIA4_COMPILER_ERA_OVERFLOWED LIBANDRIA4_COMPILER_ERAMASK
		/* This should be set in lock-step with ( LIBANDRIA4_COMPILER & */
		/*  LIBANDRIA4_COMPILER_ERAMASK ), unless the value is 31 or above. Note */
		/*  that if value is "0", then it actually just hasn't been set. */
		/* This is a lazy hack, we should really detect language era here. */
	#define LIBANDRIA4_COMPILER_ERA LIBANDRIA4_COMPILER_ERA_CURRENT
	
	#define LIBANDRIA4_COMPILER_CODEBASEANTIMASK LIBANDRIA4_COMPILER_ERAMASK
	#define LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER ( LIBANDRIA4_COMPILER_CODEBASEANTIMASK + 1 )
	
	#define LIBANDRIA4_COMPILER_IS_CODEBASE( ref ) \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
			( ( ref ) * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER ) )
	#define LIBANDRIA4_COMPILER_IS_ERA( ref ) \
		( ( LIBANDRIA4_COMPILER & LIBANDRIA4_COMPILER_ERAMASK ) == ( ref ) )
	
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
		/*  __DMC__ : Digital Mars C, maybe C++. They're the folks that do "D". */
	#define LIBANDRIA4_COMPILER_CODEBASE_DIGIMARS ( 19 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
		/* Note: Highest allowable value is 65504! Not that anyone should */
		/*  reach that. */
	
	
	
	/* For all of these, "0" means "undefined/unspecified/error". For *_PROCESSOR* 0 & */
	/*  1, the sequential ordering of numbers "2" and above have no actual meaning */
	/*  beyond distinguishing one group from another group. */
		/* For *_PROCESSOR0, the sequential ordering of "1" and "2" aren't directly */
		/*  meaningful, they indicate only that the two processor categories are */
		/*  majorly different from each other... excepting, of course, that "1" and */
		/*  "2" are intentionally allocated to the Intel 4004 and 8008 for historical */
		/*  reasons. */
		/* It is worth noting that some machine types, such as 68k and ColdFire, or */
		/*  8080 and x86, might be EXPECTED to share the same *_PROCESSOR0 value, but */
		/*  actually MUST have seperate values, because despite their common heritage */
		/*  they actually are meaningfully incompatible with each other's byte-code. */
	#define LIBANDRIA4_PROCESSOR0 0
	/* For all the rest of these, 1 means "founder" (such as the 6502, 8080, */
	/*  8086/8088, or 68000), "2"+ means "successor". */
		/* Used to distinguish major variant lines of the *_PROCESSOR0 architectures, */
		/*  e.g. the 80186 from normal x86 processors, or the z80 from it's */
		/*  half-sibling 8085. */
	#define LIBANDRIA4_PROCESSOR1 0
		/* Used to distinguish secondary variations, such as the 80286 from the */
		/*  80386, or the 8080 (as the "1" machine) from it's descendants (the 8085 */
		/*  and/or z80 & descendants). Unlike *_PROCESSOR* 0 & 1, the sequential */
		/*  ordering of "1"+ is meant to be DIRECTLY informative, indicating a direct */
		/*  progression of features. As a result, features that are not reliably */
		/*  present in all members of multiple later "generations" of designs MUST NOT */
		/*  be represented in *_PROCESSOR2... and if a feature suddenly becomes */
		/*  unreliably present instead of reliably existing or disappearing, then that */
		/*  is a major problem, which MUST be represented by either: */
			/* 1) (desirable) producing new values of *_PROCESSOR1 to represent this */
			/*  break, or */
			/* 2) producing a new *_PROCESSOR2 value and creating a *_PROCESSOR3 to */
			/*  represent further development of reliable features. */
	#define LIBANDRIA4_PROCESSOR2 0
	/* Note that UNRELIABLE FEATURES should be represented by machine-specific flags. */
	
	/* These use the same values as the *_PROCESSOR* macros, but speak of the target. */
	#define LIBANDRIA4_TARGETPROCESSOR0 0
	#define LIBANDRIA4_TARGETPROCESSOR1 0
	#define LIBANDRIA4_TARGETPROCESSOR2 0
	
	
	#define LIBANDRIA4_PROCESSOR0_ERAMASK 1
	#define LIBANDRIA4_PROCESSOR0_ERAMULT 2
		/* The "older" ttl-logic processor implementations... and stuff like BMOW. */
	#define LIBANDRIA4_PROCESSOR0_ERA_INSTITUTIONAL 0
		/* Begins with the Intel 4004, and ONLY includes processors that first REACHED */
		/*  the general populace as Medium-Scale Integration chip implementations */
		/*  instead of Standard Logic, discrete transistors, or other low-density */
		/*  approaches. Thus, the OLDEST generally agreed member of this group is the */
		/*  Intel 4004. The 4004 is choosen because it was the first single-chip */
		/*  maximally-general-purpose CPU available for purchase: even classified */
		/*  predecessors were either multi-chip, or could only be programmed at their */
		/*  manufacturing facility. The 8008 might be argued to be a better candidate, */
		/*  but it was ALSO from Intel... */
	#define LIBANDRIA4_PROCESSOR0_ERA_POPULIS 1
	
	#define LIBANDRIA4_PROCESSOR0_ERAINSTITUTIONAL( val ) \
		( ( ( val ) * LIBANDRIA4_PROCESSOR0_ERAMULT ) | \
			LIBANDRIA4_PROCESSOR0_ERA_INSTITUTIONAL )
	#define LIBANDRIA4_PROCESSOR0_ERAPOPULIS( val ) \
		( ( ( val ) * LIBANDRIA4_PROCESSOR0_ERAMULT ) | \
			LIBANDRIA4_PROCESSOR0_ERA_POPULIS )
	
	
	#define LIBANDRIA4_PROCESSOR0_ISA_UNKNOWN 0
		/* I'd be surprised if anything that runs on a 4004 or 8008 can even process */
		/* this file. */
	#define LIBANDRIA4_PROCESSOR0_ISA_Intel4004 LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 1 ) /* 1971 */
	#define LIBANDRIA4_PROCESSOR0_ISA_Intel8008 LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 2 ) /* 1972 */
	
	/* Now, the ones somewhat worth taking seriously. */
		/* Note that the Intel 8080, 8085, z80, and other descendants, must be */
		/*  distinguished through *_PROCESSOR1 (8085==2, z80==3). */
	#define LIBANDRIA4_PROCESSOR0_ISA_8080 LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 3 ) /* 1974 */
	#define LIBANDRIA4_PROCESSOR0_ISA_6800 LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 4 ) /* 1974 */
	#define LIBANDRIA4_PROCESSOR0_ISA_6502 LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 5 ) /* 1975 */
		/* *_PROCESSOR1: common x86==2, 80186==3. */
	#define LIBANDRIA4_PROCESSOR0_ISA_x86 LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 6 ) /* 1978 */
	#define LIBANDRIA4_PROCESSOR0_ISA_68k LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 7 ) /* 1979 */
	#define LIBANDRIA4_PROCESSOR0_ISA_MIPS LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 8 ) /* 1985 */
	#define LIBANDRIA4_PROCESSOR0_ISA_ARM LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 9 ) /* 1985 */
	#define LIBANDRIA4_PROCESSOR0_ISA_SPARC LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 10 ) /* 1987 */
		/* Originally & mostly IBM. */
	#define LIBANDRIA4_PROCESSOR0_ISA_PowerISA LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 11 ) /* 1990 */
		/* Included because of 32x, Saturn, & Dreamcast. */
	#define LIBANDRIA4_PROCESSOR0_ISA_SuperH LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 12 ) /* 1992 */
	#define LIBANDRIA4_PROCESSOR0_ISA_RISC_V LIBANDRIA4_PROCESSOR0_ERAPOPULIS( 13 ) /* 2010 */
	
	/*
		It is time to produce processor-identification logic.
	*/
	
#endif /* End primitive platdet predefs.h */
