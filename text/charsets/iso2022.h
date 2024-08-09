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

#ifndef LIBANDRIA4_TEXT_CHARSETS_ISO2022_H
# define LIBANDRIA4_TEXT_CHARSETS_ISO2022_H
	
	/* Charset: ISO 2022 (generic) */
	
	/* The G* situation: */
		/* ISO 2022 specifies, among other things, ways to swap particular character */
		/*  sets in and out. These sets ARE NOT fonts, but instead logically distinct */
		/*  CHARACTERS. They can be either 94 or 96 -character sets. These sets can */
		/*  themselves be allocated to a selectable character set, those being G0, */
		/*  G1, G2, and G3. G0 ONLY accepots 94-character sets, while the other three */
		/*  can accept 94 or 96 -character sets. Those numbered sets can then be */
		/*  assigned to either the GL or GR ranges: GL corresponds to part of the */
		/*  ASCII set of numbers, while GR corresponds to part of the 128-255 numeric */
		/*  range. Once they've been assigned to either GL or GR, the characters of */
		/*  that set are able to be used. Characters are "spacing" characters instead */
		/*  of combining characters, unless a particular set specifically says */
		/*  otherwise. ISO 2022 recognizes the use of backspace and carriage return */
		/*  to use spacing characters as combining characters, but is banned by SOME */
		/*  ISO 2022 -derived standards, such as ISO 8859 (Unicode is derived from */
		/*  the -1 variant of 8859). */
	
	#include "ascii.h"
	
	/* Refer to https://en.wikipedia.org/wiki/ISO/IEC_2022#Shift_functions for more info. */
	/* See also: */
		/* https://en.wikipedia.org/wiki/ISO/IEC_JTC_1/SC_2 */
		/* https://en.wikipedia.org/wiki/ISO/IEC_8859 */
		/* https://en.wikipedia.org/wiki/Unicode_control_characters */
		/* https://en.wikipedia.org/wiki/C0_and_C1_control_codes */
		/* https://en.wikipedia.org/wiki/Extended_Unix_Code */
		/* https://en.wikipedia.org/wiki/MARC-8 */
		/* https://en.wikipedia.org/wiki/ARIB_STD_B24_character_set */
		/* https://en.wikipedia.org/wiki/ANSI_escape_code */
		/* https://en.wikipedia.org/wiki/Unicode */
		/* https://en.wikipedia.org/wiki/C0_and_C1_control_codes */
		/* https://en.wikipedia.org/wiki/ISO/IEC_646 */
		/* https://www.ecma-international.org/wp-content/uploads/ECMA-35_6th_edition_december_1994.pdf */
	
	/* Note that unlike the graphics characters, the control codes never change meaning. */
	
	/* These are USUALLY just the ASCII control codes, but ALWAYS feature "escape" */
	/*  at 0x1B (the location used in ASCII). 0x00–0x1F */
	#define LIBANDRIA4_CHARSETS_ISO2022_CL_escape LIBANDRIA4_CHARSETS_ASCII_escape
	
	#define LIBANDRIA4_CHARSETS_ISO2022_CL_lowest 0x00
	#define LIBANDRIA4_CHARSETS_ISO2022_CL_highest 0x1F
	
	
	/* "Graphics Left". By default the G0 set, which itself is ASCII. 0x20–0x7F */
		/* As a special note, these two are swapped out by 96 character sets, */
		/*  but left as-is by 94 character sets. This makes them somewhat */
		/*  special when compared to other characters. Also, when g0 is applied */
		/*  to GL they will be present, REGARDLESS of anything else. */
			/* Space: 0x20 */
	#define LIBANDRIA4_CHARSETS_ISO2022_GL_space LIBANDRIA4_CHARSETS_ASCII_space
			/* Delete: 0x7F */
	#define LIBANDRIA4_CHARSETS_ISO2022_GL_delete LIBANDRIA4_CHARSETS_ASCII_delete
	
	#define LIBANDRIA4_CHARSETS_ISO2022_GL_lowest 0x20
	#define LIBANDRIA4_CHARSETS_ISO2022_GL_highest 0x7F
	
	
	/* Actual ISO 2022 -sourced control codes. 0x80 - 0x9F */
	#define LIBANDRIA4_CHARSETS_ISO2022_CR_lowest 0x80
	#define LIBANDRIA4_CHARSETS_ISO2022_CR_highest 0x9F
	
	
	/* ISO 2022 -"sourced" character codes. By default the G1 set. 0xA0–0xFF */
		/* As with space and delete in the GL space, these two get swapped out */
		/*  by 96-character sets, but are left as-is by 94-character sets. */
	#define LIBANDRIA4_CHARSETS_ISO2022_GR_optlow 0xA0
	#define LIBANDRIA4_CHARSETS_ISO2022_GR_opthigh 0xFF
	
	#define LIBANDRIA4_CHARSETS_ISO2022_GR_lowest 0xA0
	#define LIBANDRIA4_CHARSETS_ISO2022_GR_highest 0xFF
	
	
		/* The standard escape sequence format, inherited & used by the ANSI */
		/*  terminal standard. */
	#define LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( finalchara, ... ) \
		LIBANDRIA4_CHARSETS_ISO2022_CL_escape __VA_ARGS__ , finalchara
	
			/* Disable manual input. How much gets disables depends on e.g. the hardware. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_DMI \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_grv )
			/* Interrupts "the current process". */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_INT \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_a )
			/* Enable manual input, the opposite of DMI. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_EMI \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_b )
			/* Reset the device to it's state after being powered on. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_RIS \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_c )
			/* Coding method delimiter. Used when interaction with an enclosing system. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_CMD \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_d )
	/* These two lock G2 or G3 to the GL space. */
			/* Locking shift 2. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_LS2 \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_n )
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_LS3 \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_o )
	/* The next three lock G1, G2, or G3 to the GR space. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_LS3R \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_vbar )
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_LS2R \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_clcrl )
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_LS1R \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_tild )
			/* GL and GR encode G2 for ONLY the immediately following character. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_SS2_ESCAPE \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_N )
			/* As above, but G3. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_SS3_ESCAPE \
		LIBANDRIA4_CHARSETS_ISO2022_ESCAPESEQUENCE( LIBANDRIA4_CHARSETS_ASCII_O )
	
		/* Note that ISO 2022 / ECMA 35 defines these next two to NOT */
		/*  affect the control character space. */
			/* Set GL to G0. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_LS0 LIBANDRIA4_CHARSETS_ASCII_shiftin
			/* Set GL to G1. */
	#define LIBANDRIA4_CHARSETS_ISO2022_FUNCTION_LS1 LIBANDRIA4_CHARSETS_ASCII_shiftout
	
#endif
/* End libandria4 text charsets iso2022.h */
