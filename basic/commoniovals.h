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

	/* This won't result in an infinit inclusion loop, because all of the */
	/*  includes in commonio.h are wrapped by it's include-guard and thus */
	/*  will only be included once. */
#include "commonio.h"

#ifndef LIBANDRIA4_BASIC_COMMONIOVALS_H
# define LIBANDRIA4_BASIC_COMMONIOVALS_H
	
	#define LIBANDRIA4_COMMONIOVALS_SUCCESS ( (libandria4_commonio_perr)0 )
		/* This was previously 0, because EOF isn't always an error and */
		/*  error * 0 OBVIOUSLY is no error at all, but it became ever */
		/*  more clear that I REALLY DO want a distinct "success" value, */
		/*  so EOF had to make way. Note though that it still doesn't */
		/*  have *_ERR_* in it's name. */
	#define LIBANDRIA4_COMMONIOVALS_EOF ( LIBANDRIA4_RESULT_FAILURE_EOF )
	const libandria4_commonio_perr libandria4_commoniovals_eof =
		LIBANDRIA4_COMMONIOVALS_EOF;
	const libandria4_commonio_mayerr libandria4_commoniovals_justeof =
		LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_COMMONIOVALS_EOF );
	const libandria4_commonio_mayerr2 libandria4_commoniovals_justeof2 =
		LIBANDRIA4_COMMONIO_MAYERR2_BUILDJUST( LIBANDRIA4_COMMONIOVALS_EOF );
	
		/* EIO, generic I/O error. Was LIBANDRIA4_COMMONIOVALS_ERR_IO. Usually hardware related. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_GENERIC ( LIBANDRIA4_RESULT_FAILURE_IOERROR )
	
		/* One or more arguments had an "illegal" value for the function. e.g. EINVAL */
	#define LIBANDRIA4_COMMONIOVALS_ERR_BADARGS ( LIBANDRIA4_RESULT_FAILURE_DOMAIN )
		/* The correct return is impossible to actually provide. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_UNRETURNABLE ( LIBANDRIA4_RESULT_FAILURE_RANGE )
		/* A illegal sequence was encountered, usually in multi-byte encodings. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_ILSEQ ( LIBANDRIA4_RESULT_FAILURE_ILSEQ )
		/* No error value has been allocated, so it's getting rolled into */
		/*  this one. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_UNDIFFERENTIATED ( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED )
		/* A back-end system hasn't been initialized. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_NOTINITIALIZED ( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED )
	#define LIBANDRIA4_COMMONIOVALS_ERR_GENERICMISMATCH ( LIBANDRIA4_RESULT_FAILURE_GENERICMISMATCH )
		/* e.g. EMSGSIZE, You tried to specifically use an argument that in */
		/*  some way was the wrong size. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_SIZEMISMATCH ( LIBANDRIA4_RESULT_FAILURE_SIZEMISMATCH )
	#define LIBANDRIA4_COMMONIOVALS_ERR_TYPEMISMATCH ( LIBANDRIA4_RESULT_FAILURE_TYPEMISMATCH )
		/* e.g. EROFS (read-only filesys), ENOSYS, ENOTTY */
	#define LIBANDRIA4_COMMONIOVALS_ERR_MODEMISMATCH ( LIBANDRIA4_RESULT_FAILURE_MODEMISMATCH )
		/* Array stuff. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_BELOWBOUNDS ( LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS )
	#define LIBANDRIA4_COMMONIOVALS_ERR_ABOVEBOUNDS ( LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS )
	
	
	/* Note that LIBANDRIA4_RESULT_FAILURE_EOF is intentionally not here: */
	/*  it's meant only for cases where 0 CANNOT be EOF. */
	
	
	#define LIBANDRIA4_COMMONIOVALS_ERR_SEGFAULT ( LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS )
		/* This is for stuff like 1 + 1 == 3, and other such madness. Most */
		/*  likely a hardware failure or uncaught integer over/underflow. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_LOGICFAULT ( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT )
	
		/* ENOMEM, there's not enough memory available. Often this refers */
		/*  specifically to virtual memory, but can mean any memory type. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_MEMORYFULL ( LIBANDRIA4_RESULT_FAILURE_MEMORYFULL )
		/* ENOSPC, EDQUOT, EFBIG, ENOBUFS, ENOSR, etc. You've run out */
		/*  of some limited-amount resource. Never DIRECTLY means memory. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_RATIONFULL1 ( LIBANDRIA4_RESULT_FAILURE_RATIONFULL1 )
	
		/* ENOTSOCK, ENOSTR, ENOTSUP, EOPNOTSUPP, ENOTDIR, EISDIR, */
		/*  ESPIPE, etc. Note that "broken pipe" is actually EPIPE, not */
		/*  ESPIPE. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_INVALIDOPER ( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER )
	
		/*  The I/O handle isn't connected to anything. The reason for */
		/*  the disconnection... well, who knows. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_NOTCONN ( LIBANDRIA4_RESULT_FAILURE_NOTCONN )
		/* EDESTADDRREQ ; You e.g. need to bind() the socket before */
		/*  using it. More specific version of *_NOTCONN */
	#define LIBANDRIA4_COMMONIOVALS_ERR_PARTCONN ( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN )
	
		/* e.g. "Broken handle, close it.", ENETDOWN, ENETRESET, ENOLINK, EIDRM, EPROTO */
	#define LIBANDRIA4_COMMONIOVALS_ERR_BROKEN ( LIBANDRIA4_RESULT_FAILURE_BROKEN )
		/* ETIME, ETIMEDOUT ; A more-specific *_BROKEN */
	#define LIBANDRIA4_COMMONIOVALS_ERR_TIMEOUT ( LIBANDRIA4_RESULT_FAILURE_TIMEOUT )
		/* e.g. "This process is broken, exit it." */
	#define LIBANDRIA4_COMMONIOVALS_ERR_KILLING ( LIBANDRIA4_RESULT_FAILURE_KILLING )
	
		/* e.g. EBADMSG */
	#define LIBANDRIA4_COMMONIOVALS_ERR_CORRUPTED ( LIBANDRIA4_RESULT_FAILURE_CORRUPTED )
		/* e.g. ENOMSG, ENODATA, ENOATTR ; SPECIFIC data not available. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_NARROWEOF ( LIBANDRIA4_RESULT_FAILURE_NARROWEOF )
		/* EOVERFLOW, ENAMETOOLONG ; Data value too large for destination */
		/*  field (e.g. 64-bit time into 32-bit time). Note: never means */
		/*  the same as *_SIZEMISMATCH, intended for formatted I/O. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_OVERFLOW ( LIBANDRIA4_RESULT_FAILURE_OVERFLOW )
	
		/* EDEADLK, ENOLOCK, ETXTBSY: A resource is bound incompatibily */
		/*  with the operation, resolve and try again. In the case of */
		/*  ETXTBSY for example, you're trying to open a file for writing */
		/*  that's currently read-only for execution. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_WOULDCLOG ( LIBANDRIA4_RESULT_FAILURE_WOULDCLOG )
		/* EWOULDBLOCK, EBUSY, EAGAIN, EINTR, ERESTART: A non-blocking */
		/*  resource/action would be forced to block/wait, try again. */
		/*  It's usually best to wait a few seconds before the next */
		/*  attempt. */
	#define LIBANDRIA4_COMMONIOVALS_ERR_WOULDBLOCK ( LIBANDRIA4_RESULT_FAILURE_WOULDBLOCK )
		/* EINPROGRESS, EALREADY: An alternative to *_WOULDBLOCK for */
		/*  innately-blocking things like "connect". */
	#define LIBANDRIA4_COMMONIOVALS_ERR_ONGOING ( LIBANDRIA4_RESULT_FAILURE_ONGOING )
		/* ECANCELED, ECONNABORTED */
	#define LIBANDRIA4_COMMONIOVALS_ERR_STOPPED ( LIBANDRIA4_RESULT_FAILURE_STOPPED )
	
#endif
/* End libandria4 basic commoniovals.h */
