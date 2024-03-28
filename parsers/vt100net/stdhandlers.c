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


#include "stdhandlers.h"
#include "stdbuffer.h"
#include "innerutils.h"



typedef uint8_t vt100net_actionstool_execrecog_recogplat;
#define vt100net_actionstool_execrecog_recogplat_NULL \
	(vt100net_actionstool_execrecog_recogplat)( 0 )
#define vt100net_actionstool_execrecog_recogplat_VT100 \
	(vt100net_actionstool_execrecog_recogplat)( 1 )

#define EXECRECOG_NULL vt100net_actionstool_execrecog_recogplat_NULL
#define EXECRECOG_VT100 vt100net_actionstool_execrecog_recogplat_VT100


#define vt100_action_INVALID ( 0 )
#define vt100_action_NOACTION ( 1 )
#define vt100_action_SENDRESP ( 2 )
#define vt100_action_ALERTUSER ( 3 )
#define vt100_action_LEFTWARD_WRAPLESS ( 4 )
#define vt100_action_HTAB ( 5 )
#define vt100_action_LINEFEED ( 6 )
#define vt100_action_FULLLEFTWARD_WRAPLESS ( 7 )
#define vt100_action_FONTSWAP0_LOCKING ( 8 )
#define vt100_action_FONTSWAP1_LOCKING ( 9 )
#define vt100_action_RESUMETRANSMISSION ( 10 )
#define vt100_action_PAUSETRANSMISSION ( 11 )
	/* Note: this probably shouldn't actually happen? Though the error char is meant to be printed. */
#define vt100_action_TERMINATESEQUENCE ( 12 )
	/* Should NEVER happen. */
#define vt100_action_ESCAPE ( 13 )


typedef struct
{
	vt100net_actionstool_execrecog_recogplat supported;
	uint8_t on_exec;
	
} vt100net_actionstool_execrecog_lookuptype;
	/* The actual definition is further down. */
static vt100net_actionstool_execrecog_lookuptype lookups[ 256 ];

	/* The control-character function. */
int vt100net_actionstool_execrecog1
(
	vt100net_termcontext *term_ctx,
	
	uint32_t chara,
	
	vt100net_actionstool_execrecog_recogplat *plat,
	uint8_t *act
)
{
	if( term_ctx &&  plat && act )
	{
		if( chara > 255 )
		{
			*plat = 0;
			return( 1 );
		}

		*plat = lookups[ chara ].supported;
		*act = lookups[ chara ].action;
		return( 1 );
	}
	
	return( -1 );
}


/* The functions below are all handlers. The first arg is mostly */
/*  obvious, but the second is a smidge less obvious. Here's a */
/*  table: */
	/* vt100net_termcontext_INVALID : The calling context is */
	/*  either onEntry, onExit, or a non-transition. */
	/* vt100net_termcontext_INITIAL_ENTRY, */
	/*  vt100net_termcontext_FETCHCHAR, */
	/*  vt100net_termcontext_GROUND_POSTREAD : probably always */
	/*  errors, as these should really be kept within the caller */
	/*  instead. */
	/* Everything else: the destination of a transition, the */
	/*  source is term_ctx(or other first arg)->dispatch */

	/* Just ignores the current character */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_ignore( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	if( term_ctx )
	{
		if
		(
			nstate > vt100net_termcontext_INVALID &&
			nstate < vt100net_termcontext_STATES__PAST_END
		)
		{
			term_ctx->dispatch = nstate;
		}
		
		return( 1 );
	}
	
	return( -1 );
}
	/* Prints the current character, only happens in GROUND (really GROUND_POSTREAD). */
	/* Must modify glyph in accordance with current char mappings & shift states. */
	/*  ASCII 0x20 & 0x7F have somewhat special behavior. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_print( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	if( term_ctx )
	{
		if
		(
			!(
				term_ctx->buffer &&
					term_ctx->buffer->funcs &&
						term_ctx->buffer->funcs->setcell
			)
		)
		{
			return( -2 );
		}
		
		
		libandria4_buffercell_common value = { { 255, 255, 255 }, { 0, 0, 0 }, 0, 0 /* .chara */ };
		value = term_ctx->buffer_flags;
		value.chara = 0;
