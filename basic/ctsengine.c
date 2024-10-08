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



int libandria4_cts_isvalid( libandria4_cts_context *ctx )
{
	if( ctx->stacks && ctx->align && ctx->used && ctx->alignreq && ctx->reallocatable )
	{
		size_t len = ctx->stacks->len;
		if
		(
			len == ctx->align->len &&
			len == ctx->used->len &&
			len == ctx->alignreq->len &&
			len == ctx->reallocatable->len
		)
		{
			if( ctx->next_iteration.handler )
			{
				return( 2 );
			}
			
			return( 1 );
		}
		
		return( 0 );
	}
	
	return( -1 );
}
int libandria4_cts_isvalid2( libandria4_cts_context *ctx )
{
	if( libandria4_cts_isvalid( ctx ) )
	{
		size_t iter = 0;
		while( iter < ctx->stacks->len )
		{
			if( !( ctx->stacks->body[ iter ] ) )
			{
				return( -2 );
			}
			if
			(
				ctx->stacks->body[ iter ]->len <
				ctx->align->body[ iter ] + ctx->used->body[ iter ]
			)
			{
				return( -3 );
			}
			
			++iter;
		}
		
		return( 1 );
	}
	
	return( -1 );
}

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



int libandria4_cts_sizedpop( libandria4_cts_context *ctx, size_t stack,  void *dest_, size_t size )
{
	if( ctx && dest )
	{
		if( !libandria4_cts_isvalid2( ctx ) )
		{
			return( -2 );
		}
		if( ctx->stacks.len <= stack )
		{
			return( -3 );
		}
		if( size > ctx->used->body[ stack ] )
		{
			return( -4 );
		}
		if( !size )
		{
			return( 0 );
		}
		
		unsigned char *dest = (unsigned char*)dest_;
		while( size )
		{
			--size;
			--( ctx->used->body[ stack ] );
			
			dest[ size ] =
				ctx->stacks->body[ stack ]->body
				[
					ctx->align->body[ stack ] +
					ctx->used->body[ stack ]
				];
		}
		
		return( 1 );
	}
	
	return( -1 );
}
int libandria4_cts_sizedpush( libandria4_cts_context *ctx, size_t stack,  void *dest_, size_t size )
{
	if( ctx && dest )
	{
		if( !libandria4_cts_isvalid2( ctx ) )
		{
			return( -2 );
		}
		if( ctx->stacks.len <= stack )
		{
			return( -3 );
		}
		if
		(
			ctx->stacks->body[ stack ]->len <
			ctx->align->body[ stack ] + ctx->used->body[ stack ] + size
		)
		{
			return( -4 );
		}
		if( !size )
		{
			return( 0 );
		}
		
		unsigned char *dest = (unsigned char*)dest_;
		while( size )
		{
			--size;
			
			dest[ size ] =
				ctx->stacks->body[ stack ]->body
				[
					ctx->align->body[ stack ] +
					ctx->used->body[ stack ] +
					size
				];
		}
		ctx->used->body[ stack ] += size;
		
		return( 1 );
	}
	
	return( -1 );
}


LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _schar, signed char );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _uchar, unsigned char );

LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _sshort, signed short );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _ushort, unsigned short );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _sint, signed int );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _uint, unsigned int );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _slong, signed long );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _ulong, unsigned long );

LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _float, float );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _double, double );

LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _sizet, size_t );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _ptrdifft, ptrdiff_t );

LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _voidp, void* );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _scharp, signed char* );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _ucharp, unsigned char* );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _voidf, void (*)() );

LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
LIBANDRIA4_CTS_DEFPOP( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );


LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _schar, signed char );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _uchar, unsigned char );

LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _sshort, signed short );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _ushort, unsigned short );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _sint, signed int );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _uint, unsigned int );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _slong, signed long );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _ulong, unsigned long );

LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _float, float );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _double, double );

LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _sizet, size_t );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _ptrdifft, ptrdiff_t );

LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _voidp, void* );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _scharp, signed char* );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _ucharp, unsigned char* );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _voidf, void (*)() );

LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _ctsffuncp, libandria4_cts_framefunc* );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _ctsclsr, libandria4_cts_closure );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _ctsclsrp, libandria4_cts_closure* );
LIBANDRIA4_CTS_DEFPUSH( libandria4_cts_, _ctsctxtp, libandria4_cts_context* );



libandria4_cts_closure libandria4_cts_innerreturn( libandria4_cts_context *ctx, void *dat )
{
	static libandria4_cts_closure stop = LIBANDRIA4_CTS_BUILDCLOSURE( 0, 0 );
	if( !( stop.handler ) )
	{
		stop =
			LIBANDRIA4_CTS_BUILDCLOSURE
			(
				&libandria4_cts_framefunc_stoprun,
				(void*)&stop
			);
	}
	
	libandria4_cts_closure ret;
	libandria4_cts_innerreturn_data *data = (libandria4_cts_innerreturn_data*)dat;
	
	int res;
	if( data )
	{
		res = libandria4_cts_pop_ctsclsr( ctx, data->stack,  &ret );
		
	} else {
		
		res = -1;
	}
	if( !res )
	{
		return
		(
			( data->failfunc ) ?
				( data->failfunc( data->faildata, ctx, res ) ) :
				(
					LIBANDRIA4_CTS_BUILDCLOSURE
					(
						&libandria4_cts_framefunc_stoprun,
						(void*)&stop
					)
				)
		);
	}
	
	return( ret );
}
