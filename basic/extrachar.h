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

#ifndef LIBANDRIA4_BASIC_EXTRACHAR_H
# define LIBANDRIA4_BASIC_EXTRACHAR_H
	
	
	/* extrachar.h : A file for stream I/O with per-character metadata. */
	
	/* This started as a direct copy of the MetaC version: it will probably */
	/*  replace the MetaC version whenever work restarts on that. */
	
	/* extrachars should be used anywhere that some context-sensitivity (or */
	/*  just the desire to track row, column, and source file) exists on a */
	/*  per-character basis. Because these characters are MUCH heavier than */
	/*  normal, you should swap them out for normal characters just as soon */
	/*  as you get done with the need to track that data (for example, in */
	/*  C-style macros, you can ditch almost all of it in the process of */
	/*  storing the macro, just keeping line/column/file data on a per-macro */
	/*  basis). */
	
	
	
		/* size_t and ptrdiff_t. */
	#include <stddef.h>
		/* The uint*_t and int*_t types. */
	#include <stdint.h>
	#include <errno.h>
	
	#include "stdmonads.h"
	#include "commonlib.h"
	
	#include "stream.h"
	
		/* Because we WILL want to define full string-handling support. */
	#include "pascalstring.h"
	#include "commonparrs.h"
	
	
	
		/* The character type used INSIDE of an extrachar. Note that */
		/*  this will HOPEFULLY be rendered configurable in the future, */
		/*  so don't be hardcoding things, just use this typedef and */
		/*  these defines. */
	typedef uint32_t libandria_extrachar_innerchar;
	#define LIBANDRIA4_EXTRACHAR_INNERCHAR_MIN 0
	#define LIBANDRIA4_EXTRACHAR_INNERCHAR_MAX UINT32_MAX
	
		/* Because it's wasteful to have individual variables for these. */
	typedef enum
	{
		libandria4_extrachar_flags_NULL = 0,
		
			/* No non-space display characters had been seen since the */
			/*  last line-incrementing character WHEN this character was */
			/*  first read: this character might or might not change that */
			/*  for the NEXT character. */
		libandria4_extrachar_flags_freshline = 1,
			/* This character occurs in the first column of the current */
			/*  line. */
		libandria4_extrachar_flags_firstcol = 2,
			/* This line COUNTS AS part of the previous line: this */
			/*  depends on user-specific feedback, but it's state during */
			/*  *_firstcol will be maintained for the rest of the line. */
		libandria4_extrachar_flags_delimited = 4,
			/* This line is AFFILIATED WITH the preceding NON-DELIMITED */
			/*  line: the state of this value should remain the same for */
			/*  the entirety of a set of delimited lines. */
		libandria4_extrachar_flags_continuation = 8,
			/* Used ONLY for line-incrementing characters: pretend that */
			/*  the character in question is just a keep-alive or */
			/*  something, DO NOT advance the line, screw with */
			/*  *_freshline/*_delimited/etc., or anything else you'd */
			/*  normally do in response to a new line. It should ALSO */
			/*  not be treated as a space or tab character, it's just a */
			/*  NO-OP control character to be mostly (or entirely) */
			/*  ignored. Mostly meant for compatibility with */
			/*  Microsoft-style two-character newlines, though there are */
			/*  some other cases (other companies, delimited newlines, */
			/*  etc.) where it's relevant. */
		libandria4_extrachar_flags_silentnewline = 16,
			/* I don't need to know what these do, that's the USER'S */
			/*  problem. They're here in case I expand to the limits of */
			/*  an int at some point.  */
		libandria4_extrachar_flags_usermarker1 = 32,
		libandria4_extrachar_flags_usermarker2 = 64,
		libandria4_extrachar_flags_usermarker3 = 128,
		
		libandria4_extrachar_flags_END
		
	} libandria4_extrachar_flags;
	
	
		/*
			* pascalarray
			* parr (a duplicate of * pascalarray)
			* pascalarray_result
			* parrres (a duplicate of * pascalarray_result)
			* pascalarray_excerpt
			* pascalarray_excerpt_result
			* pascalarray_tracker
			* pascalarray_tracker_result
		*/
	typedef libandria4_utf32_pascalarray_tracker libandria4_extrachar_stringtracker;
		/* libandria4_extrachar_stringtracker_pascalarray{} */
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE(
		libandria4_extrachar_stringtracker_,
		libandria4_extrachar_stringtracker );
	typedef libandria4_extrachar_stringtracker_pascalarray libandria4_extrachar_nameparr;
	
	
	typedef struct libandria4_extrachar_stream
	{
		libandria4_extrachar_stringtracker name;
		
			/* Data source. Note that buf should be drawn from first. */
		libandria4_commonio_handle *hand;
		libandria4_extrachar_pascalarray *buf;
		size_t used;
		
			/* These may or may not get used by the streamset, depending */
			/*  on it's configuration. */
		uintmax_t line, column;
		libandria4_extrachar_flags flags;
		
			/* Note: set this to 0, then let the streamset do everything */
			/*  else. Only the streamset should modify it after it's */
			/*  initialization. */
		size_t index;
		
	} libandria4_extrachar_stream;
	libandria4_extrachar_result libandria4_extrachar_getchar
	(
		libandria4_extrachar_stream *stream,
			uintmax_t *over_line,
			uintmax_t *over_col,
			libandria4_extrachar_flags *over_flags
	);
	int libandria4_extrachar_ungetchar
	(
		libandria4_extrachar_stream *stream,
			libandria4_extrachar ec
	);
	libandria4_extrachar_result libandria4_extrachar_peekchar
	(
		libandria4_extrachar_stream *stream,
			uintmax_t *over_line,
			uintmax_t *over_col,
			libandria4_extrachar_flags *over_flags
	);
	
	
	
	
	/* The code below here is incomplete: Finish it before using this file. */
	
	
	
	typedef struct libandria4_extrachar_streamset libandria4_extrachar_streamset;
	
	typedef struct libandria4_extrachar
	{
		uintmax_t line, column;
		size_t srcstream;
		
			/* This will stereotypically be Unicode, but could be ASCII, */
			/*  de-shifted Shift-JIS, or any other fixed-size character */
			/*  set that WILL actually fit. DO NOT try to shove */
			/*  variable-width characters into it, convert them to */
			/*  fixed-width first. */
		libandria_extrachar_innerchar c;
		libandria4_extrachar_flags flags;
		
	} libandria4_extrachar;
	LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDECLARE( libandria4_extrachar_, libandria4_extrachar );
	
		/* A set of identifiers for the streams being used by a particular */
		/*  sequence of extrachars. Individual identifiers should have */
		/*  their ref counts control their lifetimes, so that individual */
		/*  "slots" can be reused when available. The streamset() should */
		/*  be managed via refcount too. */
		/* Actually, thinking about it, the streamset should SPECIFICALLY */
		/*  be tracked by user code, not individual extrachars. Doing */
		/*  otherwise would be a bit much bloat to really justify, even if */
		/*  extrachars use proportionatly no space. Instead of coding it */
		/*  explicitly, use the refcount/refpointer "monads" for it. */
	struct libandria4_extrachar_streamset
	{
		libandria4_extrachar_stream *stream;
		
		libandria4_extrachar_flags flags;
		
		libandria4_extrachar_nameparr *streamnames;
		
		??? ;
		
	};
	
	LIB4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_extrachar_result,
		
		libandria4_extrachar,
			/* Both cases are meant to be errors, one just provides some */
			/*  sort of error-description pointer. */
		libandria4_commonlib_eithvoidp
	);
	
	#define LIBANDRIA4_EXTRACHARRESULT_BUILDSUCCESS( val ) \
		LIB4_MONAD_EITHER_BUILDLEFT( libandria4_extrachar_result, libandria4_extrachar, (val) )
	#define LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_VOIDP( val ) \
		LIB4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_extrachar_result, libandria4_commonlib_eithvoidp, \
			LIBANDRIA4_COMMONLIB_EITHVOIDP_VOIDP( val ) )
	#define LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( val ) \
		LIB4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_extrachar_result, libandria4_commonlib_eithvoidp, \
			LIBANDRIA4_COMMONLIB_EITHVOIDP_ERR( val ) )
	
	#define LIBANDRIA4_EXTRACHARRESULT_BODYMATCH( var,  onsucc, onptrerr, onnumerr, onanomaly ) \
		{ libandria4_extrachar_result \
			libandria4_extrachar_result_tmp = (var); int res = 0; \
			libandria4_extrachar a; \
			libandria4_commonlib_eithvoidp b; \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( libandria4_extrachar_result_tmp, \
				LIBANDRIA4_OP_SETaFLAGresAS1, LIBANDRIA4_OP_SETbFLAGresAS2 ); \
			if( res == 1 ) { onsucc( a ); } \
			else if( res == 2 ) { LIBANDRIA4_MONAD_EITHER_BODYMATCH( b, onptrerr, onnumerr ); } \
			else { onanomaly( res, libandria4_extrachar_result_tmp ); } }
	#define LIBANDRIA4_EXTRACHARRESULT_EXPRMATCH( var, type,  onsucc, onptrerr, onnumerr ) \
		( ( LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
			LIBANDRIA4_OP_ISVAL1, LIBANDRIA4_OP_ISVAL0 ) ) ? \
				( onsucc( *( (libandria4_extrachar*) \
					LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
						LIBANDRIA4_OP_UNARYTOPTR, LIBANDRIA4_OP_ISVAL0 ) ) ) ) : \
				( LIBANDRIA4_MONAD_EITHER_EXPRMATCH( \
						*( (libandria4_commonlib_eithvoidp*) \
							LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, \
								LIBANDRIA4_OP_ISVAL0, LIBANDRIA4_OP_UNARYTOPTR ) ), \
						onptrerr, onnumerr ) ) )
	
	#define LIBANDRIA4_EXTRACHARRESULT_RETURNSUCCESS( val ) \
		return( LIBANDRIA4_EXTRACHARRESULT_BUILDSUCCESS( val ) )
	#define LIBANDRIA4_EXTRACHARRESULT_RETURNERROR_VOIDP( val ) \
		return( LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_VOIDP( val ) )
	#define LIBANDRIA4_EXTRACHARRESULT_RETURNERROR_NUM( val ) \
		return( LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( val ) )
	
#endif
