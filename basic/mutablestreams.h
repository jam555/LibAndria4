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

#ifndef LIBANDRIA4_BASIC_MUTABLESTREAMS_H
# define LIBANDRIA4_BASIC_MUTABLESTREAMS_H
	
	#include <stdint.h>
	#include <stdio.h>
	
	#include "monads.h"
	#include "commonio.h"
	
	
	
	/* Tool macros are located in the last third of this file. */
	
	
	
	typedef struct libandria4_FILE_substream_vtable libandria4_FILE_substream_vtable;
	
	
		/* libandria4_FILE_handle{} probably never had any users, */
		/*  but just in case there were, it's now named */
		/*  libandria4_FILE_tracker{}. */
	LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDDECL(
			libandria4_FILE_tracker,
				libandria4_FILE_substream_vtable*
		);
	
		/* libandria4_FILE_substream used to be named libandria4_FILE_file. */
	typedef libandria4_FILE_tracker_counttype libandria4_FILE_substream;
	
	
		/* If "just", replace your previous substream with this provided */
		/*  one. If "nothing", continue using your current substream. */
	LIBANDRIA4_MONAD_MAYBE_BUILDTYPE(
		libandria4_FILE_redirection,
			libandria4_FILE_substream*
	);
	
	
	
		/* Last chance to add a header with stuff like bituplic2{}... */
		/*  libandria4_FILE_redirection{} is needed for some of it, and */
		/*  that's defined in this file above this line, so there's only so */
		/*  much choice in where to put it. */
	#include "mutablestreams_innertypes.h"
	
	
	
		/* The virtual table for the whole thing. A void ointer will also be */
		/*  provided by libandria4_FILE_tracker{}, but that type is fixed by */
		/*  *_substream{}, not configurable. */
		/* Refer to mutastreams/muta_notes.h to understand missing elements. */
	struct libandria4_FILE_substream_vtable
	{
			/* These two are used directly by libandria4_FILE_tracker{}. */
		void (*attending)( uintptr_t *count );
		void (*neglecting)( uintptr_t *count );
		
		int (*is_eof)( void* /* FILE* */ );
			/* If there isn't an error, then it MIGHT still indicate eof. */
		libandria4_newstreams_result2 (*get_error)( void* );
		
		libandria4_newstreams_bituplic2 (*clear_err)( void* );
		
		
			/* For the int argument, use SEEK_SET, SEEK_CUR, or SEEK_END, */
			/*  all from stdio.h . The intmax_t is an offset in reference */
			/*  to the point specified to the regular int. */
		libandria4_newstreams_bituplic4 (*tell)( void*, int );
		libandria4_newstreams_bituplic2 (*seek)( void*, intmax_t, int );
		
		libandria4_newstreams_bituplic2 (*rewind)( void* );
		
		libandria4_newstreams_bituplic2 (*flush)( void* );
		
		
		libandria4_newstreams_bituplic3 (*get_c)( void* );
		libandria4_newstreams_bituplic1 (*put_c)( void*, char );
		
			/* This is used directly by libandria4_FILE_tracker{}. */
		void (*close)( void* /* FILE* */ );
	};
	
	
	/* TODO: I think this stuff needs to move to the head of the .c file? */
		/* The ondie handler is vitally important, and needs to interplay with */
		/*  the rest of this system. See libandria4_FILE_tracker_initialize()'s */
		/*  note. */
		/* Note that we SHOULD give this a better name later. */
		/* The first argument will be ->aux, the second will be ->data, but */
		/*  we're storing the FILE pointer in aux and the virtual table in val, */
		/*  so this is actually correct. */
		/* Is *_ONDIE() supposed to redirect to the EOF stream? But that might */
		/*  be impossible? */
	#define LIBANDRIA4_FILE_TRACKER_ONATTEND( tracked, file_p, vtab_p ) \
		( ( ( vtab_p ) && (vtab_p)->attending ) \
			? ( (vtab_p)->attending( &( (tracked)->ref_count ) ) ) )
	#define LIBANDRIA4_FILE_TRACKER_ONNEGLECT( tracked, file_p, vtab_p ) \
		( ( ( vtab_p ) && (vtab_p)->neglecting ) \
			? ( (vtab_p)->neglecting( &( (tracked)->ref_count ) ) ) )
	#define LIBANDRIA4_FILE_TRACKER_ONDIE( file_p, vtab_p ) \
		( ( ( vtab_p ) && (vtab_p)->close ) \
			? ( (vtab_p)->close( (file_p) ) ) )
		/* We want to just use malloc() & friends, so *_STDIMPL(). */
	LIBANDRIA4_MONAD_REFPOINTER_DEFINE_STDIMPL(
			libandria4_FILE_tracker,
				libandria4_FILE_substream_vtable*,
				
				LIBANDRIA4_FILE_TRACKER_ONATTEND,
				LIBANDRIA4_FILE_TRACKER_ONNEGLECT,
				LIBANDRIA4_FILE_TRACKER_ONDIE
		);
	
	
	
	
	
	#define LIBANDRIA4_FILE_TRACKER_BODYINIT( var, innerval, aux,  failinit, badalloc, badata ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYINIT( \
			libandria4_FILE_tracker,  var, innerval, aux,  failinit, badalloc, badata )
	#define LIBANDRIA4_FILE_TRACKER_BODYSET( var, valptr,  failneglect, failattend, succneglect, succattend, ondead ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYSET( \
			libandria4_FILE_tracker,  var, valptr,  failneglect, failattend, succneglect, succattend, ondead )
	#define LIBANDRIA4_FILE_TRACKER_BODYDEINIT( var,  failneglect, succneglect, ondead ) \
		LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYDEINIT( \
			libandria4_FILE_tracker,  var,  failneglect, succneglect, ondead )
	
	/* Legacy names, these need to be replaced whereever they get used. */
	#define LIBANDRIA4_FILE_REDIRECTION_BODYINIT( var, innerval, aux,  failinit, badalloc, badata ) \
		LIBANDRIA4_FILE_TRACKER_BODYINIT( var, innerval, aux,  failinit, badalloc, badata )
	#define LIBANDRIA4_FILE_REDIRECTION_BODYSET( var, valptr,  failneglect, failattend, succneglect, succattend, ondead ) \
		LIBANDRIA4_FILE_TRACKER_BODYSET( var, valptr,  failneglect, failattend, succneglect, succattend, ondead )
	#define LIBANDRIA4_FILE_REDIRECTION_BODYDEINIT( var,  failneglect, succneglect, ondead ) \
		LIBANDRIA4_FILE_TRACKER_BODYDEINIT( var,  failneglect, succneglect, ondead )
	
	
	
	/* These are correctly named. */
	
	#define LIBANDRIA4_FILE_REDIRECTION_TOTARGET( val ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( libandria4_FILE_redirection, libandria4_FILE_substream*, (val) )
	#define LIBANDRIA4_FILE_REDIRECTION_TOCURRENT( ... ) \
		LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( libandria4_FILE_redirection, libandria4_FILE_substream* )
	#define LIBANDRIA4_FILE_REDIRECTION_RETURNTARGET( val ) \
		LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( libandria4_FILE_redirection, libandria4_FILE_substream*, (val) )
	#define LIBANDRIA4_FILE_REDIRECTION_RETURNCURRENT( ... ) \
		LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( libandria4_FILE_redirection, libandria4_FILE_substream* )
	
	
	
	/* LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE() is */
	/*  libandria4_FILE_redirection{}'s equivalent of *_BODYMATCH(). */
	/*  It specifically updates a libandria4_FILE_tracker{} instance */
	/*  if AND ONLY IF a non-nothing libandria4_FILE_redirection{} */
	/*  instance is provided to it, otherwise leaving the */
	/*  libandria4_FILE_tracker{} untouched. It exists to make */
	/*  certain that libandria4_FILE_tracker{} and */
	/*  libandria4_FILE_redirection{} interact correctly. */
		#define LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE_INNERTOOL( val ) \
			( LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE_trip = 1, \
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE_trig = (val) )
		/* FILE_tracker is a libandria4_FILE_tracker{} variable. */
		/* redir_var is a libandria4_FILE_redirection{} variable. */
		/* on_failattend() and: */
		/* on_failneglect() are just for logging, neither gets an */
		/*  argument. */
		/* on_redir() is for... whatever you feel like, it receives */
		/*  FILE_tracker{} by value as it's argument. */
	#define LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE( FILE_tracker, redir_var,  on_failattend, on_failneglect, on_redir ) \
		{ \
			libandria4_FILE_substream *LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE_trig = \
				(libandria4_FILE_substream*)0; \
			int LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE_trip = 0; \
			LIBANDRIA4_MONAD_MAYBE_BODYMATCH( \
				( redir_var ), \
				LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE_INNERTOOL, \
				LIBANDRIA4_NULL_MACRO ); \
			if( LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE_trip ) { \
				LIBANDRIA4_FILE_REDIRECTION_BODYSET( \
					( FILE_tracker ), LIBANDRIA4_FILE_REDIRECTION_BODYUPDATE_trig, \
					( on_failneglect ), ( on_failattend ), \
					LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO, \
					LIBANDRIA4_NULL_MACRO /* on_dead( ptr ), just for logging. */ ); \
				( on_redir( FILE_tracker ) ); } }
	
	
	
	
	
		/* These are specifically for a never-deallocating substream */
		/*  that always acts as an EOF, no matter what, and does */
		/*  pretty much nothing else. */
	extern libandria4_FILE_substream lib4_FILE_EOFsubstream;
	#define LIBANDRIA4_FILE_REDIRECTION_TOEOF() \
		LIBANDRIA4_MONAD_MAYBE_BUILDJUST( \
			libandria4_FILE_redirection, libandria4_FILE_substream*, \
			&lib4_FILE_EOFsubstream )
	#define LIBANDRIA4_FILE_REDIRECTION_RETURNEOF() \
		LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( \
			libandria4_FILE_redirection, libandria4_FILE_substream*, \
			&lib4_FILE_EOFsubstream )
	
	
	
	
		/* A standard wrapper to allow a mutablestream to be used as */
		/*  the backend of a normal IO stream. */
	#include "mutastreams/muta2std.h"
	
#endif
/* End mutablestreams.h */
