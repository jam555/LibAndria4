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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "../../basic/commonerr.h"
#include "../../text/stdbuffer.h"
#include "../../basic/bitarray.h"
#include "../../text/charsettranslators.h"
#include "terminalutils.h"

/*
TODO:
	Check that all the needed includes are here (they probably aren't).
	vt100net_actionstool_execute():
		vt100_action_FULLRESET
			needs an implementation
		vt100_action_RESET_MODE
			standard modes
		vt100_action_SET_MODE
			standard modes
		vt100_action_CLEARHTAB
			params[ 0 ] == 3, clear ALL tabs
		vt100_action_SET_CHARACTERSET
			unknown term_ctx->sequence_dispatch.final_character value
			unknown term_ctx->sequence_dispatch.intermediates[ 0 ] value
		vt100_action_TERMINATESEQUENCE
			needs to print an "error character", so we need to decide how to do that.
*/


#define VT100NET_REPORT_ERR_INNER( val ) return( -5 );
#define VT100NET_REPORT_ERR( ctx, rep_type_mmbr_ptr, filename, linenum )
	{
		libandria4_error_mayerr VT100NET_REPORT_ERR_res = libandria4_error_print
			(
				( ctx )->errroute.errrep,
					(libandria4_error_basalstruct*)rep_type_mmbr_ptr,
					( linenum ),
					( filename )
			);
		LIBANDRIA4_COMMONIO_MAYERR_NULLSUCC( VT100NET_REPORT_ERR_res,  VT100NET_REPORT_ERR_INNER );
	}
	#define VT100NET_REPORT_ERR( ctx, rep_type_mmbr_ptr, filename, linenum ) \
		{ int res = vt100net_report_parser_error( (vt100net_termcontext*)( ctx ), (uint32_t*)( rep_type_mmbr_ptr ) ); \
			if( res != -1 ) { \
				term_ctx->errroute.error_values.file = ( filename ); \
				term_ctx->errroute.error_values.line = ( linenum ); } \
			switch( res ) \
			{ case -1: \
					fprintf( stderr, \
						"ERROR: VT100NET_REPORT_ERR() received a \"bad args\" error in %s at %i.\n", \
						(char*)(filename), (int)(linenum) ); return( -5 ); \
				case -4: return( -6 ); \
				case -2: case -3: return( -7 ); \
				default: break; } }



/* Simple calculations. */

libandria4_termbuffer_directions vt100net_actionstool_calcdir
(
	vt100net_termcontext *term_ctx,
	libandria4_termbuffer_directions dir
)
{
	libandria4_termbuffer_directions ret = libandria4_termbuffer_directions_invalid;
	
	if
	(
		term_ctx &&
		dir >= libandria4_termbuffer_directions_up &&
		dir <= libandria4_termbuffer_directions_left
	)
	{
		dir += term_ctx->flags3 & vt100net_termcontext_flags3_SPDmask;
		if( dir > libandria4_termbuffer_directions_left )
		{
			dir -= 4;
		}
		/* Yeah, that's all, just an add then range constraint. */
	}
	
	return( ret );
}


/* Cursor ops. */

