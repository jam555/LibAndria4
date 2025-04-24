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

#if LIBANDRIA4_PRIMITIVE_PLATDET_PROCS_X86_H
# define LIBANDRIA4_PRIMITIVE_PLATDET_PROCS_X86_H
	
	#include "../platformdetect.h"
	
	
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_8086 1
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_80286 2
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_80386 3
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_80486 4
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1 5
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium2 6
		/* Introduced SSE, seems that the Athlon XP was comparable. */
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium3 6
		/* Early Pentium4 */
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_SSE2 6
		/* Mid-late Pentium4, with 64-bit support disabled. The 3D Now stuff */
		/*  in Athlon and similar processors seems to be highly similar to */
		/*  some of these extensions. Note that 3D Now used the x87 */
		/*  registers, so no special saving behavior. Beware that 3D Now must */
		/*  either be detected by the user, or through a feature-test macro. */
	#define LIBANDRIA4_PROCESSOR0_ISA_x86_32bSSE3 6
	
	/* AVX-512 is NOT reliably available, so it should (even if temporarily) */
	/*  be recognized through detect-macro only. */
	
	
	#if LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU )
		/* GNU GCC */
		
		#if defined( i386 || __i386 || __i386__ )
			/* 32-bit x86 */
			
			#undef LIBANDRIA4_TARGETPROCESSOR0
			#define LIBANDRIA4_TARGETPROCESSOR0 LIBANDRIA4_PROCESSOR0_ISA_x86
			
			#undef LIBANDRIA4_TARGETPROCESSOR1
				/* This SHOULD BE the primary development line, as opposed to */
				/*  e.g. the 80186. */
			#define LIBANDRIA4_TARGETPROCESSOR1 1
			
			#if defined( __i386__ )
				/* 386 */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_386
			#endif
			#if defined( __i486__ )
				/* 486 */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_486
			#endif
			#if defined( __i586__ )
				/* Pentium */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
			#endif
			#if defined( __i686__ )
				/* Pentium Pro/Pentium II */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium2
			#endif
			#if LIBANDRIA4_TARGETPROCESSOR2 == 0
				#error "Unidentified x86-32 target processor.\n"
			#endif
			
		#else
			#error "Unrecognized x86 target mode.\n"
		#endif
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_MSVC )
		/* Microsoft MSVC */
		/* Supported: */
			/* _MSC_VER : MSVC. */
		
		#if defined( _M_I86 )
			/* 16-bit x86. */
			#error "16-bit x86 currently not supported.\n"
			
		#elif defined( _M_IX86 )
			/* 32-bit x86. */
			
			#undef LIBANDRIA4_TARGETPROCESSOR0
			#define LIBANDRIA4_TARGETPROCESSOR0 LIBANDRIA4_PROCESSOR0_ISA_x86
			
			#undef LIBANDRIA4_TARGETPROCESSOR1
				/* This SHOULD BE the primary development line, as opposed to e.g. the 80186. */
			#define LIBANDRIA4_TARGETPROCESSOR1 1
			
			#if _M_IX86 == 300
				/* 386 */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_386
				
			#elif _M_IX86 == 400
				/* 486 */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_486
				
			#elif _M_IX86 == 500
				/* Pentium */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
				
			#elif _M_IX86 == 600
				/* Pentium Pro/Pentium II */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium2
				
			#else
				#error "Unidentified x86-32 target processor.\n"
			#endif
			
		#else
			#error "Unrecognized x86 target mode.\n"
		#endif
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_DIGIMARS )
		/* This is a place-holder for Digital Mars C/C++. */
		
		#if defined( _M_I86 )
			/* 16-bit x86. */
			
		#elif defined( __I86__ )
			/* 32-bit x86. */
			
			#undef LIBANDRIA4_TARGETPROCESSOR0
			#define LIBANDRIA4_TARGETPROCESSOR0 LIBANDRIA4_PROCESSOR0_ISA_x86
			
			#undef LIBANDRIA4_TARGETPROCESSOR1
				/* This SHOULD BE the primary development line, as opposed to e.g. the 80186. */
			#define LIBANDRIA4_TARGETPROCESSOR1 1
			
			#if __I86__ == 3
				/* 386 */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_386
				
			#elif __I86__ == 4
				/* 486 */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_486
				
			#elif __I86__ == 5
				/* Pentium */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
				
			#elif __I86__ == 6
				/* Pentium Pro/Pentium II */
				#undef LIBANDRIA4_TARGETPROCESSOR2
				#define LIBANDRIA4_TARGETPROCESSOR2 LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium2
				
			#else
				#error "Unidentified x86-32 target processor.\n"
			#endif
			
		#else
			#error "Unrecognized x86 target mode.\n"
		#endif
		
	#else
		#error "Unrecognized compiler.\n"
	#endif
	
#endif /* End primitive platdet procs x86.h */
