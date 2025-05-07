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


#error "arbicall.c is not ready!"


/* Concept: a function that will place arbitrary arguments onto the stack, */
/*  and then make a call to something. This is what the calling-convention */
/*  notes are for. */

typedef enum
{
	typeinfo_callconv_style__invalid = -1,
	typeinfo_callconv_style__uninitialized = 0,
	
		/* This will have to start as illegal, because I'll have to think about how it works. */
	typeinfo_callconv_style__naked = 1,
		/* C-style: the caller cleans up the arguments, and arguments are pushed int the */
		/*  reverse of the order that they occur in the argument list. Makes variadic */
		/*  functions easy to implement, so even Pascal variants with variadic arguments */
		/*  will tend to use it. */
	typeinfo_callconv_style__cdecl,
		/* Pascal-style: the callee cleans up the arguments, and arguments are pushed in */
		/*  the order that they occur in the argument list. Complicates variadic */
		/*  functions, as the size of the argument space must be communicated. Pascal-*/
		/*  -style cleanup with Cdecl-style argument order is most commonly called */
		/*  "stdcall", though that IS a Microsoft-ism. */
	typeinfo_callconv_style__pascal,
		/* Two stacks, one for returns and the other for data. on x86, SP is likely the */
		/*  return, and BP the data. */
	typeinfo_callconv_style__forth,
		/* Pascal, but according to Raymond Chen "has strange pass-by-reference behavior". */
	typeinfo_callconv_style__fortran,
	
	
		/* As cdecl, but the return-value somehow specifies a jump-target for exception */
		/*  handling. */
	typeinfo_callconv_style__cdecl_excpjmp = 1024,
		/* As above, but a return instead of a jump (most likely by altering the return */
		/*  value to skip a hardcoded jump). */
	typeinfo_callconv_style__cdecl_excepret,
		/* As above, but a flag is set somewhere. On x86 the FLAGS register is */
		/*  obviously of interest, and particularly the LAHF and SAHF instructions are */
		/*  probably the correct way to access that register, since they allow the "only */
		/*  interesting" (for normal versions of this use-case) flags to be swapped to & */
		/*  from the A register, where they can then be freely modified: beware that */
		/*  these aren't available in older x64 processors, but seems to have been */
		/*  introduced on the original 8086/8088. */
		/* "Interesting" x86 FLAGS bits: */
			/*
				Carry : Probably best used to imply an iterative function needs to be called to continue processing.
				Zero : Best used to indicate "true null".
				Sign : For my edecl convention, negative will trigger exception-handling in the caller.
				Overflow : Some mix of Carry and Overflow? Don't know how to use.
				
			*/
			/*
				Other flags:
					Adjust ? : Restricted access, don't use.
					Trap ? : Restricted access, don't use.
					Interrupt ? : Restricted access, don't use.
					Direction : Controls the direction of the striong opcodes, and not in LAHF/SAHF, so don't use.
				Parity : Indicates an even (a) or odd (0) number of bits set, don't use.
			*/
	typeinfo_callconv_style__cdecl_excepflag,
		/* As above, but GCC style: lookup a table based on the return address, then */
		/*  deal with that table's contents. */
	typeinfo_callconv_style__cdecl_exceplookup,
	
	/* As above, but callee-cleanup instead of caller-cleanup. */
	/* THIS IS A MISTAKE! excepjmp and excepret probably aren't compatible, but the */
	/*  other two should probably be modifiers to calling conventions rather than */
	/*  discrete conventions themselves. */
	typeinfo_callconv_style__cdecl_excpjmp,
	typeinfo_callconv_style__cdecl_excepret,
	typeinfo_callconv_style__cdecl_excepflag,
	typeinfo_callconv_style__cdecl_exceplookup,
	
	
	/* Don't use this to size arrays, there's lots of gaps. */
	typeinfo_callconv_style__PAST_END
	
} typeinfo_callconv_style;
typedef enum
{
	typeinfo_callconv_flags1__uninitialized = -1,
	
		/* New items cause the stack-pointer to become LARGER. Normally not set. */
	typeinfo_callconv_flags1__upwardstack = 1,
		/* Use a reversed stack implementation: on x86, swap the use of BP and SP. */
		/*  Mostly for Forth. */
	typeinfo_callconv_flags1__inversestack = 2,
		/* Result returned via register (whether direct or via reference). */
	typeinfo_callconv_flags1__resinreg = 4,
		/* Result returned vis data stack. */
	typeinfo_callconv_flags1__resasdata = 8,
		/* Result returned via return stack. Only differs from *__resasdata for */
		/*  Forth-style. */
	typeinfo_callconv_flags1__resasret = 16,
		/* Swaps the order that members in an argument list get pushed: e.g. turns */
		/*  "typeinfo_callconv_style__pascal" into a stdcall specification. */
	typeinfo_callconv_flags1__inversepush = 32
	
} typeinfo_callconv_flags1;