int vt100net_actionstool_cursorhome( vt100net_termcontext *term_ctx )
{
	if( term_ctx )
	{
		/* Actual location should probably depend on SPD, but I'm */
		/*  not dealing with that right now. */
		
		if( !( term_ctx->vt100_flags & vt100net_termcontext_vt100flags_originmode ) )
		{
			/* DEC Origin Mode "reset": the entire screen is accessible. */
			
			term_ctx->cursor.x = 0;
			term_ctx->cursor.y = 0;
			
		} else {
			
			/* DEC Origin Mode "set": the accessible screen is restricted */
			/*  to within the margins. */
			
			term_ctx->cursor.x = 0;
			term_ctx->cursor.y = term_ctx->scrolling_region.top;
		}
		
		return( 1 );
	}
	
	return( -1 );
}
int vt100net_actionstool_cursorclamp( vt100net_termcontext *term_ctx )
{
	if( term_ctx )
	{
		if( term_ctx->vt100_flags & vt100net_termcontext_vt100flags_originmode )
		{
			/* DEC Origin Mode "set": the entire screen is accessible. */
			
			if( term_ctx->cursor.y > term_ctx->scrolling_region.bottom )
			{
				term_ctx->cursor.y = term_ctx->scrolling_region.bottom;
				
			} else if( term_ctx->cursor.y < term_ctx->scrolling_region.top )
			{
				term_ctx->cursor.y = term_ctx->scrolling_region.top;
			}
			
		} else {
			
			if( term_ctx->cursor.y > term_ctx->dimensions.y )
			{
				term_ctx->cursor.y = term_ctx->dimensions.y;
				
			} else if( term_ctx->cursor.y == 0 )
			{
				term_ctx->cursor.y = 1;
			}
		}
		
		if( term_ctx->cursor.x > term_ctx->dimensions.x )
		{
			term_ctx->cursor.x = term_ctx->dimensions.x;
			
		} else if( term_ctx->cursor.x == 0 )
		{
			term_ctx->cursor.x = 0;
		}
		
		return( 1 );
	}
	
	return( -1 );
}
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
)
{
	if
	(
		term_ctx &&
		
		dir < libandria4_termbuffer_directions_pastmax &&
		dir > libandria4_termbuffer_directions_invalid
	)
	{
		int res;
		
		if( !( term_ctx->buffer ) )
		{
			return( -2 );
		}
		
		if( dir == libandria4_termbuffer_directions_null )
		{
			return( 0 );
		}
		
		switch( dir )
		{
			case libandria4_termbuffer_directions_up:
				if
				(
					(
						term_ctx->vt100_flags & vt100net_termcontext_vt100flags_originmode &&
						term_ctx->cursor.y > term_ctx->scrolling_region.top
					) ||
					(
						!( term_ctx->vt100_flags & vt100net_termcontext_vt100flags_originmode ) &&
						term_ctx->cursor.y > 1
					)
				)
				{
					term_ctx->cursor.y -= 1;
					
				} else if( force )
				{
					res = vt100net_actionstool_scroll( term_ctx, dir, force );
					
					if( !res )
					{
						return( res - 3 );
						
					} else {
						
						return( res + 4 );
					}
					
				} else {
					
					return( 0 );
				}
				break;
			case libandria4_termbuffer_directions_right:
				if( term_ctx->cursor.x < term_ctx->buffer->width )
				{
					term_ctx->cursor.x += 1;
					
				} else if( force )
				{
					res = vt100net_actionstool_itercursor( term_ctx, libandria4_termbuffer_directions_down, force );
					term_ctx->cursor.x = 0;
					
					if( !res )
					{
						return( res - 3 );
						
					} else {
						
						return( res + 4 );
					}
					
				} else {
					
					return( 0 );
				}
				break;
			case libandria4_termbuffer_directions_down:
				if
				(
					(
						term_ctx->vt100_flags & vt100net_termcontext_vt100flags_originmode &&
						term_ctx->cursor.y < term_ctx->scrolling_region.bottom &&
						term_ctx->cursor.y + 1 < term_ctx->buffer->height
					) ||
					(
						!( term_ctx->vt100_flags & vt100net_termcontext_vt100flags_originmode ) &&
						term_ctx->cursor.y + 1 < term_ctx->buffer->height
					)
				)
				{
					term_ctx->cursor.y += 1;
					
				} else if( force )
				{
					res = vt100net_actionstool_scroll( term_ctx, dir, force );
					
					if( !res )
					{
						return( res - 3 );
						
					} else {
						
						return( res + 4 );
					}
					
				} else {
					
					return( 0 );
				}
				break;
			case libandria4_termbuffer_directions_left:
				if( term_ctx->cursor.x > 0 )
				{
					term_ctx->cursor.x -= 1;
					
				} else if( force )
				{
					res = vt100net_actionstool_itercursor( term_ctx, libandria4_termbuffer_directions_up, force );
					term_ctx->cursor.x = term_ctx->buffer->width;
					if( term_ctx->cursor.x )
					{
						term_ctx->cursor.x -= 1;
					}
					
					if( !res )
					{
						return( res - 3 );
						
					} else {
						
						return( res + 4 );
					}
					
				} else {
					
					return( 0 );
				}
				break;
			case libandria4_termbuffer_directions_isCR:
				term_ctx->cursor.x = 0;
				break;
			case libandria4_termbuffer_directions_islastline:
				res = vt100net_actionstool_scroll( term_ctx, libandria4_termbuffer_directions_down, force );
				if( !res )
				{
					return( res - 3 );
					
				} else {
					
					return( res + 4 );
				}
			default:
				return( -3 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}


/* Not quite cursor stuff, not quite character stuff. */

	/* If vt100net_actionstool_itercursor_direction is found, it should */
	/*  be replaced with libandria4_termbuffer_directions. */
int vt100net_actionstool_scroll
(
	vt100net_termcontext *term_ctx,
	libandria4_termbuffer_directions dir,
	int force
)
{
	if
	(
		term_ctx &&
		
		dir < libandria4_termbuffer_directions_pastmax &&
		dir > libandria4_termbuffer_directions_invalid
	)
	{
		int res;
		
		if
		(
			!(
				term_ctx->buffer &&
				term_ctx->buffer->vtab &&
				term_ctx->buffer->vtab->scroll
			)
		)
		{
			return( -2 );
		}
		
		if( dir == libandria4_termbuffer_directions_null )
		{
			return( 0 );
		}
		
		switch( dir )
		{
			case libandria4_termbuffer_directions_isCR:
			case libandria4_termbuffer_directions_right:
			case libandria4_termbuffer_directions_left:
				return( -3 );
			case libandria4_termbuffer_directions_up:
				if( term_ctx->vt100_flags & vt100net_termcontext_vt100flags_originmode )
				{
					res =
						term_ctx->buffer->vtab->scroll
							(
								term_ctx->buffer,
									libandria4_termbuffer_directions_up,
									term_ctx->buffer_flags,
									0, term_ctx->scrolling_region.top,
									term_ctx->dimensions.x,
										term_ctx->scrolling_region.bottom -
										term_ctx->scrolling_region.top + 1
							);
					
				} else {
					
					res =
						term_ctx->buffer->vtab->scroll
							(
								term_ctx->buffer,
									libandria4_termbuffer_directions_up,
									term_ctx->buffer_flags,
									0, 0,
									term_ctx->dimensions.x, term_ctx->dimensions.y
							);
				}
				
				if( !res )
				{
					return( res - 4 );
				}
				break;
			case libandria4_termbuffer_directions_down:
			case libandria4_termbuffer_directions_islastline:
				if( term_ctx->vt100_flags & vt100net_termcontext_vt100flags_originmode )
				{
					res =
						term_ctx->buffer->vtab->scroll
							(
								term_ctx->buffer,
									libandria4_termbuffer_directions_down,
									term_ctx->buffer_flags,
									0, term_ctx->scrolling_region.top,
									term_ctx->dimensions.x,
										term_ctx->scrolling_region.bottom -
										term_ctx->scrolling_region.top + 1
							);
					
				} else {
					
					res =
						term_ctx->buffer->vtab->scroll
							(
								term_ctx->buffer,
									libandria4_termbuffer_directions_down,
									term_ctx->buffer_flags,
									0, 0,
									term_ctx->dimensions.x, term_ctx->dimensions.y
							);
				}
				
				if( !res )
				{
					return( res - 4 );
				}
				break;
			default:
				return( -4 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}


/* Character operations. */

	/* TODO: Rationalize the line & column numbers! */
int vt100net_actionstool_clearcharas
(
	vt100net_termcontext *term_ctx,
	uint32_t line, uint32_t column1, uint32_t column2,
	uint32_t blankval
)
{
	if( term_ctx )
	{
		if
		( !(
			term_ctx->buffer &&
			term_ctx->buffer->funcs &&
			term_ctx->buffer->funcs->setcell
		) )
		{
			return( -2 );
		}
		if
		(
			line > term_ctx->buffer->height ||
			column2 > term_ctx->buffer->width
		)
		{
			return( -3 );
		}
		if( column1 > column2 )
		{
			return( -4 );
		}
		
		libandria4_buffercell_common chara = term_ctx->buffer_flags;
		int res;
		
		chara.chara &= libandria4_buffercell_common_chara_UNICODEINVALID_mask;
		blankval &= libandria4_buffercell_common_chara_UNICODEVALID_mask;
		chara.chara |= blankval;
		
		while( column1 < column2 )
		{
			res = term_ctx->buffer->funcs->setcell( term_ctx->buffer,  column1, line, chara );
			if( res < 0 )
			{
				return( -5 );
			}
			
			++column1;
		}
		
		return( 1 );
	}
	
	return( -1 );
}
int vt100net_actionstool_writechara( vt100net_termcontext *term_ctx, uint32_t newval )
{
	if( term_ctx )
	{
		if
		( !(
			term_ctx->buffer &&
			term_ctx->buffer->funcs &&
			term_ctx->buffer->funcs->setcell
		) )
		{
			return( -2 );
		}
		if
		(
			term_ctx->cursor.y > term_ctx->buffer->height ||
			term_ctx->cursor.x > term_ctx->buffer->width
		)
		{
			return( -3 );
		}
		
		libandria4_buffercell_common chara = term_ctx->buffer_flags;
		int res;
		
		chara.chara &= libandria4_buffercell_common_chara_UNICODEINVALID_mask;
		newval &= libandria4_buffercell_common_chara_UNICODEVALID_mask;
		chara.chara |= newval;
		
		res = term_ctx->buffer->funcs->setcell( term_ctx->buffer,  term_ctx->cursor.x, term_ctx->cursor.y, chara );
		if( res < 0 )
		{
			return( -5 );
		}
		
		if
		(
			!vt100net_actionstool_columnright
			(
				term_ctx,
				( term_ctx->vt100_flags & vt100net_termcontext_vt100flags_autowrapmode ? 1 : 0 )
			)
		)
		{
			return( -6 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}





/*****************************************************************************/
/*****************************************************************************/
/** ANSI terminal SGR: "Select Graphic Rendition" (or something like that). **/
/**  In essence, per-character traits like font, bold, etc. ******************/
/*****************************************************************************/
/*****************************************************************************/

	/* Note that per VT510 SGR documentation, all of these traits move with */
	/*  the characters. As should be normally desired. */
int vt100net_actionstool_SGR
(
	vt100net_termcontext *term_ctx,
	uint16_t *params, size_t param_count
)
{
	if( term_ctx && params )
	{
		size_t iter = 0;
		uint16_t par;
		
		while( iter < param_count )
		{
			par = params[ iter ];
			if( par & ( ( 1 << 15 ) - 1 ) )
			{
				par = 0;
			}
			switch( par )
			{
					/* VT100 attributes. */
				case 0: /* Reset ALL SGR & similar traits to "default". */
					term_ctx->buffer_flags.style = libandria4_buffercell_common_style_NONE;
					term_ctx->buffer_flags.chara &= ~( libandria4_buffercell_common_chara_FONT_mask );
					term_ctx->buffer_flags.chara |= libandria4_buffercell_common_chara_FONT_Terminal;
					break;
				case 1: /* Bold or increased intensity */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_intensity_MASK );
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_intensity_BOLD;
					break;
				case 21: /* Doubly underlined, but we'll probably only support single. */
						/* Double gets used as "disable bold" on Linux console before 4.17, and others. */
				case 4: /* Underscore */
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_UNDERSCORE;
					break;
				case 5: /* Blink, slow, less than 150x per minute */
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_SLOWBLINK;
					break;
				case 7: /* Negative (reverse) image */
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_INVERT;
					break;
				
					/* These are various things we probably won't/shouldn't support. */
				case 51: /* Framed */
						/* Implemented as "emoji variation selector" in mintty. */
						/* Probably shouldn't support framed or encircled. */
				case 52: /* Encircled */
				case 54: /* Neither framed nor encircled */
				case 26: /* Proportional spacing. Probably won't support, though useful for cursive & arabic. */
				case 50: /* Disable proportional spacing. The norm for terminals. */
				default: /* If we don't know it, just ignore it. */
					break;
				
				/* Below are non-VT100 attributes. */
				
				case 2: /* Faint, decreased intensity, or dim */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_intensity_MASK );
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_intensity_FAINT;
					break;
				case 6: /* Blink, fast, more than 150x per minute. An MS-DOS/IBM PC thing. Limited support. */
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_FASTBLINK;
					break;
				case 8: /* Conceal or hide */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_intensity_MASK );
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_intensity_HIDDEN;
					break;
				case 9: /* Crossed-out, or strike	Characters legible but marked as if for deletion. */
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_STRIKETHROUGH;
					break;
				case 28: /* Reveal	Not concealed */
					/* We'll treat this as just normal intensity. */
				case 22: /* Normal intensity	Neither bold nor faint */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_intensity_MASK );
						/* Technically we don't need this bit, but might as well for future-proofing. */
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_intensity_NORMAL;
					break;
				case 24: /* Not underlined	Neither singly nor doubly underlined */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_UNDERSCORE );
					break;
				case 25: /* Not blinking	Turn blinking off */
						/* I see no reason to distinguish between these here. */
					term_ctx->buffer_flags.style &=
						~(
							libandria4_buffercell_common_style_SLOWBLINK |
							libandria4_buffercell_common_style_FASTBLINK
						);
					break;
				case 27: /* Not reversed */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_INVERT );
					break;
				case 29: /* Not crossed out */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_STRIKETHROUGH );
					break;
				case 53: /* Overlined */
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_OVERLINED;
					break;
				case 55: /* Not overlined */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_OVERLINED );
					break;
				
					/* On graphics targets we do WANT this... but we don't have support yet. */
				case 73: /* Superscript		Implemented only in mintty */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_sizing_MASK );
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_sizing_SUPERSCRIPT;
				case 74: /* Subscript */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_sizing_MASK );
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_sizing_SUBSCRIPT;
				case 75: /* Neither superscript nor subscript */
					term_ctx->buffer_flags.style &= ~( libandria4_buffercell_common_style_sizing_MASK );
					term_ctx->buffer_flags.style |= libandria4_buffercell_common_style_sizing_NORMAL;
					break;
				/* We don't currently support libandria4_buffercell_common_style_sizing_MINITEXT, */
				/*  but it would be nice. */
				
					/* Fonts. */
				case 23: /* Neither italic, nor blackletter */
						/* How is 23 different from 10 for us? */
				case 10: /* Primary (default) font */
						/* For us, a "terminal" font. */
					term_ctx->buffer_flags.chara &= ~( libandria4_buffercell_common_chara_FONT_mask );
					term_ctx->buffer_flags.chara |= libandria4_buffercell_common_chara_FONT_Terminal;
					break;
				case 3: /* Italic	Not widely supported. Sometimes treated as inverse or blink. */
						/* For us, a font. */
					term_ctx->buffer_flags.chara &= ~( libandria4_buffercell_common_chara_FONT_mask );
					term_ctx->buffer_flags.chara |= libandria4_buffercell_common_chara_FONT_Italic;
					break;
				case 20: /* Fraktur (Gothic) */
						/* Just one of our blackletter fonts. */
					term_ctx->buffer_flags.chara &= ~( libandria4_buffercell_common_chara_FONT_mask );
					term_ctx->buffer_flags.chara |= libandria4_buffercell_common_chara_FONT_Fraktur;
					break;
			}

			++iter;
		}
		
		/* This space intentionally left blank. */
	}
	
	return( -1 );
}





