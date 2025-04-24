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

/* Attention users! jetjmp()/longjmp() have unpredictable interations with */
/*  compiler optimizations, so if your variables might get updated after */
/*  setjmp(), then analyze them to figure out which need to be tagged */
/*  "volatile". */


#include "platformdetect.h"


/*
	Floating point: for generic access, include fenv.h
		for x86, referencing https://www.felixcloutier.com/ :
			"RDSSPD \n" read shadow-stack pointer
			Note: look up the other shadow-stack stuff
			
			"fwait \n" check for and handle pending exceptions that aren't
			* 	 masked before proceeding
			"fwait \n finit \n" ops get the exception status, then clear the
			* 	 whole x87
			"fwait \n fnstsw \n" ops get the exception status (use for
			* 	 dispatching, not setjmp).
			"fnop \n" does nothing but take space, time, & increment x86 & x87
			* 	 ip pointers: use for alignment
			"fldenv \n" loads the entire x87 state from memory, should execute
			* 	 from same mode as the store
			"fwait \n fnstenv \n" ops get exscept. status, then store all x87
			* 	 state expect stack vals to mem: reverse of fldenv
			"frstor \n" loads an entire x87 state, including stack
			"fwait \n fnsave \n" ops do fnstenv, then store stack, then finit:
			* 	 reverse of frstor
			
			"fxrstor \n" Reloads the x87 FPU, MMX technology, XMM, and MXCSR
			* 	 registers
			"fxsave \n" reverse of fxrstor
			
			"pause \n" a no-op specifically used to mark spin-loops: a hint that
			* 	 memory-order problems PROBABLY won't happen
			
			"rdpid \n" get the processor id
*/

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
	*  most-significant 32 bits, while EAX holds the least-significant 32 bits.
*/


typedef void *libandria4_jmpalike_buf[ LIBANDRIA4_JMPBUF_CELLCOUNT ];
typedef uint16_t libandria4_jmpalike_float[ LIBANDRIA4_FLOATBUF_CELLCOUNT ];

