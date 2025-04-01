#ifndef LIBANDRIA4_BASIC_EXCEPTIONS_H
 #define LIBANDRIA4_BASIC_EXCEPTIONS_H
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
	
	
	
	/*
		Relevant macros:
			__COUNTER__ : every time it's encountered, it's value will be stepped.
				Clang, GCC, & MSVC.
			__TIMESTAMP__ : Contains a string form of the current file's
				modification time. Clang, GCC, & MSVC.
	*/
	#if defined( __cplusplus ) && __cplusplus < 201103L
		#error "LibAndria4 basic exceptions.h: Too-old C++ version detected.\n"
	#elif defined( __STDC_VERSION__ ) && __STDC_VERSION__ < 201112L
		/* If we wanted C99, we would compare to 199901L. */
		#error "LibAndria4 basic exceptions.h: Too-old C version detected.\n"
	#else
		#error "LibAndria4 basic exceptions.h: Unrecognized platform encountered.\n"
	#endif
	
	
	
	#include <setjmp.h>
	
	
	
		/* The only "correct" types for exceptions are those handed to */
		/*  LIBANDRIA4_EXCEPTIONS_TYPE(), which will be allocated at link-time */
		/*  instead of needing to be dynamically allocated. To the extent */
		/*  possible, they are meant to overlay each other, so don't bother */
		/*  hoping for all of them to be simultaqneously accessible. */
		/* This is technically wrong. */
	
		/* Pseudo-code, fix this up. */
	#if GCC
		
		#define LIBANDRIA4_EXCEPTIONS_MAKESECTION_R( sect ) \
			/* Don't need to explicitly declare sections for GCC. */
		#define LIBANDRIA4_EXCEPTIONS_MAKESECTION_RW( sect ) \
			/* Don't need to explicitly declare sections for GCC. */
		#define LIBANDRIA4_EXCEPTIONS_MAKESECTION_X( sect ) \
			/* Don't need to explicitly declare sections for GCC. */
		
		#define LIBANDRIA4_EXCEPTIONS_SECTION_VAR( sect, type, name ) \
			type name __attribute__ ((section ( sect )))
		
	#elif MSVC
		
		#error "MSVC syntax isn't quite right yet.\n"
		
		
		#define LIBANDRIA4_EXCEPTIONS_MAKESECTION_R( sect ) \
			#pragma section( sect,read )
		#define LIBANDRIA4_EXCEPTIONS_MAKESECTION_RW( sect ) \
			#pragma section( sect,read,write )
				/* For executable stuff. */
		#define LIBANDRIA4_EXCEPTIONS_MAKESECTION_X( sect ) \
			#error "LIBANDRIA4_EXCEPTIONS_MAKESECTION_X hasn't been defined for MSVC."
		
		
		#define LIBANDRIA4_EXCEPTIONS_SECTION_VAR( sect, type, name ) \
			__declspec(allocate( sect )) type name;
		
	#endif
	
	
	#define LIBANDRIA4_EXCEPTIONS_TYPE_DEC( type, name ) \
		extern type name; \
		extern uintptr_t * LIBANDRIA4_CAT( libandria4_exceptions_typekey_, type );
	#define LIBANDRIA4_EXCEPTIONS_TYPE_DEF( type, name ) \
		LIBANDRIA4_EXCEPTIONS_SECTION_VAR( \
			"LIBANDRIA4_EXCEPTIONS_TYPEOVR" LIBANDRIA4_STRINGIFY( name ), \
			type, name ); \
		static uintptr_t LIBANDRIA4_CAT( libandria4_exceptions_typekeyval_, type ) = \
			(uintptr_t)( &( name ) ); \
		uintptr_t * LIBANDRIA4_CAT( libandria4_exceptions_typekey_, type ) = \
			(uintptr_t)( & LIBANDRIA4_CAT( libandria4_exceptions_typekeyval_, type ) ); \
		typedef enum { LIBANDRIA4_CAT( libandria4_exceptions_typekeynum_, type ) = __COUNTER__ } \
			LIBANDRIA4_CAT( libandria4_exceptions_typekeyenum_, type ) ;
	
	
	
	/* Pre-define foreseeably needed sections. */
		/* We need this for lookups. */
	LIBANDRIA4_EXCEPTIONS_MAKESECTION_RW( "LIBANDRIA4_EXCEPTIONS_HANDLER_TABLES" )
		/* For the pre-allocated exception-data instances. */
	LIBANDRIA4_EXCEPTIONS_MAKESECTION_R( "LIBANDRIA4_EXCEPTIONS_TYPEOVR" )
	
	
	
		/* The per-"try" datatype. */
	typedef struct libandria4_exceptions_lexctx libandria4_exceptions_lexctx;
		/* Per-"catch" data. */
	typedef struct libandria4_exceptions_handler libandria4_exceptions_handler;
		/* Nesting-tracker data. Gets instantiated on the stack. */
	typedef struct libandria4_exceptions_runctx
	{
		libandria4_exceptions_runctx *prev;
		libandria4_exceptions_lexctx *here;
		unsigned progress;
		jmp_buf jb;
		
	} libandria4_exceptions_runctx;
	
	
	#include <threads.h>
	
	
	struct libandria4_exceptions_lexctx
	{
		const char *filename, *funcname;
		const int line;
		libandria4_exceptions_handler *handlers;
	};
	#define LIBANDRIA4_EXCEPTIONS_LEXCTX( body ) \
		{ static LIBANDRIA4_EXCEPTIONS_SECTION_VAR( \
				"LIBANDRIA4_EXCEPTIONS_HANDLER_TABLES", \
				libandria4_exceptions_handler[], \
				???1 ); \
			static libandria4_exceptions_lexctx \
				libandria4_exceptions_lexctx_herectx = \
					{ __FILE__, __func__, __LINE__, ???1 }; \
			libandria4_exceptions_runctx \
				libandria4_exceptions_runctx_herectx = \
					{ libandria4_exceptions_curstate, \
						&libandria4_exceptions_lexctx_herectx, \
						0, { 0 } }; \
			libandria4_exceptions_curstate = \
				&libandria4_exceptions_runctx_herectx; \
			\
			int libandria4_exceptions_setjmpres = \
				setjmp( &( libandria4_exceptions_runctx_herectx.jb ) ); \
			if( libandria4_exceptions_setjmpres ) { \
				libandria4_exceptions_handler *libandria4_exceptions_curstate_tmp = \
					libandria4_exceptions_runctx_herectx.handlers; \
				while( libandria4_exceptions_curstate_tmp ) { \
						if( libandria4_exceptions_curstate_tmp->type != \
							libandria4_exceptions_setjmpres ) { \
								libandria4_exceptions_setjmpres = \
									libandria4_exceptions_curstate_tmp->enu; \
								break; } \
						libandria4_exceptions_curstate_tmp = \
							libandria4_exceptions_curstate_tmp->prev; } } \
			switch( libandria4_exceptions_setjmpres ) { \
				case 0: body ; } }
	/*
		So, we need the last argument to *_herectx, and we need it to be
		possible to insert pointers into it, but we need it to be scoped
		to the current lexical scope only... I'm not sure how to do this.
		I've temporarily written the arg as ???1 as a marker.
	*/
	
	
	
	struct libandria4_exceptions_handler
	{
		libandria4_exceptions_handler *prev;
		
			/* enu is needed to convert from our sane pointer-based ids */
			/*  to the enum-based stuff that we need for the switches. */
		uintptr_t type, enu;
		bool catches;
		
		void *data;
			/* Note that this actually gets cast to */
				/* int (*)( void*, uintptr_t, type* ) */
			/*  as part of the call. */
		int (*preempted)( void* /* See "data" above. */, uintptr_t, void* );
	};
		/* In the hope of improving traversal times, we shove the handler */
		/*  structures all into a single object-file section. It will have */
		/*  to do for now. */
		/* predata & prehand are for preemption-handlers. */
	#define LIBANDRIA4_EXCEPTIONS_CATCHER( type, predata, prehand, body ) \
		LIBANDRIA4_EXCEPTIONS_SECTION_VAR( \
			"LIBANDRIA4_EXCEPTIONS_HANDLER_TABLES", \
			libandria4_exceptions_handler, \
			LIBANDRIA4_CAT( libandria4_exceptions_typehandler_, type ) ) = { 0 }; \
		if( !( LIBANDRIA4_CAT( libandria4_exceptions_typehandler_, type ).enu ) ) { \
			LIBANDRIA4_CAT( libandria4_exceptions_typehandler_, type ) = \
				{ libandria4_exceptions_lexctx_herectx.handlers, \
					*( LIBANDRIA4_CAT( libandria4_exceptions_typekey_, type ) ), \
					LIBANDRIA4_CAT( libandria4_exceptions_typekeynum_, type ), \
					0, \
					predata, prehand }; } \
		libandria4_exceptions_lexctx_herectx.handlers = \
			&( LIBANDRIA4_CAT( libandria4_exceptions_typehandler_, type ) ); \
		++( libandria4_exceptions_curstate.progress ); \
		if( 0 ) /* Default to bypassing the catch-handler. */ { \
			case LIBANDRIA4_CAT( libandria4_exceptions_typekeynum_, type ): \
				{ body ; } break; }
	
	/* For a "finally" macro, the case should be NEGATIVE, because */
	/*  negatives should only be used for special stuff. */
	
	
	
	
	
		/* This should ideally have hidden visibility. Or should it? */
	thread_local libandria4_exceptions_runctx *libandria4_exceptions_curstate;
	
		/* This is for debug reference. */
	struct
	{
		const char *date, *time;
		const char *langname;
		const long lang_ver;
		const char *filetime;
		
	} libandria4_exceptions_compiletimeinfo =
		{
			0,
			__DATE__, __TIME__,
	#if defined( __cplusplus )
			"C++",
			__cplusplus,
	#elif defined( __STDC_VERSION__ )
			"C",
			__STDC_VERSION__,
	#else
			"Unknown",
			0,
	#endif
				/* This appears common to Clang, GCC, & MSVC. */
			__TIMESTAMP__
		};
	
	
	
	
	
	
	
	/* Ending basic / exceptions.h */
	
#endif
