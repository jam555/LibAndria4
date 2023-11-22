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

#ifndef LIBANDRIA4_BASIC_MONADS_H
# define LIBANDRIA4_BASIC_MONADS_H
	
	/* This is some untested monadic C code. Monads are used for several */
	/*  things, but in particularly are the latest fad for errors in */
	/*  functional programming. */
	/* Also, they're a good toolkit for returns in C. */
	
	
	
	/* For when you want to support null-or-data. Acts as if C supported */
	/*  functions returning one of two types, one of those being (void), and */
	/*  the other being whatever your actual type is. If you want (void), */
	/*  then use *_BUILDNOTHING() to get the value to return, otherwise use */
	/*  *_BUILDJUST(). Notice that *_BUILDNOTHING() doesn't build a */
	/*  pointer-to-void, it just returns an actual absence of data. */
	/* Note that you should really build wrappers around these if you're */
	/*  actually going to use them. Also, you should be able to assign your */
	/*  "nothing" value to a static & just use that if you want to. */
	
		/* This should be specialized for packing purposes. */
	#define LIBANDRIA4_MONAD_MAYBE_BUILDTYPE_DEFINITION( name, type ) \
		struct name { type val; unsigned char is_valid; };
	#define LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( name, type ) \
		typedef struct name name; \
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE_DEFINITION( name, type );
	
		/* These produce the actual values. */
	#define LIBANDRIA4_MONAD_MAYBE_BUILDJUST( name, type, val ) \
		( (name){ (type)( val ), 0 } )
	#define LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( name, type ) \
		( (name){ (type){ 0 }, 1 } ) \
		/* C allows compound-literals for scalar types too, so this is fine. */
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_MONAD_MAYBE_BODYMATCH( var, match, otherwise ) \
		if( ( var ).is_valid ) { match( ( var ).val ); } else { otherwise(); }
	#define LIBANDRIA4_MONAD_MAYBE_EXPRMATCH( var, match, otherwise ) \
		( ( ( var ).is_valid ) ? ( match( ( var ).val ) ) : ( otherwise() ) )
		/* I'm of mixed views on this, but the "Null Conundrum" video by */
		/*  Zoran Horvat made mention of it around minute 13, and I CAN see */
		/*  the utility of it, so I've added it. */
	#define LIBANDRIA4_MONAD_MAYBE_REDUCE( type, var, alt ) \
		( ( ( var ).is_valid ) ? ( ( var ).val ) : (type)( alt ) )
	
		/* Like the *MATCH() stuff above, but intended for chaining. I */
		/*  honestly don't know if the re-ordering does anything useful, but */
		/*  the change in result type could be useful. */
	#define LIBANDRIA4_MONAD_MAYBE_EXPRCHAIN( name, type, var, match ) \
		( ( !( ( var ).is_valid ) ) \
			? ( LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( name, type ) ) \
			: ( match )( ( var ).val ) )
	
		/* Convenience wrappers. See the *_EITHER_* versions for the */
		/*  involved concept. Remember that the "type" is in both cases the */
		/*  SAME type. */
	#define LIBANDRIA4_MONAD_MAYBE_RETURNLEFT( name, type, val ) \
		return( LIBANDRIA4_MONAD_MAYBE_BUILDJUST( name, type, ( (type)( val ) ) ) );
	#define LIBANDRIA4_MONAD_MAYBE_RETURNRIGHT( name, type ) \
		return( LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( name, type ) );
	
	
	
	/* Full-blown two-types-in-one! Except they can actually be the same */
	/*  type with different meanings as well. */
	
		/* This should ALSO be specialized for packing purposes. */
		/* This should probably do the "struct type type;" thing directly... */
	#define LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION( name, typea, typeb ) \
		struct name \
			{ union{ typea a; typeb b; } val; \
				unsigned char is_b; };
	#define LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name, typea, typeb ) \
		typedef struct name name; \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE_DEFINITION( name, typea, typeb );
	
		/* These produce the actual values. */
	#define LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name, typea, val ) \
		( (name){ { .a = (typea)( val ) }, 0 } )
	#define LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name, typeb, val ) \
		( (name){ { .b = (typeb)( val ) }, 1 } )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_MONAD_EITHER_BODYMATCH( var, matcha, matchb ) \
		if( !( (var).is_b ) ) { \
			matcha( (var).val.a ); \
		} else { \
			matchb( (var).val.b ); }
	#define LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var, matcha, matchb ) \
		( ( !( (var).is_b ) ) \
			? ( matcha( (var).val.a ) ) \
			: ( matchb( (var).val.b ) ) )
		/* Chaining doesn't make much sense without a type change; usually */
		/*  a maybe monad is the correct choice. */
	#define LIBANDRIA4_MONAD_EITHER_EXPRCHAIN( var, matcha, buildalt ) \
		( !( ( var ).is_b ) \
			? ( matcha( (var).val.a ) ) \
			: ( buildalt( (var).val.b ) ) )
		/* Unlike for maybe, the signature should match exprmatch, so */
		/*  we just wrap it. */
	#define LIBANDRIA4_MONAD_EITHER_REDUCE( var,  reducea, reduceb ) \
		LIBANDRIA4_MONAD_EITHER_EXPRMATCH( var,  reducea, reduceb )
	
		/* Convenience wrappers. Intended to convert between differing */
		/*  *_EITHER_* wrappers, when the return of one function returning */
		/*  an either-type can be DIRECTLY derived from an either-type */
		/*  returned by one of it's own internal calls. */
	#define LIBANDRIA4_MONAD_EITHER_RETURNLEFT( name, typea, val ) \
		return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( \
			name, typea, ( (typea)( val ) ) ) );
	#define LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( name, typeb, val ) \
		return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( \
			name, typeb, ( (typeb)( val ) ) ) );
	#define LIBANDRIA4_MONAD_EITHER_RETURN_A( name, typea, val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNLEFT( name, typea, val )
	#define LIBANDRIA4_MONAD_EITHER_RETURN_B( name, typeb, val ) \
		LIBANDRIA4_MONAD_EITHER_RETURNRIGHT( name, typeb, val )
	
#endif
/* End libandria4 basic monads.h */
