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

#ifndef LIBANDRIA4_BASIC_BINTREES_BINTREES_H
# define LIBANDRIA4_BASIC_BINTREES_BINTREES_H
	
	#include "../simpleops.h"
	#include "../monads.h"
	#include "../commonio.h"
	#include "../commonerrvals.h"
	#include "../nulls.h"
	
	
	
	/* TODO: */
		/* Is there anythiung we want from stdmaybes.h ? What about */
		/*  commonio.h (note: libandria4_commonio_err ?) ? */
	
	
	
		/* Normal style. */
	#define LIBANDRIA4_BINTREES_GETLEFTPTR( name, nodetype, nodeptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			(name),  libandria4_commonio_err, nodetype*,  ( (nodeptr)->left ) )
	#define LIBANDRIA4_BINTREES_GETRIGHTPTR( name, nodetype, nodeptr ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			(name),  libandria4_commonio_err, nodetype*,  ( (nodeptr)->right ) )
	
		/* EternallyConfuzzled style (RIP site, seek on Wayback Machine). */
		/*  There's 6 options in case of more complex node styles */
	#define LIBANDRIA4_BINTREES_GET0PTR( name, nodetype, nodeptr, arrname ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			(name),  libandria4_commonio_err, nodetype*,  ( (nodeptr)->(arrname)[ 0 ] ) )
	#define LIBANDRIA4_BINTREES_GET1PTR( name, nodetype, nodeptr, arrname ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			(name),  libandria4_commonio_err, nodetype*,  ( (nodeptr)->(arrname)[ 1 ] ) )
	#define LIBANDRIA4_BINTREES_GET2PTR( name, nodetype, nodeptr, arrname ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			(name),  libandria4_commonio_err, nodetype*,  ( (nodeptr)->(arrname)[ 2 ] ) )
	#define LIBANDRIA4_BINTREES_GET3PTR( name, nodetype, nodeptr, arrname ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			(name),  libandria4_commonio_err, nodetype*,  ( (nodeptr)->(arrname)[ 3 ] ) )
	#define LIBANDRIA4_BINTREES_GET4PTR( name, nodetype, nodeptr, arrname ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			(name),  libandria4_commonio_err, nodetype*,  ( (nodeptr)->(arrname)[ 4 ] ) )
	#define LIBANDRIA4_BINTREES_GET5PTR( name, nodetype, nodeptr, arrname ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTRIGHT( \
			(name),  libandria4_commonio_err, nodetype*,  ( (nodeptr)->(arrname)[ 5 ] ) )
	
	
	/* This system is built around a requirmnent for several macros that */
	/*  follow the naming pattern of a shared prefix followed by an */
	/*  identifying function name. The names are as follows: */
		/* _STARTTRANSACTION */ /* Mark the start of a transaction. Will */
				/*  often need to be used by the caller instead of the */
				/*  builder macros. Must be nesting-safe. Things like */
				/*  *_GETLEFT must not be required to be called inside */
				/*  of a transaction in order to be successfully used. */
				/*  The transaction tracker must track the actions so */
				/*  that they can be REVERSED, NOT ENACTED. */
			/* _TRANSTRACKPTRTYPE */ /*  */
			/* _GETLEFT */ /*  */
			/* _GETRIGHT */ /*  */
			/* _SETLEFT */ /*  */
			/* _SETRIGHT */ /*  */
		/* _CANCELTRANSACTION */ /* Cancels the current transaction. One */
			/*  of two ways to "reduce the layers" of transaction. */
			/*  Actually REVERSES actions that have already been taken. */
		/* _COMPLETETRANSACTION */ /* Finishes and applies the current */
			/*  transaction. One of two ways to "reduce the layers" of */
			/*  transaction. Technically just discards the "undo info". */
		/* _COMPAREk */ /* Compares a node-contained key to a bare key */
			/*  value. Return -1 if node>bare, 0 if node==bare, 1 if */
			/*  node<bare. */
		/* _COMPAREn */ /* Compares two node keys, not currently used, */
			/*  but there is naming space for it. Same behavior as */
			/*  _COMPAREk() . */
	/* This pattern is followed so that users need only specify the */
	/*  prefix to the builder macros in this file, and ensure that */
	/*  appropriately named implementations are already in-scope. */
	
	
	
	#include "../reversivetransactor.h"
	
	/* Incomplete, finish these out. */
	/* Note that if the EternallyConfuzzled approach were taken, then */
	/*  the name of the pointer array would need to be ADDED here, as */
	/*  the builder macros can't know it before hand. */
	#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_DECLARE( head, nodetype, ... ) \
		LIBANDRIA4_RECURSIVETRANSACTOR_DECLARE( head ## transactor_, nodetype ); \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE( head ## bitup, libandria4_commonio_err, (nodetype) * );
		/* This needs to be called in a .c file to create needed */
		/*  functions. */
	#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_DEFINE( head, nodetype ) \
			LIBANDRIA4_RECURSIVETRANSACTOR_DEFINE( head ## transactor_, nodetype );
		#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_GETLEFT( head, nodetype, nodeptr ) \
			LIBANDRIA4_BINTREES_GETLEFTPTR( head ## bitup, nodetype, nodeptr )
		#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_GETRIGHT( head, nodetype, nodeptr ) \
			LIBANDRIA4_BINTREES_GETRIGHTPTR( head ## bitup, nodetype, nodeptr )
		#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_STARTTRANSACTION( ... ) \
				/* This style doesn't need initialization. */
			#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_TRANSTRACKPTRTYPE( head ) \
				head ## transactor_transactionset
			#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_SETLEFT( ... ) ???
				/*
					This function adds a change to those that can be reversed.
					int
						( head ## track )
						(
							libandria4_memfuncs_t *mf,
								( head ## transactionset ) *set,
								( head ## transactionelement ) elem
						);
				*/
			#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_SETRIGHT( ... ) ???
				/*
					This function adds a change to those that can be reversed.
					int
						( head ## track )
						(
							libandria4_memfuncs_t *mf,
								( head ## transactionset ) *set,
								( head ## transactionelement ) elem
						);
				*/
		#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_CANCELTRANSACTION( ... ) ???
			/*
				int ( head ## revert ) ( ( head ## transactionset ) *set );
				int ( head ## destroyarr ) ( libandria4_memfuncs_t *mf,  ( head ## transactionset ) *set );
			*/
		#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_COMPLETETRANSACTION( ... ) ???
			/*
				int ( head ## clear ) ( ( head ## transactionset ) *set );
				int ( head ## destroyarr ) ( libandria4_memfuncs_t *mf,  ( head ## transactionset ) *set );
			*/
			/* Arguments: pointer to node being travelled through, then the key to compare to. */
			/* Returns: */
				/* -1: The node's key is larger than the comparison key. */
				/* 0: The node is a null pointer, or it's key equals the comparison key. THIS IS IMPORTANT! */
				/* 1: The node's key is smaller than the comparison key. */
		#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_COMPAREk( ... ) ???
			/* As COMPAREk, but the comparison key is conmtained inside another node. */
		#define LIBANDRIA4_BINTREES_MACROSET_NAMEDMEMS_COMPAREn( ... ) ???
	
	
	#define LIBANDRIA4_BINTREES_UTILITY_RETURNroute( ... ) return( route )
	#define LIBANDRIA4_BINTREES_UTILITY_SETlibandria4_base( val ) \
		if( old_base ) { *old_base = libandria4_base; } libandria4_base = (val);
	
		/* If the left member of the bi-tuplic is set, then there was an error. */
		/* Errors: */
			/* LIBANDRIA4_RESULT_FAILURE_DOMAIN: You fed it null arguments. */
			/* LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED: The compare() code return a value other than -1, 0, and 1. */
			/* LIBANDRIA4_RESULT_FAILURE_IOERROR: either getleft() or getright() returned a null bi-tuplic.
				/* The next two indicate some sort of memory or execution error. */
			/* LIBANDRIA4_RESULT_FAILURE_LOGICFAULT: Internal flow error- an unreachable location was somehow reached. */
			/* LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED: Internal data error- an internally used pointer wasn't initialized. */
		/* Note that if getleft() or getright() return a bi-tuplic with it's left member set, then that bi-tuplic is returned directly. */
	#define LIBANDRIA4_BINTREES_BUILDSEARCHk( name,  nodetype, keytype,  macroset ) \
		( name ## _bitup ) \
			name ## _searchk( (nodetype) *libandria4_base, keytype libandria4_key, (nodetype) **old_base ) { \
				if( libandria4_base && libandria4_dest ) { \
					( name ## _bitup ) route, \
						a = LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTLEFT( \
							( name ## _bitup ), \
								libandria4_commonio_err, nodetype*, \
								LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ); \
						/* This will get run by LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa(). */ \
					( name ## _bitup ) (*LIBANDRIA4_OP_runable1)() = \
						&( ( name ## _bitup_buildIOErr ) ); \
					int test; \
					while( 1 ) { \
						test = macroset ## _COMPAREk( libandria4_base, libandria4_key ); switch( test ) { \
							case -1: route = macroset ## _GETLEFT( libandria4_base ); break; \
							case 0: LIBANDRIA4_MONAD_BITUPLIC_RETURNRIGHT( \
										( name ## _bitup ), \
											libandria4_commonio_err, nodetype*, \
											libandria4_base ); \
							case 1: route = macroset ## _GETRIGHT( libandria4_base ); break; \
							default: LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( \
										( name ## _bitup ), \
											libandria4_commonio_err, nodetype*, \
											LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED, libandria4_base ); } \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							route, \
								LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
								LIBANDRIA4_BINTREES_UTILITY_SETlibandria4_base, \
								LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); } \
					LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( \
						( name ## _bitup ), \
							libandria4_commonio_err, nodetype*, \
							LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); } \
				return( ( name ## _bitup_buildDomainErr )() ); }
	#define LIBANDRIA4_BINTREES_BUILDVISIT( name,  nodetype,  macroset ) \
		( name ## _bitup ) \
			name ## _visit \
			( nodetype *libandria4_base, unsigned depth,  void *visdata, int (*visitor)( void*,  unsigned, nodetype* ) ) { \
				if( base && visitor ) { \
					( name ## _bitup ) route, \
						a = LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTLEFT( \
							( name ## _bitup ), \
								libandria4_commonio_err, nodetype*, \
								LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ); \
					( name ## _bitup ) (*LIBANDRIA4_OP_runable1)() = \
						&( ( name ## _bitup_buildIOErr ) ); \
					nodetype *b; \
					int res; \
					res = visitor( visdata,  depth, libandria4_base ); if( !res ) { \
						LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( \
							( name ## _bitup ), \
								libandria4_commonio_err, nodetype*, \
								LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED, \
								libandria4_base ); } \
					route = macroset ## _GETLEFT( libandria4_base ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							route, \
								LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
								LIBANDRIA4_OP_SETb, \
								LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
						route = visit( b, depth + 1,  visdata, visitor ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							route, \
								LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
								LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO ); \
					route = macroset ## _GETRIGHT( libandria4_base ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							route, \
								LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
								LIBANDRIA4_OP_SETb, \
								LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
						route = visit( b, depth + 1,  visdata, visitor ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							route, \
								LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
								LIBANDRIA4_NULL_MACRO, LIBANDRIA4_NULL_MACRO ); \
					LIBANDRIA4_MONAD_BITUPLIC_RETURNNOTHING( \
						( name ## _bitup ), \
							libandria4_commonio_err, nodetype* ); } \
				return( ( name ## _bitup_buildDomainErr )() ); }
	#define LIBANDRIA4_BINTREES_BUILDLEFTROT( name,  nodetype,  macroset ) \
		( name ## _bitup ) \
			name ## _rotateleft( nodetype *base ) { /* Move nodes toward the lower-valued (left) side of the tree. */ \
				if( base ) { \
					( name ## _bitup ) route, \
						a = LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTLEFT( \
							( name ## _bitup ), \
								libandria4_commonio_err, nodetype*, \
								LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ); \
					nodetype *c /* "x" */, *d /* "w" */; \
					( name ## _bitup ) (*LIBANDRIA4_OP_runable1)() = &( ( name ## _bitup_buildIOErr ) ); \
						/* This should become a thread-static for optimization purposes. */ \
					( macroset ## _TRANSTRACKPTRTYPE ) transact; \
					int e = 0; \
					route = macroset ## _GETRIGHT( base ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						route, \
							LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
							LIBANDRIA4_OP_SETc, \
							LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
					route = macroset ## _GETLEFT( c ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						route, \
							LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
							LIBANDRIA4_OP_SETd, \
							LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
					macroset ## _STARTTRANSACTION( transact ); \
						route = macroset ## _SETRIGHT( base, d ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							route, \
								LIBANDRIA4_OP_SETeTO2, \
								LIBANDRIA4_NULL_MACRO, \
								LIBANDRIA4_OP_SETeTO1 ); \
						if( !e ) { \
							route = macroset ## _SETLEFT( c, base ); \
							LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
								route, \
									LIBANDRIA4_OP_SETeTO2, \
									LIBANDRIA4_NULL_MACRO, \
									LIBANDRIA4_OP_SETeTO1 ); } \
					if( !e ) { \
						macroset ## _COMPLETETRANSACTION( transact ); } \
					else { \
						macroset ## _CANCELTRANSACTION( transact ); \
						if( e == 2 ) { return( route ); } } \
					LIBANDRIA4_MONAD_BITUPLIC_RETURNRIGHT( \
						( name ## _bitup ), \
							libandria4_commonio_err, nodetype*, \
							c ); } \
				return( ( name ## _bitup_buildDomainErr )() ); }
	#define LIBANDRIA4_BINTREES_BUILDRIGHTROT( name,  nodetype,  macroset ) \
		( name ## _bitup ) \
			name ## _rotateright( nodetype *base ) { /* Move nodes toward the higher-valued (right) side of the tree. */ \
				if( base ) { \
					( name ## _bitup ) route, \
						a = LIBANDRIA4_MONAD_BITUPLIC_BUILDJUSTLEFT( \
							( name ## _bitup ), \
								libandria4_commonio_err, nodetype*, \
								LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ); \
					nodetype *c /* "x" */, *d /* "w" */; \
					( name ## _bitup ) (*LIBANDRIA4_OP_runable1)() = &( ( name ## _bitup_buildIOErr ) ); \
						/* This should become a thread-static for optimization purposes. */ \
					( macroset ## _TRANSTRACKPTRTYPE ) transact; \
					libandria4_commonio_err e = 0; \
					route = macroset ## _GETLEFT( base ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						route, \
							LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
							LIBANDRIA4_OP_SETc, \
							LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
					route = macroset ## _GETRIGHT( c ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						route, \
							LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
							LIBANDRIA4_OP_SETd, \
							LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
					macroset ## _STARTTRANSACTION( transact ); \
						route = macroset ## _SETLEFT( base, d ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							route, \
								LIBANDRIA4_OP_SETeTO2, \
								LIBANDRIA4_NULL_MACRO, \
								LIBANDRIA4_OP_SETeTO1 ); \
						if( !e ) { \
							route = macroset ## _SETRIGHT( c, base ); \
							LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
								route, \
									LIBANDRIA4_OP_SETeTO2, \
									LIBANDRIA4_NULL_MACRO, \
									LIBANDRIA4_OP_SETeTO1 ); } \
					if( !e ) { \
						macroset ## _COMPLETETRANSACTION( transact ); } \
					else { \
						macroset ## _CANCELTRANSACTION( transact ); \
						if( e == 2 ) { return( route ); } } \
					LIBANDRIA4_MONAD_BITUPLIC_RETURNRIGHT( \
						( name ## _bitup ), \
							libandria4_commonio_err, nodetype*, \
							c ); } \
				return( ( name ## _bitup_buildDomainErr )() ); }
	#define LIBANDRIA4_BINTREES_BUILDDOUBLEROT( name,  nodetype,  macroset ) \
		( name ## _bitup ) _doublerotateleft( nodetype *base ) { \
			if( base ) { \
				( name ## _bitup ) res; \
				( name ## _bitup ) (*LIBANDRIA4_OP_runable1)() = &( ( name ## _bitup_buildIOErr ) ); \
				nodetype *c; \
				int b = 0; \
				libandria4_commonio_err e; \
				res = macroset ## _GETRIGHT( base ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETb, \
						LIBANDRIA4_OP_SETc, \
						LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
				if( b ) { \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						res, \
							LIBANDRIA4_OP_SETe, \
							LIBANDRIA4_NULL_MACRO, \
							LIBANDRIA4_NULL_MACRO ); \
					LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( \
						( name ## _bitup ), \
							libandria4_commonio_err, nodetype*, \
							e ); } \
				res = name ## _rotateright( c ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					route, \
						LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
						LIBANDRIA4_OP_SETc, \
						LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
				res = macroset ## _SETRIGHT( base, c ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					route, \
						LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
						LIBANDRIA4_NULL_MACRO, \
						LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
				return( name ## _rotateleft( base ) ); } \
			return( ( name ## _bitup_buildDomainErr )() ); } \
		( name ## _bitup ) _doublerotateright( nodetype *base ) { \
			if( base ) { \
				( name ## _bitup ) res; \
				( name ## _bitup ) (*LIBANDRIA4_OP_runable1)() = &( ( name ## _bitup_buildIOErr ) ); \
				nodetype *c; \
				int b = 0; \
				libandria4_commonio_err e; \
				res = macroset ## _GETLEFT( base ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETb, \
						LIBANDRIA4_OP_SETc, \
						LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
				if( b ) { \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						res, \
							LIBANDRIA4_OP_SETe, \
							LIBANDRIA4_NULL_MACRO, \
							LIBANDRIA4_NULL_MACRO ); \
					LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( \
						( name ## _bitup ), \
							libandria4_commonio_err, nodetype*, \
							e ); } \
				res = name ## _rotateleft( c ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					route, \
						LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
						LIBANDRIA4_OP_SETc, \
						LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
				res = macroset ## _SETLEFT( base, c ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					route, \
						LIBANDRIA4_BINTREES_UTILITY_RETURNroute, \
						LIBANDRIA4_NULL_MACRO, \
						LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa ); \
				return( name ## _rotateright( base ) ); } \
			return( ( name ## _bitup_buildDomainErr )() ); }
	
		#define LIBANDRIA4_BINTREES_countnodes_brancherr( err ) \
			return( ( name ## _bitup_errsznodp_nodal ) ( ( name ## _eitherrsz_err )( err ), base ) );
		#define LIBANDRIA4_BINTREES_countnodes_nullrot( ... ) \
			return( ( name ## _bitup_errsznodp_nodal ) \
				( ( name ## _eitherrsz_err )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ), c ) );
	#define LIBANDRIA4_BINTREES_BUILDCOUNTNODES( name,  nodetype,  macroset ) \
	( name ## _bitup_errsznodp ) ( name ## _countnodes )( nodetype *base ) { \
		if( !base ) { \
			return ( \
				( name ## _bitup_errsznodp_nodeless )( \
					( name ## _eitherrsz_size )( 0 ) ) ); } \
		( name ## _bitup_errsznodp ) tmp; ( name ## _bitup ) res; \
		nodetype *a, *b; int c, d; \
		/* Get the sub-trees. */ \
		res = ( macroset ## _GETLEFT( base ) ); \
		LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
			res, \
				LIBANDRIA4_BINTREES_countnodes_brancherr, \
				LIBANDRIA4_OP_SETa, \
				LIBANDRIA4_BINTREES_countnodes_nullrot ); \
		res = ( macroset ## _GETRIGHT( base ) ); \
		LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
			res, \
				LIBANDRIA4_BINTREES_countnodes_brancherr, \
				LIBANDRIA4_OP_SETb, \
				LIBANDRIA4_BINTREES_countnodes_nullrot ); \
		/* Get the sizes of the sub-branches. */ \
		tmp = ( name ## _countnodes )( a ); \
		/* A proper monad would force us to at least use */ \
		/*  LIBANDRIA4_NULL_MACRO(), but C doesn't have a mechanism for */ \
		/*  that. */ \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
			tmp.left,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETc ); \
		tmp = ( name ## _countnodes )( b ); \
		/* A proper monad would force us to at least use */ \
		/*  LIBANDRIA4_NULL_MACRO(), but C doesn't have a mechanism for */ \
		/*  that. */ \
		LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
			tmp.left,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETd ); \
		/* Return the size. */ \
		return ( \
			( name ## _bitup_errsznodp_nodeless )( \
				( name ## _eitherrsz_size )( c + d + 1 ) ) ); }
	
	#define LIBANDRIA4_BINTREES_BASICSBUILDER( name,  nodetype, keytype,  macroset ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE_DEFINITION( LIBANDRIA4_CAT( (name), _bitup ), libandria4_commonio_err, nodetype* ) \
			inline ( name ## _bitup ) ( name ## _bitup_buildError )( libandria4_commonio_err err ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( ( name ## _bitup ), \
					libandria4_commonio_err, nodetype*,  err ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildNodeptr )( nodetype *ptr ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( ( name ## _bitup ), \
					libandria4_commonio_err, nodetype*,  ptr ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildBoth )( libandria4_commonio_err err, nodetype *ptr ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( ( name ## _bitup ), \
					libandria4_commonio_err, nodetype*,  err, ptr ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildIOErr ) () { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_IOERROR ) ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildDomainErr ) () { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildIndrDomainErr ) () { \
				return( ( name ## _bitup_buildError )( LIBANDRIA4_RESULT_FAILURE_INDIRDOMAIN ) ); } \
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( name ## _maynodp, nodetype* ); \
			( name ## _maynodep ) ( name ## _maynodp_nothing )() \
				{ return( LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( name ## _maynodp, nodetype* ) ); } \
			( name ## _maynodep ) ( name ## _maynodp_just )( nodetype *n ) \
				{ return( LIBANDRIA4_MONAD_MAYBE_BUILDJUST( name ## _maynodp, nodetype*, n ) ); } \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name ## _eitherrsz, unsigned, size_t ); \
			( name ## _eitherrsz ) ( name ## _eitherrsz_err )( unsigned err ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name ## _maynodp, unsigned, err ) ); } \
			( name ## _eitherrsz ) ( name ## _eitherrsz_size )( size_t sz ) \
				{ return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name ## _maynodp, size_t, sz ) ); } \
		typedef struct ( name ## _bitup_errsznodp ) ( name ## _bitup_errsznodp ); \
		struct ( name ## _bitup_errsznodp ) { \
				( name ## _eitherrsz ) left; ( name ## _maynodp ) right; }; \
			( name ## _bitup_errsznodp ) ( name ## _bitup_errsznodp_nodeless ) ( ( name ## _eitherrsz ) ersz ) \
				{ return( ( name ## _bitup_errsznodp ){ ersz, ( ( name ## _maynodp_nothing )() ) } ); } \
			( name ## _bitup_errsznodp ) ( name ## _bitup_errsznodp_nodal ) ( ( name ## _eitherrsz ) ersz, nodetype *n ) \
				{ return( ( name ## _bitup_errsznodp ){ ersz, ( ( name ## _maynodp_just )( n ) ) } ); } \
			( name ## _bitup_errsznodp ) ( name ## _bitup_errsznodp_nullreterr )( ... ) { \
				return( ( name ## _bitup_errsznodp_nodeless )( \
						( name ## _eitherrsz_err )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) ) ); } \
		LIBANDRIA4_BINTREES_BUILDSEARCHk( name,  nodetype, keytype,  macroset ) \
		LIBANDRIA4_BINTREES_BUILDVISIT( name,  nodetype,  macroset ) \
		LIBANDRIA4_BINTREES_BUILDLEFTROT( name,  nodetype,  macroset ) \
		LIBANDRIA4_BINTREES_BUILDRIGHTROT( name,  nodetype,  macroset ) \
		LIBANDRIA4_BINTREES_BUILDDOUBLEROT( name,  nodetype,  macroset ) \
		LIBANDRIA4_BINTREES_BUILDCOUNTNODES( name,  nodetype,  macroset )
	
#endif
/* End libandria4 basic bintrees bintrees.h */