/*******************************/
/*******************************/
/** Basic underlying actions. **/
/*******************************/
/*******************************/

int vt100net_actionstool_execute
(
	vt100net_termcontext *term_ctx,
	
	uint32_t chara, uint8_t action,
	uint16_t *params_, size_t param_count
)
{
	LIBANDRIA4_ERROR_BUILDFUNCNAME_SIMPLESTRUCT( funcname, __func__ );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			badargs,
			"FATAL: vt100net_actionstool_execute() was given an illegal null term_ctx."
		);
	
	if( term_ctx && ( !!params == !!param_count ) )
	{
#define vt100net_actionstool_execute_PARAMCOUNT 2
		uint16_t params[ vt100net_actionstool_execute_PARAMCOUNT ];
		int res = 0;
		
			/* TODO: Do we even use this anywhere? */
		while( param_count > res && vt100net_actionstool_execute_PARAMCOUNT < res )
		{
			params[ res ] = params_[ res ];
			++res;
		}
		
#define vt100net_actionstool_execute_BUILDERRSTRUCT( resultname, calleetext, casetext ) \
	VT100NET_BUILDERRORSTRUCT_SIMPLETYPE( &funcname, resultname, \
		"ERROR: vt100net_actionstool_execute() received an error return from " \
			calleetext "in case" casetext "." )
		
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE( &funcname, invalidcase,
			"ERROR: vt100net_actionstool_execute() encountered the invalid case, "
			"check for initialization errors." );
		vt100net_actionstool_execute_BUILDERRSTRUCT( badalert,
			"term_ctx->buffer->vtab->alertuser()", "vt100_action_ALERTUSER" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( lw_wless_badcl,
			"vt100net_actionstool_columnleft()", "vt100_action_LEFTWARD_WRAPLESS" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( lf_badld,
			"vt100net_actionstool_linedown()", "vt100_action_LINEFEED" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( lf_badch,
			"vt100net_actionstool_columnhome()", "vt100_action_LINEFEED" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( flw_wless_badch,
			"vt100net_actionstool_columnhome()", "vt100_action_FULLLEFTWARD_WRAPLESS" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( scurpos_crclmp,
			"vt100net_actionstool_cursorclamp()", "vt100_action_SETCURPOS" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( rstr_cradj_crclmp,
			"vt100net_actionstool_cursorclamp()", "vt100_action_RESTORE_CURSORADJACENCIES" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( rst_md_crhm,
			"vt100net_actionstool_cursorhome()", "vt100_action_RESET_MODE" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( st_md_crhm,
			"vt100net_actionstool_cursorhome()", "vt100_action_SET_MODE" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( st_vrtmrgns_crhm,
			"vt100net_actionstool_cursorhome()", "vt100_action_SET_VERTICALMARGINS" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( htab_btsurfrd,
			"libandria4_bitsurface_read()", "vt100_action_HTAB" );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE( &funcname, sthtab_curbnds,
			"ERROR: vt100net_actionstool_execute() encountered a cursor bounds "
			"violation in case vt100_action_SETHTAB." );
		vt100net_actionstool_execute_BUILDERRSTRUCT( sthtab_btsurfwr,
			"libandria4_bitsurface_write()", "vt100_action_SETHTAB" );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE( &funcname, clrhtab_curbnds,
			"ERROR: vt100net_actionstool_execute() encountered a cursor bounds "
			"violation in case vt100_action_CLEARHTAB." );
		vt100net_actionstool_execute_BUILDERRSTRUCT( clrhtab_btsurfwr,
			"libandria4_bitsurface_write()", "vt100_action_CLEARHTAB" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( st_chrsz11_btarrwr,
			"libandria4_bitarray_write()", "vt100_action_SET_CHARSIZE1W1H" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( st_chrsz21_clrchrs,
			"vt100net_actionstool_clearcharas()", "vt100_action_SET_CHARSIZE2W1H" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( st_chrsz21_btarrwr,
			"libandria4_bitarray_write()", "vt100_action_SET_CHARSIZE2W1H" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( st_chrsz22_clrchrs,
			"vt100net_actionstool_clearcharas()", "vt100_action_SET_CHARSIZE2W2H" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( st_chrsz22_btarrwr,
			"libandria4_bitarray_write()", "vt100_action_SET_CHARSIZE2W2H" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( ers_nlin_clrchrs,
			"vt100net_actionstool_clearcharas()", "vt100_action_ERASE_INLINE" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( ers_nscrn_clrchrs,
			"vt100net_actionstool_clearcharas()", "vt100_action_ERASE_INSCREEN" );
		vt100net_actionstool_execute_BUILDERRSTRUCT( st_grphrend_sgr,
			"vt100net_actionstool_SGR()", "vt100_action_SET_GRAPHICRENDITION" );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE( &funcname, vt100scrcalib_uninitvars,
			"ERROR: vt100net_actionstool_execute() encountered uninitialized "
			"variables in case vt100_action_VT100SCRNCALIB." );
		vt100net_actionstool_execute_BUILDERRSTRUCT( vt100scrcalib_indr_stcll,
			"term_ctx->buffer.funcs->setcell()", "vt100_action_VT100SCRNCALIB" );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE( &funcname, unknowncase,
			"ERROR: vt100net_actionstool_execute() encountered an unknown case." );
		
		switch( action )
		{
	        case vt100_action_INVALID:
				VT100NET_REPORT_ERR( term_ctx, &( invalidcase.type.typeid ), __FILE__, __LINE__ );
				break;
	        case vt100_action_NOACTION:
					/* NOOP. */
				break;
	        case vt100_action_FULLRESET:
					/* Reset the entire known part of the terminal. May need the */
					/*  caller to also call OTHER code for features that this */
					/*  section doesn't know of. */
					/* This is often triggered by <ESC>"c". */
				???
				
				break;
			case vt100_action_RESET_MODE:
				{
					size_t iter = 0;
					if( iter )
					{
							/* Default is "ignore", so ignore. */
						if( !( term_ctx->params[ iter ] & ( 1 << 15 ) ) )
						{
							if( term_ctx->params[ iter ] == '?' )
							{
								/* Private modes. */
								
								++iter;
								
								if( iter < term_ctx->param_count )
								{
									switch( term_ctx->params[ iter ] )
									{
										case '6': /* DECOM – Origin Mode */
											/* When reset causes the origin to be at the */
											/*  upper-left position OF THE SCREEN. Line & column numbers become */
											/*  relative to the screen instead of the margins, with the origin */
											/*  still being numbered (1,1). Cursor CAN be positioned outside the */
											/*  margins via CUP and/or HVP control sequences, and will be moved */
											/*  to the new home position. */
											
											term_ctx->vt100_flags &= ~( vt100net_termcontext_vt100flags_originmode );
											
											if( vt100net_actionstool_cursorhome( term_ctx ) )
											{
												VT100NET_REPORT_ERR( term_ctx, &( rst_md_crhm.type.typeid ), __FILE__, __LINE__ );
											}
											
											break;
										case '4': /* DECSCLM: smooth-scroll, a no-op. */
											term_ctx->vt100_flags &= ~( vt100net_termcontext_vt100flags_smoothscrollmode );
											break;
										case '9': /* DECINLM: interlaced screen, a no-op. */
											term_ctx->vt100_flags &= ~( vt100net_termcontext_vt100flags_interlacemode );
											break;
										case '5': /* DECSCNM: swaps foreground & background colors for the entire screen. */
											term_ctx->vt100_flags &= ~( vt100net_termcontext_vt100flags_screeninversionmode );
											break;
										case '7': /* DECAWM: allows auto-wraping to next line. */
											term_ctx->vt100_flags &= ~( vt100net_termcontext_vt100flags_autowrapmode );
											break;
										default:
											/* If we don't know it, just ignore it. */
											break;
									}
								}
								
								/* End of private modes. */
								
							} else {
								
								/* Standard modes. */
								
								???
								
								/* End of standard modes. */
							}
						}
					}
				}
				break;
			case vt100_action_SET_MODE:
				{
					size_t iter = 0;
					if( iter )
					{
							/* Default is "ignore", so ignore. */
						if( !( term_ctx->params[ iter ] & ( 1 << 15 ) ) )
						{
							if( term_ctx->params[ iter ] == '?' )
							{
								/* Private modes. */
								
								++iter;
								
								if( iter < term_ctx->param_count )
								{
									switch( term_ctx->params[ iter ] )
									{
										case '6': /* DECOM – Origin Mode */
											/* When set causes the origin to be at the */
											/*  upper-left position INSIDE the margins. Line & column numbers */
											/*  become relative to the current margin settings, with the origin */
											/*  still being numbered (1,1). Cursor CANNOT by positioned outside */
											/*  the margins, and will be moved to the new home position. */
											
											term_ctx->vt100_flags |= vt100net_termcontext_vt100flags_originmode;
											
											if( vt100net_actionstool_cursorhome( term_ctx ) )
											{
												VT100NET_REPORT_ERR( term_ctx, &( st_md_crhm.type.typeid ), __FILE__, __LINE__ );
											}
											
											break;
										case '4': /* DECSCLM: smooth-scroll, a no-op. */
											term_ctx->vt100_flags |= vt100net_termcontext_vt100flags_smoothscrollmode;
											break;
										case '9': /* DECINLM: interlaced screen, a no-op. */
											term_ctx->vt100_flags |= vt100net_termcontext_vt100flags_interlacemode;
											break;
										case '5': /* DECSCNM: swaps foreground & background colors for the entire screen. */
											term_ctx->vt100_flags |= vt100net_termcontext_vt100flags_screeninversionmode;
											break;
										case '7': /* DECAWM: allows auto-wraping to next line. */
											term_ctx->vt100_flags |= vt100net_termcontext_vt100flags_autowrapmode;
											break;
										default:
											/* If we don't know it, just ignore it. */
											break;
									}
								}
								
								/* End of private modes. */
								
							} else {
								
								/* Standard modes. */
								
								???
								
								/* End of standard modes. */
							}
						}
					}
				}
				break;
			case vt100_action_SENDRESP:
					/* We blindly set this, because that's probably all we need. */
					/* TODO: Confirm that a binary setting is enough. */
				term_ctx->owner_flags |= vt100net_termcontext_flags2_responseneeded;
				break;
	        case vt100_action_ALERTUSER:
				res = term_ctx->buffer->vtab->alertuser( term_ctx->buffer );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( badalert.type.typeid ), __FILE__, __LINE__ );
				}
				break;
	        case vt100_action_SETCURPOS:
				params[ 0 ] = ( params[ 0 ] & ( 1 << 15 ) && param_count > 0 ? params[ 0 ] : 1 );
				params[ 1 ] = ( params[ 1 ] & ( 1 << 15 ) && param_count > 1 ? params[ 1 ] : 1 );
				
					/* Origin is (1,1), not (0,0). */
				term_ctx->cursor.x = params[ 1 ];
				term_ctx->cursor.y = params[ 0 ];
				
				if( !vt100net_actionstool_cursorclamp( term_ctx ) )
				{
					VT100NET_REPORT_ERR( term_ctx, &( scurpos_crclmp.type.typeid ), __FILE__, __LINE__ );
				}
				
				break;
			case vt100_action_SAVE_CURSORADJACENCIES:
				term_ctx->vt100_curssaves.cursor = term_ctx->cursor;
				term_ctx->vt100_curssaves.graphrend.fore = term_ctx->buffer_flags.fore;
				term_ctx->vt100_curssaves.graphrend.back = term_ctx->buffer_flags.back;
				term_ctx->vt100_curssaves.graphrend.style = term_ctx->buffer_flags.style;
				term_ctx->vt100_curssaves.graphrend.chara =
					term_ctx->buffer_flags.chara &
					libandria4_buffercell_common_chara_FONT_mask;
				term_ctx->vt100_curssaves.charhooks = term_ctx->type_tests;
				
				break;
			case vt100_action_RESTORE_CURSORADJACENCIES:
				term_ctx->cursor = term_ctx->vt100_curssaves.cursor;
				term_ctx->buffer_flags.fore = term_ctx->vt100_curssaves.graphrend.fore;
				term_ctx->buffer_flags.back = term_ctx->vt100_curssaves.graphrend.back;
				term_ctx->buffer_flags.style = term_ctx->vt100_curssaves.graphrend.style;
				term_ctx->buffer_flags.chara &= ~( libandria4_buffercell_common_chara_FONT_mask );
				term_ctx->buffer_flags.chara |=
					term_ctx->vt100_curssaves.graphrend.chara &
					libandria4_buffercell_common_chara_FONT_mask;
				term_ctx->type_tests = term_ctx->vt100_curssaves.charhooks;
				
				if( !vt100net_actionstool_cursorclamp( term_ctx ) )
				{
					VT100NET_REPORT_ERR( term_ctx, &( rstr_cradj_crclmp.type.typeid ), __FILE__, __LINE__ );
				}
				
				break;
			case vt100_action_LEFTWARD_WRAPLESS:
				params[ 0 ] = ( params[ 0 ] & ( 1 << 15 ) && param_count > 0 ? params[ 0 ] : 1 );
				while( params[ 0 ] )
				{
					res = vt100net_actionstool_columnleft( term_ctx,  0 );
					if( res < 0 )
					{
						VT100NET_REPORT_ERR( term_ctx, &( lw_wless_badcl.type.typeid ), __FILE__, __LINE__ );
					}
					
					--( params[ 0 ] );
				}
				break;
	        case vt100_action_UPWARD_WRAPLESS:
				params[ 0 ] = ( params[ 0 ] & ( 1 << 15 ) && param_count > 0 ? params[ 0 ] : 1 );
				while( params[ 0 ] )
				{
					res = vt100net_actionstool_lineup( term_ctx,  0 );
					if( res < 0 )
					{
						VT100NET_REPORT_ERR( term_ctx, &( lw_wless_badcl.type.typeid ), __FILE__, __LINE__ );
					}
					
					--( params[ 0 ] );
				}
				break;
	        case vt100_action_RIGHTWARD_WRAPLESS:
				params[ 0 ] = ( params[ 0 ] & ( 1 << 15 ) && param_count > 0 ? params[ 0 ] : 1 );
				while( params[ 0 ] )
				{
					res = vt100net_actionstool_columnright( term_ctx,  0 );
					if( res < 0 )
					{
						VT100NET_REPORT_ERR( term_ctx, &( lw_wless_badcl.type.typeid ), __FILE__, __LINE__ );
					}
					
					--( params[ 0 ] );
				}
				break;
	        case vt100_action_DOWNWARD_WRAPLESS:
				params[ 0 ] = ( params[ 0 ] & ( 1 << 15 ) && param_count > 0 ? params[ 0 ] : 1 );
				while( params[ 0 ] )
				{
					res = vt100net_actionstool_linedown( term_ctx,  0 );
					if( res < 0 )
					{
						VT100NET_REPORT_ERR( term_ctx, &( lw_wless_badcl.type.typeid ), __FILE__, __LINE__ );
					}
					
					--( params[ 0 ] );
				}
				break;
	        case vt100_action_UPWARD_SCROLLING:
				params[ 0 ] = ( params[ 0 ] & ( 1 << 15 ) && param_count > 0 ? params[ 0 ] : 1 );
				while( params[ 0 ] )
				{
					res = vt100net_actionstool_lineup( term_ctx,  1 );
					if( res < 0 )
					{
						VT100NET_REPORT_ERR( term_ctx, &( lw_wless_badcl.type.typeid ), __FILE__, __LINE__ );
					}
					
					--( params[ 0 ] );
				}
				break;
	        case vt100_action_DOWNWARD_SCROLLING:
				params[ 0 ] = ( params[ 0 ] & ( 1 << 15 ) && param_count > 0 ? params[ 0 ] : 1 );
				while( params[ 0 ] )
				{
					res = vt100net_actionstool_linedown( term_ctx,  1 );
					if( res < 0 )
					{
						VT100NET_REPORT_ERR( term_ctx, &( lw_wless_badcl.type.typeid ), __FILE__, __LINE__ );
					}
					
					--( params[ 0 ] );
				}
				break;
			case vt100_action_SET_VERTICALMARGINS:
					/* Check for defaulting. */
				params[ 0 ] =
					(
						params[ 0 ] & ( 1 << 15 ) && param_count > 0 ?
							params[ 0 ] :
							1
					);
				params[ 1 ] =
					(
						params[ 1 ] & ( 1 << 15 ) && param_count > 1 ?
							params[ 1 ] :
							term_ctx->dimensions.y
					);
					/* Constrain to bounds. */
				params[ 0 ] =
					(
						params[ 0 ] >= term_ctx->dimensions.y ?
							term_ctx->dimensions.y :
							params[ 0 ]
					);
				params[ 1 ] =
					(
						params[ 1 ] >= term_ctx->dimensions.y ?
							term_ctx->dimensions.y :
							params[ 1 ]
					);
						/* Constrain to ordering. */
				params[ 0 ] = ( params[ 0 ] > params[ 1 ] ? params[ 1 ] : params[ 0 ] );
					/* Constrain to spacing. */
				if( params[ 0 ] == params[ 1 ] )
				{
					if( params[ 1 ] > 1 )
					{
						params[ 0 ] -= 1;
						
					} else {
						
						params[ 1 ] += 1;
					}
				}
				
					/* Set scrolling region. */
				term_ctx->scrolling_region.top = params[ 0 ];
				term_ctx->scrolling_region.bottom = params[ 1 ];
				
					/* Move the cursor to the home position. */
				if( vt100net_actionstool_cursorhome( term_ctx ) )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_vrtmrgns_crhm.type.typeid ), __FILE__, __LINE__ );
				}
				
				break;
	        case vt100_action_HTAB:
				/* Seek out the next set tab stop, or the end of the */
				/*  current line, whichever comes first. The tabs are */
				/*  set with a seperate command (which we don't have */
				/*  an entry for yet). */
				{
					size_t iter = term_ctx->cursor.x + 1;
					int res = libandria4_bitsurface_read( term_ctx->htabstops, iter, term_ctx->cursor.y );
					if( res < 0 )
					{
						VT100NET_REPORT_ERR( term_ctx, &( htab_btsurfrd.type.typeid ), __FILE__, __LINE__ );
						return( -2 );
					}
					while( iter < term_ctx->dimensions.width && !res )
					{
						res = libandria4_bitsurface_read( term_ctx->htabstops, iter, term_ctx->cursor.y );
						if( res < 0 )
						{
							VT100NET_REPORT_ERR( term_ctx, &( htab_btsurfrd.type.typeid ), __FILE__, __LINE__ );
							return( -2 );
						}
						
						++iter;
					}
					
					term_ctx->cursor.x = iter;
						/* Placeholder for clamping the range of "x" to only actual terminal columns. */
					if( 0 )
					{
						term_ctx->cursor.x -= 1;
					}
				}
				break;
	        case vt100_action_SETHTAB:
				{
					if
					(
						term_ctx->->cursor.x >= term_ctx->dimensions.width ||
						term_ctx->cursor.y >= term_ctx->dimensions.height
					)
					{
						VT100NET_REPORT_ERR( term_ctx, &( sthtab_curbnds.type.typeid ), __FILE__, __LINE__ );
						return( -2 );
					}
					int res = libandria4_bitsurface_write( term_ctx->htabstops, term_ctx->->cursor.x, term_ctx->cursor.y,  1 );
					if( res < 0 )
					{
						VT100NET_REPORT_ERR( term_ctx, &( sthtab_btsurfwr.type.typeid ), __FILE__, __LINE__ );
						return( -2 );
					}
				}
				break;
	        case vt100_action_CLEARHTAB:
				{
					if
					(
						term_ctx->->cursor.x >= term_ctx->dimensions.width ||
						term_ctx->cursor.y >= term_ctx->dimensions.height
					)
					{
						VT100NET_REPORT_ERR( term_ctx, &( clrhtab_curbnds.type.typeid ), __FILE__, __LINE__ );
						return( -2 );
					}
					int res;
					switch( params[ 0 ] == 0 )
					{
						case 0:
							res = libandria4_bitsurface_write( term_ctx->htabstops, term_ctx->->cursor.x, term_ctx->cursor.y,  0 );
							if( res < 0 )
							{
								VT100NET_REPORT_ERR( term_ctx, &( clrhtab_btsurfwr.type.typeid ), __FILE__, __LINE__ );
								return( -2 );
							}
							break;
						case 3:
							??? /* Clear ALL tabs, not just one at the current position. */ ;
							break;
						default:
							/* We do nothing, and instead just ignore the request. */ ;
							break;
						
					}
				}
				break;
			case vt100_action_LINEFEED:
				/* Standard newline, moves to home position of next line. */
				res = vt100net_actionstool_linedown( term_ctx,  1 );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( lf_badld.type.typeid ), __FILE__, __LINE__ );
				}
				res = vt100net_actionstool_columnhome( term_ctx,  1 ); /* TODO: That 1 should probably be a 0. */
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( lf_badch.type.typeid ), __FILE__, __LINE__ );
				}
				break;
	        case vt100_action_FULLLEFTWARD_WRAPLESS: /* Carraige return. */
				res = vt100net_actionstool_columnhome( term_ctx,  1 ); /* TODO: That 1 should probably be a 0. */
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( flw_wless_badch.type.typeid ), __FILE__, __LINE__ );
				}
				break;
	        case vt100_action_FONTSWAP0_LOCKING:
				term_ctx->buffer_flags.chara =
					( term_ctx->buffer_flags.chara & ~libandria4_buffercell_common_chara_FONT_mask ) |
					( 0 << libandria4_buffercell_common_chara_FONT_offset );
				break;
	        case vt100_action_FONTSWAP1_LOCKING:
				term_ctx->buffer_flags.chara =
					( term_ctx->buffer_flags.chara & ~libandria4_buffercell_common_chara_FONT_mask ) |
					( 1 << libandria4_buffercell_common_chara_FONT_offset );
				break;
			case vt100_action_SET_CHARACTERSET:
				{
					libandria4_text_charsettranslators_fptr **desta = 0, **destb = 0, *vala = 0, *valb = 0;
					
					switch
					(
						term_ctx->sequence_dispatch.final_character &
						libandria4_buffercell_common_chara_UNICODEVALID_mask
					)
					{
						case 0x41: /* ESC x A */
							vala = &libandria4_text_charsettranslators_vt100uk_to_unicode;
							valb = &libandria4_text_charsettranslators_unicode_to_vt100uk;
							break;
						case 0x42: /* ESC x B */
						case 0x31: /* ESC x 1 */ /* Alternate characters */
						case 0x32: /* ESC x 2 */ /* Alternate spec. graphics */
							vala = &libandria4_text_charsettranslators_strict_ascii_to_unicode;
							valb = &libandria4_text_charsettranslators_strict_unicode_to_ascii;
							break;
						case 0x30: /* ESC x 0 */
								/* Special graphics. */
							vala = &libandria4_text_charsettranslators_vt100specgraph_to_unicode;
							valb = &libandria4_text_charsettranslators_unicode_to_vt100specgraph_lossless;
							break;
						default:
							???;
							break;
					}
					switch
					(
						term_ctx->sequence_dispatch.intermediates[ 0 ] &
						libandria4_buffercell_common_chara_UNICODEVALID_mask
					)
					{
						case 0x28: /* ESC ( x */
							desta = &( term_ctx->type_tests.input1 );
							destb = &( term_ctx->type_tests.output1 );
							break;
						case 0x29: /* ESC ) x */
							desta = &( term_ctx->type_tests.input2 );
							destb = &( term_ctx->type_tests.output2 );
							break;
						default:
							???;
							break;
					}

					if( desta && vala && term_ctx->interm_count > 0 )
					{
						*desta = vala;
							/* Should this even be done? */
						*destb = valb;
					}
				}
				break;
	        case vt100_action_SET_CHARSIZE1W1H:
					/* Clear width. */
				res = libandria4_bitarray_write( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 0,  0 );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz11_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
					/* Clear height. */
				res = libandria4_bitarray_write( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 1,  0 );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz11_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
				res = libandria4_bitarray_write( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 2,  0 );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz11_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
				break;
			case vt100_action_SET_CHARSIZE2W1H:
				res = libandria4_bitarray_read( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 0 );
				if( res == 0 )
				{
						/* Clear the right half of the line (should be affected by SPD). */
					res = vt100net_actionstool_clearcharas
						(
							term_ctx,
							term_ctx->cursor.y,
								( term_ctx->cursor.x - ( term_ctx->cursor.x & 1 ) ) / 2 + ( term_ctx->cursor.x & 1 ),
								term_ctx.dimensions.x,
							(uint32_t)' ' /* Fill with spaces. */
						);
					if( !res )
					{
						VT100NET_REPORT_ERR( term_ctx, &( st_chrsz21_clrchrs.type.typeid ), __FILE__, __LINE__ );
						/* I don't think we need to return in this case? */
					}
					
					/* Adjust cursor position to remain over same character: if the */
					/*  character is off screen, move cursor to the right margin. */
					/* Note: we're going to assume that only margin corrections are */
					/*  needed. */
					if( term_ctx->cursor.x * 2 >= term_ctx.dimensions.x )
					{
						term_ctx.cursor.x =
							(
								term_ctx.dimensions.x -
								( term_ctx.dimensions.x & 1 )
							) / 2;
					}
				}
					/* Clear width. */
				res = libandria4_bitarray_write( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 0,  1 );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz21_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
					/* Clear height. */
				res = libandria4_bitarray_write( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 1,  0 );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz21_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
				res = libandria4_bitarray_write( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 2,  0 );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz21_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
				break;
			case vt100_action_SET_CHARSIZE2W2H:
				/* TODO: Verify that 2-wide goes with 2-hgh. The info seems inconsistent. */
				res = libandria4_bitarray_read( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 0 );
				if( res == 0 )
				{
					/* It is the user's obligation to use this correctly: both lines */
					/*  should be adjacent, correctly ordered, and contain identical */
					/*  data. These two escape codes only do the proper line clear & */
					/*  graphic changes. */
					
						/* Clear the right half of the line (should be affected by SPD). */
					res = vt100net_actionstool_clearcharas
						(
							term_ctx,
							term_ctx->cursor.y,
								( term_ctx->cursor.x - ( term_ctx->cursor.x & 1 ) ) / 2 + ( term_ctx->cursor.x & 1 ),
								term_ctx.dimensions.x,
							(uint32_t)' ' /* Fill with spaces. */
						);
					if( !res )
					{
						VT100NET_REPORT_ERR( term_ctx, &( st_chrsz22_clrchrs.type.typeid ), __FILE__, __LINE__ );
					}
					
					/* Adjust cursor position to remain over same character: if the */
					/*  character is off screen, move cursor to the right margin. */
					/* Note: we're going to assume that only margin corrections are */
					/*  needed. */
					if( term_ctx->cursor.x * 2 >= term_ctx.dimensions.x )
					{
						term_ctx.cursor.x =
							(
								term_ctx.dimensions.x -
								( term_ctx.dimensions.x & 1 )
							) / 2;
					}
				}
					/* Set width. */
				res = libandria4_bitarray_write( term_ctx->charasize, ( term_ctx->cursor.y ) * 4 + 0,  1 );
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz22_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
						/* Lower line. */
				res =
					libandria4_bitarray_write
					(
						term_ctx->charasize,
						( term_ctx->cursor.y ) * 4 + 1,
						(
							term_ctx->sequence_dispatch.final_character &
							libandria4_buffercell_common_chara_UNICODEVALID_mask
						) == '4' ? 1 : 0
					);
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz22_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
						/* Upper line. */
				res =
					libandria4_bitarray_write
					(
						term_ctx->charasize,
						( term_ctx->cursor.y ) * 4 + ,
						(
							term_ctx->sequence_dispatch.final_character &
							libandria4_buffercell_common_chara_UNICODEVALID_mask
						) == '3' ? 1 : 0
					);
				if( res < 0 )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_chrsz22_btarrwr.type.typeid ), __FILE__, __LINE__ );
					return( -2 );
				}
				break;
			case vt100_action_ERASE_INLINE:
				{
					uint32_t start, end;
					
					switch( ( term_ctx->param_count ? term_ctx->params[ 0 ] : -1 ) )
					{
						case 2:
							start = 1;
							end = term_ctx.dimensions.x;
							break;
						case 1:
							start = 1;
							end = term_ctx->cursor.x;
							break;
						case 0:
						default:
							start = term_ctx->cursor.x;
							end = term_ctx.dimensions.x;
							break;
					}
					
					/* Clear the relevant bit of the line. */
					res = vt100net_actionstool_clearcharas
						(
							term_ctx,
							term_ctx->cursor.y, start, end,
							(uint32_t)' ' /* Fill with spaces. */
						);
					if( !res )
					{
						VT100NET_REPORT_ERR( term_ctx, &( ers_nlin_clrchrs.type.typeid ), __FILE__, __LINE__ );
					}
				}
				break;
			case vt100_action_ERASE_INSCREEN:
				{
					uint32_t start, end, top, bottom;
					
					switch( term_ctx->param_count ? term_ctx->params[ 0 ] : -1 )
					{
						case 2:
							start = 1;
							end = term_ctx.dimensions.x;
							top = 1;
							bottom = term_ctx.dimensions.y;
							break;
						case 1:
							start = 1;
							end = term_ctx->cursor.x;
							top = 1;
							bottom = term_ctx->cursor.y;
							
								/* Preclear the last line for a simpler algorithm later. */
							res = vt100net_actionstool_clearcharas
								(
									term_ctx,
									bottom, start, end,
									(uint32_t)' ' /* Fill with spaces. */
								);
							if( !res )
							{
								VT100NET_REPORT_ERR( term_ctx, &( ers_nscrn_clrchrs.type.typeid ), __FILE__, __LINE__ );
								/* This isn't good, but we might as well just continue. */
							}
							--bottom;
							end = term_ctx.dimensions.x;
							
							break;
						case 0:
						default:
							start = term_ctx->cursor.x;
							end = term_ctx.dimensions.x;
							top = term_ctx->cursor.y;
							bottom = term_ctx->cursor.y;
							break;
					}
					
						/* Clear over the rest of the lines that need to be cleared. */
					while( top <= bottom )
					{
						res = vt100net_actionstool_clearcharas
							(
								term_ctx,
								top, start, end,
								(uint32_t)' ' /* Fill with spaces. */
							);
						if( !res )
						{
							VT100NET_REPORT_ERR( term_ctx, &( ers_nscrn_clrchrs.type.typeid ), __FILE__, __LINE__ );
							/* This isn't good, but we might as well just continue. */
						}
						
						++top;
						start = 1;
						end = term_ctx.dimensions.x;
					}
				}
				break;
			case vt100_action_SET_GRAPHICRENDITION:
				res = vt100net_actionstool_SGR( term_ctx );
				if( !res )
				{
					VT100NET_REPORT_ERR( term_ctx, &( st_grphrend_sgr.type.typeid ), __FILE__, __LINE__ );
				}
				break;
			case vt100_action_RESUMETRANSMISSION:
					/* This should be all we need. */
					/* TODO: Confirm that just setting this is enough. */
				term_ctx->owner_flags |= vt100net_termcontext_flags2_allowbacktalk;
				break;
	        case vt100_action_PAUSETRANSMISSION:
					/* This should be all we need. */
					/* TODO: Confirm that just setting this is enough. */
				term_ctx->owner_flags ^=
					( term_ctx->owner_flags ) &
					vt100net_termcontext_flags2_allowbacktalk;
				break;
				/* Note: this probably shouldn't actually happen? */
				/*  Though the error char is meant to be printed. */
	        case vt100_action_TERMINATESEQUENCE:
				???
				break;
			case vt100_action_VT100SCRNCALIB:
				/* This literally just fills the screen with capital 'E' characters. */
				/*  The VT100 used it for screen calibration, some test suites look */
				/*  for it, and there's little real reason to do without. */
				/* Besides, it may someday be useful. */
				{
					libandria4_buffercell_common chara = term_ctx->buffer_flags;
					chara.chara = 'E';
					size_t x = 0, y = 0;
					while( y < term_ctx->dimensions.y )
					{
						while( x < term_ctx->dimensions.x )
						{
							if( !( term_ctx->buffer ) )
							{
								VT100NET_REPORT_ERR(
										term_ctx,
											&( vt100scrcalib_uninitvars.type.typeid ),
											__FILE__,
											__LINE__
									);
								return( -2 );
							}
							if( !( term_ctx->buffer.funcs ) )
							{
								VT100NET_REPORT_ERR(
										term_ctx,
											&( vt100scrcalib_uninitvars.type.typeid ),
											__FILE__,
											__LINE__
									);
								return( -2 );
							}
							if( !( term_ctx->buffer.funcs->setcell ) )
							{
								VT100NET_REPORT_ERR(
										term_ctx,
											&( vt100scrcalib_uninitvars.type.typeid ),
											__FILE__,
											__LINE__
									);
								return( -2 );
							}
							res = term_ctx->buffer.funcs->setcell
								(
									term_ctx->buffer,
									x, y,
									chara
								);
							if( res < 1 )
							{
								VT100NET_REPORT_ERR(
										term_ctx,
											&( vt100scrcalib_indr_stcll.type.typeid ),
											__FILE__,
											__LINE__
									);
								return( -2 );
							}
							
							++x;
						}
						
						++y;
					}
				}
				
				break;
			default:
				VT100NET_REPORT_ERR(
						term_ctx,
						&( unknowncase.type.typeid ),
						__FILE__,
						__LINE__
					);
				break;
		}

		return( 1 );
	}

	VT100NET_REPORT_ERR( term_ctx, &( badargs.type.typeid ), __FILE__, __LINE__ );
	return( -1 );
}





/********************/
/********************/
/** Just wrappers: **/
/********************/
/********************/

/* Convenience wrappers. */
int vt100net_actionstool_lineup
(
	vt100net_termcontext *term_ctx,
	int force
)
{
	if( term_ctx )
	{
			/* Note: VERY WRONG. The ACTUAL direction should depend on SPD, */
			/*  and thus be configurable. Still, this will do for now. */
		return
		(
			vt100net_actionstool_itercursor
			(
				term_ctx,
				
				vt100net_actionstool_calcdir( term_ctx, libandria4_termbuffer_directions_up ),
				force
			)
		);
	}

	return( -1 );
}
int vt100net_actionstool_columnright
(
	vt100net_termcontext *term_ctx,
	int force
)
{
	if( term_ctx )
	{
			/* Note: VERY WRONG. The ACTUAL direction should depend on SPD, */
			/*  and thus be configurable. Still, this will do for now. */
		return
		(
			vt100net_actionstool_itercursor
			(
				term_ctx,
				
				vt100net_actionstool_calcdir( term_ctx, libandria4_termbuffer_directions_right ),
				force
			)
		);
	}

	return( -1 );
}
int vt100net_actionstool_linedown
(
	vt100net_termcontext *term_ctx,
	int force
)
{
	if( term_ctx )
	{
			/* Note: VERY WRONG. The ACTUAL direction should depend on SPD, */
			/*  and thus be configurable. Still, this will do for now. */
			/* Note to self: doesn't adding *_calcdir() obsolete the comment above? */
		return
		(
			vt100net_actionstool_itercursor
			(
				term_ctx,
				
				vt100net_actionstool_calcdir( term_ctx, libandria4_termbuffer_directions_down ),
				force
			)
		);
	}

	return( -1 );
}
int vt100net_actionstool_columnleft
(
	vt100net_termcontext *term_ctx,
	int force
)
{
	if( term_ctx )
	{
			/* Note: VERY WRONG. The ACTUAL direction should depend on SPD, */
			/*  and thus be configurable. Still, this will do for now. */
		return
		(
			vt100net_actionstool_itercursor
			(
				term_ctx,
				
				vt100net_actionstool_calcdir( term_ctx, libandria4_termbuffer_directions_left ),
				force
			)
		);
	}

	return( -1 );
}
int vt100net_actionstool_columnhome
(
	vt100net_termcontext *term_ctx,
	int force
)
{
	if( term_ctx )
	{
			/* Note: VERY WRONG. The ACTUAL direction should depend on SPD, */
			/*  and thus be configurable. Still, this will do for now. */
			/* Note: calcdir() probably obsoletes the above message, but */
			/*  also probably needs special handling for *_isCR. */
		return
		(
			vt100net_actionstool_itercursor
			(
				term_ctx,
				libandria4_termbuffer_directions_isCR, force
			)
		);
	}

	return( -1 );
}
