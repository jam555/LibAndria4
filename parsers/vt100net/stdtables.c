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

#include "stdtables.h"



/***************************************************************/
/***************************************************************/
/** TODO: Fix up the C1 mappings of the various tables below! **/
/***************************************************************/
/***************************************************************/

/* At the bottom of this area is a listing of C1 control characters. */
/* Various lookup tables go here. */
/* Note that "handlers" are all indexes into vt100net_handlers[ 16 ], */
/*  except for that array itself, which contains function pointers. */
/* Codes A0-FF are treated the same as 20-7F, but C0 & C1 aren't */
/*  treated the same. */

	/* A set of handler & destination pairs. Note that "invalid" */
	/*  destinations mean "stay here". */
vt100net_handler_mapping vt100net_handler_mappingset[ 29 ] =
	{
			/* 0 */
		{ vt100net_HAND_BLANK, vt100net_termcontext_INVALID },
			/* Was fromAnywhere_INVALID, use as "do nothing". */
		
			/* 1 */
		{ vt100net_HAND_EXEC, vt100net_termcontext_GROUND }, /* Was fromAnywhere_EXECGND. */
		{ vt100net_HAND_NULLACT, vt100net_termcontext_GROUND },
		{ vt100net_HAND_NULLACT, vt100net_termcontext_ESCAPE },
		{ vt100net_HAND_NULLACT, vt100net_termcontext_DCS_ENTRY },
		{ vt100net_HAND_NULLACT, vt100net_termcontext_SOS_PMAC_APC__STRING },
		
			/* 6 */
		{ vt100net_HAND_NULLACT, vt100net_termcontext_CSI_ENTRY },
		{ vt100net_HAND_NULLACT, vt100net_termcontext_OSC_STRING },
		{ vt100net_HAND_NULLACT, vt100net_termcontext_SOS_PMAC_APC__STRING },
		{ vt100net_HAND_PRINT, vt100net_termcontext_INVALID },
		{ vt100net_HAND_IGN, vt100net_termcontext_INVALID },
		
			/* 11 */
		{ vt100net_HAND_COLL, vt100net_termcontext_ESCAPE_INTERMEDIATE },
		{ vt100net_HAND_ESCDISP, vt100net_termcontext_GROUND },
		{ vt100net_HAND_EXEC, vt100net_termcontext_INVALID },
		{ vt100net_HAND_COLL, vt100net_termcontext_INVALID },
		{ vt100net_HAND_COLL, vt100net_termcontext_CSI_INTERMEDIATE },
		
			/* 16 */
		{ vt100net_HAND_PARAM, vt100net_termcontext_CSI_PARAM },
		{ vt100net_HAND_NULLACT, vt100net_termcontext_CSI_IGNORE },
		{ vt100net_HAND_COLL, vt100net_termcontext_CSI_PARAM },
		{ vt100net_HAND_CSIDISP, vt100net_termcontext_GROUND },
		{ vt100net_HAND_PARAM, vt100net_termcontext_INVALID },
		
			/* 21 */
		{ vt100net_HAND_COLL, vt100net_termcontext_DCS_INTERMEDIATE },
		{ vt100net_HAND_NULLACT, vt100net_termcontext_DCS_IGNORE },
		{ vt100net_HAND_PARAM, vt100net_termcontext_DCS_PARAM },
		{ vt100net_HAND_COLL, vt100net_termcontext_DCS_PARAM },
		{ vt100net_HAND_NULLACT, vt100net_termcontext_DCS_PASSTHROUGH },
		
			/* 26 */
		{ vt100net_HAND_PUT, vt100net_termcontext_INVALID },
		{ vt100net_HAND_OSCPUT, vt100net_termcontext_INVALID },
		{ vt100net_HAND_FALLTHROUGH, vt100net_termcontext_INVALID }
		
		/* Next would be 29. */
	};

		/* Element values are indexes into vt100net_handler_mappingset[]. */
		/*  This table contains only entries that are common to ALL */
		/*  relevant states. */
