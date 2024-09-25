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

#ifndef LIBANDRIA4_MATH_HEAPSALGO_H
# define LIBANDRIA4_MATH_HEAPSALGO_H
	/*
		Heap's algorithm
			An algorithm to produce every permutation of an array.
			First proposed by B. R. Heap in 1963.
			This algorithm was added to LibAndria to support testing of
				Red-Black tree algorithms, by producing every possible
				ordering of the choosen elements to try to detect defects
				by "brute force" checking of possibilities.
			Produces every possible rearrangement of the elements in the
				provided array. Note that the iterations will circle back
				around if this is called first.
			Use LIBANDRIA4_HEAPSPERMUTATOR_DECLARE() in e.g. headers.
			Use LIBANDRIA4_HEAPSPERMUTATOR_BUILDINNER() in implementation
				files, followed by LIBANDRIA4_HEAPSPERMUTATOR_BUILD(). If
				you want to inline any piece, then you can just use the
				"inline" keyword immediately before the *_BUILD*() macro's
				use.
			
	*/
	
	#define LIBANDRIA4_HEAPSPERMUTATOR_BUILDINNER( head, arrtype ) \
		int ( head ## _inner )( \
			size_t k,  size_t argn, (arrtype) *argv, \
			void *data, void (*viewer)( void*,  size_t, (arrtype)* ) ) { \
				if( argn < 2 ) { return( 0 ); } \
				\
				if( argn && argv && viewer ) { \
					if( k == 1 ) { viewer( data,  argn, argv ); } \
					else { \
						if( ( head ## _inner )( k - 1, argn, argv, data, viewer ) < 0 ) { \
							return( -2 ); } \
						\
						size_t i = 0; (arrtype) swap; \
						while( i < k - 1 ) { \
							if( !( k % 2 ) ) { \
								swap = argc[ i ]; argc[ i ] = argc[ k - 1 ]; argc[ k - 1 ] = swap; } \
							else { \
								swap = argc[ 0 ]; argc[ 0 ] = argc[ k - 1 ]; argc[ k - 1 ] = swap; } \
							\
							if( ( head ## _inner )( k - 1, argn, argv, data, viewer ) < 0 ) { \
								return( -2 ); } \
							\
							i += 1; } } \
					return( 1 ); } \
				return( -1 ); }
	#define LIBANDRIA4_HEAPSPERMUTATOR_BUILD( head, arrtype ) \
		int ( head )( size_t argn, arrtype *argv, \
			void *data, void (*viewer)( void*,  size_t, arrtype* ) ) { \
				return( ( head ## _inner )( argn,  argn, argv,  data, viewer ) ); }
	#define LIBANDRIA4_HEAPSPERMUTATOR_DECLARE( head, arrtype ) \
		int ( head )( size_t argn, arrtype *argv, \
			void *data, void (*viewer)( void*,  size_t, arrtype* ) );
#endif
/* End lib4 math heapsalgo.h */