#if ???
typedef uint16_t libandria4_mathbuf_opt0[ LIBANDRIA4_MATHBUF_OPTSIZE_x87 ];
#elif ???
typedef uint16_t libandria4_mathbuf_opt0[ LIBANDRIA4_MATHBUF_OPTSIZE_x87 ];
	#if \
		( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_GNU
typedef uint16_t libandria4_mathbuf_opt1[ LIBANDRIA4_MATHBUF_OPTSIZE_SSE ]
	__attribute__ ((aligned (16)));
typedef uint16_t libandria4_mathbuf_opt2[ LIBANDRIA4_MATHBUF_OPTSIZE__AVX1 ]
	__attribute__ ((aligned (64)));
	#endif
#else
#endif


#if \
	( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
	( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_LLVM )
	
	#define LIBANDRIA4_NAKEDATTR __attribute__((naked))
	#define LIBANDRIA4_SETJMPATTR __attribute__((naked,returns_twice))
	
#elif  \
	( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_MSVC )
	
	#error "This is unverified!\n"
	
	#define LIBANDRIA4_NAKEDATTR __declspec(naked)
	#define LIBANDRIA4_SETJMPATTR _Noreturn
	
#elif \
	( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_TCC )
	
	#error "Syntax for TCC in jmpalike.h hasn't been worked out yet.\n"
	
#else
	
	#error "jmpalike.h doesn't recognize this compiler yet.\n"
	
#endif



	/* Called once per exception-handler throw-context. */
int libandria4_jmpalike_rebasestack
(
	libandria4_jmpalike_buf buf,
	  void *oldref, void *newref
);

#define LIBANDRIA4_JMPALIKE_SETCORE( buf ) \
	( LIBANDRIA4_SIGNAL_FENCE( var ), \
		libandria4_jmpalike_setcore( buf ) )

#define LIBANDRIA4_JMPALIKE_SETOTHERS( buf ) \
	( LIBANDRIA4_SIGNAL_FENCE( var ), \
		libandria4_jmpalike_setothers( buf ) )

#define LIBANDRIA4_JMPALIKE_SET( buf ) \
	( LIBANDRIA4_SIGNAL_FENCE( var ), \
		libandria4_jmpalike_set( buf ) )

#define LIBANDRIA4_JMPALIKE_JMP( buf, retval ) \
	( LIBANDRIA4_SIGNAL_FENCE( var ), \
		libandria4_jmpalike_jmp( buf, retval ) )



/* DO NOT directly call ay of these, use the macro versions above instead. */

	/* Called once per exception-handler catch-context. */
LIBANDRIA4_SETJMPATTR
uintptr_t libandria4_jmpalike_setcore( libandria4_jmpalike_buf buf );

	/* Called every time it's passed, in exception-handler catch-context. */
void libandria4_jmpalike_setothers( libandria4_jmpalike_buf buf );

LIBANDRIA4_SETJMPATTR
uintptr_t libandria4_jmpalike_set( libandria4_jmpalike_buf buf );


int libandria4_jmpalike_jmp( libandria4_jmpalike_buf buf, uintptr_t ret );





	/* Demo version. This stuff really goes in exceptions.h, except */
	/*  that it should be a more-complete implementation. */
typedef struct
{
	libandria4_jmpalike_buf buf;
	void *oldref;
	
} ;
#define LIBANDRIA4_EXCEPTIONS_THROW( destptr ) \
	{ \
		if( !libandria4_rebasestack( \
				( destptr )->buf, \
				( destptr )->oldref, \
				(void*)&libandria4_exceptions_progress \
			) ) \
		{ \
				/* We've adjusted stuff, so we need to update the ref. addr. */ \
			( destptr )->oldref = (void*)&libandria4_exceptions_progress; \
			libandria4_longjmp( ( destptr )->buf, uintptr_t ret ); \
		} \
	}







/*
The .c file contents proper are below.
*/






static uintptr_t ptrhash( size_t len, char *str )
{
	uintptr_t ret = 0, offr = 0, offp = 0;
	uint16_t patch = 0;
	
	while( len )
	{
		patch += ( *str ) << offp;
		
		len -= 1;
		++str;
		offp += 7;
		if( offp >= 8 )
		{
			offp -= 8;
			offr += 8;
			ret ^= ( ( patch & 255 ) << offr );
			patch &= ( 255 << 8 );
			patch >>= 8;
		}
		if( offr >= CHAR_BITS * LIBANDRIA4_CELLTYPE_REGSIZE )
		{
			offr = 0;
		}
	}
	while( patch )
	{
		offr += 8;
		ret ^= ( ( patch & 255 ) << offr );
		patch &= ( 255 << 8 );
		patch >>= 8;
		
		if( offr >= CHAR_BITS * LIBANDRIA4_CELLTYPE_REGSIZE )
		{
			offr = 0;
		}
	}
	
	return( ret );
}
#define LIB4_MASK_PTR( val ) \
	( (libandria4_jmpalike_buf)( (uintptr_t)( val ) ^ \
		ptrhash( strlen( __DATE__ ), __DATE__ ) ^ \
		ptrhash( strlen( __TIME__ ), __TIME__ ) ^ \
		ptrhash( strlen( __TIMESTAMP__ ), __TIMESTAMP__ ) ) )

#if \
	( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
	( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_LLVM )
	
	#if LIBANDRIA4_CELLTYPE_REGSIZE == 8
		
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
		
		#if LIBANDRIA4_TARGETPROCESSOR2 >= \
			LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium3
		/* The Pentium3 introduced SSE. */
		
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
		#if ( LIBANDRIA4_CELLTYPE_SIZE == 8 )
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
		#elif LIBANDRIA4_CELLTYPE_SIZE > 8
			#error "Unrecognized cell size.\n"
		#endif
		}
		#endif
		#if ???
		/* Initial AVX specific stuff, always 64 bit. */
		
		/*
			The stuff here is partially based on:
				https://www.moritz.systems/blog/how-debuggers-work-getting-and-setting-x86-registers-part-1/#fxsave-vs-fxsave64
		*/
		
			/* Some 486 also support this, but I'm not sure how to ID them, */
			/*  so waiting for Pentium will do. */
		#if LIBANDRIA4_TARGETPROCESSOR2 >= \
			LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
			
			static thread char procname[ 12 ];
			uint32_t libandria4_cpuid_inner( uint32_t leaf, uint32_t sub )
			{
				uint32_t res, a, b, c;
				
				__asm__ volatile {
					"mov %%ecx %%eax\n"
					"mov %%edx %%ecx\n"
					"cpuid\n"
					"mov %%eax %0\n"
					"mov %%ebx %1\n"
					"mov %%edx %2\n"
					"mov %%ecx %3\n"
					:
					"=m"(res), "=m"(a), "=m"(b), "=m"(c)
				};
				
				if( leaf == 0 )
				{
					int i1 = 0, i2 = 0;
					while( i2 < 3 )
					{
						procname[ i2 * 4 + i1 ] =
							(
								a & ( 255 << ( i1 * 8 ) )
							) >> ( i1 * 8 );
						++i1;
						if( i1 >= 4 )
						{
							i1 = 0;
							++i2;
							a = b;
							b = c;
						}
					}
				}
				
				return( res );
			}
		#endif
		int libandria4_cpuid( uint32_t leaf, uint32_t subleaf,  uint32_t *ret, char *name )
		{
			#if LIBANDRIA4_TARGETPROCESSOR2 < \
				LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
				
				return( -1 );
				
			#else
				uint32_t tmp;
				if( !ret )
				{
					ret = &tmp;
				}
				*ret = libandria4_cpuid_inner( leaf, subleaf );
				if( leaf == 0 && name )
				{
					int i = 0;
					while( i < 12 )
					{
						name[ i ] = procname[ i ];
						++i;
					}
				}
				
				return( 1 );
			#endif
		}
		
		int test_xsave_avail()
		{
			static int status = 0;
			
			
			if( status == 0 )
			{
				volatile uint32_t tmp;
				volatile uint32_t str[ 3 ];
				int res = libandria4_cpuid( 1, 0,  &tmp, (char*)str );
				
					/* Test ECX for XSAVE. */
				if( str[ 2 ] & 0x04000000 )
				{
					status = 1;
					
				} else {
					
					status = -1;
				}
			
			return( status );
		}
		int test_avx_avail()
		{
			static int status = 0;
			
			
			if( status == 0 )
			{
				volatile uint32_t tmp;
				volatile uint32_t str[ 3 ];
				int res = libandria4_cpuid( 1, 0,  &tmp, (char*)str );
				
					/* Test ECX for AVX. */
				if( str[ 2 ] & 0x10000000 )
				{
					status = 1;
					
				} else {
					
					status = -1;
				}
			
			return( status );
		}
		int find_avxoffset( uint32_t *off )
		{
			static uint32_t offset;
			static int status = 0;
			
			
			if( status == 0 )
			{
				volatile uint32_t tmp;
				volatile uint32_t str[ 3 ];
				int res = libandria4_cpuid( 0x0D, 0x02,  &tmp, (char*)str );
				
				res = 1;
				offset = str[ 0 ];
			}
			if( status && off )
			{
				*off = offset;
			}
			
			return( status );
		}
		int find_avxsize( uint32_t *sz )
		{
			static uint32_t size;
			static int status = 0;
			
			
			if( status == 0 )
			{
				volatile uint32_t tmp;
				volatile uint32_t str[ 3 ];
				int res = libandria4_cpuid( 0x0D, 0,  &tmp, (char*)str );
				
				res = 1;
				size = str[ 0 ];
			}
			if( status && sz )
			{
				*sz = size;
			}
			
			return( status );
		}
		
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
		
	#elif \
		( LIBANDRIA4_TARGETPROCESSOR0 != LIBANDRIA4_PROCESSOR0_ISA_x86 ) || \
		( LIBANDRIA4_TARGETPROCESSOR1 != 1 )
		
		#error "Unimplemented PROCESSOR 0 value.\n"
		
	#else
		
		#error "Unsupported machine in jmpalike.c .\n"
		
	#endif
	
#elif  \
	( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_MSVC )
	
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
	
#elif \
	( ( LIBANDRIA4_COMPILER & ~(LIBANDRIA4_COMPILER_ERAMASK) ) == \
		LIBANDRIA4_COMPILER_CODEBASE_TCC )
	
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

