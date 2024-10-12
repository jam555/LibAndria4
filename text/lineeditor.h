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



#include "monads.h"
#include "stdmonads.h"

#include "commoniokeysyms.h"

#include "stdint.h"
/*
	size_t:
Defined in header <stddef.h>
Defined in header <stdio.h>
Defined in header <stdlib.h>
Defined in header <string.h>
Defined in header <time.h>
*/

#include "pascalarray.h"
#include "pascalstring.h"
#include "commonparrs.h"

#include "ctsengine.h"

	/* For libandria4_memmem() */
#include "commonlib.h"



enum
{
	libandria4_lineeditor_mods_nomods = 0,
	
	libandria4_lineeditor_mods_release = 1,
	
		/* Standard shift. */
	libandria4_lineeditor_mods_chara1 = 2,
		/* Alt-graphic, probably just ignore this. */
	libandria4_lineeditor_mods_chara2 = 4,
		/* Currently control, maybe configurable in the future. */
	libandria4_lineeditor_mods_command = 8,
	libandria4_lineeditor_mods_select = 16,
	libandria4_lineeditor_mods_scroll = 32,
	libandria4_lineeditor_mods_insert = 64,
	
	libandria4_lineeditor_mods_last = 128
};
enum
{
	libandria4_lineeditor_oper_init = 0,
	
	libandria4_lineeditor_oper_fetch,
	libandria4_lineeditor_oper_dispatch,
	libandria4_lineeditor_oper_
};
typedef struct libandria4_lineeditor libandria4_lineeditor;
struct libandria4_lineeditor
{
	libandria4_cts_closure delegate, fetcher, alerter, commandkey, altcommandkey, ???;
	
	uintptr_t operation;
	libandria4_commoniokeys_simplekeycode key;
	
		/* The string to edit. */
	libandria4_utf32_pascalarray *str;
		/* The recognized separator characters. */
	libandria4_utf32_pascalarray *sep;
	
	uint8_t modifiers;
		/* For both: 0 is BEFORE the first character, 1 is AFTER the first */
		/*  character, etc. */
	size_t cursor, select;
	
	??? ;
};



int libandria4_lineeditor_iteration_deleteselection
( libandria4_lineeditor *le )
{
	if( le )
	{
		if( le->cursor == le->select )
		{
			return( 0 );
		}
		
		int endwards = ( le->cursor < le->select ) ? 1 : 0;
		size_t start = ( endwards ? le->cursor : le->select );
		size_t len = ( endwards ? le->select : le->cursor ) - start;
		libandria4_utf32_pascalarray_except exc =
			LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_LITERAL(
				libandria4_utf32_pascalarray,  le->str, start, len );
		if( !( libandria4_utf32_pascalarray_excerpt_isvalid( &exc ) ) )
		{
			return( -2 );
		}
		
			/* Delete the designated range. */
		int resi =
			libandria4_utf32_stringops_mutatingdelete
			(
				le->str->body, le->str->len,
				start, len, 0x00 /* Ascii null. */
			);
		if( !resi )
		{
			return( -3 );
		}
		
		le->select = le->cursor;
		
		return( 1 );
	}
	
	return( -1 );
}
	/* Implements the "home" and "end" keys. If le->cursor < extent, then */
	/*  "end" will be enacted. */
int libandria4_lineeditor_iteration_extent
( libandria4_lineeditor *le, size_t extent )
{
	if( le )
	{
		if( le->modifiers & libandria4_lineeditor_mods_command )
		{
			int endwards = ( le->cursor < extent ) ? 1 : 0;
			size_t start = ( endwards ? 0 : le->cursor );
			size_t len = ( endwards ? le->cursor : le->str->len ) - start;
			libandria4_utf32_pascalarray_except exc =
				LIBANDRIA4_DEFINE_PASCALARRAY_EXCERPT_LITERAL(
					libandria4_utf32_pascalarray,  le->str, start, len );
			if( !( libandria4_utf32_pascalarray_excerpt_isvalid( &exc ) ) )
			{
				return( -2 );
			}
			
				/* Delete the designated range. */
			int resi =
				libandria4_utf32_stringops_mutatingdelete
				(
					le->str->body, le->str->len,
					start, len, 0x00 /* Ascii null. */
				);
			if( !resi )
			{
				return( -3 );
			}
			
			le->select = le->cursor;
			
		} else if( le->modifiers & libandria4_lineeditor_mods_select )
		{
			le->select = extent;
			
		} else {
			
			le->cursor = extent;
			le->select = le->cursor;
		}
		
		return( 1 );
	}
	
	return( -1 );
}
	/* Implements left and right arror keys. Set selmod to 1+ to reverse the */
	/*  select mode. */
