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

#include "extrachar.h"

LIBANDRIA4_DEFINE_PASCALARRAY_WRAPEDDEFINE( libandria4_extrachar_, libandria4_extrachar, memfuncs_ptr );



libandria4_extrachar_result libandria4_extrachar_getchar
(
	libandria4_extrachar_stream *stream,
		uintmax_t *over_line,
		uintmax_t *over_col,
		libandria4_extrachar_flags *over_flags
)
{
	libandria4_extrachar_result ret =
		LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
			LIBANDRIA4_RESULT_FAILURE_DOMAIN );
	
	if( stream )
	{
		ret =
			LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
				LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN );
		
		if( stream->hand || ( stream->buf && stream->buf->len && stream->buf->len >= stream->used ) )
		{
			if( stream->buf && stream->used > 0 )
			{
				--( stream->used );
				ret = LIBANDRIA4_EXTRACHARRESULT_BUILDSUCCESS(
						stream->buf->body[ stream->used ] );
				
			} else if( stream->hand )
			{
				libandria4_extrachar chara =
					{
						( over_line ? *over_line : stream->line ),
						( over_col ? *over_col : stream->column ),
						stream->index,
						0, /* Just use a dummy value for ->c . */
						( over_flags ? *over_flags : stream->flags )
					};
				
				int res = -2, tmp, err, swap = errno;
				libandria4_commonio_byte a;
				libandria4_commonio_err b;
				libandria4_commonio_succ c;
				libandria4_commonio_eithgeneric status;
					/* We actually don't use the value of "e", it's */
					/*  just filler. */
				libandria4_commonio_eithbyte e, test =
					libandria4_commonio_handle_EXPRMATCH(
						stream->hand,
							libandria4_commonio_handle_GETC_HELPER1,
							libandria4_commonio_handle_GETC_HELPER1,
							
							LIBANDRIA4_OP_ISVAReFLAGresASn1,
							LIBANDRIA4_OP_ISVARe );
				err = errno;
				errno = swap;
				LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
					test,
						LIBANDRIA4_OP_SETaFLAGresAS1,
						LIBANDRIA4_OP_SETbFLAGresAS0 );
				switch( res )
				{
					case 1:
						/* Success. */
						chara.c = a;
						ret = LIBANDRIA4_EXTRACHARRESULT_BUILDSUCCESS( chara );
						break;
					case 0:
						/* getc() error. */
						status = libandria4_commonio_handle_EOF( stream->hand );
						LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
							status,
								LIBANDRIA4_OP_SETcFLAGresAS1,
								LIBANDRIA4_OP_SETbFLAGresAS0 );
							/* Handle quick returns. */
						if( res != 1 || c != 0 )
						{
							if( res == 1 )
							{
								tmp = LIBANDRIA4_RESULT_FAILURE_EOF;
								
							} else if( res == 0 )
							{
								tmp = LIBANDRIA4_RESULT_FAILURE_IOERROR;
								
							} else {
								
								tmp = LIBANDRIA4_RESULT_FAILURE_LOGICFAULT;
							}
							ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( tmp );
							
								/* Just skip all further processing. */
							res = 1;
							break;
						}
						
						/* Not EOF. */
						status = libandria4_commonio_handle_ERROR( stream->hand );
						LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
							status,
								LIBANDRIA4_OP_SETcFLAGresAS1,
								LIBANDRIA4_OP_SETbFLAGresAS0 );
							/* Handle quick returns. */
						if( res != 1 || c != 0 )
						{
							if( res == 1 )
							{
								status = libandria4_commonio_handle_CLEARERR( hptr );
								LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
									status,
										LIBANDRIA4_OP_SETcFLAGresAS1,
										LIBANDRIA4_OP_SETbFLAGresAS0 );
									/* Handle quick returns. */
								if( res != 1 )
								{
									ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
										LIBANDRIA4_RESULT_FAILURE_IOERROR );
									
										/* Just skip all further */
										/*  processing. */
									res = 1;
									break;
								}
								
									/* The error is cleared, so make */
									/*  certain to enter the loop. */
								res = 0;
								
							} else if( res == 0 )
							{
								tmp = LIBANDRIA4_RESULT_FAILURE_IOERROR;
								res = 1;
								
							} else {
								
								tmp = LIBANDRIA4_RESULT_FAILURE_LOGICFAULT;
								res = 1;
							}
							ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( tmp );
							
								/* Just skip all further processing. */
							break;
							
						} else {
							
							/* Blindly return the error number set by */
							/*  getc()... this should SERIOUSLY be */
							/*  converted to commonerrvals.h values or */
							/*  something, maybe logging? */
							
							ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( err );
							res = 1;
						}
						
							/* If res == 0, then the loop will be entered. */
						break;
					case -1:
						/* Error: Output stream. */
						ret =
							LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
								LIBANDRIA4_RESULT_FAILURE_INVALIDOPER );
						break;
					case -2:
						/* Bad handle. */
						ret =
							LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
								LIBANDRIA4_RESULT_FAILURE_BROKEN );
					default:
						ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
							LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
						break;
				}
				
				while( res == 0 )
				{
					test =
						libandria4_commonio_handle_EXPRMATCH(
							stream->hand,
								libandria4_commonio_handle_GETC_HELPER1,
								libandria4_commonio_handle_GETC_HELPER1,
								
								LIBANDRIA4_OP_ISVAReFLAGresASn1,
								LIBANDRIA4_OP_ISVARe );
					LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
						test,
							LIBANDRIA4_OP_SETaFLAGresAS1,
							LIBANDRIA4_OP_SETbFLAGresAS0 );
					
					switch( res )
					{
						case 1:
							/* Success. */
							chara.c = a;
							ret = LIBANDRIA4_EXTRACHARRESULT_BUILDSUCCESS( chara );
							break;
						case 0:
							/* getc() error. */
							status = libandria4_commonio_handle_EOF( stream->hand );
							LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
								status,
									LIBANDRIA4_OP_SETcFLAGresAS1,
									LIBANDRIA4_OP_SETbFLAGresAS0 );
								/* Handle quick returns. */
							if( res != 1 || c != 0 )
							{
								if( res == 1 )
								{
									tmp = LIBANDRIA4_RESULT_FAILURE_EOF;
									
								} else if( res == 0 )
								{
									tmp = LIBANDRIA4_RESULT_FAILURE_IOERROR;
									
								} else {
									
									tmp = LIBANDRIA4_RESULT_FAILURE_LOGICFAULT;
								}
								ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( tmp );
								
									/* Just skip all further processing. */
								res = 1;
								break;
							}
							
							/* Not EOF. */
							status = libandria4_commonio_handle_ERROR( stream->hand );
							LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
								status,
									LIBANDRIA4_OP_SETcFLAGresAS1,
									LIBANDRIA4_OP_SETbFLAGresAS0 );
								/* Handle quick returns. */
							if( res != 1 || c != 0 )
							{
								if( res == 1 )
								{
									status = libandria4_commonio_handle_CLEARERR( hptr );
									LIBANDRIA4_COMMONIO_EITHBYTE_BODYMATCH(
										status,
											LIBANDRIA4_OP_SETcFLAGresAS1,
											LIBANDRIA4_OP_SETbFLAGresAS0 );
										/* Handle quick returns. */
									if( res != 1 )
									{
										ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
											LIBANDRIA4_RESULT_FAILURE_IOERROR );
										
											/* Just skip all further */
											/*  processing. */
										res = 1;
										break;
									}
									
										/* The error is cleared, so make */
										/*  certain to enter the loop. */
									res = 0;
									
								} else if( res == 0 )
								{
									tmp = LIBANDRIA4_RESULT_FAILURE_IOERROR;
									res = 1;
									
								} else {
									
									tmp = LIBANDRIA4_RESULT_FAILURE_LOGICFAULT;
									res = 1;
								}
								ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( tmp );
								
									/* Just skip all further processing. */
								break;
								
							} else {
								
								/* Blindly return the error number set by */
								/*  getc()... this should SERIOUSLY be */
								/*  converted to commonerrvals.h values or */
								/*  something, maybe logging? */
								
								ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( err );
								res = 1;
							}
							
								/* If res == 0, then the loop will just */
								/*  continue looping. */
							break;
						case -1:
							/* Error: Output stream. */
							ret =
								LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
									LIBANDRIA4_RESULT_FAILURE_CORRUPTED );
							break;
						case -2:
							/* Bad handle. */
							ret =
								LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
									LIBANDRIA4_RESULT_FAILURE_KILLING );
						default:
							ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
								LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
							break;
					}
				}
				
			} else {
				
				ret =
					LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM(
						LIBANDRIA4_RESULT_FAILURE_EOF );
			}
		}
	}
	
	return( ret );
}
int libandria4_extrachar_ungetchar
(
	libandria4_extrachar_stream *stream,
		libandria4_extrachar ec
)
{
	int ret = LIBANDRIA4_RESULT_FAILURE_DOMAIN;
	
	if( stream )
	{
		ret = LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN;
		
		if( stream->buf )
		{
			if( stream->used < stream->buf->len )
			{
				stream->buf->body[ stream->used ] = ec;
				++( stream->used );
				
				ret = LIBANDRIA4_RESULT_GENERIC;
				
			} else {
				
				ret = LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS;
			}
		}
	}
	
	return( ret );
}
libandria4_extrachar_result libandria4_extrachar_peekchar
(
	libandria4_extrachar_stream *stream,
		uintmax_t *over_line,
		uintmax_t *over_col,
		libandria4_extrachar_flags *over_flags
)
{
	int ret = LIBANDRIA4_RESULT_FAILURE_DOMAIN;
	
	if( stream )
	{
		int a = 0;
		ret = LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN;
		
		ret =
			libandria4_extrachar_getchar
			(
				libandria4_extrachar_stream *stream,
					uintmax_t *over_line,
					uintmax_t *over_col,
					libandria4_extrachar_flags *over_flags
			);
		LIBANDRIA4_EXTRACHARRESULT_BODYMATCH(
			ret,
				LIBANDRIA4_OP_SETaTO1,
				LIBANDRIA4_NULL_MACRO,
				LIBANDRIA4_NULL_MACRO,
				LIBANDRIA4_NULL_MACRO
		);
		
		if( a == 1 )
		{
			a = libandria4_extrachar_ungetchar
				(
					libandria4_extrachar_stream *stream,
						libandria4_extrachar ec
				);
			if( a != LIBANDRIA4_RESULT_GENERIC )
			{
				ret = LIBANDRIA4_EXTRACHARRESULT_BUILDERROR_NUM( a );
			}
		}
	}
	
	return( ret );
}
