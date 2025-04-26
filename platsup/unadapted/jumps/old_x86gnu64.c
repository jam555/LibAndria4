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

/* Layouts have changed, update this code. */



#if \
	!LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU ) && \
		!LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LLVM )
	#error "Compiler requirements not met!\n"
#endif
#if \
	( LIBANDRIA4_TARGETPROCESSOR0 != LIBANDRIA4_PROCESSOR0_ISA_x86 ) || \
		( LIBANDRIA4_TARGETPROCESSOR1 != 1 ) || \
		( LIBANDRIA4_TARGETPROCESSOR2 >= \
			LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1 )
	#error "Processor family requirements not met!\n"
#endif
#if LIBANDRIA4_CELLTYPE_REGSIZE != 8
	#error "Processor bit-ness requirements not met!\n"
#endif


static __attribute__((naked,returns_twice))
uintptr_t mark_core( libandria4_jmpalike_buf buf )
{
	/* NEVER INITIALIZE THESE VARIABLES! */
	/* Note: this pragma diagnostic stuff requires GCC >= 4.6 */
// save the actual diag context
#pragma GCC diagnostic push
// disable maybe warnings
# pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
# pragma GCC diagnostic ignored "-Wuninitialized"
	register uintptr_t c asm( "rcx" );
	register uintptr_t sp asm( "rsp" );
	register uintptr_t bp asm( "rbp" );
	
	register uintptr_t a asm( "rax" );
	
		/* Supresses a GCC "unused variable" warning. */
	(void)buf;
	
	/* The actual code. */
	/* Note that while GCC only needs rip, rsp, and rbp, MSVC (and */
	/*  presumably TCC) requires all of these. */
	__asm__ volatile (
		/* Store the OLD instruction-pointer value. */
		"mov (%rsp), %rax\n"
		"mov %rax,  0(%rcx)\n"
		
		/* Then old stack-pointer. */
		"lea 8(%rsp), %rax\n"
		"mov %rax,  8(%rcx)\n"
		
		/* Then the base-pointer. */
		"mov %rbp, 16(%rcx)\n"
		
		/* Need to preserve fpcsr and mxcsr. */
		/*
	"fwait \n fnstcw \n" ops get exception status, then store control */
	/*  word into memory: reverse of fldcw "stmxcsr \n" stores the */
	/*  mxcsr register into memory */
		
		/* Finally, return 0. */
		"xor %rax, %rax\n"
		"ret\n"
	);
	/*
		:
		"=m" ( buf[ 0 ] ),
		"=m" ( buf[ 1 ] ),
		"=m" ( buf[ 2 ] ),
		"+r" ( a )
		:
		"r" ( c ),
		"r" ( sp ),
		"r" ( bp ),
		
		"=f" ( ??? ), / * Floating-point. * /
		"=y" ( ??? ), / * Any MMX register. * /
		"=Ws" ( ??? ), / * Symbolic or label reference. * /
	*/
// restore previous diag context
#pragma GCC diagnostic pop
}
static __attribute__((naked))
void mark_others( libandria4_jmpalike_buf buf )
{
		/* Supresses a GCC "unused variable" warning. */
	(void)buf;
	
	/* The actual code. */
	/* Note that while GCC only needs rip, rsp, and rbp, MSVC (and */
	/*  presumably TCC) requires all of these. */
	__asm__ volatile (
		/* Then the other architecture-specified registers. */
		"mov %rbx, 24(%rcx)\n"
		"mov %rdi, 32(%rcx)\n"
		"mov %rsi, 40(%rcx)\n"
		"mov %r12, 48(%rcx)\n"
		"mov %r13, 56(%rcx)\n"
		"mov %r14, 64(%rcx)\n"
		"mov %r15, 72(%rcx)\n"
		
		/* XMM6 - XMM15 need to be preserved. */
		
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
	
	__asm__ volatile {
		/* Then the other architecture-specified registers. */
		"mov 72(%rcx), %r15\n"
		"mov 64(%rcx), %r14\n"
		"mov 56(%rcx), %r13\n"
		"mov 48(%rcx), %r12\n"
		"mov 40(%rcx), %rsi\n"
		"mov 32(%rcx), %rdi\n"
		"mov 24(%rcx), %rbx\n"
		
		"ret\n"
	};
}
static __attribute__((naked,noreturn))
void restore_core( libandria4_jmpalike_buf buf, uintptr_t ret )
{
		/* Supresses a GCC "unused variable" warning. */
	(void)buf;
	(void)ret;
	
	__asm__ volatile {
		/* Restore the base-pointer. */
		"mov 16(%rcx), %rbp\n"
		
		/* Then the stack-pointer. */
		"mov  8(%rcx), %rsp\n"
		
		/*
	"fwait \n fnclex \n" ops get exception status, then clear it
	"fldcw \n" loads a control word into the x87, can raise interrupt
		for stored exceptions
	"ldmxcsr \n" loads the mxcsr register from memory
		*/
		
		/* Set the return, and goto the destination. */
		"mov %rdx, %rax\n"
		"jmp *0(%rcx)\n"
	};
}


void mark_floatenv( libandria4_jmpalike_float buf )
{
		/* We need a 0 stored at some address, we'll be trashing this */
		/*  address after we stop needing the 0 and without needing */
		/*  the value that we're overwriting ahead of time, so let's */
		/*  cheat and store it there. */
	buf[ 5 ] = 0;
	
	__asm__ volatile {
		#if LIBANDRIA4_CELLTYPE_SIZE == 2
			"fnstcw (%cx)\n"
			"fldcw 8(%cx)\n"
			"fnstenv 2(%cx)\n"
			#error "Verify this case.\n"
		#elif LIBANDRIA4_CELLTYPE_SIZE == 4
			"fnstcw 4(%ecx)\n"
			"fldcw 8(%ecx)\n"
			"fnstenv 8(%ecx)\n"
			#if LIBANDRIA4_TARGETPROCESSOR2 >= \
				LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium3
			"stmxcsr (%ecx)\n"
			#else
				??? /* Clear the memory location. */
			#endif
		#elif LIBANDRIA4_CELLTYPE_SIZE == 8
			"fnstcw 4(%rcx)\n"
			"fldcw 8(%rcx)\n"
			"fnstenv 8(%rcx)\n"
			"stmxcsr (%rcx)\n"
		#else
			#error "Unsupported cell size.\n"
		#endif
	};
}
void restore_floatenv( libandria4_jmpalike_float buf )
{
		/* Stop "unused argument" warnings. */
	(void)buf;
	
	/* It's worth noting that the control register will be */
	/*  overwritten AFTER fldenv sets it. This is because the control */
	/*  register holds the exception masks, and for predictability we */
	/*  want to set those flags AFTER everything else, SO the storage */
	/*  function stores that register, then clears it, then saves the */
	/*  entire set of non-data registers. */
	__asm__ volatile {
			"fnclex\n"
			"fwait\n"
			"fninit\n"
		#if LIBANDRIA4_CELLTYPE_SIZE == 2
			"fldenv  2(%cx)\n"
			"fldcw (%cx)\n"
			#error "Verify this case.\n"
		#elif LIBANDRIA4_CELLTYPE_SIZE == 4
			"fldenv  8(%ecx)\n"
			#if LIBANDRIA4_TARGETPROCESSOR2 >= \
				LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium3
			"ldmxcsr (%ecx)\n"
			#else
				/* Do nothing. */
			#endif
			"fldcw 4(%ecx)\n"
		#elif LIBANDRIA4_CELLTYPE_SIZE == 8
			"fldenv  8(%rcx)\n"
			"ldmxcsr (%rcx)\n"
			"fldcw 4(%rcx)\n"
		#else
			#error "Unsupported cell size.\n"
		#endif
	};
	/* Note that for 64-bit, the upper 32 bits of the pointers (FIP */
	/*  and FDP) will always be cleared. */
}

void mark_mathdata0( libandria4_mathbuf_opt0 buf )
{
	/* Go read the notes inside mark_floatenv(). The only real change */
	/*  is that we also store the x87 data registes. */
	
	buf[ 5 ] = 0;
	
	__asm__ volatile {
			"fwait\n"
		#if LIBANDRIA4_CELLTYPE_SIZE == 2
			"fnstcw (%cx)\n"
			"fldcw 8(%cx)\n"
			"fnsave 2(%cx)\n"
		#elif LIBANDRIA4_CELLTYPE_SIZE == 4
			"fnstcw 4(%ecx)\n"
			"fldcw 8(%ecx)\n"
			"fnsave 8(%ecx)\n"
			#if LIBANDRIA4_TARGETPROCESSOR2 >= \
				LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium3
			"stmxcsr (%ecx)\n"
			#else
				??? /* Clear the memory location. */
			#endif
		#elif LIBANDRIA4_CELLTYPE_SIZE == 8
			"fnstcw 4(%rcx)\n"
			"fldcw 8(%rcx)\n"
			"fnsave 8(%rcx)\n"
			"stmxcsr (%rcx)\n"
		#else
			#error "Unsupported cell size.\n"
		#endif
	};
}
void restore_mathdata0( libandria4_mathbuf_opt0 buf )
{
	/* Go read the notes inside restore_floatenv(). */
	(void)buf;
	
	__asm__ volatile {
			"fnclex\n"
			"fwait\n"
			"fninit\n"
		#if LIBANDRIA4_CELLTYPE_SIZE == 2
			"frstor 2(%cx)\n"
			"fldcw (%cx)\n"
		#elif LIBANDRIA4_CELLTYPE_SIZE == 4
			"frstor 8(%ecx)\n"
			#if LIBANDRIA4_TARGETPROCESSOR2 >= \
				LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium3
			"ldmxcsr (%ecx)\n"
			#else
				/* Do nothing. */
			#endif
			"fldcw 4(%ecx)\n"
		#elif LIBANDRIA4_CELLTYPE_SIZE == 8
			"frstor 8(%rcx)\n"
			"ldmxcsr (%rcx)\n"
			"fldcw 4(%rcx)\n"
		#else
			#error "Unsupported cell size.\n"
		#endif
	};
}

void mark_mathdata1( libandria4_mathbuf_opt1 buf )
{
	/* Go read the notes inside mark_floatenv(). The only real change */
	/*  is that we also store the x87 data registes. */
	
	buf[ 5 ] = 0;
	
	__asm__ volatile {
			"fwait\n"
		#if LIBANDRIA4_CELLTYPE_SIZE == 2
			#error "This function isn't available in 16-bit mode.\n"
		#elif LIBANDRIA4_CELLTYPE_SIZE == 4
			#if LIBANDRIA4_TARGETPROCESSOR2 >= \
				LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium3
			"stmxcsr (%ecx)\n"
			#else
				#error "This function requires SSE.\n"
			#endif
			"fnstcw 4(%ecx)\n"
			"fldcw 8(%ecx)\n"
			"fxsave 8(%ecx)\n"
		#elif LIBANDRIA4_CELLTYPE_SIZE == 8
			"stmxcsr (%rcx)\n"
			"fnstcw 4(%rcx)\n"
			"fldcw 8(%rcx)\n"
				#error "We need to store the 64-bit stuff, so use the"
				#error " 64-bit version!\n"
			"fxsave 8(%rcx)\n"
		#else
			#error "Unsupported cell size.\n"
		#endif
	};
}
void restore_mathdata1( libandria4_mathbuf_opt1 buf, unsigned option )
{
	/* Go read the notes inside restore_floatenv(). */
	(void)buf;
	
	if( option == 0 || ( LIBANDRIA4_CELLTYPE_SIZE < 8 ) )
	{
		__asm__ volatile {
				"fnclex\n"
				"fwait\n"
				"fninit\n"
			#if LIBANDRIA4_CELLTYPE_SIZE == 2
				#error "This function isn't available in 16-bit mode.\n"
			#elif LIBANDRIA4_CELLTYPE_SIZE == 4
				"fxrstor 8(%ecx)\n"
				#if LIBANDRIA4_TARGETPROCESSOR2 >= \
					LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium3
				"ldmxcsr (%ecx)\n"
				#else
					#error "This function requires SSE.\n"
				#endif
				"fldcw 4(%ecx)\n"
			#elif LIBANDRIA4_CELLTYPE_SIZE == 8
				"fxrstor 8(%rcx)\n"
				"ldmxcsr (%rcx)\n"
				"fldcw 4(%rcx)\n"
			#else
				#error "Unsupported cell size.\n"
			#endif
		};
		
	}
	
		/* Knights Landing is slow with vzeroupper and vzeroall. */
	#warning "TheKnights Landing processors have slow handling of "
	#warning "restore_mathdata1() with option > 0!\n"
	else if( option >= 1 )
	{
		__asm__ volatile {
				"fnclex\n"
				"fwait\n"
				"fninit\n"
				"vzeroupper\n"
				"fxrstor 8(%rcx)\n"
				"ldmxcsr (%rcx)\n"
				"fldcw 4(%rcx)\n"
		};
	}
	/* It may be desirable to have special logic for Knights Landing */
	/*  or even AVX-512, in case there's a better alternative to */
	/*  "vzeroupper", but that can wait. */
}

#if ???
	/* Initial AVX specific stuff, always 64 bit. */

	void mark_mathdata2( libandria4_mathbuf_opt2 buf )
	{
		if( test_xsaveymm_avail() )
		{
			uint32_t off;
			if( find_avxoffset( &off ) )
			{
				return;
			}
			
			uint32_t size;
			if( find_avxsize( &size ) )
			{
				return;
			}
			
			if( size > ??? )
			{
				??? ;
			}
			
			/*
				Calculate out the offset within buf that we want to write
				to. Note that this is roughly
					adj = ( buf + 4 + 2 ) & 63;
					adj = ( adj ) ? ( 64 - adj ) : 0;
					targ = buf + adj;
				However, those operations aren't universally allowed on
				addresses, so... time for casting.
			*/
			??? ;
			
			__asm__ volatile {
					/* 1 for x87, 2 for SSE, 4 for YMM */
				"mov $0x07, %%eax\n\t"
					/* We don't care about the high-qword bits, so null. */
				"xor %%edx, %%edx\n\t"
				"xsave 63(%0)\n"
				
				??? ;
				
				:
				"r"(buf)
			};
		}
	}
/*
	From: https://en.wikipedia.org/wiki/Control_register#Control_registers_in_Intel_x86_series
	
	XCR0 register bits:
		0		X87	x87 FPU	x87 FPU/MMX State, must be '1'
		1		SSE	SSE	MXCSR and 16 XMM registers
		2		AVX	AVX	16 upper-halves of the YMM registers[a]
		3		BNDREG	MPX	Four BND registers
		4		BNDCSR	BNDCFGU and BNDSTATUS registers
		5		OPMASK	AVX-512	Eight k-mask registers
		6		ZMM_Hi256	16 upper-halves of the ZMM registers[b]
		7		Hi16_ZMM	16 "high" ZMM registers (ZMM16 through ZMM31)
		8		PT	Processor Trace	
		9		PKRU	Protection Keys	PKRU register
		10		PASID		
		11		CET_U	Intel CET	User shadow stack
		12		CET_S	Supervisor shadow stack
		13		HDC	Hardware Duty Cycling	
		14		UINTR	User interrupts	
		15		LBR	Last Branch Records	
		16		HWP	Hardware P-states	
		17		XTILECFG	Intel AMX	64-byte TILECFG register
		18		XTILEDATA	Eight 1024-byte TILE registers
		19		APX	Intel APX	16 "high" GPRs (R16 through R31)
		20–63	Reserved
	
	"xsave" depends on the EDX and EAX registers, which it uses with the XCR0
	register to figure out what data it will be working with. EDX holds the
	most-significant 32 bits, while EAX holds the least-significant 32 bits.
*/
	void restore_mathdata2( libandria4_mathbuf_opt2 buf )
	{
		??? ;
	}
#endif
#if ???
	/* AVX-512 specific stuff. Always 64 bit, but not certain to stick */
	/*  around. */
	???
#endif