int libandria4_lineeditor_iteration_horizontal
( libandria4_lineeditor *le, int rightward, int selmod )
{
	rightward = ( rightward ? 1 : -1 );
	selmod = ( selmod ? 1 : 0 );
	int usesel =
		( ( !( le->modifiers & libandria4_lineeditor_mods_select ) == selmod
			) ? 1 : 0 );
	if( le )
	{
		if( le->modifiers & libandria4_lineeditor_mods_command )
		{
			/* Move by a word. Note that select still affects what EXACTLY */
			/*  happens. */
			libandria4_uipresult res =
				pass_separator
				(
					le->str, le->sep,
					( usesel ? le->select : le->cursor ), rightward
				);
			libandria4_success_uipresult step;
			libandria4_failure_uipresult fail = { 0 };
			LIBANDRIA4_UIPRESULT_BODYMATCH( var, matcha, matchb )
			if( fail.val )
			{
				return( -( fail.val ) );
			}
			
			if( usesel )
			{
				le->select += step.val * rightward;
				
			} else {
				le->cursor += step.val * rightward;
				le->select = le->cursor;
			}
			
		} else if( usesel )
		{
			le->select += 1 * rightward;
			
		} else {
			
			le->cursor += 1 * rightward;
			le->select = le->cursor;
		}
		
		return( 1 );
	}
	
	return( -1 );
}

	/* Toggle select-lock, scroll-lock, etc. */
int libandria4_lineeditor_iteration_togglelock
( libandria4_lineeditor *le,  uint8_t *epilog_toggler, uint8_t modifier )
{
	if( le && epilog_toggler )
	{
		if( !modifier )
		{
			return( 0 );
		}
		
		if( !( le->modifiers & libandria4_lineeditor_mods_release ) )
		{
			le->modifiers ^= modifier;
			if( ( *epilog_toggler ) & modifier )
			{
				( *epilog_toggler ) ^= modifier;
			}
		}
		/* We just ignore the release case. */
		
		return( 1 );
	}
	
	return( -1 );
}
int libandria4_lineeditor_iteration_shift
( libandria4_lineeditor *le,  uint8_t *epilog_toggler, uint8_t modifier )
{
	if( le && epilog_toggler )
	{
		if( !modifier )
		{
			return( 0 );
		}
		
		if( !( le->modifiers & libandria4_lineeditor_mods_release ) )
		{
			le->modifiers |= modifier;
			if( ( *epilog_toggler ) & modifier )
			{
				( *epilog_toggler ) ^= modifier;
			}
			
		} else {
			
			le->modifiers &= ~( modifier );
			if( ( *epilog_toggler ) & modifier )
			{
				( *epilog_toggler ) ^= modifier;
			}
		}
		
		return( 1 );
	}
	
	return( -1 );
}


	/* Finds and returns the first non-separator character AFTER a single */
	/*  contiguous block of separator characters. */
	/* stepForward is STEREOTYPICALLY positive when a user presses */
	/*  control-right, and stereotypically not positive when the user */
	/*  presses control-left. */
libandria4_uipresult pass_separator
(
	libandria4_utf32_pascalarray *str,
	libandria4_utf32_pascalarray *separators,
	
	size_t curPos,
	int stepForward
)
{
	libandria4_utf32_pascalarray_excerpt a;
	libandria4_failure_uipresult e = { 0 };
	
	libandria4_utf32_pascalarray_excerpt_result res =
		libandria4_utf32_stringops_memeqspn( str, separators, curPos, stepForward );
	LIBANDRIA4_MONAD_EITHER_BODYMATCH( res, matcha, matchb )
	if( e.val )
	{
			LIBANDRIA4_UIPRESULT_RETURNFAILURE( e.val );
	}
	
	LIBANDRIA4_UIPRESULT_RETURNSUCCESS( a.start );
}
