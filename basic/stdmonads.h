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

#ifndef LIBANDRIA4_BASIC_STDMONADS_H
# define LIBANDRIA4_BASIC_STDMONADS_H
	
		/* size_t and ptrdiff_t. */
	#include <stddef.h>
		/* intptr_t and uintptr_t. */
	#include <stdint.h>
	
	#include "monads.h"
	#include "commonerrvals.h"
	
		/* Some OTHER standard monads, that are plain maybe wrappers for */
		/*  standard C types. */
	#include "stdmaybes.h"
	
	
	
	/* These are intended to allow success & failure to be encoded via type, */
	/*  thus reducing the actual value to just a version of one or the */
	/*  other. And no, C doesn't have MEANINGFUL direct support for this, */
	/*  but it does have simple typing, and that is enough to be useful. */
	
	typedef struct libandria4_success_stdresult
	{
		int val;
		
	} libandria4_success_result;
	typedef struct libandria4_failure_stdresult
	{
		int val;
		
	} libandria4_failure_result;
	
	
	
		/* These two types are used if your success or failure needs to */
		/*  support encoding as a pointer. */
	typedef struct libandria4_success_uipresult
	{
		uintptr_t val;
		
	} libandria4_success_uipresult;
	typedef struct libandria4_failure_uipresult
	{
		uintptr_t val;
		
	} libandria4_failure_uipresult;
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_result,
		
		libandria4_success_result,
		libandria4_failure_result
	);
	
	#define LIBANDRIA4_RESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_result, libandria4_success_result, (val) )
	#define LIBANDRIA4_RESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_result, libandria4_failure_result, (val) )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_RESULT_BODYMATCH( var, onsucc, onfail ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, onsucc, onfail )
	#define LIBANDRIA4_RESULT_EXPRMATCH( var, onsucc, onfail ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, onsucc, onfail )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_RESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_result, libandria4_success_result, val )
	#define LIBANDRIA4_RESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_result, libandria4_failure_result, val )
	
	
	libandria4_result libandria4_errno_2result();
	libandria4_result libandria4_errno_popresult( int *errnum );
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_charresult,
		
		char,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_CHARRESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_charresult, char, (val) \
		)
	#define LIBANDRIA4_CHARRESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_charresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_CHARRESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_CHARRESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_CHARRESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_charresult, char, val )
	#define LIBANDRIA4_CHARRESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_charresult, libandria4_failure_uipresult, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_intresult,
		
		int,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_INTRESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_intresult, int, (val) \
		)
	#define LIBANDRIA4_INTRESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_intresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_INTRESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_INTRESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_INTRESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_intresult, int, val )
	#define LIBANDRIA4_INTRESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_intresult, libandria4_failure_uipresult, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_uipresult,
		
		libandria4_success_uipresult,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_UIPRESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_uipresult, libandria4_success_uipresult, (val) \
		)
	#define LIBANDRIA4_UIPRESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_uipresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_UIPRESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_UIPRESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_UIPRESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( \
			libandria4_uipresult, libandria4_success_uipresult, val )
	#define LIBANDRIA4_UIPRESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_uipresult, libandria4_failure_uipresult, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_ptrresult,
		
		void*,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_PTRRESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_ptrresult, void*, (val) \
		)
	#define LIBANDRIA4_PTRRESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_ptrresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_PTRRESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_PTRRESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_PTRRESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_ptrresult, void*, val )
	#define LIBANDRIA4_PTRRESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_ptrresult, libandria4_failure_uipresult, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_sizeresult,
		
		size_t,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_SIZERESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_sizeresult, size_t, (val) \
		)
	#define LIBANDRIA4_SIZERESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_sizeresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_SIZERESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_SIZERESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_SIZERESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_sizeresult, size_t, val )
	#define LIBANDRIA4_SIZERESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_sizeresult, libandria4_failure_uipresult, val )
	
#endif
/* End libandria4 basic stdmonads.h */
