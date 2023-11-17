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


#include "stdhandlers.h"

	
	/* Just ignores the current character */
int vt100net_actions_ignore( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Prints the current character, only happens in GROUND (really GROUND_POSTREAD). */
	/* Must modify glyph in accordance with current char mappings & shift states. */
	/*  ASCII 0x20 & 0x7F have somewhat special behavior. */
int vt100net_actions_print( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Perform a C0 or C1 control function. */
int vt100net_actions_execute( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Reset current "private" flag, intermediate characters, final character, and */
	/*  parameters. Happens entering ESCAPE, CSI_ENTRY, and DCS_ENTRY. */
int vt100net_actions_clear( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Store private marker or intermediate character for use when a "final" */
	/*  character arrives. X3.64 defined control sequences with one intermediate, */
	/*  Digital defined escape sequences with two intermediates and device control */
	/*  strings with one. If too many intermediates arrive, it can be flaged to */
	/*  turn the op into a null op. */
int vt100net_actions_collect( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Collect parameter string characters for SEC or DCS sequences, and build */
	/*  list of parameters. Processes characters '0'-'9', and ';'. Semicolon */
	/*  seperates parameters. No limit to param string length, but only 16 */
	/*  params need be stored, all extras are silently ignored. */
	/* VT500 manual says that all parameters will be capped at 9999 (decimal), */
	/*  but also says that DECSR can accept 16383. Individual funcs must verify */
	/*  parameter values anyways, so just support 16383 (14 bit unsigned max), */
	/*  and leave the rest to the command. */
	/* Commands can have defaults, triggered by either leaving blank or setting */
	/*  at 0. For blank use an extra bit in the 16bit param value as a flag, */
	/*  and leave the rest to the command. ECMA-48 distinguishes between blank */
	/*  & zero; until fifth edition it had a ZDM mode that treated them */
	/*  identically, but it costs nothing extra to skip that... */
int vt100net_actions_param( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Final char of esc seq has arrived; determine operation from */
	/*  intermediates and final, then exec. Remember *_collect(). */
int vt100net_actions_esc_dispatch( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* As with esc, but also use marker for dispatch. "Pass in param list", but */
	/*  the command can probably just grab those itself... The private marker is */
	/*  only needed for dispatch by VT500's DECSTBM and DECPCTERM, but there's */
	/*  no real problem in most or any cases. */
	/* The command will ignore extra params, but missing params may cause a */
	/*  partial or complete NOOP instead of the intended action. */
int vt100net_actions_csi_dispatch( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Happens when "final" char arrives in first part of device control string. */
	/*  Dispatches by private marker, intermediates, and final char, passing in */
	/*  params; also selects handler for rest of chars in control string, */
	/*  handler will be called bu *_put() for every remaining string char as it */
	/*  arrives. This allows easy plug-in of extra parsers to support added */
	/*  functionality: main parser could add e.g. DECDLD fairly easy, but e.g. */
	/*  ReGIS is overly complicated to belong in main parser. */
int vt100net_actions_hook( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Passes characters from data string part of a device control string to a */
	/*  handler selected by *_hook(). Also passes C0 controls to the handler. */
int vt100net_actions_put( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Calls a previously selected handler with "end of data" when a device */
	/*  control string is terminated with ST, CAN, SUB, or ESC. This allows the */
	/*  handler to finish cleanly. */
int vt100net_actions_unhook( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Initializes an external parser (the OSC Handler) to handle the */
	/*  characters from the control string. OSC control strings are structured */
	/*  differently than device control strings, so there's no choosing the */
	/*  parser. */
int vt100net_actions_osc_start( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Passes characters to the OSC Handler as they arrive. There is no need to */
	/*  buffer characters while waiting for the end of the control string. */
int vt100net_actions_osc_put( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
	/* Called to let the OSC Handler finish neatly when ST, CAN, SUB, or ESC */
	/*  terminate the OSC string. */
int vt100net_actions_osc_end( vt100net_termcontext *term_ctx, uint8_t nstate )
{
	???
}
