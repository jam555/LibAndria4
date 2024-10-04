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

#include "ctsengine.h"



	/* Performs the actual trampolining. */
int libandria4_cts_engine( libandria4_cts_context *ctx )
{
	if( ctx )
	{
		while( ctx->run != 0 )
		{
			if( ctx->next_iteration.handler )
			{
				ctx->next_iteration =
					ctx->next_iteration.handler( ctx, ctx->next_iteration.data );
			}
			
			if( ctx->run )
			{
				--( ctx->run );
			}
		}
	}
	
	return( -1 );
}

libandria4_cts_closure libandria4_cts_framefunc_stoprun
(
	libandria4_cts_context *ctx, void *next_iteration
)
{
	if( ctx )
	{
		ctx->run = 0;
	}
	
	return( *( (libandria4_cts_closure*)next_iteration ) );
}
