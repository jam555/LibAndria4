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

#if LIBANDRIA4_PRIMITIVE_PLATDET_PLATFORM_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_PLATFORM_H
	
	#include "../platformdetect.h"
	
	
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
		#if defined( LIBANDRIA4_PLATFORMPREVIEW0 ) && LIBANDRIA4_PLATFORMPREVIEW0 != 0 && LIBANDRIA4_PLATFORMPREVIEW0 != LIBANDRIA4_PLATFORM0_MSWIN
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
	
#endif /* End primitive platdet platform.h */
