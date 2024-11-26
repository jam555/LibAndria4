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
	
	
		/* For the continuation-trampoline-style engine & related definitions. */
	#include "../../basic/ctsengine.h"
		/* For libandria4_char_pascalarray{} and friends. */
	#include "../../basic/pascalstring.h"
	
	
	
	???
	
#endif
	
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

/* CSV1.c: A parser for simple comma-separated-value files. */
/* At the base level, values are separated by commas. */
	/* The values themselves may be wrapped by double-quotes. */
		/* If a comma or whitespace is part of the value, then the value */
		/*  should/must be so wrapped. */
		/* If a double-quote is to be part of a value, then the value MUST */
		/*  be double-quote wrapped, and the contained double-quotes must be */
		/*  encoded as DOUBLE souble-quotes. */


	/* For libandria4_common_monadicchar8{}. */
#include "../../commontypes.h"

typedef struct libandria4_parser_CSV_CSV1_file libandria4_parser_CSV_CSV1_file;
struct libandria4_parser_CSV_CSV1_file
{
	??? file;
	int cStr, csvStr;
};

	/* Returns a character, or an "error status" (EOF is positive, retry is */
	/*  0, error is negative). */
libandria4_common_monadicchar8 libandria4_parser_CSV_CSV1_getc( libandria4_parser_CSV_CSV1_file* );
	/* Negative on error, 0 on retry, positive on success. */
int libandria4_parser_CSV_CSV1_unget( libandria4_parser_CSV_CSV1_file*, char );





/* The following functions are compliant with (libandria4_cts_framefunc*). */

/* These two push two unsigned chars onto stack[ 1 ] (so the second stack); */
/*  the top character is a tag (0-2: error, EOF, character) */
	/* Fetches a character outside of a string. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_notstring
(
	libandria4_cts_context*, void*
);
	/* Fetches a character as a member of a string: this may consume */
	/*  MULTIPLE characters per result, or even consume a character for an */
	/*  "EOF" result (which happens as the end of a string). */
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string
(
	libandria4_cts_context*, void*
);

	/* Iteratively fetches a string. The opening double-quote should ALREADY */
	/*  BE CONSUMED. A void-pointer to the string will be on stack[1], with a */
	/*  bool (as an unsigned char) on top: the pointer will be invalid if the */
	/*  char is 0, else the string-pointer will be valid; the string itself */
	/*  will be a libandria4_char_pascalarray{}. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_accumulate_string
(
	libandria4_cts_context*, void*
);
	/* As string, but not a string. Not allowed to contain whitespace or  */
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


typedef struct libandria4_parser_CSV_CSV1_callargs libandria4_parser_CSV_CSV1_callargs;

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









""?;








	#define LIBANDRIA4_CTS_BUILDCLOSURE( funcptr, voidptr ) \
		( (libandria4_cts_closure){ (funcptr), (voidptr) } )
	#define LIBANDRIA4_CTS_RETURNCLOSURE( funcptr, voidptr ) \
		return( (libandria4_cts_closure){ (funcptr), (voidptr) } )
	
		/* The void pointer will be dereferenced and returned, so that it'll */
		/*  be the first thing to run when (if) you resume execution: you */
		/*  should generally use a static libandria_cts_closure{} pointer */
		/*  for it, but perhaps a nonstatic will work for you. As a GENERAL */
		/*  rule (it may be ok on some platforms), you should NOT give it a */
		/*  null pointer, as only the context gets checked. */
	libandria4_cts_closure libandria4_cts_framefunc_stoprun



LIBANDRIA4_CTS_RETURNCLOSURE(
	&libandria4_cts_framefunc_stoprun,
	(void*)0 )






/* WARNING,NOT VALID C! Replace all of the handleeither() constructs with */
/*  valid macros. */
static libandria4_cts_closure failfunc;


static libandria4_cts_closure failfunc =
	LIBANDRIA4_CTS_BUILDCLOSURE(
		&libandria4_cts_framefunc_stoprun,
		(void*)&failfunc );



