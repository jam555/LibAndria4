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

#ifndef LIBANDRIA4_STDMONADS_H
# define LIBANDRIA4_STDMONADS_H
	
	#include <stddef.h>
	#include <stdint.h>
	
	#include "monads.h"
	
	
	
	#define LIBANDRIA4_STDERRS_BADARGS_SIMPLE ( -1 )
	#define LIBANDRIA4_STDERRS_BADARGS_COMPLEX ( -2 )
	#define LIBANDRIA4_STDERRS_BADARGS_DEEP ( -3 )
	
		/* The number of this error will need to be increased as new ones */
		/*  are added: in particular, this must ALWAYS be the lowest */
		/*  numbered error in the *_STDERRS_* group. */
	#define LIBANDRIA4_STDERRS__LAST_UNALLOC_ERR ( -4 )
	
	
	
	/* These are intended to allow success & failure to be encoded via type, */
	/*  thus reducing the actual value to just a version of one or the */
	/*  other. And no, C doesn't have MEANINGFUL direct support for this, */
	/*  but it does have simple typing, and that is enough to be useful. */
	
	typedef struct libandria4_success_stdresult
	{
		int val;
		
	} libandria4_success_result;
	typedef struct libandria4_failure_stdresult
	{
		int val;
		
	} libandria4_failure_result;
	
	
	
	/* These are standard ints for standard errno values. A lot of stuff */
	/*  that got brought into C++ from POSIX is currently hidden by the */
	/*  preprocessor. */
	
	#define LIBANDRIA4_RESULT_GENERICFALSE ( 0 )
	#define LIBANDRIA4_RESULT_GENERICTRUE ( 1 )
	#define LIBANDRIA4_RESULT_GENERIC ( 2 )
	
		/* The domain of a mathematical function is the full set of it's */
		/*  legal inputs. So if you get a domain error, you fed it wrong. */
		/*  Probably not by feeding it after midnight though. */
	#define LIBANDRIA4_RESULT_FAILURE_DOMAIN ( 3 )
		/* Meanwhile, the RANGE is the valid OUTPUTS of a mathematical */
		/*  function. If you get this error, think of it as an overflow */
		/*  error. */
	#define LIBANDRIA4_RESULT_FAILURE_RANGE ( 4 )
		/* And this one is expected to be unrelated to math, as it's an */
		/*  "invalid sequence" error. Mostly relevant for multi-byte */
		/*  character sequences, much like trying to cross a bridge AFTER */
		/*  you burn it down. */
	#define LIBANDRIA4_RESULT_FAILURE_ILSEQ ( 5 )
		/* This error is for when I don't bother creating a distinct failure */
		/*  number. No, not GENERIC, undifferentiated. */
	#define LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ( 6 )
		/* To mark stuff that's not yet been PROPERLY initialized. */
	#define LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ( 7 )
		/* Should be obvious enough... but intentionally vague. */
	#define LIBANDRIA4_RESULT_FAILURE_GENERICMISMATCH ( 8 )
	#define LIBANDRIA4_RESULT_FAILURE_SIZEMISMATCH ( 9 )
	#define LIBANDRIA4_RESULT_FAILURE_TYPEMISMATCH ( 10 )
	#define LIBANDRIA4_RESULT_FAILURE_MODEMISMATCH ( 11 )
		/* Array stuff. */
	#define LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS ( 12 )
	#define LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS ( 13 )
		/* File & directory stuff. */
	#define LIBANDRIA4_RESULT_FAILURE_EOF ( 14 )
	
	
	#if 0
		/* These are apparently POSIX values that were added to C++11. */
		
		/* Note: renumber these. */
		
			/* EBADF */
		#define LIBANDRIA4_RESULT_FAILURE_BADFILEDESC ( 5 )
			/* EEXIST */
		#define LIBANDRIA4_RESULT_FAILURE_FILEEXISTS ( 6 )
			/* ENAMETOOLONG */
		#define LIBANDRIA4_RESULT_FAILURE_NAMETOOLONG ( 7 )
			/* ESPIPE, note that "broken pipe" is actually EPIPE. */
		#define LIBANDRIA4_RESULT_FAILURE_INVALIDSEEK ( 8 )
			/* EIO. Usually hardware related. */
		#define LIBANDRIA4_RESULT_FAILURE_IOERROR ( 9 )
			/* EISDIR */
		#define LIBANDRIA4_RESULT_FAILURE_ISDIR ( 10 )
			/* ENOENT, "no entry". */
		#define LIBANDRIA4_RESULT_FAILURE_NOFILEORDIR ( 11 )
			/* ENOTDIR */
		#define LIBANDRIA4_RESULT_FAILURE_NOTDIR ( 12 )
			/* EACCES */
		#define LIBANDRIA4_RESULT_FAILURE_ACCESSDENIED ( 13 )
			/* EROFS */
		#define LIBANDRIA4_RESULT_FAILURE_ROFILESYS ( 14 )
			/* EMFILE, too many open in PROCESS specifically. */
		#define LIBANDRIA4_RESULT_FAILURE_TOOMANYOPFILES ( 15 )
			/* ENFILE, too many open in SYSTEM specifically. */
		#define LIBANDRIA4_RESULT_FAILURE_TOOMANYOPFILES2 ( 16 )
			/* ELOOP */
		#define LIBANDRIA4_RESULT_FAILURE_SYMLINKSTOODEEP ( 17 )
			/* EOVERFLOW */
		#define LIBANDRIA4_RESULT_FAILURE_OVERFLOW ( 18 )
			/* EFAULT: Note that this indicates a segfault. */
		#define LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ( 19 )
			/* ENOMEM, there's not enough memory available. */
		#define LIBANDRIA4_RESULT_FAILURE_MEMORYFULL ( 20 )
		
		/* The following are pairings of C++11 enum members and the */
		/*  C++11-standardized posix error macros that they correspond to. */
		/* These have not yet been brought in, but it would be good if they */
		/*  were. Note that the POSIX meanings should probably be followed. */
		/*  Also, while POSIX standardizes the macro names, it does not */
		/*  attempt to standardize the values, as many of them would likely */
		/*  have been defined in some form by already existing pre-POSIX */
		/*  Unix distributions, such as the early BSD variants. */
		/*
			address_family_not_supported	EAFNOSUPPORT
			address_in_use	EADDRINUSE
			address_not_available	EADDRNOTAVAIL
			already_connected	EISCONN
			argument_list_too_long	E2BIG
			bad_message	EBADMSG
			broken_pipe	EPIPE
			connection_aborted	ECONNABORTED
			connection_already_in_progress	EALREADY
			connection_refused	ECONNREFUSED
			connection_reset	ECONNRESET
			cross_device_link	EXDEV
			destination_address_required	EDESTADDRREQ
			device_or_resource_busy	EBUSY
			directory_not_empty	ENOTEMPTY
			executable_format_error	ENOEXEC
			file_too_large	EFBIG
			function_not_supported	ENOSYS
			host_unreachable	EHOSTUNREACH
			identifier_removed	EIDRM
			illegal_byte_sequence	EILSEQ
			inappropriate_io_control_operation	ENOTTY
			interrupted	EINTR
			invalid_argument	EINVAL
			message_size	EMSGSIZE
			network_down	ENETDOWN
			network_reset	ENETRESET
			network_unreachable	ENETUNREACH
			no_buffer_space	ENOBUFS
			no_child_process	ECHILD
			no_link	ENOLINK
			no_lock_available	ENOLOCK
			no_message	ENOMSG
			no_message_available	ENODATA
			no_protocol_option	ENOPROTOOPT
			no_space_on_device	ENOSPC
			no_stream_resources	ENOSR
			no_such_device	ENODEV
			no_such_device_or_address	ENXIO
			no_such_process	ESRCH
			not_a_socket	ENOTSOCK
			not_a_stream	ENOSTR
			not_connected	ENOTCONN
			not_supported	ENOTSUP
			operation_canceled	ECANCELED
			operation_in_progress	EINPROGRESS
			operation_not_permitted	EPERM
			operation_not_supported	EOPNOTSUPP
			operation_would_block	EWOULDBLOCK
			owner_dead	EOWNERDEAD
			protocol_error	EPROTO
			protocol_not_supported	EPROTONOSUPPORT
			resource_deadlock_would_occur	EDEADLK
			resource_unavailable_try_again	EAGAIN
			state_not_recoverable	ENOTRECOVERABLE
			stream_timeout	ETIME
			text_file_busy	ETXTBSY
			timed_out	ETIMEDOUT
			too_many_links	EMLINK
			wrong_protocol_type	EPROTOTYPE
		*/
	#endif
	/* If you add to this, add support in libandria4_errno_2result() too. Note */
	/*  that C++11 added a number of errno errors from POSIX, so there IS */
	/*  some more stuff to add. */
	
	
	
		/* These two types are used if your success or failure needs to */
		/*  support encoding as a pointer. */
	typedef struct libandria4_success_uipresult
	{
		uintptr_t val;
		
	} libandria4_success_uipresult;
	typedef struct libandria4_failure_uipresult
	{
		uintptr_t val;
		
	} libandria4_failure_uipresult;
		/* As a special case, 0 always means general success or general */
		/*  failure, since it can't POSSIBLY point to something that's */
		/*  reliably legally placed, and success or error is indicated by */
		/*  type instead of value. */
	#define LIBANDRIA4_UIPRESULT_GENERIC ( 0 )
	
	
	
		/* This probably SHOULDN'T be the *_DEFINITION()... */
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_result,
		
		libandria4_success_result,
		libandria4_failure_result
	);
	
	#define LIBANDRIA4_RESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( libandria4_result, libandria4_success_result, (val) )
	#define LIBANDRIA4_RESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( libandria4_result, libandria4_failure_result, (val) )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_RESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_RESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_RESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_result, libandria4_success_result, val )
	#define LIBANDRIA4_RESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( libandria4_result, libandria4_failure_result, val )
	
	
	libandria4_result libandria4_errno_2result()
	{
		#include <errno.h>
		
		int errnum = errno;
		
		switch( errnum )
		{
			case 0:
					/* No error. */
				break;
				
			case EDOM:
				return
				(
					LIBANDRIA4_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_DOMAIN )
				);
			case ERANGE:
				return
				(
					LIBANDRIA4_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_RANGE )
				);
			case EILSEQ:
				return
				(
					LIBANDRIA4_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_ILSEQ )
				);
				
			default:
					/* Because whatever it is, I added a result number for it. */
				return
				(
					LIBANDRIA4_RESULT_BUILDFAILURE( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED )
				);
		}
		
		return( LIBANDRIA4_RESULT_BUILDSUCCESS( LIBANDRIA4_RESULT_GENERIC ) );
	}
	libandria4_result libandria4_errno_popresult( int *errnum )
	{
		libandria4_result res = libandria4_errno_2result();
		
		if( errnum )
		{
			*errnum = errno;
		}
		
		errno = 0;
		
		return( res );
	}
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_charresult,
		
		char,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_CHARRESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_charresult, char, (val) \
		)
	#define LIBANDRIA4_CHARRESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_charresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_CHARRESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_CHARRESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_CHARRESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_charresult, char, val )
	#define LIBANDRIA4_CHARRESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_charresult, libandria4_failure_uipresult, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_intresult,
		
		int,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_INTRESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_intresult, int, (val) \
		)
	#define LIBANDRIA4_INTRESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_intresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_INTRESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_INTRESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_INTRESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_intresult, int, val )
	#define LIBANDRIA4_INTRESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_intresult, libandria4_failure_uipresult, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_uipresult,
		
		libandria4_success_uipresult,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_UIPRESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_uipresult, libandria4_success_uipresult, (val) \
		)
	#define LIBANDRIA4_UIPRESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_uipresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_UIPRESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_UIPRESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_UIPRESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( \
			libandria4_uipresult, libandria4_success_uipresult, val )
	#define LIBANDRIA4_UIPRESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_uipresult, libandria4_failure_uipresult, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_ptrresult,
		
		void*,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_PTRRESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_ptrresult, void*, (val) \
		)
	#define LIBANDRIA4_PTRRESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_ptrresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_PTRRESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_PTRRESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_PTRRESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_ptrresult, void*, val )
	#define LIBANDRIA4_PTRRESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_ptrresult, libandria4_failure_uipresult, val )
	
	
	
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION(
		libandria4_sizeresult,
		
		size_t,
		libandria4_failure_uipresult
	);
	
	#define LIBANDRIA4_SIZERESULT_BUILDSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			libandria4_sizeresult, size_t, (val) \
		)
	#define LIBANDRIA4_SIZERESULT_BUILDFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			libandria4_sizeresult, libandria4_failure_uipresult, (val) \
		)
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
		/*  The matches must be function-style, though function macros are */
		/*  allowed. */
	#define LIBANDRIA4_SIZERESULT_BODYMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb )
	#define LIBANDRIA4_SIZERESULT_EXPRMATCH( var, matcha, matchb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb )
	
		/* Convenience wrappers. See monads.h for more details. */
	#define LIBANDRIA4_SIZERESULT_RETURNSUCCESS( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( libandria4_sizeresult, size_t, val )
	#define LIBANDRIA4_SIZERESULT_RETURNFAILURE( val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( \
			libandria4_sizeresult, libandria4_failure_uipresult, val )
	
#endif
/* End libandria4 basic stdmonads.h */
