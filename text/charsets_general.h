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

#ifndef LIBANDRIA4_MACROTIME_CHARSETS_GENERAL_H
# define LIBANDRIA4_MACROTIME_CHARSETS_GENERAL_H
	
	#include "../basic/simpleops.h"
	#include "../basic/arraccess.h"
	
	
	/* This is a general interface to the entire character-sets macro */
	/*  system. LIBANDRIA4_CHARSETS_STD( character ) is defined at the very end to */
	/*  provide an automatically adjustable default interface. Use it unless */
	/*  you have reason not to (e.g. an assumption of a specific character */
	/*  set). If you want to override it, then set LIBANDRIA4_CHARSETS_SETSTD to */
	/*  one of the following LIBANDRIA4_CHARSETS_SETSTD_USE* macros, or set */
	/*  LIBANDRIA4_MACROTIME_CHARSETS_GENERAL_H_INCLUDEHOOK to a file description */
	/*  appropriate for usage by the preprocessor's include directive. */
	
	
	
	#define LIBANDRIA4_CHARSETS_SETSTD_USEASCII 0
	#define LIBANDRIA4_CHARSETS_SETSTD_USEEBCDICInvariant 1
	#define LIBANDRIA4_CHARSETS_SETSTD_USEASCII1963 2
	
	
	
	/* Note: while the concept behind this is solid, it hasn't been tested */
	/*  yet. Beware. */
	/* Also note: the list of abbreviations is VERY MUCH not finished yet. */
	/* Need a list of acceptable character postfixes, for reference when */
	/*  adding other character sets. */
	
	/* Current acceptable postfixes: summary */
		/* The single-digit numbers (0-1) and letters (a-z, A-Z) */
		/* Spelled out forms of the single-digit numbers (e.g. "nine") */
		/* "space", or a blank space */
		/* "nul" or "null" */
		/* The UN phonetic alphabet (e.g. "bravo" for b), fully lowercase or */
		/*  fully uppercase */
		/* Some UN phonetic alphabet pronunciations ("tree", "fife", and */
		/*  "niner") */
		/* Some Greek letter names as used in English (e.g. "upsilon" for */
		/*  y), fully lowercase or fully uppercase */
	
	
	
		/* Utility macro, don't use yourself. Should probably have a similar */
		/*  macro system to equate different names to their "standard" */
		/*  abbreviation... */
		/* *_DOWNSELECT() checks it's arguments to see if the first one is a */
		/*  parenthese pair, and if so, returns the second argument; if not, */
		/*  then it returns a parenthese pair, for the sake of detection. */
	#define LIBANDRIA4_CHARSETS_DOWNSELECT( ... ) \
		LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( LIBANDRIA4_RETURN_1ST( __VA_ARGS__ ) ) ) \
			( LIBANDRIA4_RETURN_2ND( __VA_ARGS__ ), () )
	
		/* *_GATECHAR() short-circuits execution if the provided character */
		/*  is a parenthese pair. */
	#define LIBANDRIA4_CHARSETS_GATECHAR( set, character ) \
		LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( character ) ) \
			( (), LIBANDRIA4_CHARSETS_DOWNSELECT( LIBANDRIA4_CAT( set, character ) ) )
	
	
	
	
		/* Finder for the ASCII character set. */
	#define LIBANDRIA4_CHARSETS_ASCII( character ) \
		LIBANDRIA4_CHARSETS_GATECHAR( \
			LIBANDRIA4_CHARSETS_ASCII_, LIBANDRIA4_CHARSETS_ABBREVIATIONS( character ) \
		)
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_null (), 0x00
	
	#define LIBANDRIA4_CHARSETS_ASCII_startofheader (), 0x01
	#define LIBANDRIA4_CHARSETS_ASCII_startoftext (), 0x02
	#define LIBANDRIA4_CHARSETS_ASCII_endoftext (), 0x03
	#define LIBANDRIA4_CHARSETS_ASCII_endoftransmission (), 0x04
	
	#define LIBANDRIA4_CHARSETS_ASCII_enquiry (), 0x05
	#define LIBANDRIA4_CHARSETS_ASCII_acknowledge (), 0x06
	
	#define LIBANDRIA4_CHARSETS_ASCII_bell (), 0x07
	#define LIBANDRIA4_CHARSETS_ASCII_backspace (), 0x08
	
	#define LIBANDRIA4_CHARSETS_ASCII_horizontaltab (), 0x09
	#define LIBANDRIA4_CHARSETS_ASCII_linefeed (), 0x0A
	#define LIBANDRIA4_CHARSETS_ASCII_verticaltab (), 0x0B
	#define LIBANDRIA4_CHARSETS_ASCII_formfeed (), 0x0C
	#define LIBANDRIA4_CHARSETS_ASCII_carriagereturn (), 0x0D
	
	#define LIBANDRIA4_CHARSETS_ASCII_shiftout (), 0x0E
	#define LIBANDRIA4_CHARSETS_ASCII_shiftin (), 0x0F
	#define LIBANDRIA4_CHARSETS_ASCII_datalinkescape (), 0x10
	
	#define LIBANDRIA4_CHARSETS_ASCII_devicecontrol1 (), 0x11
	#define LIBANDRIA4_CHARSETS_ASCII_devicecontrol2 (), 0x12
	#define LIBANDRIA4_CHARSETS_ASCII_devicecontrol3 (), 0x13
	#define LIBANDRIA4_CHARSETS_ASCII_devicecontrol4 (), 0x14
	
	#define LIBANDRIA4_CHARSETS_ASCII_negativeacknowledge (), 0x15
	#define LIBANDRIA4_CHARSETS_ASCII_synchronousidle (), 0x16
	#define LIBANDRIA4_CHARSETS_ASCII_endoftransmissionblock (), 0x17
	#define LIBANDRIA4_CHARSETS_ASCII_cancel (), 0x18
	
	#define LIBANDRIA4_CHARSETS_ASCII_endofmedium (), 0x19
	
	#define LIBANDRIA4_CHARSETS_ASCII_substitute (), 0x1A
	#define LIBANDRIA4_CHARSETS_ASCII_escape (), 0x1B
	
	#define LIBANDRIA4_CHARSETS_ASCII_fileseparator (), 0x1C
	#define LIBANDRIA4_CHARSETS_ASCII_groupseparator (), 0x1D
	#define LIBANDRIA4_CHARSETS_ASCII_recordseparator (), 0x1E
	#define LIBANDRIA4_CHARSETS_ASCII_unitseparator (), 0x1F
	
	#define LIBANDRIA4_CHARSETS_ASCII_space (), 0x20
	
	#define LIBANDRIA4_CHARSETS_ASCII_excl (), 0x21
	#define LIBANDRIA4_CHARSETS_ASCII_dblq (), 0x22
	#define LIBANDRIA4_CHARSETS_ASCII_hash (), 0x23
	#define LIBANDRIA4_CHARSETS_ASCII_dolr (), 0x24
	#define LIBANDRIA4_CHARSETS_ASCII_perc (), 0x25
	#define LIBANDRIA4_CHARSETS_ASCII_ampr (), 0x26
	#define LIBANDRIA4_CHARSETS_ASCII_sinq (), 0x27
	#define LIBANDRIA4_CHARSETS_ASCII_oppr (), 0x28
	#define LIBANDRIA4_CHARSETS_ASCII_clpr (), 0x29
	#define LIBANDRIA4_CHARSETS_ASCII_ast (), 0x2A
	#define LIBANDRIA4_CHARSETS_ASCII_plus (), 0x2B
	#define LIBANDRIA4_CHARSETS_ASCII_coma (), 0x2C
	#define LIBANDRIA4_CHARSETS_ASCII_minu (), 0x2D
	#define LIBANDRIA4_CHARSETS_ASCII_perd (), 0x2E
	#define LIBANDRIA4_CHARSETS_ASCII_forwardslash (), 0x2F
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_0 (), 0x30
	
	#define LIBANDRIA4_CHARSETS_ASCII_1 (), 0x31
	#define LIBANDRIA4_CHARSETS_ASCII_2 (), 0x32
	#define LIBANDRIA4_CHARSETS_ASCII_3 (), 0x33
	#define LIBANDRIA4_CHARSETS_ASCII_4 (), 0x34
	#define LIBANDRIA4_CHARSETS_ASCII_5 (), 0x35
	
	#define LIBANDRIA4_CHARSETS_ASCII_6 (), 0x36
	#define LIBANDRIA4_CHARSETS_ASCII_7 (), 0x37
	#define LIBANDRIA4_CHARSETS_ASCII_8 (), 0x38
	#define LIBANDRIA4_CHARSETS_ASCII_9 (), 0x39
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_cln (), 0x3A
	#define LIBANDRIA4_CHARSETS_ASCII_scln (), 0x3B
	#define LIBANDRIA4_CHARSETS_ASCII_lthn (), 0x3C
	#define LIBANDRIA4_CHARSETS_ASCII_eq (), 0x3D
	#define LIBANDRIA4_CHARSETS_ASCII_gthn (), 0x3E
	#define LIBANDRIA4_CHARSETS_ASCII_ques (), 0x3F
	#define LIBANDRIA4_CHARSETS_ASCII_at (), 0x40
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_A (), 0x41
	#define LIBANDRIA4_CHARSETS_ASCII_B (), 0x42
	#define LIBANDRIA4_CHARSETS_ASCII_C (), 0x43
	#define LIBANDRIA4_CHARSETS_ASCII_D (), 0x44
	#define LIBANDRIA4_CHARSETS_ASCII_E (), 0x45
	#define LIBANDRIA4_CHARSETS_ASCII_F (), 0x46
	
	#define LIBANDRIA4_CHARSETS_ASCII_G (), 0x47
	#define LIBANDRIA4_CHARSETS_ASCII_H (), 0x48
	#define LIBANDRIA4_CHARSETS_ASCII_I (), 0x49
	#define LIBANDRIA4_CHARSETS_ASCII_J (), 0x4A
	#define LIBANDRIA4_CHARSETS_ASCII_K (), 0x4B
	#define LIBANDRIA4_CHARSETS_ASCII_L (), 0x4C
	
	#define LIBANDRIA4_CHARSETS_ASCII_M (), 0x4D
	#define LIBANDRIA4_CHARSETS_ASCII_N (), 0x4E
	#define LIBANDRIA4_CHARSETS_ASCII_O (), 0x4F
	#define LIBANDRIA4_CHARSETS_ASCII_P (), 0x50
	#define LIBANDRIA4_CHARSETS_ASCII_Q (), 0x51
	#define LIBANDRIA4_CHARSETS_ASCII_R (), 0x52
	
	#define LIBANDRIA4_CHARSETS_ASCII_S (), 0x53
	#define LIBANDRIA4_CHARSETS_ASCII_T (), 0x54
	#define LIBANDRIA4_CHARSETS_ASCII_U (), 0x55
	#define LIBANDRIA4_CHARSETS_ASCII_V (), 0x56
	#define LIBANDRIA4_CHARSETS_ASCII_W (), 0x57
	#define LIBANDRIA4_CHARSETS_ASCII_X (), 0x58
	
	#define LIBANDRIA4_CHARSETS_ASCII_Y (), 0x59
	#define LIBANDRIA4_CHARSETS_ASCII_Z (), 0x5A
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_opsq (), 0x5B
	#define LIBANDRIA4_CHARSETS_ASCII_backslash (), 0x5C
	#define LIBANDRIA4_CHARSETS_ASCII_clsq (), 0x5D
	#define LIBANDRIA4_CHARSETS_ASCII_car (), 0x5E
	#define LIBANDRIA4_CHARSETS_ASCII_und (), 0x5F
	#define LIBANDRIA4_CHARSETS_ASCII_grv (), 0x60
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_a (), 0x61
	#define LIBANDRIA4_CHARSETS_ASCII_b (), 0x62
	#define LIBANDRIA4_CHARSETS_ASCII_c (), 0x63
	#define LIBANDRIA4_CHARSETS_ASCII_d (), 0x64
	#define LIBANDRIA4_CHARSETS_ASCII_e (), 0x65
	#define LIBANDRIA4_CHARSETS_ASCII_f (), 0x66
	
	#define LIBANDRIA4_CHARSETS_ASCII_g (), 0x67
	#define LIBANDRIA4_CHARSETS_ASCII_h (), 0x68
	#define LIBANDRIA4_CHARSETS_ASCII_i (), 0x69
	#define LIBANDRIA4_CHARSETS_ASCII_j (), 0x6A
	#define LIBANDRIA4_CHARSETS_ASCII_k (), 0x6B
	#define LIBANDRIA4_CHARSETS_ASCII_l (), 0x6C
	
	#define LIBANDRIA4_CHARSETS_ASCII_m (), 0x6D
	#define LIBANDRIA4_CHARSETS_ASCII_n (), 0x6E
	#define LIBANDRIA4_CHARSETS_ASCII_o (), 0x6F
	#define LIBANDRIA4_CHARSETS_ASCII_p (), 0x70
	#define LIBANDRIA4_CHARSETS_ASCII_q (), 0x71
	#define LIBANDRIA4_CHARSETS_ASCII_r (), 0x72
	
	#define LIBANDRIA4_CHARSETS_ASCII_s (), 0x73
	#define LIBANDRIA4_CHARSETS_ASCII_t (), 0x74
	#define LIBANDRIA4_CHARSETS_ASCII_u (), 0x75
	#define LIBANDRIA4_CHARSETS_ASCII_v (), 0x76
	#define LIBANDRIA4_CHARSETS_ASCII_w (), 0x77
	#define LIBANDRIA4_CHARSETS_ASCII_x (), 0x78
	
	#define LIBANDRIA4_CHARSETS_ASCII_y (), 0x79
	#define LIBANDRIA4_CHARSETS_ASCII_z (), 0x7A
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_opcrl (), 0x7B
	#define LIBANDRIA4_CHARSETS_ASCII_vbar (), 0x7C
	#define LIBANDRIA4_CHARSETS_ASCII_clcrl (), 0x7D
	#define LIBANDRIA4_CHARSETS_ASCII_tild (), 0x7E
	#define LIBANDRIA4_CHARSETS_ASCII_delete (), 0x7F
	
	
	
	
	/* Reverse lookup entries: */
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x00 (), null
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x01 (), startofheader
	#define LIBANDRIA4_CHARSETS_ASCII_0x02 (), startoftext
	#define LIBANDRIA4_CHARSETS_ASCII_0x03 (), endoftext
	#define LIBANDRIA4_CHARSETS_ASCII_0x04 (), endoftransmission
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x05 (), enquiry
	#define LIBANDRIA4_CHARSETS_ASCII_0x06 (), acknowledge
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x07 (), bell
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x08 (), backspace
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x09 (), horizontaltab
	#define LIBANDRIA4_CHARSETS_ASCII_0x0A (), linefeed
	#define LIBANDRIA4_CHARSETS_ASCII_0x0B (), verticaltab
	#define LIBANDRIA4_CHARSETS_ASCII_0x0C (), formfeed
	#define LIBANDRIA4_CHARSETS_ASCII_0x0D (), carriagereturn
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x0E (), shiftout
	#define LIBANDRIA4_CHARSETS_ASCII_0x0F (), shiftin
	#define LIBANDRIA4_CHARSETS_ASCII_0x10 (), datalinkescape
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x11 (), devicecontrol1
	#define LIBANDRIA4_CHARSETS_ASCII_0x12 (), devicecontrol2
	#define LIBANDRIA4_CHARSETS_ASCII_0x13 (), devicecontrol3
	#define LIBANDRIA4_CHARSETS_ASCII_0x14 (), devicecontrol4
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x15 (), negativeacknowledge
	#define LIBANDRIA4_CHARSETS_ASCII_0x16 (), synchronousidle
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x17 (), endoftransmissionblock
	#define LIBANDRIA4_CHARSETS_ASCII_0x18 (), cancel
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x19 (), endofmedium
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x1A (), substitute
	#define LIBANDRIA4_CHARSETS_ASCII_0x1B (), escape
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x1C (), fileseparator
	#define LIBANDRIA4_CHARSETS_ASCII_0x1D (), groupseparator
	#define LIBANDRIA4_CHARSETS_ASCII_0x1E (), recordseparator
	#define LIBANDRIA4_CHARSETS_ASCII_0x1F (), unitseparator
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x20 (), space
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x21 (), excl
	#define LIBANDRIA4_CHARSETS_ASCII_0x22 (), dblq
	#define LIBANDRIA4_CHARSETS_ASCII_0x23 (), hash
	#define LIBANDRIA4_CHARSETS_ASCII_0x24 (), dolr
	#define LIBANDRIA4_CHARSETS_ASCII_0x25 (), perc
	#define LIBANDRIA4_CHARSETS_ASCII_0x26 (), ampr
	#define LIBANDRIA4_CHARSETS_ASCII_0x27 (), sinq
	#define LIBANDRIA4_CHARSETS_ASCII_0x28 (), oppr
	#define LIBANDRIA4_CHARSETS_ASCII_0x29 (), clpr
	#define LIBANDRIA4_CHARSETS_ASCII_0x2A (), ast
	#define LIBANDRIA4_CHARSETS_ASCII_0x2B (), plus
	#define LIBANDRIA4_CHARSETS_ASCII_0x2C (), coma
	#define LIBANDRIA4_CHARSETS_ASCII_0x2D (), minu
	#define LIBANDRIA4_CHARSETS_ASCII_0x2E (), perd
	#define LIBANDRIA4_CHARSETS_ASCII_0x2F (), forwardslash
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x30 (), 0
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x31 (), 1
	#define LIBANDRIA4_CHARSETS_ASCII_0x32 (), 2
	#define LIBANDRIA4_CHARSETS_ASCII_0x33 (), 3
	#define LIBANDRIA4_CHARSETS_ASCII_0x34 (), 4
	#define LIBANDRIA4_CHARSETS_ASCII_0x35 (), 5
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x36 (), 6
	#define LIBANDRIA4_CHARSETS_ASCII_0x37 (), 7
	#define LIBANDRIA4_CHARSETS_ASCII_0x38 (), 8
	#define LIBANDRIA4_CHARSETS_ASCII_0x39 (), 9
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x3A (), cln
	#define LIBANDRIA4_CHARSETS_ASCII_0x3B (), scln
	#define LIBANDRIA4_CHARSETS_ASCII_0x3C (), lthn
	#define LIBANDRIA4_CHARSETS_ASCII_0x3D (), eq
	#define LIBANDRIA4_CHARSETS_ASCII_0x3E (), gthn
	#define LIBANDRIA4_CHARSETS_ASCII_0x3F (), ques
	#define LIBANDRIA4_CHARSETS_ASCII_0x40 (), at
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x41 (), A
	#define LIBANDRIA4_CHARSETS_ASCII_0x42 (), B
	#define LIBANDRIA4_CHARSETS_ASCII_0x43 (), C
	#define LIBANDRIA4_CHARSETS_ASCII_0x44 (), D
	#define LIBANDRIA4_CHARSETS_ASCII_0x45 (), E
	#define LIBANDRIA4_CHARSETS_ASCII_0x46 (), F
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x47 (), G
	#define LIBANDRIA4_CHARSETS_ASCII_0x48 (), H
	#define LIBANDRIA4_CHARSETS_ASCII_0x49 (), I
	#define LIBANDRIA4_CHARSETS_ASCII_0x4A (), J
	#define LIBANDRIA4_CHARSETS_ASCII_0x4B (), K
	#define LIBANDRIA4_CHARSETS_ASCII_0x4C (), L
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x4D (), M
	#define LIBANDRIA4_CHARSETS_ASCII_0x4E (), N
	#define LIBANDRIA4_CHARSETS_ASCII_0x4F (), O
	#define LIBANDRIA4_CHARSETS_ASCII_0x50 (), P
	#define LIBANDRIA4_CHARSETS_ASCII_0x51 (), Q
	#define LIBANDRIA4_CHARSETS_ASCII_0x52 (), R
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x53 (), S
	#define LIBANDRIA4_CHARSETS_ASCII_0x54 (), T
	#define LIBANDRIA4_CHARSETS_ASCII_0x55 (), U
	#define LIBANDRIA4_CHARSETS_ASCII_0x56 (), V
	#define LIBANDRIA4_CHARSETS_ASCII_0x57 (), W
	#define LIBANDRIA4_CHARSETS_ASCII_0x58 (), X
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x59 (), Y
	#define LIBANDRIA4_CHARSETS_ASCII_0x5A (), Z
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x5B (), opsq
	#define LIBANDRIA4_CHARSETS_ASCII_0x5C (), backslash
	#define LIBANDRIA4_CHARSETS_ASCII_0x5D (), clsq
	#define LIBANDRIA4_CHARSETS_ASCII_0x5E (), car
	#define LIBANDRIA4_CHARSETS_ASCII_0x5F (), und
	#define LIBANDRIA4_CHARSETS_ASCII_0x60 (), grv
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x61 (), a
	#define LIBANDRIA4_CHARSETS_ASCII_0x62 (), b
	#define LIBANDRIA4_CHARSETS_ASCII_0x63 (), c
	#define LIBANDRIA4_CHARSETS_ASCII_0x64 (), d
	#define LIBANDRIA4_CHARSETS_ASCII_0x65 (), e
	#define LIBANDRIA4_CHARSETS_ASCII_0x66 (), f
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x67 (), g
	#define LIBANDRIA4_CHARSETS_ASCII_0x68 (), h
	#define LIBANDRIA4_CHARSETS_ASCII_0x69 (), i
	#define LIBANDRIA4_CHARSETS_ASCII_0x6A (), j
	#define LIBANDRIA4_CHARSETS_ASCII_0x6B (), k
	#define LIBANDRIA4_CHARSETS_ASCII_0x6C (), l
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x6D (), m
	#define LIBANDRIA4_CHARSETS_ASCII_0x6E (), n
	#define LIBANDRIA4_CHARSETS_ASCII_0x6F (), o
	#define LIBANDRIA4_CHARSETS_ASCII_0x70 (), p
	#define LIBANDRIA4_CHARSETS_ASCII_0x71 (), q
	#define LIBANDRIA4_CHARSETS_ASCII_0x72 (), r
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x73 (), s
	#define LIBANDRIA4_CHARSETS_ASCII_0x74 (), t
	#define LIBANDRIA4_CHARSETS_ASCII_0x75 (), u
	#define LIBANDRIA4_CHARSETS_ASCII_0x76 (), v
	#define LIBANDRIA4_CHARSETS_ASCII_0x77 (), w
	#define LIBANDRIA4_CHARSETS_ASCII_0x78 (), x
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x79 (), y
	#define LIBANDRIA4_CHARSETS_ASCII_0x7A (), z
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x7B (), opcrl
	#define LIBANDRIA4_CHARSETS_ASCII_0x7C (), vbar
	#define LIBANDRIA4_CHARSETS_ASCII_0x7D (), clcrl
	#define LIBANDRIA4_CHARSETS_ASCII_0x7E (), tild
	
	
	#define LIBANDRIA4_CHARSETS_ASCII_0x7F (), delete
	
	
	
	
	/* The following is a system to convert various abbreviations, and */
	/*  sometimes misspellings, to standardized forms. Use the standardized */
	/*  forms when relevant. Note that this is NOT complete, as not all of */
	/*  ASCII has been entered. "tild", for example, should be standardized */
	/*  as "tilde". */
	
		/* Uses *_DOWNSELECT() to get standardized abbreviations from */
		/*  arbitrary inputs. */
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONSVERIFIER( character, conversion ) \
		LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( conversion ) ) \
			( character, conversion )
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS( character ) \
		LIBANDRIA4_CHARSETS_ABBREVIATIONSVERIFIER( \
			character, \
			LIBANDRIA4_CHARSETS_DOWNSELECT( LIBANDRIA4_CAT( \
				LIBANDRIA4_CHARSETS_, LIBANDRIA4_CAT( ABBREVIATIONS_, character ) \
			) ) \
		)
	
	
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_space (), space
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_spc (), space
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ (), space
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_nul (), null
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_null (), null
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_eo (), eightones
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_eones (), eightones
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_eighto (), eightones
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_8ones (), eightones
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_eight1s (), eightones
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_eightones (), eightones
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_soh (), startofheader
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_startofheader (), startofheader
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_stx (), startoftext
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_startoftext (), startoftext
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_etx (), endoftext
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endoftext (), endoftext
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_eot (), endoftransmission
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endoftransmission (), endoftransmission
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_enq (), enquiry
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_enquiry (), enquiry
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ack (), acknowledge
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_acknowlege (), acknowledge
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_acknowledge (), acknowledge
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_nak (), negativeacknowledge
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_negativeacknowlege (), negativeacknowledge
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_negativeacknowledge (), negativeacknowledge
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_err (), error
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_error (), error
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_bs (), backspace
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_bspace (), backspace
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_backspace (), backspace
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_cr (), carriagereturn
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_cret (), carriagereturn
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_creturn (), carriagereturn
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_carraigereturn (), carriagereturn
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_carriagereturn (), carriagereturn
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_tab (), horizontaltab
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_htab (), horizontaltab
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_horizontaltab (), horizontaltab
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_vtab (), verticaltab
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_verticaltab (), verticaltab
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_verticaletab (), verticaltab
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_verticletab (), verticaltab
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_lf (), linefeed
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_lfeed (), linefeed
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_linefeed (), linefeed
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ff (), formfeed
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ffeed (), formfeed
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_formfeed (), formfeed
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_bel (), bell
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_bell (), bell
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_so (), shiftout
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_shifto (), shiftout
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_shiftout (), shiftout
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_si (), shiftin
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_shifti (), shiftin
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_shiftin (), shiftin
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_dle (), datalinkescape
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_dlesc (), datalinkescape
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_datalinkescape (), datalinkescape
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_byp (), bypass
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_byps (), bypass
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_bypass (), bypass
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_dc1 (), devicecontrol1
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devc1 (), devicecontrol1
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devcont1 (), devicecontrol1
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devicecontrol1 (), devicecontrol1
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_dc2 (), devicecontrol2
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devc2 (), devicecontrol2
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devcont2 (), devicecontrol2
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devicecontrol2 (), devicecontrol2
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_dc3 (), devicecontrol3
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devc3 (), devicecontrol3
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devcont3 (), devicecontrol3
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devicecontrol3 (), devicecontrol3
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_dc4 (), devicecontrol4
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devc4 (), devicecontrol4
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devcont4 (), devicecontrol4
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_devicecontrol4 (), devicecontrol4
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_syn (), synchronousidle
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_syni (), synchronousidle
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_synidle (), sunchronousidle
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_syncidle (), synchronousidle
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_synchronousidle (), synchronousidle
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_etb (), endoftransmissionblock
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endtb (), endoftransmissionblock
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endtransb (), endoftransmissionblock
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endtransblock (), endoftransmissionblock
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endoftransmissionblock (), endoftransmissionblock
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_can (), cancel
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_cancl (), cancel
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_cancel (), cancel
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_em (), endofmedium
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endmed (), endofmedium
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endmedium (), endofmedium
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_endofmedium (), endofmedium
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_sub (), substitute
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_subtitute (), substitute
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_esc (), escape
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_escape (), escape
	
		/* The i*s ones are EBCDIC equivalents to ASCII *s. */
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ifs (), fileseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fs (), fileseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fsep (), fileseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fils (), fileseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_filsep (), fileseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_filesep (), fileseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fileseparator (), fileseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_igs (), groupseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_gs (), groupseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_gsep (), groupseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_grps (), groupseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_grpsep (), groupseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_groupsep (), groupseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_groupseparator (), groupseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_irs (), recordseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_rs (), recordseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_rsep (), recordseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_rcrds (), recordseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_recsep (), recordseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_rcrdsep (), recordseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_recordsep (), recordseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_recordseparator (), recordseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ius (), unitseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_us (), unitseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_usep (), unitseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_unts (), unitseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_untsep (), unitseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_unitsep (), unitseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_unitseparator (), unitseparator
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_flds (), fieldseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fldsep (), fieldseparator
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fieldseparator (), fieldseparator
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_del (), delete
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_delete (), delete
	
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fsls (), forwardslash
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fslash (), forwardslash
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_forwardslash (), forwardslash
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_bsls (), backslash
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_bslash (), backslash
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_backslash (), backslash
	
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_zero (), 0
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_one (), 1
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_two (), 2
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_three (), 3
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_four (), 4
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_five (), 5
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_six (), 6
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_seven (), 7
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_eight (), 8
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_nine (), 9
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_tree (), 3
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_fife (), 5
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_niner (), 9
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_0 (), 0
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_1 (), 1
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_2 (), 2
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_3 (), 3
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_4 (), 4
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_5 (), 5
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_6 (), 6
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_7 (), 7
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_8 (), 8
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_9 (), 9
	
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_alpha (), a
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_bravo (), b
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_charlie (), c
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_delta (), d
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_echo (), e
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_foxtrot (), f
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_golf (), g
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_hotel (), h
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_india (), i
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_juliet (), j
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_kilo (), k
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_lima (), l
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_mike (), m
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_november (), n
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_oscar (), o
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_papa (), p
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_quebec (), q
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_romeo (), r
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_sierra (), s
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_tango (), t
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_uniform (), u
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_victor (), v
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_whiskey (), w
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_xray (), x
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_yankee (), y
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_zulu (), z
	
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ALPHA (), A
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_BRAVO (), B
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_CHARLIE (), C
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_DELTA (), D
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ECHO (), E
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_FOXTROT (), F
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_GOLF (), G
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_HOTEL (), H
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_INDIA (), I
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_JULIET (), J
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_KILO (), K
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_LIMA (), L
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_MIKE (), M
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_NOVEMBER (), N
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_OSCAR (), O
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_PAPA (), P
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_QUEBEC (), Q
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ROMEO (), R
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_SIERRA (), S
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_TANGO (), T
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_UNIFORM (), U
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_VICTOR (), V
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_WHISKEY (), W
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_XRAY (), X
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_YANKEE (), Y
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ZULU (), Z
	
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_beta (), b
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_charlie (), c
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_epsilon (), e
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_zeta (), z
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_eta (), h
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_iota (), i
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_kappa (), k
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_mu (), m
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_nu (), n
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_omikron (), o
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_rho (), p
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_tau (), t
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_upsilon (), y
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_chi (), x
	
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_BETA (), B
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_CHARLIE (), C
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_EPSILON (), E
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ZETA (), Z
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_ETA (), H
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_IOTA (), I
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_KAPPA (), K
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_MU (), M
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_NU (), N
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_OMIKRON (), O
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_RHO (), P
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_TAU (), T
	
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_UPSILON (), Y
	#define LIBANDRIA4_CHARSETS_ABBREVIATIONS_CHI (), X
	
	
	
	
	/* Define the standard macro. */
	
	#if !defined( LIBANDRIA4_CHARSETS_SETSTD ) || LIBANDRIA4_CHARSETS_SETSTD == LIBANDRIA4_CHARSETS_SETSTD_USEASCII
		
		#define LIBANDRIA4_CHARSETS_STD( character ) \
			LIBANDRIA4_CHARSETS_ASCII( character )
		
	#elif LIBANDRIA4_CHARSETS_SETSTD == LIBANDRIA4_CHARSETS_SETSTD_USEEBCDICInvariant
		
		#include "charsets_EBCDICInvariant.h"
		#define LIBANDRIA4_CHARSETS_STD( character ) \
			LIBANDRIA4_CHARSETS_EBCDICInvariant( character )
		
	#elif LIBANDRIA4_CHARSETS_SETSTD == LIBANDRIA4_CHARSETS_SETSTD_USEASCII1963
		
		#include "charsets_ASCII1963.h"
		#define LIBANDRIA4_CHARSETS_STD( character ) \
			LIBANDRIA4_CHARSETS_ASCII1963( character )
		
	#elif defined( LIBANDRIA4_MACROTIME_CHARSETS_GENERAL_H_INCLUDEHOOK )
		
		/* It is acceptable to reuse the LIBANDRIA4_CHARSETS_SETSTD value in */
		/*  LIBANDRIA4_MACROTIME_CHARSETS_GENERAL_H_INCLUDEHOOK. However, it's */
		/*  usage should preferably reflect the normal usage. */
		
		#include LIBANDRIA4_MACROTIME_CHARSETS_GENERAL_H_INCLUDEHOOK
		
	#else
		
		#error "Unknown LIBANDRIA4_CHARSETS_SETSTD value while "
		#error " LIBANDRIA4_CHARSETS_STDINCLUDE undefined."
		#error " LIBANDRIA4_CHARSETS_SETSTD value:"
		#error LIBANDRIA4_CHARSETS_SETSTD
		
	#endif
	
#endif
/* End libandria4 text charsets_general.h */
