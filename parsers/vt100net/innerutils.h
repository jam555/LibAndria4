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

#ifndef LIBANDRIA4_PARSERS_VT100NET_INNERUTILS_H
# define LIBANDRIA4_PARSERS_VT100NET_INNERUTILS_H
	
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
	int vt100net_actionstool_SGR
	(
		vt100net_termcontext *term_ctx,
		uint16_t *params, size_t param_count
	);
	
	
	
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
	
	
	
	/* Note: this DOES NOT currently consider SPD. */
	
	int vt100net_actionstool_columnhome
	(
		vt100net_termcontext *term_ctx,
		int force
	);
	
		/* Moves the cursor to wherever the current origin is. Affected by DEC Origin Mode and SPD. */
	int vt100net_actionstool_cursorhome( vt100net_termcontext *term_ctx );
		/* Restricts cursor location to currently legal values. */
	int vt100net_actionstool_cursorclamp( vt100net_termcontext *term_ctx );
	
#endif
/* End libandria4 parsers vt100net innerutils.h */
