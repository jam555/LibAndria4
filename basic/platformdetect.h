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
	
		/* These are used later. */
	#include <errno.h>
	#include "monads.h"
	
	
	
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
	#define LIBANDRIA4_COMPILER_ERA_OVERFLOWED 31
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
	#define LIBANDRIA4_COMPILER_CODEBASE_PCC ( 5 * LIBANDRIA4_COMPILER_CODEBASEMULTIPLIER )
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
	
	
	
	/* Platform detection. When this is run, it should not only detect the */
	/*  general operating system & big-file support, but also indicate the */
	/*  size of the big-file support, and set some CUSTOM macros that */
	/*  specify THE VERSION of the operating system. None of which do any of */
	/*  these currently do. */
	
	/* Note: need to keep copying/translating things over from the */
	/*  "non-localized" equivalent. */
	
		/* *Nix-family detect. Rather bare-bones at the moment. */
	#if defined( __GNUC__ )
		# undef LIBANDRIA4_PLATFORM0
		
		#if defined( _POSIX_C_SOURCE ) || defined( _XOPEN_SOURCE ) || defined( _GNU_SOURCE )
			# define LIBANDRIA4_PLATFORM0 LIBANDRIA4_PLATFORM_NIX
			
			#if defined( _POSIX_C_SOURCE ) && _POSIX_C_SOURCE >= 200112L
				# undef LIBANDRIA4_BIGFILES_SEEK
				# define LIBANDRIA4_BIGFILES_SEEK 1
			#endif
			
			#if defined( _XOPEN_SOURCE ) && _XOPEN_SOURCE >= 600
				# undef LIBANDRIA4_BIGFILES_SEEK
				# define LIBANDRIA4_BIGFILES_SEEK 1
			#endif
			
			#if defined( _LARGEFILE64_SOURCE ) || defined( _LARGEFILE_SOURCE )
				# undef LIBANDRIA4_BIGFILES_SEEK
				# define LIBANDRIA4_BIGFILES_SEEK 1
			#endif
			
			
			#if LIBANDRIA4_TARGETPLATFORM == 0 && !defined( LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_NIX )
				# undef LIBANDRIA4_TARGETPLATFORM
				# define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_TARGETPLATFORM_NIX
			#endif
			
		#else
			
			/* This is BAD, it needs PROPER testing. */
			
			# define LIBANDRIA4_PLATFORM LIBANDRIA4_PLATFORM_MSWIN
			
			#if LIBANDRIA4_TARGETPLATFORM == 0 && !defined( LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_MSWIN )
				# undef LIBANDRIA4_TARGETPLATFORM
				# define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_TARGETPLATFORM_MSWIN
			#endif
			
		#endif
		
	#elif defined( _POSIX_C_SOURCE ) || defined( _XOPEN_SOURCE ) || defined( _GNU_SOURCE )
		/* This is BAD, it needs to be replaced. */
		# undef LIBANDRIA4_PLATFORM0
	# define LIBANDRIA4_PLATFORM0 LIBANDRIA4_PLATFORM_NIX
		
		#if defined( _POSIX_C_SOURCE ) && _POSIX_C_SOURCE >= 200112L
			# undef LIBANDRIA4_BIGFILES_SEEK
			# define LIBANDRIA4_BIGFILES_SEEK 1
		#endif
		
		#if defined( _XOPEN_SOURCE ) && _XOPEN_SOURCE >= 600
			# undef LIBANDRIA4_BIGFILES_SEEK
			# define LIBANDRIA4_BIGFILES_SEEK 1
		#endif
		
		#if defined( _LARGEFILE64_SOURCE ) || defined( _LARGEFILE_SOURCE )
			# undef LIBANDRIA4_BIGFILES_SEEK
			# define LIBANDRIA4_BIGFILES_SEEK 1
		#endif
		
		
		#if LIBANDRIA4_TARGETPLATFORM == 0 && !defined( LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_NIX )
			# undef LIBANDRIA4_TARGETPLATFORM
			# define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_TARGETPLATFORM_NIX
		#endif
		
	#endif
	
		/* MSWindows-family detect. Actually MORE bare-bones than the *nix */
		/*  stuff.  */
	#if defined( _MSC_VER )
		# undef LIBANDRIA4_PLATFORM
		# define LIBANDRIA4_PLATFORM LIBANDRIA4_PLATFORM_MSWIN
		
		#if defined( _WIN32_WCE )
			/* This is defined for Windows CE devices. We currently don't */
			/*  distinguish those. */
		#endif
		
		#if defined( _MSC_VER ) && _MSC_VER >= 1000
			# undef LIBANDRIA4_BIGFILES_SEEK
			# define LIBANDRIA4_BIGFILES_SEEK 1
		#endif
		
		
		#if LIBANDRIA4_TARGETPLATFORM == 0 && !defined( LIBANDRIA4_MACROSWITCHES_NO_PLATFORM_MSWIN )
			# undef LIBANDRIA4_TARGETPLATFORM
			# define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_TARGETPLATFORM_MSWIN
		#endif
		
	#endif
	
		/* Finish handling the target-platform identification. */
	#if LIBANDRIA4_TARGETPLATFORM == -1
		# undef LIBANDRIA4_TARGETPLATFORM
		# define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM
	#endif
	
	
	
		/* File size/ file-offset-type size detection. Overrides because */
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
		/*  libandria4 system, _FILE_OFFSET_BITS is actually from Posix. However, */
		/*  the idea of it (whatever the exact idea actually is: it's been a */
		/*  while since I originally wrote the code that I've localized */
		/*  above) is itself useful enough to fairly directly copied. */
	
	
	
	/* Compiler detection. */
	
	/* This is some of the lazyist code I've ever written, to the point */
	/*  that MSVC before version 3.0 should actually register as */
	/*  LIBANDRIA4_COMPILER_CODEBASE_LATTICEC in some sense, because Microsoft */
	/*  licensed it. However, for place-holder code, I guess it's */
	/*  survivable. Barely. */
	
	#if LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_MSWIN
		# undef LIBANDRIA4_COMPILER
		
		#if defined( _MSC_VER )
			
			# define LIBANDRIA4_COMPILER \
				( LIBANDRIA4_COMPILER_CODEBASE_MSVC | LIBANDRIA4_COMPILER_ERA_CURRENT )
		#else
			
			/* This is BAD, and needs to be replaced. */
			# define LIBANDRIA4_COMPILER \
				( LIBANDRIA4_COMPILER_CODEBASE_GNU | LIBANDRIA4_COMPILER_ERA_CURRENT )
			
		#endif
		
	#endif
	
	
	
	/* Some function name definitions. These should probably have an inline */
	/*  wrapper, because there is at least some variation between MSWindows */
	/*  & Linux. */
	
	#if LIBANDRIA4_PLATFORM_FILE_OFFSET_BITS > 32
		#ifdef LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_MSWIN
			typedef __int64 libandria4_foff_t;
			#define LIBANDRIA4_FSEEK_FUNCTION _fseeki64
			#define LIBANDRIA4_FTELL_FUNCTION _ftelli64
		#elif LIBANDRIA4_TARGETPLATFORM == LIBANDRIA4_TARGETPLATFORM_NIX
			typedef off_t libandria4_foff_t;
			#define LIBANDRIA4_FSEEK_FUNCTION fseeko
			#define LIBANDRIA4_FTELL_FUNCTION ftello
		#else
		# error "Unknown platform: ftello/_ftelli64 equivalent not known."
			typedef long libandria4_foff_t;
			#define LIBANDRIA4_FSEEK_FUNCTION fseek
			#define LIBANDRIA4_FTELL_FUNCTION ftell
		#endif
	#else
		typedef long libandria4_foff_t;
		#define LIBANDRIA4_FSEEK_FUNCTION fseek
		#define LIBANDRIA4_FTELL_FUNCTION ftell
	#endif
	
	#ifdef LIBANDRIA4_FSEEK_INNER
		# define LIBANDRIA4_FSEEK( stream, offset, origin ) \
		LIBANDRIA4_FSEEK_INNER( ( stream ), ( offset ), ( origin ) )
	#else
		# define LIBANDRIA4_FSEEK( stream, offset, origin ) \
		LIBANDRIA4_FSEEK_FUNCTION( ( stream ), ( offset ), ( origin ) )
	#endif
	
	#ifdef LIBANDRIA4_FTELL_INNER
		# define LIBANDRIA4_FTELL( stream ) LIBANDRIA4_FTELL_INNER( ( stream ) )
	#else
		# define LIBANDRIA4_FTELL( stream ) LIBANDRIA4_FTELL_FUNCTION( ( stream ) )
	#endif
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE( libandria4_either_fofft_int, libandria4_foff_t, int );
	typedef libandria4_either_fofft_int libandria4_either_fofft;
	#define LIBANDRIA4_EITHER_FOFFT_BUILDLEFT( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_either_fofft, libandria4_foff_t, ( val ) )
	#define LIBANDRIA4_EITHER_FOFFT_BUILDRIGHT( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_either_fofft, int, ( val ) )
	#define LIBANDRIA4_EITHER_FOFFT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_EITHER_FOFFT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
	typedef struct libandria4_int_errint
	{
		int val, err;
		
	} libandria4_int_errint;
	
	inline libandria4_int_errint libandria4_fseek( FILE *stream, libandria4_either_fofft offset, int origin )
	{
			/* Used internally. */
		#define libandria4_fseek_MATCHA( val ) \
			res = LIBANDRIA4_FSEEK( stream, val, origin )
		#define libandria4_fseek_MATCHB( val ) \
			ret = (libandria4_int_errint){ -2, val }; errno = err; return( ret )
		
		int res, err = errno;
		errno = 0;
		libandria4_int_errint ret;
		
		LIBANDRIA4_EITHER_FOFFT_BODYMATCH(
			offset,
			
			libandria4_fseek_MATCHA,
			libandria4_fseek_MATCHB
		)
		
		ret = (libandria4_int_errint){ res, errno };
		
		errno = err;
		
		return( ret );
	}
	inline libandria4_either_fofft libandria4_ftell( FILE *stream )
	{
		libandria4_either_fofft ret;
		libandria4_foff_t res;
		err = errno;
		errno = 0;
		
		res = LIBANDRIA4_FTELL( stream );
		
		if( res >= 0 )
		{
			ret = LIBANDRIA4_EITHER_FOFFT_BUILDLEFT( res );
			
		} else {
			
			ret = LIBANDRIA4_EITHER_FOFFT_BUILDRIGHT( errno );
		}
		
		errno = err;
		
		return( ret );
	}
	
#endif
/* End libandria4 basic platformdetect.h */
