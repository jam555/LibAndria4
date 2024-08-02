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

#ifndef LIBANDRIA4_TEXT_CHARSETS_EBCDICInvariant_H
# define LIBANDRIA4_TEXT_CHARSETS_EBCDICInvariant_H
	
	#include "general.h"
	
	
	/* This needs to be brought into compliance with the abbreviations. */
	/*  Probably need to augment the abbreviations in the process. The */
	/*  current postfixes also need to be brought more in compliance with */
	/*  their descriptions too. */
	/* Several entries are noted in comments, but not actually entered: that */
	/*  needs to be fixed. */
	/* Also, several entries need to be converted to alternate forms that */
	/*  are described in comments. */
	
	
	/* EBCDIC has several different variations. The invariant subset is */
	/*  below, so that it can be used either directly, or as a shared base */
	/*  for multiple specific variants. */
	
	
		/* Finder for the Invariant characters in the multiple EBCDIC */
		/*  character sets. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant( character ) \
		LIBANDRIA4_CHARSETS_GATECHAR( \
			LIBANDRIA4_CHARSETS_EBCDICInvariant_, \
			LIBANDRIA4_CHARSETS_ABBREVIATIONS( character ) \
		)
	
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_null (), 0x00
	
		/* Same meaning as with ASCII. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_startofheader (), 0x01
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_startoftext (), 0x02
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_endoftext (), 0x03
	
		/* "Punch off". Select. Takes single-byte parameter. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_pf (), 0x04
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_horizontaltab (), 0x05
	
		/* "Lower case". RNL. Forced linebreak, resets "IT" mode. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_lc (), 0x06
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_delete (), 0x07
	
		/* Graphic escape. Following character sourced from code page 310. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_ge (), 0x08
		/* SPS. Begin superscript or end subscript. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_rlf (), 0x09
	
		/* Start of Manual Message. Repeat a printing buffer. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_smm (), 0x0A
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_verticaltab (), 0x0B
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_formfeed (), 0x0C
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_carriagereturn (), 0x0D
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_shiftout (), 0x0E
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_shiftin (), 0x0F
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_datalinkescape (), 0x10
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_devicecontrol1 (), 0x11
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_dc2 (), 0x12
	
		/* Tape mark, aka DC3. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_tm (), 0x13
		/* Restore/Enable Presentation. Resumes output after BYP/INP. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_res (), 0x14
	
		/* NL maps to UNICODE's C1 character NEL. Sometimes swapped with */
		/*  EBCDIC 0x25 LF per Unix convention. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_nl (), 0x15
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_backspace (), 0x16
	
		/* Program operator communication. Followed by two one-byte */
		/*  operators that identify a specific function. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_poc (), 0x17
		/* Cancel. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_cancel (), 0x18
		/* End of Medium. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_endofmedium (), 0x19
	
		/* Unit backspace. A "fractional" (?) backspace. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_ubs (), 0x1A
	
		/* Customer use 1. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_cu1 (), 0x1B
	
		/* Directly equivalent to ASCII fs/gs/rs/us. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_fileseparator (), 0x1C
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_groupseparator (), 0x1D
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_recordseparator (), 0x1E
		/* aka ITB if used to end an "intermediate block". */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_unitseparator (), 0x1F
	
	/* These next 3 are used by the S/360 CPU edit instruction. IFS is */
	/*  apparently also used? */
		/* Digit select. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_ds (), 0x20
		/* Start of significance. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_sos (), 0x21
		/* Field separator. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_fieldseparator (), 0x22
	
	/* 0x23: WUS. Word underscore. Applies underscore to immediately */
	/*  preceding word. */
	
		/* Bypass/INP. Deactivates output, surpressing everything EXCEPT */
		/*  transmission control codes and RES/ENP. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_bypass (), 0x24
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_linefeed (), 0x25
	
		/* End of Transmission Block. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_endoftransmissionblock () 0x26
		/* Escape. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_escape (), 0x27
	
	/* 0x28: SA. Set Attribute. Marks the begining of a fixed-length */
	/*  device-specific control sequence. Use CSP instead. */
	/* 0x29: SFE. Start field extended. As SA, but variable-length. ALSO */
	/*  deprecated in favor of CSP. */
	
		/* Set mode/SWitch. Device specific, sets a mode of operation. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_sm (), 0x2A
	
		/* CSP (Control sequence prefix). Marks the start of a */
		/*  device-specific variable-length control sequence. Follow by */
		/*  "class" byte specifying category of control function, a count */
		/*  byte specifying sequence length (not including CSP nor class */
		/*  byte), a type byte specifying function WITHIN the category */
		/*  (included in length), and zero or more parameter bytes. */
		/* Was formerly "customer use 2", but got repurposed. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_cu2 (), 0x2B
	
	/* 0x2C: MFA. Modify field attribute. Replaced by CSP, variable-length */
	/*  sequences. */
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_enquiry (), 0x2D
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_acknowledge (), 0x2E
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_bell (), 0x2F
	
		/* Synchronous idle. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_synchronousidle (), 0x32
	
	/* 0x33: IR. Index return. Either move to start of next line (see also */
	/*  NL), of end information unit (see also IUS/ITB). */
	
		/* Presentation position. Follow by two one-byte parameters (first */
		/*  function, then number of either column or line) to set current */
		/*  position. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_pp (), 0x34
		/* Transparent. Follow by one-byte parameter specifying number of */
		/*  transparent bytes to follow. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_trn (), 0x35
	
		/* Numeric backspace. Move backwards widtyh of one character. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_nbs (), 0x36
	
		/* End of Transmission. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_endoftransmission (), 0x37
	
	/* 0x38: SBS. Subscript. Begin subscript or end superscript. */
	/* 0x39: IT. Indent tab. Indents current and all following lines, until */
	/*  RNL or RFF is encountered. */
	/* 0x3A: RFF. Required form feed. Page-break, and resets Indent Tab */
	/*  mode. */
	
		/* Customer use 3, except now 2 instead, because the previous cu2 */
		/*  got repurposed as CSP. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_cu3 (), 0x3B
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_dc4 (), 0x3C
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_negativeacknowledge (), 0x3D
	
		/* Substitute. */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_substitute (), 0x3F
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_space (), 0x40
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_cent (), 0x4A
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_dot (), 0x4B
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_gr (), 0x4C
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_oppar (), 0x4D
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_plus (), 0x4E
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_solidvbar (), 0x4F
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_amp (), 0x50
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_excl (), 0x5A
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_dollar (), 0x5B
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_asterisk (), 0x5C
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_clpar (), 0x5D
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_semicolon (), 0x5E
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_negation (), 0x5F
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_hyphen (), 0x60
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_forwardslash (), 0x61
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_brokenvbar (), 0x6A
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_comma (), 0x6B
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_percent (), 0x6C
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_underscore (), 0x6D
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_ls (), 0x6E
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_ques (), 0x6F
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_graveaccent (), 0x79
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_colon (), 0x7A
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_hash (), 0x7B
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_at (), 0x7C
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_apostrophe (), 0x7D
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_eq (), 0x7E
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_doublequote (), 0x7F
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_a (), 0x81
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_b (), 0x82
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_c (), 0x83
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_d (), 0x84
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_e (), 0x85
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_f (), 0x86
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_g (), 0x87
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_h (), 0x88
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_i (), 0x89
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_plusminus (), 0x8F
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_j (), 0x91
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_k (), 0x92
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_l (), 0x93
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_m (), 0x94
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_n (), 0x95
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_o (), 0x96
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_p (), 0x97
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_q (), 0x98
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_r (), 0x99
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_tilde (), 0xA1
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_s (), 0xA2
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_t (), 0xA3
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_u (), 0xA4
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_v (), 0xA5
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_w (), 0xA6
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_x (), 0xA7
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_y (), 0xA8
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_z (), 0xA9
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_caret (), 0xB0
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_opsqr (), 0x8A
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_clsqr (), 0x8B
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_opcrl (), 0xC0
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_A (), 0xC1
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_B (), 0xC2
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_C (), 0xC3
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_D (), 0xC4
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_E (), 0xC5
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_F (), 0xC6
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_G (), 0xC7
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_H (), 0xC8
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_I (), 0xC9
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_clcrl (), 0xD0
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_J (), 0xD1
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_K (), 0xD2
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_L (), 0xD3
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_M (), 0xD4
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_N (), 0xD5
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_O (), 0xD6
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_P (), 0xD7
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_Q (), 0xD8
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_R (), 0xD9
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_backslash (), 0xE0
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_S (), 0xE2
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_T (), 0xE3
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_U (), 0xE4
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_V (), 0xE5
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_W (), 0xE6
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_X (), 0xE7
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_Y (), 0xE8
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_Z (), 0xE9
	
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_0 (), 0xF0
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_1 (), 0xF1
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_2 (), 0xF2
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_3 (), 0xF3
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_4 (), 0xF4
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_5 (), 0xF5
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_6 (), 0xF6
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_7 (), 0xF7
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_8 (), 0xF8
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_9 (), 0xF9
	
		/* A synchronization character. Also used as filler, I guess because */
		/*  on some punch-card readers interpretted the LACK of a hole as a */
		/*  1? */
	#define LIBANDRIA4_CHARSETS_EBCDICInvariant_eightones (), 0xFF
	
#endif
/* End relocated: libandria4 text charsets EBCDICInvariant.h */
