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

#include "../support.h"

#ifndef LIBANDRIA4_PLATSUP_PLATSUP_X86_H
# define LIBANDRIA4_PLATSUP_PLATSUP_X86_H
	
	#if !defined( LIBANDRIA4_TARGETPROCESSOR0 )
		#error "platsup x86.h didn't find LIBANDRIA4_TARGETPROCESSOR0.\n"
	#endif
	#if LIBANDRIA4_TARGETPROCESSOR0 != LIBANDRIA4_PROCESSOR0_ISA_x86
		#error "platsup x86.h found a non-x86 *_TARGETPROCESSOR0.\n"
	#endif
	#if LIBANDRIA4_TARGETPROCESSOR1 != 1
		#error "platsup x86.h found a non-mainline *_TARGETPROCESSOR1.\n"
	#endif
	
	
	
	#if LIBANDRIA4_TARGETPROCESSOR0 != LIBANDRIA4_PROCESSOR0_ISA_x86
		uintptr_t libandria4_ptrhash( size_t len, char *str );
			/* Was called LIB4_MASK_PTR(). */
		#define LIBANDRIA4_MASK_PTR( ptrtype, val ) \
			( (ptrtype)( (uintptr_t)( val ) ^ \
				libandria4_ptrhash( strlen( __DATE__ ), __DATE__ ) ^ \
				libandria4_ptrhash( strlen( __TIME__ ), __TIME__ ) ^ \
				libandria4_ptrhash( strlen( __TIMESTAMP__ ), __TIMESTAMP__ ) ) )
	#endif
	
	#if \
		LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
		LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LLVM ) || \
		LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_TCC )
		/* Supported: */
			/* __GNUC__ : GCC C/C++. */
			/* __llvm__ and/or __clang__ : LLVM C / Clang. */
			/* __TINYC__ : Tiny C Compiler. */
		
		#if LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_TCC )
			#warning "TCC might not support the more advanced assembly format"
			#warning " I'm using.\n"
		#endif
		
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
				#define LIBANDRIA4_SIGNAL_FENCE( ) \
					#error "??? signal fence hasn't been identified yet.\n"
				#define LIBANDRIA4_ATOMIC_FENCE( ) \
					#error "??? isn't known to support atomics.\n"
			#elif __STDC_VERSION__ >= 201112L
				#include <stdatomic.h>
				#define LIBANDRIA4_SIGNAL_FENCE( ) \
					atomic_signal_fence( memory_order_seq_cst )
				#define LIBANDRIA4_ATOMIC_FENCE( ) \
					atomic_thread_fence( memory_order_seq_cst )
			#else
				#define LIBANDRIA4_SIGNAL_FENCE( ) \
					#error "??? signal fence hasn't been identified yet.\n"
				#define LIBANDRIA4_ATOMIC_FENCE( ) \
					#error "??? atomic fence hasn't been identified yet.\n"
			#endif
			
		#else
			#error "Unknown C support level in platformdetect.h .\n"
		#endif
		
	#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_MSVC )
		/* Supported: */
			/* _MSC_VER : MSVC. */
		
		#if LIBANDRIA4_CELLTYPE_REGSIZE == 8
			
			#error "MSVC doesn't support inline assembly, nor some needed"
			#error " intrinsics.\n"
			#error "\tRelated: the MASM alternates haven't been built yet.\n"
			#error "\tSee https://learn.microsoft.com/en-us/cpp/assembler/masm/"
			#error " masm-for-x64-ml64-exe?view=msvc-170\n"
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
				#define LIBANDRIA4_SIGNAL_FENCE( var ) \
					#error "MSVC signal fence hasn't been identified yet.\n"
				#define LIBANDRIA4_ATOMIC_FENCE( var ) \
					#error "MSVC atomic fence hasn't been identified yet.\n"
			#elif __STDC_VERSION__ >= 201112L
				#include <stdatomic.h>
				#define LIBANDRIA4_SIGNAL_FENCE( var ) \
					atomic_signal_fence( var )
				#define LIBANDRIA4_ATOMIC_FENCE( var ) \
					atomic_thread_fence( var )
			#else
				#define LIBANDRIA4_SIGNAL_FENCE( var ) \
					#error "MSVC signal fence hasn't been identified yet.\n"
				#define LIBANDRIA4_ATOMIC_FENCE( var ) \
					#error "MSVC atomic fence hasn't been identified yet.\n"
			#endif
			
		#else
			#error "Unknown C support level in platformdetect.h .\n"
		#endif
		
	#else
		
		#error "LibAndria4 platsup x86.h doesn't yet support this compiler.\n"
		
	#endif
	
	
	
	#if LIBANDRIA4_TARGETPROCESSOR0 != LIBANDRIA4_PROCESSOR0_ISA_x86
		#warning "AVX-512 isn't currently paid attention to, fix that.\n"
		
		int libandria4_cpuid
		(
			uint32_t leaf, uint32_t subleaf,
			uint32_t *ret, char *name
		);
		int libandria4_cpuid_x86_xsaveavail();
		int libandria4_cpuid_x86_avxavail();
		int libandria4_cpuid_x86_avxoffset( uint32_t *off );
		int libandria4_cpuid_x86_avxsize( uint32_t *sz );
	#else
		#error "Only x86 has been developed for, fixing that is suggested.\n"
	#endif
	
#endif
/* End LibAndria4 platsup platsup x86.h */
