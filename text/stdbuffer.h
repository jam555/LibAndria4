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

#ifndef LIBANDRIA4_TEXT_STDBUFFER_H
# define LIBANDRIA4_TEXT_STDBUFFER_H
	
	/* This file was built for use by the VT100 parser code in the */
	/*  ../parsers folder. For a default implementation, look in */
	/*  commonbuffer.h/.c */
	
	#include "../basic/commonmacros.h"
	#include "../basic/stdmem.h"
		/* The nearly omniversal utility header... */
	#include "../basic/pascalarray.h"
	#include "../basic/pascalstring.h"
	#include "../basic/commonio.h"
		/* This include shouldn't be needed, but let's not delete it just */
		/*  yet... */
	/* include "termninal.h" */
	
	
	
	/* The terminal buffer system. */
	
	LIBANDRIA4_DEFINE_PASCALARRAY_BAREDECLARE( libandria4_bytebuffer_, uint8_t );
	
	typedef struct libandria4_termbuffer_generic libandria4_termbuffer_generic;
	
	
	
		/* TODO: Rename this to actually fit with this file. */
	typedef enum
	{
		libandria4_termbuffer_directions_invalid = -1,
		
		libandria4_termbuffer_directions_null = 0,
		
		libandria4_termbuffer_directions_up = 1,
		libandria4_termbuffer_directions_right,
		libandria4_termbuffer_directions_down,
		libandria4_termbuffer_directions_left,
		
			/* Returns to the the left-most (or equivalent) location. */
		libandria4_termbuffer_directions_isCR = 5,
			/* This prompts a vertical scroll. */
		libandria4_termbuffer_directions_islastline,
		
		libandria4_termbuffer_directions_pastmax
		
	} libandria4_termbuffer_directions;
	
		/* Just a convenience type. */
	typedef struct libandria4_buffercell_common
	{
			/* E.g. "blink" and "vermillion". */
		struct
		{
			uint8_t r, g, b;
			
		} fore, back;
		uint16_t style;
		
			/* Presumably a Unicode character, but maybe something (e.g. */
			/*  JIS, EBCDIC) incompatible. Should ALWAYS be a "resolved" */
			/*  character though, so no e.g. surrogate code points allowed. */
			/* ... probably not even combining characters for this style. */
		uint32_t chara;
		
	} libandria4_buffercell_common;
	/* Note: this is ABSOLUTELY expected to be just 64 bits in size. If it */
	/*  isn't, then add some compiler pragmas. */
	
	/* These get stored in the libandria4_buffercell_common.style member. */
		/* For when you just want to clear things out... */
	#define libandria4_buffercell_common_style_NONE ( (uint16_t)( 0 ) )
		/* These were e.g. libandria4_buffercell_common_FASTBLINK */
	#define libandria4_buffercell_common_style_FASTBLINK ( (uint16_t)( 1 ) )
		/* Note: Fast blink and slow blink is a platform thing, but my */
		/*  thinking is support both, with the timing based on differing */
		/*  prime numbers. Fast blink was IBM PC and above 150 blinks per */
		/*  min, slow was below 150 blinks per min, use XOR logic. */
	#define libandria4_buffercell_common_style_SLOWBLINK ( (uint16_t)( 2 ) )
	#define libandria4_buffercell_common_style_INVERT ( (uint16_t)( 4 ) )
	#define libandria4_buffercell_common_style_intensity_MASK ( (uint16_t)( 24 ) )
		#define libandria4_buffercell_common_style_intensity_HIDDEN ( (uint16_t)( 8 ) )
		#define libandria4_buffercell_common_style_intensity_FAINT ( (uint16_t)( 16 ) )
			/* Yes, this one is out of order. */
		#define libandria4_buffercell_common_style_intensity_NORMAL ( (uint16_t)( 0 ) )
			/* On e.g. IBM MDA cards, implemented by higher intensity. */
		#define libandria4_buffercell_common_style_intensity_BOLD ( (uint16_t)( 24 ) )
	#define libandria4_buffercell_common_style_UNDERSCORE ( (uint16_t)( 32 ) )
	#define libandria4_buffercell_common_style_STRIKETHROUGH ( (uint16_t)( 64 ) )
	#define libandria4_buffercell_common_style_OVERLINED ( (uint16_t)( 128 ) )
	#define libandria4_buffercell_common_style_sizing_MASK ( (uint16_t)( 768 ) )
		#define libandria4_buffercell_common_style_sizing_NORMAL ( (uint16_t)( 0 ) )
		#define libandria4_buffercell_common_style_sizing_SUBSCRIPT ( (uint16_t)( 256 ) )
		#define libandria4_buffercell_common_style_sizing_MINITEXT ( (uint16_t)( 512 ) )
		#define libandria4_buffercell_common_style_sizing_SUPERSCRIPT ( (uint16_t)( 768 ) )
		/* VT100 attributes: */
	/*
			4: Underscore
		All other parameter values are ignored.
	*/
		/* Plain SGR modifiers: */
	/*
0	Reset or normal	All attributes become turned off
1	Bold or increased intensity	As with faint, the color change is a PC (SCO / CGA) invention.[25][better source needed]
2	Faint, decreased intensity, or dim	May be implemented as a light font weight like bold.[26]
4	Underline	Style extensions exist for Kitty, VTE, mintty, iTerm2 and Konsole.[27][28][29]

5	Slow blink	Sets blinking to less than 150 times per minute
6	Rapid blink	MS-DOS ANSI.SYS, 150+ per minute; not widely supported

9	Crossed-out, or strike	Characters legible but marked as if for deletion. Not supported in Terminal.app.
21	Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on several terminals, including in the Linux kernel's console before version 4.17.[31]
22	Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
24	Not underlined	Neither singly nor doubly underlined
29	Not crossed out	

51	Framed	Implemented as "emoji variation selector" in mintty.[32]
52	Encircled	Implemented as "emoji variation selector" in mintty.[32]

53	Overlined	Not supported in Terminal.app
54	Neither framed nor encircled	
55	Not overlined
	*/
		/* Desired modifiers: */
	/*
Oblique (slanted version of normal font, oft mistaken for Italic)
	*/
		/* "Select Graphics Rendition" fonts: */
	/*
3	Italic	Not widely supported. Sometimes treated as inverse or blink.[25]
10	Primary (default) font	
11–19	Alternative font	Select alternative font n − 10
20	Fraktur (Gothic)	Rarely supported
23	Neither italic, nor blackletter	
	*/
		/* Color SGR modifiers: */
	/*
30–37	Set foreground color	
38	Set foreground color	Next arguments are 5;n or 2;r;g;b
39	Default foreground color	Implementation defined (according to standard)
40–47	Set background color	
48	Set background color	Next arguments are 5;n or 2;r;g;b
49	Default background color	Implementation defined (according to standard)

58	Set underline color	Not in standard; implemented in Kitty, VTE, mintty, and iTerm2.[27][28] Next arguments are 5;n or 2;r;g;b.
59	Default underline color	Not in standard; implemented in Kitty, VTE, mintty, and iTerm2.[27][28]
	*/
		/* Unsorted SGR: */
	/*
	Per-character spacing, belongs outside terminals proper
26	Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
50	Disable proportional spacing	T.61 and T.416

	Rarely supported
60	Ideogram underline or right side line
61	Ideogram double underline, or double line on the right side
62	Ideogram overline or left side line
63	Ideogram double overline, or double line on the left side
64	Ideogram stress marking
65	No ideogram attributes	Reset the effects of all of 60–64
	*/
		/* VT100 alt graphics sets: */
		/* You know what? These should just be translated to specific */
		/*  characters. Don't support them in .style */
	/*
		United Kingdom Set
		ASCII Set
		Special Graphics
		Alternate Character ROM Standard Character Set
		Alternate Character ROM Special Graphics
	*/
	
	/* DEC UK character set */
