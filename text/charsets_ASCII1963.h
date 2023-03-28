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

#ifndef LIBANDRIA4_MACROTIME_CHARSETS_ASCII1963_H
# define LIBANDRIA4_MACROTIME_CHARSETS_ASCII1963_H
	
	#include "charsets_general.h"
	
	
	/* Note: this still needs the same abbreviation standardizations that */
	/*  ASCII, and at least somewhat EBCDIC Invariant, need. */
	
	
	/* The 1963 version of ASCII is not a 100% match to the normal version. */
	/*  Names have been kept to the standard abbreviations where a sensible */
	/*  version already exists. Notable is that fe0 exists instead of */
	/*  backspace: for most uses it'll presumably be backspace, but it's */
	/*  actually more generic and thus flexible than just being backspace. */
	
	
		/* Finder for the ASCII 1963 character sets. */
	#define LIBANDRIA4_CHARSETS_ASCII1963( character ) \
		LIBANDRIA4_CHARSETS_GATECHAR( \
			LIBANDRIA4_CHARSETS_ASCII1963_, \
			LIBANDRIA4_CHARSETS_ABBREVIATIONS( character ) \
		)
	
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_null (), 0x00
	
		/* "Start of message" */
	#define LIBANDRIA4_CHARSETS_ASCII1963_startofheader (), 0x01
		/* "End of address" */
	#define LIBANDRIA4_CHARSETS_ASCII1963_startoftext (), 0x02
		/* "End of message" */
	#define LIBANDRIA4_CHARSETS_ASCII1963_endoftext (), 0x03
	#define LIBANDRIA4_CHARSETS_ASCII1963_endoftransmission (), 0x04
	
		/* "Who are you...?" */
	#define LIBANDRIA4_CHARSETS_ASCII1963_enquiry (), 0x05
		/* "Are you...?" became acknowledge. I have left it as "ru" because */
		/*  that arguably has a different (specifically, more restrictive) */
		/*  meaning. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_ru (), 0x06
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_bell (), 0x07
	
		/* "Format effector" became backspace. It apparently was intended as */
		/*  a "generic format effector", and specifically was the start of a */
		/*  contiguous block that ended with carraige-return: this should be */
		/*  taken as a hint of the general sort of behavior expected from */
		/*  fe0, particularly that it is NOT a "alternate character" switch: */
		/*  indeed, ASCII only has such in either the form of "shift in", */
		/*  "shift out", and "data link escape", the device control */
		/*  characters, particular usages of "escape", or if you assume that */
		/*  overstrike is allowed, in which case it's just because you can */
		/*  add another character to an existing one. It's pretty natural */
		/*  that it became backspace (which originally did not delete */
		/*  characters, that instead stereotypically being done with a */
		/*  character sequence instead, consisting of backspace followed by */
		/*  either null, space, or delete, depending on application */
		/*  perspective), the alternatives presumably being either */
		/*  "backline", "backform", or if printing on both side of paper was */
		/*  supported then "flipform". */
	#define LIBANDRIA4_CHARSETS_ASCII1963_fe0 (), 0x08
	
		/* Was also described as "skip" for punched cards. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_horizontaltab (), 0x09
	#define LIBANDRIA4_CHARSETS_ASCII1963_linefeed (), 0x0A
	#define LIBANDRIA4_CHARSETS_ASCII1963_verticaltab (), 0x0B
	#define LIBANDRIA4_CHARSETS_ASCII1963_formfeed (), 0x0C
	#define LIBANDRIA4_CHARSETS_ASCII1963_carriagereturn (), 0x0D
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_shiftout (), 0x0E
	#define LIBANDRIA4_CHARSETS_ASCII1963_shiftin (), 0x0F
	#define LIBANDRIA4_CHARSETS_ASCII1963_datalinkescape (), 0x10
	
		/* DC1 and DC2 are sometimes used as 'XON'. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_devicecontrol1 (), 0x11
	#define LIBANDRIA4_CHARSETS_ASCII1963_devicecontrol2 (), 0x12
		/* DC3 and DC4 are sometimes used as 'XOFF'. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_devicecontrol3 (), 0x13
		/* DC4 is apparently intended for "Stop" in '63. Though I think it */
		/*  actually often gets used for that anyways... OFTEN, but not */
		/*  always. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_devicecontrol4 (), 0x14
	
		/* "Error", became negative-acknowledge. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_error (), 0x15
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_synchronousidle (), 0x16
	#define LIBANDRIA4_CHARSETS_ASCII1963_endofmedium (), 0x17
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_s0 (), 0x18
	#define LIBANDRIA4_CHARSETS_ASCII1963_s1 (), 0x19
	#define LIBANDRIA4_CHARSETS_ASCII1963_s2 (), 0x1A
	#define LIBANDRIA4_CHARSETS_ASCII1963_s3 (), 0x1B
	#define LIBANDRIA4_CHARSETS_ASCII1963_s4 (), 0x1C
	#define LIBANDRIA4_CHARSETS_ASCII1963_s5 (), 0x1D
	#define LIBANDRIA4_CHARSETS_ASCII1963_s6 (), 0x1E
	#define LIBANDRIA4_CHARSETS_ASCII1963_s7 (), 0x1F
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_space (), 0x20
	#define LIBANDRIA4_CHARSETS_ASCII1963_excl (), 0x21
	#define LIBANDRIA4_CHARSETS_ASCII1963_dblq (), 0x22
	#define LIBANDRIA4_CHARSETS_ASCII1963_hash (), 0x23
	#define LIBANDRIA4_CHARSETS_ASCII1963_dolr (), 0x24
	#define LIBANDRIA4_CHARSETS_ASCII1963_perc (), 0x25
	#define LIBANDRIA4_CHARSETS_ASCII1963_ampr (), 0x26
	#define LIBANDRIA4_CHARSETS_ASCII1963_sinq (), 0x27
	#define LIBANDRIA4_CHARSETS_ASCII1963_oppr (), 0x28
	#define LIBANDRIA4_CHARSETS_ASCII1963_clpr (), 0x29
	#define LIBANDRIA4_CHARSETS_ASCII1963_ast (), 0x2A
	#define LIBANDRIA4_CHARSETS_ASCII1963_plus () 0x2B
	#define LIBANDRIA4_CHARSETS_ASCII1963_coma (), 0x2C
	#define LIBANDRIA4_CHARSETS_ASCII1963_minu (), 0x2D
	#define LIBANDRIA4_CHARSETS_ASCII1963_perd (), 0x2E
	#define LIBANDRIA4_CHARSETS_ASCII1963_forwardslash (), 0x2F
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0 (), 0x30
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_1 (), 0x31
	#define LIBANDRIA4_CHARSETS_ASCII1963_2 (), 0x32
	#define LIBANDRIA4_CHARSETS_ASCII1963_3 (), 0x33
	#define LIBANDRIA4_CHARSETS_ASCII1963_4 (), 0x34
	#define LIBANDRIA4_CHARSETS_ASCII1963_5 (), 0x35
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_6 (), 0x36
	#define LIBANDRIA4_CHARSETS_ASCII1963_7 (), 0x37
	#define LIBANDRIA4_CHARSETS_ASCII1963_8 (), 0x38
	#define LIBANDRIA4_CHARSETS_ASCII1963_9 (), 0x39
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_cln (), 0x3A
	#define LIBANDRIA4_CHARSETS_ASCII1963_scln (), 0x3B
	#define LIBANDRIA4_CHARSETS_ASCII1963_lthn (), 0x3C
	#define LIBANDRIA4_CHARSETS_ASCII1963_eq (), 0x3D
	#define LIBANDRIA4_CHARSETS_ASCII1963_gthn (), 0x3E
	#define LIBANDRIA4_CHARSETS_ASCII1963_ques (), 0x3F
	#define LIBANDRIA4_CHARSETS_ASCII1963_at (), 0x40
	
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_A (), 0x41
	#define LIBANDRIA4_CHARSETS_ASCII1963_B (), 0x42
	#define LIBANDRIA4_CHARSETS_ASCII1963_C (), 0x43
	#define LIBANDRIA4_CHARSETS_ASCII1963_D (), 0x44
	#define LIBANDRIA4_CHARSETS_ASCII1963_E (), 0x45
	#define LIBANDRIA4_CHARSETS_ASCII1963_F (), 0x46
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_G (), 0x47
	#define LIBANDRIA4_CHARSETS_ASCII1963_H (), 0x48
	#define LIBANDRIA4_CHARSETS_ASCII1963_I (), 0x49
	#define LIBANDRIA4_CHARSETS_ASCII1963_J (), 0x4A
	#define LIBANDRIA4_CHARSETS_ASCII1963_K (), 0x4B
	#define LIBANDRIA4_CHARSETS_ASCII1963_L (), 0x4C
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_M (), 0x4D
	#define LIBANDRIA4_CHARSETS_ASCII1963_N (), 0x4E
	#define LIBANDRIA4_CHARSETS_ASCII1963_O (), 0x4F
	#define LIBANDRIA4_CHARSETS_ASCII1963_P (), 0x50
	#define LIBANDRIA4_CHARSETS_ASCII1963_Q (), 0x51
	#define LIBANDRIA4_CHARSETS_ASCII1963_R (), 0x52
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_S (), 0x53
	#define LIBANDRIA4_CHARSETS_ASCII1963_T (), 0x54
	#define LIBANDRIA4_CHARSETS_ASCII1963_U (), 0x55
	#define LIBANDRIA4_CHARSETS_ASCII1963_V (), 0x56
	#define LIBANDRIA4_CHARSETS_ASCII1963_W (), 0x57
	#define LIBANDRIA4_CHARSETS_ASCII1963_X (), 0x58
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_Y (), 0x59
	#define LIBANDRIA4_CHARSETS_ASCII1963_Z (), 0x5A
	
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_opsq (), 0x5B
	#define LIBANDRIA4_CHARSETS_ASCII1963_backslash (), 0x5C
	#define LIBANDRIA4_CHARSETS_ASCII1963_clsq (), 0x5D
	
		/* These explicitly do NOT match normal ASCII. 'E' is caret, and 'F' */
		/*  is underscore. And yes, these are graphical arrows. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_uparr (), 0x5E
	#define LIBANDRIA4_CHARSETS_ASCII1963_lftarr (), 0x5F
	
	
		/* Here's an empty space! Note that 'grave accent' would be first, */
		/*  and then the lowercase letters. No curly brackets, vertical bar, */
		/*  or tilde either. There's something like 28 unused values here. */
		/*  It's worth noting that the normal version moves two control */
		/*  codes, leaving only 'delete' "above" the graphical characters. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_acknowledge (), 0x7C
		/* Gap again! This became the closing curly bracket, but in 1963 was */
		/*  described as an unassigned control character. */
	#define LIBANDRIA4_CHARSETS_ASCII1963_escape (), 0x7E
	
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_delete (), 0x7F
	
	
	
	
	/* Reverse lookup entries: */
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x00 (), null
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x01 (), startofheader
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x02 (), startoftext
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x03 (), endoftext
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x04 (), endoftransmission
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x05 (), enquiry
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x06 (), ru
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x07 (), bell
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x08 (), fe0
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x09 (), horizontaltab
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x0A (), linefeed
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x0B (), verticaltab
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x0C (), formfeed
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x0D (), carriagereturn
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x0E (), shiftout
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x0F (), shiftin
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x10 (), datalinkescape
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x11 (), devicecontrol1
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x12 (), devicecontrol2
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x13 (), devicecontrol3
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x14 (), devicecontrol4
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x15 (), error
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x16 (), synchronousidle
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x17 (), endofmedium
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x18 (), s0
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x19 (), s1
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x1A (), s2
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x1B (), s3
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x1C (), s4
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x1D (), s5
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x1E (), s6
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x1F (), s7
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x20 (), space
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x21 (), excl
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x22 (), dblq
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x23 (), hash
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x24 (), dolr
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x25 (), perc
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x26 (), ampr
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x27 (), sinq
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x28 (), oppr
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x29 (), clpr
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x2A (), ast
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x2B (), plus
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x2C (), coma
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x2D (), minu
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x2E (), perd
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x2F (), fsls
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x30 (), 0
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x31 (), 1
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x32 (), 2
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x33 (), 3
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x34 (), 4
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x35 (), 5
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x36 (), 6
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x37 (), 7
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x38 (), 8
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x39 (), 9
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x3A (), cln
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x3B (), scln
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x3C (), lthn
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x3D (), eq
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x3E (), gthn
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x3F (), ques
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x40 (), at
	
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x41 (), A
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x42 (), B
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x43 (), C
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x44 (), D
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x45 (), E
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x46 (), F
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x47 (), G
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x48 (), H
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x49 (), I
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x4A (), J
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x4B (), K
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x4C (), L
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x4D (), M
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x4E (), N
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x4F (), O
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x50 (), P
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x51 (), Q
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x52 (), R
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x53 (), S
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x54 (), T
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x55 (), U
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x56 (), V
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x57 (), W
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x58 (), X
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x59 (), Y
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x5A (), Z
	
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x5B (), opsq
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x5C (), bsls
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x5D (), clsq
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x5E (), uparr
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x5F (), lftarr
	
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x7C (), acknowledge
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x7E (), escape
	
	
	#define LIBANDRIA4_CHARSETS_ASCII1963_0x7F (), delete
	
#endif
/* End libandria4 text charsets_ASCII1963.h */
