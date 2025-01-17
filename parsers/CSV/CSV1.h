#ifndef LIBANDRIA4_PARSER_CSV_CSV1_H
 #define LIBANDRIA4_PARSER_CSV_CSV1_H
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
	
	
	#include <ctype.h>
		/* For the continuation-trampoline-style engine & related definitions. */
	#include "../../basic/ctsengine.h"
		/* For libandria4_char_pascalarray{} and friends. */
	#include "../../basic/pascalstring.h"
	
	
	
	typedef struct libandria4_parser_CSV_CSV1_file libandria4_parser_CSV_CSV1_file;
	typedef struct libandria4_parser_CSV_CSV1_callargs libandria4_parser_CSV_CSV1_callargs;
	
	
	
	struct libandria4_parser_CSV_CSV1_file
	{
		??? file;
			/* This MUST get initialized to 0 at the start, and it WILL get */
			/*  incremented for EACH distinct record. Also, rollover IS an */
			/*  error that will cause onfatal() to get called. Be ready to */
			/*  "dynamically patch" around that by setting this to 3, then */
			/*  building the needed stack state... or maybe another route is */
			/*  better? */
		unsigned recordindex;
		int cStr, csvStr;
			/* BitTorrent strings: INCOMPATIBLE with colonSep. */
		int btStr;
		int commaSep, colonSep, semiSep, spacedSep, tabSep;
		int parenNest, sqrNest, curlNest, angleNest;
		
		/* The following should, except for onfatal(), basically just return */
		/*  whatever is on top of stack[ 0 ]. They shouldn't alter anything on */
		/*  any of the "standard" stacks (there's at least two, but I don't */
		/*  recall the actual total). */
			/* Used for things like allocation failures. Note that this WILL */
			/*  blindly get used, so actually fill it with something. */
			/* Note: find everywhere that uses this, and make sure it has */
			/*  some way to indicate it's actual position uniquely. Maybe a */
			/*  pointer to a function-static? */
		libandria4_cts_closure onfatal;
			/* Which of these get used depends on this->recordindex . */
		libandria4_cts_closure firstrec, secondrec, restrec;
	};
	
	
	
	/* I think these three actually need to be written... or, more likely, */
	/*  swapped out for "real" equivalents from elsewhere. */
		/* Returns a character, or an "error status" (EOF is positive, retry is */
		/*  0, error is negative). */
	libandria4_common_monadicchar8 libandria4_parser_CSV_CSV1_getc( libandria4_parser_CSV_CSV1_file* );
		/* Negative on error, 0 on retry, positive on success. Gets used by */
		/*  libandria4_parser_CSV_CSV1_ungetc(), which is listed further down. */
	int libandria4_parser_CSV_CSV1_unget( libandria4_parser_CSV_CSV1_file*, char );
		/* Negative on null argument, 0 on invalid, 1 on valid. */
	int libandria4_parser_CSV_CSV1_validate( libandria4_parser_CSV_CSV1_file* );
	
	
		/* This identifies the interpretation of the supplied character */
		/*  according to the settings in the provided *_CSV1_file{}. */
	typedef enum
	{
		libandria4_parser_CSV_CSV1_sortchar_categories__error_badargs = -1,
		
		libandria4_parser_CSV_CSV1_sortchar_categories_invalid = 0,
		
		libandria4_parser_CSV_CSV1_sortchar_categories_recordsep = 1,
		libandria4_parser_CSV_CSV1_sortchar_categories_fieldsep,
		libandria4_parser_CSV_CSV1_sortchar_categories_allvaluechar,
		libandria4_parser_CSV_CSV1_sortchar_categories_nestingopener,
		libandria4_parser_CSV_CSV1_sortchar_categories_nestingcloser,
		libandria4_parser_CSV_CSV1_sortchar_categories_doublequote
		
	} libandria4_parser_CSV_CSV1_sortchar_categories;
	libandria4_parser_CSV_CSV1_sortchar_categories libandria4_parser_CSV_CSV1_sortchar
	(
		libandria4_parser_CSV_CSV1_file *f,
		char character
	);
	
	
	
	
	
	/* The following functions are compliant with (libandria4_cts_framefunc*). */
	
	
	
		/* This wraps around libandria4_parser_CSV_CSV1_unget() */
		/* Expects a type on top of a character, both as uchars on stack[ 1 ], */
		/*  and a return closure on stack[ 0 ] as a libandria4_cts_closure{}. */
		/*  DOES NOT pop the type or character, but DOES pop the return closure. */
		/*  Note that while the character gets handed to *_unget(), the type is */
		/*  expected to just be recalculated if needed. */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_ungetc( libandria4_cts_context *ctx, void *data_ );
		/* Expects a type on top of a character, both as uchars on stack[ 1 ], */
		/*  and a return closure on stack[ 0 ] as a libandria4_cts_closure{}. It */
		/*  pops everything it expects, returns the closure, and otherwise does */
		/*  nothing. Meant to be used with libandria4_parser_CSV_CSV1_ungetc(). */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_popchar( libandria4_cts_context *ctx, void *data_ );
	
	
	
	/* These two push two unsigned chars onto stack[ 1 ] (so the second stack); */
	/*  the top character is a tag (0-2: error, EOF, character), and expect a */
	/*  return closure on top of stack[ 0 ]. */
		/* Fetches a character outside of a string. 0 is error, 1 is token-EOF */
		/*  (the character will be un-gotten back to the source), 2 is plain */
		/*  success. */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_notstring
	(
		libandria4_cts_context*, void*
	);
		/* Fetches a character as a member of a string: this may consume */
		/*  MULTIPLE characters per result, or even consume a character for an */
		/*  "EOF" result (which happens as the end of a string). Same type */
		/*  values as *_getc_notstring(). */
		/* This hard-codes a CSV behavior, so it needs to be reworked. Work is */
		/*  needed on C-style escapes too, but only to extend the versions */
		/*  supported. */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string
	(
		libandria4_cts_context*, void*
	);
	
		/* Preemptively-retrospective note: the string gets allocated by */
		/*  *_accumulate_string(), not by it's caller. */
		/* Iteratively fetches a string. The opening double-quote should ALREADY */
		/*  BE CONSUMED. A void-pointer to the string will be on stack[1], with a */
		/*  bool (as an unsigned char) on top: the pointer will be invalid if the */
		/*  char is 0, else the string-pointer will be valid; the string itself */
		/*  will be a libandria4_char_pascalarray{}. */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_string
	(
		libandria4_cts_context*, void*
	);
		/* Note: contrary to previous notes, this actually IS used, specifically by */
		/*  way of *_accumulate_nonstring(). */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_btstring
	(
		libandria4_cts_context*, void*
	);
			/* Eventually delegates to either: */
					/* Fetches a character into a string: this consumes characters on a */
					/*  one-to-one basis. */
					/* Upon entry, there must be a "characters not yet read" value on */
					/*  stack[ 1 ] as a size_t, on top of a pascal-string as a */
					/*  void-pointer, where the size_t IS NOT larger than the size of */
					/*  the pascal-string. */
					/* Upon return, there will be a result flag on stack[ 1 ] as a */
					/*  uchar, on top of a "characters not yet read" as a size_t, on */
					/*  top of a pascal-string as a void-pointer. The result will */
					/*  either be 0 for success, or larger than one for a failure. */
				/* libandria4_parser_CSV_CSV1_accumulate_btstring(), */
			/*  or */
					/* As string, but not a string. Not allowed to contain whitespace, commas, */
					/*  or double-quotes. The storage-string gets allocated by this */
					/*  accumulator, just like the *string() version, including with the */
					/*  tag-uchar stored on top of it on stack[1]. */
				/* libandria4_parser_CSV_CSV1_accumulate_nonstring_inner(), */
			/*  depending on whether the "full" bit-torrent string header is */
			/*  detected. Thus, this MUST act like *_nonstring_inner() until */
			/*  either a colon (':') or a non-decimal character. */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_preaccumulate_btstring
	(
		libandria4_cts_context*, void*
	);
		/* As string, but not a string. Not allowed to contain whitespace, commas, */
		/*  or double-quotes. The storage-string gets allocated by this */
		/*  accumulator, just like the *string() version, including with the */
		/*  tag-uchar stored on top of it on stack[1]. Also handles the start of */
		/*  BitTorrent-style strings. */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_nonstring
	(
		libandria4_cts_context*, void*
	);
	
		/* Fetches the actual value. May use e.g. *_string(). */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_value
	(
		libandria4_cts_context*, void*
	);
	
		/* Fetches a full line (excepting that newlines inside strings don't */
		/*  count for defining lines...) of values. Returns a pointer to a list, */
		/*  with a bool (ala *_accumulate_string) on top of it: the list will */
		/*  contain libandria4_char_pascalarray* instances. */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_record
	(
		libandria4_cts_context*, void*
	);
	
	
	
		/* Calls the functions registered in it's data pointer, handing them one */
		/*  record (a "line" of data, as described above) in the form of a list of */
		/*  libandria4_char_pascalarray* instances at a time. To support this, the */
		/*  data pointer of the closure used to call this must point to an instance */
		/*  of libandria4_parser_CSV_CSV1_callargs{}. */
	libandria4_cts_closure libandria4_parser_CSV_CSV1_file
	(
		libandria4_cts_context*, void*
	);
	
		/* This initializes an instance of libandria4_parser_CSV_CSV1_callargs{}. */
		/*  Use it. */
	int libandria4_parser_CSV_CSV1_callargs_init
	(
		libandria4_parser_CSV_CSV1_callargs *dest,
			
			??? ???
	);
	
	struct libandria4_parser_CSV_CSV1_callargs
	{
		??? ;
	};
	
	
	
	
	
	
	
	
	
	
	/* The following is convenience code for those that want to build parse */
	/*  trees from the parse process. Use it or ignore it as you see fit. */
	
	typedef struct libandria4_parser_CSV_CSV1_listnode libandria4_parser_CSV_CSV1_listnode;
	#define LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE_GETLEFT( refnodeptr ) \
		( ( refnodeptr ) ? \
			( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) : \
			( ( name ## _bitup_buildNodeptr )( \
				*libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 0 ) ) ) )
	#define LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE_GETRIGHT( refnodeptr ) \
		( ( refnodeptr ) ? \
			( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) : \
			( ( name ## _bitup_buildNodeptr )( \
				*libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 1 ) ) ) )
	#define LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE_SETLEFT( refnodeptr, valptr ); \
		( ( refnodeptr ) ? \
			( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) : \
			( *libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 0 ) = (valptr), \
				( name ## _bitup ) ( name ## _bitup_buildNodeptr )( \
					*libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 0 ) ) ) )
	#define LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE_SETRIGHT( refnodeptr, valptr ); \
		( ( refnodeptr ) ? \
			( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) : \
			( *libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 1 ) = (valptr), \
				( name ## _bitup ) ( name ## _bitup_buildNodeptr )( \
					*libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 1 ) ) ) )
	
	LIBANDRIA4_LIST_BASICBUILDER_SINGLELINKED(
		libandria4_parser_CSV_CSV1_list,
		libandria4_parser_CSV_CSV1_listnode,
		LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE );
	
	LIBANDRIA4_MONAD_TRIETHER_BUILDTYPE_DEFINITION(
		libandria4_parser_CSV_CSV1_trival,
			libandria4_char_pascalarray*,
			libandria4_parser_CSV_CSV1_list*,
			libandria4_parser_CSV_CSV1_list* );
	
	struct libandria4_parser_CSV_CSV1_listnode
	{
		libandria4_parser_CSV_CSV1_trival here;
		libandria4_parser_CSV_CSV1_listnode *peers[ 2 ];
	};
	
	
	
	libandria4_parser_CSV_CSV1_listnode**
		libandria4_parser_CSV_CSV1_listnode_getneighbor( libandria4_parser_CSV_CSV1_listnode *ref, int getright );
	
	???
	
#endif
