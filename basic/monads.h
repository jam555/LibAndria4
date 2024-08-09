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
	
	
	
	/* Either, but with three types instead of one! Also, the name is a pun. */
	
		/* This should ALSO be specialized for packing purposes. */
		/* This should probably do the "struct type type;" thing directly... */
	#define LIBANDRIA4_MONAD_TRIETHER_BUILDTYPE_DEFINITION( name, typea, typeb, typec ) \
		struct name \
			{ union{ typea a; typeb b;, typec c; } val; \
				unsigned char val_id; };
	#define LIBANDRIA4_MONAD_TRIETHER_BUILDTYPE( name, typea, typeb, typec ) \
		typedef struct name name; \
		LIBANDRIA4_MONAD_TRIETHER_BUILDTYPE_DEFINITION( name, typea, typeb, typec );
	
		/* These produce the actual values. */
	#define LIBANDRIA4_MONAD_TRIETHER_BUILDLEFT( name, typea, val ) \
		( (name){ { .a = (typea)( val ) }, 1 } )
	#define LIBANDRIA4_MONAD_TRIETHER_BUILDCENTER( name, typeb, val ) \
		( (name){ { .b = (typeb)( val ) }, 2 } )
	#define LIBANDRIA4_MONAD_TRIETHER_BUILDRIGHT( name, typec, val ) \
		( (name){ { .c = (typec)( val ) }, 3 } )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_MONAD_TRIETHER_BODYMATCH( var, matcha, matchb, matchc ) \
		if( ( (var).val_id == 1 ) ) { \
			matcha( (var).val.a ); \
		} else if( ( (var).val_id == 2 ) ) { \
			matchb( (var).val.b ); \
		} else { \
			matchc( (var).val.c ); }
	#define LIBANDRIA4_MONAD_TRIETHER_EXPRMATCH( var, matcha, matchb, matchc ) \
		( ( ( (var).val_id == 1 ) \
			? ( matcha( (var).val.a ) ) \
			: ( ( (var).val_id == 2 ) \
				? ( matchb( (var).val.b ) ) \
				: ( matchc( (var).val.c ) ) ) ) )
		/* Chaining doesn't make much sense without a type change; usually */
		/*  a maybe monad is the correct choice. */
	#define LIBANDRIA4_MONAD_TRIETHER_EXPRCHAIN( var, matcha, buildb, buildc ) \
		( ( (var).val_id == 1 ) \
			? ( matcha( (var).val.a ) ) \
			: ( (var).val_id == 2 ) \
				? ( buildb( (var).val.b ) ) \
				: ( buildc( (var).val.c ) ) )
		/* Unlike for maybe, the signature should match exprmatch, so */
		/*  we just wrap it. */
	#define LIBANDRIA4_MONAD_TRIETHER_REDUCE( var,  reducea, reduceb, reducec ) \
		LIBANDRIA4_MONAD_TRIETHER_EXPRMATCH( var,  reducea, reduceb, reducec )
	
		/* Convenience wrappers. Intended to convert between differing */
		/*  *_EITHER_* wrappers, when the return of one function returning */
		/*  an either-type can be DIRECTLY derived from an either-type */
		/*  returned by one of it's own internal calls. */
	#define LIBANDRIA4_MONAD_TRIETHER_RETURNLEFT( name, typea, val ) \
		return( LIBANDRIA4_MONAD_TRIETHER_BUILDLEFT( \
			name, typea, ( (typea)( val ) ) ) );
	#define LIBANDRIA4_MONAD_TRIETHER_RETURNCENTER( name, typeb, val ) \
		return( LIBANDRIA4_MONAD_TRIETHER_BUILDCENTER( \
			name, typeb, ( (typeb)( val ) ) ) );
	#define LIBANDRIA4_MONAD_TRIETHER_RETURNRIGHT( name, typec, val ) \
		return( LIBANDRIA4_MONAD_TRIETHER_BUILDRIGHT( \
			name, typec, ( (typec)( val ) ) ) );
	#define LIBANDRIA4_MONAD_TRIETHER_RETURN_A( name, typea, val ) \
		LIBANDRIA4_MONAD_TRIETHER_RETURNLEFT( name, typea, val )
	#define LIBANDRIA4_MONAD_TRIETHER_RETURN_B( name, typeb, val ) \
		LIBANDRIA4_MONAD_TRIETHER_RETURNCENTER( name, typeb, val )
	#define LIBANDRIA4_MONAD_TRIETHER_RETURN_C( name, typec, val ) \
		LIBANDRIA4_MONAD_TRIETHER_RETURNRIGHT( name, typec, val )
	
	
	
	/* The bi-tuplic monad is metaphoroically two maybes in a trenchcoat. */
	
	#define LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE_DEFINITION( name, typea, typeb ) \
		struct name { typea left; typeb right; unsigned char valid_flags; };
	#define LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE( name, typea, typeb ) \
		typedef struct name name; \
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE_DEFINITION( name, typea, typeb );
	
	#define LIBANDRIA4_MONAD_BITUPLIC_BUILDNOTHING( name, typea, typeb ) \
		( (name){ (typea){ 0 }, (typeb){ 0 }, 0 } ) \
		/* C allows compound-literals for scalar types too, so this is fine. */
	#define LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTLEFT( name, typea, typeb, val ) \
		( (name){ (typea)( val ), (typeb){ 0 }, 1 } )
	#define LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( name, typea, typeb, val ) \
		( (name){ (typea){ 0 }, (typeb)( val ), 2 } )
	#define LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTBOTH( name, typea, typeb, vala, valb ) \
		( (name){ (typea)( vala ), (typeb)( valb ), 3 } )
	
		/* The *BODY* version takes statements, *EXPR* takes expressions. */
	#define LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( var, matchleft, matchright, onempty ) \
		if( ( var ).valid_flags <= 0 ) { onempty(); } \
		else { \
			if( ( var ).valid_flags & 1 ) { matchleft( ( var ).left ); } \
			if( ( var ).valid_flags & 2 ) { matchright( ( var ).right ); } }
	#define LIBANDRIA4_MONAD_BITUPLIC_EXPRMATCH( var, matchleft, matchright, onempty ) \
		( \
				( ( ( var ).valid_flags & 1 ) ? ( matchleft( ( var ).left ), 1 ) : 0 ) + \
				( ( ( var ).valid_flags & 2 ) ? ( matchright( ( var ).right ), 1 ) : 0 ) > 0 \
			? 1 : onempty() )
		/* Named after a biological process. */
		/* The rough equivalent of *_MAYBE_*'s *_REDUCE(). maya & mayb */
		/*  are the names of the desired "maybe" types, typea and typeb */
		/*  are the data types. reducer() should GENERALLY return an */
		/*  alttype value. */
	#define LIBANDRIA4_MONAD_BITUPLIC_MEIOSIC( maya, typea, mayb, typeb,  var,  reducer, alttype, altval ) \
		( ( ( var ).valid_flags ) \
			? ( reducer( \
				( ( ( var ).valid_flags & 1 ) ? \
					( LIBANDRIA4_MONAD_MAYBE_BUILDJUST( maya, typea, ( var ).left ) ) : \
					( LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( maya, typea ) ) ), \
				( ( ( var ).valid_flags & 2 ) ? \
					( LIBANDRIA4_MONAD_MAYBE_BUILDJUST( mayb, typeb, ( var ).right ) ) : \
					( LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( mayb, typeb ) ) ) ) \
			: (alttype)( altval ) )
	
	#define LIBANDRIA4_MONAD_BITUPLIC_RETURNNOTHING( name, typea, typeb ) \
		return( LIBANDRIA4_MONAD_BITUPLIC_BUILDNOTHING( name, typea, typeb ) );
	#define LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( name, typea, typeb, val ) \
		return( LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTLEFT( name, typea, typeb, ( (typea)( val ) ) ) );
	#define LIBANDRIA4_MONAD_BITUPLIC_RETURNRIGHT( name, typea, typeb, val ) \
		return( LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( name, typea, typeb, ( (typeb)( val ) ) ) );
	#define LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( name, typea, typeb, vala, valb ) \
		return( LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTBOTH( name, typea, typeb, ( (typea)( vala ) ), ( (typeb)( valb ) ) ) );
	
	
	
	
	
	/* The following two monads are for reference-counted stuff. So, */
	/*  essentially smart-pointers, to what extent C can support such. */
	
	/* Note: The two systems have been moved over to using libandria4_memfuncs_t{} */
	/*  pointers, so all references to other memory management can now be deleted, */
	/*  if they even exist. */
	
	
	/* RefCounted: a monad to eximplify reference-counted resources. */
	
	/* Note that LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE_DEFINITION() (which */
	/*  shouldn't actually get used) and LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE() */
	/*  are used to define the data structure, while */
		/* LIBANDRIA4_MONAD_REFCOUNTED_DEFINEIMPLEMENTATION() */
	/*  is used to define a few implementation functions: the first set goes in */
	/*  headers, while *_DEFINEIMPLEMENTATION() goes in .c files. */
	/* The *_EXPR* macros equate to expressions, while the *_BODY* macros equate */
	/*  to block-statements. */
	/* LIBANDRIA4_MONAD_REFCOUNTED_EXPRINIT( name, pointer,  value, aux,  onbad, badalloc, badata ) */
		/* result will be either int (on success), or the result of onbad(). */
		/* onbad : Mandatory, signature: ( name*, valuetype, void* ) ; Used only */
		/*  in the macro and when init() fails. */
		/* badalloc : Can be null, signature: */
			/* void (*badalloc)( void*,  name**, valuetype, void* ) */
		/*  ; Used only when init() cannot allocate memory, the first value will */
		/*  be badata, the second a pointer to the provided pointer, the third */
		/*  and fourth are the contents of the name{} instance. */
		/* badata : Can be null, signature: void* */
	/* LIBANDRIA4_MONAD_REFCOUNTED_EXPRREINIT( pointer,  value, aux,  receiver, recdata, resvar ) */
		/* result will be the value of ->auxiliary (void*), and means essentially */
		/*  nothing. */
		/* receiver : Mandatory, signature: ( recdata, valuetype, void* ) ; The */
		/*  first argument is whatever receiver() is supplied along with, the */
		/*  second is the value to be replaced, the third is the auxiliary data */
		/*  to be replaced. */
		/* resvar : Mandatory, the type is whatever receiver returns, because */
		/*  that's what gets stored inside it. */
	/* LIBANDRIA4_MONAD_REFCOUNTED_EXPRREDUCE( pointer,  func, badptr ) */
		/* result will be the result of func() if pointer isn't null, else the */
		/*  result of badptr. */
		/* func : Mandatory, signature: ( void*, valuetype ) ; First arg is */
		/*  pointer->auxiliary, second is pointer->val. */
		/* badptr : Mandatory, signature: ( name* ) ; Arg is pointer. */
	/* LIBANDRIA4_MONAD_REFCOUNTED_BODYATTEND( name, pointer,  onbad, onsucc ) */
		/* Block statement, so no result. */
		/* onbad : Mandatory, no arguments, gets used by the internal */
		/*  *_BODYMATCH() invocation. */
		/* onsucc : Mandatory, signature: ( name** ) */
	/* LIBANDRIA4_MONAD_REFCOUNTED_BODYNEGLECT( name, pointer,  onbad, onsucc, ondead ) */
		/* Block statement, so no result. */
		/* onbad : Mandatory, no arguments, gets used by the internal */
		/*  *_BODYMATCH() invocation. */
		/* onsucc : Mandatory, signature: ( name** ) */
		/* ondead : Mandatory, signature: ( name** ) */
	
		/* The "auxiliary" member exists because there might be important */
		/*  back-end stuff that needs separate tracking. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE_DEFINITION( name, valuetype ) \
		struct name \
			{ uintptr_t ref_count; \
				void *auxiliary; \
				valuetype val; };
	#define LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE( name, valuetype ) \
		typedef struct name name; \
		LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE_DEFINITION( name, valuetype ); \
		typedef void (*name##_onbadfp)( void*,  name**, valuetype, void* );
	
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_INIT( name, valuetype ) \
		int name##_init( libandria4_memfuncs_t *mf,  name **ptr, \
			valuetype val, void *aux, \
			name##_onbadfp badalloc, void *badata ) \
		{ if( ptr && !( *ptr ) ) { LIBANDRIA4_MEMFUNCS_T_PTR_BLOCKREQUIRE( mf ); \
				if( !( mf->alloc ) ) { if( badalloc ) { badalloc( badata,  ptr,  val, aux ); } \
					return( -2 ); } \
				void *a = (void*)0; \
				libandria4_ptrresult ptrres = (mf->alloc)( mf->data, sizeof( name ) ); \
				LIBANDRIA4_PTRRESULT_BODYMATCH( ptrres, \
					LIBANDRIA4_OP_SETa, LIBANDRIA4_NULL_MACRO ) } \
				if( a ) { \
					*ptr = (name*)a; ( *ptr )->ref_count = 1; \
					( *ptr )->auxiliary = aux; ( *ptr )->val = val; } \
				else { if( badalloc ) { badalloc( badata,  ptr,  val, aux ); } \
					return( -3 ); } \
				return( 1 ); } \
			return( -1 ); }
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_ATTEND( name,  onattend ) \
		libandria4_maybeint name##_attend( name **ptr ) { \
			if( ptr && *ptr && ( *ptr )->ref_count =< 1 ) { \
				++( ( *ptr )->ref_count ); \
				onattend( *ptr, ( *ptr )->auxiliary, ( *ptr )->val ); \
				LIBANDRIA4_MAYBEINT_RETURNJUST( 1 ); } \
			LIBANDRIA4_MAYBEINT_RETURNNOTHING(); }
		/* Returns "nothing" for bad args, 1 for normal success, 2 for deallocating success. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_NEGLECT( name,  onneglect, ondie ) \
		libandria4_maybeint name##_neglect( libandria4_memfuncs_t *mf,  name **ptr ) { \
			if( ptr && ( *ptr )->ref_count =< 1 ) { int res = 1; \
				--( ( *ptr )->ref_count ); \
				onneglect( *ptr, ( *ptr )->auxiliary, ( *ptr )->val ); \
				if( ( *ptr )->ref_count < 1 ) { \
					ondie( ( *ptr )->auxiliary, ( *ptr )->val ); \
					if( mf->dealloc ) { return( (mf->dealloc)( mf->data, *ptr ) ); } \
					res = 2; } \
				*ptr = ((name)*)0; \
				LIBANDRIA4_MAYBEINT_RETURNJUST( res ); } \
			LIBANDRIA4_MAYBEINT_RETURNNOTHING(); }
	
	
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_BAREDECL( name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE( name, valuetype ); \
		int name##_init( libandria4_memfuncs_t *mf,  name **ptr,  valuetype val, void *aux, \
			name##_onbadfp badalloc, void *badata ); \
		libandria4_maybeint name##_attend( name **ptr ); \
		libandria4_maybeint name##_neglect( libandria4_memfuncs_t *mf,  name **ptr );
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_BAREIMPL( name, valuetype,  onattend, onneglect, ondie ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_INIT( name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_ATTEND( name,  onattend ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_NEGLECT( name,  onneglect, ondie )
		/* Start tracking. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_BARE_EXPRINIT( name, pointer, memfuncs_ptr,  value, aux,  onfull, badalloc, badata ) \
		( !(pointer) ? \
			name##_init( ( memfuncs_ptr ), &(pointer),  (value), (aux), &(badalloc), (badata) ) : \
			onfull( pointer,  value, aux ) )
		/* Drop reference. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_BARE_BODYNEGLECT( name, pointer, memfuncs_ptr,  onbad, onsucc, ondead ) \
		{ name ** name##_ptr = &(pointer); \
			libandria4_maybeint name##res = name##_neglect( ( memfuncs_ptr ),  name##_ptr ); \
			int a = 0;   LIBANDRIA4_MAYBEINT_BODYMATCH( name##res,  LIBANDRIA4_OP_SETa, onbad ); \
			if( a == 1 ) { onsucc( name##_ptr ); } \
			else { ondead( name##_ptr ); } }
	
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDDECL( name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE( name, valuetype ); \
		int name##_init( name **ptr,  valuetype val, void *aux, \
			name##_onbadfp badalloc, void *badata ); \
		libandria4_maybeint name##_attend( name **ptr ); \
		libandria4_maybeint name##_neglect( name **ptr );
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDIMPL( name, valuetype, memfuncs_ptr,  onattend, onneglect, ondie ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_INIT( libandria4_definer_##name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_NEGLECT( libandria4_definer_##name,  onneglect, ondie ) \
		int name##_init( name **ptr,  valuetype val, void *aux,  name##_onbadfp badalloc, void *badata ) \
				{ return( libandria4_definer_##name##_init( ( memfuncs_ptr ),  ptr,  val, aux, badalloc, badata ) ); } \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_ATTEND( name,  onattend ) \
		libandria4_maybeint name##_neglect( name **ptr ) { return( name##_neglect( ( memfuncs_ptr ),  ptr ) ); }
		/* Start tracking. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_WRAPPED_EXPRINIT( name, pointer,  value, aux,  onfull, badalloc, badata ) \
		( !(pointer) ? \
			name##_init( &(pointer),  (value), (aux), &(badalloc), (badata) ) : \
			onfull( pointer,  value, aux ) )
		/* Drop reference. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_WRAPPED_BODYNEGLECT( name, pointer,  onbad, onsucc, ondead ) \
		{ name ** name##_ptr = &(pointer);  libandria4_maybeint name##res = name##_neglect( name##_ptr ); \
			int a = 0;   LIBANDRIA4_MAYBEINT_BODYMATCH( name##res,  LIBANDRIA4_OP_SETa, onbad ); \
			if( a == 1 ) { onsucc( name##_ptr ); } \
			else { ondead( name##_ptr ); } }
	
		/* This needs to be paired with a LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDDECL() invocation. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_STDIMPL( name, valuetype,  onattend, onneglect, ondie ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDIMPL( \
			name, valuetype, &libandria4_stdmemfuncs, \
			onattend, onneglect, ondie )
	
	
		/* Restart tracking. No cleanup is done, so if cleanup is needed then receiver() needs to do it. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_EXPRREINIT( pointer, memfuncs_ptr,  value, aux,  receiver, recdata, resvar ) \
		( (resvar) = receiver( recdata, (pointer)->val, (pointer)->auxiliary ), \
			(pointer)->val = (value), (pointer)->auxiliary = aux )
	#define LIBANDRIA4_MONAD_REFCOUNTED_EXPRREDUCE( pointer,  func, badptr ) \
		( !!(pointer) ? ( func( (pointer)->auxiliary, (pointer)->val ) ) : ( badptr( pointer ) ) )
		/* Add reference. */
	#define LIBANDRIA4_MONAD_REFCOUNTED_BODYATTEND( name, pointer,  onbad, onsucc ) \
		{ name ** name##_ptr = &(pointer);  libandria4_maybeint name##res = name##_attend( name##_ptr ); \
			int a = 0;   LIBANDRIA4_MAYBEINT_BODYMATCH( name##res,  LIBANDRIA4_OP_SETa, onbad ); \
			if( a == 1 ) { onsucc( name##_ptr ); } }
	
	
	/** !!!NOTE TO SELF!!! **/
		/* I have the reference-counting stuff, so go write a standard wrapper for FILE* for it! */
	
	/* RefPointer: a monad to wrap around RefCounted. */
	
	/* RefPointer (obviously) is a pointer, and as close as I can get */
	/*  to a smart pointer in C. These four macro-functions: */
		/** _BODYINIT(), *_BODYSET(), *_EXPRAPPLY(), and *_BODYDEINIT() */
	/*  are THE four interaction routes for this monad. Once you've */
	/*  defined the thing, these are the only ways that it should be */
	/*  interacted with. */
	/* *_BODYINIT() is the equivalent of a C++ constructor. */
	/* *_BODYSET() allows you to redirect the pointer. */
	/* *_EXPRAPPLY() lets you actually use the thing being tracked- you */
	/*  should generally supply a macro function instead of a run-time */
	/*  function. */
	/* *_BODYDEINIT() is the equivalent of a C++ destructor. */
	/* LIBANDRIA4_MONAD_REFPOINTER_BUILDTYPE() should be used in header */
	/*  files, and LIBANDRIA4_MONAD_REFPOINTER_DEFINEIMPLEMENTATION() */
	/*  in .c files. */
	/* In general, you should wrap the "interaction routes" in helper */
	/*  macros (or even functions) with as few arguments as possible: */
	/*  for example, *_BODYINIT()'s failattend() should in general only */
	/*  report an error over your chosen error reporting route, so it */
	/*  in general SHOULD NOT be exposed through the interfaces you */
	/*  directly use. Properly form your wrappers! */
	
	#define LIBANDRIA4_MONAD_REFPOINTER_BUILDTYPE_DEFINITION( name ) \
		struct name { name##_counttype *counted; };
	#define LIBANDRIA4_MONAD_REFPOINTER_BUILDTYPE( name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_BUILDTYPE( name##_counttype, valuetype ); \
		typedef struct name name; \
		LIBANDRIA4_MONAD_REFPOINTER_BUILDTYPE_DEFINITION( name );
	
	
	/* This is a summation of the arguments to the *_*IMPL() macros: */
		/* name: The name of the ref-pointer type; the ref-counter type's */
			/* name is the derived "name##_counttype". */
		/* valuetype: The type of value that you want the entire system to */
			/* store. */
		/* memfuncs_ptr: A pointer to a lib4_memfuncs_t instance that */
			/* contains function pointers to various memory management */
			/* functions. The stereotypical value is */
				/* &libandria4_stdmemfuncs, */
			/* which is populated with simple wrappers of the standard C */
			/* functions like malloc(). */
		/* onattend: A function with the signature */
				/* void func( void*, name##_counttype* ) */
			/* that is called when the reference count is successfully */
			/* increased. It exists solely for debugging/logging, and can */
			/* safely be set to e.g. LIBANDRIA4_NULL_MACRO. */
		/* onneglect: A function with the same signature as onattend, but */
			/* called when the reference count is successfully decreased. */
			/* It exists solely for debugging/logging, and can safely be */
			/* e.g. LIBANDRIA4_NULL_MACRO. */
		/* ondie: As onneglect, but only called when the reference count */
			/* has reached 0 and thus the name##_counttype instance is */
			/* about to be handed to the deallocator. Never a replacement */
			/* for onneglect, and onneglect will always be called first if */
			/* ondie will be called at all. */
	/* Various implementation macros only take some of these arguments. */
	/*  "name", "valuetype", and "ondie" are universally used, the others */
	/*  are often hidden by wrapper layers. */
	/* LIBANDRIA4_MONAD_REFPOINTER_COMMONIMPLEMENTATION() is probably the */
	/*  best for ordinary usages. */
	
	#define LIBANDRIA4_MONAD_REFPOINTER_DEFINE_BAREDECL( name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_BAREDECL( name##_counttype, valuetype ); \
		typedef struct name name; \
		LIBANDRIA4_MONAD_REFPOINTER_BUILDTYPE_DEFINITION( name );
	#define LIBANDRIA4_MONAD_REFPOINTER_DEFINE_BAREIMPL( name, valuetype,  onattend, onneglect, ondie ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_BAREIMPL( \
			name##_counttype, valuetype,  onattend, onneglect, ondie )
	#define LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYINIT( name, var, innerval, aux, memfuncs_ptr,  failinit, badalloc, badata ) \
		{ name##_counttype ** name##_ptr = &( (var).counted ); \
			LIBANDRIA4_MONAD_REFCOUNTED_BARE_EXPRINIT( name##_counttype, name##_ptr, ( memfuncs_ptr ), \
				innerval, aux,  failinit, badalloc, badata ); }
	#define LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYSET( name, var, valptr, memfuncs_ptr,  failneglect, failattend, succneglect, succattend, ondead ) \
		{ if( (var).counted == (valptr) ) { /* Do nothing. */ ; } \
			else { if( valptr ) { \
					LIBANDRIA4_MONAD_REFCOUNTED_BODYATTEND( \
						name##_counttype, (var).counted,  failattend, succattend ); } \
				if( (var).counted ) { \
					LIBANDRIA4_MONAD_BARE_REFCOUNTED_BODYNEGLECT( \
						name##_counttype, (var).counted, ( memfuncs_ptr ), \
						failneglect, succneglect, ondead ); } \
				(var).counted = valptr; } }
	#define LIBANDRIA4_MONAD_REFPOINTER_BARE_BODYDEINIT( name, var, memfuncs_ptr,  failneglect, succneglect, ondead ) \
		{ name##_counttype * name##_ptr = &( (var).counted ); \
			LIBANDRIA4_MONAD_REFCOUNTED_BODYNEGLECT( name##_counttype, name##_ptr, ( memfuncs_ptr ), \
				failneglect, succneglect, ondead ) }
	
	#define LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDDECL( name, valuetype ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPEDDECL( name##_counttype, valuetype ); \
		typedef struct name name; \
		LIBANDRIA4_MONAD_REFPOINTER_BUILDTYPE_DEFINITION( name );
	#define LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDIMPL( name, valuetype, memfuncs_ptr,  onattend, onneglect, ondie ) \
		LIBANDRIA4_MONAD_REFCOUNTED_DEFINE_WRAPPEDIMPL( \
			name##_counttype, valuetype, memfuncs_ptr,  onattend, onneglect, ondie )
	#define LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYINIT( name, var, innerval, aux,  failinit, badalloc, badata ) \
		{ name##_counttype * name##_ptr = &( (var).counted ); \
			LIBANDRIA4_MONAD_REFCOUNTED_WRAPPED_EXPRINIT( name##_counttype, name##_ptr, \
				innerval, aux,  failinit, badalloc, badata ); }
	#define LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYSET( name, var, valptr,  failneglect, failattend, succneglect, succattend, ondead ) \
		{ if( (var).counted == (valptr) ) { /* Do nothing. */ ; } \
			else { if( valptr ) { \
					LIBANDRIA4_MONAD_REFCOUNTED_BODYATTEND( \
						name##_counttype, (valptr),  failattend, succattend ); } \
				if( (var).counted ) { \
					LIBANDRIA4_MONAD_REFCOUNTED_WRAPPED_BODYNEGLECT( \
						name##_counttype, (var).counted, \
						failneglect, succneglect, ondead ); } \
				(var).counted = valptr; \
				 } }
	#define LIBANDRIA4_MONAD_REFPOINTER_WRAPPED_BODYDEINIT( name, var,  failneglect, succneglect, ondead ) \
		{ name##_counttype * name##_ptr = &( (var).counted ); \
			LIBANDRIA4_MONAD_REFCOUNTED_WRAPPED_BODYNEGLECT( name##_counttype, name##_ptr, \
				failneglect, succneglect, ondead ) }
	
		/* This needs to be paired with a LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDDECL() */
		/*  invocation, and the related operation macros. */
	#define LIBANDRIA4_MONAD_REFPOINTER_DEFINE_STDIMPL( name, valuetype,  onattend, onneglect, ondie ) \
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDIMPL( \
			name, valuetype, &libandria4_stdmemfuncs, \
			onattend, onneglect, ondie )
	
		/* This needs to be paired with a LIBANDRIA4_MONAD_REFPOINTER_DEFINE_WRAPPEDDECL() */
		/*  invocation, and the related operation macros. */
	#define LIBANDRIA4_MONAD_REFPOINTER_COMMONIMPL( name, valuetype,  ondie ) \
		LIBANDRIA4_MONAD_REFPOINTER_DEFINE_STDIMPL( \
			name, valuetype,  LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO, ondie )
	
	
	/* These macros can be used with ANY of the *_IMPL() macros, they're agnostic to those */
	/*  macro's differences. */
	
	#define LIBANDRIA4_MONAD_REFPOINTER_EXPRINIT_NULL( name, var ) \
		(( (var).counted = (name##_counttype*)0, 1 ))
	#define LIBANDRIA4_MONAD_REFPOINTER_EXPRAPPLY( var,  func, onnull ) \
		( (var).counted ? \
			( func( (var).counted->val, (var).counted->auxiliary ) ) : \
			( onnull( var ) ) )
		/* Note that *_neglect() will actually null out our pointer, so */
		/*  there's no need to do it ourselves. */
	
#endif
/* End libandria4 basic monads.h */
