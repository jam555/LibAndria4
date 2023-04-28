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


	/* For size_t, though I think it's in stdlib.h and stdio.h as well. */
#include <stddef.h>
	/* For EXIT_SUCCESS and EXIT_FAILURE. */
#include <stdlib.h>
	/* For printf(). */
#include <stdio.h>
	/* For the standard "errno" variable. */
#include <errno.h>

#include "../basic/pascalarray.h"



#define STATIC_TEXT 'h', 'e', 'l', 'l', 'o', '\0'
#define CHANGED_TEXT 'W', 'e', 'l', 'l', 'o', '\0'
#define CHANGE_VALUE 'W'
#define CHANGE_INDEX 0
#define GROW_LEN 2
#define GROW_TEXT '!', '!', '\0'
#define GROW_INDEX 5
#define GROWN_TEXT 'h', 'e', 'l', 'l', 'o', '!', '!', '\0'
#define DELTA_LEN -1


LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( testchar_, char );

LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD( filescoped, inner, testchar_, char, STATIC_TEXT );

int visit_progress = 0;
void visit_checker( void *ref_, char *elem )
{
	char *ref = (char*)ref_;
	
	if( !ref )
	{
		printf( "   visit_checker() received a null void pointer!\n" );
		visit_progress = ( visit_progress ? -visit_progress : visit_progress ) - 1;
		return;
	}
	
	if( visit_progress < 0 )
	{
		visit_progress = -visit_progress;
		
		++visit_progress;
		
		if( *elem != ref[ visit_progress - 1 ] )
		{
			printf
			(
				"   Element mismatch at element %i\n",
					visit_progress - 1
			);
		}
		
		visit_progress = -visit_progress;
		
	} else {
		
		++visit_progress;
		
		if( *elem != ref[ visit_progress - 1 ] )
		{
			printf
			(
				"   Element mismatch at element %i\n",
					visit_progress - 1
			);
			visit_progress = - visit_progress;
		}
	}
	
}

