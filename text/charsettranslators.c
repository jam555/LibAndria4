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

#include "charsettranslators.h"


libandria4_common_monadicchar32
	libandria4_text_charsettranslators_ascii_to_unicode
	( void *ign, libandria4_common_monadicchar32 val )
{
	libandria4_common_monadicchar_BODYMATCH(
		val,
			libandria4_common_monadicchar32_RETURNSUCC,
			libandria4_common_monadicchar32_RETURNERR );
}
libandria4_common_monadicchar32
	libandria4_text_charsettranslators_unicode_to_ascii
	( void *ign, libandria4_common_monadicchar32 val )
{
	uint32_t a;
	
	libandria4_common_monadicchar_BODYMATCH(
		val,
			???_SETa,
			libandria4_common_monadicchar32_RETURNERR );
	
	if( a <= 255 )
	{
		libandria4_common_monadicchar32_RETURNSUCC( a );
	}
	
	libandria4_common_monadicchar32_RETURNERR( a );
}


/* These actually should have identical behaviors. */
libandria4_common_monadicchar32
	libandria4_text_charsettranslators_strict_ascii_to_unicode
	( void *ign, libandria4_common_monadicchar32 val )
{
	uint32_t a;
	
	libandria4_common_monadicchar_BODYMATCH(
		val,
			???_SETa,
			libandria4_common_monadicchar32_RETURNERR );
	
	if( a <= 127 )
	{
		libandria4_common_monadicchar32_RETURNSUCC( a );
	}
	
	libandria4_common_monadicchar32_RETURNERR( a );
}
libandria4_common_monadicchar32
	libandria4_text_charsettranslators_strict_unicode_to_ascii
	( void *ign, libandria4_common_monadicchar32 val )
{
	return( libandria4_text_charsettranslators_strict_ascii_to_unicode( ign, val ) );
}


libandria4_common_monadicchar32
	libandria4_text_charsettranslators_vt100uk_to_unicode
	( void *ign, libandria4_common_monadicchar32 val )
{
	uint32_t a;
	
	libandria4_common_monadicchar_BODYMATCH(
		val,
			???_SETa,
			libandria4_common_monadicchar32_RETURNERR );
	
		/* For the UK case, the US weight pound is replaced by the UK */
		/*  currency pound. */
	if( a == 0x23 )
	{
		libandria4_common_monadicchar32_RETURNSUCC( 0xA3 );
	}
	if( a <= 127 )
	{
		libandria4_common_monadicchar32_RETURNSUCC( a );
	}
	
	libandria4_common_monadicchar32_RETURNERR( a );
}
libandria4_common_monadicchar32
	libandria4_text_charsettranslators_unicode_to_vt100uk
	( void *ign, libandria4_common_monadicchar32 val )
{
	uint32_t a;
	
	libandria4_common_monadicchar_BODYMATCH(
		val,
			???_SETa,
			libandria4_common_monadicchar32_RETURNERR );
	
		/* For the UK case, the US weight pound is replaced by the UK */
		/*  currency pound. */
	if( a == 0xA3 )
	{
		libandria4_common_monadicchar32_RETURNSUCC( 0x23 );
	}
	if( a <= 127 )
	{
		libandria4_common_monadicchar32_RETURNSUCC( a );
	}
	
	libandria4_common_monadicchar32_RETURNERR( a );
}


