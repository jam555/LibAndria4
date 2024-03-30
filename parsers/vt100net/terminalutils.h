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

#ifndef LIBANDRIA4_PARSERS_VT100NET_TERMINALUTILS_H
# define LIBANDRIA4_PARSERS_VT100NET_TERMINALUTILS_H
	
	/* TODO: */
		/* We need an init() and deinit() function. */
			/* Need a reset function for vt100net_actionstool_execute() to call. */
		/* We should probably move some of these structures into a different */
		/*  file. */
		/* Need some output capacity to finish up the vt100 support. */
		/* Check whether anything else needs to be copied from terminal.h */
	
	/* This is a reorganization of terminal.h, to make the file cleaner. */
	
	
		/* This is vitally important, it's where stuff gets written to */
		/*  represent the screen contents. */
	#include "../../text/stdbuffer.h"
		/* This is required for bit surfaces, which get used to mark HTab */
		/*  locations, and bit arrays, which get used to mark lines for */
		/*  double-wide/double-high characters. */
	#include "../../basic/bitarray.h"
		/* Needed for libandria4_text_charsettranslators_fptr in */
		/*  vt100net_termcontext_chartype_hooks{}. */
	#include "../../text/charsettranslators.h"
	
	
	typedef struct vt100net_termcontext vt100net_termcontext;
	typedef struct vt100net_termcontext_chartype_hooks vt100net_termcontext_chartype_hooks;
	
	
	
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
	
	
	
	typedef struct vt100net_innererrs
	{
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
		
	} vt100net_innererrs;
	
		/* This enum represents the bit masks for vt100 modes. */
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
			/* Send your error reports here by default. The values formerly */
			/*  were clogging up *_termcontext{}. */
		vt100net_innererrs errroute;
		
		
			/* Initialized by vt100net_termcontext_INITIAL_ENTRY. Looping */
			/*  will continue for as long as run is different than 0. */
		int run;
		
			/* The call stack, we don't need too much space. */
		uint8_t dispatch, *callstack;
		
		
		/*******************************************************************/
		/*******************************************************************/
		/** The "real" terminal stuff starts below here. Everything above **/
		/**  is "merely" behind-the-scenes implementation stuff. ***********/
		/*******************************************************************/
		/*******************************************************************/
		
		
		vt100net_termcontext_flags1 flags1;
		vt100net_termcontext_flags2 owner_flags;
		vt100net_termcontext_flags3 flags3;
		vt100net_termcontext_vt100flags vt100_flags;
		
		
		/* General I/O stuff. */
		
			/* These are used by the input code to translate text into the */
			/*  form that belongs in acc_char. Note that translation CAN */
			/*  fail. */
		vt100net_termcontext_chartype_hooks translations;
			/* Newly fetched characters go here. */
		uint32_t acc_char;
		
		
		/* Arguments parsed from the inputs... or at least that you want */
		/*  utility code to THINK was parsed. */
		
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
		
		
		/* The display buffer. This represents the screen, but the screen */
		/*  itself must be implemented by SOMETHING ELSE that just uses this */
		/*  system. */
		
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
		
		
		/* "Saved data". More stuff should be supported, but we need the */
		/*  commands to support that too, so it's left as an excercise for */
		/*  the future. */
		
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
	
		/* Adjusts the provided "dir" to consider term_ctx->flags3 */
		/*  & vt100net_termcontext_flags3_SPDmask. */
		/* "dir" must be one of the cardinal directions, else *_invalid */
		/*  will be returned. */
	libandria4_termbuffer_directions vt100net_actionstool_calcdir
	(
		vt100net_termcontext *term_ctx,
		libandria4_termbuffer_directions dir
	);
	
	int vt100net_actionstool_scroll
	(
		vt100net_termcontext *term_ctx,
		libandria4_termbuffer_directions dir,
		int force
	);
		/* Implicit movement: */
			/* If the cursor's target isn't the last chara of it's line, move to the next chara. */
			/*  There is no standards-defined else. */
			/* Happens every time a graphical representation is applied. */
		/* Explicit movement: */
			/* Move the cursor target to the designated chara. */
			/* What to do if the designated location doesn't exist isn't standards-defined. */
	int vt100net_actionstool_itercursor
	(
		vt100net_termcontext *term_ctx,
		libandria4_termbuffer_directions dir,
		int force
	);
	
	int vt100net_actionstool_clearcharas
	(
		vt100net_termcontext *term_ctx,
		uint32_t line, uint32_t column1, uint32_t column2,
		uint32_t blankval
	);
		/* Note that this will also progress the cursor after writing the character, */
		/*  with the singular exception that it won't proceed past the right margin */
		/*  unless vt100net_termcontext_vt100flags_autowrapmode is set in */
		/*  (vt100net_termcontext*)->vt100_flags. */
		/* The character is written to the CURSOR POSITION AS OF THE TIME THIS */
		/*  FUNCTION IS CALLED, combined with term_ctx->buffer_flags such that the */
		/*  chara comes from newval and everything else comes from buffer_flags. */
	int vt100net_actionstool_writechara
	(
		vt100net_termcontext *term_ctx,
		uint32_t newval
	);
	
		/* Note that per VT510 SGR documentation, all of these traits move */
		/*  with the characters. As should be normally desired. */
		/* Does something about translating the values stored in e.g. ->params */
		/*  into values for e.g. ->buffer_flags. */
	int vt100net_actionstool_SGR
	(
		vt100net_termcontext *term_ctx,
		uint16_t *params, size_t param_count
	);
	
	/* Convenience wrappers. None of them are done, but the */
	/*  name tells you approximately what they do. Direction */
	/*  can be affected by SPD. These all wrap *_itercursor(), */
	/*  but use vt100net_actionstool_calcdir() internally. */
	
	int vt100net_actionstool_lineup
	(
		vt100net_termcontext *term_ctx,
		int force
	);
	int vt100net_actionstool_columnright
	(
		vt100net_termcontext *term_ctx,
		int force
	);
	int vt100net_actionstool_linedown
	(
		vt100net_termcontext *term_ctx,
		int force
	);
	int vt100net_actionstool_columnleft
	(
		vt100net_termcontext *term_ctx,
		int force
	);
	int vt100net_actionstool_columnhome
	(
		vt100net_termcontext *term_ctx,
		int force
	);
	
		/* Moves the cursor to wherever the current origin is. Affected by DEC Origin Mode and SPD. */
	int vt100net_actionstool_cursorhome( vt100net_termcontext *term_ctx );
		/* Restricts cursor location to currently legal values. */
	int vt100net_actionstool_cursorclamp( vt100net_termcontext *term_ctx );
	
	
	/* Arguments for the "action" argument of vt100net_actionstool_execute(). */
		/* Should NEVER happen. */
	#define vt100_action_INVALID ( 0 )
	#define vt100_action_NOACTION ( 1 )
	#define vt100_action_FULLRESET ( 2 )
	#define vt100_action_SENDRESP ( 3 )
	#define vt100_action_ALERTUSER ( 4 )
	#define vt100_action_LEFTWARD_WRAPLESS ( 5 )
	#define vt100_action_UPWARD_WRAPLESS ( 6 )
	#define vt100_action_RIGHTWARD_WRAPLESS ( 7 )
	#define vt100_action_DOWNWARD_WRAPLESS ( 8 )
	#define vt100_action_HTAB ( 9 )
	#define vt100_action_LINEFEED ( 10 )
	#define vt100_action_FULLLEFTWARD_WRAPLESS ( 11 )
	#define vt100_action_FONTSWAP0_LOCKING ( 12 )
	#define vt100_action_FONTSWAP1_LOCKING ( 13 )
	#define vt100_action_RESUMETRANSMISSION ( 14 )
	#define vt100_action_PAUSETRANSMISSION ( 15 )
		/* Note: this probably shouldn't actually happen? Though the error char is meant to be printed. */
	#define vt100_action_TERMINATESEQUENCE ( 16 )
	#define vt100_action_SETHTAB ( 17 )
	#define vt100_action_SETCURPOS ( 18 )
		/* Fills the entire screen with capital 'E' chars. Used for screen calibration. */
	#define vt100_action_VT100SCRNCALIB ( 19 )
	#define vt100_action_UPWARD_SCROLLING ( 20 )
	#define vt100_action_DOWNWARD_SCROLLING ( 21 )
	#define vt100_action_SAVE_CURSORADJACENCIES ( 22 )
	#define vt100_action_RESTORE_CURSORADJACENCIES ( 23 )
	#define vt100_action_SET_CHARACTERSET ( 24 )
	#define vt100_action_SET_CHARSIZE1W1H ( 25 )
	#define vt100_action_SET_CHARSIZE2W1H ( 26 )
	#define vt100_action_SET_CHARSIZE2W2H ( 27 )
	#define vt100_action_ERASE_INLINE ( 28 )
	#define vt100_action_ERASE_INSCREEN ( 29 )
	#define vt100_action_SET_GRAPHICRENDITION ( 30 )
	#define vt100_action_SET_VERTICALMARGINS ( 31 )
	#define vt100_action_RESET_MODE ( 32 )
	#define vt100_action_SET_MODE ( 33 )
	
	int vt100net_actionstool_execute
	(
		vt100net_termcontext *term_ctx,
		
		uint32_t chara, uint8_t action,
		uint16_t *params_, size_t param_count
	);
	
#endif
/* End libandria4 parsers vt100net terminalutils.h */
