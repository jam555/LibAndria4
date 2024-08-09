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
	/* TODO: There's a function elsewhere that converts from errno to these: */
	/*  update it. */
	
	
	
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
	
	/* Note that these values may be used for completely different */
	/*  meanings in some circumstances. For example, 0 was for a short */
	/*  time used as EOF, and afterwards in those same cases used as "no */
	/*  message". */
	#define LIBANDRIA4_RESULT_GENERICFALSE ( 0 )
	#define LIBANDRIA4_RESULT_GENERICTRUE ( 1 )
	#define LIBANDRIA4_RESULT_GENERIC ( 2 )
	
		/* The domain of a mathematical function is the full set of it's */
		/*  legal inputs. So if you get a domain error, you fed it wrong. */
		/*  Probably not by feeding it after midnight though. e.g. EINVAL */
	#define LIBANDRIA4_RESULT_FAILURE_DOMAIN ( 3 )
		/* Meanwhile, the RANGE is the valid OUTPUTS of a mathematical */
		/*  function. If you get this error, think of it as an overflow */
		/*  error. */
	#define LIBANDRIA4_RESULT_FAILURE_RANGE ( 4 )
		/* EILSEQ */
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
		/* e.g. E2BIG, EMSGSIZE, alternative to */
		/*  LIBANDRIA4_RESULT_FAILURE_MEMORYFULL when SMALLER blocks are */
		/*  available. You tried to specifically use an argument that in */
		/*  some way was the wrong size. */
	#define LIBANDRIA4_RESULT_FAILURE_SIZEMISMATCH ( 9 )
	#define LIBANDRIA4_RESULT_FAILURE_TYPEMISMATCH ( 10 )
		/* e.g. EROFS (read-only filesys), ENOSYS, ENOTTY */
	#define LIBANDRIA4_RESULT_FAILURE_MODEMISMATCH ( 11 )
		/* Array stuff. */
	#define LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS ( 12 )
	#define LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS ( 13 )
		/* File & directory stuff, but never used directly by those */
		/*  functions in LibAndria. Instead, this is only produced by */
		/*  more generic functions that interact with standard-library's */
		/*  "errno" system, as LibAndria's EOF is 0, but errno treats 0 */
		/*  as "no message". */
		/* Except that has changed, this IS now the LibAndria EOF. */
	#define LIBANDRIA4_RESULT_FAILURE_EOF ( 14 )
	
		/* EFAULT: Note that this indicates a segfault. */
	#define LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ( 15 )
	
		/* This is for stuff like 1 + 1 == 3, and other such madness. Most */
		/*  likely a hardware failure or uncaught integer over/underflow. */
	#define LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ( 16 )
	
	
	
	/* Note: These aren't yet handled by any errno-repackaging functions. */
	
		/* ENOMEM, there's not enough memory available. Often this refers */
		/*  specifically to virtual memory, but can mean any memory type. */
	#define LIBANDRIA4_RESULT_FAILURE_MEMORYFULL ( 17 )
		/* ENOSPC, EDQUOT, EFBIG, ENOBUFS, ENOSR, etc. You've run out */
		/*  of some limited-amount resource. Never DIRECTLY means memory. */
	#define LIBANDRIA4_RESULT_FAILURE_RATIONFULL1 ( 18 )
	
		/* ENOTSOCK, ENOSTR, ENOTSUP, EOPNOTSUPP, ENOTDIR, EISDIR, */
		/*  ESPIPE, etc. Note that "broken pipe" is actually EPIPE, not */
		/*  ESPIPE. */
	#define LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ( 19 )
		/* EIO. Usually hardware related. */
	#define LIBANDRIA4_RESULT_FAILURE_IOERROR ( 20 )
	
		/* ENOTCONN, EBADF, EPIPE, ESTALE, ECONNRESET, EOWNERDEAD, etc: */
		/*  The I/O handle isn't connected to anything. The reason for */
		/*  the disconnection... well, who knows. */
	#define LIBANDRIA4_RESULT_FAILURE_NOTCONN ( 21 )
		/* EDESTADDRREQ ; You e.g. need to bind() the socket before */
		/*  using it. More specific version of *_NOTCONN */
	#define LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ( 22 )
	
		/* e.g. "Broken handle, close it.", ENETDOWN, ENETRESET, ENOLINK, EIDRM, EPROTO */
	#define LIBANDRIA4_RESULT_FAILURE_BROKEN ( 23 )
		/* ETIME, ETIMEDOUT ; A more-specific *_BROKEN */
	#define LIBANDRIA4_RESULT_FAILURE_TIMEOUT ( 24 )
		/* e.g. "This process is broken, exit it." */
	#define LIBANDRIA4_RESULT_FAILURE_KILLING ( 25 )
	
		/* e.g. EBADMSG */
	#define LIBANDRIA4_RESULT_FAILURE_CORRUPTED ( 26 )
		/* e.g. ENOMSG, ENODATA, ENOATTR ; SPECIFIC data not available. */
	#define LIBANDRIA4_RESULT_FAILURE_NARROWEOF ( 27 )
		/* EOVERFLOW, ENAMETOOLONG ; Data value too large for destination */
		/*  field (e.g. 64-bit time into 32-bit time). Note: never means */
		/*  the same as *_SIZEMISMATCH */
	#define LIBANDRIA4_RESULT_FAILURE_OVERFLOW ( 28 )
	
		/* EDEADLK, ENOLOCK, ETXTBSY: A resource is bound incompatibily */
		/*  with the operation, resolve and try again. In the case of */
		/*  ETXTBSY for example, you're trying to open a file for writing */
		/*  that's currently read-only for execution. */
	#define LIBANDRIA4_RESULT_FAILURE_WOULDCLOG ( 29 )
		/* EWOULDBLOCK, EBUSY, EAGAIN, EINTR, ERESTART: A non-blocking */
		/*  resource/action would be forced to block/wait, try again. */
		/*  It's usually best to wait a few seconds before the next */
		/*  attempt. */
	#define LIBANDRIA4_RESULT_FAILURE_WOULDBLOCK ( 30 )
		/* EINPROGRESS, EALREADY: An alternative to *_WOULDBLOCK for */
		/*  innately-blocking things like "connect". */
	#define LIBANDRIA4_RESULT_FAILURE_ONGOING ( 31 )
		/* ECANCELED, ECONNABORTED */
	#define LIBANDRIA4_RESULT_FAILURE_STOPPED ( 32 )
	
	
	#if 0
		/* Note: renumber these. */
	
			/* ELOOP, EXDEV, etc., too many levels of travel. */
		#define LIBANDRIA4_RESULT_FAILURE_TOODEEP ( 20 )
			/* EACCES, EPERM, ECONNREFUSED */
		#define LIBANDRIA4_RESULT_FAILURE_PERMSDENIED ( 25 )
			/* EEXIST, EADDRNOTAVAIL, EADDRINUSE, ENOTEMPTY, EISCONN */
		#define LIBANDRIA4_RESULT_FAILURE_EXISTS ( 6 )
			/* ENOENT, EAFNOSUPPORT, EPROTONOSUPPORT, EPROTOTYPE, ENOPROTOOPT, ENODEV, ENXIO, ESRCH, ECHILD, ENETUNREACH, EHOSTUNREACH */
		#define LIBANDRIA4_RESULT_FAILURE_NOENTRY ( 11 )
			/* EMFILE, too many open in PROCESS specifically. */
		#define LIBANDRIA4_RESULT_FAILURE_RATIONFULL2 ( 15 )
			/* ENFILE, too many open in SYSTEM specifically. */
		#define LIBANDRIA4_RESULT_FAILURE_RATIONFULL3 ( 16 )
			/* e.g. directly executing a library; ENOEXEC, ELIBEXEC */
		#define LIBANDRIA4_RESULT_FAILURE_WRONGFORMAT ( 30 )
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