typedef struct
{
	typeinfo_callconv_style style;
	typeinfo_callconv_flags1 flags1;
		/* Reference processor, platform (e.g. OS), and compiler. */
	uintptr_t proc, plat, comp;
		/* Interpretation depends on ->style, ->proc, ->plat, and ->comp */
	uintptr_t style2;
	
} typeinfo_callconv__styles;
typedef struct
{
	size_t ret_align, res_align, arg_align;
	size_t retstack_align, resstack_align, argstack_align;
		/* The maximum size value that can be stored directly on a stack, instead */
		/*  of as a reference. */
	size_t res_reftrans, arg_reftrans;
		/* Number of args storable in registers, vs max registers per arg. */
	size_t arg_inreg, arg_maxreg;
	
} typeinfo_callconv__sizing;

typedef struct
{
		/* Describes the actual implementation: only typeinfo_callconv__type1{} */
		/*  exists right now. */
		/* Note: all the alternates will still start with typeinfo_callconv{}, */
		/*  since this is for better compatibility. */
	uintptr_t metaconv;
	
	typeinfo_callconv__styles *styles;
	typeinfo_callconv__sizing *sizes;
	
} typeinfo_callconv;

typedef struct
{
	typeinfo_callconv conv;
	
	typeinfo_callconv__styles *styles;
	typeinfo_callconv__sizing *sizes;
	
	typeinfo_callconv__styles style_;
	typeinfo_callconv__sizing sizing_;
	
} typeinfo_callconv__type1;

typedef struct
{
	void *loc;
		/* The type at the target of ->loc */
	typeinfo *desc;
} arg_descriptor;
typedef pascalstring< arg_descriptor >  argdescs;
	/* Note: this function DOES NOT handle C++ member functions! At least not */
	/*  correctly. Those need the "this" pointer to ALWAYS be the lowest-addressed */
	/*  element on the stack, lower even than the pointer for an indirect-return, */
	/*  but this has absolutely no support for that. */
	/* dest: */
	/*  the lowest address of the destination buffer. */
	/* size: */
	/*  holds the number of available elements, not the number of available bytes. */
	/* ret: */
	/*  holds the destination of the return value. For some returns it */
	/*  needs to be pushed on the stack as a hidden variable, while for others */
	/*  THIS function should ignore it. */
uintptr_t argpaste( uintptr_t *dest, uintptr_t size, argdescs *args, void *ret )
{
	if( dest && args && args->len <= size )
	{
		size_t i = 0;
		unsigned char ptrret = 0;
		
			/* Figure out whether the return value is allowed in a register: if */
			/*  not, we need to pass a pointer to it's destination as a hidden */
			/*  1st argument on the stack. */
		if( ??? )
		{
			ptrret = 1;
		}
		
		while( i < args->len )
		{
			if( i == 0 && ptrret > 0 )
			{
				/* The return value is "illegal" for direct return, so copy a */
				/*  pointer to it's destination onto the stack. */
				
				LIBANDRIA4_TYPEINFO_VTABLE__SET(
					( args->body[ i ].desc ),
						( dest + i ),
						( &ret )
				);
				
			} else if( ??? )
			{
				/* The specified value is "illegal" for direct stack storage, */
				/*  so copy a pointer to it onto the stack. */
				
				/* TODO: Add insturmentation for cases where we want to do some */
				/*  sort of tracking here! */
				*( dest + i ) = (uintptr_t)( args->body[ i ].loc );
				
			} else {
				
				/* The specified value is "legal" for direct stack storage, so */
				/*  copy directly. */
				
				LIBANDRIA4_TYPEINFO_VTABLE__SET(
					( args->body[ i ].desc ),
						( dest + i ),
						( args->body[ i ].loc )
				);
			}
			
			++i;
		}
		
			/* We need to return a 2 on floating-point! */
		??? ;
		return( ptrret );
	}
	
	exit( -1 );
}

