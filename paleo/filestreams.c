/*
LibAndria version 4
A C-based general purpose utility library.
Copyright (c) 2025 Jared A. Maddox

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

#include <stddef.h>
#include <errno.h>

#include "streams.h"
#include "streamsinner.h"

#include "simpleops.h"
#include "nulls.h"

#include "commonerrvals.h"



/* Standard FILE* implmentations. */

#include <string.h>

libandria4_commonio_eithhandle
	libandria4_commonio_fopen
	(
		libandria4_char_pascalarray *fname_,
		libandria4_commonio_handle_vtabtype mode_
	)
{
	if
	(
		fname_ &&
		mode_ > libandria4_commonio_handle_vtabtype_invalid &&
		mode_ < libandria4_commonio_handle_vtabtype__END
	)
	{
		char *mode, *options[] =
			{
				"r+b", /* libandria4_commonio_handle_vtabtype_handle == 1 */
				"rb", /* libandria4_commonio_handle_vtabtype_istream */
				"r+b", /* libandria4_commonio_handle_vtabtype_ostream */
				"rb", /* libandria4_commonio_handle_vtabtype_seekable */
				"rb" /* libandria4_commonio_handle_vtabtype_errorable */
			};
		switch( mode_ )
		{
			case libandria4_commonio_handle_vtabtype_handle:
			case libandria4_commonio_handle_vtabtype_istream:
			case libandria4_commonio_handle_vtabtype_ostream:
			case libandria4_commonio_handle_vtabtype_seekable:
			case libandria4_commonio_handle_vtabtype_errorable:
				mode = options[ mode_ - 1 ];
				break;
			
			default:
				LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR(
					LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
		}
		
		size_t i = 0;
		while( i < fname_->len && fname_->body[ i ] != '\0' )
			{ ++i; }
		libandria4_char_pascalarray *fname = 0;
		if( i < fname_->len )
		{
			fname = fname_;
			
		} else {
			
			/* Allocate a new p-string with one extra character, copy over fname, set the last character to null. */
			
			libandria4_char_pascalarray_result res =
				libandria4_char_pascalarray_build( fname_->len + 1 );
#define libandria4_commonio_fopen_OPERR_RET( var ) \
	LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( var.val )
			libandria4_char_pascalarray *a;
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
				res,
					LIBANDRIA4_OP_SETa,
					libandria4_commonio_fopen_OPERR_RET );
			void* memcpy( a->body, fname_->body, fname_->len );
			a->body[ a->len - 1 ] = '\0';
			
			fname = a;
		}
		
		int e_ = errno, retried = 0;
		errno = 0;
		FILE *f = fopen( fname->body, mode );
		libandria4_commonio_fopen_retrytarget:
		if( !f )
		{
			int e2_ = errno;
			switch( e2_ )
			{
				case ERANGE:
			/* The following errors are only defined as on C++11. */
				case EOVERFLOW:
				case EMFILE:
					LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_RANGE );
				
					/* "Temporary" failures. */
				case EINTR:
				case ENETRESET:
				case ETXTBSY:
				case EAGAIN:
#if EAGAIN != EWOULDBLOCK
				case EWOULDBLOCK:
#endif
					if( !retried )
					{
						errno = 0;
						
						/* TODO: Add a timer system to wait before retrying. */
							/* Note: use libandria4_sleep() from commonlib.h */
						
						retried = 1;
						f = fopen( fname->body, mode );
						goto libandria4_commonio_fopen_retrytarget;
						
					} else {
						
						errno = e_;
						LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_WOULDBLOCK );
					}
					
					LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR(
						LIBANDRIA4_RESULT_FAILURE_LOGICFAULT );
				
				
				
					/* Uncertain errors. */
				case ECANCELED:
				case ECONNREFUSED:
				case ECONNRESET:
				case EDEADLK:
				case EEXIST:
				case ECONNABORTED:
				case EALREADY:
				case EBUSY:
				case EINPROGRESS:
				case EISCONN:
				case EMLINK:
				case ENETDOWN:
				case ENETUNREACH:
				case ENFILE:
				case ENOBUFS:
				case ENODATA:
				case ENOLCK:
				case ENOMEM:
				case ENOSR:
				case ENOTCONN:
				case ENOTDIR:
				case ENOTEMPTY:
				case ENOTSOCK:
				case EPIPE:
				case EPROTO:
				case ETIME:
				
					/* Simple failures. */
				case EBADF:
				case EACCES:
				case EFAULT:
				case EFBIG:
				case EHOSTUNREACH:
				case EIDRM:
				case EILSEQ:
				case EINVAL:
				case EIO:
				case EISDIR:
				case ELOOP:
				case ENAMETOOLONG:
				case ENODEV:
				case ENOENT:
				case ENOPROTOOPT:
				case ENOSPC:
				case ENOSTR:
				case ENOSYS:
				case ENOTRECOVERABLE:
				case ENOTSUP:
				case ENOTTY:
				case ENXIO:
#if EOPNOTSUPP != ENOTSUP
				case EOPNOTSUPP:
#endif
				case EOWNERDEAD:
				case EPERM:
				case EPROTONOSUPPORT:
				case EPROTOTYPE:
				case EROFS:
				case ESPIPE:
				case ESRCH:
				case ETIMEDOUT:
				case EXDEV:
				
					/* Explicitly unsupported errors. */
				case EBADMSG:
				case EADDRINUSE:
				case EADDRNOTAVAIL:
				case EAFNOSUPPORT:
				case EDESTADDRREQ:
				case EMSGSIZE:
				case ENOEXEC:
				case ENOLINK:
				case ENOMSG:
					/* Everything else. */
				default:
					LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR(
						LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED );
			}
		}
		errno = e_;
		
		if( fname != fname_ )
		{
			/* Free up the locally-allocated file name. */
			
			libandria4_result res = libandria4_char_pascalarray_destroy( fname );
#define libandria4_commonio_fopen_CLERR_RET( var ) \
	fclose( f ); f = 0; \
	LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( var.val )
			LIBANDRIA4_DEFINE_PASCALARRAY_RESULT_BODYMATCH(
				res,
					LIBANDRIA4_NULL_MACRO,
					libandria4_commonio_fopen_CLERR_RET );
			
			fname = 0;
		}
		
		???
		/* The current code RESEMBLES something complete, but actually isn't complete: We */
		/*  CAN'T hand a FILE* directly to  LIBANDRIA4_COMMONIO_EITHHANDLE_RETHANDLE(), */
		/*  but instead need to properly wrap it! Further, the switch() above most */
		/*  certainly needs to be gone over. */
		/*  So, TODO: finish this. */
		???
		
		LIBANDRIA4_COMMONIO_EITHHANDLE_RETHANDLE( f );
	}
	
	LIBANDRIA4_COMMONIO_EITHHANDLE_RETERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN );
}
