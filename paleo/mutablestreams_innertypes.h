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



	/* This will initially trigger a recursion loop, but it'll end on the */
	/*  SECOND inclusion of "mutablestreams.h", as that one only includes */
	/*  this file INSIDE of an include guard. Also, the original inclusion */
	/*  of this file will (if it was done directly) never actually include */
	/*  the contents of it's include guard, as it's SECOND inclusion will */
	/*  under those conditions define the include guard before the first */
	/*  invocation has a chance to do the same. */
#include "mutablestreams.h"

#ifndef LIBANDRIA4_BASIC_MUTABLESTREAMS_innertypes_H
# define LIBANDRIA4_BASIC_MUTABLESTREAMS_innertypes_H
	/* Change this macro name eventually. */
	
	#include <stddef.h>
	#include <stdint.h>
	
	#include "monads.h"
	#include "commonio.h"
	
	
	
	/* These are temps to retain compatibility while the mutablestreams */
	/*  files move over to the permanent names. */
	
	typedef libandria4_commonio_perr libandria4_newstreams_err;
	#define libandria4_newstreams_eof ( libandria4_commoniovals_eof )
	#define LIBANDRIA4_NEWSTREAMS_EOF ( LIBANDRIA4_COMMONIOVALS_EOF )
	
	#define libandria4_newstreams_result1 ( libandria4_commonio_eithsize2 )
	#define LIBANDRIA4_NEWSTREAMS_RESULT1_BUILDSIZET( ... ) \
		LIBANDRIA4_COMMONIO_EITHSIZE2_BUILDSIZE( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT1_BUILDERR( ... ) \
		LIBANDRIA4_COMMONIO_EITHSIZE2_BUILDERR( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT1_RETURNSIZET( ... ) \
		LIBANDRIA4_COMMONIO_EITHSIZE2_RETURNSIZE( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT1_RETURNERR( ... ) \
		LIBANDRIA4_COMMONIO_EITHSIZE2_RETURNERR( __VA_ARGS__ )
	
	#define libandria4_newstreams_result2 ( libandria4_commonio_mayerr2 )
	#define LIBANDRIA4_NEWSTREAMS_RESULT2_BUILDJUST( ... ) \
		LIBANDRIA4_COMMONIO_MAYERR2_BUILDJUST( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT2_BUILDNOTHING( ... ) \
		LIBANDRIA4_COMMONIO_MAYERR2_BUILDNOTHING( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT2_RETURNJUST( ... ) \
		LIBANDRIA4_COMMONIO_MAYERR2_RETURNJUST( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT2_RETURNNOTHING( ... ) \
		LIBANDRIA4_COMMONIO_MAYERR2_RETURNNOTHING( __VA_ARGS__ )
	
	#define libandria4_newstreams_result3 ( libandria4_commonio_eithchar2 )
	#define LIBANDRIA4_NEWSTREAMS_RESULT3_BUILDCHAR( ... ) \
		LIBANDRIA4_COMMONIO_EITHCHAR2_BUILDCHAR( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT3_BUILDERR( ... ) \
		LIBANDRIA4_COMMONIO_EITHCHAR2_BUILDERR( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT3_RETURNCHAR( ... ) \
		LIBANDRIA4_COMMONIO_EITHCHAR2_RETURNCHAR( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT3_RETURNERR( ... ) \
		LIBANDRIA4_COMMONIO_EITHCHAR2_RETURNERR( __VA_ARGS__ )
	
	#define libandria4_newstreams_result4 ( libandria4_commonio_eithintmax2 )
	#define LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDINT( ... ) \
		LIBANDRIA4_COMMONIO_EITHINTMAX2_BUILDINT( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR( ... ) \
		LIBANDRIA4_COMMONIO_EITHINTMAX2_BUILDERR( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT4_RETURNINT( ... ) \
		LIBANDRIA4_COMMONIO_EITHINTMAX2_RETURNINT( __VA_ARGS__ )
	#define LIBANDRIA4_NEWSTREAMS_RESULT4_RETURNERR( ... ) \
		LIBANDRIA4_COMMONIO_EITHINTMAX2_RETURNERR( __VA_ARGS__ )
	
	
	
	/* The types below this will remain here: they exist to support special */
	/*  mutablestream capabilities instead of normal commonio stuff. */
	
	LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE(
		libandria4_newstreams_bituplic1,
			libandria4_newstreams_result1, /* libandria4_commonio_eithsize2 */
			libandria4_FILE_redirection
	);
	#define LIBANDRIA4_NEWSTREAMS_BITUP1_BUILDJUSTSTREAM( strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			libandria4_newstreams_bituplic1, \
			libandria4_newstreams_result1, \
			libandria4_FILE_redirection, \
			strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP1_BUILDJUSTBOTH( reslt, strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTBOTH( \
			libandria4_newstreams_bituplic1, \
			libandria4_newstreams_result1, \
			libandria4_FILE_redirection, \
			reslt, strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP1_RETURNSTREAM( strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_RETURNRIGHT( \
			libandria4_newstreams_bituplic1, \
			libandria4_newstreams_result1, \
			libandria4_FILE_redirection, \
			strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP1_RETURNBOTH( reslt, strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( \
			libandria4_newstreams_bituplic1, \
			libandria4_newstreams_result1, \
			libandria4_FILE_redirection, \
			reslt, strmptr )
	
	LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE(
		libandria4_newstreams_bituplic2,
			libandria4_newstreams_err,
			libandria4_FILE_redirection
	);
	#define LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTSTREAM( strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			libandria4_newstreams_bituplic2, \
			libandria4_newstreams_err, \
			libandria4_FILE_redirection, \
			strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP2_BUILDJUSTBOTH( reslt, strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTBOTH( \
			libandria4_newstreams_bituplic2, \
			libandria4_newstreams_err, \
			libandria4_FILE_redirection, \
			reslt, strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP2_RETURNSTREAM( strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_RETURNRIGHT( \
			libandria4_newstreams_bituplic2, \
			libandria4_newstreams_err, \
			libandria4_FILE_redirection, \
			strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP2_RETURNBOTH( reslt, strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( \
			libandria4_newstreams_bituplic2, \
			libandria4_newstreams_err, \
			libandria4_FILE_redirection, \
			reslt, strmptr )
	
	LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE(
		libandria4_newstreams_bituplic3,
			libandria4_newstreams_result3, /* libandria4_commonio_eithchar2 */
			libandria4_FILE_redirection
	);
	#define LIBANDRIA4_NEWSTREAMS_BITUP3_BUILDJUSTSTREAM( strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			libandria4_newstreams_bituplic3, \
			libandria4_newstreams_result3, \
			libandria4_FILE_redirection, \
			strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP3_BUILDJUSTBOTH( reslt, strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTBOTH( \
			libandria4_newstreams_bituplic3, \
			libandria4_newstreams_result3, \
			libandria4_FILE_redirection, \
			reslt, strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP3_RETURNSTREAM( strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_RETURNRIGHT( \
			libandria4_newstreams_bituplic3, \
			libandria4_newstreams_result3, \
			libandria4_FILE_redirection, \
			strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP3_RETURNBOTH( reslt, strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( \
			libandria4_newstreams_bituplic3, \
			libandria4_newstreams_result3, \
			libandria4_FILE_redirection, \
			reslt, strmptr )
	
	LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE(
		libandria4_newstreams_bituplic4,
			libandria4_newstreams_result4, /* libandria4_commonio_eithintmax2 */
			libandria4_FILE_redirection
	);
	#define LIBANDRIA4_NEWSTREAMS_BITUP4_BUILDJUSTSTREAM( strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			libandria4_newstreams_bituplic4, \
			libandria4_newstreams_result4, \
			libandria4_FILE_redirection, \
			strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP4_BUILDJUSTBOTH( reslt, strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTBOTH( \
			libandria4_newstreams_bituplic4, \
			libandria4_newstreams_result4, \
			libandria4_FILE_redirection, \
			reslt, strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNSTREAM( strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_RETURNRIGHT( \
			libandria4_newstreams_bituplic4, \
			libandria4_newstreams_result4, \
			libandria4_FILE_redirection, \
			strmptr )
	#define LIBANDRIA4_NEWSTREAMS_BITUP4_RETURNBOTH( reslt, strmptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( \
			libandria4_newstreams_bituplic4, \
			libandria4_newstreams_result4, \
			libandria4_FILE_redirection, \
			reslt, strmptr )
	
#endif
