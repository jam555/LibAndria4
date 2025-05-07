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
	/* TODO: Move this to a distinct directory, and sub-divide. */
	
	
	/* There was endianness detection code here, but it's been moved */
	/*  to platformdetect.h and platformsupport.c. */
	
	
	
	/* This is a system to represent information about types. Currently */
	/*  only some simpler data types are represented, but support for */
	/*  function signatures can (and should) reasonably be achievable. */
		/* Note: see arbicall.c in platsup for initial function work. */
	
	/* Note that while some type descriptors have been added, they are */
	/*  limited in number, with the primary focus placed on fully */
	/*  representing the types defined in this header: they should be */
	/*  expamded in number to cover at least MOST of the standard C */
	/*  types (maybe not functions and floats for a while...), and */
	/*  reorganized so that the descriptors for anything not defined */
	/*  in this file is both declared in another header, and defined */
	/*  in a matching .c file. */
	
	/* Note to self: I forgot to do libandria4_typeinfo_vtable_integers{} */
	/*  and similar, fix that! */
	
	
	#include <limits.h>
	#include <stdint.h>
	
	#if !defined( UINT_LEAST16_MAX )
		#error "Error! uint_least16_t support not detected!"
	#else
		typedef uint_least16_t libandria4_typeinfo_uinttype;
		#define LIBANDRIA4_TYPEINFO_UINTTYPE UINT16_MAX
	#endif
	
		/* The list of type info interpretations. */
	typedef enum
	{
		libandria4_typeinfo_typeenum__nulltype = 0,
		
		libandria4_typeinfo_typeenum_pretype = 1,
		libandria4_typeinfo_typeenum_plainnamingtype,
			/* Only REALLY used for e.g. void, and other types that */
			/*  otherwise can't be logically represented. */
		libandria4_typeinfo_typeenum_plaintype,
			/* This jst marks the descriptor for the pointer's size info, */
			/*  for relations between pointer and pointed look to */
			/*  libandria4_typeinfo_typeenum_plainannotated_pointer or */
			/*  *_redirect. */
		libandria4_typeinfo_typeenum_pointertype,
		libandria4_typeinfo_typeenum_extendedtype,
		libandria4_typeinfo_typeenum_twintype,
		libandria4_typeinfo_typeenum_plainannotatedtype,
		libandria4_typeinfo_typeenum_derivedtype,
			/* Note: value is 8, covers both structs and unions. Use */
			/*  with libandria4_typeinfo_aggregatetype{}. */
		libandria4_typeinfo_typeenum_aggregatetype,
		
		libandria4_typeinfo_typeenum_plain_unsigned = 16,
			/* Highest bit is sign, zero has pos & neg forms. */
		libandria4_typeinfo_typeenum_plain_signmagnitude,
			/* Zero has pos & neg, all neg values bit-compl of pos */
			/*  version. */
		libandria4_typeinfo_typeenum_plain_onescomplement,
			/* Common implementation; only one zero, math identical w/ */
			/*  unsigned, one more neg value than pos. */
		libandria4_typeinfo_typeenum_plain_twoscomplement,
		libandria4_typeinfo_typeenum_plain_simpleUnpackedBCD,
			/* Generic group, seperate sign nibble; 0xA, 0xC, and 0xE are */
			/*  positive, OxB & 0xD are negative, 0xF is "unsigned" */
			/*  (~positive), 0xC and 0xD are prefered. */
		libandria4_typeinfo_typeenum_plain_ZoneBCD,
			/* This is unsigned. */
		libandria4_typeinfo_typeenum_plain_simplePackedBCD,
			/* Uses -3 to 9, contiguous. */
		libandria4_typeinfo_typeenum_plain_excess3,
			/* Uses -6 to 9, contiguous. */
		libandria4_typeinfo_typeenum_plain_excess6,
			/* Lowest value unused, all values shifted up by 1. */
		libandria4_typeinfo_typeenum_plain_magnetictapeBCD,
		libandria4_typeinfo_typeenum_plain_GraycodeBCD,
		libandria4_typeinfo_typeenum_plain_Excess3GraycodeBCD,
			/* Uses the sign nibbles from Zone BCD in a packed form- one */
			/*  nibble per number is sacrificed to the sign. */
		libandria4_typeinfo_typeenum_plain_packedZoneBCD,
		libandria4_typeinfo_typeenum_plain_10sComplement,
		
			/* A signed int form: the number is added to an offset to convert */
			/*  it to unsigned form for storage. */
		libandria4_typeinfo_typeenum_twin_offsetbinary = 32,
			/* As above, but hardcoded offset. */
		libandria4_typeinfo_typeenum_extended_offsetbinary,
		libandria4_typeinfo_typeenum_extended_unsignedfixedpoint,
		libandria4_typeinfo_typeenum_extended_offsetBCD,
		libandria4_typeinfo_typeenum_extended_unsignedfixedpointBCD,
		
		/* These three styles of hyper-complex numbers can exist in other forms too. */
			/* Complex numbers, i*i==-1, but i!=-1 nor +1. */
		libandria4_typeinfo_typeenum_twin_complexnumber_fixedpoint = 48,
			/* Aka "nilplex numbers". */
			/* Related to complex numbers, but E*E==0, not -1, but E!=0. */
			/* Useful for "automatic differentiation". */
		libandria4_typeinfo_typeenum_twin_dualnumber_fixedpoint,
			/* Aka "split complex number", "hyperbolic number", "perplex number", or others. */
			/* Related to complex numbers, but j*j==+1, not -1, but j!=+1. */
		libandria4_typeinfo_typeenum_twin_doublenumber_fixedpoint,
		
			/* These two are synonyms. The mantissa is stored missing the highest */
			/*  bit (which is ALWAYS 0.5 aka 0.1*0b1), the exponent is stored */
			/*  always with a bias (unless stored as 0 or ~0, which is always */
			/*  special values which might break the specified mantissa rule), */
			/*  which ensures the smallest exponent is stored as a 1. */
		libandria4_typeinfo_typeenum_twin_floatingpoint_common_mantMNsPt0b1_2expBiased = 64,
		libandria4_typeinfo_typeenum_twin_floatingpoint_common_IEEE754style = 64,
		
			/* "A" is the flag, "B" is the value. */
		libandria4_typeinfo_typeenum_twin_monad_maybe = 80,
		libandria4_typeinfo_typeenum_twin_monad_either,
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
		libandria4_typeinfo_typeenum_plainannotated_atomic = 96,
			/* Always skip the cache and go straight to the address, but atomics */
			/*  aren't mandatory. */
		libandria4_typeinfo_typeenum_plainannotated_volatile,
			/* Cache aggressively. This is meant not to change, so never change */
			/*  it and pretend it won't change once set. */
		libandria4_typeinfo_typeenum_plainannotated_constant,
		/* These next two types introduce indirection, while the three above */
		/*  don't. Beware that difference. */
			/* Just like in C or C++. Check for type inconsistencies. A pointer */
			/*  is innately a different type than a legitimate target for it, so */
			/*  reference loops should be "illegal". */
		libandria4_typeinfo_typeenum_plainannotated_pointer,
			/* A C++ style reference, skip on to it's target. Same warnings as */
			/*  pointers, but treat redirects themselves as constant under normal */
			/*  circumstances. */
		libandria4_typeinfo_typeenum_plainannotated_redirect,
		
			/* This value is reserved for the next block/subject/category of */
			/*  libandria4_typeinfo_pretype.type_info_type values. */
		libandria4_typeinfo_typeenum__nextstart = 112,
		libandria4_typeinfo_typeenum__pastend
		
	} libandria4_typeinfo_typeenum;
	
	
	??? ; /* TODO: Actually bring this into reality, for MetaC/real-world */
	/*  representation. */
		/* Some types, such as object-oriented-design structs, are effectively */
		/*  several different types at the same time: */
			/* libandria4_typeinfo_multiplicitoustype */
		/*  both IS one of these types, and also DESCRIBES other such types. */
		/*  It describes them by having it's target type's real description */
		/*  immediately follow it, while having pointers accessed through this */
		/*  descriptor to descriptions for it's other forms. Each alternate */
		/*  type might be at a different location than the "real" type */
		/*  (example: C strings versus MSVC++'s BSTR Pascal-style strings, */
		/*  where the prefix length is in front of both the C string, AND the */
		/*  location pointed to be a BSTR's pointer), and so offsets for each */
		/*  alternate type are included. */
	/*
		typedef struct libandria4_typeinfo_multiplicitoustype
		{
			libandria4_typeinfo_pretype header1;
			
			libandria4_typeinfo_pretype *alttype;
				/ * Note that ptrdiff_t and size_t are both defined in stddef.h, * /
				/ *  though size_t is also defined in multiple other places. * /
			ptrdiff_t *altoffset;
			size_t altcount;
			
				/ * The header for the "real" typeinfo type, which should be one * /
				/ *  of the others defined below. * /
			libandria4_typeinfo_pretype real_header;
			
		} libandria4_typeinfo_multiplicitoustype;
	*/
	
		/* Just a header for the real description structures. */
	typedef struct libandria4_typeinfo_pretype
	{
		libandria4_typeinfo_typeenum type_info_type;
		
	} libandria4_typeinfo_pretype;
	
		/* For types that are somewhat arbitrary, like custom annotated types. */
		/*  The name should be informative, e.g. a "Direct Threaded Code" */
		/*  subroutine should be clarified as all of those things instead of */
		/*  just e.g. "Threaded Code"; be ready for this string to be printed */
		/*  in debug messages, and don't try to emit anything other than simple */
		/*  text. */
	typedef struct libandria4_typeinfo_plainnamingtype
	{
		libandria4_typeinfo_pretype header;

		char *name;
		
	} libandria4_typeinfo_plainnamingtype;
	
	typedef struct libandria4_typeinfo_plaintype_inner
	{
			/* Size and alignment are both in BITS, not bytes. */
		libandria4_typeinfo_uinttype size, alignment;
		
	} libandria4_typeinfo_plaintype_inner;
		/* Descriptions for integers, technically including characters. */
	typedef struct libandria4_typeinfo_plaintype
	{
		libandria4_typeinfo_pretype header;
		
		libandria4_typeinfo_plaintype_inner info;
		
	} libandria4_typeinfo_plaintype;
	
		/* SLIGHTLY fancier integers. */
	typedef struct libandria4_typeinfo_extendedtype
	{
		libandria4_typeinfo_pretype header;
		
			/* Fixed-point fractions: exponent of two that's used to calculate */
			/*  real value. */
			/* Offset-binary signed ints: offset to add to value to allow it to */
			/*  be stored. */
			/* Other types as iterations on those above. */
		libandria4_typeinfo_uinttype operand;
		libandria4_typeinfo_plaintype_inner info;
		
	} libandria4_typeinfo_extendedtype;
	
		/* Numbers better described as two integers. */
	typedef struct libandria4_typeinfo_twintype
	{
		libandria4_typeinfo_plaintype header;
		
			/* Floating-point fractions: A is the mantissa, B is the exponent. */
		libandria4_typeinfo_typeenum A_type, B_type;
		libandria4_typeinfo_plaintype_inner A_info, B_info;
		
	} libandria4_typeinfo_twintype;
	
		/* For types that are another type, but with strict additions to */
		/*  required behavior; e.g. atomic variables. */
	typedef struct libandria4_typeinfo_plainannotatedtype
	{
		libandria4_typeinfo_pretype header;
		
		libandria4_typeinfo_pretype *basetype;
		libandria4_typeinfo_plaintype_inner baseinfo;
		
	} libandria4_typeinfo_plainannotatedtype;
	
		/* Mostly for use directly with libandria4_typeinfo_plainnamingtype{} as */
		/*  the modifier of the designated base type, but */
		/*  libandria4_typeinfo_pretype{} can be used as the modifier via */
		/*  libandria4_typeinfo_typeenum_plainannotated_* variants. Stuff like */
		/*  libandria4_typeinfo_typeenum_twin_monad_maybe could also be used via */
		/*  libandria4_typeinfo_plaintype{} or similar, at the cost of requiring */
		/*  knowledge of HOW to use a monad derivation for whatever the */
		/*  base type is. */
	typedef struct libandria4_typeinfo_derivedtype
	{
		libandria4_typeinfo_pretype header;
		
		libandria4_typeinfo_pretype *basetype, *modifier;
		
	} libandria4_typeinfo_derivedtype;
	
		/* For description of types like unions and structures. Could also */
		/*  be used to describe things like maybe-monads if desired. Meant */
		/*  for use with libandria4_typeinfo_typeenum_aggregatetype . */
	typedef struct libandria4_typeinfo_aggregatetype
	{
			/* Describes the aggregate type... in aggregate. */
		libandria4_typeinfo_plaintype header;
		
			/* These describe the individual elements within the aggregate */
			/*  type. Note that the interlinked behaviors aren't described. */
		libandria4_typeinfo_pretype **elemtype;
		size_t *elemoffset;
		size_t elemcount;
		
	} libandria4_typeinfo_aggregatetype;
	
	
	
	
	/* Need to convert these func-ptr types to use some more-generic vtable */
	/*  type. */
	typedef struct libandria4_typeinfo_vtable_integers libandria4_typeinfo_vtable_integers;
	typedef int (*libandria4_typeinfo_vtable_integers_unaop)( libandria4_typeinfo_vtable_integers*,  void*,  void* );
	typedef int (*libandria4_typeinfo_vtable_integers_biop)( libandria4_typeinfo_vtable_integers*,  void*, void*,  void* );
	typedef int (*libandria4_typeinfo_vtable_integers_shiftop)( libandria4_typeinfo_vtable_integers*,  void*, unsigned,  void* );
	typedef int (*libandria4_typeinfo_vtable_integers_unaint)( libandria4_typeinfo_vtable_integers*,  void*,  int* );
	typedef int (*libandria4_typeinfo_vtable_integers_biint)( libandria4_typeinfo_vtable_integers*,  void*, void*,  int* );
	struct libandria4_typeinfo_vtable_integers
	{
		libandria4_typeinfo_plaintype format;
		void *maxvalue, *zerovalue, *minvalue, *highbit_mask;
		
		libandria4_typeinfo_vtable_integers_shiftop init;
		libandria4_typeinfo_vtable_integers_unaint deinit;
		libandria4_typeinfo_vtable_integers_unaop set, incr, decr, negate, complement;
		libandria4_typeinfo_vtable_integers_biop add, sub, mul, div, mod, band, bior, bxor;
		libandria4_typeinfo_vtable_integers_shiftop left, right;
		libandria4_typeinfo_vtable_integers_unaint not;
		libandria4_typeinfo_vtable_integers_biint equal, nequal, greater, lesser, greq, lseq, land, lior;
	};
		/* Just an example macro. And yes, all three MUST BE pointers */
		/*  to their actual values, rather than the values themselves. */
	#define LIBANDRIA4_TYPEINFO_VTABLE__SET( vtabptr, destptr, srcptr ) ???
	
	
	typedef struct
	{
		libandria4_typeinfo_plaintype *nchar;
		libandria4_typeinfo_plaintype *schar;
		libandria4_typeinfo_plaintype *uchar;
		
		libandria4_typeinfo_plaintype *uint_8;
		libandria4_typeinfo_plaintype *uint_16;
		libandria4_typeinfo_plaintype *uint_32;
		
		/* There are no signed because I don't want to deal with the */
		/*  different options for signed numbers just yet. */
		
	} libandria4_typeinfo_stdtypes_inner;
	typedef struct
	{
		libandria4_typeinfo_stdtypes_inner native;
		libandria4_typeinfo_stdtypes_inner common;
		
	} libandria4_typeinfo_stdtypes;
	libandria4_typeinfo_stdtypes libandria4_typeinfo_stdtypes_platform;
	
	
	
	/* The following are all common type descriptors. */
	
	extern const libandria4_typeinfo_plaintype
		libandria4_typeinfo_descriptor__void,
		
		libandria4_typeinfo_descriptor__char,
		
		libandria4_typeinfo_descriptor__size_t,
		
		libandria4_typeinfo_descriptor__uint8_t,
		libandria4_typeinfo_descriptor__uint16_t,
		libandria4_typeinfo_descriptor__uint32_t;
	
	extern const libandria4_typeinfo_derivedtype
		libandria4_typeinfo_descriptor__voidptr,
		libandria4_typeinfo_descriptor__charptr,
		libandria4_typeinfo_descriptor__size_tptr;
	
	
	extern const libandria4_typeinfo_plaintype
		libandria4_typeinfo_descriptor__libandria4_typeinfo_typeenum,
		libandria4_typeinfo_descriptor__libandria4_typeinfo_uinttype;
	
	extern const libandria4_typeinfo_aggregatetype
		libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype,
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner,
		libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype,
		libandria4_typeinfo_descriptor__libandria4_typeinfo_plainnamingtype,
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_extendedtype,
		libandria4_typeinfo_descriptor__libandria4_typeinfo_plainannotatedtype,
		libandria4_typeinfo_descriptor__libandria4_typeinfo_derivedtype,
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_twintype,
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype;
	
	extern const libandria4_typeinfo_derivedtype
		libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptr,
		libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptrptr;
	
#endif
/* End libandria4 basic typeinfo.h */
