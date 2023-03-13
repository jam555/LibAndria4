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

#include <stdlib.h>
#include <errno.h>


#include "stdmem.h"
#include "macrotime/simpleops.h"


lib4_ptrresult lib4_mallocwrapper( void *ign, size_t size )
{
	int errmem = errno;
	errno = 0;
	
	void *mem = malloc( size );
	lib4_result e = lib4_errno_2result();
	
	lib4_ptrresult ret;
#define lib4_mallocwrapper_SUCCESS( val ) \
		ret = LIB4_PTRRESULT_BUILDSUCCESS( mem );
#define lib4_mallocwrapper_FAILURE( val ) \
		ret = LIB4_PTRRESULT_BUILDFAILURE( val );
	LIB4_RESULT_BODYMATCH(
		e,
		
		lib4_mallocwrapper_SUCCESS,
		lib4_mallocwrapper_FAILURE
	);
	
	errno = errmem;
	return( ret );
}
lib4_ptrresult lib4_reallocwrapper( void *ign,  void *cur, size_t size )
{
	int errmem = errno;
	errno = 0;
	
	void *mem = realloc( cur, size );
	lib4_result e = lib4_errno_2result();
	
	lib4_ptrresult ret;
#define lib4_reallocwrapper_SUCCESS( val ) \
		ret = LIB4_PTRRESULT_BUILDSUCCESS( mem );
#define lib4_reallocwrapper_FAILURE( val ) \
		ret = LIB4_PTRRESULT_BUILDFAILURE( val );
	LIB4_RESULT_BODYMATCH(
		e,
		
		lib4_reallocwrapper_SUCCESS,
		lib4_reallocwrapper_FAILURE
	);
	
	errno = errmem;
	return( ret );
}
lib4_result lib4_deallocwrapper( void *ign, void *mem )
{
	int errmem = errno;
	errno = 0;
	
	free( mem );
	lib4_result ret = lib4_errno_2result()
	
	errno = errmem;
	
	return( ret );
}



lib4_memfuncs_t lib4_stdmemfuncs =
#if 1
	{
		(void*)0,
		
		&lib4_mallocwrapper,
		&lib4_reallocwrapper,
		&lib4_deallocwrapper
	};
#else
	#error "stdmem.c : invalid stdmemfuncs override."
#endif
