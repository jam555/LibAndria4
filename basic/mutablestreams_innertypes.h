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


/* We need monads.h, but what else? */

#ifndef LIBANDRIA4_BASIC_MUTABLESTREAMS_innertypes_H
# define LIBANDRIA4_BASIC_MUTABLESTREAMS_innertypes_H
	/* Change this macro name eventually. */
	
	/* The stuff below should probably be merged into another file. */
	
	
	
		/* EOF is 0, because EOF isn't really an error, and ( error * 0 ) */
		/*  should "obviously" be no error at all. */
	typedef uintptr_t libandria4_newstreams_err;
	static const libandria4_newstreams_err libandria4_newstreams_eof =
		(libandria4_newstreams_err)0;
	#define LIBANDRIA4_NEWSTREAMS_EOF ( libandria4_newstreams_eof )
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_newstreams_result1,
			size_t,
			libandria4_newstreams_err
	);
	#define LIBANDRIA4_NEWSTREAMS_RESULT1_BUILDSIZET( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_newstreams_result1, size_t, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT1_BUILDERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_newstreams_result1, libandria4_newstreams_err, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT1_RETURNSIZET( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_newstreams_result1, size_t, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT1_RETURNERR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_newstreams_result1, libandria4_newstreams_err, val )
	
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_newstreams_result2,
			libandria4_newstreams_err
	);
	#define LIBANDRIA4_NEWSTREAMS_RESULT2_BUILDJUST( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_newstreams_result2, libandria4_newstreams_err, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT2_BUILDNOTHING( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_newstreams_result2, libandria4_newstreams_err )
	#define LIBANDRIA4_NEWSTREAMS_RESULT2_RETURNJUST( val ) \
		LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_newstreams_result2, libandria4_newstreams_err, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT2_RETURNNOTHING( ... ) \
		LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_newstreams_result2, libandria4_newstreams_err )
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_newstreams_result3,
			char,
			libandria4_newstreams_err
	);
	#define LIBANDRIA4_NEWSTREAMS_RESULT3_BUILDCHAR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_newstreams_result3, char, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT3_BUILDERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_newstreams_result3, libandria4_newstreams_err, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT3_RETURNCHAR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_newstreams_result3, char, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT3_RETURNERR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_newstreams_result3, libandria4_newstreams_err, val )
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		libandria4_newstreams_result4,
			intmax_t,
			libandria4_newstreams_err
	);
	#define LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDINT( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_newstreams_result4, intmax_t, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT4_BUILDERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_newstreams_result4, libandria4_newstreams_err, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT4_RETURNINT( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_newstreams_result4, intmax_t, val )
	#define LIBANDRIA4_NEWSTREAMS_RESULT4_RETURNERR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_newstreams_result4, libandria4_newstreams_err, val )
	
	
	LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE(
		libandria4_newstreams_bituplic1,
			libandria4_newstreams_result1,
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
			libandria4_newstreams_result3,
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
			libandria4_newstreams_result4,
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
	
	
	
	/* End the separate type definitions file, switch back to the */
	/*  primary new-streams file. */
	
#endif
