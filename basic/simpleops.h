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

#ifndef LIBANDRIA4_BASIC_SIMPLEOPS_H
# define LIBANDRIA4_BASIC_SIMPLEOPS_H
	
	
	#include "simpleruntimeops.h"
	
		/* For LIBANDRIA4_RETURN_* macros. */
	#include "arraccess.h"
		/* Mostly for true/false defines. */
	#include "../math/numerics.h"
	#include "../math/logic.h"
	#include "sizeofmacros.h"
	#include "nulls.h"
	
	
	#define LIBANDRIA4_OP_UNARYIDENTITY( val ) (val)
	#define LIBANDRIA4_OP_UNARYFROMPTR( val ) ( *(val) )
	#define LIBANDRIA4_OP_UNARYTOPTR( val ) ( &(val) )
	
	
	#define LIBANDRIA4_OP_ISVALvoid( ... ) ( void )
	
	#define LIBANDRIA4_OP_ISVAL0( ... ) ( 0 )
	#define LIBANDRIA4_OP_ISVAL1( ... ) ( 1 )
	#define LIBANDRIA4_OP_ISVAL2( ... ) ( 2 )
	#define LIBANDRIA4_OP_ISVAL3( ... ) ( 3 )
	#define LIBANDRIA4_OP_ISVAL4( ... ) ( 4 )
	#define LIBANDRIA4_OP_ISVAL5( ... ) ( 5 )
	#define LIBANDRIA4_OP_ISVAL6( ... ) ( 6 )
	#define LIBANDRIA4_OP_ISVAL7( ... ) ( 7 )
	#define LIBANDRIA4_OP_ISVAL8( ... ) ( 8 )
	#define LIBANDRIA4_OP_ISVAL9( ... ) ( 9 )
	
	#define LIBANDRIA4_OP_ISVARtmp( ... ) ( tmp )
	#define LIBANDRIA4_OP_ISVARret( ... ) ( ret )
	#define LIBANDRIA4_OP_ISVARres( ... ) ( res )
	#define LIBANDRIA4_OP_ISVARa( ... ) ( a )
	#define LIBANDRIA4_OP_ISVARb( ... ) ( b )
	#define LIBANDRIA4_OP_ISVARc( ... ) ( c )
	#define LIBANDRIA4_OP_ISVARd( ... ) ( d )
	#define LIBANDRIA4_OP_ISVARe( ... ) ( e )
		/* NEVER treat dummy as holding meaningful data, it ONLY exists to */
		/*  fill syntactically-demanded value/variable slots (such as in */
		/*  ternary operations). */
	#define LIBANDRIA4_OP_ISVARdummy( ... ) ( dummy )
	
	
		/* These are somewhat "special": they're used when you need to embed */
		/*  a "set" operation via macro. You can always define more of these */
		/*  if needed. Try not to though. */
	#define LIBANDRIA4_OP_SETtmp( val ) ( tmp = (val) )
	#define LIBANDRIA4_OP_SETret( val ) ( ret = (val) )
	#define LIBANDRIA4_OP_SETres( val ) ( res = (val) )
	#define LIBANDRIA4_OP_SETa( val ) ( a = (val) )
	#define LIBANDRIA4_OP_SETb( val ) ( b = (val) )
	#define LIBANDRIA4_OP_SETc( val ) ( c = (val) )
	#define LIBANDRIA4_OP_SETd( val ) ( d = (val) )
	#define LIBANDRIA4_OP_SETe( val ) ( e = (val) )
		/* NEVER treat dummy as holding meaningful data, it ONLY exists to */
		/*  fill syntactically-demanded value/variable slots (such as in */
		/*  ternary operations). */
	#define LIBANDRIA4_OP_SETdummy( val ) ( dummy = (val) )
	
		/* Take the pointers of variables instead. */
	#define LIBANDRIA4_OP_SETtmpPTR( var ) ( tmp = &(var) )
	#define LIBANDRIA4_OP_SETretPTR( var ) ( ret = &(var) )
	#define LIBANDRIA4_OP_SETresPTR( var ) ( res = &(var) )
	#define LIBANDRIA4_OP_SETaPTR( var ) ( a = &(var) )
	#define LIBANDRIA4_OP_SETbPTR( var ) ( b = &(var) )
	#define LIBANDRIA4_OP_SETcPTR( var ) ( c = &(var) )
	#define LIBANDRIA4_OP_SETdPTR( var ) ( d = &(var) )
	#define LIBANDRIA4_OP_SETePTR( var ) ( e = &(var) )
		/* NEVER treat dummy as holding meaningful data, it ONLY exists to */
		/*  fill syntactically-demanded value/variable slots (such as in */
		/*  ternary operations). */
	#define LIBANDRIA4_OP_SETdummyptr( val ) ( dummy = &(val) )
	
	/* Treat different members AS pointers. */
	#define LIBANDRIA4_OP_SETtmpREF( var ) ( tmp = *(var) )
	#define LIBANDRIA4_OP_SETretREF( var ) ( ret = *(var) )
	#define LIBANDRIA4_OP_SETresREF( var ) ( res = *(var) )
	#define LIBANDRIA4_OP_SETaREF( var ) ( a = *(var) )
	#define LIBANDRIA4_OP_SETbREF( var ) ( b = *(var) )
	#define LIBANDRIA4_OP_SETcREF( var ) ( c = *(var) )
	#define LIBANDRIA4_OP_SETdREF( var ) ( d = *(var) )
	#define LIBANDRIA4_OP_SETeREF( var ) ( e = *(var) )
		/* NEVER treat dummy as holding meaningful data, it ONLY exists to */
		/*  fill syntactically-demanded value/variable slots (such as in */
		/*  ternary operations). */
	#define LIBANDRIA4_OP_SETdummyREF( val ) ( dummy = *(val) )
	
	#define LIBANDRIA4_OP_SETREFtmp( var ) ( *tmp = (var) )
	#define LIBANDRIA4_OP_SETREFret( var ) ( *ret = (var) )
	#define LIBANDRIA4_OP_SETREFres( var ) ( *res = (var) )
	#define LIBANDRIA4_OP_SETREFa( var ) ( *a = (var) )
	#define LIBANDRIA4_OP_SETREFb( var ) ( *b = (var) )
	#define LIBANDRIA4_OP_SETREFc( var ) ( *c = (var) )
	#define LIBANDRIA4_OP_SETREFd( var ) ( *d = (var) )
	#define LIBANDRIA4_OP_SETREFe( var ) ( *e = (var) )
		/* NEVER treat dummy as holding meaningful data, it ONLY exists to */
		/*  fill syntactically-demanded value/variable slots (such as in */
		/*  ternary operations). */
	#define LIBANDRIA4_OP_SETREFdummy( val ) ( *dummy = (val) )
	
	#define LIBANDRIA4_OP_SETREFtmpREF( var ) ( *tmp = *(var) )
	#define LIBANDRIA4_OP_SETREFretREF( var ) ( *ret = *(var) )
	#define LIBANDRIA4_OP_SETREFresREF( var ) ( *res = *(var) )
	#define LIBANDRIA4_OP_SETREFaREF( var ) ( *a = *(var) )
	#define LIBANDRIA4_OP_SETREFbREF( var ) ( *b = *(var) )
	#define LIBANDRIA4_OP_SETREFcREF( var ) ( *c = *(var) )
	#define LIBANDRIA4_OP_SETREFdREF( var ) ( *d = *(var) )
	#define LIBANDRIA4_OP_SETREFeREF( var ) ( *e = *(var) )
		/* NEVER treat dummy as holding meaningful data, it ONLY exists to */
		/*  fill syntactically-demanded value/variable slots (such as in */
		/*  ternary operations). */
	#define LIBANDRIA4_OP_SETREFdummyREF( val ) ( *dummy = *(val) )
	
	#define LIBANDRIA4_OP_SETREFtmpPTR( var ) ( *tmp = &(var) )
	#define LIBANDRIA4_OP_SETREFretPTR( var ) ( *ret = &(var) )
	#define LIBANDRIA4_OP_SETREFresPTR( var ) ( *res = &(var) )
	#define LIBANDRIA4_OP_SETREFaPTR( var ) ( *a = &(var) )
	#define LIBANDRIA4_OP_SETREFbPTR( var ) ( *b = &(var) )
	#define LIBANDRIA4_OP_SETREFcPTR( var ) ( *c = &(var) )
	#define LIBANDRIA4_OP_SETREFdPTR( var ) ( *d = &(var) )
	#define LIBANDRIA4_OP_SETREFePTR( var ) ( *e = &(var) )
		/* NEVER treat dummy as holding meaningful data, it ONLY exists to */
		/*  fill syntactically-demanded value/variable slots (such as in */
		/*  ternary operations). */
	#define LIBANDRIA4_OP_SETREFdummyPTR( val ) ( *dummy = &(val) )
	
	/* These are all about hard-wired values. */
	
	#define LIBANDRIA4_OP_SETtmpTOn1( ... ) ( tmp = -1 )
	#define LIBANDRIA4_OP_SETretTOn1( ... ) ( ret = -1 )
	#define LIBANDRIA4_OP_SETresTOn1( ... ) ( res = -1 )
	#define LIBANDRIA4_OP_SETaTOn1( ... ) ( a = -1 )
	#define LIBANDRIA4_OP_SETbTOn1( ... ) ( b = -1 )
	#define LIBANDRIA4_OP_SETcTOn1( ... ) ( c = -1 )
	#define LIBANDRIA4_OP_SETdTOn1( ... ) ( d = -1 )
	#define LIBANDRIA4_OP_SETeTOn1( ... ) ( e = -1 )
	
	#define LIBANDRIA4_OP_SETtmpTO0( ... ) ( tmp = 0 )
	#define LIBANDRIA4_OP_SETretTO0( ... ) ( ret = 0 )
	#define LIBANDRIA4_OP_SETresTO0( ... ) ( res = 0 )
	#define LIBANDRIA4_OP_SETaTO0( ... ) ( a = 0 )
	#define LIBANDRIA4_OP_SETbTO0( ... ) ( b = 0 )
	#define LIBANDRIA4_OP_SETcTO0( ... ) ( c = 0 )
	#define LIBANDRIA4_OP_SETdTO0( ... ) ( d = 0 )
	#define LIBANDRIA4_OP_SETeTO0( ... ) ( e = 0 )
	
	#define LIBANDRIA4_OP_SETtmpTO1( ... ) ( tmp = 1 )
	#define LIBANDRIA4_OP_SETretTO1( ... ) ( ret = 1 )
	#define LIBANDRIA4_OP_SETresTO1( ... ) ( res = 1 )
	#define LIBANDRIA4_OP_SETaTO1( ... ) ( a = 1 )
	#define LIBANDRIA4_OP_SETbTO1( ... ) ( b = 1 )
	#define LIBANDRIA4_OP_SETcTO1( ... ) ( c = 1 )
	#define LIBANDRIA4_OP_SETdTO1( ... ) ( d = 1 )
	#define LIBANDRIA4_OP_SETeTO1( ... ) ( e = 1 )
	
	#define LIBANDRIA4_OP_SETtmpTO2( ... ) ( tmp = 2 )
	#define LIBANDRIA4_OP_SETretTO2( ... ) ( ret = 2 )
	#define LIBANDRIA4_OP_SETresTO2( ... ) ( res = 2 )
	#define LIBANDRIA4_OP_SETaTO2( ... ) ( a = 2 )
	#define LIBANDRIA4_OP_SETbTO2( ... ) ( b = 2 )
	#define LIBANDRIA4_OP_SETcTO2( ... ) ( c = 2 )
	#define LIBANDRIA4_OP_SETdTO2( ... ) ( d = 2 )
	#define LIBANDRIA4_OP_SETeTO2( ... ) ( e = 2 )
	
	
		/* Sometimes we need to set two at once. */
	#define LIBANDRIA4_OP_SETretres( ret_, res_ ) ( ret = (ret_), res = (res_) )
	#define LIBANDRIA4_OP_SETab( aa, bb ) ( a = (aa), b = (bb) )
	#define LIBANDRIA4_OP_SETbc( bb, cc ) ( b = (bb), c = (cc) )
	#define LIBANDRIA4_OP_SETcd( cc, dd ) ( c = (cc), d = (dd) )
	#define LIBANDRIA4_OP_SETde( dd, ee ) ( d = (dd), e = (ee) )
	
		/* As above, but take the pointer of the first val. */
	#define LIBANDRIA4_OP_SETretPTRres( ret_, res_ ) ( ret = &(ret_), res = (res_) )
	#define LIBANDRIA4_OP_SETaPTRb( aa, bb ) ( a = &(aa), b = (bb) )
	#define LIBANDRIA4_OP_SETbPTRc( bb, cc ) ( b = &(bb), c = (cc) )
	#define LIBANDRIA4_OP_SETcPTRd( cc, dd ) ( c = &(cc), d = (dd) )
	#define LIBANDRIA4_OP_SETdPTRe( dd, ee ) ( d = &(dd), e = (ee) )
	
		/* The pointer of the second val. */
	#define LIBANDRIA4_OP_SETretresPTR( ret_, res_ ) ( ret = (ret_), res = &(res_) )
	#define LIBANDRIA4_OP_SETabPTR( aa, bb ) ( a = (aa), b = &(bb) )
	#define LIBANDRIA4_OP_SETbcPTR( bb, cc ) ( b = (bb), c = &(cc) )
	#define LIBANDRIA4_OP_SETcdPTR( cc, dd ) ( c = (cc), d = &(dd) )
	#define LIBANDRIA4_OP_SETdePTR( dd, ee ) ( d = (dd), e = &(ee) )
	
		/* The pointer of the both vals. */
	#define LIBANDRIA4_OP_SETretPTRresPTR( ret_, res_ ) ( ret = &(ret_), res = &(res_) )
	#define LIBANDRIA4_OP_SETaPTRbPTR( aa, bb ) ( a = &(aa), b = &(bb) )
	#define LIBANDRIA4_OP_SETbPTRcPTR( bb, cc ) ( b = &(bb), c = &(cc) )
	#define LIBANDRIA4_OP_SETcPTRdPTR( cc, dd ) ( c = &(cc), d = &(dd) )
	#define LIBANDRIA4_OP_SETdPTRePTR( dd, ee ) ( d = &(dd), e = &(ee) )
	
	
		/* Returns to match the sets above. */
	#define LIBANDRIA4_OP_RETtmp( ... ) ( return( tmp ) )
	#define LIBANDRIA4_OP_RETret( ... ) ( return( ret ) )
	#define LIBANDRIA4_OP_RETres( ... ) ( return( res ) )
	#define LIBANDRIA4_OP_RETa( ... ) ( return( a ) )
	#define LIBANDRIA4_OP_RETb( ... ) ( return( b ) )
	#define LIBANDRIA4_OP_RETc( ... ) ( return( c ) )
	#define LIBANDRIA4_OP_RETd( ... ) ( return( d ) )
	#define LIBANDRIA4_OP_RETe( ... ) ( return( e ) )
	
	
	#define LIBANDRIA4_OP_RETURNvoid( ... ) return( )
	
	#define LIBANDRIA4_OP_RETURNVAL_n4( ... ) return( -4 )
	#define LIBANDRIA4_OP_RETURNVAL_n3( ... ) return( -3 )
	#define LIBANDRIA4_OP_RETURNVAL_n2( ... ) return( -2 )
	#define LIBANDRIA4_OP_RETURNVAL_n1( ... ) return( -1 )
	
	#define LIBANDRIA4_OP_RETURNVAL_0( ... ) return( 0 )
	
	#define LIBANDRIA4_OP_RETURNVAL_1( ... ) return( 1 )
	#define LIBANDRIA4_OP_RETURNVAL_2( ... ) return( 2 )
	#define LIBANDRIA4_OP_RETURNVAL_3( ... ) return( 3 )
	#define LIBANDRIA4_OP_RETURNVAL_4( ... ) return( 4 )
	#define LIBANDRIA4_OP_RETURNVAL_8( ... ) return( 8 )
	#define LIBANDRIA4_OP_RETURNVAL_9( ... ) return( 9 )
	#define LIBANDRIA4_OP_RETURNVAL_10( ... ) return( 10 )
	#define LIBANDRIA4_OP_RETURNVAL_16( ... ) return( 16 )
	#define LIBANDRIA4_OP_RETURNVAL_32( ... ) return( 32 )
	#define LIBANDRIA4_OP_RETURNVAL_64( ... ) return( 64 )
	#define LIBANDRIA4_OP_RETURNVAL_99( ... ) return( 99 )
	#define LIBANDRIA4_OP_RETURNVAL_100( ... ) return( 100 )
	#define LIBANDRIA4_OP_RETURNVAL_128( ... ) return( 128 )
	#define LIBANDRIA4_OP_RETURNVAL_255( ... ) return( 255 )
	#define LIBANDRIA4_OP_RETURNVAL_256( ... ) return( 256 )
	#define LIBANDRIA4_OP_RETURNVAL_512( ... ) return( 512 )
	#define LIBANDRIA4_OP_RETURNVAL_999( ... ) return( 999 )
	#define LIBANDRIA4_OP_RETURNVAL_1000( ... ) return( 1000 )
	#define LIBANDRIA4_OP_RETURNVAL_1kilo( ... ) return( 1000 )
	#define LIBANDRIA4_OP_RETURNVAL_1KILO( ... ) return( 1000 )
	#define LIBANDRIA4_OP_RETURNVAL_1023( ... ) return( 1023 )
	#define LIBANDRIA4_OP_RETURNVAL_1024( ... ) return( 1024 )
	#define LIBANDRIA4_OP_RETURNVAL_1kibi( ... ) return( 1024 )
	#define LIBANDRIA4_OP_RETURNVAL_1KIBI( ... ) return( 1024 )
	
	
		/* Reserved: LIBANDRIA4_OP_runable1 MUST be equivalent to a function */
		/*  pointer, and LIBANDRIA4_OP_runabledata1 MUST be equivalent to a */
		/*  pointer that it can take as it's first argument. Depending on */
		/*  your usage case, it CAN accept any variety of other arguments, */
		/*  and/or return any type. If the pointer is NULL, then the value */
		/*  of the variable named after *_ELSE will be returned instead of */
		/*  invoking the function pointer. */
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEtmp( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : tmp )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEa( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : a )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEb( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : b )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEc( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : c )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEd( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : d )
	#define LIBANDRIA4_OP_RUNifABLE1_ELSEe( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)( LIBANDRIA4_OP_runabledata1, __VA_ARGS__ ) : e )
	
	/* The definitions below are as above, but the hook names have their */
	/*  contained number swapped to match the relevant macro. */
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEtmp( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : tmp )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEa( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : a )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEb( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : b )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEc( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : c )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEd( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : d )
	#define LIBANDRIA4_OP_RUNifABLE2_ELSEe( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)( LIBANDRIA4_OP_runabledata2, __VA_ARGS__ ) : e )
		
	
	/* The definitions below are as above, but the functions take no args. */
	#define LIBANDRIA4_OP_RUNifABLE1argless_ELSEtmp( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)(  ) : tmp )
	#define LIBANDRIA4_OP_RUNifABLE1argless_ELSEa( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)(  ) : a )
	#define LIBANDRIA4_OP_RUNifABLE1argless_ELSEb( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)(  ) : b )
	#define LIBANDRIA4_OP_RUNifABLE1argless_ELSEc( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)(  ) : c )
	#define LIBANDRIA4_OP_RUNifABLE1argless_ELSEd( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)(  ) : d )
	#define LIBANDRIA4_OP_RUNifABLE1argless_ELSEe( ... ) \
		( (LIBANDRIA4_OP_runable1) ? (LIBANDRIA4_OP_runable1)(  ) : e )
	
	/* As above. */
	#define LIBANDRIA4_OP_RUNifABLE2argless_ELSEtmp( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)(  ) : tmp )
	#define LIBANDRIA4_OP_RUNifABLE2argless_ELSEa( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)(  ) : a )
	#define LIBANDRIA4_OP_RUNifABLE2argless_ELSEb( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)(  ) : b )
	#define LIBANDRIA4_OP_RUNifABLE2argless_ELSEc( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)(  ) : c )
	#define LIBANDRIA4_OP_RUNifABLE2argless_ELSEd( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)(  ) : d )
	#define LIBANDRIA4_OP_RUNifABLE2argless_ELSEe( ... ) \
		( (LIBANDRIA4_OP_runable2) ? (LIBANDRIA4_OP_runable2)(  ) : e )
	
	
	/* As above, except that the result is returned instead of just */
	/*  floating around to be used. */
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1_ELSEtmp( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1_ELSEtmp( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1_ELSEa( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1_ELSEa( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1_ELSEb( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1_ELSEb( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1_ELSEc( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1_ELSEc( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1_ELSEd( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1_ELSEd( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1_ELSEe( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1_ELSEe( __VA_ARGS__ ) ) );
	
	/* As above. */
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2_ELSEtmp( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2_ELSEtmp( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2_ELSEa( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2_ELSEa( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2_ELSEb( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2_ELSEb( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2_ELSEc( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2_ELSEc( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2_ELSEd( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2_ELSEd( __VA_ARGS__ ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2_ELSEe( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2_ELSEe( __VA_ARGS__ ) ) );
	
	
	/* As above. */
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEtmp( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1argless_ELSEtmp(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEa( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1argless_ELSEa(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEb( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1argless_ELSEb(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEc( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1argless_ELSEc(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEd( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1argless_ELSEd(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE1argless_ELSEe( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE1argless_ELSEe(  ) ) );
	
	/* As above. */
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2argless_ELSEtmp( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2argless_ELSEtmp(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2argless_ELSEa( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2argless_ELSEa(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2argless_ELSEb( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2argless_ELSEb(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2argless_ELSEc( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2argless_ELSEc(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2argless_ELSEd( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2argless_ELSEd(  ) ) );
	#define LIBANDRIA4_OP_RETURN_RUNifABLE2argless_ELSEe( ... ) \
		( return( LIBANDRIA4_OP_RUNifABLE2argless_ELSEe(  ) ) );
	
	
	
	#define LIBANDRIA4_STRINGIFY( a ) LIBANDRIA4_INNER_STRINGIFY( a )
	#define LIBANDRIA4_INNER_STRINGIFY( a ) #a
	
	
	#define LIBANDRIA4_BOOLCAT( a, b ) \
		LIBANDRIA4_CAT( LIBANDRIA4_BOOL( a ), LIBANDRIA4_BOOL( b ) )
	#define LIBANDRIA4_CAT( a, ... ) LIBANDRIA4_PRIMITIVE_CAT( a, __VA_ARGS__ )
	#define LIBANDRIA4_PRIMITIVE_CAT( a, ... ) a ## __VA_ARGS__
	
	#define LIBANDRIA4_CONCAT( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	#define LIBANDRIA4_CONCATENATE( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	#define LIBANDRIA4_JOIN( ... ) LIBANDRIA4_CAT( __VA_ARGS__ )
	
	
	#define LIBANDRIA4_CHECK( ... ) LIBANDRIA4_SELECT_2ND( __VA_ARGS__, 0 )
		/* Should x be wrapped in parens for this to work right? */
	#define LIBANDRIA4_PROBE( x ) x, 1,
	
	
	#define LIBANDRIA4_APPLY( func, ... ) func( __VA_ARGS__ )
	#define LIBANDRIA4_APPLY_GATE( flag, func ) \
		LIBANDRIA4_IIF( flag ) ( func, LIBANDRIA4_APPLY_GATE( 1, func ) )
			/* This will initially result in an UNPROCESSED call to */
			/*  *_APPLY_GATE() just sitting amidst your code, but when you */
			/*  run it through EVAL() later it SHOULD get processed. The */
			/*  basic design was created for macrotime/tree.h. You should */
			/*  generally wrap it in another function of your own. */
			/* See also LIBANDRIA4_IDENTITY_LATER() in this same file. */
	#define LIBANDRIA4_APPLY_LATER( func ) LIBANDRIA4_APPLY_GATE( 0, func )
	
	
	/* These generate a function that returns an integer that uniquely */
	/*  identifies the provided type. Extra differentiation via tag, just in */
	/*  case. Use *_IDFUNC() for POD types, use *_IDFUNC2() for non-POD */
	/*  types. And yes, it's ok to use the statics as variables, as long as */
	/*  you know what you're doing. */
	#define LIBANDRIA4_BUILDIDFUNC( type, tag, inner_type ) \
		uintptr_t libandria4_idfunc_type_##type##tag() { \
			static inner_type t; return( (uintptr_t)&t ); }
		/* As above, but with call-once configuration, for more advanced */
		/*  type info. */
	#define LIBANDRIA4_BUILDIDFUNC2( type, tag, inner_type, config_func ) \
		uintptr_t libandria4_idfunc_type_##type##tag() { \
			static inner_type t, *t_ = (inner_type*)0; \
			if( !t_ ) { t_ = &t; config_func( t_ ); } \
			return( (uintptr_t)t_ ); }
	
	
	
	#define LIBANDRIA4_STRIPPARENS( ... ) LIBANDRIA4_STRIPPARENS_INNER __VA_ARGS__
	#define LIBANDRIA4_STRIPPARENS_INNER( ... ) __VA_ARGS__
	
	
	#define LIBANDRIA4_IGNORETHIS_LIBANDRIA4_UNPARENTHESIZE_RECURSE 
	#define LIBANDRIA4_UNPARENTHESIZE( x ) \
		LIBANDRIA4_CAT( LIBANDRIA4_IGNORETHIS_, LIBANDRIA4_UNPARENTHESIZE_RECURSE x )
	#define LIBANDRIA4_UNPARENTHESIZE_RECURSE( ... ) \
		LIBANDRIA4_UNPARENTHESIZE_RECURSE __VA_ARGS__
	
		/* If the first argument has paired parentheses, then this returns */
		/*  1, else 0. */
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED( ... ) \
		LIBANDRIA4_RETURN_1( \
			LIBANDRIA4_CAT( \
				LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_, LIBANDRIA4_TRUEFUNC __VA_ARGS__ \
			) \
		)
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_1 1, ~
	#define LIBANDRIA4_PARENTHESIZE_ISHEADED_FLAG_LIBANDRIA4_TRUEFUNC 0, ~
	
	
	#define LIBANDRIA4_PUSH_COMMA( ... ) ,
	
	
	#define LIBANDRIA4_IS_PAREN( x ) LIBANDRIA4_CHECK( LIBANDRIA4_IS_PAREN_PROBE x )
	#define LIBANDRIA4_IS_PAREN_PROBE( ... ) LIBANDRIA4_PROBE( ~ )
	
	
	#define LIBANDRIA4_PAREN_GATE( func, flag, ... ) \
	    LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( flag ) )( func, LIBANDRIA4_NULL_MACRO )
	#define LIBANDRIA4_PAREN_UNGATE( func, flag, ... ) \
	    LIBANDRIA4_IIF( LIBANDRIA4_IS_PAREN( flag ) )( LIBANDRIA4_NULL_MACRO, func )
	
#endif
/* End libsndria4 basic simpleops.h */