/*
Replace # with the "pound L". Nothing else.
*/
	/* DEC Special Graphics / Unicode proposed mapping: */
/*
All of the characters exist in Unicode, though there does not seem to
be an official mapping. The horizontal "scan" line characters were
added in Unicode 3.2.0[1].

Here is an unofficial Unicode mapping:

	DEC Character							Proposed Unicode equivalent
0x5f Blank								U+00A0 NO-BREAK SPACE
0x60 Diamond							U+25C6 BLACK DIAMOND
0x61 Checkerboard						U+2592 MEDIUM SHADE
0x62 HT									U+2409 SYMBOL FOR HORIZONTAL TABULATION
0x63 FF									U+240C SYMBOL FOR FORM FEED
0x64 CR									U+240D SYMBOL FOR CARRIAGE RETURN
0x65 LF									U+240A SYMBOL FOR LINE FEED
0x66 Degree symbol						U+00B0 DEGREE SIGN
0x67 Plus/minus							U+00B1 PLUS-MINUS SIGN
0x68 NL									U+2424 SYMBOL FOR NEWLINE
0x69 VT									U+240B SYMBOL FOR VERTICAL TABULATION
0x6a Lower-right corner					U+2518 BOX DRAWINGS LIGHT UP AND LEFT
0x6b Upper-right corner					U+2510 BOX DRAWINGS LIGHT DOWN AND LEFT
0x6c Upper-left corner					U+250C BOX DRAWINGS LIGHT DOWN AND RIGHT
0x6d Lower-left corner					U+2514 BOX DRAWINGS LIGHT UP AND RIGHT
0x6e Crossing Lines						U+253C BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
	These five lines seem to just be horizontal lines. "1" is highest, "9" seems to be
	approximately an underscore, they rest are sequentially placed between them. I
	don't know why "scan" is in the description.
0x6f Horizontal line - scan 1			U+23BA HORIZONTAL SCAN LINE-1
0x70 Horizontal line - scan 3			U+23BB HORIZONTAL SCAN LINE-3
0x71 Horizontal line - scan 5			U+2500 BOX DRAWINGS LIGHT HORIZONTAL
0x72 Horizontal line - scan 7			U+23BC HORIZONTAL SCAN LINE-7
0x73 Horizontal line - scan 9			U+23BD HORIZONTAL SCAN LINE-9
0x74 Left "T"							U+251C BOX DRAWINGS LIGHT VERTICAL AND RIGHT
0x75 Right "T"							U+2524 BOX DRAWINGS LIGHT VERTICAL AND LEFT
0x76 Bottom "T"							U+2534 BOX DRAWINGS LIGHT UP AND HORIZONTAL
0x77 Top "T"							U+252C BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
0x78 Vertical bar						U+2502 BOX DRAWINGS LIGHT VERTICAL
0x79 Less than or equal to				U+2264 LESS-THAN OR EQUAL TO
0x7a Greater than or equal to			U+2265 GREATER-THAN OR EQUAL TO
0x7b Pi									U+03C0 GREEK SMALL LETTER PI
0x7c Not equal to						U+2260 NOT EQUAL TO
0x7d UK pound symbol					U+00A3 POUND SIGN
0x7e Centered dot						U+00B7 MIDDLE DOT
*/
	
	
		/* Note: Unicode has restricted itself to only 21 bits instead */
		/*  of a full 32, hence the details of *_UNICODEVALID_MASK */
	#define libandria4_buffercell_common_chara_UNICODEVALID_baseval ( (uint32_t)(( 1 << 21 ) - 1 ) )
	#define libandria4_buffercell_common_chara_UNICODEVALID_offset ( (uint32_t)0 )
	#define libandria4_buffercell_common_chara_UNICODEVALID_multiplier \
		( (uint32_t)( 1 << 0 ) )
	#define libandria4_buffercell_common_chara_UNICODEVALID_mask \
		( libandria4_buffercell_common_chara_UNICODEVALID_baseval << 0 )
	
		/* These defines correspond to the section of a 32-bit uint */
		/*  that UNICODE has decided to never use. */
	#define libandria4_buffercell_common_chara_UNICODEINVALID_baseval ( (uint32_t)(( 1 << 11 ) - 1 ) )
	#define libandria4_buffercell_common_chara_UNICODEINVALID_offset ( (uint32_t)21 )
	#define libandria4_buffercell_common_chara_UNICODEINVALID_multiplier \
		( (uint32_t)( 1 << libandria4_buffercell_common_chara_UNICODEINVALID_offset ) )
	#define libandria4_buffercell_common_chara_UNICODEINVALID_mask \
		( libandria4_buffercell_common_chara_UNICODEINVALID_baseval << \
			libandria4_buffercell_common_chara_UNICODEINVALID_offset )
	
	/* These defines overlap with the */
	/*  libandria4_buffercell_common_chara_UNICODEINVALID range. */
	/*  They're various things that aren't actually Unicode, but */
	/*  still have some similar behavior, e.g. different font options. */
			/* We need to support 21 (so 32) different font options, */
			/*  so we need 5 bits. This is part of the ANSI graphic */
			/*  rendition. This stuff used to be e.g. */
			/*  libandria4_buffercell_common_chara_CHARSET_mask */
		#define libandria4_buffercell_common_chara_FONT_baseval ( (uint32_t)31 )
		#define libandria4_buffercell_common_chara_FONT_offset ( (uint32_t)21 )
		#define libandria4_buffercell_common_chara_FONT_multiplier \
			( (uint32_t)( 1 << libandria4_buffercell_common_chara_font_offset ) )
				/* I believe this should equal 130023424 */
		#define libandria4_buffercell_common_chara_FONT_mask \
			( libandria4_buffercell_common_chara_FONT_baseval << \
				libandria4_buffercell_common_chara_FONT_offset )
		/* Desired fonts for this system: */
			/* Terminal types. */
				/* Default font. Sans-serif, mono-width, single-stroke */
			#define libandria4_buffercell_common_chara_FONT_Terminal ( 0 )
				/* Slab-serif, square-tipped, single-stroke, basically Blackletter Terminal */
			#define libandria4_buffercell_common_chara_FONT_Tannenburg ( 1 )
			
			/* "Common hand" types. */
				/* Serif, wide-tipped, single-stroke */
			#define libandria4_buffercell_common_chara_FONT_Roman ( 2 )
				/* A more "hand written" Roman, such as Antiqua */
			#define libandria4_buffercell_common_chara_FONT_Antique ( 3 )
			
			/* Blackletter ("Gothic") types. */
				/* Serif, wide-tipped, single-stroke, curvy Blackletter variant */
			#define libandria4_buffercell_common_chara_FONT_Fraktur ( 4 )
				/* Another curvy Blackletter, older than Fraktur */
			#define libandria4_buffercell_common_chara_FONT_Schwabacher ( 5 )
				/* Serif, wide-tipped, single-stroke, "straight" Blackletter variant */
			#define libandria4_buffercell_common_chara_FONT_Textualis ( 6 )
				/* Like Textualis, but double-stroke like Blackboard */
			#define libandria4_buffercell_common_chara_FONT_Texuaboard ( 7 )
			
			/* "Common print" types. */
				/* Serif, thick verticals & thin horizontals; stereotypical "modern" serif font */
			#define libandria4_buffercell_common_chara_FONT_Didonic ( 8 )
				/* Serif, Didone style with thicker elements very so; similar in 'weight' to Blackletter */
			#define libandria4_buffercell_common_chara_FONT_Fatface ( 9 )
				/* switch thick and narrow line widths; e.g. thin verticals, thick horizontals */
			#define libandria4_buffercell_common_chara_FONT_ReverseDidonic ( 10 )
				/* e.g. Courier, a rounded slab-serif; Courier itself is public-domain */
			#define libandria4_buffercell_common_chara_FONT_Curvislab ( 11 )
				/* more angular slab-serif, e.g. Rockwell */
			#define libandria4_buffercell_common_chara_FONT_Angular ( 12 )
				/* technically bolded, but just treated as a font; serif, mono-width, */
				/*  double-strokes where Didone are thick; MUST combine well with bold */
			#define libandria4_buffercell_common_chara_FONT_Blackboard ( 13 )
			
			/* "Slightly fancy" types. */
				/* not the same as Oblique, but is slanted! Use e.g. long 's'! Single-stroke */
			#define libandria4_buffercell_common_chara_FONT_Italic ( 14 )
				/* an Italic relative with flourishes like exagerated serifs */
			#define libandria4_buffercell_common_chara_FONT_Swash ( 15 )
				/* mono-width & single-stroke, curvy, base on some standard cursive script such as Palmer Method */
			#define libandria4_buffercell_common_chara_FONT_Cursive ( 16 )
				/* styles like Copperplate, Ronde */
			#define libandria4_buffercell_common_chara_FONT_Formal ( 17 )
			
			/* "Fully fancy  types.*/
				/* English Chancery, not Cursive; technically a variant of Blackletter */
			#define libandria4_buffercell_common_chara_FONT_Chancery ( 18 )
				/* wide-tipped & single-stroke, curvy, some common calligraphic script */
			#define libandria4_buffercell_common_chara_FONT_Calligraphy ( 19 )
				/* styles like Chinese Caoshu and Japanese Sosho styles */
			#define libandria4_buffercell_common_chara_FONT_Brushed ( 20 )
		
		#define libandria4_buffercell_common_chara_UNUSED_baseval ( (uint32_t)31 )
		#define libandria4_buffercell_common_chara_UNUSED_offset ( (uint32_t)26 )
		#define libandria4_buffercell_common_chara_UNUSED_multiplier \
			( (uint32_t)( 1 << libandria4_buffercell_common_chara_UNUSED_offset ) )
				/* I believe this should equal 4160749568 */
		#define libandria4_buffercell_common_chara_UNUSED_mask \
			( libandria4_buffercell_common_chara_UNUSED_baseval << \
				libandria4_buffercell_common_chara_UNUSED_offset )
	
	
	
	typedef int (*libandria4_termbuffer_generic_generic)
		(
			libandria4_termbuffer_generic*
		);
	typedef int (*libandria4_termbuffer_generic_cellsetter)
		(
			libandria4_termbuffer_generic*,
				uint32_t /* x */, uint32_t /* y */,
				libandria4_buffercell_common
		);
	typedef int (*libandria4_termbuffer_generic_blocksetter)
		(
			libandria4_termbuffer_generic*,
				uint32_t /* x */, uint32_t /* y */,
				uint32_t /* w */, uint32_t /* h */,
				libandria4_buffercell_common*
		);
	typedef int (*libandria4_termbuffer_generic_cellgetter)
		(
			libandria4_termbuffer_generic*,
				uint32_t /* x */, uint32_t /* y */,
				libandria4_termbuffer_func_receiver
		);
	typedef int (*libandria4_termbuffer_generic_blockgetter)
		(
			libandria4_termbuffer_generic*,
				uint32_t /* x */, uint32_t /* y */,
				uint32_t /* w */, uint32_t /* h */,
				libandria4_termbuffer_func_receiver
		);
	typedef int (*libandria4_termbuffer_common_scroll)
		(
			libandria4_termbuffer_generic*,
				libandria4_termbuffer_directions /* dir */,
				libandria4_buffercell_common /* fill */,
				uint32_t /* x */, uint32_t /* y */,
				uint32_t /* w */, uint32_t /* h */
		);
	typedef int (*libandria4_termbuffer_generic_resizer)
		(
			libandria4_termbuffer_generic*,
				uint32_t /* new_w */, uint32_t /* new_h */
		);
	typedef struct libandria4_termbuffer_generic_vtab
	{
		libandria4_termbuffer_generic_generic alertuser;
		
		libandria4_termbuffer_generic_cellsetter setcell;
		libandria4_termbuffer_generic_blocksetter setblock;
		
		libandria4_termbuffer_generic_cellgetter getcell;
		libandria4_termbuffer_generic_blockgetter getblock;
		
		libandria4_termbuffer_common_scroll scroll;
		libandria4_termbuffer_generic_resizer resize;
		
	} libandria4_termbuffer_generic_vtab;
	
	struct libandria4_termbuffer_generic
	{
		libandria4_termbuffer_generic_vtab *funcs;
		
			/* Measured in character cells, not in e.g. pixels, or inches. */
		uint32_t width, height;
		
		libandria4_memfuncs_t *mfuncs;
		libandria4_commonio_handle *messaging;
	};
	
	typedef struct libandria4_termbuffer_func_receiver
	{
		uintptr_t id;
		
		int (*func)
			(
				libandria4_termbuffer_func_receiver*,
					uint32_t /* width aka x */, uint32_t /* height aka y */,
					libandria4_buffercell_common
			);
		
	} libandria4_termbuffer_func_receiver;
	
	
	extern libandria4_termbuffer_generic_vtab libandria4_termbuffer_common_vtab;
	
#endif
/* End libandria4 text stdbuffer.h */

