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


	/* Fore size_t, though I think it's in stdlib.h and stdio.h as well. */
#include <stddef.h>
	/* For EXIT_SUCCESS and EXIT_FAILURE. */
#include <stdlib.h>
	/* For printf(). */
#include <stdio.h>
	/* For the standard "errno" variable. */
#include <errno.h>

#include "../basic/stdmonads.h"


int main( int argn, char *argc[] )
{
	libandria4_result res;
	int desired = errno, tmp;
	int ret = EXIT_SUCCESS;
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
	
	errno = EDOM;
	desired = LIBANDRIA4_RESULT_FAILURE_DOMAIN;
	desiredname = "LIBANDRIA4_RESULT_FAILURE_DOMAIN";
	printf( "  Trying errno == EDOM for %s.\n", desiredname );
	res = libandria4_errno_2result();
	LIBANDRIA4_RESULT_BODYMATCH( res, ONSUCC, ONFAIL );
	
	errno = ERANGE;
	desired = LIBANDRIA4_RESULT_FAILURE_RANGE;
	desiredname = "LIBANDRIA4_RESULT_FAILURE_RANGE";
	printf( "  Trying errno == ERANGE for %s.\n", desiredname );
	res = libandria4_errno_2result();
	LIBANDRIA4_RESULT_BODYMATCH( res, ONSUCC, ONFAIL );
	
	errno = EILSEQ;
	desired = LIBANDRIA4_RESULT_FAILURE_ILSEQ;
	desiredname = "LIBANDRIA4_RESULT_FAILURE_ILSEQ";
	printf( "  Trying errno == EILSEQ for %s.\n", desiredname );
	res = libandria4_errno_2result();
	LIBANDRIA4_RESULT_BODYMATCH( res, ONSUCC, ONFAIL );
	
	tmp = 1;
	if( tmp == EDOM ) { ++tmp; }
	if( tmp == ERANGE ) { ++tmp; }
	if( tmp == EILSEQ ) { ++tmp; }
	errno = tmp;
	desiredname = "LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED";
	printf( "  Trying errno == %i for %s.\n", tmp, desiredname );
	desired = LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED;
	res = libandria4_errno_2result();
	LIBANDRIA4_RESULT_BODYMATCH( res, ONSUCC, ONFAIL );
	
	
	printf( "  Trying libandria4_errno_popresult() for errno == %i for %s.\n", tmp, desiredname );
	res = libandria4_errno_popresult( &tmp );
	LIBANDRIA4_RESULT_BODYMATCH( res, ONSUCC, ONFAIL );
	printf( "  libandria4_errno_popresult() returned %i via it's arguments.\n", tmp );
	
	
	if( ret == EXIT_SUCCESS )
	{
		printf( " Testing was successful.\n" );
		
	} else {
		
		printf( " Testing was unsuccessful.\n" );
	}
	return( ret );
}
