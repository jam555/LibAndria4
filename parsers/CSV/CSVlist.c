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











#if 0
	
	/* This was grabbed from the header. It needs to be worked on. */
	
	
	
	/* The following is convenience code for those that want to build parse */
	/*  trees from the parse process. Use it or ignore it as you see fit. */
/* Basic structure: build a trieither (not just an either!) that can accept */
/*  a list pointer (of either of two types) or a p-string pointer: this is */
/*  the "fundamental" value, and each "real" value is represented by one. One */
/*  list-p will represent a sequential value (a value made of multiple parts), */
/*  and the other will represent a record (a line when ignoring vertical */
/*  spacers within a string) composed of some arbitrary number of "real */
/*  values". Whether these "real values" are simple tokens & strings or */
/*  include lists depends on the settings inside the relevant */
/*  libandria4_parser_CSV_CSV1_file{} instance. */
	
	typedef struct libandria4_parser_CSV_CSV1_listnode libandria4_parser_CSV_CSV1_listnode;
	#define LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE_GETLEFT( refnodeptr ) \
		( ( refnodeptr ) ? \
			( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) : \
			( ( name ## _bitup_buildNodeptr )( \
				*libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 0 ) ) ) )
	#define LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE_GETRIGHT( refnodeptr ) \
		( ( refnodeptr ) ? \
			( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) : \
			( ( name ## _bitup_buildNodeptr )( \
				*libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 1 ) ) ) )
	#define LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE_SETLEFT( refnodeptr, valptr ); \
		( ( refnodeptr ) ? \
			( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) : \
			( *libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 0 ) = (valptr), \
				( name ## _bitup ) ( name ## _bitup_buildNodeptr )( \
					*libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 0 ) ) ) )
	#define LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE_SETRIGHT( refnodeptr, valptr ); \
		( ( refnodeptr ) ? \
			( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ) : \
			( *libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 1 ) = (valptr), \
				( name ## _bitup ) ( name ## _bitup_buildNodeptr )( \
					*libandria4_parser_CSV_CSV1_listnode_getneighbor( (refnodeptr), 1 ) ) ) )
	
	LIBANDRIA4_LIST_BASICBUILDER_SINGLELINKED(
		libandria4_parser_CSV_CSV1_list,
		libandria4_parser_CSV_CSV1_listnode,
		LIBANDRIA4_PARSER_CSV_CSV1_LISTNODE );
	
	LIBANDRIA4_MONAD_TRIETHER_BUILDTYPE_DEFINITION(
		libandria4_parser_CSV_CSV1_trival,
			libandria4_char_pascalarray*,
			libandria4_parser_CSV_CSV1_list*,
			libandria4_parser_CSV_CSV1_list* );
	
	struct libandria4_parser_CSV_CSV1_listnode
	{
		libandria4_parser_CSV_CSV1_trival here;
		libandria4_parser_CSV_CSV1_listnode *peers[ 2 ];
	};
	
	
	
	libandria4_parser_CSV_CSV1_listnode**
		libandria4_parser_CSV_CSV1_listnode_getneighbor( libandria4_parser_CSV_CSV1_listnode *ref, int getright );
	
	???
	
#endif










/*
			libandria4_result ( libandria4_parser_CSV_CSV1_list_destroylist )( \
					lib4_memfuncs_t *mf_ptr, libandria4_parser_CSV_CSV1_list *a,  void *data, void (*nodefunc)( void*, (nodetype)* ) )
*/



/* Note: all of that stuff about lists and triethers and stuff? Yeah, that */
/*  doesn't belong there. Take that stuff, and move it into some helper */
/*  implementations that CAN be used if the application wants to build a */
/*  parse-tree or something, and have easy wrappers to make that a simple */
/*  one-liner, but don't get invoked if the application doesn't want (as in */
/*  the "splitter" application described a bit further down...). That stuff */
/*  CAN be useful, and SHOULD be pre-written, but ISN'T correct for */
/*  automatic integration. So stop trying to automatically integrate it. */



/* Note: next we need to write some stuff to specially handle the first two */
/*  records (the first two "lines") if (and only if) special handlers for */
/*  them are detected. */

/* Write that here. */



/* Then we need to go back through and actually call the handlers (the */
	/* ( (libandria4_parser_CSV_CSV1_file*)data )->{ libandria4_cts_closure onstr, onval, outrec; } */
/*  stuff) when the proper conditions are reached. */

/* Write that here. */



/* Then we need to write a program that will do all of that, but dispatches */
/*  the resulting stuff to other programs via fork: remember to include */
/*  record and field numbers as part of the data! */

/* DON'T write that here, write that in another file. It should be a full program. */









libandria4_parser_CSV_CSV1_listnode**
	libandria4_parser_CSV_CSV1_listnode_getneighbor( libandria4_parser_CSV_CSV1_listnode *ref, int getright )
{
	if( ref )
	{
		return( &( ref->peers[ getright ? 1 : 0 ] ) );
	}
	
	return( (libandria4_parser_CSV_CSV1_listnode**)0 );
}
