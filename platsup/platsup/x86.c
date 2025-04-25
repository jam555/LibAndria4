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

#include "x86.h"


uintptr_t libandria4_ptrhash( size_t len, char *str )
{
	uintptr_t ret = 0, offr = 0, offp = 0;
	uint16_t patch = 0;
	
	while( len )
	{
		patch += ( *str ) << offp;
		
		len -= 1;
		++str;
		offp += 7;
		if( offp >= 8 )
		{
			offp -= 8;
			offr += 8;
			ret ^= ( ( patch & 255 ) << offr );
			patch &= ( 255 << 8 );
			patch >>= 8;
		}
		if( offr >= CHAR_BITS * LIBANDRIA4_CELLTYPE_REGSIZE )
		{
			offr = 0;
		}
	}
	while( patch )
	{
		offr += 8;
		ret ^= ( ( patch & 255 ) << offr );
		patch &= ( 255 << 8 );
		patch >>= 8;
		
		if( offr >= CHAR_BITS * LIBANDRIA4_CELLTYPE_REGSIZE )
		{
			offr = 0;
		}
	}
	
	return( ret );
}



/*
	The stuff here is partially based on:
		https://www.moritz.systems/blog/how-debuggers-work-getting-and-setting-x86-registers-part-1/#fxsave-vs-fxsave64
*/

#if LIBANDRIA4_TARGETPROCESSOR2 >= \
	LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
	static thread char procname[ 12 ];
	static uint32_t libandria4_cpuid_inner( uint32_t leaf, uint32_t sub );
#endif
int libandria4_cpuid
(
	uint32_t leaf, uint32_t subleaf,
	uint32_t *ret, char *name
)
{
	#if LIBANDRIA4_TARGETPROCESSOR2 < \
		LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
		
		return( -1 );
		
	#else
		uint32_t tmp;
		if( !ret )
		{
			ret = &tmp;
		}
		*ret = libandria4_cpuid_inner( leaf, subleaf );
		if( leaf == 0 && name )
		{
			int i = 0;
			while( i < 12 )
			{
				name[ i ] = procname[ i ];
				++i;
			}
		}
		
		return( 1 );
	#endif
}
	/* Some 486 also support this, but I'm not sure how to ID them, */
	/*  so waiting for Pentium will do. */
#if LIBANDRIA4_TARGETPROCESSOR2 >= \
	LIBANDRIA4_PROCESSOR0_ISA_x86_Pentium1
	
	static uint32_t libandria4_cpuid_inner( uint32_t leaf, uint32_t sub )
	{
		uint32_t res, a, b, c;
		
		__asm__ volatile {
			"mov %%ecx %%eax\n"
			"mov %%edx %%ecx\n"
			"cpuid\n"
			"mov %%eax %0\n"
			"mov %%ebx %1\n"
			"mov %%edx %2\n"
			"mov %%ecx %3\n"
			:
			"=m"(res), "=m"(a), "=m"(b), "=m"(c)
		};
		
		if( leaf == 0 )
		{
			int i1 = 0, i2 = 0;
			while( i2 < 3 )
			{
				procname[ i2 * 4 + i1 ] =
					(
						a & ( 255 << ( i1 * 8 ) )
					) >> ( i1 * 8 );
				++i1;
				if( i1 >= 4 )
				{
					i1 = 0;
					++i2;
					a = b;
					b = c;
				}
			}
		}
		
		return( res );
	}
	
	int libandria4_cpuid_x86_xsaveavail()
	{
		static int status = 0;
		
		
		if( status == 0 )
		{
			volatile uint32_t tmp;
			volatile uint32_t str[ 3 ];
			int res = libandria4_cpuid( 1, 0,  &tmp, (char*)str );
			
				/* Test ECX for XSAVE. */
			if( str[ 2 ] & 0x04000000 )
			{
				status = 1;
				
			} else {
				
				status = -1;
			}
		
		return( status );
	}
	int libandria4_cpuid_x86_avxavail()
	{
		static int status = 0;
		
		
		if( status == 0 )
		{
			volatile uint32_t tmp;
			volatile uint32_t str[ 3 ];
			int res = libandria4_cpuid( 1, 0,  &tmp, (char*)str );
			
				/* Test ECX for AVX. */
			if( str[ 2 ] & 0x10000000 )
			{
				status = 1;
				
			} else {
				
				status = -1;
			}
		
		return( status );
	}
	int libandria4_cpuid_x86_avxoffset( uint32_t *off )
	{
		static uint32_t offset;
		static int status = 0;
		
		
		if( status == 0 )
		{
			volatile uint32_t tmp;
			volatile uint32_t str[ 3 ];
			int res = libandria4_cpuid( 0x0D, 0x02,  &tmp, (char*)str );
			
			res = 1;
			offset = str[ 0 ];
		}
		if( status && off )
		{
			*off = offset;
		}
		
		return( status );
	}
	int libandria4_cpuid_x86_avxsize( uint32_t *sz )
	{
		static uint32_t size;
		static int status = 0;
		
		
		if( status == 0 )
		{
			volatile uint32_t tmp;
			volatile uint32_t str[ 3 ];
			int res = libandria4_cpuid( 0x0D, 0,  &tmp, (char*)str );
			
			res = 1;
			size = str[ 0 ];
		}
		if( status && sz )
		{
			*sz = size;
		}
		
		return( status );
	}
#endif
