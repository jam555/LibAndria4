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



#include "terminal.h"
#include "stdtables.h"
#include "stdhandlers.h"



int vt100net_report_parser_error( vt100net_termcontext *term_ctx, uint32_t *report_type_member )
{
	VT100NET_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME( funcname, __func__ );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			no_errrep_func,
			"FATAL: The vt100net_termcontext error reporting func is directly missing."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			no_errrep_func2,
			"FATAL: The vt100net_termcontext error reporting func is indirectly missing."
		);
	
	if( term_ctx && report_type_member )
	{
		if( !( term_ctx->errrec.func ) )
		{
			term_ctx->res = (intmax_t)&( no_errrep_func.type.typeid );
			return( -2 );
		}
		if( !( *( term_ctx->errrec.func ) ) )
		{
			term_ctx->res = (intmax_t)&( no_errrep_func2.type.typeid );
			return( -3 );
		}
		
		int res = ( *( term_ctx->erreec.func ) )( &( term_ctx->erreec ), (void*)report_type_member );
		if( !res )
		{
			term_ctx->res = res;
			return( -4 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}



/* The actual parser itself. Note that parsers for e.g. escape codes aren't */
/*  here, this is a parser that CALLS those other parsers, in the process */
/*  providing the needed data to them. */

int vt100net_parser( vt100net_termcontext *term_ctx );
int vt100net_reader( vt100net_termcontext *term_ctx );

int vt100net_looper( vt100net_termcontext *term_ctx )
{
	VT100NET_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME( funcname, __func__ );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			chartype_hooks_bad,
			"FATAL: Failure while validating character type test function pointers."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			IOhooks_bad,
			"FATAL: Failure while validating IOhook function pointers."
		);
	
	if( term_ctx )
	{
		intmax_t res;
		
		if( !( term_ctx->errrec.func ) )
		{
				/* The desired error reporting mechanism is absent, fail immediately! */
			return( -2 );
		}
		if( !( *( term_ctx->errrec.func ) ) )
		{
				/* The desired error reporting mechanism is absent, fail immediately! */
			return( -3 );
		}
		
		term_ctx->res = vt100net_termcontext_chartype_hook_validate( &( term_ctx->type_tests ) );
		if( !( term_ctx->res ) )
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( chartype_hooks_bad.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			
				/* We can NORMALLY just go with generic "-4" errors from here on. */
			return( -4 );
		}
		
		res = vt100net_termcontext_IOhook_validate( term_ctx );
		if( !res )
		{
			if( res < -4 )
			{
				return( res );
			}
			
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( IOhooks_bad.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			
			return( -4 );
		}
		
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			UTF8_banned,
			"FATAL: UTF8 is forbidden in this *_looper() version."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			CANSUB_unhandled,
			"FATAL: The CAN and SUB Ascii codes haven't been paid attention to yet!"
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			ZDM_unhandled,
			"FATAL: ECMA-48's ZDM hasn't been paid attention to yet!"
		);
		
		do
		{
			if
			(
				term_ctx->flags1 & vt100net_termcontext_flags1_UTF8loose == vt100net_termcontext_flags1_UTF8loose ||
				term_ctx->flags1 & vt100net_termcontext_flags1_UTF8strict == vt100net_termcontext_flags1_UTF8strict
			)
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( UTF8_banned.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				
				return( -4 );
			}
			if( term_ctx->flags1 & vt100net_termcontext_flags1_CANSUB_cancelseq == vt100net_termcontext_flags1_CANSUB_cancelseq )
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( CANSUB_unhandled.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				
				return( -4 );
			}
			if( term_ctx->flags1 & vt100net_termcontext_flags1_ZDMenable == vt100net_termcontext_flags1_ZDMenable )
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( ZDM_unhandled.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				
				return( -4 );
			}
			
			switch( term_ctx->dispatch )
			{
				case vt100net_termcontext_INVALID:
					/* Error, nuclear meltdown! */
					
					VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
						&funcname,
						vt100net_termcontext_INVALID_report,
						"FATAL: (vt100net_termcontext).dispatch == vt100net_termcontext_INVALID."
					);
					VT100NET_REPORT_ERR(
						term_ctx,
						&( vt100net_termcontext_INVALID_report.type.typeid ),
						__FILE__, __LINE__
					);
					return( -4 );
					
				case vt100net_termcontext_INITIAL_ENTRY:
					/* The initial entry state. Do some initialization, then goto GROUND. */
					
					/* Initialize pointers. */
					term_ctx->callstack = term_ctx->dispatchstack;
					term_ctx->sequence_dispatch.intermediates = term_ctx->intermediate_characters;
					term_ctx->params = term_ctx->parameter_values;
					
					/* Initialize values. */
					term_ctx->callstack[ 0 ] = vt100net_termcontext_GROUND;
					term_ctx->dispatch = vt100net_termcontext_FETCHCHAR;
					term_ctx->run = 1;
					
					break;
					
					/* This is in vt100net_looper() to make it easier to support different */
					/*  encoding setups: just change the loop function... though that MIGHT */
					/*  be achievable in the fetch function itself. */
					/* We'll currently assume simple ASCII, but for Unicode & similar we'll */
					/*  need to calculate FINAL values instead of just settling on the first */
					/*  full character we get. Note that while complete surrogate support */
					/*  should be fairly easy, full combining character support is simply */
					/*  impossible (combining characters are used for that "text corruption" */
					/*  horror-text thing that throws characters vertically from normal text, */
					/*  and it very specifically can have ARBITRARY NUMBERS of combining */
					/*  characters following the initial "base" character: the only way to */
					/*  fully support it is bitmap or vector graphics); fortunately, full */
					/*  combining character support is a semi-specialized thing, so single */
					/*  combining characters should (hopefully) be fairly easy, especially */
					/*  since UNICODE gave up on the top few bits of 32-bit representation. */
				case vt100net_termcontext_FETCHCHAR:
					/* The actual character-fetch code is in another function, because it */
					/*  was already a bit large. */
					
					VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
						&funcname,
						vt100net_termcontext_FETCHCHAR_normerror,
						"FATAL: vt100net_reader() failed."
					);
					VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
						&funcname,
						vt100net_termcontext_FETCHCHAR_abnormalerror,
						"FATAL: vt100net_reader() experienced an abnormal error."
					);
					
					res = vt100net_reader( vt100net_termcontext *term_ctx );
					if( res == -4 )
					{
						res = term_ctx->res;
							VT100NET_REPORT_ERR(
								term_ctx,
								&( vt100net_termcontext_FETCHCHAR_normerror.type.typeid ),
								__FILE__, __LINE__
							);
						term_ctx->res = res;
						return( -4 );
						
					} else if( res < 0 )
					{
							/* ERROR: How did we even get here??? */
						res = term_ctx->res;
							VT100NET_REPORT_ERR(
								term_ctx,
								&( vt100net_termcontext_FETCHCHAR_abnormalerror.type.typeid ),
								__FILE__, __LINE__
							);
						term_ctx->res = res;
						return( -4 );
					}
					
						/* The VT500+ kept null characters, while older members of */
						/*  the series discarded nulls before the parser saw them. */
						/*  This allows this system's user to choose which behavior */
						/*  to follow. */
					if
					(
						term_ctx->acc_char == '\0' &&
						term_ctx->flags1 & vt100net_termcontext_flags1_retainnull
							!= vt100net_termcontext_flags1_retainnull
					)
					{
						/* We're done, return to the "caller". */
						
						uint8_t tmp;
						vt100net_termcontext_dispatch_POP( term_ctx, tmp )
						
						if( tmp != vt100net_termcontext_FETCHCHAR )
						{
								/* ERROR: How did we get here??? */
							VT100NET_REPORT_ERR(
								term_ctx,
								&( in_function_POP_fail.type.typeid ),
								__FILE__, __LINE__
							);
							term_ctx->res = tmp;
							return( -4 );
						}
					}
					
					break;
					
				default:
					VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
						&funcname,
						vt100net_parser_failure,
						"FATAL: vt100net_parser() returned an error."
					);
					VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
						&funcname,
						vt100net_dispatchPUSH_error,
						"FATAL: vt100net_termcontext_dispatch_PUSH() returned a exec-able bottom value."
					);
					
					res = vt100net_parser( term_ctx );
					if( !res )
					{
							/* ERROR: How did we get here??? */
						res = term_ctx->res;
							VT100NET_REPORT_ERR(
								term_ctx,
								&( vt100net_parser_failure.type.typeid ),
								__FILE__, __LINE__
							);
						term_ctx->res = res;
						return( -4 );
					}
					
					{
						uint8_t tmp = vt100net_termcontext_FETCHCHAR;
						
						vt100net_termcontext_dispatch_PUSH( term_ctx, tmp );
						
						if( tmp != vt100net_termcontext_INVALID )
						{
							/* Welp, there was something on the bottom of the stack... */
							
							VT100NET_REPORT_ERR(
								term_ctx,
								&( vt100net_dispatchPUSH_error.type.typeid ),
								__FILE__, __LINE__
							);
							term_ctx->res = tmp;
							return( -4 );
						}
					}
					
					break;
			}
		} while( term_ctx->run != 0 );
	}
	
		/* As always, "immediately invalid args". */
	return( -1 );
}

	/* Reads a character from the provided character source. */