uint8_t vt100net_fromAnywhere[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 16, 0x10 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		1, 0, 1, 3,   0, 0, 0, 0,
		
		
			/* [ 32, 0x20 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 48, 0x30 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
		
		
			/* [ 64, 0x40 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 80, 0x50 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
			/* [ 96, 0x60 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 112, 0x70 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
		
		
			/* [ 128, 0x80 ] */
		1, 1, 1, 1,   1, 1, 1, 1,
		1, 1, 1, 1,   1, 1, 1, 1,
		
			/* [ 144, 0x90 ] */
		4, 1, 1, 1,   1, 1, 1, 1,
		5, 1, 1, 6,   2, 7, 5, 5,
		
		
			/* [ 160, 0xA0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 176, 0xB0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
		
		
			/* [ 192, 0xC0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 208, 0xD0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
			/* [ 224, 0xE0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 240, 0xF0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0
		
		/* Next would be [ 256, 0x100 ] */
	};
	/* Mappings from state to handlers. */
uint8_t
	onEntry[ 14 ] =
		{
			vt100net_HAND_IGN, vt100net_HAND_CLEAR, vt100net_HAND_IGN, vt100net_HAND_CLEAR, vt100net_HAND_IGN,
			vt100net_HAND_IGN, vt100net_HAND_IGN, vt100net_HAND_CLEAR, vt100net_HAND_IGN, vt100net_HAND_IGN,
			vt100net_HAND_HOOK, vt100net_HAND_IGN, vt100net_HAND_OSCSTRT, vt100net_HAND_IGN
		},
	onExit[ 14 ] =
		{
			vt100net_HAND_IGN, vt100net_HAND_IGN, vt100net_HAND_IGN, vt100net_HAND_IGN, vt100net_HAND_IGN,
			vt100net_HAND_IGN, vt100net_HAND_IGN, vt100net_HAND_IGN, vt100net_HAND_IGN, vt100net_HAND_IGN,
			vt100net_HAND_UNHOOK, vt100net_HAND_IGN, vt100net_HAND_OSCEND, vt100net_HAND_IGN
		};

	/* State-specific mappings of characters to */
	/*  vt100net_handler_mappingset[] entries. */
