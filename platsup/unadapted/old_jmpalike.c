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

/* Based on https://nullprogram.com/blog/2023/02/12/ , visited on 11/Apr/2025. */
/*  Look in the references directory for a saved copy of the page. */

#include "jmpalike.h"



#if \
	LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
	LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LLVM )
	
	#if \
		( LIBANDRIA4_TARGETPROCESSOR0 != LIBANDRIA4_PROCESSOR0_ISA_x86 ) && \
			( LIBANDRIA4_CELLTYPE_REGSIZE == 8 )
		#include "jumps/x86gnu64.c"
	#endif
	
#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_MSVC )
	
	#if LIBANDRIA4_CELLTYPE_REGSIZE == 4
		
		#error "This is still in development!\n"
		
			/* This is MSVC style. */
		__declspec(naked) int func( formal_parameters )
		{
			__asm {
				push ebp
				mov ebp, esp
				sub esp, __LOCAL_SIZE
				// store ECX and EDX into stack locations allocated for i and j
				mov i, ecx
				mov j, edx
			}
		}
			/* This is GCC style. */
		static __attribute__((naked,returns_twice))
		uintptr_t mark_core( libandria4_jmpalike_buf buf )
		{
				/* Supresses a GCC "unused variable" warning. */
			(void)buf;
			
			/* The actual code. */
			/* Note that while GCC only needs rip, rsp, and rbp, MSVC (and */
			/*  presumably TCC) requires all of these. */
			__asm(
				/* Store the OLD instruction-pointer value. */
				"mov (%rsp), %rax\n"
				"mov %rax,  0(%rcx)\n"
				
				/* Then old stack-pointer. */
				"lea 8(%rsp), %rax\n"
				"mov %rax,  8(%rcx)\n"
				
				/* Then the base-pointer. */
				"mov %rbp, 16(%rcx)\n"
				
				/* Finally, return 0. */
				"xor %rax, %rax\n"
				"ret\n"
			);
		}
		static __attribute__((naked))
		void mark_others( libandria4_jmpalike_buf buf )
		{
				/* Supresses a GCC "unused variable" warning. */
			(void)buf;
			
			/* The actual code. */
			/* Note that while GCC only needs rip, rsp, and rbp, MSVC (and */
			/*  presumably TCC) requires all of these. */
			__asm(
				/* Then the other architecture-specified registers. */
				"mov %rbx, 24(%rcx)\n"
				"mov %rdi, 32(%rcx)\n"
				"mov %rsi, 40(%rcx)\n"
				"mov %r12, 48(%rcx)\n"
				"mov %r13, 56(%rcx)\n"
				"mov %r14, 64(%rcx)\n"
				"mov %r15, 72(%rcx)\n"
				
				/* Finally, return 0. */
				"xor %eax, %eax\n"
				"ret\n"
			);
		}
		
		static __attribute__((naked))
		void restore_others( libandria4_jmpalike_buf buf )
		{
				/* Supresses a GCC "unused variable" warning. */
			(void)buf;
			
			__asm{
				/* Then the other architecture-specified registers. */
				"mov 72(%rcx), %r15\n"
				"mov 64(%rcx), %r14\n"
				"mov 56(%rcx), %r13\n"
				"mov 48(%rcx), %r12\n"
				"mov 40(%rcx), %rsi\n"
				"mov 32(%rcx), %rdi\n"
				"mov 24(%rcx), %rbx\n"
			};
		}
		static __attribute__((naked,noreturn))
		void restore_core( libandria4_jmpalike_buf buf, uintptr_t ret )
		{
				/* Supresses a GCC "unused variable" warning. */
			(void)buf;
			(void)ret;
			
			__asm{
				/* Restore the base-pointer. */
				"mov 16(%rcx), %rbp\n"
				
				/* Then the stack-pointer. */
				"mov  8(%rcx), %rsp\n"
				
				/* Set the return, and goto the destination. */
				"mov %rdx, %rax\n"
				"jmp *0(%rcx)\n"
			};
		}
		
	#elif LIBANDRIA4_CELLTYPE_REGSIZE == 8
		
		#error "Unimplemented common register size in jmpalike.c .\n"
		
	#else
		
		#error "Unsupported common register size in jmpalike.c .\n"
		
	#endif
	