int vt100net_reader( vt100net_termcontext *term_ctx )
{
	VT100NET_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME( funcname, __func__ );
	
	if( term_ctx )
	{
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			no_in_function1,
			"FATAL: The vt100net_termcontext character input func is indirectly missing."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			no_in_function2,
			"FATAL: The vt100net_termcontext character input func is directly missing."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			in_function_failure,
			"FATAL: The vt100net_termcontext character input func returned a failure."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			in_function_POP_fail,
			"FATAL: The vt100net_termcontext FETCHCHAR had a failure in *_dispatch_POP()."
		);
		
		if( !( term_ctx->in.func ) )
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( no_in_function1.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			return( -4 );
		}
		if( !( *( term_ctx->in.func ) ) )
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( no_in_function2.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			return( -4 );
		}
		
		res = ( *( term_ctx->in.func ) )( &( term_ctx->erreec ), (void*)&( term_ctx->acc_char ) );
		if( !res )
		{
			VT100NET_REPORT_ERR(
				term_ctx,
				&( in_function_failure.type.typeid ),
				__FILE__, __LINE__
			);
			term_ctx->res = res;
			return( -4 );
		}
		
		/* Note: This is strictly NOT the Unicode version, so no */
		/*  values over 255 even IF it's somehow provided. Might */
		/*  be bettter to just produce a null if excessively */
		/*  high values are detected? */
		if( term_ctx->flags1 & vt100net_termcontext_flags1_8bit == 0 )
		{
			term_ctx->acc_char &= 127;
			
		} else {
			
			term_ctx->acc_char &= 255;
		}
		
		return( 1 );
	}
	
	return( -1 );
}

	/* Performs the actual parsing, and executes handlers/actions */
	/*  when appropriate. */