int arbicall( typeinfo_callconv *callconv, void (*func)(), argdescs *args, void *ret )
{
	/* Move the arguments listed in args into position according to */
	/*  their own description + callconv, then enter func according */
	/*  to callconv. */
}
/*
This is basically arbicall() as assembly, but we need to explicitly
 deal with returns, and we don't even accept the needed arg yet.
rcx == first arg == callconv
rdx == second arg == func
r8 == third arg == args
r9 == fourth arg == return destination
		/ * Archive the arguments. * /
	move 8(rsp) <-< rcx
	move 16(rsp) <-< rdx
	move 24(rsp) <-< r8
	move 32(rsp) <-< r9
	
		/ * Prep the frame: we want a base-pointer. * /
	push rbp
	move rbp <-< rsp
	 	 / * Push the first 16 flag bits to stack: note that this * /
		 / *  DOES NOT generate an error in unprotected mode (except * /
		 / *  in some cases in virtual-8086 mode, which 64-bit code * /
		 / *  need not care about...), but insted just alters which * /
		 / *  bits can be set. * /
	pushf
		/ * Realign  to a 64bit*4 alignment, & allocate call args. * /
	rsp -= ( 14 + 32 )
	
		/ * Allocate the space for the actual call. * /
				/ * Set the sole argument. * /
			move 0(rsp) <-< r8
			move rcx <-< r8
			cld / * Just in case, clear the direction flag. * /
			/ * Calculate the space needed for the desired call. Note that * /
			/ *  we want this to ALWAYS return at least "32", to support * /
			/ *  x64 "4 entry minimum" stack argument-space rules. * /
		call ??? calcsize ???
				/ * We should do something to ensure the size is a multiple of 8. * /
			???
				/ * On-stack allocation. This is slightly space-suboptimal. * /
			rsp -= rax
				/ * To force correct alignment. * /
			rsp &= ~( 0xF )
		
		/ * Assemble the argument block. * /
				/ * Mark the lowest address of the buffer... except it's a bit lower than that. * /
			move rcx <-< rsp
			rcx += 32 / * Moves away from the argument space, to the actual buffer space. * /
				/ * Pass along the size, for verification * /
			/ * We can't do this! RAX is likely trashed by now! * /
			/ * Actually, is it trashed? Have we touched it at all? * /
			move rdx <-< rax
			shr rdx, 3 / * Shift-right, equates to divide-by-8, for element-count -> byte-count. * /
				/ * Restore the pointer to the argdescs into R8. * /
			move r8 <-< 32(rbp)
				/ * Restore the pointer to the return "receiver". * /
			move r9 <-< 40(rbp)
			cld / * Just in case, clear the direction flag. * /
		call argpaste
				/ * We no longer need argdescs / 32(rbp), so store the return-via-pointer flag there. * /
			move 32(rbp) <-< rax
		
		/ * Now we need to do the actual call. * /
				/ * As with rcx before the call to argpaste(), move THE STACK * /
				/ *  away from the argument space we've been using. * /
			rsp += 32;
				/ * Load the registers with their designated values * /
			move rcx <-< (rsp)
			move rdx <-< 8(rsp)
			move r8 <-< 16(rsp)
			move r9 <-< 24(rsp)
				/ * Load the target from the stack. * /
			move rax <-< 24(rbp)
			/ * RAX was going to be overwritten with the return value anyways. * /
		call (rax)
			/ * RAX now contains some form of return value. * /
		
			/ * 32(rbp) has the return-via-pointer flag. * /
			/ * If flag == 0, direct return, else indirect return. Set RAX accordingly, leave XMM0 untouched. * /
		cmp 32(rbp) - 1 / * Yes, ( mem - imm ) is valid. Note that mem > imm must trigger jg! * /
		je after_dirret
		jg on_floating
				/ * Direct return, so the return value HAS NOT been stored at the destination address. * /
			move rcx <-< 40(rbp)
			move 0(rcx) <-< rax
			jmp after_dirent
		on_floating:
				/ * Direct return, so the return value HAS NOT been stored at the destination address. * /
			move rcx <-< 40(rbp)
			move 0(rcx) <-< xmm0
				/ * Just fall-through. * /
		after_dirret:
	
		/ * We need to reset the stack so only the bare essentials are present. LEA probably isn't appropriate. * /
	rbp -= 2; / * Calculate where we stored the flags. * /
	rsp = rbp;
	rbp += 2; / * Return to the base-pointer location. * /
	
		/ * As noted with pushf, insufficient priviledges change the set */
		/*  bits instead of throwing exceptions. * /
	popf
	move rsp <-< rbp
	pop rbp
	ret
*/
















