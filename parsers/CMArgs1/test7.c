
#include <stdlib.h>
#include "../../basic/pascalarray.h"

typedef struct testtype
{
	int *ptr;
	
} testtype;
LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( testtype_arr_, testtype )

int dummy1;

int main( int argn, char *args[] )
{
	int dummy2;
	
	static int
		*reftest1 = &dummy1,
		*reftest2[] = { &dummy1 };
	
	static struct
	{
		testtype_arr_pascalarray arr;
		testtype libandria4_pascalarray_arrmember
			[
				sizeof(
					(testtype[])
					{
						(testtype){ &dummy1 },
						(testtype){ &dummy1 }
					}
				) /
				sizeof( testtype )
			];
	}
		/* test1 =
			{
				(testtype_arr_pascalarray)
				{
					sizeof(
						(testtype[])
						{
							(testtype){ &dummy1 },
							(testtype){ &dummy1 }
						}
					) /
					sizeof( testtype )
				}, */
					/* The error appears to be the aggregate initializer */
					/*  ITSELF. I would expect the opposite, but whatever. */
				/* (const testtype[])
				{
					(testtype){ &dummy1 },
					(testtype){ &dummy1 }
				}
			}, */
		test2 =
			{
				(testtype_arr_pascalarray)
				{
					sizeof(
						(testtype[])
						{
							(testtype){ &dummy1 },
							(testtype){ &dummy1 }
						}
					) /
					sizeof( testtype )
				},
				{
					(testtype){ &dummy1 },
					(testtype){ &dummy1 }
				}
			},
		test3 =
			{
				(testtype_arr_pascalarray)
				{
					sizeof(
						(testtype[])
						{
							(testtype){ &dummy1 },
							(testtype){ &dummy1 }
						}
					) /
					sizeof( testtype )
				},
				(const testtype[])
				{
					&dummy1,
					&dummy1
				}
			},
		test4 =
			{
				(testtype_arr_pascalarray)
				{
					sizeof(
						(testtype[])
						{
							(testtype){ &dummy1 },
							(testtype){ &dummy1 }
						}
					) /
					sizeof( testtype )
				},
				{
					&dummy1,
					&dummy1
				}
			};
	
	printf( "\nTest 7." );
	/*
	printf( "\n    :%c %i",  'a', *( test1.arr.body[ 0 ].ptr ) );
	printf( "\n    :%c %i",  'b', *( test1.arr.body[ 1 ].ptr ) );
	*/
	printf( "\n    :%c %i",  'a', *( test2.arr.body[ 0 ].ptr ) );
	printf( "\n    :%c %i",  'b', *( test2.arr.body[ 1 ].ptr ) );
	
	printf( "\n    :%c %i",  'a', *( test3.arr.body[ 0 ].ptr ) );
	printf( "\n    :%c %i",  'b', *( test3.arr.body[ 1 ].ptr ) );
	
	printf( "\n    :%c %i",  'a', *( test4.arr.body[ 0 ].ptr ) );
	printf( "\n    :%c %i",  'b', *( test4.arr.body[ 1 ].ptr ) );
	
	putc( '\n', stdout );
}
