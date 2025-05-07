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



#include "../jmpalike.h"
#include "../platsup/x86.h"

	/* Compiler compatibility. */
#if \
	!LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU ) && \
		LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LLVM )!
	#error "Unrecognized compiler in x86gnu64.c\n"
#endif

	/* General processor compatibility. */
#if \
	( LIBANDRIA4_TARGETPROCESSOR0 != LIBANDRIA4_PROCESSOR0_ISA_x86 ) && \
		( LIBANDRIA4_CELLTYPE_REGSIZE == 8 )
	#error "Unrecognized processor family in x86gnu64.c\n"
#endif

	/* "Native size" processor compatibility. */
#if LIBANDRIA4_CELLTYPE_REGSIZE != 8
	#error "Unsupported processor bit-size in x86gnu64.c\n"
#endif



/*
	The x64 ABI considers registers RSP, RBP, RBX, RDI, RSI, R12, R13, R14,
	R15, and XMM6-XMM15 nonvolatile. A call to setjmp preserves the current
	stack pointer, nonvolatile registers, FPCSR, and MXCSR registers.
	
	In this code, we divide setjmp() into two parts, one for the stuff that GCC
	does need (core), and another for the stuff that GCC supposedly doesn't need
	(others).
*/
/*
 When present, the upper portions of YMM0-YMM15 and ZMM0-ZMM15 are also volatile.
 On AVX512VL, the ZMM, YMM, and XMM registers 16-31 are also volatile. When AMX
 support is present, the TMM tile registers are volatile. Consider volatile
 registers destroyed on function calls unless otherwise safety-provable by
 analysis such as whole program optimization.
*/
static __attribute__((naked,returns_twice))
intptr_t jmpalike_setcore( libandria4_jmpalike_buf buf )
{
		/* Supresses a GCC "unused variable" warning. */
	(void)buf;
	
	__asm__ volatile (
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
void jmpalike_setothers( libandria4_jmpalike_buf buf )
{
		/* Supresses a GCC "unused variable" warning. */
	(void)buf;
	
	/* The actual code. */
	/* Note that while GCC only needs rip, rsp, and rbp, MSVC (and */
	/*  presumably TCC) requires all of these. */
	__asm__ volatile (
		/*
			The x64 ABI also considers registers RBX, RDI, RSI, R12, R13, R14,
			and R15 non-volatile (so the callee must preserve them)...
		*/
		"mov %rbx, 24(%rcx)\n"
		"mov %rdi, 32(%rcx)\n"
		"mov %rsi, 40(%rcx)\n"
		"mov %r12, 48(%rcx)\n"
		"mov %r13, 56(%rcx)\n"
		"mov %r14, 64(%rcx)\n"
		"mov %r15, 72(%rcx)\n"
		
		/* ... as well as FPCSR ... */
		"fnstcw 80(%rcx)\n"
		
		/* ... then we leave a blank two bytes at 82 & 83, and eight bytes */
		/*  from 84 to 91 ... */
		
		/* ... and MXCSR... */
		"stmxcsr 92(%rcx)\n"
		
		/* ... and XMM6-XMM15. */
		"movdqa %xmm6, 96(%rcx)\n"
		"movdqa %xmm7, 112(%rcx)\n"
		"movdqa %xmm8, 128(%rcx)\n"
		"movdqa %xmm9, 144(%rcx)\n"
		"movdqa %xmm10, 160(%rcx)\n"
		"movdqa %xmm11, 176(%rcx)\n"
		"movdqa %xmm12, 192(%rcx)\n"
		"movdqa %xmm13, 208(%rcx)\n"
		"movdqa %xmm14, 224(%rcx)\n"
		"movdqa %xmm15, 240(%rcx)\n"
		
		/* Finally, return. */
		"ret\n"
	);
}

static __attribute__((naked))
void jmpalike_loadothers( libandria4_jmpalike_buf buf )
{
		/* Supresses a GCC "unused variable" warning. */
	(void)buf;
	
	__asm__ volatile (
		/* Reload the general-purpose registers. */
		"mov 24(%rcx), %rbx\n"
		"mov 32(%rcx), %rdi\n"
		"mov 40(%rcx), %rsi\n"
		"mov 48(%rcx), %r12\n"
		"mov 56(%rcx), %r13\n"
		"mov 64(%rcx), %r14\n"
		"mov 72(%rcx), %r15\n"
		
		/* Reload MXCSR (part of SSE). */
		"ldmxcsr 92(%rcx)\n"
		
		/* Reload the SSE data registers. */
		"movdqa 96(%rcx), %xmm6\n"
		"movdqa 112(%rcx), %xmm7\n"
		"movdqa 128(%rcx), %xmm8\n"
		"movdqa 144(%rcx), %xmm9\n"
		"movdqa 160(%rcx), %xmm10\n"
		"movdqa 176(%rcx), %xmm11\n"
		"movdqa 192(%rcx), %xmm12\n"
		"movdqa 208(%rcx), %xmm13\n"
		"movdqa 224(%rcx), %xmm14\n"
		"movdqa 240(%rcx), %xmm15\n"
		
		/* Delay this to here in case we have lurking x87 errors. */
		"fldcw 80(%rcx)\n"
		
		/* Finally, return. */
		"ret\n"
	};
}
__attribute__((naked,noreturn))
void jmpalike_jmpcore( libandria4_jmpalike_buf buf, intptr_t ret )
{
    (void)buf;
    (void)ret;
    
    __asm__ volatile (
        "mov 16(%rcx), %rbp\n"
        "mov  8(%rcx), %rsp\n"
        "mov %rdx, %rax\n"
        "jmp *0(%rcx)\n"
    );
}