int vt100net_parser( vt100net_termcontext *term_ctx )
{
	VT100NET_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME( funcname, __func__ );
	
	if( term_ctx )
	{
		/* "Bad environment" errors. */
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			underrange,
			"FATAL: hooks->test_count < vt100net_termcontext_chartype_MAXLEN."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			overrange,
			"FATAL: hooks->test_count < vt100net_termcontext_chartype_MAXLEN."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			bad_fromAnywhere,
			"FATAL: vt100net_fromAnywhere[ chara ] had an invalid value."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			bad_vt100net_handlers,
			"FATAL: vt100net_handlers[] had an invalid value."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			bad_onEntry,
			"FATAL: vt100net_onEntry[ state ] had an invalid value."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			bad_onExit,
			"FATAL: vt100net_onExit[ state ] had an invalid value."
		);
		
		/* "Failure" errors. */
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			failed_onEntry,
			"FATAL: Call via vt100net_onEntry[ state ] had a bad return."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			failed_onEvent,
			"FATAL: Call via vt100net_handlers[ ->handler_index ]... had a bad return."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			failed_onExit,
			"FATAL: Call via vt100net_onExit[ state ] had a bad return."
		);
		
		uint8_t
			state = term_ctx->dispatch,
			chara = (uint8_t)( term_ctx->acc_char & 255 );
		intmax_t res;
		
		if( state < vt100net_termcontext_GROUND )
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( underrange.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			return( -4 );
		}
		if( state >= vt100net_termcontext_STATES_PASTEND )
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( overrange.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			return( -4 );
		}
			/* Adjust for lookups. */
		state -= vt100net_termcontext_GROUND;
		
		
		
		vt100net_handler_mapping *map;
		
		/* Standard path. */
		map =
			(
				vt100net_handler_mappingset +
				( vt100net_stateMappings[ state ][ chara ] )
			);
		if
		(
			map->handler_index < vt100net_HAND_FALLTHROUGH &&
			vt100net_handlers[ map->handler_index ] == (vt100net_action_handler)0
		)
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( bad_vt100net_handlers.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			return( -4 );
		}
		if( map->handler_index >= vt100net_HAND_FALLTHROUGH )
		{
			/* Current target is a pass-through. */
			
			map =
				(
					vt100net_handler_mappingset +
					( vt100net_fromAnywhere[ chara ] )
				);
		}
		
		/* "Universal behavior" verifiers. */
		if
		(
			map->handler_index < vt100net_HAND_FALLTHROUGH &&
			vt100net_handlers[ map->handler_index ] == (vt100net_action_handler)0
		)
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( bad_vt100net_handlers.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			return( -4 );
		}
		if( map->handler_index >= vt100net_HAND_FALLTHROUGH )
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( bad_fromAnywhere.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			return( -4 );
		}
		
		
		
		/* State transitions cause: */
			/* 1: the exit action of the initial state */
			/* 2: the transition action */
			/* 3: the entry action of the new state */
		
			/* State-exit section. */
		if( map->nstate != vt100net_termcontext_INVALID )
		{
			/* On-exit path. */
			
			if
			(
				onExit[ state ] < vt100net_HAND_FALLTHROUGH &&
				vt100net_handlers[ onExit[ state ] ] == (vt100net_action_handler)0
			)
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( bad_vt100net_handlers.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				return( -4 );
			}
			if( onExit[ state ] >= vt100net_HAND_FALLTHROUGH )
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( bad_onExit.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				return( -4 );
			}
			
			res = vt100net_handlers[ onExit[ state ] ]( term_ctx, vt100net_termcontext_INVALID );
			if( !res )
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( failed_onExit.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				return( -4 );
			}
		}
		
			/* Event/Transition section. */
		res = vt100net_handlers[ map->handler_index ]( term_ctx, map->nstate );
		if( !res )
		{
			res = term_ctx->res;
				VT100NET_REPORT_ERR(
					term_ctx,
					&( failed_onEvent.type.typeid ),
					__FILE__, __LINE__
				);
			term_ctx->res = res;
			return( -4 );
		}
		
			/* State-entry section. */
		if( map->nstate != vt100net_termcontext_INVALID )
		{
			/* On-entry path. */
			
			if
			(
				onEntry[ state ] < vt100net_HAND_FALLTHROUGH &&
				vt100net_handlers[ onEntry[ state ] ] == (vt100net_action_handler)0
			)
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( bad_vt100net_handlers.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				return( -4 );
			}
			if( onEntry[ state ] >= vt100net_HAND_FALLTHROUGH )
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( bad_onEntry.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				return( -4 );
			}
			
			res = vt100net_handlers[ onEntry[ state ] ]( term_ctx, vt100net_termcontext_INVALID );
			if( !res )
			{
				res = term_ctx->res;
					VT100NET_REPORT_ERR(
						term_ctx,
						&( failed_onEntry.type.typeid ),
						__FILE__, __LINE__
					);
				term_ctx->res = res;
				return( -4 );
			}
		}
		
		
		
		return( 1 );
	}
	
		/* As always, "immediately invalid args". */
	return( -1 );
}