libandria4_common_monadicchar32
	libandria4_text_charsettranslators_vt100specgraph_to_unicode
	( void *ign, libandria4_common_monadicchar32 val )
{
		/* The base address is 0x5F, not 0, so test & offset. */
		/* I grabbed this set of mappings from some Wikipedia */
		/*  page on 14/Mar/2024. Formatting is my own */
	static uint32_t mapping[  ] =
		{
				/* 0x5F */
			0x00A0, /* NO-BREAK SPACE */
			
				/* 0x60 */
			0x25C6, /* BLACK DIAMOND */
			0x2592, /* Checkerboard: Unicode MEDIUM SHADE */
			0x2409, /* SYMBOL FOR HORIZONTAL TABULATION */
			0x240C, /* SYMBOL FOR FORM FEED */
			
			0x240D, /* SYMBOL FOR CARRIAGE RETURN */
			0x240A, /* SYMBOL FOR LINE FEED */
			0x00B0, /* DEGREE SIGN */
			0x00B1, /* PLUS-MINUS SIGN */
			
				/* 0x68 */
			0x2424, /* SYMBOL FOR NEWLINE */
			0x240B, /* SYMBOL FOR VERTICAL TABULATION */
			0x2518, /* Lower-right corner: Unicode BOX DRAWINGS LIGHT UP AND LEFT */
			0x2510, /* Upper-right corner: Unicode BOX DRAWINGS LIGHT DOWN AND LEFT */
			
			0x250C, /* Upper-left corner: Unicode BOX DRAWINGS LIGHT DOWN AND RIGHT */
			0x2514, /* Lower-left corner: Unicode BOX DRAWINGS LIGHT UP AND RIGHT */
			0x253C, /* Crossing Lines: Unicode BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
				/* These next five lines seem to just be */
				/*  horizontal lines. "1" is highest, "9" */
				/*  seems to be approximately an underscore, */
				/*  the rest are sequentially placed between */
				/*  them. I don't know why "scan" is in the */
				/*  description. */
			0x23BA, /* HORIZONTAL SCAN LINE-1 */
			
				/* 0x70 */
			0x23BB, /* HORIZONTAL SCAN LINE-3 */
			0x2500, /* Horizontal line - scan 5: Unicode BOX DRAWINGS LIGHT HORIZONTAL */
			0x23BC, /* HORIZONTAL SCAN LINE-7 */
			0x23BD, /* HORIZONTAL SCAN LINE-9 */
			
			0x251C, /* Left "T": Unicode BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
			0x2524, /* Right "T": Unicode BOX DRAWINGS LIGHT VERTICAL AND LEFT */
			0x2534, /* Bottom "T": Unicode BOX DRAWINGS LIGHT UP AND HORIZONTAL */
			0x252C, /* Top "T": Unicode BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
			
				/* 0x78 */
			0x2502, /* Vertical bar: Unicode BOX DRAWINGS LIGHT VERTICAL */
			0x2264, /* LESS-THAN OR EQUAL TO */
			0x2265, /* GREATER-THAN OR EQUAL TO */
			0x03C0, /* GREEK SMALL LETTER PI */
			
			0x2260, /* NOT EQUAL TO */
			0x00A3, /* UK pound symbol: Unicode POUND SIGN */
			0x00B7 /* Centered dot: Unicode MIDDLE DOT */
		};
	uint32_t a;
	
	libandria4_common_monadicchar_BODYMATCH(
		val,
			???_SETa,
			libandria4_common_monadicchar32_RETURNERR );
	
		/* For the UK case, the US weight pound is replaced by the UK */
		/*  currency pound. */
	if( a >= 0x5F && a <= 0x7E )
	{
		libandria4_common_monadicchar32_RETURNSUCC( mapping[ a - 0x5F ] );
	}
	if( a <= 0x7F )
	{
		libandria4_common_monadicchar32_RETURNSUCC( a );
	}
	
	libandria4_common_monadicchar32_RETURNERR( a );
}
libandria4_common_monadicchar32
	libandria4_text_charsettranslators_unicode_to_vt100specgraph_lossless
	( void *ign, libandria4_common_monadicchar32 val )
{
	uint32_t a;
	
	libandria4_common_monadicchar_BODYMATCH(
		val,
			???_SETa,
			libandria4_common_monadicchar32_RETURNERR );
	
	switch( a )
	{
		case 0x00A0: /* NO-BREAK SPACE */
			a = 0x5F; break;
		case 0x00A3: /* UK pound symbol: Unicode POUND SIGN */
			a = 0x7D; break;
		case 0x00B0: /* DEGREE SIGN */
			a = 0x66; break;
		case 0x00B1: /* PLUS-MINUS SIGN */
			a = 0x67; break;
		case 0x00B7: /* Centered dot: Unicode MIDDLE DOT */
			a = 0x7E; break;
		
		case 0x2260: /* NOT EQUAL TO */
			a = 0x7C; break;
		case 0x2264: /* LESS-THAN OR EQUAL TO */
			a = 0x79; break;
		case 0x2265: /* GREATER-THAN OR EQUAL TO */
			a = 0x7A; break;
		
		case 0x23BA: /* HORIZONTAL SCAN LINE-1 */
			a = 0x6F; break;
		case 0x23BB: /* HORIZONTAL SCAN LINE-3 */
			a = 0x70; break;
		case 0x23BC: /* HORIZONTAL SCAN LINE-7 */
			a = 0x72; break;
		case 0x23BD: /* HORIZONTAL SCAN LINE-9 */
			a = 0x73; break;
		
		case 0x2409: /* SYMBOL FOR HORIZONTAL TABULATION */
			a = 0x62; break;
		case 0x240A: /* SYMBOL FOR LINE FEED */
			a = 0x65; break;
		case 0x240B: /* SYMBOL FOR VERTICAL TABULATION */
			a = 0x69; break;
		case 0x240C: /* SYMBOL FOR FORM FEED */
			a = 0x63; break;
		case 0x240D: /* SYMBOL FOR CARRIAGE RETURN */
			a = 0x64; break;
		case 0x2424: /* SYMBOL FOR NEWLINE */
			a = 0x68; break;
		
		case 0x2500: /* Horizontal line - scan 5: Unicode BOX DRAWINGS LIGHT HORIZONTAL */
			a = 0x71; break;
		case 0x2502: /* Vertical bar: Unicode BOX DRAWINGS LIGHT VERTICAL */
			a = 0x78; break;
		case 0x250C: /* Upper-left corner: Unicode BOX DRAWINGS LIGHT DOWN AND RIGHT */
			a = 0x6C; break;
		case 0x2510: /* Upper-right corner: Unicode BOX DRAWINGS LIGHT DOWN AND LEFT */
			a = 0x6B; break;
		case 0x2514: /* Lower-left corner: Unicode BOX DRAWINGS LIGHT UP AND RIGHT */
			a = 0x6D; break;
		case 0x2518: /* Lower-right corner: Unicode BOX DRAWINGS LIGHT UP AND LEFT */
			a = 0x6A; break;
		case 0x251C: /* Left "T": Unicode BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
			a = 0x74; break;
		case 0x2524: /* Right "T": Unicode BOX DRAWINGS LIGHT VERTICAL AND LEFT */
			a = 0x75; break;
		case 0x252C: /* Top "T": Unicode BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
			a = 0x77; break;
		case 0x2534: /* Bottom "T": Unicode BOX DRAWINGS LIGHT UP AND HORIZONTAL */
			a = 0x76; break;
		case 0x253C: /* Crossing Lines: Unicode BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
			a = 0x6E; break;
		case 0x2592: /* Checkerboard: Unicode MEDIUM SHADE */
			a = 0x61; break;
		case 0x25C6: /* BLACK DIAMOND */
			a = 0x60; break;
		
		case 0x03C0: /* GREEK SMALL LETTER PI */
			a = 0x7B; break;
		
		default:
			break;
	}
	if( a <= 127 )
	{
		libandria4_common_monadicchar32_RETURNSUCC( a );
	}
	
	libandria4_common_monadicchar32_RETURNERR( a );
}