#error "FIXME: term_ctx->buffer_flags now has detailed formatting, so we need to use some mask!"
		
			/* The "&& 1" is just because I don't want to check if standard */
			/*  space & delete behavior should be done or not. */
		if( term_ctx->acc_char >= 0x20 && term_ctx->acc_char < 0x7F && 1 )
		{
			value.chara = term_ctx->acc_char;
			
		} else if( term_ctx->acc_char == 0x7F && 0 )
		{
			/* Delete. We just iognore this for 94 chara fonts, we only use */
			/*  it for 96 chara fonts, hence the "&& 0". */
			
			value.chara = term_ctx->acc_char;
			
		} else {
			
			/* Just do nothing. */
		}
		
		if( value.chara )
		{
			int res =
				( term_ctx->buffer->funcs->setcell )
				(
					term_ctx,
						term_ctx->cursor.x,
						term_ctx->cursor.y,
						
						value
				);
			if( !res )
			{
				return( -3 );
			}
			
			if( term_ctx->buffer->width != term_ctx->cursor.x )
			{
				res =
					vt100net_actionstool_scroll
					(
						term_ctx,
							libandria4_termbuffer_directions_right,
							0
					);
				if( !res )
				{
					return( -4 );
				}
			}
			
		} else {
			
			/* chara == 0 */
			
			/* Currently we do nothing, but this should really depend on flags. */
		}
		
		return( 1 );
	}
	
	return( -1 );
}
	/* Perform a C0 or C1 control function. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_execute( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	if( term_ctx )
	{
		int res_i;
		vt100net_actionstool_execrecog_recogplat platforms;
		uint8_t action;
		
			/* The control-character function. */
		res_i = vt100net_actionstool_execrecog1( term_ctx,  uint32_t chara,  &platform, &action );
		/* Just for logging, in case it's useful in the future/for debugging. */
		
		
			/* This has not yet been adapted to vt100net_actionstool_execrecog1(). */
		switch( term_ctx->acc_char )
		{
			/* For seemingly missing entries, see the "default" at the end of this switch. */
			
			
			
			/* C0 command set. */
			
			case 0x0: /* Null. */
				if
				(
					0
					
					&&
					
					term_ctx->flags1 & vt100net_termcontext_flags1_retainnull
					== vt100net_termcontext_flags1_retainnull
				)
				{
					/* We don't need this right now. Though, honestly, what */
					/*  would we even do here anyways? */
					
				} else {
					
						/* If we're not retaining nulls, then we're not */
						/*  retaining nulls. */ 
					break;
				}
			case 0x1: /* Start of heading. */
			case 0x2: /* Start of text. */
			case 0x3: /* End of text. */
			case 0x4: /* End of transmission. */
			case 0x5: /* Enquiry. */
			case 0x6: /* Acknowledge. */
				??? ;
			
			case 0x7: /* Bell. */
				/* Signal something! We have no way to do this yet. */
				??? break;
			case 0x8: /* Backspace. */
					/* Move "backwards", as defined by SPD. We don't currently */
					/*  pay attention to SPD, but that should change. */
				??? res_i = vt100net_actionstool_columnleft( term_ctx,  1 );
				???;
				break;
			case 0xA: /* Line feed. */
					/* As with 0x8, we do the wrong thing right now. */
				??? res_i = vt100net_actionstool_linedown( term_ctx,  1 );
				???;
				break;
			case 0xD: /* Carriage return. */
					/* Move active position to "home" of same line. */
				res_i = vt100net_actionstool_columnhome( term_ctx,  1 );
				???;
				break;
					
			case 0x9: /* Character tabulation. */
			case 0xB: /* Line (vertical) tabulation. */
			
			case 0xC: /* Form feed. */
			
				/* Shift in/out are 7-bit; all locking-shifts are 8-bit. */
			case 0xE: /* Shift out / Locking-shift 1. */
				/* Shift-out, per ECMA-35 / ISO 2022, changes the meaning of byte values */
				/*  0x21 to 0x7E to an alternative set, but is "7 bit only". */
			case 0xF: /* Shift in / Locking-shift 0. */
				/* Shift-in does the opposite of Shift-out, swapping the relevant */
				/*  characters back to their normal meanings. */
			
			case 0x10: /* Data link escape. */
			case 0x11: /* Device control 1. */
			case 0x12: /* Device control 2. */
			case 0x13: /* Device control 3. */
			case 0x14: /* Device control 4. */
			case 0x15: /* Negative acknowledge. */
			case 0x16: /* Synchronous idle. */
			case 0x17: /* End of transmission block. */
			case 0x18: /* Cancel. */
					/* We just ignore this. */
				break;
			case 0x19: /* End of medium. */
			case 0x1A: /* Substitute. */
			
			case 0x1C: /* File separator / Info separator 4. */
			case 0x1D: /* Group separator / Info separator 3. */
			case 0x1E: /* Record separator / Info separator 2. */
			case 0x1F: /* Unit separator / Info separator 1. */
			
			
			
			/* C1 command set. */
			
			case 0x82: /* Break permitted here. */
				/* Like ASCII space, but zero width, so a "zero width space". Unlike */
				/*  soft hyphens, ALWAYS breaks "kerning". */
			case 0x83: /* No break here. */
				/* Non-graphic character, the preceding and following characters */
				/*  must not be separated onto different lines. */
				/* Note: maybe ignore? */
			case 0x84: /* Index. */
				/* Basically Line feed. Move the active position / cursor */
				/*  down one line without changing it's column. Used to */
				/*  eliminate ambiguity about whether LF means LF+CR, but */
				/*  mostly unneeded. Deprecated. */
				/* Also, current implementation is bad. */
				??? res_i = vt100net_actionstool_linedown( term_ctx,  1 );
				???
				break;
			case 0x85: /* Next line. */
				/* Standard newline, moves to home position of next line. */
				??? res_i = vt100net_actionstool_linedown( term_ctx,  1 );
				res_i = vt100net_actionstool_columnhome( term_ctx,  1 );
				???
				break;
			
			case 0x86: /* Start of selected area. */
				/* Some software assumes that at least some encodings of this move */
				/*  the active position / cursor to the lower-left corner of the */
				/*  screen. */
				/* Used by block-oriented terminals. */
			case 0x87: /* End of selected area. */
				/* Used by block-oriented terminals. */
			case 0x88: /* Character tabulation set. */
				/* Set tab-stops for columns. */
			case 0x89: /* Character tabulation with justification. */
				/* Sounds like a pain in the ass. */
			case 0x8A: /* Line tabulation set. */
				/* Set tab-stops for vertical movement / lines. */
			
			??? /* These are for partial line movements. I don't know if I'll support it. */
			case 0x8B: /* Partial line down. */
				/* Usable to implement subscripts or undo PLU. */
			case 0x8C: /* Partial line up. */
				/* Usable to implement superscripts or undo PLD. */
			
			case 0x8D: /* Reverse line feed. */
				??? res_i = vt100net_actionstool_lineup( term_ctx,  1 );
				???;
				break;
			
			case 0x8E: /* Single-shift two. */
				/* Effectively a font designator. If G2 is a 94-character set, then no */
				/*  characters will be allocated to A0 or FF. Swaps with the G1 (standard */
				/*  ASCII) set if accessed via this command, but NOT if via SI/SO. */
			case 0x8F: /* Single-shift three. */
				/* As above, including the related character range.. */
			case 0x90: /* Device control string. */
			case 0x91: /* Private use 1. */
			case 0x92: /* Private use 2. */
			case 0x94: /* Cancel character. */
				/* Basically destructive delete. */
				res_i = vt100net_actionstool_columnleft( term_ctx,  1 );
				??? /* Set character to blank? */
				break;
			
			case 0x95: /* Message waiting. */
				/* Triggers the recipient to respond with a "Device status report", */
				/*  because sometimes you want to be sent a query instead of send */
				/*  one yourself. */
			case 0x96: /* Start of protected area. */
				/* Used by block-oriented terminals. */
			case 0x97: /* End of protected area. */
				/* Used by block-oriented terminals. */
			case 0x98: /* Start of string. */
				/* Context/implementation/etc. dependant, similar to 0x9B. */
			case 0x9A: /* Single character introducer. */
				/* I believe this was from some proposal that never got standardized. */
			case 0x9B: /* Control sequence introducer. */
				/* Context/implementation/etc. dependant, similar to 0x9D. */
			case 0x9C: /* String terminator. */
				/* Because '\0' != 0 in ANSI terminal coding. */
			case 0x9D: /* Operating system command. */
				/* Context/implementation/etc. dependant, similar to 0x9E. */
			case 0x9E: /* Privacy message. */
				/* Context/implementation/etc. dependant, similar to 0x9F. */
			case 0x9F: /* Application program command. */
				/* Sometimes used for e.g. sending Kermit commands. Thus, also */
				/*  sometimes filtered. Context/implementation/etc. dependant. */
			
			case 0xA0: /* Non-breaking space. */
				/* A space is REQUIRED, but MOST NOT be treated as a prefered line */
				/*  break location. In HTML it cannot be combined with ther spaces */
				/*  (including other copies of itself), which is absolutely needed. */
			case 0xAD: /* Soft hyphen. */
				/* A prefered line-break position. In older (e.g. VT100) cases */
				/*  indicates a middle-man inserted hyphen, so that it and an */
				/*  immediately following whitespace can be deleted to restore the */
				/*  original text form. In newer originator-inserted cases, */
				/*  indicates suggested line break locations, where a hyphen is */
				/*  displayed if the line is broken, but no hyphen if no line break */
				/*  is performed; if no hyphen is displayed, then character-kerning */
				/*  must behave as if there is no soft hyphen at all. */
				/* The older version could be called "mandatory-newline hyphen", */
				/*  with the newer version called "hypen if newline". */
			
			default:
				switch( term_ctx->acc_char )
				{
					case 0x20: /* Space. */
						/* Must be handled elsewhere for 96-character sets, and */
						/* SHOULD always be handled elsewhere. */
					case 0x7F: /* Delete. */
						/* Must be handled elsewhere for 96-character sets. In all */
						/*  other cases, we just do nothing (other than maybe send */
						/*  some logging data. */
					case 0x80: /* Padding. */
						/* Mostly wasn't standardized, was initially meant to encode */
						/*  non-ASCII characters. */
					case 0x81: /* High octet preset. */
						/* Mostly wasn't standardized, was initially meant to encode a */
						/*  sequence of multi-byte characters that all started with */
						/*  the same first byte without needing repeats (would have */
						/*  broken even at maybe the second character?). */
					case 0x99: /* Single graphic character introducer. */
						/* Basically a single-character of 0x81, could TEMPORARILY */
						/*  override 0x81 so that "HOP mode" didn't need to change. */
						/*  Originally(?) meant to be followed by a single "UCS-4" */
						/*  (32-bit Unicode) encoded character. */
					
					case 0x1B: /* Escape. */
						/* Definitely an error, this is meant to be caught by the outer parser. */
					
					default:
						/* A display character. Should never be here. */
						???
				}
				???
		}
		
		???
	}
	
	return( -1 );
	
	???
	
	struct libandria4_termbuffer_generic
	{
		libandria4_termbuffer_generic_vtab *funcs;
		
			/* Measured in character cells, not in e.g. pixels, or inches. */
		uint32_t width, height;
		
		libandria4_memfuncs_t *mfuncs;
		libandria4_commonio_handle *messaging;
	};
	typedef struct libandria4_termbuffer_generic_vtab
	{
		libandria4_termbuffer_generic_cellsetter setcell;
		libandria4_termbuffer_generic_blocksetter setblock;
		
		libandria4_termbuffer_generic_cellsetter getcell;
		libandria4_termbuffer_generic_blocksetter getblock;
		
		libandria4_termbuffer_common_scroll scroll;
		libandria4_termbuffer_generic_resizer resize;
		
	} libandria4_termbuffer_generic_vtab;
	int libandria4_termbuffer_common_scroll
	(
		libandria4_termbuffer_generic *term_,
			libandria4_termbuffer_directions dir,
			libandria4_buffercell_common fill
	);
	
	
	
			/* The current state of the buffer. */
		libandria4_termbuffer_generic *buffer;
		libandria4_buffercell_common buffer_flags;
		struct
		{
			uint32_t x, y;
			
		} cursor;
	struct libandria4_termbuffer_generic
	{
		libandria4_termbuffer_generic_vtab *funcs;
		
			/* Measured in character cells, not in e.g. pixels, or inches. */
		uint32_t width, height;
		
		libandria4_memfuncs_t *mfuncs;
		libandria4_commonio_handle *messaging;
	};
	
	???
}
	/* Reset current "private" flag, intermediate characters, final character, and */
	/*  parameters. Happens entering ESCAPE, CSI_ENTRY, and DCS_ENTRY. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_clear( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	if( term_ctx )
	{
		int loop;
		
		term_ctx->sequence_dispatch.private_marker = ( ( (uint32_t)1 ) << 31 );
		
		loop = 0;
		while( loop < vt100net_termcontext_INTERMS_LEN )
		{
			term_ctx->sequence_dispatch.intermediates[ loop ] = ( ( (uint32_t)1 ) << 31 );
			
			loop += 1;
		}
		term_ctx->interm_count = 0;
		
		term_ctx->sequence_dispatch.final_character = ( ( (uint32_t)1 ) << 31 );
		
		loop = 0;
		while( loop < vt100net_termcontext_PARAMS_LEN )
		{
			term_ctx->params[ loop ] = ( ( (uint32_t)1 ) << 15 );
			
			loop += 1;
		}
		term_ctx->param_count = 0;
		
		return( vt100net_actions_ignore( term_ctx, nstate ) );
	}
	
	return( -1 );
}
	/* Store private marker or intermediate character for use when a "final" */
	/*  character arrives. X3.64 defined control sequences with one intermediate, */
	/*  Digital defined escape sequences with two intermediates and device control */
	/*  strings with one. If too many intermediates arrive, it can be flaged to */
	/*  turn the op into a null op. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_collect( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
	
		/* Confirm that ->acc_char is the right source for the character. */
	term_ctx->sequence_dispatch.intermediates[ term_ctx->interm_count ] =
		??? term_ctx->acc_char ???  &
		libandria4_buffercell_common_chara_UNICODEVALID_mask;
	term_ctx->interm_count += 1;
	
	???
}
	/* Collect parameter string characters for SEC or DCS sequences, and build */
	/*  list of parameters. Processes characters '0'-'9', and ';'. Semicolon */
	/*  seperates parameters. No limit to param string length, but only 16 */
	/*  params need be stored, all extras are silently ignored. */
	/* VT500 manual says that all parameters will be capped at 9999 (decimal), */
	/*  but also says that DECSR can accept 16383. Individual funcs must verify */
	/*  parameter values anyways, so just support 16383 (14 bit unsigned max), */
	/*  and leave the rest to the command. */
	/* Commands can have defaults, triggered by either leaving blank or setting */
	/*  at 0. For blank use an extra bit in the 16bit param value as a flag, */
	/*  and leave the rest to the command. ECMA-48 distinguishes between blank */
	/*  & zero; until fifth edition it had a ZDM mode that treated them */
	/*  identically, but it costs nothing extra to skip that... */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_param( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Final char of esc seq has arrived; determine operation from */
	/*  intermediates and final, then exec. Remember *_collect(). */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_esc_dispatch( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
	
		/* Confirm that ->acc_char is the right source for the character. */
	term_ctx->sequence_dispatch.final_character =
		??? term_ctx->acc_char ???  &
		libandria4_buffercell_common_chara_UNICODEVALID_mask;
	
	???
}
	/* As with esc, but also use marker for dispatch. "Pass in param list", but */
	/*  the command can probably just grab those itself... The private marker is */
	/*  only needed for dispatch by VT500's DECSTBM and DECPCTERM, but there's */
	/*  no real problem in most or any cases. */
	/* The command will ignore extra params, but missing params may cause a */
	/*  partial or complete NOOP instead of the intended action. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_csi_dispatch( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Happens when "final" char arrives in first part of device control string. */
	/*  Dispatches by private marker, intermediates, and final char, passing in */
	/*  params; also selects handler for rest of chars in control string, */
	/*  handler will be called bu *_put() for every remaining string char as it */
	/*  arrives. This allows easy plug-in of extra parsers to support added */
	/*  functionality: main parser could add e.g. DECDLD fairly easy, but e.g. */
	/*  ReGIS is overly complicated to belong in main parser. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_hook( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Passes characters from data string part of a device control string to a */
	/*  handler selected by *_hook(). Also passes C0 controls to the handler. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_put( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Calls a previously selected handler with "end of data" when a device */
	/*  control string is terminated with ST, CAN, SUB, or ESC. This allows the */
	/*  handler to finish cleanly. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_unhook( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Initializes an external parser (the OSC Handler) to handle the */
	/*  characters from the control string. OSC control strings are structured */
	/*  differently than device control strings, so there's no choosing the */
	/*  parser. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_osc_start( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Passes characters to the OSC Handler as they arrive. There is no need to */
	/*  buffer characters while waiting for the end of the control string. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_osc_put( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Called to let the OSC Handler finish neatly when ST, CAN, SUB, or ESC */
	/*  terminate the OSC string. */
	/* nstate is the new state. Do we need to care here? */
int vt100net_actions_osc_end( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}



static vt100net_actionstool_execrecog_lookuptype lookups[ 256 ] =
	{
		/* 0x00, 00 */
			{ EXECRECOG_VT100, vt100_action_NOACTION },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
				/* ENQ, send an answerback message. */
			{ EXECRECOG_VT100, vt100_action_SENDRESP },
			{ EXECRECOG_NULL, vt100_action_INVALID },
				/* BEL, emit SOME SORT of user notification signal. */
			{ EXECRECOG_VT100, vt100_action_ALERTUSER },
			
				/* BS, move active pos toward left margin, NO LINE WRAP. */
			{ EXECRECOG_VT100, vt100_action_LEFTWARD_WRAPLESS },
				/* HT, move active pos to next tab stop, or right margin if no stops. */
			{ EXECRECOG_VT100, vt100_action_HTAB },
				/* LF, causes either line feed or newline, depending on newline mode. */
			{ EXECRECOG_VT100, vt100_action_LINEFEED },
				/* VT, treated as LF. */
			{ EXECRECOG_VT100, vt100_action_LINEFEED },
			
				/* VT, treated as LF. */
			{ EXECRECOG_VT100, vt100_action_LINEFEED },
				/* CR, move active pos to left margin of current line. */
			{ EXECRECOG_VT100, vt100_action_FULLLEFTWARD_WRAPLESS },
				/* SO, invoke G1 char set, as designated by SCS control sequence. */
			{ EXECRECOG_VT100, vt100_action_FONTSWAP0_LOCKING },
				/* SI, select G0 char set, as selected by ESC ( sequence. */
			{ EXECRECOG_VT100, vt100_action_FONTSWAP1_LOCKING },
		/* 0x10, 020 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
				/* XON / DC1, causes terminal to resume transmission. */
			{ EXECRECOG_VT100, vt100_action_RESUMETRANSMISSION },
			{ EXECRECOG_NULL, vt100_action_INVALID },
				/* XOFF / DC3, causes terminal to stop all transmissions except XON and XOFF. */
			{ EXECRECOG_VT100, vt100_action_PAUSETRANSMISSION },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
				/* CAN, terminate any incomplete control sequence without executing. Also, cause error character to display. */
			{ EXECRECOG_VT100, vt100_action_TERMINATESEQUENCE },
			{ EXECRECOG_NULL, vt100_action_INVALID },
				/* SUB, treated as CAN. */
			{ EXECRECOG_VT100, vt100_action_TERMINATESEQUENCE },
				/* ESC, starts a control sequence. */
			{ EXECRECOG_VT100, vt100_action_NOACTION },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0x20 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0x30 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0x40 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0x50 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0x60 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0x70 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
				/* DEL, ignore, preferably not stored in input buffer. */
			{ EXECRECOG_VT100, vt100_action_NOACTION },
		/* 0x80 : C1 control codes */
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
		/* 0x90 : C1 control codes */
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
			{ EXECRECOG_NULL },
		/* 0xA0 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0xB0 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0xC0 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0xD0 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0xE0 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
		/* 0xF0 */
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID },
			{ EXECRECOG_NULL, vt100_action_INVALID }
	};
