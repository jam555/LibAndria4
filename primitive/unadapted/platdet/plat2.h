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

#if LIBANDRIA4_PRIMITIVE_PLATDET_PLAT2_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_PLAT2_H
	
	#include "../platformdetect.h"
	
	
	/* This is second-pass platform-detection code, meant to narrow down */
	/*  the platform after rough generalities have been identified. */
	/* Also, it's use of e.g. _XOPEN_VERSION is almost guaranteed to be */
	/*  backwards. */
	/* TODO: fix the use of the feature-enable macros below. */
	
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
					#undef LIBANDRIA4_BIGFILES_SEEK
					#define LIBANDRIA4_BIGFILES_SEEK 1
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
					#undef LIBANDRIA4_BIGFILES_SEEK
					#define LIBANDRIA4_BIGFILES_SEEK 1
				#endif
			#endif
			#if ( _POSIX_VERSION >= 200809L )
				/* IEEE 1003.1-2008 */
			#endif
		#endif
		#if defined( _POSIX2_C_VERSION )
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
		
		
		#undef LIBANDRIA4_PLATFORM0
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
		#undef LIBANDRIA4_TARGETPLATFORM
		#define LIBANDRIA4_TARGETPLATFORM LIBANDRIA4_MACROSWITCHES_OVERRIDE_TARGETPLATFORM
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
	
#endif /* End primitive platdet plat2.h */