/* Validator functions. */


intmax_t vt100net_termcontext_chartype_hook_validate( vt100net_termcontext_chartype_hooks *hooks )
{
	VT100NET_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME( funcname, __func__ );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			small_count,
			"FATAL: hooks->test_count < vt100net_termcontext_chartype_MAXLEN."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			big_count,
			"FATAL: hooks->test_count > vt100net_termcontext_chartype_MAXLEN."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			null_member,
			"FATAL: hooks->tests[ loop ] had a null function pointer."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			null_whole,
			"FATAL: hooks->tests was null."
		);
	static intmax_t rets[ 4 ] = { 0, 0, 0, 0 };
	int loop;
	if( rets[ 3 ] == 0 )
	{
		loop = 0;
		intmax_t tmp;
		while( loop < 4 )
		{
			switch( loop )
			{
				case 0: tmp = -imaxabs( (intmax_t)&( small_count.type.typeid ) ); break;
				case 1: tmp = -imaxabs( (intmax_t)&( big_count.type.typeid ) ); break;
				case 2: tmp = -imaxabs( (intmax_t)&( null_member.type.typeid ) ); break;
				case 3: tmp = -imaxabs( (intmax_t)&( null_whole.type.typeid ) ); break;
			}
			
			if( tmp >= -2 && tmp <= 1 )
			{
					/* Error message structures overlapped with dedicated error values! */
				return( -2 );
			}
			
			rets[ loop ] = tmp;
			++loop;
		}
	}
	
	if( hooks )
	{
		if( hooks->test_count < vt100net_termcontext_chartype_MAXLEN )
		{
			return( rets[ 0 ] );
		}
		if( hooks->test_count > vt100net_termcontext_chartype_MAXLEN )
		{
			return( rets[ 1 ] );
		}
		
		if( hooks->tests )
		{
			loop = 0;
			while( loop < hooks->test_count )
			{
				if( !( hooks->tests[ loop ] ) )
				{
					return( rets[ 2 ] );
				}
				
				++loop;
			}
			
			return( 1 );
		}
		
		return( rets[ 3 ] );
	}
	
	return( -1 );
}