uint8_t
	fromGround[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		1, 1, 1, 1,   1, 1, 1, 1,
		1, 1, 1, 1,   1, 1, 1, 1,
			/* [ 16, 0x10 ] */
		1, 1, 1, 1,   1, 1, 1, 1,
		28, 1, 28, 28,   1, 1, 1, 1,
		
			/* [ 32, 0x20 ] */
			/* 0x20 needs a CONDITIONAL print. */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
			/* [ 48, 0x30 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
		
		
			/* [ 64, 0x40 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
			/* [ 80, 0x50 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
		
			/* [ 96, 0x60 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
			/* [ 112, 0x70 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
			/* 0x7F needs a CONDITIONAL print. */
		
		
		/* These 32 cases are the C1 control characters, */
		/*  and may need to be reconsidered in the future. */
			/* [ 128, 0x80 ] */
		0, 0, 0, 0,   1, 1, 1, 0,
		1, 1, 1, 1,   1, 1, 1, 1,
			/* [ 144, 0x90 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 160, 0xA0 ] */
			/* 0xA0 needs a CONDITIONAL print. */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
			/* [ 176, 0xB0 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
		
		
			/* [ 192, 0xC0 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
			/* [ 208, 0xD0 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
		
			/* [ 224, 0xE0 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9,
			/* [ 240, 0xF0 ] */
		9, 9, 9, 9,   9, 9, 9, 9,
		9, 9, 9, 9,   9, 9, 9, 9
			/* 0xFF needs a CONDITIONAL print. */
		
		/* Next would be [ 256, 0x100 ] */
	},
	fromEscape[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		1, 1, 1, 1,   1, 1, 1, 1,
		1, 1, 1, 1,   1, 1, 1, 1,
			/* [ 16, 0x10 ] */
		1, 1, 1, 1,   1, 1, 1, 1,
		28, 1, 28, 28,   1, 1, 1, 1,
		
			/* [ 32, 0x20 ] */
		11, 11, 11, 11,   11, 11, 11, 11,
		11, 11, 11, 11,   11, 11, 11, 11,
			/* [ 48, 0x30 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
		
		
			/* [ 64, 0x40 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
			/* [ 80, 0x50 ] */
		4, 12, 12, 12,   12, 12, 12, 12,
		5, 12, 12, 6,    12,  7,  5,  5,
		
			/* [ 96, 0x60 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
			/* [ 112, 0x70 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 3,
		
		/* In all cases shown here, codes A0‒FF (GR area) are */
		/*  treated identically to codes 20‒7F (GL area). This */
		/*  symmetry does not extend to the C0 and C1 areas. */
			/* [ 128, 0x80 ] */
		???
			/* [ 144, 0x90 ] */
		???
		/* Note: the codes below should be Unicode compatible. */
		
			/* [ 160, 0xA0 ] */
		11, 11, 11, 11,   11, 11, 11, 11,
		11, 11, 11, 11,   11, 11, 11, 11,
			/* [ 176, 0xB0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
		
		
			/* [ 192, 0xC0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
			/* [ 208, 0xD0 ] */
		4, 12, 12, 12,   12, 12, 12, 12,
		5, 12, 12, 6,    12,  7,  5,  5,
		
			/* [ 224, 0xE0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
			/* [ 240, 0xF0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 3
	},
	fromEscapeIntermediate[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		13, 13, 13, 13,   13, 13, 13, 13,
			/* [ 16, 0x10 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		28, 13, 28, 28,   13, 13, 13, 13,
		
			/* [ 32, 0x20 ] */
		14, 14, 14, 14,   14, 14, 14, 14,
		14, 14, 14, 14,   14, 14, 14, 14,
			/* [ 48, 0x30 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
		
		
			/* [ 64, 0x40 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
			/* [ 80, 0x50 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
		
			/* [ 96, 0x60 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
			/* [ 112, 0x70 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		
			/* [ 160, 0xA0 ] */
		14, 14, 14, 14,   14, 14, 14, 14,
		14, 14, 14, 14,   14, 14, 14, 14,
			/* [ 176, 0xB0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
		
		
			/* [ 192, 0xC0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
			/* [ 208, 0xD0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
		
			/* [ 224, 0xE0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 12,
			/* [ 240, 0xF0 ] */
		12, 12, 12, 12,   12, 12, 12, 12,
		12, 12, 12, 12,   12, 12, 12, 0
	},
	fromCsiEntry[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		13, 13, 13, 13,   13, 13, 13, 13,
			/* [ 16, 0x10 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		28, 13, 28, 28,   13, 13, 13, 13,
		
			/* [ 32, 0x20 ] */
		15, 15, 15, 15,   15, 15, 15, 15,
		15, 15, 15, 15,   15, 15, 15, 15,
			/* [ 48, 0x30 ] */
		16, 16, 16, 16,   16, 16, 16, 16,
		16, 16, 17, 16,   18, 18, 18, 18,
		
		
			/* [ 64, 0x40 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 80, 0x50 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
		
			/* [ 96, 0x60 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 112, 0x70 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		
			/* [ 160, 0xA0 ] */
		15, 15, 15, 15,   15, 15, 15, 15,
		15, 15, 15, 15,   15, 15, 15, 15,
			/* [ 176, 0xB0 ] */
		16, 16, 16, 16,   16, 16, 16, 16,
		16, 16, 17, 16,   18, 18, 18, 18,
		
		
			/* [ 192, 0xC0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 208, 0xD0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
		
			/* [ 224, 0xE0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 240, 0xF0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 0
	},
	fromCsiParam[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		13, 13, 13, 13,   13, 13, 13, 13,
			/* [ 16, 0x10 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		28, 13, 28, 28,   13, 13, 13, 13,
		
			/* [ 32, 0x20 ] */
		15, 15, 15, 15,   15, 15, 15, 15,
		15, 15, 15, 15,   15, 15, 15, 15,
			/* [ 48, 0x30 ] */
		20, 20, 20, 20,   20, 20, 20, 20,
		20, 20, 17, 20,   17, 17, 17, 17,
		
		
			/* [ 64, 0x40 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 80, 0x50 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
		
			/* [ 96, 0x60 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 112, 0x70 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		
			/* [ 160, 0xA0 ] */
		15, 15, 15, 15,   15, 15, 15, 15,
		15, 15, 15, 15,   15, 15, 15, 15,
			/* [ 176, 0xB0 ] */
		20, 20, 20, 20,   20, 20, 20, 20,
		20, 20, 17, 20,   17, 17, 17, 17,
		
		
			/* [ 192, 0xC0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 208, 0xD0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
		
			/* [ 224, 0xE0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 240, 0xF0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 0
	},
	fromCsiIntermediate[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		13, 13, 13, 13,   13, 13, 13, 13,
			/* [ 16, 0x10 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		28, 13, 28, 28,   13, 13, 13, 13,
		
			/* [ 32, 0x20 ] */
		14, 14, 14, 14,   14, 14, 14, 14,
		14, 14, 14, 14,   14, 14, 14, 14,
			/* [ 48, 0x30 ] */
		17, 17, 17, 17,   17, 17, 17, 17,
		17, 17, 17, 17,   17, 17, 17, 17,
		
		
			/* [ 64, 0x40 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 80, 0x50 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
		
			/* [ 96, 0x60 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 112, 0x70 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		
			/* [ 160, 0xA0 ] */
		14, 14, 14, 14,   14, 14, 14, 14,
		14, 14, 14, 14,   14, 14, 14, 14,
			/* [ 176, 0xB0 ] */
		17, 17, 17, 17,   17, 17, 17, 17,
		17, 17, 17, 17,   17, 17, 17, 17,
		
		
			/* [ 192, 0xC0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 208, 0xD0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
		
			/* [ 224, 0xE0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 19,
			/* [ 240, 0xF0 ] */
		19, 19, 19, 19,   19, 19, 19, 19,
		19, 19, 19, 19,   19, 19, 19, 0
	},
	fromCsiIgnore[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		13, 13, 13, 13,   13, 13, 13, 13,
			/* [ 16, 0x10 ] */
		13, 13, 13, 13,   13, 13, 13, 13,
		28, 13, 28, 28,   13, 13, 13, 13,
		
			/* [ 32, 0x20 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 48, 0x30 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
			/* [ 64, 0x40 ] */
		2, 2, 2, 2,   2, 2, 2, 2,
		2, 2, 2, 2,   2, 2, 2, 2,
			/* [ 80, 0x50 ] */
		2, 2, 2, 2,   2, 2, 2, 2,
		2, 2, 2, 2,   2, 2, 2, 2,
		
			/* [ 96, 0x60 ] */
		2, 2, 2, 2,   2, 2, 2, 2,
		2, 2, 2, 2,   2, 2, 2, 2,
			/* [ 112, 0x70 ] */
		2, 2, 2, 2,   2, 2, 2, 2,
		2, 2, 2, 2,   2, 2, 2, 0,
		
		
		
		
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		
			/* [ 160, 0xA0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 176, 0xB0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
			/* [ 192, 0xC0 ] */
		2, 2, 2, 2,   2, 2, 2, 2,
		2, 2, 2, 2,   2, 2, 2, 2,
			/* [ 208, 0xD0 ] */
		2, 2, 2, 2,   2, 2, 2, 2,
		2, 2, 2, 2,   2, 2, 2, 2,
		
			/* [ 224, 0xE0 ] */
		2, 2, 2, 2,   2, 2, 2, 2,
		2, 2, 2, 2,   2, 2, 2, 2,
			/* [ 240, 0xF0 ] */
		2, 2, 2, 2,   2, 2, 2, 2,
		2, 2, 2, 2,   2, 2, 2, 0
	},
	fromDcsEntry[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 16, 0x10 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		28, 0, 28, 28,   0, 0, 0, 0,
		
			/* [ 32, 0x20 ] */
		21, 21, 21, 21,   21, 21, 21, 21,
		21, 21, 21, 21,   21, 21, 21, 21,
			/* [ 48, 0x30 ] */
		23, 23, 23, 23,   23, 23, 23, 23,
		23, 23, 22, 23,   24, 24, 24, 24,
		
		
			/* [ 64, 0x40 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 80, 0x50 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
		
			/* [ 96, 0x60 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 112, 0x70 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		
			/* [ 160, 0xA0 ] */
		21, 21, 21, 21,   21, 21, 21, 21,
		21, 21, 21, 21,   21, 21, 21, 21,
			/* [ 176, 0xB0 ] */
		23, 23, 23, 23,   23, 23, 23, 23,
		23, 23, 22, 23,   24, 24, 24, 24,
		
		
			/* [ 192, 0xC0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 208, 0xD0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
		
			/* [ 224, 0xE0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 240, 0xF0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 0
	},
	fromDcsParam[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 16, 0x10 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		28, 0, 28, 28,   0, 0, 0, 0,
		
			/* [ 32, 0x20 ] */
		21, 21, 21, 21,   21, 21, 21, 21,
		21, 21, 21, 21,   21, 21, 21, 21,
			/* [ 48, 0x30 ] */
		20, 20, 20, 20,   20, 20, 20, 20,
		20, 20, 22, 20,   22, 22, 22, 22,
		
		
			/* [ 64, 0x40 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 80, 0x50 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
		
			/* [ 96, 0x60 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 112, 0x70 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		
			/* [ 160, 0xA0 ] */
		21, 21, 21, 21,   21, 21, 21, 21,
		21, 21, 21, 21,   21, 21, 21, 21,
			/* [ 176, 0xB0 ] */
		20, 20, 20, 20,   20, 20, 20, 20,
		20, 20, 22, 20,   22, 22, 22, 22,
		
		
			/* [ 192, 0xC0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 208, 0xD0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
		
			/* [ 224, 0xE0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 240, 0xF0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 0
	},
	fromDcsIntermediate[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 16, 0x10 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		28, 0, 28, 28,   0, 0, 0, 0,
		
			/* [ 32, 0x20 ] */
		14, 14, 14, 14,   14, 14, 14, 14,
		14, 14, 14, 14,   14, 14, 14, 14,
			/* [ 48, 0x30 ] */
		22, 22, 22, 22,   22, 22, 22, 22,
		22, 22, 22, 22,   22, 22, 22, 22,
		
		
			/* [ 64, 0x40 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 80, 0x50 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
		
			/* [ 96, 0x60 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 112, 0x70 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		
			/* [ 160, 0xA0 ] */
		14, 14, 14, 14,   14, 14, 14, 14,
		14, 14, 14, 14,   14, 14, 14, 14,
			/* [ 176, 0xB0 ] */
		22, 22, 22, 22,   22, 22, 22, 22,
		22, 22, 22, 22,   22, 22, 22, 22,
		
		
			/* [ 192, 0xC0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 208, 0xD0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
		
			/* [ 224, 0xE0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 25,
			/* [ 240, 0xF0 ] */
		25, 25, 25, 25,   25, 25, 25, 25,
		25, 25, 25, 25,   25, 25, 25, 0
	},
	fromDcsPassthrough[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
			/* [ 16, 0x10 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		28, 26, 28, 28,   26, 26, 26, 26,
		
			/* [ 32, 0x20 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
			/* [ 48, 0x30 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
		
		
			/* [ 64, 0x40 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
			/* [ 80, 0x50 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
		
			/* [ 96, 0x60 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
			/* [ 112, 0x70 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
			?,
			?, ?, ?, ?,   2,
		
			/* [ 160, 0xA0 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
			/* [ 176, 0xB0 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
		
		
			/* [ 192, 0xC0 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
			/* [ 208, 0xD0 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
		
			/* [ 224, 0xE0 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 26,
			/* [ 240, 0xF0 ] */
		26, 26, 26, 26,   26, 26, 26, 26,
		26, 26, 26, 26,   26, 26, 26, 0
	},
	fromDcsIgnore[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 16, 0x10 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		28, 0, 28, 28,   0, 0, 0, 0,
		
			/* [ 32, 0x20 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 48, 0x30 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
			/* [ 64, 0x40 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 80, 0x50 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 96, 0x60 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 112, 0x70 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		?,
		?, ?, ?, ?,   2,
		
			/* [ 160, 0xA0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 176, 0xB0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
			/* [ 192, 0xC0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 208, 0xD0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 224, 0xE0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 240, 0xF0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0
	},
	fromOscString[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 16, 0x10 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		28, 0, 28, 28,   0, 0, 0, 0,
		
			/* [ 32, 0x20 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
			/* [ 48, 0x30 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
		
		
			/* [ 64, 0x40 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
			/* [ 80, 0x50 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
		
			/* [ 96, 0x60 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
			/* [ 112, 0x70 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		?,
		?, ?, ?, ?,   2,
		
			/* [ 160, 0xA0 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
			/* [ 176, 0xB0 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
		
		
			/* [ 192, 0xC0 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
			/* [ 208, 0xD0 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
		
			/* [ 224, 0xE0 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27,
			/* [ 240, 0xF0 ] */
		27, 27, 27, 27,   27, 27, 27, 27,
		27, 27, 27, 27,   27, 27, 27, 27
	},
	fromSosPmacApc_String[ 256 ] =
	{
			/* [ 0, 0x00 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 16, 0x10 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		28, 0, 28, 28,   0, 0, 0, 0,
		
			/* [ 32, 0x20 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 48, 0x30 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
			/* [ 64, 0x40 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 80, 0x50 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 96, 0x60 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 112, 0x70 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
		
		
		/* These two are the C1 control block, they need some */
		/*  customization. */
			/* [ 128, 0x80 ] */
			/* [ 144, 0x90 ] */
		?,
		?, ?, ?, ?,   2,
		
			/* [ 160, 0xA0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 176, 0xB0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
		
			/* [ 192, 0xC0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 208, 0xD0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
		
			/* [ 224, 0xE0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0,
			/* [ 240, 0xF0 ] */
		0, 0, 0, 0,   0, 0, 0, 0,
		0, 0, 0, 0,   0, 0, 0, 0
	};