libandria4_cts_closure libandria4_parser_CSV_CSV1_ungetc
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		unsigned char c, type;
		int e, res = 0;
		
		
		/* Get the values. */
		res = libandria4_cts_pop_uchar( ctx, 1,  &type );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_pop_uchar( ctx, 1,  &c );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Unget the character. */
		res = 0;
		while( res == 0 )
		{
			res = libandria4_parser_CSV_CSV1_unget( data, c );
		}
		if( res )
		{
			/* Success. Just fall-through. */
			
		} else {
			
			/* Failure. */
			return( failfunc );
		}
		c = 0;
		
		/* Push. */
		res = libandria4_cts_push2_uchar( ctx, 1,  c );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_uchar( ctx, 1,  type );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}



/* These two push two unsigned chars onto stack[ 1 ] (so the second stack); */
/*  the top character is a tag (0-2: error, EOF, character) */
	/* Fetches a character outside of a string. */
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_notstring
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		/* Analyze. */
		if( res == 1 )
		{
			/* Success. */
			type = 2;
			
		} else if( res == -1 )
		{
			if( e > 0 )
			{
				/* EOF. */
				type = 1;
				
			} else if( e == 0 )
			{
				/* Retry, so early exit + trigger repeat. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_notstring,
					data_ );
				
			} else {
				
				/* Error. */
				type = 0;
			}
			
		} else {
			
			/* This should never happen. */
			return( failfunc );
		}
		
		/* Push. */
		res = libandria4_cts_push2_uchar( ctx, 1,  c );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_uchar( ctx, 1,  type );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}

	/* An implementation function for libandria4_parser_CSV_CSV1_getc_string(). */
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_dquote
(
	libandria4_cts_context *ctx, void *data
);
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_cescape
(
	libandria4_cts_context *ctx, void *data
);
	/* Fetches a character as a member of a string: this may consume */
	/*  MULTIPLE characters per result, or even consume a character for an */
	/*  "EOF" result (which happens as the end of a string). */
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		/* Analyze. */
		if( res == 1 )
		{
			/* Success. */
			
			if( c == '\"' && data->csvStr )
			{
					/* Double-quote, so we need to dig a bit more, delegate. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_dquote,
					data_ );
				
			} else if( c == '\\' && data->cStr )
			{
					/* Backslash, so we need to dig a bit more, delegate. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_cescape,
					data_ );
				
			} else {
			
				/* Normal character, so normal behavior. */
				type = 2;
			}
			
		} else if( res == -1 )
		{
			if( e > 0 )
			{
				/* EOF. */
				type = 1;
				
			} else if( e == 0 )
			{
				/* Retry, so early exit + trigger repeat. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string,
					data_ );
				
			} else {
				
				/* Error. */
				type = 0;
			}
			
		} else {
			
			/* This should never happen. */
			return( failfunc );
		}
		
		/* Push. */
		res = libandria4_cts_push2_uchar( ctx, 1,  c );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_uchar( ctx, 1,  type );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_dquote
