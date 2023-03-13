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

#ifndef LIB4_PLATFORMDETECT_H
# define LIB4_PLATFORMDETECT_H
	
		/* These are used later. */
	#include <errno.h>
	#include "monads.h"
	
	
	
	/* Here's a list of defines that can be used as switches! */
		/* LIB4_MACROSWITCHES_NO_LARGE_FILES */
		/* LIB4_MACROSWITCHES_NO_PLATFORM_NIX */
		/* LIB4_MACROSWITCHES_NO_PLATFORM_MSWIN */
		/* LIB4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM */
	
	/* To use platform detection, compare LIB4_PLATFORM0 to the */
	/*  LIB4_PLATFORM0_* values. LIB4_PLATFORM1 is not currently used, but */
	/*  is reserved for JUST IN CASE we want to support more than than 15 */
	/*  platforms. */
	/* Alternatively, compare LIB4_TARGETPLATFORM to the */
	/*  LIB4_TARGETPLATFORM_* values. */
	
	/* To use compiler detection, "and" LIB4_COMPILER with */
	/*  LIB4_COMPILER_ERAMASK (for the compiler's approximate time period) */
	/*  to compare with the LIB4_COMPILER_ERA_* values, or "and" */
	/*  LIB4_COMPILER with ~(LIB4_COMPILER_ERAMASK) to compare with the */
	/*  LIB4_COMPILER_CODEBASE_* values. */
	
	/* We currently don't distinguish OS variants, such as Windows CE. That */
	/*  should be changed in the future. */
	
	/* We currently don't detect platform architecture (e.g. x86 vs 68k, or */
	/*  Tandy vs IBM). We should change that in the future. */
		/* Here's two relevant macros: __i386__  __x86_64__ */
	
	/* We probably want a "feature detect" file too, to do things like */
	/*  detect if signals are relevant to the target. */
	
	
	
	#define LIB4_PLATFORM0 0
	
	#define LIB4_PLATFORM0_NIX 1
	#define LIB4_PLATFORM0_DOS 2
	#define LIB4_PLATFORM0_MSWIN 4
	#define LIB4_PLATFORM0_ATARIOS 8
	#define LIB4_PLATFORM0_COMMODOREOS 16
	#define LIB4_PLATFORM0_CPM 32
	#define LIB4_PLATFORM0_IBMPCBIOS 64
	
	#define LIB4_PLATFORM0_OVERFLOW 32768
		/* Note: no values over 32768! Must support 16-bit ints! */
	
	#define LIB4_PLATFORM1 0
	
		/* For the platform defines below, the values correspond to the bit */
		/*  index of the LIB4_PLATFORM* values above, + 1. So e.g. the value */
		/*  "3" would correspond to LIB4_PLATFORM0's "4" value, while the */
		/*  value "4" would correspond to LIB4_PLATFORM0's "8" value, and */
		/*  the value "17" would correspond to LIB4_PLATFORM1's "1" value. */
	#define LIB4_TARGETPLATFORM_NIX 1
	#define LIB4_TARGETPLATFORM_DOS 2
	#define LIB4_TARGETPLATFORM_MSWIN 3
	#define LIB4_TARGETPLATFORM_ATARIOS 4
	#define LIB4_TARGETPLATFORM_COMMODOREOS 5
	#define LIB4_TARGETPLATFORM_CPM 6
	#define LIB4_TARGETPLATFORM_IBMPCBIOS 7
	
		/* Prepare for target-platform detection. */
	#ifdef LIB4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM
	# define LIB4_TARGETPLATFORM -1
	#else
	# define LIB4_TARGETPLATFORM 0
	#endif
	
	
	#define LIB4_BIGFILES_SEEK 0
	
	
		/* This value needs to be built by detection logic to contain an */
		/*  era, and a codebase. Other macros should then be set to nail */
		/*  down any interesting quirks. */
	#define LIB4_COMPILER 0
	
	#define LIB4_COMPILER_ERAMASK 31
	#define LIB4_COMPILER_ERA_CURRENT 0
	#define LIB4_COMPILER_ERA_1970S 1
	#define LIB4_COMPILER_ERA_1980S 2
	#define LIB4_COMPILER_ERA_1990S 3
	#define LIB4_COMPILER_ERA_2000S 4
	#define LIB4_COMPILER_ERA_2010S 5
	#define LIB4_COMPILER_ERA_2020S 6
	#define LIB4_COMPILER_ERA_OVERFLOWED 31
		/* This should be set in lock-step with ( LIB4_COMPILER & */
		/*  LIB4_COMPILER_ERAMASK ), unless the value is 31 or above. Note */
		/*  that if value is "0", then it actually just hasn't been set. */
	#define LIB4_COMPILER_ERA 0
	
	#define LIB4_COMPILER_CODEBASEANTIMASK LIB4_COMPILER_ERAMASK
	#define LIB4_COMPILER_CODEBASEMULTIPLIER ( LIB4_COMPILER_CODEBASEANTIMASK + 1 )
		/* __TINYC__ : Tiny C Compiler. */
	#define LIB4_COMPILER_CODEBASE_TCC ( 0 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __GNUC__ : GCC C/C++. */
	#define LIB4_COMPILER_CODEBASE_GNU ( 1 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __llvm__ and/or __clang__ : LLVM C / Clang. */
	#define LIB4_COMPILER_CODEBASE_LLVM ( 2 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* _MSC_VER : MSVC. */
	#define LIB4_COMPILER_CODEBASE_MSVC ( 3 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __TURBOC__ : Borland Turbo C. */
		/* __BORLANDC__ or __CODEGEARC__ : Borland / CodeGear / Embarcadero */
		/*  C++ Builder. Versions have targeted MSWindows, Linux, Solaris, */
		/*  OS X, iOS, and Android. */
	#define LIB4_COMPILER_CODEBASE_BORLAND ( 4 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __WATCOMC__ : Watcom / OpenWatcom C/C++. */
	#define LIB4_COMPILER_CODEBASE_PCC ( 5 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __PCC__ : Portable C Compiler. */
	#define LIB4_COMPILER_CODEBASE_PCC ( 6 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __LCC__ : LCC. */
	#define LIB4_COMPILER_CODEBASE_LCC ( 7 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* SDCC : Small Device C Compiler. */
	#define LIB4_COMPILER_CODEBASE_SDCC ( 8 * LIB4_COMPILER_CODEBASEMULTIPLIER )
	#define LIB4_COMPILER_CODEBASE_SMALLC ( 9 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __ACK__ : Amsterdam Compiler Kit. For MINIX, multiple processors. */
	#define LIB4_COMPILER_CODEBASE_ACK ( 10 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* "Brain Damage Software" C Compiler. */
	#define LIB4_COMPILER_CODEBASE_BDS ( 11 * LIB4_COMPILER_CODEBASEMULTIPLIER )
	#define LIB4_COMPILER_CODEBASE_LATTICEC ( 12 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __OPEN64__ or __OPENCC__ : Open64. */
	#define LIB4_COMPILER_CODEBASE_OPEN64 ( 13 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* AZTEC_C or __AZTEC_C__ : Aztec C. For MSDOS, Apple II DOS 3.3 & */
		/*  ProDOS, Commodore 64, early Macs, CP/M-80, Amiga, & Atari ST. */
	#define LIB4_COMPILER_CODEBASE_AZTECC ( 14 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __CC_NORCROFT : Norcroft C. */
	#define LIB4_COMPILER_CODEBASE_NORCROFTC ( 15 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __TenDRA__ : TenDRA C/C++. */
	#define LIB4_COMPILER_CODEBASE_TENDRAC ( 16 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/* __COMO__ : Comeau C++. */
	#define LIB4_COMPILER_CODEBASE_COMEAU ( 17 * LIB4_COMPILER_CODEBASEMULTIPLIER )
		/*  __DJGPP__ or __GO32__ : DJGPP. For MSDOS. */
	#define LIB4_COMPILER_CODEBASE_DJGPP ( 18 * LIB4_COMPILER_CODEBASEMULTIPLIER )
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
	# undef LIB4_PLATFORM0
		
		#if defined( _POSIX_C_SOURCE ) || defined( _XOPEN_SOURCE ) || defined( _GNU_SOURCE )
			# define LIB4_PLATFORM0 LIB4_PLATFORM_NIX
			
			#if defined( _POSIX_C_SOURCE ) && _POSIX_C_SOURCE >= 200112L
			# undef LIB4_BIGFILES_SEEK
			# define LIB4_BIGFILES_SEEK 1
			#endif
			
			#if defined( _XOPEN_SOURCE ) && _XOPEN_SOURCE >= 600
			# undef LIB4_BIGFILES_SEEK
			# define LIB4_BIGFILES_SEEK 1
			#endif
			
			#if defined( _LARGEFILE64_SOURCE ) || defined( _LARGEFILE_SOURCE )
			# undef LIB4_BIGFILES_SEEK
			# define LIB4_BIGFILES_SEEK 1
			#endif
			
			
			#if LIB4_TARGETPLATFORM == 0 && !defined( LIB4_MACROSWITCHES_NO_PLATFORM_NIX )
			# undef LIB4_TARGETPLATFORM
			# define LIB4_TARGETPLATFORM LIB4_TARGETPLATFORM_NIX
			#endif
			
		#else
			
			/* This is BAD, it needs PROPER testing. */
			
			# define LIB4_PLATFORM LIB4_PLATFORM_MSWIN
			
			#if LIB4_TARGETPLATFORM == 0 && !defined( LIB4_MACROSWITCHES_NO_PLATFORM_MSWIN )
			# undef LIB4_TARGETPLATFORM
			# define LIB4_TARGETPLATFORM LIB4_TARGETPLATFORM_MSWIN
			#endif
			
		#endif
		
	#elif defined( _POSIX_C_SOURCE ) || defined( _XOPEN_SOURCE ) || defined( _GNU_SOURCE )
		/* This is BAD, it needs to be replaced. */
	# undef LIB4_PLATFORM0
	# define LIB4_PLATFORM0 LIB4_PLATFORM_NIX
		
		#if defined( _POSIX_C_SOURCE ) && _POSIX_C_SOURCE >= 200112L
		# undef LIB4_BIGFILES_SEEK
		# define LIB4_BIGFILES_SEEK 1
		#endif
		
		#if defined( _XOPEN_SOURCE ) && _XOPEN_SOURCE >= 600
		# undef LIB4_BIGFILES_SEEK
		# define LIB4_BIGFILES_SEEK 1
		#endif
		
		#if defined( _LARGEFILE64_SOURCE ) || defined( _LARGEFILE_SOURCE )
		# undef LIB4_BIGFILES_SEEK
		# define LIB4_BIGFILES_SEEK 1
		#endif
		
		
		#if LIB4_TARGETPLATFORM == 0 && !defined( LIB4_MACROSWITCHES_NO_PLATFORM_NIX )
		# undef LIB4_TARGETPLATFORM
		# define LIB4_TARGETPLATFORM LIB4_TARGETPLATFORM_NIX
		#endif
		
	#endif
	
		/* MSWindows-family detect. Actually MORE bare-bones than the *nix */
		/*  stuff.  */
	#if defined( _MSC_VER )
	# undef LIB4_PLATFORM
	# define LIB4_PLATFORM LIB4_PLATFORM_MSWIN
		
		#if defined( _WIN32_WCE )
			/* This is defined for Windows CE devices. We currently don't */
			/*  distinguish those. */
		#endif
		
		#if defined( _MSC_VER ) && _MSC_VER >= 1000
		# undef LIB4_BIGFILES_SEEK
		# define LIB4_BIGFILES_SEEK 1
		#endif
		
		
		#if LIB4_TARGETPLATFORM == 0 && !defined( LIB4_MACROSWITCHES_NO_PLATFORM_MSWIN )
		# undef LIB4_TARGETPLATFORM
		# define LIB4_TARGETPLATFORM LIB4_TARGETPLATFORM_MSWIN
		#endif
		
	#endif
	
		/* Finish handling the target-platform identification. */
	#if LIB4_TARGETPLATFORM == -1
	# undef LIB4_TARGETPLATFORM
	# define LIB4_TARGETPLATFORM LIB4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM
	#endif
	
	
	
		/* File size/ file-offset-type size detection. Overrides because */
		/*  sometimes people care. */
	#if !defined( LIB4_MACROSWITCHES_NO_LARGE_FILES ) && !defined( _FILE_OFFSET_BITS )
		#if LIB4_TARGETPLATFORM == LIB4_TARGETPLATFORM_MSWIN && LIB4_BIGFILES_SEEK
			#define LIB4_PLATFORM_FILE_OFFSET_BITS 64
		#elif LIB4_TARGETPLATFORM == LIB4_TARGETPLATFORM_NIX && LIB4_BIGFILES_SEEK
			#define LIB4_PLATFORM_FILE_OFFSET_BITS 64
		#else
			#define LIB4_PLATFORM_FILE_OFFSET_BITS 32
		#endif
	#elif defined( _FILE_OFFSET_BITS )
		#define LIB4_PLATFORM_FILE_OFFSET_BITS _FILE_OFFSET_BITS
	#else
		#define LIB4_PLATFORM_FILE_OFFSET_BITS 32
	#endif
		/* Note: while LIB4_SWITCHES_NO_LARGE_FILES is an argument to the */
		/*  lib4 system, _FILE_OFFSET_BITS is actually from Posix. However, */
		/*  the idea of it (whatever the exact idea actually is: it's been a */
		/*  while since I originally wrote the code that I've localized */
		/*  above) is itself useful enough to fairly directly copied. */
	
	
	
	/* Compiler detection. */
	
	/* This is some of the lazyist code I've ever written, to the point */
	/*  that MSVC before version 3.0 should actually register as */
	/*  LIB4_COMPILER_CODEBASE_LATTICEC in some sense, because Microsoft */
	/*  licensed it. However, for place-holder code, I guess it's */
	/*  survivable. Barely. */
	
	#if LIB4_TARGETPLATFORM == LIB4_TARGETPLATFORM_MSWIN
	# undef LIB4_COMPILER
		
		#if defined( _MSC_VER )
			
			# define LIB4_COMPILER \
				( LIB4_COMPILER_CODEBASE_MSVC | LIB4_COMPILER_ERA_CURRENT )
		#else
			
			/* This is BAD, and needs to be replaced. */
			# define LIB4_COMPILER \
				( LIB4_COMPILER_CODEBASE_GNU | LIB4_COMPILER_ERA_CURRENT )
			
		#endif
		
	#endif
	
	
	
	/* Some function name definitions. These should probably have an inline */
	/*  wrapper, because there is at least some variation between MSWindows */
	/*  & Linux. */
	
	#if LIB4_PLATFORM_FILE_OFFSET_BITS > 32
		#ifdef LIB4_TARGETPLATFORM == LIB4_TARGETPLATFORM_MSWIN
			typedef __int64 lib4_foff_t;
			#define LIB4_FSEEK_FUNCTION _fseeki64
			#define LIB4_FTELL_FUNCTION _ftelli64
		#elif LIB4_TARGETPLATFORM == LIB4_TARGETPLATFORM_NIX
			typedef off_t lib4_foff_t;
			#define LIB4_FSEEK_FUNCTION fseeko
			#define LIB4_FTELL_FUNCTION ftello
		#else
		# error "Unknown platform: ftello/_ftelli64 equivalent not known."
			typedef long lib4_foff_t;
			#define LIB4_FSEEK_FUNCTION fseek
			#define LIB4_FTELL_FUNCTION ftell
		#endif
	#else
		typedef long lib4_foff_t;
		#define LIB4_FSEEK_FUNCTION fseek
		#define LIB4_FTELL_FUNCTION ftell
	#endif
	
	#ifdef LIB4_FSEEK_INNER
	# define LIB4_FSEEK( stream, offset, origin ) \
		LIB4_FSEEK_INNER( ( stream ), ( offset ), ( origin ) )
	#else
	# define LIB4_FSEEK( stream, offset, origin ) \
		LIB4_FSEEK_FUNCTION( ( stream ), ( offset ), ( origin ) )
	#endif
	
	#ifdef LIB4_FTELL_INNER
	# define LIB4_FTELL( stream ) LIB4_FTELL_INNER( ( stream ) )
	#else
	# define LIB4_FTELL( stream ) LIB4_FTELL_FUNCTION( ( stream ) )
	#endif
	
	LIB4_MONAD_EITHER_BUILDTYPE( lib4_either_fofft_int, lib4_foff_t, int );
	typedef lib4_either_fofft_int lib4_either_fofft;
	#define LIB4_EITHER_FOFFT_BUILDLEFT( val ) \
		LIB4_MONAD_EITHER_BUILDLEFT( lib4_either_fofft, lib4_foff_t, ( val ) )
	#define LIB4_EITHER_FOFFT_BUILDRIGHT( val ) \
		LIB4_MONAD_EITHER_BUILDRIGHT( lib4_either_fofft, int, ( val ) )
	#define LIB4_EITHER_FOFFT_BODYMATCH( var, matcha, matchb ) \
		LIB4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIB4_EITHER_FOFFT_EXPRMATCH( var, matcha, matchb ) \
		LIB4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
	typedef struct lib4_int_errint
	{
		int val, err;
		
	} lib4_int_errint;
	
	inline lib4_int_errint lib4_fseek( FILE *stream, lib4_either_fofft offset, int origin )
	{
			/* Used internally. */
		#define lib4_fseek_MATCHA( val ) \
			res = LIB4_FSEEK( stream, val, origin )
		#define lib4_fseek_MATCHB( val ) \
			ret = (lib4_int_errint){ -2, val }; errno = err; return( ret )
		
		int res, err = errno;
		errno = 0;
		lib4_int_errint ret;
		
		LIB4_EITHER_FOFFT_BODYMATCH(
			offset,
			
			lib4_fseek_MATCHA,
			lib4_fseek_MATCHB
		)
		
		ret = (lib4_int_errint){ res, errno };
		
		errno = err;
		
		return( ret );
	}
	inline lib4_either_fofft lib4_ftell( FILE *stream )
	{
		lib4_either_fofft ret;
		lib4_foff_t res;
		err = errno;
		errno = 0;
		
		res = LIB4_FTELL( stream );
		
		if( res >= 0 )
		{
			ret = LIB4_EITHER_FOFFT_BUILDLEFT( res );
			
		} else {
			
			ret = LIB4_EITHER_FOFFT_BUILDRIGHT( errno );
		}
		
		errno = err;
		
		return( ret );
	}
	
#endif
/* End lib4 platformdetect.h */
