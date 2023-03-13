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

#ifndef LIB4_MACROTIME_CHARSETS_GENERAL_H
# define LIB4_MACROTIME_CHARSETS_GENERAL_H
	
	#include "simpleops.h"
	#include "arraccess.h"
	
	
	/* This is a general interface to the entire character-sets macro */
	/*  system. LIB4_CHARSETS_STD( character ) is defined at the very end to */
	/*  provide an automatically adjustable default interface. Use it unless */
	/*  you have reason not to (e.g. an assumption of a specific character */
	/*  set). If you want to override it, then set LIB4_CHARSETS_SETSTD to */
	/*  one of the following LIB4_CHARSETS_SETSTD_USE* macros, or set */
	/*  LIB4_MACROTIME_CHARSETS_GENERAL_H_INCLUDEHOOK to a file description */
	/*  appropriate for usage by the preprocessor's include directive. */
	
	
	
	#define LIB4_CHARSETS_SETSTD_USEASCII 0
	#define LIB4_CHARSETS_SETSTD_USEEBCDICInvariant 1
	#define LIB4_CHARSETS_SETSTD_USEASCII1963 2
	
	
	
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
	#define LIB4_CHARSETS_DOWNSELECT( ... ) \
		LIB4_IIF( LIB4_IS_PAREN( LIB4_RETURN_1ST( __VA_ARGS__ ) ) ) \
			( LIB4_RETURN_2ND( __VA_ARGS__ ), () )
	
		/* *_GATECHAR() short-circuits execution if the provided character */
		/*  is a parenthese pair. */
	#define LIB4_CHARSETS_GATECHAR( set, character ) \
		LIB4_IIF( LIB4_IS_PAREN( character ) ) \
			( (), LIB4_CHARSETS_DOWNSELECT( LIB4_CAT( set, character ) ) )
	
	
	
	
		/* Finder for the ASCII character set. */
	#define LIB4_CHARSETS_ASCII( character ) \
		LIB4_CHARSETS_GATECHAR( \
			LIB4_CHARSETS_ASCII_, LIB4_CHARSETS_ABBREVIATIONS( character ) \
		)
	
	
	#define LIB4_CHARSETS_ASCII_null (), 0x00
	
	#define LIB4_CHARSETS_ASCII_startofheader (), 0x01
	#define LIB4_CHARSETS_ASCII_startoftext (), 0x02
	#define LIB4_CHARSETS_ASCII_endoftext (), 0x03
	#define LIB4_CHARSETS_ASCII_endoftransmission (), 0x04
	
	#define LIB4_CHARSETS_ASCII_enquiry (), 0x05
	#define LIB4_CHARSETS_ASCII_acknowledge (), 0x06
	
	#define LIB4_CHARSETS_ASCII_bell (), 0x07
	#define LIB4_CHARSETS_ASCII_backspace (), 0x08
	
	#define LIB4_CHARSETS_ASCII_horizontaltab (), 0x09
	#define LIB4_CHARSETS_ASCII_linefeed (), 0x0A
	#define LIB4_CHARSETS_ASCII_verticaltab (), 0x0B
	#define LIB4_CHARSETS_ASCII_formfeed (), 0x0C
	#define LIB4_CHARSETS_ASCII_carriagereturn (), 0x0D
	
	#define LIB4_CHARSETS_ASCII_shiftout (), 0x0E
	#define LIB4_CHARSETS_ASCII_shiftin (), 0x0F
	#define LIB4_CHARSETS_ASCII_datalinkescape (), 0x10
	
	#define LIB4_CHARSETS_ASCII_devicecontrol1 (), 0x11
	#define LIB4_CHARSETS_ASCII_devicecontrol2 (), 0x12
	#define LIB4_CHARSETS_ASCII_devicecontrol3 (), 0x13
	#define LIB4_CHARSETS_ASCII_devicecontrol4 (), 0x14
	
	#define LIB4_CHARSETS_ASCII_negativeacknowledge (), 0x15
	#define LIB4_CHARSETS_ASCII_synchronousidle (), 0x16
	#define LIB4_CHARSETS_ASCII_endoftransmissionblock (), 0x17
	#define LIB4_CHARSETS_ASCII_cancel (), 0x18
	
	#define LIB4_CHARSETS_ASCII_endofmedium (), 0x19
	
	#define LIB4_CHARSETS_ASCII_substitute (), 0x1A
	#define LIB4_CHARSETS_ASCII_escape (), 0x1B
	
	#define LIB4_CHARSETS_ASCII_fileseparator (), 0x1C
	#define LIB4_CHARSETS_ASCII_groupseparator (), 0x1D
	#define LIB4_CHARSETS_ASCII_recordseparator (), 0x1E
	#define LIB4_CHARSETS_ASCII_unitseparator (), 0x1F
	
	#define LIB4_CHARSETS_ASCII_space (), 0x20
	
	#define LIB4_CHARSETS_ASCII_excl (), 0x21
	#define LIB4_CHARSETS_ASCII_dblq (), 0x22
	#define LIB4_CHARSETS_ASCII_hash (), 0x23
	#define LIB4_CHARSETS_ASCII_dolr (), 0x24
	#define LIB4_CHARSETS_ASCII_perc (), 0x25
	#define LIB4_CHARSETS_ASCII_ampr (), 0x26
	#define LIB4_CHARSETS_ASCII_sinq (), 0x27
	#define LIB4_CHARSETS_ASCII_oppr (), 0x28
	#define LIB4_CHARSETS_ASCII_clpr (), 0x29
	#define LIB4_CHARSETS_ASCII_ast (), 0x2A
	#define LIB4_CHARSETS_ASCII_plus (), 0x2B
	#define LIB4_CHARSETS_ASCII_coma (), 0x2C
	#define LIB4_CHARSETS_ASCII_minu (), 0x2D
	#define LIB4_CHARSETS_ASCII_perd (), 0x2E
	#define LIB4_CHARSETS_ASCII_forwardslash (), 0x2F
	
	
	#define LIB4_CHARSETS_ASCII_0 (), 0x30
	
	#define LIB4_CHARSETS_ASCII_1 (), 0x31
	#define LIB4_CHARSETS_ASCII_2 (), 0x32
	#define LIB4_CHARSETS_ASCII_3 (), 0x33
	#define LIB4_CHARSETS_ASCII_4 (), 0x34
	#define LIB4_CHARSETS_ASCII_5 (), 0x35
	
	#define LIB4_CHARSETS_ASCII_6 (), 0x36
	#define LIB4_CHARSETS_ASCII_7 (), 0x37
	#define LIB4_CHARSETS_ASCII_8 (), 0x38
	#define LIB4_CHARSETS_ASCII_9 (), 0x39
	
	
	#define LIB4_CHARSETS_ASCII_cln (), 0x3A
	#define LIB4_CHARSETS_ASCII_scln (), 0x3B
	#define LIB4_CHARSETS_ASCII_lthn (), 0x3C
	#define LIB4_CHARSETS_ASCII_eq (), 0x3D
	#define LIB4_CHARSETS_ASCII_gthn (), 0x3E
	#define LIB4_CHARSETS_ASCII_ques (), 0x3F
	#define LIB4_CHARSETS_ASCII_at (), 0x40
	
	
	#define LIB4_CHARSETS_ASCII_A (), 0x41
	#define LIB4_CHARSETS_ASCII_B (), 0x42
	#define LIB4_CHARSETS_ASCII_C (), 0x43
	#define LIB4_CHARSETS_ASCII_D (), 0x44
	#define LIB4_CHARSETS_ASCII_E (), 0x45
	#define LIB4_CHARSETS_ASCII_F (), 0x46
	
	#define LIB4_CHARSETS_ASCII_G (), 0x47
	#define LIB4_CHARSETS_ASCII_H (), 0x48
	#define LIB4_CHARSETS_ASCII_I (), 0x49
	#define LIB4_CHARSETS_ASCII_J (), 0x4A
	#define LIB4_CHARSETS_ASCII_K (), 0x4B
	#define LIB4_CHARSETS_ASCII_L (), 0x4C
	
	#define LIB4_CHARSETS_ASCII_M (), 0x4D
	#define LIB4_CHARSETS_ASCII_N (), 0x4E
	#define LIB4_CHARSETS_ASCII_O (), 0x4F
	#define LIB4_CHARSETS_ASCII_P (), 0x50
	#define LIB4_CHARSETS_ASCII_Q (), 0x51
	#define LIB4_CHARSETS_ASCII_R (), 0x52
	
	#define LIB4_CHARSETS_ASCII_S (), 0x53
	#define LIB4_CHARSETS_ASCII_T (), 0x54
	#define LIB4_CHARSETS_ASCII_U (), 0x55
	#define LIB4_CHARSETS_ASCII_V (), 0x56
	#define LIB4_CHARSETS_ASCII_W (), 0x57
	#define LIB4_CHARSETS_ASCII_X (), 0x58
	
	#define LIB4_CHARSETS_ASCII_Y (), 0x59
	#define LIB4_CHARSETS_ASCII_Z (), 0x5A
	
	
	#define LIB4_CHARSETS_ASCII_opsq (), 0x5B
	#define LIB4_CHARSETS_ASCII_backslash (), 0x5C
	#define LIB4_CHARSETS_ASCII_clsq (), 0x5D
	#define LIB4_CHARSETS_ASCII_car (), 0x5E
	#define LIB4_CHARSETS_ASCII_und (), 0x5F
	#define LIB4_CHARSETS_ASCII_grv (), 0x60
	
	
	#define LIB4_CHARSETS_ASCII_a (), 0x61
	#define LIB4_CHARSETS_ASCII_b (), 0x62
	#define LIB4_CHARSETS_ASCII_c (), 0x63
	#define LIB4_CHARSETS_ASCII_d (), 0x64
	#define LIB4_CHARSETS_ASCII_e (), 0x65
	#define LIB4_CHARSETS_ASCII_f (), 0x66
	
	#define LIB4_CHARSETS_ASCII_g (), 0x67
	#define LIB4_CHARSETS_ASCII_h (), 0x68
	#define LIB4_CHARSETS_ASCII_i (), 0x69
	#define LIB4_CHARSETS_ASCII_j (), 0x6A
	#define LIB4_CHARSETS_ASCII_k (), 0x6B
	#define LIB4_CHARSETS_ASCII_l (), 0x6C
	
	#define LIB4_CHARSETS_ASCII_m (), 0x6D
	#define LIB4_CHARSETS_ASCII_n (), 0x6E
	#define LIB4_CHARSETS_ASCII_o (), 0x6F
	#define LIB4_CHARSETS_ASCII_p (), 0x70
	#define LIB4_CHARSETS_ASCII_q (), 0x71
	#define LIB4_CHARSETS_ASCII_r (), 0x72
	
	#define LIB4_CHARSETS_ASCII_s (), 0x73
	#define LIB4_CHARSETS_ASCII_t (), 0x74
	#define LIB4_CHARSETS_ASCII_u (), 0x75
	#define LIB4_CHARSETS_ASCII_v (), 0x76
	#define LIB4_CHARSETS_ASCII_w (), 0x77
	#define LIB4_CHARSETS_ASCII_x (), 0x78
	
	#define LIB4_CHARSETS_ASCII_y (), 0x79
	#define LIB4_CHARSETS_ASCII_z (), 0x7A
	
	
	#define LIB4_CHARSETS_ASCII_opcrl (), 0x7B
	#define LIB4_CHARSETS_ASCII_vbar (), 0x7C
	#define LIB4_CHARSETS_ASCII_clcrl (), 0x7D
	#define LIB4_CHARSETS_ASCII_tild (), 0x7E
	#define LIB4_CHARSETS_ASCII_delete (), 0x7F
	
	
	
	
	/* Reverse lookup entries: */
	
	#define LIB4_CHARSETS_ASCII_0x00 (), null
	
	#define LIB4_CHARSETS_ASCII_0x01 (), startofheader
	#define LIB4_CHARSETS_ASCII_0x02 (), startoftext
	#define LIB4_CHARSETS_ASCII_0x03 (), endoftext
	#define LIB4_CHARSETS_ASCII_0x04 (), endoftransmission
	
	#define LIB4_CHARSETS_ASCII_0x05 (), enquiry
	#define LIB4_CHARSETS_ASCII_0x06 (), acknowledge
	
	#define LIB4_CHARSETS_ASCII_0x07 (), bell
	
	#define LIB4_CHARSETS_ASCII_0x08 (), backspace
	
	#define LIB4_CHARSETS_ASCII_0x09 (), horizontaltab
	#define LIB4_CHARSETS_ASCII_0x0A (), linefeed
	#define LIB4_CHARSETS_ASCII_0x0B (), verticaltab
	#define LIB4_CHARSETS_ASCII_0x0C (), formfeed
	#define LIB4_CHARSETS_ASCII_0x0D (), carriagereturn
	
	#define LIB4_CHARSETS_ASCII_0x0E (), shiftout
	#define LIB4_CHARSETS_ASCII_0x0F (), shiftin
	#define LIB4_CHARSETS_ASCII_0x10 (), datalinkescape
	
	#define LIB4_CHARSETS_ASCII_0x11 (), devicecontrol1
	#define LIB4_CHARSETS_ASCII_0x12 (), devicecontrol2
	#define LIB4_CHARSETS_ASCII_0x13 (), devicecontrol3
	#define LIB4_CHARSETS_ASCII_0x14 (), devicecontrol4
	
	#define LIB4_CHARSETS_ASCII_0x15 (), negativeacknowledge
	#define LIB4_CHARSETS_ASCII_0x16 (), synchronousidle
	
	#define LIB4_CHARSETS_ASCII_0x17 (), endoftransmissionblock
	#define LIB4_CHARSETS_ASCII_0x18 (), cancel
	
	#define LIB4_CHARSETS_ASCII_0x19 (), endofmedium
	
	#define LIB4_CHARSETS_ASCII_0x1A (), substitute
	#define LIB4_CHARSETS_ASCII_0x1B (), escape
	
	#define LIB4_CHARSETS_ASCII_0x1C (), fileseparator
	#define LIB4_CHARSETS_ASCII_0x1D (), groupseparator
	#define LIB4_CHARSETS_ASCII_0x1E (), recordseparator
	#define LIB4_CHARSETS_ASCII_0x1F (), unitseparator
	
	#define LIB4_CHARSETS_ASCII_0x20 (), space
	
	#define LIB4_CHARSETS_ASCII_0x21 (), excl
	#define LIB4_CHARSETS_ASCII_0x22 (), dblq
	#define LIB4_CHARSETS_ASCII_0x23 (), hash
	#define LIB4_CHARSETS_ASCII_0x24 (), dolr
	#define LIB4_CHARSETS_ASCII_0x25 (), perc
	#define LIB4_CHARSETS_ASCII_0x26 (), ampr
	#define LIB4_CHARSETS_ASCII_0x27 (), sinq
	#define LIB4_CHARSETS_ASCII_0x28 (), oppr
	#define LIB4_CHARSETS_ASCII_0x29 (), clpr
	#define LIB4_CHARSETS_ASCII_0x2A (), ast
	#define LIB4_CHARSETS_ASCII_0x2B (), plus
	#define LIB4_CHARSETS_ASCII_0x2C (), coma
	#define LIB4_CHARSETS_ASCII_0x2D (), minu
	#define LIB4_CHARSETS_ASCII_0x2E (), perd
	#define LIB4_CHARSETS_ASCII_0x2F (), forwardslash
	
	
	#define LIB4_CHARSETS_ASCII_0x30 (), 0
	
	#define LIB4_CHARSETS_ASCII_0x31 (), 1
	#define LIB4_CHARSETS_ASCII_0x32 (), 2
	#define LIB4_CHARSETS_ASCII_0x33 (), 3
	#define LIB4_CHARSETS_ASCII_0x34 (), 4
	#define LIB4_CHARSETS_ASCII_0x35 (), 5
	
	#define LIB4_CHARSETS_ASCII_0x36 (), 6
	#define LIB4_CHARSETS_ASCII_0x37 (), 7
	#define LIB4_CHARSETS_ASCII_0x38 (), 8
	#define LIB4_CHARSETS_ASCII_0x39 (), 9
	
	
	#define LIB4_CHARSETS_ASCII_0x3A (), cln
	#define LIB4_CHARSETS_ASCII_0x3B (), scln
	#define LIB4_CHARSETS_ASCII_0x3C (), lthn
	#define LIB4_CHARSETS_ASCII_0x3D (), eq
	#define LIB4_CHARSETS_ASCII_0x3E (), gthn
	#define LIB4_CHARSETS_ASCII_0x3F (), ques
	#define LIB4_CHARSETS_ASCII_0x40 (), at
	
	
	#define LIB4_CHARSETS_ASCII_0x41 (), A
	#define LIB4_CHARSETS_ASCII_0x42 (), B
	#define LIB4_CHARSETS_ASCII_0x43 (), C
	#define LIB4_CHARSETS_ASCII_0x44 (), D
	#define LIB4_CHARSETS_ASCII_0x45 (), E
	#define LIB4_CHARSETS_ASCII_0x46 (), F
	
	#define LIB4_CHARSETS_ASCII_0x47 (), G
	#define LIB4_CHARSETS_ASCII_0x48 (), H
	#define LIB4_CHARSETS_ASCII_0x49 (), I
	#define LIB4_CHARSETS_ASCII_0x4A (), J
	#define LIB4_CHARSETS_ASCII_0x4B (), K
	#define LIB4_CHARSETS_ASCII_0x4C (), L
	
	#define LIB4_CHARSETS_ASCII_0x4D (), M
	#define LIB4_CHARSETS_ASCII_0x4E (), N
	#define LIB4_CHARSETS_ASCII_0x4F (), O
	#define LIB4_CHARSETS_ASCII_0x50 (), P
	#define LIB4_CHARSETS_ASCII_0x51 (), Q
	#define LIB4_CHARSETS_ASCII_0x52 (), R
	
	#define LIB4_CHARSETS_ASCII_0x53 (), S
	#define LIB4_CHARSETS_ASCII_0x54 (), T
	#define LIB4_CHARSETS_ASCII_0x55 (), U
	#define LIB4_CHARSETS_ASCII_0x56 (), V
	#define LIB4_CHARSETS_ASCII_0x57 (), W
	#define LIB4_CHARSETS_ASCII_0x58 (), X
	
	#define LIB4_CHARSETS_ASCII_0x59 (), Y
	#define LIB4_CHARSETS_ASCII_0x5A (), Z
	
	
	#define LIB4_CHARSETS_ASCII_0x5B (), opsq
	#define LIB4_CHARSETS_ASCII_0x5C (), backslash
	#define LIB4_CHARSETS_ASCII_0x5D (), clsq
	#define LIB4_CHARSETS_ASCII_0x5E (), car
	#define LIB4_CHARSETS_ASCII_0x5F (), und
	#define LIB4_CHARSETS_ASCII_0x60 (), grv
	
	
	#define LIB4_CHARSETS_ASCII_0x61 (), a
	#define LIB4_CHARSETS_ASCII_0x62 (), b
	#define LIB4_CHARSETS_ASCII_0x63 (), c
	#define LIB4_CHARSETS_ASCII_0x64 (), d
	#define LIB4_CHARSETS_ASCII_0x65 (), e
	#define LIB4_CHARSETS_ASCII_0x66 (), f
	
	#define LIB4_CHARSETS_ASCII_0x67 (), g
	#define LIB4_CHARSETS_ASCII_0x68 (), h
	#define LIB4_CHARSETS_ASCII_0x69 (), i
	#define LIB4_CHARSETS_ASCII_0x6A (), j
	#define LIB4_CHARSETS_ASCII_0x6B (), k
	#define LIB4_CHARSETS_ASCII_0x6C (), l
	
	#define LIB4_CHARSETS_ASCII_0x6D (), m
	#define LIB4_CHARSETS_ASCII_0x6E (), n
	#define LIB4_CHARSETS_ASCII_0x6F (), o
	#define LIB4_CHARSETS_ASCII_0x70 (), p
	#define LIB4_CHARSETS_ASCII_0x71 (), q
	#define LIB4_CHARSETS_ASCII_0x72 (), r
	
	#define LIB4_CHARSETS_ASCII_0x73 (), s
	#define LIB4_CHARSETS_ASCII_0x74 (), t
	#define LIB4_CHARSETS_ASCII_0x75 (), u
	#define LIB4_CHARSETS_ASCII_0x76 (), v
	#define LIB4_CHARSETS_ASCII_0x77 (), w
	#define LIB4_CHARSETS_ASCII_0x78 (), x
	
	#define LIB4_CHARSETS_ASCII_0x79 (), y
	#define LIB4_CHARSETS_ASCII_0x7A (), z
	
	
	#define LIB4_CHARSETS_ASCII_0x7B (), opcrl
	#define LIB4_CHARSETS_ASCII_0x7C (), vbar
	#define LIB4_CHARSETS_ASCII_0x7D (), clcrl
	#define LIB4_CHARSETS_ASCII_0x7E (), tild
	
	
	#define LIB4_CHARSETS_ASCII_0x7F (), delete
	
	
	
	
	/* The following is a system to convert various abbreviations, and */
	/*  sometimes misspellings, to standardized forms. Use the standardized */
	/*  forms when relevant. Note that this is NOT complete, as not all of */
	/*  ASCII has been entered. "tild", for example, should be standardized */
	/*  as "tilde". */
	
		/* Uses *_DOWNSELECT() to get standardized abbreviations from */
		/*  arbitrary inputs. */
	#define LIB4_CHARSETS_ABBREVIATIONSVERIFIER( character, conversion ) \
		LIB4_IIF( LIB4_IS_PAREN( conversion ) ) \
			( character, conversion )
	#define LIB4_CHARSETS_ABBREVIATIONS( character ) \
		LIB4_CHARSETS_ABBREVIATIONSVERIFIER( \
			character, \
			LIB4_CHARSETS_DOWNSELECT( LIB4_CAT( \
				LIB4_CHARSETS_, LIB4_CAT( ABBREVIATIONS_, character ) \
			) ) \
		)
	
	
	
	#define LIB4_CHARSETS_ABBREVIATIONS_space (), space
	#define LIB4_CHARSETS_ABBREVIATIONS_spc (), space
	#define LIB4_CHARSETS_ABBREVIATIONS_ (), space
	
	#define LIB4_CHARSETS_ABBREVIATIONS_nul (), null
	#define LIB4_CHARSETS_ABBREVIATIONS_null (), null
	#define LIB4_CHARSETS_ABBREVIATIONS_eo (), eightones
	#define LIB4_CHARSETS_ABBREVIATIONS_eones (), eightones
	#define LIB4_CHARSETS_ABBREVIATIONS_eighto (), eightones
	#define LIB4_CHARSETS_ABBREVIATIONS_8ones (), eightones
	#define LIB4_CHARSETS_ABBREVIATIONS_eight1s (), eightones
	#define LIB4_CHARSETS_ABBREVIATIONS_eightones (), eightones
	
	#define LIB4_CHARSETS_ABBREVIATIONS_soh (), startofheader
	#define LIB4_CHARSETS_ABBREVIATIONS_startofheader (), startofheader
	#define LIB4_CHARSETS_ABBREVIATIONS_stx (), startoftext
	#define LIB4_CHARSETS_ABBREVIATIONS_startoftext (), startoftext
	#define LIB4_CHARSETS_ABBREVIATIONS_etx (), endoftext
	#define LIB4_CHARSETS_ABBREVIATIONS_endoftext (), endoftext
	
	#define LIB4_CHARSETS_ABBREVIATIONS_eot (), endoftransmission
	#define LIB4_CHARSETS_ABBREVIATIONS_endoftransmission (), endoftransmission
	
	#define LIB4_CHARSETS_ABBREVIATIONS_enq (), enquiry
	#define LIB4_CHARSETS_ABBREVIATIONS_enquiry (), enquiry
	#define LIB4_CHARSETS_ABBREVIATIONS_ack (), acknowledge
	#define LIB4_CHARSETS_ABBREVIATIONS_acknowlege (), acknowledge
	#define LIB4_CHARSETS_ABBREVIATIONS_acknowledge (), acknowledge
	#define LIB4_CHARSETS_ABBREVIATIONS_nak (), negativeacknowledge
	#define LIB4_CHARSETS_ABBREVIATIONS_negativeacknowlege (), negativeacknowledge
	#define LIB4_CHARSETS_ABBREVIATIONS_negativeacknowledge (), negativeacknowledge
	#define LIB4_CHARSETS_ABBREVIATIONS_err (), error
	#define LIB4_CHARSETS_ABBREVIATIONS_error (), error
	
	#define LIB4_CHARSETS_ABBREVIATIONS_bs (), backspace
	#define LIB4_CHARSETS_ABBREVIATIONS_bspace (), backspace
	#define LIB4_CHARSETS_ABBREVIATIONS_backspace (), backspace
	#define LIB4_CHARSETS_ABBREVIATIONS_cr (), carriagereturn
	#define LIB4_CHARSETS_ABBREVIATIONS_cret (), carriagereturn
	#define LIB4_CHARSETS_ABBREVIATIONS_creturn (), carriagereturn
	#define LIB4_CHARSETS_ABBREVIATIONS_carraigereturn (), carriagereturn
	#define LIB4_CHARSETS_ABBREVIATIONS_carriagereturn (), carriagereturn
	#define LIB4_CHARSETS_ABBREVIATIONS_tab (), horizontaltab
	#define LIB4_CHARSETS_ABBREVIATIONS_htab (), horizontaltab
	#define LIB4_CHARSETS_ABBREVIATIONS_horizontaltab (), horizontaltab
	#define LIB4_CHARSETS_ABBREVIATIONS_vtab (), verticaltab
	#define LIB4_CHARSETS_ABBREVIATIONS_verticaltab (), verticaltab
	#define LIB4_CHARSETS_ABBREVIATIONS_verticaletab (), verticaltab
	#define LIB4_CHARSETS_ABBREVIATIONS_verticletab (), verticaltab
	#define LIB4_CHARSETS_ABBREVIATIONS_lf (), linefeed
	#define LIB4_CHARSETS_ABBREVIATIONS_lfeed (), linefeed
	#define LIB4_CHARSETS_ABBREVIATIONS_linefeed (), linefeed
	#define LIB4_CHARSETS_ABBREVIATIONS_ff (), formfeed
	#define LIB4_CHARSETS_ABBREVIATIONS_ffeed (), formfeed
	#define LIB4_CHARSETS_ABBREVIATIONS_formfeed (), formfeed
	
	#define LIB4_CHARSETS_ABBREVIATIONS_bel (), bell
	#define LIB4_CHARSETS_ABBREVIATIONS_bell (), bell
	
	#define LIB4_CHARSETS_ABBREVIATIONS_so (), shiftout
	#define LIB4_CHARSETS_ABBREVIATIONS_shifto (), shiftout
	#define LIB4_CHARSETS_ABBREVIATIONS_shiftout (), shiftout
	#define LIB4_CHARSETS_ABBREVIATIONS_si (), shiftin
	#define LIB4_CHARSETS_ABBREVIATIONS_shifti (), shiftin
	#define LIB4_CHARSETS_ABBREVIATIONS_shiftin (), shiftin
	#define LIB4_CHARSETS_ABBREVIATIONS_dle (), datalinkescape
	#define LIB4_CHARSETS_ABBREVIATIONS_dlesc (), datalinkescape
	#define LIB4_CHARSETS_ABBREVIATIONS_datalinkescape (), datalinkescape
	#define LIB4_CHARSETS_ABBREVIATIONS_byp (), bypass
	#define LIB4_CHARSETS_ABBREVIATIONS_byps (), bypass
	#define LIB4_CHARSETS_ABBREVIATIONS_bypass (), bypass
	
	#define LIB4_CHARSETS_ABBREVIATIONS_dc1 (), devicecontrol1
	#define LIB4_CHARSETS_ABBREVIATIONS_devc1 (), devicecontrol1
	#define LIB4_CHARSETS_ABBREVIATIONS_devcont1 (), devicecontrol1
	#define LIB4_CHARSETS_ABBREVIATIONS_devicecontrol1 (), devicecontrol1
	#define LIB4_CHARSETS_ABBREVIATIONS_dc2 (), devicecontrol2
	#define LIB4_CHARSETS_ABBREVIATIONS_devc2 (), devicecontrol2
	#define LIB4_CHARSETS_ABBREVIATIONS_devcont2 (), devicecontrol2
	#define LIB4_CHARSETS_ABBREVIATIONS_devicecontrol2 (), devicecontrol2
	#define LIB4_CHARSETS_ABBREVIATIONS_dc3 (), devicecontrol3
	#define LIB4_CHARSETS_ABBREVIATIONS_devc3 (), devicecontrol3
	#define LIB4_CHARSETS_ABBREVIATIONS_devcont3 (), devicecontrol3
	#define LIB4_CHARSETS_ABBREVIATIONS_devicecontrol3 (), devicecontrol3
	#define LIB4_CHARSETS_ABBREVIATIONS_dc4 (), devicecontrol4
	#define LIB4_CHARSETS_ABBREVIATIONS_devc4 (), devicecontrol4
	#define LIB4_CHARSETS_ABBREVIATIONS_devcont4 (), devicecontrol4
	#define LIB4_CHARSETS_ABBREVIATIONS_devicecontrol4 (), devicecontrol4
	
	#define LIB4_CHARSETS_ABBREVIATIONS_syn (), synchronousidle
	#define LIB4_CHARSETS_ABBREVIATIONS_syni (), synchronousidle
	#define LIB4_CHARSETS_ABBREVIATIONS_synidle (), sunchronousidle
	#define LIB4_CHARSETS_ABBREVIATIONS_syncidle (), synchronousidle
	#define LIB4_CHARSETS_ABBREVIATIONS_synchronousidle (), synchronousidle
	#define LIB4_CHARSETS_ABBREVIATIONS_etb (), endoftransmissionblock
	#define LIB4_CHARSETS_ABBREVIATIONS_endtb (), endoftransmissionblock
	#define LIB4_CHARSETS_ABBREVIATIONS_endtransb (), endoftransmissionblock
	#define LIB4_CHARSETS_ABBREVIATIONS_endtransblock (), endoftransmissionblock
	#define LIB4_CHARSETS_ABBREVIATIONS_endoftransmissionblock (), endoftransmissionblock
	#define LIB4_CHARSETS_ABBREVIATIONS_can (), cancel
	#define LIB4_CHARSETS_ABBREVIATIONS_cancl (), cancel
	#define LIB4_CHARSETS_ABBREVIATIONS_cancel (), cancel
	#define LIB4_CHARSETS_ABBREVIATIONS_em (), endofmedium
	#define LIB4_CHARSETS_ABBREVIATIONS_endmed (), endofmedium
	#define LIB4_CHARSETS_ABBREVIATIONS_endmedium (), endofmedium
	#define LIB4_CHARSETS_ABBREVIATIONS_endofmedium (), endofmedium
	
	#define LIB4_CHARSETS_ABBREVIATIONS_sub (), substitute
	#define LIB4_CHARSETS_ABBREVIATIONS_subtitute (), substitute
	#define LIB4_CHARSETS_ABBREVIATIONS_esc (), escape
	#define LIB4_CHARSETS_ABBREVIATIONS_escape (), escape
	
		/* The i*s ones are EBCDIC equivalents to ASCII *s. */
	#define LIB4_CHARSETS_ABBREVIATIONS_ifs (), fileseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_fs (), fileseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_fsep (), fileseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_fils (), fileseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_filsep (), fileseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_filesep (), fileseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_fileseparator (), fileseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_igs (), groupseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_gs (), groupseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_gsep (), groupseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_grps (), groupseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_grpsep (), groupseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_groupsep (), groupseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_groupseparator (), groupseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_irs (), recordseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_rs (), recordseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_rsep (), recordseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_rcrds (), recordseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_recsep (), recordseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_rcrdsep (), recordseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_recordsep (), recordseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_recordseparator (), recordseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_ius (), unitseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_us (), unitseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_usep (), unitseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_unts (), unitseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_untsep (), unitseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_unitsep (), unitseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_unitseparator (), unitseparator
	
	#define LIB4_CHARSETS_ABBREVIATIONS_flds (), fieldseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_fldsep (), fieldseparator
	#define LIB4_CHARSETS_ABBREVIATIONS_fieldseparator (), fieldseparator
	
	#define LIB4_CHARSETS_ABBREVIATIONS_del (), delete
	#define LIB4_CHARSETS_ABBREVIATIONS_delete (), delete
	
	
	#define LIB4_CHARSETS_ABBREVIATIONS_fsls (), forwardslash
	#define LIB4_CHARSETS_ABBREVIATIONS_fslash (), forwardslash
	#define LIB4_CHARSETS_ABBREVIATIONS_forwardslash (), forwardslash
	#define LIB4_CHARSETS_ABBREVIATIONS_bsls (), backslash
	#define LIB4_CHARSETS_ABBREVIATIONS_bslash (), backslash
	#define LIB4_CHARSETS_ABBREVIATIONS_backslash (), backslash
	
	
	#define LIB4_CHARSETS_ABBREVIATIONS_zero (), 0
	
	#define LIB4_CHARSETS_ABBREVIATIONS_one (), 1
	#define LIB4_CHARSETS_ABBREVIATIONS_two (), 2
	#define LIB4_CHARSETS_ABBREVIATIONS_three (), 3
	#define LIB4_CHARSETS_ABBREVIATIONS_four (), 4
	#define LIB4_CHARSETS_ABBREVIATIONS_five (), 5
	
	#define LIB4_CHARSETS_ABBREVIATIONS_six (), 6
	#define LIB4_CHARSETS_ABBREVIATIONS_seven (), 7
	#define LIB4_CHARSETS_ABBREVIATIONS_eight (), 8
	#define LIB4_CHARSETS_ABBREVIATIONS_nine (), 9
	
	#define LIB4_CHARSETS_ABBREVIATIONS_tree (), 3
	#define LIB4_CHARSETS_ABBREVIATIONS_fife (), 5
	#define LIB4_CHARSETS_ABBREVIATIONS_niner (), 9
	
	#define LIB4_CHARSETS_ABBREVIATIONS_0 (), 0
	
	#define LIB4_CHARSETS_ABBREVIATIONS_1 (), 1
	#define LIB4_CHARSETS_ABBREVIATIONS_2 (), 2
	#define LIB4_CHARSETS_ABBREVIATIONS_3 (), 3
	#define LIB4_CHARSETS_ABBREVIATIONS_4 (), 4
	#define LIB4_CHARSETS_ABBREVIATIONS_5 (), 5
	
	#define LIB4_CHARSETS_ABBREVIATIONS_6 (), 6
	#define LIB4_CHARSETS_ABBREVIATIONS_7 (), 7
	#define LIB4_CHARSETS_ABBREVIATIONS_8 (), 8
	#define LIB4_CHARSETS_ABBREVIATIONS_9 (), 9
	
	
	#define LIB4_CHARSETS_ABBREVIATIONS_alpha (), a
	#define LIB4_CHARSETS_ABBREVIATIONS_bravo (), b
	#define LIB4_CHARSETS_ABBREVIATIONS_charlie (), c
	#define LIB4_CHARSETS_ABBREVIATIONS_delta (), d
	#define LIB4_CHARSETS_ABBREVIATIONS_echo (), e
	#define LIB4_CHARSETS_ABBREVIATIONS_foxtrot (), f
	
	#define LIB4_CHARSETS_ABBREVIATIONS_golf (), g
	#define LIB4_CHARSETS_ABBREVIATIONS_hotel (), h
	#define LIB4_CHARSETS_ABBREVIATIONS_india (), i
	#define LIB4_CHARSETS_ABBREVIATIONS_juliet (), j
	#define LIB4_CHARSETS_ABBREVIATIONS_kilo (), k
	#define LIB4_CHARSETS_ABBREVIATIONS_lima (), l
	
	#define LIB4_CHARSETS_ABBREVIATIONS_mike (), m
	#define LIB4_CHARSETS_ABBREVIATIONS_november (), n
	#define LIB4_CHARSETS_ABBREVIATIONS_oscar (), o
	#define LIB4_CHARSETS_ABBREVIATIONS_papa (), p
	#define LIB4_CHARSETS_ABBREVIATIONS_quebec (), q
	#define LIB4_CHARSETS_ABBREVIATIONS_romeo (), r
	
	#define LIB4_CHARSETS_ABBREVIATIONS_sierra (), s
	#define LIB4_CHARSETS_ABBREVIATIONS_tango (), t
	#define LIB4_CHARSETS_ABBREVIATIONS_uniform (), u
	#define LIB4_CHARSETS_ABBREVIATIONS_victor (), v
	#define LIB4_CHARSETS_ABBREVIATIONS_whiskey (), w
	#define LIB4_CHARSETS_ABBREVIATIONS_xray (), x
	
	#define LIB4_CHARSETS_ABBREVIATIONS_yankee (), y
	#define LIB4_CHARSETS_ABBREVIATIONS_zulu (), z
	
	
	#define LIB4_CHARSETS_ABBREVIATIONS_ALPHA (), A
	#define LIB4_CHARSETS_ABBREVIATIONS_BRAVO (), B
	#define LIB4_CHARSETS_ABBREVIATIONS_CHARLIE (), C
	#define LIB4_CHARSETS_ABBREVIATIONS_DELTA (), D
	#define LIB4_CHARSETS_ABBREVIATIONS_ECHO (), E
	#define LIB4_CHARSETS_ABBREVIATIONS_FOXTROT (), F
	
	#define LIB4_CHARSETS_ABBREVIATIONS_GOLF (), G
	#define LIB4_CHARSETS_ABBREVIATIONS_HOTEL (), H
	#define LIB4_CHARSETS_ABBREVIATIONS_INDIA (), I
	#define LIB4_CHARSETS_ABBREVIATIONS_JULIET (), J
	#define LIB4_CHARSETS_ABBREVIATIONS_KILO (), K
	#define LIB4_CHARSETS_ABBREVIATIONS_LIMA (), L
	
	#define LIB4_CHARSETS_ABBREVIATIONS_MIKE (), M
	#define LIB4_CHARSETS_ABBREVIATIONS_NOVEMBER (), N
	#define LIB4_CHARSETS_ABBREVIATIONS_OSCAR (), O
	#define LIB4_CHARSETS_ABBREVIATIONS_PAPA (), P
	#define LIB4_CHARSETS_ABBREVIATIONS_QUEBEC (), Q
	#define LIB4_CHARSETS_ABBREVIATIONS_ROMEO (), R
	
	#define LIB4_CHARSETS_ABBREVIATIONS_SIERRA (), S
	#define LIB4_CHARSETS_ABBREVIATIONS_TANGO (), T
	#define LIB4_CHARSETS_ABBREVIATIONS_UNIFORM (), U
	#define LIB4_CHARSETS_ABBREVIATIONS_VICTOR (), V
	#define LIB4_CHARSETS_ABBREVIATIONS_WHISKEY (), W
	#define LIB4_CHARSETS_ABBREVIATIONS_XRAY (), X
	
	#define LIB4_CHARSETS_ABBREVIATIONS_YANKEE (), Y
	#define LIB4_CHARSETS_ABBREVIATIONS_ZULU (), Z
	
	
	#define LIB4_CHARSETS_ABBREVIATIONS_beta (), b
	#define LIB4_CHARSETS_ABBREVIATIONS_charlie (), c
	#define LIB4_CHARSETS_ABBREVIATIONS_epsilon (), e
	#define LIB4_CHARSETS_ABBREVIATIONS_zeta (), z
	#define LIB4_CHARSETS_ABBREVIATIONS_eta (), h
	#define LIB4_CHARSETS_ABBREVIATIONS_iota (), i
	
	#define LIB4_CHARSETS_ABBREVIATIONS_kappa (), k
	#define LIB4_CHARSETS_ABBREVIATIONS_mu (), m
	#define LIB4_CHARSETS_ABBREVIATIONS_nu (), n
	#define LIB4_CHARSETS_ABBREVIATIONS_omikron (), o
	#define LIB4_CHARSETS_ABBREVIATIONS_rho (), p
	#define LIB4_CHARSETS_ABBREVIATIONS_tau (), t
	
	#define LIB4_CHARSETS_ABBREVIATIONS_upsilon (), y
	#define LIB4_CHARSETS_ABBREVIATIONS_chi (), x
	
	
	#define LIB4_CHARSETS_ABBREVIATIONS_BETA (), B
	#define LIB4_CHARSETS_ABBREVIATIONS_CHARLIE (), C
	#define LIB4_CHARSETS_ABBREVIATIONS_EPSILON (), E
	#define LIB4_CHARSETS_ABBREVIATIONS_ZETA (), Z
	#define LIB4_CHARSETS_ABBREVIATIONS_ETA (), H
	#define LIB4_CHARSETS_ABBREVIATIONS_IOTA (), I
	
	#define LIB4_CHARSETS_ABBREVIATIONS_KAPPA (), K
	#define LIB4_CHARSETS_ABBREVIATIONS_MU (), M
	#define LIB4_CHARSETS_ABBREVIATIONS_NU (), N
	#define LIB4_CHARSETS_ABBREVIATIONS_OMIKRON (), O
	#define LIB4_CHARSETS_ABBREVIATIONS_RHO (), P
	#define LIB4_CHARSETS_ABBREVIATIONS_TAU (), T
	
	#define LIB4_CHARSETS_ABBREVIATIONS_UPSILON (), Y
	#define LIB4_CHARSETS_ABBREVIATIONS_CHI (), X
	
	
	
	
	/* Define the standard macro. */
	
	#if !defined( LIB4_CHARSETS_SETSTD ) || LIB4_CHARSETS_SETSTD == LIB4_CHARSETS_SETSTD_USEASCII
		
		#define LIB4_CHARSETS_STD( character ) \
			LIB4_CHARSETS_ASCII( character )
		
	#elif LIB4_CHARSETS_SETSTD == LIB4_CHARSETS_SETSTD_USEEBCDICInvariant
		
		#include "charsets_EBCDICInvariant.h"
		#define LIB4_CHARSETS_STD( character ) \
			LIB4_CHARSETS_EBCDICInvariant( character )
		
	#elif LIB4_CHARSETS_SETSTD == LIB4_CHARSETS_SETSTD_USEASCII1963
		
		#include "charsets_ASCII1963.h"
		#define LIB4_CHARSETS_STD( character ) \
			LIB4_CHARSETS_ASCII1963( character )
		
	#elif defined( LIB4_MACROTIME_CHARSETS_GENERAL_H_INCLUDEHOOK )
		
		/* It is acceptable to reuse the LIB4_CHARSETS_SETSTD value in */
		/*  LIB4_MACROTIME_CHARSETS_GENERAL_H_INCLUDEHOOK. However, it's */
		/*  usage should preferably reflect the normal usage. */
		
		#include LIB4_MACROTIME_CHARSETS_GENERAL_H_INCLUDEHOOK
		
	#else
		
		#error "Unknown LIB4_CHARSETS_SETSTD value while "
		#error " LIB4_CHARSETS_STDINCLUDE undefined."
		#error " LIB4_CHARSETS_SETSTD value:"
		#error LIB4_CHARSETS_SETSTD
		
	#endif
	
#endif
/* End lib4 macrotime charsets_general.h */