uint8_t
	*vt100net_stateMappings
		[
			vt100net_termcontext_STATES__PAST_END -
			vt100net_termcontext_GROUND
		] =
	{
		fromGround,
		fromEscape,
		fromEscapeIntermediate,
		fromCsiEntry,
		fromCsiParam,
		fromCsiIntermediate,
		fromCsiIgnore,
		fromDcsEntry,
		fromDcsParam,
		fromDcsIntermediate,
		fromDcsPassthrough,
		fromDcsIgnore,
		fromOscString,
		fromSosPmacApc_String,
		
		(*vt100net_stateMappings)0
	};

	/* The lookup array for individual handler functions. */
vt100net_action_handler vt100net_handlers[ 15 ] =
	{
		&vt100net_actions_ignore,
		&vt100net_actions_print,
		&vt100net_actions_execute,
		&vt100net_actions_clear,
		&vt100net_actions_collect,
		
			/* [ 5 ] */
		&vt100net_actions_param,
		&vt100net_actions_esc_dispatch,
		&vt100net_actions_csi_dispatch,
		&vt100net_actions_hook,
		&vt100net_actions_put,
		
			/* [ 10 ] */
		&vt100net_actions_unhook,
		&vt100net_actions_osc_start,
		&vt100net_actions_osc_put,
		&vt100net_actions_osc_end,
		
		(vt100net_action_handler)0
			/* If this element ( [14] ) is targetted, then there IS NOT a */
			/*  handler in the current selection stack, and the next */
			/*  possible stack should be checked. */
	};


