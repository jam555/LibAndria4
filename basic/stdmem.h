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

#ifndef LIB4_STDMEM_H
# define LIB4_STDMEM_H
	
	#include <stdint.h>
	
	#include "stdmonads.h"
	
	lib4_ptrresult lib4_mallocwrapper( void *ign, size_t size );
	lib4_ptrresult lib4_reallocwrapper( void *ign,  void *cur, size_t size );
	lib4_result lib4_deallocwrapper( void *ign, void *mem );
	
	typedef struct lib4_memfuncs_t
	{
		void *data;
		
		lib4_ptrresult (*alloc)( void*, size_t );
		lib4_ptrresult (*realloc)( void*,  void* /*mem*/, size_t );
		lib4_result (*dealloc)( void*, void* /*mem*/ );
		
	} lib4_memfuncs_t;
	extern lib4_memfuncs_t lib4_stdmemfuncs;
	
	
	#define LIB4_MEMFUNCS_MEMMANARGS \
		void *data, \
		lib4_ptrresult (*alloc)( void*, size_t ), \
		lib4_ptrresult (*realloc_)( void*,  void*, size_t ), \
		lib4_result (*dealloc)( void*, void* )
	
	#define LIB4_MEMFUNCS_T_UNPACK( var ) \
		( var ).data, ( var ).alloc, ( var ).realloc, ( var ).dealloc
	
	#define LIB4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf_ptr ) \
		if( !( mf_ptr ) ) { ( mf_ptr ) = &lib4_stdmemfuncs; }
	
#endif
/* End lib4 stdmem.h */
