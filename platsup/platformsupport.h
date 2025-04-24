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

#ifndef LIBANDRIA4_BASIC_PLATFORMSUPPORT_H
# define LIBANDRIA4_BASIC_PLATFORMSUPPORT_H
	
	#include <stdio.h>
	
	#include "platformdetect.h"
	
	#include "monads.h"
	
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
	libandria4_int_errint libandria4_fseek( FILE *stream, libandria4_either_fofft offset, int origin );
	libandria4_either_fofft libandria4_ftell( FILE *stream );
	
	
	
	int libandria4_endiancheck_islittleendian();
	int libandria4_endiancheck_isbigendian();
	int libandria4_endiancheck_ispdp11endian();
	int libandria4_endiancheck_ishoneywell316endian();
	
	
	
	#if \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_LLVM )
		/* Supported: */
			/* __GNUC__ : GCC C/C++. */
			/* __llvm__ and/or __clang__ : LLVM C / Clang. */
		
		#if LIBANDRIA4_CELLTYPE_REGSIZE == 8
			
			/* Stack pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETSP( ptr ) \
				asm volatile("movq %%rsp, %0" : "=r"(ptr))
			#define LIBANDRIA4_PLATSUPP_PROC_SETSP( ptr ) \
				asm volatile("movq %0, %%rsp" : : "r"(ptr))
			
			/* Frame pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETFP( ptr ) \
				asm volatile("movq %%rbp, %0" : "=r"(ptr))
			#define LIBANDRIA4_PLATSUPP_PROC_SETFP( ptr ) \
				asm volatile("movq %0, %%rbp" : : "r"(ptr))
			
		#elif LIBANDRIA4_CELLTYPE_REGSIZE == 4
			
			/* Stack pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETSP( ptr ) \
				asm volatile("movd %%esp, %0" : "=r"(ptr))
			#define LIBANDRIA4_PLATSUPP_PROC_SETSP( ptr ) \
				asm volatile("movd %0, %%esp" : : "r"(ptr))
			
			/* Frame pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETFP( ptr ) \
				asm volatile("movd %%ebp, %0" : "=r"(ptr))
			#define LIBANDRIA4_PLATSUPP_PROC_SETFP( ptr ) \
				asm volatile("movd %0, %%ebp" : : "r"(ptr))
			
		#else
			#error "Undefined.\n"
		#endif
		
		#if __STDC_VERSION__ >= 199901L
			
			#ifdef __STDC_NO_ATOMICS__
				#define LIBANDRIA4_SIGNAL_FENCE( var ) #error "??? signal fence hasn't been identified yet.\n"
				#define LIBANDRIA4_ATOMIC_FENCE( var ) #error "??? isn't known to support atomics.\n"
			#elif __STDC_VERSION__ >= 201112L
				#include <stdatomic.h>
				#define LIBANDRIA4_SIGNAL_FENCE( var ) atomic_signal_fence( var )
				#define LIBANDRIA4_ATOMIC_FENCE( var ) atomic_thread_fence( var )
			#else
				#define LIBANDRIA4_SIGNAL_FENCE( var ) #error "??? signal fence hasn't been identified yet.\n"
				#define LIBANDRIA4_ATOMIC_FENCE( var ) #error "??? atomic fence hasn't been identified yet.\n"
			#endif
			
		#else
			#error "Unknown C support level in platformdetect.h .\n"
		#endif
		
	#elif \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_TCC )
		/* Supported: */
			/* __TINYC__ : Tiny C Compiler. */
		/* Actually, does TCC support the ADVANCED GCC assembly syntax? */
		
		#if LIBANDRIA4_CELLTYPE_REGSIZE == 8
			
			/* Stack pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETSP( ptr ) \
				/* asm volatile("movq %%rsp, %0" : "=r"(ptr)) */
			#define LIBANDRIA4_PLATSUPP_PROC_SETSP( ptr ) \
				/* asm volatile("movq %0, %%rsp" : : "r"(ptr)) */
			
			/* Frame pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETFP( ptr ) \
				/* asm volatile("movq %%rbp, %0" : "=r"(ptr)) */
			#define LIBANDRIA4_PLATSUPP_PROC_SETFP( ptr ) \
				/* asm volatile("movq %0, %%rbp" : : "r"(ptr)) */
			
			#warning "TCC might not support the more advanced assembly format I'm using.\n"
			
		#elif LIBANDRIA4_CELLTYPE_REGSIZE == 4
			
			/* Stack pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETSP( ptr ) \
				/* asm volatile("movd %%esp, %0" : "=r"(ptr)) */
			#define LIBANDRIA4_PLATSUPP_PROC_SETSP( ptr ) \
				/* asm volatile("movd %0, %%esp" : : "r"(ptr)) */
			
			/* Frame pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETFP( ptr ) \
				/* asm volatile("movd %%ebp, %0" : "=r"(ptr)) */
			#define LIBANDRIA4_PLATSUPP_PROC_SETFP( ptr ) \
				/* asm volatile("movd %0, %%ebp" : : "r"(ptr)) */
			
			#warning "TCC might not support the more advanced assembly format I'm using.\n"
			
		#else
			
			#error "Undefined.\n"
			
		#endif
		
		#if __STDC_VERSION__ >= 199901L
			
			#define LIBANDRIA4_SIGNAL_FENCE( var ) /* TCC always spills are regs at each statement end. */
			#define LIBANDRIA4_ATOMIC_FENCE( var ) #error "TCC isn't known to support atomics.\n"
			
			#warning "TCC isn't known to support threads, but some systems in LibAndria4 require threads.\n"
			
		#else
			#error "Unknown C support level in platformdetect.h .\n"
		#endif
		
		
	#elif \
		( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == LIBANDRIA4_COMPILER_CODEBASE_MSVC )
		/* Supported: */
			/* _MSC_VER : MSVC. */
		
		#if LIBANDRIA4_CELLTYPE_REGSIZE == 8
			
			#error "MSVC doesn't support inline assembly, nor some needed intrinsics.\n"
			#error "\tRelated: the MASM alternates haven't been built yet.\n"
			#error "\tSee https://learn.microsoft.com/en-us/cpp/assembler/masm/masm-for-x64-ml64-exe?view=msvc-170\n"
			#error "\n"
			
		#elif LIBANDRIA4_CELLTYPE_REGSIZE == 4
			
			/* Stack pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETSP( ptr ) \
				__asm { mov esp, ptr }
			#define LIBANDRIA4_PLATSUPP_PROC_SETSP( ptr ) \
				__asm { mov ptr, esp }
			
			/* Frame pointers. */
			#define LIBANDRIA4_PLATSUPP_PROC_GETFP( ptr ) \
				__asm { mov ebp, ptr }
			#define LIBANDRIA4_PLATSUPP_PROC_SETFP( ptr ) \
				__asm { mov ptr, ebp }
			
		#else
			
			#error "Undefined.\n"
			
		#endif
		
		#if __STDC_VERSION__ >= 199901L
			
			#ifdef __STDC_NO_ATOMICS__
				#define LIBANDRIA4_SIGNAL_FENCE( var ) #error "MSVC signal fence hasn't been identified yet.\n"
				#define LIBANDRIA4_ATOMIC_FENCE( var ) #error "MSVC atomic fence hasn't been identified yet.\n"
			#elif __STDC_VERSION__ >= 201112L
				#include <stdatomic.h>
				#define LIBANDRIA4_SIGNAL_FENCE( var ) atomic_signal_fence( var )
				#define LIBANDRIA4_ATOMIC_FENCE( var ) atomic_thread_fence( var )
			#else
				#define LIBANDRIA4_SIGNAL_FENCE( var ) #error "MSVC signal fence hasn't been identified yet.\n"
				#define LIBANDRIA4_ATOMIC_FENCE( var ) #error "MSVC atomic fence hasn't been identified yet.\n"
			#endif
			
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
		
		/* Stack pointers. */
		#define LIBANDRIA4_PLATSUPP_PROC_GETSP( ... ) \
			#error "The currently detected compiler DOES NOT support *_PLATSUPP_PROC_GETSP().\n"
		#define LIBANDRIA4_PLATSUPP_PROC_SETSP( ... ) \
			#error "The currently detected compiler DOES NOT support *_PLATSUPP_PROC_SETSP().\n"
		
		/* Frame pointers. */
		#define LIBANDRIA4_PLATSUPP_PROC_GETSP( ... ) \
			#error "The currently detected compiler DOES NOT support *_PLATSUPP_PROC_GETFP().\n"
		#define LIBANDRIA4_PLATSUPP_PROC_GETFP( ... ) \
			#error "The currently detected compiler DOES NOT support *_PLATSUPP_PROC_GETFP().\n"
		
	#endif
	
	
	
	
	
	
	
	
	
	/* Set the actual feature -test / -detect macros. */
	/* Note that TCC, GCC, Clang, and MSVC all use the same approach, which */
	/*  includes <stdint.h>: this may confuse error detection at some later */
	/*  point. */
	#else
		#error "Unknown compiler.\n"
		
	#endif
	
#endif
/* End libandria4 basic platformsupport.h */