/* Various states, with their input->action mappings. Note that */
/*  the transitions (input->action mappings that also change the */
/*  listed state) aren't currently listed. */
/* Codes A0-FF are treated the same as 20-7F, but C0 & C1 aren't */
	/* Input->action mappings: */
		/* entry / action : Only performed during initial state entry */
		/* event * / action : Perform action when * symbol encountered, retain current state */
		/* exit / action : Happens whenever an incoming symbol causes (even just conceptually) a state change */
		/* transition * / action -> destination : The obvious */
	/* All symbols lised in hex. */
	/* State transitions cause: */
		/* 1: the exit action of the initial state */
		/* 2: the transition action */
		/* 3: the entry action of the new state */
/*
vt100net_termcontext_GROUND ( 64 )
	event 00-17,19,1C-1F / execute
	event 20-7F / print
vt100net_termcontext_ESCAPE
	entry / clear
	event 00-17,19,1C-1F / execute
	event 7F / ignore
vt100net_termcontext_ESCAPE_INTERMEDIATE
	event 00-17,19,1C-1F / execute
	event 20-2F / collect
	event 7F / ignore
vt100net_termcontext_CSI_ENTRY
	entry / clear
	event 00-17,19,1C-1F / execute
	event 7F / ignore
vt100net_termcontext_CSI_PARAM
	event 00-17,19,1C-1F / execute
	event 30-39,3B / param
	event 7F / ignore
vt100net_termcontext_CSI_INTERMEDIATE
	event 00-17,19,1C-1F / execute
	event 20-2F / collect
	event 7F / ignore
vt100net_termcontext_CSI_IGNORE
	event 00-17,19,1C-1F / execute
	event 20-3F,7F / ignore
vt100net_termcontext_DCS_ENTRY
	entry / clear
	event 00-17,19,1C-1F / ignore
	event 7F / ignore
vt100net_termcontext_DCS_PARAM
	event 00-17,19,1C-1F / ignore
	event 30-39,3B / param
	event 7F / ignore
vt100net_termcontext_DCS_INTERMEDIATE
	event 00-17,19,1C-1F / ignore
	event 20-2F / collect
	event 7F / ignore
vt100net_termcontext_DCS_PASSTHROUGH
	entry / hook
	event 00-17,19,1C-1F,20-7E / put
	event 7F / ignore
	exit / unhook
vt100net_termcontext_DCS_IGNORE
	event 00-17,19,1C-1F,20-7F / ignore
vt100net_termcontext_OSC_STRING
	entry / osc_start
	event 00-17,19,1C-1F / ignore
	event 20-7F / osc_put
	exit / osc_end
vt100net_termcontext_SOS_PMAC_APC__STRING
	event 00-17,19,1C-1F,20-7F / ignore
*/

	/* This table covers all of the common "ASCII+" C1 control */
	/*  codes: they are part of Unicode, as well as older */
	/*  systems. Most or all of these should probably be */
	/*  "ignore" characters, but they should be actually */
	/*  examined and considered. */
