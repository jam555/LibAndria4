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

#ifndef LIBANDRIA4_BASIC_MUTASTREAMS_MUTA2STD_H
# define LIBANDRIA4_BASIC_MUTASTREAMS_MUTA2STD_H
	
	/*
		Wrapper progress:
	struct libandria4_FILE_substream_vtable
	{
		void (*attending)( uintptr_t *count );
		void (*neglecting)( uintptr_t *count );
		
		
		
		int (*is_eof)( void* ( FILE* ) );																Done.
		libandria4_newstreams_result2 (*get_error)( void* ( FILE* ) );									Done.
		
		libandria4_newstreams_bituplic2 (*clear_err)( void* ( FILE* ) );								Done.
		
		libandria4_newstreams_bituplic4 (*tell)( void* ( FILE* ), int (Reference point.) );				Done.
		libandria4_newstreams_bituplic2 (*seek)( void* ( FILE* ), intmax_t, int (Reference point.) );	Done.
		
		libandria4_newstreams_bituplic2 (*rewind)( void* ( FILE* 0 );									Done.
		
		libandria4_newstreams_bituplic2 (*flush)( void* ( FILE* ) );									Done.
		
		libandria4_newstreams_bituplic3 (*get_c)( void* ( FILE* ) );									Done.
		libandria4_newstreams_bituplic1 (*put_c)( void* ( FILE* ), char );								Done.
		
		
		
		void (*close)( void* ( FILE* ) );
	};
	*/
	
	typedef struct libandria4_mutastream_2stream
	{
		libandria4_commonio_handle handle;
		libandria4_commonio_istream_ungetwrapper_vtable uget_host;
		libandria4_commonio_istream_vtable uget_support;
		libandria4_FILE_tracker trk;
		
	} libandria4_mutastream_2stream;
	
#endif
/* End muta2std.h */
