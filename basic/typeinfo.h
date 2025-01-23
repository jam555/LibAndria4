/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2019 Jared A. Maddox

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

#ifndef LIBANDRIA4_BASIC_TYPEINFO_H
# define LIBANDRIA4_BASIC_TYPEINFO_H
	/* There was endianness detection code here, but it's been moved */
	/*  to platformdetect.h and platformsupport.c. */
	
	
	
	/* This is a system to represent information about types. Currently */
	/*  only some simpler data types are represented, but support for */
	/*  e.g. structures & function signatures can (and should) */
	/*  reasonably be achievable. */
	
	
	#include <limits.h>
	#include <stdint.h>
	
	#if !defined( UINT_LEAST16_MAX )
		#error "Error! uint_least16_t support not detected!"
	#else
		typedef uint_least16_t lib4_typeinfo_uinttype;
	#endif
	
		/* The list of type info interpretations. */
	typedef enum
	{
		lib4_typeinfo_typeenum__nulltype = 0,
		
		lib4_typeinfo_typeenum_pretype = 1,
		lib4_typeinfo_typeenum_plainnamingtype,
		lib4_typeinfo_typeenum_plaintype_inner,
		lib4_typeinfo_typeenum_plaintype,
		lib4_typeinfo_typeenum_extendedtype,
		lib4_typeinfo_typeenum_twintype,
		lib4_typeinfo_typeenum_plainannotatedtype,
		lib4_typeinfo_typeenum_derivedtype,
		
		lib4_typeinfo_typeenum_plain_unsigned = 16,
			/* Highest bit is sign, zero has pos & neg forms. */
		lib4_typeinfo_typeenum_plain_signmagnitude,
			/* Zero has pos & neg, all neg values bit-compl of pos */
			/*  version. */
		lib4_typeinfo_typeenum_plain_onescomplement,
			/* Common implementation; only one zero, math identical w/ */
			/*  unsigned, one more neg value than pos. */
		lib4_typeinfo_typeenum_plain_twoscomplement,
		lib4_typeinfo_typeenum_plain_simpleUnpackedBCD,
			/* Generic group, seperate sign nibble; 0xA, 0xC, and 0xE are */
			/*  positive, OxB & 0xD are negative, 0xF is "unsigned" */
			/*  (~positive), 0xC and 0xD are prefered. */
		lib4_typeinfo_typeenum_plain_ZoneBCD,
			/* This is unsigned. */
		lib4_typeinfo_typeenum_plain_simplePackedBCD,
			/* Uses -3 to 9, contiguous. */
		lib4_typeinfo_typeenum_plain_excess3,
			/* Uses -6 to 9, contiguous. */
		lib4_typeinfo_typeenum_plain_excess6,
			/* Lowest value unused, all values shifted up by 1. */
		lib4_typeinfo_typeenum_plain_magnetictapeBCD,
		lib4_typeinfo_typeenum_plain_GraycodeBCD,
		lib4_typeinfo_typeenum_plain_Excess3GraycodeBCD,
			/* Uses the sign nibbles from Zone BCD in a packed form- one */
			/*  nibble per number is sacrificed to the sign. */
		lib4_typeinfo_typeenum_plain_packedZoneBCD,
		lib4_typeinfo_typeenum_plain_10sComplement,
		
			/* A signed int form: the number is added to an offset to convert */
			/*  it to unsigned form for storage. */
		lib4_typeinfo_typeenum_twin_offsetbinary = 32,
			/* As above, but hardcoded offset. */
		lib4_typeinfo_typeenum_extended_offsetbinary,
		lib4_typeinfo_typeenum_extended_unsignedfixedpoint,
		lib4_typeinfo_typeenum_extended_offsetBCD,
		lib4_typeinfo_typeenum_extended_unsignedfixedpointBCD,
		
		/* These three styles of hyper-complex numbers can exist in other forms too. */
			/* Complex numbers, i*i==-1, but i!=-1 nor +1. */
		lib4_typeinfo_typeenum_twin_complexnumber_fixedpoint = 48,
			/* Aka "nilplex numbers". */
			/* Related to complex numbers, but E*E==0, not -1, but E!=0. */
			/* Useful for "automatic differentiation". */
		lib4_typeinfo_typeenum_twin_dualnumber_fixedpoint,
			/* Aka "split complex number", "hyperbolic number", "perplex number", or others. */
			/* Related to complex numbers, but j*j==+1, not -1, but j!=+1. */
		lib4_typeinfo_typeenum_twin_doublenumber_fixedpoint,
		
			/* These two are synonyms. The mantissa is stored missing the highest */
			/*  bit (which is ALWAYS 0.5 aka 0.1*0b1), the exponent is stored */
			/*  always with a bias (unless stored as 0 or ~0, which is always */
			/*  special values which might break the specified mantissa rule), */
			/*  which ensures the smallest exponent is stored as a 1. */
		lib4_typeinfo_typeenum_twin_floatingpoint_common_mantMNsPt0b1_2expBiased = 64,
		lib4_typeinfo_typeenum_twin_floatingpoint_common_IEEE754style = 64,
		
			/* "A" is the flag, "B" is the value. */
		lib4_typeinfo_typeenum_twin_monad_maybe = 80,
		lib4_typeinfo_typeenum_twin_monad_either,
			/* Note: following my own construction of monads, it's desirable to */
			/*  have a monadic type that corresponds to raw memory allocations: */
			/*  if detected at compile time to be left unallocated, that's a */
			/*  syntax error; if detected at compile time to be freed before all */
			/*  of it's constituents are all released, that's a syntax error; if */
			/*  detected at runtime to be released before all of it's constituents */
			/*  are released, that's a runtime error similar to a segfault, and */
			/*  may correspond to any number of things like hardware failures and */
			/*  external tampering with the file. */
			/* Also desirable is a "future" monad: it has the structure of maybe, */
			/*  but it uses atomic operations to allow asynchronous operations. */
			/*  Similarly desirable is a pipelined version built around either. An */
			/*  extra-special redirect should be used for both to distinguish */
			/*  receiver from sender. */
		
			/* The variable in question MUST be accessed via atomic/thread-safe */
			/*  operations. Required (but not quite sufficient) to upgrade a */
			/*  "maybe" monad to a "future". Note that atomics effectively count */
			/*  as volatiles, since the buffering/caching allowed by non-volatile */
			/*  variables is sometimes incompatible with atomic operations. */
		lib4_typeinfo_typeenum_plainannotated_atomic = 96,
			/* Always skip the cache and go straight to the address, but atomics */
			/*  aren't mandatory. */
		lib4_typeinfo_typeenum_plainannotated_volatile,
			/* Cache aggressively. This is meant not to change, so never change */
			/*  it and pretend it won't change once set. */
		lib4_typeinfo_typeenum_plainannotated_constant,
		/* These next two types introduce indirection, while the three above */
		/*  don't. Beware that difference. */
			/* Just like in C or C++. Check for type inconsistencies. A pointer */
			/*  is innately a different type than a legitimate target for it, so */
			/*  reference loops should be "illegal". */
		lib4_typeinfo_typeenum_plainannotated_pointer,
			/* A C++ style reference, skip on to it's target. Same warnings as */
			/*  pointers, but treat redirects themselves as constant under normal */
			/*  circumstances. */
		lib4_typeinfo_typeenum_plainannotated_redirect,
		
			/* This value is reserved for the next block/subject/category of */
			/*  lib4_typeinfo_pretype.type_info_type values. */
		lib4_typeinfo_typeenum__nextstart = 112,
		lib4_typeinfo_typeenum__pastend
		
	} lib4_typeinfo_typeenum;
	
	
		/* Just a header for the real description structures. */
	typedef struct lib4_typeinfo_pretype
	{
		lib4_typeinfo_typeenum type_info_type;
		
	} lib4_typeinfo_pretype;
	
		/* For types that are somewhat arbitrary, like custom annotated types. */
		/*  The name should be informative, e.g. a "Direct Threaded Code" */
		/*  subroutine should be clarified as all of those things instead of */
		/*  just e.g. "Threaded Code"; be ready for this string to be printed */
		/*  in debug messages, and don't try to emit anything other than simple */
		/*  text. */
	typedef struct lib4_typeinfo_plainnamingtype
	{
		lib4_typeinfo_pretype header;

		char *name;
		
	} lib4_typeinfo_plainnamingtype;
	
	typedef struct lib4_typeinfo_plaintype_inner
	{
			/* Size and alignment are both in BITS, not bytes. */
		lib4_typeinfo_uinttype size, alignment;
		
	} lib4_typeinfo_plaintype_inner;
		/* Descriptions for integers, technically including characters. */
	typedef struct lib4_typeinfo_plaintype
	{
		lib4_typeinfo_pretype header;
		
		lib4_typeinfo_plaintype_inner info;
		
	} lib4_typeinfo_plaintype;
	
		/* SLIGHTLY fancier integers. */
	typedef struct lib4_typeinfo_extendedtype
	{
		lib4_typeinfo_pretype header;
		
			/* Fixed-point fractions: exponent of two that's used to calculate */
			/*  real value. */
			/* Offset-binary signed ints: offset to add to value to allow it to */
			/*  be stored. */
			/* Other types as iterations on those above. */
		lib4_typeinfo_uinttype operand;
		lib4_typeinfo_plaintype_inner info;
		
	} lib4_typeinfo_extendedtype;
	
		/* Numbers better described as two integers. */
	typedef struct lib4_typeinfo_twintype
	{
		lib4_typeinfo_plaintype header;
		
			/* Floating-point fractions: A is the mantissa, B is the exponent. */
		lib4_typeinfo_typeenum A_type, B_type;
		lib4_typeinfo_plaintype_inner A_info, B_info;
		
	} lib4_typeinfo_twintype;
	
		/* For types that are another type, but with strict additions to */
		/*  required behavior; e.g. atomic variables. */
	typedef struct lib4_typeinfo_plainannotatedtype
	{
		lib4_typeinfo_plaintype header;
		
		lib4_typeinfo_typeenum basetype;
		lib4_typeinfo_plaintype_inner baseinfo;
		
	} lib4_typeinfo_plainannotatedtype;
	
		/* Mostly for use directly with lib4_typeinfo_plainnamingtype{} as */
		/*  the modifier of the designated base type, but */
		/*  lib4_typeinfo_pretype{} can be used as the modifier via */
		/*  lib4_typeinfo_typeenum_plainannotated_* variants. Stuff like */
		/*  lib4_typeinfo_typeenum_twin_monad_maybe could also be used via */
		/*  lib4_typeinfo_plaintype{} or similar, at the cost of requiring */
		/*  knowledge of HOW to use a monad derivation for whatever the */
		/*  base type is. */
	typedef struct lib4_typeinfo_derivedtype
	{
		lib4_typeinfo_plaintype header;
		
		lib4_typeinfo_plaintype_inner *basetype, *modifier;
		
	} lib4_typeinfo_derivedtype;
	
	
	
	
	typedef struct lib4_typeinfo_vtable_integers lib4_typeinfo_vtable_integers;
	typedef int (*lib4_typeinfo_vtable_integers_unaop)( lib4_typeinfo_vtable_integers*,  void*,  void* );
	typedef int (*lib4_typeinfo_vtable_integers_biop)( lib4_typeinfo_vtable_integers*,  void*, void*,  void* );
	typedef int (*lib4_typeinfo_vtable_integers_shiftop)( lib4_typeinfo_vtable_integers*,  void*, unsigned,  void* );
	typedef int (*lib4_typeinfo_vtable_integers_unaint)( lib4_typeinfo_vtable_integers*,  void*,  int* );
	typedef int (*lib4_typeinfo_vtable_integers_biint)( lib4_typeinfo_vtable_integers*,  void*, void*,  int* );
	struct lib4_typeinfo_vtable_integers
	{
		lib4_typeinfo_plaintype format;
		void *maxvalue, *zerovalue, *minvalue, *highbit_mask;
		
		lib4_typeinfo_vtable_integers_shiftop init;
		lib4_typeinfo_vtable_integers_unaint deinit;
		lib4_typeinfo_vtable_integers_unaop set, incr, decr, negate, complement;
		lib4_typeinfo_vtable_integers_biop add, sub, mul, div, mod, band, bior, bxor;
		lib4_typeinfo_vtable_integers_shiftop left, right;
		lib4_typeinfo_vtable_integers_unaint not;
		lib4_typeinfo_vtable_integers_biint equal, nequal, greater, lesser, greq, lseq, land, lior;
	};
	
	
	typedef struct
	{
		lib4_typeinfo_plaintype *nchar;
		lib4_typeinfo_plaintype *schar;
		lib4_typeinfo_plaintype *uchar;
		
		lib4_typeinfo_plaintype *uint_8;
		lib4_typeinfo_plaintype *uint_16;
		lib4_typeinfo_plaintype *uint_32;
		
		/* There are no signed because I don't want to deal with the */
		/*  different options for signed numbers just yet. */
		
	} lib4_typeinfo_stdtypes_inner;
	typedef struct
	{
		lib4_typeinfo_stdtypes_inner native;
		lib4_typeinfo_stdtypes_inner common;
		
	} lib4_typeinfo_stdtypes;
	lib4_typeinfo_stdtypes lib4_typeinfo_stdtypes_platform;
	
#endif
/* End libandria4 basic typeinfo.h */