/*
	ESC @	0x80	PAD*	Padding Character
	ESC A	0x81	HOP*	High Octet Preset
		Was originally meant to mark the start of a multi-byte
		character sequence so that constant escape characters
		wouldn't be required, but was never standardized.
	ESC B	0x82	BPH		Break Permitted Here
	ESC C	0x83	NBH		No Break Here
	ESC D	0x84	IND		Index
		Move the active position one line down, to eliminate
		ambiguity about the meaning of LF. Deprecated in 1988 and
		withdrawn in 1992 from ISO/IEC 6429 (1986 and 1991
		respectively for ECMA-48).
	ESC E	0x85	NEL		Next Line
		Equivalent to CR+LF. Used to mark end-of-line on some IBM
		mainframes.
	
	ESC F	0x86	SSA		Start of Selected Area
	ESC G	0x87	ESA		End of Selected Area
		Used by block-oriented terminals. xterm supports a
		compatibility mode in which ESC F moves to the lower-left
		corner of the screen, since certain software assumes this
		behaviour.
	
	ESC H	0x88	HTS		Character Tabulation Set
		Horizontal Tabulation Set	Causes a character tabulation
		stop to be set at the active position.
	ESC I	0x89	HTJ		Character Tabulation With Justification
			(Horizontal Tabulation With Justification)
		Similar to Character Tabulation, except that instead of
		spaces or lines being placed after the preceding characters
		until the next tab stop is reached, the spaces or lines are
		placed preceding the active field so that the preceding
		graphic character is placed just before the next tab stop.
	ESC J	0x8A	VTS		Line Tabulation Set
			(Vertical Tabulation Set)
		Causes a line tabulation stop to be set at the active
		position.
	
	ESC K	0x8B	PLD		Partial Line Forward
			(Partial Line Down)
	ESC L	0x8C	PLU		Partial Line Backward
			(Partial Line Up)
		Used to produce subscripts and superscripts in ISO/IEC
			6429, e.g., in a printer. Subscripts use:
				PLD text PLU
			while superscripts use:
				PLU text PLD.
	
	ESC M	0x8D	RI		Reverse Line Feed
			(Reverse Index)
	
	ESC N	0x8E	SS2		Single Shift Two
		Select G2 character set for next character
	ESC O	0x8F	SS3		Single Shift Three
		Select G3 character set for next character
	ESC P	0x90	DCS		Device Control String
		Terminated by ST
	
	ESC Q	0x91	PU1		Private Use 1
	ESC R	0x92	PU2		Private Use 2
	ESC S	0x93	STS		Set Transmit State
	
	ESC T	0x94	CCH		Cancel character
		Destructive backspace, intended to eliminate ambiguity about
		meaning of BS.
	
	ESC U	0x95	MW		Message Waiting
	
	ESC V	0x96	SPA		Start of Protected Area
	ESC W	0x97	EPA		End of Protected Area
	
	ESC X	0x98	SOS		Start of String
		As 0x9E, but can contain anu character except SOS and ST.
	
	ESC Y	0x99	SGC*, SGCI*		Single Graphic Character Introducer
		Not part of ISO/IEC 6429. In early drafts of ISO 10646, was
		used to encode a single multiple-byte character without
		switching out of a HOP mode, or to allow access to the entire
		character set from UCS-3, UCS-2 or Latin-1. Would be followed
		by a UCS-4 representation of a character.
	ESC Z	0x9A	SCI*	Single Character Introducer
		To be followed by a single printable character (0x20 through
		0x7E) or format effector (0x08 through 0x0D). The intent was to
		provide a means by which a control function or a graphic
		character that would be available regardless of which graphic
		or control sets were in use could be defined. Definitions of
		what the following byte would invoke was never implemented in
		an international standard.
	
	ESC [	0x9B	CSI		Control Sequence Introducer
		Terminated by 0x40 - 0x7E
	ESC \	0x9C	ST		String Terminator
		Ends strings in other controls
	ESC ]	0x9D	OSC		Operating System Command
		Terminated by ST. Some terminal emulators, including xterm,
		support OSC sequences for setting the window title and
		reconfiguring the available colour palette. They may also
		support terminating an OSC sequence with BEL as a
		non-standard alternative to the standard ST.
	ESC ^	0x9E	PM		Privacy Message
		As below
	ESC _	0x9F	APC		Application Program Command
		Takes an argument of a string of text, terminated by ST.
		The uses for these string control sequences are defined
		by the application  or privacy discipline.  These functions
		are rarely implemented and the arguments are ignored by
		xterm. Some Kermit clients allow the server to
		automatically execute Kermit commands on the client by
		embedding them in APC sequences; this is a potential
		security risk if the server is untrusted, and thus APC
		may be disabled or filtered in some cases.
	
	* : The PAD, HOP, SGC, SGCI characters aren't defined by
		ISO/IEC 6429 (ECMA-48), but their names are preserved
		from older proposals.
	U+0080–U+009F (C1 controls) assigned to the Latin-1 Supplement
		block. Unicode only specifies semantics for U+0009–U+000D,
		U+001C–U+001F, and U+0085.
*/
