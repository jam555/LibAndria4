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

#ifndef LIBANDRIA4_PRIMITIVE_EXCEPTIONS_H
 #define LIBANDRIA4_PRIMITIVE_EXCEPTIONS_H
	
	#error "LIBANDRIA4_EXCEPTIONS_CATCH_INNER() can't work right, because\n"
	#error "it's use of setjump() does too much, specifically we want it to\n"
	#error "work a little more like goto instead, by altering the size of the\n"
	#error "current stack FRAME instead of setting the size of the TOTAL\n"
	#error "stack, and that requires a different set of function than\n"
	#error "setjump() and longjump().\n"
	#error "\n"
	
	
	
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
	
		/* "Prime the pump," so to speak. */
	LIBANDRIA4_NULLMACRO( __COUNTER__ );
	
	
	
	#include <setjmp.h>
	
	
	
		/* The only "correct" types for exceptions are those handed to */
		/*  LIBANDRIA4_EXCEPTIONS_TYPE(), which will be allocated at link-time */
		/*  instead of needing to be dynamically allocated. To the extent */
		/*  possible, they are meant to overlay each other, so don't bother */
		/*  hoping for all of them to be simultaqneously accessible. */
		/* This is technically wrong. */
	
		/* Pseudo-code, fix this up. */
	/*
		LIBANDRIA4_EXCEPTIONS_MAKESECTION_R(),
		LIBANDRIA4_EXCEPTIONS_MAKESECTION_RW(),
		LIBANDRIA4_EXCEPTIONS_MAKESECTION_X(),
		and LIBANDRIA4_EXCEPTIONS_SECTION_VAR() were defined here, but now are in
		commonmacros.h with the "_EXCEPTIONS" part removed from all of the names.
		Adjust code appropriately.
	*/
	#include "commonmacros.h"
	#include "simpleops.h"
	
	#define LIBANDRIA4_EXCEPTIONVAR( tag_str, typedef_name, var_name ) \
		LIBANDRIA4_MAKESECTION_RW( \
			tag_str \
			".LIBANDRIA4_EXCEPTIONS_TYPEOVR." \
			LIBANDRIA4_STRINGIFY( typedef_name ) ); \
		LIBANDRIA4_SECTION_VAR( thread, \
			".LIBANDRIA4_EXCEPTIONS_TYPEOVR." LIBANDRIA4_STRINGIFY( typedef_name ), \
			typedef_name, var_name );
	
	
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
	LIBANDRIA4_MAKESECTION_R( "LIBANDRIA4_EXCEPTIONS_HANDLER_TABLES" );
		/* For the pre-allocated exception-data instances. */
	LIBANDRIA4_MAKESECTION_R( "LIBANDRIA4_EXCEPTIONS_TYPEOVR" );
	
	
	
		/* The per-"try" datatype. */
	typedef struct libandria4_exceptions_lexctx libandria4_exceptions_lexctx;
		/* Per-"catch" data. */
	typedef struct libandria4_exceptions_handler libandria4_exceptions_handler;
		/* Nesting-tracker data. Gets instantiated on the stack. */
	typedef struct libandria4_exceptions_runctx libandria4_exceptions_runctx;
		/* This needs to be instantiated in a .c file. */
	extern thread libandria4_exceptions_runctx libandria4_exceptions_now;
		/* Set this to null, always! */
	extern thread libandria4_exceptions_runctx * const libandria4_exceptions_prev;
	
	
	#include <threads.h>
	
	
	struct libandria4_exceptions_runctx
	{
		libandria4_exceptions_lexctx *here;
		unsigned progress;
		jmp_buf jb;
		
	};
		/* Note that this MUST ALWAYS be invoked inside a LIBANDRIA4_EXCEPTIONS_TRY() macro. */
	#define LIBANDRIA4_EXCEPTIONS_CATCH( excep_type, ... ) \
		LIBANDRIA4_EXCEPTIONS_CATCH_INNER( __COUNT__, excep_type, __VA_ARGS__ )
	#define LIBANDRIA4_EXCEPTIONS_CATCH_INNER( num, excep_type, ... ) \
		static const int LIBANDRIA4_CONCAT( libandria4_exceptions_types_, excep_type ) = num; { \
			if( libandria4_exceptions_progress < num ) { \
				static libandria4_exceptions_runctx \
					libandria4_exceptions_runctx_herectx = \
						{ &libandria4_exceptions_here, num, { 0 } }; \
				LIBANDRIA4_SECTION_VAR( thread, \
					".LIBANDRIA4_EXCEPTIONS_TYPEOVR." LIBANDRIA4_STRINGIFY( excep_type ) ".catcher", \
					excep_type, libandria4_exceptions_thisexception ); \
				switch( setjmp( &( libandria4_exceptions_runctx_herectx.jb ) != 0 ) { \
					case 1: { \
							__VA_ARGS__; }; \
					case 0: break; } \
				if( libandria4_exceptions_progress < num ) { \
					libandria4_exceptions_progress = num; } } }
	#define LIBANDRIA4_EXCEPTIONS_THROW( excep_type, ... ) \
		LIBANDRIA4_EXCEPTIONS_THROW_INNER( excep_type, __VA_ARGS__ )
	#define LIBANDRIA4_EXCEPTIONS_THROW_INNER( excep_type, ... ) \
		{ \
			LIBANDRIA4_SECTION_VAR( thread, \
				".LIBANDRIA4_EXCEPTIONS_TYPEOVR." LIBANDRIA4_STRINGIFY( excep_type ) ".thrower", \
				excep_type, libandria4_exceptions_thisexception ); \
			libandria4_exceptions_thisexception = (excep_type){ __VA_ARGS__ }; \
			??? ; }
	#error "LIBANDRIA4_EXCEPTIONS_THROW_INNER() needs to actually throw somehow,\n"
	#error "all it does right now is set the exception value in preperation for\n"
	#error "the throw. It also needs to do something to allow preemption-handlers\n"
	#error "to exist... which they currently don't.\n"
	#error "At any rate, targeting the correct catch() must somehow involve the\n"
	#error "variable named\n"
	#error "  LIBANDRIA4_CONCAT( libandria4_exceptions_types_, excep_type ),\n"
	#error "which exists solely for that purpose.\n"
	#error "\n"
	
	#error "Also, we need a rethrow macro.\n"
	#error "\n"
	
	#error "Further, we should make a finally macro.\n"
	#error "\n"
	
	
	struct libandria4_exceptions_lexctx
	{
		const char *filename, *funcname;
		const int line;
		libandria4_exceptions_handler *handlers;
	};
		/* Note: this DOES NOT support nexting try blocks. */
	#define LIBANDRIA4_EXCEPTIONS_TRY( body ) \
		LIBANDRIA4_EXCEPTIONS_TRY_INNER( __COUNTER__, body )
	#define LIBANDRIA4_STRINGIFY( a ) LIBANDRIA4_INNER_STRINGIFY( a )
	#define LIBANDRIA4_INNER_STRINGIFY( a ) #a
	#define LIBANDRIA4_EXCEPTIONS_TRY_INNER( num, ... )
		{
			static int libandria4_exceptions_progress = 0;
			LIBANDRIA4_SECTION_VAR(
				static,
				"LIBANDRIA4_EXCEPTIONS_HANDLER_TABLE." LIBANDRIA4_STRINGIFY( num ),
				libandria4_exceptions_handler[],
				libandria4_exceptions_handlers
			);
			static libandria4_exceptions_lexctx libandria4_exceptions_here =
				{ __FILE__, __func__, __LINE__, &libandria4_exceptions_handler };
			
				/* Stuff for this run. */
			libandria4_exceptions_runctx * const libandria4_exceptions_prev =
				&libandria4_exceptions_now;
			libandria4_exceptions_runctx libandria4_exceptions_generic = { 0 };
			
			__VA_ARGS__;
		}
	#error "This needs to be reviewed more.\n"
	#error "\n"
	
	
	
	
	
	
	
	
	#error "Heavily review this, among other things it assumes a the\n"
	#error "use of enums which won't be used anymore.\n"
	#error "\n"
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
	
	#error "This compile-time info, at least, should ABSOLUTELY\n"
	#error "be carried forward.\n"
	#error "\n"
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
	
#endif
/* Ending primitive exceptions.h */