int main( int argn, char *argc[] )
{
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD( functionscoped, inner, testchar_, char, STATIC_TEXT );
	
	testchar_pascalarray_result buildres;
	libandria4_result otherres;
	testchar_pascalarray *parr1;
	int ret = EXIT_SUCCESS, teststatus, errval = errno;
	size_t iter1, size1;
	
	
#define EARLYSUCC( ignore ) \
		printf( "   Initial success.\n" );
		
#define TRUESUCC( ignore ) \
		printf( "   True success.\n" );
#define TRUEFAIL( err ) \
		printf( "   True failure, code: %i.\n", (int)( err.val ) ); \
		teststatus = 0; \
		ret = EXIT_FAILURE;
	
#define BUILDSUCC( parrptr ) \
		printf( "   Build succeeded, allocated %p.\n", (void*)( parrptr ) ); \
		TRUESUCC( ignore ); \
		parr1 = ( parrptr );
#define BUILDFAIL( wrappederr ) \
		printf( \
			"   False failure, allocation failed. Skipping linked tests. Err val: %i\n", \
				(int)( ( wrappederr ).val ) ); \
		teststatus = 0; \
		if( wrappederr.val == LIBANDRIA4_RESULT_FAILURE_DOMAIN ) { \
			printf( "    Failure code matches LIBANDRIA4_RESULT_FAILURE_DOMAIN.\n" ); } \
		ret = EXIT_FAILURE;
	
	/* TODO: Improve the final error messaging at the end of this macro. */
#define TEST_CONTENT( parrref, reference, index, runstat ) \
		( runstat ) = 1; ( index ) = 0; \
		if( ( parrref ).len != ( sizeof( reference ) / sizeof( char ) ) ) { \
			( runstat ) = 0; printf( \
				"   Length failure: array len( %i ) != reference len( %i ).\n", \
				(int)( ( parrref ).len ), \
				(int)( sizeof( reference ) / sizeof( char ) ) ); } \
		while( \
			( index ) < ( parrref ).len && \
			( index ) < ( sizeof( reference ) / sizeof( char ) )  ) \
		{ if( ( reference )[ ( index ) ] != ( parrref ).body[ ( index ) ] ) { \
			( runstat ) = 0; printf( \
				"   Content failure at %i: expected \'%c\', found \'%c\'\n", \
					(int)( index ), \
					( reference )[ ( index ) ], ( parrref ).body[ ( index ) ] ); \
			TRUEFAIL( (libandria4_failure_uipresult){ 0 } ); \
			} ++( index ); } \
		if( ( index ) < ( parrref ).len ) { \
			( runstat ) = 0; printf( \
				"   Abortive failure: testing stopped at index %i of %i.\n", \
					(int)( index ), (int)( ( parrref ).len ) ); } \
		if( ( runstat ) == 1 ) { TRUESUCC( ignore ); } \
		else { TRUEFAIL( (libandria4_failure_uipresult){ 0 } ); }
	
	
	
	
	printf( "\nRunning LibAndria4 pascalarray.c test program with char as element type.\n" );
	printf( " Preliminary errno value: %i\n", errval );
	printf( " Static text: %s\n", ( (char[]){ STATIC_TEXT } ) );
	
	
	printf( "  Trying file-scoped static pascal array for contents & length.\n" );
	printf( "   File-scope text: %s\n", filescoped.inner.body );
	TEST_CONTENT( filescoped.inner, (char[]){ STATIC_TEXT }, iter1, teststatus );
	
	printf( "  Trying function-scoped static pascal array for contents & length.\n" );
	printf( "   Function-scope text: %s\n", functionscoped.inner.body );
	TEST_CONTENT( functionscoped.inner, (char[]){ STATIC_TEXT }, iter1, teststatus );
	
	
	printf( "  Trying modified file-scoped static pascal array for contents & length.\n" );
	printf
	(
		"   Modifying index %i ( \'%c\' ) to \'%c\'\n ",
			(int)CHANGE_INDEX,
			(char)( filescoped.inner.body[ CHANGE_INDEX ] ),
			(char)CHANGE_VALUE
	);
	printf( "   Pre-change file-scope text: %s\n", filescoped.inner.body );
	filescoped.inner.body[ CHANGE_INDEX ] = CHANGE_VALUE;
	printf( "   Post-change file-scope text: %s\n", filescoped.inner.body );
	TEST_CONTENT( filescoped.inner, (char[]){ CHANGED_TEXT }, iter1, teststatus );
	
	printf( "  Trying modified function-scoped static pascal array for contents & length.\n" );
	printf
	(
		"   Modifying index %i ( \'%c\' ) to \'%c\'\n ",
			(int)CHANGE_INDEX,
			(char)( functionscoped.inner.body[ CHANGE_INDEX ] ),
			(char)CHANGE_VALUE
	);
	printf( "   Pre-change function-scope text: %s\n", functionscoped.inner.body );
	functionscoped.inner.body[ CHANGE_INDEX ] = CHANGE_VALUE;
	printf( "   Post-change function-scope text: %s\n", functionscoped.inner.body );
	TEST_CONTENT( functionscoped.inner, (char[]){ CHANGED_TEXT }, iter1, teststatus );
	
	
	teststatus = 1;
	size1 = sizeof( (char[]){ STATIC_TEXT } ) / sizeof( char );
	printf( "  Trying dynamic allocation of pascal array, intended size == %i.\n", (int)size1 );
	buildres = testchar_pascalarray_build( size1 );
	LIBANDRIA4_MONAD_EITHER_BODYMATCH( buildres, BUILDSUCC, BUILDFAIL );
	if( teststatus )
	{
		if( !parr1 )
		{
			printf( "   Critical error, newly built pascal array is a null pointer!\n" );
			printf
			(
				"    errno value: %i; ret==failure? %i; teststatus==failure? %i\n",
					(int)( errno ),
					(int)( ret == EXIT_FAILURE ? 1 : 0 ),
					(int)( teststatus == 0 ? 1 : 0 )
			);
			exit( EXIT_FAILURE );
		}
		if( parr1->len != sizeof( (char[]){ STATIC_TEXT } ) / sizeof( char ) )
		{
			printf
			(
				"   Length failure: array len( %i ) != reference len( %i ).\n",
					(int)( parr1->len ),
					(int)( sizeof( (char[]){ STATIC_TEXT } ) / sizeof( char ) )
			);
			TRUEFAIL( (libandria4_failure_uipresult){ 0 } )
			
		} else {
			
			printf
			(
				"   Length success: array len( %i ) = reference length.\n",
					(int)( parr1->len )
			);
			
			
			printf( "  Trying to fill allocated array.\n" );
			otherres = testchar_pascalarray_fill( parr1, (char[]){ STATIC_TEXT } );
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( otherres, EARLYSUCC, TRUEFAIL );
			if( teststatus )
			{
				TEST_CONTENT( *parr1, (char[]){ STATIC_TEXT }, iter1, teststatus );
			}
		}
		
		
		if( teststatus )
		{
			printf
			(
				"  Trying to reallocate array from %i to %i elements.\n",
					(int)( parr1->len ),
					(int)( parr1->len + GROW_LEN )
			);
			buildres = testchar_pascalarray_rebuild( parr1, parr1->len + GROW_LEN );
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( buildres, BUILDSUCC, BUILDFAIL );
			if( !parr1 )
			{
				printf( "   Critical error, reallocated pascal array is a null pointer!\n" );
				printf
				(
					"    errno value: %i; ret==failure? %i; teststatus==failure? %i\n",
						(int)( errno ),
						(int)( ret == EXIT_FAILURE ? 1 : 0 ),
						(int)( teststatus == 0 ? 1 : 0 )
				);
				exit( EXIT_FAILURE );
			}
			
			if( teststatus && parr1 )
			{
				printf( "  Trying to refill grown array.\n" );
				
				iter1 = 0;
				while( iter1 < GROW_LEN )
				{
					parr1->body[ GROW_INDEX + iter1 ] =
						( (char[]){ GROW_TEXT } )[ iter1 ];
					++iter1;
				}
					/* We've overwritten the old null, but not yet replaced it. */
				parr1->body[ GROW_INDEX + iter1 ] =
					( (char[]){ GROWN_TEXT } )[ GROW_INDEX + iter1 ];
				
				TEST_CONTENT( *parr1, (char[]){ GROWN_TEXT }, iter1, teststatus );
			}
		}
		
		
		{
			printf( "  Trying to visit all array elements.\n" );
			
			visit_progress = 0;
			testchar_pascalarray_visit( parr1, (void*)( (char[]){ GROWN_TEXT } ), &visit_checker );
			
			if( visit_progress < 0 )
			{
				TRUEFAIL( (libandria4_failure_uipresult){ -visit_progress } );
				
			} else {
				
				TRUESUCC( ignore );
			}
		}
		
		
		if( parr1 )
		{
			printf( "  Trying to reinit array to a different size.\n" );
			iter1 = parr1->len + DELTA_LEN;
			printf
			(
				"   Old size: %i; Planned size: %i\n",
					(int)( parr1->len ),
					(int)( iter1 )
			);
			
			errval = testchar_pascalarray_init( parr1, iter1 );
			switch( errval )
			{
				case 1:
					printf( "   init() claims success.\n" );
					break;
				case -1:
					printf( "   init() claims null pointer: %p\n", (void*)parr1 );
					teststatus = 0;
					break;
				default:
					printf
					(
						"   init() provided unexpected value: %i; array ptr: %p\n",
							(int)errval,
							(void*)parr1
					);
					teststatus = 0;
					break;
			}
			
			printf( "   resulting length: %i\n", (int)( parr1->len ) );
			if( parr1->len != iter1 )
			{
				TRUEFAIL( (libandria4_failure_uipresult){ 0 } );
			}
		}
		
		
		if( parr1 )
		{
			printf( "  Trying to delete allocated array.\n" );
			otherres = testchar_pascalarray_destroy( parr1 );
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( otherres, TRUESUCC, TRUEFAIL );
			parr1 = (testchar_pascalarray*)0;
		}
	}
	
	
	printf( "  Trying buildNfill() allocation of pascal array.\n" );
	teststatus = 1;
	buildres =
		testchar_pascalarray_buildNfill
		(
			sizeof( (char[]){ STATIC_TEXT } ) / sizeof( char ),
			(char[]){ STATIC_TEXT }
		);
	LIBANDRIA4_MONAD_EITHER_BODYMATCH( buildres, BUILDSUCC, BUILDFAIL );
	if( teststatus )
	{
		if( !parr1 )
		{
			printf( "   Critical error, buildNfill() pascal array is a null pointer!\n" );
			printf
			(
				"    errno value: %i; ret==failure? %i; teststatus==failure? %i\n",
					(int)( errno ),
					(int)( ret == EXIT_FAILURE ? 1 : 0 ),
					(int)( teststatus == 0 ? 1 : 0 )
			);
			exit( EXIT_FAILURE );
		}
		if( parr1->len != sizeof( (char[]){ STATIC_TEXT } ) / sizeof( char ) )
		{
			printf
			(
				"   Length failure: array len( %i ) != reference len( %i ).\n",
					(int)( parr1->len ),
					(int)( sizeof( (char[]){ STATIC_TEXT } ) / sizeof( char ) )
			);
			TRUEFAIL( (libandria4_failure_uipresult){ 0 } )
			
		} else {
			
			printf
			(
				"   Length success: array len( %i ) = reference length.\n",
					(int)( parr1->len )
			);
			
			printf( "  Checking contents of buildNfill() array.\n" );
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( otherres, EARLYSUCC, TRUEFAIL );
			if( teststatus )
			{
				TEST_CONTENT( *parr1, (char[]){ STATIC_TEXT }, iter1, teststatus );
			}
		}
		
		
		if( parr1 )
		{
			printf( "  Trying to delete buildNfill() array.\n" );
			otherres = testchar_pascalarray_destroy( parr1 );
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( otherres, TRUESUCC, TRUEFAIL );
			parr1 = (testchar_pascalarray*)0;
		}
	}
	
	
	
	
	if( ret == EXIT_SUCCESS )
	{
		printf( " Testing was successful.\n" );
		
	} else {
		
		printf( " Testing was unsuccessful.\n" );
	}
	return( ret );
}
