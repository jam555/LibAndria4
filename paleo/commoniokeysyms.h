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

#ifndef LIBANDRIA4_BASIC_COMMONIOKEYSYMS_H
# define LIBANDRIA4_BASIC_COMMONIOKEYSYMS_H
	
	/* WARNING! Parts of this duplicate stuff like */
		/* libandria4_buffercell_common_chara_UNICODEVALID_baseval */
	/* from stdbuffer.h! Produce a unified version (for ../text/ ?) and just */
	/*  reference it in both! */
	
	/* I think that FunctionLock & FunctionModifier still need to be added, */
	/*  to produce e.g. F1 when there aren't discrete function keys (though */
	/*  this IS often handled in hardware). */
	/* Should add Symbol and SymbolLock for some virtual keyboards. */
	/* Should add Cut for "copy then delete". */
	
	/* Note that Japanese and Korean seem to be postfix-key systems: enter */
	/*  some character(s), press a "trigger IME" key, and maybe click */
	/*  additional keys to either work through the options, or narrow / */
	/*  broaden the selection of options. These keys should ideally be */
	/*  refered to as "undead" characters, as they're sort-of dead keys, but */
	/*  they happen AFTER the modified keys instead of BEFORE the modified */
	/*  keys. */
	
	/* Check this: */
		/* https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h */
	/*  to see if this list is "sufficient". Same with this: */
		/* https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2 */
	/* , and this: */
		/* https://wiki.libsdl.org/SDL2/SDL_Scancode */
	
	/* An example of the first file drawn from is here: */
		/* https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h */
	
	
	
	
	
		/* Key codes encode the PURPOSE of a key, like "A", or Function Key */
		/*  1, or Play/Pause. */
		/* Note: change all references to "key codes" to "key syms": key */
		/*  codes will often be a "universalized" transformation of scan */
		/*  codes, and while they'll often be informative about e.g. ESC, */
		/*  they won't be transformed by modifiers AT ALL in most cases. */
	typedef uint32_t libandria4_commoniokeys_simplekeycode;
		/* Scan codes are a (hopefully unique) identifier for individual */
		/*  keyswitch positions. */
	typedef uint32_t libandria4_commoniokeys_simplescancode;
	
	
	
	
	
	/* What follows is a listing of generic keys. They don't include */
	/*  character keys, because THAT is simply handled by UNICODE value. */
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_invalidcode
		( (libandria4_commoniokeys_simplekeycode)0xFFFFFFFF )
	
	
	/* These masks are used for fast & lazy identifications. If a bit that */
	/*  isn't set in *_legalmask is set, then it ISN'T a legal Unicode */
	/*  character, and thus MUST be something else, such as a function key. */
			/* *_legalmask = 2097151 */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask \
		( (libandria4_commoniokeys_simplekeycode)0x1FFFFF )
			/* *_droppedmask == 2047 */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask \
		( (libandria4_commoniokeys_simplekeycode)0x7FF )
			/* *_multiplier == 2097152 */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_multiplier \
		( (libandria4_commoniokeys_simplekeycode)0x200000 )
			/* *_mask == *droppedmask * *_multiplier == 0xFFFFFF - *_legalmask == 0xFFE00000 == 4292870144 */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_mask \
		( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask << 21 )
	
	
	
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildillegal( high, low ) \
		( ( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask & high ) << 21 ) | \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask & low ) )
	
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_trueUnicode ( 0 )
	
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_generifunc ( 1 )
	
	
		/* The "set" and "func" of a function key both get allocated from the "illegal" */
		/*  low zone: the high 4 bits get allocated to set, while the low 17 bits get */
		/*  allocated to func. This is expected to be DRASTICALLY more than is needed */
		/*  for either category. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_droppedmask ( ( 1 << 3 ) - 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_multiplier \
		( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask >> 3 ) - \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask >> 4 ) )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildgenerifunc( high, set, func ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildillegal( high, \
			( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_droppedmask & ( set ) ) * \
				LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_multiplier ) | \
			( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask >> 4 ) & ( func ) ) )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_stdset ( 0 )
	
	/* The X11 guys found keyboards that had function keys divided into a left and a */
	/*  right group: so, I generified that a bit. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_forwardset ( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_rightset ( 2 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_rearwardset ( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_leftset ( 4 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_upwardset ( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_downwardset ( 6 )
		/* oikos-the, "toward the familiar", from Greek, the "th" is voiced. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_oikosthewardset ( 7 )
		/* As oikos, so xenos, "toward the foreign" or "... outer", again the "th" is voiced. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_xenosthewardset ( 8 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildgenerifunc( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_generifunc, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_stdset, num )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildgenerifunc( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_generifunc, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_leftset, num )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildgenerifunc( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_generifunc, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_generifunc_rightset, num )
	
	/* Function keys. The X11 guys apparently never found a keyboard with more than 35 */
	/*  generic function keys. The IBM 3270 PA keys (XK_3270_PA1, XK_3270_PA2, and */
	/*  XK_3270_PA3) seem like they should be translated to some of these (note that */
	/*  the 3270's PF keys ABSOLUTELY should be mapped to these.). */
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std2 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 2 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std3 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std4 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 4 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std5 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std6 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 6 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std7 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 7 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std8 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 8 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std9 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 9 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std10 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 10 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std11 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 11 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std12 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 12 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std13 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 13 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std14 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 14 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std15 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 15 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std16 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 16 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std17 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 17 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std18 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 18 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std19 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 19 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std20 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 20 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std21 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 21 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std22 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 22 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std23 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 23 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std24 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 24 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std25 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 25 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std26 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 26 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std27 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 27 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std28 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 28 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std29 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 29 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std30 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 30 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std31 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 31 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std32 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 32 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std33 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 33 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std34 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 34 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std35 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Std( 35 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left2 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 2 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left3 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left4 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left5 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 5 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left6 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 6 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left7 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 7 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left8 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 8 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left9 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 9 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left10 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Left( 10 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right2 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 2 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right3 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right4 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 4 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right5 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 5 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right6 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 6 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right7 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 7 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right8 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 8 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right9 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 9 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right10 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 10 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right11 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 11 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right12 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 12 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right13 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 13 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right14 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 14 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right15 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Functionkey_Right( 15 )
	
	/* There's probably something out there that has e.g. "front" or "back" function */
	/*  keys, or something else of that ilk, but I can't be bothered to care just yet. */
	/*  Also, the values would be pretty formulaic anyways. */
	
	
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_commonedit ( 2 )
	
	
		/* The "set" and "func" of a function key both get allocated from the "illegal" */
		/*  low zone: the high 4 bits get allocated to set, while the low 17 bits get */
		/*  allocated to func. This is expected to be DRASTICALLY more than is needed */
		/*  for either category. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_droppedmask ( ( 1 << 3 ) - 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_multiplier \
		( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask >> 3 ) - \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask >> 4 ) )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcommonedit( high, set, func ) \
		( ( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask & ( high ) ) << 21 ) | \
			( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_droppedmask & ( set ) ) * \
				LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_multiplier ) | \
			( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask >> 4 ) & ( low ) ) )
	
		/* Actual modifications. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_edit ( 1 )
		/* Mode switches. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_modallock ( 2 )
		/* Mode switches, but one-time instead of locking. Also known as deadkeys. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_modalprefix ( 3 )
		/* Cursor movement: directly affects where edits occur. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_cursor ( 4 )
		/* Pointer actions: indirectly affect where edits occur. In essence, a mouse */
		/*  alternative. Commonly used for accessibility. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_pointer ( 5 )
		/* Viewport actions: doesn't affect where edits occur, but instead what's */
		/*  being viewed. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_view ( 6 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_edit( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcommonedit( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_commonedit, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_edit, num )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcommonedit( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_commonedit, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_modallock, num )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcommonedit( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_commonedit, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_modalprefix, num )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcommonedit( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_commonedit, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_cursor, num )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcommonedit( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_commonedit, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_pointer, num )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_view( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcommonedit( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_commonedit, \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_commonedit_view, num )
	
	
	/* Note that "copy" is down in the Action section. */
		/* The common PC keyboard "backspace" key. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Backerase \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_edit( 1 )
			/* The common PC keyboard "delete" key. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Forwarderase \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_edit( 2 )
			/* Clears the contents of whatever's selected. XK_Clear */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clear \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_edit( 3 )
			/* Alternative to ctrl-z. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Undo \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_edit( 4 )
			/* Alternative to ctrl-y. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Redo \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_edit( 5 )
			/* XK_3270_Duplicate? Except I think that may have been an entry to a more */
			/*  advanced "multi-destination" thing, maybe? */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Paste \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_edit( 6 )
	
	
	/* Note that modal keys are a mixture of deadkey/latching keys (keys that modify */
	/*  the following keypress only, or maybe "only"), and locking keys (keys that */
	/*  affect all following keypresses until a distinct "unlock" action). */
	
		/* In the TPU editor on VMS, sets "select" mode, allowing text to be highlighted */
		/*  for actions such as copy, erase, etc. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_SelectLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 1 )
			/* Note that unlike Paste, this toggles between insert and overwrite. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_InsertLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 2 )
			/* XK_Pointer_EnableKeys and/or XK_MouseKeys_Enable; Toggle whether normal */
			/*  cursor keys act like pointer keys. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MouseKeysLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 3 )
			/* Use cursor keys to drag instead of just move. Locking. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_DragLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 4 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CapsLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ShiftLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 6 )
			/* Toggles between cursor and view functions. If both cursor and view keys */
			/*  are present, all keys in either category that have an equivalent in the */
			/*  other switch function. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ScrollLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 7 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_NumLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 8 )
  			/* Toggle the emission of beep-codes for things like activating SlowKeys or */
			/*  turning an LED off. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_FeedbackLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 9 )
			/* Repetition has first and later repeat delays. Repeats encoded as extra */
			/*  "press" without release. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_RepeatLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 10 )
			/* SlowKeys mode rejects any key not pressed for at least x period of time. */
			/*  Used by users that may accidentally hit keys, such as those that use a */
			/*  "pointing stick" (e.g. an in-mouth joystick) to interact with an */
			/*  on-screen keyboard. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_SlowLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 11 )
			/* Toggles software-based key-debouncing. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_BounceLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 12 )
			/* StickyKeys causes modifier keys to "stick": single-click causes */
			/*  deadkey-latching, double-click causes locking, another press unlocks */
			/*  it. Modifiers do not cause other latched modifiers to unlatch. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_StickyLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 13 )
			/* This & the next relate to whether MouseKeys undergoes acceleration and */
			/*  repetition. Both are toggles. Look at the X11 Pointer Keys stuff. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerAccelLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 14 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerAccelEnLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 15 )
			/* Toggles responses to SUGGESTED (not forced) sound requests. Maybe see */
			/*  also XK_3270_KeyClick (see page 3-8 in "3174 Establishment Controller */
			/*  Terminal User's Reference for Expanded Functions"), as that sounds */
			/*  very similar? */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_SuggBellsLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 16 )
			/* The XK_Overlay*_Enable codes from X11. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Over1Lock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 17 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Over2Lock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 18 )
			/* This is just normal pause behavior. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PauseLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 19 )
			/* When "compose" is active, all other keysyms indicate something */
			/*  about a SINGLE character that is to be entered. For example, */
			/*  following the activation of Compose with ~ and n could produce */
			/*  that one Spanish character. It's worth noting that while that */
			/*  sequence could be TRANSLATED to the one described for *_IMEMark */
			/*  below, Compose DOES NOT natively participate in that, being a */
			/*  much simpler system, though Compose COULD reasonably be fed into */
			/*  that if configured correctly: the IMEMark system is much more */
			/*  robust, but therefore also more complex. */
			/* Along with *_ComposeModifier, an option for XK_Multi_key */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ComposeLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 20 )
	
		/* Locks into "MS DOS/Windows Alt code mode" to allow arbitrary keysyms */
		/*  to be entered from a common set choosen by Microsoft. Option for */
		/*  XK_Codeinput . */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltCodeLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 21 )
			/* As *_AltCodeLock, but with hexadecimal input, and specifying */
			/*  Unicode. Option for XK_Codeinput . */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_UnicodeNumInpLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 22 )
			/* Like Alt Codes, but for Hangul. Apparenntly almost no Koreans */
			/*  bother with it? XK_Hangul_Codeinput */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_HangulCodeLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 23 )
			/* Like Alt Codes, but for Japanese. XK_Kanji_Bangou */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_KanjiCodeLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 24 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ZenkakuHankakuToggle \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 25 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_HiraganaKatakanaToggle \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 26 )
	
			/* Just Japanese keyboards, look at *_AltGrExt_* for "richer" */
			/*  keyboards. XK_Kana_Lock */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_KanaLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 25 )
	
			/* Recognize the next "button" click as a double-click instead of a */
			/*  single-click. Mostly a MouseKeys thing, but also for the 3270's */
			/*  double-move arrow keys stuff, and I don't know any reason for it */
			/*  not to work with other stuff too. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Double \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 1 )
			/* Recognizes the next key press as either nothing, or toggles one of */
			/*  the lock keys. XK_AccessX_Enable? Provides a way to lock e.g. */
			/*  SlowKeys without a special key, app, or other method.  */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AlternateLockKeys \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 2 )
			/* Actual MSX key if I understand correctly. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Deadkey \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 3 )
			/* This exists to allow arbitrary numbers of buttons to be supported */
			/*  on e.g. a mouse. It forms a single-click, unless the *_Double */
			/*  prefix (or something else) is mixed in, and the prefix must be */
			/*  followed by... something, but a Unicode character (like "a", not */
			/*  STX or SPACE) is, in general, the right choice: DO NOT treat */
			/*  these as actual characters, they're just ARBITRARY identifiers */
			/*  that should be respected for their arbitrary nature. */
			/* Note that this DOES NOT form the default buttons. If it operates */
			/*  on the default button values then they remain unchanged, but it */
			/*  NEVER actually FORMS them. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CursorSingle_ButtonPrefix \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 4 )
			/* Used to mark e.g. a button as being used to drag something, such */
			/*  as the selection. It exists so that I don't have to duplicate */
			/*  button-drag keysyms from X11, but thinking about it, I'm not */
			/*  100% certain how those were supposed to work. Regardless, it's a */
			/*  modifier here, so it should work on arbitrary keys. Don't miss */
			/*  any key-ups, I guess? */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CursorSingle_DragPrefix \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 5 )
			/* Used to e.g. alter Home and End keys for media-control purposes, */
			/*  such as moving through a playlist. Note that Media keysyms */
			/*  should be ignored by most stuff, and should ALSO be propogated */
			/*  to non-focussed applications instead of the more normal "keep it */
			/*  to the focus chain" behaviors of normal keysyms. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MediaPrefix \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 6 )
	
	/* Inspired by *_Thai_maihanakat_maitho. Note that "n3" is "completely */
	/*  uncertain", 0 is "completely wrong", and 3 is "completely certain". */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clarity_n3 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 7 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clarity_n2 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 8 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clarity_n1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 9 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clarity_0 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 10 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clarity_1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 11 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clarity_2 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 12 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clarity_3 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 13 )
	
	/* Modal Prefixes 14 to 32 are available for whatever seems sensible. */
	
	/* These prefix keys are all "dead" keys: they don't display directly, but */
	/*  rather alter the next glyph to be indicated by the keyboard. */
	
	/* These are essentially IME hooks/triggers, UNLESS something about system */
	/*  settings specifies a correct interpretation all by itself, which */
	/*  PROBABLY is possible with some language or another. */
		/* Note that Unicode recommends using a character that already has the */
		/*  hook... but we're (at least sometimes) working in the scope that */
		/*  IDENTIFIES which character that should be, so we (theoretically) */
		/*  need this. Note that actually handling this essentially requires an */
		/*  IME system to allow the correct choice to be VISIBLY identified. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Dead_Hook \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 33 )
			/* Again, IME. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Dead_Stroke \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 34 )
			/* Again, IME. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Dead_Currency \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 35 )
	
		/* Trigger an Input Method Editor. Mostly this is used for languages */
		/*  like Japanese, Chinese, and Korean, but can be conceptually used to */
		/*  combine various things like tildes with letters to form e.g. */
		/*  non-English European letters (such as that n with a tilde over it), */
		/*  and even for accessibility. */
		/* Note that only for the "combine characters for Europe" is this keysym */
		/*  enough, and even that needs to use some sort of packet interface to */
		/*  wrap the characters to be combined (use the ASCII/Unicode SOH right */
		/*  after this keysym; followed by any "language identifier" or "IME */
		/*  identifier" (see the end of this sentance) that might be relevant; */
		/*  optionally FS, GS, RS, or US followed by some sort of preferably */
		/*  hexadecimal query ID; then STX; then the Unicode characters and */
		/*  other keysyms to be combined; then ETX): everything else needs to */
		/*  establish a distinct two-way communications channel with the code */
		/*  supplying IME support so that the IME code can display feedback for */
		/*  the user in a way that's "friendly" with the code that needs help */
		/*  from the IME system, with the actual IME system behavior being */
		/*  decided by the character immediately following this keysym */
		/*  (excepting only that any IME identifier that is provided after the */
		/*  SOH character option described above should SPECIFICALLY result in */
		/*  the symbols between the STX and ETX being interpretted as if they */
		/*  were submitted to the IME system that would have been started up */
		/*  if this IMEMark keysym had been immediately followed by the */
		/*  provided IME identifier instead of SOH). */
		/*   */
		/*  Note that while I don't need to know HOW this will be useful, */
		/*  (someone else can figure out how they want to use it), I CAN imagine */
		/*  it being used for some sort of "fast translation" software, */
		/*  multiple-choice narrowing widgets, or similar such things. */
		/*   */
		/*  Also note that if the IME is meant to operate on already entered */
		/*  text, then that text should be sent with the SOH + IME identifier */
		/*  method: there's nothing in particular in it's description that */
		/*  forbids the more complex interactive IME stuff from starting up if */
		/*  the provided symbols are insufficient, and if they ARE insufficient */
		/*  then the more advanced protocol SHOULD start up.  */
		/*  */
		/* XK_Hangul_Start (한); Half of XK_Hangul (한/영 key, toggles between */
		/*  Hangul (한) and English (영) ); XK_Hangul_Hanja (Hangul -> Hanja */
		/*  (Chinese characters used to represent Korean sounds) ) and */
		/*  XK_Hangul_Special (한자 key? Hanja seems to happen when a "full" */
		/*  Hangul syllable is used, Special (symbols and other non-Hanja */
		/*  non-Chinese characters) when just a consonant is used); XK_Kanji */
		/*  (start Japanese character entry); XK_Hangul_Romaja (transliterates */
		/*  from latin characters to Hangul, seems rarely used) */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_IMEMark \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 36 )
			/* A response to any number of things, including an IMEMark packet */
			/*  as described above. Should be followed by a packet of mostly the */
			/*  same format as IMEMark's SOH format, excepting only that the */
			/*  keysyms between the SOH and STX should in some way specifically */
			/*  identify what is being responded to; FS, GS, RS, and US are used */
			/*  to separate the sections of said header one again, and the first */
			/*  section should specify enough for the rest of header to be */
			/*  parsed afterwards. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Response \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 37 )
	
			/* Switch to a Latin-like keyboard from e.g. Hangul for one key. Note */
			/*  that technically I don't know if this belongs as a deadkey, it */
			/*  might be intended by X11 to be a Lock or Modifier instead. */
			/*  XK_Eisu_toggle */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_LatinateToggle \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 38 )
	
	/* These two are extensions to SS2 and SS3 from ISO 2022. If you want SS2 or */
	/*  SS3 then just use them directly from Unicode. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_SingleShift0 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 39 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_SingleShift1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modalprefix( 40 )
 
 
 
	/* Delete all whitespace above this comment once done, the proper spacing is safe below it.*/
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CurUp \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CurRight \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 2 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CurDown \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CurLeft \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 4 )
			/* The next 4 AREN'T in X11, but they're obvious enough. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CurUpRight \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CurDownRight \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 6 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CurDownLeft \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 7 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CurUpLeft \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 8 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Home \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 9 )
			/* Technically I don't know this key's purpose, but it's in X11. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Begin \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 10 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_End \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 11 )
			/* Previous in sequence: often alternative to shift-tab. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Prior \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 12 )
			/* Next in sequence: often alternative tab. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Next \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 13 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PageUp \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 14 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PageDown \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_cursor( 15 )
	
	
	/* These act as a substitute for a mouse. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerUp \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerRight \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( 2 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerDown \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerLeft \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( 4 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerUpRight \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerDownRight \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( 6 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerDownLeft \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( 7 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_PointerUpLeft \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_pointer( 8 )
	
	
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_modifiers ( 2 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildmodifiers( high, mod ) \
		( ( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask & ( high ) ) << 21 ) | \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask & ( low ) ) )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildmodifiers( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_modifiers, num )
	
	
	/* Shift, control, etc., only have one entry each, never several. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Shift \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Ctrl \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 2 )
			/* Note: Meta == the Win and Mac-command key per Mozilla. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Meta \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Alt \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 4 )
			/* "Alternate Graphic", like shift but more distant than capitals. Usually */
			/*  mapped to the right Alt key by the OS. Basically synonymous with */
			/*  XK_Mode_switch, XK_script_switch, and XK_ISO_Group_Shift (which */
			/*  themselves are aliases for each other). */
			/* Note: there's also XK_ISO_Group_Latch and XK_ISO_Group_Lock, which */
			/*  SHOULD have the obvious meanings, but which I haven't implemented. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltGr \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Super \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 6 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Hyper \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 7 )
	
	/* These *_GenMod* keys correspond to GENERIFIED modifiers. X11 uses such a */
	/*  thing to allow actual keys (e.g. Alt) to be seperated from the alternative */
	/*  keysyms that they're supposed to trigger. This is useful because it lets */
	/*  multiple sets of transforms be defined in one file, and then another file */
	/*  can describe per-keyboard (or other) ways to indicate which set of */
	/*  transforms should currently be active. X11 apparently has 4, so that's */
	/*  what'll initially be defined here, more can be added later if needed. */
			/* XK_ISO_Lock */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_GenMod1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 8 )
			/* XK_ISO_Level2_Latch : Presumably triggered by Shift in most cases. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_GenMod2 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 9 )
			/* XK_ISO_Level3_Shift, XK_ISO_Level3_Latch, and XK_ISO_Level3_Lock, */
			/*  though we only handle the shift here, so the lock & latch should */
			/*  be considered elsewhere. Stereotypically associated with AltGr, */
			/*  see: */
				/* https://bugzilla.cendio.com/show_bug.cgi?id=5226 */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_GenMod3 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 10 )
			/* XK_ISO_Level5_Shift, XK_ISO_Level5_Latch, XK_ISO_Level5_Lock, */
			/*  again we only handle the shift here. I don't know anything that */
			/*  these are commonly associated with. I also don't know why "4" is */
			/*  skipped. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_GenMod4 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 11 )
	
	/* What should these do? I don't know, so I'm judging from the X11 keysym */
	/*  names. If they're useless, then useful additions should be created */
	/*  instead of changing these. */
			/* XK_Kana_Shift. I don't know what this does. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_KanaShift \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 12 )
			/* XK_Eisu_Shift. Maybe it's just normal shift? */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_LatinateShift \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 13 )
	
	/* Values 14-16 have been left unused in case we want them for more of these */
	/*  generified modifier groups in the future. */
	
			/* XK_ISO_First_Group, XK_ISO_First_Group_Lock, I assume these allow */
			/*  sequential switching between the GenMod groups above? */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_GenModFirst \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 17 )
			/* XK_ISO_Prev_Group, XK_ISO_Prev_Group_Lock */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_GenModPrev \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 18 )
			/* XK_ISO_Next_Group, XK_ISO_Next_Group_Lock */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_GenModNext \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 19 )
			/* XK_ISO_Last_Group, XK_ISO_Last_Group_Lock */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_GenModLast \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 20 )
	
		/* XK_3270_ExSelect. Allows the selection to be extended up, down, or */
		/*  side-to-side. So, basically just what the shift key gets used for */
		/*  with cursor keys, but remember that at least the 3270 was an 80s and */
		/*  older platform, so some of that stuff would have just used a */
		/*  rectangle for selections.... yeah, even text. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ExtendSelection \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 21 )
	
			/* When "compose" is active, all other keysyms indicate something */
			/*  about a SINGLE character that is to be entered. For example, */
			/*  following the activation of Compose with ~ and n could produce */
			/*  that one Spanish character. It's worth noting that while that */
			/*  sequence could be TRANSLATED to the one described for *_IMEMark */
			/*  below, Compose DOES NOT natively participate in that, being a */
			/*  much simpler system, though Compose COULD reasonably be fed into */
			/*  that if configured correctly: the IMEMark system is much more */
			/*  robust, but therefore also more complex. */
			/* Along with *_ComposeLock, an option for XK_Multi_key */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ComposeModifier \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Modifiers_action( 22 )
	
		/* As *_AltCodeLock, but must be held down- this is technically the */
		/*  traditional form of "Alt codes". */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltCodeMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 23 )
			/* As *_UnicodeNumInpLock, but non-locking like *_AltCodeMod. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_UnicodeNumInpMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 24 )
			/* Like *_HangulCodeLock and *_AltCodeMod. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_HangulCodeLock \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commonedit_modallock( 21 )
	
	
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_actions ( 3 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildactions( high, mod ) \
		( ( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask & ( high ) ) << 21 ) | \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask & ( low ) ) )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildactions( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_actions, num )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Escape \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Return \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 2 )
			/* XK_3270_Attn */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_SysReq \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Menu \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 4 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Print \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 5 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Execute \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 6 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Find \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 7 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Cancel \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 8 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Help \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 9 )
			/* Often the same key as "Pause", which is listed above as a locking */
			/*  key. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Break \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 10 )
	
	/* These represent the ACTION, not the character. When in a text environment */
	/*  instead of an execution context they should be interpreted as characters, */
	/*  but otherwise shouldn't be. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Add \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 11 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Subtract \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 12 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Multiply \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 13 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Divide \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 14 )
	
	/* Not actions, but still conceptual. The text fallback depends on e.g. US */
	/*  versus German standards, and thus varies. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Decimal \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 15 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Separator \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 16 )
	
	/* These are technically meant for MouseKeys support, but will probably be */
	/*  used for more stuff later. Note that these are the default-supported */
	/*  pointer keys, the prefix key above DO NOT form the default buttons. For */
	/*  double-click or drag use the associated modifiers. */
		/* e.g. XK_Pointer_Button_Dflt */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CursorSingle_BDefault \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 17 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CursorSingle_B1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 18 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CursorSingle_B2 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 19 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CursorSingle_B3 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 20 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CursorSingle_B4 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 21 )
			/* e.g. XK_Pointer_Button5 */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CursorSingle_B5 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 22 )
	
	/* Note that there is also a Media prefix keysym. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Volume_Down \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 23 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Volume_Up \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 24 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Volume_Mute \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 25 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Play \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 26 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Stop \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 27 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Pause \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 28 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_PlayPause_Toggle \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 29 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Prev \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 30 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Next \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 31 )
	
		/* E.g. XK_First_Virtual_Screen */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_View_First \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 32 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_View_Prev \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 33 )
			/* X11 had it's own X-server keysym for this, but the concept */
			/*  overlaps with X11's XK_3270_Jump keysym for IBM 3270 usage. The */
			/*  Jump key jumped between "partitions", where (per page 2-1 of */
			/*  the Jan/1981 "IBM 3270 Data Stream Programmer's Reference") */
				/* 'a "logical" screen, called a PARTITION, which may differ in */
				/*  both size and shape from the physical display screen'  */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_View_Next \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 34 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_View_Last \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 35 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_View_Initiate \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 36 )
			/*  E.g. XK_Terminate_Server */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_View_Conclude \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 37 )
	
			/* Meant for calculator memory & clipboards. Maybe XK_3270_Record? */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Copy \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 38 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Reset \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 39 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Quit \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 40 )
			/* Enter a test mode, this is mostly for users to see what upgrades */
			/*  have been installed in a terminal. Usable, but of limited */
			/*  value. E.g. XK_3270_Test */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Test \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 41 )
			/* XK_3270_Ident . Used to enter a "choose the destination" mode. */
			/*  In the IBM 3270 system, it specifically is used to trigger a */
			/*  query for the specific printer (or printer class, which is */
			/*  probably a designated group) so that the user can say which */
			/*  printer to use for a particular operation (per page 3-25 of */
			/*  IBM's Feb/1980 */
				/* "3270 Information Display System Component Description" */
			/*  ). */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Delegate \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 42 )
			/* Adds on to *_Copy and *_Paste to finish the common calculator */
			/*  memory operations. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Forget \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 43 )
			/* XK_3270_FieldMark */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_FieldComplete \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 44 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_BackwardsTab \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 43 )
			/* Delete from cursor, to end of line/field/etc. that cursor is */
			/*  inside. XK_3270_EraseEOF */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ProgressiveDelete \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 46 )
			/* Erase all input fields or other on the screen, move cursor to */
			/*  first writable position on screen. XK_3270_EraseInput */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ScreenErase \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 47 )
			/* XK_3270_CursorBlink */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Cursor_ToggleBlink \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 48 )
			/* XK_3270_AltCursor */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Cursor_ToggleStyle \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 49 )
			/* XK_3270_Rule. The 3270 version is a crosshair? */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Cursor_ToggleRuler \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 50 )
			/* Though, this often WON'T be passed to hardware, but instead */
			/*  stay inside a hardware terminal... */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Setup \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 51 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_DeleteWord \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 52 )
	
	/* The following two seem likely to be used to pick an option from the */
	/*  Hangul dropdown, and that's what Mozilla (per: */
		/* https://bugzilla.mozilla.org/show_bug.cgi?id=865564 */
	/*  ) started using them for. */
		/* XK_Hangul_PreHanja, but useful concept in general. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_IMEPrev \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 53 )
		/* XK_Hangul_PostHanja, but useful concept in general. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_IMENext \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 54 )
  	/* Return to the candidate before the addition of the most recent */
	/*  disambiguation character: conceptually similar to backspace. Typing */
	/*  another character while the IME is active is used to change the guess */
	/*  (preferably "closer" to the desired option), while this moves to the */
	/*  guess BEFORE the most-recent character that was added (and is still */
	/*  active-if this keysym is issued repeatedly, then a removed character */
	/*  SHOULD NOT be added back in response to the next issuance of this */
	/*  keysym), thus an IME-sp[ecific backspace. */
	/* XK_PreviousCandidate, XK_Hangul_PreviousCandidate, XK_Mae_Koho */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_IMEBackspace \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 55 )
  	/* Switch to displaying only one candidate. */
	/* XK_SingleCandidate, XK_Hangul_SingleCandidate */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_IMESingleView \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 56 )
  	/* Switch to showing multiple candidates. */
  	/* Multiple/All Candidate(s); display all of the guesses instead of just the current */
	/*  prediction; normally this is done automatically after the third wrong guess */
	/*  anyways (for Japanese). */
	/* XK_MultipleCandidate, XK_Hangul_MultipleCandidate, XK_Zen_Koho */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_IMEMultipleView \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 57 )
		/* Cancel the conversion from the initial characters / keysyms to */
		/*  whatever the destination class was. XK_Muhenkan (leave as Japanese */
		/*  Kana), half of XK_Henkan_Mode (toggles Kanji vs Kana), XK_Hangul_End */
		/*  (leave as English (영) / Korean Jamo), half of XK_Hangul (The 한/영 key, */
		/*  toggles Jamo / English (영) vs Hangul (한) ) */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_IMECancel \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 58 )
	
		/* Add to a dictionary. XK_Touroku from X11 supports an IME dictionary. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Dict_Add \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 59 )
		/* Delete from a dictionary. XK_Massyo from X11 supports an IME dictionary. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Dict_Del \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 60 )
	
	/* These are keys grabbed from a Mozilla page listing keys that some of their */
	/*  apps support. I don't recall which page. */
			/* For IME methods, and more. Same as "Accept" or "Ok". */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Commit \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 61 )
			/* Repeat a previous key or action. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Again \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 62 )
			/* Finish an ongoing action. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Finish \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 63 )
	/* These should probably be moved to *_View_*, but maybe not. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Zoom_In \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 64 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Zoom_Out \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 65 )
	/* There was a "play" to "complement Pause", but I already have one. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Brightness_Up \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 66 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Brightness_Down \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 67 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Eject \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 68 )
			/* Not one of the listed keysyms, but I've added it anyways. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_Intake \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 69 )
			/* Toggles between Eject & Intake, another I've added. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Media_ToggleEject \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 70 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Account_LogOn \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 71 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Account_LogOff \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 72 )
	/* Verify the normal mapping of names & sleep-depth, it would be best to actuially ORGANIZE it. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Power_On \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 73 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Power_Off \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 74 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Power_ONOffToggle \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 75 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Power_Standby \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 76 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Power_Suspend \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 77 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Power_Sleep \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 78 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Power_Hibernate \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 79 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Power_Wake \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Actions( 80 )
	
	
	
		/* Action-locks are lock keys, except that only one option is associated */
		/*  with the key. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_actionlocks ( 4 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildactionlocks( high, mod ) \
		( ( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask & ( high ) ) << 21 ) | \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask & ( low ) ) )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildactionlocks( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_actionlocks, num )
	
	
	/* Character-size mode. */
		/* XK_Zenkaku ("to Zenkaku") from X11 applies to Japanese. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Text_Fullsize \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Text_HalfHeight \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 2 )
		/* XK_Hankaku ("to Hankaku") from X11 applies to Japanese, probably Chinese, */
		/*  and maybe Korean. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Text_HalfWidth \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Text_HalfByHalf \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 4 )
	
	/* Key -> character class, "Alternate Graphic Extended". */
  	/* These change the type of character from the key. They're basically */
	/*  locking versions of AltGr, but with more possible options. Jamo is */
	/*  included in this set. */
		/* XK_Romaji */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltGrExt_USAscii \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 5 )
		/* XK_Hiragana */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltGrExt_Hiragana \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 6 )
		/* XK_Katakana */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltGrExt_Katakana \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 7 )
		/* Korean syllabic characters. Note that the characters are composed of a */
		/*  consonant piece and a vowel piece, possibly with another following */
		/*  consonant (uncertain if it's integrated, or a stand-alone "Jamo" */
		/*  character)? */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltGrExt_Hangul \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 8 )
		/* The individual consontant and vowel components of Hangul. XK_Hangul_Jamo */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltGrExt_Jamo \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 9 )
		/* The 3270 at least had keyboards with symbols for APL. So, CONCEPTUALLY */
		/*  this is a useful key. I don't know of it actually existing ANYWHERE, */
		/*  but conceptually it's useful. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AltGrExt_APLSyms \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 10 )
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Encoding_PlatformDefault \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 11 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Encoding_UTF8 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 12 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Encoding_UTF32 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 13 )
			/* aka Junja. Double-byte characters per */
				/* (https://bugzilla.mozilla.org/show_bug.cgi?id=865564) */
			/*  Seems to usually be Johab from KS X 1001.  */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Encoding_HangulJeonja \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 14 )
			/* Single-byte characters, presumably variable-length from KS X 1001. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Encoding_HangulBanja \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_ActionLocks( 15 )
	
	
	
		/* This category is for characters that are missing from Unicode. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_missingcharas ( 5 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildmissingcharas( high, mod ) \
		( ( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask & ( high ) ) << 21 ) | \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask & ( low ) ) )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildmissingcharas( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_missingcharas, num )
	
	
	/* Single-Stroke Multiple-Character N-Graph Keysyms For The X Input Method */
  	/* Note that these all emit MULTIPLE characters in Unicode, to support Breton */
	/*  keyboards, but in Breton each is considered a SINGLE character. The "ch" */
	/*  characters emit a digraph of those two characters, while the "c_h" */
	/*  characters emit a 'c', a "right quote, left bended (Unicode character */
	/*  0x2019)" (per https://bugs.freedesktop.org/show_bug.cgi?id=19506), and */
	/*  then an 'h'. Thus, these go with the "missing character" group. */
	/* Note that while Unicode has a way to represent these characters, it's */
	/*  literally just by emitting multiple characters. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Breton_ch \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Breton_Ch \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 2 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Breton_CH \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Breton_c_h \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 4 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Breton_C_h \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Breton_C_H \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 6 )
	
	/* Braille. I don't know Braille, and what I'm reading says only 8 dot */
	/*  positions are ever used, but I assume there's a reason that X11 had */
	/*  ten (even though I suspect "space and backspace" is the reason), so */
	/*  there's ten here. Note that these need to be combined together, which */
	/*  is what distinguishes them from Unicode: Unicode includes the */
	/*  fully-resolved characters, while THESE are the chording-keyboard */
	/*  style keys that actually get used. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_1 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 17 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_2 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 18 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_3 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 19 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_4 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 20 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_5 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 21 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_6 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 22 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_7 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 23 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_8 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 24 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_9 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 25 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Braille_10 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 26 )
	
	/* DEC VT330+ Technical characters. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECTech_TopLeftSum \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 32 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECTech_BotLeftSum \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 33 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECTech_TopVertSumConn \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 34 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECTech_BotVertSumConn \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 35 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECTech_TopRightSum \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 36 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECTech_BotRightSum \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 37 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECTech_RightMidSum \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 38 )
	
	/* DEC VT100 Special Graphics characters. */
			/* This seems to be a duplicate space. I'm not sure why, but I */
			/*  would guess that either they intended to fill it later, or */
			/*  that they just thought it useful to have a distinct additional */
			/*  space. Regardless, treat it as "special space". */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECSpecial_Blank \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 39 )
	
	/* DEC Publishing, because X11 thought it was some forgotten DEC Publishing */
	/*  font from DECWrite. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECPublish_marker \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 40 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECPublish_circled_trademark \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 41 )
			/* X11 lists a "hexagram", but I don't know whether it's supposed to */
			/*  be a Star of David or from the "I, Ching", and all of them are in */
			/*  Unicode anyways, so I'm leaving a blank spot in the progression. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_DECPublish_cursor \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 42 )
	
	/* So, apparently Thai has two characters (May Thoo and May Han Aakaat) that */
	/*  are both loops, and hard to differentiate. This is for a merged character, */
	/*  which I expect to be useful at least as a marker character by OCR software */
	/*  when it isn't certain what is what. X11 has it as XK_Thai_maihanakat_maitho. */
	/* See also LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_Clarity_*. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas_Thai_maihanakat_maitho \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_MissingCharas( 43 )
	
	
	
		/* This category is for audio keyboards and notes. To find a note, combine */
		/*  all of the sub-categories that you care about. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_audioboardkeys ( 6 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildaudioboardkeys( high, mod ) \
		( ( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask & ( high ) ) << 21 ) | \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask & ( low ) ) )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildaudioboardkeys( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_audioboardkeys, num )
	
	
	/* Note that the common "12 equal temper" chromatic scale, in addition to the 7 */
	/*  notes below, also includes 5 flat/sharp notes: Af/Gs, Bf/As, Df/Cs, Ef/Ds, */
	/*  and Gf/Fs: two options are given for each because in 12et both versions are */
	/*  the same note from a different perspective. In this system, they must be */
	/*  represented with either the Flat & Sharp modifiers, or using the "customkeys" */
	/*  category further below: note that: */
		/* LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_GenericNoteMod */
	/*  exists for the later case. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_A \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 1 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_B \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 2 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_C \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 3 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_D \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 4 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_E \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 5 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_F \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 6 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_G \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 7 )
	
		/* A deadkey marking the following character as a "CommonNote": use */
		/*  CustomKeys, with the "1" position corresponding to A, "2" to B, etc. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_GenericNoteMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 17 )
			/* Moves the note it's associated with to a lower pitch, a stylized */
			/*  version of a lower-case letter B. Note that in common 12et, C */
			/*  flat is simply B. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_FlatMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 18 )
			/* Moves the note it's associated with to a higher pitch, a version */
			/*  of the octothorpe (#) with tilted horizontal lines INSTEAD OF */
			/*  tilted verticals is used to mark it. Note that in common 12et, B */
			/*  sharp is simply C. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_SharpMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 19 )
			/* Indicates that a sharp or flat that was "sticky" (continued to */
			/*  apply, even if the symbol was no longer present) is now cancelled. */
			/*  Represented by a symbol that looks like a square with it's left */
			/*  line extended down, and it's right line extended up. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_NaturalMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 20 )
	
			/* A flat of half the distance of a demiflat. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_CommaFlatMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 25 )
	/* The rest of these are just the flat-note equivalents of the similar sharps */
	/*  below. They won't be further documented, as there's no strong need (at */
	/*  least in my eyes). */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_DemiFlatMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 26 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_SesquiFlatMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 27 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_DoubleFlatMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 28 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_TripleFlatMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 29 )
	
			/* Raises the reference note by a "quarter tone", or in 12et a */
			/*  frequency multiplier of 2 to the one-twentyfourth power of the */
			/*  reference frequency. On a logarithmic scale it's half of a */
			/*  semi-tone, and is stereotypically used in Middle-Eastern music. */
			/*  It's commonly depicted with either the left or right half of an */
			/*  octothorpe (so, two plus signs arranged like a colon, with their */
			/*  vertical lines merged), or as two plus signs side-by-side. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_DemiSharpMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 39 )
			/* Raises the reference note by "three-quarters" of a tone, an */
			/*  addition of the effects of a sharp and a demisharp. Indicated by */
			/*  a demisharp indicator merged with a sharp indicator so there are */
			/*  two horizontal lines and three vertical lines. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_SesquiSharpMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 40 )
			/* Applies a sharp twice: B becomes C sharp instead of just C. It's */
			/*  indicator often resembles an X, or an octothorpe that has had it's */
			/*  points curved towards each other until they form "rain drops" at */
			/*  the corners of a square. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_DoubleSharpMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 41 )
			/* A double-sharp and a sharp. Indicated by a double-sharp sign */
			/*  following a sharp sign. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_CommonNotes_TripleSharpMod \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 42 )
	
		/* This is the standard reference pitch for modern Western music: an A */
		/*  note at 440 Hz. Aka Stuttgart pitch, and ISO 16 from 1975 onwards. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_StandardPitch_A440 \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 47 )
			/* 430 Hz, also suggested by Austria in 1885. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_StandardPitch_1860sFrench \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 47 )
			/* 439 Hz, also suggested by Austria in 1885. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_StandardPitch_1899British \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 47 )
			/* 442 Hz, New York Philharmonic. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_StandardPitch_Bernstein \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 47 )
			/* 415 Hz. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_StandardPitch_Baroque \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 47 )
			/* 466 Hz. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_StandardPitch_Chorton \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 47 )
			/* 427-430 Hz. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_StandardPitch_Classical \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 47 )
	
		/* The standard note system used in Western music: 12 octaves, equally */
		/*  spaced along a logarithmic scale. The spacing is specifically that */
		/*  each note has a frequence of 2 to the power of one-twelfth times the */
		/*  frequency of the note immediately below it: this distance is called */
		/*  the semi-tone, for reasons I don't need to know. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_Octaves_12EqualTemper \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 129 )
			/* An old systyem rarely used these days; there were TWO sizes of */
			/*  semitone instead of just one (as with 12et). */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_Octaves_Pythagorean \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 130 )
			/* Proposed by Claudius Ptolemy in the second century, a "5-limit */
			/*  just intonation". */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_Octaves_PtolemyIntenseDiatonic \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 131 )
			/* Both of these were devised by Wendy Carlos in the 1980s. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_Octaves_WendyCarlosAlpha \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 130 )
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys_Octaves_WendyCarlosBeta \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_AudioBoardKeys( 130 )
	/* There are several other systems, but I'll leave it as a later exercise to add them. */
	
	
	
		/* This category is for arbitrary keys. It just exists so that custom */
		/*  builders can have custom keys without stepping on or being stepped */
		/*  on by updates to this file. */
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_customkeys ( 7 )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcustomkeys( high, mod ) \
		( ( ( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_illegal_droppedmask & ( high ) ) << 21 ) | \
			( LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_legalmask & ( low ) ) )
	
	
	#define LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODE_CustomKeys( num ) \
		LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_buildcustomkeys( \
			LIBANDRIA4_COMMONIOKEYS_SIMPLEKEYCODEMASK_Unicode_highkey_customkeys, num )
	
	
	/* No custom keys will be specified, because literally the implementer */
	/*  should do it themselves. Having said that, remember that '0' should */
	/*  never be allocated, leave it as a null. Allocate from 1 upwards. */
	
#endif
/* End libandria4 basic commoniokeysyms.h */

