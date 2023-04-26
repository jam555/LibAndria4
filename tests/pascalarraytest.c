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


LIBANDRIA4_DEFINE_PASCALARRAY_STDDEFINE( testchar_, char );

LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD( filescoped, inner, testchar_, char, STATIC_TEXT );

int main( int argn, char *argc[] )
{
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD( functionscoped, inner, testchar_, char, STATIC_TEXT );
	
	int ret = EXIT_SUCCESS;
	
#define TRUESUCC( ignore ) \
		printf( "   True success.\n" );
#define TRUEFAIL( ignore ) \
		printf( "   True failure.\n" ); \
		ret = EXIT_FAILURE;
	
	
	
	int errval = errno;
	size_t iter1;
	
	printf( "\nRunning LibAndria4 pascalarray.c test program with char as element type.\n" );
	printf( " Preliminary errno value: %i\n", errval );
	
	
#define TEST_CONTENT( parrref, reference, index, runstat ) \
		( runstat ) = 1; ( index ) = 0; \
		if( parrref.len != ( sizeof( reference ) / sizeof( char ) ) ) { \
			( runstat ) = 0; printf( \
				"   Length failure: array len( %i ) != reference len( %i ).\n", \
				(int)( parrref.len ), \
				(int)( sizeof( reference ) / sizeof( char ) ) ); } \
		while( \
			( index ) < parrref.len && \
			( index ) < ( sizeof( reference ) / sizeof( char ) ) && \
			parrref.body[ ( index ) ] != '\0' ) \
		{ if( ( reference )[ ( index ) ] != parrref.body[ ( index ) ] ) { \
			( runstat ) = 0; printf( \
				"   Content failure at %i: expected \'%c\', found '\%c'\.\n", \
					(int)( index ), \
					( reference )[ ( index ) ], parrref.body[ ( index ) ] ); \
			TRUEFAIL( ignore ); \
		} ++( index ); } \
		if( ( index ) < parrref.len ) { \
			( runstat ) = 0; printf( \
				"   Abortive failure: testing stopped at index %i of %i.\n", \
					(int)( index ), (int)( parrref.len ) ); } \
		if( ( runstat ) == 1 ) { TRUESUCC( ignore ); } else { TRUEFAIL( ignore ); }
	
	
	printf( "  Trying file-scoped static pascal array for contents & length.\n", desiredname );
	iter1 = 0;
	while
	(
		iter1 < filescoped.inner.len &&
		iter1 < ( sizeof( (char[]){ STATIC_TEXT } ) / sizeof( char ) ) &&
		filescoped.inner.body[ iter ] != '\0'
	)
	{
		if( ( (char[]){ STATIC_TEXT } )[ iter1 ] != filescoped.inner.body[ iter ] )
		{
			printf
			(
				"   Content failure at %i: expected \'%c\', found '\%c'\.\n",
					(int)iter1,
					( (char[]){ STATIC_TEXT } )[ iter1 ],
					filescoped.inner.body[ iter ]
			);
			TRUEFAIL( ignore );
		}
		
		++iter1;
	}
	
	
	
	
	
	
	
	
	typedef struct testchar_pascalarray
	{
		size_t len;
		char body[ LIBANDRIA4_FLEXARRAY_FILLERLENGTH ];
		
	} testchar_pascalarray;
	LIBANDRIA4_MONAD_EITHER_BUILDTYPE(
		
		testchar_pascalarray_result,
		
		testchar_pascalarray*,
		libandria4_failure_uipresult
	)
	
		/* 1 on succ, -1 on fail. */
	int testchar_pascalarray_init( testchar_pascalarray *parr, size_t len );
	
		/* Note: len gets stored UNALTERED into the pascal array. If you use */
		/*  it as an index directly, then it will point you past the legal */
		/*  end of the array. */
	testchar_pascalarray_result testchar_pascalarray_build( size_t len );
		/* This also stores newlen directly into the array. */
		/* Responds to a newlen of 0 with LIB4_RESULT_FAILURE_DOMAIN. */
	testchar_pascalarray_result testchar_pascalarray_rebuild( testchar_pascalarray *parr, size_t newlen );
	libandria4_result testchar_pascalarray_destroy( testchar_pascalarray *parr );
	
	libandria4_result testchar_pascalarray_fill( testchar_pascalarray *parr, char *src );
	testchar_pascalarray_result testchar_pascalarray_buildNfill( size_t len, char *src );
	void testchar_pascalarray_visit( testchar_pascalarray *parr, void *data, void (*visitor)( void*, char* ) )
	
	
	
	
	
	
	
	
	
	
	
	
	libandria4_result res;
	int tmp;
	char *desiredname;
	
#define ONSUCC( sval ) \
	if( sval.val == desired && desired == LIBANDRIA4_RESULT_GENERIC ) { \
		printf( "   Good success, result == desired == generic success.\n" ); } \
	else { \
		printf( \
			"   False success, result: %i; result == desired: %i; desired == generic success: %i.\n", \
			sval.val, \
			(int)( sval.val == desired ), \
			(int)( desired == LIBANDRIA4_RESULT_GENERIC ) ); \
		ret = EXIT_FAILURE; }
#define ONFAIL_INNER( result ) \
	if( result == desired ) { \
		printf( "   Good failure, result == desired == %s.\n", desiredname ); } \
	else { \
		printf( \
			"   Bad failure, result == %i != desired, desired == %i == %s.\n", \
			(int)( result ), \
			desired, \
			desiredname ); \
		ret = EXIT_FAILURE; }
#define ONFAIL( err ) \
	switch( err.val ) { \
		case LIBANDRIA4_RESULT_FAILURE_DOMAIN: ONFAIL_INNER( err.val ); break; \
		case LIBANDRIA4_RESULT_FAILURE_RANGE: ONFAIL_INNER( err.val ); break; \
		case LIBANDRIA4_RESULT_FAILURE_ILSEQ: ONFAIL_INNER( err.val ); break; \
		case LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED: ONFAIL_INNER( err.val ); break; \
		default: printf( "   Bad failure, unfamiliar result == %i.\n", (int)( err.val ) ); ret = EXIT_FAILURE; break; }
	
	
	
	printf( "\nRunning LibAndria4 stdmonads.c test program.\n" );
	printf( " Preliminary errno value: %i\n", desired );
	
	
	errno = 0;
	desired = LIBANDRIA4_RESULT_GENERIC;
	desiredname = "LIBANDRIA4_RESULT_GENERIC";
	printf( "  Trying errno == 0 for %s.\n", desiredname );
	res = libandria4_errno_2result();
	LIBANDRIA4_RESULT_BODYMATCH( res, ONSUCC, ONFAIL );
	
	???
	
	
	if( ret == EXIT_SUCCESS )
	{
		printf( " Testing was successful.\n" );
		
	} else {
		
		printf( " Testing was unsuccessful.\n" );
	}
	return( ret );
}
