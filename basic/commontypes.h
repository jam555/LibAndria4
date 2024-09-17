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

#ifndef LIBANDRIA4_BASIC_COMMONTYPES_H
# define LIBANDRIA4_BASIC_COMMONTYPES_H
	
	#if __INTELLISENSE__
		#include <BaseTsd.h>
		typedef SSIZE_T libandria4_ssize;
	#else
		#include <sys/types.h>
		typedef ssize_t libandria4_ssize;
	#endif
	
	
	
	#define LIBANDRIA4_DOUBLEELEMENT_DECLARE( newname, type ) \
		typedef struct ( newname ) { (type) left; (type) right; } ( newname ); \
		inline ( newname ) ( newname ## _build )( (type) l, (type) r ) { return( (newname){ l, r } ); }
	#define LIBANDRIA4_DOUBLEELEMENT_DEFINE( newname, type ) \
		( newname ) ( newname ## _build )( (type) l, (type) r ) { return( (newname){ l, r } ); }
	
	/* All of these following declares should have a corresponding define in a .c file. */
	LIBANDRIA4_DOUBLEELEMENT_DECLARE( libandria4_doublechar, char );
	LIBANDRIA4_DOUBLEELEMENT_DECLARE( libandria4_doubleshort, short );
	LIBANDRIA4_DOUBLEELEMENT_DECLARE( libandria4_doubleint, int );
	LIBANDRIA4_DOUBLEELEMENT_DECLARE( libandria4_doublelong, long );
	
	LIBANDRIA4_DOUBLEELEMENT_DECLARE( libandria4_doublesize, size_t );
	LIBANDRIA4_DOUBLEELEMENT_DECLARE( libandria4_doubleintptr, intptr_t );
	LIBANDRIA4_DOUBLEELEMENT_DECLARE( libandria4_doubleuintptr, uintptr_t );
	
	LIBANDRIA4_DOUBLEELEMENT_DECLARE( libandria4_doublevoidp, void* );
	
	
	
	#include "../basic/monads.h"
	
	/* Positive errors are always untranslatable characters, negative are */
	/*  function-dependant errors. Unicode is expected for *_monadicchar32{}, */
	/*  so only 22 bit character values, thus posing no overflow risks. */
	/* ... Isn't Unicode 21 bit instead of 22? */
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE( libandria4_common_monadicchar8, char, int32_t );
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE( libandria4_common_monadicchar32, uint32_t, int32_t );
	
	/* These produce the actual values. */
	#define libandria4_common_monadicchar8_BUILDSUCC( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_common_monadicchar8, uint8_t, val )
	#define libandria4_common_monadicchar8_BUILDERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_common_monadicchar8, int32_t, val )
	/* Convenience wrappers. */
	#define libandria4_common_monadicchar8_RETURNSUCC( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_common_monadicchar8, uint8_t, val )
	#define libandria4_common_monadicchar8_RETURNERR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_common_monadicchar8, int32_t, val )
	
	/* These produce the actual values. */
	#define libandria4_common_monadicchar32_BUILDSUCC( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_common_monadicchar32, uint32_t, val )
	#define libandria4_common_monadicchar32_BUILDERR( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_common_monadicchar32, int32_t, val )
	/* Convenience wrappers. */
	#define libandria4_common_monadicchar32_RETURNSUCC( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_common_monadicchar32, uint32_t, val )
	#define libandria4_common_monadicchar32_RETURNERR( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_common_monadicchar32, int32_t, val )
	
	/* These defines are generic, usable both for all the */
	/*  *_monadicchar*{} types, and any other types derived by */
	/*  LIBANDRIA4_MONAD_EITHER_BUILDTYPE(). The *BODY* version */
	/*  takes statements, *EXPR* takes expressions and produces */
	/*  an expression. */
	#define libandria4_common_monadicchar_BODYMATCH( var, onsucc, onerr ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, onsucc, onerr )
	#define libandria4_common_monadicchar_EXPRMATCH( var, onsucc, onerr) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, onsucc, onerr )
		/* Chaining doesn't make much sense without a type change; usually */
		/*  a maybe monad is the correct choice. */
	#define libandria4_common_monadicchar_EXPRCHAIN( var, onsucc, builderr ) \
		LIBANDRIA4_MONAD_EITHER_EXPRCHAIN( var, onsucc, builderr )
	/* Note: If you need reduce(), then just wrap *_EXPRMATCH(). */
	
#endif
/* End libandria4 basic commontypes.h */
