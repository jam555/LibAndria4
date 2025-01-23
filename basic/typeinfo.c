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

#include "typeinfo.h"

#if 0
	/* This is an override for things like the CDC Cyber 200 or Intel */
	/*  8051 bit-addressing capabilities. It'll probably never be used. */
	
	#error "Dispatching only currently supports CHAR_BIT!"
	
#elif CHAR_BIT > 32
	#error "CHAR_BIT too large!"
#elif CHAR_BIT > 7
	
	static struct
	{
		libandria4_typeinfo_plaintype nchar, uchar, schar;
		
		libandria4_typeinfo_plaintype uint_8, uint_16, uint_32;
		
	} type_defs =
	{
		{
			{ libandria4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ sizeof( char ) * CHAR_BIT,
				/* alignment */ sizeof( char ) * CHAR_BIT
			}
		},
		{
			{ libandria4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ sizeof( signed char ) * CHAR_BIT,
				/* alignment */ sizeof( signed char ) * CHAR_BIT
			}
		},
		{
			{ libandria4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ sizeof( unsigned char ) * CHAR_BIT,
				/* alignment */ sizeof( unsigned char ) * CHAR_BIT
			}
		},
		
			/* unsigned least 8 */
		{
			{ libandria4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ 8,
				/* alignment */ sizeof( uint_least8_t ) * CHAR_BIT
			}
		},
			/* unsigned least 16 */
		{
			{ libandria4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ 16,
				/* alignment */ sizeof( uint_least16_t ) * CHAR_BIT
			}
		},
			/* unsigned least 32 */
		{
			{ libandria4_typeinfo_typeenum_plain_unsigned },
			{
				/* size */ 32,
				/* alignment */ sizeof( uint_least32_t ) * CHAR_BIT
			}
		}
	};
	
	libandria4_typeinfo_stdtypes libandria4_typeinfo_stdtypes_platform =
	{
		{
			&( type_defs.nchar ), &( type_defs.uchar ), &( type_defs.schar ),
			&( type_defs.uint_8 ), &( type_defs.uint_16 ), &( type_defs.uint_32 )
		},
		{
			&( type_defs.nchar ), &( type_defs.uchar ), &( type_defs.schar ),
			&( type_defs.uint_8 ), &( type_defs.uint_16 ), &( type_defs.uint_32 )
		}
	};
	
	
	
	
	/* The variables below are a pre-written set of type descriptors. */
	/*  It should be filled out more, but will work for now. */
	
	const libandria4_typeinfo_plaintype
		libandria4_typeinfo_descriptor__void =
			{
				{ libandria4_typeinfo_typeenum_plaintype },
				{ 0, 0 }
			},
		
		libandria4_typeinfo_descriptor__char =
			{
				{ libandria4_typeinfo_typeenum_plain_unsigned },
				{ CHAR_BITS * sizeof( char ), 0 }
			},
		
		libandria4_typeinfo_descriptor__size_t =
			{
				{ libandria4_typeinfo_typeenum_plain_unsigned },
				{ CHAR_BITS * sizeof( size_t ), 0 }
			},
		
		libandria4_typeinfo_descriptor__uint8_t =
			{
				{ libandria4_typeinfo_typeenum_plain_unsigned },
				{ CHAR_BITS * sizeof( uint8_t ), 0 }
			},
		libandria4_typeinfo_descriptor__uint16_t =
			{
				{ libandria4_typeinfo_typeenum_plain_unsigned },
				{ CHAR_BITS * sizeof( uint16_t ), 0 }
			},
		libandria4_typeinfo_descriptor__uint32_t =
			{
				{ libandria4_typeinfo_typeenum_plain_unsigned },
				{ CHAR_BITS * sizeof( uint32_t ), 0 }
			},
		
			/* Not listed in the header, because it likely isn't fully */
			/*  portable to use them for other target types. */
		libandria4_typeinfo_descriptor__stdsizedvoidptr =
			{
				{ libandria4_typeinfo_typeenum_pointertype },
				{ CHAR_BITS * sizeof( void* ), 0 }
			},
		libandria4_typeinfo_descriptor__stdsizedcharptr =
			{
				{ libandria4_typeinfo_typeenum_pointertype },
				{ CHAR_BITS * sizeof( char* ), 0 }
			},
		libandria4_typeinfo_descriptor__stdsizedsize_tptr =
			{
				{ libandria4_typeinfo_typeenum_pointertype },
				{ CHAR_BITS * sizeof( size_t* ), 0 }
			};
	const libandria4_typeinfo_derivedtype
		libandria4_typeinfo_descriptor__voidptr =
			{
				{ libandria4_typeinfo_typeenum_plainannotated_pointer },
				
				&libandria4_typeinfo_descriptor__void,
				&libandria4_typeinfo_descriptor__stdsizedvoidptr
			},
		libandria4_typeinfo_descriptor__charptr =
			{
				{ libandria4_typeinfo_typeenum_plainannotated_pointer },
				
				&libandria4_typeinfo_descriptor__char,
				&libandria4_typeinfo_descriptor__stdsizedcharptr
			},
		libandria4_typeinfo_descriptor__size_tptr =
			{
				{ libandria4_typeinfo_typeenum_plainannotated_pointer },
				
				&libandria4_typeinfo_descriptor__size_t,
				&libandria4_typeinfo_descriptor__stdsizedsize_tptr
			};
	
	
	
	const libandria4_typeinfo_plaintype
		libandria4_typeinfo_descriptor__libandria4_typeinfo_typeenum =
			{
				{
				#if 1
						/* Note that this technically depends on a number of */
						/*  things, including machine architecture and whether */
						/*  C23 is in use. However, it is a sane starting */
						/*  point, and thus will be used for now. */
					libandria4_typeinfo_typeenum_plain_twoscomplement
				#endif
				},
				{ CHAR_BITS * sizeof( libandria4_typeinfo_typeenum ), 0 }
			},
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_uinttype =
				/* Initialize based on something already defined. */
			#if LIBANDRIA4_TYPEINFO_UINTTYPE == UINT8_MAX
				libandria4_typeinfo_descriptor__uint8_t
			#elif LIBANDRIA4_TYPEINFO_UINTTYPE == UINT16_MAX
				libandria4_typeinfo_descriptor__uint16_t
			#elif LIBANDRIA4_TYPEINFO_UINTTYPE == UINT32_MAX
				libandria4_typeinfo_descriptor__uint32_t
			#else
				{
					{ libandria4_typeinfo_typeenum_plain_unsigned },
					{ CHAR_BITS * sizeof( size_t ), 0 }
				}
				#error "Error! LibAndria4 / basic / typeinfo.c did not detect a recognized *_uinttype size!"
			#endif
			;
	
	
	
	const libandria4_typeinfo_plaintype
			/* Not listed in the header, because them likely isn't fully */
			/*  portable to use it for other target types. */
		libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype_ptr =
			{
				{ libandria4_typeinfo_typeenum_pointertype },
				{ CHAR_BITS * sizeof( libandria4_typeinfo_pretype* ), 0 }
			},
		libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype_ptrptr =
			{
				{ libandria4_typeinfo_typeenum_pointertype },
				{ CHAR_BITS * sizeof( libandria4_typeinfo_pretype** ), 0 }
			};
	const libandria4_typeinfo_derivedtype
		libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptr =
			{
				{ libandria4_typeinfo_typeenum_plainannotated_pointer },
				
				&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype,
				&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype_ptr
			},
		libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptrptr =
			{
				{ libandria4_typeinfo_typeenum_plainannotated_pointer },
				
				&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptr,
				&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype_ptrptr
			};
	
				static libandria4_typeinfo_pretype
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__pre[ 1 ] =
						{ &libandria4_typeinfo_descriptor__libandria4_typeinfo_typeenum },
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner__pre[ 2 ] =
						{
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_uinttype,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_uinttype
						},
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype__pre[ 2 ] =
						{
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner
						},
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_plainnamingtype__pre[ 2 ] =
						{
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype,
							&libandria4_typeinfo_descriptor__charptr
						},
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_extendedtype__pre[ 3 ] =
						{
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_uinttype,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner
						},
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_plainannotatedtype__pre[ 3 ] =
						{
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptr,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner
						},
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_derivedtype__pre[ 3 ] =
						{
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptr,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptr
						},
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_twintype__pre[ 5 ] =
						{
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_typeenum,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_typeenum,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner
						},
					*libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype__pre[ 4 ] =
						{
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype,
							&libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__ptrptr,
							&libandria4_typeinfo_descriptor__size_tptr,
							&libandria4_typeinfo_descriptor__size_t
						};
				static size_t
					libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__sizet[ 1 ] = { 0 },
					libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner__sizet[ 2 ] =
						{
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plaintype_inner*)1 )->size ) ) -
								( (char*)( (libandria4_typeinfo_plaintype_inner*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plaintype_inner*)1 )->alignment ) ) -
								( (char*)( (libandria4_typeinfo_plaintype_inner*)1 ) )
							)
						},
					libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype__sizet[ 2 ] =
						{
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plaintype*)1 )->header ) ) -
								( (char*)( (libandria4_typeinfo_plaintype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plaintype*)1 )->info ) ) -
								( (char*)( (libandria4_typeinfo_plaintype*)1 ) )
							)
						},
					libandria4_typeinfo_descriptor__libandria4_typeinfo_plainnamingtype__sizet[ 2 ] =
						{
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plainnamingtype*)1 )->header ) ) -
								( (char*)( (libandria4_typeinfo_plainnamingtype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plainnamingtype*)1 )->name ) ) -
								( (char*)( (libandria4_typeinfo_plainnamingtype*)1 ) )
							)
						},
					libandria4_typeinfo_descriptor__libandria4_typeinfo_extendedtype__sizet[ 3 ] =
						{
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_extendedtype*)1 )->header ) ) -
								( (char*)( (libandria4_typeinfo_extendedtype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_extendedtype*)1 )->operand ) ) -
								( (char*)( (libandria4_typeinfo_extendedtype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_extendedtype*)1 )->info ) ) -
								( (char*)( (libandria4_typeinfo_extendedtype*)1 ) )
							)
						},
					libandria4_typeinfo_descriptor__libandria4_typeinfo_plainannotatedtype__sizet[ 3 ] =
						{
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plainannotatedtype*)1 )->header ) ) -
								( (char*)( (libandria4_typeinfo_plainannotatedtype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plainannotatedtype*)1 )->basetype ) ) -
								( (char*)( (libandria4_typeinfo_plainannotatedtype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_plainannotatedtype*)1 )->baseinfo ) ) -
								( (char*)( (libandria4_typeinfo_plainannotatedtype*)1 ) )
							)
						},
					libandria4_typeinfo_descriptor__libandria4_typeinfo_derivedtype__sizet[ 3 ] =
						{
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_derivedtype*)1 )->header ) ) -
								( (char*)( (libandria4_typeinfo_derivedtype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_derivedtype*)1 )->basetype ) ) -
								( (char*)( (libandria4_typeinfo_derivedtype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_derivedtype*)1 )->modifier ) ) -
								( (char*)( (libandria4_typeinfo_derivedtype*)1 ) )
							)
						},
					libandria4_typeinfo_descriptor__libandria4_typeinfo_twintype__sizet[ 5 ] =
						{
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->header ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->A_type ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->B_type ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->A_info ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->B_info ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							)
						},
					libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype__sizet[ 4 ] =
						{
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->header ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->elemtype ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->elemoffset ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							),
							(size_t)(
								( (char*)&( ( (libandria4_typeinfo_twintype*)1 )->elemcount ) ) -
								( (char*)( (libandria4_typeinfo_twintype*)1 ) )
							)
						};
	const libandria4_typeinfo_aggregatetype
		libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{
						CHAR_BITS *
							sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ),
						0
					}
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_pretype__sizet,
				1
			},
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{
						CHAR_BITS *
							sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ),
						0
					}
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype_inner__sizet,
				2
			},
		libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{
						CHAR_BITS *
							sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ),
						0
					}
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_plaintype__sizet,
				2
			},
		libandria4_typeinfo_descriptor__libandria4_typeinfo_plainnamingtype =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{
						CHAR_BITS *
							sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ),
						0
					}
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_plainnamingtype__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_plainnamingtype__sizet,
				2
			},
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_extendedtype =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{
						CHAR_BITS *
							sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ),
						0
					}
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_extendedtype__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_extendedtype__sizet,
				3
			},
		libandria4_typeinfo_descriptor__libandria4_typeinfo_plainannotatedtype =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{
						CHAR_BITS *
							sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ),
						0
					}
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_plainannotatedtype__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_plainannotatedtype__sizet,
				3
			},
		libandria4_typeinfo_descriptor__libandria4_typeinfo_derivedtype =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{
						CHAR_BITS *
							sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ),
						0
					}
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_derivedtype__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_derivedtype__sizet,
				3
			},
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_twintype =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{
						CHAR_BITS *
							sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ),
						0
					}
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_twintype__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_twintype__sizet,
				5
			},
		
		libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype =
			{
				{
					{ libandria4_typeinfo_typeenum_aggregatetype },
					{ CHAR_BITS * sizeof( libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype ), 0 }
				},
				
				libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype__pre,
				libandria4_typeinfo_descriptor__libandria4_typeinfo_aggregatetype__sizet,
				4
			};
#else
	#error "CHAR_BIT too small!"
#endif