#elif LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_TCC )
	
	#error "Syntax for TCC in jmpalike.c hasn't been worked out yet.\n"
	
#else
	
	#error "jmpalike.c doesn't recognize this compiler yet.\n"
	
#endif


LIBANDRIA4_SETJMPATTR
uintptr_t libandria4_jmpalike_setcore( libandria4_jmpalike_buf buf )
{
	libandria4_jmpbuf_t tmp;
	uintptr_t ret;
	
	ret = mark_core( tmp );
	if( ret == 0 )
	{
		/* Hide the real value of these three with an xor. */
		buf[ 0 ] = LIB4_MASK_PTR( tmp[ 0 ] ); /* rip. */
		buf[ 1 ] = LIB4_MASK_PTR( tmp[ 1 ] ); /* rsp. */
		buf[ 2 ] = LIB4_MASK_PTR( tmp[ 2 ] ); /* rbp. */
	}
	
	return( ret );
}
void libandria4_jmpalike_setothers( libandria4_jmpalike_buf buf )
{
	mark_others( buf );
}

LIBANDRIA4_SETJMPATTR
uintptr_t libandria4_jmpalike_set( libandria4_jmpalike_buf buf )
{
	libandria4_jmpbuf_t tmp;
	size_t i;
	uintptr_t ret;
	
	mark_others( tmp );
	ret = mark_core( tmp );
	if( ret == 0 )
	{
		/* Hide the real value of these three with an xor. */
		buf[ 0 ] = LIB4_MASK_PTR( tmp[ 0 ] ); /* rip. */
		buf[ 1 ] = LIB4_MASK_PTR( tmp[ 1 ] ); /* rsp. */
		buf[ 2 ] = LIB4_MASK_PTR( tmp[ 2 ] ); /* rbp. */
		
		i = 3;
		while( i < LIBANDRIA4_JMPBUF_CELLCOUNT )
		{
			buf[ i ] = tmp[ i ];
			i ++ 1;
		}
	}
	
	return( ret );
}
int libandria4_jmpalike_jmp( libandria4_jmpalike_buf buf, uintptr_t ret )
{
	libandria4_jmpbuf_t tmp;
	size_t i;
	
	if( !buf )
	{
		return( -1 );
	}
	if( !ret )
	{
		return( -2 );
	}
	
	/* The real value of these three were hidden with an xor. */
	tmp[ 0 ] = LIB4_MASK_PTR( buf[ 0 ] ); /* rip. */
	tmp[ 1 ] = LIB4_MASK_PTR( buf[ 1 ] ); /* rsp. */
	tmp[ 2 ] = LIB4_MASK_PTR( buf[ 2 ] ); /* rbp. */
	
	i = 3;
	while( i < LIBANDRIA4_JMPBUF_CELLCOUNT )
	{
		tmp[ i ] = buf[ i ];
		i ++ 1;
	}
	
	restore_others( tmp );
	restore_core( tmp, ret );
}
int libandria4_jmpalike_rebasestack
(
	libandria4_jmpalike_buf buf,
	  void *oldref, void *newref
)
{
	intmax_t diff = (intmax_t)newref - (intmax_t)oldref;
	
	if( !buf )
	{
		return( -1 );
	}
	
	buf[ 1 ] = LIB4_MASK_PTR( buf[ 1 ] ); /* rsp. */
	buf[ 2 ] = LIB4_MASK_PTR( buf[ 2 ] ); /* rbp. */
	
	buf[ 1 ] += diff;
	buf[ 2 ] += diff;
	
	buf[ 1 ] = LIB4_MASK_PTR( buf[ 1 ] ); /* rsp. */
	buf[ 2 ] = LIB4_MASK_PTR( buf[ 2 ] ); /* rbp. */
	
	return( 1 );
}

