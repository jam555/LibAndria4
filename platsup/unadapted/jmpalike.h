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

/* Attention users! jetjmp()/longjmp() have unpredictable interations with */
/*  compiler optimizations, so if your variables might get updated after */
/*  setjmp(), then analyze them to figure out which need to be tagged */
/*  "volatile". */

#include "../platdet/detect.h"
#include "../primitive/basictypes.h"


typedef void *libandria4_jmpalike_buf[ LIBANDRIA4_JMPBUF_CELLCOUNT ];
typedef uint16_t libandria4_jmpalike_float[ LIBANDRIA4_FLOATBUF_CELLCOUNT ];

#if LIBANDRIA4_TARGETPROCESSOR2 < LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
typedef uint16_t libandria4_mathbuf_opt0[ LIBANDRIA4_MATHBUF_OPTSIZE_x87 ];
#elif LIBANDRIA4_TARGETPROCESSOR2 >= LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
typedef uint16_t libandria4_mathbuf_opt0[ LIBANDRIA4_MATHBUF_OPTSIZE_x87 ];
	#if LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU )
typedef uint16_t libandria4_mathbuf_opt1[ LIBANDRIA4_MATHBUF_OPTSIZE_SSE ]
	__attribute__ ((aligned (16)));
typedef uint16_t libandria4_mathbuf_opt2[ LIBANDRIA4_MATHBUF_OPTSIZE__AVX1 ]
	__attribute__ ((aligned (64)));
	#else
		#error "Unsupported compiler, add support.\n"
	#endif
#endif


typedef struct libandria4_coro1_buf libandria4_coro1_buf;
typedef struct libandria4_coro1_startparams libandria4_coro1_startparams;

struct libandria4_coro1_buf
{
	libandria4_jmpalike_buf callee, caller;
};
	/* For the Coro-1 style coroutrines, this structure needs to be at the */
	/*  start of the coroutine's "personal" stack, which for x86 (and many */
	/*  other processor architectures) means that it belongs at the highest */
	/*  address of the memory that you're allocating for your stack. It's */
	/*  variables MUST be laid out in the same low-level format as */
	/*  libandria4_coro1_start()'s arguments... because */
	/*  libandria4_coro1_start() actually WILL use it as it's stack-frame */
	/*  starting roughly half-way through the function. */
	/* TODO: make certain that this structure ACTUALLY matches the layout of */
	/*  libandria4_coro1_start()'s arguments! */
#if \
	LIBANDRIA4_TARGETPROCESSOR0 == LIBANDRIA4_PROCESSOR0_ISA_x86 && \
	LIBANDRIA4_CELLTYPE_REGSIZE == 4 && \
	( \
		LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_MSVC )\
	)
	/*
	Probably works for these too:
		LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
		LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LLVM ) || \
		LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_TCC )
	*/
		/* Note this the elements of this struct MUST be listed in the same */
		/*  order as the arguments of libandria4_coro1_start(). */
	struct libandria4_coro1_startparams
	{
		/* These should all have the same alignment as stack-slots, so no */
		/*  need for special alignment stunts. */
		
			/* &coro - sizeof( pointer ) * 1 */
			/* This will hold the return address. It doesn't correspond to  */
		libandria4_common_voidfuncp_void retaddr;
		
		libandria4_coro1_buf *coro,
		
			/* &coro + sizeof( pointer ) * 1 */
		libandria4_common_voidfuncp_voidp func,
			/* &coro + sizeof( pointer ) * 2 */
		void *arg,
			/* &coro + sizeof( pointer ) * 3 */
		libandria4_coro1_startparams *stack_head,
		
		void *dummy1, /* &coro + sizeof( pointer ) * 4 */
		void *dummy2 /* &coro + sizeof( pointer ) * 5 */
	};
		/* This should be located at the END of */
#else
#endif
void libandria4_coro1_start
(
	libandria4_coro1_buf *coro,
	
		/* &coro + sizeof( pointer ) * 1 */
	libandria4_common_voidfuncp_voidp func,
		/* &coro + sizeof( pointer ) * 2 */
	void *arg,
		/* &coro + sizeof( pointer ) * 3 */
	libandria4_coro1_startparams *stack_head,
	
	void *dummy1, /* &coro + sizeof( pointer ) * 4 */
	void *dummy2/* &coro + sizeof( pointer ) * 5 */
);



#if \
	LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_GNU ) || \
	LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_LLVM )
	
	#define LIBANDRIA4_NAKEDATTR __attribute__((naked))
	#define LIBANDRIA4_SETJMPATTR __attribute__((naked,returns_twice))
	
#elif  \
	LIBANDRIA4_COMPILER_IS_CODEBASE( LIBANDRIA4_COMPILER_CODEBASE_MSVC )
	
	#error "This is unverified!\n"
	
	#define LIBANDRIA4_NAKEDATTR __declspec(naked)
	#define LIBANDRIA4_SETJMPATTR _Noreturn
	
#else
	
	#error "jmpalike.h doesn't support this compiler yet.\n"
	
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


void libandria_coro1_yield( libandria4_coro1_buf *coro );
int libandria4_coro1_next( libandria4_coro1_buf *coro );



/* DO NOT directly call ay of these, use the macro versions above instead. */

	/* Called once per exception-handler catch-context. */
LIBANDRIA4_SETJMPATTR
intptr_t libandria4_jmpalike_setcore( libandria4_jmpalike_buf buf );

	/* Called every time it's passed, in exception-handler catch-context. */
void libandria4_jmpalike_setothers( libandria4_jmpalike_buf buf );

LIBANDRIA4_SETJMPATTR
intptr_t libandria4_jmpalike_set( libandria4_jmpalike_buf buf );

int libandria4_jmpalike_jmp( libandria4_jmpalike_buf buf, intptr_t ret );
