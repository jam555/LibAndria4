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

#ifndef LIBANDRIA4_TEXT_CHARSETTRANSLATORS_H
# define LIBANDRIA4_TEXT_CHARSETTRANSLATORS_H
	
	#include "../basic/commontypes.h"
	
	
	
	typedef libandria4_common_monadicchar32 (libandria4_text_charsettranslators_fptr*)
		( void*, libandria4_common_monadicchar32 );
	
	
	
	libandria4_common_monadicchar32
		libandria4_text_charsettranslators_ascii_to_unicode
		( void *ign, libandria4_common_monadicchar32 val );
	libandria4_common_monadicchar32
		libandria4_text_charsettranslators_unicode_to_ascii
		( void *ign, libandria4_common_monadicchar32 val );
	
	libandria4_common_monadicchar32
		libandria4_text_charsettranslators_strict_ascii_to_unicode
		( void *ign, libandria4_common_monadicchar32 val );
	libandria4_common_monadicchar32
		libandria4_text_charsettranslators_strict_unicode_to_ascii
		( void *ign, libandria4_common_monadicchar32 val );
	
	libandria4_common_monadicchar32
		libandria4_text_charsettranslators_vt100uk_to_unicode
		( void *ign, libandria4_common_monadicchar32 val );
	libandria4_common_monadicchar32
		libandria4_text_charsettranslators_unicode_to_vt100uk
		( void *ign, libandria4_common_monadicchar32 val );
	
	libandria4_common_monadicchar32
		libandria4_text_charsettranslators_vt100specgraph_to_unicode
		( void *ign, libandria4_common_monadicchar32 val );
			/* "lossless" because it only reverses the conversions done */
			/*  by libandria4_text_charsettranslators_vt100specgraph_to_unicode(), */
			/*  so any look-alikes are left unchanged. */
	libandria4_common_monadicchar32
		libandria4_text_charsettranslators_unicode_to_vt100specgraph_lossless
		( void *ign, libandria4_common_monadicchar32 val );
	
#endif
/* End libandria4 text charsettranslators.h */
