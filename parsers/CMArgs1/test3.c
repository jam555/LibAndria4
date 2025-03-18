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

#include "../../basic/pascalstring.h"

LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( test3_, int );

static struct
{
	test3_pascalarray arr;
	int libandria4_pascalarray_arrmember
		[
			sizeof( (int[]){ 0, 1, 2 } ) /
			sizeof( int )
		];
} a =
	{
		(test3_pascalarray)
		{
			sizeof( (int[]){ 0, 1, 2 } ) / sizeof( int )
		},
		{ 0, 1, 2 }
	};

test3_parrexrpres test3()
{
	test3_parrexrp ret = ( (test3_parrexrpt){ (&( a.arr )), (0), (1) } ) ;
	
	/*
	LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( head, type )
		typedef struct test3_pascalarray
		{
			size_t len;
			int body[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
			
		} test3_pascalarray;
		typedef test3_pascalarray test3_parr;
		
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
			test3_pascalarray_result,
			test3_pascalarray*,
			libandria4_failure_uipresult
		);
		typedef test3_pascalarray_result test3_parres;
		typedef test3_pascalarray_result test3_parrres;
		
		typedef struct test3_pascalarray_excerpt
		{
			test3_pascalarray *arr;
			size_t start, len;
			
		} test3_pascalarray_excerpt;
		typedef test3_pascalarray_excerpt test3_parrexrp;
		typedef test3_pascalarray_excerpt test3_parrexrpt;
		
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
			test3_pascalarray_excerpt_result,
			
			test3_pascalarray_excerpt,
			libandria4_failure_uipresult
		);
		typedef test3_pascalarray_excerpt_result test3_parrexrpres;
		typedef test3_pascalarray_excerpt_result test3_parrexrptres;
	*/
	test3_pascalarray_excerpt_result res;
	res.val.a = (test3_pascalarray_excerpt){ 0 };
	
	return
	(
		(
			(test3_pascalarray_excerpt_result)
			{
				{
					.a = ret
				},
				0
			}
		)
	);
}


