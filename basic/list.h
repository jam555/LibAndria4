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

#ifndef LIBANDRIA4_BASIC_LIST_H
# define LIBANDRIA4_BASIC_LIST_H
	
	#include "simpleops.h"
	#include "monads.h"
		/* libandria4_commonio_err */
	#include "commonio.h"
	#include "commonerrvals.h"
	
	/* Note that the compilation unit MUST contain at least the four left & */
	/*  right macroset macros, so that the implementations below can work */
	/*  correctly. */
	
	
	/* TODO: */
		/* Add insertion functions (must ALL require the list pointer.). */
		/* Add a doubly-linked list builder. */
	
	
	#define LIBANDRIA4_LIST_BUILDPREV( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) ( name ## _getprev )( ( name ## _eitherrnod ) tmp ) { \
			(nodetype) *a, *c; libandria4_commonio_err b = 0; \
			static ( name ## _eitherrnod ) d = \
				( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
				tmp,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); \
			if( !a ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			( name ## _bitup ) res = macroset ## _GETLEFT( a ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETb, \
						LIBANDRIA4_OP_SETc, \
						LIBANDRIA4_OP_RETd ); \
			if( b ) { \
				return( ( name ## _eitherrnod_err )( b ) ); } \
			if( c ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_EOF ) ); } \
			return( ( name ## _eitherrnod_nodeptr )( c ) ); }
	#define LIBANDRIA4_LIST_BUILDNEXT( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) ( name ## _getnext )( ( name ## _eitherrnod ) tmp ) { \
			(nodetype) *a, *c; libandria4_commonio_err b = 0; \
			static ( name ## _eitherrnod ) d = \
				( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
				tmp,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); \
			if( !a ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			( name ## _bitup ) res = macroset ## _GETRIGHT( a ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETb, \
						LIBANDRIA4_OP_SETc, \
						LIBANDRIA4_OP_RETd ); \
			if( b ) { \
				return( ( name ## _eitherrnod_err )( b ) ); } \
			if( c ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_EOF ) ); } \
			return( ( name ## _eitherrnod_nodeptr )( c ) ); }
	
	#define LIBANDRIA4_LIST_BUILDNOPREV( name,  nodetype ) \
		( name ## _eitherrnod ) ( name ## _getprev )( ( name ## _eitherrnod ) tmp ) { \
			(nodetype) *a; \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
				tmp,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); \
			if( !a ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	#define LIBANDRIA4_LIST_BUILDNONEXT( name,  nodetype ) \
		( name ## _eitherrnod ) ( name ## _getnext )( ( name ## _eitherrnod ) tmp ) { \
			(nodetype) *a; \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
				tmp,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); \
			if( !a ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	
		/* For a doubly-linked list, use LIBANDRIA4_LIST_BUILDPREV() instead */
		/*  of LIBANDRIA4_LIST_BUILDNOPREV(). */
	#define LIBANDRIA4_LIST_BASICBUILDER_SINGLELINKED( name,  nodetype,  macroset ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE_DEFINITION( ( name ## _bitup ), libandria4_commonio_err, nodetype* ); \
		LIBANDRIA4_MONAD_MAYBE_BUILDTYPE( name ## _maynodp, nodetype* ); \
			( name ## _maynodep ) ( name ## _maynodp_nothing )() { \
				return( LIBANDRIA4_MONAD_MAYBE_BUILDNOTHING( name ## _maynodp, nodetype* ) ); } \
			( name ## _maynodep ) ( name ## _maynodp_nil )( nodetype *ignore, ... ) { \
				return( ( name ## _maynodp_nothing )() ); } \
			( name ## _maynodep ) ( name ## _maynodp_nill )( nodetype *ignore, ... ) { \
				return( ( name ## _maynodp_nothing )() ); } \
			( name ## _maynodep ) ( name ## _maynodp_null )( nodetype *ignore, ... ) { \
				return( ( name ## _maynodp_nothing )() ); } \
			( name ## _maynodep ) ( name ## _maynodp_void )( nodetype *ignore, ... ) { \
				return( ( name ## _maynodp_nothing )() ); } \
			( name ## _maynodep ) ( name ## _maynodp_just )( nodetype *n ) { \
				return( LIBANDRIA4_MONAD_MAYBE_BUILDJUST( name ## _maynodp, nodetype*, n ) ); } \
		typedef struct name { size_t len; (nodetype) *head, tail; } name; \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name ## _eitherrsz, unsigned, size_t ); \
			( name ## _eitherrsz ) ( name ## _eitherrsz_err )( unsigned err ) { \
				return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name ## _eitherrsz, unsigned, err ) ); } \
			( name ## _eitherrsz ) ( name ## _eitherrsz_size )( size_t sz ) { \
				return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name ## _eitherrsz, size_t, sz ) ); } \
		( name ## _eitherrsz ) ( name ## _getlen )( (name) *list ) { \
			if( list ) { return( ( name ## _eitherrsz_size )( list->len ) ); } \
			return( ( name ## _eitherrsz_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
		LIBANDRIA4_MONAD_EITHER_BUILDTYPE( name ## _eitherrnod, unsigned, nodetype* ); \
			( name ## _eitherrnod ) ( name ## _eitherrnod_err )( unsigned err ) { \
				return( LIBANDRIA4_MONAD_EITHER_BUILDLEFT( name ## _eitherrnod, unsigned, err ) ); } \
			( name ## _eitherrnod ) ( name ## _eitherrnod_nodeptr )( nodetype *ptr ) { \
				return( LIBANDRIA4_MONAD_EITHER_BUILDRIGHT( name ## _eitherrnod, nodetype*, ptr ) ); } \
		( name ## _eitherrnod ) ( name ## _getfirst )( name *list ) { \
			if( !list ) { return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			if( !( list->head && list->tail ) ) \
				{ return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			return( ( name ## _eitherrnod_nodeptr )( list->head ) ); } \
		( name ## _eitherrnod ) ( name ## _getlast )( name *list ) { \
			if( !list ) { return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
			if( !( list->head && list->tail ) ) \
				{ return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			return( ( name ## _eitherrnod_nodeptr )( list->tail ) ); } \
		LIBANDRIA4_LIST_BUILDNOPREV( name,  nodetype ); \
		LIBANDRIA4_LIST_BUILDNEXT( name,  nodetype,  macroset ); \
		;
	
#endif
/* End libandria4 basic list.h */
