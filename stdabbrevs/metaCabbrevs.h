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

#ifndef LIBANDRIA4_STDABBREVS_METACABBREVS_H
# define LIBANDRIA4_STDABBREVS_METACABBREVS_H
	
	/* Developer note: When writing a *_BODYMATCH() or *_EXPRMATCH() (or */
	/*  anything similar), you MUST NOT wrap the "functional" arguments in */
	/*  parentheses when handing themn to the wrapped macro, because they */
	/*  can't be recognized as function macros if you do, which in turn */
	/*  prevents the most common (and completely intended) use-case of */
	/*  handing a function macro to the things so that you can use a simple */
	/*  wrapper for local cases. */
	
		/* Sourced from simpleops.h */
	#define LIB4_OP_SETa \
		LIBANDRIA4_OP_SETa
	#define LIB4_OP_SETb \
		LIBANDRIA4_OP_SETb
	
	
		/* Sourced from commontypes.h */
	#define LIB4_SSIZE \
		libandria4_ssize
	
	
		/* From pascalarray.h */
	#define LIB4_DEFINE_PASCALARRAY_LITERAL2 \
		LIBANDRIA4_DEFINE_PASCALARRAY_LITERAL2
	#define LIB4_DEFINE_PASCALARRAY_STDDEFINE( head, type ) \
		LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( ( head ), ( type ) )
	
	
		/* From monads.h */
	#define LIB4_MONAD_EITHER_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ( var ), matcha, matchb )
	
	
		/* Sourced from stdmonads.h */
	#define LIB4_F_UIPRES \
		libandria4_failure_uipresult
	
	#define LIB4_RESULT \
		libandria4_result
	#define LIB4_INTRESULT \
		libandria4_intresult
	
	#define LIB4_ERRNO_2RESULT \
		libandria4_errno_2result
	
	#define LIB4_RESULT_BUILDSUCCESS( succ ) \
		LIBANDRIA4_RESULT_BUILDSUCCESS( (libandria4_success_result){ succ } )
	#define LIB4_RESULT_BUILDFAILURE( fail ) \
		LIBANDRIA4_RESULT_BUILDFAILURE( (libandria4_failure_result){ fail } )
	
	#define LIB4_INTRESULT_RETURNSUCCESS( succ ) \
		LIBANDRIA4_INTRESULT_RETURNSUCCESS( (int){ succ } )
	#define LIB4_INTRESULT_RETURNFAILURE( fail ) \
		LIBANDRIA4_INTRESULT_RETURNFAILURE( (libandria4_failure_uipresult){ fail } )
	
	#define LIB4_INTRESULT_BODYMATCH( var, matchsucc, matchfail ) \
		LIBANDRIA4_INTRESULT_BODYMATCH( ( var ), matchsucc, matchfail )
	
	
		/* Sourced from commonerrvals.h, often via stdmonads.h */
	#define LIB4_RESULT_GENERIC \
		LIBANDRIA4_RESULT_GENERIC
	#define LIB4_RESULT_FAILURE_DOMAIN \
		LIBANDRIA4_RESULT_FAILURE_DOMAIN
	#define LIB4_RESULT_FAILURE_RANGE \
		LIBANDRIA4_RESULT_FAILURE_RANGE
	
	
		/* From arraccess.h */
	#define LIB4_RETURN_2ND \
		LIBANDRIA4_RETURN_2ND
	
#endif
/* End libandria4 stdabbrevs metaCabbrevs.h */
