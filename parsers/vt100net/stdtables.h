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

#ifndef LIBANDRIA4_PARSERS_VT100NET_STDTABLES_H
# define LIBANDRIA4_PARSERS_VT100NET_STDTABLES_H
	
	#include "terminal.h"
	
	/* Various types & values for a "vanilla" terminal implementation. */
	
	
	extern uint8_t onEntry[ 14 ], onExit[ 14 ];
		/* The C1 portion of the various uint8_t arrays below are */
		/*  variously not filled out at all, or in need of */
		/*  verification. */
	extern uint8_t vt100net_fromAnywhere[ 256 ];
	extern uint8_t
		*vt100net_stateMappings
			[
				vt100net_termcontext_STATES__PAST_END -
				vt100net_termcontext_GROUND
			];
	
	extern vt100net_handler_mapping vt100net_handler_mappingset[ 29 ];
	
	extern vt100net_action_handler vt100net_handlers[ 15 ];
	
		/* These defines are indexes into vt100net_handlers[]. */
		/* I think that vt100net_HAND_IGN and vt100net_HAND_NULLACT are */
		/*  basically the same thing, so I've pointed them at the same */
		/*  handler, but it would be better to verify that.*/
	#define vt100net_HAND_IGN ( 0 )
	#define vt100net_HAND_NULLACT ( 0 )
	#define vt100net_HAND_PRINT ( 1 )
	#define vt100net_HAND_EXEC ( 2 )
	#define vt100net_HAND_CLEAR ( 3 )
	#define vt100net_HAND_COLL ( 4 )
	#define vt100net_HAND_PARAM ( 5 )
	#define vt100net_HAND_ESCDISP ( 6 )
	#define vt100net_HAND_CSIDISP ( 7 )
	#define vt100net_HAND_HOOK ( 8 )
	#define vt100net_HAND_PUT ( 9 )
	#define vt100net_HAND_UNHOOK ( 10 )
	#define vt100net_HAND_OSCSTRT ( 11 )
	#define vt100net_HAND_OSCPUT ( 12 )
	#define vt100net_HAND_OSCEND ( 13 )
	#define vt100net_HAND_FALLTHROUGH ( 14 )
	
#endif
/* End libandria4 parsers vt100net stdtables.h */
