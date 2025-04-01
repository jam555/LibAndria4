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

#ifndef LIBANDRIA4_BASIC_BINTREES_MACROSET_H
# define LIBANDRIA4_BASIC_BINTREES_MACROSET_H
	
	
	/* This file is very incomplete: finish it. */
	
	
	/* This system is built around a requirmnent for several macros that */
	/*  follow the naming pattern of a shared prefix followed by an */
	/*  identifying function name. */
	/*
		Expected types:
		LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE_DEFINITION( ( name ## _bitup ), libandria4_commonio_err, nodetype* );
		??? ;
	*/
	/* The names are as follows: */
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
	
#endif
/* End libandria4 basic bintrees macroset.h */
