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

#include "commonlib.h"

	/* For uintptr_t. */
#include <stdint.h>

	/* For LIBANDRIA4_RESULT_FAILURE_DOMAIN. */
#include "commonerrvals.h"

	/* Works like C's strstr(), but with arbitrary memory patterns. */
	/* Note that the "needle" will only be searched for on needlegrain-sized */
	/*  alignments: this is to allow arbitrarily sized type searches to be */
	/*  performed. */
libandria4_ptrresult libandria4_memmem
(
	void *haystack_, size_t haysize,
	void *needle_, size_t needlesize, size_t needlegrain
)
{
	void *ret = haystack_;
	
	if( haystack_ && needle_ && haysize >= needlesize )
	{
		unsigned char *haystack = (char*)haystack_, *needle = (char*)needle_;
		size_t hoff = 0, noff = 0, goff = 0;
		
		if( needlesize % needlegrain )
		{
			LIBANDRIA4_PTRRESULT_RETURNFAILURE(
				LIBANDRIA4_RESULT_FAILURE_DOMAIN );
		}
		
		while( hoff + needlesize <= haysize )
		{
			while( noff < needlesize &&
				haystack[ hoff + noff + goff ] == needle[ noff + goff ] )
			{
				while( graintest < needlegrain &&
					haystack[ hoff + noff + goff ] == needle[ noff + goff ] )
				{
					++goff;
				}
				if( goff == needlegrain )
				{
					noff += needlegrain;
					goff = 0;
				}
			}
			if( noff == needlesize )
			{
				/* Success. */
				
				LIBANDRIA4_PTRRESULT_RETURNSUCCESS(
					(void*)&( haystack[ hoff ] ) );
			}
			
			hoff += needlegrain;
			noff = 0;
			goff = 0;
		}
		
		/* No match found, fall-through to null. */
	}
	
	LIBANDRIA4_PTRRESULT_RETURNFAILURE( LIBANDRIA4_RESULT_FAILURE_EOF );
}

	/* Reverses the order of the elements in the memory buffer. */
int memreverse( void *base_, size_t count, size_t size )
{
	if( base_ && count && size )
	{
		size_t elem = 0, eoff = 0;
		unsigned char tmp, *base = (char*)base_;
		
		while( ( elem * 2 ) + 1 < count )
		{
			while( eoff < size )
			{
				tmp = base[ ( elem * size ) + eoff ];
				base[ ( elem * size ) + eoff ] =
					base[ ( ( count - ( elem + 1 )) * size ) + eoff ];
				base[ ( ( count - ( elem + 1 )) * size ) + eoff ] = tmp;
				
				++eoff;
			}
			
			++elem;
			eoff = 0;
		}
		
		return( 1 );
	}
	
	return( 0 );
}
