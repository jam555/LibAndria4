#ifndef LIBANDRIA4_PARSER_CMARGS1_CMARGS_H
 #define LIBANDRIA4_PARSER_CMARGS1_CMARGS_H
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
	
	
	#include <stdio.h>
	#include <ctype.h>
	
		/* For libandria4_commonlib_firstchars[]. */
	#include "../../basic/commonlib.h"
		/* For the continuation-trampoline-style engine & related definitions. */
		/* Usually stack[ 0 ] should be a return/C stack. A FORTH data */
		/*  stack should be stack[ 1 ]. Stack[ 2 ] is used for string building. */
	#include "../../basic/ctsengine.h"
		/* For pascal-array, libandria4_char_pascalarray{}, and */
		/*  libandria4_charparrptr_pascalarray{}. */
	#include "../../basic/commonparrs.h"
	
	
	
	typedef enum
	{
		libandria4_parser_cmargs1_opt_spec__INVALID = -1,
		libandria4_parser_cmargs1_opt_spec__NULL = 0,
		
		libandria4_parser_cmargs1_opt_spec__generint = 1,
		libandria4_parser_cmargs1_opt_spec__signdec,
		libandria4_parser_cmargs1_opt_spec__usigndec,
		libandria4_parser_cmargs1_opt_spec__oct,
		libandria4_parser_cmargs1_opt_spec__hex,
		
		libandria4_parser_cmargs1_opt_spec__generfloat,
		libandria4_parser_cmargs1_opt_spec__floata,
		
		libandria4_parser_cmargs1_opt_spec__char,
		libandria4_parser_cmargs1_opt_spec__string,
		
		libandria4_parser_cmargs1_opt_spec__PASTEND
		
	} libandria4_parser_cmargs1_opt_spec;
	LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( libandria4_parser_cmargs1_opt_spec_, libandria4_parser_cmargs1_opt_spec );
	/* libandria4_parser_cmargs1_opt_spec_pascalarray{} is now available. */
	
	typedef struct libandria4_parser_cmargs1_opt
	{
		libandria4_char_pascalarray *name;
			/* Note: switch this to an array of ints or something. */
		libandria4_parser_cmargs1_opt_spec_pascalarray *subarg_specifiers;
		
		libandria4_cts_closure handler, abbrev;
		
		char name_abbrev;
		
	} libandria4_parser_cmargs1_opt;
	LIBANDRIA4_DEFINE_PASCALARRAY_TYPE( libandria4_parser_cmargs1_opt_, libandria4_parser_cmargs1_opt );
	/* libandria4_parser_cmargs1_opt_pascalarray{} is now available. */
	
	typedef struct libandria4_parser_cmargs1_arginfo
	{
		/* The arguments to parse. Conceptually the arguments given to main(), */
		/*  but frankly can be anything so long as argn correctly specifies the */
		/*  number of entries in args, and each string in args ends with a null. */
		int argn;
		char **args;
		
			/* These handlers MUST all point to a valid function. */
		libandria4_cts_closure
				/* onfatal() will find a function-pointer, on a void-pointer, on */
				/*  an unsigned int, all in stack[ 1 ]. The function pointer */
				/*  indicates the "entry function" for a group of 1 or more */
				/*  implementation functions, the other two further refine that */
				/*  information in group-specific ways. The function pointer */
				/*  will point to libandria4_parser_cmargs1_arginfo_parse() */
			onfatal,
				/* Called only when the last argument was reached but the */
				/*  sub-args of an option were only partially completed. No */
				/*  particular args, but args[ arg_progress - 1 ] is the */
				/*  triggering argument. */
			onshortfall,
				/* Either there weren't any leading dashes in the arg, or */
				/*(  nothing matched it. Regardless, it was */
					/* args[ arg_progress - 1 ] */
				/*  that triggered this call, just like onshortfall. */
			onoptless;
		
			/* The array of options to look through. */
		libandria4_parser_cmargs1_opt_pascalarray *opts_list;
		
			/* This is just for quick lookup. */
		libandria4_parser_cmargs1_opt *acti_opt;
		size_t arg_progress, acti_progress, sub_progress;
		
	} libandria4_parser_cmargs1_arginfo;
	
	
	
	int libandria4_parser_cmargs1_arginfo_invalid( libandria4_parser_cmargs1_arginfo* );	
	int libandria4_parser_cmargs1_arginfo_invalidopts
	(
		libandria4_parser_cmargs1_opt_pascalarray *opts,
		size_t *last
	);
	libandria4_cts_closure libandria4_parser_cmargs1_arginfo_onfatal
	(
		libandria4_cts_context *ctx, void *data_,
		libandria4_cts_framefunc tag_ptr, void *tag2, unsigned int tag3
	);
	
	#define libandria4_parser_cmargs1_arginfo_RETONFATAL( ctxptr, dataptr, funcptr, sec_id, thrd_id ) \
		return( \
			libandria4_parser_cmargs1_arginfo_onfatal( \
				(ctxptr), (dataptr), \
				(funcptr), \
				(void*)&( libandria4_commonlib_firstchars[ (sec_id) ] ), \
				(thrd_id) ) )
	
	
	
	libandria4_cts_closure libandria4_parser_cmargs1_arginfo_parse( libandria4_cts_context *ctx, void *data_ );
	
	/* End parsers/cmargs1/cmargs.h */
	
#endif
