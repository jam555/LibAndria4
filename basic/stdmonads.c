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

#include <errno.h>

#include "stdmonads.h"
#include "simpleops.h"



libandria4_result libandria4_errno_2result()
{
	int errnum = errno;
	
	switch( errnum )
	{
		case 0:
				/* No error. */
			break;
			
		case EDOM:
			return
			(
				LIBANDRIA4_RESULT_BUILDFAILURE(
					(libandria4_failure_result){
						LIBANDRIA4_RESULT_FAILURE_DOMAIN } )
			);
		case ERANGE:
			return
			(
				LIBANDRIA4_RESULT_BUILDFAILURE(
					(libandria4_failure_result){
						LIBANDRIA4_RESULT_FAILURE_RANGE } )
			);
		case EILSEQ:
			return
			(
				LIBANDRIA4_RESULT_BUILDFAILURE(
					(libandria4_failure_result){
						LIBANDRIA4_RESULT_FAILURE_ILSEQ } )
			);
			
		default:
				/* Because whatever it is, I added a result number for it. */
			return
			(
				LIBANDRIA4_RESULT_BUILDFAILURE(
					(libandria4_failure_result){
						LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED } )
			);
	}
	
	return
	(
		LIBANDRIA4_RESULT_BUILDSUCCESS(
			(libandria4_success_result){
				LIBANDRIA4_RESULT_GENERIC } )
	);
}
libandria4_result libandria4_errno_popresult( int *errnum )
{
	libandria4_result res = libandria4_errno_2result();
	
	if( errnum )
	{
		*errnum = errno;
	}
	
	errno = 0;
	
	return( res );
}

libandria4_result libandria4_result_from_maybeerr( libandria4_maybeint err )
{
	int a, res;
	LIBANDRIA4_MAYBEINT_BODYMATCH(
		err,
		
		LIBANDRIA4_OP_SETaFLAGresAS1,
		LIBANDRIA4_OP_SETresTOn1 );
	
	if( res )
	{
		LIBANDRIA4_RESULT_RETURNFAILURE( a );
		
	} else {
		
		LIBANDRIA4_RESULT_RETURNSUCCESS( LIBANDRIA4_RESULT_GENERIC );
	}
}
libandria4_result libandria4_result_from_maybesucc( libandria4_maybeint succ )
{
	int a, res;
	LIBANDRIA4_MAYBEINT_BODYMATCH(
		succ,
		
		LIBANDRIA4_OP_SETresTOn1,
		LIBANDRIA4_OP_SETaFLAGresAS1 );
	
	if( res )
	{
		LIBANDRIA4_RESULT_RETURNSUCCESS( a );
		
	} else {
		
		LIBANDRIA4_RESULT_RETURNFAILURE( LIBANDRIA4_RESULT_GENERIC );
	}
}
libandria4_maybeint libandria4_result_to_maybeerr( libandria4_result err )
{
	int a, res;
	LIBANDRIA4_RESULT_BODYMATCH(
		err,
		
		LIBANDRIA4_OP_SETresTOn1,
		LIBANDRIA4_OP_SETaFLAGresAS1 );
	
	if( res )
	{
		LIBANDRIA4_MAYBEINT_RETURNJUST( a );
		
	} else {
		
		LIBANDRIA4_MAYBEINT_RETURNNOTHING();
	}
}
libandria4_maybeint libandria4_result_to_maybesucc( libandria4_result succ )
{
	int a, res;
	LIBANDRIA4_RESULT_BODYMATCH(
		err,
		
		LIBANDRIA4_OP_SETaFLAGresAS1,
		LIBANDRIA4_OP_SETresTOn1 );
	
	if( res )
	{
		LIBANDRIA4_MAYBEINT_RETURNJUST( a );
		
	} else {
		
		LIBANDRIA4_MAYBEINT_RETURNNOTHING();
	}
}
