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

#ifndef LIBANDRIA4_PRIMITIVE_COMMONMACROS_H
# define LIBANDRIA4_PRIMITIVE_COMMONMACROS_H
	
	#if 1
		#define LIBANDRIA4_FLEXARRAY_FILLERLENGTH 
	#else
			/* Note: to improve this header, first verify & probably */
			/*  improve the contents of platformdetecxt.h ... */
		#error "LibAndria4 only supports the C99 default for flex arrays, for e.g. C++ support, improve the header."
	#endif
	
	
	#define LIBANDRIA4_INNERNULLMACRO( ... ) 
	#define LIBANDRIA4_NULLMACRO( ... ) LIBANDRIA4_INNERNULLMACRO( __VA_ARGS__ )
	#define LIBANDRIA4_NULL_MACRO( ... ) LIBANDRIA4_INNERNULLMACRO( __VA_ARGS__ )
	#define LIBANDRIA4_PUSH_NULLMACRO( ... ) LIBANDRIA4_NULLMACRO
	#define LIBANDRIA4_PUSH_NULL_MACRO( ... ) LIBANDRIA4_NULL_MACRO
	#define LIBANDRIA4_DOUBLEPUSH_NULLMACRO( ... ) LIBANDRIA4_PUSH_NULLMACRO
	#define LIBANDRIA4_DOUBLEPUSH_NULL_MACRO( ... ) LIBANDRIA4_PUSH_NULL_MACRO
	
	
	#define LIBANDRIA4_STRINGIFY( a ) LIBANDRIA4_INNER_STRINGIFY( a )
	#define LIBANDRIA4_INNER_STRINGIFY( a ) #a
	
	
	#define LIBANDRIA4_BOOLCAT( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_BOOL( a ), LIBANDRIA4_BOOL( b ) )
	#define LIBANDRIA4_CAT( a, ... ) LIBANDRIA4_PRIMITIVE_CAT( a, __VA_ARGS__ )
	#define LIBANDRIA4_PRIMITIVE_CAT( a, ... ) a ## __VA_ARGS__
	
	#define LIBANDRIA4_CONCAT( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	#define LIBANDRIA4_CONCATENATE( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	#define LIBANDRIA4_JOIN( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	
	
		/* Packages the algorithm to convert from a structure element's */
		/*  address to the structure's address. */
	#define LIBANDRIA4_STRUCTADDRfromELEMADDR( structtype, elemname,  elemptr ) \
		( ( structtype *)( \
			(char*)( elemptr ) + ( \
				(char*)&( ( ( structtype *)0 )-> elemname ) - \
				(char*)( ( structtype *)0 ) ) ) )
	
	
	/* TODO: move these to commonlib.h, and add a define-macro for header */
	/*  use. Also add some to the type-description files that use type-descs */
	/*  instead of "t" in the version-2 variant. */
	/* These generate a function that returns an integer that uniquely */
	/*  identifies the provided type. Extra differentiation via tag, just in */
	/*  case. Use *_IDFUNC() for POD types, use *_IDFUNC2() for non-POD */
	/*  types. And yes, it's ok to use the statics as variables, as long as */
	/*  you know what you're doing. */
	#define LIBANDRIA4_BUILDIDFUNC( type, tag, inner_type ) \
		uintptr_t libandria4_idfunc_type_##type##tag() { \
			static inner_type t; return( (uintptr_t)&t ); }
		/* As above, but with call-once configuration, for more advanced */
		/*  type info. */
	#define LIBANDRIA4_BUILDIDFUNC2( type, tag, inner_type, config_func ) \
		uintptr_t libandria4_idfunc_type_##type##tag() { \
			static inner_type t, *t_ = (inner_type*)0; \
			if( !t_ ) { t_ = &t; config_func( t_ ); } \
			return( (uintptr_t)t_ ); }
	
	
		/* TODO: Pseudo-code, start using platformdetect.h. */
	#if GCC
		
		#define LIBANDRIA4_MAKESECTION_R( sect ) \
			/* Don't need to explicitly declare sections for GCC. */
		#define LIBANDRIA4_MAKESECTION_RW( sect ) \
			/* Don't need to explicitly declare sections for GCC. */
		#define LIBANDRIA4_MAKESECTION_X( sect ) \
			/* Don't need to explicitly declare sections for GCC. */
		
		#define LIBANDRIA4_SECTION_VAR( storage, sect, type, name ) \
			storage type name __attribute__ ((section ( sect )))
		
	#elif MSVC
		
		/* Note that depending on what you want to do, the standard Microsoft */
		/*  tools might not be enough. That seems likely with e.g. overlays */
		/*  for creating link-time equivalents of a C union{}. */
		
		#error "MSVC syntax isn't quite right yet.\n"
		
		
		#define LIBANDRIA4_MAKESECTION_R( sect ) \
			#pragma section( sect,read )
		#define LIBANDRIA4_MAKESECTION_RW( sect ) \
			#pragma section( sect,read,write )
				/* For executable stuff. */
		#define LIBANDRIA4_MAKESECTION_X( sect ) \
			#error "LIBANDRIA4_MAKESECTION_X hasn't been defined for MSVC."
		
		
		#define LIBANDRIA4_SECTION_VAR( storage, sect, type, name ) \
			storage __declspec(allocate( sect )) type name
		
	#endif
	
#endif
/* End libandria4 primitive commonmacros.h */
