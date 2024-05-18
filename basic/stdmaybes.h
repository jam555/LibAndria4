/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2024 Jared A. Maddox

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

#ifndef LIBANDRIA4_BASIC_STDMAYBES_H
# define LIBANDRIA4_BASIC_STDMAYBES_H
	
		/* size_t and ptrdiff_t. */
	#include <stddef.h>
		/* intptr_t and uintptr_t. */
	#include <stdint.h>
	
	#include "monads.h"
	
	
	/* Just generic monads, no special use-case. For the explicit */
	/*  error/success stuff (like libandria4_resuilt{}) check stdmonads.h. */
	/* These types (with their data value) are always available: */
		/*
			libandria4_maybechar			char
			libandria4_maybeint				int
			libandria4_maybefloat			float
			libandria4_maybedouble			double
			libandria4_maybeldouble			long double
			
			libandria4_maybesizet			size_t
			libandria4_maybeptrdifft		ptrdiff_t
			libandria4_maybevoidptr			void*
			libandria4_maybefuncptr			void (*)()
		*/
	/* These types are sometimes available, depending an macro detection: */
		/*
			libandria4_maybeint8t			int8_t
			libandria4_maybeuint8t			uint8_t
			libandria4_maybeintptrt			intptr_t
			libandria4_maybeuintptrt		uintptr_t
			libandria4_maybeintmaxt			intmax_t
			
			libandria4_maybeuintmaxt		uintmax_t
		*/
	
	
	/* Common integer maybes: */
	
	#ifdef INT8_MAX
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeint8t, int8_t );
		
		#define LIBANDRIA4_MAYBEINT8T_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeint8t, int8_t, val )
		#define LIBANDRIA4_MAYBEINT8T_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeint8t, int8_t )
		
		#define LIBANDRIA4_MAYBEINT8T_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEINT8T_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEINT8T_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
			/* Alters the result type of the "nothing" case. */
		#define LIBANDRIA4_MAYBEINT8T_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
		
		#define LIBANDRIA4_MAYBEINT8T_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeint8t, int8_t, val )
		#define LIBANDRIA4_MAYBEINT8T_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeint8t, int8_t )
	#endif
	
	
	#ifdef UINT8_MAX
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeuint8t, uint8_t );
		
		#define LIBANDRIA4_MAYBEUINT8T_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeuint8t, uint8_t, val )
		#define LIBANDRIA4_MAYBEUINT8T_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeuint8t, uint8_t )
		
		#define LIBANDRIA4_MAYBEUINT8T_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEUINT8T_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEUINT8T_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
			/* Alters the result type of the "nothing" case. */
		#define LIBANDRIA4_MAYBEUINT8T_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
		
		#define LIBANDRIA4_MAYBEUINT8T_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeuint8t, uint8_t, val )
		#define LIBANDRIA4_MAYBEUINT8T_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeuint8t, uint8_t )
	#endif
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybechar, char );
	
	#define LIBANDRIA4_MAYBECHAR_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybechar, char, val )
	#define LIBANDRIA4_MAYBECHAR_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybechar, char )
	
	#define LIBANDRIA4_MAYBECHAR_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBECHAR_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBECHAR_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBECHAR_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBECHAR_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybechar, char, val )
	#define LIBANDRIA4_MAYBECHAR_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybechar, char )
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeint, int );
	
	#define LIBANDRIA4_MAYBEINT_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeint, int, val )
	#define LIBANDRIA4_MAYBEINT_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeint, int )
	
	#define LIBANDRIA4_MAYBEINT_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEINT_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEINT_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBEINT_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBEINT_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeint, int, val )
	#define LIBANDRIA4_MAYBEINT_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeint, int )
	
	
	#ifdef INTPTR_MAX
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeintptrt, intptr_t );
		
		#define LIBANDRIA4_MAYBEINTPTRT_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeintptrt, intptr_t, val )
		#define LIBANDRIA4_MAYBEINTPTRT_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeintptrt, intptr_t )
		
		#define LIBANDRIA4_MAYBEINTPTRT_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEINTPTRT_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEINTPTRT_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
			/* Alters the result type of the "nothing" case. */
		#define LIBANDRIA4_MAYBEINTPTRT_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
		
		#define LIBANDRIA4_MAYBEINTPTRT_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeintptrt, intptr_t, val )
		#define LIBANDRIA4_MAYBEINTPTRT_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeintptrt, intptr_t )
	#endif
	
	
	#ifdef UINTPTR_MAX
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeuintptrt, uintptr_t );
		
		#define LIBANDRIA4_MAYBEUINTPTRT_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeuintptrt, uintptr_t, val )
		#define LIBANDRIA4_MAYBEUINTPTRT_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeuintptrt, uintptr_t )
		
		#define LIBANDRIA4_MAYBEUINTPTRT_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEUINTPTRT_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEUINTPTRT_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
			/* Alters the result type of the "nothing" case. */
		#define LIBANDRIA4_MAYBEUINTPTRT_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
		
		#define LIBANDRIA4_MAYBEUINTPTRT_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeuintptrt, uintptr_t, val )
		#define LIBANDRIA4_MAYBEUINTPTRT_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeuintptrt, uintptr_t )
	#endif
	
	
	#ifdef INTMAX_MAX
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeintmaxt, intmax_t );
		
		#define LIBANDRIA4_MAYBEINTMAXT_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeintmaxt, intmax_t, val )
		#define LIBANDRIA4_MAYBEINTMAXT_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeintmaxt, intmax_t )
		
		#define LIBANDRIA4_MAYBEINTMAXT_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEINTMAXT_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEINTMAXT_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
			/* Alters the result type of the "nothing" case. */
		#define LIBANDRIA4_MAYBEINTMAXT_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
		
		#define LIBANDRIA4_MAYBEINTMAXT_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeintmaxt, intmax_t, val )
		#define LIBANDRIA4_MAYBEINTMAXT_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeintmaxt, intmax_t )
	#endif
	
	
	#ifdef UINTMAX_MAX
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeuintmaxt, uintmax_t );
		
		#define LIBANDRIA4_MAYBEUINTMAXT_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeuintmaxt, uintmax_t, val )
		#define LIBANDRIA4_MAYBEUINTMAXT_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeuintmaxt, uintmax_t )
		
		#define LIBANDRIA4_MAYBEUINTMAXT_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEUINTMAXT_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
		#define LIBANDRIA4_MAYBEUINTMAXT_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
			/* Alters the result type of the "nothing" case. */
		#define LIBANDRIA4_MAYBEUINTMAXT_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
			LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
		
		#define LIBANDRIA4_MAYBEUINTMAXT_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeuintmaxt, uintmax_t, val )
		#define LIBANDRIA4_MAYBEUINTMAXT_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeuintmaxt, uintmax_t )
	#endif
	
	
	
	/* Floating-point maybes: */
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybefloat, float );
	
	#define LIBANDRIA4_MAYBEFLOAT_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybefloat, float, val )
	#define LIBANDRIA4_MAYBEFLOAT_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybefloat, float )
	
	#define LIBANDRIA4_MAYBEFLOAT_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEFLOAT_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEFLOAT_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBEFLOAT_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBEFLOAT_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybefloat, float, val )
	#define LIBANDRIA4_MAYBEFLOAT_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybefloat, float )
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybedouble, double );
	
	#define LIBANDRIA4_MAYBEDOUBLE_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybedouble, double, val )
	#define LIBANDRIA4_MAYBEDOUBLE_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybedouble, double )
	
	#define LIBANDRIA4_MAYBEDOUBLE_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEDOUBLE_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEDOUBLE_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBEDOUBLE_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBEDOUBLE_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybedouble, double, val )
	#define LIBANDRIA4_MAYBEDOUBLE_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybedouble, double )
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeldouble, long double );
	
	#define LIBANDRIA4_MAYBELDOUBLE_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeldouble, long double, val )
	#define LIBANDRIA4_MAYBELDOUBLE_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeldouble, long double )
	
	#define LIBANDRIA4_MAYBELDOUBLE_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBELDOUBLE_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBELDOUBLE_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBELDOUBLE_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBELDOUBLE_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeldouble, long double, val )
	#define LIBANDRIA4_MAYBELDOUBLE_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeldouble, long double )
	
	
	
	/* Array and pointer maybes: */
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybesizet, size_t );
	
	#define LIBANDRIA4_MAYBESIZET_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybesizet, size_t, val )
	#define LIBANDRIA4_MAYBESIZET_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybesizet, size_t )
	
	#define LIBANDRIA4_MAYBESIZET_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBESIZET_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBESIZET_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBESIZET_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBESIZET_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybesizet, size_t, val )
	#define LIBANDRIA4_MAYBESIZET_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybesizet, size_t )
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybeptrdifft, ptrdiff_t );
	
	#define LIBANDRIA4_MAYBEPTRDIFFT_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybeptrdifft, ptrdiff_t, val )
	#define LIBANDRIA4_MAYBEPTRDIFFT_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybeptrdifft, ptrdiff_t )
	
	#define LIBANDRIA4_MAYBEPTRDIFFT_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEPTRDIFFT_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEPTRDIFFT_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBEPTRDIFFT_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBEPTRDIFFT_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybeptrdifft, ptrdiff_t, val )
	#define LIBANDRIA4_MAYBEPTRDIFFT_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybeptrdifft, ptrdiff_t )
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybevoidptr, void* );
	
	#define LIBANDRIA4_MAYBEVOIDPTR_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybevoidptr, void*, val )
	#define LIBANDRIA4_MAYBEVOIDPTR_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybevoidptr, void* )
	
	#define LIBANDRIA4_MAYBEVOIDPTR_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEVOIDPTR_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEVOIDPTR_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBEVOIDPTR_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBEVOIDPTR_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybevoidptr, void*, val )
	#define LIBANDRIA4_MAYBEVOIDPTR_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybevoidptr, void* )
	
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( libandria4_maybefuncptr, void (*)() );
	
	#define LIBANDRIA4_MAYBEFUNCPTR_BUILDJUST( val ) LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_maybefuncptr, void (*)(), val )
	#define LIBANDRIA4_MAYBEFUNCPTR_BUILDNOTHING() LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_maybefuncptr, void (*)() )
	
	#define LIBANDRIA4_MAYBEFUNCPTR_BODYMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEFUNCPTR_EXPRMATCH( var, onjust, otherwise ) LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, onjust, otherwise )
	#define LIBANDRIA4_MAYBEFUNCPTR_REDUCE( var, alttype, altval ) LIBANDRIA4_MONAD_MAYBE_REDUCE( alttype, var, altval )
		/* Alters the result type of the "nothing" case. */
	#define LIBANDRIA4_MAYBEFUNCPTR_EXPRCHAIN( var, onjust, nothingname, nothingtype ) \
		LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( var, onjust, nothingname, nothingtype )
	
	#define LIBANDRIA4_MAYBEFUNCPTR_RETURNJUST( val ) LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_maybefuncptr, void (*)(), val )
	#define LIBANDRIA4_MAYBEFUNCPTR_RETURNNOTHING() LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_maybefuncptr, void (*)() )
	
#endif
/* End libandria4 basic stdmaybes.h */
