
#include <stdlib.h>
#include "../../basic/pascalarray.h"

LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( libandria4_char_, char )

int main( int argn, char *args[] )
{
	LIBANDRIA4_DEFINE_PASCALARRAY_STATICBUILD(
		name1,
		arr,
		
		libandria4_char_,
		char,
		
		'c','h','a','r', '\0' );
	
	printf( "\nTest 2.\n    :" );
	
	int l = 0;
	while( name1.arr.len > l )
	{
		putc( name1.arr.body[ l ], stdout );
		++l;
	}
	
	putc( '\n', stdout );
}
