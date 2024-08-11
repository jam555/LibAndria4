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

#ifndef LIBANDRIA4_BASIC_BINTREES_BARETREES_H
# define LIBANDRIA4_BASIC_BINTREES_BARETREES_H
	
	#include "bintrees.h"
	
		/* I don't know if this is the best algorithm, and perhaps it doesn't */
		/*  even work RIGHT, but it's my current version. Partially because */
		/*  the results I've found when looking up the algorithm seem to be */
		/*  AVL trees instead of vanilla binary trees. */
		/* Note that this isn't C, or even C++: it's pseudo-code. */
	bitup< size_t, nodetype* > Hbal( nodetype *n )
	{
		if( !n )
		{
			return( bitup::left( 1 ) );
		}
		
		size_t a, b;
		nodetype *c = 0, *d = 0;
		
		{ a, c } = Hbal( n->left );
		{ b, d } = Hbal( n->right );
		
		while( a + 1 < b || a > b + 1 || c || d )
		{
			if( c )
			{
				n->left = c;
				c = 0;
				{ a, c } = Hbal( n->left );
				
			} else if( d )
			{
				n->right = d;
				d = 0;
				{ b, d } = Hbal( n->right );
				
			} else if( a + 1 < b )
			{
				return( bitup::both( b - 1, rotleft( n ) ) );
				
			} else {
				return( bitup::both( a - 1, rotleft( n ) ) );
				
			}
		}
		
		return( bitup::left( a > b ? a : b ) );
	}
	
#endif
/* End libandria4 basic bintrees baretrees.h */
