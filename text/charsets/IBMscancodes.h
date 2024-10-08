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

#ifndef LIBANDRIA4_TEXT_CHARSETS_IBMscancodes_H
# define LIBANDRIA4_TEXT_CHARSETS_IBMscancodes_H
	
	#include "general.h"
	
	
	/* Note: need to verify the below. */
	
	
		/* Finder for the IBM PC keyboard scan codes... or at least, one */
		/*  version. */
	#define LIBANDRIA4_IBMscancodes( character ) \
		LIBANDRIA4_CHARSETS_GATECHAR( \
			LIBANDRIA4_CHARSETS_ASCII_, LIBANDRIA4_CHARSETS_ABBREVIATIONS( character ) \
		)
	
	
	#define LIBANDRIA4_IBMscancodes_PressMask (), 0x80
	#define LIBANDRIA4_IBMscancodes_PressVal (), 0x00
	#define LIBANDRIA4_IBMscancodes_ReleaseVal (), 0x80
	
	
		/* Note: assumes little-endian encoding. */
	#define LIBANDRIA4_IBMscancodes_AltA (), 0x1E00
	#define LIBANDRIA4_IBMscancodes_AltB (), 0x3000
	#define LIBANDRIA4_IBMscancodes_AltC (), 0x2E00
	#define LIBANDRIA4_IBMscancodes_AltD (), 0x2000
	#define LIBANDRIA4_IBMscancodes_AltE (), 0x1200
	#define LIBANDRIA4_IBMscancodes_AltF (), 0x2100
	
	#define LIBANDRIA4_IBMscancodes_AltG (), 0x2200
	#define LIBANDRIA4_IBMscancodes_AltH (), 0x2300
	#define LIBANDRIA4_IBMscancodes_AltI (), 0x1700
	#define LIBANDRIA4_IBMscancodes_AltJ (), 0x2400
	#define LIBANDRIA4_IBMscancodes_AltK (), 0x2500
	#define LIBANDRIA4_IBMscancodes_AltL (), 0x2600
	
	#define LIBANDRIA4_IBMscancodes_AltM (), 0x3200
	#define LIBANDRIA4_IBMscancodes_AltN (), 0x3100
	#define LIBANDRIA4_IBMscancodes_AltO (), 0x1800
	#define LIBANDRIA4_IBMscancodes_AltP (), 0x1900
	#define LIBANDRIA4_IBMscancodes_AltQ (), 0x1000
	#define LIBANDRIA4_IBMscancodes_AltR (), 0x1300
	
	#define LIBANDRIA4_IBMscancodes_AltS (), 0x1A00
	#define LIBANDRIA4_IBMscancodes_AltT (), 0x1400
	#define LIBANDRIA4_IBMscancodes_AltU (), 0x1600
	#define LIBANDRIA4_IBMscancodes_AltV (), 0x2F00
	#define LIBANDRIA4_IBMscancodes_AltX (), 0x2D00
	#define LIBANDRIA4_IBMscancodes_AltW (), 0x1100
	
	#define LIBANDRIA4_IBMscancodes_AltY (), 0x1500
	#define LIBANDRIA4_IBMscancodes_AltZ (), 0x2C00
	
	#define LIBANDRIA4_IBMscancodes_PageUp (), 0x4900
	#define LIBANDRIA4_IBMscancodes_PageDown (), 0x5100
	#define LIBANDRIA4_IBMscancodes_Home (), 0x4700
	#define LIBANDRIA4_IBMscancodes_End (), 0x4F00
	#define LIBANDRIA4_IBMscancodes_UpArrow (), 0x4800
	#define LIBANDRIA4_IBMscancodes_DownArrow (), 0x5000
	#define LIBANDRIA4_IBMscancodes_LeftArrow (), 0x4B00
	#define LIBANDRIA4_IBMscancodes_RightArrow (), 0x4D00
	
	#define LIBANDRIA4_IBMscancodes_Function1 (), 0x3B00
	#define LIBANDRIA4_IBMscancodes_Function2 (), 0x3C00
	#define LIBANDRIA4_IBMscancodes_Function3 (), 0x3D00
	#define LIBANDRIA4_IBMscancodes_Function4 (), 0x3E00
	#define LIBANDRIA4_IBMscancodes_Function5 (), 0x3F00
	#define LIBANDRIA4_IBMscancodes_Function6 (), 0x4000
	#define LIBANDRIA4_IBMscancodes_Function7 (), 0x4100
	#define LIBANDRIA4_IBMscancodes_Function8 (), 0x4200
	#define LIBANDRIA4_IBMscancodes_Function9 (), 0x4300
	#define LIBANDRIA4_IBMscancodes_Function10 (), 0x4400
	#define LIBANDRIA4_IBMscancodes_Function11 (), 0x8500
	#define LIBANDRIA4_IBMscancodes_Function12 (), 0x8600
	
	#define LIBANDRIA4_IBMscancodes_AltFunction1 (), 0x6800
	#define LIBANDRIA4_IBMscancodes_AltFunction2 (), 0x6900
	#define LIBANDRIA4_IBMscancodes_AltFunction3 (), 0x6A00
	#define LIBANDRIA4_IBMscancodes_AltFunction4 (), 0x6B00
	#define LIBANDRIA4_IBMscancodes_AltFunction5 (), 0x6C00
	#define LIBANDRIA4_IBMscancodes_AltFunction6 (), 0x6D00
	#define LIBANDRIA4_IBMscancodes_AltFunction7 (), 0x6E00
	#define LIBANDRIA4_IBMscancodes_AltFunction8 (), 0x6F00
	#define LIBANDRIA4_IBMscancodes_AltFunction9 (), 0x7000
	#define LIBANDRIA4_IBMscancodes_AltFunction10 (), 0x7100
	#define LIBANDRIA4_IBMscancodes_AltFunction11 (), 0x8B00
	#define LIBANDRIA4_IBMscancodes_AltFunction12 (), 0x8C00
	
	
		/* For reverse lookup. */
	#define LIBANDRIA4_IBMscancodes_0x1E00 (), AltA
	#define LIBANDRIA4_IBMscancodes_0x3000 (), AltB
	#define LIBANDRIA4_IBMscancodes_0x2E00 (), AltC
	#define LIBANDRIA4_IBMscancodes_0x2000 (), AltD
	#define LIBANDRIA4_IBMscancodes_0x1200 (), AltE
	#define LIBANDRIA4_IBMscancodes_0x2100 (), AltF
	
	#define LIBANDRIA4_IBMscancodes_0x2200 (), AltG
	#define LIBANDRIA4_IBMscancodes_0x2300 (), AltH
	#define LIBANDRIA4_IBMscancodes_0x1700 (), AltI
	#define LIBANDRIA4_IBMscancodes_0x2400 (), AltJ
	#define LIBANDRIA4_IBMscancodes_0x2500 (), AltK
	#define LIBANDRIA4_IBMscancodes_0x2600 (), AltL
	
	#define LIBANDRIA4_IBMscancodes_0x3200 (), AltM
	#define LIBANDRIA4_IBMscancodes_0x3100 (), AltN
	#define LIBANDRIA4_IBMscancodes_0x1800 (), AltO
	#define LIBANDRIA4_IBMscancodes_0x1900 (), AltP
	#define LIBANDRIA4_IBMscancodes_0x1000 (), AltQ
	#define LIBANDRIA4_IBMscancodes_0x1300 (), AltR
	
	#define LIBANDRIA4_IBMscancodes_0x1A00 (), AltS
	#define LIBANDRIA4_IBMscancodes_0x1400 (), AltT
	#define LIBANDRIA4_IBMscancodes_0x1600 (), AltU
	#define LIBANDRIA4_IBMscancodes_0x2F00 (), AltV
	#define LIBANDRIA4_IBMscancodes_0x2D00 (), AltW
	#define LIBANDRIA4_IBMscancodes_0x1100 (), AltX
	
	#define LIBANDRIA4_IBMscancodes_0x1500 (), AltY
	#define LIBANDRIA4_IBMscancodes_0x2C00 (), AltZ
	
	#define LIBANDRIA4_IBMscancodes_0x4900 (), PageUp
	#define LIBANDRIA4_IBMscancodes_0x5100 (), PageDown
	#define LIBANDRIA4_IBMscancodes_0x4700 (), Home
	#define LIBANDRIA4_IBMscancodes_0x4F00 (), End
	#define LIBANDRIA4_IBMscancodes_0x4800 (), UpArrow
	#define LIBANDRIA4_IBMscancodes_0x5000 (), DownArrow
	#define LIBANDRIA4_IBMscancodes_0x4B00 (), LeftArrow
	#define LIBANDRIA4_IBMscancodes_0x4D00 (), RightArrow
	
	#define LIBANDRIA4_IBMscancodes_0x3B00 (), Function1
	#define LIBANDRIA4_IBMscancodes_0x3C00 (), Function2
	#define LIBANDRIA4_IBMscancodes_0x3D00 (), Function3
	#define LIBANDRIA4_IBMscancodes_0x3E00 (), Function4
	#define LIBANDRIA4_IBMscancodes_0x3F00 (), Function5
	#define LIBANDRIA4_IBMscancodes_0x4000 (), Function6
	#define LIBANDRIA4_IBMscancodes_0x4100 (), Function7
	#define LIBANDRIA4_IBMscancodes_0x4200 (), Function8
	#define LIBANDRIA4_IBMscancodes_0x4300 (), Function9
	#define LIBANDRIA4_IBMscancodes_0x4400 (), Function10
	#define LIBANDRIA4_IBMscancodes_0x8500 (), Function11
	#define LIBANDRIA4_IBMscancodes_0x8600 (), Function12
	
	#define LIBANDRIA4_IBMscancodes_0x6800 (), AltFunction1
	#define LIBANDRIA4_IBMscancodes_0x6900 (), AltFunction2
	#define LIBANDRIA4_IBMscancodes_0x6A00 (), AltFunction3
	#define LIBANDRIA4_IBMscancodes_0x6B00 (), AltFunction4
	#define LIBANDRIA4_IBMscancodes_0x6C00 (), AltFunction5
	#define LIBANDRIA4_IBMscancodes_0x6D00 (), AltFunction6
	#define LIBANDRIA4_IBMscancodes_0x6E00 (), AltFunction7
	#define LIBANDRIA4_IBMscancodes_0x6F00 (), AltFunction8
	#define LIBANDRIA4_IBMscancodes_0x7000 (), AltFunction9
	#define LIBANDRIA4_IBMscancodes_0x7100 (), AltFunction10
	#define LIBANDRIA4_IBMscancodes_0x8B00 (), AltFunction11
	#define LIBANDRIA4_IBMscancodes_0x8C00 (), AltFunction12
	
#endif
/* End relocated: libandria4 text charsets IBMscancodes.h */
