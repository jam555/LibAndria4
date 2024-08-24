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
		/* Add a doubly-linked list builder. */
	
	
	#define LIBANDRIA4_LIST_BUILDPREV( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) ( name ## _getprev )( ( name ## _eitherrnod ) tmp ) { \
			(nodetype) *a, *c = 0; libandria4_commonio_err b = 0; \
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
			if( !c ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_EOF ) ); } \
			return( ( name ## _eitherrnod_nodeptr )( c ) ); }
	#define LIBANDRIA4_LIST_BUILDNEXT( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) ( name ## _getnext )( ( name ## _eitherrnod ) tmp ) { \
			(nodetype) *a, *c = 0; libandria4_commonio_err b = 0; \
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
			if( !c ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_EOF ) ); } \
			return( ( name ## _eitherrnod_nodeptr )( c ) ); }
	
	#define LIBANDRIA4_LIST_BUILDNOPREV( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) ( name ## _getprev )( ( name ## _eitherrnod ) tmp ) { \
			(nodetype) *a; \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
				tmp,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); \
			if( !a ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	#define LIBANDRIA4_LIST_BUILDNONEXT( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) ( name ## _getnext )( ( name ## _eitherrnod ) tmp ) { \
			(nodetype) *a; \
			LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
				tmp,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); \
			if( !a ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_NOTINITIALIZED ) ); } \
			return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	
	#define LIBANDRIA4_LIST_BUILDINSPREV( name,  nodetype,  macroset ) \
		libandria4_commonio_mayerr \
			( name ## _insertptr_prev )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				if( !base || !add ) { \
					return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
				libandria4_commonio_err e = 0; \
				(nodetype) *a; \
				static const libandria4_commonio_mayerr c = \
					LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); \
				\
				if( next ) { \
					( name ## _bitup ) res = macroset ## _SETLEFT( next, add ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							res, \
								LIBANDRIA4_OP_SETe, \
								LIBANDRIA4_OP_SETa, \
								LIBANDRIA4_OP_RETc ); } \
				( name ## _bitup ) res = macroset ## _SETLEFT( add, prev ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						res, \
							LIBANDRIA4_OP_SETe, \
							LIBANDRIA4_OP_SETa, \
							LIBANDRIA4_OP_RETc ); \
				\
				if( base->head == next ) { base->head = add; } \
				if( base->tail == prev ) { base->tail = add; } \
				\
				int ret = 0; \
				if( !( base->head ) ) { ret = LIBANDRIA4_RESULT_FAILURE_CORRUPTED; } \
				if( !( base->tail ) ) { ret = LIBANDRIA4_RESULT_FAILURE_CORRUPTED; } \
				return( ret == 0 ? \
					LIBANDRIA4_COMMONIO_MAYERR_NOERR() : \
					LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( ret ) ); }
	#define LIBANDRIA4_LIST_BUILDINSNEXT( name,  nodetype,  macroset ) \
		libandria4_commonio_mayerr \
			( name ## _insertptr_next )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				if( !base || !add ) { \
					return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
				libandria4_commonio_err e = 0; \
				(nodetype) *a; \
				static const libandria4_commonio_mayerr c = \
					LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); \
				\
				if( prev ) { \
					( name ## _bitup ) res = macroset ## _SETRIGHT( prev, add ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							res, \
								LIBANDRIA4_OP_SETe, \
								LIBANDRIA4_OP_SETa, \
								LIBANDRIA4_OP_RETc ); \
								if( e ) { return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( e ) ); } } \
				( name ## _bitup ) res = macroset ## _SETRIGHT( add, next ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						res, \
							LIBANDRIA4_OP_SETe, \
							LIBANDRIA4_OP_SETa, \
							LIBANDRIA4_OP_RETc ); \
				if( e ) { return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( e ) ); } \
				\
				if( base->head == next ) { base->head = add; } \
				if( base->tail == prev ) { base->tail = add; } \
				\
				int ret = 0; \
				if( !( base->head ) ) { ret = LIBANDRIA4_RESULT_FAILURE_CORRUPTED; } \
				if( !( base->tail ) ) { ret = LIBANDRIA4_RESULT_FAILURE_CORRUPTED; } \
				return( ret == 0 ? \
					LIBANDRIA4_COMMONIO_MAYERR_NOERR() : \
					LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( ret ) ); }
	#define LIBANDRIA4_LIST_BUILDINSBIDIR( name,  nodetype ) \
		libandria4_commonio_mayerr \
			( name ## _insertptr )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				if( !base || !add ) { \
					return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
				\
				libandria4_commonio_mayerr ret = insert_prevptr( base, prev, next,  add ); \
				LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( ret,  LIBANDRIA4_OP_RETret, LIBANDRIA4_NULL_MACRO ); \
				ret = insert_nextptr( base, prev, next,  add ); \
				LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( ret,  LIBANDRIA4_OP_RETret, LIBANDRIA4_NULL_MACRO ); \
				\
				return( LIBANDRIA4_COMMONIO_MAYERR_NOERR() ); }
	
	#define LIBANDRIA4_LIST_BUILDNOINSPREV( name,  nodetype,  macroset ) \
		libandria4_commonio_mayerr \
			( name ## _insertptr_prev )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	#define LIBANDRIA4_LIST_BUILDNOINSNEXT( name,  nodetype,  macroset ) \
		libandria4_commonio_mayerr \
			( name ## _insertptr_next )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	#define LIBANDRIA4_LIST_BUILDINSBIDIR_NOPREV( name,  nodetype ) \
		libandria4_commonio_mayerr \
			( name ## _insertptr )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				return( ( name ## insertptr_next )( base, prev, next,  add ) ); }
	#define LIBANDRIA4_LIST_BUILDINSBIDIR_NONEXT( name,  nodetype ) \
		libandria4_commonio_mayerr \
			( name ## _insertptr )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				return( ( name ## insertptr_prev )( base, prev, next,  add ) ); }
	
		/* DOES NOT delete the previous node, deletes the EXPLICITLY */
		/*  IDENTIFIED node in a list with ->prev pointers. */
	#define LIBANDRIA4_LIST_BUILDDELPREV( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) \
			( name ## _deleteptr_prev )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *del ) { \
				if( !base ) { return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
				if( !del ) { return( ( name ## _eitherrnod_nodeptr )( del ) ); } \
				\
				libandria4_commonio_err e = 0; \
				(nodetype) *a; \
				static const ( name ## _eitherrnod ) \
					c = ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ), \
					d = ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_BROKEN ); \
				\
				( name ## _bitup ) res = macroset ## _GETLEFT( next ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						res, \
							LIBANDRIA4_OP_SETe, \
							LIBANDRIA4_OP_SETa, \
							LIBANDRIA4_OP_RETc ); \
				if( e ) { return( ( name ## _eitherrnod_err )( e ) ); } \
				if( a != del ) { \
					return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				\
				res = macroset ## _GETLEFT( del ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						res, \
							LIBANDRIA4_OP_SETe, \
							LIBANDRIA4_OP_SETa, \
							LIBANDRIA4_OP_RETc ); \
				if( e ) { return( ( name ## _eitherrnod_err )( e ) ); } \
				if( a != prev ) { \
					return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				\
				res = macroset ## _SETLEFT( next, prev ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETe, \
						LIBANDRIA4_OP_SETa, \
						LIBANDRIA4_OP_RETd ); \
				if( e ) { return( ( name ## _eitherrnod_err )( e ) ); } \
				if( base->head == del ) { base->head = next; } \
				if( base->tail == del ) { base->tail = prev; } \
				\
				return( ( name ## _eitherrnod_nodeptr )( del ) ); }
	#define LIBANDRIA4_LIST_BUILDDELNEXT( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) \
			( name ## _deleteptr_next )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *del ) { \
				if( !base ) { return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
				if( !del ) { return( ( name ## _eitherrnod_nodeptr )( del ) ); } \
				\
				libandria4_commonio_err e = 0; \
				(nodetype) *a; \
				static const ( name ## _eitherrnod ) \
					c = ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ), \
					d = ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_BROKEN ); \
				\
				( name ## _bitup ) res = macroset ## _GETRIGHT( prev ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						res, \
							LIBANDRIA4_OP_SETe, \
							LIBANDRIA4_OP_SETa, \
							LIBANDRIA4_OP_RETc ); \
				if( e ) { return( ( name ## _eitherrnod_err )( e ) ); } \
				if( a != del ) { \
					return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				\
				res = macroset ## _GETRIGHT( del ); \
					LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
						res, \
							LIBANDRIA4_OP_SETe, \
							LIBANDRIA4_OP_SETa, \
							LIBANDRIA4_OP_RETc ); \
				if( e ) { return( ( name ## _eitherrnod_err )( e ) ); } \
				if( a != next ) { \
					return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_BADMEMADDRESS ) ); } \
				\
				res = macroset ## _SETRIGHT( prev, next ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETe, \
						LIBANDRIA4_OP_SETa, \
						LIBANDRIA4_OP_RETd ); \
				if( e ) { return( ( name ## _eitherrnod_err )( e ) ); } \
				if( base->head == del ) { base->head = next; } \
				if( base->tail == del ) { base->tail = prev; } \
				\
				return( ( name ## _eitherrnod_nodeptr )( del ) ); }
	#define LIBANDRIA4_LIST_BUILDDELBIDIR( name,  nodetype ) \
		( name ## _eitherrnod ) \
			( name ## _deleteptr )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *del ) { \
				if( !base ) { return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
				if( !del ) { return( ( name ## _eitherrnod_nodeptr )( del ) ); } \
				\
				(nodetype) *a; \
				libandria4_commonio_err e = 0; \
				( name ## _eitherrnod ) tmp = ( name ## _deleteptr_prev )( base, prev, next,  del ); \
				LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
					tmp,  LIBANDRIA4_OP_RETtmp, LIBANDRIA4_OP_SETa ); \
				if( a != del ) { \
					( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_GENERICMISMATCH ); } \
				\
				tmp = ( name ## _deleteptr_next )( base, prev, next,  del ); \
				LIBANDRIA4_MONAD_EITHER_BODYMATCH( \
					tmp,  LIBANDRIA4_OP_SETe, LIBANDRIA4_OP_SETa ); \
				switch( e ) { \
					case 0: break; \
					case LIBANDRIA4_RESULT_FAILURE_BROKEN: \
						return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ) ); \
					default: \
						return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_UNDIFFERENTIATED ) ); } \
				if( a != del ) { \
					( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_GENERICMISMATCH ); } \
				return( tmp ); }
	;
	
	#define LIBANDRIA4_LIST_BUILDNODELPREV( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) \
			( name ## _deleteptr_prev )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	#define LIBANDRIA4_LIST_BUILDNODELNEXT( name,  nodetype,  macroset ) \
		( name ## _eitherrnod ) \
			( name ## _deleteptr_next )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	#define LIBANDRIA4_LIST_BUILDDELBIDIR_NOPREV( name,  nodetype ) \
		( name ## _eitherrnod ) \
			( name ## _insertptr )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				return( ( name ## _deleteptr_next )( base, prev, next,  add ) ); }
	#define LIBANDRIA4_LIST_BUILDDELBIDIR_NONEXT( name,  nodetype ) \
		( name ## _eitherrnod ) \
			( name ## _insertptr )( (name) *base, (nodetype) *prev, (nodetype) *next,  (nodetype) *add ) { \
				return( ( name ## _deleteptr_prev )( base, prev, next,  add ) ); }
	
	#define LIBANDRIA4_LIST_BUILDVISITPREV( name,  nodetype,  macroset ) \
		libandria4_commonio_mayerr \
			( name ## _visitprev )( \
				(name) *base, \
				void *data, void (*func)( void*,  uintptr_t, ((nodetype)*) ) ) { \
					if( !base || !func ) { \
						return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
					if( ( base->head ? 1 : 0 ) != ( base->tail ? 1 : 0 ) ) { \
						return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ) ); } \
					( name ## _bitup ) res; \
					static const libandria4_commonio_mayerr c = \
						LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); \
					libandria4_commonio_err e; \
					uintptr_t count = 0; (nodetype) *a = base->tail; \
					while( a && a != base->head && count < UINTMAX_MAX ) { \
						func( data,  count, a ); \
						++count; res = macroset ## _GETLEFT( a ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							res, \
								LIBANDRIA4_OP_SETe, \
								LIBANDRIA4_OP_SETa, \
								LIBANDRIA4_OP_RETc ); \
						if( e ) { \
							return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( e ) ); } } \
					if( count == UINTMAX_MAX ) { \
						/* Should never happen, so almost guaranteed loop. */ \
						return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS ) ); } \
					return( LIBANDRIA4_COMMONIO_MAYERR_NOERR() ); }
	#define LIBANDRIA4_LIST_BUILDVISITNEXT( name,  nodetype,  macroset ) \
		libandria4_commonio_mayerr \
			( name ## _visitnext )( \
				(name) *base, \
				void *data, void (*func)( void*,  uintptr_t, ((nodetype)*) ) ) { \
					if( !base || !func ) { \
						return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_DOMAIN ) ); } \
					if( ( base->head ? 1 : 0 ) != ( base->tail ? 1 : 0 ) ) { \
						return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ) ); } \
					( name ## _bitup ) res; \
					static const libandria4_commonio_mayerr c = \
						LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_LOGICFAULT ); \
					libandria4_commonio_err e; \
					uintptr_t count = 0; (nodetype) *a = base->head; \
					while( a && a != base->tail && count < UINTMAX_MAX ) { \
						func( data,  count, a ); \
						++count; res = macroset ## _GETRIGHT( a ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							res, \
								LIBANDRIA4_OP_SETe, \
								LIBANDRIA4_OP_SETa, \
								LIBANDRIA4_OP_RETc ); \
						if( e ) { \
							return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( e ) ); } } \
					if( count == UINTMAX_MAX ) { \
						/* Should never happen, so almost guaranteed loop. */ \
						return( LIBANDRIA4_COMMONIO_MAYERR_JUSTERR( LIBANDRIA4_RESULT_FAILURE_ABOVEBOUNDS ) ); } \
					return( LIBANDRIA4_COMMONIO_MAYERR_NOERR() ); }
	
	#define LIBANDRIA4_LIST_BUILDNOVISITPREV( name,  nodetype,  macroset ) \
		libandria4_commonio_mayerr ( name ## _visitprev )( \
				(name) *base,  void *data, void (*func)( void*,  uintptr_t, ((nodetype)*) ) ) { \
					return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	#define LIBANDRIA4_LIST_BUILDNOVISITNEXT( name,  nodetype,  macroset ) \
		libandria4_commonio_mayerr ( name ## _visitnext )( \
				(name) *base,  void *data, void (*func)( void*,  uintptr_t, ((nodetype)*) ) ) { \
					return( ( name ## _eitherrnod_err )( LIBANDRIA4_RESULT_FAILURE_INVALIDOPER ) ); }
	
	#define LIBANDRIA4_LIST_BUILDVERIFYHELPER( name,  nodetype,  macroset ) \
		typedef struct ( name ## _verifyhelper_dat ) ( name ## _verifyhelper_dat ); \
		struct ( name ## _verifyhelper_dat ) { (nodetype) *node; uintptr_t len; }; \
		void ( name ## _verifyhelper )( void *dat,  uintptr_t len, (nodetype) *n ) { \
			if( dat ) { \
				( name ## _verifyhelper_dat ) *data = (( name ## _verifyhelper_dat )*)dat; \
				data->node = n; data->len = len; } }
	#define LIBANDRIA4_LIST_BUILDVERIFYHELPERBIDIR( name,  nodetype,  macroset ) \
		typedef struct ( name ## _verifyhelper_dat ) ( name ## _verifyhelper_dat ); \
		struct ( name ## _verifyhelper_dat ) { (nodetype) *node; uintptr_t len; int badaddr; }; \
		void ( name ## _verifyhelper )( void *dat,  uintptr_t len, (nodetype) *n ) { \
			if( dat ) { \
				( name ## _verifyhelper_dat ) *data = (( name ## _verifyhelper_dat )*)dat; \
				data->node = n; data->len = len; \
				( name ## _bitup ) res; (nodetype) *a; libandria4_commonio_err e = 0; \
				if( data->badaddr == 0 ) { \
					if( n ) { \
						res = macroset ## _GETLEFT( n ); \
						LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
							res, \
								LIBANDRIA4_OP_SETe, \
								LIBANDRIA4_OP_SETa, \
								LIBANDRIA4_OP_RETURNvoid ); \
						if( e ) { data->badaddr = -e; } \
						else { \
							res = macroset ## _GETRIGHT( a ); \
							LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
								res, \
									LIBANDRIA4_OP_SETe, \
									LIBANDRIA4_OP_SETa, \
									LIBANDRIA4_OP_RETURNvoid ); \
							if( e ) { data->badaddr = e; } \
							else { data->badaddr = ( a != n ) ? 1 : 0; } } } \
					else { data->badaddr = 1; } } } }
	#define LIBANDRIA4_LIST_BUILDVERIFYNONEXT( name,  nodetype,  macroset ) \
		int ( name ## _verify )( (name) *base, uintptr_t *count, (nodetype) **n ) { \
			libandria4_commonio_err e = 0; \
			if( !base ) { return( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			if( ( base->head ? 1 : 0 ) != ( base->tail ? 1 : 0 ) ) { \
				return( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ); } \
			if( base->head ) { \
				( name ## _bitup ) res; (nodetype) *a; \
				res = macroset ## _GETLEFT( base->head ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETe, \
						LIBANDRIA4_OP_SETa, \
						LIBANDRIA4_OP_RETURNVAL_1 ); \
				if( e ) { return( -e ); }; \
				if( a ) { return( LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS ); } } \
			( name ## _verifyhelper_dat ) vhdat = { 0, 0 }; \
			libandria4_commonio_mayerr tmp = ( name ## _visitprev )( base, (void*)&vhdat, &( name ## _verifyhelper ) ); \
				if( count ) { *count = vhdat.len; } \
				if( n ) { *n = vhdat->node; } \
			LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( tmp,  LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO ); \
				if( e ) { return( e ); } \
			if( vhdat->node != base->tail ) { return( LIBANDRIA4_RESULT_FAILURE_GENERICMISMATCH ); } \
			/* Success. */ return( 0 ); }
	#define LIBANDRIA4_LIST_BUILDVERIFYNOPREV( name,  nodetype,  macroset ) \
		int ( name ## _verify )( (name) *base, uintptr_t *count, (nodetype) **n ) { \
			libandria4_commonio_err e = 0; \
			if( !base ) { return( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			if( ( base->head ? 1 : 0 ) != ( base->tail ? 1 : 0 ) ) { \
				return( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ); } \
			if( base->tail ) { \
				( name ## _bitup ) res; (nodetype) *a; \
				res = macroset ## _GETRIGHT( base->tail ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETe, \
						LIBANDRIA4_OP_SETa, \
						LIBANDRIA4_OP_RETURNVAL_1 ); \
				if( e ) { return( -e ); }; \
				if( a ) { return( LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS ); } } \
			( name ## _verifyhelper_dat ) vhdat = { 0, 0 }; \
			libandria4_commonio_mayerr tmp = ( name ## _visitnext )( base, (void*)&vhdat, &( name ## _verifyhelper ) ); \
				if( count ) { *count = vhdat.len; } \
				if( n ) { *n = vhdat->node; } \
			LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( tmp,  LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO ); \
				if( e ) { return( e ); } \
			if( vhdat->node != base->tail ) { return( LIBANDRIA4_RESULT_FAILURE_GENERICMISMATCH ); } \
			/* Success. */ return( 0 ); }
	#define LIBANDRIA4_LIST_BUILDVERIFYBIDIR( name,  nodetype,  macroset ) \
		int ( name ## _verify )( (name) *base, uintptr_t *count, (nodetype) **n ) { \
			if( !base ) { return( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			if( ( base->head ? 1 : 0 ) != ( base->tail ? 1 : 0 ) ) { \
				return( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ); } \
			( name ## _bitup ) res; (nodetype) *a; libandria4_commonio_err e = 0; \
			if( base->head ) { \
				res = macroset ## _GETLEFT( base->head ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETe, \
						LIBANDRIA4_OP_SETa, \
						LIBANDRIA4_OP_RETURNVAL_1 ); \
				if( e ) { return( -e ); }; \
				if( a ) { return( LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS ); } } \
			if( base->tail ) { \
				res = macroset ## _GETRIGHT( base->tail ); \
				LIBANDRIA4_MONAD_BITUPLIC_BODYMATCH( \
					res, \
						LIBANDRIA4_OP_SETe, \
						LIBANDRIA4_OP_SETa, \
						LIBANDRIA4_OP_RETURNVAL_1 ); \
				if( e ) { return( -e ); }; \
				if( a ) { return( LIBANDRIA4_RESULT_FAILURE_BELOWBOUNDS ); } } \
			( name ## _verifyhelper_dat ) vhdat = { 0, 0, 0 }; \
			libandria4_commonio_mayerr tmp = ( name ## _visitprev )( base, (void*)&vhdat, &( name ## _verifyhelper ) ); \
				if( count ) { *count = vhdat.len; } \
				if( n ) { *n = vhdat->node; } \
			LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( tmp,  LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO ); \
				if( e ) { return( e ); } \
				if( vhdat->badaddr ) { return( LIBANDRIA4_RESULT_FAILURE_BROKEN ); } \
			if( vhdat->node != base->tail ) { return( LIBANDRIA4_RESULT_FAILURE_GENERICMISMATCH ); } \
			/* Success. */ return( 0 ); }
	
	#define LIBANDRIA4_LIST_BUILDLENGTHHELPER( name,  nodetype ) \
		typedef struct ( name ## _lengthhelper_dat ) ( name ## _lengthhelper_dat ); \
		struct ( name ## _lengthhelper_dat ) { uintptr_t len; }; \
		void ( name ## _lengthhelper )( void *dat,  uintptr_t len, (nodetype) *ignore ) { \
			if( dat ) { ( (( name ## _verifyhelper_dat )*)dat )->len = len; } }
	#define LIBANDRIA4_LIST_BUILDLENGTHNONEXT( name,  nodetype ) \
		int ( name ## _length )( (name) *base, uintptr_t *count ) { \
			if( !base || !count ) { return( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			if( ( base->head ? 1 : 0 ) != ( base->tail ? 1 : 0 ) ) { \
				return( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ); } \
			libandria4_commonio_err e = 0; ( name ## _lengthhelper_dat ) lhdat = { 0 }; \
			libandria4_commonio_mayerr tmp = ( name ## _visitprev )( base, (void*)&lhdat, &( name ## _lengthhelper ) ); \
				*count = lhdat.len; \
			LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( tmp,  LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO ); \
				if( e ) { return( e ); } /* Success. */ return( 0 ); }
	#define LIBANDRIA4_LIST_BUILDLENGTHNOPREV( name,  nodetype ) \
		int ( name ## _length )( (name) *base, uintptr_t *count ) { \
			if( !base || !count ) { return( LIBANDRIA4_RESULT_FAILURE_DOMAIN ); } \
			if( ( base->head ? 1 : 0 ) != ( base->tail ? 1 : 0 ) ) { \
				return( LIBANDRIA4_RESULT_FAILURE_CORRUPTED ); } \
			libandria4_commonio_err e = 0; ( name ## _lengthhelper_dat ) lhdat = { 0 }; \
			libandria4_commonio_mayerr tmp = ( name ## _visitnext )( base, (void*)&lhdat, &( name ## _lengthhelper ) ); \
				*count = lhdat.len; \
			LIBANDRIA4_COMMONIO_MAYERR_BODYMATCH( tmp,  LIBANDRIA4_OP_SETe, LIBANDRIA4_NULL_MACRO ); \
				if( e ) { return( e ); } /* Success. */ return( 0 ); }
	
		/* For a doubly-linked list, replace the following "starting" macros */
		/*  with the respective "trailing" macro: */
			/* LIBANDRIA4_LIST_BUILDPREV -> LIBANDRIA4_LIST_BUILDNOPREV */
			/* LIBANDRIA4_LIST_BUILDINSPREV -> LIBANDRIA4_LIST_BUILDNOINSPREV */
			/* LIBANDRIA4_LIST_BUILDINSBIDIR -> LIBANDRIA4_LIST_BUILDINSBIDIR_NOPREV */
			/* LIBANDRIA4_LIST_BUILDNODELPREV -> LIBANDRIA4_LIST_BUILDDELPREV */
			/* LIBANDRIA4_LIST_BUILDDELBIDIR_NOPREV -> LIBANDRIA4_LIST_BUILDDELBIDIR */
			/* LIBANDRIA4_LIST_BUILDNOVISITPREV -> LIBANDRIA4_LIST_BUILDVISITPREV */
			/* LIBANDRIA4_LIST_BUILDVERIFYHELPER -> LIBANDRIA4_LIST_BUILDVERIFYHELPERBIDIR */
			/* LIBANDRIA4_LIST_BUILDVERIFYNOPREV -> LIBANDRIA4_LIST_BUILDVERIFYBIDIR */
		/*  Note that nodetype MUST have an equivalent of a ->next pointer */
		/*  accessible through the "right" macroset macros.*/
	#define LIBANDRIA4_LIST_BASICBUILDER_SINGLELINKED( name,  nodetype,  macroset ) \
		LIBANDRIA4_MONAD_BITUPLIC_BUILDTYPE_DEFINITION( ( name ## _bitup ), libandria4_commonio_err, nodetype* ); \
			inline ( name ## _bitup ) ( name ## _bitup_buildError )( libandria4_commonio_err err ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNLEFT( ( name ## _bitup ), \
					libandria4_commonio_err, nodetype*,  err ); } \
			inline ( name ## _bitup ) ( name ## _bitup_buildNodeptr )( nodetype *ptr ) { \
				LIBANDRIA4_MONAD_BITUPLIC_RETURNBOTH( ( name ## _bitup ), \
					libandria4_commonio_err, nodetype*,  ptr ); } \
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
		typedef struct name { size_t len; (nodetype) *head, *tail; } name; \
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
		LIBANDRIA4_LIST_BUILDNOPREV( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDNEXT( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDINSNEXT( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDNOINSPREV( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDINSBIDIR_NOPREV( name,  nodetype ); \
		LIBANDRIA4_LIST_BUILDDELNEXT( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDNODELPREV( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDDELBIDIR_NOPREV( name,  nodetype ); \
		LIBANDRIA4_LIST_BUILDVISITNEXT( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDNOVISITPREV( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDVERIFYHELPER( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDVERIFYNOPREV( name,  nodetype,  macroset ); \
		LIBANDRIA4_LIST_BUILDLENGTHHELPER( name,  nodetype ); \
		LIBANDRIA4_LIST_BUILDLENGTHNOPREV( name,  nodetype );
	
#endif
/* End libandria4 basic list.h */
