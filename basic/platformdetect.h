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

#ifndef LIBANDRIA4_BASIC_PLATFORMDETECT_H
# define LIBANDRIA4_BASIC_PLATFORMDETECT_H
	
	/**************************************************************************/
	/**************************************************************************/
	/** WARNING! From here until a comment specifying otherwise, there must ***/
	/**  be NO inclusions of other files, due to the need to specify feature **/
	/**  enabling macros for GNU Libc. ****************************************/
	/**************************************************************************/
	/**************************************************************************/
	
	
	
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
	
	/* We probably want a "feature detect" file too, to do things like */
	/*  detect if signals are relevant to the target. */
	
	
	
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
	
		/* Prepare for target-platform detection. */
	#ifdef LIBANDRIA4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM
	# define LIBANDRIA4_TARGETPLATFORM -1
	#else
	# define LIBANDRIA4_TARGETPLATFORM 0
	#endif
	
	
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
	#define LIBANDRIA4_COMPILER_ERA 0
	
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
	
	/* Still need id macros for: */
	/*  Small C. */
	/*  BDS C. */
	/*  Lattice C. */
	
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
	
	
		/* Define LIBANDRIA4_COMPILER_ERA here. */
	/* This is a lazy hack, we should really detect language era here. */
	#undef LIBANDRIA4_COMPILER_ERA
	#define LIBANDRIA4_COMPILER_ERA LIBANDRIA4_COMPILER_ERA_CURRENT
	
	
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
	
	
	
	/* Initial detection for the platform. This is essentially a preview, */
	/*  meant to be double-checked and expanded upon with later logic. */
	
	#if defined( linux ) || defined( __linux ) || defined( __linux__ )
		#if defined( LIBANDRIA4_PLATFORMPREVIEW0 ) && LIBANDRIA4_PLATFORMPREVIEW0 != 0 && LIBANDRIA4_PLATFORMPREVIEW0 != LIBANDRIA4_PLATFORM0_NIX
			#error "Error: Libandria4 platformdetect.h LIBANDRIA4_PLATFORMPREVIEW0"
			#error " already had a non-null value when detecting Linux."
		#else
			#ifdef LIBANDRIA4_PLATFORMPREVIEW0
				#undef LIBANDRIA4_PLATFORMPREVIEW0
			#endif
			#define LIBANDRIA4_PLATFORMPREVIEW0 LIBANDRIA4_PLATFORM0_NIX
		#endif
	#endif
	
	#if defined( _WIN32 ) || defined( __WIN32__ ) || defined( __TOS_WIN__ ) || defined( __WINDOWS__ )
		if defined( LIBANDRIA4_PLATFORMPREVIEW0 ) && LIBANDRIA4_PLATFORMPREVIEW0 != 0 && LIBANDRIA4_PLATFORMPREVIEW0 != LIBANDRIA4_PLATFORM0_MSWIN
			#error "Error: Libandria4 platformdetect.h LIBANDRIA4_PLATFORMPREVIEW0"
			#error " already had a non-null value when detecting MSWindows."
		#else
			#ifdef LIBANDRIA4_PLATFORMPREVIEW0
				#undef LIBANDRIA4_PLATFORMPREVIEW0
			#endif
			#define LIBANDRIA4_PLATFORMPREVIEW0 LIBANDRIA4_PLATFORM0_MSWIN
		#endif
	#endif
	
	#if defined( _WIN16 ) || defined( MSDOS ) || defined( __MSDOS__ ) || defined( _MSDOS ) || defined( __DOS__ )
		#if defined( LIBANDRIA4_PLATFORMPREVIEW0 ) && LIBANDRIA4_PLATFORMPREVIEW0 != 0 && LIBANDRIA4_PLATFORMPREVIEW0 != LIBANDRIA4_PLATFORM0_DOS
			#error "Error: Libandria4 platformdetect.h LIBANDRIA4_PLATFORMPREVIEW0"
			#error " already had a non-null value when detecting MSDOS / 16bit MSWindows."
		#else
			#ifdef LIBANDRIA4_PLATFORMPREVIEW0
				#undef LIBANDRIA4_PLATFORMPREVIEW0
			#endif
			#define LIBANDRIA4_PLATFORMPREVIEW0 LIBANDRIA4_PLATFORM0_DOS
		#endif
	#endif
	
	
	
	/*************************************************************************/
	/*************************************************************************/
	/** WARNING! Only override files may be included from here onwards, and **/
	/**  they MUST NOT contain includes of any system files, lest conflicts **/
	/**  with e.g. Posix feature-enable macros occur. ************************/
	/*************************************************************************/
	/*************************************************************************/
	
	
	
	/* This is the proper area to perform any override inclusions that might */
	/*  activate feature-control macros. */
	
	#if ( LIBANDRIA4_PLATFORMPREVIEW0 == LIBANDRIA4_PLATFORM0_NIX ) && ( LIBANDRIA4_COMPILER & ( ~LIBANDRIA4_COMPILER_CODEBASEANTIMASK ) != LIBANDRIA4_COMPILER_CODEBASE_GNU )
			/* This is some weird thing that might be GNU specific, or */
			/*  might not. You define some mix of _POSIX_VERSION, */
			/*  _POSIX_C_SOURCE, _XOPEN_SOURCE, etc., to enable extra */
			/*  features in system headers. Some will cause the others to be */
			/*  defined as well. */
		#define _POSIX_C_VERSION 200112L
		#warning "Warning: Defining POSIX C version macro. This needs to allow an override to be specified."
	#endif
	
	
	
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
	
	#if LIBANDRIA4_PLATFORMPREVIEW0 == LIBANDRIA4_PLATFORM0_NIX && !defined( LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_NIX )
		#if defined( unix ) || defined( __unix__ ) || defined( __unix )
			#include <unistd.h>
		#endif
		
			/* The defines in this block are from */
			/*  https://sourceforge.net/p/predef/wiki/Standards/ : */
			/*  Need to figure out my own equivalent. */
		#if defined( _XOPEN_VERSION )
			#if ( _XOPEN_VERSION >= 3 )
				/* X/Open Portability Guide 3 (1989) */
			#endif
			#if ( _XOPEN_VERSION >= 4 )
				/* X/Open Portability Guide 4 (1992) */
			#endif
			#if ( _XOPEN_VERSION >= 4 ) && defined( _XOPEN_UNIX )
				/* X/Open Single UNIX Specification (UNIX95) (1995) */
			#endif
			#if ( _XOPEN_VERSION >= 500 )
				/* X/Open Single UNIX Specification, Version 2 (UNIX98) (1998) */
			#endif
			#if ( _XOPEN_VERSION >= 600 )
				/* Open Group Single UNIX Specification, Version 3 (UNIX03) (2003) */
				#if defined( _XOPEN_SOURCE ) && _XOPEN_SOURCE >= 600
					# undef LIBANDRIA4_BIGFILES_SEEK
					# define LIBANDRIA4_BIGFILES_SEEK 1
				#endif
			#endif
			#if ( _XOPEN_VERSION >= 700 )
				/* Open Group Single UNIX Specification, Version 4 (2008) */
			#endif
		#endif
		
		#if defined( _POSIX_VERSION )
			#if ( _POSIX_VERSION >= 198808L )
			#endif
			#if ( _POSIX_VERSION >= 199009L )
				/* ISO/IEC 9945-1:1990 */
			#endif
			#if ( _POSIX_VERSION >= 199309L )
				/* IEEE 1003.1b-1993 */
			#endif
			#if ( _POSIX_VERSION >= 199506L )
				/* IEEE 1003.1-1996 */
			#endif
			#if ( _POSIX_VERSION >= 200112L )
				/* IEEE 1003.1-2001 */
				#if defined( _POSIX_C_SOURCE ) && _POSIX_C_SOURCE >= 200112L
					# undef LIBANDRIA4_BIGFILES_SEEK
					# define LIBANDRIA4_BIGFILES_SEEK 1
				#endif
			#endif
			#if ( _POSIX_VERSION >= 200809L )
				/* IEEE 1003.1-2008 */
			#endif
		#endif
		if defined( _POSIX2_C_VERSION )
			#if ( _POSIX2_C_VERSION == 199209L )
				/* ISO/IEC 9945-2:1993 */
			#endif
		#endif
		
		#if defined( __LSB_VERSION__ )
			/*
				__LSB_VERSION__ == VR
				Linux Standards Base,
					V = Version
					R = Revision
			*/
		#endif
		
		
		#if defined( _LARGEFILE64_SOURCE ) || defined( _LARGEFILE_SOURCE )
			#undef LIBANDRIA4_BIGFILES_SEEK
			#define LIBANDRIA4_BIGFILES_SEEK 1
		#endif
		
		#if LIBANDRIA4_TARGETPLATFORM != 0
			#error "Error: LibAndria4 platformdetect.h detected Nix, but LIBANDRIA4_TARGETPLATFORM was already set."
		#else
			#undef LIBANDRIA4_TARGETPLATFORM
			#define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_TARGETPLATFORM_NIX
		#endif
		
		
		#define LIBANDRIA4_PLATFORM0 LIBANDRIA4_PLATFORM_NIX
		
	#elif LIBANDRIA4_PLATFORMPREVIEW0 == LIBANDRIA4_PLATFORM0_NIX && defined( LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_NIX )
		#error "Error: LibAndria4 platformdetect.h detected Nix, but LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_NIX was set."
		
	#endif
	
	
	
	#if LIBANDRIA4_PLATFORMPREVIEW0 == LIBANDRIA4_PLATFORM_MSWIN && !defined( LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_MSWIN )
		#if defined( _WIN32_WCE )
			/* This is defined for Windows CE devices. We currently don't */
			/*  distinguish those. */
		#endif
		
		
		#if defined( _MSC_VER ) && _MSC_VER >= 1000
			# undef LIBANDRIA4_BIGFILES_SEEK
			# define LIBANDRIA4_BIGFILES_SEEK 1
		#endif
		
		#if LIBANDRIA4_TARGETPLATFORM != 0
			#error "Error: LibAndria4 platformdetect.h detected MSWindows, but LIBANDRIA4_TARGETPLATFORM was already set."
		#else
			#undef LIBANDRIA4_TARGETPLATFORM
			#define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_TARGETPLATFORM_MSWIN
		#endif
		
		
		#define LIBANDRIA4_PLATFORM0 LIBANDRIA4_PLATFORM_MSWIN
		
	#elif LIBANDRIA4_PLATFORMPREVIEW0 == LIBANDRIA4_PLATFORM_MSWIN && defined( LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_MSWIN )
		#error "Error: LibAndria4 platformdetect.h detected MSWindows, but LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_MSWIN was set."
	#endif
	
	
		/* Allow the user to override platform detection. */
	#if LIBANDRIA4_TARGETPLATFORM == -1
		# undef LIBANDRIA4_TARGETPLATFORM
		# define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM
	#endif
	
	
	
		/* File size / file-offset-type size detection. Overrides because */
		/*  sometimes people care. */
	#if !defined( LIBANDRIA4_MACROSWITCHES_NO_LARGE_FILES ) && !defined( _FILE_OFFSET_BITS )
		#if LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_MSWIN && LIBANDRIA4_BIGFILES_SEEK
			#define LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS 64
		#elif LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_NIX && LIBANDRIA4_BIGFILES_SEEK
			#define LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS 64
		#else
			#define LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS 32
		#endif
	#elif defined( _FILE_OFFSET_BITS )
		#define LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS _FILE_OFFSET_BITS
	#else
		#define LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS 32
	#endif
		/* Note: while LIBANDRIA4_SWITCHES_NO_LARGE_FILES is an argument to the */
		/*  LibAndria4 system, _FILE_OFFSET_BITS is actually from Posix. However, */
		/*  the idea of it (whatever the exact idea actually is: it's been a */
		/*  while since I originally wrote the code that I've localized */
		/*  above) is itself useful enough to fairly directly copied. */
	
	
	
	
	
	
	
	
	/* TODO: Create a platformsupport.h, and move the stuff below into it. */
	
	#include "monads.h"
	#include "stdio.h"
	
	#if LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS > 32
		#if LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_MSWIN
			typedef __int64 libandria4_foff_t;
		#elif LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_NIX
			typedef off_t libandria4_foff_t;
		#else
			#warning "Unknown platform: ftello/_ftelli64 equivalent not known."
			typedef long libandria4_foff_t;
		#endif
	#else
		typedef long libandria4_foff_t;
	#endif
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE( libandria4_either_fofft_int, libandria4_foff_t, int );
	typedef libandria4_either_fofft_int libandria4_either_fofft;
	#define LIBANDRIA4_EITHER_FOFFT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_either_fofft, libandria4_foff_t, ( val ) )
	#define LIBANDRIA4_EITHER_FOFFT_BUILDERROR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_either_fofft, int, ( val ) )
	#define LIBANDRIA4_EITHER_FOFFT_BODYMATCH( var, succmatch, errmatch ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, succmatch, errmatch )
	#define LIBANDRIA4_EITHER_FOFFT_EXPRMATCH( var, succmatch, errmatch ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, succmatch, errmatch )
	
	typedef struct libandria4_int_errint
	{
		int val, err;
		
	} libandria4_int_errint;
	
		/* origin expects the standard SEEK_SET, SEEK_CUR, and SEEK_END macros from C. */
	inline libandria4_int_errint libandria4_fseek( FILE *stream, libandria4_either_fofft offset, int origin );
	inline libandria4_either_fofft libandria4_ftell( FILE *stream );
	
#endif
/* End libandria4 basic platformdetect.h */
