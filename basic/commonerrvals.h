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

#ifndef LIBANDRIA4_BASIC_COMMONERRVALS_H
# define LIBANDRIA4_BASIC_COMMONERRVALS_H
	
	
	/* These defines were pulled out of stdmonads.h, and does have at least */
	/*  one reference back to that file (look for the reference to C++ and */
	/*  POSIX). */
	
	
	
	#define LIBANDRIA4_STDERRS_BADARGS_SIMPLE ( -1 )
	#define LIBANDRIA4_STDERRS_BADARGS_COMPLEX ( -2 )
	#define LIBANDRIA4_STDERRS_BADARGS_DEEP ( -3 )
	
		/* The number of this error will need to be increased as new ones */
		/*  are added: in particular, this must ALWAYS be the lowest */
		/*  numbered error in the *_STDERRS_* group. */
	#define LIBANDRIA4_STDERRS__LAST_UNALLOC_ERR ( -4 )
	
	
	
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
	
		/* EFAULT: Note that this indicates a segfault. */
	#define LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ( 15 )
	
		/* This is for stuff like 1 + 1 == 3, and other such madness. Most */
		/*  likely a hardware failure or uncaught integer over/underflow. */
	#define LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ( 16 )
	
	
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
	
	
	
		/* As a special case, 0 always means general success or general */
		/*  failure, since it can't POSSIBLY point to something that's */
		/*  reliably legally placed, and success or error is indicated by */
		/*  type instead of value. */
	#define LIBANDRIA4_UIPRESULT_GENERIC ( 0 )
	
	
	
#endif
/* End libandria4 basic commonerrvals.h */