(
	libandria4_cts_context *ctx, void *data_
)
{
	if( ctx && data )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
			/* Setup a default "return via return stack" route. */
		libandria4_cts_innerreturn_data iret_d =
			{ 0, &libandria4_cts_innerreturn_returnstop, 0 };
		libandria4_cts_closure ret =
			LIBANDRIA4_CTS_BUILDCLOSURE(
				&libandria4_cts_innerreturn,
				(void*)&iret_d );
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		/* Analyze. */
		if( res == 1 )
		{
			/* Success. */
			
			if( c == '\"' )
			{
				/* Embedded double-quote. */
				type = 2;
				
			} else {
				
				/* Not a double-quote, so unget via delegation. */
				
					/* Override the default return route, with unget() as a detour. */
				ret =
					LIBANDRIA4_CTS_BUILDCLOSURE(
						&libandria4_parser_CSV_CSV1_ungetc,
						data_ );
				
				/* We treat this as an EOF. 'c' holds the value to unget, so no touching that. */
				type = 1;
			}
			
		} else if( res == -1 )
		{
			/* Error. */
			if( e > 0 )
			{
				/* EOF. */
				type = 1;
				
			} else if( e == 0 )
			{
				/* Retry, so early exit + trigger repeat. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_dquote,
					data_ );
				
			} else {
				
				/* Error. */
				type = 0;
			}
			
		} else {
			
			/* This should never happen. */
			return( failfunc );
		}
		
		/* Push. */
		res = libandria4_cts_push2_uchar( ctx, 1,  c );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_uchar( ctx, 1,  type );
		if( !res )
		{
			return( failfunc );
		}
		
			/* Just use the pre-set default return. */
		return( ret );
	}
	
	return( failfunc );
}
libandria4_cts_closure libandria4_parser_CSV_CSV1_getc_string_cescape
(
	libandria4_cts_context *ctx, void *data
)
{
	if( ctx && data )
	{
		libandria4_parser_CSV_CSV1_file *data =
			(libandria4_parser_CSV_CSV1_file*)data_;
		
		libandria4_common_monadicchar8 ec =
			libandria4_parser_CSV_CSV1_getc( data );
		unsigned char c, type;
		int e, res = 0;
		
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( ec,
			LIBANDRIA4_OP_SETaFLAGresAS1,
			LIBANDRIA4_OP_SETeFLAGresASn1 );
		
		/* Analyze. */
		if( res == 1 )
		{
			/* Success. */
			
			switch( c )
			{
				case 'a': /* Audible bell. */
					c = 0x07;
					type = 2;
					break;
				case 'b': /* Backspace. */
					c = 0x08;
					type = 2;
					break;
				case 'f': /* Formfeed. */
					c = 0x0c;
					type = 2;
					break;
				case 'n': /* New line. */
					c = 0x0a; /* Line feed. */
					type = 2;
					break;
				case 'r': /* Carriage return. */
					c = 0x0d;
					type = 2;
					break;
				case 't': /* horizontal Tab. */
					c = 0x09;
					type = 2;
					break;
				case 'v': /* Vertical tab. */
					c = 0x0;
					type = 2;
					break;
				case '\"':
				case '\'':
				case '\\':
				case '\?':
					/* Embed character. */
					type = 2;
					break;
				default:
					/* Not recognized, treat it as a "boring" literal. */
					
					/* Unhandled meaningfull characters: */
						/* A number starts an octal value to be embedded. */
						/* An 'x' starts a hexadecimal number. */
						/* A 'u' or 'U' starts a Unicode character. */
					/* These all should preferably be handled, but currently */
					/*  aren't: they honestly call for their own functions, */
					/*  and I don't want to implement that just yet. */
					
					type = 2;
					break;
			}
			
		} else if( res == -1 )
		{
			/* Error. */
			if( e > 0 )
			{
				/* EOF. */
				type = 1;
				
			} else if( e == 0 )
			{
				/* Retry, so early exit + trigger repeat. */
				LIBANDRIA4_CTS_RETURNCLOSURE(
					&libandria4_parser_CSV_CSV1_getc_string_cescape,
					data_ );
				
			} else {
				
				/* Error. */
				type = 0;
			}
			
		} else {
			
			/* This should never happen. */
			return( failfunc );
		}
		
		/* Push. */
		res = libandria4_cts_push2_uchar( ctx, 1,  c );
		if( !res )
		{
			return( failfunc );
		}
		res = libandria4_cts_push2_uchar( ctx, 1,  type );
		if( !res )
		{
			return( failfunc );
		}
		
		/* Get the return value. */
		libandria4_cts_closure ret;
		res = libandria4_cts_pop_ctsclsr( ctx, 0,  &ret );
		if( !res )
		{
			return( failfunc );
		}
		return( ret );
	}
	
	return( failfunc );
}














	/* Our closure construct. THe void* is just whatever arbitrary data, and */
	/*  we CAN'T guess in the engine system as to how to deal with it, it */
	/*  MUST be understood by the closure by itself. Sooo... it's never set */
	/*  by the engine itself, JUST by whatever actually builds the closure. */
	/* Note: if you WANT to extend the closure, THEN DON'T, just use the */
	/*  void pointer instead. The closures get moved around BY VALUE, within */
	/*  the engine, which again CAN'T know about whatever random extensions */
	/*  you try to apply to them, so just DON'T. */
	typedef struct libandria4_cts_closure libandria4_cts_closure;
	typedef
		libandria4_cts_closure (*libandria4_cts_framefunc)
		(
			libandria4_cts_context*, void*
		);
	struct libandria4_cts_closure
	{
		libandria4_cts_framefunc handler;
		void *data;
	};
	
	
	/* The info required to directly run the engine. */
	struct libandria4_cts_context
	{
			/* Usually ->body[ 0 ] should be a return/C stack. A FORTH data */
			/*  stack should be ->body[ 1 ]. */
		libandria4_charparrptr_pascalarray *stacks;
		libandria4_sizet_pascalarray *align, *used, *alignreq;
		libandria4_bitarray *reallocatable;
		
		libandria4_cts_closure next_iteration;
			/* The number of iterations to run through: negative means */
			/*  "infinite". */
		int run;
		
		/* TODO: add an output stream here, to route error messages. */
	};
	int libandria4_cts_isvalid( libandria4_cts_context *ctx );
	int libandria4_cts_isvalid2( libandria4_cts_context *ctx );
	
		/* Performs the actual trampolining. */
	int libandria4_cts_engine( libandria4_cts_context *ctx );
	
	
	#define LIBANDRIA4_CTS_BUILDCLOSURE( funcptr, voidptr ) \
		( (libandria4_cts_closure){ (funcptr), (voidptr) } )
	#define LIBANDRIA4_CTS_RETURNCLOSURE( funcptr, voidptr ) \
		return( (libandria4_cts_closure){ (funcptr), (voidptr) } )
	
		/* The void pointer will be dereferenced and returned, so that it'll */
		/*  be the first thing to run when (if) you resume execution: you */
		/*  should generally use a static libandria_cts_closure{} pointer */
		/*  for it, but perhaps a nonstatic will work for you. As a GENERAL */
		/*  rule (it may be ok on some platforms), you should NOT give it a */
		/*  null pointer, as only the context gets checked. */
	libandria4_cts_closure libandria4_cts_framefunc_stoprun
	(
		libandria4_cts_context*, void*
	);
	/* More closure functions are near the end of this header. */
	
	extern libandria4_commonio_handle libandria4_cts_errout;
	
	
	
	int libandria4_cts_sizedpop( libandria4_cts_context *ctx, size_t stack,  void *dest_, size_t size );
	int libandria4_cts_sizedpush( libandria4_cts_context *ctx, size_t stack,  void *dest_, size_t size );
	
	
	#define LIBANDRIA4_CTS_DECPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val );
	#define LIBANDRIA4_CTS_DEFPOP( prefix, postfix, type ) \
		int prefix ## pop ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val ) { \
			if( !val ) { return( -1 ); } \
			return( libandria4_cts_sizedpop( ctx, stack,  (void*)val, sizeof( type ) ) ); }
	
	#define LIBANDRIA4_CTS_DECPUSH( prefix, postfix, type ) \
		int prefix ## push ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val );
	#define LIBANDRIA4_CTS_DEFPUSH( prefix, postfix, type ) \
		int prefix ## push ## postfix ( libandria4_cts_context *ctx, size_t stack,  (type) *val ) { \
			if( !val ) { return( -1 ); } \
			return( libandria4_cts_sizedpush( ctx, stack,  (void*)val, sizeof( type ) ) ); }
	
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _schar, signed char );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _uchar, unsigned char );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _sshort, signed short );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ushort, unsigned short );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _sint, signed int );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _uint, unsigned int );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _slong, signed long );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ulong, unsigned long );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _float, float );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _double, double );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _sizet, size_t );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ptrdifft, ptrdiff_t );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _voidp, void* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _scharp, signed char* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ucharp, unsigned char* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _voidf, void (*)() );
	
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
	LIBANDRIA4_CTS_DECPOP( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );
	
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _schar, signed char );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _uchar, unsigned char );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _sshort, signed short );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ushort, unsigned short );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _sint, signed int );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _uint, unsigned int );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _slong, signed long );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ulong, unsigned long );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _float, float );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _double, double );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _sizet, size_t );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ptrdifft, ptrdiff_t );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _voidp, void* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _scharp, signed char* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ucharp, unsigned char* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _voidf, void (*)() );
	
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
	LIBANDRIA4_CTS_DECPUSH( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );

