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

#ifndef LIBANDRIA4_PARSERS_VT100NET_TERMINAL_H
# define LIBANDRIA4_PARSERS_VT100NET_TERMINAL_H
	
	
	#include "../../basic/commonerr.h"
	#include "../../text/stdbuffer.h"
	
	
	
	/* Just a bunch of pre-defs. */
	
	typedef struct vt100net_errorstruct vt100net_errorstruct;
	typedef struct vt100net_errorstruct_simple vt100net_errorstruct_simple;
	
	typedef struct vt100net_termcontext_IOhook;
	
	typedef struct vt100net_termcontext_chartype_hooks vt100net_termcontext_chartype_hooks;
	
	typedef struct vt100net_handler_mapping vt100net_handler_mapping;
	typedef struct vt100net_termcontext vt100net_termcontext;
	
	
	
	/* The system for I/O functions. */
	
	typedef int (vt100net_termcontext_IOfuncptr*)( vt100net_termcontext_IOhook*, void* /* The I/O data */ );
		/* These may be copied in the future, so DO NOT rely on the same */
		/*  pointer always being passed around, instead just set */
		/*  data.whichever to the value or pointer you need, and adapt your */
		/*  code accordingly. The function takes the full hook context */
		/*  instead of just a void pointer in case you want to use it for */
		/*  implementing your own state-machine behaviors: beware that */
		/*  ->func is a pointer TO a function pointer, NOT the function */
		/*  pointer itself, and must be treated accordingly. */
		/* Also, beware that input and output ARE NOT diferentiated by */
		/*  type, but instead by variable, and you must therefore exert */
		/*  more caution: */
			/* Input functions are expected to store a uint8_t by value */
			/*  into the target of the second argument, but the target */
			/*  itself is a uint32_t. These functions are used as a more */
			/*  generic equivalent to getc(), and should never provide */
			/*  more than one char-equivalent. */
			/* Output functions are expected to receive a volume of data */
			/*  sized according to THE vt100net_looper() VERSION THAT WAS */
			/*  INITIALLY CALLED, which WILL complicate calling code, but */
			/*  the data itself will be provided in form of a uint32_t */
			/*  regardless of the value's actual size. These functions are */
			/*  used as the equivalent of putc(), but the provided */
			/*  character is always the encoding's equivalent of full */
			/*  UTF-32 instead of some "minimum sized" piece like a byte */
			/*  from a UTF-8 stream. */
			/* Error receiver functions are given a pointer to a uint32_t */
			/*  inside of some arbitrary error structure: the value of */
			/*  the uint32_t identifies the structure type. These */
			/*  functions are used to report errors inside the vt100 parser */
			/*  system to the enclosing system. */
			/* Error decoders are provided with a pointer to a pointer to */
			/*  a uint32_t that contains the abs() of the triggering */
			/*  error, and is expected to redirect that pointer to a */
			/*  string that describes the error in a format (e.g. ASCII, */
			/*  UTF-8, EBCDIC, etc.) appropriate to whatever stderr's */
			/*  current configuration requires. These functions are used */
			/*  so the vt100 parser can provide meaningfull error messages. */
	struct vt100net_termcontext_IOhook
	{
		union
		{
			void *vdat;
			uintptr_t idat;
			
		} data;
		vt100net_termcontext_IOfuncptr *func;
	};
	
	
	
	/* A character-type testing system. Currently unused, but will be */
	/*  vital (and probably need a little expansion) for e.g. Uincode */
	/*  support. */
	
	#define vt100net_termcontext_chartype_INVALIDLEN ( -1 )
		#define vt100net_termcontext_chartype_CONTROL ( 0 )
		#define vt100net_termcontext_chartype_SPACE ( 1 )
		#define vt100net_termcontext_chartype_BLANK ( 2 )
		#define vt100net_termcontext_chartype_PRINT ( 3 )
		#define vt100net_termcontext_chartype_GRAPH ( 4 )
		#define vt100net_termcontext_chartype_PUNCT ( 5 )
		#define vt100net_termcontext_chartype_ALNUM ( 6 )
		#define vt100net_termcontext_chartype_ALPHA ( 7 )
		#define vt100net_termcontext_chartype_UPPER ( 8 )
		#define vt100net_termcontext_chartype_LOWER ( 9 )
		#define vt100net_termcontext_chartype_CASELESS ( 10 )
		#define vt100net_termcontext_chartype_BDIGIT ( 11 )
		#define vt100net_termcontext_chartype_DIGIT ( 12 )
		#define vt100net_termcontext_chartype_ODIGIT ( 13 )
		#define vt100net_termcontext_chartype_XDIGIT ( 14 )
	#define vt100net_termcontext_chartype_MAXLEN ( 15 )
	
		/* Return negative on error, 0 on "test failed", positive on "test succeeded". */
	typedef int (vt100net_termcontext_chartype_funcptr*)( vt100net_termcontext_chartype_hooks*, uint32_t /* The character. */ );
	struct vt100net_termcontext_chartype_hooks
	{
		union
		{
			void *vdat;
			uintptr_t idat;
			
		} data;
			/* Must point to the first member of an array of function */
			/*  pointers, don't fiddle with this stuff. */
		vt100net_termcontext_chartype_funcptr *tests;
			/* 1 + the number of the highest-numbered test provided. */
		uint8_t test_count;
	};
	intmax_t vt100net_termcontext_chartype_hook_validate( vt100net_termcontext_chartype_hooks* );
	
	
	
	/* The actual terminal parsing system. */
	
			/* Note that when this is designated as a "new state", it */
			/*  actually means to leave the state unchanged. It's only */
			/*  actually invalid when it's STORED as the current state. */
	#define vt100net_termcontext_INVALID				( 0 )
	#define vt100net_termcontext_INITIAL_ENTRY			( 1 )
	#define vt100net_termcontext_FETCHCHAR				( 2 )
	#define vt100net_termcontext_GROUND_POSTREAD		( 3 )
		/* These are normal execution stages. The first starts at 64 in */
		/*  case there's a need for more "support" hooks, so that */
		/*  renumbering is less likely to be needed in the future. */
	#define vt100net_termcontext_GROUND					( 64 )
	#define vt100net_termcontext_ESCAPE					( 65 )
	#define vt100net_termcontext_ESCAPE_INTERMEDIATE	( 66 )
	#define vt100net_termcontext_CSI_ENTRY				( 67 )
	#define vt100net_termcontext_CSI_PARAM				( 68 )
	#define vt100net_termcontext_CSI_INTERMEDIATE		( 69 )
	#define vt100net_termcontext_CSI_IGNORE				( 70 )
	#define vt100net_termcontext_DCS_ENTRY				( 71 )
	#define vt100net_termcontext_DCS_PARAM				( 72 )
	#define vt100net_termcontext_DCS_INTERMEDIATE		( 73 )
	#define vt100net_termcontext_DCS_PASSTHROUGH		( 74 )
	#define vt100net_termcontext_DCS_IGNORE				( 75 )
	#define vt100net_termcontext_OSC_STRING				( 76 )
	#define vt100net_termcontext_SOS_PMAC_APC__STRING	( 77 )
	#define vt100net_termcontext_STATES__PAST_END \
		( vt100net_termcontext_SOS_PMAC_APC__STRING + 1 )
	
	typedef struct vt100net_handler_mapping
	{
			/* Indexes into vt100net_handlers[]. */
		uint8_t handler_index;
		uint8_t nstate;
		
	};
		/* If the new state is *_INVALID, then don't change the state; */
		/*  otherwise change the current state to match the provided */
		/*  new state. */
	int (*vt100net_action_handler)( vt100net_termcontext* /*term_ctx*/, uint8_t /*new_state*/ );
	
	typedef enum vt100net_termcontext_flags1
	{
			/* Not real flags, just markers. */
		vt100net_termcontext_flags1_INVALID = -1,
		vt100net_termcontext_flags1_NULL = 0,
		
			/* The VT100 was 7 bit, so mask out the high bit if this isn't enabled. */
		vt100net_termcontext_flags1_8bit = 1,
			/* "loose" should also enable "strict", even if strict isn't marked. */
		vt100net_termcontext_flags1_UTF8loose = 2,
		vt100net_termcontext_flags1_UTF8strict = 4,
			/* Enable non-VT320 behavior for CAN and SUB ascii bytes. */
		vt100net_termcontext_flags1_CANSUB_cancelseq = 8,
			/* Disable VT500+ behavior in regards to ascii NUL. */
		vt100net_termcontext_flags1_retainnull = 16,
			/* ZDM treats blank & 0 params identically: it ended with ECMA-48 edition 5. */
		vt100net_termcontext_flags1_ZDMenable = 32,
			/* These are graphics capabilities. */
		vt100net_termcontext_flags1_sixel = ??? ,
		
			/* Not a real flag, just another marker. */
		vt100net_termcontext_flags1_LAST
	};
	struct vt100net_termcontext
	{
			/* Initialized by vt100net_termcontext_INITIAL_ENTRY. Looping */
			/*  will continue for as long as run is different than 0. */
		int run;
		
		vt100net_termcontext_flags1 flags1;
		
		
			/* The call stack, we don't need too much space. */
		uint8_t dispatch, *callstack;
		
			/* Newly fetched characters go here. */
		uint32_t acc_char;
		
			/* Input functions are expected to store a uint8_t by value */
			/*  into the target of the second argument, but the target */
			/*  itself is a uint32_t. These functions are used as a more */
			/*  generic equivalent to getc(), and should never provide */
			/*  more than one char-equivalent. */
			/* Output functions are expected to receive a volume of data */
			/*  sized according to THE vt100net_looper() VERSION THAT WAS */
			/*  INITIALLY CALLED, which WILL complicate calling code, but */
			/*  the data itself will be provided in form of a uint32_t */
			/*  regardless of the value's actual size. These functions are */
			/*  used as the equivalent of putc(), but the provided */
			/*  character is always the encoding's equivalent of full */
			/*  UTF-32 instead of some "minimum sized" piece like a byte */
			/*  from a UTF-8 stream. */
			/* Error receiver functions are given a pointer to a uint32_t */
			/*  inside of some arbitrary error structure: the value of */
			/*  the uint32_t identifies the structure type. These */
			/*  functions are used to report errors inside the vt100 parser */
			/*  system to the enclosing system. */
			/* Error decoders are provided with a pointer to a pointer to */
			/*  a uint32_t that contains the abs() of the triggering */
			/*  error, and is expected to redirect that pointer to a */
			/*  string that describes the error in a format (e.g. ASCII, */
			/*  UTF-8, EBCDIC, etc.) appropriate to whatever stderr's */
			/*  current configuration requires. These functions are used */
			/*  so the vt100 parser can provide meaningfull error messages. */
		vt100net_termcontext_IOhook errrec, errdec, in, out;
		libandria4_commonio_handle *errrep;
		vt100net_termcontext_chartype_hooks type_tests;
		
		intmax_t res;
			/* Used for when the parser "breaks" to hold the values of */
			/*  __FILE__ and __LINE__ at that error report. */
		struct
		{
			
			intptr_t file, line;
			
		} error_values;
		
		
			/* If a high bit of a param is set, then the param or other is */
			/*  blank. This is the default state. */
		struct
		{
			uint32_t private_marker;
			uint32_t *intermediates;
			uint32_t final_character;
			
		} sequence_dispatch;
		uint16_t *params;
		
		
			/* The current state of the buffer. */
		vt100net_termbuffer_generic *buffer;
		
		
		
		/* The members below should always stay near the bottom, and never be accessed directly, in case of future resizing. */
		
			/* Use callstack[]. */
		uint8_t dispatchstack[ 1 ];
			/* Use sequence_dispatch.intermediates[]. */
		uint32_t intermediate_characters[ 3 ];
			/* Access via params[]. */
		uint16_t parameter_values[ 16 ];
	};
	#define vt100net_termcontext_DISPSTACK_LEN ( 1 )
	#define vt100net_termcontext_INTERMS_LEN ( 3 )
	#define vt100net_termcontext_PARAMS_LEN ( 16 )

	/* Utility macros. */
	#define vt100net_termcontext_dispatch_PUSH( ctx, var ) \
			{ uint8_t vt100net_termcontext_dispatch_PUSH_tmp = ( ctx )->callstack[ 0 ]; \
				( ctx )->callstack[ 0 ] = ( ctx )->dispatch; \
				( ctx )->dispatch = ( var ); \
				( var ) = vt100net_termcontext_dispatch_PUSH_tmp; }
	#define vt100net_termcontext_dispatch_POP( ctx, rec ) \
			{ ( rec ) = ( ctx )->dispatch; \
				( ctx )->dispatch = ( ctx )->callstack[ 0 ]; \
				( ctx )->callstack[ 0 ] = vt100net_termcontext_INVALID; }
	
	int vt100net_termcontext_IOhook_validate( vt100net_termcontext* );
	
		/* This is the main function of the parser. */
	int vt100net_looper( vt100net_termcontext *term_ctx );
	
#endif
/* End libandria4 parsers vt100net terminal.h */