int vt100net_termcontext_IOhook_validate_innertest( vt100net_termcontext *ctx, vt100net_termcontext_IOhook *hook )
{
	VT100NET_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME( funcname, __func__ );
	
	if( ctx && hook )
	{
		if( !( hook->func ) )
		{
			VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
				&funcname,
				nullhook1,
				"FATAL: Failure while validating IOhook function pointer,"
					" IOhook->func is directly null."
			);
			VT100NET_REPORT_ERR( ctx, &( nullhook1.type.typeid ), __FILE__, __LINE__ );
			return( -2 );
		}
		if( !( *( hook->func ) ) )
		{
			VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
				&funcname,
				nullhook2,
				"FATAL: Failure while validating IOhook function pointer,"
					" IOhook->func is indirectly null."
			);
			VT100NET_REPORT_ERR( ctx, &( nullhook2.type.typeid ), __FILE__, __LINE__ );
			return( -3 );
		}
		
		return( 1 );
	}
	
	return( -1 );
}
int vt100net_termcontext_IOhook_validate( vt100net_termcontext *ctx )
{
	VT100NET_BUILDERRORSTRUCT_SIMPLETYPE_FUNCNAME( funcname, __func__ );
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			null_errdec,
			"FATAL: Failure while validating character type test function pointers."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			null_in,
			"FATAL: Failure while validating character type test function pointers."
		);
		VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
			&funcname,
			null_out,
			"FATAL: Failure while validating character type test function pointers."
		);
	static uint32_t *errmsgs[ 3 ] =
		{
			&( null_errdec.type.typeid ),
			&( null_in.type.typeid ),
			&( null_out.type.typeid )
		};
	
	if( ctx )
	{
		vt100net_termcontext_IOhook *hooks[ 3 ];
			hooks[ 0 ] = &( ctx->errdec );
			hooks[ 1 ] = &( ctx->in );
			hooks[ 2 ] = &( ctx->out );
		int loop = 0, res, ret;
		
		while( loop < 3 )
		{
			res = vt100net_termcontext_IOhook_validate_innertest( ctx, hooks[ loop ] );
			
			switch( res )
			{
				case 1:
					break;
				
				case -1:
					VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
						&funcname,
						null_args,
						"FATAL: Failure calling vt100net_termcontext_IOhook_validate_innertest(), null args detected."
					);
					VT100NET_REPORT_ERR( ctx, &( null_args.type.typeid ), __FILE__, __LINE__ );
					ret = -2;
					break;
				case -2: case -3:
					ret = -3;
					break;
				default:
					VT100NET_BUILDERRORSTRUCT_SIMPLETYPE(
						&funcname,
						bad_ret,
						"FATAL: Failure calling vt100net_termcontext_IOhook_validate_innertest(), invalid return."
					);
					VT100NET_REPORT_ERR( ctx, &( bad_ret.type.typeid ), __FILE__, __LINE__ );
					ret = -4;
					break;
			}
			if( !res )
			{
				VT100NET_REPORT_ERR( ctx, errmsgs[ loop ], __FILE__, __LINE__ );
				return( ret );
			}
			
			++loop;
		}
	}
	
	return( -1 );
}
