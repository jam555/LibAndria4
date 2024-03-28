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
	#include "../../basic/pascalarray.h"
	#include "../../text/charsettranslators.h"
	
	
	
	/* Just a bunch of pre-defs. */
	
	typedef struct vt100net_errorstruct vt100net_errorstruct;
	typedef struct vt100net_errorstruct_simple vt100net_errorstruct_simple;
	
	typedef struct vt100net_termcontext_IOhook vt100net_termcontext_IOhook;
	
	typedef struct vt100net_termcontext_chartype_hooks vt100net_termcontext_chartype_hooks;
	
	typedef struct vt100net_handler_mapping vt100net_handler_mapping;
	typedef struct vt100net_termcontext vt100net_termcontext;
	
		/* Defines vt100net_uint8_pascalarray{} and */
		/*  vt100net_uint8arr_pascalarray{}. */
		/* Convert these into a full bit vector & bit surface implementation. */
	LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( vt100net_uint8_, uint8_t );
	LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( vt100net_uint8arr_, vt100net_uint8_pascalarray* );
	
	
	
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
	/*  vital (and probably need a little expansion) for e.g. Unicode */
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
			/* Input translates characters that will be stored into */
			/*  vt100net_termcontext->acc_char. Output translates */
			/*  characters being sent from the vt100net_termcontext{} */
			/*  towards the source of the characters that are given to */
			/*  input. The 1/2 difference is SI vs SO. */
			/* TODO: We need to actually use these. Just move over to */
			/*  the terminal using Unicode internally by definition */
			/*  afterwards? */
		libandria4_text_charsettranslators_fptr output1, output2;
		libandria4_text_charsettranslators_fptr input1, input2;
		
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
		
	} vt100net_handler_mapping;
		/* If the new state is *_INVALID, then don't change the state; */
		/*  otherwise change the current state to match the provided */
		/*  new state. */
	int (*vt100net_action_handler)( vt100net_termcontext* /*term_ctx*/, uint8_t /*new_state*/ );
	
	typedef enum
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
		
	} vt100net_termcontext_flags1;
	typedef enum
	{
			/* Not real flags, just markers. */
		vt100net_termcontext_flags2_INVALID = -1,
		vt100net_termcontext_flags2_NULL = 0,
		
			/* Allow the terminal emulator instance that the *_termcontext{} */
			/*  is embedded in, to (at least theoretically) send */
			/*  communications back to whatever other software is the source */
			/*  of the character stream that this *_termcontext{} is parsing. */
		vt100net_termcontext_flags2_allowbacktalk = 1,
			/* In order to respond, "back talk" must be allowed. If backtalk */
			/*  isn't enabled, then just leave this set as a marker until */
			/*  either backtalk IS allowed, or the software just exits or */
			/*  something. */
			/* Clear this when and ONLY when the enclosing terminal emulator */
			/*  actually sends a response. */
		vt100net_termcontext_flags2_responseneeded = 2,
			/* Like "response needed", but only toggled by this */
			/*  *_termcontext{}, not by the enclosing terminal emulator */
			/*  instance (except when first creating the *_termcontext{}). */
		vt100net_termcontext_flags2_responsepersistent = 4,
		
			/* Not a real flag, just another marker. */
		vt100net_termcontext_flags2_LAST
		
	} vt100net_termcontext_flags2;
	typedef enum
	{
			/* Not real flags, just markers. */
		vt100net_termcontext_flags3_INVALID = -1,
		vt100net_termcontext_flags3_NULL = 0,
		
			/* The SPD system affects cursor progression, and was originally */
			/*  intended for languages like Hebrew, or traditionally written */
			/*  Japanese, that DO NOT follow the same left-to-right */
			/*  progression as English. Some people don't think they've ever */
			/*  been used, but I see no particular reason not to... WITHIN */
			/*  SOME BOUNDS. */
		vt100net_termcontext_flags3_SPDbase = 1,
		vt100net_termcontext_flags3_SPDmask = 3,
			/* The actual values. Note that the values still need to be */
			/*  verified. */
		vt100net_termcontext_flags3_SPDrightward = 0,
		vt100net_termcontext_flags3_SPDdownward = 1,
		vt100net_termcontext_flags3_SPDleftward = 2,
		vt100net_termcontext_flags3_SPDupward = 3,
		
		/* TODO: */
		/* The ECMA JFY and Fraktur (SGR 20) flags/equivalents should be */
		/*  looked at to see if they can reasonably be done. */
		/* VT-52 compat & double high/wide text are rarely implemented. */
		/* Color extensions are normally supported, but at most an "allow" */
		/*  flag belongs here, as color is a per-character thing. */
		/* Common cursor display: <ESC>"[?25h" */
		/*  And hide it: <ESC>"[?25l" */
		/* Cannonical mode doesn't send characters until the user hits */
		/*  enter, raw mode sends characters as they're sent. The */
		/*  differentiation doesn't really belong here (this is meant */
		/*  to handle things coming TO the terminal, not sent FROM the */
		/*  terminal), but cannonical mode IS the correct default, and */
		/*  mentioning it here is appropriate (especially since the */
		/*  sending code hasn't been started on yet, and the controlling */
		/*  code would be in this receiving code). */
		/* Echo vs non-echo mode is in almost the same camp as cannonical */
		/*  mode. */
		/* Cursors: */
			/* Block: */
				/* blinking: <ESC>"[0"<SPACE>"q" or <ESC>"[1"<SPACE>"q" */
				/* steady: <ESC>"[2"<SPACE>"q" */
			/* Underline: */
				/* blinking: <ESC>"[3"<SPACE>"q" */
				/* steady: <ESC>"[4"<SPACE>"q" */
			/* I-beam: */
				/* blinking: <ESC>"[5"<SPACE>"q" */
				/* steady: <ESC>"[6"<SPACE>"q" */
			
		
			/* Not a real flag, just another marker. */
		vt100net_termcontext_flags3_LAST
		
	} vt100net_termcontext_flags3;
	typedef enum
	{
			/* Not real flags, just markers. */
		vt100net_termcontext_vt100flags_INVALID = -1,
		vt100net_termcontext_vt100flags_NULL = 0,
		
			/* If clear, origin is upper-left of all characters, and cursor may be */
			/*  placed outside the margins. If set, origin is upper-left position */
			/*  within the margins, and cursor CANNOT be placed outside the margins. */
		vt100net_termcontext_vt100flags_originmode = 1,
			/* These two are tracked, but characteristically will be NO-OPs. */
		vt100net_termcontext_vt100flags_smoothscrollmode = 2, /* DECSCLM */
		vt100net_termcontext_vt100flags_interlacemode = 4, /* DECINLM */
			/* Swaps the foreground & background colors for the entire terminal */
			/*  screen. This can only be implemented by the rendering code, which */
			/*  isn't currently being worked on. */
		vt100net_termcontext_vt100flags_screeninversionmode = 8, /* DECSCNM */
			/* Allows writes to the right margin to move the cursor to the first */
			/*  character of the next line for the next write. */
		vt100net_termcontext_vt100flags_autowrapmode = 16, /* DECAWM */
		
			/* Not a real flag, just another marker. */
		vt100net_termcontext_vt100flags_LAST
		
	} vt100net_termcontext_vt100flags;
	typedef struct vt100net_termcontext_point
	{
		uint32_t x, y;
		
	} vt100net_termcontext_point;
	struct vt100net_termcontext
	{
			/* Initialized by vt100net_termcontext_INITIAL_ENTRY. Looping */
			/*  will continue for as long as run is different than 0. */
		int run;
		
		vt100net_termcontext_flags1 flags1;
		vt100net_termcontext_flags2 owner_flags;
		vt100net_termcontext_flags3 flags3;
		vt100net_termcontext_vt100flags vt100_flags;
		
		
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
		size_t interm_count, param_count;
		
		
			/* The current state of the buffer. */
			/* Note that many terminals have an "alternate" buffer that's */
			/*  used for Text UI apps. It's activated with <ESC>"[?1049h", */
			/*  and sometimes (but buggily) with <ESC>"47h". To reverse */
			/*  this, use <ESC>"[?1049l". After activation and before */
			/*  deactivation, <ESC>"[2J" (to clear both screen and scrollback) */
			/*  should be issued. */
		libandria4_termbuffer_generic *buffer;
			/* Currently gets used as a fill character. */
		libandria4_buffercell_common buffer_flags;
			/* To set the cursor position, use ‹ESC›"[(r);(c)H", where (r) */
			/*  is the row as an index (NOT an offset!), and {c} is the */
			/*  column (also an index). */
			/* Note that dimensions.x was previously .width, and .y was .height. */
		vt100net_termcontext_point cursor, dimensions;
		struct
		{
				/* Scrolling ONLY happens at and between these lines. Remember, */
				/*  "1" indexing instead of "0" offsetting. */
				/* Lines moved outside of the scrolling region are simply lost, */
				/*  their contents are NOT backed up anywhere. Top and bottom */
				/*  must always be different values, thereby ensuring AT LEAST */
				/*  two scrolling lines. Characters that are genuinely ADDED */
				/*  OUTSIDE the scrolling region don't cause scrolling: this is */
				/*  useful for e.g. updating status bars. */
				/*
					To put the cursor outside the scrolling region:
						make certain that DECOM is on "reset", and use cursor
						position (CUP) or horizontal and vertical position (HVP)
					To scroll:
						Use "Index", "Reverse Index",  "Next Line", OR:
							set "Autowrap Mode", position the cursor on the
							lower-right margin, and send a displayable character-
							the scroll will be triggered, and the character placed
							in the first available column on that line.
				*/
				/* By default, the scrolling region is the whole screen. You */
				/*  have to set it if you want something else. */
				/* We eventually will want flags that indicate if these */
				/*  individually are absolute positions, or relative. */ 
			uint32_t top, bottom;
			
		} scrolling_region;
			/* A bit mask of horizontal tab stops. ->surf.len must be => */
			/*  line count, ->surf.body is an array of ->surf.len size */
			/*  and type vt100net_uint8_pascalarray*. Both ->width and */
			/*  all ->surf.body[]->len * 8 values must be => column count. */
			/*  Each character position in vt100net_termcontext.buffer */
			/*  corresponds to the bit at: */
				/* htabstops->surf.body[ line ]-> */
				/*  body[ ( column - ( column % 8 ) ) / 8 ] & */
				/*  ( 1 << ( column % 8 ) ) */
			/*  If the bit is set, then that position is a horizontal tab */
			/*  stop, otherwise it isn't. */
			/* For convenience, use these two functions for access: */
				/* int libandria4_bitsurface_read( surface*, x, y ) */
				/* int libandria4_bitsurface_write( surface*, x, y, value ) */
		libandria4_bitsurface *htabstops;
			/* A bit set of per-line double-width and double-height flags. */
			/*  For double-width flag line*4, for double-height flags */
			/*  (line*4)+1 and (line*4)+2. */
		libandria4_bitarray *charasizes;
		
		
			/* These are the various pieces of data saved by the VT100 */
			/*  terminal DECSC control sequence. The character set, cursor */
			/*  position, and graphic rendition (color, font, etc.) need */
			/*  to be saved. */
		struct
		{
				/* Mostly important for the .input and .output members, but */
				/*  the tests are worth remembering too. */
			vt100net_termcontext_chartype_hooks charhooks;
			
				/* Cursor position. */
			vt100net_termcontext_point cursor;
				/* Graphic rendition. Only .r, .g,.b, and .style are fully */
				/*  used, .chara is only used in the bits set in */
				/*  libandria4_buffercell_common_chara_CHARSET_mask. */
			libandria4_buffercell_common graphrend;
			
		} vt100_curssaves;
		
		
		
		/* The members below should always stay near the bottom, and never */
		/*  be accessed directly, in case of future resizing. */
		
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
